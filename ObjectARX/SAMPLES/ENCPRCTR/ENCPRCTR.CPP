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
//  encprctr.cpp
//
// This sample program demonstrates one way to make use of C++ to encapsulate
// the necessary functionality for transient reactors in the derived reactor
// class.  This allows the reactor itself to deal with caching the objectIds
// of all objects it's attached to and to add and remove itself from objects
// as well as enhancing the ways a program can specify which object(s) to
// attach to.

#include "rxregsvc.h"
#include "aced.h"
#include "adslib.h"

class AsdkMsgReactor : public AcDbEntityReactor
{
//
// AsdkMsgReactor - customized entity reactor class which encapsulates all
// the functionality of adding/removing the reactor and enhances the
// addReactor mechanism by providing a series of attachTo functions that
// accept all sorts of object identifiers in addition to the standard
// AcDbEntity*.
//
public:
    AsdkMsgReactor() {};
    virtual ~AsdkMsgReactor();

    void attachTo(const ads_name ename);
    void attachTo(const AcDbEntity* pEnt);
    void attachTo(const AcDbObjectId& id);
    void attachTo(const AcDbObjectIdArray& idArray);
    void attachTo(const AcDbVoidPtrArray& entPtrArray);
    void attachToSset(const ads_name sset);
 
    void detachFrom(const ads_name ename);
    void detachFrom(const AcDbEntity* pEnt);
    void detachFrom(const AcDbObjectId& id);
    void detachFrom(const AcDbObjectIdArray& idArray);
    void detachFrom(const AcDbVoidPtrArray& entPtrArray);
    void detachFromSset(const ads_name sset);
 
    void clearIds();

    // AcDbObjectReactor protocol:
    //
    virtual void modified(const AcDbObject* pObj);
private:
    AcDbObjectIdArray objIds;
};

// This destructor removes the reactor from all the objects it was
// attached to thus ensuring proper cleanup.
//
AsdkMsgReactor::~AsdkMsgReactor()
{
    if (acdbCurDwg()) {
        // Remove the AsdkMsgReactor from all the entities it's been
        // attached to
        //
        int length = objIds.length();
        AcDbEntity *pEnt;
        for (int i=0; i < length; i++) {
            acdbOpenObject(pEnt, objIds[i], AcDb::kForRead,
                Adesk::kTrue);
            pEnt->removeReactor(this);
            pEnt->close();
        }
    }
}

// This method adds the reactor to the entity specified by ename
//
void AsdkMsgReactor::attachTo(const ads_name ename)
{
    AcDbObjectId id;
    acdbGetObjectId(id, (long*)ename);

    AcDbEntity *pEnt;
    acdbOpenObject(pEnt, id, AcDb::kForRead);

    pEnt->addReactor(this);
    objIds.append(id);

    pEnt->close();
}

// This method adds the reactor to the entity pointed to by pEnt
//
void AsdkMsgReactor::attachTo(const AcDbEntity* pEnt)
{
    pEnt->addReactor(this);
    objIds.append(pEnt->objectId());
}

// This method adds the reactor to the entity specified by id
//
void AsdkMsgReactor::attachTo(const AcDbObjectId& id)
{
    AcDbEntity *pEnt;
    acdbOpenObject(pEnt, id, AcDb::kForRead);

    pEnt->addReactor(this);
    objIds.append(id);

    pEnt->close();
}

// This method adds the reactor to the entities with objectIds in
// the idArray
//
void AsdkMsgReactor::attachTo(const AcDbObjectIdArray& idArray)
{
    int length = idArray.length();
    AcDbEntity *pEnt;
    for (int i=0; i < length; i++) {
        acdbOpenObject(pEnt, idArray[i], AcDb::kForRead,
            Adesk::kTrue);
        pEnt->addReactor(this);
        objIds.append(idArray[i]);
        pEnt->close();
    }
}

// This method adds the reactor to the entities with pointers in
// entPtrArray
//
void AsdkMsgReactor::attachTo(const AcDbVoidPtrArray& entPtrArray)
{
    int length = entPtrArray.length();
    for (int i=0; i < length; i++) {
        ((AcDbEntity*)entPtrArray[i])->addReactor(this);
        objIds.append(((AcDbEntity*)entPtrArray[i])->objectId());
    }
}

// This method adds the reactor to the entities within the sset
// selection set
//
void AsdkMsgReactor::attachToSset(const ads_name sset)
{
    ads_name ename;
    AcDbObjectId id;
    for (long i = 0L; ads_ssname((long*)sset, i, ename) == RTNORM; i++) {
        acdbGetObjectId(id, ename);
    
        AcDbEntity *pEnt;
        acdbOpenObject(pEnt, id, AcDb::kForRead);

        pEnt->addReactor(this);
        objIds.append(id);

        pEnt->close();
    }
}

// This method removes the reactor from the entity specified by ename
//
void AsdkMsgReactor::detachFrom(const ads_name ename)
{
    AcDbObjectId id;
    acdbGetObjectId(id, (long*)ename);
    
    AcDbEntity *pEnt;
    acdbOpenObject(pEnt, id, AcDb::kForRead);

    pEnt->removeReactor(this);
    objIds.remove(id);

    pEnt->close();
}

// This method removes the reactor from the entity pointed to by pEnt
//
void AsdkMsgReactor::detachFrom(const AcDbEntity* pEnt)
{
    pEnt->removeReactor(this);
    objIds.remove(pEnt->objectId());
}

// This method removes the reactor from the entity specified by id
//
void AsdkMsgReactor::detachFrom(const AcDbObjectId& id)
{
    AcDbEntity *pEnt;
    acdbOpenObject(pEnt, id, AcDb::kForRead);

    pEnt->removeReactor(this);
    objIds.remove(id);

    pEnt->close();
}

// This method removes the reactor from the entities with objectIds
// in idArray
//
void AsdkMsgReactor::detachFrom(const AcDbObjectIdArray& idArray)
{
    int length = idArray.length();
    AcDbEntity *pEnt;
    for (int i=0; i < length; i++) {
        acdbOpenObject(pEnt, idArray[i], AcDb::kForRead,
            Adesk::kTrue);
        pEnt->removeReactor(this);
        objIds.remove(idArray[i]);
        pEnt->close();
    }
}

// This method removes the reactor from the entities with pointers
// in entPtrArray
//
void AsdkMsgReactor::detachFrom(const AcDbVoidPtrArray& entPtrArray)
{
    int length = entPtrArray.length();
    for (int i=0; i < length; i++) {
        ((AcDbEntity*)entPtrArray[i])->removeReactor(this);
        objIds.remove(((AcDbEntity*)entPtrArray[i])->objectId());
    }
}

// This method removes the reactor from the entities in the sset
// selection set
//
void AsdkMsgReactor::detachFromSset(const ads_name sset)
{
    ads_name ename;
    AcDbObjectId id;
    for (long i = 0L; ads_ssname((long*)sset, i, ename) == RTNORM; i++) {
        acdbGetObjectId(id, ename);
    
        AcDbEntity *pEnt;
        acdbOpenObject(pEnt, id, AcDb::kForRead);

        pEnt->removeReactor(this);
        objIds.remove(id);

        pEnt->close();
    }
}

// This function the objectId cache array within the reactor
// 
void AsdkMsgReactor::clearIds()
{
    for (; !objIds.isEmpty();)
        objIds.removeLast();
}

// This is the reactors overridden notification method
//
void AsdkMsgReactor::modified(const AcDbObject* pObj)
{
    ads_printf("\nInside modified.\n");
}

// Global reactor pointer.  This pointer is global in this example
// so that it can be used by several functions.
//
static AsdkMsgReactor *pReact = NULL;

// This function is called when the ADD command is executed by the user
//
void
add()
{
    ads_name en;
    ads_point pt;
    if (ads_entsel("\nSelect entity:  ", en, pt) != RTNORM) {
        ads_printf("Nothing Selected\n");
        return;
    }
    if (!pReact)
        pReact = new AsdkMsgReactor;
    
    pReact->attachTo(en);
}

// This function is called when the ADDSET command
// is executed by the user
//
void
addSet()
{
    ads_name sset;
    if (ads_ssget(NULL, NULL, NULL, NULL, sset) != RTNORM) {
        ads_printf("Nothing Selected\n");
        return;
    }
    if (!pReact)
        pReact = new AsdkMsgReactor;
    
    pReact->attachToSset(sset);
    ads_ssfree(sset);
}


// This function is called when the REMOVE command
// is executed by the user
//
void
remove()
{
    if (!pReact)
        return;

    ads_name en;
    ads_point pt;
    if (ads_entsel("\nSelect entity:  ", en, pt) != RTNORM) {
        ads_printf("Nothing Selected\n");
        return;
    }
    pReact->detachFrom(en);
}

// This function is called when the REMOVESET command
// is executed by the user
//
void
removeSet()
{
    if (!pReact)
        return;

    ads_name sset;
    if (ads_ssget(NULL, NULL, NULL, NULL, sset) != RTNORM) {
        ads_printf("Nothing Selected\n");
        return;
    }
    if (!pReact)
        pReact = new AsdkMsgReactor;
    
    pReact->detachFromSset(sset);
    ads_ssfree(sset);
}

void
initApp()
{
    acedRegCmds->addCommand("ASDK_DWG_COMMANDS",
        "ADD", "ADD", ACRX_CMD_MODAL, add);

    acedRegCmds->addCommand("ASDK_DWG_COMMANDS",
        "ADDSET", "ADDSET", ACRX_CMD_MODAL, addSet);

    acedRegCmds->addCommand("ASDK_DWG_COMMANDS",
        "REMOVE", "REMOVE", ACRX_CMD_MODAL, remove);

    acedRegCmds->addCommand("ASDK_DWG_COMMANDS",
        "REMOVESET", "REMOVESET", ACRX_CMD_MODAL, removeSet);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_DWG_COMMANDS");
    delete pReact;
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    case AcRx::kLoadDwgMsg:
        if (pReact)
            pReact->clearIds();
        break;
    }
    return AcRx::kRetOK;
}

