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
#include <winbase.h>


static HWND hWndACAD = NULL;

extern "C" HINSTANCE _hdllInstance;
extern "C" BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID);

extern void MFCTest();
extern void InitMFC();
extern void EndMFC();                

//////////////////////////////////////////////////////////////
//
// Standard C Test function
//
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
  InitMFC();

  ads_printf( "\nLoading Drag & Drop Sample ..." );

  acedRegCmds->addCommand( "DD-INSERT",         // Group name 
                           "DDInsert",          // Global function name
                           "DDInsert",          // Local function name
                           ACRX_CMD_MODAL,      // Type
                           &MFCTest );          // Function pointer

  ads_printf( ".OK!\n" );
}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "DD-INSERT" );

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
    case AcRx::kLoadDwgMsg: 	// Sent at same time
	        		// ADS Apps receive RQXLOAD code, i.e.
	break;			// once per drawing Open. At this time
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
    if (!pMainFrame->Create(NULL,
            WS_VISIBLE | WS_SYSMENU | WS_CAPTION  , rect,NULL))
	    TRACE("Error creating dragDrop window.!");
    AfxSetResourceHandle(oldInstance); // Reset the module

}


void InitMFC()
{
   DllMain(_hdllInstance, DLL_PROCESS_ATTACH, NULL);

}

void EndMFC()
{
    DllMain(_hdllInstance, DLL_PROCESS_DETACH, NULL);
}


