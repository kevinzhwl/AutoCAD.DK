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
// File Name: IniFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIniFile document

#ifndef _INIFILE_H
#define _INIFILE_H

#define S_ARRAY_SIZE 15

#include <adslib.h>
#include <adesk.h>


class CIniFile
{
public:
	CIniFile();

// Attributes
public:
	// current application file and path name
	CString currentApp;
	// list of used applications file and path names
	CStringArray usedApp;
	// list of hidden applications file and path names
	CStringList hiddenApp;
	// full path name of loadapp.ini
	CString fileName;
	// initial directory to look at when browsing
	CString initDir;

	BOOL viewAll;
	BOOL showApp;
	BOOL watchLisp;
	BOOL watchDragDrop;

// Operations
public:

	void setCurrApp(CString);
	void iniRead();
	void iniSave();
	Adesk::Boolean readRegistry();
	Adesk::Boolean saveRegistry();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIniFile)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIniFile();

};

#endif
