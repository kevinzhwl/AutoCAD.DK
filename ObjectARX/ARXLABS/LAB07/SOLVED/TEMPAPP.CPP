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
// tempapp.cpp
//
// ========= tempapp.cc:  ARX Protocol Extension Test ================
//
// Test App for ARX Usage of Protocol Extension in conjunction
// with the AcDb library.
//
// Defines the EntTemperature "property" extension protocol class for
// AcDbEntity,  a default implementation, and specific implementations
// for Circles and Regions.
//
// In addition,  there is the file apistub.cpp that can be used to create
// a static link library of the EntTemperature abstract base class.  This
// static link library can be used by other applications as an API to allow
// them to derive their own speciality classes from EntTemperature to
// extend their own classes.
//
// Since this application can be used as a server for other apps,  it must
// have a dependency registration mechanism so that when other apps are
// relying on it,  it cannot be unloaded.  The dependency() function in
// this program serves this purpose.  dependency() is an exported function
// (look in the tempapp.def file) that other applications can access via
// the ARX service registery,  so that they can call it to register a
// dependency on this program causing it to lock itself to prevent unloading.
// when the dependency count is 0,  this app will unlock itself so that it
// can be unloaded.


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rxregsvc.h"
#include "aced.h"
#include "adslib.h"
#include "dbents.h"
#include "dbregion.h"
#include <dbelipse.h>

// This app's exported Protocol Extension Class
//
#include "enttemp.h"


// Status checking
//
Adesk::Boolean
statOk(Acad::ErrorStatus stat)
{
    if (stat == Acad::eOk)
        return Adesk::kTrue;
    ads_printf("\nStatus Check Failed:  %d\n", stat);
    return Adesk::kFalse;
}

// getYorN - utility function to get boolean from user:
//
static Adesk::Boolean
getYorN(const char* pStr)
{
    char yorn_str[132];

    yorn_str[0] = 'Y';
    yorn_str[1] = '\0';
    ads_printf("\n%s", pStr);
    ads_initget(0, "No Yes");
    ads_getkword(" -- No/<Yes>:  ", yorn_str);
    return(yorn_str[0] != 'N');
}

AcDbEntity*
selectEntity(AcDbObjectId& eId, AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;
    int ss;

    if ((ss = ads_entsel("\nSelect an Entity:  ", en, pt)) != RTNORM) {
        ads_printf("Nothing Selected, Return Code==%d\n", ss);
        return NULL;
    }

    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id.
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

// printObjectInfo - utility function to print object info:
//
void
printObjectInfo(const AcDbObject* obj)
{

    AcDbHandle objHandle;
    obj->getAcDbHandle(objHandle);

    char handleStr[20];
    objHandle.getIntoAsciiBuffer(handleStr);
    const char *pCname = obj->isA()->name();

    ads_printf("Object Id %lx, handle %s, class %s.\n", obj->objectId(),
        handleStr, pCname);
}

// printObjectInfo - utility function to print object info:
//
void
printObjectInfo(const AcDbObjectId& id)
{
    AcDbObject *pObj;

    if (acdbOpenObject(pObj, id, AcDb::kForRead) != Acad::eOk) {
        ads_printf("printObjectInfo: open object failed.\n");
    } else {
        printObjectInfo(pObj);
        pObj->close();
    }
}

/* =================== EntTemperature Protocol Extension Class  ========= */

// Temperature extension:  maintains a temperature member variable in XData.
// on relevant entities.

ACRX_NO_CONS_DEFINE_MEMBERS(EntTemperature,AcRxObject);

class DefaultTemperature : public EntTemperature
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

double
DefaultTemperature::reflectedEnergy(AcDbEntity* pEnt) const
{
    ads_printf("\nThis entity has no area, and no reflection.\n");
    return -1.0;
}

// --- EntTemperature implementation for Regions.

class RegionTemperature : public EntTemperature
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

double
RegionTemperature::reflectedEnergy(AcDbEntity* pEnt) const
{
    AcDbRegion *pRegion = AcDbRegion::cast(pEnt);

    if (pRegion == NULL)
        ads_printf("\nThe impossible has happened!");

    // Compute reflected energy as region area multiplied by a
    // Dummy constant.  Could be computed from other AcDbRegion
    // values or app-specific XData, in practice.  But this
    // bogus computation complements the bogus property.
    //
    double retVal;
    if (pRegion->getArea(retVal) != Acad::eOk)
        return -1.0;

    return retVal * 42.0;
}

// --- EntTemperature implementation for circles.

class CircleTemperature : public EntTemperature
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

#define PI 6.21

double
CircleTemperature::reflectedEnergy(AcDbEntity* pEnt) const
{
    AcDbCircle *pCircle = AcDbCircle::cast(pEnt);

    // Compute reflected energy in manner distinctly different
    // than for AcDbRegion.  Had this been a real application,
    // This would have made more sense.
    //
    return pCircle->radius() * PI * 42.0;
}

// OPTIONAL:
// Create a class EllipseTemperature derived from EntTemperature
// that provides the EntTemperature protocol for AcDbEllipse.
// ...next 17 lines conmplete this...

class EllipseTemperature : public EntTemperature
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

double
EllipseTemperature::reflectedEnergy(AcDbEntity* pEnt) const
{
    AcDbEllipse *pEllipse = AcDbEllipse::cast(pEnt);

    // Compute reflected energy in manner distinctly different
    // than for AcDbRegion.  Had this been a real application,
    // This would have made more sense.
    //
    return pEllipse->radiusRatio() * 42.0;
}

// Protocol Extension Object pointers.  These pointers are global so
// that they can be accessed during initialization and cleanup
//
DefaultTemperature *pDefaultTemp;
RegionTemperature  *pRegionTemp;
CircleTemperature  *pCircleTemp;
// if you have done EllipseTemperature class,  declare a pointer to
// an objectof it's type here.
// ...next line completes...
EllipseTemperature *pEllipseTemp;

/* ============Exported function that other apps can call ============ */

double
energy(AcDbEntity* pEnt)
{
    double eTemp;
    // add a call to execute the protocol extension class function for
    // the entity pointed to by pEnt.  You'll need to use the ACRX_X_CALL
    // macro for this.  Have the return value assigned to eTemp.
    //
    // ...next line completes this...
    eTemp = ACRX_X_CALL(pEnt, EntTemperature)->reflectedEnergy(pEnt);

    return eTemp;
}

/* =================== Commands defined in this Module ================ */

void
printEnergy()
{
    AcDbEntity *pEnt;
    AcDbObjectId pEntId;

    if ((pEnt = selectEntity(pEntId, AcDb::kForRead)) == NULL) {
        return;
    }
    ads_printf("\nEnergy == %f Joules\n", energy(pEnt));
    statOk(pEnt->close());
}

/* =================== ARx Module Interface Functions ================ */

// Initialization
//
void
initApp()
{
    EntTemperature::rxInit();
    acrxBuildClassHierarchy();

    pDefaultTemp = new DefaultTemperature();
    pRegionTemp = new RegionTemperature();
    pCircleTemp = new CircleTemperature();
    // if you've done EllipseTemperature class, create a new
    // EllipseTemperature object and assign it's address to the
    // EllipseTemperature variable you declared globally earlier.
    // ...next line completes...
    pEllipseTemp = new EllipseTemperature;

    // Add the protocol extension objects to AcDbEntity, AcDbRegion, and
    // AcDbCircle.  You'll need to use the AcRxClass::addX function to
    // do this.  If you've done an EllipseTemperature class you'll need to
    // do one for it too.
    //
    // ...next four lines complete this...
    AcDbEntity::desc()->addX(EntTemperature::desc(), pDefaultTemp);
    AcDbRegion::desc()->addX(EntTemperature::desc(), pRegionTemp);
    AcDbCircle::desc()->addX(EntTemperature::desc(), pCircleTemp);
    AcDbEllipse::desc()->addX(EntTemperature::desc(), pEllipseTemp);

    // Add a command to report the temperature
    //
    ads_printf("Loading Tempapp, command ENERGY.\n");

    acedRegCmds->addCommand("TEMPERATURE_APP", "ENERGY", "ENERGY",
        ACRX_CMD_TRANSPARENT, printEnergy);
}

// Cleanup
//
void
unloadApp()
{
    delete acrxServiceDictionary->remove(TEMPERATURE_SERVICE);

    acedRegCmds->removeGroup("TEMPERATURE_APP");

    // Remove the protocol extension objects from the AcRxClass objects using
    // AcRxClass::delX.  Then delete the protocol extension objects pointed to
    // by pDefaultTemp, pRegionTemp, pCircleTemp (and EllipseTemperature pointer
    // if implemented).  The delX calls must be done *before* the EntTemperature
    // base class is removed from the runtime tree so that it's ::desc is
    // still valid.  If you've done an EllipseTemperature class don't forget
    // to remove it as well.
    // ...next eight lines complete...
    AcDbEntity::desc()->delX(EntTemperature::desc());
    delete pDefaultTemp;
    AcDbRegion::desc()->delX(EntTemperature::desc());
    delete pRegionTemp;
    AcDbCircle::desc()->delX(EntTemperature::desc());
    delete pCircleTemp;
    AcDbEllipse::desc()->delX(EntTemperature::desc());
    delete pEllipseTemp;

    // remove the EntTemperature abstract base class from the AcRx runtime tree
    //
    deleteAcRxClass(EntTemperature::desc());
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    static void *pSvc, *moduleHandle;

    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        pSvc = acrxRegisterService(TEMPERATURE_SERVICE);
        moduleHandle = pkt;
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;

    // The kDependencyMsg gets sent when a service this app has registered
    // has it's dependency count incremented from 0 to 1 (via a call to
    // the service's addDependency() method).  When this message is sent,
    // the pkt argument is a pointer to the AcRxService object that has had
    // the dependency count bumped.  This allows an app with multiple
    // services registered to tell which one is sending the message.
    //
    case AcRx::kDependencyMsg:
        // Since we only have one service registered, this should
        // always be true,  but it doesn't hurt to be sure.
        // So,  we've got a dependency. Lock ourself so we can't be
        // unloaded.
        //
        if (pSvc == pkt)
            acrxDynamicLinker->lockApplication(moduleHandle);
        break;
    // The kNoDependencyMsg gets sent when a service this app has registered
    // has it's dependency count decremented from 1 to 0 (via a call to
    // the service's removeDependency() method).  When this message is sent,
    // the pkt argument is a pointer to the AcRxService object that has had
    // the dependency count zero'd.  As with the kDependency method, this
    // allows an app with multiple services registered to tell which one is
    // sending the message.
    //
    case AcRx::kNoDependencyMsg:
        // No more dependency,  so unlock to make it possible to be
        // unloaded.
        //
        if (pSvc == pkt)
            acrxDynamicLinker->unlockApplication(moduleHandle);
    }
    return AcRx::kRetOK;
}
