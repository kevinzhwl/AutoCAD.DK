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
// File Name: LaMfcToolbar.cpp

#include "stdafx.h"

#include <rxmfcapi.h>


/////////////////////////////////////////////////////////////////////////////
// LaMfcToolbar

LaMfcToolbar::LaMfcToolbar()
{
}

LaMfcToolbar::~LaMfcToolbar()
{
}


BEGIN_MESSAGE_MAP(LaMfcToolbar, CToolBar)
	//{{AFX_MSG_MAP(LaMfcToolbar)
	ON_COMMAND(ID_LADIA, OnLadia)
	ON_COMMAND(ID_LCA, OnLca)
	ON_COMMAND(ID_TITLE, OnTitle)
	ON_COMMAND(ID_ULCS, OnUlcs)
	ON_UPDATE_COMMAND_UI(ID_LADIA, OnUpdateLadia)
	ON_UPDATE_COMMAND_UI(ID_LCA, OnUpdateLca)
	ON_UPDATE_COMMAND_UI(ID_TITLE, OnUpdateTitle)
	ON_UPDATE_COMMAND_UI(ID_ULCS, OnUpdateUlcs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LaMfcToolbar message handlers

void LaMfcToolbar::OnLadia() 
{

}

void LaMfcToolbar::OnLca() 
{
}

void LaMfcToolbar::OnTitle() 
{
}

void LaMfcToolbar::OnUlcs() 
{
}

void LaMfcToolbar::OnUpdateLadia(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void LaMfcToolbar::OnUpdateLca(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theApp.isLoaded);
	pCmdUI->Enable(!theApp.isLoaded);
}

void LaMfcToolbar::OnUpdateTitle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(theApp.iniFile.showApp);
}

void LaMfcToolbar::OnUpdateUlcs(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!theApp.isLoaded);
	pCmdUI->Enable(theApp.isLoaded);
}

// End of LaMfcToolbar class implementation
//////////////////////////////////////////////////////////////////

void toolbarProc(WORD whichButton)
{
	CWinApp* pWinApp = acedGetAcadWinApp();
	CString cmdStr;

	switch(whichButton){
		case ID_LADIA:
		{
			cmdStr = "loadapp ";
			sendCommandToAutoCAD(cmdStr);
			break;
		}

		case ID_LCA:
			cmdStr = "lca ";
			sendCommandToAutoCAD(cmdStr);
			break;
		break;

		case ID_TITLE:
			showInTitle();
			break;
		break;

		case ID_ULCS:
			cmdStr = "ulca ";
			sendCommandToAutoCAD(cmdStr);
			break;
		break;
	}
	// Force AutoCAD Toolbar to be updated.
	// It's updated only when AutoCAD is on idle.
	pWinApp->OnIdle(0);
}

void createToolBar()
{
	// Set resource to our resource
	//AfxSetResourceHandle(_hdllInstance);

	theApp.pToolBar = new  LaMfcToolbar();

	if(!theApp.pToolBar){
		ads_alert("Impossible to create toolbar object.");
		return;
	}


	CMDIFrameWnd *pAcadFrame = acedGetAcadFrame();

	// Enable AutoCAD's mainframe for docking
	pAcadFrame->EnableDocking(CBRS_ALIGN_ANY);
	// need this step to force some MFC initialization
	pAcadFrame->RecalcLayout(); 

	BOOL s1 = theApp.pToolBar->Create(pAcadFrame, WS_CHILD | WS_VISIBLE |
											CBRS_SIZE_DYNAMIC  | CBRS_FLYBY |
											CBRS_TOP | CBRS_TOOLTIPS  );

	if(!s1){
		ads_alert("Impossible to create toolbar.");
		delete theApp.pToolBar;
		theApp.pToolBar = NULL;
		return;
	}


	BOOL s2 = theApp.pToolBar->LoadToolBar(IDR_LATOOLBAR);

	if(!s2){
		ads_alert("Impossible to load toolbar.");
		delete theApp.pToolBar;
		theApp.pToolBar = NULL;
		return;
	}

	// create toolbar handler
	theApp.pToolBarHandler = new CTBHandler();

	if(!theApp.pToolBarHandler){
		ads_alert("Impossible to create toolbar handler object.");
		delete theApp.pToolBar;
		theApp.pToolBar = NULL;
		return;
	}


	BOOL s3 = theApp.pToolBarHandler->Create(NULL, NULL, WS_CHILD|  WS_MINIMIZE , CRect(0,0,1,1), pAcadFrame, 10);

	if(!s3){
		ads_alert("Impossible to create toolbar handler.");
		delete theApp.pToolBarHandler;
		theApp.pToolBarHandler = NULL;
		delete theApp.pToolBar;
		theApp.pToolBar = NULL;
		return;
	}

	theApp.pToolBar->GetToolBarCtrl().SetOwner(theApp.pToolBarHandler);
/////////////////////////////////////////////////////////////////////////	
	theApp.pToolBar->EnableDocking(CBRS_ALIGN_ANY);
	theApp.pToolBar->SetWindowText(_T("LoadApp"));
	theApp.pToolBar->SetButtonStyle(0, TBBS_CHECKBOX);
	theApp.pToolBar->SetButtonStyle(1, TBBS_CHECKBOX);
	theApp.pToolBar->SetButtonStyle(2, TBBS_SEPARATOR);
	theApp.pToolBar->SetButtonStyle(3, TBBS_BUTTON);
	theApp.pToolBar->SetButtonStyle(4, TBBS_SEPARATOR);
	theApp.pToolBar->SetButtonStyle(5, TBBS_CHECKBOX);

	

	HKEY hLoadAppKey = NULL;
	hLoadAppKey = loadAppRegistry(KEY_READ);
	if(hLoadAppKey){
		HKEY hToolbarKey = NULL;
		if(RegOpenKeyEx(hLoadAppKey,
						"Toolbar",
						0,
						KEY_READ,
						&hToolbarKey) == ERROR_SUCCESS)
		{
			RegCloseKey(hToolbarKey);
			theApp.pToolBar->GetToolBarCtrl( ).RestoreState(hLoadAppKey, "Toolbar", "Settings");
			pAcadFrame->RecalcLayout();
			RegCloseKey(hLoadAppKey);

		}
		else
		{
			pAcadFrame->DockControlBar(theApp.pToolBar, AFX_IDW_DOCKBAR_BOTTOM);
		}


	}

	pAcadFrame->ShowControlBar(theApp.pToolBar, TRUE, TRUE);

}
