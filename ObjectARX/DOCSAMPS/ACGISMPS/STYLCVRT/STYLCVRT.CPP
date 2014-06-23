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
// stylcvrt.cpp
//

#include <string.h>
#include <stdio.h>
#include "aced.h"
#include "adslib.h"
#include "dbsymtb.h"
#include "acgi.h"


// globals
//
static AcGiTextStyle AsdkStyle;


class AsdkTxtStyleSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTxtStyleSamp);
    virtual Adesk::Boolean worldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus transformBy(const AcGeMatrix3d &);
};


ACRX_DXF_DEFINE_MEMBERS(AsdkTxtStyleSamp,AcDbEntity,0,\
    AsdkTxtStyleSamp,AsdkTextStyle Sample);
MAKE_ACDBOPENOBJECT_FUNCTION(AsdkTxtStyleSamp);

Acad::ErrorStatus AsdkTxtStyleSamp::transformBy(
    const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}
 

Adesk::Boolean
AsdkTxtStyleSamp::worldDraw(AcGiWorldDraw* pW)
{
    AcGePoint3d pos(0.0, 0.0, 0.0);
    AcGeVector3d norm(0.0, 0.0, 1.0);
    AcGeVector3d dir(1.0, 0.2, 0.0);
    char *pStr = "Test string";
    int len = strlen(pStr);
    
    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, AsdkStyle);

    return Adesk::kTrue;
}


// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Get an AcGiTextStyle from an acDbTextStyleTableRecord.
// Try to map as many characteristics as possible.
//
void
getTextStyle(AcGiTextStyle& newStyle, AcDbObjectId styleId)
{
    AcDbTextStyleTableRecord *pOldStyle;
    acdbOpenObject((AcDbObject*&)pOldStyle, styleId,
        AcDb::kForRead);
    char *pTmpStr;
    pOldStyle->fileName(pTmpStr);
    newStyle.setFileName(pTmpStr);
    delete pTmpStr;

    pOldStyle->bigFontFileName(pTmpStr);
    newStyle.setBigFontFileName(pTmpStr);
    delete pTmpStr;

    newStyle.setTextSize(pOldStyle->textSize());
    newStyle.setXScale(pOldStyle->xScale());
    newStyle.setObliquingAngle(pOldStyle->obliquingAngle());

    pOldStyle->close();
    newStyle.loadStyleRec();
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTxtStyleSampObject()
{
    // First set up the styleId global with a valid
    // ObjectId for an AcDbTextStyleTableRecord.
    //
    AcDbTextStyleTable *pStyleTable;
    acdbCurDwg()->getTextStyleTable(pStyleTable,
        AcDb::kForRead);
   
    AcDbTextStyleTableIterator *pIterator;
    pStyleTable->newIterator(pIterator);

    // get ObjectId of first record in table
    //
    AcDbObjectId styleId;
    pIterator->getRecordId(styleId);

    delete pIterator;
    pStyleTable->close();
    
    // convert the AcDbTextStyleTableRecord to an
    // AcGiTextStyle using the global AsdkStyle
    // AcGiTextStyle object as the recipient.
    //
    getTextStyle(AsdkStyle, styleId);


    // Ok,  now make one of our AsdkTxtStyleSamp entities
    // and add it to Model Space.
    
    AsdkTxtStyleSamp *pNewObj = new AsdkTxtStyleSamp;

    AcDbBlockTable *pBlockTable;
    acdbCurDwg()->getBlockTable(pBlockTable,
        AcDb::kForRead);

    AcDbBlockTableRecord *pBlock;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);

    AcDbObjectId objId;
    pBlock->appendAcDbEntity(objId, pNewObj);

    pBlockTable->close();
    pBlock->close();
    pNewObj->close();
}

static void initAsdkTxtStyleSamp()
{
    AsdkTxtStyleSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand("ASDK_STYLE_CONVERT_SAMP",
                            "ASDKSTYLECVRT",
                            "STYLECVRT",
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTxtStyleSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
	    initAsdkTxtStyleSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup("ASDK_STYLE_CONVERT_SAMP");
            deleteAcRxClass(AsdkTxtStyleSamp::desc());
    }
    return AcRx::kRetOK;
}
