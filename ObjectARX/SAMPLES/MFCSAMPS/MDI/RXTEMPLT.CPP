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
#include "rxmfcapi.h"

extern "C" HINSTANCE _hdllInstance;
static HWND hWndACAD = NULL;
extern "C" BOOL APIENTRY InitModule(HINSTANCE, DWORD, LPVOID);

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
  ads_printf( "\nTest function called\n" );
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

  ads_printf( "\nLoading MDI Sample ..." );

  acedRegCmds->addCommand( "MFC",      // Group name 
                           "bounce",      // Global function name
                           "bounce",          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &rxTest );         // Function pointer
  ads_printf( ".OK!\n" );
  ads_printf( "Command is 'bounce'!\n" );

}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "MFC" );

  // end MFC
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
void InitMFC()
{
    InitModule(_hdllInstance, DLL_PROCESS_ATTACH, NULL);
}

void EndMFC()
{
    InitModule(_hdllInstance, DLL_PROCESS_DETACH, NULL);
}

void MFCTest()
{

    HINSTANCE oldInstance = AfxGetResourceHandle();
    AfxSetResourceHandle(_hdllInstance); // This module resource

	CBounceWnd *pBounceWnd = new CBounceWnd;
        CWinApp* theAcad =  acedGetAcadWinApp();
        CMDIFrameWnd* pParent = acedGetAcadFrame();
        RECT rect = {0,0,300,300}; 
	if (!pBounceWnd->Create("Bounce",
            WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rect, pParent))
		return;
        pParent->MDITile();
    AfxSetResourceHandle(oldInstance); // Reset the module

}

/////////////////////////////////////////////////////////////////////////////
