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
//  rxcom.h
//
//  This file contains all of the COM structs and typedef's that are needed
//  to compile the COM/DB-related code.  It actually contains small chunks
//  that were copied from Microsoft's standard files.  You can use this file
//  if you are compiling for a non-Windows platform, or if you don't want to
//  pull in the standard OLE files.
//
//  Note:  If you use this file in conjunction with any original Microsoft
//  files, you have to #include the MS files first to avoid redefinitions.
//

#if !defined(P386) || (!defined(_INC_WINDOW) && !defined(_WINDOWS))
#define USE_RXCOM_H 1
#endif

#if !defined(_RXCOM_H) && defined(USE_RXCOM_H)
#define _RXCOM_H

#if defined(P386)
#include <memory.h>
#endif
#include <string.h>
#include "comsys.h"

//   This was taken from \msvc20\include\windef.h.
//
//      09/16/94  02:00p                 6,520 windef.h
//
#ifndef _WINDEF_    // If windef.h hasn't already been #included...

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#endif // _WINDEF_

//
//   This was taken from \msvc20\include\winerror.h.
//
//      09/16/94  02:00p               170,298 winerror.h
//
#ifndef _WINERROR_    // If winerror.h hasn't already been #included...

#ifndef NOEERROR
#define NOERROR             S_OK
#endif

#ifndef S_OK
#define S_OK                                   (0x00000000L)
#endif

#ifndef E_NOINTERFACE
#define E_NOINTERFACE                    0x80004002L
#endif

#ifndef E_OUTOFMEMORY
#define E_OUTOFMEMORY                    0x8007000EL
#endif

#ifndef CLASS_E_NOAGGREGATION
#define CLASS_E_NOAGGREGATION            0x80040110L
#endif

#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#define FAILED(Status) ((HRESULT)(Status)<0)

#define ResultFromScode(sc) ((HRESULT) (sc))

#endif	//      _WINERROR_


//
//   This was taken from \msvc20\include\winnt.h.
//
//      09/16/94  02:00p               151,807 winnt.h
//
#ifndef _WINNT_    // If winnt.h hasn't already been #included...

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

#endif	//      _WINNT_


//
//   This was taken from \msvc20\include\objbase.h.
//
//      01/13/95  02:10p               257,465 objbase.h
//
#ifndef _OBJBASE_H_    // If objbase.h hasn't already been #included...

typedef LONG HRESULT;

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct  _GUID
    {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[ 8 ];
    }   GUID;
#endif // !GUID_DEFINED

#if !defined( __IID_DEFINED__ )
#define __IID_DEFINED__
typedef GUID IID;
#endif	// !__IID_DEFINED__

#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID              const IID &
#endif	// !_REFIID_DEFINED

#if !defined( __CLSID_DEFINED__ )
#define __CLSID_DEFINED__
typedef GUID CLSID;
#endif	// !__CLSID_DEFINED__

#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID              const CLSID &
#endif	// !_CLSID_DEFINED

#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID             const GUID &
#endif // !_REFGUID_DEFINED

#define IsEqualGUID(rguid1, rguid2) (!memcmp(&rguid1, &rguid2, sizeof(GUID)))


#ifndef interface
#define interface struct
#endif

#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__
interface IUnknown
    {
    public:
                virtual HRESULT __stdcall QueryInterface ( REFIID riid,
								void ** ppvObject ) = 0;
                virtual ULONG __stdcall AddRef() = 0;
                virtual ULONG __stdcall Release() = 0;
    };
#endif  //      __IUnknown_INTERFACE_DEFINED__


#ifndef __IClassFactory_INTERFACE_DEFINED__
#define __IClassFactory_INTERFACE_DEFINED__
interface IClassFactory : public IUnknown
    {
    public:
        virtual HRESULT __stdcall CreateInstance ( IUnknown  *pUnkOuter,
                                                          REFIID riid,
                                                          void **ppvObject ) = 0;

        virtual HRESULT __stdcall LockServer ( BOOL fLock ) = 0;

    };
#endif  //      __IClassFactory_INTERFACE_DEFINED__


#endif	//      _OBJBASE_H


#endif	//      !defined(_RXCOM_H) && !defined(_INC_WINDOWS) && ! defined(_WINDOWS_)

