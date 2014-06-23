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
// MFC classes for ARx modeless dialogue box
//

#ifndef _CHELLO_H
#define _CHELLO_H

//
// ChelloDlg dialog:
//
class ChelloDlg : public CDialog
{
public:
	ChelloDlg( CWnd* pParent = NULL );
	BOOL Create( CWnd* pParent = NULL );
	enum { IDD = DbmodDlg };

protected:
	virtual void OnClose();
	afx_msg LONG onAcadKeepFocus ( UINT, LONG );
	afx_msg void OnSysCommand ( UINT nID, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

#endif // _CHELLO_H
