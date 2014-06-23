#ifndef __INTERMAC_H__
#define __INTERMAC_H__
//
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

// Declare IUnknown methods implementation
#define DECLARE_IUNKNOWN_METHODS \
  STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*); \
  STDMETHODIMP_(ULONG) AddRef(void); \
  STDMETHODIMP_(ULONG) Release(void); \

// Declare IDispatch methods implementation
#define DECLARE_IDISPATCH_METHODS \
  STDMETHODIMP GetTypeInfoCount(UINT FAR*); \
  STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo FAR* FAR*); \
  STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR FAR* FAR*, UINT, LCID, DISPID FAR*); \
  STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS FAR*, VARIANT FAR*, EXCEPINFO FAR*, UINT FAR*); \

// Declare IClassFactory methods implementation
#define DECLARE_ICLASSFACTORY_METHODS \
  STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR*); \
  STDMETHODIMP LockServer(BOOL); \

// Declare IAcadBaseObject implmentation
#define DECLARE_ACADBASEOBJECT \
private: \
  interface IAcadBaseObjectImp : public IAcadBaseObject \
  { \
    STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*); \
    STDMETHODIMP_(ULONG) AddRef(void); \
    STDMETHODIMP_(ULONG) Release(void); \
\
    /* IAcadBaseObject methods */ \
    STDMETHODIMP SetObjectId(AcDbObjectId& objId, TCHAR* entryName, TCHAR* keyName = NULL); \
    STDMETHODIMP GetObjectId(AcDbObjectId* objId); \
    STDMETHODIMP Clone(AcDbObjectId ownerId, LPUNKNOWN* pUnkClone); \
    STDMETHODIMP GetClassID(CLSID& clsid); \
    STDMETHODIMP NullObjectId(void); \
\
  } m_xAcadBaseObject; \
\
friend interface IAcadBaseObjectImp; \

// Declare IRetrieveApplication implementation
#define DECLARE_RETRIEVEAPPLICATION \
private: \
  interface IRetrieveApplicationImp : public IRetrieveApplication \
  { \
    STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*); \
    STDMETHODIMP_(ULONG) AddRef(void); \
    STDMETHODIMP_(ULONG) Release(void); \
\
    /* IRetrieveApplication methods */ \
    STDMETHODIMP SetApplicationObject(LPDISPATCH pAppDisp); \
\
  } m_xRetrieveApplication; \
\
friend interface IRetrieveApplicationImp; \

// Declare EntityCommon methods implementation
#define DECLARE_ENTITYCOMMON_METHODS \
  STDMETHODIMP get_Handle(BSTR FAR* handle); \
  STDMETHODIMP get_EntityName(BSTR FAR* className); \
  STDMETHODIMP get_Color(int FAR* color); \
  STDMETHODIMP put_Color(int color); \
  STDMETHODIMP get_Layer(BSTR FAR* layer); \
  STDMETHODIMP put_Layer(BSTR layer); \
  STDMETHODIMP get_Linetype(BSTR FAR* lineType); \
  STDMETHODIMP put_Linetype(BSTR lineType); \
  STDMETHODIMP get_LinetypeScale(double FAR* ltScale); \
  STDMETHODIMP put_LinetypeScale(double ltScale); \
  STDMETHODIMP get_Visible(VARIANT_BOOL FAR* bVisible); \
  STDMETHODIMP put_Visible(VARIANT_BOOL bVisible); \
  STDMETHODIMP GetXData(BSTR bstrName, VARIANT FAR* type, VARIANT FAR* data); \
  STDMETHODIMP SetXData(SAFEARRAY FAR* type, SAFEARRAY FAR* data); \
  STDMETHODIMP ArrayPolar(int numObjs, double fillAngle, SAFEARRAY FAR* basePoint, SAFEARRAY FAR* FAR* pArrayObjs); \
  STDMETHODIMP ArrayRectangular(int numRows, int numCols, int numLvls, double disRows, double disCols, double disLvls, SAFEARRAY FAR* FAR* pArrayObjs); \
  STDMETHODIMP Highlight(VARIANT_BOOL bFlag); \
  STDMETHODIMP Copy(LPDISPATCH FAR* pCopyObj); \
  STDMETHODIMP Erase(void); \
  STDMETHODIMP Move(SAFEARRAY FAR* fromPoint, SAFEARRAY FAR* toPoint); \
  STDMETHODIMP Rotate(SAFEARRAY FAR* basePoint, double rotationAngle); \
  STDMETHODIMP Rotate3d(SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, double rotationAngle); \
  STDMETHODIMP Mirror(SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, LPDISPATCH FAR* pMirrorObj); \
  STDMETHODIMP Mirror3d(SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, SAFEARRAY FAR* point3, LPDISPATCH FAR* pMirrorObj); \
  STDMETHODIMP ScaleEntity(SAFEARRAY FAR* basePoint, double scaleFactor); \
  STDMETHODIMP TransformBy(SAFEARRAY FAR* transMatrix); \
  STDMETHODIMP Update(void); \
  STDMETHODIMP GetBoundingBox(VARIANT FAR* minPoint, VARIANT FAR* maxPoint); \
  STDMETHODIMP IntersectWith(LPDISPATCH pEntity, int option, SAFEARRAY FAR* FAR* intPoints); \

//
// Macros for implementation
//

// GET_pThis macro
#define GET_pThis(Class, x) Class* pThis = (Class*) ((int)this - (int) &(((Class*) 0)->x))

// Implement IUnknown methods delegation
#define IMPLEMENT_IUNKNOWN_METHODS_DELEGATION(theClass, nestClass) \
  STDMETHODIMP_(ULONG) C##theClass::I##nestClass##Imp::AddRef(void) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pUnkOuter->AddRef(); \
  } \
\
  STDMETHODIMP_(ULONG) C##theClass::I##nestClass##Imp::Release(void) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pUnkOuter->Release(); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::QueryInterface(REFIID riid, LPVOID FAR* ppv) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pUnkOuter->QueryInterface(riid, ppv); \
  } \

// Implement IDispatch methods delegation
#define IMPLEMENT_IDISPATCH_METHODS_DELEGATION(theClass, nestClass) \
  STDMETHODIMP C##theClass::I##nestClass##Imp::GetTypeInfoCount(UINT FAR* pctinfo) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    HRESULT hr = NOERROR; \
    LPDISPATCH pDisp = NULL; \
    hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp); \
    if (SUCCEEDED(hr)) \
    { \
      hr = pDisp->GetTypeInfoCount(pctinfo); \
      pDisp->Release(); \
    } \
    return hr; \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::GetTypeInfo(UINT itinfo, LCID lcid, \
    ITypeInfo FAR* FAR* pptinfo) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    HRESULT hr = NOERROR; \
    LPDISPATCH pDisp = NULL; \
    hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp); \
    if (SUCCEEDED(hr)) \
    { \
      hr = pDisp->GetTypeInfo(itinfo, lcid, pptinfo); \
      pDisp->Release(); \
    } \
    return hr; \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::GetIDsOfNames(REFIID riid, \
    OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgdispid) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    HRESULT hr = NOERROR; \
    LPDISPATCH pDisp = NULL; \
    hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp); \
    if (SUCCEEDED(hr)) \
    { \
      hr = pDisp->GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid); \
      pDisp->Release(); \
    } \
    return hr; \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Invoke(DISPID dispidMember, REFIID riid, \
    LCID lcid, WORD wFlags, DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult, \
    EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    HRESULT hr = NOERROR; \
    LPDISPATCH pDisp = NULL; \
    hr = pThis->m_pStdDispatch->QueryInterface(IID_IDispatch, (LPVOID*) &pDisp); \
    if (SUCCEEDED(hr)) \
    { \
      hr = pDisp->Invoke(dispidMember, riid, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr); \
      pDisp->Release(); \
    } \
    return hr; \
  } \

// Implement EntityCommon methods
#define IMPLEMENT_ENTITYCOMMON_METHODS(theClass, nestClass, theClsid) \
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_Handle(BSTR FAR* handle) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_Handle(pThis->m_objId, pThis->m_pStdDispatch, \
      handle); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_EntityName(BSTR FAR* className) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_EntityName(pThis->m_objId, pThis->m_pStdDispatch, \
      className); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_Color(int FAR* color) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_Color(pThis->m_objId, pThis->m_pStdDispatch, \
      color); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::put_Color(int color) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->put_Color(pThis->m_objId, pThis->m_pStdDispatch, \
      color); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_Layer(BSTR FAR* layer) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_Layer(pThis->m_objId, pThis->m_pStdDispatch, \
      layer); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::put_Layer(BSTR layer) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->put_Layer(pThis->m_objId, pThis->m_pStdDispatch, \
      layer); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_Linetype(BSTR FAR* lineType) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_Linetype(pThis->m_objId, pThis->m_pStdDispatch, \
      lineType); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::put_Linetype(BSTR lineType) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->put_Linetype(pThis->m_objId, pThis->m_pStdDispatch, \
      lineType); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_LinetypeScale(double FAR* ltScale) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_LinetypeScale(pThis->m_objId, pThis->m_pStdDispatch, \
      ltScale); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::put_LinetypeScale(double ltScale) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->put_LinetypeScale(pThis->m_objId, pThis->m_pStdDispatch, \
      ltScale); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::get_Visible(VARIANT_BOOL FAR* bVisible) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->get_Visible(pThis->m_objId, pThis->m_pStdDispatch, \
      bVisible); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::put_Visible(VARIANT_BOOL bVisible) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->put_Visible(pThis->m_objId, pThis->m_pStdDispatch, \
      bVisible); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::GetXData(BSTR bstrName, VARIANT FAR* type, VARIANT FAR* data) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->GetXData(pThis->m_objId, pThis->m_pStdDispatch, \
      bstrName, type, data); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::SetXData(SAFEARRAY FAR* type, SAFEARRAY FAR* data) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->SetXData(pThis->m_objId, pThis->m_pStdDispatch, \
      type, data); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::ArrayPolar(int numObjs, double fillAngle, \
    SAFEARRAY FAR* basePoint, SAFEARRAY FAR* FAR* pArrayObjs) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->ArrayPolar(pThis->m_objId, pThis->m_pStdDispatch, \
      theClsid, pThis->m_pAppDisp, numObjs, fillAngle, basePoint, pArrayObjs); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::ArrayRectangular(int numRows, int numCols, \
    int numLvls, double disRows, double disCols, double disLvls, SAFEARRAY FAR* FAR* pArrayObjs) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->ArrayRectangular(pThis->m_objId, pThis->m_pStdDispatch, \
      theClsid, pThis->m_pAppDisp, numRows, numCols, numLvls, disRows, disCols, disLvls, pArrayObjs); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Highlight(VARIANT_BOOL bFlag) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Highlight(pThis->m_objId, pThis->m_pStdDispatch, \
      bFlag); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Copy(LPDISPATCH FAR* pCopyObj) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Copy(pThis->m_objId, pThis->m_pStdDispatch, \
      theClsid, pThis->m_pAppDisp, pCopyObj); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Erase(void) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    HRESULT hr = pThis->m_pEntComm->Erase(pThis->m_objId, pThis->m_pStdDispatch); \
    return hr; \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Move(SAFEARRAY FAR* fromPoint, \
    SAFEARRAY FAR* toPoint) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Move(pThis->m_objId, pThis->m_pStdDispatch, \
      fromPoint, toPoint); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Rotate(SAFEARRAY FAR* basePoint, \
    double rotationAngle) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Rotate(pThis->m_objId, pThis->m_pStdDispatch, \
      basePoint, rotationAngle); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Rotate3d(SAFEARRAY FAR* point1, \
    SAFEARRAY FAR* point2, double rotationAngle) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Rotate3d(pThis->m_objId, pThis->m_pStdDispatch, \
      point1, point2, rotationAngle); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Mirror(SAFEARRAY FAR* point1, \
    SAFEARRAY FAR* point2, LPDISPATCH FAR* pMirrorObj) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Mirror(pThis->m_objId, pThis->m_pStdDispatch, \
      theClsid, pThis->m_pAppDisp, point1, point2, pMirrorObj); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Mirror3d(SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, \
    SAFEARRAY FAR* point3, LPDISPATCH FAR* pMirrorObj) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Mirror3d(pThis->m_objId, pThis->m_pStdDispatch, \
      theClsid, pThis->m_pAppDisp, point1, point2, point3, pMirrorObj); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::ScaleEntity(SAFEARRAY FAR* basePoint, \
    double scaleFactor) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->ScaleEntity(pThis->m_objId, pThis->m_pStdDispatch, \
      basePoint, scaleFactor); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::TransformBy(SAFEARRAY FAR* transMatrix) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->TransformBy(pThis->m_objId, pThis->m_pStdDispatch, \
      transMatrix); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::Update(void) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->Update(pThis->m_objId, pThis->m_pStdDispatch); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::GetBoundingBox(VARIANT FAR* minPoint, \
    VARIANT FAR* maxPoint) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->GetBoundingBox(pThis->m_objId, pThis->m_pStdDispatch, \
      minPoint, maxPoint); \
  } \
\
  STDMETHODIMP C##theClass::I##nestClass##Imp::IntersectWith(LPDISPATCH pEntity, \
    int option, SAFEARRAY FAR* FAR* intPoints) \
  { \
    GET_pThis(C##theClass, m_x##nestClass); \
    return pThis->m_pEntComm->IntersectWith(pThis->m_objId, pThis->m_pStdDispatch, \
      pEntity, option, intPoints); \
  } \

#endif // __INTERMAC_H__
