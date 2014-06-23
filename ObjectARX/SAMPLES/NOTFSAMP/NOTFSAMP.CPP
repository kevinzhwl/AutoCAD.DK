// Next available MSG number is   1
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
// notfsamp.cc:  Arx Notification Sample                   
//
// This program demonstrates basic transient reactor usage, basic persistent
// reactor usage, and a practical example of notfication usage.
//
// The transient reactor classes consist of the following:
//
//   AcRxDLinkerReactor
//   AcEditorReactor
//   AcDbDatabaseReactor
//   AcTransactionReactor 
//   AcDbObjectReactor
//     AcDbEntityReactor
//
// This sample will implement each of these types except AcDbEntityReactor.
// AcDbEntityReactor is derived from AcDbObjectReactor, and sample code
// implementing this reactor type would be quite similar to sample code
// implementing AcDbObjectReactor. This is therefore left as an exercise.
//
// The implementation of the transient reactor classes is trivial; in 
// each case, the notifications result in a simple printout of information
// to AutoCAD's command window.  
//
// The persistent reactor example is likewise trivial, but does demonstrate
// the necessary steps for creating and using a persistent reactor.
//
// The next example demonstrates using a few reactors to cause each new
// circle one adds to the database to be inscribed with a square.
//
// Finally, there is an example for iterating through the reactor chain of
// a given object.  This example illustrates that you can identify the type
// of reactor found, and even force fire the reactor's methods.
//

#include "rxobject.h"
#include "rxregsvc.h"
#include "rxdlinkr.h"
#include "rxditer.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "actrans.h"
#include "appinfo.h"

#include "notfsamp.h"

#include "adslib.h"
#include "ol_errno.h"



// locally defined entry point invoked by Rx.
//
extern "C" {
    AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void *pkt);
}

// prototypes needed as forward declarations
//
void inscribe();



// ********************* UTILITY ROUTINES ***************************

Adesk::Boolean 
statOk(Acad::ErrorStatus stat)
{
    if (stat == Acad::eOk)
        return Adesk::kTrue;
    ads_printf(/*MSG0*/"\nStatus Check Failed:  %d\n", stat);
    return Adesk::kFalse;
}


static Adesk::Boolean 
getAorR(const char *pStr)
{
    char aorr_str[132];
    
    // specific prompt.
    ads_printf("\n%s", pStr);
    
    ads_initget(0, "Add Remove");
    
    aorr_str[0] = 'A';
    aorr_str[1] = '\0';
    
    switch (ads_getstring(Adesk::kFalse, " -- Remove/<Add>:  ", aorr_str)) {
    case RTKWORD:
        ads_getinput(aorr_str);
        // Deliberate fallthrough
        //
    default:
        break;
    } 
    
    return (!((aorr_str[0] == 'R') || (aorr_str[0] == 'r')));
}


void 
printObj(const AcDbObject *pObj)
{
    if (pObj == NULL) {
        ads_printf("(NULL)");
        return;
    }
    
    AcDbHandle objHand;
    char  handbuf[17];
    
    // Get the handle string
    //
    pObj->getAcDbHandle(objHand);
    objHand.getIntoAsciiBuffer(handbuf);
    
    ads_printf
        ("\n   (class==%s, handle==%s, id==%lx, db==%lx)",
        pObj->isA()->name(), handbuf,
        pObj->objectId().asOldId(),
        pObj->database());
}


static void 
printEntEvent(const AcDbObject *pObj, 
              char       *pEventStr, 
              const AcDbObject *pObj2 = NULL)
{
    ads_printf("\n  Event: AcDbObjectReactor::%s", pEventStr);
    printObj(pObj);
    if (pObj2 != NULL)
        printObj(pObj2);
    ads_printf("\n");
}


static void 
printAcEdEvent(const char *pEvent)
{
    ads_printf("\n  Event:  AcEditorReactor::%s ", pEvent);
}


void 
printDbEvent(const AcDbObject *pObj, const char *pEventStr)
{
    ads_printf("\n  Event: AcDbDatabaseReactor::%s ", pEventStr);
    printObj(pObj);
}

Acad::ErrorStatus 
getAcDbBlockTablePtr(AcDbDatabase* pDb, AcDbBlockTableRecord*& pSpaceRecord) 
{
    // open block table to search for model space block:
    //
    Acad::ErrorStatus es;
    AcDbBlockTable *pBlockTable;
    
    if ((es = pDb->getBlockTable(pBlockTable, AcDb::kForRead)) != Acad::eOk) {
        ads_printf("Unable to open block table \n" );
        return es;
    }
    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
        pSpaceRecord, AcDb::kForWrite)) != Acad::eOk) {
        ads_printf( "Unable to open model space block.  Error %d\n", es);
        if ((es = pBlockTable->close()) != Acad::eOk) {
            ads_printf("Unable to close Block Table\n");
            return es;
        }
        return es;
    }
    // close block table
    //
    if ((es = pBlockTable->close()) != Acad::eOk) {
        ads_printf("Unable to close Block Table\n");
        return es;
    }
    
    return Acad::eOk;
}

Acad::ErrorStatus 
getPersReactorKey(char*& keyname, AcDbObjectId persObjId)
{
    Acad::ErrorStatus retStat;
    AcDbObject        *pPersReacObj;
    
    if ((retStat = acdbOpenAcDbObject(pPersReacObj,
        persObjId, AcDb::kForWrite)) != Acad::eOk) {
        ads_printf(
            "\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        return retStat;
    }
    
    AcDbObjectId dictId = pPersReacObj->ownerId();
    if (dictId == AcDbObjectId::kNull) {
        ads_printf("\nReactor's OwnerId not set");
        pPersReacObj->close();
        return Acad::eNullObjectId;
    }
    AcDbDictionary *pDict;
    if ((retStat = acdbOpenObject(pDict,
        dictId, AcDb::kForRead)) != Acad::eOk) {
        ads_printf(
            "\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        pPersReacObj->close();
        return retStat;
    }
    retStat = pDict->nameAt(persObjId, keyname);
    pDict->close();
    pPersReacObj->close(); 
    return retStat;
}

// ****************************** GLOBALS *****************************
//

AsdkSimpleObjReactor   *gpSimpleObjReactor = NULL;
AsdkAppReactor         *gpAppReactor = NULL;
AsdkSysVarReactor      *gpSysVarReactor = NULL;
AsdkCommandReactor     *gpCommandReactor = NULL;
AsdkDbReactor          *gpDbReactor = NULL;
AsdkTransReactor       *gpTransReactor = NULL;

static Adesk::Boolean amWatchingDb;
static AcDbObjectIdArray storedAr;

AsdkInscribeReactor   *gpInscribeReactor = NULL;
AsdkDbInscribeReactor *gpDbInsReactor = NULL;

// ************ IMPLEMENTATIONS OF TRANSIENT REACTOR CLASSES ***********
//


// Minimal AcDbObjectReactor -- Database event Notification
//
// This class, AsdkSimpleObjReactor implements just a few of the
// notifications available from AcDbObjectReactor.  You could also
// choose to be notified of the following events by overriding their
// methods from AcDbObjectReactor...
//   cancelled
//   goodbye
//   openedForModify
//   modifyUndone
//   modifiedXData
//   unappended
//   objectClosed.
//
// Additionally, if you had derived from AcDbEntityReactor, you would
// have the method 
//   modifiedGraphics
// avaible to override.
//
// The command WATCH_ENT will add or remove this reactor to a single
// selected object.
//

void 
AsdkSimpleObjReactor::modified(const AcDbObject *pObj)
{
    printEntEvent(pObj, "Modified");
}

void 
AsdkSimpleObjReactor::erased(const AcDbObject *pObj, Adesk::Boolean erasing)
{
    if (erasing)
        printEntEvent(pObj, "Erased");
    else
        printEntEvent(pObj, "Unerased");
}

void
AsdkSimpleObjReactor::copied(const AcDbObject* pObj, const AcDbObject* pNewObj)
{
    if(pNewObj->objectId() == AcDbObjectId::kNull)
    {
        // Shallow clone case:
        //
        // See AsdkPersReactor::copied(...) for details
    }
    else
    {
        printEntEvent(pObj, "copied from/to", pNewObj);
    }
}

// AcRxDLinkerReactor --  Application Load Notification 
//
// This class, AsdkAppReactor, trivially implements both of the methods
// available from AcRxDLinkerReactor.  This reactor class is designed to
// provide notification of Application loading and unloading.
//
// The command WATCH_APPS will add or remove this reactor to the
// acrxDynamicLinker system object.
//

void 
AsdkAppReactor::rxAppLoaded(const char *pModuleName)
{
    ads_printf("\n  Event:  AcRxDynamicLinkerReactor::rxAppLoaded '%s'\n",
        pModuleName);
}

void 
AsdkAppReactor::rxAppUnloaded(const char *pModuleName)
{
    ads_printf("\n  Event:  AcRxDynamicLinkerReactor::rxAppUnloaded '%s'\n",
        pModuleName);
}


// AcTransactionReactor --  Transaction Notification 
//
// This class, AsdkTransReactor, provides notifications of transaction
// start and end events.
//
// The command WATCH_TRANS will add or remove this reactor to the
// actrTransactionManager system object.
//
// The sample "polysamp" includes test code for transactions.  Loading
// polysamp and running the "TRANSACT" command will trigger these
// notifications.
//

void
AsdkTransReactor::transactionStarted(int& numTransactions)
{
    ads_printf("\n Event: AcTransactionReactor::transactionStarted\n");
    ads_printf(" \n'%d' active or successfully completed transactions\n", 
        numTransactions);
}

void
AsdkTransReactor::transactionEnded(int& numTransactions)
{
    ads_printf("\n Event: AcTransactionReactor::transactionEnded");
    ads_printf(" \n'%d' active or successfully completed transactions\n", 
        numTransactions);
}

void
AsdkTransReactor::transactionAborted(int& numTransactions)
{
    ads_printf("\n Event: AcTransactionReactor::transactionAborted");
    ads_printf(" \n'%d' active or successfully completed transactions\n", 
        numTransactions);
}

void
AsdkTransReactor::endCalledOnOutermostTransaction(int& numTransactions)
{
    ads_printf(
        "\n Event: AcTransactionReactor::endCalledOnOutermostTransaction");
    ads_printf(" \n'%d' active or successfully completed transactions\n", 
        numTransactions);
}

// AcEditorReactor
//
// Following are two classes derived from AcEditorReactor.  AcEditorReactor
// has a large selection of callbacks.  You can be very selective of
// the kinds of events you watch by deriving several different reactors
// from AcEditorReactor, each of which focus on a specific type of event.
// In these examples, we watch System Variable changes, and Command events.
//

// AcEditorReactor --  System Variable Change Notification
//
// The command WATCH_SYSVARS will add or remove this reactor to the
// acedEditor system object to monitor system variables.
//

void 
AsdkSysVarReactor::sysVarWillChange(const char *pVarName)
{
    printAcEdEvent("sysVarWillChange");
    ads_printf(" '%s'\n", pVarName);
}

void 
AsdkSysVarReactor::sysVarChanged(const char *pVarName, Adesk::Boolean success)
{
    printAcEdEvent("sysVarChanged");
    ads_printf(" '%s' (%ssuccessful).\n", pVarName, (success ? "" : "un"));
}


// AcEditorReactor --  Command Event Notification
//
// The command WATCH_COMMANDS will add or remove this reactor to the
// acedEditor system object to monitor commands.
//
// The "commandEnded" reactor is implemented slightly differently than
// the other methods in this class in order to match examples in the
// documentation.


void 
AsdkCommandReactor::commandWillStart(const char *pCmdStr)
{
    printAcEdEvent("commandWillStart");
    ads_printf("  '%s'\n", pCmdStr);
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void 
AsdkCommandReactor::commandEnded(const char *pCmdStr)
{
    // Print the user typed name. Get both the global name
    // and local name and print that out too.
    //
    printAcEdEvent("commandEnded");
    ads_printf(" '%s'\n", pCmdStr);
    
    AcEdCommand* pCmd = NULL;
    if ((pCmd = acedRegCmds->lookupCmd(pCmdStr,
        Adesk::kTrue, Adesk::kTrue)) != NULL)
    {
        ads_printf("\nGlobal name : %s",
            pCmd->globalName());
        ads_printf("\nLocal  name : %s",
            pCmd->localName());
    } else if ((pCmd = acedRegCmds->lookupCmd(pCmdStr,
        Adesk::kFalse, Adesk::kTrue)) != NULL)
    {
        ads_printf("\nGlobal name : %s",
            pCmd->globalName());
        ads_printf("\nLocal  name : %s",
            pCmd->localName());
    } else {
        ads_printf("\nThis is not an ARX-registered"
            " command");
    }
}

// END CODE APPEARING IN SDK DOCUMENT.

void 
AsdkCommandReactor::commandCancelled(const char *pCmdStr)
{
    printAcEdEvent("commandCancelled");
    ads_printf("  '%s'\n", pCmdStr);
}

void 
AsdkCommandReactor::commandFailed(const char *pCmdStr)
{
    printAcEdEvent("commandFailed");
    ads_printf("  '%s'\n", pCmdStr);
}

// Unknown Command Notification Mechanism

// First we need a "loader" function that AutoCAD can call when our
// application lets AutoCAD know that the unknown command is ours
// and we want to deal with it.

AcadAppInfo::CmdStatus unknownCmdLoader(void *)
{
    // Within this function we are expected to do anything necessary
    // to deal with the unknown command situation.  This might include
    // loading one or more other ARX apps or plain dlls to support the
    // command, or it might be as simple as registering the command as
    // we do here.
    //
    acedRegCmds->addCommand("NOTIFY_SAMP",
        "INSCRIBE",
        "INSCRIBE",
        ACRX_CMD_TRANSPARENT,
        inscribe);
    
    // Returning kRetry tells AutoCAD to try and re-execute the unknown
    // command without displaying any unknown command message before
    // doing so.  Since we've now registered the command, this will
    // make it appear to the user as though the command was always
    // there since no error messages will appear and the command will
    // execute normally.
    //
    return AcadAppInfo::kRetry;
}

// Next we need the unknown command reactor to watch for unknown command calls
// and let AutoCAD know when one of them is ours.
//
// This reactor is automatically added to the editor when notfsamp.arx is loaded
// so that it can monitor for the attempted execution of the INSCRIBE command and
// register it when such an attempt occurs.

void 
AsdkUnknownCommandReactor::unknownCommand(const char*             pCmdStr,
                                          AcDbVoidPtrArray *pAppInfoArr)
{
    printAcEdEvent("unknownCommand");
    ads_printf("  '%s'\n", pCmdStr);
    
    if (stricmp("INSCRIBE", pCmdStr) == 0) {
        //First we need to do is create a new AcadAppInfo object
        //
        AcadAppInfo *pInfo = new AcadAppInfo();
        
        // Since we don't need to have AutoCAD load another ARX app
        // for us, all we need to do now is fill in the AcadAppInfo
        // object with the address of our loader function,  and then
        // append the new AcadAppInfo object to the passed in array.
        //
        pInfo->setAppLoader(unknownCmdLoader);
        pAppInfoArr->append(pInfo);
    }
}


// AcDbDatabaseReactor --  Database Event Notification
//
// This class, AsdkDbReactor, trivially implements all of the methods
// available from AcDbDatabaseReactor.  This reactor class is designed to
// provide notification of database events.
//
// The command WATCH_DB will add or remove this reactor to the acedEditor
// system object to monitor database events.
//

void 
AsdkDbReactor::objectAppended(const AcDbDatabase *pDb, const AcDbObject *pObj)
{
    printDbEvent(pObj, "objectAppended");
    ads_printf(" Db==%lx\n", (long) pDb);
}

void 
AsdkDbReactor::objectModified(const AcDbDatabase *pDb, const AcDbObject *pObj)
{
    printDbEvent(pObj, "objectModified");
    ads_printf(" Db==%lx\n", (long) pDb);
}

void 
AsdkDbReactor::objectErased(const AcDbDatabase *pDb,
                            const AcDbObject   *pObj, 
                            Adesk::Boolean      erased)
{
    if (erased)
        printDbEvent(pObj, "objectErased");
    else
        printDbEvent(pObj, "object(Un)erased");
    ads_printf(" Db==%lx\n", (long) pDb);
}


// ************ IMPLEMENTATION OF PERSISTENT REACTOR CLASS ***********
//
// AcDbObject --  Persistent Reactor Example
//
// This class, AsdkPersReactor, trivially implements a few of the methods
// available from AcDbObject, as a persistent Reactor.  
//
// It also adds a custom notification, which can be fired explicitly
// by an application, if that application takes the time to traverse
// an object's reactor chain, in search of that reactor.  This example
// is in the command, LIST_REACTORS.
//
// The command ADD_PERS will add this reactor to a selected
// object to monitor copied and erased events.  The persistent nature
// of the reactor can be verified by attaching the reactor to an object,
// saving and reloading the drawing, and then copying or erasing the
// object in question.
//
// The command REM_PERS will allow the user to delete a persistent reactor
// from a selected entity, if it has one.
//

ACRX_DXF_DEFINE_MEMBERS(AsdkPersReactor,AcDbObject,0,AsdkPersReactor,AutoCAD);

AsdkPersReactor::AsdkPersReactor() {}
AsdkPersReactor::~AsdkPersReactor() {}

void
AsdkPersReactor::erased(const AcDbObject *pObj, Adesk::Boolean erasing)
{
    if (erasing) {
        ads_printf("\n  Event: AsdkPersReactor::erased - erasing ");
    } else {
        ads_printf("\n  Event: AsdkPersReactor::erased - unerasing ");
    }
    printObj(pObj);
    ads_printf("\n");
}

void
AsdkPersReactor::copied(const AcDbObject *pObj, const AcDbObject *pNewObj)

{
    if(pNewObj->objectId() == AcDbObjectId::kNull)
    {
        // Shallow clone case:
        //
        // This will be the case for an ARX object being dragged about
        // We make 'transient' copies of the object using clone to be able to display 
        // the drag image. 
        // (This only applies to first class ARX objects like 'ellipse')
        //
        // Uncomment these lines to see
        //
        //        ads_printf("\n  Event: AsdkPersReactor  Transient Copy");
        //        printObj(pObj);
        //        ads_printf(" from/to ");
        //        if (pNewObj)
        //            printObj(pNewObj);
        //        ads_printf("\n");
    }
    else
    {
        ads_printf("\n  Event: AsdkPersReactor::copied ");
        printObj(pObj);
        ads_printf(" from/to ");
        if (pNewObj)
            printObj(pNewObj);
        ads_printf("\n");
    }
}

void
AsdkPersReactor::custom()
{
    ads_printf("\nThis is a custom notification");
}


Acad::ErrorStatus
AsdkPersReactor::dwgInFields(AcDbDwgFiler *pFiler)
{
    assertWriteEnabled();
    
    return AcDbObject::dwgInFields(pFiler);
}

Acad::ErrorStatus
AsdkPersReactor::dwgOutFields(AcDbDwgFiler *pFiler) const
{
    assertReadEnabled();
    
    return AcDbObject::dwgOutFields(pFiler);
}

// ************ IMPLEMENTATION OF REACTOR CLASSES FOR ***************
// ************   INSCRIBING SQUARES IN NEW CIRCLES   ***************
//

void
AsdkDbInscribeReactor::objectAppended(const AcDbDatabase *pDb, 
                                      const AcDbObject   *pObj)
{
    // Keep track of newly added circles
    //
    // The reason we don't just do the inscription here, is that
    // if a new circle was added via a COPY or ARRAY command, the
    // translation of the new Object to its new location has not
    // yet occured.  So, we would have a new square drawn directly
    // on top of the old square in the originating location, and it
    // would appear that the new circle was not inscribed at all.
    //
    if (pObj->isKindOf(AcDbCircle::desc())) {
        storedAr.append(pObj->objectId());
    }
}

void
AsdkInscribeReactor::commandEnded(const char *cmdStr)
{
    // for each newly added circle...
    //
    for (int i = 0; i < storedAr.length(); i++) {
        
        AcDbCircle* circ;
        acdbOpenObject(circ, storedAr[i], AcDb::kForRead);
        
        
        AcGePoint3d cen = circ->center();
        double rad = circ->radius();
        
        // These will be the vertices of the polyline
        //
        AcGePoint3dArray vertArray;
        vertArray.setLogicalLength(4);
        vertArray.setAll(cen);
        AcGeVector3d xoffset(rad, 0.0, 0.0);
        AcGeVector3d yoffset(0.0, rad, 0.0);
        vertArray[0] += yoffset; // top
        vertArray[1] += xoffset; // right
        vertArray[2] -= yoffset; // bottom
        vertArray[3] -= xoffset; // left
        
        Acad::ErrorStatus es;
        AcDbDatabase * pDb = acdbCurDwg();
        AcDbBlockTableRecord *pSpaceRecord;
        
        if ((es = getAcDbBlockTablePtr(pDb, pSpaceRecord)) != Acad::eOk) {
            ads_printf("Error retrieving BlockTableRecord pointer\n");
            return;
        }
        
        AcDb2dPolyline *pPolyline = new AcDb2dPolyline(
            AcDb::k2dSimplePoly, vertArray, 0, Adesk::kTrue);
        //add polyline to modelspace
        //
        AcDbObjectId polyId;
        if ((es = pSpaceRecord->appendAcDbEntity(polyId, pPolyline))
            != Acad::eOk)
        {
            ads_printf("Unable to append polyline\n");
            delete pPolyline;
            pSpaceRecord->close();
            return;
        }
        
        // close polyline
        //
        if ((es = pPolyline->close()) != Acad::eOk) {
            ads_printf("Unable to close polyline\n");
        }
        
        // Close Block Table Record
        //
        if ((es =  pSpaceRecord->close()) != Acad::eOk) {
            ads_printf("Unable to close BlockTableRecord\n");
            return;
        }
        circ->close();
    }
    storedAr.setPhysicalLength(0);
}


//****************************** COMMANDS *****************************

// "WATCHeNTITY" -- Add or remove a reactor to a single selected
//                object.
//
//

void 
watchEntity()
{
    ads_name ename;
    ads_point pt, xform[4];
    struct resbuf* pResbuf;
    
    
    switch (ads_nentsel("\nPick an Entity to Watch:  ", ename, pt, 
        xform, &pResbuf)) {
        
    case RTNORM:   // Didn't really need this.
        ads_relrb(pResbuf);
        break;
    case RTNONE:   ads_alert("No result value");
        return;
    case RTCAN:    ads_alert("Cancelled");
        return;
    case RTERROR:  
        {            
            resbuf rbuf;
            ads_getvar("ERRNO", &rbuf);
            if (rbuf.resval.rint == OL_ENTSELPICK
                || rbuf.resval.rint == OL_ENTSELNULL)
            {
                ads_alert("No entity was selected");
            } else {
                ads_alert("An unknown error occured");
            }
            return;
        }
    default:       ads_alert("Unknown condition");
        return;
    }
    
    // Now, exchange the ads_name for the object id...
    
    Acad::ErrorStatus retStat;
    AcDbObjectId entityId;
    AcDbEntity *pEnt;
    
    retStat = acdbGetObjectId(entityId, ename);
    // Open the selected entity for Notify
    //
    if ((retStat = acdbOpenAcDbEntity(pEnt, entityId, AcDb::kForNotify))
        != Acad::eOk)
    {
        ads_printf("\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        return;
    }
    
    // Add or remove the reactor from the selected entity
    //
    if (getAorR("Add or Remove Reactor")) {
        pEnt->addReactor(gpSimpleObjReactor);
        ads_printf("  Attached Reactor to entity.\n");
    } else {
        pEnt->removeReactor(gpSimpleObjReactor);
        ads_printf("  Removed Reactor from entity.\n");
    }
    
    pEnt->close();
}

// "WATCHtRANSACTIONS" -- Add or remove a reactor to the 
//                        actrTransactionManager system object.
//
//
void
watchTransactions()
{
    if (getAorR("Add or Remove Transaction reactor")) {
        actrTransactionManager->addReactor(gpTransReactor);
        ads_printf("  Added Reactor to actrTransactionManager.\n");
    } else {
        actrTransactionManager->removeReactor(gpTransReactor);
        ads_printf("  Removed Reactor from actrTransactionManager.\n");
    }
}


// "WATCHaPPS" -- Add or remove a reactor to the acrxDynamicLinker system
//                object.
//
//

void 
watchApps()
{
    if (getAorR("Add or Remove Application reactor")) {
        acrxDynamicLinker->addReactor(gpAppReactor);
        ads_printf("  Added Reactor to acrxDynamicLinker.\n");
    } else {
        acrxDynamicLinker->removeReactor(gpAppReactor);
        ads_printf("  Removed Reactor from acrxDynamicLinker.\n");
    }
}



// "WATCHsYSVARS" -- Add or remove a reactor to the acedEditor system
//                   object to monitor system variables.
//
//

void 
watchSysvars()
{
    if (getAorR("Add or Remove Sysvar reactor")) {
        acedEditor->addReactor(gpSysVarReactor);
        ads_printf("  Added Sysvar Reactor to acedEditor.\n");
    } else {
        acedEditor->removeReactor(gpSysVarReactor);
        ads_printf("  Removed Sysvar Reactor from acedEditor.\n");
    }
}

// "WATCHcOMMANDS" -- Add or remove a reactor to the acedEditor system
//                    object to monitor commands.
//
//

void 
watchCommands()
{
    if (getAorR("Add or Remove Command reactor")) {
        acedEditor->addReactor(gpCommandReactor);
        ads_printf("  Added Command Reactor to acedEditor.\n");
    } else {
        acedEditor->removeReactor(gpCommandReactor);
        ads_printf("  Removed Command Reactor from acedEditor.\n");
    }
}


// "WATCHdATABASE" -- Add or remove a reactor to the current drawing
//                    to monitor database events.
//
//

void 
watchDatabase()
{
    if (getAorR("Add or Remove Database reactor")) {
        acdbCurDwg()->addReactor(gpDbReactor);
        amWatchingDb = Adesk::kTrue;
        ads_printf("  Added Database Reactor to acdbCurDwg().\n");
    } else {
        acdbCurDwg()->removeReactor(gpDbReactor);
        amWatchingDb = Adesk::kFalse;
        ads_printf("  Removed Database Reactor from acdbCurDwg().\n");
    }
}

// "ADDpERSrEAC" -- Add a persistent reactor to 
//                  object to monitor 
//
//

void
addPersReac()
{
    ads_name ename;
    ads_point pt, xform[4];
    struct resbuf* pResbuf;
    
    
    switch (ads_nentsel("\nPick an Entity to receive a persistent reactor:  ", 
        ename, pt, xform, &pResbuf)) {
        
    case RTNORM:   // Didn't really need this.
        ads_relrb(pResbuf);
        break;
    case RTNONE:   ads_alert("No result value");
        return;
    case RTCAN:    ads_alert("Cancelled");
        return;
    case RTERROR:
        {              
            resbuf rbuf;
            ads_getvar("ERRNO", &rbuf);
            if (rbuf.resval.rint == OL_ENTSELPICK
                || rbuf.resval.rint == OL_ENTSELNULL)
            {
                ads_alert("No entity was selected");
            } else {
                ads_alert("An unknown error occured");
            }
            return;
        }
    default:       ads_alert("Unknown condition");
        return;
    }
    
    char result[132];
    ads_getstring(Adesk::kFalse, "\nEnter a key for the persistent reactor:  ",
        result);
    
    Acad::ErrorStatus retStat;
    
    // Persistent reactor object must be added to a container object
    // such as the NamedObjectsDictionary
    //
    AcDbDictionary *pDict = NULL;
    acdbCurDwg()->getNamedObjectsDictionary(pDict, AcDb::kForWrite);

    if (NULL == pDict)
    {
        ads_printf("\nFailed to open NamedObjectDict");
        return;
    }

    AsdkPersReactor *pPersReactor = new AsdkPersReactor();
    AcDbObjectId    reactorId;
    
    // Let's disallow duplicate keys . . .
    //
    AcDbObjectId tempId;
    while ((retStat = pDict->getAt(result, tempId)) == Acad::eOk) {
        ads_printf("\nDuplicate Key\n");
        ads_getstring(
            Adesk::kFalse, "\nEnter a key for the persistent reactor:  ",
            result);
    }
    
    if ((retStat = pDict->setAt(result, pPersReactor, reactorId)) != Acad::eOk){
        ads_printf("\nFailure for NamedObjectDict setAt: retStat==%d\n",
            retStat);
        // If we failed to hand over the persistent reactor object, let's
        // remember to clean up our mess, and get out.
        //
        delete pPersReactor;
        pDict->close();
        return;
    }
    pPersReactor->close();
    pDict->close();
    
    // Now, exchange the ads_name for the object id...
    
    AcDbObjectId entityId;
    AcDbEntity *pEnt;
    
    retStat = acdbGetObjectId(entityId, ename);
    // Note that object must be opened for write to add persistent reactor
    //
    if ((retStat = acdbOpenAcDbEntity(pEnt, entityId, AcDb::kForWrite))
        != Acad::eOk)
    {
        ads_printf("\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        return;
    }
    
    pEnt->addPersistentReactor(reactorId);
    pEnt->close();
    
    ads_printf("  Attached Persistent Reactor to entity.\n");
}

// "REMpERS" -- Remove a persistent reactor from an entity
//
//

void
remPers()
{
    ads_name ename;
    ads_point pt, xform[4];
    struct resbuf* pResbuf;
    
    
    switch (ads_nentsel(
        "\nPick an Entity to have Persistent reactor(s) removed :  ", 
        ename, pt, xform, &pResbuf))
    {
        
    case RTNORM:   // Didn't really need this.
        ads_relrb(pResbuf);
        break;
    case RTNONE:   ads_alert("No result value");
        return;
    case RTCAN:    ads_alert("Cancelled");
        return;
    case RTERROR:
        {              resbuf rbuf;
        ads_getvar("ERRNO", &rbuf);
        if (rbuf.resval.rint == OL_ENTSELPICK
            || rbuf.resval.rint == OL_ENTSELNULL) {
            ads_alert("No entity was selected");
        } else {
            ads_alert("An unknown error occured");
        }
        return;
        }
    default:       ads_alert("Unknown condition");
        return;
    }
    
    // Now, exchange the ads_name for the object id...
    
    Acad::ErrorStatus retStat;
    AcDbObjectId entityId;
    AcDbEntity *pEnt;
    
    retStat = acdbGetObjectId(entityId, ename);
    // Open the selected entity for Write
    //
    if ((retStat = acdbOpenAcDbEntity(pEnt, entityId, AcDb::kForWrite))
        != Acad::eOk)
    {
        ads_printf("\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        return;
    }
    
    AcDbVoidPtrArray *pReactors;
    void             *pSomething;
    
    AcDbObjectId      persObjId;
    
    pReactors = pEnt->reactors();
    
    if (pReactors != NULL) {
        // Traverse the entity's reactor list looking for persistent reactors
        // to delete
        //
        for (int i = 0; i < pReactors->length(); i++) {
            pSomething = pReactors->at(i);
            if (acdbIsPersistentReactor(pSomething)) {
                persObjId = acdbPersistentReactorObjectId(pSomething);
                
                // Let's get its key from its dictionary, and 
                // ask the user if this is the one to delete.
                //
                char *keyname;
                if ((retStat = getPersReactorKey(keyname, persObjId)) 
                    != Acad::eOk)
                {
                    ads_printf(
                        "\nError retrieving keyname of Persistent Reactor\n");
                    pEnt->close(); 
                    return;
                }
                
                ads_printf("\nThis is the reactor named %s\n", keyname);
                if (getAorR("Remove This Reactor")) {
                    ads_printf("  Reactor not removed.\n");
                } else {
                    pEnt->removePersistentReactor(persObjId);
                    ads_printf("  Removed Reactor from entity.\n");
                    i--;
                }
            } 
        }
    }
    
    pEnt->close();
}

// "WATCHeVENTS" -- Add or remove all transient reactors defined in 
//                  this module. 
//
//                  Prepare for a flood on the text screen...
//
//                  NOTE: if you have been adding reactors
//                        one by one, entering this command and
//                        entering "No" will clear them all.
//
//

void 
clear_reactors()
{
    acrxDynamicLinker->removeReactor(gpAppReactor);
    actrTransactionManager->removeReactor(gpTransReactor);
    acedEditor->removeReactor(gpSysVarReactor);
    acedEditor->removeReactor(gpCommandReactor);
    if (acdbCurDwg() != NULL)
        acdbCurDwg()->removeReactor(gpDbReactor);
}



void 
watchEvents()
{
    if (getAorR("Add or Remove ALL reactors in this module")) {
        acrxDynamicLinker->addReactor(gpAppReactor);
        actrTransactionManager->addReactor(gpTransReactor);
        acedEditor->addReactor(gpSysVarReactor);
        acedEditor->addReactor(gpCommandReactor);
        acdbCurDwg()->addReactor(gpDbReactor);
        ads_printf("\nAdded all AcEditorReactors to acedEditor, \n");
        ads_printf("added AsdkAppReactor to acrxDynamicLinker and\n");
        ads_printf("added AsdkTransReactor to actrTransactionManager and\n");
        ads_printf("added Db Reactor to acdbCurDwg().\n");
        amWatchingDb = Adesk::kTrue;
    } else {
        clear_reactors();
        ads_printf("\nRemoved all AcEditorReactors from acedEditor,\n");
        ads_printf("removed AsdkAppReactor from acrxDynamicLinker and\n");
        ads_printf(
            "removed AsdkTransReactor from actrTransactionManager and\n");
        ads_printf("removed Db Reactor from acdbCurDwg().\n");
        amWatchingDb = Adesk::kFalse;
    }
}

// "INSCRIBE" -- Add reactors to the acedEditor object and to the database.
//               Watch for the addition of circles to the database and inscribe
//               a square in each new circle.
//

void
inscribe()
{
    
    if (getAorR("Add Reactor Set to Inscribe circles?")) {
        gpDbInsReactor = new AsdkDbInscribeReactor();
        acdbCurDwg()->addReactor(gpDbInsReactor);
        ads_printf("  Added Reactor to acdbCurDwg().\n");
        gpInscribeReactor = new AsdkInscribeReactor();
        acedEditor->addReactor(gpInscribeReactor);
        ads_printf("  Added Inscribe Reactor to acedEditor.\n");
    } else {
        acdbCurDwg()->removeReactor(gpDbInsReactor);
        delete gpDbInsReactor;
        gpDbInsReactor = NULL;
        ads_printf("  Removed Reactor from acdbCurDwg().\n");
        acedEditor->removeReactor(gpInscribeReactor);
        delete gpInscribeReactor;
        gpInscribeReactor = NULL;
        ads_printf("  Removed Inscribe Reactor from acedEditor.\n");
    }
}

// "LISTrEACTORS" -- Select an entity, and attempt to list all the reactors
//                    currently attached.  Shows differentiation between 
//                    handling transient and persistent reactors.  
//                    Demonstrates that you can identify the class of the 
//                    reactor found, and you can explicitly call a 
//                    reactor's methods.
//                
//

void
listReactors()
{
    ads_name ename;
    ads_point pt, xform[4];
    struct resbuf* pResbuf;
    
    
    switch (ads_nentsel("\nPick an Entity to List Reactors:  ", ename, pt, 
        xform, &pResbuf))
    {
        
    case RTNORM:   // Didn't really need this.
        ads_relrb(pResbuf);
        break;
    case RTNONE:   ads_alert("No result value");
        return;
    case RTCAN:    ads_alert("Cancelled");
        return;
    case RTERROR:
        {              
            resbuf rbuf;
            ads_getvar("ERRNO", &rbuf);
            if (rbuf.resval.rint == OL_ENTSELPICK
                || rbuf.resval.rint == OL_ENTSELNULL) {
                ads_alert("No entity was selected");
            } else {
                ads_alert("An unknown error occured");
            }
            return;
        }
    default:       ads_alert("Unknown condition");
        return;
    }
    
    // Now, exchange the ads_name for the object id...
    
    Acad::ErrorStatus retStat;
    AcDbObjectId entityId;
    AcDbEntity *pEnt;
    
    retStat = acdbGetObjectId(entityId, ename);
    // Open the selected entity for Notify
    //
    if ((retStat = acdbOpenAcDbEntity(pEnt, entityId, AcDb::kForNotify))
        != Acad::eOk)
    {
        ads_printf("\nFailure for openAcDbObject: retStat==%d\n",
            retStat);
        return;
    }
    
    
    // THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
    
    AcDbVoidPtrArray *pReactors;
    void             *pSomething;
    
    AcDbObjectReactor *pObjReactor;
    AcDbObjectId       persObjId;
    AcDbObject        *pPersReacObj;
    
    pReactors = pEnt->reactors();
    
    if (pReactors != NULL && pReactors->length() > 0) {
        for (int i = 0; i < pReactors->length(); i++) {
            pSomething = pReactors->at(i);
            // Is it a persistent reactor?
            //
            if (acdbIsPersistentReactor(pSomething)) {
                persObjId = acdbPersistentReactorObjectId(
                    pSomething);
                ads_printf("\n\nPersistent reactor found.");
                
                // Let's echo the keyname to the user...
                //
                char *keyname = NULL;
                getPersReactorKey(keyname, persObjId);
                if (keyname) {
                    ads_printf("\nThis is the reactor named %s",
                        keyname);
                    free (keyname);
                }
                
                // Let's open it up and see if it's one of
                // ours. If it is, let's fire the custom
                // notification.
                //
                if ((retStat =
                    acdbOpenAcDbObject(pPersReacObj,
                    persObjId, AcDb::kForNotify))
                    != Acad::eOk)
                {
                    ads_printf("\nFailure for"
                        " openAcDbObject: retStat==%d\n",
                        retStat);
                    return;
                }
                AsdkPersReactor *pTmpPers;
                if ((pTmpPers =
                    AsdkPersReactor::cast((AcRxObject*)
                    pPersReacObj)) != NULL)
                {
                    pTmpPers->custom();
                }
                pPersReacObj->close(); 
            } else {
                // Or is it transient?
                //
                pObjReactor = (AcDbObjectReactor *)
                    (pReactors->at(i));
                ads_printf("\n\nTransient Reactor found");
                
                // Let's just report what kind we found...
                //
                if (pObjReactor->isKindOf(
                    AsdkSimpleObjReactor::desc()))
                {
                    ads_printf(" of type"
                        " AsdkSimpleObjReactor");
                } else if (pObjReactor->isKindOf(
                    AcDbEntityReactor::desc()))
                {
                    ads_printf(" of type"
                        " AcDbEntityReactor");
                } else if (pObjReactor->isKindOf(
                    AcDbObjectReactor::desc()))
                {
                    ads_printf(" of type"
                        " AcDbObjectReactor");
                } else {
                    ads_printf(" of unknown type.");
                }
            }
        }
    } else {
        ads_printf("\nThis entity has no reactors.\n");
    }
    
    // END CODE APPEARING IN SDK DOCUMENT.
    
    pEnt->close();
}

// ******************* ARX INTERFACE FUNCTIONS ****************

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    static AsdkUnknownCommandReactor *pUK = new AsdkUnknownCommandReactor();
    
    switch(msg) {
    case AcRx::kInitAppMsg:
        gpSimpleObjReactor   = new AsdkSimpleObjReactor();
        gpAppReactor         = new AsdkAppReactor();
        gpTransReactor       = new AsdkTransReactor();
        gpSysVarReactor      = new AsdkSysVarReactor();
        gpCommandReactor     = new AsdkCommandReactor();
        gpDbReactor          = new AsdkDbReactor();
        amWatchingDb         = Adesk::kFalse;
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_ENT",
            "WATCH_ENT",
            ACRX_CMD_TRANSPARENT,
            watchEntity);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_APPS",
            "WATCH_APPS",
            ACRX_CMD_TRANSPARENT,
            watchApps);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_TRANS",
            "WATCH_TRANS",
            ACRX_CMD_TRANSPARENT,
            watchTransactions);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_SYSVARS",
            "WATCH_SYSVARS",
            ACRX_CMD_TRANSPARENT,
            watchSysvars);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_COMMANDS",
            "WATCH_COMMANDS",
            ACRX_CMD_TRANSPARENT,
            watchCommands);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_DB",
            "WATCH_DB",
            ACRX_CMD_TRANSPARENT,
            watchDatabase);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "WATCH_EVENTS",
            "WATCH_EVENTS",
            ACRX_CMD_TRANSPARENT,
            watchEvents);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "ADD_PERS",
            "ADD_PERS",
            ACRX_CMD_TRANSPARENT,
            addPersReac);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "LIST_REACTORS",
            "LIST_REACTORS",
            ACRX_CMD_TRANSPARENT,
            listReactors);
        
        acedRegCmds->addCommand("NOTIFY_SAMP",
            "REM_PERS",
            "REM_PERS",
            ACRX_CMD_TRANSPARENT,
            remPers);
        
        AsdkPersReactor::rxInit();
        acrxDynamicLinker->unlockApplication(pkt);
        acrxBuildClassHierarchy();
        acedEditor->addReactor(pUK);
        break;
    case AcRx::kUnloadAppMsg:
        //
        // Pull off all the global object reactors, but
        // beware! Either you removed gpSimpleObjReactor
        // (of "watchEntity" command) off of all object 
        // reactor chains, or else you'll die the next 
        // time an object they are attached to try to 
        // invoke them.
        //
        clear_reactors();
        acedEditor->removeReactor(pUK);
        delete pUK;
        if(gpInscribeReactor) {
            acedEditor->removeReactor(gpInscribeReactor);
            delete gpInscribeReactor;
        }
        if (acdbCurDwg()) {
            if (gpDbInsReactor) {
                acdbCurDwg()->removeReactor(gpDbInsReactor);
                delete(gpDbInsReactor);
                gpDbInsReactor = NULL;
            }
        }
        acedRegCmds->removeGroup("NOTIFY_SAMP");
        delete gpSimpleObjReactor;
        delete gpAppReactor;
        delete gpTransReactor;
        delete gpSysVarReactor;
        delete gpCommandReactor;
        delete gpDbReactor;
        deleteAcRxClass(AsdkPersReactor::desc());
    default:
        break;
}
return AcRx::kRetOK;
}
