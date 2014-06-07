// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// AsdkLongTransSample.cpp
// 
// Example showing how to use Long Transactions.
//


#include <rxregsvc.h>
#include <aced.h>

#include <dbidmap.h>
#include <lngtrans.h>
#include <dbltrans.h>

#include <dbmain.h>
#include <dbsymtb.h>
#include <dbents.h>
#include <dbapserv.h>
#include <adslib.h>

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
refEditApiExample()
{

    AcDbObjectId transId;
    AcDbDatabase* pDb;
    char *fname;
    struct resbuf *rb;

    // Get a dwg file from the user.
    //
    rb = acutNewRb(RTSTR);
    int stat = acedGetFileD("Pick a drawing", NULL, "dwg", 0, rb);
    
    if ((stat != RTNORM) || (rb == NULL)) {
        acutPrintf("\nYou must pick a drawing file.");
        return;
    }

    fname = (char*)acad_malloc(strlen(rb->resval.rstring) + 1);
    strcpy(fname, rb->resval.rstring);
    acutRelRb(rb);
    
    // Open the dwg file.
    //
    pDb = new AcDbDatabase(Adesk::kFalse);
    if (pDb->readDwgFile(fname) != Acad::eOk) {
        acutPrintf("\nSorry, that draing is probably already open.");
        return;
    }

    // Get the Block Table and then the model space record.
    //
    AcDbBlockTable *pBlockTable;
    pDb->getSymbolTable(pBlockTable, AcDb::kForRead);
    AcDbBlockTableRecord *pOtherMsBtr;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pOtherMsBtr, AcDb::kForRead);
    pBlockTable->close();

    // Create an iterator.
    //
    AcDbBlockTableRecordIterator *pIter;
    pOtherMsBtr->newIterator(pIter);

    // Set up an object ID array.
    //
    AcDbObjectIdArray objIdArray;

    // Iterate over the model space BTR. Look specifically 
    // for lines and append their object ID to the array.
    //
    for (pIter->start(); !pIter->done(); pIter->step()) {
        AcDbEntity *pEntity;
        pIter->getEntity(pEntity, AcDb::kForRead);

        // Look for only AcDbLine objects and add them to the 
        // object ID array.
        //
        if (pEntity->isKindOf(AcDbLine::desc())) {
            objIdArray.append(pEntity->objectId());
        }
        pEntity->close();
    }
    delete pIter;
    pOtherMsBtr->close();

    if (objIdArray.isEmpty()) {
        acad_free(fname);
        acutPrintf("\nYou must pick a drawing file that contains lines.");
        return;
    }

    // Now get the current database and the object ID for the
    // current database's model space BTR.
    //
    AcDbBlockTable *pThisBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pThisBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pThisMsBtr;
    pThisBlockTable->getAt(ACDB_MODEL_SPACE, pThisMsBtr, AcDb::kForWrite);
    pThisBlockTable->close();
    
    AcDbObjectId id = pThisMsBtr->objectId();
    pThisMsBtr->close();


    // Create the long transaction. This will check all the entities 
    // out of the external database.
    //
    AcDbIdMapping errorMap;
    acapLongTransactionManagerPtr()->checkOut(transId, objIdArray, id, errorMap);

    // Now modify the color of these entities.
    //
    int colorIndex;
    acedGetInt("\nEnter color number to change entities to: ", &colorIndex);
    AcDbObject* pObj;
    if (acdbOpenObject(pObj, transId, AcDb::kForRead) == Acad::eOk) {

        // Get a pointer to the transaction.
        //
        AcDbLongTransaction* pLongTrans = AcDbLongTransaction::cast(pObj);
        if (pLongTrans != NULL) {

            // Get a work set iterator.
            //
            AcDbLongTransWorkSetIterator* pWorkSetIter;
            pLongTrans->newWorkSetIterator(pWorkSetIter);

            // Iterate over the entities in the work set and change the color.
            //
            for (pWorkSetIter->start(); !pWorkSetIter->done(); pWorkSetIter->step()) {
                AcDbEntity *pEntity;
                acdbOpenAcDbEntity(pEntity, pWorkSetIter->objectId(), AcDb::kForWrite);
                pEntity->setColorIndex(colorIndex);
                pEntity->close();
            }
            delete pWorkSetIter;
        }
        pObj->close();
    }

    // Pause to see the change.
    //
    char str[132];
    acedGetString(0, "\nSee the new colors. Press return to check the object into the original database", str);

    // Check the entities back in to the original database.
    //
    acapLongTransactionManagerPtr()->checkIn(transId, errorMap);

    // Save the original database, since we have made changes.
    //
    pDb->saveAs(fname);

    // Close/Delete the database
    //
    delete pDb;
    pDb = NULL;

    acad_free(fname);
}

// END CODE APPEARING IN SDK DOCUMENT.

void
initApp()
{

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("AsdkLongTransSample_COMMANDS", "AsdkLongTrans", "LongTrans", ACRX_CMD_MODAL, refEditApiExample);

}


void unloadApp()
{
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("AsdkLongTransSample_COMMANDS");

}

extern "C" AcRx::AppRetCode 
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
        break;
    case AcRx::kLoadDwgMsg:

        break;
    case AcRx::kUnloadDwgMsg:

        break;
    case AcRx::kInvkSubrMsg:

        break;
    default:
        ;
    }
    return AcRx::kRetOK;
}

