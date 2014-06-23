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
// File Name: utils.cpp
//
// DESCRIPTION:
//
// Defines some utility functions.

#include "stdafx.h"
#include <adesk.h>

#include <rxmfcapi.h>


///////////////////////////////////////////////////////////////////////////

// get the extension of a file name
CString getExtension(CString filename){
	int length = filename.GetLength();
	CString ext = "";
	if(length > 3)
		for(int i = length - 3; i < length; i++)
			ext += filename[i];

	ext.MakeUpper();
	return ext;
}

// get the file name without its extension and path
CString getFileName(CString pathname){
	int length = pathname.GetLength();
	CString filename = "";
	int i;
	for(i = length-1; i >= 0; i--)
		if( (pathname[i] == '\\') || (pathname[i] == '/'))
			break;

	for(int j = i+1; j < length; j++)
			filename += pathname[j];

	return filename;
}

// get the file name without its extension and path
CString getPath (CString filename){
	int length = filename.GetLength();
	CString path = "";
	int i;
	for(i = length-1; i >= 0; i--)
		if( (filename[i] == '\\') || (filename[i] == '/'))
			break;

	for(int j = 0; j < i; j++)
			path += filename[j];

	return path;
}

BOOL isEqualApp(CString filename, CString appname){
	int	flength = filename.GetLength();
	int alength = appname.GetLength();
	CString app;
	if(flength>=alength){
		for(int i=flength-alength; i<flength; i++)
			app += filename[i];
		if(app.CompareNoCase(appname) == 0)
			return TRUE;
	}
	return FALSE;
}

void updateCurrApp(){
	CString element;
	POSITION pos;
	int size = theApp.iniFile.usedApp.GetSize();

	for( pos = theApp.loadedApp.GetHeadPosition(); pos != NULL; )
	{
		element = theApp.loadedApp.GetNext( pos );
		for(int i=0; i<size; i++){
			if(element.CompareNoCase(theApp.iniFile.usedApp[i]) == 0){
				theApp.iniFile.usedApp[i] = element;
				break;
			}
		}
	}

	if(theApp.isAppLoaded(theApp.iniFile.usedApp[0]))
		theApp.isLoaded = TRUE;
	else
		theApp.isLoaded = FALSE;

}


void setTitle(CString name){
	if(!theApp.iniFile.showApp)
		return;
	
	CWnd * AcadW = CWnd::FromHandle(theApp.hWndACAD);
	CString title = "AutoCAD";
/*	CString title = "AutoCAD-Prerelease Software";

#if defined(DEBUG_AUTOCAD)
    title = "AutoCAD-Nonproduction Software";
#endif
*/

	if(name.IsEmpty()){
		AcadW->SetWindowText( title );
		return;
	}

	title += " - " + name;
	CString ext = getExtension(name);
	if(ext == "lsp")
		AcadW->SetWindowText( title );
	else{
		if(!theApp.isAppLoaded(name))
			title += " - not loaded";
		else
			title += " - loaded";
	}
	AcadW->SetWindowText( title );
}

// utility function to display the fully qualified
// file name of the current application in the AutoCAD
// window title.

void showInTitle()
{
	if(theApp.iniFile.showApp){
		setTitle("");
		theApp.iniFile.showApp = FALSE;
		theApp.iniFile.iniSave();
	}
	else{
		theApp.iniFile.showApp = TRUE;
		setTitle();
		theApp.iniFile.iniSave();
	}
}

void setTitle(char * name){
	CString cname = name;
	setTitle(cname);
}

void setTitle(){
	CString name = theApp.iniFile.usedApp[0];
	setTitle(name);
}


// Utility function to send a command
// to AutoCAD.
void sendCommandToAutoCAD(CString cmd)
{
  COPYDATASTRUCT cmdMsg;
  cmdMsg.dwData = (DWORD)1;
  cmdMsg.cbData = (DWORD)_tcslen(cmd) + 1;
  cmdMsg.lpData = cmd.GetBuffer(cmd.GetLength()+1) ;                   
  SendMessage(adsw_acadMainWnd(), WM_COPYDATA, (WPARAM)adsw_acadMainWnd(), 
             (LPARAM)&cmdMsg);
}

BOOL FilterOnDrop(MSG * pMessage)
{
	if(pMessage->message != WM_DROPFILES)
		return FALSE;
	
	HDROP hDrop;
	hDrop = (HDROP)pMessage->wParam;
	char file[512];

	// Could be (should be) more sophisticated:
	// do not handle the case of multiple files.
	// But who will still load applications using
	// drag'n drop from the explorer now that
	// loadApp makes your life so much easier ???
	DragQueryFile( hDrop, 0, file, 511);
	CString filename = file;
	CString ext = getExtension(filename);

	if((ext == "ARX") || (ext == "EXE")){
		if(theApp.pLispReactor)
			theApp.pLispReactor->fromDragDrop = TRUE;
		if(theApp.iniFile.watchDragDrop)
			ads_queueexpr("(command \"_*update*\")");
	}

	return FALSE;
}

char * getLoadAppPath()
{
	HKEY hLoadAppKey = NULL;
	// Open the "loadApp" key for read
	hLoadAppKey = loadAppRegistry(KEY_READ);
	if(!hLoadAppKey)
		return NULL;

	// check if the registry is up to date
	HKEY hApplicationsKey = NULL;
	if(RegOpenKeyEx(hLoadAppKey,
					"Current Applications",
					0,
					KEY_READ,
					&hApplicationsKey) != ERROR_SUCCESS)
	{
		RegCloseKey(hLoadAppKey);
		return NULL;
	}

	RegCloseKey(hApplicationsKey);

	
	HKEY hLoader = NULL;
	// Open the "loader" key to query the "MODULE" value
	if(RegOpenKeyEx(hLoadAppKey,
					"Loader",
					0,
					KEY_QUERY_VALUE,
					&hLoader) != ERROR_SUCCESS)
	{
		RegCloseKey(hLoadAppKey);
		return NULL;
	}


	DWORD lpType;
	DWORD size;
	char * path = NULL;
	// get the path
	RegQueryValueEx(hLoader, "MODULE", NULL, &lpType, NULL, &size);
	if(lpType == REG_SZ)
	{
		path = new char[size];	
		RegQueryValueEx(hLoader, "MODULE", NULL, &lpType,
						(LPBYTE)path,
						&size);
	}
	RegCloseKey(hLoader);
	RegCloseKey(hLoadAppKey);
	return path;
}
 

HKEY loadAppRegistry(REGSAM regsam)
{
	HKEY hLoadAppKey = NULL;
	// open the "loadApp" key
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				 "SOFTWARE\\Autodesk\\ObjectARX\\2.0\\SampleApps\\loadApp",
				 0, regsam, &hLoadAppKey);
	return hLoadAppKey;
}

void registerLoadApp()
{
	CString loadAppPath, loadAppPathName;
	char fpath[512];
	// find acad.exe directory.
	// ads_findfile can't fail to find it.
	ads_findfile("acad.exe", fpath);
	// get the path only
	int fpSize = strlen(fpath) - 9;
	// copy the path
	for(int i=0; i<fpSize; i++)
		loadAppPath += fpath[i];

	loadAppPathName = loadAppPath;
	loadAppPathName += "\\loadApp.arx";


	HKEY hLoadAppKey = NULL;
	HKEY hObjectARX20Key = NULL;
	HKEY hSampleAppsKey = NULL;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
					"SOFTWARE\\Autodesk\\ObjectARX\\2.0",
					0,
					KEY_WRITE,
					&hObjectARX20Key) == ERROR_SUCCESS)
	{
		DWORD dw;
		// Create the "SampleApps" key if not there
		if(RegCreateKeyEx(hObjectARX20Key, "SampleApps", 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
			&hSampleAppsKey, &dw) == ERROR_SUCCESS)
		{
			// Create the "loadApp" key
			if(RegCreateKeyEx(hSampleAppsKey, "loadApp", 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
				&hLoadAppKey, &dw) == ERROR_SUCCESS)
			{
				HKEY hLoaderKey = NULL;
				// Create the "Loader" key
				RegCreateKeyEx(hLoadAppKey, "Loader", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hLoaderKey, &dw);

				// set the "MODULE" value (loadApp path)
				RegSetValueEx(hLoaderKey, "MODULE", 0, REG_SZ,
							  (LPBYTE)(LPCTSTR)loadAppPathName,
							  loadAppPathName.GetLength()+1);
				if (hLoaderKey)
					RegCloseKey(hLoaderKey);


				HKEY hCommandsKey = NULL;
				// Create the "Commands" key
				RegCreateKeyEx(hLoadAppKey, "Commands", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hCommandsKey, &dw);

				// set the command values
				RegSetValueEx(hCommandsKey, "LOADAPP", 0, REG_SZ,
							  (LPBYTE)_T("LOADAPP"), 8);
				RegSetValueEx(hCommandsKey, "LCA", 0, REG_SZ,
							  (LPBYTE)_T("LCA"), 4);
				RegSetValueEx(hCommandsKey, "ULCA", 0, REG_SZ,
							  (LPBYTE)_T("ULCA"), 5);
				RegSetValueEx(hCommandsKey, "VIEWTITLE", 0, REG_SZ,
							  (LPBYTE)_T("VIEWTITLE"), 10);
				if (hCommandsKey)
					RegCloseKey(hCommandsKey);

				HKEY hNameKey = NULL;
				// Create the "Name" key
				RegCreateKeyEx(hLoadAppKey, "Name", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hNameKey, &dw);
				// set the name value
				RegSetValueEx(hNameKey, "LOADAPP", 0, REG_SZ,
							  (LPBYTE)_T("LOADAPP"), 8);
				if (hNameKey)
					RegCloseKey(hNameKey);

				HKEY hSettingsKey = NULL;
				// Create the "Settings" key
				RegCreateKeyEx(hLoadAppKey, "Settings", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hSettingsKey, &dw);
				// set the View All value
				dw = 0x0;
				RegSetValueEx(hSettingsKey, "View All", 0, REG_DWORD,
							  (LPBYTE)&dw, sizeof(DWORD));
				// set the Show Current Application value
				dw = 0x0;
				RegSetValueEx(hSettingsKey, "Show Current Application", 0, REG_DWORD,
							  (LPBYTE)&dw, sizeof(DWORD));
				// set the Watch Lisp loads value
				dw = 0x1;
				RegSetValueEx(hSettingsKey, "Watch AutoLISP loads", 0, REG_DWORD,
							  (LPBYTE)&dw, sizeof(DWORD));
				// set the Watch Drag'nDrop loads value
				dw = 0x1;
				RegSetValueEx(hSettingsKey, "Watch Drag'nDrop loads", 0, REG_DWORD,
							  (LPBYTE)&dw, sizeof(DWORD));
				// set the Initial directory value
				RegSetValueEx(hSettingsKey, "Initial directory", 0, REG_SZ,
							  (LPBYTE)(LPCTSTR)loadAppPath, loadAppPath.GetLength()+1);

				if (hSettingsKey)
					RegCloseKey(hSettingsKey);


				HKEY hApplicationsKey = NULL;
				// Create the "Current Applications" key
				RegCreateKeyEx(hLoadAppKey, "Current Applications", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hApplicationsKey, &dw);

				if (hApplicationsKey)
					RegCloseKey(hApplicationsKey);

				HKEY hHiddenAppsKey = NULL;
				// Create the "Hidden Applications" key
				RegCreateKeyEx(hLoadAppKey, "Hidden Applications", 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hHiddenAppsKey, &dw);

				if (hHiddenAppsKey)
					RegCloseKey(hHiddenAppsKey);


			}
			if (hLoadAppKey)
				RegCloseKey(hLoadAppKey);
		}
		if (hSampleAppsKey)
			RegCloseKey(hSampleAppsKey);
	}
	if (hObjectARX20Key)
		RegCloseKey(hObjectARX20Key);
	  
}
