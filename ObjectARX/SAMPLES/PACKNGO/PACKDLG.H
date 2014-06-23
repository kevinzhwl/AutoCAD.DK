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
//


// Send.h : main header file for the SEND DLL
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendApp
// See Send.cpp for the implementation of this class
//

class CSendApp : public CWinApp
{
public:
	CSendApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSendApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDepend dialog
// See send.cpp for implementation of this class
// This class holds all the UI components of the main dialog box 

class CDepend : public CDialog
{
private:
	CImageList				m_imageList;

	CToolBarCtrl			tbView;  // Buttons for view toggle
	CToolTipCtrl			ttView;  // Tool tips for the view toggle buttons
	TBBUTTON				*tbbView;  // Button structures

	BOOL					mCurrentView; // 0 list view 1 treeview

	static int				mColumnSpacing[];

	// Construction
public:
	CDepend(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDepend)
	enum { IDD = IDD_DEPEND_DLG };
	CTreeCtrl	m_DependTree;
	CListCtrl	m_DependList;
	CString	m_status;
	BOOL	m_subdir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDepend)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void	InitToggleButtons( int nButtons,int idToolbar,int idCommand,int idString,int idBitmap);
	void	OnListView();
	void	OnTreeView();

	void	PolulateList();
	void	PolulateTree();


	// Generated message map functions
	//{{AFX_MSG(CDepend)
		virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnCopy();
	virtual void OnCancel();
	afx_msg void OnReport();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnColumnclickDependlist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/* file types as follows
	m_type  Value   Filetype
			1		Xref
			2		Image
			3		Font
*/


////////////////////////////////////////////////////////////////////////  
/////
// CPrintBox window

class CPrintBox : public CEdit
{
// Construction
public:
	CPrintBox();

	void __cdecl Print(LPCTSTR pszFormat,...);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrintBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPrintBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CReports dialog

class CReports : public CDialog
{
// Construction
public:
	CReports(CWnd* pParent = NULL);   // standard constructor

	int m_nLines;


// Dialog Data
	//{{AFX_DATA(CReports)
	enum { IDD = IDD_REPORT };
	CPrintBox	m_reporttext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReports)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// void doCoolStatusText(CDC *pDC);

	// Generated message map functions
	//{{AFX_MSG(CReports)
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnReportprint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CSaveDwg dialog

class CSaveDwg : public CDialog
{
// Construction
public:
	CSaveDwg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveDwg)
	enum { IDD = IDD_SAVEDWG };
	CString	m_dwgname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveDwg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveDwg)
	afx_msg void OnYes();
	afx_msg void OnNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

