//////////////////////////////////////////////////////////////////////////////
//  (C) Copyright 2002 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for Status Bar Classes.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ACSTATUSBAR_H
#define _ACSTATUSBAR_H 1

#pragma pack (push, 8)

#include "acdocman.h"

class AcStatusBarItem
{
public:
    AcStatusBarItem();
    virtual ~AcStatusBarItem();

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

    virtual BOOL SetToolTipText(const CString& strText);
    virtual BOOL GetToolTipText(CString& strText) const;

    virtual BOOL QueryToolTipText(CString& strText) const;

    virtual void Enable(BOOL bValue);
    virtual BOOL IsEnabled();

    virtual void SetVisible(BOOL bIsVisible);
    virtual BOOL IsVisible();

    virtual void OnLButtonDown(UINT nFlags, CPoint point);
    virtual void OnRButtonDown(UINT nFlags, CPoint point);
    virtual void OnLButtonDblClk(UINT nFlags, CPoint point);

    virtual void OnDelete();

    virtual BOOL ClientToScreen(LPPOINT lpPoint);
    virtual BOOL ClientToScreen(LPRECT lpRect);

    virtual BOOL ScreenToClient(LPPOINT lpPoint);
    virtual BOOL ScreenToClient(LPRECT lpRect);

    virtual UINT DisplayContextMenu(CMenu& menu, CPoint point);

    virtual BOOL ShowTraySettingsDialog();

    //////////////////////////////////////////////////////////////////////////////
    // Note: These methods are for INTERNAL USE ONLY.  Using these methods may
    //       adversely affect application functionality
    virtual void SetContentChanged(BOOL bChanged) {m_bContentChanged = bChanged;}
    virtual BOOL ContentChanged() const {return m_bContentChanged;}

    virtual void SetVisibilityChanged(BOOL bChanged) {m_bVisibilityChanged = bChanged;}
    virtual BOOL VisibilityChanged() const {return m_bVisibilityChanged;}

    virtual void SetInternalData(void* pData, BOOL bForDocSwitch = FALSE);
    virtual void* GetInternalData(BOOL bForDocSwitch = TRUE) const;
   // End INTERNAL USE ONLY.
    //////////////////////////////////////////////////////////////////////////////
private:
    HICON           m_hIcon;
    CString         m_strToolTipText;
    BOOL            m_bEnabled;
    BOOL            m_bVisible;
    BOOL            m_bContentChanged;
    BOOL            m_bVisibilityChanged;
    void*           m_pData;
    void*           m_pDocSwitchData;
};

#define ACSB_NOBORDERS  (1<<0)
#define ACSB_POPOUT     (1<<1)
#define ACSB_STRETCH    (1<<2)
#define ACSB_NORMAL     (1<<3)
#define ACSB_COMMAND    (1<<4)
#define ACSB_POPUP      (1<<5)

class AcPane : public AcStatusBarItem
{
public:
    AcPane();
    virtual ~AcPane();

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

    virtual BOOL SetText(const CString& strText);
    virtual BOOL GetText(CString& strText) const;

    virtual BOOL SetStyle(int nStyle);
    virtual int GetStyle() const;

    virtual BOOL SetMinWidth(int cxWidth);
    virtual int GetMinWidth();

    virtual BOOL SetMaxWidth(int cxWidth);
    virtual int GetMaxWidth();

    virtual UINT DisplayPopupPaneMenu(CMenu& menu);

private:
    CString m_strText;
    int     m_nStyle;
    int     m_cxMinWidth;
    int     m_cxMaxWidth;
};

typedef void (*AcTrayItemBubbleWindowCallbackFunc)(void *, int);
typedef void *AcTrayItemBubbleWindowCallbackData;

class AcTrayItemBubbleWindowControl
{
public:
    AcTrayItemBubbleWindowControl();
    AcTrayItemBubbleWindowControl(
            const CString& strTitle,
            const CString& strText,
            const CString& strHyperText = "",
            const CString& strHyperLink = ""
            );
    ~AcTrayItemBubbleWindowControl();

    void SetIconType(int nIconType) { m_nIconType = nIconType; }
    void SetTitle(const CString& strTitle) { m_strTitle = strTitle; }
    void SetText(const CString& strText) { m_strText = strText; }
    void SetHyperText(const CString& strHyperText) { m_strHyperText = strHyperText; }
    void SetHyperLink(const CString& strHyperLink) { m_strHyperLink = strHyperLink; }
    void SetCallback(AcTrayItemBubbleWindowCallbackFunc pCallbackFunc, AcTrayItemBubbleWindowCallbackData pCallbackData = 0)
    {
        m_pCallbackFunc = pCallbackFunc;
        m_pCallbackData = pCallbackData;
    }

    int GetIconType() const { return m_nIconType; };
    const CString& GetTitle() const { return m_strTitle; }
    const CString& GetText() const { return m_strText; }
    const CString& GetHyperText() const { return m_strHyperText; }
    const CString& GetHyperLink() const { return m_strHyperLink; }
    AcTrayItemBubbleWindowCallbackFunc GetCallbackFunc() const { return m_pCallbackFunc; }
    AcTrayItemBubbleWindowCallbackData GetCallbackData() const { return m_pCallbackData; }

    enum
    {
        BUBBLE_WINDOW_ICON_NONE,
        BUBBLE_WINDOW_ICON_INFORMATION,
        BUBBLE_WINDOW_ICON_CRITICAL,
        BUBBLE_WINDOW_ICON_WARNING,
    };

    enum
    {
        BUBBLE_WINDOW_ERROR_NO_CREATE,
        BUBBLE_WINDOW_ERROR_NO_ICONS,
        BUBBLE_WINDOW_ERROR_NO_NOTIFICATIONS,
        BUBBLE_WINDOW_CLOSE,
        BUBBLE_WINDOW_TIME_OUT,
        BUBBLE_WINDOW_HYPERLINK_CLICK,
        BUBBLE_WINDOW_DOCUMENT_DEACTIVATED
    };

private:
    void InitDefault()
    {
        m_pCallbackFunc = 0;
        m_pCallbackData = 0;
        m_nIconType = BUBBLE_WINDOW_ICON_INFORMATION;
    }

    int                                 m_nIconType;
    CString                             m_strTitle;
    CString                             m_strText;
    CString                             m_strHyperText;
    CString                             m_strHyperLink;
    AcTrayItemBubbleWindowCallbackFunc  m_pCallbackFunc;
    AcTrayItemBubbleWindowCallbackData  m_pCallbackData;
};

class AcTrayItem : public AcStatusBarItem
{
public:
    AcTrayItem();
    virtual ~AcTrayItem();

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

    virtual BOOL ShowBubbleWindow(AcTrayItemBubbleWindowControl* pBubbleWindowControl);
    virtual AcTrayItemBubbleWindowControl* GetBubbleWindowControl() const;

    virtual BOOL CloseAllBubbleWindows();

private:
    AcTrayItemBubbleWindowControl   m_BubbleWindowControl;
    AcTrayItemBubbleWindowControl   *m_pBubbleWindowControl;
};

enum AcDefaultPane
{
    ACSBPANE_APP_MODEMACRO,
    ACSBPANE_APP_CURSORCOORD,
    ACSBPANE_APP_SNAP,
    ACSBPANE_APP_GRID,
    ACSBPANE_APP_ORTHO,
    ACSBPANE_APP_POLAR,
    ACSBPANE_APP_OTRACK,
    ACSBPANE_APP_LINEWEIGHT,
    ACSBPANE_APP_PAPERMODEL,
        ACSBPANE_APP_PAPER,
        ACSBPANE_APP_MODEL,
    ACSBPANE_APP_OSNAP,
    ACSBPANE_APP_FLOAT,
    ACSBPANE_APP_TABLET,
    ACSBPANE_APP_ALL,
};

class AcApStatusBar
{
public:
    virtual BOOL Insert(int nIndex, AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Insert(int nIndex, AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

    virtual BOOL Remove(AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Remove(AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Remove(int nIndex, BOOL bTrayItem = FALSE, BOOL bUpdate = TRUE) = 0;

    virtual BOOL RemoveAllPanes(BOOL bUpdate = TRUE) = 0;

    virtual int Add(AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual int Add(AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

    virtual void Update() = 0;

    virtual int GetIndex(AcPane* pPane) const = 0;
    virtual int GetIndex(AcTrayItem* pTrayItem) const = 0;
    virtual int GetIndex(int nID, BOOL bTrayItem = FALSE) const = 0;

    virtual int GetID(AcPane* pPane) const = 0;
    virtual int GetID(AcTrayItem* pTrayItem) const = 0;
    virtual int GetID(int nIndex, BOOL bTrayItem = FALSE) const = 0;

    virtual int GetPaneCount() const = 0;

    virtual AcPane* GetPane(int nIndex) = 0;

    virtual int GetTrayItemCount() const = 0;

    virtual AcTrayItem* GetTrayItem(int nIndex) = 0;

    virtual BOOL RemoveAllTrayIcons(BOOL bUpdate = TRUE) = 0;

    virtual BOOL ClientToScreen(LPPOINT lpPoint) = 0;
    virtual BOOL ClientToScreen(LPRECT lpRect) = 0;

    virtual BOOL ScreenToClient(LPPOINT lpPoint) = 0;
    virtual BOOL ScreenToClient(LPRECT lpRect) = 0;

    virtual int GetTextWidth(const CString& strText) const = 0;

    virtual UINT DisplayContextMenu(CMenu& menu, CPoint point) = 0;
    virtual UINT DisplayPopupPaneMenu(AcPane* pPane, CMenu& menu) = 0;

    virtual BOOL GetTraySettingsShowIcons() const = 0;
    virtual BOOL GetTraySettingsShowNotifications() const = 0;

    virtual void ShowStatusBarMenuIcon(BOOL bShow) = 0;

    virtual BOOL SetStatusBarMenuItem(AcPane* pPane) = 0;

    virtual BOOL ShowTraySettingsDialog() = 0;

    virtual AcPane* GetDefaultPane(AcDefaultPane nPane) = 0;
    virtual BOOL RemoveDefaultPane(AcDefaultPane nPane, BOOL bUpdate = TRUE) = 0;

    virtual BOOL CloseAllBubbleWindows(AcTrayItem* pTrayItem) = 0;

};

#pragma pack (pop)
#endif // ACSTATUSBAR_H

