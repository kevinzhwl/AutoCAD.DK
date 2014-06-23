//
// (C) Copyright 1998-2008 by Autodesk, Inc. 
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
//
#include "StdAfx.h"
//
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


extern CSampDialog* gpDlg;
extern bool gbDisplayDialog;

#include "AdskDMgr.h"


class CDocInfo
{
public:
    CDocInfo();
    bool undoBtnAvailable;
    bool undoCmd;
};

CDocInfo::CDocInfo(){this->undoBtnAvailable=false; this->undoCmd=false;}

AsdkDataManager<CDocInfo> DocDataMgr; //MDI safe
#define docState DocDataMgr.docData()

//
//	Attach the database reactor if one isn't attached already.  
//	Then, start up the dialog.
//
//
void attachDbReactor(AcDbDatabase* pDb)
{
    if(gbDisplayDialog)
    {
        AcDbDatabase* pWkDb = acdbHostApplicationServices()->workingDatabase();
        assert(pWkDb == pDb);
        AcDbDatabase* pCurDb = curDoc()->database();
        assert(pCurDb == pDb);
        acDocManager->lockDocument(curDoc(), AcAp::kWrite);
    
        gpDbReactor = new CDbModReactor();
        pWkDb->addReactor(gpDbReactor);
        acutPrintf(_T("\nAttached CDbModReactor to the current database.\n"));     
        
        acDocManager->unlockDocument(curDoc());
        acedPostCommandPrompt();
    }
    else
        endDlg();
}
//
//
//	Detach the database reactor if the db is deactivated.  
//  Close the dialog if requested by the user.
//
//
void detachDbReactor(AcDbDatabase* pDb)
{
    acDocManager->lockDocument(curDoc(), AcAp::kWrite);
    if(gpDbReactor) 
    {
        pDb->removeReactor(gpDbReactor);
        delete gpDbReactor;
        gpDbReactor = NULL;
        acutPrintf(_T("\nDetached DbReactor from the current database.\n"));
    }
    acDocManager->unlockDocument(curDoc());

    acedPostCommandPrompt();
}
//
//	CDbModReactor overrides
//
//
//
void CDbModReactor::objectModified(const AcDbDatabase* pDb,
                                  const AcDbObject* pDbObj)
{
    AcAxDocLock docLock(pDbObj->ownerId(), AcAxDocLock::kNormal);	
    if(docLock.lockStatus() != Acad::eOk)
        return;
    else 
        objDisplay(_T("modified"), pDbObj);

}
//
//
//
void CDbModReactor::objectErased(const AcDbDatabase* pDb,
                                const AcDbObject* pDbObj,
                                Adesk::Boolean bErased)
{
    AcAxDocLock docLock(pDbObj->ownerId(), AcAxDocLock::kNormal);	
    if(docLock.lockStatus() != Acad::eOk)
        return;
    else
    {
        TCHAR buf[40];
        _stprintf_s(buf, _countof(buf), _T("%serased"), (bErased ? _T("") : _T("not ")));
        objDisplay(buf, pDbObj);
    }
}
//
// Update the content displayed in the modeless dialog.
//
void objDisplay(const TCHAR* pWhat, const AcDbObject* pDbObj)
{
    if(!gpDlg)
        return;
    TCHAR hstr[20];
    TCHAR idstr[20];
    const TCHAR *pClsName = NULL;
    if(pDbObj)
    {
        AcDbObjectId id = pDbObj->objectId();
        AcDbHandle h;
        pClsName = pDbObj->isA()->name();
    
        pDbObj->getAcDbHandle(h);
        h.getIntoAsciiBuffer(hstr);
    
        acutPrintf(_T("\nDbModReactor: obj %s: ")
            _T("class %s, id %lx, handle %s.\n"),
            pWhat, pClsName , id, hstr);
    
        _stprintf_s(idstr, _countof(idstr), _T("0x%08lx"), id);
    }
    else
    {
        pClsName = _T("");
        _tcscpy_s(hstr, _countof(hstr), _T(""));
        _tcscpy_s(idstr, _countof(idstr), _T(""));
    }

    gpDlg->SetDlgItemText(IDC_WHAT, pWhat);
    gpDlg->SetDlgItemText(IDC_EDIT_CLASS, pClsName);
    gpDlg->SetDlgItemText(IDC_EDIT_OBJID, idstr);
    gpDlg->SetDlgItemText(IDC_EDIT_HANDLE, hstr);

    //enable UNDO dialog button only if UNDO not already underway and
    //either an entity is being generated or modified.
    if (pDbObj && pDbObj->isKindOf(AcDbEntity::desc()) && !docState.undoCmd) 
        docState.undoBtnAvailable = TRUE;
    
}


void CEdReactor::commandWillStart(const TCHAR *cmd)
{
        if (!_tcscmp(cmd,_T("UNDO")))
            docState.undoCmd = TRUE;
}

void CEdReactor::commandEnded(const TCHAR *cmd)
{
    if (docState.undoBtnAvailable)
    {
        if ( gpDlg )
            gpDlg->m_undoBtn.EnableWindow(TRUE);
        //disable this button next command if no entity changes
        docState.undoBtnAvailable = FALSE; 
        
    }	
    else
    {
        if ( gpDlg )
            gpDlg->m_undoBtn.EnableWindow(FALSE);
    }
    
    if (docState.undoCmd)
        docState.undoCmd = FALSE; //undo is finished
}
/////////////////////////////////////////////////////////////////////////////////////
//
// document manager reactor
//
/////////////////////////////////////////////////////////////////////////////////////
//
//
//
void CDocReactor::documentActivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
    acutPrintf(_T("\ndocumentActiveated: %s.\n"), pDoc->fileName());
    acedPostCommandPrompt();
#endif
    attachDbReactor(pDoc->database());
}
//
// We need to attach the database reactor to the newly created
// database. We need to delete the previous database reactor as well.
//

void CDocReactor::documentCreated(AcApDocument* pDoc)
{
#ifndef NDEBUG
    acutPrintf(_T("\ndocumentCreated: %s.\n"), pDoc->fileName());
    acedPostCommandPrompt();
#endif
    if(gpDlg)
        objDisplay(_T(""), NULL);
}

//
// This deactivation includes a non-Acad window is activated 
// so the Acad window is losing focus.
//
void CDocReactor::documentToBeDeactivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
    acutPrintf(_T("\ndocumentToBeDeactiveated: %s."), pDoc->fileName());
    acedPostCommandPrompt();
#endif
    detachDbReactor(pDoc->database());
    if(gpDlg)
        objDisplay(_T(""), NULL);
}
//
// Obviously, we need to delete the database reactor associated
// with the destroyed doc.
//
void CDocReactor::documentToBeDestroyed(AcApDocument* pDoc)
{
#ifndef NDEBUG
    acutPrintf(_T("\ndocumentToBeDestroyed: %s.\n"), pDoc->fileName());
    acedPostCommandPrompt();
#endif
    detachDbReactor(pDoc->database());
    if(gpDlg)
        objDisplay(_T(""), NULL);
}
//
// This one can not be used because it gives the historically 
// to be activated document prior to the current action.
//
void CDocReactor::documentToBeActivated(AcApDocument* pDoc)
{
#ifndef NDEBUG
    acutPrintf(_T("\ndocumentToBeActivated: %s."), pDoc->fileName());
    acedPostCommandPrompt();
#endif
}


