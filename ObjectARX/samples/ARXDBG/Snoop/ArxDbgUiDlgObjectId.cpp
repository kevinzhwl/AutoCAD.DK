//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//

#include "stdafx.h"
#include "ArxDbgUiDlgObjectId.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::ArxDbgUiDlgObjectId
**
**  **jma
**
*************************************/

ArxDbgUiDlgObjectId::ArxDbgUiDlgObjectId(const AcDbObjectId& objId, CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgObjectId::IDD, parent, ArxDbgApp::getApp()->dllInstance()),
	m_objId(objId)
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgObjectId)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjectId::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgObjectId)
    DDX_Control(pDX, ARXDBG_LC_VALUES, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgObjectId message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgObjectId, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgObjectId)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgObjectId message handlers

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgObjectId::OnInitDialog() 
{
    CAcUiDialog::OnInitDialog();
    
    buildColumns();
    display();
    
    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::buildColumns
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjectId::buildColumns()
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    m_dataList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 2;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.cx = col1_width;
    lvc.iSubItem = 0;
    lvc.pszText = _T("Field");
    m_dataList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    m_dataList.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::display
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjectId::display()
{
		// remove any existing items
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;
	SetDlgItemText(ARXDBG_TXT_OBJTYPE, ArxDbgUtils::objToClassAndHandleStr(m_objId, str));

	addToDataList(_T("Is Null"), ArxDbgUtils::booleanToStr(m_objId.isNull(), str));
	addToDataList(_T("Is Valid"), ArxDbgUtils::booleanToStr(m_objId.isValid(), str));
	addToDataList(_T("Is Erased"), ArxDbgUtils::booleanToStr(m_objId.isErased(), str));
	addToDataList(_T("Is Effectively Erased"), ArxDbgUtils::booleanToStr(m_objId.isEffectivelyErased(), str));
	addToDataList(_T("Object Left On Disk"), ArxDbgUtils::booleanToStr(m_objId.objectLeftOnDisk(), str));

    TCHAR tmpStr[256];
    m_objId.handle().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Handle"), tmpStr);

    m_objId.handle().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Non-Forwarded Handle"), tmpStr);

	addToDataList(_T("As Old Id"), ArxDbgUtils::intToStr(m_objId.asOldId(), str));

	addToDataList(_T("Database"), ArxDbgUtils::dbToStr(m_objId.database(), str));
	addToDataList(_T("Original Database"), ArxDbgUtils::dbToStr(m_objId.originalDatabase(), str));

	drawPropsList();
}

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::drawPropsList
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjectId::drawPropsList()
{
	this->LockWindowUpdate();		// suppress redraw events

    m_dataList.DeleteAllItems();	// remove any existing items from the control

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    POSITION pos1 = m_fieldStrList.GetHeadPosition();
    POSITION pos2 = m_valueStrList.GetHeadPosition();

    while ((pos1 != NULL) && (pos2 != NULL)) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        m_dataList.InsertItem(&lvi);
        m_dataList.SetItemText(row, 0, m_fieldStrList.GetNext(pos1));
        m_dataList.SetItemText(row, 1, m_valueStrList.GetNext(pos2));
        row++;
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxDbgUiDlgObjectId::addToDataList
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgObjectId::addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes)
{
    if (field == NULL)
		m_fieldStrList.AddTail(_T(""));
	else
		m_fieldStrList.AddTail(field);

    if (value == NULL) {
        m_valueStrList.AddTail(_T("(NULL)"));    // some Acad funcs return Null strings!
    }
    else {
        if (addQuotes) {
            CString str;
            str.Format(_T("\"%s\""), value);
            m_valueStrList.AddTail(str);
        }
        else
            m_valueStrList.AddTail(value);
    }
}