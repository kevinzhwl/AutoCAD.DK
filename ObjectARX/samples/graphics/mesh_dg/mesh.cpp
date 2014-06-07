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
// mesh.cpp

#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"

// Helpful Color constants for setting attributes:
//
static const Adesk::UInt16 kColorByBlock   = 0;
static const Adesk::UInt16 kRed            = 1;
static const Adesk::UInt16 kYellow         = 2;
static const Adesk::UInt16 kGreen          = 3;
static const Adesk::UInt16 kCyan           = 4;
static const Adesk::UInt16 kBlue           = 5;
static const Adesk::UInt16 kMagenta        = 6;
static const Adesk::UInt16 kWhite          = 7;
static const Adesk::UInt16 kColorByLayer   = 256;


class AsdkMeshSamp: public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AsdkMeshSamp);
    AsdkMeshSamp(); 
    ~AsdkMeshSamp();
    virtual Adesk::Boolean  worldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus       transformBy(const AcGeMatrix3d &);
};

ACRX_DXF_DEFINE_MEMBERS(AsdkMeshSamp, AcDbEntity, 
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKMESHSAMP, AcGiMesh Sample);


AsdkMeshSamp::AsdkMeshSamp()
{}

AsdkMeshSamp::~AsdkMeshSamp()
{}

Acad::ErrorStatus
AsdkMeshSamp::transformBy(const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
 
Adesk::Boolean
AsdkMeshSamp::worldDraw(AcGiWorldDraw* pW)
{
    Adesk::UInt32 i, j, k;
    Adesk::UInt32 numRows = 4;
    Adesk::UInt32 numCols = 4;
    AcGePoint3d *pVerts =
        new AcGePoint3d[numRows * numCols];

    for (k = 0, i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++, k++) {
            pVerts[k].x = (double)j;
            pVerts[k].y = (double)i;
            pVerts[k].z = 0.;
        }
    }

    // Construct an array of colors to be applied to each
    // edge of the mesh.  Here, let the rows be cyan and
    // the columns be green.
    //
    AcGiEdgeData edgeInfo;
    Adesk::UInt32 numRowEdges = numRows * (numCols - 1);
    Adesk::UInt32 numColEdges = (numRows - 1) * numCols;
    Adesk::UInt32 numEdges = numRowEdges + numColEdges;
    short *pEdgeColorArray = new short[numEdges];
    
    for (i = 0; i < numEdges; i++) {
        pEdgeColorArray[i] = 
            i < numRowEdges ? kCyan : kGreen;
    }
	edgeInfo.setColors(pEdgeColorArray);

    // Make the first face transparent and the rest
    // different colors.
    //
    Adesk::UInt32 numFaces = (numRows - 1) 
        * (numCols - 1);
    Adesk::UInt8 *pFaceVisArray =
        new Adesk::UInt8[numFaces];
    short *pFaceColorArray = new short[numFaces];
    AcGiFaceData faceInfo;
    faceInfo.setVisibility(pFaceVisArray);

    for (i = 0; i < numFaces; i++) {
        pFaceVisArray[i] =
            i ? kAcGiVisible : kAcGiInvisible;
        pFaceColorArray[i] = (short)(i + 1);
    }
	faceInfo.setColors(pFaceColorArray);

    // If the fill type is kAcGiFillAlways, then a shell,
    // mesh, or polygon will be interpreted as faces;
    // otherwise, they will be interpreted as edges.

    // Output mesh as faces.
    //
    pW->subEntityTraits().setFillType(kAcGiFillAlways);
    pW->geometry().mesh(numRows, numCols, pVerts, NULL,
        &faceInfo);

    // Output mesh as edges over the faces.
    //
    pW->subEntityTraits().setFillType(kAcGiFillNever);
    pW->geometry().mesh(numRows, numCols, pVerts,
        &edgeInfo);

    delete [] pVerts;
    delete [] pEdgeColorArray;
    delete [] pFaceColorArray;
    delete [] pFaceVisArray;
 
    return Adesk::kTrue;
}

// END CODE APPEARING IN SDK DOCUMENT.

static void
addAsdkMeshSampObject()
{
    Acad::ErrorStatus es;
    AcDbBlockTable   *pBlockTable;
    es = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk)
        return;

    AcDbBlockTableRecord *pBlock;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);
    if (es != Acad::eOk)
        return;

    AcDbObjectId  objId;
    AsdkMeshSamp *pNewObj = new AsdkMeshSamp;
    es = pBlock->appendAcDbEntity(objId, pNewObj);
    if (es != Acad::eOk) {
        delete pNewObj;
        return;
    }

    es = pBlock->close();
    if (es != Acad::eOk)
        acrx_abort("\nUnable to close block table record");

    es = pBlockTable->close();
    if (es != Acad::eOk) 
        acrx_abort("\nUnable to close block table");

    es = pNewObj->close();
    if (es != Acad::eOk) 
        acrx_abort("\nUnable to close new entity");
}

static void
initAsdkMeshSamp()
{
    AsdkMeshSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ACGI_MESH_SAMP",
                            "ASDKMAKEMESH",
                            "MAKEMESH",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkMeshSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkMeshSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup("ACGI_MESH_SAMP");
            deleteAcRxClass(AsdkMeshSamp::desc());
    }
    return AcRx::kRetOK;
}
