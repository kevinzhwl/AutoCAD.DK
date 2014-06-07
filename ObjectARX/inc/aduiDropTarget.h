/////////////////////////////////////////////////////////////////////////////
//                 (C) Copyright 2001, 2002 by Autodesk, Inc.
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
/////////////////////////////////////////////////////////////////////////////
// 
// Purpose:
// 
// Derives from COleDropTarget to implement drop target
// The palette set and palette creates this object as a member and calls 
// Register() to register itself as target window for drag and drop.
// Routes the drag messages to the registered window to let it handle the 
// drag messages.
// 
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_DROP_TARGET_H_
#define _ADUI_DROP_TARGET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// These messages are for ***INTERNAL USE ONLY***
//Drag and drop messages to send to the target window
//
#define UM_ADUI_DRAGENTER				(WM_USER + 120)
#define UM_ADUI_DRAGOVER				(WM_USER + 121)
#define UM_ADUI_DRAGLEAVE				(WM_USER + 122)
#define UM_ADUI_DROP					(WM_USER + 123)
#define UM_ADUI_DROPEX					(WM_USER + 124)
#define UM_ADUI_DRAGSCROLL				(WM_USER + 125)

//Structure to hold the drag and drop data to be sent to the target window 
//while sending drag and drop messages 
//
typedef struct tagADUI_DRAGDATA
{
	// Pointer to the window the cursor is entering/leaving or currently over.
	CWnd				*	mpWnd;
	// Data object. Valid for UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, 
	// UM_ADUI_DROP and UM_ADUI_DROPEX.
	COleDataObject		*	mpDataObject;
	// State of the modifier keys. This is a combination of any number of 
	// the following: MK_CONTROL, MK_SHIFT, MK_ALT, MK_LBUTTON, MK_MBUTTON,
	// and MK_RBUTTON. Valid for UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER.
	DWORD					mdwKeyState;
	// Current location of cursor in client co-ordinates. Valid for 
	// UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, UM_ADUI_DROP and 
	// UM_ADUI_DROPEX
	POINTL					mPoint;
	// The drop effect that the user chose for the default drop operation 
	// based on the current key state. Valid for UM_ADUI_DROP and 
	// UM_ADUI_DROPEX.
	DROPEFFECT				mDropEffect;
	// List of the drop effects that the drop source supports. Valid for 
	// UM_ADUI_DROPEX
	DROPEFFECT				mDropList;

} ADUI_DRAGDATA,*PADUI_DRAGDATA;

// This class is for ***INTERNAL USE ONLY***
// CAdUiDropTarget class is used to make a window a drag and drop target. 
// Declare a member variable of this class in the CWnd derived class which 
// is to be made drop target and call CAdUiDropTarget::Register() to 
// register the window as drop target. The drag and drop messages received 
// by this object is routed back to the respective window which contains 
// this object as UM_ADUI_xxx messages. The drag and drop messages are 
// UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, UM_ADUI_DRAGLEAVE, UM_ADUI_DROP, 
// UM_ADUI_DROPEX, UM_ADUI_DRAGSCROLL. All the messages except UM_ADUI_DRAGLEAVE 
// contain ADUI_DRAGDATA structure pointer as lParam. 
// Handle these messages in the window class and return appropriate return value.
//
#pragma warning(push)
#pragma warning(disable : 4275)
class CAdUiDropTarget : public COleDropTarget
{
public:
    CAdUiDropTarget();
    ~CAdUiDropTarget();
    
protected:
    virtual DROPEFFECT 	OnDragEnter			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DWORD dwKeyState, 
											 CPoint point);
    virtual DROPEFFECT 	OnDragOver			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DWORD dwKeyState, 
											 CPoint point);
    virtual BOOL		OnDrop				(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DROPEFFECT 	dropEffect, 
											 CPoint point);
    virtual DROPEFFECT 	OnDropEx			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DROPEFFECT dropDefault, 
											 DROPEFFECT dropList, 
											 CPoint point);
    virtual void		OnDragLeave			(CWnd* pWnd);
    virtual DROPEFFECT  OnDragScroll	    (CWnd* pWnd,
									         DWORD dwKeyState, 
										     CPoint point);

protected:
	DWORD				mdwKeyState;
};
#pragma warning(pop)

#endif // _ADUI_DROP_TARGET_H_
