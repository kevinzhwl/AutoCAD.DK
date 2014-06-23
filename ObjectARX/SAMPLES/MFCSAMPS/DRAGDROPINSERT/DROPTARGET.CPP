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


BOOL gInsertDwg= FALSE;
BOOL removeWindowsHook();
BOOL addWindowsHook();


BOOL filterInsertDD(MSG *pMsg)
{
    if (pMsg->message == WM_LBUTTONUP)
    {
        pMsg->message = WM_LBUTTONDOWN; 
        removeWindowsHook();  // no longer needs the hook
    }
    return FALSE; // continue
}

BOOL removeWindowsHook()
{
    return acedRemoveFilterWinMsg(filterInsertDD); 
}


BOOL addWindowsHook()
{
    BOOL bRes;
    if ((bRes = acedRegisterFilterWinMsg(filterInsertDD)) == FALSE)
        ads_printf("Can't register Windows Msg hook ");
    return bRes;
}


BOOL PasteFromData(IDataObject* pDataObject, CString &fileBuf)
{
	FORMATETC formatEtc;
	STGMEDIUM medium;
	
	SetDefFormatEtc(formatEtc,CF_TEXT, TYMED_HGLOBAL);
	if (!SUCCEEDED(pDataObject->GetData(&formatEtc, &medium)))
		return FALSE;
                
	char * pstr = (char*) GlobalLock (medium.hGlobal);
        fileBuf = pstr;
	GlobalUnlock(medium.hGlobal);

	ReleaseStgMedium(&medium);
	
	return TRUE;
}



CDropTarget::CDropTarget()
{
	m_pIDataObject = NULL;
        m_cRef =0;
}

CDropTarget::~CDropTarget()
{
}


void sendCommandToAutoCAD(CString cmd)
{
    CWnd *pWnd = acedGetAcadDockCmdLine();

    int len = cmd.GetLength();
    for (int i=0; i < len ; i++)
        pWnd->SendMessage(WM_CHAR, (TCHAR)cmd[i], 0);
}


extern void acedInsertDwg(char *blockName);

STDMETHODIMP 
CDropTarget::DragEnter(IDataObject * pDataObject,
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
    gInsertDwg= FALSE;

    // get file Name from pDataObject
    CString filename;
    CString cmdStr;
    ::PasteFromData(pDataObject, filename);;

    cmdStr = "insert " + filename + "\n";

    sendCommandToAutoCAD(cmdStr);

    // Plant Windows hook here  that will replace LButtonUp w/ DoubleClick
    addWindowsHook();

    *pdwEffect=DROPEFFECT_COPY;

    return NOERROR;
}


STDMETHODIMP 
CDropTarget::DragOver(
    DWORD grfKeyState,	//Current state of keyboard modifier keys
    POINTL pt,	//Current cursor coordinates
    DWORD * pdwEffect)	//Effect of the drag-and-drop operation
{
    gInsertDwg= TRUE;
    *pdwEffect=DROPEFFECT_COPY;
    return NOERROR;
}


STDMETHODIMP 
CDropTarget::DragLeave(void)
{

    gInsertDwg= FALSE;
    
    if (m_pIDataObject !=NULL)
    {
	    m_pIDataObject->Release();
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
    DragLeave();
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
