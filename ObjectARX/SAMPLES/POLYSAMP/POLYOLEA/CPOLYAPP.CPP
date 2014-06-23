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
// CPOLYAPP.CPP 
//
// DESCRIPTION:
//
// This file contains the body of the class CAsdkPolyApp.

#include <afxwin.h>
#include <afxole.h>
#include "..\poly.h"
#include "..\command.h"
#include "polyolea.h" // generated from ODL file
#include "cpolyapp.h"
#include "cpoly.h"
#include "oleaprot.h"

#include <stdlib.h>


//////////// Utility functions //////////////////

HRESULT ProcAcadBaseObject(TCHAR* entryName, LPUNKNOWN pUnk, AcDbObjectId& objId)
{
  HRESULT hr = NOERROR;
  LPACADBASEOBJECT pEntObj = NULL;

  hr = pUnk->QueryInterface(IID_IAcadBaseObject, (LPVOID*)&pEntObj);
  if (FAILED(hr))
  {
    return DISP_E_EXCEPTION;
  }

  hr = pEntObj->SetObjectId(objId, entryName); // insert it into space too.
  if (FAILED(hr))
  {
    pEntObj->Release();             
    return DISP_E_EXCEPTION;
  }

  hr = pEntObj->GetObjectId(&objId);
  if (FAILED(hr))
  {
    return DISP_E_EXCEPTION;
  }

  pEntObj->Release();
  return hr;
}            

HRESULT ProcAcDbProtocol(AcDbObjectId objId, AcAutoWrapCreate* wCreate, 
                         LPUNKNOWN pUnk, CLSID* pClsid)
{
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AcAutomationWrap *rapper = NULL;

  es = acdbOpenAcDbObject(pObj, objId, AcDb::kForRead);
  if (es != Acad::eOk)
  {
    return E_FAIL;
  }
  rapper = wCreate->CreateAutomationProtocol(pObj, pClsid);
  rapper->SetIUnknown(pObj, pUnk);
  pObj->close();

  return NOERROR;
}             

void EraseAcDbObjectOnError(AcDbObjectId objId)
{
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;

  if ((es = acdbOpenAcDbObject(pObj, objId, AcDb::kForWrite)) == Acad::eOk)
  {
    es = pObj->erase();
    pObj->close();
  }
}       

HRESULT ConvertUnicodeToAnsi(LPWSTR pszWStr, LPSTR* ppszCStr)
{
  *ppszCStr = NULL;

  UINT uStrLen = WideCharToMultiByte(CP_ACP, NULL, pszWStr, -1, *ppszCStr, 0, NULL, NULL);
  *ppszCStr = new char[uStrLen + 1];
  if (! *ppszCStr)
    return ResultFromScode(E_OUTOFMEMORY);

  if (WideCharToMultiByte(CP_ACP, NULL, pszWStr, -1, *ppszCStr, uStrLen, NULL, NULL))
    return NOERROR;
  else
    return E_FAIL;
}                    
//////////// End of Utility functions //////////////////


//*************************************************************************
// COM and OLE automation support
//*************************************************************************

//
// CAsdkPolyApp Class
//
CAsdkPolyApp::CAsdkPolyApp(LPUNKNOWN pUnkOuter)
{
  m_pUnkOuter = pUnkOuter ? pUnkOuter : (LPUNKNOWN) (LPVOID) this;
  m_ulRef = 0L;
  m_pStdDispatch = NULL;

  DllServerIncrementNumberOfObjects();
}

CAsdkPolyApp::~CAsdkPolyApp()
{
  if (m_pStdDispatch)
    m_pStdDispatch->Release();
  DllServerDecrementNumberOfObjects();
}

HRESULT CAsdkPolyApp::InitNew()
{
  HRESULT hr = NOERROR;
  LPTYPELIB pTypeLib = NULL;
  LPTYPEINFO pTypeInfo = NULL;

  hr = LoadRegTypeLib(LIBID_AsdkPolySamp, 1, 0, 0x0, &pTypeLib);
  if (FAILED(hr))
  {
    hr = LoadTypeLib(OLESTR("POLYOLEA.tlb"), &pTypeLib);
    if (FAILED(hr))
      return hr;
  }

  if (SUCCEEDED(hr))
  {
    hr = pTypeLib->GetTypeInfoOfGuid(IID_IAsdkPolyApp, &pTypeInfo);
    if (FAILED(hr)){
		 if (pTypeLib)
			pTypeLib->Release();
		  if (pTypeInfo)
			pTypeInfo->Release();
	}

    hr = CreateStdDispatch(m_pUnkOuter, &m_xAsdkPolyApp, pTypeInfo, &m_pStdDispatch);

  }


  if (pTypeLib)
    pTypeLib->Release();
  if (pTypeInfo)
    pTypeInfo->Release();
  return hr;
}

STDMETHODIMP_(ULONG) CAsdkPolyApp::AddRef(void)
{
  return ++m_ulRef;
}

STDMETHODIMP_(ULONG) CAsdkPolyApp::Release(void)
{
  if (m_ulRef == 1)
  {
    delete this;
    return 0L;
  }
  else
    return --m_ulRef;
}

STDMETHODIMP CAsdkPolyApp::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
  *ppv = NULL;
  
  if (IsEqualIID(riid, IID_IUnknown))
    *ppv = (LPVOID) this;
  else if (IsEqualIID(riid, IID_IAsdkPolyApp) || IsEqualIID(riid, IID_IDispatch))
    *ppv = (LPVOID) &m_xAsdkPolyApp;
  else
    return ResultFromScode(E_NOINTERFACE);

  ((LPUNKNOWN) *ppv)->AddRef();
  return NOERROR;
}

STDMETHODIMP_(ULONG) CAsdkPolyApp::IAsdkPolyAppImp::AddRef(void)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  return pThis->m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) CAsdkPolyApp::IAsdkPolyAppImp::Release(void)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  return pThis->m_pUnkOuter->Release();
}

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::QueryInterface(REFIID riid, LPVOID FAR* ppv)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  return pThis->m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::GetTypeInfoCount(UINT FAR* pctinfo)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  HRESULT hr = NOERROR;
  LPDISPATCH pDisp = NULL;
  hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp);
  if (SUCCEEDED(hr))
  {
    hr = pDisp->GetTypeInfoCount(pctinfo);
    pDisp->Release();
  }
  return hr;
}

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::GetTypeInfo(UINT itinfo, LCID lcid,
  ITypeInfo FAR* FAR* pptinfo)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  HRESULT hr = NOERROR;
  LPDISPATCH pDisp = NULL;
  hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp);
  if (SUCCEEDED(hr))
  {
    hr = pDisp->GetTypeInfo(itinfo, lcid, pptinfo);
    pDisp->Release();
  }
  return hr;
}

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::GetIDsOfNames(REFIID riid,
  OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgdispid)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  HRESULT hr = NOERROR;
  LPDISPATCH pDisp = NULL;
  hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp);
  if (SUCCEEDED(hr))
  {
    hr = pDisp->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);
    pDisp->Release();
  }
  return hr;
}

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::Invoke(DISPID dispidMember, REFIID riid,
  LCID lcid, WORD wFlags, DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
  EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr)
{
  GET_pThis(CAsdkPolyApp, m_xAsdkPolyApp);
  HRESULT hr = NOERROR;
  LPDISPATCH pDisp = NULL;
  hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp);
  if (SUCCEEDED(hr))
  {
    hr = pDisp->Invoke(dispidMember, riid, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
    pDisp->Release();
  }
  return hr;
}



/* Poly Application method  */
STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::CreatePoly()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    polyCommand();
    
    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}


STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::CreateDragPoly()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    dragPolyCommand();

    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}
STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::EditPoly()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    polyeditCommand();
    
    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}
STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::TransactPoly()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    transactCommand();

    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}
STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::HilitPoly()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    hilitPoly();
    
    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}
STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::HilitSolid()
{
    if (acedSetOLELock(5) != Adesk::kTrue)
        return E_FAIL;

    hilitSolid();

    acedPostCommandPrompt(); 
    acedClearOLELock(5);
    return NOERROR;
}

extern CWinApp* acedGetAcadWinApp(); 

STDMETHODIMP CAsdkPolyApp::IAsdkPolyAppImp::AddPoly(BSTR entryName, BSTR bstrName, 
                                                    int nSide ,
                                                    SAFEARRAY FAR* ptCenter, 
                                                    SAFEARRAY FAR* ptStart, 
                                                    LPDISPATCH FAR* pObjDisp)
{

    *pObjDisp = NULL;

    AcAutoWrapCreate *wCreate = GET_OLEAUTO_CREATE_PROTO(acdbCurDwg());
    if (wCreate == NULL)  // arx application must not be loaded
        return  E_FAIL;

    HRESULT hr = NOERROR;

    CLSID clsid = CLSID_CAsdkPoly;
    LPUNKNOWN pUnk = NULL;
    AcDbObjectId objId = AcDbObjectId::kNull;
    LPRETRIEVEAPPLICATION pRetApp = NULL;
    LPDISPATCH pAppDisp = acedGetAcadWinApp()->GetIDispatch(TRUE);
    IAsdkPoly *pPoly;

    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (LPVOID*)&pUnk);
    if (FAILED(hr))
       return hr;

    TCHAR* pszName = NULL;
    hr = ConvertUnicodeToAnsi(entryName, &pszName);
      if (FAILED(hr))
    return hr;

    hr = ProcAcadBaseObject(pszName,  pUnk, objId);
    delete [] pszName;

    if (FAILED(hr)) 
        goto exit;

    hr = pUnk->QueryInterface(IID_IRetrieveApplication, (LPVOID*)&pRetApp);
    if (SUCCEEDED(hr))
    {
      hr = pRetApp->SetApplicationObject(pAppDisp);
      if (FAILED(hr))
      {
        goto exit;
      }
    }
    else
    {
      pRetApp = NULL;
    }

    hr = ProcAcDbProtocol( objId, wCreate, pUnk, &clsid);
    if (FAILED(hr)) goto exit;

    hr = pUnk->QueryInterface(IID_IAsdkPoly, (LPVOID*)&pPoly);
    if (FAILED(hr))
        goto exit;
        // set the args
    hr = pPoly->initializeAll(bstrName, nSide, ptCenter, ptStart);
    pPoly->Release();
    if (FAILED(hr))
        goto exit;

    hr = pUnk->QueryInterface(IID_IDispatch, (LPVOID*) pObjDisp);
    if (FAILED(hr))
    {
      *pObjDisp = NULL;
    }

exit:
  if (FAILED(hr)) EraseAcDbObjectOnError(objId);
  if (pUnk) pUnk->Release();
  if (pRetApp) pRetApp->Release();
  return hr;
}
