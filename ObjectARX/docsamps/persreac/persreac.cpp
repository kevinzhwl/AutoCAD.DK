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
// Description:
// 
// This program demonstrates the use of persistent reactors
// by attaching two reactors one to each of two lines.  Each
// reactor stores the objectId of the line it is not
// attached to so that when the line it is attached to is
// lengthened or shortened, the reactor opens the other line
// and modifies it's length to be the same as the new length
// of the line just changed.

#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>

void assocLines();
void addToModelSpace(AcDbObjectId&, AcDbEntity*);
void initApp(void);
void unloadApp(void);
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkObjectToNotify : public AcDbObject
//
// AsdkObjectToNotify - customized AcDbObject for persistent
// reactor to notify:
//
{
public:
    ACRX_DECLARE_MEMBERS(AsdkObjectToNotify);
    AsdkObjectToNotify() {};
    void eLinkage(AcDbObjectId i, double f=1.0)
        {mId=i; mFactor=f; };
    void              modified(const AcDbObject*);
    Acad::ErrorStatus dwgInFields(AcDbDwgFiler*);
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
    Acad::ErrorStatus dxfInFields(AcDbDxfFiler*);
    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;

private:
    AcDbObjectId mId;
    double mFactor;
};

ACRX_DXF_DEFINE_MEMBERS(AsdkObjectToNotify, AcDbObject, 
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
0, \
    ASDKOBJECTTONOTIFY, persreac);

// This function is called everytime the line it's
// "watching" is modified.  When it's called, it opens the
// other line of the pair and changes that line's length to
// match the new length of the line that's just been
// modified.
// 
void
AsdkObjectToNotify::modified(const AcDbObject* pObj)
{
    AcDbLine *pLine = AcDbLine::cast(pObj);
    if (!pLine) {
        const char* cstr = pObj->isA()->name();
        acutPrintf("This is a %s.\n", cstr);
        acutPrintf("I only work with lines. Sorry.\n");
        return;
    }
    acutPrintf("\nReactor attached to %lx calling %lx.\n",
        pLine->objectId(), mId);

    // This open will fail during notification caused by
    // reactor being added to the entity or when this
    // notification is in reaction to a change due to the
    // other line's reactor changing this line.  This will
    // properly prevent an infinite recursive cross loop
    // between the two lines and their reactors.
    // 
    AcDbLine *pLine2;
    if (acdbOpenObject((AcDbObject*&)pLine2, mId,
        AcDb::kForWrite) == Acad::eOk)
    {
        // get length of line entity we're being notified
        // has just been modified
        //
        AcGePoint3d p = pLine->startPoint();
        AcGePoint3d q = pLine->endPoint();
        AcGeVector3d v = q-p;
        double len = v.length();
        //
        // update other entity to match:
        //
        p = pLine2->startPoint();
        q = pLine2->endPoint();
        v = q-p;
        v = len * mFactor * v.normal();
        pLine2->setEndPoint(p+v);
        pLine2->close();
    }
}


// Files object's information in from DWG, UNDO, etc.
//
Acad::ErrorStatus
AsdkObjectToNotify::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
    AcDbObject::dwgInFields(filer);
    filer->readItem(&mFactor);
    filer->readItem((AcDbSoftPointerId*) &mId);
    return filer->filerStatus();
}


// Files object's information out to DWG, UNDO, etc.
//
Acad::ErrorStatus
AsdkObjectToNotify::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();
    AcDbObject::dwgOutFields(filer);
    filer->writeItem(mFactor);
    filer->writeItem((AcDbSoftPointerId&)mId);
    return filer->filerStatus();
}


// Files object's information in from DXF and LISP/ADS
//
Acad::ErrorStatus
AsdkObjectToNotify::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();

    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfInFields(filer))
        != Acad::eOk)
    {
        return es;
    }

    // Check if we're at the right subclass data marker
    //
    if(!filer->atSubclassData("AsdkObjectToNotify")) {
        return Acad::eBadDxfSequence;
    }

    struct resbuf rbIn;

    while (es == Acad::eOk) {
        if ((es = filer->readItem(&rbIn)) == Acad::eOk) {
            if (rbIn.restype == AcDb::kDxfReal) {
                mFactor = rbIn.resval.rreal;
            } else if (rbIn.restype
                == AcDb::kDxfSoftPointerId)
            {
                // ObjectIds are filed in as ads_names
                // 
                acdbGetObjectId(mId, rbIn.resval.rlname);
            } else {   // invalid group
                return(filer->pushBackItem());
            }
        }
    }
    return filer->filerStatus();
}


// files object's information out to DXF and LISP/ADS
//
Acad::ErrorStatus
AsdkObjectToNotify::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();
    AcDbObject::dxfOutFields(filer);
    filer->writeItem(AcDb::kDxfSubclass,
        "AsdkObjectToNotify");
    filer->writeItem(AcDb::kDxfReal, mFactor);
    filer->writeItem(AcDb::kDxfSoftPointerId, mId);
    return filer->filerStatus();
}


// Creates two lines and two AsdkObjectToNotify objects and
// ties them all together.
//
void
assocLines()
{
    AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
    AcDbObjectId aId, bId;

    AcDbLine *pLineA = new AcDbLine;
    pLineA->setDatabaseDefaults(pDb);
    pLineA->setStartPoint(AcGePoint3d(1, 1, 0));
    pLineA->setEndPoint(AcGePoint3d(2, 1, 0));
    addToModelSpace(aId, pLineA);

    ads_printf( "Line A is %lx from 1,1 to 2,1.\n",
        pLineA->objectId());


    AcDbLine *pLineB = new AcDbLine;
    pLineB->setDatabaseDefaults(pDb);
    pLineB->setStartPoint(AcGePoint3d(1, 2, 0));
    pLineB->setEndPoint(AcGePoint3d(2, 2, 0));
    addToModelSpace(bId, pLineB);

    ads_printf("Line B is %lx from 1,2 to 2,2.\n",
        pLineB->objectId());

    // Open the named object dictionary, check if there is
    // an entry with the key "ASDK_DICT".  If not, create a
    // dictionary and add it.
    // 
    AcDbDictionary *pNamedObj;
    AcDbDictionary *pNameList;
    pDb->getNamedObjectsDictionary(pNamedObj,
        AcDb::kForWrite);
    if (pNamedObj->getAt("ASDK_DICT",
        (AcDbObject*&)pNameList, AcDb::kForWrite)
            == Acad::eKeyNotFound)
    {
        pNameList = new AcDbDictionary;
        AcDbObjectId DictId;
        pNamedObj->setAt("ASDK_DICT", pNameList, DictId);
    }
    pNamedObj->close();

    // Create the AsdkObjectToNotify for lineA
    //
    AsdkObjectToNotify *pObj = new AsdkObjectToNotify();
    pObj->eLinkage(bId);

    AcDbObjectId objId;
    if ((pNameList->getAt("object_to_notify_A", objId))
        == Acad::eKeyNotFound)
    {
        pNameList->setAt("object_to_notify_A", pObj, objId);
        pObj->close();
    } else {
        delete pObj;
        ads_printf("object_to_notify_A already exists\n");
    }

    // Set up persistent reactor link between line a
    // and AsdkObjectToNotify
    //
    pLineA->addPersistentReactor(objId);
    pLineA->close();

    // Create the AsdkObjectToNotify for LineB
    //
    pObj = new AsdkObjectToNotify();
    pObj->eLinkage(aId);

    if ((pNameList->getAt("object_to_notify_B", objId))
        == Acad::eKeyNotFound)
    {
        pNameList->setAt("object_to_notify_B", pObj, objId);
        pObj->close();
    } else {
        delete pObj;
        ads_printf("object_to_notify_B already exists\n");
    }
    pNameList->close();

    // Set up persistent reactor link between line b
    // and AsdkObjectToNotify
    //
    pLineB->addPersistentReactor(objId);
    pLineB->close();
}

// Adds an entity to Model Space, but does not close
// the entity.
//
void
addToModelSpace(AcDbObjectId &objId, AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;
    AcDbBlockTableRecord *pSpaceRecord;

    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord,
            AcDb::kForWrite);
    pBlockTable->close();

    pSpaceRecord->appendAcDbEntity(objId, pEntity);
    pSpaceRecord->close();

    return;
}


// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand("ASDK_ALINES", "ASDK_ALINES",
        "ALINES", ACRX_CMD_MODAL, assocLines);

    AsdkObjectToNotify::rxInit();
    acrxBuildClassHierarchy();
}


// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this apps
// command set from the command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_ALINES");

    // Remove the AsdkObjectToNotify class from the ACRX
    // runtime class hierarchy.  If this is done while
    // database is still active, it should cause all objects
    // of class AsdkObjectToNotify to be turned into proxies.
    // 
    deleteAcRxClass(AsdkObjectToNotify::desc());
}


// ARX entry point
//
AcRx::AppRetCode
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

// END CODE APPEARING IN SDK DOCUMENT.
