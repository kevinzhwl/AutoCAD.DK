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
// coordsys.cpp
//
//  This example demonstrates the use of isPerspective(),
//  doPerspective(), getBackAndFrontClippingValues(),
//  polygonDc(), polygonEye(), and polygon().
//
//  To do this, it takes an original line segment in
//  model coords and creates its equivalents in eye
//  and display coords.  When displayed, all lines 
//  will overlap exactly.

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aced.h"
#include "adslib.h"
#include "dbsymtb.h"
#include "acgi.h"
#include "dbapserv.h"

// Helpful constants for setting attributes:

// COLOR
static const Adesk::UInt16 kColorByBlock   = 0;
static const Adesk::UInt16 kRed            = 1;
static const Adesk::UInt16 kYellow         = 2;
static const Adesk::UInt16 kGreen          = 3;
static const Adesk::UInt16 kCyan           = 4;
static const Adesk::UInt16 kBlue           = 5;
static const Adesk::UInt16 kMagenta        = 6;
static const Adesk::UInt16 kWhite          = 7;
static const Adesk::UInt16 kColorByLayer   = 256;

class AsdkCoordSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkCoordSamp);

     AsdkCoordSamp(); 
    ~AsdkCoordSamp();

    virtual Adesk::Boolean  worldDraw(AcGiWorldDraw *);
    void viewportDraw(AcGiViewportDraw *);
    Acad::ErrorStatus transformBy(const AcGeMatrix3d &);

private:

    Adesk::UInt32 mNumVerts;
    AcGePoint3d  *mpVerts;
};


ACRX_DXF_DEFINE_MEMBERS(AsdkCoordSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKCOORDSAMP,AsdkCoord Sample);


AsdkCoordSamp::AsdkCoordSamp() : mNumVerts(4)
{
    mpVerts = new AcGePoint3d[mNumVerts];

    mpVerts[0] = AcGePoint3d(0.0, 0.0, 0.0);
    mpVerts[1] = AcGePoint3d(1.0, 0.0, 0.0);
    mpVerts[2] = AcGePoint3d(0.0, 1.0, 0.0);
    mpVerts[3] = AcGePoint3d(0.0, 0.0, 1.0);
}

AsdkCoordSamp::~AsdkCoordSamp()
{
    delete [] mpVerts;
}


Acad::ErrorStatus
AsdkCoordSamp::transformBy(const AcGeMatrix3d &xfm)
{
    assertWriteEnabled();
    for (Adesk::UInt32 i = 0; i < mNumVerts; i++) {
        mpVerts[i].transformBy(xfm);
    }
    return Acad::eOk;
}


Adesk::Boolean
AsdkCoordSamp::worldDraw(AcGiWorldDraw* pW)
{
    // If regenType is kAcGiSaveWorldDrawForProxy then we
    // must return Adesk::kTrue, otherwise we need to return
    // Adesk::kFalse to trigger calls to our viewportDraw().
    //
    return (pW->regenType() == kAcGiSaveWorldDrawForProxy);
}


// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkCoordSamp::viewportDraw(AcGiViewportDraw* pV)
{
    pV->subEntityTraits().setFillType(kAcGiFillAlways);

    const int count = 3;
    AcGePoint3d verts[count];
    verts[0] = AcGePoint3d(0.0, 0.0, 0.0);
    verts[1] = AcGePoint3d(1.0, 0.0, 0.0);
    verts[2] = AcGePoint3d(1.0, 1.0, 0.0);

    // Draw model space line segment.
    //
    pV->subEntityTraits().setColor(kBlue);
    pV->geometry().polygon(count, verts);
 
    // Compute its representation in eye space.
    //
    AcGeMatrix3d mat;
    pV->viewport().getModelToEyeTransform(mat); 

    for (int i = 0; i < count; i++) {
        verts[i].x += 0.01;
        verts[i].y += 0.01;
        verts[i].z += 0.01;
        verts[i].transformBy(mat);
    }

    // Display the eye coordinate equivalent of the 
    // model space polygon.
    //
    pV->subEntityTraits().setColor(kGreen);
    pV->geometry().polygonEye(count, verts);

    // Convert from eye to display coordinates.
    // 
    for (i = 0; i < count; i++) {
        verts[i].x += 0.01;
        verts[i].y += 0.01;
        verts[i].z += 0.01;
    }

    // Draw the display space equivalent of the
    // model space polygon.
    //
    pV->subEntityTraits().setColor(kRed);
    pV->geometry().polygonDc(count, verts);
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkCoordSampObject()
{
    AsdkCoordSamp *pNewObj = new AsdkCoordSamp;

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlock;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);

    AcDbObjectId objId;
    pBlock->appendAcDbEntity(objId, pNewObj);

    pBlockTable->close();
    pBlock->close();
    pNewObj->close();
}


void
initAsdkCoordSamp()
{
    AsdkCoordSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ASDK_COORD_SAMP",
                            "ASDKCOORDSAMP",
                            "COORDSAMP",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkCoordSampObject);
}


extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkCoordSamp();
        break;
    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup("ASDK_COORD_SAMP");
        deleteAcRxClass(AsdkCoordSamp::desc());
    }
    return AcRx::kRetOK;
}
