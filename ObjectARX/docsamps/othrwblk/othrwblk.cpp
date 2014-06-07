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
// othrwblk.cpp
// 
// Example showing correct and incorrect ways to use
// AcEditorReactor::otherWblock to get the destination database's
// Model Space BTR ObjectId


#include "rxregsvc.h"
#include "aced.h"
#include "dbsymtb.h"
#include "dbidmap.h"
#include "adslib.h"


class AsdkWblockReactor : public AcEditorReactor 
// This reactor implements only the otherWblock notification 
// reaction from AcEditorReactor.
//
{
  public:

    virtual void otherWblock(AcDbDatabase*,
                             AcDbIdMapping&,
                             AcDbDatabase*);
};

#ifdef WRONGWAY

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkWblockReactor::otherWblock(AcDbDatabase*  pDestDb,
                               AcDbIdMapping& idMap,
                               AcDbDatabase*  pSrcDb)
{
    AcDbBlockTable       *pDestBlockTable;
    AcDbBlockTableRecord *pDestBTR;

    pDestDb->getSymbolTable(pDestBlockTable, AcDb::kForRead);
    pDestBlockTable->getAt(ACDB_MODEL_SPACE,
        pDestBTR, AcDb::kForRead);
    pDestBlockTable->close();

    // Now pDestBTR is pointing to pSrcDb database's Model
    // Space not to the destination database's Model Space!
    // The code above is not correct!

// END CODE APPEARING IN SDK DOCUMENT.

    acutPrintf("\nIncorrect destination BTR's ObjectId is \t\t%Ld",
        pDestBTR->objectId().asOldId());
    pDestBTR->close();

    AcDbBlockTable *pSrcBlockTable;
    AcDbObjectId    srcModelSpaceId;
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    acutPrintf("\nSource Database's Model Space BTR's ObjectId is \t%Ld",
        srcModelSpaceId.asOldId());
}

#else

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkWblockReactor::otherWblock(AcDbDatabase*  pDestDb,
                               AcDbIdMapping& idMap,
                               AcDbDatabase*  pSrcDb)
{
    // To find the destination Model Space,  you must look
    // it up in the ID map:

    AcDbBlockTable *pSrcBlockTable;
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);

    AcDbObjectId srcModelSpaceId;
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    AcDbIdPair idPair;
    idPair.setKey(srcModelSpaceId);
    idMap.compute(idPair);

    AcDbBlockTableRecord *pDestBTR;
    acdbOpenAcDbObject((AcDbObject*&)pDestBTR,
        idPair.value(), AcDb::kForRead, Adesk::kTrue);

// END CODE APPEARING IN SDK DOCUMENT.

    acutPrintf("\nCorrect destination BTR's ObjectId is:\t\t%Ld",
        pDestBTR->objectId().asOldId());
    pDestBTR->close();

    // Incorrect way done here so that the wrong value can be
    // compared to the correct value
    //
    AcDbBlockTable *pDestBlockTable;
    pDestDb->getSymbolTable(pDestBlockTable, AcDb::kForRead);
    pDestBlockTable->getAt(ACDB_MODEL_SPACE,
        pDestBTR, AcDb::kForRead);
    pDestBlockTable->close();

	acutPrintf("\nIncorrect destination BTR's ObjectId is \t\t%Ld",
        pDestBTR->objectId().asOldId());
    
	pDestBTR->close();

    // source database Model Space BTR's ObjectId is shown to
    // demonstrate that this is what the incorrect method gets
    //
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    acutPrintf("\nSource Database's Model Space BTR's ObjectId is \t%Ld",
        srcModelSpaceId.asOldId());
}

#endif /* WRONGWAY */

// Arx entry point function
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
   static AsdkWblockReactor *pEdReac = new AsdkWblockReactor();

   switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        acedEditor->addReactor(pEdReac);
        break;
    case AcRx::kUnloadAppMsg:
        acedEditor->removeReactor(pEdReac);
        delete pEdReac;
    }
    return AcRx::kRetOK;
}
