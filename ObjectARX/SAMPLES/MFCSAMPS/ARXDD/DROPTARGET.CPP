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

#include "acdb.h"
#include "adslib.h"
#include "rxregsvc.h"
#include "dbents.h"
#include <dbsymtb.h>

Adesk::Boolean
append(AcDbEntity* pEntity, int vport)
{
    AcDbBlockTable *pBlockTable;
    Acad::ErrorStatus es = acdbCurDwg()->getBlockTable(pBlockTable,
        AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table!");
        return Adesk::kFalse;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(vport == 1 ?  ACDB_PAPER_SPACE : ACDB_MODEL_SPACE ,
      pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table record!");
        pBlockTable->close();
        return Adesk::kFalse;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
    if (es != Acad::eOk) {
        ads_alert("Failed to append entity!");
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return Adesk::kFalse;
    }
    pBlockRec->close();
    pBlockTable->close();
    return Adesk::kTrue;
}


BOOL PasteFromData(IDataObject* pDataObject, CRect& resRect, int& objType)
{
    FORMATETC formatEtc;
    STGMEDIUM medium;

    SetDefFormatEtc(formatEtc,CF_TEXT, TYMED_HGLOBAL);
    if (!SUCCEEDED(pDataObject->GetData(&formatEtc, &medium)))
	    return FALSE;

    CRect rect;
    int type, left, top, right, bottom;
      
    char * pstr = (char*) GlobalLock (medium.hGlobal);
    if (sscanf(pstr, "%d %d %d %d %d", &type, &left, &top, &right, &bottom) != 5)
	    TRACE("Getting incorrect ObjType & CRect information\n");
    GlobalUnlock(medium.hGlobal);

      rect.SetRect(left, top, right, bottom);
      rect.NormalizeRect();
      resRect = rect;
      objType = type;

    ReleaseStgMedium(&medium);

    return TRUE;
}



CDropTarget::CDropTarget(CView *pView, CView *pOwnView)
{
	  m_pIDataObject = NULL;
    m_pView = pView;
    m_pOwnView = pOwnView;
    m_cRef =0;
    m_rad = 0;
}

CDropTarget::~CDropTarget()
{
}

STDMETHODIMP 
CDropTarget::DragEnter(IDataObject * pDataObject,
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
	  if (!QueryData(pDataObject))
	  {
		  *pdwEffect = DROPEFFECT_NONE;
		  return NOERROR;
	  }

	  m_pIDataObject = pDataObject;
	  m_pIDataObject->AddRef(); 
    
    // set the tracker size.         
    CRect rSize;
    int objType;
    if (!::PasteFromData(pDataObject, rSize, objType) || rSize.IsRectEmpty() == TRUE)
        m_rad = 50;
    else 
        m_rad = min(rSize.Width(), rSize.Height());

    return DragOver(grfKeyState, pt, pdwEffect); 
}


STDMETHODIMP 
CDropTarget::DragOver(
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
    // find the tracker size
    CSize trackerSize;
    int pixelDiam;
    acedDwgPoint ptIn, ptIn2;

    CPoint ptOut, ptOut2;
    ptIn[0]=0;
    ptIn[1]=0;
    ptIn[2]=0;
    ptIn2[0]=(2*m_rad);
    ptIn2[1]=0;
    ptIn2[2]=0;
     
    CPoint localPt2 ((int)pt.x, (int)pt.y);
    m_pView->ScreenToClient(&localPt2);

    int windnum = acedGetWinNum(localPt2.x, localPt2.y);
    if (windnum == 0)
    {
 		  *pdwEffect=DROPEFFECT_NONE;
      if (m_prevDropEffect != DROPEFFECT_NONE)
      {   // erase the prev tracker
         m_pView->GetDC()->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize));
         m_prevDropEffect = *pdwEffect ;
      }     
      return NOERROR; // Don't draw rect here
    }

    acedCoordFromWorldToPixel(windnum, ptIn,  ptOut);
    acedCoordFromWorldToPixel(windnum, ptIn2,  ptOut2);

    pixelDiam = ptOut2.x - ptOut.x;
    TRACE("diamPixel is %d\n", pixelDiam);

    trackerSize = CSize(pixelDiam,pixelDiam);

    /////

    CPoint localPt ((int)pt.x - trackerSize.cx/2, (int)pt.y - trackerSize.cx/2);

    m_pView->ScreenToClient(&localPt);

    if (NULL==m_pIDataObject)
	  {
		  *pdwEffect=DROPEFFECT_NONE;
		  return NOERROR;
	  }

	  *pdwEffect=DROPEFFECT_COPY;
 
    // check if it's the same point
    if (localPt == m_lastDragPt)
         return NOERROR;
    
    if (m_pView == NULL) // can't draw tracker!
        return NOERROR;
        
    CDC *pDC = m_pView->GetDC();
    ASSERT(pDC);
    if (m_prevDropEffect != DROPEFFECT_NONE)
    {   // erase the prev tracker

        pDC->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize));
    }
    m_prevDropEffect = *pdwEffect;

    if (m_prevDropEffect != DROPEFFECT_NONE)
    {   // draw new tracker
        pDC->DrawFocusRect(CRect(localPt, trackerSize));
        m_lastDragPt = localPt;
        m_trackerSize = trackerSize;
    }

	return NOERROR;
}


STDMETHODIMP 
CDropTarget::DragLeave(void)
{
	if (m_pIDataObject !=NULL)
	{
		m_pIDataObject->Release();
	}

    if (m_prevDropEffect != DROPEFFECT_NONE)
    {
        if (m_pView == NULL) // can't draw tracker
            return NOERROR;
            
        CDC* pDC = acedGetAcadDwgView()->GetDC();
        ASSERT(pDC);
        // erase previous focus rect
        pDC->DrawFocusRect(CRect(m_lastDragPt, m_trackerSize)); 
        m_prevDropEffect = DROPEFFECT_NONE;
    }
	return NOERROR;
}
 
STDMETHODIMP 
CDropTarget::Drop(
    IDataObject * pDataObject,	//Points to the IDataObject interface for the source data
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect )	//Effect of the drag-and-drop operation
{
	  BOOL fRet=TRUE;

	  *pdwEffect = DROPEFFECT_NONE;

	  if (NULL == m_pIDataObject)
	      return ResultFromScode(E_FAIL);

	  DragLeave();

    CRect rSize;
    int objType;
    fRet = ::PasteFromData(pDataObject, rSize, objType);
    
    if (rSize.IsRectEmpty() == TRUE)
        return NOERROR;

    CPoint localPt ((int)pt.x, (int)pt.y);
    m_pView->ScreenToClient(&localPt);

    acedDwgPoint dwgPt;
    int windnum = acedGetWinNum(localPt.x, localPt.y);
    if (windnum == 0)
    {
        *pdwEffect=DROPEFFECT_NONE;
		    return NOERROR;
    }

    acedCoordFromPixelToWorld(windnum, localPt, dwgPt);
    switch (objType) 
    {
        case 0 :  // circle
        {
            double rad = min(rSize.Width(), rSize.Height());
    
            AcGeVector3d mnormal(0,0,1);
            AcGePoint3d center(dwgPt[0], dwgPt[1], 0);
            AcDbCircle *pCircle = new AcDbCircle(center, mnormal, rad);
            if (::append(pCircle, windnum) != Adesk::kTrue)
                return ResultFromScode(E_FAIL);
            pCircle->close();
        }
        break;

        case 1 : // square
        {
            double half = rSize.Width();

            AcGePoint3dArray  sqrPts;
            double x = dwgPt[0];
            double y = dwgPt[1];

            sqrPts.append(AcGePoint3d(x-half, y-half,0));
            sqrPts.append(AcGePoint3d(x-half, y+half,0));
            sqrPts.append(AcGePoint3d(x+half, y+half,0));
            sqrPts.append(AcGePoint3d(x+half, y-half,0));

            AcDb2dPolyline *pSquare = new AcDb2dPolyline(AcDb::k2dSimplePoly, sqrPts);
            pSquare->makeClosed();
            if (::append(pSquare, windnum) != Adesk::kTrue)
                return ResultFromScode(E_FAIL);
            pSquare->close();

        }
        break;

        case 2 :
        {
            AcGePoint3dArray  tri;
            double x = dwgPt[0];
            double y = dwgPt[1];
            double size = rSize.Width();
            tri.append(AcGePoint3d(x, y+size,0));
            tri.append(AcGePoint3d(x-size, y-size,0));
            tri.append(AcGePoint3d(x+size, y-size,0));

            AcDb2dPolyline *pUp = new AcDb2dPolyline(AcDb::k2dSimplePoly, tri);
            pUp->makeClosed();
            if (::append(pUp, windnum) != Adesk::kTrue)
                return ResultFromScode(E_FAIL);
            pUp->close();

        }
        break;

        case 3 :
        {
            AcGePoint3dArray  tri;
            double x = dwgPt[0];
            double y = dwgPt[1];
            double size = rSize.Width();

            tri.append(AcGePoint3d(x, y-size,0));
            tri.append(AcGePoint3d(x-size, y+size,0));
            tri.append(AcGePoint3d(x+size, y+size,0));

            AcDb2dPolyline *pDown = new AcDb2dPolyline(AcDb::k2dSimplePoly, tri);
            pDown->makeClosed();
            if (::append(pDown,windnum) != Adesk::kTrue)
                return ResultFromScode(E_FAIL);
            pDown->close();

        }
        break;

    }

    // Set Focus to AutoCAD because AutoCAD doesn't update its
    // display if it's not in focus.
    acedGetAcadFrame()->SetActiveWindow();

    // Only COPY operation
    *pdwEffect = DROPEFFECT_COPY;

    return NOERROR;
}

BOOL CDropTarget::QueryData(IDataObject* pObjectData)
{
	FORMATETC formatEtc;
	SetDefFormatEtc(formatEtc,CF_TEXT, TYMED_HGLOBAL);

	if (SUCCEEDED(pObjectData->QueryGetData(&formatEtc)))
		return TRUE;
	else
		return FALSE;

}


	//IUnknown members
STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, PPVOID ppv)
{
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropTarget==riid)
        *ppv=this;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
{
    ++m_cRef;
    return m_cRef;
}

STDMETHODIMP_(ULONG) CDropTarget::Release(void)
{
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
}


///////////////////////// Dummy IDropTarget ///////////////////////////
CDummyDropTarget::CDummyDropTarget()
{
}

CDummyDropTarget::~CDummyDropTarget()
{
}

STDMETHODIMP 
CDummyDropTarget::DragEnter(IDataObject * pDataObject,
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
    *pdwEffect = DROPEFFECT_MOVE;
    return NOERROR;
}


STDMETHODIMP 
CDummyDropTarget::DragOver(
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
    *pdwEffect=DROPEFFECT_MOVE;
    return NOERROR;
}               
 


STDMETHODIMP 
CDummyDropTarget::DragLeave(void)
{
	return NOERROR;
}
 
STDMETHODIMP 
CDummyDropTarget::Drop(
    IDataObject * pDataObject,	//Points to the IDataObject interface for the source data
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect )	//Effect of the drag-and-drop operation
{
	BOOL fRet=TRUE;

	*pdwEffect = DROPEFFECT_NONE;

        return NOERROR;
}

	//IUnknown members
STDMETHODIMP CDummyDropTarget::QueryInterface(REFIID riid, PPVOID ppv)
{
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropTarget==riid)
        *ppv=this;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CDummyDropTarget::AddRef(void)
{
    ++m_cRef;
    return m_cRef;
}

STDMETHODIMP_(ULONG) CDummyDropTarget::Release(void)
{
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
}
