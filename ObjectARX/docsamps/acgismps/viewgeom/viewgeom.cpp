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
// viewgeom.cpp
//
// This example demonstrates using viewportDraw,
// getModelToEyeTransform, doPerspective, RegenType, and
// polylineEye.
//
// In a regular display of a pyramid made of 6 lines,
// you cannot easily determine which lines are on the
// back side of the pyramid.  This example colors the
// pyramid edges blue if they're on the far side and
// yellow if they're on the front side, so that you get
// a sense of the visible and hidden edges of the pyramid.
// This example could have been done with viewport's world
// coordinate polyline geometry, but since the calculations
// on the vertices to figure out (per viewport) which edges
// were visible resulted in eye coordinates, I chose to
// exemplify polylineEye() which accepts them.  The only
// drawback about eye coordinate line geometry is that it
// cannot currently be linetyped; to do that you use
// polyline() with world coordinate vertices.

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
// LINETYPE
/*static const char* const no_linetype       = "Continuous";
static const char* const linetype_by_layer = "ByLayer";
static const char* const linetype_by_block = "ByBlock";
// LAYER
static const char* const layer_zero        = "0";
  */

class AsdkViewGeomSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkViewGeomSamp);

     AsdkViewGeomSamp(); 

    virtual Adesk::Boolean worldDraw(AcGiWorldDraw*);
    void viewportDraw(AcGiViewportDraw*);
    Acad::ErrorStatus transformBy(const AcGeMatrix3d&);

private:

    Adesk::UInt32 mNumVerts;
    AcGePoint3d	  mVerts[4];
};

ACRX_DXF_DEFINE_MEMBERS(AsdkViewGeomSamp,\
    AcDbEntity,AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
0,ASDKVIEWGEOMSAMP,AsdkViewGeom Sample);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

AsdkViewGeomSamp::AsdkViewGeomSamp() : mNumVerts(4)
{
    mVerts[0] = AcGePoint3d(0.0, 0.0, 0.0);
    mVerts[1] = AcGePoint3d(1.0, 0.0, 0.0);
    mVerts[2] = AcGePoint3d(0.0, 1.0, 0.0);
    mVerts[3] = AcGePoint3d(0.0, 0.0, 1.0);
}


Acad::ErrorStatus
AsdkViewGeomSamp::transformBy(const AcGeMatrix3d &xfm)
{
    assertWriteEnabled();
    for (Adesk::UInt32 i = 0; i < mNumVerts; i++) {
        mVerts[i].transformBy(xfm);
    }
    return Acad::eOk;
}
 

Adesk::Boolean
AsdkViewGeomSamp::worldDraw(AcGiWorldDraw* pW)
{
    // Draw a pyramid.


    // If this is the REGULAR ACAD DISPLAY mode,
    //
    if (pW->regenType() == kAcGiStandardDisplay) {

        //  from each viewport's vantage point, figure out
        //  which sides of the pyramid are visible,
        //  then draw the visible ones yellow and the hidden
        //  ones blue.

        //  Set the extents of the pyramid here because 
        //  AcGiViewportGeometry's polylineEye() doesn't
        //  set extents.
        //
        for (Adesk::UInt32 i = 0; i < mNumVerts; i++) {
            AcGePoint3d pt[2];
            pt[0] = mVerts[i];
            pt[1] = mVerts[(i + 1) % mNumVerts];
            pW->geometry().setExtents(pt);
        }
        return Adesk::kFalse;  // Call viewport draws.
    }

    // Otherwise give HIDE, SHADE, RENDER, or Proxy Graphics
    // a pyramid with filled faces.
    //
    const Adesk::UInt32 faceListSize = 16;
    static Adesk::Int32 faceList[faceListSize] = {
        3, 0, 1, 2,
        3, 0, 2, 3,
        3, 0, 3, 1,
        3, 1, 2, 3
    };

    pW->geometry().shell(mNumVerts, mVerts, faceListSize,
        faceList);

    return Adesk::kTrue;  // Do NOT CALL viewportDraw.
}


void
AsdkViewGeomSamp::viewportDraw(AcGiViewportDraw* pV)
{
    // For this viewport, draw a pyramid with yellow
    // visible lines and blue hidden lines.


    // Get this viewport's net transform.  This transform
    // includes this entity's block transforms and this
    // viewport's view transform; it does not include the
    // perspective transform if we're in perspective
    // mode -- that currently has to be applied separately
    // when in perspective mode.
    //
    AcGeMatrix3d modelToEyeMat;
    pV->viewport().getModelToEyeTransform(modelToEyeMat);

    // Get the pyramid's vertices.
    //
    AcGePoint3d A = mVerts[0];
    AcGePoint3d B = mVerts[1];
    AcGePoint3d C = mVerts[2];
    AcGePoint3d D = mVerts[3];

    // Convert them to the viewport's eye coordinates.
    //
    A.transformBy(modelToEyeMat);
    B.transformBy(modelToEyeMat);
    C.transformBy(modelToEyeMat);
    D.transformBy(modelToEyeMat);

    // Save the eye coordinates.
    //
    AcGePoint3d AEye = A;
    AcGePoint3d BEye = B;
    AcGePoint3d CEye = C;
    AcGePoint3d DEye = D;

    // Perform the perspective transform if necessary.
    //
    if (pV->viewport().isPerspective()) {
        pV->viewport().doPerspective(A);
        pV->viewport().doPerspective(B);
        pV->viewport().doPerspective(C);
        pV->viewport().doPerspective(D);
    }

    // From that view, figure out which faces are
    // facing the the viewport and which are not.
    //
    int which_faces;
    which_faces  = ((C - A).crossProduct(B - A)).z 
        > 0.0 ? 1 : 0;
    which_faces |= ((D - A).crossProduct(C - A)).z 
        > 0.0 ? 2 : 0;
    which_faces |= ((B - A).crossProduct(D - A)).z 
        > 0.0 ? 4 : 0;
    which_faces |= ((B - D).crossProduct(C - D)).z 
        > 0.0 ? 8 : 0;

    // Those edges that meet between two faces that are
    // facing away from the viewport will be hidden edges
    // so draw them blue; otherwise, they are visible
    // edges.  (This example is incomplete as the test is
    // indeterminate when the face is edge-on to the
    // screen -- neither facing away or toward the screen.)

    // Draw the 6 edges connecting the vertices using eye
    // coordinate geometry that can be back and front
    // clipped.

    AcGePoint3d verts[2];
    Adesk::UInt16 color;
    // AB
    color = which_faces & 0x5 ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = AEye;
    verts[1] = BEye;
    pV->geometry().polylineEye(2, verts);
    // AC
    color = which_faces & 0x3 ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = AEye;
    verts[1] = CEye;
    pV->geometry().polylineEye(2, verts);
    // AD
    color = which_faces & 0x6 ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = AEye;
    verts[1] = DEye;
    pV->geometry().polylineEye(2, verts);
    // CD
    color = which_faces & 0xa ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = CEye;
    verts[1] = DEye;
    pV->geometry().polylineEye(2, verts);
    // DB
    color = which_faces & 0xc ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = DEye;
    verts[1] = BEye;
    pV->geometry().polylineEye(2, verts);
    // BC
    color = which_faces & 0x9 ? kYellow : kBlue;
    pV->subEntityTraits().setColor(color);
    verts[0] = BEye;
    verts[1] = CEye;
    pV->geometry().polylineEye(2, verts);
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkViewGeomSampObject()
{
    AsdkViewGeomSamp *pNewObj = new AsdkViewGeomSamp;

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
initAsdkViewGeomSamp()
{
    AsdkViewGeomSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ASDK_VIEWGEOM_SAMP",
                            "ASDKGEOM",
                            "GEOM",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkViewGeomSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
	    initAsdkViewGeomSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup("ASDK_VIEWGEOM_SAMP");
            deleteAcRxClass(AsdkViewGeomSamp::desc());
    }
    return AcRx::kRetOK;
}
