//////////////////////////////////////////////////////////////////////////////
//
//               (C) Copyright 1994-2010 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiListBox_h
#define _aduiListBox_h
#pragma pack (push, 8)

#pragma once

#ifndef _ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
// CAdUiListBox window
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiListBox : public CListBox {
    DECLARE_DYNAMIC(CAdUiListBox);

public:
                CAdUiListBox ();
virtual         ~CAdUiListBox ();

// Misc.
protected:
        CPoint  m_lastMousePoint;
        int     m_tipItem;
        CRect   m_tipRect;

public:
virtual void    GetContentExtent (
                    int item, LPCTSTR text, int& width, int& height
                );
        int     GetItemAtPoint (CPoint& p);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    IsOwnerDraw ();

// AdUi message handlers
protected:
        CWnd    *m_aduiParent;

virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual void    OnDrawTip (CDC& dc);
virtual BOOL    OnDrawTipText (CAdUiDrawTipText& dtt);
virtual ADUI_REPLY OnGetTipSupport (CPoint& p);
virtual BOOL    OnGetTipRect (CRect& r);
virtual BOOL    OnGetTipText (CString& text);
virtual BOOL    OnHitTipRect (CPoint& p);
public:
        CWnd    *GetAdUiParent ();
        void    SetAdUiParent (CWnd *w);

// Subclassed ComboLBox support
protected:
        BOOL    m_bComboBoxDraw;
        CAdUiComboBox *m_pComboBox;

public:
        CAdUiComboBox *GetComboBox ();
        void    SetComboBox (CAdUiComboBox *control);
        BOOL    GetComboBoxDraw ();
        void    SetComboBoxDraw (BOOL comboBoxDraw);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiListBox)
    virtual int  CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
    virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiListBox)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnDestroy();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
