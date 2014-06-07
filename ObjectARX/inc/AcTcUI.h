//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1982-2006 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcTcUi.h
//
// Description:     Place for all the exported global functions 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUI_H__
#define __ACTCUI_H__

#include "adui.h"
#include "AdAChar.h"
#include <afxtempl.h>

#ifdef  _ACTCUI_BUILD
#  define   ACTCUI_PORT  __declspec(dllexport)
#else
#  define   ACTCUI_PORT  
#endif


class CAcTcUiManager;
class CAcTcUiToolPaletteSet;
class CAcTcUiToolPalette;
class CAcTcUiCatalogView;
class AcTcCatalogItem;
class AcTcCatalog;
class AcTcStockTool;
class AcTcTool;

typedef CTypedPtrArray<CPtrArray, AcTcCatalogItem*> AcTcCatalogItemArray;
typedef CTypedPtrArray<CPtrArray, AcTcStockTool*>   AcTcStockToolArray;
typedef CTypedPtrArray<CPtrArray, AcTcCatalog*>     AcTcCatalogArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPaletteSet*> AcTcUiToolPaletteSetArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPalette*> AcTcUiToolPaletteArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiCatalogView*> AcTcUiCatalogViewArray;



// Drag and drop formats
//
#define ACTCUI_DRAGFORMAT_CUSTOM        (0x1 << 0)
#define ACTCUI_DRAGFORMAT_IDROP         (0x1 << 1)
#define ACTCUI_DRAGFORMAT_HDROP         (0x1 << 2)

// For creating a new default palette set
#define ACTCUI_CNPS_NOCREATEWINDOW      (0x1 << 0)
#define ACTCUI_CNPS_NOADD               (0x1 << 1)
#define ACTCUI_CNPS_CREATEHIDDEN        (0x1 << 2)

// Clipboard formats
//
#define CF_ACTCUI_CATALOG_ITEM          ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM")
#define CF_ACTCUI_CATALOG_ITEM_HEADER   ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER")
#define CF_ACTC_CATALOG_ITEM_16_1       ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM_16_1")
#define CF_ACTCUI_CATALOG_ITEM_HEADER_16_1 ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER_16_1")
#define CF_ACTC_CATALOG_ITEM_17_1       ACRX_T(/*MSGO*/"CF_ACTC_CATALOG_ITEM_17_1")
#define CF_ACTCUI_CATALOG_ITEM_HEADER_17_1 ACRX_T(/*MSGO*/"CF_ACTCUI_CATALOG_ITEM_HEADER_17_1")
#define CF_IDROP_ACTCUI_TOOL            ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_TOOL")
#define CF_IDROP_ACTCUI_PALETTE         ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_PALETTE")
#define CF_IDROP_ACTCUI_PACKAGE         ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_PACKAGE")
#define CF_IDROP_ACTCUI_CATEGORY        ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_CATEGORY")
#define CF_IDROP_ACTCUI_CATALOG         ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_CATALOG")
#define CF_IDROP_ACTCUI_STOCKTOOL       ACRX_T(/*MSGO*/"CF_IDROP.XML_ACTCUI_STOCKTOOL")
#define CF_ACTCUI_TOOLBAR_ITEM          ACRX_T(/*MSGO*/"CF_ACTCUI_TOOLBAR_ITEM")

// AcTcUiPasteItems flags
//
#define ACTCUI_PI_SHOW_PROGRESS         (0x1 << 0)
#define ACTCUI_PI_USE_NEW_IDS           (0x1 << 1)
#define ACTCUI_PI_BREAK_SOURCE_LINK     (0x1 << 2)      // For internal use
#define ACTCUI_PI_NOTIFY_TOOLS          (0x1 << 3)      // For internal use


// Structure for drag and drop header information
//
typedef struct ACTCUI_DRAG_HEADER
{
    DWORD               mdwDragFormat;      // Dragged object: ACTCUIDRAGFORMATCUSTOM, etc.
    CLIPFORMAT          mcfClipFormat;      // Clipformat: CF_ACTC_CATALOG_ITEM, etc.
    BOOL                mbAutoCADSource;    // TRUE if source is AutoCAD
    DWORD               mdwSourceProcessId; // Source process ID
    GUID                mRootId;            // Root id of the catalog items being dragged
    GUID                mParentId;          // Parent id of the catalog items being dragged
    BOOL                mbReadOnlySource;   // True if source is read-only
    int                 mnCount;            // Number of items being dragged
    int                 mnStockTools;       // Number of stock tool items being dragged
    DWORD               mdwItemTypes;       // Item types being dragged
} ACTCUI_DRAG_HEADER;


ACTCUI_PORT CAcTcUiManager* AcTcUiGetManager(void);
ACTCUI_PORT BOOL        AcTcUiCopyItems     (COleDataSource* pDataSource,
                                             const AcTcCatalogItemArray* pItems,
                                             BOOL bAutoCADSource);
ACTCUI_PORT BOOL        AcTcUiGetDragInfo   (IDataObject* pDataObject,
                                             ACTCUI_DRAG_HEADER* pHeader);
ACTCUI_PORT BOOL        AcTcUiPasteItems    (IDataObject* pDataObject,
                                             AcTcCatalogItemArray* pItems,
                                             AcTcCatalogItemArray* pStockTools,
                                             DWORD dwFlag = ACTCUI_PI_SHOW_PROGRESS);
ACTCUI_PORT CAcTcUiToolPaletteSet* AcTcUiGetToolPaletteWindow(void);
ACTCUI_PORT BOOL        AcTcUiFilterShapesDialog(AcTcCatalogItem* pPackage,
                                             AcTcCatalogItemArray* pActiveShapes,
                                             AcTcTool*& pCurrentShape,
                                             CWnd* pParentWnd);

#endif //__ACTCUI_H__
