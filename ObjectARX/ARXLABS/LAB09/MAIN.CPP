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
//            and add it to the database
//
// The entity is created by the AutoCAD command JBLOB.
// All other protocol is accessed by the polymorphism 
// of the AutoCAD editing commands.


#include <string.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "jblob.h"


// Function Prototypes
//
void createJblob(void);
void acquireJblob(Jblob* pJ);
Adesk::Boolean append(AcDbEntity* pEntity);
upt2wgept(ads_point p1, AcGePoint3d& p2);
AcGeVector3d zUcs();
void initApp(void);
void unloadApp(void);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void*);


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
    ads_point p, q;
    double r;

    if (ads_getpoint(NULL, "From point: ", p) == RTNORM
        && ads_getpoint(p, "To point: ", q) == RTNORM
        && ads_grdraw(p, q, -1, 1) == RTNORM
        && ads_getdist(q, "Blob radius: ", &r) == RTNORM)
    {
        AcGePoint3d s, t;
        upt2wgept(p, s);
        upt2wgept(q, t);

        pJ->setEp(s);
        pJ->setBp(t);
        pJ->setBr(r);

        pJ->setNormal(zUcs());

        append(pJ);
        pJ->close();
    }
}

// append - append an opened entity to paper space in the database:
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

int
upt2wgept(ads_point p1, AcGePoint3d& p2)
{
    struct resbuf wcs,ucs;
    wcs.restype     = RTSHORT;
    wcs.resval.rint = 0;
    ucs.restype     = RTSHORT;
    ucs.resval.rint = 1;

    ads_point temp;
    int stat;
    if ((stat = ads_trans(p1, &ucs, &wcs, 0, temp)) != RTNORM)
        return stat;

    p2[X] = temp[X];
    p2[Y] = temp[Y];
    p2[Z] = temp[Z];

    return RTNORM;
}

// getZucs - retrieve Model Space UCS Z coordinate:
//
AcGeVector3d
zUcs()
{
    AcGeVector3d x = acdbCurDwg()->ucsxdir();
    AcGeVector3d y = acdbCurDwg()->ucsydir();
    
    return (x.crossProduct(y)).normalize();
}

void
initApp()
{
    acedRegCmds->addCommand("JBLOB_CMDS", "JBLOB", "JBLOB",
        ACRX_CMD_MODAL, createJblob);

    Jblob::rxInit();
    acrxBuildClassHierarchy();
}

void
unloadApp()
{
    acedRegCmds->removeGroup("JBLOB_CMDS");

    // remove the Jblob class from the AcRx runtime tree.  This will cause
    // any existing Joblob entities to become proxies if this app is unloaded
    // while AutoCAD is still active.
    //
    deleteAcRxClass(Jblob::desc());

}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    }
    return AcRx::kRetOK;
}
