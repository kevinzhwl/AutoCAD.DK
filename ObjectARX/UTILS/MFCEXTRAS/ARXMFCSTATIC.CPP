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
// ARXMFCSTATIC.CPP 
//
// DESCRIPTION:
// This is a template file to demonstrate the structure required by      
// ARX applications using MFC Static library. 
//
// 
//
//
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "aced.h"
#include <adslib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();
extern "C" HINSTANCE _hdllInstance;
extern "C" BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID);


/////////////////////////////////////////////////////////////////////////////
/// CWinApp derived class.
/////////////////////////////////////////////////////////////////////////////

class CMFCTemplateApp : public CWinApp
{
public:
	CMFCTemplateApp();
    virtual ~CMFCTemplateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCTemplateApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMFCTemplateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMFCTemplateApp, CWinApp)
	//{{AFX_MSG_MAP(CMFCTemplateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCTemplateApp construction

CMFCTemplateApp::CMFCTemplateApp()
{
}

CMFCTemplateApp::~CMFCTemplateApp()
{
}

BOOL CMFCTemplateApp::InitInstance() 
{
	TRACE("Init	Instance MFCTemplate\n");
	return CWinApp::InitInstance();
}

int CMFCTemplateApp::ExitInstance() 
{
	TRACE("Exit	Instance MFCTemplate\n");
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMFCTemplateApp object

CMFCTemplateApp theApp;



///////////////////////////////////////////////////////////////////////

void InitMFC()
{
    DllMain(_hdllInstance, DLL_PROCESS_ATTACH, NULL);
}

void EndMFC()
{
    DllMain(_hdllInstance, DLL_PROCESS_DETACH, NULL);
}




//////////////////////////////////////////////////////////////
//
// Rx interface
//
//////////////////////////////////////////////////////////////

void initApp()
{
    InitMFC();

    // Do some othe initialization here.
}

void unloadApp()
{

    EndMFC();
}

//////////////////////////////////////////////////////////////
//
// Entry point
//
//////////////////////////////////////////////////////////////


extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* )
{
  switch( msg ) 
  {
    case AcRx::kInitAppMsg: 
      initApp(); 
      break;
    case AcRx::kUnloadAppMsg: 
      unloadApp(); 
      break;
    default:
      break;
  }
  return AcRx::kRetOK;
}




