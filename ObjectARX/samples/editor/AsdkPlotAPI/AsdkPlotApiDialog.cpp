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

//-----------------------------------------------------------------------------
//----- AsdkPlotApiDialog.cpp : Initialization functions
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include <initguid.h>
#include "AsdkPlotApiDialog.h"
#include <afxdllx.h>
#include "AsdkPlotApiDialog_i.c"
#include "acadi_i.c"
//-----------------------------------------------------------------------------
class CAsdkPlotApiDialogModule : public CAtlDllModuleT<CAsdkPlotApiDialogModule> {

public :
	DECLARE_LIBID(LIBID_asdkAsdkPlotApiDialogLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ASDKPLOTAPIDIALOG, "{726667B4-FA4A-49E6-9353-576BAADA24F9}")
} ;

CAsdkPlotApiDialogModule _AtlModule ;

//-----------------------------------------------------------------------------
//----- Define the sole extension module object.
AC_IMPLEMENT_EXTENSION_MODULE(AsdkPlotApiDialogDLL)
//- Please do not remove the 3 following lines. These are here to make .NET MFC Wizards
//- running properly. The object will not compile but is require by .NET to recognize
//- this project as being an MFC project
#ifdef NEVER
AFX_EXTENSION_MODULE AsdkPlotApiDialogExtDLL ={ NULL, NULL } ;
#endif

//----- Now you can use the CAcModuleResourceOverride class in
//----- your application to switch to the correct resource instance.
//----- Please see the ObjectARX Documentation for more details

//-----------------------------------------------------------------------------
//----- DLL Entry Point
extern "C"
BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	//----- Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved) ;

	if ( dwReason == DLL_PROCESS_ATTACH ) {
        _hdllInstance =hInstance ;
		AsdkPlotApiDialogDLL.AttachInstance (hInstance) ;
		DllRegisterServer();
		InitAcUiDLL () ;
	} else if ( dwReason == DLL_PROCESS_DETACH ) {
		AsdkPlotApiDialogDLL.DetachInstance () ;
	}
	return (_AtlModule.DllMain (dwReason, lpReserved)) ; 
}

//-----------------------------------------------------------------------------
//----- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow (void) {
	return ((_AtlModule.GetLockCount () == 0) ? S_OK : S_FALSE) ;
}

//-----------------------------------------------------------------------------
//----- Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
	return (_AtlModule.GetClassObject (rclsid, riid, ppv)) ;
}

//-----------------------------------------------------------------------------
//----- DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer (void) {
	//----- Registers object, typelib and all interfaces in typelib
	return (_AtlModule.RegisterServer (TRUE)) ;
}

//-----------------------------------------------------------------------------
//----- DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer (void) {
	return (_AtlModule.UnregisterServer (TRUE)) ;
}

