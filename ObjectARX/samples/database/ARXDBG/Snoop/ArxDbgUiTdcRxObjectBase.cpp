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
#include "ArxDbgUiTdcRxObjectBase.h"
#include "ArxDbgUtils.h"
#include "ArxDbgApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::ArxDbgUiTdcRxObjectBase
**
**  **jma
**
*************************************/

ArxDbgUiTdcRxObjectBase::ArxDbgUiTdcRxObjectBase()
:	CAcUiTabChildDialog(NULL, ArxDbgApp::getApp()->dllInstance()),
	m_dataListCtrl(NULL)
{
}

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcRxObjectBase::DoDataExchange(CDataExchange* pDX)
{
    CAcUiTabChildDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcRxObjectBase)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcRxObjectBase message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcRxObjectBase, CAcUiTabChildDialog)
    //{{AFX_MSG_MAP(ArxDbgUiTdcRxObjectBase)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcRxObjectBase message handlers

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::buildColumns
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcRxObjectBase::buildColumns(CListCtrl& dataList)
{
        // get the width of the window
    CRect lvRect;
    int col1_width, col2_width;
    dataList.GetClientRect(lvRect);
    col1_width = lvRect.Width() / 2;
    col2_width = lvRect.Width() - col1_width - ::GetSystemMetrics(SM_CXVSCROLL);

        // initialize the columns
    LV_COLUMN lvc;
    lvc.mask = LVCF_WIDTH | LVCF_SUBITEM | LVCF_TEXT;
    lvc.cx = col1_width;
    lvc.pszText = _T("Field");
    lvc.iSubItem = 0;
    dataList.InsertColumn(0, &lvc);

    lvc.cx = col2_width;
    lvc.iSubItem = 1;
    lvc.pszText = _T("Value");
    dataList.InsertColumn(1, &lvc);
}

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::drawPropsList
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcRxObjectBase::drawPropsList(CListCtrl& dataList)
{
	this->LockWindowUpdate();		// suppress redraw events

    dataList.DeleteAllItems();		// remove any existing items from the control

        // build up the list view control
    LV_ITEM lvi;
    lvi.mask = 0;
    int row = 0;

    POSITION pos1 = m_fieldStrList.GetHeadPosition();
    POSITION pos2 = m_valueStrList.GetHeadPosition();

    while ((pos1 != NULL) && (pos2 != NULL)) {
        lvi.iItem = row;
        lvi.iSubItem = 0;
        dataList.InsertItem(&lvi);
        dataList.SetItemText(row, 0, m_fieldStrList.GetNext(pos1));
        dataList.SetItemText(row, 1, m_valueStrList.GetNext(pos2));
        row++;
    }

	this->UnlockWindowUpdate();		// flushes redraw events
}

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::addToDataList
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcRxObjectBase::addToDataList(LPCTSTR field, LPCTSTR value, bool addQuotes)
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

/****************************************************************************
**
**  ArxDbgUiTdcRxObjectBase::addSeperatorLine
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcRxObjectBase::addSeperatorLine(LPCTSTR className)
{
    CString str;

    str.Format(_T("------ %s ------"), className);
    addToDataList(str, _T(""));
}

