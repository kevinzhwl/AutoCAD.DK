#ifndef _COMSYS_H
#define _COMSYS_H
//
// (C) Copyright 1995-1997 by Autodesk, Inc.
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
// The check below means we want to provide DB-COM support for
// Windows platforms.
//
#if (defined WIN || defined WIN32) && !defined WINDU && !defined ACDBLIB \
    && !defined(ACDB_COM_SUPPORT)
#define ACDB_COM_SUPPORT
#endif

// The check below means we only want __stdcall for MSC compilers.
//
#if !defined(_MSC_VER)
#define __stdcall
#endif

#endif

