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
// shell.cpp

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


class AsdkShellSamp: public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AsdkShellSamp);
    AsdkShellSamp(); 
    ~AsdkShellSamp();
    virtual Adesk::Boolean  worldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus       transformBy(const AcGeMatrix3d &);
};

ACRX_DXF_DEFINE_MEMBERS(AsdkShellSamp, AcDbEntity, 
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKSHELLSAMP, AcGiShell Sample);


AsdkShellSamp::AsdkShellSamp()
{}

AsdkShellSamp::~AsdkShellSamp()
{}

Acad::ErrorStatus
AsdkShellSamp::transformBy(const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
 
Adesk::Boolean
AsdkShellSamp::worldDraw(AcGiWorldDraw* pW)
{
    // Fill the faces with the current color.
    //
    pW->subEntityTraits().setFillType(kAcGiFillAlways);

    // Create vertices.
    //
    Adesk::UInt32 numVerts = 4;
    AcGePoint3d *pVerts = new AcGePoint3d[numVerts];
    pVerts[0] = AcGePoint3d(0.0, 0.0, 0.0);
    pVerts[1] = AcGePoint3d(0.0, 1.0, 0.0);
    pVerts[2] = AcGePoint3d(1.0, 1.0, 0.0);
    pVerts[3] = AcGePoint3d(1.0, 0.0, 2.0);

    // Create 2 faces.
    //
    Adesk::UInt32 faceListSize = 8;
    Adesk::Int32 *pFaceList
        = new Adesk::Int32[faceListSize];

    // Assign vertices for face #1.
    //
    pFaceList[0] = 3;   // 3 vertices in the face
    pFaceList[1] = 0;   // pVerts[0]
    pFaceList[2] = 1;   // pVerts[1]
    pFaceList[3] = 2;   // pVerts[2]

    // assign vertices for face #2.
    //
    pFaceList[4] = 3;   // 3 vertices in the face
    pFaceList[5] = 0;   // pVerts[0]
    pFaceList[6] = 2;   // pVerts[2]
    pFaceList[7] = 3;   // pVerts[3]

    // Apply colors to edges.
    //
    AcGiEdgeData edgeData;
    int numEdges = 6;
    short *pEdgeColorArray = new short[numEdges];

    pEdgeColorArray[0] = kRed;
    pEdgeColorArray[1] = kYellow;
    pEdgeColorArray[2] = kGreen;
    pEdgeColorArray[3] = kCyan;
    pEdgeColorArray[4] = kBlue;
    pEdgeColorArray[5] = kMagenta;

	edgeData.setColors(pEdgeColorArray);

    // Apply visibility to edges and make common edge
    // between two faces have silhouette visibility during
    // the HIDE command with ACAD variable DISPSILH = 1.
    //
    Adesk::UInt8 *pEdgeVisArray
        = new Adesk::UInt8[numEdges];
    edgeData.setVisibility(pEdgeVisArray);

    pEdgeVisArray[0] = kAcGiVisible;
    pEdgeVisArray[1] = kAcGiVisible;
    pEdgeVisArray[2] = kAcGiSilhouette;
    pEdgeVisArray[3] = kAcGiSilhouette;
    pEdgeVisArray[4] = kAcGiVisible;
    pEdgeVisArray[5] = kAcGiVisible;
    
    // Apply colors to faces.
    //
    AcGiFaceData faceData;
    int numFaces = 2;
    short *pFaceColorArray = new short[numFaces];

    pFaceColorArray[0] = kBlue;
    pFaceColorArray[1] = kRed;

	faceData.setColors(pFaceColorArray);

    pW->geometry().shell(numVerts, pVerts, faceListSize,
        pFaceList, &edgeData, &faceData);

    delete [] pVerts;
    delete [] pFaceList;
    delete [] pEdgeColorArray;
    delete [] pFaceColorArray;
 
    return Adesk::kTrue;
}

// END CODE APPEARING IN SDK DOCUMENT.

static void
addAsdkShellSampObject()
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
    AsdkShellSamp *pNewObj = new AsdkShellSamp;
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
initAsdkShellSamp()
{
    AsdkShellSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ACGI_SHELL_SAMP",
                            "ASDKMAKESHELL",
                            "MAKESHELL",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkShellSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkShellSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup("ACGI_SHELL_SAMP");
            deleteAcRxClass(AsdkShellSamp::desc());
    }
    return AcRx::kRetOK;
}
