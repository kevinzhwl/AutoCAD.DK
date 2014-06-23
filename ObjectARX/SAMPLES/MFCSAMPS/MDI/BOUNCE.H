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
#ifndef __BOUNCE_H__
#define __BOUNCE_H__

/////////////////////////////////////////////////////////////////////////////

class CBounceWnd : public CMDIChildWnd
{
public:
	CBounceWnd();
	BOOL Create(LPCSTR szTitle, LONG style = 0,
				const RECT& rect = rectDefault,
				CMDIFrameWnd* pParent = NULL);

// Implementation
protected:
	static CMenu NEAR menu;     // menu for all BOUNCE windows

	// bounce window client area and bouncing ball color/size parameters
	UINT m_nIDColor;
	COLORREF m_clrBall;

	BOOL m_bFastSpeed;          // current speed

	CPoint m_ptPixel;           // pixel size
	CSize m_sizeRadius;         // radius of ball
	CSize m_sizeMove;           // move speed
	CSize m_sizeTotal;          // total size for ball bitmap
	CPoint m_ptCenter;          // current center for the ball
        CMDIFrameWnd* m_parent;      // parent

	// for replicating bouncing ball
	CBitmap m_bmBall;

	void MakeNewBall();
	void ChangeSpeed();

	// message handlers
	//{{AFX_MSG(CBounceWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	afx_msg void OnColor();
	afx_msg void OnCustomColor();
	afx_msg void OnUpdateSlow(CCmdUI* pCmdUI);
	afx_msg void OnSlow();
	afx_msg void OnUpdateFast(CCmdUI* pCmdUI);
	afx_msg void OnFast();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __BOUNCE_H__
