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
// File Name: loadApp main.cpp
//
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <aced.h>
#include <adslib.h>
#include <RXREGSVC.H>

#include "resourcehelper.h"
extern "C" HINSTANCE _hdllInstance;
extern BOOL InitModule(HINSTANCE, DWORD, LPVOID);

//////////////////////////////////////////////////////////////
//
// Temporary Resource Override
//
//////////////////////////////////////////////////////////////
HINSTANCE CTemporaryResourceOverride::m_hInstanceDefault = NULL;

void CTemporaryResourceOverride::SetDefaultResource(HINSTANCE hInstDefault)
// For using the default constructor, you've got to use this guy once.
// Typically, you do this once in your DLLMain function....
{
    ASSERT(hInstDefault != NULL);

    m_hInstanceDefault = hInstDefault;
}

void CTemporaryResourceOverride::CommonConstruction(HINSTANCE hInst)
// Handles the various flavors of construction with a common handler
{
    // Here, we scurry away the old resource handle.
    m_hInstanceOld = AfxGetResourceHandle();
    AfxSetResourceHandle(hInst);
}

CTemporaryResourceOverride::CTemporaryResourceOverride(HINSTANCE hInstNew)
// If you have a specific instance in mind, use this variant.
{
    ASSERT(hInstNew != NULL);

    CommonConstruction(hInstNew);
}

CTemporaryResourceOverride::CTemporaryResourceOverride()
// If you're always using the same instance, set the default, and use this variant.
{
    ASSERT(m_hInstanceDefault != NULL);

    CommonConstruction(m_hInstanceDefault);
}

CTemporaryResourceOverride::~CTemporaryResourceOverride()
// And here's where we clean up.  Nice and simple.
{
    AfxSetResourceHandle(m_hInstanceOld);
}

// globals                 
CLoadApp theApp;

// Calling the loadApp dialog function
void loadApp(){
	InitDialog();
}

void createToolBar();
void InitApp();
void UnloadApp();

// Update the AutoCAD Window title, and the loadApp tollbar.
// This function is to be called from one of our notification
// functions only. This is a trick
void update()
{
	ads_printf("of loadApp due to a load through lisp or drag'n drop");
	theApp.getLoadedApp();
	updateCurrApp();
	setTitle();
}

//////////////////////////////////////////////////////////////
//
// MFC Initialization
//
//////////////////////////////////////////////////////////////

void InitMFC()
{
    InitModule(_hdllInstance, DLL_PROCESS_ATTACH, NULL);
}

void EndMFC()
{
   InitModule(_hdllInstance, DLL_PROCESS_DETACH, NULL);
}

 
static AFX_EXTENSION_MODULE arxmfcDLL;

extern BOOL 
InitModule(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {
      // Extension DLL one-time initialization 
      if (!AfxInitExtensionModule(
             arxmfcDLL, hInstance))
         return 0;

      // CTemporaryResourceOverride initialization
      CTemporaryResourceOverride::SetDefaultResource(_hdllInstance);

      // TODO: perform other initialization tasks here
      // ...
      // Insert this DLL into current process state.
      new CDynLinkLibrary(arxmfcDLL);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      // Extension DLL per-process termination
      AfxTermExtensionModule(arxmfcDLL);

      // TODO: perform other cleanup tasks here
   }
   return 1;   // ok
}


//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void InitApp()
{
    // Get the initial AutoCAD's Resource handle.
	//  ghAcadResource = AfxGetResourceHandle();

	CString loadAppPath;
	char fpath[512];
	// find acad.exe directory.
	// ads_findfile can't fail to find it.
	ads_findfile("acad.exe", fpath);
	// get the path only
	int fpSize = strlen(fpath) - 8;
	// copy the path
	for(int i=0; i<fpSize; i++)
		loadAppPath += fpath[i];

	loadAppPath += "loadApp.arx";
	char * currentPath = getLoadAppPath();

	if( !currentPath || loadAppPath != currentPath)
		registerLoadApp();

	delete [] currentPath;

	acrxRegisterApp((AcadApp::LoadReasons)(AcadApp::kOnCommandInvocation | AcadApp::kOnAutoCADStartup),
					"loadApp",
					"SOFTWARE\\Autodesk\\ObjectARX\\2.0\\SampleApps",
					2);


    // Init MFC
	InitMFC();

	createToolBar();

	// defines our commands
	// loadApp dialog
	acedRegCmds->addCommand( "LOADAPP", "loadApp", "loadApp", ACRX_CMD_MODAL, &loadApp );
	// quick load of the current application
	acedRegCmds->addCommand( "LOADAPP", "loadCurApp", "lca", ACRX_CMD_MODAL, &loadCurApp );
	// quick unload of the current application
	acedRegCmds->addCommand( "LOADAPP", "unloadCurApp", "ulca", ACRX_CMD_MODAL, &unloadCurApp );
	// toggle the display of the current application path name
	// in the AutoCAD Windows title.
	acedRegCmds->addCommand( "LOADAPP", "showtitle", "stle", ACRX_CMD_MODAL, &showInTitle );

	acedRegCmds->addCommand( "LOADAPP", "*update*", "_*update*", ACRX_CMD_MODAL, &update );

}

void UnloadApp()
{

	// removing the custom title if unloading loadApp
	// but not quitting AutoCAD
	if(acdbCurDwg())
		setTitle("");

	// undefining our commands
	acedRegCmds->removeGroup( "LOADAPP" );

	// End MFC
	EndMFC();

}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////


// our minimum Entry Point function
extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt ){
	switch( msg ){

		case AcRx::kInitAppMsg:
			acrxDynamicLinker->unlockApplication(pkt);
			InitApp();
		break;

		case AcRx::kUnloadAppMsg: 
			UnloadApp(); 
		break;
		
		case AcRx::kLoadDwgMsg:
			theApp.getLoadedApp();
			updateCurrApp();
			setTitle();
			theApp.isInitialized = TRUE;
		break;

		case AcRx::kUnloadDwgMsg:
			theApp.isInitialized = FALSE;
		break;

		default:
		break;
	}

	return AcRx::kRetOK;
}

