//
//  (C) Copyright 2004-2005 by Autodesk, Inc.  All rights reserved.
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

//
//              AdAChar.h
//
// Define the ACHAR type and ACRX_T() macro for use in ARX/DBX headers.
//
#pragma once

#ifndef AD_UNICODE
typedef char    ACHAR;
#define _ACRX_T(x)      x
#else
typedef wchar_t ACHAR;
#define _ACRX_T(x)      L ## x
#endif

// Same mechanism as tchar.h's _T() macro.  We redirect this to a
// second macro, so that other macros can be passed as the x arg,
// as in ACRX_T(__FILE__)
//
#define ACRX_T(x)      _ACRX_T(x)

