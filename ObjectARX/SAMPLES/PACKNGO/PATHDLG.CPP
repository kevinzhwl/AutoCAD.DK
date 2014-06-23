//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1997 by Autodesk, Inc. 
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
//
// Name:        PATHDLG - Implements the CPathDialog class which is derived 
//                        from CFileDialog. The class allows the user to only 
//                        select directories. 
//
// Remarks:     None
//
//////////////////////////////////////////////////////////////////////////////


// pathdlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "shlobj.h"

#include "pathdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL CPathDialog::m_bNewShell = FALSE;
BOOL CPathDialog::m_bInitialized = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CPathDialog

IMPLEMENT_DYNAMIC(CPathDialog, CFileDialog)

CPathDialog::CPathDialog(CWnd* pParentWnd) :
        CFileDialog(FALSE, NULL, NULL, OFN_SHOWHELP | OFN_HIDEREADONLY | 
                    OFN_OVERWRITEPROMPT | OFN_ENABLETEMPLATE | OFN_NOCHANGEDIR, 
                    NULL, pParentWnd)
{
    m_ofn.hInstance = AfxGetResourceHandle();
    m_ofn.lpTemplateName = /*MSG0*/"DIRSELECT";
    m_ofn.Flags &= ~OFN_EXPLORER;
    m_mParentWnd = pParentWnd;

    if (!m_bInitialized) {
        OSVERSIONINFO   osvers;          // all about Windows

        osvers.dwOSVersionInfoSize = sizeof(osvers);
        if (GetVersionEx(&osvers)) {

            // m_bNewShell is true if we're running under WIN 95
            // or under NT 4.x
            //
            m_bNewShell = (osvers.dwMajorVersion >= 4);
        }
        m_bInitialized = TRUE;        
    }
}

BEGIN_MESSAGE_MAP(CPathDialog, CFileDialog)
	//{{AFX_MSG_MAP(CPathDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPathDialog::OnPaint() 
{
    CPaintDC dc(this); // device context for painting


    // This code makes the directory listbox "highlight" an entry when it first
    // comes up.  W/O this code, the focus is on the directory listbox, but no
    // focus rectangle is drawn and no entries are selected.  Ho hum.

    if (m_bDlgJustCameUp) {
        m_bDlgJustCameUp = FALSE;
        SendDlgItemMessage(lst2, LB_SETCURSEL, 0, 0L);
    }
}

BOOL CPathDialog::OnInitDialog() 
{
    CenterWindow();

    // Let's hide these windows so the user cannot tab to them.  Note that in
    // the private template (in cddemo.dlg) the coordinates for these guys are
    // *outside* the coordinates of the dlg window itself.  Without the following
    // ShowWindow()'s you would not see them, but could still tab to them.
    
    GetDlgItem(stc2)->ShowWindow(SW_HIDE);
    GetDlgItem(stc3)->ShowWindow(SW_HIDE);
    GetDlgItem(edt1)->ShowWindow(SW_HIDE);
    GetDlgItem(lst1)->ShowWindow(SW_HIDE);
    GetDlgItem(cmb1)->ShowWindow(SW_HIDE);
    GetDlgItem(psh15)->ShowWindow(SW_HIDE);


    // We must put something in this field, even though it is hidden.  This is
    // because if this field is empty, or has something like "*.txt" in it,
    // and the user hits OK, the dlg will NOT close.  We'll jam something in
    // there (like "Junk") so when the user hits OK, the dlg terminates.
    // Note that we'll deal with the "Junk" during return processing (see below)

    SetDlgItemText(edt1, /*MSG0*/"Junk");

    // Now set the focus to the directories listbox.  Due to some painting
    // problems, we *must* also process the first WM_PAINT that comes through
    // and set the current selection at that point.  Setting the selection
    // here will NOT work.  See comment below in the on paint handler.
            
    GetDlgItem(lst2)->SetFocus();
            
    m_bDlgJustCameUp = TRUE;
             
    CFileDialog::OnInitDialog();
   
    return FALSE;

}

CString CPathDialog::GetSelectedPath()
{
    if (!m_bNewShell) {
        WORD wFileOffset;
    
        wFileOffset = m_ofn.nFileOffset;
        // Get rid of the "Junk" placed in the edit control during
        // OnInitDialog()
        //
        m_ofn.lpstrFile[wFileOffset - 1] = 0;
        m_selectedPath.Format(/*MSG0*/"%s", m_ofn.lpstrFile);
    }
    return m_selectedPath;
}

int CPathDialog::DoModal()
{
    if (!m_bNewShell) {
        return CFileDialog::DoModal();
    }

    LPMALLOC pMalloc;
    int returnValue = IDCANCEL;

    /* Gets the Shell's default allocator */
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
        // Get help on BROWSEINFO struct - it's got all the bit settings.
        bi.hwndOwner = m_pParentWnd ? m_pParentWnd->GetSafeHwnd() : GetSafeHwnd();
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;
        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
            // At this point pszBuffer contains the selected path */.
                m_selectedPath = pszBuffer;
                returnValue = IDOK;
            }
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }

    return returnValue;
}
