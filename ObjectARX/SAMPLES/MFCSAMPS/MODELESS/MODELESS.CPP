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
// modeless.cpp - Rx app to keep track of changes to entities with a modeless
// dialog
//
//
// Check if the build is DEBUG version and it's intended
// to be used with Non-DEBUG AutoCAD.
// In this case, for MFC header files, we need to undefine
// _DEBUG symbol
// Read this project readme.txt for more detail
#if defined(_DEBUG) && !defined(DEBUG_AUTOCAD)
    #pragma message("Building debug version of modeless.arx to be used with non-debug/Prod AutoCAD")
    #define _DEBUG_WAS_DEFINED
    #undef _DEBUG
#endif

#include "stdafx.h"

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif



#include <stdio.h>
#include <stdarg.h>
#include <aced.h>
#include <adslib.h>
#include "dbmr.h"
#include "resource.h"
#include "chello.h"
#include "modeless.h"
#include "adeskabb.h"
#include "rxmfcapi.h"
#include "resourcehelper.h"

DbModReactor * dbmr = NULL;

static HWND hWndACAD = NULL;

ChelloDlg* dlg = NULL;



//
//	hello()
//
//	AutoCAD command to watch database modifications:
//
//
void hello()
{
	if ( getYorN ( "Start watching entity modifications" ) )
			attachDbmr();
		else
			detachDbmr();
}


//
//	attachDbmr()
//
//	Attach the database reactor if one isn't attached already.  Then,
//	start up the dialog.
//
//
void attachDbmr()
{
	if ( !dbmr )
		{
		dbmr = new DbModReactor();
		if ( dbmr == NULL )
			{
			ads_printf ( "Unable to create a DbModReactor.\n" );
			return;
			}

		acdbCurDwg()->addReactor(dbmr);
		ads_printf( "Attached DbModReactor to database.\n" );

		if( !dlg && !startDlg() )
			ads_printf( "Failed to create modeless dialog box.\n" );
		}
}


//
//	detachDbmr()
//
//	Disconnect the database reactor if one's attached.  Close the dialog.
//
//
void detachDbmr()
{
	if ( dbmr ) 
		{
		AcDbDatabase * pDb = acdbCurDwg();
		if ( pDb )
			pDb->removeReactor( dbmr );
		delete dbmr;
		dbmr = NULL;
		ads_printf( "\nDetached DbModReactor from database.\n" );
        ads_prompt( "Command: ");
		endDlg();
		}
}


//
//	DbModReactor overrides
//
//	These functions get called by AutoCAD when the database has been
//	modified.
//
//
void DbModReactor::objectAppended ( const AcDbDatabase * dwg, 
					const AcDbObject* dbObj )
{
	objDisplay( "appended", dbObj );
}

void DbModReactor::objectModified( const AcDbDatabase * dwg,
					const AcDbObject* dbObj )
{
	objDisplay( "modified", dbObj );
}

void DbModReactor::objectErased ( const AcDbDatabase* dwg,
					const AcDbObject* dbObj,
					Adesk::Boolean pErased )
{
	char buf[40];
	sprintf( buf, "%serased", (pErased ? "" : "not ") );
	objDisplay( buf, dbObj );
}

void DbModReactor::objDisplay ( const char* what,
				const AcDbObject* dbObj ) const
{
	AcDbObjectId id = dbObj->objectId();
	AcDbHandle h;
	char hstr[20];
	char idstr[20];
	const char *cname = dbObj->isA()->name();
	
	dbObj->getAcDbHandle( h );
	h.getIntoAsciiBuffer( hstr );

	ads_printf( "\nDbModReactor: obj %s: "
		"class %s, id %lx, handle %s.\n",
		what, cname , id, hstr );

	sprintf( idstr, "0x%08lx", id );

	dlg->SetDlgItemText( IDC_WHAT, (LPSTR) what );
	dlg->SetDlgItemText( IDC_EDIT_CLASS, (LPSTR) cname );
	dlg->SetDlgItemText( IDC_EDIT_OBJID, (LPSTR) idstr );
	dlg->SetDlgItemText( IDC_EDIT_HANDLE, (LPSTR) hstr );
}


//
//	getYorN()
//
//	Get a boolean from the user.
//
//
Adesk::Boolean getYorN( const char* pStr )
{
	char yorn_str[132];

	yorn_str[0] = 'Y';
	yorn_str[1] = '\0';
	ads_printf ( "\n%s", pStr );
	ads_initget ( 0, "No Yes" );
	ads_getkword ( " -- No/<Yes>:  ", yorn_str );

	return yorn_str[0] != 'N';
}



//
//	startDlg()
//
//	Start up the modeless dialog.
//
//
Adesk::Boolean startDlg()
{
    // when resource from this ARX app is needed,
    // instantiate a local object of CTemporaryResourceOverride    
    CTemporaryResourceOverride   useThisDllResource;

	HWND hwndAcad = acedGetAcadFrame()->m_hWnd;

	if ( !hwndAcad )
		{
		errmsg( "Unable to locate AutoCAD parent window." );
		return Adesk::kFalse;
		}

	CWnd *pWnd = CWnd::FromHandle ( hwndAcad );
	if ( (dlg = new ChelloDlg ( pWnd )) == NULL )
		{
		errmsg ( "Unable to allocate a ChelloDlg." );
		return Adesk::kFalse;
		}

	BOOL succeeded = dlg->Create ( pWnd );
	if ( !succeeded )
		errmsg ( "Unable to create the dialog." );
		
	return succeeded ? Adesk::kTrue : Adesk::kFalse;
}


//
//	endDlg()
//
//
Adesk::Boolean endDlg()
{
	if ( !dlg )
		return Adesk::kTrue;

	Boolean ok = dlg->DestroyWindow();
	if ( ok )
		dlg = NULL;
	return ok;
}

ChelloDlg::ChelloDlg ( CWnd* pParent ) : CDialog( ChelloDlg::IDD, pParent )
{
}



//	When AutoCAD asks your dialog if it is willing to give up input
//	focus, return true to keep the focus and false to give it up.
//
#ifndef WM_ACAD_MFC_BASE
#define WM_ACAD_MFC_BASE        (1000)
#endif

#ifndef WM_ACAD_KEEPFOCUS
#define WM_ACAD_KEEPFOCUS       (WM_ACAD_MFC_BASE + 1)
#endif


BEGIN_MESSAGE_MAP( ChelloDlg, CDialog )
	ON_COMMAND( IDCLOSE, OnClose )
	ON_WM_SYSCOMMAND()
	ON_MESSAGE( WM_ACAD_KEEPFOCUS, onAcadKeepFocus )
END_MESSAGE_MAP()



//
//	ChelloDlg::OnClose()
//
//	Because the dialog is about to close, disconnect the database reactor.
//
//
void ChelloDlg::OnClose()
{
	detachDbmr();
}
    

//
//	ChelloDlg::onAcadKeepFocus()
//
//	This function gets called repeatedly whenever the mouse is moved over
//	the AutoCAD window.
//
afx_msg LONG ChelloDlg::onAcadKeepFocus( UINT, LONG )
{
	return TRUE;
}


//
//	ChelloDlg::OnSysCommand()
//
//	Handle commands invoked from the dialog's system menu.
//
//
afx_msg void ChelloDlg::OnSysCommand ( UINT nID, LPARAM lParam )
{
	CDialog::OnSysCommand ( nID, lParam );
	if ( nID == SC_CLOSE )
		OnClose();
}


//
//	ChelloDlg::Create()
//
//	Call the parent class's Create() with the ID of the dialog resource.
//
//
BOOL ChelloDlg::Create( CWnd* pParent )
{
	return CDialog::Create( ChelloDlg::IDD, pParent );
}


//
//	errmsg()
//
//	Send an error message to the command window.
//
void errmsg( LPSTR msg )
{
	ads_printf ( "\nModeless sample app error: %s\n", msg );
}


//
//	errmsgf - put up a MessageBox, accept printf arguments:
//
void errmsgf ( LPSTR fmt, ... )
{
	char buf[256];
	va_list marker;

	va_start( marker, fmt );
	wvsprintf ( buf, fmt, marker );
	va_end( marker );
	errmsg ( buf );
}
