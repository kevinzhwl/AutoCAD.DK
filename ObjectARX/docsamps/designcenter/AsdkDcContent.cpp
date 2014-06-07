// (C) Copyright 1999 by Autodesk, Inc. 
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

// AsdkDcContent.cpp : Implementation of CAsdkDcContent
#include "stdafx.h"
#include "AsdkDesignCenterSamp.h"
#include "AsdkDcContent.h"

/////////////////////////////////////////////////////////////////////////////
// CAsdkDcContent

STDMETHODIMP CAsdkDcContent::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IAsdkDcContent
    };
    for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i],riid))
            return S_OK;
    }
    return S_FALSE;
}

Adesk::Boolean append(AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;

    AcApDocument* pDoc = acDocManager->curDocument();

    Acad::ErrorStatus es = acDocManager->lockDocument(pDoc);
    if (es != Acad::eOk) {
        ads_alert("Failed to lock the document!");
        return Adesk::kFalse;
    }

    AcDbDatabase* pDb = pDoc->database();
    
    es = pDb/*acdbCurDwg()*/->getBlockTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_alert("Failed to get block table!");
        return Adesk::kFalse;
    }

    AcDbBlockTableRecord *pBlockRec;

    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
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
    
    acDocManager->unlockDocument(pDoc);

    return Adesk::kTrue;
}


STDMETHODIMP CAsdkDcContent::Initialize(VARIANT varBrowser, VARIANT)
{
    
    m_pBrowser = (IAcDcContentBrowser*)varBrowser.punkVal;
    m_pBrowser->AddRef();
    return S_OK; 
}

STDMETHODIMP CAsdkDcContent::SetImageLists()
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::NavigatorNodeExpanding(
            VARIANT varhNode,
            BSTR bstrFullPath)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::NavigatorNodeCollapsing(
            VARIANT varhNode,
            BSTR bstrFullPath)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::NavigatorNodeClick(
            VARIANT varhNode,
            BSTR bstrFullPath)
{

    return S_OK;
}

STDMETHODIMP CAsdkDcContent::NavigatorMouseUp(
            VARIANT varhNode,
            BSTR bstrFullPath,
            VARIANT varX, 
            VARIANT varY)
{
    return S_OK;
}

CString CAsdkDcContent::OpenAndReadTextFile(DWORD& length) 
{
    
    CFile fileText;
    fileText.Open(m_strSelectedItemText, CFile::modeRead);
    length = fileText.GetLength();
    char *strBuff = new char[length];
    fileText.Read(strBuff, length);
    fileText.Close();

    CString cstrBuff(strBuff);
    delete strBuff;

    cstrBuff.SetAt(length, '\0');
    cstrBuff.FreeExtra();

    return cstrBuff;
}

void CAsdkDcContent::OpenAndDisplayTextFile()
{

    DWORD length;
    CString cstrBuff = OpenAndReadTextFile(length);

    BSTR bstrBuf = cstrBuff.AllocSysString();

    m_pBrowser->SetItemDescription(bstrBuf);

    ::SysFreeString(bstrBuf);
}


STDMETHODIMP CAsdkDcContent::PaletteItemClick(BSTR bstrItemText)
{
    USES_CONVERSION;
    m_strSelectedItemText = OLE2T(bstrItemText);

    OpenAndDisplayTextFile();

    return S_OK;
}

void CAsdkDcContent::OpenAndInsertTextFile()
{

    DWORD length;
    CString cstrBuff = OpenAndReadTextFile(length);

    cstrBuff.Replace("\015\012", "\\P");
    
    struct resbuf resbufViewCtr;
    resbufViewCtr.restype = RT3DPOINT;
    acedGetVar("VIEWCTR", &resbufViewCtr);
    AcGePoint3d pt(resbufViewCtr.resval.rpoint[X],
                    resbufViewCtr.resval.rpoint[Y],
                    resbufViewCtr.resval.rpoint[Z]);

    AcDbMText *pMText = new AcDbMText();
    
    pMText->setLocation(pt);
    pMText->setContents(cstrBuff);

    append(pMText);

    pMText->downgradeOpen();
    pMText->draw();
    pMText->close();

}

STDMETHODIMP CAsdkDcContent::PaletteItemDblClick(BSTR bstrItemText)
{
    USES_CONVERSION;
    m_strSelectedItemText = OLE2T(bstrItemText);
    OpenAndInsertTextFile();

    return S_OK;
}

STDMETHODIMP CAsdkDcContent::PaletteColumnClick(
            VARIANT varIndex)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::PaletteMouseUp(
            VARIANT varButton,
            VARIANT varItemTexts,
            VARIANT varX, 
            VARIANT varY)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::PaletteMouseDown(
            VARIANT varButton,
            BSTR bstrFullText, 
            VARIANT varX, VARIANT varY)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::RenderPreviewWindow(
            BSTR bstrFullText,
            VARIANT varhPreviewWindow)
{

    return S_OK;
}

STDMETHODIMP CAsdkDcContent::PreviewMouseUp(
            VARIANT varButton, 
            VARIANT varX,
            VARIANT varY)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::Refresh()
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::PaletteBeginDrag(
            VARIANT varItemTexts,
            VARIANT varX, 
            VARIANT varY)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::ReleaseBrowser()
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::QueryContextMenu(
            VARIANT varhMenu,
            VARIANT varIndex,
            VARIANT varCmdFirst,
            VARIANT varCmdLast,
            VARIANT varItemTexts)
{
    return S_OK;
}

STDMETHODIMP CAsdkDcContent::InvokeCommand(VARIANT varMenuID)
{
    return S_OK;
}

STDMETHODIMP 
CAsdkDcContent::IsExpandable(/* [string][in] */ BSTR bstrItemText,
                            /* [retval][out] */ VARIANT __RPC_FAR *pvarIsExpandable)
{
    pvarIsExpandable->iVal = TRUE;
    return S_OK;
}
    
STDMETHODIMP 
CAsdkDcContent::GetLargeImage(/* [in] */ BSTR bstrFileName,
                                      /* [out][in] */ VARIANT __RPC_FAR *pvarhLargeImage)
{
    return E_NOTIMPL;
}

STDMETHODIMP
CAsdkDcContent::GetSmallImageListForContent(BSTR bstrFileName,
                                                    VARIANT *pvarhImageList)
{
    return E_NOTIMPL;
} 

STDMETHODIMP
CAsdkDcContent::GetLargeImageListForContent(BSTR bstrFileName,
                                                    VARIANT *pvarhImageList)
{
    return E_NOTIMPL;
} 

STDMETHODIMP
CAsdkDcContent::GetCommandString (
        /*[in]*/ VARIANT varMenuID          // menu id
        , /*[in]*/ dcMenuInfoFlag           // which information is required
        , /*[out]*/ VARIANT *pvarReserved   // reserved, handlers must ignore this
        , /*[out]*/ BSTR *pbstrName         // menu information
    )
{
    return E_NOTIMPL;
}

STDMETHODIMP
CAsdkDcContent::DeleteItemData(dcItemDataSource dcSrc, VARIANT varItemDataArray)
{
    return E_NOTIMPL;
} // CAsdkDcContent::DeleteItemData 
