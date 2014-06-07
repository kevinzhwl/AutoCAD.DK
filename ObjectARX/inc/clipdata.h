//
//                 (C) Copyright 1988-1999 by Autodesk, Inc.
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
// Name:    ClipData.h
//
// Remarks: Supports Clipboard and Drag and Drop Geometry from AutoCAD
//
//////////////////////////////////////////////////////////////////////////////
#pragma pack (push, 8)

enum eClipInfoFlags {
    kbDragGeometry = 0x01
};

enum eExpandedClipDataTypes {
    kDcPlotStyles       = 1,
    kDcXrefs            = 2,
    kDcLayouts          = 3,
    kDcBlocks           = 4,
    kDcLayers           = 5,
    kDcDrawings         = 6,
    kDcLinetypes        = 7,
    kDcTextStyles       = 8,
    kDcDimStyles        = 9,
    kDcBlocksWithAttdef = 10,
//#ifdef ADCHATCH
    kDcHatches          = 11
//#endif
};

const int nBlockFileSize = 260;

// Clipboard and drag and drop information stored in the format
// CAcadDoc::m_cfPrivate ("AutoCAD.r15").
//
typedef struct tagClipboardInfo {
    char        szTempFile[nBlockFileSize];     // block temp file name
    char        szSourceFile[nBlockFileSize];   // file name of drawing from which selection was made
    char        szSignature[4];                 // szClipSignature
    int         nFlags;                         // kbDragGeometry: dragging geometry from AutoCAD?
    AcGePoint3d dptInsert;                      // original world coordinate of insertion point
    RECT        rectGDI;                        // GDI coord bounding rectangle of sset
    void*       mpView;                         // Used to verify that this object was created in this view (CDwgView*)
    DWORD       m_dwThreadId;                   // AutoCAD thread that created this DataObject
    int         nLen;                           // Length of next segment of data, if any, starting with chData
    int         nType;                          // Type of data, if any (eExpandedClipDataTypes)
    char        chData[1];                      // Start of data, if any.
} ClipboardInfo;

#define szClipSignature /*MSG0*/"R15"
#pragma pack (pop)

