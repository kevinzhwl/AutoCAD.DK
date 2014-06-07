#ifndef   _ACDBLMGR_H
#define   _ACDBLMGR_H
// 
// (C) Copyright 1993-1999 by Autodesk, Inc. 
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
//  AcDbLMgr.h - Exported Interface class for Database specific 
//               routines that manipulate and access AcDbLayout 
//               objects.
//
#include "adesk.h"
#include "dbid.h"
#include "dblayout.h"
#include "dblaymgrrctr.h"
#pragma pack (push, 8)

// The maximum number of layouts in a single drawing.
#define  MAX_PSPACE_LAYOUTS     256

class AcDbObjectId;

class AcDbLayoutManager: public AcRxObject  {
  public:

    virtual Acad::ErrorStatus 
    setCurrentLayout          (const char* newname) = 0;
    virtual Acad::ErrorStatus 
    setCurrentLayoutId        (AcDbObjectId layoutId) = 0;
    virtual const char *      
    findActiveLayout          (Adesk::Boolean allowModel) = 0;

    virtual AcDbObjectId      
    getActiveLayoutBTRId      () = 0;

    virtual AcDbLayout *      
    findLayoutNamed           (const char* name, 
                               Adesk::Boolean leaveRecordOpen = FALSE) = 0;
    virtual Acad::ErrorStatus 
    copyLayout                (const char* copyname, 
                               const char* newname) = 0;

    virtual Acad::ErrorStatus 
    deleteLayout              (const char* delname) = 0;

    virtual Acad::ErrorStatus 
    createLayout              (const char *newname, AcDbObjectId& layoutId, 
                               AcDbObjectId& blockTableRecId, 
                               AcDbDatabase* pDatabase = NULL) = 0;
    virtual Acad::ErrorStatus 
    renameLayout              (const char* oldname, 
                               const char* newname) = 0;
    virtual Acad::ErrorStatus 
    cloneLayout               (AcDbLayout* pLBTR, 
                               const char* newname, 
                               int newTabOrder = 0) = 0;

    virtual AcDbObjectId      
    getNonRectVPIdFromClipId  (AcDbObjectId clipId) = 0;

    virtual bool              
    isVpnumClipped            (short index) = 0;

    virtual int               
    countLayouts              (AcDbDatabase *useDb = NULL) = 0;

    virtual void 
    addReactor                (AcDbLayoutManagerReactor * newObj) = 0;

    virtual void 
    removeReactor             (AcDbLayoutManagerReactor * delObj) = 0;
};

Acad::ErrorStatus 
acdbDoSetupForLayouts(AcDbDatabase* pDatabase, unsigned int& contextHandle);

Acad::ErrorStatus
acdbClearSetupForLayouts(unsigned int contextHandle);

#pragma pack (pop)
#endif // _ACDBLMGR_H
