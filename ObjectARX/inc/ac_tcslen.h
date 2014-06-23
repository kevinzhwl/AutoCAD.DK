//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#pragma once

#ifdef _tcslen
#undef _tcslen
#endif

#ifdef UNICODE
#define _tcslen ac_wcslen
#else
#define _tcslen ac_strlen
#endif

#ifdef wcslen
#undef wcslen
#endif
#define wcslen ac_wcslen
#ifdef strlen
#undef strlen
#endif
#define strlen ac_strlen

#if defined ASSERT
#define AcTcsLen_Assert ASSERT
#elif defined(assert)
#define AcTcsLen_Assert assert
#elif defined(_ASSERTE)
#define AcTcsLen_Assert _ASSERTE
#elif defined ATLASSERT
#define AcTcsLen_Assert ATLASSERT
#else
#define AcTcsLen_Assert(x)
#endif

// use inline to prevent multiple definition errors.
__declspec(noinline) inline unsigned __stdcall ac_wcslen(const wchar_t * s)
{
    unsigned n = 0;
    while (*s != L'\0') {
        s++;
        n++;
        AcTcsLen_Assert(n < 0x7FFFFFFE);  // 2G-1 sanity check
    }
    return n;
}

__declspec(noinline) inline unsigned __stdcall ac_strlen(const char * s)
{
    unsigned n = 0;
    while (*s != '\0') {
        s++;
        n++;
        AcTcsLen_Assert(n < 0x7FFFFFFE);  //  2G-1 sanity check
    }
    return n;
}

