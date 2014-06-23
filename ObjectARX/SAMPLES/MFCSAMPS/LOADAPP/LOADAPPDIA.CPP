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
// File Name: loadAppDia.cpp
//
// DESCRIPTION:
//
// Our dialog box handler functions.

#include "stdafx.h"

#include <adslib.h>
#include "resourcehelper.h"


/////////////////////////////////////////////////////////////////////////////
// CLoadAppDia dialog


CLoadAppDia::CLoadAppDia(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadAppDia::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadAppDia)
	m_CBCurrApp = _T("");
	m_viewAll = FALSE;
	m_title = FALSE;
	m_DragDrop = FALSE;
	m_WatchLisp = FALSE;
	//}}AFX_DATA_INIT
}


void CLoadAppDia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadAppDia)
	DDX_Control(pDX, IDC_VIEWALL, m_ViewAllButton);
	DDX_Control(pDX, IDC_UNHIDE, m_unhide);
	DDX_Control(pDX, IDC_HIDE, m_hide);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_REMOVE, m_remove);
	DDX_Control(pDX, IDC_COMBO_CURRAPP, m_CBUsedApp);
	DDX_Control(pDX, IDC_LIST_LOADED_APP, m_loadedAppList);
	DDX_Control(pDX, IDBROWSE, m_browseButton);
	DDX_Control(pDX, IDUNLOAD, m_unloadButton);
	DDX_Control(pDX, IDLOAD, m_loadButton);
	DDX_CBString(pDX, IDC_COMBO_CURRAPP, m_CBCurrApp);
	DDV_MaxChars(pDX, m_CBCurrApp, 512);
	DDX_Check(pDX, IDC_VIEWALL, m_viewAll);
	DDX_Check(pDX, IDC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadAppDia, CDialog)
	//{{AFX_MSG_MAP(CLoadAppDia)
	ON_BN_CLICKED(IDUNLOAD, OnUnload)
	ON_BN_CLICKED(IDLOAD, OnLoad)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOADED_APP, OnDblclkListLoadedApp)
	ON_BN_CLICKED(IDBROWSE, OnBrowse)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LOADED_APP, OnClickListLoadedApp)
	ON_CBN_SETFOCUS(IDC_COMBO_CURRAPP, OnSetfocusComboCurrapp)
	ON_CBN_CLOSEUP(IDC_COMBO_CURRAPP, OnCloseupComboCurrapp)
	ON_BN_CLICKED(IDC_VIEWALL, OnViewall)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_LOADED_APP, OnRclickListLoadedApp)
	ON_CBN_EDITCHANGE(IDC_COMBO_CURRAPP, OnEditchangeComboCurrapp)
	ON_BN_CLICKED(IDC_TITLE, OnTitle)
	ON_BN_CLICKED(IDC_HIDE, OnHide)
	ON_BN_CLICKED(IDC_UNHIDE, OnUnhide)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLoadAppDia message handlers

// The user clicked the "Unload" button
void CLoadAppDia::OnUnload()
{
	// selection is a public data member of this class
	// used to store the full path name of the application
	// currently selected. See loadApp.h.
	
	if(selection.IsEmpty()){
		m_CBUsedApp.SetFocus();
		return;
	}
	
	// getExtension is defined in util.cpp.
	// It retrieves the extension (.arx, .exe or .lsp)
	// of the current selection.
	CString ext = getExtension(selection);
	
	// Prepare the error message in case
	// unload fails.
	CString message = "Unable to unload " + selection;

	// Unloading loadApp.arx is unloading an ARX application
	// from within itself, which obviously is a special case.
	// Basically, this can't be done without ads_queueexpr()
	// which will queue up Lisp expressions that will
	// be executed AFTER exiting the arx application.
	// Here, the Lisp expression is actually the one
	// unload loadApp.arx.
	// Please refer to the documentation for more details
	// about ads_queueexpr().
	if(isEqualApp(selection, "LOADAPP.ARX")){
		CString alertMessage = "You are about to unload loadApp.";
		alertMessage += "\nProceed anyway ?";
		int stat = MessageBox(alertMessage, "Alert", MB_OKCANCEL);
		if(stat == IDCANCEL) return;

		theApp.isInitialized = FALSE;
		message = "(arxunload \"" + selection + "\")";
		int length = message.GetLength();
		for(int i=0; i<length; i++)
			if(message[i] == '\\' )
				message.SetAt(i, '/');
		EndDialog(1);
		setTitle("");
		ads_queueexpr("(prompt \"\nunloading loadApp...\")");
		ads_queueexpr((char *)LPCTSTR(message));

		return;
	}

	// unloads arx applications
	if(ext == "ARX"){
		if(ads_arxunload(selection) != RTNORM){
			MessageBox( message, "Alert");
		}
	}

	// unload ads applications
	else if(ext == "EXE"){
		if(ads_xunload(selection) != RTNORM){
			MessageBox(message, "Alert");
		}
	}

	// in case of a Lisp application (extension .lsp),
	// the unload button is disabled, so the is not need
	// to handle this case here.
	// Any other case will tigger the following message.
	else{
		message = "Don't know how to unload " + selection;
		MessageBox(message, "Alert");
		m_CBUsedApp.SetFocus();
		return;
	}

	// refresh the list of loaded applications.
	getLoadedApp();

	// refresh the current selection
	UpdateData();
	selection = m_CBCurrApp;
	m_CBUsedApp.SetEditSel( 0, -1 );
	// update the state for all the buttons.
	setButtonState();

	m_OK.SetFocus();
	// update the title.
	setTitle();
}

// The user clicked the "Load" button
void CLoadAppDia::OnLoad() 
{

	if(selection.IsEmpty()){
		setButtonState();
		return;
	}

	CString path = getPath(selection);
	if(path == ""){
		char result[512];
		if(ads_findfile(selection, result) != RTNORM){
			CString errorString = "Cannot find " + selection;
			MessageBox( errorString, "Alert");
			m_CBUsedApp.SetFocus();
			return;
		}
		else{
			selection = result;
			m_CBCurrApp = selection;
		}
	}

	if(m_CBUsedApp.FindString( -1, selection) == CB_ERR){
		// this is not one of the used application
		// so make it one of them
		theApp.iniFile.setCurrApp(m_CBCurrApp);
		// this is for an eventual real-time
		// update of loadapp.ini
		m_CBUsedApp.ResetContent();
		for(int i=0; i<S_ARRAY_SIZE; i++){
			m_CBUsedApp.AddString(theApp.iniFile.usedApp[i]);
		}
		// select in the Edit Box the newly loaded application.
		m_CBUsedApp.SelectString( -1, theApp.iniFile.usedApp[0]);
		m_CBUsedApp.SetEditSel( 0, -1 );
	}

	if(theApp.isAppLoaded(selection)){
		// already loaded.
		setButtonState();
		return;
	}
	
	CString ext = getExtension(selection);

	// preparing message
	CString message = "Unable to load " + selection;

	if(ext == "ARX"){
		if(ads_arxload(selection) != RTNORM){
			MessageBox( message, "Alert");
		}
	}
	else if(ext == "EXE"){
		if(ads_xload(selection) != RTNORM){
			MessageBox( message, "Alert");
		}
	}
	else if(ext == "LSP"){
		// special setTitle function for Lisp
		// application since there is no easy way
		// to check if an application is loaded or not.
		setTitle();
		
		// Here again, the only way to load a Lisp
		// application from within an ARX application
		// is through ads_queueexpr().
		int length = selection.GetLength();
		for(int i=0; i<length; i++)
			if(selection[i] == '\\' )
				selection.SetAt(i, '/');
		message = "(load \"" + selection + "\")";
		CString prompt = "(prompt \"\nLoading " + selection + "\")";
		selection.Empty();
		EndDialog(1);

		ads_queueexpr((char *)LPCTSTR(prompt));
		ads_queueexpr((char *)LPCTSTR(message));
		return;
	}
	else{
		message = "Don't know how to load " + selection;
		message += ".\nPlease make sure extension is specified.";
		MessageBox(message, "Alert");
		m_CBUsedApp.SetFocus();
		return;
	}
	getLoadedApp();
	UpdateData();
	selection = m_CBCurrApp;
	m_CBUsedApp.SetEditSel( 0, -1 );
	setButtonState();
	m_OK.SetFocus();

	setTitle();
}


// The user clicked in the Loaded Applictions list box
void CLoadAppDia::OnClickListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_CBUsedApp.SetEditSel( -1, -1 );

	int item = m_loadedAppList.GetNextItem( -1, LVNI_SELECTED );

	if(item >= 0)
		selection = m_loadedAppList.GetItemText( item, 0 );
	else
		selection.Empty();
	setButtonState();
	*pResult = 0;
}


// The user double clicked in the Loaded Applictions list box.
// This triggers the OnUnload() member function.
void CLoadAppDia::OnDblclkListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int item = m_loadedAppList.GetNextItem( -1, LVNI_SELECTED );
	if(item >= 0){
		selection = m_loadedAppList.GetItemText( item, 0 );
		OnUnload();
	}
	*pResult = 0;
}

// The user clicked the "Browse" button.
// This triggers the CFileDialog common dialog.
void CLoadAppDia::OnBrowse() 
{
	
	// Check what is the current platform
	// to decide is the "explorer" style
	// should be use for the CFileDialog
	struct resbuf platf;
	ads_getvar("platform", &platf);
	DWORD flags = OFN_ENABLEHOOK | OFN_HIDEREADONLY;
	
	// Explorer style only if under NT 4.0 or 95.
	if(!strcmp(platf.resval.rstring, "Microsoft Windows NT Version 4.0 (x86)") ||
	   !strcmp(platf.resval.rstring, "Microsoft Windows Version 4.0 (x86)") )
		flags = flags | OFN_EXPLORER;

	free(platf.resval.rstring);

	// this is an "Open" dialog
	BOOL dialmode = TRUE;
	// the max path name size...
	char *buffer;
	buffer = new char [512];
	buffer[0] = '\0';

	// CFileDialog constructor.
	CFileDialog Fdlg(dialmode);

	Fdlg.m_ofn.nMaxFile = 512;
	Fdlg.m_ofn.lpstrFile = buffer;
	Fdlg.m_ofn.Flags = flags;
	Fdlg.m_ofn.hwndOwner = m_hWnd;

	
	// Set the file filter list.
	Fdlg.m_ofn.lpstrFilter =
	"ADS ARX LISP Applications (*.exe;*.arx;*.lsp)\0*.exe;*.arx;*.lsp\0ARX Applications (*.arx}\0 *.arx\0ADS Applications (*.exe)\0*.exe\0LISP Applications (*.lsp)\0*.lsp\0All Files (*.*)\0*.*\0";
	// default filter
	Fdlg.m_ofn.nFilterIndex = 1;

	// dialog box title
	Fdlg.m_ofn.lpstrTitle = "Select an ARX, ADS or Lisp application...";

	// initialize the initial directory if exists
	if(!theApp.iniFile.initDir.IsEmpty())
		Fdlg.m_ofn.lpstrInitialDir = theApp.iniFile.initDir;
	else
		Fdlg.m_ofn.lpstrInitialDir = NULL;

	int ret;
	// launch the dialog box
	ret = Fdlg.DoModal();


	if(ret == IDOK ){
		CString file = Fdlg.GetPathName();
		if(!file.IsEmpty()){
			// update the initial directory
			theApp.iniFile.initDir = getPath(file);
			theApp.iniFile.setCurrApp(file);
			m_CBUsedApp.ResetContent();
			for(int i=0; i<S_ARRAY_SIZE; i++){
				m_CBUsedApp.AddString(theApp.iniFile.usedApp[i]);
			}
			m_CBUsedApp.SelectString( -1, theApp.iniFile.usedApp[0]);
			m_CBUsedApp.SetEditSel( 0, -1 );
			OnSetfocusComboCurrapp();
			m_loadButton.SetFocus();
		}	
	}

	delete buffer;
}

void CLoadAppDia::getLoadedApp()
{
	
	theApp.getLoadedApp();
	BOOL stat = m_loadedAppList.DeleteAllItems();

	int i=0;
	POSITION pos;
		
	// pos is incremented automatically by GetNext
	for( pos = theApp.loadedApp.GetHeadPosition(); pos != NULL; ){
		m_loadedAppList.InsertItem( i, theApp.loadedApp.GetNext(pos));	
		i++;
	}
}



BOOL CLoadAppDia::OnInitDialog() 
{
	if( !CDialog::OnInitDialog())
		return FALSE;

	getLoadedApp();
	m_CBUsedApp.ResetContent();

	for(int i=0; i<S_ARRAY_SIZE; i++){
		m_CBUsedApp.AddString(theApp.iniFile.usedApp[i]);
	}
	m_CBUsedApp.SelectString( -1, theApp.iniFile.usedApp[0]);
	m_CBUsedApp.SetEditSel( 0, -1 );
	OnSetfocusComboCurrapp();
	setButtonState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CLoadAppDia::OnSetfocusComboCurrapp() 
{

	UpdateData();
	selection = m_CBCurrApp;
	theApp.iniFile.initDir = getPath(selection);
	theApp.iniFile.setCurrApp(selection);
	setButtonState();
}

void CLoadAppDia::OnCloseupComboCurrapp() 
{
	int index = m_CBUsedApp.GetCurSel();
	if(index < 0){
		OnSetfocusComboCurrapp();
		return;
	}
	m_CBUsedApp.GetLBText( index, selection );
	theApp.iniFile.initDir = getPath(selection);
	theApp.iniFile.setCurrApp(selection);
	setButtonState();
}


void CLoadAppDia::OnViewall() 
{
	if(m_viewAll == TRUE){
		theApp.iniFile.viewAll = FALSE;
		m_viewAll = FALSE;
	}
	else{
		theApp.iniFile.viewAll = TRUE;
		m_viewAll = TRUE;
	}
	getLoadedApp();
	m_loadedAppList.SetFocus();
}

void CLoadAppDia::OnRemove() 
{
	int i;
	for(i=0; i<S_ARRAY_SIZE-1; i++)
		theApp.iniFile.usedApp[i] = theApp.iniFile.usedApp[i+1];
	setTitle(theApp.iniFile.usedApp[0]);
	theApp.iniFile.usedApp[S_ARRAY_SIZE-1] = "";
	m_CBUsedApp.ResetContent();
	for(i=0; i<S_ARRAY_SIZE; i++){
		m_CBUsedApp.AddString(theApp.iniFile.usedApp[i]);
	}
	m_CBUsedApp.SelectString( -1, theApp.iniFile.usedApp[0]);
	m_CBUsedApp.SetEditSel( 0, -1 );
	OnSetfocusComboCurrapp();
	m_remove.SetFocus();
}

void CLoadAppDia::OnRclickListLoadedApp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int item = m_loadedAppList.GetNextItem( -1, LVNI_SELECTED );

	if(item < 0){
		*pResult = 0;
		selection.Empty();
		setButtonState();
		return;
	}
	selection = m_loadedAppList.GetItemText( item, 0 );
	theApp.iniFile.setCurrApp(selection);
	m_CBUsedApp.ResetContent();
	for(int i=0; i<S_ARRAY_SIZE; i++){
		m_CBUsedApp.AddString(theApp.iniFile.usedApp[i]);
	}
	m_CBUsedApp.SelectString( -1, theApp.iniFile.usedApp[0]);
	m_CBUsedApp.SetEditSel( 0, -1 );
	setButtonState();
	OnSetfocusComboCurrapp();
	
	*pResult = 0;
}


void CLoadAppDia::OnEditchangeComboCurrapp() 
{
	UpdateData();
	selection = m_CBCurrApp;
	setButtonState();
}


void CLoadAppDia::setButtonState(){
	if(selection.IsEmpty()){
		m_loadButton.EnableWindow(FALSE);
		m_unloadButton.EnableWindow(FALSE);
		m_remove.EnableWindow(FALSE);
		m_hide.EnableWindow(FALSE);
		m_unhide.EnableWindow(FALSE);
		m_browseButton.SetFocus();
		return;
	}

	if(m_CBUsedApp.FindStringExact(-1, selection) == CB_ERR)
		// the current app is not one of the used app
		m_remove.EnableWindow(FALSE);
	else
		m_remove.EnableWindow();


	LV_FINDINFO linfo;
	linfo.flags = LVFI_STRING;

	CString appname = getFileName(selection);
	CString ext = getExtension(selection);
	if(ext == "ARX")
		linfo.psz = LPCTSTR(appname);
	else
		linfo.psz = LPCTSTR(selection);

	if(m_loadedAppList.FindItem(&linfo) < 0){
		// the current app is not one of the app loaded
		m_loadButton.EnableWindow();
		m_unloadButton.EnableWindow(FALSE);
		theApp.isLoaded = FALSE;
	}
	else{
		// the current app is already loaded
		m_unloadButton.EnableWindow();
		m_loadButton.EnableWindow(FALSE);
		theApp.isLoaded = TRUE;
	}

	if(theApp.iniFile.hiddenApp.Find(appname)){
		m_hide.EnableWindow(FALSE);
		m_loadButton.EnableWindow(FALSE);
		m_unhide.EnableWindow();
	}
	else{
		m_hide.EnableWindow();
		m_unhide.EnableWindow(FALSE);
	}
}


void CLoadAppDia::OnTitle() 
{
	if(m_title == TRUE){
		m_title = FALSE;
		setTitle("");
		theApp.iniFile.showApp = FALSE;
	}
	else{
		theApp.iniFile.showApp = TRUE;
		m_title = TRUE;
		setTitle();
	}
}

void CLoadAppDia::OnHide() 
{
	if(selection.IsEmpty())
		return;

	CString appname  = getFileName(selection);
	if(theApp.iniFile.hiddenApp.Find(appname))
		return;
	theApp.iniFile.hiddenApp.AddTail(appname);
	if(m_viewAll == TRUE){
		theApp.iniFile.viewAll = FALSE;
		m_viewAll = FALSE;
		m_ViewAllButton.SetCheck(0);
	}
	getLoadedApp();
	/////////////////
	UpdateData();
	selection = m_CBCurrApp;
	m_CBUsedApp.SetEditSel( 0, -1 );
	setButtonState();
}

void CLoadAppDia::OnUnhide() 
{
	if(selection.IsEmpty())
		return;
	CString appname  = getFileName(selection);
	POSITION pos;
	if((pos = theApp.iniFile.hiddenApp.Find(appname)) == NULL)
		return;
	theApp.iniFile.hiddenApp.RemoveAt(pos);
	getLoadedApp();
	UpdateData();
	selection = m_CBCurrApp;
	m_CBUsedApp.SetEditSel( 0, -1 );
	setButtonState();
}

// end of CLoadAppDia implementation
////////////////////////////////////////////////////////////////////////////////

// initialize and load the loadApp dialog.
void InitDialog()
{
	CWnd * AcadW = CWnd::FromHandle(theApp.hWndACAD);

	CTemporaryResourceOverride thisResource;
	CLoadAppDia loadAppDia(AcadW);
	if(theApp.iniFile.viewAll)
		loadAppDia.m_viewAll = TRUE;
	else
		loadAppDia.m_viewAll = FALSE;

	if(theApp.iniFile.showApp)
		loadAppDia.m_title = TRUE;
	else
		loadAppDia.m_title = FALSE;

	if(theApp.iniFile.watchLisp)
		loadAppDia.m_WatchLisp = TRUE;
	else
		loadAppDia.m_WatchLisp = FALSE;

	if(theApp.iniFile.watchDragDrop)
		loadAppDia.m_DragDrop = TRUE;
	else
		loadAppDia.m_DragDrop = FALSE;

	if(loadAppDia.DoModal() == IDOK){
		// check lisp loads
		if(theApp.iniFile.watchLisp)
			theApp.addLispReactor();
		else
			theApp.removeLispReactor();
		// check drag'n drop loads

		// Save settings
		theApp.iniFile.iniSave();
	}
}

