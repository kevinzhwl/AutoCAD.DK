#ifndef __CPOLYAPP_H__
#define __CPOLYAPP_H__
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
// CPOLYCOM.H
//
// DESCRIPTION: 

#include "interfac.h"  
#include "intermac.h"
#include "iretapp.h"
#include "polyolea.h" // interface definition of polyApp & poly
#include "entclsid.h"


// {64CED5D0-85A1-11d0-B1BF-080009DC322B}
DEFINE_GUID(CLSID_CAsdkPolyApp,, 
0x64ced5d0, 0x85a1, 0x11d0, 0xb1, 0xbf, 0x8, 0x0, 0x9, 0xdc, 0x32, 0x2b);

#define GET_pThis(Class, x) Class* pThis = (Class*) ((int)this - (int) &(((Class*) 0)->x))

#include "dbid.h"

class CAsdkPolyApp : public IUnknown
{
protected:
  ULONG m_ulRef;

public:
  LPUNKNOWN m_pUnkOuter;

public:
  STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*);
  STDMETHODIMP_(ULONG) AddRef(void);
  STDMETHODIMP_(ULONG) Release(void);

  interface IAsdkPolyAppImp : public IAsdkPolyApp
  {
    /* IUnknown methods */
    STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    /* IDispatch methods */
    // You can use DECLARE_IDISPATCH_METHODS for the following group of methods.
    STDMETHODIMP GetTypeInfoCount(UINT FAR*);
    STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo FAR* FAR*);
    STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR FAR* FAR*, UINT, LCID, DISPID FAR*);
    STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS FAR*, VARIANT FAR*, 
                        EXCEPINFO FAR*, UINT FAR*);

	STDMETHODIMP CreatePoly();
	STDMETHODIMP CreateDragPoly();
	STDMETHODIMP EditPoly();
	STDMETHODIMP TransactPoly();
	STDMETHODIMP HilitPoly();
	STDMETHODIMP HilitSolid();
    STDMETHODIMP AddPoly(BSTR whichSpace, BSTR bstrName, int nSide , SAFEARRAY FAR* ptCenter, 
                         SAFEARRAY FAR* ptStart, LPDISPATCH FAR* pRetDisp);
  } m_xAsdkPolyApp;

friend interface IAsdkPolyAppImp;


public:
  CAsdkPolyApp(LPUNKNOWN);
  ~CAsdkPolyApp();
  HRESULT InitNew();

private:
  LPUNKNOWN m_pStdDispatch;  

};

class CAsdkPolyAppFactory : public IClassFactory
{
protected:
  ULONG m_ulRef;

public:
  STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*);
  STDMETHODIMP_(ULONG) AddRef(void);
  STDMETHODIMP_(ULONG) Release(void);

  STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR *);
  STDMETHODIMP LockServer(BOOL);

public:
  CAsdkPolyAppFactory(void);
  ~CAsdkPolyAppFactory(void);
};


ULONG DllServerGetNumberOfObjects(void);
ULONG DllServerGetNumberOfLocks(void);
void DllServerIncrementNumberOfObjects(void);
void DllServerDecrementNumberOfObjects(void);
void DllServerIncrementNumberOfLocks(void);
void DllServerDecrementNumberOfLocks(void);


#endif // CPOLYAPP
