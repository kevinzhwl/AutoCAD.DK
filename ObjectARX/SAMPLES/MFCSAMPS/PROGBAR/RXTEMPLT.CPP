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

#include "afxwin.h"  // need this because rxmfcapi.h needs
                     // windows header. If not, you can just
                     // cut out progress bar API functions
#include "aced.h"
#include "rxmfcapi.h"


//////////////////////////////////////////////////////////////
//
// Standard C Test function
//
//////////////////////////////////////////////////////////////

void Test();

void rxTest()
{
  ads_printf( "\nTest function called\n" );
  Test();
}

//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{

  acedRegCmds->addCommand( "ProgressBar",      // Group name 
                           "progbar",      // Global function name
                           "progbar",          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &rxTest );         // Function pointer
  ads_printf( ".OK!\n" );
}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "ProgressBar" );

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
void Test()
{

    ads_printf( "Running Progress Meter...\n" );

    acedSetStatusBarProgressMeter("Test Progress Bar", 0, 100);
    for(int i =0; i <= 100; i++) {
        Sleep(100);
        acedSetStatusBarProgressMeterPos(i);
    }
    acedRestoreStatusBar();


}

