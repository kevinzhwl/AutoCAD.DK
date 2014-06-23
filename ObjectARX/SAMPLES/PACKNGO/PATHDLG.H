//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1993-1996 by Autodesk, Inc. 
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
// Name:        PATHDLG - Defines a class derived from CFileDialog that 
//                        allows the user to select only a directory.
//
//////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

// pathdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog

#ifndef __PATHDLG_H
#define __PATHDLG_H

class CPathDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CPathDialog)

public:
	CString GetSelectedPath();
	CPathDialog(CWnd* pParentWnd);
    virtual int DoModal();
protected:
	BOOL m_bDlgJustCameUp;
    CString m_selectedPath;
	//{{AFX_MSG(CPathDialog)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    static BOOL m_bNewShell;
    static BOOL m_bInitialized;
    CWnd* m_mParentWnd;
};
#endif // __PATHDLG_H
