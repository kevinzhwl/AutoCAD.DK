//
// (C) Copyright 2001 by Autodesk, Inc. 
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
#if !defined(RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_)
#define RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void _cdecl RxTrace(const TCHAR* lpszFormat, ...);

#ifdef _DEBUG
#define RXTRACE         ::RxTrace
#define RXASSERT(f)     assert(f)
#else
#define RXTRACE         1?(void)0: ::RxTrace
#define RXASSERT(f)     ((void)0)
#endif


#endif // !defined(RXTRACE_H__35A69BA3_C12C_11D2_B89B_080009DCA551__INCLUDED_)
