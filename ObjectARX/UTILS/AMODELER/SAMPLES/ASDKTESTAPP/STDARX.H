// 
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
// ---------------------------------------------------------------------
// File:        STDARX.H
// Description: All the ARX headers in one place so you can use precompiled headers
// Creation:    Feb, 1997
// -------------------------

#ifndef STD_OBJECTARX_INC
#define STD_OBJECTARX_INC

#include <dbmain.h>
#include <acgi.h>
#include <accmd.h>
#include <rxregsvc.h>                   // For acrxRegisterService 
#include <adslib.h>
#include <actrans.h>
#include <assert.h>
#include <dbsymtb.h>
#include <dbautil.h>
#include <dbents.h>
#include <geassign.h>

#else
#pragma message("ObjectARX Message: stdarx.h included more than once, Check your includes?")
#endif

