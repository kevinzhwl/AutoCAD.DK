//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1988-1999 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiDialog_h
#define _aduiDialog_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiDialog : public CAdUiBaseDialog {
    DECLARE_DYNAMIC(CAdUiDialog);

public:
                CAdUiDialog (
                    UINT idd,
                    CWnd *pParent=NULL,
                    HINSTANCE hDialogResource=NULL
                );
virtual         ~CAdUiDialog ();

// Misc.
protected:
virtual void    OnInitDialogBegin ();
virtual void    OnInitDialogFinish ();

// Elasticity
private:
        LPVOID  m_pElastic;

        CString m_dlgHelpTag;       // The help string tag for this dialog.
        
protected:
        BOOL    m_bEnableElasticMessageMap; // INTERNAL USE ONLY
        UINT    m_templateid;               // INTERNAL USE ONLY

public:
        BOOL    AddControl (CWnd *pControl);
        BOOL    AutoLoadControl (CWnd *pControl);
        BOOL    ForceControlRepaint (CWnd *pControl, BOOL bForce);
        BOOL    ForceControlResize (CWnd *pControl, LPRECT prect);
        BOOL    GetColumnSizes (CListCtrl *pList);
        CSize   *GetCurrentDelta ();
        BOOL    GetDialogData (LPCTSTR valueName, CString& data);
        BOOL    GetDialogData (LPCTSTR valueName, DWORD& data);
        BOOL    GetDialogKey (CString& key);
        BOOL    GetDialogName (CString& name);
        void    GetDialogHelpTag (CString& tag);        
        void    GetElasticMinMaxInfo (MINMAXINFO& mmi);
        LPVOID  GetElasticPointer ();
        BOOL    GetPixelData (CRect& r);
        void    LockDialogHeight ();
        void    LockDialogWidth ();
        BOOL    MoveControlX (UINT id, LONG lMovePct);
        BOOL    MoveControlXY (UINT id, LONG lMoveXPct, LONG lMoveYPct);
        BOOL    MoveControlY (UINT id, LONG lMovePct);
        BOOL    ReloadControl (CWnd *pControl, LPCTSTR lpResString);
        BOOL    RemoveControl (CWnd *pControl);
        BOOL    SaveColumnSizes (CListCtrl *pList);
        BOOL    SetControlProperty (PDLGCTLINFO lp, DWORD numElements);
        BOOL    SetDialogData (LPCTSTR valueName, LPCTSTR data);
        BOOL    SetDialogData (LPCTSTR valueName, DWORD data);
        void    SetDialogMaxExtents (int width, int height);
        void    SetDialogMinExtents (int width, int height);
        void    SetDialogName (LPCTSTR name);
        void    SetDialogHelpTag (LPCTSTR tag);        
        void    SetElasticSize (CSize& size, BOOL bRefreshDialog);
        void    SetPersistency (BOOL bFlag);
        void    SetRootKey (LPCTSTR key);
        void    SetTabSize (LPARAM lParam, BOOL bRefreshDialog);
        BOOL    StorePixelData ();
        BOOL    StretchControlX (UINT id, LONG lStretchPct);
        BOOL    StretchControlXY (UINT id, LONG lStretchXPct, LONG lStretchYPct);
        BOOL    StretchControlY (UINT id, LONG lStretchPct);

        // ClassWizard-controlled
public:
    //{{AFX_DATA(CAdUiDialog)
    enum { IDD = 0 };
    //}}AFX_DATA

    //{{AFX_VIRTUAL(CAdUiDialog)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
    virtual void OnDialogHelp();    // Override this to provide dialog help.
    virtual BOOL DoDialogHelp();                        // INTERNAL USE ONLY
            
protected:
    //{{AFX_MSG(CAdUiDialog)
    afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);    // INTERNAL USE ONLY
    virtual void OnOK();                                    // INTERNAL USE ONLY
    afx_msg void OnSize(UINT nType, int cx, int cy);        // INTERNAL USE ONLY
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
