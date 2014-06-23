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
// File Name: loadApp.cpp
//
// DESCRIPTION:
//
// OnMove.cpp : implementation file
//

#include "stdafx.h"
#include "loadapp.h"
#include "OnDrop.h"



/////////////////////////////////////////////////////////////////////////////
// COnDrop

COnDrop::COnDrop()
{
}

COnDrop::~COnDrop()
{
}


BEGIN_MESSAGE_MAP(COnDrop, CWnd)
	//{{AFX_MSG_MAP(COnDrop)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COnDrop message handlers


void COnDrop::OnDropFiles(HDROP hDropInfo) 
{
	char file[512];
	UINT cch = 511;
	DragQueryFile( hDropInfo, 0, file, 511);
	CString filename = file;
	CString ext = getExtension(filename);


	if((ext == "ARX") || (ext == "EXE")){
		if(theApp.pLispReactor)
			theApp.pLispReactor->fromDragDrop = TRUE;
		if(theApp.iniFile.watchDragDrop)
			ads_queueexpr("(command \"update\")");
	}


	CWnd::OnDropFiles(hDropInfo);
	
}

