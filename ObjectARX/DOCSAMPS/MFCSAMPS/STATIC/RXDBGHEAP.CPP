// (C) Copyright 1997 by Autodesk, Inc. 
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
// When you use rxheap.lib and want to remove all duplicate symbols
// definitions, you can insert this file in you project.
// Basically, it replaces dbgheap.cpp from C Runtime lib so that
// the linker won't pull in the object file for that file. As the
// result, you'll have a clean build without any errors and don't
// need to use /Force linker option.
// 
// Warning: this file hasn't been tested troughly.
// Please modify the file accordingly, or not use the file at all,
// if you find any problem.

#ifdef _DEBUG

#include <crtdbg.h>
#include <assert.h>

extern "C" void *acad_malloc(size_t size);
extern "C" void *acad_calloc(size_t size, size_t num);
extern "C" void *acad_realloc(void *p, size_t size);
extern "C" size_t acad__msize(void *);
extern "C" void acad_free(void *p);
extern "C" char *acad__strdup(const char *p);

extern "C"  void * __cdecl _malloc_dbg (
        size_t nSize,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  //assert(0);
  //return 0;
  return acad_malloc(nSize);
}

extern "C" void * __cdecl _nh_malloc (
        size_t nSize,
        int nhFlag
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}



extern "C" void * __cdecl _nh_malloc_dbg (
        size_t nSize,
        int nhFlag,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}

extern "C" void * __cdecl _heap_alloc(
        size_t nSize
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}

extern "C" void * __cdecl _heap_alloc_dbg(
        size_t nSize,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C" void * __cdecl _calloc_dbg(
        size_t nNum,
        size_t nSize,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
//  assert(0);
//  return 0;
  return acad_calloc(nNum, nSize);
}


extern "C" void * __cdecl _realloc_dbg(
        void * pUserData,
        size_t nNewSize,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
//  assert(0);
//  return 0;
  return acad_realloc(pUserData, nNewSize);
}

extern "C"  void * __cdecl _expand(
        void * pUserData,
        size_t nNewSize
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C" void * __cdecl _expand_dbg(
        void * pUserData,
        size_t nNewSize,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}

extern "C" void __cdecl _free_lk(
        void * pUserData
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}

extern "C" void __cdecl _free_dbg(
        void * pUserData,
        int nBlockUse
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
//  assert(0);
//  return;
  acad_free(pUserData);
}

extern "C" void __cdecl _free_dbg_lk(
        void * pUserData,
        int nBlockUse
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}


extern "C"  size_t __cdecl _msize_dbg (
        void * pUserData,
        int nBlockUse
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
//  assert(0);
//  return 0;
  return acad__msize(pUserData);
}

extern "C" long __cdecl _CrtSetBreakAlloc(
        long lNewBreakAlloc
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}

extern "C"  void __cdecl _CrtSetDbgBlockType(
        void * pUserData,
        int nBlockUse
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}

extern "C" _CRT_ALLOC_HOOK __cdecl _CrtSetAllocHook(
        _CRT_ALLOC_HOOK pfnNewHook
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}
 
extern "C" int __cdecl _CrtCheckMemory(
        void
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C"  int __cdecl _CrtSetDbgFlag(
        int fNewBits
        )
{
  // It seems that debug static MFC use this method so that
  // we can't just assert(0);
#if !defined(_WINDLL) && !defined(_USRDLL) && defined(_MFC_VER)
  // Can't use Debug C Runtime heap routines with rxheap.lib
  // Since ARX apps using smartheap memory facility, an attempt
  // to set dbg flag is just a no-op operation.
  assert(0);
#endif
  return 0;
}

extern "C"  void __cdecl _CrtDoForAllClientObjects(
        void (*pfn)(void *, void *),
        void * pContext
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}


extern "C"  int __cdecl _CrtIsValidPointer(
        const void * pv,
        unsigned int nBytes,
        int bReadWrite
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}

extern "C"  int __cdecl _CrtIsValidHeapPointer(
        const void * pUserData
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C"  int __cdecl _CrtIsMemoryBlock(
        const void * pUserData,
        unsigned int nBytes,
        long * plRequestNumber,
        char ** pszFileName,
        int * pnLine
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C"  _CRT_DUMP_CLIENT __cdecl _CrtSetDumpClient(
        _CRT_DUMP_CLIENT pfnNewDump
        )
{
  // It seems that debug static MFC use this method so that
  // we can't just assert(0);
#if !defined(_WINDLL) && !defined(_USRDLL) && defined(_MFC_VER)
  // Can't use Debug C Runtime heap routines with rxheap.lib
  // Since ARX apps using smartheap memory facility, an attempt
  // to hook in the dump client is just a noop.
  assert(0);
#endif
  return 0;
}


extern "C"  void __cdecl _CrtMemCheckpoint(
        _CrtMemState * state
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return ;
}


extern "C"  int __cdecl _CrtMemDifference(
        _CrtMemState * state,
        const _CrtMemState * oldState,
        const _CrtMemState * newState
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return 0;
}


extern "C"  void __cdecl _CrtMemDumpAllObjectsSince(
        const _CrtMemState * state
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}


extern "C"  int __cdecl _CrtDumpMemoryLeaks(
        void
        )
{
  // It seems that debug static MFC use this method so that
  // we can't just assert(0);
#if !defined(_WINDLL) && !defined(_USRDLL) && defined(_MFC_VER)
  // Can't use Debug C Runtime heap routines with rxheap.lib
  // Since ARX apps using smartheap memory facility, an attempt
  // to dump memory leaks is just a noop.
  assert(0);
#endif
  return 0;
}

extern "C" void __cdecl _CrtMemDumpStatistics(
        const _CrtMemState * state
        )
{
  // Can't use Debug C Runtime heap routines with rxheap.lib
  assert(0);
  return;
}

#endif // _debug of c runtime routines








