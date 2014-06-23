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
// Description:
//
//  Test App for AcDbDatabaseReactor,

#include "rxobject.h"
#include "rxregsvc.h"
#include "rxdlinkr.h"
#include "rxditer.h"
#include "aced.h"
#include "dbmain.h"
#include "dbdict.h"
#include "dbidmap.h"
#include "adslib.h"

void printDbEvent(const AcDbObject*, const char* eventStr);
void printObj(const AcDbObject* pObj);
void watchDb();
void clearReactors();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkDbReactor;

long gEntAcc = 0;            // Global entity count
AsdkDbReactor *gpDbr = NULL; // pointer to database reactor

class AsdkDbReactor : public AcDbDatabaseReactor
//
// Custom AcDbDatabaseReactor class for Database
// event notification.
//
{
public:

    virtual void objectAppended(const AcDbDatabase* dwg,
        const AcDbObject* dbObj);

    virtual void objectModified(const AcDbDatabase* dwg,
        const AcDbObject* dbObj);

    virtual void objectErased(const AcDbDatabase* dwg,
        const AcDbObject* dbObj, Adesk::Boolean pErased);
};


// Called whenever an object is added to the database
//
void
AsdkDbReactor::objectAppended(const AcDbDatabase* db,
    const AcDbObject* pObj)
{
    printDbEvent(pObj, "objectAppended");
    ads_printf(" Db==%lx\n", (long) db);
    gEntAcc++;
    ads_printf("Entity Count = %d\n", gEntAcc);
}


// Called whenever an object in the database is modified
//
void
AsdkDbReactor::objectModified(const AcDbDatabase* db,
    const AcDbObject* pObj)
{
    printDbEvent(pObj, "objectModified");
    ads_printf(" Db==%lx\n", (long) db);
}


// Called whenever an object is erased from the database
//
void
AsdkDbReactor::objectErased(const AcDbDatabase* db,
    const AcDbObject* pObj, Adesk::Boolean pErased)
{
    if (pErased) {
        printDbEvent(pObj, "objectErased");
        gEntAcc--;
    } else {
        printDbEvent(pObj, "object(Un)erased");
        gEntAcc++;
    }
    ads_printf(" Db==%lx\n", (long) db);
    ads_printf("Entity Count = %d\n", gEntAcc);
}


// Prints the message passed in by eventStr and then
// proceeds to call printObj to print the information about
// the object that's triggered the notification.
//
void
printDbEvent(const AcDbObject* pObj, const char* pEvent)
{
    ads_printf("  Event: AcDbDatabaseReactor::%s ", pEvent);
    printObj(pObj);
}


// Prints out the basic information about the object pointed
// to by pObj.
//
void
printObj(const AcDbObject* pObj)
{
    if (pObj == NULL) {
        ads_printf("(NULL)");
        return;
    }

    AcDbHandle objHand;
    char  handbuf[17];

    // Get the handle as a string
    //
    pObj->getAcDbHandle(objHand);
    objHand.getIntoAsciiBuffer(handbuf);

    ads_printf(
        "\n   (class==%s, handle==%s, id==%lx, db==%lx)",
        pObj->isA()->name(), handbuf,
        pObj->objectId().asOldId(), pObj->database());
}


// Adds a reactor to the database to monitor changes.
// This can be called multiple times without any ill
// effects because subsequent calls will be ignored.
//
void
watchDb()
{
    if (gpDbr == NULL) {
        gpDbr = new AsdkDbReactor();
    }
    acdbCurDwg()->addReactor(gpDbr);
    ads_printf(
        "  Added Database Reactor to acdbCurDwg().\n");
}


// Removes the database reactor
//
void
clearReactors()
{
    if (acdbCurDwg() != NULL) {
        acdbCurDwg()->removeReactor(gpDbr);
        delete gpDbr;
        gpDbr = NULL;
    }
}

// Arx entry point function
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        acedRegCmds->addCommand("ASDK_NOTIFY_TEST",
            "ASDK_WATCH",
            "WATCH",
            ACRX_CMD_TRANSPARENT,
            watchDb);

        acedRegCmds->addCommand("ASDK_NOTIFY_TEST",
            "ASDK_CLEAR",
            "CLEAR",
            ACRX_CMD_TRANSPARENT,
            clearReactors);
        break;
    case AcRx::kUnloadAppMsg:
        clearReactors();
        acedRegCmds->removeGroup("ASDK_NOTIFY_TEST");
        break;
    case AcRx::kLoadDwgMsg:
        // New AcDbDatabase, so if reactor exists
        // attach it.
        //
        if (gpDbr != NULL) {
            watchDb();
        }
    }
    return AcRx::kRetOK;
}

// END CODE APPEARING IN SDK DOCUMENT.
