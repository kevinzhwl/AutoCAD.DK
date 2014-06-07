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
#include "dbapserv.h"
#include "adslib.h"
#include "acdocman.h"

void printDbEvent(const AcDbObject*, const char* eventStr);
void printObj(const AcDbObject* pObj);
void watchDb();
void clearReactors();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkDbReactor;

class AsdkDocReactor: public AcApDocManagerReactor
{
public:
	virtual void documentToBeActivated(AcApDocument* pDoc);
	virtual void documentCreated(AcApDocument* pDoc);
	virtual void documentToBeDestroyed(AcApDocument* pDoc);
};

class AsdkPerDocData {
	friend class AsdkAppDocGlobals;
public:
	AsdkPerDocData(AcApDocument* pDoc);
private:
	AcApDocument* m_pDoc;
	AsdkPerDocData* m_pNext;
	long m_EntAcc;			// Entity count
	AsdkDbReactor* m_pDbr;	// Pointer to database reactor
};

class AsdkAppDocGlobals 
{
public:
	AsdkAppDocGlobals(AcApDocument* pDoc);
	void setGlobals(AcApDocument* pDoc);
	void removeDocGlobals(AcApDocument *pDoc);
	void removeAllDocGlobals(AsdkPerDocData* pTarget);
	void unload();
	long &entityCount();
	void incrementEntityCount();
	void decrementEntityCount();
	AsdkDbReactor *dbReactor();
	void setDbReactor(AsdkDbReactor *pDb);
private:
	AsdkPerDocData *m_pHead;
	AsdkPerDocData *m_pData;
	AsdkDocReactor *m_pDocReactor;
};

AsdkAppDocGlobals *gpAsdkAppDocGlobals;

//
// Custom AcDbDatabaseReactor class for Database
// event notification.
//
class AsdkDbReactor : public AcDbDatabaseReactor
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
    acutPrintf(" Db==%lx\n", (long) db);
    gpAsdkAppDocGlobals->incrementEntityCount();
    acutPrintf("Entity Count = %d\n", gpAsdkAppDocGlobals->entityCount());
}


// Called whenever an object in the database is modified
//
void
AsdkDbReactor::objectModified(const AcDbDatabase* db,
    const AcDbObject* pObj)
{
    printDbEvent(pObj, "objectModified");
    acutPrintf(" Db==%lx\n", (long) db);
}


// Called whenever an object is erased from the database
//
void
AsdkDbReactor::objectErased(const AcDbDatabase* db,
    const AcDbObject* pObj, Adesk::Boolean pErased)
{
    if (pErased) {
        printDbEvent(pObj, "objectErased");
      gpAsdkAppDocGlobals->decrementEntityCount();
    } else {
        printDbEvent(pObj, "object(Un)erased");
        gpAsdkAppDocGlobals->incrementEntityCount();
    }
    acutPrintf(" Db==%lx\n", (long) db);
    acutPrintf("Entity Count = %d\n", gpAsdkAppDocGlobals->entityCount());
}


// Prints the message passed in by eventStr and then
// proceeds to call printObj to print the information about
// the object that's triggered the notification.
//
void
printDbEvent(const AcDbObject* pObj, const char* pEvent)
{
    acutPrintf("  Event: AcDbDatabaseReactor::%s ", pEvent);
    printObj(pObj);
}


// Prints out the basic information about the object pointed
// to by pObj.
//
void
printObj(const AcDbObject* pObj)
{
    if (pObj == NULL) {
        acutPrintf("(NULL)");
        return;
    }

    AcDbHandle objHand;
    char  handbuf[17];

    // Get the handle as a string
    //
    pObj->getAcDbHandle(objHand);
    objHand.getIntoAsciiBuffer(handbuf);

    acutPrintf(
        "\n   (class==%s, handle==%s, id==%lx, db==%lx)",
        pObj->isA()->name(), handbuf,
        pObj->objectId().asOldId(), pObj->database());
}

// Document swapping functions
void
AsdkDocReactor::documentToBeActivated(AcApDocument *pDoc)
{
	gpAsdkAppDocGlobals->setGlobals(pDoc);
}

void
AsdkDocReactor::documentCreated(AcApDocument *pDoc)
{
	gpAsdkAppDocGlobals->setGlobals(pDoc);
}

void
AsdkDocReactor::documentToBeDestroyed(AcApDocument *pDoc)
{
	gpAsdkAppDocGlobals->removeDocGlobals(pDoc);
}

AsdkPerDocData::AsdkPerDocData(AcApDocument *pDoc)
{
	m_pDoc = pDoc;
	m_pNext = NULL;
	m_EntAcc = 0;
	m_pDbr = NULL;
}

AsdkAppDocGlobals::AsdkAppDocGlobals(AcApDocument *pDoc)
{
	m_pData = m_pHead = NULL;
	m_pDocReactor = new AsdkDocReactor();
	acDocManager->addReactor(m_pDocReactor);
}

// Iterate through the list until we find the doc's global data.
// If it's not found, create a new set of doc globals.
//
void
AsdkAppDocGlobals::setGlobals(AcApDocument *pDoc)
{
    AsdkPerDocData *p_data = m_pHead, *prev_data = m_pHead;
    while (p_data != NULL) {
        if (p_data->m_pDoc == pDoc) {
            m_pData = p_data;
            break;
        }
        prev_data = p_data;
        p_data = p_data->m_pNext;
    }
    if (p_data == NULL) {
        if (m_pHead == NULL)
            m_pHead = m_pData = new AsdkPerDocData(pDoc);
        else
            prev_data->m_pNext = m_pData = new AsdkPerDocData(pDoc);
    }
}
// Delete the globals associated with pDoc.
//
void
AsdkAppDocGlobals::removeDocGlobals(AcApDocument *pDoc)
{
    AsdkPerDocData  *p_data = m_pHead, *prev_data = m_pHead;
    while (p_data != NULL) {
        if (p_data->m_pDoc == pDoc) {
            if (p_data == m_pHead)
                m_pHead = p_data->m_pNext;
            else
                prev_data->m_pNext = p_data->m_pNext;
            if (m_pData == p_data)
                m_pData = m_pHead;
            delete p_data;
            break;
        }
        prev_data = p_data;
        p_data = p_data->m_pNext;
    }
}

// Delete all the doc globals in the list (recursively).
//
void
AsdkAppDocGlobals::removeAllDocGlobals(AsdkPerDocData *p_target)
{
    if (p_target == NULL)
        return;
    if (p_target->m_pNext != NULL)
        removeAllDocGlobals(p_target->m_pNext);
	if (p_target->m_pDbr != NULL)
	{
		acdbHostApplicationServices()->workingDatabase()->removeReactor(p_target->m_pDbr);
		delete p_target->m_pDbr;
		p_target->m_pDbr = NULL;
	}
    delete p_target;
}

// Application was unloaded - delete everything associated with this
//
void AsdkAppDocGlobals::unload()
{
    acDocManager->removeReactor(m_pDocReactor);
    delete m_pDocReactor;
    removeAllDocGlobals(m_pHead);
    m_pHead = m_pData = NULL;
}

long &
AsdkAppDocGlobals::entityCount()
{
	return m_pData->m_EntAcc;
}

void
AsdkAppDocGlobals::incrementEntityCount()
{
	m_pData->m_EntAcc++;
}

void
AsdkAppDocGlobals::decrementEntityCount()
{
	m_pData->m_EntAcc--;
}

AsdkDbReactor *
AsdkAppDocGlobals::dbReactor()
{
	return m_pData->m_pDbr;
}

void
AsdkAppDocGlobals::setDbReactor(AsdkDbReactor *pDb)
{
	m_pData->m_pDbr = pDb;
}

// Adds a reactor to the database to monitor changes.
// This can be called multiple times without any ill
// effects because subsequent calls will be ignored.
//
void
watchDb()
{
    AsdkDbReactor *pDbr;
	if (gpAsdkAppDocGlobals->dbReactor() == NULL) 
	{
        pDbr = new AsdkDbReactor();
		gpAsdkAppDocGlobals->setDbReactor(pDbr);
        acdbHostApplicationServices()->workingDatabase()->addReactor(pDbr);
        acutPrintf(
            "  Added Database Reactor to "
            "acdbHostApplicationServices()->workingDatabase().\n");
	}
}


// Removes the database reactor
//
void
clearReactors()
{
	AsdkDbReactor *pDbr;
	if ((pDbr = gpAsdkAppDocGlobals->dbReactor()) != NULL)
	{
        acdbHostApplicationServices()->workingDatabase()->removeReactor(pDbr);
        delete pDbr;
        gpAsdkAppDocGlobals->setDbReactor(NULL);
    }
}

// Arx entry point function
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(appId);
		acrxRegisterAppMDIAware(appId);
		gpAsdkAppDocGlobals = new AsdkAppDocGlobals(curDoc());
		gpAsdkAppDocGlobals->setGlobals(curDoc());
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
		if (gpAsdkAppDocGlobals != NULL)
		{
			gpAsdkAppDocGlobals->unload();
			delete gpAsdkAppDocGlobals;
			gpAsdkAppDocGlobals = NULL;
		}
        acedRegCmds->removeGroup("ASDK_NOTIFY_TEST");
        break;
    }
    return AcRx::kRetOK;
}

// END CODE APPEARING IN SDK DOCUMENT.
