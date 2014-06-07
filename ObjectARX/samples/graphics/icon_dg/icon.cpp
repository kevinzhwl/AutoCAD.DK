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
// icon.cpp
//
//  This example demonstrates the main use of polylineDc(),
//  polygonDc() and getViewportDcCorners() -- graphics
//  that depend on the physical layout of the viewport,
//  such as icons, markers, or borders that vary with the
//  size of the viewport.
//
//  For the demonstration, this example draws a box in
//  the upper right corner of the viewport.  The box's
//  width and height are always a tenth of the viewport's
//  shortest dimension and are centered a tenth of the
//  viewport's shortest dimension down and to the left of
//  the upper righthand corner of the viewport.

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"

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

class AsdkIconSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkIconSamp);

    AsdkIconSamp(); 
    ~AsdkIconSamp();

    virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    void viewportDraw(AcGiViewportDraw*);
    Acad::ErrorStatus transformBy(const AcGeMatrix3d&);

private:

    Adesk::UInt32 mNumVerts;
    AcGePoint3d *pmVerts;
};

ACRX_DXF_DEFINE_MEMBERS(AsdkIconSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKICONSAMP,Icon Sample);


AsdkIconSamp::AsdkIconSamp() : mNumVerts(4)
{
    pmVerts = new AcGePoint3d[mNumVerts];
    pmVerts[0] = AcGePoint3d(0.0, 0.0, 0.0);
    pmVerts[1] = AcGePoint3d(1.0, 0.0, 0.0);
    pmVerts[2] = AcGePoint3d(0.0, 1.0, 0.0);
    pmVerts[3] = AcGePoint3d(0.0, 0.0, 1.0);
}


AsdkIconSamp::~AsdkIconSamp()
{
    delete [] pmVerts;
}


Acad::ErrorStatus
AsdkIconSamp::transformBy(const AcGeMatrix3d &xfm)
{
    assertWriteEnabled();
    for (Adesk::UInt32 i = 0; i < mNumVerts; i++) {
        pmVerts[i].transformBy(xfm);
    }
    return Acad::eOk;
}


Adesk::Boolean
AsdkIconSamp::worldDraw(AcGiWorldDraw* pW)
{
    // If regenType is kAcGiSaveWorldDrawForProxy then we
    // must return Adesk::kTrue, otherwise we need to return
    // Adesk::kFalse to trigger calls to our viewportDraw().
    //
    return (pW->regenType() == kAcGiSaveWorldDrawForProxy);
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkIconSamp::viewportDraw(AcGiViewportDraw* pV)
{
    // Get the current viewport's display coordinates.
    //
    AcGePoint2d lower_left, upper_right;
    pV->viewport().getViewportDcCorners(lower_left,
        upper_right);

    double xsize = upper_right.x - lower_left.x;
    double ysize = upper_right.y - lower_left.y;

    xsize /= 10.0;
    ysize /= 10.0;

    double xcenter = upper_right.x - xsize;
    double ycenter = upper_right.y - ysize;

    double half_xsize = xsize / 2.0;
    double half_ysize = ysize / 2.0;

    // Create a unit square.
    //
    const int num_verts = 5;

    AcGePoint3d verts[num_verts];

    for (int i = 0; i < num_verts; i++) {
        verts[i].x = xcenter;
        verts[i].y = ycenter;
        verts[i].z = 0.0;
    }
    verts[0].x -= half_xsize;
    verts[0].y += half_ysize;
    verts[1].x += half_xsize;
    verts[1].y += half_ysize;
    verts[2].x += half_xsize;
    verts[2].y -= half_ysize;
    verts[3].x -= half_xsize;
    verts[3].y -= half_ysize;

    verts[4] = verts[0];

    pV->subEntityTraits().setColor(kRed);
 
    pV->geometry().polylineDc(num_verts, verts);
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkIconSampObject()
{
    AsdkIconSamp *pNewObj = new AsdkIconSamp;

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
initAsdkIconSamp()
{
    AsdkIconSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ASDK_ICON_SAMP",
                            "ASDKICONSAMP",
                            "ICONSAMP",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkIconSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
    case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkIconSamp();
        break;
    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup("ASDK_ICON_SAMP");
        deleteAcRxClass(AsdkIconSamp::desc());
    }
    return AcRx::kRetOK;
}
