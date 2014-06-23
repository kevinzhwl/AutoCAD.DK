// (C) Copyright 1993-1997 by Autodesk, Inc.
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
// File Name: TBHandler.cpp
// implementation file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CTBHandler

CTBHandler::CTBHandler()
{
}

CTBHandler::~CTBHandler()
{
}


BEGIN_MESSAGE_MAP(CTBHandler, CWnd)
	//{{AFX_MSG_MAP(CTBHandler)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTBHandler message handlers

extern void toolbarProc(WORD);

BOOL CTBHandler::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	

    if (wParam == ID_LADIA ||
        wParam == ID_LCA ||
        wParam == ID_TITLE ||
        wParam == ID_ULCS)
    {
        toolbarProc(wParam);
        return TRUE; // end of msg
    }

	return CWnd::OnCommand(wParam, lParam);
}

