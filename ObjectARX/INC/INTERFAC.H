#ifndef __INTERFAC_H__
#define __INTERFAC_H__
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

#include "dbid.h"

// {72C2D810-461D-11CF-93D2-0800099EB3B7}
DEFINE_GUID(IID_IEntityCommon,
0x72C2D810, 0x461D, 0x11CF, 0x93, 0xD2, 0x8, 0x0, 0x9, 0x9E, 0xB3, 0xB7);

/* Definition of interface: IEntityCommon */
#undef INTERFACE
#define INTERFACE IEntityCommon

DECLARE_INTERFACE_(IEntityCommon, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IEntityCommon methods */
    STDMETHOD(get_Handle)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR FAR* handle) PURE;
    STDMETHOD(get_EntityName)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR FAR* className) PURE;
    STDMETHOD(get_Color)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      int FAR* color) PURE;
    STDMETHOD(put_Color)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      int color) PURE;
    STDMETHOD(get_Layer)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR FAR* layer) PURE;
    STDMETHOD(put_Layer)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR layer) PURE;
    STDMETHOD(get_Linetype)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR FAR* lineType) PURE;
    STDMETHOD(put_Linetype)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR lineType) PURE;
    STDMETHOD(get_LinetypeScale)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      double FAR* ltScale) PURE;
    STDMETHOD(put_LinetypeScale)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      double ltScale) PURE;
    STDMETHOD(get_Visible)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      VARIANT_BOOL FAR* bVisible) PURE;
    STDMETHOD(put_Visible)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      VARIANT_BOOL bVisible) PURE;
    STDMETHOD(GetXData)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      BSTR bstrName, VARIANT FAR* type, VARIANT FAR* data) PURE;
    STDMETHOD(SetXData)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* type, SAFEARRAY FAR* data) PURE;
    STDMETHOD(ArrayPolar)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      const CLSID& clsid, LPDISPATCH pAppDisp,
      int numObjs, double fillAngle, SAFEARRAY FAR* basePoint, SAFEARRAY FAR* FAR* pArrayObjs) PURE;
    STDMETHOD(ArrayRectangular)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      const CLSID& clsid, LPDISPATCH pAppDisp,
      int numRows, int numCols, int numLvls, double disRows, double disCols, double disLvls,
      SAFEARRAY FAR* FAR* pArrayObjs) PURE;
    STDMETHOD(Highlight)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      VARIANT_BOOL bFlag) PURE;
    STDMETHOD(Copy)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      const CLSID& clsid, LPDISPATCH pAppDisp,
      LPDISPATCH FAR* pCopyObj, AcDbObjectId ownerId = AcDbObjectId::kNull) PURE;
    STDMETHOD(Erase)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch) PURE;
    STDMETHOD(Move)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* fromPoint, SAFEARRAY FAR* toPoint) PURE;
    STDMETHOD(Rotate)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* basePoint, double rotationAngle) PURE;
    STDMETHOD(Rotate3d)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, double rotationAngle) PURE;
    STDMETHOD(Mirror)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      const CLSID& clsid, LPDISPATCH pAppDisp,
      SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, LPDISPATCH FAR* pMirrorObj) PURE;
    STDMETHOD(Mirror3d)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      const CLSID& clsid, LPDISPATCH pAppDisp,
      SAFEARRAY FAR* point1, SAFEARRAY FAR* point2, SAFEARRAY FAR* point3, LPDISPATCH FAR* pMirrorObj) PURE;
    STDMETHOD(ScaleEntity)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* basePoint, double scaleFactor) PURE;
    STDMETHOD(TransformBy)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      SAFEARRAY FAR* transMatrix) PURE;
    STDMETHOD(Update)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch) PURE;
    STDMETHOD(GetBoundingBox)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      VARIANT FAR* minPoint, VARIANT FAR* maxPoint) PURE;
    STDMETHOD(IntersectWith)(THIS_ AcDbObjectId& objId, LPUNKNOWN pStdDispatch,
      LPDISPATCH pEntity, int option, SAFEARRAY FAR* FAR* intPoints) PURE;
};

typedef IEntityCommon FAR* LPENTITYCOMMON;

// {5F3C54C0-49E1-11cf-93D5-0800099EB3B7}
DEFINE_GUID(IID_IAcadBaseObject, 
0x5f3c54c0, 0x49e1, 0x11cf, 0x93, 0xd5, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IAcadBaseObject */
#undef INTERFACE
#define INTERFACE IAcadBaseObject

DECLARE_INTERFACE_(IAcadBaseObject, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject methods */
    STDMETHOD(SetObjectId)(THIS_ AcDbObjectId& objId, TCHAR* entryName, TCHAR* keyName = NULL) PURE;
    STDMETHOD(GetObjectId)(THIS_ AcDbObjectId* objId) PURE;
    STDMETHOD(Clone)(THIS_ AcDbObjectId ownerId, LPUNKNOWN* pUnkClone) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
    STDMETHOD(NullObjectId)(THIS) PURE;
};

typedef IAcadBaseObject FAR* LPACADBASEOBJECT;

#endif // __INTERFAC_H__
