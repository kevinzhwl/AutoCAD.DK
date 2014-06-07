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


#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <geassign.h>
#include <adscodes.h>

void doit();
void printAll();
void makeABlock();
void createPolyline();
void addBlockWithAttributes();
Acad::ErrorStatus addToModelSpace(AcDbObjectId&,
    AcDbEntity*);
void defineBlockWithAttributes(AcDbObjectId&,
    const AcGePoint3d&, double, double);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
makeABlock()
{
     // Create and name a new block table record.
     //
     AcDbBlockTableRecord *pBlockTableRec
         = new AcDbBlockTableRecord();
     pBlockTableRec->setName("ASDK-NO-ATTR");

     // Get the block table.
     //
     AcDbBlockTable *pBlockTable = NULL;
     acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForWrite);

     // Add the new block table record to the block table.
     //
     AcDbObjectId blockTableRecordId;
     pBlockTable->add(blockTableRecordId, pBlockTableRec);
     pBlockTable->close();

     // Create and add a line entity to the component's
     // block record.
     //
     AcDbLine *pLine = new AcDbLine();
     AcDbObjectId lineId;

     pLine->setStartPoint(AcGePoint3d(3, 3, 0));
     pLine->setEndPoint(AcGePoint3d(6, 6, 0));
     pLine->setColorIndex(3);

     pBlockTableRec->appendAcDbEntity(lineId, pLine);
     pLine->close();
     pBlockTableRec->close();
}

void
defineBlockWithAttributes(
    AcDbObjectId& blockId, // This is a returned value.
    const AcGePoint3d& basePoint,
    double textHeight,
    double textAngle)
{
    int retCode = 0;
    AcDbBlockTable *pBlockTable = NULL;
    AcDbBlockTableRecord* pBlockRecord
       = new AcDbBlockTableRecord;
    AcDbObjectId entityId;

    // Step 1: Set the block name and base point of the block definition
    //
    pBlockRecord->setName("ASDK-BLOCK-WITH-ATTR");
    pBlockRecord->setOrigin(basePoint);

    // Open the block table for write.
    //
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForWrite);

    // Step 2: Add the block table record to block table.
    //
    pBlockTable->add(blockId, pBlockRecord);

    // Step 3: Create a circle entity.
    //
    AcDbCircle *pCircle = new AcDbCircle;
    pCircle->setCenter(basePoint);
    pCircle->setRadius(textHeight * 4.0);
    pCircle->setColorIndex(3);

    // Append the circle entity to the block record.
    //
    pBlockRecord->appendAcDbEntity(entityId, pCircle);
    pCircle->close();

    // Step 4: Create an attribute definition entity.
    //
    AcDbAttributeDefinition *pAttdef
        = new AcDbAttributeDefinition;

    // Set the attribute definition values.
    //
    pAttdef->setPosition(basePoint);
    pAttdef->setHeight(textHeight);
    pAttdef->setRotation(textAngle);
    pAttdef->setHorizontalMode(AcDb::kTextLeft);
    pAttdef->setVerticalMode(AcDb::kTextBase);
    pAttdef->setPrompt("Prompt");
    pAttdef->setTextString("DEFAULT");
    pAttdef->setTag("Tag");
    pAttdef->setInvisible(Adesk::kFalse);
    pAttdef->setVerifiable(Adesk::kFalse);
    pAttdef->setPreset(Adesk::kFalse);
    pAttdef->setConstant(Adesk::kFalse);
    pAttdef->setFieldLength(25);

    // Append the attribute definition to the block.
    //
    pBlockRecord->appendAcDbEntity(entityId, pAttdef);

    // The second attribute definition is a little easier
    // because we are cloning the first one.
    //
    AcDbAttributeDefinition *pAttdef2
        = AcDbAttributeDefinition::cast(pAttdef->clone());

    // Set the values which are specific to the
    // second attribute definition.
    //
    AcGePoint3d tempPt(basePoint);
    tempPt.y -= pAttdef2->height();
    pAttdef2->setPosition(tempPt);
    pAttdef2->setColorIndex(1); // Red
    pAttdef2->setConstant(Adesk::kTrue);

    // Append the second attribute definition to the block.
    //
    pBlockRecord->appendAcDbEntity(entityId, pAttdef2);

    pAttdef->close();
    pAttdef2->close();
    pBlockRecord->close();
    pBlockTable->close();
    return;
}

void
addBlockWithAttributes()
{
    // Get an insertion point for the block reference,
    // definition, and attribute definition.
    //
    AcGePoint3d basePoint;
    if (acedGetPoint(NULL, "\nEnter insertion point: ",
        asDblArray(basePoint)) != RTNORM)
        return;

    // Get the rotation angle for the attribute definition.
    //
    double textAngle;
    if (acedGetAngle(asDblArray(basePoint),
        "\nEnter rotation angle: ", &textAngle) != RTNORM)
        return;

    // Define the height used for the attribute definition text.
    //
    double textHeight;
    if (acedGetDist(asDblArray(basePoint),
        "\nEnter text height: ", &textHeight) != RTNORM)
        return;

    // Build the block definition to be inserted.
    //
    AcDbObjectId blockId;
    defineBlockWithAttributes(blockId, basePoint,
        textHeight, textAngle);

    // Step 1: Allocate a block reference object.
    //
    AcDbBlockReference *pBlkRef = new AcDbBlockReference;

    // Step 2: Set up the block reference to the newly
    // created block definition.
    //
    pBlkRef->setBlockTableRecord(blockId);

    // Give it the current UCS normal.
    //
    struct resbuf to, from;

    from.restype = RTSHORT;
    from.resval.rint = 1; // UCS
    to.restype = RTSHORT;
    to.resval.rint = 0; // WCS

    AcGeVector3d normal(0.0, 0.0, 1.0);
    acedTrans(&(normal.x), &from, &to, Adesk::kTrue,
        &(normal.x));

    // Set the insertion point for the block reference.
    //
    pBlkRef->setPosition(basePoint);

    // Indicate the LCS 0.0 angle, not necessarily the UCS 0.0 angle.
    //
    pBlkRef->setRotation(0.0);
    pBlkRef->setNormal(normal);

    // Step 3: Open the current database's model space
    // block Table Record.
    //
    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);

    pBlockTable->close();

    // Append the block reference to the model space
    // block Table Record.
    //
    AcDbObjectId newEntId;
    pBlockTableRecord->appendAcDbEntity(newEntId, pBlkRef);
    pBlockTableRecord->close();

    // Step 4: Open the block definition for read.
    //
    AcDbBlockTableRecord *pBlockDef;
    acdbOpenObject(pBlockDef, blockId, AcDb::kForRead);

    // Set up a block table record iterator to iterate
    // over the attribute definitions.
    //
    AcDbBlockTableRecordIterator *pIterator;
    pBlockDef->newIterator(pIterator);

    AcDbEntity *pEnt;
    AcDbAttributeDefinition *pAttdef;
    for (pIterator->start(); !pIterator->done();
        pIterator->step())
    {
        // Get the next entity.
        //
        pIterator->getEntity(pEnt, AcDb::kForRead);

        // Make sure the entity is an attribute definition
        // and not a constant.
        //
        pAttdef = AcDbAttributeDefinition::cast(pEnt);

        if (pAttdef != NULL && !pAttdef->isConstant()) {

            // We have a non-constant attribute definition,
            // so build an attribute entity.
            //
            AcDbAttribute *pAtt = new AcDbAttribute();
            pAtt->setPropertiesFrom(pAttdef);
            pAtt->setInvisible(pAttdef->isInvisible());

            // Translate the attribute by block reference.
            // To be really correct, the entire block
            // reference transform should be applied here.
            //
            basePoint = pAttdef->position();
            basePoint += pBlkRef->position().asVector();
            pAtt->setPosition(basePoint);

            pAtt->setHeight(pAttdef->height());
            pAtt->setRotation(pAttdef->rotation());

            pAtt->setTag("Tag");
            pAtt->setFieldLength(25);

            char *pStr = pAttdef->tag();
            pAtt->setTag(pStr);
            free(pStr);

            pAtt->setFieldLength(pAttdef->fieldLength());

            // The database column value should be displayed.
            // INSERT prompts for this.
            //
            pAtt->setTextString("Assigned Attribute Value");

            AcDbObjectId attId;

            pBlkRef->appendAttribute(attId, pAtt);
            pAtt->close();
        }
        pEnt->close(); // use pEnt... pAttdef might be NULL
    }
    delete pIterator;
    pBlockDef->close();
    pBlkRef->close();
}

void
printAll()
{
    int rc;
    char blkName[50];
    rc = acedGetString(Adesk::kTrue,
        "Enter Block Name <CR for current space>: ",
        blkName);

    if (rc != RTNORM)
        return;

    if (blkName[0] == '\0') {
        if (acdbHostApplicationServices()->workingDatabase()->tilemode() 
            == Adesk::kFalse) {
            struct resbuf rb;
            acedGetVar("cvport", &rb);
            if (rb.resval.rint == 1) {
                strcpy(blkName, ACDB_PAPER_SPACE);
            } else {
                strcpy(blkName, ACDB_MODEL_SPACE);
            }
        } else {
            strcpy(blkName, ACDB_MODEL_SPACE);
        }
    }
    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(blkName, pBlockTableRecord,
        AcDb::kForRead);
    pBlockTable->close();

    AcDbBlockTableRecordIterator *pBlockIterator;
    pBlockTableRecord->newIterator(pBlockIterator);

    for (; !pBlockIterator->done();
        pBlockIterator->step())
    {
        AcDbEntity *pEntity;
        pBlockIterator->getEntity(pEntity, AcDb::kForRead);

        AcDbHandle objHandle;
        pEntity->getAcDbHandle(objHandle);

        char handleStr[20];
        objHandle.getIntoAsciiBuffer(handleStr);
        const char *pCname = pEntity->isA()->name();

        acutPrintf("Object Id %lx, handle %s, class %s.\n",
            pEntity->objectId(), handleStr, pCname);

        pEntity->close();
    }
    delete pBlockIterator;
    pBlockTableRecord->close();

    acutPrintf("\n");
}

void
createPolyline()
{
    // Set four vertex locations for the pline.
    //
    AcGePoint3dArray ptArr;
    ptArr.setLogicalLength(4);
    for (int i = 0; i < 4; i++) {
        ptArr[i].set((double)(i/2), (double)(i%2), 0.0);
    }

    // Dynamically allocate an AcDb2dPolyline object,
    // given four vertex elements whose locations are supplied
    // in ptArr.  The polyline has no elevation, and is
    // explicitly set as closed.  The polyline is simple;
    // that is, not curve fit or a spline.  By default, the
    // widths are all 0.0 and there are no bulge factors.
    //
    AcDb2dPolyline *pNewPline = new AcDb2dPolyline(
        AcDb::k2dSimplePoly, ptArr, 0.0, Adesk::kTrue);

    pNewPline->setColorIndex(3);

    // Get a pointer to a Block Table object.
    //
    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    // Get a pointer to the MODEL_SPACE BlockTableRecord.
    //
    AcDbBlockTableRecord *pBlockTableRecord;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
        AcDb::kForWrite);

    pBlockTable->close();

    // Append the pline object to the database and
    // obtain its Object ID.
    //
    AcDbObjectId plineObjId;
    pBlockTableRecord->appendAcDbEntity(plineObjId,
        pNewPline);

    pBlockTableRecord->close();

    // Make the pline object reside on layer "0".
    //
    pNewPline->setLayer("0");

    pNewPline->close();
}

// END CODE APPEARING IN SDK DOCUMENT.

Acad::ErrorStatus
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
    Acad::ErrorStatus     es = Acad::eOk;
    AcDbBlockTable        *pBlockTable;
    AcDbBlockTableRecord  *pSpaceRecord;

    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
        AcDb::kForWrite);

    pSpaceRecord->appendAcDbEntity(objId, pEntity);

    pBlockTable->close();
    pEntity->close();
    pSpaceRecord->close();
    return es;
}

void
initApp()
{
    acedRegCmds->addCommand("ASDK_COMPLEX",
                            "ASDK_MAKEABLOCK",
                            "MAKEABLOCK",
                            ACRX_CMD_MODAL,
                            makeABlock);

    acedRegCmds->addCommand("ASDK_COMPLEX",
                            "ASDK_CREATEPOLY",
                            "CREATEPOLY",
                            ACRX_CMD_MODAL,
                            createPolyline);

    acedRegCmds->addCommand("ASDK_COMPLEX",
                            "ASDK_ADDBLKWITHATT",
                            "ADDBLKWITHATT",
                            ACRX_CMD_MODAL,
                            addBlockWithAttributes);

    acedRegCmds->addCommand("ASDK_COMPLEX",
                            "ASDK_PRINTALL",
                            "PRINTALL",
                            ACRX_CMD_MODAL,
                            printAll);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_COMPLEX");
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
    }
    return AcRx::kRetOK;
}
