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
// CPOLY.CPP 
//
// DESCRIPTION:
//
// This file contains the body of the class CAsdkPoly.

#include <afxwin.h>
#include <afxole.h>
#include "..\poly.h"
#include "polyolea.h" // generated from ODL file
#include "cpoly.h"
#include "oleaprot.h"

#include <stdlib.h>

#include "assert.h"
#include "math.h"

#include "gepnt3d.h"
#include "gevec3d.h"

#include "dbsymtb.h"

// {33C36D91-E034-11cf-9B81-080009B133D5}
// DEFINE_GUID(CLSID_CAsdkPoly, 
// 0x33c36d91, 0xe034, 0x11cf, 0x9b, 0x81, 0x8, 0x0, 0x9, 0xb1, 0x33, 0xd5);


//*************************************************************************
// COM and OLE automation support
//*************************************************************************

// The following three are utility functions

//
// Create a one dimensional safe array of given type and size.
//
HRESULT CreateSafeArray(VARTYPE vt, ULONG numElems, SAFEARRAY** pArray)
{
  SAFEARRAYBOUND rgsaBound;
  rgsaBound.lLbound = 0L;
  rgsaBound.cElements = numElems;

  *pArray = SafeArrayCreate(vt, 1, &rgsaBound);
  if (! *pArray)
  {
    return ResultFromScode(E_OUTOFMEMORY);
  }
  return NOERROR;
}

//
// Caller allocates memory for the safearray array which should accommodate
// at least three doubles.
//
HRESULT DoubleArrayPointToSafeArrayPoint(double* dPt, SAFEARRAY* sPt)
{
  HRESULT hr = NOERROR;

  if (SafeArrayGetDim(sPt) != 1)
  {
    return ResultFromScode(E_INVALIDARG);
  }

  long lLbound;
  long lUbound;
  SafeArrayGetLBound(sPt, 1, &lLbound);
  SafeArrayGetUBound(sPt, 1, &lUbound);

  if ((lUbound - lLbound + 1) != 3)
  {
    return ResultFromScode(E_INVALIDARG);
  }

  for (long i = 0; i < 3; i++)
    hr = SafeArrayPutElement(sPt, &i, &dPt[i]);

  return hr;
}

//
// Caller allocates memory for the double array which should accommodate
// at least three doubles.
//
HRESULT SafeArrayPointToDoubleArrayPoint(SAFEARRAY* sPt, double* dPt)
{
  HRESULT hr = NOERROR;

  if (SafeArrayGetDim(sPt) != 1)
  {
    return ResultFromScode(E_INVALIDARG);
  }

  long lLbound;
  long lUbound;
  SafeArrayGetLBound(sPt, 1, &lLbound);
  SafeArrayGetUBound(sPt, 1, &lUbound);

  if ((lUbound - lLbound + 1) != 3)
  {
    return ResultFromScode(E_INVALIDARG);
  }

  for (long i = 0; i < 3; i++)
    hr = SafeArrayGetElement(sPt, &i, &dPt[i]);

  return hr;
}


//
// CAsdkPoly Class
//
CAsdkPoly::CAsdkPoly(LPUNKNOWN pUnkOuter)
{
  m_pUnkOuter = pUnkOuter ? pUnkOuter : (LPUNKNOWN) (LPVOID) this;
  m_ulRef = 0L;
  m_pStdDispatch = NULL;
  m_pAppDisp = NULL; 

  DllServerIncrementNumberOfObjects();
}

CAsdkPoly::~CAsdkPoly()
{
  if (m_pStdDispatch)
    m_pStdDispatch->Release();
  if (m_pAppDisp)
    m_pAppDisp->Release();

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AcAutomationWrap *rapper;

  es = acdbOpenAcDbObject(pObj, m_objId, AcDb::kForRead, Adesk::kTrue);

  /* Get the automation protocol from the AutoCAD,
     and let AutoCAD know that this object will be gone
     by the way of setting the IUnknown hold by AutoCAD to NULL*/
  if (es == Acad::eOk)
  {
    rapper = GET_AUTOMATION_PROTOCOL(pObj);

    if (rapper) // should always be non-NULL
      rapper->SetIUnknown(pObj, NULL);
  
    pObj->close();
  }
  DllServerDecrementNumberOfObjects();
}

HRESULT CAsdkPoly::InitNew()
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
    hr = pTypeLib->GetTypeInfoOfGuid(IID_IAsdkPoly, &pTypeInfo);
    if (FAILED(hr)){
		 if (pTypeLib)
			pTypeLib->Release();
		  if (pTypeInfo)
			pTypeInfo->Release();
	}

    hr = CreateStdDispatch(m_pUnkOuter, &m_xAsdkPoly, pTypeInfo, &m_pStdDispatch);

  }


//entity common CoCreateInstance
  LPUNKNOWN pUnk = NULL;
  
  hr = CoCreateInstance(CLSID_CEntityCommon, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown,
                        (LPVOID*)&pUnk);
  if (FAILED(hr)) goto exit;

  hr = pUnk->QueryInterface(IID_IEntityCommon, (LPVOID*)&m_pEntComm);
  if (FAILED(hr))
  {
    m_pStdDispatch->Release();
    m_pStdDispatch = NULL;
  }

exit:
  if (pUnk) pUnk->Release();
  if (pTypeLib)
    pTypeLib->Release();
  if (pTypeInfo)
    pTypeInfo->Release();
  return hr;
}

STDMETHODIMP_(ULONG) CAsdkPoly::AddRef(void)
{
  return ++m_ulRef;
}

STDMETHODIMP_(ULONG) CAsdkPoly::Release(void)
{
  if (m_ulRef == 1)
  {
    delete this;
    return 0L;
  }
  else
    return --m_ulRef;
}

STDMETHODIMP CAsdkPoly::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
  *ppv = NULL;
  
  if (IsEqualIID(riid, IID_IUnknown))
    *ppv = (LPVOID) this;
  else if (IsEqualIID(riid, IID_IAsdkPoly) || IsEqualIID(riid, IID_IDispatch))
    *ppv = (LPVOID) &m_xAsdkPoly;
  else if (IsEqualIID(riid, IID_IAcadBaseObject))
    *ppv = (LPVOID) &m_xAcadBaseObject;
  else if (IsEqualIID(riid, IID_IRetrieveApplication))
    *ppv = (LPVOID) &m_xRetrieveApplication;
  else
    return ResultFromScode(E_NOINTERFACE);

  ((LPUNKNOWN) *ppv)->AddRef();
  return NOERROR;
}

STDMETHODIMP_(ULONG) CAsdkPoly::IAsdkPolyImp::AddRef(void)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  return pThis->m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) CAsdkPoly::IAsdkPolyImp::Release(void)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  return pThis->m_pUnkOuter->Release();
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::QueryInterface(REFIID riid, LPVOID FAR* ppv)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  return pThis->m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::GetTypeInfoCount(UINT FAR* pctinfo)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
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

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::GetTypeInfo(UINT itinfo, LCID lcid,
  ITypeInfo FAR* FAR* pptinfo)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
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

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::GetIDsOfNames(REFIID riid,
  OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgdispid)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
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

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Invoke(DISPID dispidMember, REFIID riid,
  LCID lcid, WORD wFlags, DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
  EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
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


//////////////////////////////////////////////////////////////////////////
// implement all the entity common methods 
//////////////////////////////////////////////////////////////////////////

// The following macro implements the Entitiy Comman methods.
// Use it when you are already comfatable with it. 
// IMPLEMENT_ENTITYCOMMON_METHODS(AsdkPoly, AsdkPoly, CLSID_CAsdkPoly)

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Handle(BSTR FAR* handle)
  {
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_Handle(pThis->m_objId, pThis->m_pStdDispatch, 
      handle); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_EntityName(BSTR FAR* className) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_EntityName(pThis->m_objId, pThis->m_pStdDispatch, className); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Color(int FAR* color) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_Color(pThis->m_objId, pThis->m_pStdDispatch, color); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Color(int color) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->put_Color(pThis->m_objId, pThis->m_pStdDispatch, color); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Layer(BSTR FAR* layer) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_Layer(pThis->m_objId, pThis->m_pStdDispatch, layer); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Layer(BSTR layer) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->put_Layer(pThis->m_objId, pThis->m_pStdDispatch, layer); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Linetype(BSTR FAR* lineType) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_Linetype(pThis->m_objId, pThis->m_pStdDispatch, lineType); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Linetype(BSTR lineType) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->put_Linetype(pThis->m_objId, pThis->m_pStdDispatch, lineType); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_LinetypeScale(double FAR* ltScale) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_LinetypeScale(pThis->m_objId, pThis->m_pStdDispatch, ltScale); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_LinetypeScale(double ltScale) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->put_LinetypeScale(pThis->m_objId, pThis->m_pStdDispatch, ltScale); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Visible(VARIANT_BOOL FAR* bVisible) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->get_Visible(pThis->m_objId, pThis->m_pStdDispatch, bVisible); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Visible(VARIANT_BOOL bVisible) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->put_Visible(pThis->m_objId, pThis->m_pStdDispatch, bVisible); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::GetXData(BSTR name, VARIANT FAR* type, VARIANT FAR* data) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->GetXData(pThis->m_objId, pThis->m_pStdDispatch, name, type, data); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::SetXData(SAFEARRAY FAR* type, SAFEARRAY FAR* data) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->SetXData(pThis->m_objId, pThis->m_pStdDispatch, type, data); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::ArrayPolar(int numObjs, double fillAngle, 
    SAFEARRAY FAR* basePoint, SAFEARRAY FAR* FAR* pArrayObjs) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->ArrayPolar( pThis->m_objId, pThis->m_pStdDispatch ,CLSID_CAsdkPoly,
      pThis->m_pAppDisp, numObjs, fillAngle, basePoint, pArrayObjs); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::ArrayRectangular(int numRows, int numCols, 
    int numLvls, double disRows, double disCols, double disLvls, SAFEARRAY FAR* FAR* pArrayObjs) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->ArrayRectangular( pThis->m_objId, pThis->m_pStdDispatch, CLSID_CAsdkPoly, 
      pThis->m_pAppDisp, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Highlight(VARIANT_BOOL bFlag) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Highlight(pThis->m_objId, pThis->m_pStdDispatch, bFlag); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Copy(LPDISPATCH FAR* pCopyObj) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Copy( pThis->m_objId, pThis->m_pStdDispatch, CLSID_CAsdkPoly, pThis->m_pAppDisp, pCopyObj); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Erase(void) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    HRESULT hr = pThis->m_pEntComm->Erase(pThis->m_objId, pThis->m_pStdDispatch); 
    pThis->Release(); 
    return hr; 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Move(SAFEARRAY FAR* fromPoint, 
    SAFEARRAY FAR* toPoint) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Move(pThis->m_objId, pThis->m_pStdDispatch, fromPoint, toPoint); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Rotate(SAFEARRAY FAR* basePoint, 
    double rotationAngle) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Rotate(pThis->m_objId, pThis->m_pStdDispatch, basePoint, rotationAngle); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Rotate3d(SAFEARRAY FAR* point1, 
    SAFEARRAY FAR* point2, double rotationAngle) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Rotate3d(pThis->m_objId, pThis->m_pStdDispatch, point1, point2, rotationAngle); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Mirror(SAFEARRAY FAR* point1, 
    SAFEARRAY FAR* point2, LPDISPATCH FAR* pMirrorObj) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Mirror(pThis->m_objId, pThis->m_pStdDispatch, CLSID_CAsdkPoly, pThis->m_pAppDisp, 
      point1, point2, pMirrorObj); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Mirror3d(SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, 
    SAFEARRAY FAR* point3, LPDISPATCH FAR* pMirrorObj) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Mirror3d( pThis->m_objId, pThis->m_pStdDispatch, CLSID_CAsdkPoly, pThis->m_pAppDisp, 
      point1, point2, point3, pMirrorObj); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::ScaleEntity(SAFEARRAY FAR* basePoint, 
    double scaleFactor) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->ScaleEntity(pThis->m_objId, pThis->m_pStdDispatch, basePoint, scaleFactor); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::TransformBy(SAFEARRAY FAR* transMatrix) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->TransformBy(pThis->m_objId, pThis->m_pStdDispatch, transMatrix); 
  } 


  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::Update(void) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->Update(pThis->m_objId, pThis->m_pStdDispatch); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::GetBoundingBox(VARIANT FAR* minPoint, 
    VARIANT FAR* maxPoint) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->GetBoundingBox(pThis->m_objId, pThis->m_pStdDispatch, minPoint, maxPoint); 
  } 

  STDMETHODIMP CAsdkPoly::IAsdkPolyImp::IntersectWith(LPDISPATCH pEntity, 
    int option, SAFEARRAY FAR* FAR* intPoints) 
  { 
    GET_pThis(CAsdkPoly, m_xAsdkPoly); 
    return pThis->m_pEntComm->IntersectWith(pThis->m_objId, pThis->m_pStdDispatch, pEntity, option, intPoints); 
  } 

/// end of entity common methods 
// 

//////////////////////////////////////////////////////////////////////////
// Poly specific Interface Implementation
//////////////////////////////////////////////////////////////////////////

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_NumberOfSide(int FAR* nSide)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForRead, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    *nSide = pPoly->numSides();
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_NumberOfSide(int nSide)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    es = pPoly->setNumSides(nSide);
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Center(SAFEARRAY FAR* FAR* ptCenter)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForRead, Adesk::kFalse);

  AcGePoint3d p;
  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    p = pPoly->center();
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }

  double dPt[3];
  dPt[0] = p[0];
  dPt[1] = p[1];
  dPt[2] = p[2];

  HRESULT hr = NOERROR;
  hr = CreateSafeArray(VT_R8, 3, ptCenter);
  if (FAILED(hr)) return hr;

  hr = DoubleArrayPointToSafeArrayPoint(dPt, *ptCenter);
  return hr;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Center(SAFEARRAY FAR* ptCenter)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  HRESULT hr = NOERROR;
  double dPt[3];
  hr = SafeArrayPointToDoubleArrayPoint(ptCenter, dPt);
  if (FAILED(hr)) return hr;

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    AcGePoint3d p(dPt[0], dPt[1], dPt[2]);
    es = pPoly->setCenter(p);
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_StartPoint(SAFEARRAY FAR* FAR* ptStart)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForRead, Adesk::kFalse);

  AcGePoint3d p;
  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    p = pPoly->startPoint();
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }

  double dPt[3];
  dPt[0] = p[0];
  dPt[1] = p[1];
  dPt[2] = p[2];

  HRESULT hr = NOERROR;
  hr = CreateSafeArray(VT_R8, 3, ptStart);
  if (FAILED(hr)) return hr;

  hr = DoubleArrayPointToSafeArrayPoint(dPt, *ptStart);
  return hr;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_StartPoint(SAFEARRAY FAR* ptStart)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  HRESULT hr = NOERROR;
  double dPt[3];
  hr = SafeArrayPointToDoubleArrayPoint(ptStart, dPt);
  if (FAILED(hr)) return hr;

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    AcGePoint3d p(dPt[0], dPt[1], dPt[2]);
    es = pPoly->setStartPoint(p);
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Normal(SAFEARRAY FAR* FAR* vNormal)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForRead, Adesk::kFalse);

  AcGeVector3d n;
  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    n = pPoly->normal();
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }

  double dVec[3];
  dVec[0] = n[0];
  dVec[1] = n[1];
  dVec[2] = n[2];

  HRESULT hr = NOERROR;
  hr = CreateSafeArray(VT_R8, 3, vNormal);
  if (FAILED(hr)) return hr;

  hr = DoubleArrayPointToSafeArrayPoint(dVec, *vNormal);
  return hr;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Normal(SAFEARRAY FAR* vNormal)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  HRESULT hr = NOERROR;
  double dVec[3];
  hr = SafeArrayPointToDoubleArrayPoint(vNormal, dVec);
  if (FAILED(hr)) return hr;

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    AcGeVector3d n(dVec[0], dVec[1], dVec[2]);
    es = pPoly->setNormal(n);
    pPoly->close();
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::get_Name(BSTR FAR* bstrName)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForRead, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    int strLen = strlen(pPoly->name()) + 1;
    WCHAR* pWName = new WCHAR[strLen];
    if (! pWName)
    {
      pPoly->close();
      return E_OUTOFMEMORY;
    }
        
    MultiByteToWideChar(CP_ACP, NULL, pPoly->name(), -1, pWName, strLen);
    *bstrName = SysAllocString(pWName);

    pPoly->close();
    delete pWName;
  }
  else
  {
    pObj->close();
    return ResultFromScode(E_FAIL);
  }
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::put_Name(BSTR bstrName)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  UINT uStrLen = WideCharToMultiByte(CP_ACP, NULL, bstrName, -1, NULL, 0,
                       NULL, NULL);

  char* locName = new char[uStrLen+1];
  if (! locName) return ResultFromScode(E_OUTOFMEMORY);

  WideCharToMultiByte(CP_ACP, NULL, bstrName, -1, locName, uStrLen, NULL, NULL);
  locName[uStrLen] = '\0';

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
    es = pPoly->setName(locName);
    pPoly->close();
  }
  else
  {
    pObj->close();
	delete locName;
    return ResultFromScode(E_FAIL);
  }

  delete locName;
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAsdkPolyImp::initializeAll(BSTR bstrName, 
												   int nSide ,
												   SAFEARRAY FAR* ptCenter, 
												   SAFEARRAY FAR* ptStart)
{
  GET_pThis(CAsdkPoly, m_xAsdkPoly);
  double stPnt[3];
  HRESULT hr = NOERROR;

  hr = SafeArrayPointToDoubleArrayPoint(ptStart, stPnt);
  if (FAILED(hr)) return hr;

  double cenPnt[3];
  hr = SafeArrayPointToDoubleArrayPoint(ptCenter, cenPnt);
  if (FAILED(hr)) return hr;
  
  UINT uStrLen = WideCharToMultiByte(CP_ACP, NULL, bstrName, -1, NULL, 0,
                       NULL, NULL);
  char* locName = new char[uStrLen + 1];
  if (! locName) 
	  return ResultFromScode(E_OUTOFMEMORY);

  WideCharToMultiByte(CP_ACP, NULL, bstrName, -1, locName, uStrLen, NULL, NULL);
  locName[uStrLen] = '\0';

  Acad::ErrorStatus es;
  AcDbObject* pObj = NULL;
  AsdkPoly* pPoly = NULL;

  es = acdbOpenAcDbObject(pObj, pThis->m_objId, AcDb::kForWrite, Adesk::kFalse);

  if ((pPoly = AsdkPoly::cast(pObj)) != NULL)
  {
	AcGePoint3d  startPoint(stPnt[0], stPnt[1], stPnt[2]);
	AcGePoint3d  centerPoint(cenPnt[0], cenPnt[1], cenPnt[2]);

    es = pPoly->setName(locName);
	pPoly->setNumSides(nSide);
	pPoly->setStartPoint(startPoint);
	es = pPoly->setCenter(centerPoint);
 
    pPoly->close();
  }
  else
  {
    pObj->close();
	delete locName;
    return ResultFromScode(E_FAIL);
  }

  delete locName;
  return NOERROR;

}


// Implementation of IAcadBaseObject interface methods

IMPLEMENT_IUNKNOWN_METHODS_DELEGATION(AsdkPoly, AcadBaseObject)
                                                        
STDMETHODIMP CAsdkPoly::IAcadBaseObjectImp::SetObjectId(AcDbObjectId& objId, TCHAR* entryName, TCHAR* keyName)
{
  GET_pThis(CAsdkPoly, m_xAcadBaseObject);
  if (objId == AcDbObjectId::kNull)
  {
    return CreateDefaultAsdkPoly(pThis->m_objId, entryName);
  }
  else
  {
    pThis->m_objId = objId;
    return NOERROR;
  }
}

STDMETHODIMP CAsdkPoly::IAcadBaseObjectImp::GetObjectId(AcDbObjectId* objId)
{
  GET_pThis(CAsdkPoly, m_xAcadBaseObject);
  *objId = pThis->m_objId;
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAcadBaseObjectImp::Clone(AcDbObjectId ownerId, LPUNKNOWN* pUnkClone)
{
	return E_NOTIMPL;
}

STDMETHODIMP CAsdkPoly::IAcadBaseObjectImp::GetClassID(CLSID& clsid)
{
  clsid = CLSID_CAsdkPoly;
  return NOERROR;
}

STDMETHODIMP CAsdkPoly::IAcadBaseObjectImp::NullObjectId(void)
{
  GET_pThis(CAsdkPoly, m_xAcadBaseObject);
  pThis->m_objId = AcDbObjectId::kNull;
  return NOERROR;
}


//////////////////////////////////////////////////////////////////
// Implementation of IRetrieveApplication interface implementation
//////////////////////////////////////////////////////////////////

// The following Macro implements IUknown delegation
// use it when you're comfatable with it.
// IMPLEMENT_IUNKNOWN_METHODS_DELEGATION(AsdkPoly, RetrieveApplication)

STDMETHODIMP_(ULONG) CAsdkPoly::IRetrieveApplicationImp::AddRef(void) 
{ 
  GET_pThis(CAsdkPoly, m_xRetrieveApplication); 
  return pThis->m_pUnkOuter->AddRef(); 
} 

STDMETHODIMP_(ULONG) CAsdkPoly::IRetrieveApplicationImp::Release(void) 
{ 
  GET_pThis(CAsdkPoly, m_xRetrieveApplication); 
  return pThis->m_pUnkOuter->Release(); 
} 

STDMETHODIMP CAsdkPoly::IRetrieveApplicationImp::QueryInterface(REFIID riid, LPVOID FAR* ppv) 
{ 
  GET_pThis(CAsdkPoly, m_xRetrieveApplication); 
  return pThis->m_pUnkOuter->QueryInterface(riid, ppv); 
} 

// end of IMPLEMENT_IUNKNOWN_METHODS_DELEGATION

STDMETHODIMP CAsdkPoly::IRetrieveApplicationImp::SetApplicationObject(LPDISPATCH pAppDisp)
{
  GET_pThis(CAsdkPoly, m_xRetrieveApplication);
  if (pThis->m_pAppDisp)
  {
    pThis->m_pAppDisp->Release();
  }
  pThis->m_pAppDisp = pAppDisp;
  pThis->m_pAppDisp->AddRef();
  return NOERROR;
}


//
// Create a default AsdkPoly
//
HRESULT CreateDefaultAsdkPoly(AcDbObjectId& objId, char* entryName)
{
  char szName[1];

  szName[0] = '\0';
  AsdkPoly* pPoly = new AsdkPoly(AcGePoint3d(0.0, 0.0, 0.0), AcGePoint3d(0.001, 0.0, 0.0), 1,
              AcGeVector3d(0.0, 0.0, 1.0), szName);  // has to have a name due to the contructor behavior
  if (! pPoly) return ResultFromScode(E_OUTOFMEMORY);

  AcDbDatabase* pDb = acdbCurDwg();
  pPoly->setDatabaseDefaults(pDb);

  Acad::ErrorStatus es=Acad::eOk;
  AcDbBlockTable* pBlockTable = NULL;
  AcDbBlockTableRecord* pSpaceRecord = NULL;

  es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
  if (es != Acad::eOk){
	  delete pPoly;
	  return ResultFromScode(E_FAIL);
  }
  es = pBlockTable->getAt(entryName, pSpaceRecord, AcDb::kForWrite);
  if (es != Acad::eOk){
	  delete pPoly;
	  pBlockTable->close();
	  return ResultFromScode(E_FAIL);
  }
  es = pBlockTable->close();

  es = pSpaceRecord->appendAcDbEntity(objId, pPoly);
  if (es != Acad::eOk){
	  delete pPoly;
	  pBlockTable->close();
	  pSpaceRecord->close();
	  return ResultFromScode(E_FAIL);
  }
  es = pPoly->close();
  es = pSpaceRecord->close();

  return NOERROR;
}



