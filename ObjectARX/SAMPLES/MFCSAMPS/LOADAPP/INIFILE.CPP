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
// File Name: IniFile.cpp
//
// DESCRIPTION:
//
// IniFile.cpp : implementation file.
//

#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// CIniFile


CIniFile::CIniFile()
{
	usedApp.SetSize(S_ARRAY_SIZE);
	viewAll = FALSE;
	showApp = FALSE;
	watchLisp = TRUE;
	watchDragDrop = TRUE;
}

CIniFile::~CIniFile()
{
}


// Sets the current application by adding it
// at the begining of the CStringArray if not
// already there or by moving it to the first
// position if there.
// The current application is the first in the list
// 15 more recently used applications.
void
CIniFile::setCurrApp(CString app){
	if(app.IsEmpty())
		return;
	setTitle(app);
	int i, index = -1;
	for(i=0; i<S_ARRAY_SIZE; i++){
		if(usedApp[i].CompareNoCase(app) == 0){
			usedApp[i] = app;
			index = i;
			i = S_ARRAY_SIZE;
		}
	}

	if(index == -1)
		for(i=S_ARRAY_SIZE -1; i>0; i--)
			usedApp[i] = usedApp[i-1];
	else
		for(i=index; i>0; i--)
			usedApp[i] = usedApp[i-1];
	usedApp[0] = app;
}


/////////////////////////////////////////////////////////////////////////////
// CIniFile commands
Adesk::Boolean CIniFile::saveRegistry()
{
	HKEY hLoadAppKey = NULL;
	hLoadAppKey = loadAppRegistry(KEY_READ);
	if(!hLoadAppKey) return Adesk::kFalse;
	HKEY hSettingsKey = NULL;
	DWORD dw;
	if(RegOpenKeyEx(hLoadAppKey, "Settings", 0, KEY_SET_VALUE, &hSettingsKey)
		== ERROR_SUCCESS)
	{
		if(viewAll) dw = 0x1;
		else dw = 0x0;
		RegSetValueEx(hSettingsKey, "View All", 0, REG_DWORD,
						  (LPBYTE)&dw, sizeof(DWORD));

		if(showApp) dw = 0x1;
		else dw = 0x0;
		RegSetValueEx(hSettingsKey, "Show Current Application", 0, REG_DWORD,
						  (LPBYTE)&dw, sizeof(DWORD));

		if(watchLisp) dw = 0x1;
		else dw = 0x0;
		RegSetValueEx(hSettingsKey, "Watch AutoLISP loads", 0, REG_DWORD,
						  (LPBYTE)&dw, sizeof(DWORD));

		if(watchDragDrop) dw = 0x1;
		else dw = 0x0;
		RegSetValueEx(hSettingsKey, "Watch Drag'nDrop loads", 0, REG_DWORD,
						  (LPBYTE)&dw, sizeof(DWORD));

		RegSetValueEx(hSettingsKey, "Initial directory", 0, REG_SZ,
						  (LPBYTE)(LPCTSTR)initDir, initDir.GetLength()+1);

	
	}

	else
	{
		if(hLoadAppKey) RegCloseKey(hLoadAppKey);
		return Adesk::kFalse;
	}

	if(hSettingsKey) RegCloseKey(hSettingsKey);

	HKEY hApplicationsKey = NULL;
	char buffer[20];
	if(RegDeleteKey(hLoadAppKey, "Current Applications") == ERROR_SUCCESS)
	{

		RegCreateKeyEx(hLoadAppKey, "Current Applications", 0, REG_NONE,
						REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
						&hApplicationsKey, &dw);
		int size = usedApp.GetSize();
		CString value;

		for(int i=0; i<size; i++)
		{
			_itoa(i, buffer, 10);
			value = CString("Application") + buffer;
			RegSetValueEx(hApplicationsKey, (LPCTSTR)value, 0, REG_SZ,
						  (LPBYTE)(LPCTSTR)usedApp[i], usedApp[i].GetLength()+1);
		}
	}

	else
	{
		if(hLoadAppKey) RegCloseKey(hLoadAppKey);
		return Adesk::kFalse;
	}

	if(hApplicationsKey) RegCloseKey(hApplicationsKey);

	HKEY hHiddenAppsKey = NULL;
	if(RegDeleteKey(hLoadAppKey, "Hidden Applications") == ERROR_SUCCESS)
	{

		RegCreateKeyEx(hLoadAppKey, "Hidden Applications", 0, REG_NONE,
						REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
						&hHiddenAppsKey, &dw);
		int size = usedApp.GetSize();
		CString value;
		POSITION pos;
		int i=0;
		CString application;
		for( pos = hiddenApp.GetHeadPosition(); pos != NULL; )
		{
			_itoa(i, buffer, 10);
			i++;
			value = "Application";
			value += buffer;
			application = hiddenApp.GetNext(pos);
			RegSetValueEx(hHiddenAppsKey, (LPCTSTR)value, 0, REG_SZ,
						  (LPBYTE)(LPCTSTR)application, application.GetLength()+1);
		}
	}

	else
	{
		if(hLoadAppKey) RegCloseKey(hLoadAppKey);
		return Adesk::kFalse;
	}

	if(hHiddenAppsKey) RegCloseKey(hHiddenAppsKey);
	if(hLoadAppKey) RegCloseKey(hLoadAppKey);

	return Adesk::kTrue;
}



Adesk::Boolean CIniFile::readRegistry()
{
	HKEY hLoadAppKey = NULL;
	hLoadAppKey = loadAppRegistry(KEY_READ);
	if(!hLoadAppKey) return Adesk::kFalse;
	HKEY hSettingsKey = NULL;
	DWORD lpType, size, val;
	if(RegOpenKeyEx(hLoadAppKey, "Settings", 0, KEY_QUERY_VALUE, &hSettingsKey)
		== ERROR_SUCCESS)
	{

		RegQueryValueEx(hSettingsKey, "View All", NULL, &lpType, (LPBYTE)&val, &size);
		if(lpType == REG_DWORD)
		{
			if(val == 1) viewAll = TRUE;
		}

		RegQueryValueEx(hSettingsKey, "Show Current Application", NULL, &lpType, (LPBYTE)&val, &size);
		if(lpType == REG_DWORD)
		{
			if(val == 1) showApp = TRUE;
		}

		RegQueryValueEx(hSettingsKey, "Watch AutoLISP loads", NULL, &lpType, (LPBYTE)&val, &size);
		if(lpType == REG_DWORD)
		{
			if(val == 1) watchLisp = TRUE;
			else watchLisp = FALSE;
		}

		RegQueryValueEx(hSettingsKey, "Watch Drag'nDrop loads", NULL, &lpType, (LPBYTE)&val, &size);
		if(lpType == REG_DWORD)
		{
			if(val == 1) watchDragDrop = TRUE;
			else watchDragDrop = FALSE;
		}

		char sbuf[256];


		RegQueryValueEx(hSettingsKey, "Initial directory", NULL, &lpType, NULL, &size);
		if(lpType == REG_SZ)
		{
			RegQueryValueEx(hSettingsKey, "Initial directory", NULL, &lpType,
							(LPBYTE)sbuf,
							&size);
			initDir = CString(sbuf);
		}

		RegCloseKey(hSettingsKey);
	}

	HKEY hApplicationsKey;

	if(RegOpenKeyEx(hLoadAppKey, "Current Applications", 0, KEY_QUERY_VALUE, &hApplicationsKey)
		== ERROR_SUCCESS)
	{
		CString value;
		int i = 0;
		char buffer[20], *app;
		_itoa(i, buffer, 10);
		value = CString("Application") + buffer;
		while(RegQueryValueEx(hApplicationsKey, (LPCTSTR)value, NULL, &lpType, NULL, &size)
				== ERROR_SUCCESS)
		{
			if(lpType == REG_SZ)
			{
				app = new char[size];
				if(RegQueryValueEx(hApplicationsKey, (LPCTSTR)value, NULL, &lpType,	(LPBYTE)app,
								&size) == ERROR_SUCCESS)
				{
					usedApp[i] = CString(app);
				}
				delete [] app;
			}
			i++;
			_itoa(i, buffer, 10);
			value = CString("Application") + buffer;
		}

		RegCloseKey(hApplicationsKey);
	}

	HKEY hHiddenAppsKey;

	if(RegOpenKeyEx(hLoadAppKey, "Hidden Applications", 0, KEY_QUERY_VALUE, &hHiddenAppsKey)
		== ERROR_SUCCESS)
	{
		CString value;
		int i = 0;
		char buffer[20], sbuf[256];
		_itoa(i, buffer, 10);
		value = CString("Application") + buffer;
		while(RegQueryValueEx(hHiddenAppsKey, (LPCTSTR)value, NULL, &lpType, NULL, &size)
				== ERROR_SUCCESS)
		{
			if(lpType == REG_SZ)
			{
				RegQueryValueEx(hHiddenAppsKey, (LPCTSTR)value, NULL, &lpType,
								(LPBYTE)sbuf,
								&size);
				hiddenApp.AddTail(CString(sbuf));
			}
			i++;
			_itoa(i, buffer, 10);
			value = "Application";
			value += buffer;
		}

		RegCloseKey(hHiddenAppsKey);
	}

	RegCloseKey(hLoadAppKey);
	return Adesk::kTrue;
}



void CIniFile::iniSave(){

	saveRegistry();
}

void CIniFile::iniRead(){

	readRegistry();
}
