// (C) Copyright 1996,1997 by Autodesk, Inc. 
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

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//////////////////////////////////////////////////////////////
//
// Includes
//
//////////////////////////////////////////////////////////////

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

#include "stdafx.h"
#include "aced.h"
#include <adslib.h>
                 
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

  acedRegCmds->addCommand( "MFCStatic",      // Group name 
                           "staticmfc",      // Global function name
                           "staticmfc",          // Local function name
                           ACRX_CMD_MODAL,    // Type
                           &rxTest );         // Function pointer
  ads_printf( "\nEnter \"staticMfc\" to bring up the dialog.\n" );

}

void unloadApp()
{
  // Remove the command group because we are unloading
  //
  acedRegCmds->removeGroup( "MFCStatic" );

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

// END CODE APPEARING IN SDK DOCUMENT.

// This sample uses static MFC lib that requires static runtime lib.
// You need to replace CObject operator new and delete and link with
// rxheap.lib.
// This will generate duplicate definitions and you have to use
// linker option /FORCE to produce the .arx file.
// If you want to get rid of the duplicate definitions, you
// can include rxdbgheap.cpp and rxafxmem.cpp into your project and
// comment out below code section (it's in rxafxmem.cpp already)
// These two files are in this project directory but they are
// not included the project makefile.
// The use of these two files are not officially supported by
// Autodesk since they are not fully tested yet. However, since
// they are source files, you can easily modify them if you find
// problems.

#ifdef _DEBUG
void* CObject::operator new(size_t nSize)
{
	return ::operator  new(nSize);
}

void *CObject::operator new (size_t nSize,LPCSTR lpszFileName,int nLine)
{
	return ::operator  new(nSize);
}

void CObject::operator delete(void *pbData)
{
	delete pbData;
}
#endif // _DEBUG

