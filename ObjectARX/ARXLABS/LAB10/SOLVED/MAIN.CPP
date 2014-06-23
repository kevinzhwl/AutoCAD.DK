// (C) Copyright 1996 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
// main.cpp - Provides the protocol necessary to create a Jblob entity
//            and add it to the database.  In this lab we also add in
//            Protocol Extension functionality
//
// The entity is created by the AutoCAD command JBLOB.
// All other protocol is accessed by the polymorphism 
// of the AutoCAD editing commands.
//
// For protocol extension we make use of an EntTemperature protocol extension
// API exported from Lab07.  This means that we must create a static link
// library of the EntTemperature abstract base class in Lab07.  To do this we
// use the APISTUB.CPP source file in the lab07 directory.  This source file
// uses a special ACRX macro called ACRX_DEFINE_MEMBERS which defines all the
// members except for rxInit().  So,  the resulting class has all the necessary
// functionality to allow it to be used to derive from,  but it cannot be added
// to the ARX runtime tree.  Thus the original tempapp.arx must be loaded
// before the EntTemperature class will be present in the ARX runtime tree.
//
// This program will also make use of an exported function in lab07's
// tempapp.cpp,  namely dependency().  This function is in tempapp.cpp to allow
// other apps to register dependencies.  If a dependency is registered,  then
// tempapp will lock itself so that it cannot be unloaded.  When all
// dependencies are removed,  then tempapp will unlock itself so that it can be
// unloaded.
//
// In order to access the dependency() function,  this program makes use of the
// service registery and it's mechanism to return a pointer to a function in
// another application.
//
// This program also defines an ARX Dynamic Linker Reactor which is attached to
// the dynamic linker if this app is loaded and tempapp.arx is not already loaded.
// The reactor then watches to see if tempapp.arx loads.  If it does,  then the
// reactor automatically adds the Jblob protocol extension to the AcRxClass object
// for the Jblob class and calls the dependency() function in tempapp.arx to
// register the dependency.


#include <string.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "jblob.h"

// --- Protocol Extension Test

#include "enttemp.h"


// Function Prototypes
//
void createJblob(void);
void acquireJblob(Jblob* pJ);
Adesk::Boolean append(AcDbEntity* pEntity);
int getPoint(double *pF, char* pMessage, AcGePoint3d& point);
void initApp(void);
void unloadApp(void);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void*);


// --- EntTemperature implementation for Jblob.

// define a new class jblobTemperature, derived from
// EntTemperature and override the member function
// reflectedEnergy any way you see fit. Its exact
// signature is
// 'double reflectedEnergy(AcDbEntity* pEnt) const'
//
// ... The following 17 lines complete this ...

class JblobTemperature : public EntTemperature
{
public:
    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

double
JblobTemperature::reflectedEnergy(AcDbEntity* pEnt) const
{
    Jblob *pBlob = Jblob::cast(pEnt);

    // Nonsensical, yet controllable computation.
    double radval;
    pBlob->radius(radval);
    return (3.14159 * radval * radval);  // using the area as the energy value
}

// Jblob protocol extension object

JblobTemperature* JblobTemp = NULL;

void
createJblob()
{
    Jblob *pJ = new Jblob;

    if (!pJ)
        ads_printf("Error creating Jblob.\n");
    else
        acquireJblob(pJ);
}

// acquireJblob - acquire Jblob parameters from user:
//
void
acquireJblob(Jblob* pJ)
{
    AcGePoint3d p, q;
    double r;

    if (getPoint(0, "From point: ", p) == RTNORM
        && getPoint((double*)(&p), "To point: ", q) == RTNORM
        && ads_grdraw((double*)(&p), (double*)(&q), -1, 1) == RTNORM
        && ads_getdist((double*)(&q), "Blob radius: ", &r) == RTNORM)
    {
        pJ->setEp(p);
        pJ->setBp(q);
        pJ->setBr(r);
        append(pJ);
        pJ->close();
    }
}

// append - append an opened entity to Model Space in the database:
//
Adesk::Boolean
append(AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;
    Acad::ErrorStatus es = acdbCurDwg()->getBlockTable(pBlockTable,
        AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table!");
        return Adesk::kFalse;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table record!");
        pBlockTable->close();
        return Adesk::kFalse;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
    if (es != Acad::eOk) {
        ads_alert("Failed to append entity!");
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return Adesk::kFalse;
    }
    pBlockRec->close();
    pBlockTable->close();
    return Adesk::kTrue;
}

// getPoint - acquire WCS point from user:
//
int
getPoint(double *pF, char* pMessage, AcGePoint3d& point)
{
    int stat;
    ads_point ptU, ptW;
    struct resbuf rbFrom, rbTo;

    if ((stat = ads_getpoint(pF, pMessage, ptU)) != RTNORM)
        return stat;

    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1;     // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0;       // to WCS

    if ((stat = ads_trans(ptU, &rbFrom, &rbTo, FALSE, ptW)) != RTNORM)
        return stat;

    point[X] = ptW[X];
    point[Y] = ptW[Y];
    point[Z] = ptW[Z];

    ads_printf("\n");
    return RTNORM;
}


// forward declaration for the AppEventCatcher class to use
//
Adesk::Boolean addJblobTemp();


// Dynamic linker reactor to watch for loading of tempapp server application
//
class AppEventCatcher : public AcRxDLinkerReactor {
 
  public:
 
    virtual void rxAppLoaded(const char* moduleName);

    static short thisAppLoaded;
};


short AppEventCatcher::thisAppLoaded = 0;


void
AppEventCatcher::rxAppLoaded(const char* moduleName)
{
    if (!thisAppLoaded) {
        addJblobTemp();
    }
}


AcDbEntity*
selectEntity(AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;
    int ss;

    if ((ss = ads_entsel("\nSelect a Jblob:  ", en, pt)) != RTNORM) {
        ads_printf("Nothing Selected, Return Code==%d\n", ss);
        return NULL;
    }

    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id.
    AcDbObjectId eId;
    Acad::ErrorStatus retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        ads_printf("\nacdbGetObjectId failed");
        ads_printf("\nen==(%lx,%lx), retStat==%d\n", en[0], en[1], eId);
        return NULL;
    }

    AcDbEntity *pEntObj = NULL;

    if ((retStat = acdbOpenObject(pEntObj, eId, openMode))
        != Acad::eOk) {
        ads_printf(
            "\nacdbOpenObject failed: ename=(%lx,%lx), mode==%d retStat==%d\n",
            en[0], en[1], openMode, retStat);
        return NULL;
    }
    return pEntObj;
}


void
energyReport()
{
        // First we need a Jblob entity to work with
        //
        AcDbEntity *pEnt = selectEntity(AcDb::kForRead);

        if (!pEnt)
            return;

        Jblob *pBlob = Jblob::cast(pEnt);
        if (!pBlob) {
            ads_printf("The entity selected is not a Jblob\n");
            pEnt->close();
            return;
        }

        // get a pointer to the energy function in the tempapp server
        //
        EnergyFuncPtr func = NULL;
        func = (EnergyFuncPtr) acrxGetServiceSymbolAddr(TEMPERATURE_SERVICE,
            "energy");
        
        // Now get the energy value for the selected Jblob
        //
        if (func) {
            double energy = (*func)(pBlob);
            double radius;
            pBlob->radius(radius);
            double area = 3.14159 * radius * radius;
            ads_printf("Selected Jblob has an area of %f and an"
                " energy value of %f Joules\n", area, energy);
        }
        pEnt->close();
}


Adesk::Boolean
addJblobTemp()
{
    if (acrxClassDictionary->at("EntTemperature")) {
        ads_printf ("The EntTemperature is now available. Now adding "
            "temperature protocol extension to Jblob.\n");
        
        // increment the dependency counter.  If successful,  then add the Jblob
        // temperature protocol extension
        //
        AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
            ->at(TEMPERATURE_SERVICE);
        if (pSvc) {
            pSvc->addDependency();
            JblobTemp = new JblobTemperature();
            Jblob::desc()->addX(EntTemperature::desc(), JblobTemp);
            AppEventCatcher::thisAppLoaded = 1;
            // Also register the command that will use the energy() function
            // in tempapp.arx
            //
            acedRegCmds->addCommand("JBLOB_CMDS", "ENERGY_REPORT",
                "ENERGY_REPORT", ACRX_CMD_MODAL, energyReport);

            return Adesk::kTrue;
        }
    }
    return Adesk::kFalse;
}


void
initApp()
{
    acedRegCmds->addCommand("JBLOB_CMDS", "JBLOB", "JBLOB",
        ACRX_CMD_MODAL, createJblob);
    Jblob::rxInit();
    acrxBuildClassHierarchy();

    // add temperature protocol extension to Jblob:
    //
    if (!addJblobTemp()) {
        ads_printf ("%s has not been registered; unable to "
            "add its protocol extension to Jblob.\n", TEMPERATURE_SERVICE );
        ads_printf( "Please arxload it and then use JBLOBEXT command "
            "to add protocol extension to Jblob.\n" );
    }
}

void
unloadApp()
{
    acedRegCmds->removeGroup("JBLOB_CMDS");

    // If we are unloading because AutoCAD is shutting down,
    // then it's possible that the tempapp.arx application is
    // already gone,  so we need to check to see if it's still
    // there.  If it's not,  then we can't remove the protocol
    // extension nor decrement the dependency counter.
    //
    if (acrxClassDictionary->at("EntTemperature")) {
        // remove the Jblob protocol extension.
        //
        Jblob::desc()->delX(EntTemperature::desc());
        delete JblobTemp;

        // decrement the dependency counter in the tempapp server application
        //
        AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
            ->at(TEMPERATURE_SERVICE);
        if (pSvc)
            pSvc->removeDependency();
    }

    // remove the Jblob class from the AcRx runtime tree.  This will cause
    // any existing Joblob entities to become proxies if this app is unloaded
    // while AutoCAD is still active.
    //
    deleteAcRxClass(Jblob::desc());
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    static AppEventCatcher* appEventCatcher = NULL;

    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
	    
        // if tempapp server isn't present,  then create and attach
        // a dynamic linker reactor to watch to see if it ever loads up
        //
        if (!acrxClassDictionary->at("EntTemperature")) {
	        appEventCatcher = new AppEventCatcher();
	        acrxDynamicLinker->addReactor(appEventCatcher);
        }
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
	    if (appEventCatcher != NULL)
	        acrxDynamicLinker->removeReactor(appEventCatcher);
        unloadApp();
    }
    return AcRx::kRetOK;
}
