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
// server.CPP 
//
// DESCRIPTION:
//
// This file contains the code for COM/OLE support
// 

#include "windows.h"
#include "objbase.h"
#include "..\poly.h"
#include "polyolea.h" // generated from ODL file
#include "cpoly.h"
#include "cpolyapp.h"
#include "rxregsvc.h"


static ULONG ulObjects = 0;
static ULONG ulLocks = 0;

ULONG DllServerGetNumberOfObjects(void)
{
  return ulObjects;
}

ULONG DllServerGetNumberOfLocks(void)
{
  return ulLocks;
}

void DllServerIncrementNumberOfObjects(void)
{
  ulObjects++;
}

void DllServerDecrementNumberOfObjects(void)
{
  ulObjects--;
}

void DllServerIncrementNumberOfLocks(void)
{
  ulLocks++;
}

void DllServerDecrementNumberOfLocks(void)
{
  ulLocks--;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv)
{
  HRESULT hr = NOERROR;
  LPVOID pvClsFactory = NULL;

  // Check for supported interfaces
  if (!IsEqualIID(riid, IID_IUnknown) && !IsEqualIID(riid, IID_IClassFactory))
    return ResultFromScode(E_NOINTERFACE);

  // Return the class factory for the requested class
  *ppv = NULL;
  
  if (IsEqualCLSID(rclsid, CLSID_CAsdkPoly))
    pvClsFactory = new CAsdkPolyClassFactory;
  else if (IsEqualCLSID(rclsid, CLSID_CAsdkPolyApp))
    pvClsFactory = new CAsdkPolyAppFactory;
  else
    return E_FAIL;

  if (pvClsFactory == NULL)
    return ResultFromScode(E_OUTOFMEMORY);

  hr = ((LPUNKNOWN) pvClsFactory)->QueryInterface(riid, ppv);
  if (FAILED(hr))
  {
    delete pvClsFactory;
    pvClsFactory = NULL;
  }
  return hr;
}

STDAPI DllCanUnloadNow(void)
{
  // Unload if no locks and no objects.
  SCODE sc = (0L == DllServerGetNumberOfObjects() && 0L == DllServerGetNumberOfLocks()) ? S_OK : S_FALSE;
  return ResultFromScode(sc);
}


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD ulReason, LPVOID pvReserved)
{
  switch (ulReason)
  {
  case DLL_PROCESS_ATTACH:

    // check if this ARX apps is loaded or not.
    if (!acrxServiceIsRegistered("ASDK_POLYSAMP"))
    {
        if (acrxLoadModule("polysamp.arx", 1) == FALSE)
            return FALSE; // can't continue the loading process. 
    }

    break;

  case DLL_PROCESS_DETACH:
    break;

  case DLL_THREAD_ATTACH:
    break;

  case DLL_THREAD_DETACH:
    break;
  }

  return TRUE;
}
////////////////////////////////////////////////////////////////////////////////
//
// CAsdkPolyAppFactory Class
//

CAsdkPolyAppFactory::CAsdkPolyAppFactory()
{
  m_ulRef = 0L;
}

CAsdkPolyAppFactory::~CAsdkPolyAppFactory()
{
}

STDMETHODIMP_(ULONG) CAsdkPolyAppFactory::AddRef(void)
{
  return ++m_ulRef;
}

STDMETHODIMP_(ULONG) CAsdkPolyAppFactory::Release(void)
{
  if (m_ulRef == 1)
  {
    delete this;
    return 0L;
  }
  else
    return --m_ulRef;
}

STDMETHODIMP CAsdkPolyAppFactory::QueryInterface(REFIID riid, LPVOID FAR *ppv) 
{
  *ppv = NULL;
  if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
    *ppv = (LPVOID) this;
  else
    return ResultFromScode(E_NOINTERFACE);

  ((LPUNKNOWN) *ppv)->AddRef();
  return NOERROR;
}

STDMETHODIMP CAsdkPolyAppFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR *ppvObj)
{
  HRESULT hr = NOERROR;
  CAsdkPolyApp *pObj = NULL;

  *ppvObj = NULL;
  if (pUnkOuter && !IsEqualIID(riid, IID_IUnknown))
    return ResultFromScode(E_NOINTERFACE);

  pObj = new CAsdkPolyApp(pUnkOuter);
  if (pObj == NULL)
    return ResultFromScode(E_OUTOFMEMORY);

  // AddRef to prevent object from being deleted
  pObj->AddRef();

  hr = pObj->InitNew();
  if (FAILED(hr)) goto exit;

  hr = pObj->QueryInterface(riid, ppvObj);
  if (FAILED(hr)) goto exit;

  pObj->Release();

exit:
  if (FAILED(hr))
  {
    delete pObj;
    pObj = NULL;
  }
  return hr;
}

STDMETHODIMP CAsdkPolyAppFactory::LockServer(BOOL fLock)
{
  if (fLock)
    DllServerIncrementNumberOfLocks();
  else
    DllServerDecrementNumberOfLocks();

  return NOERROR;
}


////////////////////////////////////////////////////////////////////////////////
//
// CAsdkPolyClassFactory Class
//

CAsdkPolyClassFactory::CAsdkPolyClassFactory()
{
  m_ulRef = 0L;
}

CAsdkPolyClassFactory::~CAsdkPolyClassFactory()
{
}

STDMETHODIMP_(ULONG) CAsdkPolyClassFactory::AddRef(void)
{
  return ++m_ulRef;
}

STDMETHODIMP_(ULONG) CAsdkPolyClassFactory::Release(void)
{
  if (m_ulRef == 1)
  {
    delete this;
    return 0L;
  }
  else
    return --m_ulRef;
}

STDMETHODIMP CAsdkPolyClassFactory::QueryInterface(REFIID riid, LPVOID FAR *ppv) 
{
  *ppv = NULL;
  if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
    *ppv = (LPVOID) this;
  else
    return ResultFromScode(E_NOINTERFACE);

  ((LPUNKNOWN) *ppv)->AddRef();
  return NOERROR;
}

STDMETHODIMP CAsdkPolyClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR *ppvObj)
{
  HRESULT hr = NOERROR;
  CAsdkPoly *pObj = NULL;

  *ppvObj = NULL;
  if (pUnkOuter && !IsEqualIID(riid, IID_IUnknown))
    return ResultFromScode(E_NOINTERFACE);

  pObj = new CAsdkPoly(pUnkOuter);
  if (pObj == NULL)
    return ResultFromScode(E_OUTOFMEMORY);

  // AddRef to prevent object from being deleted
  pObj->AddRef();

  hr = pObj->InitNew();
  if (FAILED(hr)) goto exit;

  hr = pObj->QueryInterface(riid, ppvObj);
  if (FAILED(hr)) goto exit;

  pObj->Release();

exit:
  if (FAILED(hr))
  {
    delete pObj;
    pObj = NULL;
  }
  return hr;
}

STDMETHODIMP CAsdkPolyClassFactory::LockServer(BOOL fLock)
{
  if (fLock)
    DllServerIncrementNumberOfLocks();
  else
    DllServerDecrementNumberOfLocks();

  return NOERROR;
}



