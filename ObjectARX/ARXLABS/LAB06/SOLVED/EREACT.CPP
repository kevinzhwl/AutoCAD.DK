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
// ereact.cpp - ARX sample application for entity reactors
//
// There are three different reactors in this program:
//   MsgReactor : general object reactor with all notifications overloaded
//                with ads_printf() function bodies
//   Jreactor   : A special entity reactor that stores an objectId and modifies
//                that object when the object it's attached to is modified.
//   Jpreactor  : A persistent reactor that just watches for modifications to
//                the object it's attached to and prints out information about
//                the object when it's modified
//
// More information about the Jreactor mechanism:
//
//  We create two line entities A and B and attach reactors
//  to both of them. Whenever A's length changes, B is
//  notified and changes its length. Whenever B's length
//  changes, A is notified.  You might think this would
//  lead to an infinite loop,  but when an attempt is made
//  to open object A inside the reactor which is called in
//  reaction to the changes in B occasioned by the reactor
//  called due to the original changes in A, acdbOpenObject
//  returns the error code eOpenForNotify which breaks the
//  infinite loop.


#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "adeskabb.h"

#define streq(s,t) (strcmp((s),(t))==0)


// Function Prototypes
//
void ereact( void );
void attachMessages( void );
void createLines( void );
void createPersistent( void );
Adesk::Boolean getYorN( const char* pStr );
Adesk::Boolean append( AcDbEntity* pEntity, AcDbObjectId& objId );
Adesk::Boolean append( AcDbEntity* pEntity );
int sa_u2w( ads_point p1, ads_point p2 );
int sa_w2u( ads_point p1, ads_point p2 );
AcDbEntity* selectEntity( AcDb::OpenMode openMode );
AcDbEntity* selectEntity( AcDbObjectId& eId, AcDb::OpenMode openMode );
void initApp( void );
void unloadApp( void );
extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* );


class MsgReactor;

// Global pointer to store the address of the MsgReactor object used in this
// application. We use only one actual reactor object to conserve memory.  The
// member functions of the reactor object is passed a pointer to the object
// sending the notification so only one reactor object is needed because it
// can distinguish which entity is sending the notification.
//
MsgReactor *pMsgReactor = NULL;

// Global AcDbObjectIdArray that stores the objectIds of all the entities
// this application has attached the MsgReactor object to. This array is
// used to remove the MsgReactor object from these entities during
// application unloading. 
//
AcDbObjectIdArray msgReactorEntList;

// For the jreactor reactors we will be using more than one,  so we need to
// work with a dynamic array of structures each structure containing a pointer
// to the reactor,  and the objectId of the entity it was attached to.

// Here's the structure to store an objectId/reactor pointer pair
//
struct ReactorEntityPair {
    AcDbObjectId entity;
    AcDbObjectReactor *pReactor;
};

// Here's the Global AcDbVoidPtrArray that stores ReactorEntityPair
// structures for the jreactors attached in this program so that
// they can be removed when the application unloads.
//
AcDbVoidPtrArray reactorList;


void
ereact()
{
    char kw[20];
    ads_initget(0, "Messages Persistent Lines");
    int rc = ads_getkword("Messages/Persistent/<Lines>: ", kw);

    if (rc == RTNONE) {
        strcpy(kw, "Lines");
        rc = RTNORM;
    }
    if (rc != RTNORM) {
        ads_printf("Nothing selected.\n");
        return;
    }
    if (streq(kw, "Lines")) { createLines(); }
    else if (streq(kw, "Messages")) { attachMessages(); }
    else if (streq(kw, "Persistent")) { createPersistent(); }
}

// MsgReactor - customized entity reactor class which
//              prints out messages at all events:
//
class MsgReactor : public AcDbEntityReactor
{

public:
    MsgReactor() {}; // allow instantiation

    // AcDbObjectReactor protocol:
    //
    virtual void  cancelled(const AcDbObject* dbObj)
    {
        ads_printf("\nInside cancelled.\n");
    }

    virtual void  copied(const AcDbObject* dbObj,
        const AcDbObject* newObj)
    {
        ads_printf("\nInside copied.\n");
    }

    virtual void  erased(const AcDbObject* dbObj,
        Adesk::Boolean pErasing = Adesk::kTrue)
    {
        ads_printf("\nInside erased.\n");
    }

    virtual void  goodbye(const AcDbObject* dbObj)
    {
        ads_printf("\nInside goodbye.\n");
    }

    virtual void  openedForModify(const AcDbObject* dbObj)
    {
        ads_printf("\nInside openedForModify.\n");
    }

    virtual void  modified(const AcDbObject* dbObj)
    {
        ads_printf("\nInside modified.\n");
    }

    virtual void  modifyUndone(const AcDbObject* dbObj)
    {
        ads_printf("\nInside modifyUndone.\n");
    }

    virtual void  modifiedXData(const AcDbObject* dbObj)
    {
        ads_printf("\nInside modifiedXData.\n");
    }

    virtual void unappended(const AcDbObject* dbObj)
    {
        ads_printf("\nInside unappended.\n");
    }

    virtual void reappended(const AcDbObject* dbObj)
    {
        ads_printf("\nInside reappended.\n");
    }

    virtual void objectClosed(const AcDbObjectId objId)
    {
        ads_printf("\nInside objectClosed.\n");
    }

    // AcDbEntityReactor protocol:
    //
    virtual void  modifiedGraphics(const AcDbEntity* dbObj)
    {
        ads_printf("\nInside modifiedGraphics.\n");
    }
};


void attachMessages()
{
    AcDbEntity *pEnt;
    pEnt = selectEntity(AcDb::kForRead);

    if (pEnt) {
        // Get the entity's objectId and add it to the msgReactorEntList
        // array so that we can access the entity at cleanup and remove the
        // reactor.
        //
        // msgReactorEntList is a dynamic array of objectId's and works
        // with copies of the ids so we don't need to dynamically allocate
        // the objectId we add.
        //
        msgReactorEntList.append(pEnt->objectId());

        if (pMsgReactor == NULL) {  
            // no MsgReactor created yet so make one
            pMsgReactor = new MsgReactor();
        }

        // attach the reactor to an entity
        // don't forget to close the entity when done!
        //
        // ... Next 2 lines complete this ...
        pEnt->addReactor(pMsgReactor);
        pEnt->close();
    }
}

// Jreactor - customized entity reactor class which
// hooks up two lines:
//
class Jreactor : public AcDbEntityReactor
{
public:
    Jreactor(AcDbObjectId i, double f=1.0) { mId=i; mFactor=f; };
    virtual void modified(const AcDbObject* dbObj);

private:
    AcDbObjectId mId;
    double mFactor;
};

void Jreactor::modified(const AcDbObject* obj)
{
    AcDbLine *pLine = AcDbLine::cast(obj);
    if (!pLine) {
        const char *cstr = obj->isA()->name();
        ads_printf("This is a %s.\n", cstr);
        ads_printf("I only work with lines. Sorry.\n");
        return;
    }
    ads_printf("\nReactor attached to %lx calling %lx.\n",
    pLine->objectId(), mId);

    //
    // open object to update:
    //
    AcDbEntity *pEnt;
    Acad::ErrorStatus es = acdbOpenObject(pEnt, mId, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_printf("\nacdbOpenObject in Jreactor failed with error %d%s.\n",
            es, es==83 ? " (open for write)" 
            : es==85 ? " (open for notify)" : "");
        return;
    }
    AcDbLine *pLine2 = AcDbLine::cast(pEnt);
    if (!pLine2) {
        const char *pCstr = pEnt->isA()->name();
        ads_printf("This reactor is attached to a %s.\n", pCstr);
        ads_printf("It should only be attached to lines. Sorry.\n");
        pEnt->close();
        return;
    }
    // get length of modified entity:
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

void createLines()
{
    AcDbDatabase *pDb = acdbCurDwg();

    AcDbLine *pLineA = new AcDbLine;
    pLineA->setDatabaseDefaults(pDb);
    pLineA->setStartPoint(AcGePoint3d(1,1,0));
    pLineA->setEndPoint(AcGePoint3d(2,1,0));

    AcDbObjectId aId;
    if (!append(pLineA, aId)) {
		delete pLineA;
		return;
	}
    ads_printf("Line A is %lx from 1,1 to 2,1.\n",
    pLineA->objectId());

    AcDbLine *pLineB = new AcDbLine;
    pLineB->setDatabaseDefaults(pDb);
    pLineB->setStartPoint(AcGePoint3d(1,2,0));
    pLineB->setEndPoint(AcGePoint3d(2,2,0));

    AcDbObjectId bId;
    if (!append(pLineB, bId)) {
        pLineA->erase();
        pLineA->close();
        delete pLineB;
        return;
    }
    ads_printf("Line B is %lx from 1,2 to 2,2.\n",
    pLineB->objectId());

    Jreactor *pRa;
    // create a new Jreactor with B's object id.  Attach it to line A.
    // Use pRa to point to the reactor.  Don't forget to close line
    // A when you're done with it.
    //
    // ... Next 3 lines complete this ...
    pRa = new Jreactor(bId);
    pLineA->addReactor(pRa);
    pLineA->close();

    // Now dynamically create a ReactorEntityPair structure and
    // store the objectId of the entity and the address of the
    // reactor object so that the entity can be opened at cleanup
    // time to remove the reactor. Then add the structure to the
    // global reactorList array.
    //
    ReactorEntityPair *pPair = new ReactorEntityPair;
    pPair->entity = aId;
    pPair->pReactor = pRa;
    reactorList.append(pPair);



    Jreactor *pRb;
    // create a new Jreactor with A's object id
    // set pRb to point to the reactor
    // attach it to line B
    // don't forget to close things
    // ... Next 3 lines complete this...
    pRb = new Jreactor(aId);
    pLineB->addReactor(pRb);
    pLineB->close();

    // Now dynamically create a ReactorEntityPair structure and
    // store the objectId of the entity and the address of the
    // reactor object so that the entity can be opened at cleanup
    // time to remove the reactor. Then add the structure to the
    // global reactorList array.
    //
    pPair = new ReactorEntityPair;
    pPair->entity = bId;
    pPair->pReactor = pRb;
    reactorList.append(pPair);
}


// Jpreactor - customized AcDbObject for persistent
//       reactor notification:
//
class Jpreactor : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(Jpreactor);
    Jpreactor() {}
    virtual void modified(const AcDbObject* dbObj);
};

ACRX_DXF_DEFINE_MEMBERS(Jpreactor, AcDbObject, 0, Jpreactor, Ereact);

void Jpreactor::modified(const AcDbObject * obj)
{
    const char * cstr = obj->isA()->name();
    ads_printf("\nThe %s with id %lx has been modified.\n",
        cstr, obj->objectId());
}

Adesk::Boolean
statOk(Acad::ErrorStatus stat)
{
    if (stat == Acad::eOk)
        return Adesk::kTrue;
    ads_printf("\nStatus Check Failed:  %d\n", stat);
    return Adesk::kFalse;
}

void
createPersistent()
{
    // Open the namedObject Dictionary.  Check to see if there is an entry
    // under the name we wish to use for your storage dictionary.  If not,
    // then create a dictionary object and add it to the namedobject
    // Dictionary.  Then add the jpreactor object to this dictionary and set
    // rId to the objectId returned for it.
    //
    AcDbDictionary *pNamedObjDict, *pDict;
    acdbCurDwg()->getNamedObjectsDictionary(pNamedObjDict, AcDb::kForRead);

    Acad::ErrorStatus es = pNamedObjDict->getAt("test_dict",
        (AcDbObject*&)pDict, AcDb::kForWrite);
    if (es == Acad::eKeyNotFound) {
        pDict = new AcDbDictionary;
        AcDbObjectId dictId;
        pNamedObjDict->upgradeOpen();
        pNamedObjDict->setAt("test_dict", pDict, dictId);
    } 
    pNamedObjDict->close();

    AcDbObjectId rId;
    es = pDict->getAt("jpreactor", rId);
    if (es == Acad::eKeyNotFound) {
        Jpreactor *pReactor = new Jpreactor();
        pDict->setAt("jpreactor", pReactor, rId);
        pReactor->close();
    }
    pDict->close();

    AcDbEntity *pEnt = selectEntity(AcDb::kForWrite);

    if (pEnt) {
        // attach a persistent connection
        // from the Jpreactor object
        // to the selected entity:
        //
        //...next line completes...
        pEnt->addPersistentReactor(rId);


        es = pEnt->close();
        if (Acad::eOk != es) {
            acrx_abort("\nError %d closing entity.\n", es);
        }
    }
}

// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append(AcDbEntity* pEntity)
{
    AcDbObjectId objId;
    return append(pEntity, objId);
}

Adesk::Boolean
append(AcDbEntity* pEntity, AcDbObjectId& objId)
{

    AcDbDatabase* pDb = acdbCurDwg();
    if (pDb == NULL) {
        ads_alert("No database!");
        return Adesk::kFalse;
    }
    
    AcDbBlockTable *pBlockTable;
    if (pDb->getBlockTable(pBlockTable, AcDb::kForRead) != Acad::eOk) {
        ads_alert("Failed to get block table!");
        return Adesk::kFalse;
    }
    
    AcDbBlockTableRecord *pBlockRec;
    if (pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite)
        != Acad::eOk)
    {
        ads_alert("Failed to get block table record!");
        pBlockTable->close();
        return Adesk::kFalse;
    }

    if (pBlockRec->appendAcDbEntity(objId, pEntity) != Acad::eOk) {
        ads_alert("Failed to append entity!");
        pBlockTable->close();
        pBlockRec->close();
        return Adesk::kFalse;
    }
    pBlockRec->close();
    pBlockTable->close();
    return Adesk::kTrue;
}

// selectEntity - utility function to select entity
//
// Select entity, retrieve object Id and open it,
// creating and returning a valid object pointer.
//
AcDbEntity*
selectEntity(AcDb::OpenMode openMode)
{
    AcDbObjectId eId;
    return selectEntity(eId, openMode);
}

AcDbEntity*
selectEntity(AcDbObjectId& eId, AcDb::OpenMode openMode)
{
    ads_name en;
    ads_point pt;
    int rc = ads_entsel("\nSelect an entity: ", en, pt);

    if (rc != RTNORM) {
        ads_printf("Nothing selected.\n", rc);
        return NULL;
    }

    Acad::ErrorStatus es = acdbGetObjectId(eId, en);
    if (es != Acad::eOk) {
        ads_printf("Either acdbGetObjectId or ads_entsel failed: "
            "Entity name <%lx,%lx>, error %d.\n", en[0], en[1], es);
        return NULL;
    }
    AcDbEntity * ent;

    es = acdbOpenObject(ent, eId, openMode);
    if (es != Acad::eOk) {
        ads_printf("acdbOpenObject failed with error %d.\n", es);
        return NULL;
    }
    return ent;
}

// ----- Rx interface -----

void
initApp()
{
    acedRegCmds->addCommand("EREACT", "EREACT", "EREACT",
        ACRX_CMD_MODAL, ereact);
    Jpreactor::rxInit();
    acrxBuildClassHierarchy();
}

void
unloadApp()
{
    acedRegCmds->removeGroup("EREACT");

    // If acdbCurDwg() returns non-NULL then this app is unloading.
    // Otherwise,  AutoCAD is closing down and it's too late to
    // remove reactors from entities (nor do we need to anyway).
    //
    if (acdbCurDwg()) {
        // Remove the MsgReactor from all the entities it's been
        // attached to
        //
        int length = msgReactorEntList.length();
        AcDbEntity *pEnt;
        for (int i=0; i < length; i++) {
            acdbOpenObject(pEnt, msgReactorEntList[i], AcDb::kForRead,
                Adesk::kTrue);
            pEnt->removeReactor(pMsgReactor);
            pEnt->close();
        }

        // Remove all the jReactors added by this program
        //
        length = reactorList.length();
        for (i=0; i < length; i++) {
            acdbOpenObject(pEnt,
                ((ReactorEntityPair*) reactorList[i])->entity,
                AcDb::kForRead, Adesk::kTrue);
            pEnt->removeReactor(
                ((ReactorEntityPair*) reactorList[i])->pReactor);
            pEnt->close();
            delete ((ReactorEntityPair*)reactorList[i])->pReactor;
        }
    }

    // Remove the Jpreactor class from the ACRX runtime class hierarchy.
    // If this is done while database is still active, it should cause
    // all objects of class Jpreactor to be turned into proxies. 
    //
    deleteAcRxClass(Jpreactor::desc());
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
        // In case it's a new drawing being loaded,  attempt to 
        // empty the arrays.  If they're already empty,  no harm done.
        //
        for (; !msgReactorEntList.isEmpty();) {
            msgReactorEntList.removeLast();
        }

        if (pMsgReactor != NULL) {
            delete pMsgReactor;
            pMsgReactor = NULL;
        }
    
        ReactorEntityPair *pPair;
        for (; !reactorList.isEmpty();) {
            pPair = (ReactorEntityPair*) reactorList.last();
            reactorList.removeLast();
            delete pPair->pReactor;
            delete pPair;
        }
    }
    return AcRx::kRetOK;
}

