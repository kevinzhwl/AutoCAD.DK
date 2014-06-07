// (C) Copyright 1990-2002 by Autodesk, Inc. 
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

#include "StdAfx.h"
#include "FileNavDlg.h"
#include "resource.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_FILENAME_COMBO         13006

//I have assigned following the IDS to the user defined menu items.
#define ID_TOOL_TEST_MENU			1021
#define ID_OK_TEST_MENU				1022
#define ID_VIEW_TEST_MENU			1023

// How do i get the resource id ? : Open anavRes.dll in VC7 with File-->OPEN in resource mode.
//and click on the dialog id with 131 and click on file Name combo

IMPLEMENT_DYNAMIC(CFileNavDlg, CAcUiNavDialog);

CFileNavDlg::CFileNavDlg(CNavDataArray& dataArray, 
				   CNavFilterArray& filterArray, 
				   UINT idd, 
				   CWnd *pParent,
				   HINSTANCE hDialogResource)
				:  CAcUiNavDialog(dataArray, filterArray)
{
    //{{AFX_DATA_INIT(CFileNavDlg)
    //}}AFX_DATA_INIT

    // Set an application name to enable persistency and resizing.
    SetAppRootKey("FILENAVROOT");
    SetDialogName("FILENAVDIALOG");
    SetPersistency(TRUE);

}

void CFileNavDlg::DoDataExchange (CDataExchange *pDX)
{
    CAcUiNavDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFileNavDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileNavDlg, CAcUiNavDialog)
    //{{AFX_MSG_MAP(CFileNavDlg)
	ON_COMMAND(ID_TOOL_TEST_MENU, OnToolsTestMenu)
	ON_COMMAND(ID_VIEW_TEST_MENU, OnViewTestMenu)
	ON_COMMAND(ID_OK_TEST_MENU,OnOkTestMenu)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CFileNavDlg::GetRecentDirectory(CString& strRecent)
{
	TCHAR lpszPath[MAX_PATH];
	LPITEMIDLIST pidl;
	SHGetSpecialFolderLocation(m_hWnd, CSIDL_RECENT, &pidl);
	SHGetPathFromIDList(pidl, lpszPath);
	strRecent = lpszPath;

	return TRUE;
}

BOOL CFileNavDlg::FindInSearchPath(LPCTSTR sBase, CString* pFullPath)
{
	return TRUE;
}

void CFileNavDlg::GetDefaultBrowserStartURL(CString& strStartPage)
{
	strStartPage = "www.autodesk.com";
}

BOOL CFileNavDlg::GetProductName(CString& strProduct)
{
	return strProduct = "ArxFileNavTest", TRUE;
}

BOOL CFileNavDlg::BeginDownloadFiles(CStringArray& strURLs, CDWordArray& dwActionCodes)
{
	for(int j = 0; j < strURLs.GetSize(); j++)
	{
		TRACE("%s\n", strURLs[j]);
	}
	return CAcUiNavDialog::BeginDownloadFiles(strURLs, dwActionCodes);
}

BOOL CFileNavDlg::OnInitDialog() 
{
	SetToolsMenuItemsPresent(true);
	CAcUiNavDialog::OnInitDialog();
	return TRUE;
}

void CFileNavDlg::OnFolderItemChange()
{
	CAcUiNavDialog::OnFolderItemChange();
}

void CFileNavDlg::OnFilterChange()
{
	CAcUiNavDialog::OnFilterChange();
}

// Called when the file (or path) is selected
BOOL CFileNavDlg::OnFileNameOK()
{
	return CAcUiNavDialog::OnFileNameOK();
}

// Called when user enters/modifies a file name in file name combo box
void CFileNavDlg::OnFileNameChange()
{
	CAcUiNavDialog::OnFileNameChange();
}

// One can add the menu labels from string table instead hard coding.

// Adds one more user defined menu to 'OK' button Popup Menu
void CFileNavDlg::PrepareOkMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
	bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_OK_TEST_MENU,"OK:Test Menu'");
}

// Adds one more user defined menu to 'View' Popup Menu
void CFileNavDlg::PrepareViewsMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
	bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_VIEW_TEST_MENU,"View:Test Menu'");
}

// Adds one more user defined menu to 'Tools' Popup Menu
void CFileNavDlg::PrepareToolsMenu(CMenu* pMenu)
{
	BOOL bRet = pMenu->AppendMenu(MF_SEPARATOR);
	bRet = pMenu->InsertMenu(6,MF_BYPOSITION,ID_TOOL_TEST_MENU ,"Tools:Test Menu");
}

BOOL CFileNavDlg::PreTranslateMessage(MSG* pMsg)
{
	return CAdUiDialog::PreTranslateMessage(pMsg);
}

void CFileNavDlg::OnURLDownloadSuccess(CString& strURL)
{
	TRACE("%s\n", strURL);
}

void CFileNavDlg::OnToolsTestMenu() 
{
	AfxMessageBox ("You have slected the 'Tools:Test Menu'");
}

void CFileNavDlg::OnViewTestMenu()
{
	AfxMessageBox ("You have slected the 'View:Test Menu'");
}

void CFileNavDlg::OnOkTestMenu()
{
	AfxMessageBox ("You have slected the 'OK:Test Menu'");
}