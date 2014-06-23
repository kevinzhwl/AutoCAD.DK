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
#include "aced.h"
#include <adslib.h>
#include "resource.h"

extern "C" HINSTANCE _hdllInstance;
extern BOOL InitModule(HINSTANCE, DWORD, LPVOID);

extern void MFCTest();
extern void InitMFC();
extern void EndMFC();                

//////////////////////////////////////////////////////////////
//
// Standard C Test function
//
//////////////////////////////////////////////////////////////

void rxTest()
{
  MFCTest();
}

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
  InitMFC();

  ads_printf( "\nLoading Drag & Drop Sample ..." );

  acedRegCmds->addCommand( "ARXDnD",          // Group name 
                           "arxdd",        // Global function name
                           "arxdd",        // Local function name
                           ACRX_CMD_MODAL, // Type
                           &rxTest );      // Function pointer
  ads_printf( ".OK!\n" );
}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "ARXDnD" );

  // fin MFC
  EndMFC();
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
void MFCTest()
{ 
    HINSTANCE oldInstance = AfxGetResourceHandle();
    AfxSetResourceHandle(_hdllInstance); // This module resource

    CMainFrame *pMainFrame = new CMainFrame;
    RECT rect = {0,0,130,180}; 
    if (!pMainFrame->Create("Arxdd",
            WS_VISIBLE | WS_SYSMENU | WS_CAPTION  , rect,NULL))
	    TRACE("Error!");
    AfxSetResourceHandle(oldInstance); // Reset the module

}


void InitMFC()
{
    InitModule(_hdllInstance, DLL_PROCESS_ATTACH, NULL);
}

void EndMFC()
{
    InitModule(_hdllInstance, DLL_PROCESS_DETACH, NULL);
}

