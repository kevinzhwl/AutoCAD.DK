// (C) Copyright 1993-1998 by Autodesk, Inc.
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

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H
// Check if the build is DEBUG version and it's intended
// to be used with Non-DEBUG AutoCAD.
// In this case, for MFC header files, we need to undefine
// _DEBUG symbol
// Read this project readme.txt for more detail
#if defined( _DEBUG) && !defined(DEBUG_AUTOCAD)
#pragma message("Building debug version of curveText.arx to be used with non-debug/Prod AutoCAD")
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include <afxwin.h>


#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#include <aced.h>
#include <dbsymtb.h>
#include <acutads.h>
#include <adscodes.h>
#include <rxregsvc.h>
#include <dbapserv.h>
#include <rxmfcapi.h>
#include <dbidmap.h>
#include <dbents.h>
#include <actrans.h>
#include <math.h>
#include <dbcurve.h>
#include <dbxline.h>
#include <dbray.h>
#endif