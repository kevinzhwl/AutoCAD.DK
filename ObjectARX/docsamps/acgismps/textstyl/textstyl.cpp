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
// textstyl.cpp
//

#include <string.h>
#include <stdio.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"


class AsdkTextStyleSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTextStyleSamp);
    virtual Adesk::Boolean worldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus transformBy(const AcGeMatrix3d &);
};


ACRX_DXF_DEFINE_MEMBERS(AsdkTextStyleSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKTEXTSTYLESAMP,AsdkTextStyle Sample);

Acad::ErrorStatus AsdkTextStyleSamp::transformBy(
    const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}
 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Adesk::Boolean
AsdkTextStyleSamp::worldDraw(AcGiWorldDraw* pW)
{
    AcGePoint3d pos(4.0, 4.0, 0.0);
    AcGeVector3d norm(0.0, 0.0, 1.0);
    AcGeVector3d dir(-1.0, -0.2, 0.0);
    char *pStr = "This is a percent, '%%%'.";
    int len = strlen(pStr);
    AcGiTextStyle style;

    AcGeVector3d vec = norm;
    vec = vec.crossProduct(dir);
    dir = vec.crossProduct(norm);

    style.setFileName("txt.shx");
    style.setBigFontFileName("");
    int status;
    if (!((status = style.loadStyleRec()) & 1))
        pStr = "Font not found.";

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    pos.y += 2.0;

    style.setTrackingPercent(80.0);
    style.setObliquingAngle(10.0);

    AcGePoint2d ext = style.extents(pStr, Adesk::kFalse,
        strlen(pStr), Adesk::kFalse);

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    // Draw a rectangle around the last text drawn.
    // First you have to create a polyline the size of the
    // bounding box, then you have to transform it to the
    // correct orientation, and then to the location of the
    // text.
    
    // Compute the matrix that orients the box.
    //
    AcGeMatrix3d textMat;
    norm.normalize();
    dir.normalize();
    AcGeVector3d yAxis = norm;
    yAxis = yAxis.crossProduct(dir);
    yAxis.normalize();
    textMat.setCoordSystem(AcGePoint3d(0.0, 0.0, 0.0), dir,
        yAxis, norm);

    // Create the bounding box and enlarge it somewhat.
    //
    double offset = ext.y / 2.0;
    AcGePoint3d verts[5];
    verts[0] = verts[4] = AcGePoint3d(-offset, -offset, 0.0);
    verts[1] = AcGePoint3d(ext.x + offset, -offset, 0.0);
    verts[2] = AcGePoint3d(ext.x + offset, ext.y + offset, 0.0);
    verts[3] = AcGePoint3d(-offset, ext.y + offset, 0.0);

    // Orient and then translate each point in the
    // bounding box.
    //
    for (int i = 0; i < 5; i++) {
        verts[i].transformBy(textMat);
        verts[i].x += pos.x;
        verts[i].y += pos.y;
        verts[i].z += pos.z;
    }
    pW->geometry().polyline(5, verts);

    return Adesk::kTrue;
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTextStyleSampObject()
{
    AsdkTextStyleSamp *pNewObj = new AsdkTextStyleSamp;

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

static void initAsdkTextStyleSamp()
{
    AsdkTextStyleSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ASDK_TEXTSTYLE_SAMP",
                            "ASDKSTYLESAMP",
                            "STYLESAMP",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTextStyleSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
	    initAsdkTextStyleSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup("ASDK_TEXTSTYLE_SAMP");
            deleteAcRxClass(AsdkTextStyleSamp::desc());
    }
    return AcRx::kRetOK;
}
