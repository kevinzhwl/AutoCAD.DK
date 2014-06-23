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
// File Name: loadApp.cpp
//
// DESCRIPTION:
//
// Defines the CLoadApp class (our WinApp object).
// Defines the functions called by our ARX commands.

#include "stdafx.h"

#include <adslib.h>
#include <ads.h>
#include <dbmain.h>
#include <rxmfcapi.h>


CLoadApp::CLoadApp(){

	hWndACAD = adsw_acadMainWnd();

	isInitialized = FALSE;

	pLispReactor = NULL;

	char fpath[512];
	// find acad.exe directory.
	// ads_findfile can't fail to find it.
	ads_findfile("acad.exe", fpath);
	// get the path only
	int fpSize = strlen(fpath) - 8;
	// copy the path
	for(int i=0; i<fpSize; i++)
		theApp.iniFile.fileName += fpath[i];
	// add the file name
	iniFile.fileName += "loadapp.ini";
	iniFile.iniRead();
	setTitle(iniFile.usedApp[0]);

	if(iniFile.watchLisp)
		addLispReactor();

	watchDragDrop();


	isLoaded = FALSE;

	pToolBarHandler = NULL;
	pToolBar = NULL;

}

void
CLoadApp::watchDragDrop()
{
	acedRegisterFilterWinMsg(FilterOnDrop);
}

void
CLoadApp::unWatchDragDrop()
{
	acedRemoveFilterWinMsg(FilterOnDrop);
}


void
CLoadApp::addLispReactor()
{
	if(!pLispReactor){
		pLispReactor = new CLispReactor;
		acedEditor->addReactor(pLispReactor);
	}
}

void
CLoadApp::removeLispReactor()
{
	if(pLispReactor){
		acedEditor->removeReactor(pLispReactor);
		delete pLispReactor;
		pLispReactor = NULL;
	}
}

CLoadApp::~CLoadApp()
{
	loadedApp.RemoveAll();

	removeLispReactor();
	unWatchDragDrop();


	if(pToolBarHandler != NULL)
			delete pToolBarHandler;
	
	if(pToolBar != NULL)
		delete pToolBar;

	if(acdbCurDwg()){
		CMDIFrameWnd *pAcadFrame = acedGetAcadFrame();
		// need this step to force some MFC initialization
		pAcadFrame->RecalcLayout(); 
	}


}


// retrieves all the ADS and ARX applications
// currently loaded.

void CLoadApp::getLoadedApp(){
	// loadedApp is a CStringList data member
	// of our CLoadApp class that stores
	// the names of the applications loaded.

	// emty the existing list
	loadedApp.RemoveAll();

	// call the ads functions
	// to retreive the ARX and ADS
	// applications currently loaded
	struct resbuf * pArx, * pAds, * temp;
	pArx = ads_arxloaded();
	pAds = ads_loaded();

	temp = pArx;
	CString fappname, appname;

	// gets all the ARX apps currently loaded
	// except hidden applications
	while(temp != NULL){
		fappname = temp->resval.rstring;
		appname = getFileName(fappname);
		if(!iniFile.viewAll){
			if(iniFile.hiddenApp.Find(appname)){
				temp = temp->rbnext;
				continue;
			}
		}
 		loadedApp.AddTail(fappname);
		temp = temp->rbnext;
	}

	temp = pAds;

	// gets all the ADS apps currently loaded
	// except acadapp.exe
	while(temp != NULL){
		fappname = temp->resval.rstring;
		appname = getFileName(fappname);
		if(!iniFile.viewAll){
			if(iniFile.hiddenApp.Find(appname)){
				temp = temp->rbnext;
				continue;
			}
		}
 		loadedApp.AddTail(fappname);
		temp = temp->rbnext;
	}

	// release the linked lists no longer needed.
	ads_relrb(pArx);
	ads_relrb(pAds);
}

BOOL CLoadApp::isAppLoaded(CString app){

	CString aLoadedApp;
	CString ext = getExtension(app);
	CString filename;
	if(ext == "ARX")
		filename = getFileName(app);
	else
		filename = app;

	POSITION pos;
		
	for( pos = loadedApp.GetHeadPosition(); pos != NULL; )
	{
		aLoadedApp = theApp.loadedApp.GetNext( pos );
		if(aLoadedApp.CompareNoCase(filename) == 0)
			return TRUE;
	}

	return FALSE;

}

// end of CLoadApp implementation
//////////////////////////////////////////////////////////////////////////////



// load the current application.
void loadCurApp()
{
	// make sure we have an updatged list incase
	// the user unloaded the application using
	// another mechnism the loadApp
	theApp.getLoadedApp();

	CString appFile = theApp.iniFile.usedApp[0];
	CString message = "Unable to load " + appFile;
	if(appFile.IsEmpty()){
		message = "No default application specified.";
		message += "\nPlease run loadApp first.";
		MessageBox(theApp.hWndACAD, message, "loadApp Alert", MB_OK);
		return;
	}

	CString ext = getExtension(appFile);

	if(theApp.isAppLoaded(appFile)){
		ads_printf("\n%s already loaded.", appFile);
		return;
	}

	if(ext == "ARX"){
		if(ads_arxload(appFile) != RTNORM){
			MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
			return;
		}
		else{
			ads_printf("\n%s ", appFile);
			ads_printf("loaded.");
		}
			
	}
	else if(ext == "EXE"){
		if(ads_xload(appFile) != RTNORM){
			MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
			return;
		}
		else{
			ads_printf("\n%s ", appFile);
			ads_printf("loaded.");
		}
	}
	else if(ext == "LSP"){
  		int length = appFile.GetLength();
		for(int i=0; i<length; i++)
			if(appFile[i] == '\\' )
				appFile.SetAt(i, '/');
		message = "(load \"" + appFile + "\")";
		CString prompt = "(prompt \"\nLoading " + appFile + "\")";
		ads_queueexpr((char *)LPCTSTR(prompt));
		ads_queueexpr((char *)LPCTSTR(message));
		return;
	}
	else{
		message = "Don't know how to load " + appFile;
		MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
		return;
	}

	theApp.isLoaded = TRUE;

	theApp.getLoadedApp();
	setTitle();
}


// unload the current application

void unloadCurApp()
{
	// make sure we have an updatged list incase
	// the user unloaded the application using
	// another mechnism the loadApp
	theApp.getLoadedApp();

	CString appFile = theApp.iniFile.usedApp[0];
	CString ext = getExtension(appFile);
	CString message = "Unable to unload " + appFile;

	if(appFile.IsEmpty()){
		ads_printf("\nNo default application specified.");
		ads_printf("\nPlease run loadApp.");
		return;
	}

	if(isEqualApp(appFile, "loadApp.arx")){

		if(!theApp.iniFile.viewAll){
			// the following commented code is to simply not allow
			// unloading loadApp and display an Alert message
			message += "\nPlease use loaApp command.";
			MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
		}
		else{
			setTitle("");
			message = "(arxunload \"" + appFile + "\")";
			int length = message.GetLength();
			for(int i=0; i<length; i++)
				if(message[i] == '\\' )
			message.SetAt(i, '/');
			ads_queueexpr("(prompt \"\nunloading loadApp...\")");
			ads_queueexpr((char *)LPCTSTR(message));
		}

		return;
	}

	if(ext == "LSP"){
		message = "Cannot unload LISP applications.";
		MessageBox( theApp.hWndACAD, message, "Alert", MB_OK);
		return;
	}

	if(!theApp.isAppLoaded(appFile)){
		ads_printf("\n%s is not loaded.", appFile);
		return;
	}

	if(ext == "ARX"){
		if(ads_arxunload(appFile) != RTNORM){
			MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
			return;
		}
		else{
			ads_printf("\n%s ", appFile);
			ads_printf("unloaded.");
		}
	}
	else if(ext == "EXE"){
		if(ads_xunload(appFile) != RTNORM){
			MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
			return;
		}
		else{
			ads_printf("\n%s ", appFile);
			ads_printf("unloaded.");
		}
	}
	else{
		message = "Don't know how to load " + appFile;
		MessageBox(theApp.hWndACAD, message, "Alert", MB_OK);
		return;
	}
	theApp.isLoaded = FALSE;
	theApp.getLoadedApp();
	setTitle();
}



//////////////////////////////////////////////////////////////////////////////////








