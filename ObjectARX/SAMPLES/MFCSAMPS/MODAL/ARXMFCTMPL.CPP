// (C) Copyright 1996 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <aced.h>
#include "resourcehelper.h"
extern "C" HINSTANCE _hdllInstance;
extern BOOL InitModule(HINSTANCE, DWORD, LPVOID);

extern void InitMFC();
extern void EndMFC();                
extern void MyArxCmd();
extern void MFCTest();

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


//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
  InitMFC();
  acedRegCmds->addCommand( "MODAL", "MODAL", "MODAL",
  				ACRX_CMD_MODAL, &MyArxCmd );
  ads_printf( "\nEnter \"modal\" to bring up the dialog.\n" );
}


void unloadApp()
{
  acedRegCmds->removeGroup( "MODAL" );
  EndMFC();
}

void MyArxCmd()
{
    // point of entry for your ARX-MFC cmd.
    MFCTest();
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////

extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* )
{
  switch( msg ) 
  {
    case AcRx::kInitAppMsg: 
      initApp(); 
      break;
    case AcRx::kUnloadAppMsg: 
      unloadApp(); 
      break;
    default:
      break;
  }
  return AcRx::kRetOK;
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





