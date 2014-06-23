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
// File Name: lispReactor.cpp
//

#include "stdafx.h"

void 
CLispReactor::lispWillStart(const char * firstLine){
	CString lispExpression = firstLine;
	lispExpression.MakeUpper();

	if( (lispExpression.Find(".MNL") > 0 )		||
		(lispExpression.Find("_*UPDATE*") > 0 )	||
		(lispExpression.Find("S::INIT") > 0)	||
		(lispExpression.Find(".LSP") > 0)		||
		!theApp.isInitialized
	  )
	{
		checkIt = FALSE;
		return;
	}


	if( lispExpression.Find( "LOAD" ) != -1)
		checkIt = TRUE;
	else
		checkIt = FALSE;
}

void
CLispReactor::lispEnded(){
	if(!checkIt || !acdbCurDwg() || fromDragDrop){
		fromDragDrop = FALSE;
		return;
	}

	// This is the only workaround I could think of
	// since ads_loaded is not working if called from here,
	// but will work if called from a registred command.
	// Update is a function loadApp defines only for that
	// purpose.
	ads_queueexpr("(command \"_*update*\")");
	checkIt = FALSE;

}

void
CLispReactor::commandEnded(const char * cmdStr){
	if(!acdbCurDwg())
		return;

	CString command = cmdStr;
	command.MakeUpper();
	if(command != "ARX")
		return;

	// We don't have to use the sendCommandToAutoCAD("update ") trick
	// since ads_arxloaded (called in theApp.getLoadedApp()) works from here.
	theApp.getLoadedApp();
	updateCurrApp();
	setTitle();
}

