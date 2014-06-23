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
// File Name: loadAppDia.h
//
// DESCRIPTION:
//
// Defines our dialog box class.

#ifndef _LOADAPPDIA_H
#define _LOADAPPDIA_H


#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CLoadAppDia dialog

class CLoadAppDia : public CDialog
{
public:
	CLoadAppDia(CWnd* pParent = NULL);
	CString selection;

	void getLoadedApp();
	void setButtonState();

	// Dialog Data
	//{{AFX_DATA(CLoadAppDia)
	enum { IDD = IDD_LOADAPP };
	CButton	m_WatchLispCheck;
	CButton	m_DragDropCheck;
	CButton	m_ViewAllButton;
	CButton	m_unhide;
	CButton	m_hide;
	CButton	m_Cancel;
	CButton	m_OK;
	CButton	m_remove;
	CComboBox	m_CBUsedApp;
	CListCtrl	m_loadedAppList;
	CButton	m_browseButton;
	CButton	m_unloadButton;
	CButton	m_loadButton;
	CString	m_CBCurrApp;
	BOOL	m_viewAll;
	BOOL	m_title;
	BOOL	m_DragDrop;
	BOOL	m_WatchLisp;
	//}}AFX_DATA


protected:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadAppDia)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLoadAppDia)
	afx_msg void OnUnload();
	afx_msg void OnLoad();
	afx_msg void OnDblclkListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusComboCurrapp();
	afx_msg void OnCloseupComboCurrapp();
	afx_msg void OnViewall();
	afx_msg void OnRemove();
	afx_msg void OnRclickListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditchangeComboCurrapp();
	afx_msg void OnTitle();
	afx_msg void OnHide();
	afx_msg void OnUnhide();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif
