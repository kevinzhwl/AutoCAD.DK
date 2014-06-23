//
// (C) Copyright 1996-1997 by Autodesk, Inc.
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

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if defined(_DEBUG) && !defined(DEBUG_AUTOCAD)
    #pragma message("Building debug version of this module to be used with non-debug/Prod AutoCAD")
    #define _DEBUG_WAS_DEFINED
    #undef _DEBUG
#endif

#include <afxwin.h>
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>

// project header FIles
#include "IniFile.h"
#include "utils.h"
#include "loadapp.h"
#include "LaMfcToolbar.h"
#include "tbhandler.h"
#include "lispreactor.h"
#include "loadapp.h"
#include "loadAppDia.h"
#include "resource.h"


//extern "C" HINSTANCE _hdllInstance;
//extern "C" BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID);

extern class CLoadApp theApp;

extern void InitDialog();

void sendCommandToAutoCAD(CString);

CString getExtension(CString);
CString getFileName(CString);
CString getPath (CString);

BOOL isEqualApp(CString filename, CString appname);
void setTitle(CString);
void setTitle(char *);
void setTitle();
void showInTitle();
void updateCurrApp();
BOOL FilterOnDrop(MSG * pMessage);



// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif
