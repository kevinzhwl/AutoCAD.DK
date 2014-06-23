// (C) Copyright 1997 by Autodesk, Inc. 
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
//


#include "stdafx.h"
#include "resource.h"

#include "packcore.h"
#include "packutil.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


char *leftTrim(char *string)
{
	int sc,sl;
	int iii;
	sc = 0;
	sl = strlen(string);
	while(isspace(string[sc]))
		sc++;
	if (sc)
		for (iii=0; iii<sl-sc+1; iii++)
			string[iii]=string[sc+iii];
	return(string);

}

// removes all leading and trailing blanks
char *trimString(char *string)
{
int sc,sl;
int iii;
sc = 0;
sl = strlen(string);
while(isspace(string[sc]))
  sc++;
if (sc)
  for (iii=0; iii<sl-sc+1; iii++)
    string[iii]=string[sc+iii];
sl = strlen(string);
sc = sl-1;
while(isspace(string[sc]))
  {
  string[sc]=/*MSG0*/'\0';
  sc--;
  }
return(string);
}

int fileexists(char *fnm)
{
int found;

FILE *fv;
fv = fopen(fnm,/*MSG0*/"r");
found = ((fv==NULL) ? 0 : 1);
if (found)
  fclose(fv);
return(found);
}







/////////////////////////////////////////////////////////////////////////////
// CDReplace dialog


CDReplace::CDReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CDReplace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDReplace)
	m_FileExists = _T("");
	m_FileReplace = _T("");
	m_ESize = _T("");
	m_RSize = _T("");
	//}}AFX_DATA_INIT
}


void CDReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDReplace)
	DDX_Text(pDX, IDC_FileE, m_FileExists);
	DDV_MaxChars(pDX, m_FileExists, 60);
	DDX_Text(pDX, IDC_FileR, m_FileReplace);
	DDV_MaxChars(pDX, m_FileReplace, 60);
	DDX_Text(pDX, IDC_FileESize, m_ESize);
	DDX_Text(pDX, IDC_FileRSize, m_RSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDReplace, CDialog)
	//{{AFX_MSG_MAP(CDReplace)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDYESALL, OnYesall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDReplace message handlers

void CDReplace::OnNo() 
{
	overwrite = 0;
	EndDialog(IDNO);
	
}

void CDReplace::OnYes() 
{
	overwrite = 1;
	EndDialog(IDYES);
	
}

void CDReplace::OnYesall() 
{
	overwrite = 2;
	EndDialog(IDYESALL);
	
}

void CDReplace::OnCancel() 
{

	overwrite = -1;
	EndDialog(IDCANCEL);
}




/////////////////////////////////////////////////////////////////////////////
// CDirCreate dialog


CDirCreate::CDirCreate(CWnd* pParent /*=NULL*/)
	: CDialog(CDirCreate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirCreate)
	m_dirname = _T("");
	//}}AFX_DATA_INIT
}


void CDirCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirCreate)
	DDX_Text(pDX, IDC_DIRNAME, m_dirname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirCreate, CDialog)
	//{{AFX_MSG_MAP(CDirCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirCreate message handlers

void CDirCreate::OnCancel() 
{

	overwrite = -1;
	
	CDialog::OnCancel();
}

void CDirCreate::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
