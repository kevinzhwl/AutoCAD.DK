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
// File Name: loadApp.h
//
// DESCRIPTION:
//
// header file for loadApp.cpp. Defines the CLoadApp class
//	


#ifndef _LOADAPP_H
#define _LOADAPP_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <afxcmn.h>
#include <aced.h>

#include "resource.h"
#include "iniFile.h"
#include "lamfctoolbar.h"
#include "lispreactor.h"

extern "C" int ads_queueexpr(char*);

/////////////////////////////////////////////////////////////////////////////
// CLoadApp
// See CLoadApp.cpp for the implementation of this class
//

class CLoadApp
{
public:
	CLoadApp();
	virtual ~CLoadApp();

	void getLoadedApp();
	void addLispReactor();
	void removeLispReactor();
	void watchDragDrop();
	void unWatchDragDrop();
	BOOL isAppLoaded(CString);

	CIniFile iniFile;
	CStringList loadedApp;

	CWnd * pToolBarHandler;
	LaMfcToolbar * pToolBar;

	HWND hWndACAD;

	BOOL isInitialized;
	CLispReactor * pLispReactor;
	BOOL isLoaded;

};

void loadCurApp();
void unloadCurApp();

#endif // _LOADAPP_H
