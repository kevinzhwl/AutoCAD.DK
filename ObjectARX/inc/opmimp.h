//
// (C) Copyright 1997-2002 by Autodesk, Inc.
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
#ifndef _OPMIMP_H
#define _OPMIMP_H

//prevent the MS header "use_ansi.h" from outputing
//its linker directives, we expect clients to specify
//what flavor (debug/release) of the C++ runtime they want to
//link against.
#pragma push_macro("_USE_ANSI_CPP")
#define _USE_ANSI_CPP
#include <vector>
#pragma pop_macro("_USE_ANSI_CPP")

#include <comdef.h>
#include "Acpi.h"
#include <category.h>
#pragma pack (push, 8)

struct ACAD_OPMPROPMAP_ENTRY
{
    UINT nDescID;                  //Alternate property name
    DISPID dispid;                 //ID of the property
    PROPCAT  catid;                //categoryID
    UINT nCatNameID;               //category Name
    UINT nElementStrID;            //expanded property name list (for pts, ex.)
    UINT nPredefinedStrID;         //IPerPropertyBrowsing enumeration strings
    LPCSTR    predefinedValues;    //IPerPropertyBrowsing enumeration values
    unsigned short grouping;       //expanded property name grouping
    bool      editable;            //show property override
    const CLSID* pclsidOther;      //CLSID for Other.. combo item dlg (not used)
    const CLSID* pclsidPropPage;   //IPerPropertyBrowsing dialog CLSID
    const IID* piidDispatch;       //dispatch pointer for property
    LPCOLESTR szEllipsesTxt;       //IPerPropertyBrowsing display string
};

#define BEGIN_OPMPROP_MAP()                                 \
    static ACAD_OPMPROPMAP_ENTRY* GetOPMPropertyMap()               \
    {                                                               \
        static ACAD_OPMPROPMAP_ENTRY pPropMap[] =                   \
        {

// DescriptionID, dispID, catagoryID, catagoryNameID, elements string list ID (semi-colon separator), predefined strings ID (semi-colon separator), predefined values, grouping, editable property, other, proppage
#define OPMPROP_ENTRY(nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, other, clsid, ellipsesTxt)      \
        {nDesID, dpid, ctid, ctNameID, elementsID, predefID, vals, grp, editable, &other, &clsid, &IID_IDispatch, OLESTR(ellipsesTxt)},

#define OPMPROP_CAT_ENTRY(nDesID, dpid, ctid, ctNameID)      \
        {nDesID, dpid, ctid, ctNameID, 0, 0, "", 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_DESC_ENTRY(nDesID, dpid)      \
        {nDesID, dpid, -2, 0, 0, 0, "", 0, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PREDEFINED_ENTRY(nDesID, dpid, predefID, values, other)      \
        {nDesID, dpid, -2, 0, 0, predefID, values, 0, 1, &other, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_ELEMENT_ENTRY(dpid, ctid, ctNameID, elementsID, grouping)      \
        {0, dpid, ctid, ctNameID, elementsID, 0, "", grouping, 1, &IID_NULL, &IID_NULL, &IID_IDispatch, OLESTR("")},

#define OPMPROP_PAGE(nDesID, dpid, ctid, ctNameID, clsid)      \
        {nDesID, dpid, ctid, ctNameID, 0, 0, "", 0, 1, &IID_NULL, &clsid, &IID_IDispatch, OLESTR("")},

#define END_OPMPROP_MAP()                                           \
            {0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL, NULL, &IID_NULL, NULL}            \
        };                                                          \
        return pPropMap;                                            \
    }

typedef BOOL (*BUTTONPROC)(IAcPiCommandButton* pButton, VARIANT Objects);
typedef int PROPCAT;

struct PER_PROP_DISP_ENTRY
{
    DISPID    m_dispid;
    LPCTSTR   m_ProgID;
    LPCTSTR   m_lpLeftIconRes;
    UINT      m_nLeftIconType;
    LPCTSTR   m_lpEllipsisBmpRes;
    UINT      m_nEllipsisBmpType;
    COLORREF  m_TextColor;
    bool      m_bFullView;
    DWORD     m_dwIntegralHeight;
    long      m_nWeight;

};

#define BEGIN_PERPROPDISPLAY_MAP()                                                            \
    static PER_PROP_DISP_ENTRY* GetPerPropDisplayArray()                                    \
    {                                                                                        \
        static PER_PROP_DISP_ENTRY pPerPropDisplayArray[] =                                 \
        {
                                                                                            
#define PROP_DISP_ENTRY(dispid, progid, lpLeftIconRes, lpLeftIconType,                        \
    lpEllipsisBmpRes, lpEllipsisBmpType, textcolor,                                          \
    bFullView, dwIntegralHeight, nWeight)                                                    \
        {dispid, progid, lpLeftIconRes, lpLeftIconType, lpEllipsisBmpRes,                    \
        lpEllipsisBmpType, textcolor, bFullView,                                             \
        dwIntegralHeight, nWeight},                                                            \
                                                                                            
#define END_PERPROPDISPLAY_MAP()                                                            \
        {-1, NULL, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, 0x80000008, false, -1, -1}                    \
        };                                                                                    \
        return pPerPropDisplayArray;                                                        \
    }

struct CATCMDBTN_ENTRY
{
    PROPCAT     m_CatID;
    UINT        m_nBtnNameId;
    LPCTSTR     m_lpEnBtnBmpRes;
    UINT        m_nEnBtnBmpType;
    LPCTSTR     m_lpDisBtnBmpRes;
    UINT        m_nDisBtnBmpType;
    long        m_nStyle;
    BUTTONPROC  m_pfnBtnProc;
};

#define BEGIN_CATCMDBTN_MAP()                                                               \
    static CATCMDBTN_ENTRY * GetCmdBtnArray()                                               \
    {                                                                                       \
        static CATCMDBTN_ENTRY pCatCmdBtnArray[] =                                          \
        {
                                                                                            
                                                                                            
#define CATCMDBTN_MAP_ENTRY(nId, NameId,                                                    \
                            lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, \
                            nStyle, pfnBtnProc)                                             \
            {nId, NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc},                        
                                                                                            
#define END_CATCMDBTN_MAP()                                                                 \
            {-1, 0, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, NULL, NULL}   \
        };                                                                                  \
        return pCatCmdBtnArray;                                                             \
    }

struct CMDBTN_ENTRY
{
    UINT        m_nBtnNameId;
    LPCTSTR     m_lpEnBtnBmpRes;
    UINT        m_nEnBtnBmpType;
    LPCTSTR     m_lpDisBtnBmpRes;
    UINT        m_nDisBtnBmpType;
    long        m_nStyle;
    BUTTONPROC  m_pfnBtnProc; //?
};

#define BEGIN_CMDBTN_MAP()                                                              \
    static CMDBTN_ENTRY * GetPropCmdBtnArray()                                          \
    {                                                                                   \
        static CMDBTN_ENTRY pCmdBtnArray[] =                                            \
        {
                                                                                            
                                                                                            
#define CMDBTN_MAP_ENTRY(NameId, lpEnBtnBmpRes, lpEnBtnBmpType,                         \
                         lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc)             \
            {NameId, lpEnBtnBmpRes, lpEnBtnBmpType, lpDisBtnBmpRes, lpDisBtnBmpType, nStyle, pfnBtnProc},                        
                                                                                            
#define END_CMDBTN_MAP()                                                                \
            {0, NULL, PICTYPE_UNINITIALIZED, NULL, PICTYPE_UNINITIALIZED, NULL, NULL}   \
        };                                                                              \
        return pCmdBtnArray;                                                            \
    }

struct CATEGORY_ENTRY
{
    PROPCAT   m_CatID;
    UINT      m_nNameId;
    UINT      m_nDescId;
    PROPCAT   m_ParentCatID;
    long      m_nWeight;
};

#define BEGIN_CAT_MAP()                                                                        \
    static CATEGORY_ENTRY*  GetCatArray()                                                    \
    {                                                                                        \
        static CATEGORY_ENTRY pCatArray[] =                                                 \
        {


#define CATEGORY_MAP_ENTRY(nId, NameId, DescId, nParentId, nWeight)              \
            {nId, NameId, DescId, nParentId, nWeight}, 

#define END_CAT_MAP()                                                                        \
            {-1, 0, 0, -1, -1}                                                  \
        };                                                                                    \
        return pCatArray;                                                                    \
    }

typedef std::vector<PER_PROP_DISP_ENTRY> PROP_DISP_VECTOR;
typedef std::vector<CATCMDBTN_ENTRY> CATCMDBTN_VECTOR;
typedef std::vector<CATEGORY_ENTRY> CATEGORY_VECTOR;
typedef std::vector<CMDBTN_ENTRY> CMDBTN_VECTOR;

#pragma pack (pop)
#include "opmdrvr.h"

#endif // _OPMIMP_H
