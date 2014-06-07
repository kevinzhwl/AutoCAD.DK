//
//
// (C) Copyright 2000-2007 by Autodesk, Inc. 
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

// SmileyUi.cpp : Initialization functions
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "StdArx.h"
#include "resource.h"
#include "SmileJig.h"
#include "appinfo.h"



// This command registers an ARX command.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
void RegisterArxApp();
//}}AFX_ARX_ADDIN_FUNCS


/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    AcRxDynamicLinker *pLinker = acrxDynamicLinker;
    switch (msg) {
    case AcRx::kInitAppMsg:
        // Comment out the following line if your
        // application should be locked into memory
        pLinker->unlockApplication(pkt);
        pLinker->registerAppMDIAware(pkt);
        // check if the arx app is loaded or not.
        // if not, load it as UI so that we won't have
        // proxy if this dll is unloaded by OS
        if (!::acrxAppIsLoaded(_T("AsdkSmileyDb.dbx")))
        {
            if (!pLinker->loadModule(_T("AsdkSmileyDb.dbx"), false, true))
                return AcRx::kRetError;
        }
        // bump the reference count 
        pLinker->loadModule(_T("AsdkSmileyDb.dbx"), false, false);
        InitApplication();
        break;
    case AcRx::kUnloadAppMsg:
        pLinker->unloadModule(_T("AsdkSmileyDb.dbx"));
        UnloadApplication();
        break;
    }
    return AcRx::kRetOK;
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
    // NOTE: DO NOT edit the following lines.
    //{{AFX_ARX_INIT
    AddCommand(_T("ASDK_SMILEY"), _T("ASDK_SMILEY"), _T("SMILEY"), ACRX_CMD_MODAL, createSmiley);
    RegisterArxApp();
    //}}AFX_ARX_INIT
	InitAcUiDLL();
}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
    // NOTE: DO NOT edit the following lines.
    //{{AFX_ARX_EXIT
    acedRegCmds->removeGroup(_T("ASDK_SMILEY"));
    //}}AFX_ARX_EXIT
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
    TCHAR cmdLocRes[65];

    // If idLocal is not -1, it's treated as an ID for
    // a string stored in the resources.
    if (idLocal != -1) {
        HMODULE hModule = GetModuleHandle(_T("AsdkSmileyUi.arx"));

        // Load strings from the string table and register the command.
        ::LoadString(hModule, idLocal, cmdLocRes, 64);
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

    } else
        // idLocal is -1, so the 'hard coded'
        // localized function name is used.
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}

// This function registers this ObjectARX Application
// on AutoCAD for demandload and in the
// Windows Registry.
void RegisterArxApp()
{
    // Fill the AppInfo structure with our demand loading details.
    AcadAppInfo appInfo;
    appInfo.setAppName(_T("AsdkSmileyUi"));// Application Name
    appInfo.setModuleName(acedGetAppName());// ARX File Location
    appInfo.setAppDesc(_T("AsdkSmileyUi Sample")); // Description
    appInfo.setLoadReason( // Specify when we want this to load
        AcadApp::LoadReasons(
        AcadApp::kOnCommandInvocation |
        AcadApp::kOnLoadRequest));
    
    appInfo.writeToRegistry(false,true);// Write the AppInfo to the registry, don't write to DBX registry section.
    appInfo.writeGroupNameToRegistry(_T("ASDK_SMILEY")); // Write the Group Name
    appInfo.writeCommandNameToRegistry(_T("SMILEY"),_T("SMILEY"));// Write our command.
}
