// (C) Copyright 1990-2002 by Autodesk, Inc. 
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
// Written by Cyrille Fauvel
// Autodesk Developer Technical Services

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "dbxEntryPoint.h"
#ifdef __ATLCOM_H__
#include "dynpropmgr.h"
#endif

//-----------------------------------------------------------------------------
struct _ARXCOMMAND_ENTRY {
	const char *pszCmdGroupName ;
	const char *pszCmdGlobalName ;
	const char *pszCmdLocalName ;
	Adesk::Int32 commandFlags ;
    AcRxFunctionPtr pCmdFct ;
	AcEdUIContext *pUIContext ;
} ;

#pragma section("ARXCOMMAND$__a", read, shared)
#pragma section("ARXCOMMAND$__z", read, shared)
#pragma section("ARXCOMMAND$__m", read, shared)

extern "C" {
	__declspec(selectany) __declspec(allocate("ARXCOMMAND$__a")) _ARXCOMMAND_ENTRY* __pArxCmdMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("ARXCOMMAND$__z")) _ARXCOMMAND_ENTRY* __pArxCmdMapEntryLast =NULL ;
}

#define ACED_ARXCOMMAND_ENTRY_PRAGMA(group,globCmd) __pragma(comment(linker, "/include:___pArxCmdMap_" #group #globCmd)) ;

#define ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext) \
	__declspec(selectany) _ARXCOMMAND_ENTRY __ArxCmdMap_##group##globCmd = { _RXST(#group), _RXST(#globCmd), _RXST(#locCmd), cmdFlags, classname::##group ##globCmd, UIContext } ; \
	extern "C" __declspec(allocate("ARXCOMMAND$__m")) __declspec(selectany) _ARXCOMMAND_ENTRY* const __pArxCmdMap_##group##globCmd = &__ArxCmdMap_##group##globCmd ; \
	ACED_ARXCOMMAND_ENTRY_PRAGMA(group, globCmd)

//-----------------------------------------------------------------------------
struct _ADSSYMBOL_ENTRY {
	const char *pszName ;
	int (*fptr) () ;
	bool bRegFunc ;
} ;

#pragma section("ADSSYMBOL$__a", read, shared)
#pragma section("ADSSYMBOL$__z", read, shared)
#pragma section("ADSSYMBOL$__m", read, shared)

extern "C" {
	__declspec(selectany) __declspec(allocate("ADSSYMBOL$__a")) _ADSSYMBOL_ENTRY* __pAdsSymbolMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("ADSSYMBOL$__z")) _ADSSYMBOL_ENTRY* __pAdsSymbolMapEntryLast =NULL ;
}

#define ACED_ADSSYMBOL_ENTRY_PRAGMA(name) __pragma(comment(linker, "/include:___pAdsSymbolMap_" #name)) ;

#define ACED_ADSSYMBOL_ENTRY_AUTO(classname, name, regFunc) \
	__declspec(selectany) _ADSSYMBOL_ENTRY __AdsSymbolMap_##name = { _RXST(#name), classname::ads_ ##name, regFunc } ; \
	extern "C" __declspec(allocate("ADSSYMBOL$__m")) __declspec(selectany) _ADSSYMBOL_ENTRY* const __pAdsSymbolMap_##name = &__AdsSymbolMap_##name ; \
	ACED_ADSSYMBOL_ENTRY_PRAGMA(name)
#define ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) \
	__declspec(selectany) _ADSSYMBOL_ENTRY __AdsSymbolMap_##name = { _RXST("c:" #name), classname::ads_ ##name, regFunc } ; \
	extern "C" __declspec(allocate("ADSSYMBOL$__m")) __declspec(selectany) _ADSSYMBOL_ENTRY* const __pAdsSymbolMap_##name = &__AdsSymbolMap_##name ; \
	ACED_ADSSYMBOL_ENTRY_PRAGMA(name)

//-----------------------------------------------------------------------------
class AcRxArxApp : public AcRxDbxApp {

#ifdef __ATLCOM_H__
protected:
	AcRxDynPropManager *m_pDynPropManager ;
#endif

public:
#ifdef __ATLCOM_H__
	AcRxArxApp () : AcRxDbxApp (), m_pDynPropManager(NULL) {}
#else
	AcRxArxApp () : AcRxDbxApp () {}
#endif

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kInitAppMsg (pkt) ;
#ifdef __ATLCOM_H__
		//----- Register Dynamic Properties
		m_pDynPropManager =new AcRxDynPropManager ;
#endif
		//----- Register ARX comamnds
		_ARXCOMMAND_ENTRY **ppArxCmdMapEntryFirst =&__pArxCmdMapEntryFirst + 1 ;
		_ARXCOMMAND_ENTRY **ppArxCmdMapEntryLast =&__pArxCmdMapEntryLast ;
		for ( _ARXCOMMAND_ENTRY **ppEntry =ppArxCmdMapEntryFirst ; ppEntry < ppArxCmdMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				acedRegCmds->addCommand (
					(*ppEntry)->pszCmdGroupName,
					(*ppEntry)->pszCmdGlobalName,
					(*ppEntry)->pszCmdLocalName,
					(*ppEntry)->commandFlags,
					(*ppEntry)->pCmdFct,
					(*ppEntry)->pUIContext,
					-1,
					m_hdllInstance,
					NULL
				) ;
			}
		}
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadAppMsg (pkt) ;
#ifdef __ATLCOM_H__
		//----- Unregister Dynamic Properties
		if ( m_pDynPropManager != NULL ) {
			delete m_pDynPropManager ;
			m_pDynPropManager =NULL ;
		}
#endif
		_ARXCOMMAND_ENTRY **ppArxCmdMapEntryFirst =&__pArxCmdMapEntryFirst + 1 ;
		_ARXCOMMAND_ENTRY **ppArxCmdMapEntryLast =&__pArxCmdMapEntryLast ;
		for ( _ARXCOMMAND_ENTRY **ppEntry =ppArxCmdMapEntryFirst ; ppEntry < ppArxCmdMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				acedRegCmds->removeCmd (
					(*ppEntry)->pszCmdGroupName,
					(*ppEntry)->pszCmdGlobalName
				) ;
			}
		}
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kLoadDwgMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kLoadDwgMsg (pkt) ;
		//----- Register ADS Symbols
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryFirst =&__pAdsSymbolMapEntryFirst + 1 ;
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryLast =&__pAdsSymbolMapEntryLast ;
		int param =0 ;
		for ( _ADSSYMBOL_ENTRY **ppEntry =ppAdsSymbolMapEntryFirst ; ppEntry < ppAdsSymbolMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				acedDefun ((*ppEntry)->pszName, param) ;
				if ( (*ppEntry)->bRegFunc == true )
					acedRegFunc ((*ppEntry)->fptr, param) ;
				param++ ;
			}
		}
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadDwgMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadDwgMsg (pkt) ;
		//----- Unregister ADS Symbols
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryFirst =&__pAdsSymbolMapEntryFirst + 1 ;
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryLast =&__pAdsSymbolMapEntryLast ;
		int param =0 ;
		for ( _ADSSYMBOL_ENTRY **ppEntry =ppAdsSymbolMapEntryFirst ; ppEntry < ppAdsSymbolMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL )
				acedUndef ((*ppEntry)->pszName, param++) ;
		}
		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kInvkSubrMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kInvkSubrMsg (pkt) ;
		//----- Dispatch ADS symbol calls
		int param =acedGetFunCode () ;
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryFirst =&__pAdsSymbolMapEntryFirst + 1 ;
		_ADSSYMBOL_ENTRY **ppAdsSymbolMapEntryLast =&__pAdsSymbolMapEntryLast ;
		int paramIter =0 ;
		for ( _ADSSYMBOL_ENTRY **ppEntry =ppAdsSymbolMapEntryFirst ; ppEntry < ppAdsSymbolMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				if ( paramIter++ == param ) {
					(*((*ppEntry)->fptr)) () ;
					break ;
				}
			}
		}
		return (retCode) ;
	}
} ;
