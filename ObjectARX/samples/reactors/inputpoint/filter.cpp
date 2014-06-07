//   Copyright (C) 1998-2006 by Autodesk, Inc.
//
//     Permission to use, copy, modify, and distribute this software
//     for any purpose is restricted by the VIP Subscription program
//     license agreement.  This application was developed exclusively
//     for distribution by the VIP subscription program and may not
//     be posted pubicly, modified, copied, or distributed by any other
//     methods. 
//
//     AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
//     AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
//     MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//     DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
//     UNINTERRUPTED OR ERROR FREE.
//
//     Use, duplication, or disclosure by the U.S. Government is subject to 
//     restrictions set forth in FAR 52.227-19 (Commercial Computer 
//     Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
//     (Rights in Technical Data and Computer Software), as applicable. 
//

// AsdkInputPointFilter methods
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdbabb.h"
#include "adeskabb.h"
#include "aced.h"
#include "acgi.h"
#include "dbents.h"
#include "tchar.h"

#include "filter.h"



Acad::ErrorStatus
AsdkInputPointFilter::processInputPoint(
          bool&                            changedPoint,
          AcGePoint3d&                     newPoint,
          bool&                            displayOsnapGlyph,

          bool&                            changedTooltipStr,
          TCHAR*&                           newTooltipString,

          bool&                            retry,
          AcGiViewportDraw*                pDrawContext,

          AcApDocument*                    document,

          bool                             pointComputed,

          int                              history,

          const AcGePoint3d&               lastPoint,

          const AcGePoint3d&               rawPoint,

          const AcGePoint3d&               grippedPoint,

          const AcGePoint3d&               cartesianSnappedPoint,

          const AcGePoint3d&               osnappedPoint,
          AcDb::OsnapMask                  osnapMasks,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
          AcDb::OsnapMask                  osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,

          const AcArray<AcDbObjectId>&     pickedEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedPickedEntities,
          const AcArray<int>&              gsSelectionMark, // of 0th element in
                                                            // pickedEntities
          // AutoSnap Info:
          const AcArray<AcDbObjectId>&     keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedKeyPointEntities,
          const AcArray<int>&              keyPointGsSelectionMark,
          const AcArray<AcGeCurve3d*>&     alignmentPaths,

          const AcGePoint3d&               computedPoint,

          const TCHAR*                      tooltipString )
{
    if ( !pointComputed )
        // Points cannot be computed in the Filter
        // Forced picking may be enabled
        return Acad::eOk;

    if ( m_changePoint )
    {
        // Change the computed point to an offset of (0.2, 0.2, 0.2)
        // and draw a circular glyph at that ne point
        newPoint = computedPoint + AcGeVector3d(0.2,0.2,0.0);
        changedPoint = true;
        pDrawContext->geometry().circle( newPoint, 0.1, AcGeVector3d::kZAxis );
        displayOsnapGlyph = true;

        if ( 0 != pickedEntities.length() )
        {
            // Add a tooltip to line entities under the cursor
            //
            AcDbLine *pLine;
            if ( Acad::eOk == acdbOpenObject( pLine, pickedEntities[X], kForRead ))
            {
                pLine->close();
                changedTooltipStr = true;
                newTooltipString = _T("This is a line!!!");
            }
        }
    }
    return Acad::eOk;
}
