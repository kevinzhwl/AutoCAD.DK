// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// clonreac.cpp
//
// Wblock Modification Sample Code
//
// This code demonstrates how to add additional objects during
// beginDeepCloneXlation().  

#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include "rxregsvc.h"
#include "aced.h"
#include "dbidmap.h"
#include "dbsymtb.h"
#include "adscodes.h"
#include "tchar.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

// Function prototypes
//
void modifyWblock();
void clearReactor();
static Adesk::Boolean getYorN(const TCHAR* pStr);
extern "C" AcRx::AppRetCode
    acrxEntryPoint(AcRx::AppMsgCode, void*);

// Forward class declarations
//
class AsdkEdReactor;

// Globals
//
AsdkEdReactor *gpEdr = NULL;   // pointer to editor reactor


class AsdkEdReactor : public AcEditorReactor
//
// Custom AcEditorReactor class for Wblock Clone event
// notification
{
public:
    virtual void beginDeepCloneXlation(AcDbIdMapping& idMap,
        Acad::ErrorStatus* es);
};

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

//  Since AcDbDatabase::wblock() only supports AcDbEntities
//  in its Array of Ids, this code demonstrates how to add
//  additional objects during beginDeepCloneXlation().  If
//  it is a WBLOCK command, it asks the user if all Text
//  Styles should be Wblocked.  Otherwise, only those text
//  styles which are referenced by entities being Wblocked
//  will be included (Wblock's default behavior).

// AsdkEdReactor is derived from AcEditorReactor
//
void
AsdkEdReactor::beginDeepCloneXlation(AcDbIdMapping& idMap,
    Acad::ErrorStatus* es)
{
    if (idMap.deepCloneContext() == AcDb::kDcWblock
        && getYorN(_T("Wblock all Text Styles")))
    {
        AcDbDatabase *pOrigDb, *pDestDb;
        if (idMap.origDb(pOrigDb) != Acad::eOk)
            return;
        *es = idMap.destDb(pDestDb);
        if (*es != Acad::eOk)
            return;

        AcDbTextStyleTable *pTsTable;
        *es = pOrigDb->getSymbolTable(pTsTable,
            AcDb::kForRead);
        if (*es != Acad::eOk)
            return;

        AcDbTextStyleTableIterator *pTsIter;
        *es = pTsTable->newIterator(pTsIter);
        if (*es != Acad::eOk) {
            pTsTable->close();
            return;
        }
        AcDbTextStyleTableRecord *pTsRecord;
        AcDbObject *pClonedObj;
        for (; !pTsIter->done(); pTsIter->step()) {
            *es = pTsIter->getRecord(pTsRecord,
                AcDb::kForRead);
            if (*es != Acad::eOk) {
                delete pTsIter;
                pTsTable->close();
                return;
            }
            // We don't need to check for already cloned
            // Records.  If the Text Style is already
            // cloned, wblockClone will return Acad::eOk
            // and pCloneObj will be NULL.
            //
            pClonedObj = NULL;
            *es = pTsRecord->wblockClone(pDestDb,
                pClonedObj, idMap, Adesk::kFalse);
            if (*es != Acad::eOk) {
                pTsRecord->close();
                delete pTsIter;
                pTsTable->close();
                return;
            }
            *es = pTsRecord->close();
            if (*es != Acad::eOk) {
                delete pTsIter;
                pTsTable->close();
                return;
            }
            if (pClonedObj != NULL) {
                *es = pClonedObj->close();
                if (*es != Acad::eOk) {
                    delete pTsIter;
                    pTsTable->close();
                    return;
                }
            }
        }
        delete pTsIter;
        *es = pTsTable->close();
    }
}

// END CODE APPEARING IN SDK DOCUMENT.

// Adds the reactor to the editor to monitor changes.
//
void
modifyWblock()
{
    acedEditor->addReactor(gpEdr);
    acutPrintf(_T("Added new command to Wblock.\n"));
}


// Removes the editor reactor
//
void
clearReactor()
{
    acedEditor->removeReactor(gpEdr);
}


// Queries the user for Yes/No answer
//
static Adesk::Boolean
getYorN(const TCHAR* pStr)
{
    TCHAR yorn_str[132];

    // specific prompt.
    //
    acutPrintf(_T("\n%s"), pStr);

    acedInitGet(0, _T("No Yes"));

    yorn_str[0] = _T('Y');
    yorn_str[1] = _T('\0');

    switch (acedGetString(Adesk::kFalse, _T(" -- No/<Yes>:  "),
        yorn_str))
    {
    case RTKWORD:
        acedGetInput(yorn_str);
        /* Deliberate fallthrough */
    default:
        break;
    }

    return (!((yorn_str[0] == _T('N'))
        || (yorn_str[0] == _T('n'))));
}

// Arx entry point function
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        gpEdr = new AsdkEdReactor();
        acedRegCmds->addCommand(_T("ASDK_NOTIFY_TEST"),
            _T("ASDK_WATCH"),
            _T("MODWBLOCK"),
            ACRX_CMD_TRANSPARENT,
            modifyWblock);
        break;
    case AcRx::kUnloadAppMsg:
        clearReactor();
        acedRegCmds->removeGroup(_T("ASDK_NOTIFY_TEST"));
        delete gpEdr;
    }
    return AcRx::kRetOK;
}
