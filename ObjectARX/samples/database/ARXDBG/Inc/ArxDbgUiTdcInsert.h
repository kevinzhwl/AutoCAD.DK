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

#ifndef ARXDBGUITDCINSERT_H
#define ARXDBGUITDCINSERT_H

#include "Res_ArxDbg.h"
#include "ArxDbgCloneSet.h"
#include "SdStrObjId.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcInsert:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcInsert : public CAcUiTabChildDialog {

public:
				ArxDbgUiTdcInsert();
    virtual		~ArxDbgUiTdcInsert();

    //{{AFX_DATA(ArxDbgUiTdcInsert)
    enum { IDD = ARXDBG_TDC_INSERT };
	CListBox			m_lbSourceDb;
	CListBox			m_lbDestDb;
	BOOL				m_preserveOriginalDb;
	BOOL				m_saveAsDwg;
	CComboBox			m_puBlockDef;
	CEdit				m_ebDestName1;
	CEdit				m_ebDestName2;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcInsert)
    public:
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL

protected:

    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcInsert)
    afx_msg void OnInsertDb();
    afx_msg void OnInsertBlkDef();
    afx_msg void OnTransferBlkDef();
	afx_msg void OnSourceDatabaseChanged();
	afx_msg void OnDestDatabaseChanged();
	afx_msg void OnAddExternalDwg();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
	AcDbVoidPtrArray	m_dbPtrs;
	CStringArray		m_extDwgNames;
	SdStrObjIdList		m_blockList;

        // helper functions
	void			setButtonModes();
	void			displayDbLists();
	void			fillBlockList();
	AcDbDatabase*	getSourceDb(bool& isExternal);
	AcDbDatabase*	getDestDb();
	void			doSaveOption(AcDbDatabase* tmpDb);
	bool			hasDwgFile(CStringArray& dwgFiles, const CString& str);
	void			reloadRaidedExternalDwg(AcDbDatabase* db);
};

#endif    // ARXDBGUITDCINSERT_H
