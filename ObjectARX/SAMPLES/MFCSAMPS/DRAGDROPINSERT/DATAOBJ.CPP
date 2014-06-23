// (C) Copyright 1996 by Autodesk, Inc. 
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

#include "stdafx.h"

// IDataObject methods
CDataObj::CDataObj(CString fileName)
{
    m_cRef = 0;
    m_rectAsText = GlobalAlloc(GHND,fileName.GetLength() +1);

    char *pstr = (char*) GlobalLock(m_rectAsText);
    strcpy(pstr, fileName);
    GlobalUnlock(m_rectAsText);
}

CDataObj::~CDataObj()
{
    if (m_rectAsText != NULL)
	    GlobalFree(m_rectAsText);
}

STDMETHODIMP 
CDataObj::GetData(FORMATETC * pFormatetc,	//Pointer to the FORMATETC structure 
                        STGMEDIUM * pmedium)	//Pointer to the STGMEDIUM structure 
{

	char *pstrDest;
	char *pstrSrc;

	if (!(DVASPECT_CONTENT & pFormatetc->dwAspect))
		return  ResultFromScode(DATA_E_FORMATETC);
	if (pFormatetc->cfFormat != CF_TEXT)
		return  ResultFromScode(DATA_E_FORMATETC);
	if (!(pFormatetc->tymed & TYMED_HGLOBAL))
		return  ResultFromScode(DATA_E_FORMATETC);

	pmedium->tymed = TYMED_HGLOBAL;
	pmedium->hGlobal= GlobalAlloc(GHND, GlobalSize(m_rectAsText));
	pmedium->pUnkForRelease = NULL;
	pstrDest = (char*) GlobalLock(pmedium->hGlobal);
	pstrSrc  = (char*) GlobalLock(m_rectAsText);
	memcpy(pstrDest, pstrSrc, GlobalSize(m_rectAsText));
	GlobalUnlock(m_rectAsText);
	GlobalUnlock(pmedium->hGlobal);

	return NOERROR;
}
 
STDMETHODIMP 
CDataObj::GetDataHere(
    FORMATETC * pFormatetc,	//Pointer to the FORMATETC structure
    STGMEDIUM * pmedium)	//Pointer to the STGMEDIUM structure 
{
    return ResultFromScode(E_NOTIMPL);
}
   	
STDMETHODIMP 
CDataObj::QueryGetData(
    FORMATETC * pFormatetc)	//Pointer to the FORMATETC structure
{
	if (!(DVASPECT_CONTENT &  pFormatetc->dwAspect))
		return ResultFromScode(DATA_E_FORMATETC);
	if (pFormatetc->cfFormat != CF_TEXT)
		return ResultFromScode(DATA_E_FORMATETC);
	if (!(pFormatetc->tymed & TYMED_HGLOBAL))
		return ResultFromScode(DATA_E_FORMATETC);
	return NOERROR;
}

STDMETHODIMP 
CDataObj::GetCanonicalFormatEtc(
    FORMATETC * pFormatetcIn,	//Pointer to the FORMATETC structure
    FORMATETC * pFormatetcOut)	//Pointer to the canonical equivalent FORMATETC structure   
{
    pFormatetcOut = NULL;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
}

STDMETHODIMP 
CDataObj::SetData(
    FORMATETC * pFormatetc,	//Pointer to the FORMATETC structure
    STGMEDIUM * pmedium,	//Pointer to STGMEDIUM structure
    BOOL fRelease)      	//Indicates which object owns the storage medium after the call is completed
{
    // support only CF_TEXT
    if (pFormatetc->cfFormat != CF_TEXT)
        return ResultFromScode(E_FAIL);

    if (pFormatetc->tymed != TYMED_HGLOBAL)
        return ResultFromScode(E_FAIL);
    if (m_rectAsText != NULL)
        GlobalFree(m_rectAsText);

    m_rectAsText = GlobalAlloc(GHND, GlobalSize(pmedium->hGlobal));
    char FAR *pstrDest = (char FAR*) GlobalLock(m_rectAsText);
    char FAR *pstrSrc = (char FAR*) GlobalLock(pmedium->hGlobal);

    memcpy(pstrDest, pstrSrc,GlobalSize(pmedium->hGlobal));
    
    if (fRelease)
        ReleaseStgMedium(pmedium);

    return NOERROR;

}

STDMETHODIMP 
CDataObj::EnumFormatEtc(
    DWORD dwDirection,	//Specifies a value from the enumeration DATADIR
    IEnumFORMATETC ** ppenumFormatetc)	//Indirect pointer to the new enumerator object	
{
     if (dwDirection != DATADIR_GET)
         return ResultFromScode(E_FAIL);

     SetDefFormatEtc(m_formatetc[0], CF_TEXT, TYMED_HGLOBAL);

     *ppenumFormatetc = new CEnumFormatEtc(1, &m_formatetc[0]);
                    	 
     (*ppenumFormatetc)->AddRef();

     return NOERROR;
}
 
STDMETHODIMP 
CDataObj::DAdvise(
    FORMATETC * pFormatetc,	//Pointer to data of interest to the advise sink
    DWORD advf,	                //Flags that specify how the notification takes place
    IAdviseSink * pAdvSink,	//Pointer to the advise sink
    DWORD * pdwConnection)	//Pointer to a token that identifies this connection
{
    return ResultFromScode(E_NOTIMPL);
}

STDMETHODIMP 
CDataObj::DUnadvise(
    DWORD dwConnection)	//Connection to remove
{
    return ResultFromScode(E_NOTIMPL);

}

STDMETHODIMP 
CDataObj::EnumDAdvise(
    IEnumSTATDATA ** ppenumAdvise)	//Indirect pointer 
{
    return ResultFromScode(E_NOTIMPL);
}


STDMETHODIMP_(DWORD)
CDataObj::AddRef(void)
{
    return ++m_cRef;
}

STDMETHODIMP_(DWORD)
CDataObj::Release(void)
{
    if( 0 != --m_cRef)
      return m_cRef;

    delete this;
    return 0;

}

inline STDMETHODIMP  
CDataObj::QueryInterface(REFIID riid, void** ppv)
{

    *ppv=NULL;

   if (IsEqualIID(IID_IUnknown,riid))
	   *ppv=this;
   else if (IsEqualIID(IID_IDataObject,riid))
	   *ppv = (IDataObject*)this;

   if (NULL!=*ppv)
   {
	  ((LPUNKNOWN)*ppv)->AddRef();
	  return NOERROR;
   }

    return ResultFromScode(E_NOINTERFACE);

}



////
