//
//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 2005-2006 by Autodesk, Inc.
//
// The information contained herein is confidential, proprietary to Autodesk,
// Inc., and considered a trade secret as defined in section 499C of the
// penal code of the State of California.  Use of this information by anyone
// other than authorized employees of Autodesk, Inc. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcFStream.h
//
// Description:     Wrapper classes for std:ofstream and std::ifstream.
//
//////////////////////////////////////////////////////////////////////////////

// Note: 1. this header should be included *after* fstream headers
//        

#include "malloc.h"             // for _alloca()
#include "AdAChar.h"
#include "AdCharFmt.h"

#ifdef ASSERT
#define AcFStream_Assert ASSERT
#elif defined assert
#define AcFStream_Assert assert
#else
#define AcFStream_Assert(T)
#endif

#ifdef UNICODE
inline int AcFStream_wideToMulti(const wchar_t *pSrc, int nSrcSize,
                                 char *pDest, int nDestSize);
inline std::locale AcFStream_curLocale();
#endif

class AcIfstream : public
#ifndef UNICODE
                        std::ifstream {
#else
                        std::wifstream {
#endif
  public:
    class AcIfstream() {};
    class AcIfstream(const ACHAR *pName);
#ifdef UNICODE
    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
#endif
};

class AcOfstream : public
#ifndef UNICODE
                        std::ofstream {
#else
                        std::wofstream {
#endif
  public:
    class AcOfstream() {};
    class AcOfstream(const ACHAR *pName);
#ifdef UNICODE
    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
#endif

};

#ifndef UNICODE
inline AcIfstream::AcIfstream(const ACHAR *pName) : std::ifstream(pName)
{
}
inline AcOfstream::AcOfstream(const ACHAR *pName) : std::ofstream(pName)
{
}
#else
inline AcIfstream::AcIfstream(const ACHAR *pName)
{
    this->open(pName);
}

inline AcOfstream::AcOfstream(const ACHAR *pName)
{
    this->open(pName);
}

inline std::locale AcFStream_curLocale()
{
    char buf[100];
    sprintf(buf, ".%d", GetACP());
    // Only set LC_CTYPE, because we don't want it to start
    // formatting numbers with comma separators, etc
    return std::locale(buf, LC_CTYPE);
}

inline int AcFStream_wideToMulti(const wchar_t *pSrc, int nSrcSize,
                                 char *pDest, int nDestSize)
{
    return ::WideCharToMultiByte(
                        CP_ACP,
#if defined(WINVER) && (WINVER >= 0x0500)
                        // This function is currently only being used to
                        // convert filenames from widechar to ansi.  So
                        // we want it to fail if we can't get an exact
                        // mapping.
                        WC_NO_BEST_FIT_CHARS,
#else
                        0,
#endif
                        pSrc,
                        nSrcSize,
                        pDest,
                        nDestSize,
                        NULL,   // lpDefaultChar
                        NULL);  // lpUsedDefaultChar
}


inline void AcIfstream::open(const wchar_t *pName)
{
    this->std::wifstream::open(pName);
    this->imbue(AcFStream_curLocale());
}

inline void AcIfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
    this->std::wifstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
}

inline void AcOfstream::open(const wchar_t *pName)
{
    this->std::wofstream::open(pName);
    this->imbue(AcFStream_curLocale());
}

inline void AcOfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
    this->std::wofstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
}

#endif

