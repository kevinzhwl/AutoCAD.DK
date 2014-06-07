//
// (C) Copyright 1999-2002,2004 by Autodesk, Inc. 
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

// AsdkMfcComSamp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include <rxregsvc.h>
#include <aced.h>
#include <rxmfcapi.h>
#include "CAcadApplication.h"
#include "CAcadDocument.h"
#include "CAcadModelSpace.h"
#include "CAcadMenuBar.h"
#include "CAcadMenuGroup.h"
#include "CAcadMenuGroups.h"
#include "CAcadPopupMenu.h"
#include "CAcadPopupMenus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE MyAsdkMfcComSampDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MyAsdkMfcComSamp.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(MyAsdkMfcComSampDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(MyAsdkMfcComSampDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MyAsdkMfcComSamp.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(MyAsdkMfcComSampDLL);
	}
	return 1;   // ok
}


void addCircleThroughMfcCom()
{
	TRY
	{
		CAcadApplication IApp;
		CAcadDocument IDoc;
		CAcadModelSpace IMSpace;

		IDispatch *pDisp = acedGetAcadWinApp()->
			GetIDispatch(TRUE); //AddRef is called on the pointer
		IApp.AttachDispatch(pDisp); // does not call AddRef()
		IApp.put_Visible(true);
		pDisp = IApp.get_ActiveDocument(); //AddRef is called
		IDoc.AttachDispatch(pDisp);
		pDisp = IDoc.get_ModelSpace(); //AddRef is called
		IMSpace.AttachDispatch(pDisp);

		SAFEARRAYBOUND rgsaBound;
		rgsaBound.lLbound = 0L;
		rgsaBound.cElements = 3;
		SAFEARRAY* pStartPoint = NULL;
		pStartPoint = SafeArrayCreate(VT_R8, 1, &rgsaBound);
		// X value
		long i = 0;
		double value = 4.0;
		SafeArrayPutElement(pStartPoint, &i, &value);
		// Y value
		i++;
		value = 2.0;
		SafeArrayPutElement(pStartPoint, &i, &value);
		// Z value
		i++;
		value = 0.0;
		SafeArrayPutElement(pStartPoint, &i, &value);

		VARIANT pt1;
		VariantInit(&pt1);
		V_VT(&pt1) = VT_ARRAY | VT_R8;
		V_ARRAY(&pt1) = pStartPoint;
		IMSpace.AddCircle(pt1, 2.0);

		VariantClear(&pt1);
		// Release() is called implicitly on the local objects
	}
	CATCH(COleDispatchException,e) 
	{
			e->ReportError();
			e->Delete();
	}
	END_CATCH;


}


void
addMenuThroughMfcCom()
{
    TRY
    {
        CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));

        CAcadMenuBar IMenuBar(IAcad.get_MenuBar());

        long numberOfMenus;
        numberOfMenus = IMenuBar.get_Count();

        CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());

        VARIANT index;
        VariantInit(&index);
        V_VT(&index) = VT_I4;
        V_I4(&index) = 0;

        CAcadMenuGroup IMenuGroup(IMenuGroups.Item(index));

        CAcadPopupMenus IPopUpMenus(IMenuGroup.get_Menus());

        CString cstrMenuName = "AsdkComAccess";

        VariantInit(&index);
        V_VT(&index) = VT_BSTR;
        V_BSTR(&index) = cstrMenuName.AllocSysString();

        IDispatch* pDisp=NULL;

		//see if the menu is already there
        TRY{pDisp = IPopUpMenus.Item(index); pDisp->AddRef();} CATCH(COleDispatchException,e){}END_CATCH;

        if (pDisp==NULL) {
            //create it
            CAcadPopupMenu IPopUpMenu(IPopUpMenus.Add(cstrMenuName));

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 0;
            IPopUpMenu.AddMenuItem(index, "&Add A ComCircle", "_AsdkMfcComCircle ");

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 1;
            IPopUpMenu.AddSeparator(index);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 2;
            IPopUpMenu.AddMenuItem(index, "Auto&LISP Example", "(prin1 \"Hello\") ");

            pDisp = IPopUpMenu.m_lpDispatch;
            pDisp->AddRef();
        }

        CAcadPopupMenu IPopUpMenu(pDisp);
        if (!IPopUpMenu.get_OnMenuBar())
        {
            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = numberOfMenus - 2;;
            IPopUpMenu.InsertInMenuBar(index);
        }
        else
        {
            VariantInit(&index);
            V_VT(&index) = VT_BSTR;
            V_BSTR(&index) = cstrMenuName.AllocSysString();
            IPopUpMenus.RemoveMenuFromMenuBar(index);
			VariantClear(&index);
        }
        pDisp->Release();
    }
    CATCH(COleDispatchException,e)
    {
        e->ReportError();
        e->Delete();
    }
    END_CATCH;
}

static void initApp()
{
    acedRegCmds->addCommand(
        "ASDK_MFC_COM", 
        "AsdkMfcComCircle",
        "MfcComCircle", 
        ACRX_CMD_MODAL, 
        addCircleThroughMfcCom);

	acedRegCmds->addCommand("ASDK_MFC_COM",
		"AsdkMfcComMenu",
		"MfcComMenu",
		ACRX_CMD_MODAL,
		addMenuThroughMfcCom);
}

static void unloadApp()
{
    acedRegCmds->removeGroup("ASDK_MFC_COM");
}

extern "C" AcRx::AppRetCode acrxEntryPoint
    (AcRx::AppMsgCode msg, void* appId)
{
    switch(msg)
    {
    case AcRx::kInitAppMsg: 
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
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
