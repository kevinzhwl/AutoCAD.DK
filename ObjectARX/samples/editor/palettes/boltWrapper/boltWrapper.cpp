//
//
// (C) Copyright 2003 by Autodesk, Inc. 
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
// boltWrapper.cpp : Initialization functions
// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f boltWrapperps.mk in the project directory.
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include "boltWrapper.h"
#include <afxdllx.h>
#include "boltWrapper_i.c"
#include "Bolt.h"

HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);


// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Bolt, CBolt)
END_OBJECT_MAP()

////////////////////////////////////////////////////////////////////////////
//
// Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(BoltWrapperDLL);

// Now you can use the CAcModuleResourceOverride class in
// your application to switch to the correct resource instance.
// Please see the ObjectARX Documentation for more details

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    
    #pragma comment(lib, "asdkboltObject.lib")
    static const char* strasdkboltObject = "asdkboltObject.dbx";

	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
		// Extension DLL one time initialization
		BoltWrapperDLL.AttachInstance(hInstance);
		InitAcUiDLL();
		_Module.Init(ObjectMap, hInstance, &LIBID_AsDkBOLTWRAPPERLib);
		DisableThreadLibraryCalls(hInstance);
        // check if the arx app is loaded or not.
        // if not, load it as UI so that we won't have
        // proxy if this dll is unloaded by OS
		if(!::acrxAppIsLoaded(strasdkboltObject))
        {
            if (!acrxLoadModule(strasdkboltObject, false, true))
 	           return FALSE; //this will trigger a DLL_PROCESS_DETACH right away
        }
        //bump the reference count 
        acrxLoadModule(strasdkboltObject, false, false);

	} else if (dwReason == DLL_PROCESS_DETACH) {
		// Terminate the library before destructors are called
		BoltWrapperDLL.DetachInstance();
        //try to decrease the refcount on the dbx
        //if we couldn't load it then this a no op.
        acrxUnloadModule(strasdkboltObject);

		_Module.Term();

	}
	return TRUE;    // ok
}


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// Registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	return _Module.UnregisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	if (FAILED(DllRegisterServer()))
        acutPrintf("\nFailed to register.");//dbx safe
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT

	//}}AFX_ARX_INIT

	// TODO: add your initialization functions

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ASDK");
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
