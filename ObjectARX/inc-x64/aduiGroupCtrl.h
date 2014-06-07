//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 2004-2007 by Autodesk, Inc.
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

#ifndef _aduiGroupCtrl_h
#define _aduiGroupCtrl_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vector>

///////////////////////////////////////////////////////////////////////////////
/// CAdUiGroupCtrl class is ownerdrawin group control class that has a header
/// on the top with a title, bitmap buttons and chevron button. Chevron button
/// when clicked, minimizes or maximizes the control. This control can host a
/// CWnd control in the client region. Bitmap button can be used to display 
/// different views in the CWnd in the client region or display a different 
/// window
///

/// Callback function that will be called when bitmap button
/// on the header control is clicked.
///
typedef void (*AdUiBmpBtnFcnPtr)(CWnd*);

// Struct that maintains data related to each window that is
// added to the group control
typedef struct AdUiGroupCtrlData
{
    AdUiGroupCtrlData() : nWndIndex(0), title(/*MSG0*/""), pWnd(NULL), dwBtnCookie(-1) {};
    int nWndIndex;
    CString title;
    CWnd* pWnd;
    DWORD dwBtnCookie;
} groupData;
typedef std::vector<groupData> ADUIGROUPCTRLDATALIST;

// Struct that bundles all the required information to draw
// a bitmap button and also call it's callback funtion when
// the button is clicked
typedef struct AdUiBmpBtnData
{
    AdUiBmpBtnData() : pBmp(NULL), fcnPtr(NULL), 
        tooltip(/*MSG0*/""), dwCookie(0) {};
    CBitmap* pBmp;
    AdUiBmpBtnFcnPtr fcnPtr;
    CString tooltip;
    DWORD dwCookie;
} bmpBtnData;
typedef std::vector<bmpBtnData> ADUIHEADERBTNLIST;

// additional NC hittest codes
#define ADUI_NCHT_BASE      (HTHELP + 200)
#define ADUI_NCHT_TITLE     ADUI_NCHT_BASE
#define ADUI_NCHT_CHEVRON   (ADUI_NCHT_BASE + 1)
#define ADUI_NCHT_BUTTON    (ADUI_NCHT_BASE + 2)

// position/size for controls in NC bar
#define ADUI_GROUP_BORDER_SIZE              1
#define ADUI_GROUP_TITLE_HEIGHT             18
#define ADUI_GROUP_TITLE_BEVELSIZE          5
#define ADUI_GROUP_TITLE_TEXTLEFT           10
#define ADUI_GROUP_TITLE_TEXTTOP            1
#define ADUI_GROUP_BUTTON_SIZE              14
#define ADUI_GROUP_BUTTONS_RIGHT            25  //was 18
#define ADUI_GROUP_BUTTON_TOPPADDING        2
#define ADUI_GROUP_BUTTON_BOTTOMPADDING     2
#define ADUI_GROUP_BUTTON_SPACE             3
#define ADUI_GROUP_CHEVRON_RIGHT            6
#define ADUI_GROUP_CHILD_VERT_SPACE         12 

// Group styles
#define ADUI_GROUP_STYLE_CHEVRON        0x00000001
#define ADUI_GROUP_STYLE_SHOWBTNFORCE   0x00000002
#define ADUI_GROUP_STYLE_NONACTIVE      0x00000004

// wParam is the CWnd* to be shown/hide, lParam is SW_SHOW or SW_HIDE.
const DWORD WM_ADUI_VISIBILITY_CHANGING = WM_USER + 1936; 

/////////////////////////////////////////////////////////////////////////////
// CAdUiGroupCtrl window
#pragma warning(push)
#pragma warning(disable : 4275)

/// <summary>
/// CAdUiGroupCtrl class is ownerdrawin group control class that has a header
/// on the top with a title, bitmap buttons and chevron button. Chevron button
/// when clicked, minimizes or maximizes the control. This control can host a
/// CWnd control in the client region. Bitmap button can be used to display 
/// different views in the CWnd in the client region or display a different 
/// window.
/// </summary>
///
class ADUI_PORT CAdUiGroupCtrl : public CStatic {
    DECLARE_DYNAMIC(CAdUiGroupCtrl);

public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    CAdUiGroupCtrl( );
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~CAdUiGroupCtrl();

    // Method to add your window to the group control
    /// <summary>
    /// Method to add window and it's title to the group control. This method 
    /// can be called n number of times to add n windows.
    /// </summary>
    ///
    /// <param name="pWnd">
    /// Input pointer to a CWnd.
    /// </param>
    /// <param name="pszTitle">
    /// Title for the window.
    /// </param>
    /// <param name="pBMP">
    /// Input pointer to a CBitmap.
    /// </param>
    /// <returns>
    /// Returns true when the window is added to the group control.
    /// </returns>
    /// <remarks>
    /// This method can be called n number of time to add n windows. 
    /// There is a list of AdUiGroupCtrlData that is created with the CWnd,
    /// title and index (based on the order in which windows are added). 
    /// The use of adding multiple windows is to display different windows 
    /// when the bitmap buttons are selected on the group control header.
    /// </remarks>
    ///
    virtual bool AddWnd(CWnd* pWnd, LPCTSTR pszTitle, CBitmap* pBMP = NULL);

    // Method to add your window to the group control
    /// <summary>
    /// Method to add window and it's title to the group control. This method 
    /// can be called n number of times to add n windows.
    /// </summary>
    ///
    /// <param name="pWnd">
    /// Input pointer to a CWnd.
    /// </param>
    /// <param name="pszTitle">
    /// Title for the window.
    /// </param>
    /// <param name="pszResName">
    /// Input string specifying the name of the resource for the bitmap.
    /// </param>
    /// <returns>
    /// Returns true when the window is added to the group control.
    /// </returns>
    /// <remarks>
    /// This method can be called n number of time to add n windows. 
    /// There is a list of AdUiGroupCtrlData that is created with the CWnd,
    /// title and index (based on the order in which windows are added). 
    /// The use of adding multiple windows is to display different windows 
    /// when the bitmap buttons are selected on the group control header.
    /// </remarks>
    ///
    virtual bool AddWnd(CWnd* pWnd, LPCTSTR pszTitle, LPCTSTR pszResName);

    /// <summary>
    /// Displays the window represented by the input CWnd pointer in the 
    /// group controls client area.
    /// </summary>
    ///
    /// <param name="pWnd">
    /// Input pointer to the CWnd which will be hosted in the client area
    /// of the group control.
    /// </param>
    /// <returns>
    /// Returns true if successful, otherwise returns false.
    /// </returns>
    ///
    virtual bool ShowWnd(CWnd* pWnd);
    // Methods to add bitmap buttons to header
    /// <summary>
    /// Method to add bitmap buttons to group control header by specifying
    /// the bitmap name, callback function pointer and the tooltip. This 
    /// function returns a cookie back to the caller, which can be used to
    /// delete a bitmap button.
    /// </summary>
    ///
    /// <param name="pszResName">
    /// Input string specifying the name of the resource for the bitmap.
    /// </param>
    /// <param name="fcnPtr">
    /// Callback function that will be called when this bitmap button is clicked.
    /// Callback function is defined as a typedef as follows:
    /// typedef void (*AdUiBmpBtnFcnPtr)()
    /// void AdUiBmpBtnFcnPtr() Method
    /// A function pointer that a client needs to implement for each of the header
    /// buttons, which is called when it's corresponding header button is clicked
    /// </param>
    /// <param name="dwCookie">
    /// Output DWORD value identifying the bitmap that was added.
    /// </param>
    /// <param name="pszToolTip">
    /// Input string containing the tooltip for the bitmap button.
    /// </param>
    /// <returns>
    /// Returns true if successful, otherwise returns false.
    /// </returns>
    /// <remarks>
    /// Callback function is defined as a typedef as follows:
    /// typedef void (*AdUiBmpBtnFcnPtr)()
    /// void AdUiBmpBtnFcnPtr() Method
    /// A function pointer that a client needs to implement for each of the header
    /// buttons, which is called when it's corresponding header button is clicked
    /// </remarks>
    ///
    virtual bool AddBmpBtnToHeader(LPCTSTR pszResName, 
                                   AdUiBmpBtnFcnPtr fcnPtr,
                                   DWORD& dwCookie,
                                   LPCTSTR pszToolTip);
    // Methods to add bitmap buttons to header
    /// <summary>
    /// Method to add bitmap buttons to group control header by specifying
    /// a pointer to the CBitmap, callback function pointer and the tooltip. 
    /// This function returns a cookie back to the caller, which can be used 
    /// to delete a bitmap button.
    /// </summary>
    ///
    /// <param name="pBmp">
    /// Input pointer to a CBitmap that will be used for the bitmap button.
    /// </param>
    /// <param name="fcnPtr">
    /// Callback function that will be called when this bitmap button is clicked.
    /// Callback function is defined as a typedef as follows:
    /// typedef void (*AdUiBmpBtnFcnPtr)()
    /// void AdUiBmpBtnFcnPtr() Method
    /// A function pointer that a client needs to implement for each of the header
    /// buttons, which is called when it's corresponding header button is clicked
    /// </param>
    /// <param name="dwCookie">
    /// Output DWORD value identifying the bitmap that was added.
    /// </param>
    /// <param name="pszToolTip">
    /// Input string containing the tooltip for the bitmap button.
    /// </param>
    /// <returns>
    /// Returns true if successful, otherwise returns false.
    /// </returns>
    /// <remarks>
    /// Callback function is defined as a typedef as follows:
    /// typedef void (*AdUiBmpBtnFcnPtr)()
    /// void AdUiBmpBtnFcnPtr() Method
    /// A function pointer that a client needs to implement for each of the header
    /// buttons, which is called when it's corresponding header button is clicked
    /// </remarks>
    ///
    virtual bool AddBmpBtnToHeader(CBitmap* pBmp, 
                                   AdUiBmpBtnFcnPtr fcnPtr, 
                                   DWORD& dwCookie,
                                   LPCTSTR pszToolTip);
    // Method to remove a btn from the header of the group control
    /// <summary>
    /// Method to remove a btn from the header of the group control.
    /// </summary>
    ///
    /// <param name="dwCookie">
    /// Input to a cookie identifying the bitmap button that need to be removed
    /// from the group control's header.
    /// </param>
    /// <returns>
    /// Returns true if the button is deleted, otherwise returns false.
    /// </returns>
    ///
    virtual bool RemoveBmpBtnFromHeader(DWORD dwCookie);

    /// <summary>
    /// Function to add or remove styles on the group control.
    /// </summary>
    ///
    /// <param name="styleRemove">
    /// Input parameter that defines the window styles that needs be removed.
    /// </param>
    /// <param name="styleAdd">
    /// Input parameter that defines the window styles that need to be added.
    /// </param>
    ///
    virtual void ModGroupStyle(DWORD styleRemove, DWORD styleAdd);

    /// <summary>
    /// Sets the theme for the group control based on the theme that is 
    /// passed in.
    /// </summary>
    ///
    /// <param name="pTheme">
    /// Input parameter to a CAdUiTheme pointer, whose theme colors will be
    /// used to draw the group control.
    /// </param>
    ///
    virtual void SetTheme(CAdUiTheme* pTheme);

    /// <summary>
    /// Calls the over-loaded method SetFont with argument redraw set to TRUE.
    /// </summary>
    ///
    /// <param name="pFont">
    /// Input pointer to the CFont object.
    /// </param>
    ///
    virtual void SetFont(CFont* pFont);

    /// <summary>
    /// Set the font style to BOLD and calls the CWnd base class SetFont 
    /// function. Also calls SetFont on all the child windows that are 
    /// added to the group control.
    /// </summary>
    ///
    /// <param name="pFont">
    /// Input pointer to the CFont object.
    /// </param>
    /// <param name="bRedraw">
    /// Input boolean specifying whether to redraw the control or not.
    /// </param>
    ///
    virtual void SetFont(CFont* pFont, BOOL bRedraw);

    /// <summary>
    /// Sets the minimized or maximized state on the group control.
    /// </summary>
    ///
    /// <param name="bMinimized">
    /// Input parameter to set the minimized or maximized state on the 
    /// group control.
    /// </param>
    ///
    virtual void SetMinimized(bool bMinimized);

    /// <summary>
    /// Returns the current group control's minimized or maximized state.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if minimized and false if the window is maxmized.
    /// </returns>
    ///
    bool GetMinimized() const;

    /// <summary>
    /// Sets the title for the group control.
    /// </summary>
    ///
    /// <param name="pszTitle">
    /// Input pointer to a const string pointer that will be used as the
    /// title for the group control.
    /// </param>
    ///
    void SetTitle(LPCTSTR pszTitle) { m_csTitle = pszTitle; }

    // properties
    /// <summary>
    /// Sets the height for the group control header.
    /// </summary>
    ///
    /// <param name="nHeight">
    /// Input parameter to the group control header height .
    /// </param>
    /// <remarks>
    /// The default value for the height is set to 18 pixels.
    /// </remarks>
    ///
    void SetHeaderHeight(int nHeight) { m_nHeaderHeight = nHeight; }

    /// <summary>
    /// Returns the group control header height.
    /// </summary>
    ///
    /// <returns>
    /// Returns integer value of the group control header height.
    /// </returns>
    ///
    int GetHeaderHeight() { return m_nHeaderHeight; }
    
    /// <summary>
    /// Sets the window style for the group control.
    /// </summary>
    ///
    /// <param name="nStyle">
    /// Input parameter to set the style .
    /// </param>
    ///
    void SetStyle(DWORD nStyle) { m_nStyle = nStyle; }

    /// <summary>
    /// Returns the current window style set on the group control.
    /// </summary>
    ///
    /// <returns>
    /// Returns a DWORD with the group control current set window style.
    /// </returns>
    ///
    DWORD GetStyle() { return m_nStyle; }

    /// <summary>
    /// Sets the current window selection to be displayed in the group control.
    /// </summary>
    ///
    /// <param name="nSelIndex">
    /// Input parameter for the current window's index.
    /// </param>
    /// <remarks>
    /// When adding multiple windows to the group control, clients can control
    /// the current displayed window by setting a different index.
    /// </remarks>
    ///
    void SetSelIndex(int nSelIndex);

    /// <summary>
    /// Returns the index of the current window that is being displayed in 
    /// the group control.
    /// </summary>
    ///
    /// <returns>
    /// Returns the index of the current window that is being displayed in 
    /// the group control.
    /// </returns>
    ///
    int GetSelIndex();

    /// <summary>
    /// Controls the display of the group controls header.
    /// </summary>
    ///
    /// <param name="bHide">
    /// Input parameter to hide or show the group controls header.
    /// </param>
    ///
    void SetHideGroupHeader(bool bHide) {
        m_bHideGroupHeader = bHide;
    }

    /// <summary>
    /// Returns true or false based on the group control's header is 
    /// hidden or shown.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if header is hidden and false if it is shown.
    /// </returns>
    ///
    bool GetHideGroupHeader() {
        return m_bHideGroupHeader;
    }

    /// <summary>
    /// Controls the activated-looking of this group's title bar. If 
    /// the group has ADUI_GROUP_STYLE_NONACTIVE style, there will be
    //  visual effect by calling this. 
    /// </summary>
    ///
    /// <param name="bActive">
    /// Input parameter to make the group look active.
    /// </param>
    ///
    void SetActive(bool bActive);

    /// <summary>
    /// Returns true or false based on the group control's active  
    /// status.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the group is active (the input focus is on this control
    /// or is on one of the child controls.
    /// </returns>
    ///
    bool GetActive() { return m_bActive; }

protected:
    // Draws the group control border
    virtual void DrawGroupContent(CDC* pDC);
    // Draws the header (title, chevrons and bitmap buttons)
    virtual void DrawGroupHeader(CDC* pDC);
    virtual void DeselectGroupHeader() {
        CDC* pDC = GetWindowDC();
        DrawGroupHeader(pDC);
        ReleaseDC(pDC);
    }
    void OnChevronClicked(); // handle collapse/expand
    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
    //{{AFX_MSG(CAdUiGroupCtrl)
    afx_msg void OnNcPaint();
    afx_msg void OnPaint();
    afx_msg void OnNcCalcSize( BOOL bCalcValidRects, NCCALCSIZE_PARAMS * );
    afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
    afx_msg void OnSize( UINT nType, int cx, int cy );
    afx_msg void OnNcLButtonDown( UINT nHitTest, CPoint );
    afx_msg void OnNcLButtonDblClk( UINT nHitTest, CPoint );
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void OnSetFocus( CWnd * pOldWnd );
    afx_msg void OnKillFocus( CWnd * pNewWnd );
    afx_msg BOOL OnEraseBkgnd(CDC*) { return TRUE;};
    afx_msg HBRUSH OnCtlColor(CDC*, CWnd*, UINT);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    COLORREF m_crNCBackground;
    COLORREF m_crGroupBorder;
    COLORREF m_crHeaderActive;
    COLORREF m_crHeaderInactive;
    COLORREF m_crTitleText;
    COLORREF m_crButtonBorderNormal;
    COLORREF m_crButtonFillNormal;
    COLORREF m_crButtonFillSelected;
    COLORREF m_crButtonBorderSelected1;
    COLORREF m_crButtonBorderSelected2;
    CBrush   m_bgBrush;

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAdUiGroupCtrl)
    //}}AFX_VIRTUAL

protected:
    CString         m_csTitle;
    bool            m_bMinimized;
    bool            m_bActive;
    bool            m_bHideGroupHeader;
    int             m_nHeaderHeight;
    int             m_nRestoreHeight;
    int             m_nSelIndex;
    DWORD           m_nStyle;
    DWORD           m_dwBtnId;

    // Used to make the header font size same as that of Property Inspector
    static LOGFONT          m_lf;
    ADUIHEADERBTNLIST       m_bmpBtnList;
    ADUIGROUPCTRLDATALIST   m_groupList;
    CToolTipCtrl            m_ToolTip;    // tooltip
};

inline bool CAdUiGroupCtrl::GetMinimized() const
{
    return m_bMinimized;
}

inline void CAdUiGroupCtrl::SetMinimized( bool bMinimized )
{
    m_bMinimized = bMinimized;
}

#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
