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
// arxdrawView.cpp : implementation of the CArxdrawView class
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView

IMPLEMENT_DYNCREATE(CArxdrawView, CView)

BEGIN_MESSAGE_MAP(CArxdrawView, CView)
	//{{AFX_MSG_MAP(CArxdrawView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView construction/destruction

CArxdrawView::CArxdrawView()
{
	// TODO: add construction code here

    CDropSource *pSrc = new CDropSource;

    // getting AcadDwgView();
    CDropTarget *pTag = new CDropTarget();
    CDummyDropTarget *pDummyTag = new CDummyDropTarget();

    if (!SUCCEEDED(pSrc->QueryInterface(IID_IDropSource, (void**)&m_pDropSourceItf)))
        TRACE("Couldn't get DropSource\n");
    if (!SUCCEEDED(pTag->QueryInterface(IID_IDropTarget, (void**)&m_pDropTargetItf)))
        TRACE("Couldn't get DropTarget\n");
    if (!SUCCEEDED(pDummyTag->QueryInterface(IID_IDropTarget, (void**)&m_pDummyDropTargetItf)))
        TRACE("Couldn't get Dummy DropTarget\n");

}

CArxdrawView::~CArxdrawView()
{
	if (m_pDropSourceItf)
	    m_pDropSourceItf->Release();
        if (m_pDropTargetItf)
            m_pDropTargetItf->Release();
        if (m_pDummyDropTargetItf)
            m_pDummyDropTargetItf->Release();
}

BOOL CArxdrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    OnInitialUpdate();
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView drawing

void CArxdrawView::OnDraw(CDC* pDC)
{
    // TODO: add draw code for native data here

        CRect rect;
	GetClientRect(rect);

    int nRow =40;
    int i;

    for (i =1; i <=4; i++)
    {
        pDC->MoveTo (0, i*nRow);
        pDC->LineTo (rect.right, i*nRow);
    }

    pDC->TextOut(0,5, CString("Shuttle.dwg"));
    pDC->TextOut(0,5+ nRow*1, CString("Stair.dwg"));
    pDC->TextOut(0,5+ nRow*2, CString("Circle.dwg"));
    pDC->TextOut(0,5+ nRow*3, CString("Logo.dwg"));

}

/////////////////////////////////////////////////////////////////////////////
// CArxdrawView diagnostics

#if defined(_DEBUG ) && defined(DEBUG_AUTOCAD)
void CArxdrawView::AssertValid() const
{
	CView::AssertValid();
}

void CArxdrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG && DEBUG_AUTOCAD



/////////////////////////////////////////////////////////////////////////////
// CArxdrawView message handlers

void CArxdrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

    HRESULT hRes;
    DWORD dwEffect;

    IDataObject *pData;
    int iFile;

    char *pFiles[] = {"shuttle",
                      "stair",
                      "circle",
                      "logo"
    };
                      
    iFile = point.y / 40;

    
    ASSERT(iFile >=0 && iFile < 4);
    
    CString filename = pFiles[iFile];
    CDataObj *pDataObj = new CDataObj(filename);
    if (!SUCCEEDED(pDataObj->QueryInterface(IID_IDataObject, (void**) &pData)))
        TRACE("Can't get IDataObject\n");
      
    m_pDropSourceItf->AddRef();

    if (!acedRegisterCustomDropTarget(m_pDropTargetItf))
        TRACE("Error in registering Custom drop target!\n");

    hRes = DoDragDrop(pData, m_pDropSourceItf, DROPEFFECT_NONE |DROPEFFECT_MOVE | DROPEFFECT_COPY,
		     &dwEffect);

    if (!acedRevokeCustomDropTarget())
        TRACE("Error in revoking custom drop target\n");

    CMDIFrameWnd  *pWnd = acedGetAcadFrame();
    pWnd->SetActiveWindow();
    pWnd->SetFocus();

    m_pDropSourceItf->Release();
    pData->Release();
}

void CArxdrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonUp(nFlags, point);
}


void CArxdrawView::OnInitialUpdate() 
{
      if (FAILED(OleInitialize(NULL)))
          TRACE("OUCH!! Can't initialize ole\n");

  // TODO: Add your specialized code here and/or call the base class
      if (NULL != m_pDropTargetItf)
      {
          m_pDropTargetItf->AddRef();
 	  if (CoLockObjectExternal(m_pDropTargetItf, TRUE, FALSE) != S_OK)
          {
              TRACE("Can't lock Droptarget object\n");
	  return ;
          }
      }
      
      if (NULL != m_pDummyDropTargetItf)
      {
          m_pDummyDropTargetItf->AddRef();
 	  if (CoLockObjectExternal(m_pDummyDropTargetItf, TRUE, FALSE) != S_OK)
          {
              TRACE("Can't lock dummy Droptarget object\n");
	  return ;
          }
          
          HWND hWnd = GetSafeHwnd();
          ASSERT(m_pDummyDropTargetItf);
          m_pDummyDropTargetItf->AddRef();
          RegisterDragDrop(hWnd, (LPDROPTARGET)m_pDummyDropTargetItf);
      }
  
}

void CArxdrawView::OnDestroy() 
{
	CView::OnDestroy();
    if (NULL != m_pDropTargetItf)
    {
        CoLockObjectExternal(m_pDropTargetItf, FALSE, TRUE);
        m_pDropTargetItf->Release();
    }
    if (NULL != m_pDummyDropTargetItf)
    {
        RevokeDragDrop(GetSafeHwnd());
        CoLockObjectExternal(m_pDummyDropTargetItf, FALSE, TRUE);
        m_pDummyDropTargetItf->Release();
    }

    OleUninitialize();
}

