#ifndef __CPOLY_H__
#define __CPOLY_H__
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
// CPOLY.H
//
// DESCRIPTION: 

// Need to decide on these include files

#include "interfac.h"  
#include "intermac.h"
#include "iretapp.h"
#include "polyolea.h" // interface definition of poly
#include "entclsid.h"


// {33C36D91-E034-11cf-9B81-080009B133D5}
DEFINE_GUID(CLSID_CAsdkPoly, 
0x33c36d91, 0xe034, 0x11cf, 0x9b, 0x81, 0x8, 0x0, 0x9, 0xb1, 0x33, 0xd5);

#define GET_pThis(Class, x) Class* pThis = (Class*) ((int)this - (int) &(((Class*) 0)->x))

#include "dbid.h"

class CAsdkPoly : public IUnknown
{
protected:
  ULONG m_ulRef;

public:
  LPUNKNOWN m_pUnkOuter;

public:
  STDMETHODIMP QueryInterface(REFIID, LPVOID FAR*);
  STDMETHODIMP_(ULONG) AddRef(void);
  STDMETHODIMP_(ULONG) Release(void);

  interface IAsdkPolyImp : public IAsdkPoly
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
    STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS FAR*, VARIANT FAR*, EXCEPINFO FAR*, UINT FAR*);

    /* IEntityCommon methods */
    // You can use DECLARE_ENTITYCOMMON_METHODS  for the following group of methods.
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
    STDMETHODIMP GetXData(BSTR name, VARIANT FAR* type, VARIANT FAR* data); \
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

	  /* IAsdkPoly methods */
    STDMETHODIMP get_NumberOfSide(int FAR* nSide);
    STDMETHODIMP put_NumberOfSide(int nSide);
    STDMETHODIMP get_Center(SAFEARRAY FAR* FAR* ptCenter);
    STDMETHODIMP put_Center(SAFEARRAY FAR* ptCenter);
    STDMETHODIMP get_StartPoint(SAFEARRAY FAR* FAR* ptStart);
    STDMETHODIMP put_StartPoint(SAFEARRAY FAR* ptStart);
    STDMETHODIMP get_Normal(SAFEARRAY FAR* FAR* vNormal);
    STDMETHODIMP put_Normal(SAFEARRAY FAR* vNormal);
    STDMETHODIMP get_Name(BSTR FAR* bstrName);
    STDMETHODIMP put_Name(BSTR bstrName);
    STDMETHODIMP initializeAll(BSTR bstrName, int nSide, SAFEARRAY FAR* ptCenter, SAFEARRAY FAR* ptStart);

  } m_xAsdkPoly;

friend interface IAsdkPolyImp;

// support for IEntityObject interface

DECLARE_ACADBASEOBJECT

// support for IRetrieveApplication interface

DECLARE_RETRIEVEAPPLICATION

public:
  CAsdkPoly(LPUNKNOWN);
  ~CAsdkPoly();
  HRESULT InitNew();

private:
  LPUNKNOWN m_pStdDispatch;  
  LPENTITYCOMMON m_pEntComm;  
  AcDbObjectId m_objId;
  LPDISPATCH m_pAppDisp;      

};


class CAsdkPolyClassFactory : public IClassFactory
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
  CAsdkPolyClassFactory(void);
  ~CAsdkPolyClassFactory(void);
};


HRESULT CreateDefaultAsdkPoly(AcDbObjectId& objId, char* entryName);
ULONG DllServerGetNumberOfObjects(void);
ULONG DllServerGetNumberOfLocks(void);
void DllServerIncrementNumberOfObjects(void);
void DllServerDecrementNumberOfObjects(void);
void DllServerIncrementNumberOfLocks(void);
void DllServerDecrementNumberOfLocks(void);


#endif // __CPOLY_H__
