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
// blocks.cpp - Rx app to create and list block definitions
//
// blocks creates and lists block definitions
// in the AutoCAD database.
//
// WARNING:  This program uses clone() to make copies of the entities
//           it puts in any block definitions it creates.  But,  clone()
//           will *NOT* work for complex entities -- deepClone() must be
//           used for such entities!!!
//
#include <stdlib.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbents.h>
#include <adslib.h>
#include "adeskabb.h"

#define streq(s,t) (strcmp((s),(t))==0)

// Function Prototypes
//
void blocks(void);
Adesk::Boolean createBlock(void);
Adesk::Boolean listBlock(void);
void printObjectInfo(const AcDbObjectId& id);
void printObjectInfo(const AcDbObject* obj);
void initApp(void);
void unloadApp(void);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void*);


// blocks - AutoCAD command to manipulate block definitions
//
// Creates, iterates and modifies block definitions
// in the AutoCAD database.
//
void
blocks(void)
{
    char kw[20];
    ads_initget(0, "Create List");
    int rc = ads_getkword("Create/<List>: ", kw);

    if (rc == RTNONE) {
        strcpy(kw, "List");
        rc = RTNORM;
    }

    if (rc != RTNORM) {
        ads_printf("Nothing selected.\n");
        return;
    }

    if (streq(kw, "List")) {
        listBlock();
    } else if (streq(kw, "Create")) {
        createBlock();
    }
    return;
}

// createBlock - create a block definition using selected entites
//
// The selected entities are cloned, inserted into the block
// definition, and deleted from the database, just like the 
// AutoCAD BLOCK command does.
//
Boolean
createBlock()
{
    // get name of block
    //
    char bName[80];
    int rc = ads_getstring(kFalse, "Enter block name: ", bName);

    if (rc!=RTNORM || *bName == '\0') {
        ads_printf("Invalid block name '%s'.\n", bName);
        return kFalse;
    }

    AcDbBlockTable *pBlockTable = NULL;
    // retrieve block table from database, open for Read and check
    // to see if the selected name is already present
    //
    // ... next line completes ...
    acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead);

    if (pBlockTable->has(bName)) {
        ads_printf("\nBlock name \"%s\" is already present in block table!",
            bName);
        pBlockTable->close();
        return kFalse;
    }
    pBlockTable->close();

    // get entities for block
    //
    ads_name ss;
    rc = ads_ssget(NULL, NULL, NULL, NULL, ss);

    if (rc!=RTNORM) {
        ads_printf("Nothing selected.\n");
        return kFalse;
    }

    long len;
    rc = ads_sslength(ss, &len);

    if (rc!=RTNORM) {
        ads_printf("Invalid selection set.\n");
        ads_ssfree(ss);
        return kFalse;
    }

    // get insertion point of block
    //
    AcGePoint3d p;
    rc = ads_getpoint(NULL, "Block insertion point <0,0,0>: ", 
    (double*)(&p));

    if (rc==RTNONE) {
        p[X] = p[Y] = p[Z] = 0.0;
        rc = RTNORM;
    }

    if (rc!=RTNORM) {
        ads_printf("Invalid insertion point.\n");
        return kFalse;
    }

    // create and name a new block table record
    //
    AcDbBlockTableRecord *pBlockTableRec = new AcDbBlockTableRecord();

    // set block table record name to bName and block origin to p
    //
    // ... next 2 lines complete ...
    pBlockTableRec->setName(bName);
    pBlockTableRec->setOrigin(p);

    // retrieve block table from database, open for write
    //
    // ... next line completes ...
    acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForWrite);
    
    // add block table record to block table
    //
    // ... next line completes ...
    pBlockTable->add(pBlockTableRec);

    // close block table now that the new block record is added
    //
    // ... next line completes ...
    pBlockTable->close();

    // add entities to the block record
    //
    ads_name en;
    AcDbObjectId objId;
    AcDbEntity *pObj, *pClone;
    Boolean myrc = kTrue;

    for (long i=0; i<len; ++i) {
        ads_ssname(ss, i, en);
        if (acdbGetObjectId(objId, en) != Acad::eOk) {
            ads_printf("Error retrieving object id.\n");
            myrc = kFalse;
            break;
        }
        // open for read and clone it to create a new entity copy that
        // can be added to the new BlockTableRecord
        //
        // WARNING:  This mechanism will not work for complex entities
        // because clone() will not clone the the subentities.  DeepClone()
        // must be used for complex entities!
        //
        if (acdbOpenObject(pObj, objId, AcDb::kForRead) != Acad::eOk) {
            ads_printf("Error opening object for read.\n");
            myrc = kFalse;
            break;
        }
        if ((pClone = AcDbEntity::cast(pObj->clone())) == NULL) {
            ads_printf("Error cloning object.\n");
            myrc = kFalse;
            break;
        }
        // append cloned entity to the block table record pointed to
        // by pBlockTableRec
        //
        // ... next line completes ...
        pBlockTableRec->appendAcDbEntity(pClone);

        // erase original object, just like normal BLOCK command:
        //
        if (pObj->upgradeOpen() != Acad::eOk) {
            ads_printf("Error upgrading open on original object.\n");
            myrc = kFalse;
            if (pObj->close() != Acad::eOk) {
                acrx_abort("Error closing original object.\n");
            }
            break;
        }
        if (pObj->erase() != Acad::eOk) {
            ads_printf("Error erasing original object.\n");
            myrc = kFalse;
            if (pObj->close() != Acad::eOk) {
                acrx_abort("Error closing original object.\n");
            }
            break;
        }
        if (pObj->close() != Acad::eOk) {
            acrx_abort("Error closing original object.\n");
        }
        if (pClone->close() != Acad::eOk) {
            acrx_abort("Error closing cloned object.\n");
        }
    }
    if (ads_ssfree(ss) != RTNORM) {
        ads_printf("Error freeing selection set.\n");
        return myrc;
    }
    if (pBlockTableRec->close() != Acad::eOk) {
        acrx_abort("Error closing block table record.\n");
    }
    return myrc;
}

// listBlock - list block definitions:
//
// The user has the option of listing:
//  - the "model space block"
//  - the "paper space block"
//  - a block defined by name
//  - a block defined by picking a block insertion
//
Boolean
listBlock()
{
    char kw[20];
    char buf[50];
    char *bName = buf;

    ads_name en;
    ads_point pt;
    ads_initget(0, "Model Paper Name");
    int rc = ads_entsel("Model space/Paper space/Name/<Pick insertion>: ",
    en, pt);

    AcDbBlockTableRecord* pBlockTableRecord = NULL;
    switch (rc) {
    case RTCAN:
    case RTNONE:
        ads_printf("Nothing selected.\n");
        return kTrue;
    case RTERROR:
        ads_printf("Error in ads_entsel.\n");
        return kFalse;
    case RTKWORD:
        if (ads_getinput(kw) != RTNORM) {
            ads_printf("Error in ads_getinput.\n");
            return kFalse;
        }
        if (streq(kw, "Model")) {
            strcpy(bName, ACDB_MODEL_SPACE);
        } else if (streq(kw, "Paper")) {
            strcpy(bName, ACDB_PAPER_SPACE);
        } else {
            rc = ads_getstring(kFalse, "Enter block name: ", bName);
            if (rc!=RTNORM || *bName == '\0') {
                ads_printf("Invalid block name '%s'.\n", bName);
                return kFalse;
            }
        }
        break;

    case RTNORM:
        // Retrieve the BlockTableRecord referenced by the insert picked
        //
        AcDbObjectId objId;
        if (acdbGetObjectId(objId, en) != Acad::eOk) {
            ads_printf("Error retrieving object id.\n");
            return kFalse;
        }

        AcDbBlockReference *pInsertObj;
        if (acdbOpenObject(pInsertObj, objId, AcDb::kForRead) != Acad::eOk) {
            ads_printf("Error opening block insertion for read.\n");
            return kFalse;
        }
        AcDbObjectId bId = pInsertObj->blockTableRecord();
        pInsertObj->close();

        if (acdbOpenObject(pBlockTableRecord, bId, AcDb::kForRead)
            != Acad::eOk)
        {
            ads_printf("Error opening block definition for read.\n");
            return kFalse;
        }
        break;
    }

    // If pBlockTableRecord == NULL then we have a block name and must
    // look in the blockTable for it.
    //
    if (pBlockTableRecord == NULL) {
        AcDbBlockTable* pBlockTable;

        // open acdbCurDwg's block table for read setting pBlockTable
        // to point to it.
        //
        // ... next line completes ...
        acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead);

        // search for block table record in block table using
        // bName key.  If found have it opened for read,  setting
        // pBlockTableRecord to point to it.
        //
        // ... next 8 lines complete ...
        pBlockTable->getAt(bName, pBlockTableRecord, AcDb::kForRead);

        if (pBlockTableRecord == NULL)
        {
            ads_printf("\nunable to obtain BlockTableRecord");
            pBlockTable->close();
            return kFalse;
        }
        pBlockTable->close();
    }

    // At this point pBlockTableRecord is pointing to the Block Table
    // Record to be iterated over.
    
    // save block definition origin for display later
    //
    AcGePoint3d p = pBlockTableRecord->origin();

    AcDbBlockTableRecordIterator* pBlockIterator;
    // create a new block interator that starts at the beginning
    // of the blockTableRecord and does not skip deleted entities.
    // Use pBlockIterator to hold the iterator's address.
    //
    // ... next line completes ...
    pBlockTableRecord->newIterator(pBlockIterator, Adesk::kTrue,
        Adesk::kFalse);

    // run iterator through once to get
    // number of entities in block:
    //
    for (long n = 0; !pBlockIterator->done(); pBlockIterator->step(
        Adesk::kTrue, Adesk::kFalse))
    {
        ++n;
    }
    ads_printf("\nBlock %s at (%.2lf %.2lf %.2lf) with %ld entities:\n==",
    bName, p.x, p.y, p.z, n);
    printObjectInfo(pBlockTableRecord);

    for (pBlockIterator->start(kTrue, kFalse); !pBlockIterator->done(); 
        pBlockIterator->step(Adesk::kTrue, Adesk::kFalse)) 
    {
        AcDbEntity *pEntity;

        // retrieve entity pointer from block iterator.  Don't forget that
        // this iterator can stop on erased entities so you will need to
        // specify that it's ok to open erased entities.
        //
        // ... next line completes ...
        pBlockIterator->getEntity(pEntity, AcDb::kForRead, Adesk::kTrue);

        printObjectInfo(pEntity);
        pEntity->close();
    }
    delete pBlockIterator;

    // close the Block Table Record now that we are done with it
    //
    Acad::ErrorStatus es = pBlockTableRecord->close();
    if (es != Acad::eOk) {
        acrx_abort("Error %d closing block table record.\n", es);
    }

    ads_printf("\n");
    return kTrue;
}

// printObjectInfo - utility function to print object info:
//
void
printObjectInfo(const AcDbObjectId& id)
{
    AcDbObject* pObj;
    if (acdbOpenObject(pObj, id, AcDb::kForRead) != Acad::eOk) {
        ads_printf("printObjectInfo: open object failed.\n");
    } else {
        printObjectInfo(pObj);
        pObj->close();
    }
}

// printObjectInfo - utility function to print object info:
//
void
printObjectInfo(const AcDbObject* pObj)
{

    AcDbHandle objHandle;
    pObj->getAcDbHandle(objHandle);

    char handleStr[20];
    objHandle.getIntoAsciiBuffer(handleStr);
    const char* cname = pObj->isA()->name();

    if (pObj->isErased()) {
        ads_printf("Object Id %lx, handle %s, class %s.\t(Erased)\n",
            pObj->objectId(), handleStr, cname);
    } else {
        ads_printf("Object Id %lx, handle %s, class %s.\n",
            pObj->objectId(), handleStr, cname);
    }
}

// ----- Rx interface -----

void
initApp()
{
    acedRegCmds->addCommand("BLOCK_CMDS", "BLOCKS", "BLOCKS",
        ACRX_CMD_MODAL, blocks);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("BLOCK_CMDS");
}

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
