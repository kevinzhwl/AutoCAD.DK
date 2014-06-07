//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#include "ArxDbgUiTdcHostAppSrv.h"
#include "ArxDbgUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::ArxDbgUiTdcHostAppSrv
**
**  **jma
**
*************************************/

ArxDbgUiTdcHostAppSrv::ArxDbgUiTdcHostAppSrv()
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcHostAppSrv)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::~ArxDbgUiTdcHostAppSrv
**
**  **jma
**
*************************************/

ArxDbgUiTdcHostAppSrv::~ArxDbgUiTdcHostAppSrv()
{
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcHostAppSrv::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcHostAppSrv)
    DDX_Control(pDX, ARXDBG_LC_DATA, m_dataList);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcHostAppSrv message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcHostAppSrv, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcHostAppSrv)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcHostAppSrv message handlers

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcHostAppSrv::OnInitDialog() 
{
    ArxDbgUiTdcRxObjectBase::OnInitDialog();

	buildColumns(m_dataList);
    displayCurrent();

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcHostAppSrv::displayCurrent()
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;

	AcDbHostApplicationServices* appSrv = acdbHostApplicationServices();
	ASSERT(appSrv != NULL);

	addToDataList(_T("Ready To Display Messages"), ArxDbgUtils::booleanToStr(appSrv->readyToDisplayMessages(), str));
	addToDataList(_T("Do Full CRC Check"), ArxDbgUtils::booleanToStr(appSrv->doFullCRCCheck(), str));

	char tempPath[1024];
	Adesk::UInt32 bufSize = appSrv->getTempPath(1024, tempPath);
	addToDataList(_T("Temp Path"), tempPath);

	addToDataList(_T("Working Database"), ArxDbgUtils::dbToStr(appSrv->workingDatabase(), str));
	addToDataList(_T("Default Undo Controller"), ArxDbgUtils::ptrToStr(appSrv->defaultUndoController(), str));
	addToDataList(_T("Working Transaction Manager"), ArxDbgUtils::ptrToStr(appSrv->workingTransactionManager(), str));

	addToDataList(_T("Program"), appSrv->program());
	addToDataList(_T("Product"), appSrv->product());
	addToDataList(_T("Company Name"), appSrv->companyName());

	ProdIdCode idCode = appSrv->prodcode();
	if (idCode == kProd_ACAD)
		str = _T("Prod_ACAD");
	else if (idCode == kProd_LT)
		str = _T("Prod_LT");
	else if (idCode == kProd_OEM)
		str = _T("Prod_OEM");
	else if (idCode == kProd_AcDb)
		str = _T("Prod_AcDb");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

	addToDataList(_T("Product ID Code"), str);
	addToDataList(_T("Release Major Minor String"), appSrv->releaseMajorMinorString());
	addToDataList(_T("Release Major Version"), ArxDbgUtils::intToStr(appSrv->releaseMajorVersion(), str));
	addToDataList(_T("Release Minor Version"), ArxDbgUtils::intToStr(appSrv->releaseMinorVersion(), str));
	addToDataList(_T("Version String"), appSrv->versionString());
	addToDataList(_T("Registry Product Root Key"), appSrv->getRegistryProductRootKey());
	addToDataList(_T("Registry Product LCID"), ArxDbgUtils::intToStr(appSrv->getRegistryProductLCID(), str));
	addToDataList(_T("Code Page Id"), ArxDbgUtils::intToStr(appSrv->getSystemCodePage(), str));

	addToDataList(_T("Alternate Font Name"), appSrv->getAlternateFontName());
	addToDataList(_T("Font Map File Name"), appSrv->getFontMapFileName());
	addToDataList(_T("Cache Symbol Indices"), ArxDbgUtils::booleanToStr(appSrv->cacheSymbolIndices(), str));

	drawPropsList(m_dataList);
}
