// Packdlg.cpp : Defines the initialization routines for the DLL.
//
//   Copyright (C) 1997 by Autodesk, Inc.
//
//   Permission to use, copy, modify, and distribute this software in
//   object code form for any purpose and without fee is hereby granted,
//   provided that the above copyright notice appears in all copies and
//   that both that copyright notice and the limited warranty and
//   restricted rights notice below appear in all supporting
//   documentation.
//
//   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
//   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
//   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
//   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
//   UNINTERRUPTED OR ERROR FREE.
//
//   Use, duplication, or disclosure by the U.S. Government is subject to
//   restrictions set forth in FAR 52.227-19 (Commercial Computer
//   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
//   (Rights in Technical Data and Computer Software), as applicable.
//


//////////////////////////////////////////////////////////////////////////////
//
// Remarks:     TBC sort for list dialog.
//
//////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "packcore.h"
#include "Packdlg.h"
#include "resourcehelper.h"

#include "resource.hm"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();

#include <imgdef.h>
#include <imgent.h>
#include <imgentim.h>
#include <imgdefim.h>
#include <dbmain.h>

#include <imgvars.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbelipse.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "actrans.h"
#include "adeskabb.h"
#include "math.h"
#include <time.h>
#include <xgraph.h>

#include "winnt.h"
#include "time.h"

#include "direct.h"
#include "io.h"
#include "fcntl.h"
#include "errno.h"
#include <direct.h>


#include "pathdlg.h"  // this include file for the pathdlg dialog class

#include "packutil.h"




DependencyStatus status; // struct to hold status info
depend_type *pFile; // struct to hold file info
int nFile;  // counter for number of files
subst_type *pSubst;
int nSubst;
DWORD totalsize;  // saves size of all files
int overwrite; // variable to control if overwriting is allowed
char copypath[_MAX_PATH]; // path where files will be copied to.


//////////////////////////////////////////////////////////////////////////

// initializations follow.

int CDepend::mColumnSpacing[] = { 128,96,72,72 };


//////////////////////////////////////////////////////////////////////////


void Depend()
{
 // When resource from this ARX app is needed, just
 // instantiate a local CTemporaryResourceOverride
 CTemporaryResourceOverride thisResource;

 CDepend Depend(CWnd::FromHandle(adsw_acadMainWnd()));

 Depend.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CSendApp

BEGIN_MESSAGE_MAP(CSendApp, CWinApp)
	//{{AFX_MSG_MAP(CSendApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendApp construction

CSendApp::CSendApp()
{

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CDepend dialog


CDepend::CDepend(CWnd* pParent /*=NULL*/)
	: CDialog(CDepend::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDepend)
	m_subdir = FALSE;
	//}}AFX_DATA_INIT
}


void CDepend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepend)
	DDX_Control(pDX, IDC_DEPENDTREE, m_DependTree);
	DDX_Control(pDX, IDC_DEPENDLIST, m_DependList);
	DDX_Check(pDX, IDC_SUBDIR, m_subdir);
	//}}AFX_DATA_MAP
}


extern "C" HINSTANCE _hdllInstance;

BOOL CDepend::OnInitDialog()
{


	int found  = 0;
	CString cstr;

	::SetWindowLong( m_hWnd, GWL_EXSTYLE,
		::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_CONTEXTHELP);

	CDialog::OnInitDialog();


	// InitToggleButtons wacked form Josh Harris's Image dlg code.

	InitToggleButtons( IDC_TREE_VIEW - IDC_LIST_VIEW + 1, 130,
		IDC_LIST_VIEW, 3, IDB_SENDICONS );

	totalsize = 0;

	// initialize the status struct
	// set the isalt and isfmp to -1 as these store an index
	memset(&status,0,sizeof(DependencyStatus));
	status.isalt = -1;
	status.isfmp = -1;

	char path[_MAX_PATH];
	if( _getcwd( path, _MAX_PATH ) != NULL )
	{
		CEdit* pEdit = (CEdit*) (GetDlgItem(IDC_PATH));
		pEdit->SetWindowText(path);
		pEdit->SetSel( 0,strlen(path),FALSE);
	}

    GetDlgItem(IDC_PATH)->SetFocus();

	// create font map table
	int substcount = updateSubstTable(0);

	if(substcount)
	{
		pSubst = new subst_type[substcount+8];
		nSubst = updateSubstTable(1);
	}

	// get number of files and update
	int filecount =  getDependencyNames(0);
	
	if(filecount)
	{
		pFile = new depend_type[filecount+8];
		getDependencyNames(1);
	}

	char msg[128];

	cstr.LoadString(IDS_TOTAL_SIZE);
	sprintf(msg,(char*)(LPCTSTR)cstr,totalsize);
	SetDlgItemText(IDC_STATUS,msg);

	PolulateTree();
	PolulateList();
	
	
	// hide the tree view.
	GetDlgItem(IDC_DEPENDTREE)->ShowWindow(SW_HIDE);


	return FALSE;  // return TRUE  unless you set the focus to a control

}



void	
CDepend::PolulateList()
{
	LV_COLUMN lvColumn;

	
    m_DependList.SetImageList(&m_imageList, TVSIL_NORMAL);
	m_DependList.DeleteAllItems();
	int ItemTotal = nFile;

	int nColumns = 4;

	CString csColumnTitle;

	for (int nIndex = 0; nIndex < nColumns; nIndex++)
	{
		csColumnTitle.LoadString( nIndex + LIST_FILENAME );
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = csColumnTitle.GetBuffer(0);
		lvColumn.iSubItem = nIndex;
		lvColumn.cx = mColumnSpacing[nIndex];

		m_DependList.InsertColumn(nIndex, &lvColumn);
	}


	int count = 0;
	for(int nItem=0; nItem<nFile; nItem++)
	{
		if(pFile[nItem].found)
		{
			char buffer[_MAX_PATH];

			char path_buffer[_MAX_PATH];
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];

			strcpy(path_buffer,pFile[nItem].fname);
			_splitpath( path_buffer, drive, dir, fname, ext );

			//add name
			sprintf(buffer,/*MSG0*/"%s%s",fname,ext);

			int nSubItem = m_DependList.InsertItem(LVIF_TEXT | LVIF_PARAM, count++, buffer, NULL, NULL, 2, nItem );

			CString csBuffer;
			CString csFileSize;

			if ( pFile[nItem].size & 0xC0000000) 
			{
				pFile[nItem].size >>= 30;
				csBuffer = "GB";
			} else 
			{
				if ( pFile[nItem].size & 0xFFF00000 ) 
				{
					pFile[nItem].size >>= 20;
					csBuffer = "MB";
				} else 
				{
					if ( pFile[nItem].size & 0xFFFFFC00 ) 
					{
						pFile[nItem].size >>= 10;
						csBuffer = "kB";
					} else {
						csBuffer = "B";
					}
				}
			}
			csFileSize.Format(/*MSG0*/"%ld ",pFile[nItem].size);
			csFileSize += csBuffer;

			// add size
			//sprintf(buffer,/*MSG0*/"%ld",pFile[nItem].size);
			m_DependList.SetItem(nSubItem,1,LVIF_TEXT,csFileSize, NULL, NULL, NULL, NULL );

			// add date
			struct tm * tm;
			tm = pFile[nItem].mtime.GetLocalTm(NULL );
			strftime( buffer,_MAX_PATH,/*MSG0*/"%x  %#X",tm);
			m_DependList.SetItem(nSubItem,2,LVIF_TEXT,buffer, NULL, NULL, NULL, NULL );

			// add version if file is a drawing

			if((pFile[nItem].ftype == 1) || (pFile[nItem].ftype == 0))
				m_DependList.SetItem(nSubItem,3,LVIF_TEXT,pFile[nItem].dwgVersion, NULL, NULL, NULL, NULL );

		}


	}

}





void	
CDepend::PolulateTree()
{

	CString cstr;

	m_imageList.Create( IDB_SENDICONS, 16, 5, 0xFFFFFF );


    m_DependTree.SetImageList(&m_imageList, TVSIL_NORMAL);

	// tree structure common values
    TV_INSERTSTRUCT tvinsert;
    tvinsert.hParent = NULL;
    tvinsert.hInsertAfter = TVI_LAST;
    tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    tvinsert.item.hItem = NULL;
    tvinsert.item.state = 0;
    tvinsert.item.stateMask = 0;
    tvinsert.item.cchTextMax = 6;
    tvinsert.item.iSelectedImage = 5;
    tvinsert.item.cChildren = 0;
    tvinsert.item.lParam = 0;


	HTREEITEM hCURDWG;
	for(int i=0; i<nFile; i++)
	{
		if(pFile[i].ftype == 0)
		{
				tvinsert.item.pszText = pFile[i].fname;
				hCURDWG = m_DependTree.InsertItem(&tvinsert);
				m_DependTree.SetItemImage(hCURDWG,2,2);
		}
	}


	tvinsert.hParent = hCURDWG;
	cstr.LoadString(IDS_XREF);
    tvinsert.item.pszText = (char*)(LPCTSTR)cstr;
    tvinsert.item.iImage = 3;
    HTREEITEM hXREF = m_DependTree.InsertItem(&tvinsert);
	m_DependTree.SetItemImage( hXREF, 3, 3 );
  

	tvinsert.hParent = hCURDWG;
	cstr.LoadString(IDS_IMAGE);
    tvinsert.item.pszText = (char*)(LPCTSTR)cstr;
    tvinsert.item.iImage = 6;
    HTREEITEM hIMAGE = m_DependTree.InsertItem(&tvinsert);
	m_DependTree.SetItemImage( hIMAGE, 6, 6 );

	tvinsert.hParent = hCURDWG;
	cstr.LoadString(IDS_FONTS);
    tvinsert.item.pszText = (char*)(LPCTSTR)cstr;
    tvinsert.item.iImage = 2;
    HTREEITEM hFONTS = m_DependTree.InsertItem(&tvinsert);
	m_DependTree.SetItemImage( hFONTS, 2, 2 );

	tvinsert.hParent = hCURDWG;
		cstr.LoadString(IDS_MISCELANEOUS);
    tvinsert.item.pszText = (char*)(LPCTSTR)cstr;
    tvinsert.item.iImage = 2;
    HTREEITEM hMISC = m_DependTree.InsertItem(&tvinsert);
	m_DependTree.SetItemImage( hFONTS, 2, 2 );


	HTREEITEM hTemp;
// second level
	int found = 0;
    tvinsert.hParent = hXREF;
	for(i=0; i<nFile; i++)
	{
		if((pFile[i].ftype == 1) && (pFile[i].found))
		{
			tvinsert.item.pszText = pFile[i].fname;
		    tvinsert.item.iImage = 3;
			hTemp = m_DependTree.InsertItem(&tvinsert);
			m_DependTree.SetItemImage( hTemp, 3, 3 );
			found ++;
		}
	}
	if(found)
		m_DependTree.Expand( hXREF, TVE_EXPAND );
  

// second level
	found = 0;
    tvinsert.hParent = hIMAGE;
	for(i=0; i<nFile; i++)
	{
		if((pFile[i].ftype == 2) && (pFile[i].found))
		{
			tvinsert.item.pszText = pFile[i].fname;
		    tvinsert.item.iImage = 6;
			hTemp = m_DependTree.InsertItem(&tvinsert);
			m_DependTree.SetItemImage( hTemp, 6, 6 );
			found ++;
		}
	}
	if(found)
		m_DependTree.Expand( hIMAGE, TVE_EXPAND );

// second level
	found = 0;
    tvinsert.hParent = hFONTS;
	for(i=0; i<nFile; i++)
	{
		if((pFile[i].ftype >= 3) && (pFile[i].ftype < 7) && (pFile[i].found))
		{
			tvinsert.item.pszText = pFile[i].fname;
			tvinsert.item.iImage = 2;

			switch(pFile[i].ftype)
			{
			case 4 : //shx
				hTemp = m_DependTree.InsertItem(&tvinsert);
				m_DependTree.SetItemImage( hTemp, 13, 13 );
				found ++;
				break;
			case 5 : //pfb
				hTemp = m_DependTree.InsertItem(&tvinsert);
				m_DependTree.SetItemImage( hTemp, 11, 12 );
				found ++;
				break;
			case 6 : //ttf
				hTemp = m_DependTree.InsertItem(&tvinsert);
				m_DependTree.SetItemImage( hTemp, 12, 12 );
				found ++;
				break;
			default :
				hTemp = m_DependTree.InsertItem(&tvinsert);
				m_DependTree.SetItemImage( hTemp, 2, 2 );
				found ++;
				break;
			}
		}
	}
	if(found)
		m_DependTree.Expand( hFONTS, TVE_EXPAND );


// second level
	found = 0;
    tvinsert.hParent = hMISC;
	for(i=0; i<nFile; i++)
	{
		if((pFile[i].ftype == 16) && (pFile[i].found))
		{
			tvinsert.item.pszText = pFile[i].fname;
		    tvinsert.item.iImage = 2;
			hTemp = m_DependTree.InsertItem(&tvinsert);
			m_DependTree.SetItemImage( hTemp, 2, 2 );
			found ++;
		}
	}
	if(found)
		m_DependTree.Expand( hMISC, TVE_EXPAND );

	m_DependTree.Expand( hCURDWG, TVE_EXPAND );

}




BEGIN_MESSAGE_MAP(CDepend, CDialog)
	//{{AFX_MSG_MAP(CDepend)
	ON_BN_CLICKED(IDBROWSE, OnBrowse)
	ON_BN_CLICKED(IDCOPY, OnCopy)
	ON_BN_CLICKED(IDREPORT, OnReport)
	ON_WM_HELPINFO()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_DEPENDLIST, OnColumnclickDependlist)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LIST_VIEW, OnListView)
	ON_BN_CLICKED(IDC_TREE_VIEW, OnTreeView)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepend message handlers

void CDepend::OnBrowse() 
{
	
	char  path[_MAX_PATH];

	CPathDialog dlg(this);

	if(dlg.DoModal() == IDOK)
	{
		strcpy(path,(LPCTSTR) dlg.GetSelectedPath());
		CEdit* pEdit = (CEdit*) (GetDlgItem(IDC_PATH));
		pEdit->SetWindowText(path);
		pEdit->SetSel( 0,strlen(path),FALSE);

	}
}

void CDepend::OnCopy() 
{

	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char path[_MAX_PATH];
	char paths[_MAX_PATH];
	char tpath[_MAX_PATH];
	char currentpath[_MAX_PATH];


	CString cstr;
	struct resbuf rb;


	 _getcwd( currentpath, _MAX_PATH );

	// initialize overwrite
	overwrite = 0;

	ads_getvar(/*MSG0*/"DWGNAME",&rb);
	strcpy(path_buffer,rb.resval.rstring);
	_splitpath( path_buffer, drive, dir, fname, ext );

	ads_getvar(/*MSG0*/"DBMOD",&rb);
	if(rb.resval.rint)
	{

		cstr.LoadString(IDS_MODIFIED);
		sprintf(path_buffer,(char*)(LPCTSTR)cstr,fname,ext);
		CSaveDwg dlg;
		dlg.m_dwgname = path_buffer;
		if(dlg.DoModal() == IDCANCEL)
		{
			_chdir( currentpath);
			return;
		}
	}

	CEdit* pEdit = (CEdit*) (GetDlgItem(IDC_PATH));
	pEdit->GetWindowText( path_buffer, _MAX_PATH );

	// make a copy of path_buffer in path as path_buffer will be
	// choked in makedir
	strcpy(path,path_buffer);


	if(_chdir( path_buffer ))
	{

		CDirCreate dlg;
		dlg.m_dirname = path_buffer;
		if(dlg.DoModal() == IDCANCEL)
		{
			_chdir( currentpath);
			return;
		}
	}

	m_subdir = (BOOL)IsDlgButtonChecked(IDC_SUBDIR);

	if(m_subdir)
	{
		if(!makeDirs(path_buffer))
		{
			cstr.LoadString(IDS_CANT_CREATE);
			sprintf(path_buffer, (char*)(LPCTSTR)cstr,path);
			ads_alert(path_buffer);
			_chdir( currentpath);
			return;
		}
		for(int i=0; i<nFile; i++)
		{

			if(overwrite < 0)
			{
				// the important thing is that we must have the user exit through the main dialog cancel.
				_chdir( currentpath);
				return;
			}


			if(pFile[i].found)
			{
				strcpy(paths,pFile[i].fname);
				_splitpath( paths, drive, dir, fname, ext );
				strcpy(path_buffer,path);
				if(path_buffer[strlen(path_buffer)-1] != /*MSG0*/'\\')
					strcat(path_buffer,/*MSG0*/"\\");

				strcat(path_buffer,pFile[i].szPath);
				strcat(path_buffer,fname);
				strcat(path_buffer,ext);

				char msg[_MAX_PATH] = "Copying File ";
		
				cstr.LoadString(IDS_COPYING_FILE);
			
				sprintf(msg,(char*)(LPCTSTR)cstr,fname,ext);
				SetDlgItemText(IDC_STATUS,msg);

//				CopyFile(paths,path_buffer,FALSE);
////////////////////////////////////////////////////////////////////////////////////////////////////

				if(overwrite != 2)
				{
					if(fileexists(path_buffer))
					{
						CDReplace dlg;
	
						dlg.m_FileExists = path_buffer;
						strcpy(msg,path_buffer);
						dlg.m_ESize = getTimedate(msg);
		
						dlg.m_FileReplace = paths;
						strcpy(msg,paths);
						dlg.m_RSize = getTimedate(msg);
	
						int ret = dlg.DoModal();
						switch(overwrite)
						{	
						case 1 :
							CopyFile(paths,path_buffer,FALSE);
							overwrite = 0;
							break;
						case 0 :
							break;
						case 2 :
							CopyFile(paths,path_buffer,FALSE);
							break;
						case -1 :
							cstr.LoadString(IDS_COPY_CANCEL);
							char msg[_MAX_PATH];
							strcpy(msg,(char*)(LPCTSTR)cstr);
							SetDlgItemText(IDC_STATUS,msg);
							_chdir( currentpath);
							return;
						}
	
					}
					else
					{
						CopyFile(paths,path_buffer,FALSE);
					}
					}
				else
				{
					CopyFile(paths,path_buffer,FALSE);
				}

////////////////////////////////////////////////////////////////////////////////////////////////////

			}

		}

		if(overwrite < 0)
		{
			cstr.LoadString(IDS_COPY_CANCEL);
			char msg[_MAX_PATH];
			strcpy(msg,(char*)(LPCTSTR)cstr);
			SetDlgItemText(IDC_STATUS,msg);
			_chdir( currentpath);
			return;
		}

		else
		{

			cstr.LoadString(IDS_COPY_COMPLETE);
			char msg[_MAX_PATH];
			strcpy(msg,(char*)(LPCTSTR)cstr);
			SetDlgItemText(IDC_STATUS,msg);
		}


		ads_getvar(/*MSG0*/"DWGNAME",&rb);
		strcpy(path_buffer,rb.resval.rstring);
		_splitpath( path_buffer, drive, dir, fname, ext );

		strcpy(path_buffer,path);

		int jj = strlen(path_buffer);
		char mychar = path_buffer[jj];

		if(path_buffer[strlen(path_buffer)-1] != /*MSG0*/'\\')
			strcat(path_buffer,/*MSG0*/"\\");

		strcat(path_buffer,fname);
		strcat(path_buffer,".txt");
		doReport(path_buffer);

		ads_getvar(/*MSG0*/"DWGNAME",&rb);
		strcpy(path_buffer,rb.resval.rstring);
		_splitpath( path_buffer, drive, dir, fname, ext );

		strcpy(path_buffer,path);
		if(path_buffer[strlen(path_buffer)-1] != /*MSG0*/'\\')
			strcat(path_buffer,/*MSG0*/"\\");

		strcat(path_buffer,fname);

		strcpy(paths,path);

		strcpy(tpath,path_buffer);
		strcat(tpath,"_R12");
		strcat(tpath,".scr");
		doScript(tpath,paths,12);

		strcpy(paths,path);

		strcpy(tpath,path_buffer);
		strcat(tpath,"_R13");
		strcat(tpath,".scr");
		doScript(tpath,paths,13);
		strcpy(paths,path);

		strcpy(tpath,path_buffer);
		strcat(tpath,"_R14");
		strcat(tpath,".scr");
		doScript(tpath,paths,14);


		_chdir( currentpath);
		GetDlgItem(IDCANCEL)->SetWindowText(/*MSG0*/"Close");

		// now that we have copied with subdirectories on... return!
		return;

	}



	if(!makeDir(path_buffer))
	{
		cstr.LoadString(IDS_CANT_CREATE);
		sprintf(path_buffer, (char*)(LPCTSTR)cstr,path);
		ads_alert(path_buffer);
		_chdir( currentpath);
		return;
	}

	// set current path and call make directory.
	_chdir( currentpath);
	// call the makedirectory routine, so that
	// we can make sure that all paths are parsed properly
	// and the diskspace check is proper...
	// do this as in order to get the free disk space
	// you must point to the root directory on that drive.
	// check disk space...

	if(path[strlen(path)-1] != /*MSG0*/'\\')
		strcat(path,/*MSG0*/"\\");

	strcpy(path_buffer,path);
	strcat(path_buffer,fname);
	strcat(path_buffer,".txt");
	doReport(path_buffer);

	strcpy(tpath,path);
	strcpy(path_buffer,path);
	strcat(path_buffer,fname);
	strcat(path_buffer,"_R12");
	strcat(path_buffer,".scr");
	doScript(path_buffer,tpath,-12);
	strcpy(path_buffer,path);
	strcat(path_buffer,fname);
	strcat(path_buffer,"_R13");
	strcat(path_buffer,".scr");
	doScript(path_buffer,tpath,-13);
	strcpy(path_buffer,path);
	strcat(path_buffer,fname);
	strcat(path_buffer,"_R14");
	strcat(path_buffer,".scr");
	doScript(path_buffer,tpath,-14);


	for(int i=0; i<nFile; i++)
	{
		if(overwrite < 0)
		{
			// the important thing is that we must have the user exit through the main dialog cancel.
			_chdir( currentpath);
			return;
		}
		strcpy(paths,pFile[i].fname);
		_splitpath( paths, drive, dir, fname, ext );
		strcpy(path_buffer,path);
		strcat(path_buffer,fname);
		strcat(path_buffer,ext);

		char msg[_MAX_PATH] = "Copying File ";

		cstr.LoadString(IDS_COPYING_FILE);

		sprintf(msg,(char*)(LPCTSTR)cstr,fname,ext);

		SetDlgItemText(IDC_STATUS,msg);

		if(overwrite != 2)
		{
			if(fileexists(path_buffer))
			{
				CDReplace dlg;

				dlg.m_FileExists = path_buffer;
				strcpy(msg,path_buffer);
				dlg.m_ESize = getTimedate(msg);

				dlg.m_FileReplace = paths;
				strcpy(msg,paths);
				dlg.m_RSize = getTimedate(msg);

				int ret = dlg.DoModal();
				switch(overwrite)
				{
				case 1 :
					CopyFile(paths,path_buffer,FALSE);
					overwrite = 0;
					break;
				case 0 :
					break;
				case 2 :
					CopyFile(paths,path_buffer,FALSE);
					break;
				case -1 :
					_chdir( currentpath);
					return;
				}

			}
			else
			{
				CopyFile(paths,path_buffer,FALSE);
			}
		}
		else
		{
			CopyFile(paths,path_buffer,FALSE);
		}
		
	}


	if(overwrite < 0)
	{
		cstr.LoadString(IDS_COPY_CANCEL);
		char msg[_MAX_PATH];
		strcpy(msg,(char*)(LPCTSTR)cstr);
		SetDlgItemText(IDC_STATUS,msg);
		_chdir( currentpath);
		return;

	}
	else
	{
		cstr.LoadString(IDS_COPY_COMPLETE);
		char msg[_MAX_PATH];
		strcpy(msg,(char*)(LPCTSTR)cstr);
		SetDlgItemText(IDC_STATUS,msg);
	}


	_chdir( currentpath);

	GetDlgItem(IDCANCEL)->SetWindowText(/*MSG0*/"Close");

	return;

}


void CDepend::OnCancel() 
{
	// cleanup
	if(pFile)
		delete pFile;
	if(pSubst)
		delete pSubst;
	
	CDialog::OnCancel();
}

void CDepend::OnReport() 
{

	CReports dlg;
	dlg.DoModal();

}


BOOL CDepend::OnHelpInfo(HELPINFO* pHelpInfo) 
{

	DWORD dwContextId = pHelpInfo->dwContextId;

	switch(pHelpInfo->iCtrlId)
	{
	case IDCOPY :
		dwContextId = HIDCOPY;
		break;
	case IDCANCEL :
		dwContextId = HIDCANCEL;
		break;
	case IDC_DEPENDTREE :
		dwContextId = HIDC_DEPENDTREE;
		break;
	case IDC_PATH :
		dwContextId = HIDC_PATH;
		break;
	case IDBROWSE :
		dwContextId = HIDBROWSE;
		break;
	case IDREPORT :
		dwContextId = HIDREPORT;
		break;
	case IDC_STATUS :
		dwContextId = HIDC_STATUS;
		break;
	case IDC_SUBDIR :
		dwContextId = HIDC_SUBDIR;
		break;
	}


	char path[_MAX_PATH];

	GetModuleFileName(_hdllInstance,path,sizeof(path));

	memcpy(path+strlen(path)-3,"HLP",3);

	if(!fileexists(path))
	{
		if(ads_findfile("packngo.hlp", path) != RTNORM)
		{
			strcpy(path,"packngo.hlp");
		}
	}

	::WinHelp(m_hWnd, path,HELP_CONTEXTPOPUP,dwContextId); 

	return TRUE;
}


void
CDepend::InitToggleButtons( int nButtons,
	int idToolbar, int idCommand, int idString, int idBitmap )
{
	// Locate the appropriate placement for the buttons.
	//
	CRect rect;
	GetDlgItem(IDC_TOGGLE_BUTTON_POSITION)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.right = rect.left + 23 * nButtons;
	rect.bottom = rect.top + 24;

	tbView.Create( WS_VISIBLE | WS_CHILD | CCS_NODIVIDER | CCS_NORESIZE |
		CCS_NODIVIDER | CBRS_TOOLTIPS | TBSTYLE_TOOLTIPS, rect,
		this, idToolbar );

	VERIFY(tbView.AddBitmap(nButtons,idBitmap) != -1);

	tbbView = new TBBUTTON[nButtons];

	for (int nIndex = 0; nIndex < nButtons; nIndex++)
	{
		tbbView[nIndex].fsState = TBSTATE_ENABLED;
		tbbView[nIndex].fsStyle = TBSTYLE_CHECKGROUP;
		tbbView[nIndex].dwData = 0;
		tbbView[nIndex].iBitmap = nIndex;
		tbbView[nIndex].idCommand = nIndex + idCommand;
		tbbView[nIndex].iString = NULL;
	}

	for (nIndex = 0; nIndex < nButtons; nIndex++)
	{
		VERIFY(tbView.AddButtons(1,&tbbView[nIndex]));
	}

	// Add tool tips to the view control buttons
	//
	ttView.Create( this );

	CString cstrToolTip;

	// Setup the tooltip control for tooltips with the static controls
	for (nIndex = 0; nIndex < nButtons; nIndex++)
	{
		cstrToolTip.LoadString( nIndex + idString );
		tbView.GetItemRect(nIndex,&rect);
		ttView.AddTool( &tbView, (LPCTSTR)cstrToolTip, &rect, nIndex + 1);
	}

	ttView.Activate(TRUE);
	tbView.EnableToolTips(TRUE);

	tbView.CheckButton( idCommand, TRUE );
    delete [] tbbView;
}


void CDepend::OnListView() 
{
	GetDlgItem(IDC_DEPENDTREE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEPENDLIST)->ShowWindow(SW_SHOW);
	mCurrentView = 0;
	GotoDlgCtrl(GetDlgItem(IDC_DEPENDLIST));
}

void CDepend::OnTreeView() 
{
	GetDlgItem(IDC_DEPENDLIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DEPENDTREE)->ShowWindow(SW_SHOW);
	mCurrentView = 1;
	GotoDlgCtrl(GetDlgItem(IDC_DEPENDTREE));
}



void CDepend::OnColumnclickDependlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}	




/////////////////////////////////////////////////////////////////////////////




char *getTimedate(char *path)
{

	CFileStatus fstatus;
	if(CFile::GetStatus( (LPCTSTR) path,fstatus ))
	{

		//Created  %s , %ldBytes
		CString cstr;
		cstr.LoadString(IDS_CREATE_ON);

		CTime time = fstatus.m_mtime;

		struct tm * tm;
		char buffer[128];

		tm = fstatus.m_mtime.GetLocalTm(NULL );
		strftime( buffer,128,/*MSG0*/"%A %B %d %Y %I:%M%p",tm);

		sprintf(path,(char*)(LPCTSTR)cstr,buffer,fstatus.m_size);
		return path;
	}
	else
		sprintf(path,"");

	return path;
}



// utility function to create a print method on a CEditBox
////////////////////////////////////////////////////////////////////////  
/////
// CPrintBox

CPrintBox::CPrintBox()
{
}

CPrintBox::~CPrintBox()
{
}


BEGIN_MESSAGE_MAP(CPrintBox, CEdit)
	//{{AFX_MSG_MAP(CPrintBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////  
/////
// CPrintBox message handlers

class CKludgeString: public CString
{
public:
    CKludgeString() {};
    virtual ~CKludgeString() {};

	void AccessToFormatV(LPCTSTR lpszFormat, va_list argList)
    { FormatV(lpszFormat,argList);} ;
};


void __cdecl CPrintBox::Print(LPCTSTR pszFormat,...)
{
    va_list argList;
    va_start(argList, pszFormat);

    CKludgeString sFormat;
    sFormat.AccessToFormatV(pszFormat, argList);

    SetSel(-1,-1);
    ReplaceSel(sFormat);

    va_end(argList);
}




/////////////////////////////////////////////////////////////////////////////
// CReports dialog


CReports::CReports(CWnd* pParent /*=NULL*/)
	: CDialog(CReports::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReports)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReports::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReports)
	DDX_Control(pDX, IDC_REPORT, m_reporttext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReports, CDialog)
	//{{AFX_MSG_MAP(CReports)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDREPORTPRINT, OnReportprint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReports message handlers

BOOL CReports::OnInitDialog() 
{

	::SetWindowLong( m_hWnd, GWL_EXSTYLE,
		::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_CONTEXTHELP);

	CDialog::OnInitDialog();

	int nextfound = 0;

	struct resbuf rb;
	int i;

	CString cstr;

	m_nLines = 0;


	ads_getvar(/*MSG0*/"DWGNAME",&rb);

	m_reporttext.Print("%s has the following dependencies\r\n",strupr(rb.resval.rstring));
	m_nLines++;

	if(status.nxref)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_EXTREF_REP1);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;
		
		for(i=0; i<nFile; i++)
		{
			if((pFile[i].ftype == 1) && (pFile[i].found))
			{
				m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
				m_nLines++;
			}
		}
	}

	if(status.nimage)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_IMAGE_REP2);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;
	
		for(i=0; i<nFile; i++)
		{
			if((pFile[i].ftype == 2) && (pFile[i].found))
			{
				m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
				m_nLines++;
			}
		}
	}

	if(status.nshx+status.npfb+status.nttf)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_FONTS_REP3);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;
	
		if(status.nshx)
		{
			for(i=0; i<nFile; i++)
			{
				if((pFile[i].ftype == 4) && (pFile[i].found))
				{
					m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
					m_nLines++;
				}
			}
		}
		if(status.npfb)
		{
			for(i=0; i<nFile; i++)
			{
				if((pFile[i].ftype == 5) && (pFile[i].found))
				{
					m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
					m_nLines++;
				}
			}
		}
		if(status.nttf)
		{
			for(i=0; i<nFile; i++)
			{
				if((pFile[i].ftype == 6) && (pFile[i].found))
				{
					m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
					m_nLines++;
				}
			}
		}
	}

	if(status.isfmp >= 0) 
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_MISC_REP4);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;

		m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[status.isfmp].fname);
		m_nLines++;
	
	}


	if(status.ismissing)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_CANT_LOCATE_REP5);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;
	
		for(i=0; i<nFile; i++)
		{
			if(!pFile[i].found)
			{
				m_reporttext.Print(/*MSG0*/"\t%s\r\n",pFile[i].fname);
				m_nLines++;
			}
		}
	}

	m_reporttext.Print(/*MSG0*/"\r\n");
	m_nLines++;
	cstr.LoadString(IDS_NOTES_REP6);
	cstr = cstr+"\r\n";
	m_reporttext.Print((char*)(LPCTSTR)cstr);
	m_nLines++;


	if(status.nshx)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_SHX1_REP7);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;

		for(i=1; i<4; i++)
		{
			cstr.LoadString(IDS_SHX1_REP7+i);
			cstr = cstr+"\r\n";
			m_reporttext.Print((char*)(LPCTSTR)cstr);
			m_nLines++;
		}


/*
		m_reporttext.Print(".SHX fonts were found.\r\n");
		m_reporttext.Print("Please copy these fonts to the Autocad Fonts directory\r\n");
		m_reporttext.Print("Check with font manufacturer about distribution rights. \r\n");
*/
	}

	if(status.npfb)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;


		cstr.LoadString(IDS_PFB1_REP11);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;

		for(i=1; i<8; i++)
		{
			cstr.LoadString(IDS_PFB1_REP11+i);
			cstr = cstr+"\r\n";
			m_reporttext.Print((char*)(LPCTSTR)cstr);
			m_nLines++;
		}
/*
		m_reporttext.Print(".PFB fonts were found.\r\n");
		m_reporttext.Print("These fonts are no longer supported. \r\n" );
		m_reporttext.Print("Register these with your system usiing Control Panel Fonts. (WinNT Only)\r\n");
		m_reporttext.Print("To use equivalent fonts try setting your FONTMAP \r\n");
		m_reporttext.Print("variable to acad.fmp (found in the AutoCAD support directory)\r\n");
		m_reporttext.Print("or contact your font vendor for equivalent True Type Fonts\r\n");
		m_reporttext.Print("Check with font manufacturer about distribution rights. \r\n");
*/
	}

	if(status.nttf)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_TTF1_REP21);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr);
		m_nLines++;

		for(i=1; i<5; i++)
		{
			cstr.LoadString(IDS_TTF1_REP21+i);
			cstr = cstr+"\r\n";
			m_reporttext.Print((char*)(LPCTSTR)cstr);
			m_nLines++;
		}


/*
		m_reporttext.Print(".TTF fonts were found.\r\n");
		m_reporttext.Print("Register these with your system\r\n");
		m_reporttext.Print("To Register,select Fonts in your Control Panel to register these fonts \r\n");
		m_reporttext.Print("Check with font manufacturer about distribution rights. \r\n");
*/
	}

	if(status.isfmp >=0)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_MAP1_REP28);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr,pFile[status.isfmp].fname);
		m_nLines++;

		for(i=1; i<3; i++)
		{
			cstr.LoadString(IDS_MAP1_REP28+i);
			cstr = cstr+"\r\n";
			m_reporttext.Print((char*)(LPCTSTR)cstr);
			m_nLines++;
		}

/*
		m_reporttext.Print("The AutoCAD variable FONTMAP was set to %s\r\n",pFile[status.isfmp].fname);
		m_reporttext.Print("Please make that you set the FONTMAP variable to this file\r\n");
		m_reporttext.Print("before opening any drawings.\r\n");
*/
	}

	if(status.isalt >= 0)
	{
		m_reporttext.Print(/*MSG0*/"\r\n");
		m_nLines++;

		cstr.LoadString(IDS_ALT1_REP33);
		cstr = cstr+"\r\n";
		m_reporttext.Print((char*)(LPCTSTR)cstr,pFile[status.isalt].fname);
		m_nLines++;

		for(i=1; i<4; i++)
		{
			cstr.LoadString(IDS_ALT1_REP33+i);
			cstr = cstr+"\r\n";
			m_reporttext.Print((char*)(LPCTSTR)cstr);
			m_nLines++;
		}

/*
		m_reporttext.Print("The AutoCAD variable FONTALT was set to %s\r\n",pFile[status.isalt].fname);
		m_reporttext.Print("Please make sure that you set the FONTALT variable to this file\r\n");
		m_reporttext.Print("before opening any drawings.\r\n");
		m_reporttext.Print("All text styles with missing fonts are automatically set to this font\r\n");
*/
	}


	GetDlgItem(IDC_REPORT)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CReports::OnHelpInfo(HELPINFO* pHelpInfo) 
{

	DWORD dwContextId = pHelpInfo->dwContextId;

	switch(pHelpInfo->iCtrlId)
	{
	case IDSAVE :
		dwContextId = HIDSAVE;
		break;
	case IDCANCEL :
		dwContextId = HIDCANCEL;
		break;
	case IDC_REPORT :
		dwContextId = HIDC_REPORT;
		break;
	}

	char path[_MAX_PATH];

	GetModuleFileName(_hdllInstance,path,sizeof(path));

	memcpy(path+strlen(path)-3,"HLP",3);

	if(!fileexists(path))
	{
		if(ads_findfile("packngo.hlp", path) != RTNORM)
		{
			strcpy(path,"packngo.hlp");
		}
	}

	::WinHelp(m_hWnd, path,HELP_CONTEXTPOPUP,dwContextId); 

	return TRUE;
}



void CReports::OnReportprint() 
{

	CString rString;
	GetDlgItemText( IDC_REPORT, rString );

	int len = rString.GetLength();

	// allocate a buffer to tokenize
	// get out if insufficient ram to process buffer.

	char *pBuffer = new char[len+128];

	if(pBuffer == NULL)
	{

		CString cstr;
		cstr.LoadString(IDS_NO_MEM_TO_PRINT);
		ads_alert((char*)(LPCTSTR)cstr);
		return;
	}


	CPrintDialog PrnDlg(FALSE,PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS);

	if(PrnDlg.DoModal() == IDOK)
	{
		CDC PrintDC;

		HDC hPrnDC = PrnDlg.GetPrinterDC( );

		PrintDC.Attach(hPrnDC);

		DOCINFO DocInfo;
		DocInfo.cbSize = sizeof(DOCINFO);
		DocInfo.lpszDocName = "Pack&Go";
		DocInfo.lpszOutput = NULL;
	
		if(PrintDC.StartDoc(&DocInfo) != -1)
		{
			PrintDC.StartPage();
			PrintDC.SetMapMode(MM_LOMETRIC);

			int xPage = PrintDC.GetDeviceCaps(HORZSIZE);
			int yPage = PrintDC.GetDeviceCaps(VERTSIZE);

			TEXTMETRIC tm;

			PrintDC.GetTextMetrics(&tm);

			
			int nHeight = tm.tmHeight + tm.tmExternalLeading;
			int nWidth  = tm.tmAveCharWidth;;


			// as we have mapmode set to mm_lowmetric, height is in 0.1mm 
			// to calculate linesprepage, height of each text line is 
			// multiplied by 0.1 to get the correct lines per page.

			int nLinesPerPage = yPage/(nHeight*0.1) - 5;

			int nPages = m_nLines/nLinesPerPage + 1;

			PrintDC.SetWindowOrg(50,100);
			PrintDC.SelectStockObject(NULL_BRUSH);
			PrintDC.SetTextAlign(TA_LEFT | TA_BOTTOM);

			int nIncrementY = 0;
			long YCoord = nHeight*0.1*5;
			int nActualLines = 0;

			int nActualPages = 1;


			strcpy(pBuffer,(char *)(LPCTSTR) rString);
			char *tokn;

			tokn = strtok(pBuffer,"\n");

			if(tokn != NULL)
			{

				rString = trimString(tokn);

				PrintDC.TextOut(2.5*nWidth,YCoord,rString,rString.GetLength());
				nActualLines++;

				while (tokn !=NULL)
				{
					tokn = strtok (NULL,"\n");
					if(tokn != NULL)
					{
						rString = trimString(tokn);

						YCoord -= nHeight;
						PrintDC.TextOut(2.5*nWidth,YCoord,rString,rString.GetLength());
						nActualLines++;

					}
					if(nActualLines > nLinesPerPage)
					{
						// initialize number of lines
						nActualLines = 0;


						//leave 2 lines
						rString = "";
						YCoord -= nHeight;
						PrintDC.TextOut(2.5*nWidth,YCoord,rString,rString.GetLength());
						YCoord -= nHeight;
						PrintDC.TextOut(2.5*nWidth,YCoord,rString,rString.GetLength());

						// write footer
						rString.Format("Page %d of %d",nActualPages++,nPages);
						YCoord -= nHeight;
						PrintDC.TextOut(2.5*nWidth,YCoord,rString,rString.GetLength());

						// reset the start of text for new page
						YCoord = nHeight*0.1*5;


						PrintDC.EndPage();
					}

				}
		
			}
			PrintDC.EndPage();
			PrintDC.EndDoc();
		}
		DeleteDC(hPrnDC);
	}
	delete(pBuffer);
}


/////////////////////////////////////////////////////////////////////////////
// CSaveDwg dialog


CSaveDwg::CSaveDwg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveDwg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveDwg)
	m_dwgname = _T("");
	//}}AFX_DATA_INIT
}


void CSaveDwg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveDwg)
	DDX_Text(pDX, IDC_DWGNAME, m_dwgname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveDwg, CDialog)
	//{{AFX_MSG_MAP(CSaveDwg)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveDwg message handlers

void CSaveDwg::OnYes() 
{
	EndDialog(IDYES);
}

void CSaveDwg::OnNo() 
{
	overwrite = -1;
	EndDialog(IDNO);
	
}



int makeDirs(char *path)
{
	if(!makeDir(path))
	{
		return 0;
	}

	for(int i=0; i<nFile; i++)
	{
		if(pFile[i].found)
		{

			char savDir[_MAX_PATH];

			sprintf(savDir,path);
			strcat(savDir,pFile[i].szPath);

			if(!makeDir(savDir))
			{
				return 0;
			}
		}

	}
	return 1;
}



int makeDir(char *path)
{

	char *tokn;
	char tpath[_MAX_PATH];
	int mderr;

	if(path[strlen(path)-1] != /*MSG0*/'\\')
		strcat(path,/*MSG0*/"\\");

	// the following funciton will created a nested directory.
	trimString(path);

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	CString cstr;

    _splitpath( path, drive, dir, fname, ext );


	int isunc=0;

	if((path[0] == /*MSG0*/'\\') && (path[1] ==/*MSG0*/'\\'))
	{
		strcpy(tpath,/*MSG0*/"\\\\");
		path[0] = path[1] = ' ';
		leftTrim(path);
		tokn = strtok(path,/*MSG0*/"\\/");
		if((tokn != NULL) && (strlen(trimString(tokn))))
			strcat(tpath,tokn);
		else
		{
			ads_alert("\nbad UNC path...");
			return 0;
		}

		while((tokn != NULL) && (!isunc))
		{
			tokn = strtok(NULL,/*MSG0*/"\\/");
			if ((tokn !=NULL) || (isunc))
			{
				if(strlen(trimString(tokn)))
				{
					strcat(tpath,/*MSG0*/"\\");
					strcat(tpath,tokn);
					if(chdir (tpath) == 0)
					{
						isunc = 1;

						// return if not enough disk space on target drive
						// the getdiskfreespace routine fails if the trailing slash is missing
						if(!checkDiskspace(tpath))
							return 0;
					}
				}
			}
		}

		if(!isunc)
		{
			cstr.LoadString(IDS_BAD_UNC);
			sprintf(path,(char*)(LPCTSTR)cstr,tpath);
			ads_alert(path);
			return 0;
				
		}
		strcpy(drive,tpath);
	}


	if(path[0] == /*MSG0*/'\\') // relative path being used
	{
		int curdrive;
   
		/* Save current drive. */
		curdrive = _getdrive();
		sprintf(tpath,/*MSG0*/"%c:\\",curdrive + 'A' -1);
		// get the path and do the split thing so we will not have to bother with the
		// code that follows.
		strcat(tpath,path);
	    _splitpath( tpath, drive, dir, fname, ext );

	}

	if(strlen(drive))
	{
		strcpy(tpath,drive);

		if(!checkDiskspace(tpath))
			return 0;

		// reinit tpath to be used later
		strcpy(tpath,drive);
	}

	if(chdir(tpath)== 0)
	{
		strcpy(tpath,/*MSG0*/"\\");
		if(isunc)
			tokn = strtok(NULL,/*MSG0*/"\\/");
		else
			tokn = strtok(dir,/*MSG0*/"\\/");
		if(strlen(trimString(tokn)))
			strcat(tpath,tokn);
		if(chdir (tpath) != 0)
		{
			if((mderr = mkdir(tpath)) != 0)
			{
				sysError(mderr);
				return 0;
			}
		}


		while(tokn != NULL)
		{
			tokn = strtok(NULL,/*MSG0*/"\\/");
			if (tokn !=NULL)
			{
				if(strlen(trimString(tokn)))
				{
					strcat(tpath,/*MSG0*/"\\");
					strcat(tpath,tokn);
					if(chdir (tpath) != 0)
					{
						if((mderr = mkdir(tpath)) != 0)
						{
							sysError(mderr);
							return 0;
						}
					}
				}
			}
		}
	}

	return 1;
}


void sysError(int mderr)
{
	CString cstr;

	switch(errno)
	{
	case EACCES :
		cstr.LoadString(IDS_DIR_FNAME_EXIST);
		ads_alert((char*)(LPCTSTR)cstr);
		break;
	case ENOENT :
		cstr.LoadString(IDS_PATH_NOT_FOUND);
		ads_alert((char*)(LPCTSTR)cstr);
		break;
	}
}





void CReports::OnSave() 
{

	struct resbuf rb;
	char defaultname[_MAX_PATH];

	if(ads_getvar(/*MSG0*/"DWGNAME",&rb) != RTNORM)
		strcpy(defaultname,"*.txt");
	else
	{
		rb.resval.rstring[strlen(rb.resval.rstring)-4] = '\0';
		sprintf(defaultname,/*MSG0*/"%s.txt",rb.resval.rstring);
	}

	
	CFileDialog dlg(FALSE,/*MSG0*/"txt",defaultname, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files *.txt" );
	if(dlg.DoModal() == IDOK)
	{
		char path[_MAX_PATH];
		strcpy(path, (LPCTSTR)dlg.GetPathName());

		CString cstr;
		FILE *fv;

		if((fv = fopen(path,/*MSG0*/"w+")) == NULL)
		{
	
			char msg[_MAX_PATH];
			cstr.LoadString(IDS_ERROR_OPENING);
			sprintf(msg,(char*)(LPCTSTR)cstr,path);
			ads_alert(msg);
		}


		CString rString;
		GetDlgItemText( IDC_REPORT, rString );

		int len = rString.GetLength();

		// allocate a buffer to tokenize
		// get out if insufficient ram to process buffer.

		char *pBuffer = new char[len+128];

		if(pBuffer == NULL)
		{
			cstr.LoadString(IDS_MEM_TO_SAVE);
			ads_alert((char*)(LPCTSTR)cstr);
			return;
		}

		strcpy(pBuffer,(char *)(LPCTSTR) rString);

		for(int i=0; i<len; i++)
		{
			if(pBuffer[i] == '\r')
			{
				pBuffer[i] = 32;
			}
		}

		fprintf(fv,"%s",pBuffer);
		fclose(fv);
		delete(pBuffer);

	}
	
}



int checkDiskspace(char *path)
{

    DWORD lpSectorsPerCluster = 0;	// address of sectors per cluster 
    DWORD lpBytesPerSector = 0;	// address of bytes per sector 
    DWORD lpNumberOfFreeClusters = 0;	// address of number of free clusters  
    DWORD lpTotalNumberOfClusters = 0; 	// address of total number of clusters  
	DWORD FreeSpace = 0; // total disk space.

	CString cstr;

	// do not dup as may need to append to tpath
	char tpath[_MAX_PATH];


	FILE *fv;
	
	strcpy(tpath,path);

	// cat a file name to tpath and open for write.  If Fails, no write permission

	strcat(tpath,"junk.junk");

	if((fv = fopen(tpath,"w+b")) == NULL)
	{
		cstr.LoadString(IDS_NO_PERMISSION_TO_WRITE);
	    ads_alert((char*)(LPCTSTR)cstr);
		return 0;
	}
	else
	{
		fclose(fv);
		unlink(tpath);
	}


	
	strcpy(tpath,path);

	if(tpath[strlen(tpath)-1] != /*MSG0*/'\\')
		strcat(tpath,/*MSG0*/"\\");

	if(GetDiskFreeSpace(tpath,&lpSectorsPerCluster,	&lpBytesPerSector,	&lpNumberOfFreeClusters, &lpTotalNumberOfClusters))
	{
		FreeSpace = lpSectorsPerCluster * lpBytesPerSector * lpNumberOfFreeClusters;
		long spaceleft = FreeSpace - totalsize;
		if(spaceleft < 0)
		{
				cstr.LoadString(IDS_NOT_ENOUGH_DISK);
			    ads_alert((char*)(LPCTSTR)cstr);
				return 0;
		}
		else
			return 1;
	}
	else
	{
		cstr.LoadString(IDS_CANNOT_GET_DISK);
	    ads_alert((char*)(LPCTSTR)cstr);
		return 0;
	}

	return 1;
}




void doReport(char *path)
{

	FILE *fv;

	CString cstr;


	if((fv = fopen(path,/*MSG0*/"w+")) == NULL)
	{
	
		char msg[_MAX_PATH];
		sprintf(msg,"Error Opening\n%s",path);
		ads_alert(msg);
	}

	int nextfound = 0;

	struct resbuf rb;
	int i;


	ads_getvar(/*MSG0*/"DWGNAME",&rb);

	fprintf(fv,"%s has the following dependencies\n",strupr(rb.resval.rstring));

	if(status.nxref)
	{
		fprintf(fv,/*MSG0*/"\n");
		//fprintf(fv,"External References (Xref's)\n");

		cstr.LoadString(IDS_EXTREF_REP1);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

		
		for(i=0; i<nFile; i++)
		{
			if((pFile[i].ftype == 1) && (pFile[i].found))
				fprintf(fv,"\t%s\n",pFile[i].fname);
		}
	}

	if(status.nimage)
	{
		fprintf(fv,/*MSG0*/"\n");
		//fprintf(fv,"Images\n");

		cstr.LoadString(IDS_IMAGE_REP2);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

	
		for(i=0; i<nFile; i++)
		{
			if((pFile[i].ftype == 2) && (pFile[i].found))
				fprintf(fv,/*MSG0*/"\t%s\n",pFile[i].fname);
		}
	}

	if(status.nshx+status.npfb+status.nttf)
	{
		fprintf(fv,/*MSG0*/"\n");
		//fprintf(fv,"Fonts\n");

		cstr.LoadString(IDS_FONTS_REP3);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

	
		if(status.nshx)
		{
			for(i=0; i<nFile; i++)
				if((pFile[i].ftype == 4) && (pFile[i].found))
					fprintf(fv,/*MSG0*/"\t%s\n",pFile[i].fname);
		}
		if(status.npfb)
		{
			for(i=0; i<nFile; i++)
				if((pFile[i].ftype == 5) && (pFile[i].found))
					fprintf(fv,/*MSG0*/"\t%s\n",pFile[i].fname);
		}
		if(status.nttf)
		{
			for(i=0; i<nFile; i++)
				if((pFile[i].ftype == 6) && (pFile[i].found))
					fprintf(fv,/*MSG0*/"\t%s\n",pFile[i].fname);
		}
	}

	if(status.isfmp >= 0)
	{
		fprintf(fv,/*MSG0*/"\n");
		//fprintf(fv,"Miscelaneous\n");

		cstr.LoadString(IDS_MISC_REP4);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);


		fprintf(fv,/*MSG0*/"\t%s\n",pFile[status.isfmp].fname);
	
	}


	if(status.ismissing)
	{
		fprintf(fv,/*MSG0*/"\n");
		//fprintf(fv,"Program was unable to loacte the following files\n");

		cstr.LoadString(IDS_CANT_LOCATE_REP5);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);
		
		for(i=0; i<nFile; i++)
		{
			if(!pFile[i].found)
				fprintf(fv,/*MSG0*/"\t%s\n",pFile[i].fname);
		}
	}

	fprintf(fv,"\n");
	
	cstr.LoadString(IDS_NOTES_REP6);
	cstr = cstr+"\n";
	fprintf(fv,(char*)(LPCTSTR)cstr);

	//fprintf(fv,"Notes for distribution\n");


	if(status.nshx)
	{

		fprintf(fv,/*MSG0*/"\n");

		cstr.LoadString(IDS_SHX1_REP7);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

		for(i=1; i<4; i++)
		{
			cstr.LoadString(IDS_SHX1_REP7+i);
			cstr = cstr+"\n";
			fprintf(fv,(char*)(LPCTSTR)cstr);
		}

		/*
		fprintf(fv,".SHX fonts were found.");
		fprintf(fv,"Please copy these fonts to the AutoCAD Fonts directory and\n");
		fprintf(fv,"check with the font manufacturer about distribution rights.\n");
		fprintf(fv,"Fonts supplied with AutoCAD are freely distributable.\n");
		*/
	}

	if(status.npfb)
	{
		fprintf(fv,/*MSG0*/"\n");

		cstr.LoadString(IDS_PFB1_REP11);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

		for(i=1; i<8; i++)
		{
			cstr.LoadString(IDS_PFB1_REP11+i);
			cstr = cstr+"\n";
			fprintf(fv,(char*)(LPCTSTR)cstr);
		}

/*
		fprintf(fv,".PFB fonts were found.\n");
		fprintf(fv,"These fonts are no longer supported by AutoCAD. \n" );
		fprintf(fv,"Register these with your system usiing Control Panel Fonts. (WinNT Only)\n");
		fprintf(fv,"To use equivalent fonts try setting your FONTMAP \n");
		fprintf(fv,"variable to acad.fmp (found in the AutoCAD support directory)\n");
		fprintf(fv,"or contact your font vendor for equivalent True Type Fonts\n");
		fprintf(fv,"Check with the font manufacturer about distribution rights.\n");
		fprintf(fv,"Fonts supplied with AutoCAD are freely distributable.\n");
*/
	}

	if(status.nttf)
	{

		fprintf(fv,/*MSG0*/"\n");

		cstr.LoadString(IDS_TTF1_REP21);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr);

		for(i=1; i<5; i++)
		{
			cstr.LoadString(IDS_TTF1_REP21+i);
			cstr = cstr+"\n";
			fprintf(fv,(char*)(LPCTSTR)cstr);
		}

/*
		fprintf(fv,".TTF fonts were found.\n");
		fprintf(fv,"TTF fonts must be registered with the Operating System\n");
		fprintf(fv,"To register, select the Fonts option in your Control Panel\n");
		fprintf(fv,"Check with the font manufacturer about distribution rights.\n");
		fprintf(fv,"Fonts supplied with AutoCAD are freely distributable.\n");
*/
	}

	if(status.isfmp >=0)
	{
		fprintf(fv,/*MSG0*/"\n");

		cstr.LoadString(IDS_MAP1_REP28);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr,pFile[status.isfmp].fname);

		for(i=1; i<3; i++)
		{
			cstr.LoadString(IDS_MAP1_REP28+i);
			cstr = cstr+"\n";
			fprintf(fv,(char*)(LPCTSTR)cstr);
		}

/*
		fprintf(fv,"The AutoCAD variable FONTMAP was set to %s\n",pFile[status.isfmp].fname);
		fprintf(fv,"Please make that you set the FONTMAP variable to read this file\n");
		fprintf(fv,"before opening any drawings.\n");
*/
	}

	if(status.isalt >= 0)
	{
		fprintf(fv,/*MSG0*/"\n");

		cstr.LoadString(IDS_ALT1_REP33);
		cstr = cstr+"\n";
		fprintf(fv,(char*)(LPCTSTR)cstr,pFile[status.isalt].fname);

		for(i=1; i<4; i++)
		{
			cstr.LoadString(IDS_ALT1_REP33+i);
			cstr = cstr+"\n";
			fprintf(fv,(char*)(LPCTSTR)cstr);
		}
/*
		fprintf(fv,"The AutoCAD variable FONTALT was set to %s\n",pFile[status.isalt].fname);
		fprintf(fv,"Please make sure that the FONTALT variable is set to this file\n");
		fprintf(fv,"before opening any drawings.\n");
		fprintf(fv,"All text styles with missing fonts are automatically set to this font\n");
*/
	}

	fclose(fv);
}




void doScript(char *path,char *filebasepath,int iwhat)
{

	FILE *fv;

	CString cstr;


	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char paths[_MAX_PATH];

	if((fv = fopen(path,/*MSG0*/"w+")) == NULL)
	{
	
		char msg[_MAX_PATH];
		sprintf(msg,"Error Opening\n%s",path);
		ads_alert(msg);
	}

	if(filebasepath[strlen(filebasepath)-1] != /*MSG0*/'\\')
		strcat(filebasepath,/*MSG0*/"\\");


	for(int i=0; i<nFile; i++)
	{
		if((pFile[i].ftype == 1) || (pFile[i].ftype == 0)&& (pFile[i].found))
		{
			strcpy(paths,pFile[i].fname);
			_splitpath( paths, drive, dir, fname, ext );

			fprintf(fv,"_.OPEN\n");
			switch(iwhat)
			{

			case 12 :
				fprintf(fv,"%s%s%s%s\n",filebasepath,pFile[i].szPath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R12\n");
				fprintf(fv,"\n");
				fprintf(fv,"_y\n");
				break;
			case 13 :
				fprintf(fv,"%s%s%s%s\n",filebasepath,pFile[i].szPath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R13\n");
				fprintf(fv,"\n");
				fprintf(fv,"_y\n");
				fprintf(fv,"_y\n");
				break;
			case 14 :
				fprintf(fv,"%s%s%s%s\n",filebasepath,pFile[i].szPath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R14\n");
				fprintf(fv,"\n");
				break;
			case -12 :
				fprintf(fv,"%s%s%s\n",filebasepath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R12\n");
				fprintf(fv,"\n");
				fprintf(fv,"_y\n");
				break;
			case -13 :
				fprintf(fv,"%s%s%s\n",filebasepath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R13\n");
				fprintf(fv,"\n");
				fprintf(fv,"_y\n");
				fprintf(fv,"_y\n");
				break;
			case -14 :
				fprintf(fv,"%s%s%s\n",filebasepath,fname,ext);
				fprintf(fv,"_.saveas\n");
				fprintf(fv,"_R14\n");
				fprintf(fv,"\n");
				break;

			}
		}

	}
	fprintf(fv,"_.quit\n");

	fclose(fv);

}
