//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1982-2002 by Autodesk, Inc.
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

// Name:            AcTcUiCatalogViewItem.h
//
// Description:     Header for CAcTcUiCatalogViewItem class. This class 
//                  implements the CatalogItem item in the Catalog view window.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUICATALOGVIEWITEM_H__
#define __ACTCUICATALOGVIEWITEM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcTc.h"
#include "AcTcUi.h"

class CAcTcUiCatalogView;


// View item styles
// Push button style
#define ACTCUI_CVISTYLE_PUSHBUTTON      0x0
// Show text for items. 
// For some strange reason, this value cannot be 1. If it is 1 the images 
// are not painted properly. Most of the images will be missing.
#define ACTCUI_CVISTYLE_SHOWTEXT        (0x1 << 1)
#define ACTCUI_CVISTYLE_RIGHTTEXT       (0x1 << 2)
                                        
// View item states
// Item is highlighted (raised)
#define ACTCUI_CVISTATE_HIGHLIGHTED     (0x1 << 0)
// Item is selected (selected)           
#define ACTCUI_CVISTATE_SELECTED        (0x1 << 1)
// Item is selected (halo)           
#define ACTCUI_CVISTATE_HALO            (0x1 << 2)
// Item is focused
#define ACTCUI_CVISTATE_FOCUSED         (0x1 << 3)

// Flags for GetRect()
#define ACTCUI_CVIR_BOUNDS              (0x1 << 0)
#define ACTCUI_CVIR_IMAGE               (0x1 << 1)
#define ACTCUI_CVIR_LABEL               (0x1 << 2)
#define ACTCUI_CVIR_USEFULLLABEL        (0x1 << 3)


class __declspec(dllexport) CAcTcUiCatalogViewItem : public CObject  
{
    friend class CAcTcUiImpCatalogView;

public:
    virtual ~CAcTcUiCatalogViewItem();

    BOOL                Render              (BOOL bEraseBackground = FALSE);
    BOOL                Render              (CDC* pDC, int x, int y);
    BOOL                GetRect             (LPRECT lpRect, 
                                             int nCode) const;
    AcTcCatalogItem *   GetCatalogItem      (void) const;
    BOOL                SetCatalogItem      (AcTcCatalogItem* pCatalogItem);
    DWORD               GetStyle            (void) const;
    DWORD               GetState            (void) const;
    BOOL                SetState            (DWORD dwState);
    BOOL                GetPosition         (LPPOINT lpPoint) const;
    DWORD               GetData             (void) const;
    BOOL                SetData             (DWORD dwData);
    BOOL                Highlight           (BOOL bHighlight = TRUE);
    BOOL                Select              (BOOL bSelect = TRUE);
    BOOL                Halo                (BOOL bHalo = TRUE);

protected:
    // Constructors are protected so that this object can only be 
    // created by CAcTcUiCatalogView.
    CAcTcUiCatalogViewItem(CAcTcUiCatalogView* pCatalogView);
    CAcTcUiCatalogViewItem(CAcTcUiCatalogView* pCatalogView, 
        AcTcCatalogItem* pCatalogItem, const CSize& sizeImage, 
        DWORD dwStyle = ACTCUI_CVISTYLE_PUSHBUTTON);

protected:
    void            *   mpImpObj;           // Imp object CAcTcUiImpCatalogViewItem
};


// Array of CAcTcUiCatalogViewItem objects
typedef CTypedPtrArray<CPtrArray, CAcTcUiCatalogViewItem*> CAcTcUiCatalogViewItemArray;


#endif //__ACTCUICATALOGVIEWITEM_H__
