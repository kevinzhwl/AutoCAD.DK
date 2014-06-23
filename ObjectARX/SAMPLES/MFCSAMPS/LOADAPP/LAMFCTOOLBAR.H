// (C) Copyright 1993-1997 by Autodesk, Inc.
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
// File Name: laMfcToolbar.h
//

#ifndef __LA_TOOLBAR_H_
#define __LA_TOOLBAR_H_

// LaMfcToolbar.h : header file
//

class LaMfcToolbar : public CToolBar
{
// Construction
public:
	LaMfcToolbar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LaMfcToolbar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~LaMfcToolbar();

	// Generated message map functions
protected:
	//{{AFX_MSG(LaMfcToolbar)
	afx_msg void OnLadia();
	afx_msg void OnLca();
	afx_msg void OnTitle();
	afx_msg void OnUlcs();
	afx_msg void OnUpdateLadia(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLca(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTitle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUlcs(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


void toolbarProc(WORD whichButton);
void createToolBar();

/////////////////////////////////////////////////////////////////////////////
#endif
