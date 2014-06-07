//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

// TO DO: When added to ARX disk spec, tweak IDE settings as follows:
//        1. Remove environment variables from compile & link settings
//        2. Make build target AutoCAD program files directory
//        3. Track down all TO DO's and remove them!
//

// MaterialUi.cpp : Initialization functions
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "resource.h"
#include "MaterialJig.h"
#include "MaterialCmd.h"

#include "appinfo.h"



const TCHAR kAppRegPath[] = 
    _T("Software\\Autodesk\\ObjectARX\\3.0\\SampleApps\\Material\\");
const TCHAR *kAppName       = _T("AsdkMaterialUi");
const TCHAR *kAppDescr      = _T("ARX sample app to demonstrate AcDbMaterials");
const TCHAR *kGroupName     = _T("ASDK_MATERIAL");
const TCHAR *kDbxModuleName = _T("AsdkMaterialDb.dbx");


////////////////////////////////////////////////////////////////////////////////
// Register the ARX application command handlers
// (This function can be used to read the localized command name
// from a string table stored in the resources).
//
void AddCommand(const TCHAR* cmdGroup, const TCHAR* cmdInt, const TCHAR* cmdLoc,
                const int cmdFlags, const AcRxFunctionPtr cmdProc, 
                const int idLocal)
{
    // If idLocal is not -1, it's treated as an ID for
    // a string stored in the resources.
    if (idLocal != -1) {
        TCHAR cmdLocRes[65];
        HMODULE hModule = GetModuleHandle(_T("AsdkMaterialUi.arx"));

        // Load strings from the string table and register the command.
        ::LoadString(hModule, idLocal, cmdLocRes, 64);
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

    } else
        // idLocal is -1, so the 'hard coded'
        // localized function name is used.
        acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}

////////////////////////////////////////////////////////////////////////////////
// Register the ARX application commands for demand loading
//
void RegisterArxApp(void)
{
    AcadAppInfo appInfo;

    appInfo.setAppName    (kAppName);                    // Application name
    appInfo.setModuleName (acedGetAppName());            // ARX file location
    appInfo.setAppDesc    (kAppDescr);                   // Description
    appInfo.setLoadReason (AcadApp::LoadReasons(         // Reasons for loading:
                           AcadApp::kOnCommandInvocation //  -command invoked
                         | AcadApp::kOnLoadRequest));    //  -load requested

    appInfo.writeToRegistry(false,true);                           // Commit to registry

    appInfo.writeGroupNameToRegistry   (kGroupName);     // Write group name
    for (int i = 0; i < MaterialCmd::kCmdCt; ++i)
        appInfo.writeCommandNameToRegistry (
            MaterialCmd::cmdName(i),  // Write command name
            MaterialCmd::cmdName(i));   
}

////////////////////////////////////////////////////////////////////////////////
// Initialize this application. Register your commands, reactors...
//
void InitApplication(void)
{
    // Register the command handlers
    for (int i = 0; i < MaterialCmd::kCmdCt; ++i)
    {
        AddCommand(kGroupName,                 // Group name
                   MaterialCmd::cmdName(i),    // Global command name
                   MaterialCmd::cmdName(i),    // Local command name
                   ACRX_CMD_MODAL,             // Command flags
                   MaterialCmd::cmdHandler(i), // Command handler function
                   -1);                        // Use localized function name

    acutPrintf(_T("\n %d) %s"),i+1,MaterialCmd::cmdName(i) );
    }
    acutPrintf(_T("\n"));
    // Register for demand loading
    RegisterArxApp();
}


////////////////////////////////////////////////////////////////////////////////
// Unload this application. Unregister all objects registered in 
// InitApplication.
//
void UnloadApplication(void)
{
    acedRegCmds->removeGroup(kGroupName);
}

////////////////////////////////////////////////////////////////////////////////
// ObjectARX entry point
//
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

        // Check if the dbx app is loaded or not. If not, then load it.
        if (!::acrxAppIsLoaded(kDbxModuleName))
            if (!pLinker->loadModule(kDbxModuleName, false, true))
                return AcRx::kRetError;

        // Bump the reference count 
        pLinker->loadModule(kDbxModuleName, false, false);

        InitApplication();
        break;

    case AcRx::kUnloadAppMsg:
        pLinker->unloadModule(kDbxModuleName);

        UnloadApplication();
        break;

    case AcRx::kUnloadDwgMsg:
        MaterialCmd::unload();
        break;
    }

    return AcRx::kRetOK;
}
