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

#ifndef ARXDBGUITDCREFERENCES_H
#define ARXDBGUITDCREFERENCES_H

#include "ArxDbgUiTdcDbObjectBase.h"

/****************************************************************************
**
**	CLASS ArxDbgUiTdcReferences:
**
**	**jma
**
*************************************/

class ArxDbgUiTdcReferences : public ArxDbgUiTdcDbObjectBase {

public:
				ArxDbgUiTdcReferences(const AcDbObjectIdArray& hardPointerIds,
									  const AcDbObjectIdArray& softPointerIds,
									  const AcDbObjectIdArray& hardOwnershipIds,
									  const AcDbObjectIdArray& softOwnershipIds);
    virtual		~ArxDbgUiTdcReferences()    {}

    //{{AFX_DATA(ArxDbgUiTdcReferences)
    enum { IDD = ARXDBG_TDC_ENTS };
    CStatic		m_txtErased;
    CListCtrl	m_dataList;
    CTreeCtrl	m_entTree;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcReferences)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcReferences)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangedEnts(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members
    const AcDbObjectIdArray&	m_hardPointerIds;
    const AcDbObjectIdArray&	m_softPointerIds;
    const AcDbObjectIdArray&	m_hardOwnershipIds;
    const AcDbObjectIdArray&	m_softOwnershipIds;
    AcDbObjectIdArray			m_treeObjIdList;		// tblentry Object Ids

		// helper functions
    HTREEITEM	addOneTreeItem(LPCTSTR name, const AcDbObject* obj, HTREEITEM parent, bool sort = false);
    void        addEntriesToTree(const AcDbObjectIdArray& ids, HTREEITEM parent);

    void        displayCurrent(int index);

};


#endif    // ARXDBGUITDCENTITIES_H
