// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////////////////
//  MyEntityDynProp3.cpp : Implementation of CMyEntityDynProp3
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "MyEntityDynProp3.h"

//////////////////////////////////////////////////////////////////////////
//  CMyEntityDynProp3
STDMETHODIMP CMyEntityDynProp3::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr [] ={
		&IID_IMyEntityDynProp3
	} ;

	for ( int i =0 ; i < sizeof (arr) / sizeof (arr [0]) ; i++ ) {
		if ( InlineIsEqualGUID (*arr [i], riid) )
			return (S_OK) ;
	}
	return (S_FALSE) ;
}

//////////////////////////////////////////////////////////////////////////
//  IDynamicProperty
STDMETHODIMP CMyEntityDynProp3::GetGUID (GUID *pPropGUID) {
	if ( pPropGUID == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	memcpy (pPropGUID, &CLSID_MyEntityDynProp3, sizeof(GUID)) ;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetDisplayName (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pBstrName =::SysAllocString (L"My String") ;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::IsPropertyEnabled (IUnknown *pUnk, BOOL *pbEnabled) 
{
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	if ( pbEnabled == NULL )
		return (E_POINTER) ;

  // get the selected object
  CComQIPtr<IAcadBaseObject> pObj(pUnk);
  CComQIPtr<IMyEntityWrapper> pMyEntity(pObj);
  // get the My Type 
  LONG myType = 0;
  pMyEntity->get_MyType(&myType);

	// if the type is normal don't display this
  *pbEnabled = myType != 0 ? TRUE:FALSE;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::IsPropertyReadOnly (BOOL *pbReadOnly) {
	if ( pbReadOnly == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pbReadOnly =FALSE ;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetDescription (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pBstrName =::SysAllocString (L"Description for My Property (CMyEntityDynProp3)") ;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetCurrentValueName (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here

	//return (S_OK) ; //  If you do anything in there
	return (E_NOTIMPL) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetCurrentValueType (VARTYPE *pVarType) {
	if ( pVarType == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pVarType = VT_BSTR ; //  A string

	return (S_OK) ;
}
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetCurrentValueData (IUnknown *pUnk, VARIANT *pVarData) {
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	if ( pVarData == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 3 lines below)
	::VariantInit (pVarData) ;
	V_VT(pVarData) = VT_BSTR;
  // copy in a string
  COleVariant varValue;
  varValue = L"Hello Developers";
  *pVarData = varValue.Detach();
	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::SetCurrentValueData (IUnknown *pUnk, const VARIANT varData) 
{
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	// TODO: add your code here

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::Connect (IDynamicPropertyNotify2 *pSink) {
	if ( pSink == NULL )
		return (E_POINTER) ;
	m_pNotify =pSink ;
	m_pNotify->AddRef () ;
	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::Disconnect () {
	if ( m_pNotify ) {
		m_pNotify->Release () ;
		m_pNotify= NULL ;
	}
	return (S_OK) ;
}
//////////////////////////////////////////////////////////////////////////
//  ICategorizePropertes
STDMETHODIMP CMyEntityDynProp3::MapPropertyToCategory (DISPID dispid, PROPCAT *pPropCat) {
	if ( pPropCat == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pPropCat =0 ;

	return (S_OK) ;
}

//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CMyEntityDynProp3::GetCategoryName (PROPCAT propcat, LCID lcid, BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 3 lines below)
	if ( propcat != 0 )
		return (E_INVALIDARG) ;
	*pBstrName =::SysAllocString (L"My Dynamic Properties") ;

	return (S_OK) ;
}
//////////////////////////////////////////////////////////////////////////
// IFilterableProperty
// The "ShowFilterableProperty" method is used to dictate whether a
// property should be visible in the property filter customization user
// interface.  It is passed a DISPID of the property whose visibility is
// being determined (which would normally be "DISPID_DYNAMIC" for dynamic
// properties) and an AcFilterablePropertyContext that specifies whether
// the framework is querying about appearance in the "Quick Properties"
// customization user interface or for the "Rollover tooltips"
// customization user interface.  A boolean value indicating whether or
// not the property should be shown is returned via the "pbShow"
// output parameter.
STDMETHODIMP CMyEntityDynProp3::ShowFilterableProperty(/*[in]*/DISPID dispID,
                                                      /*[in]*/AcFilterablePropertyContext context,
                                                      /*[out, retval]*/BOOL* pbShow)
{
  // check everything is valid
  if (!pbShow)
    return E_POINTER;

  // make sure it's a dynamic property
  ASSERT(dispID == DISPID_DYNAMIC);

  // ok - show it - this is just for implementation demo purposes, the properties are really handled by 
  // the CMyPerInstancePropFactory and the IFilterableSubtypePropertySource interface
  *pbShow = TRUE;

  return S_OK;
}