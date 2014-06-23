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
// Use this file with rxdbgheap.cpp to make duplicate symbol errors
// gone away when rxheap.lib is used.
// 
// When you use rxheap.lib, you can't use anykind of MFC memory
// debugging facility at all.
//
// Note: _AFX_NO_DEBUG_CRT should not be defined. If it's defined,
//       you'll encounter duplicate definitions as before.
//
// Warning: this file hasn't been tested troughly.
// Please modify the file accordingly, or not use the file at all,
// if you find any problem.


#include "afxwin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Debug memory globals and implementation helpers

#ifdef _DEBUG       // most of this file is for debugging

/////////////////////////////////////////////////////////////////////////////
// test allocation routines

void* PASCAL CObject::operator new(size_t nSize)
{
	return ::operator new(nSize);
}

void PASCAL CObject::operator delete(void* p)
{
	free(p);
}


#ifndef _AFX_NO_DEBUG_CRT

void* AFX_CDECL operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

void* PASCAL
CObject::operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	return ::operator new(nSize, _CLIENT_BLOCK, lpszFileName, nLine);
}

void* AFXAPI AfxAllocMemoryDebug(size_t nSize, BOOL bIsObject,  LPCSTR lpszFileName, int nLine)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
  return 0;
}

void AFXAPI AfxFreeMemoryDebug(void* pbData, BOOL bIsObject)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
}

/////////////////////////////////////////////////////////////////////////////
// allocation failure hook, tracking turn on

BOOL AFXAPI _AfxDefaultAllocHook(size_t, BOOL, LONG)
{ 
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
  return TRUE;
}

static AFX_ALLOC_HOOK pfnAllocHook = _AfxDefaultAllocHook;

static _CRT_ALLOC_HOOK pfnCrtAllocHook = NULL;
int __cdecl _AfxAllocHookProxy(int nAllocType, void * pvData, size_t nSize,
	int nBlockUse, long lRequest, const char * szFilename, int nLine)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);

	return FALSE;
}

AFX_ALLOC_HOOK AFXAPI AfxSetAllocHook(AFX_ALLOC_HOOK pfnNewHook)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
	return NULL;
}

// This can be set to TRUE to override all AfxEnableMemoryTracking calls,
// allowing all allocations, even MFC internal allocations to be tracked.
BOOL _afxMemoryLeakOverride = FALSE;

BOOL AFXAPI AfxEnableMemoryTracking(BOOL bTrack)
{
  // Can't use AFX debug memory routines with rxheap.lib
  // Since ARX apps using smartheap memory facility, an attempt
  // to turn on/off AFX memory tracking is basically a no-op.
  // It seems that debug static MFC use this method so that
  // we can't just assert(0);
  // ASSERT(0);
  return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// stop on a specific memory request

// Obsolete API
void AFXAPI AfxSetAllocStop(LONG lRequestNumber)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
}

BOOL AFXAPI AfxCheckMemory()
  // check all of memory (look for memory tromps)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
  return FALSE;
}

// -- true if block of exact size, allocated on the heap
// -- set *plRequestNumber to request number (or 0)
BOOL AFXAPI AfxIsMemoryBlock(const void* pData, UINT nBytes,
		LONG* plRequestNumber)
{
  // Can't use AFX debug memory routines with rxheap.lib
  ASSERT(0);
  return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMemoryState

CMemoryState::CMemoryState()
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

void CMemoryState::UpdateData()
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

// fills 'this' with the difference, returns TRUE if significant
BOOL CMemoryState::Difference(const CMemoryState& oldState,
		const CMemoryState& newState)
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
  return FALSE;
}

void CMemoryState::DumpStatistics() const
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

// -- fill with current memory state
void CMemoryState::Checkpoint()
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

// Dump objects created after this memory state was checkpointed
// Will dump all objects if this memory state wasn't checkpointed
// Dump all objects, report about non-objects also
// List request number in {}
void CMemoryState::DumpAllObjectsSince() const
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

/////////////////////////////////////////////////////////////////////////////
// Enumerate all objects allocated in the diagnostic memory heap

struct _AFX_ENUM_CONTEXT
{
	void (*m_pfn)(CObject*,void*);
	void* m_pContext;
};

static void _AfxDoForAllObjectsProxy(void* pObject, void* pContext)
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

void AFXAPI
AfxDoForAllObjects(void (AFX_CDECL *pfn)(CObject*, void*), void* pContext)
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
}

/////////////////////////////////////////////////////////////////////////////
// Automatic debug memory diagnostics

BOOL AFXAPI AfxDumpMemoryLeaks()
{
  // Can't use AFX debug memory facility with rxheap.lib
  ASSERT(0);
  return FALSE;
}

#endif // _AFX_NO_DEBUG_CRT
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// Non-diagnostic memory routines

int AFX_CDECL AfxNewHandler(size_t /* nSize */)
{
	AfxThrowMemoryException();
	return 0;
}

#pragma warning(disable: 4273)

_PNH AFXAPI AfxGetNewHandler(void)
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	return pState->m_pfnNewHandler;
}

_PNH AFXAPI AfxSetNewHandler(_PNH pfnNewHandler)
{
	AFX_MODULE_THREAD_STATE* pState = AfxGetModuleThreadState();
	_PNH pfnOldHandler = pState->m_pfnNewHandler;
	pState->m_pfnNewHandler = pfnNewHandler;
	return pfnOldHandler;
}

static const _PNH _pfnUninitialized = (_PNH)-1;


/////////////////////////////////////////////////////////////////////////////
