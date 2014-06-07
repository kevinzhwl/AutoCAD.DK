// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// Description:
//
// This program demonstrates the use of some of the
// AcDbCurve protocol

#include <stdlib.h>
#include <string.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbelipse.h>
#include <dbsymtb.h>
#include <adslib.h>
#include <geassign.h>
#include <dbapserv.h>

void curves();
void projectEllipse(AcDbObjectId ellipseId);
void offsetEllipse(AcDbObjectId ellipseId);
Acad::ErrorStatus addToModelSpace(AcDbObjectId&, AcDbEntity*);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// This is the main function of this app.  It allows the
// user to select an entity.  It then checks to see if the
// entity is an ellipse.  If so, it calls projectCurve
// passing in the objectId of the ellipse.
//
void
curves()
{
    // Have the user select an ellipse.
    ads_name en;
    AcGePoint3d pt;
    if (acedEntSel("\nSelect an Ellipse: ", en,
        asDblArray(pt)) != RTNORM)
    {
        acutPrintf("\nNothing selected");
        return;
    }

    // Now, exchange the ads_name for the object Id.
    //
    AcDbObjectId eId;
    acdbGetObjectId(eId, en);

    // If the entity is an ellipse, pass its objectId to the
    // function that will project it onto another plane.
    //
    AcDbObject *pObj;
    acdbOpenObject(pObj, eId, AcDb::kForRead);
    if (pObj->isKindOf(AcDbEllipse::desc())) {
        pObj->close();
    
        int rc;
        char kw[20];
        acedInitGet(0, "Offset Project");
        rc = acedGetKword("Offset/<Project>: ", kw);

        if ((rc != RTNORM) && (rc != RTNONE)) {
            acutPrintf("\nNothing selected.");
            return;
        } else if (rc == RTNONE
            || strcmp(kw, "Project") == 0)
            projectEllipse(eId);
        else
            offsetEllipse(eId);
    } else {
        pObj->close();
        acutPrintf("\nSelected entity is not an ellipse");
    }
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Accepts an ellipse object ID, opens the ellipse, and uses
// its getOrthoProjectedCurve member function to create a
// new ellipse that is the result of a projection onto the
// plane with normal <1,1,1>.  The resulting ellipse is
// added to the model space block Table Record.
//
void
projectEllipse(AcDbObjectId ellipseId)
{
    AcDbEllipse *pEllipse;
    acdbOpenObject(pEllipse, ellipseId, AcDb::kForRead);

    // Now project the ellipse onto a plane with a
    // normal of <1, 1, 1>.
    //
    AcDbEllipse *pProjectedCurve;
    pEllipse->getOrthoProjectedCurve(AcGePlane(
        AcGePoint3d::kOrigin, AcGeVector3d(1, 1, 1)),
        (AcDbCurve*&)pProjectedCurve);
    pEllipse->close();

    AcDbObjectId newCurveId;
    addToModelSpace(newCurveId, pProjectedCurve);
}

// Accepts an ellipse object ID, opens the ellipse, and uses
// its getOffsetCurves() member function to create a new
// ellipse that is offset 0.5 drawing units from the
// original ellipse.
//
void
offsetEllipse(AcDbObjectId ellipseId)
{
    AcDbEllipse *pEllipse;
    acdbOpenObject(pEllipse, ellipseId, AcDb::kForRead);

    // Now generate an ellipse offset by 0.5 drawing units.
    //
    AcDbVoidPtrArray curves;
    pEllipse->getOffsetCurves(0.5, curves);
    pEllipse->close();

    AcDbObjectId newCurveId;
    addToModelSpace(newCurveId, (AcDbEntity*)curves[0]);
}

// END CODE APPEARING IN SDK DOCUMENT.

// Accepts a pointer to an entity object and adds it to the
// Model Space block table record.
//
Acad::ErrorStatus
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;
    AcDbBlockTableRecord *pSpaceRecord;

    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
        AcDb::kForWrite);

    pBlockTable->close();

    pSpaceRecord->appendAcDbEntity(objId, pEntity);

    pEntity->close();
    pSpaceRecord->close();

    return Acad::eOk;
}


// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
//
void
initApp()
{
    acedRegCmds->addCommand("ASDK_CURVETEST", "ASDK_CURVES",
        "CURVES", ACRX_CMD_MODAL, curves);
}


// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this app's
// command set from the command stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_CURVETEST");
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
