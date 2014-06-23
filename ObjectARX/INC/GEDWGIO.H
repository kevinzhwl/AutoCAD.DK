#ifndef AC_GEDWGIO_H
#define AC_GEDWGIO_H
//
// (C) Copyright 1993-1997 by Autodesk, Inc.
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
// DESCRIPTION:
//
// This file contains the class AcGeDwgIO - an utility class that
// performs DWG file IO.

#include "dbfiler.h"
#include "gefileio.h"
#include "gelibver.h"

class
#ifdef AC_GEDWGIO_CPP
GE_DLLEXPORT
#elif !defined(ACGE_XENTLIB)
GE_DLLIMPORT
#endif
AcGeDwgIO
{
public:

    // Write out to file
    //
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeMatrix2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeScale2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeMatrix3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeScale3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePoint3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeVector3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeTol&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeInterval&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeKnotVector&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeDoubleArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeIntArray&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveBoundary&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePosition2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLine2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLineSeg2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeRay2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCircArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeEllipArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePolyline2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePosition3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePointOnSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLine3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeRay3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeLineSeg3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePlane&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundedPlane&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCircArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeEllipArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGePolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCone&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCylinder&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeTorus&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeExternalSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeOffsetSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeNurbSurface&);
    static
   Acad::ErrorStatus outFields(AcDbDwgFiler*,const AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeSphere&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus outFields(AcDbDwgFiler*, const AcGeCurveCurveInt3d&);

    // Read in from file
    //
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeMatrix2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeScale2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeMatrix3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeScale3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePoint3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeVector3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeTol&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeInterval&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeKnotVector&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeDoubleArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeIntArray&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveBoundary&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePosition2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLine2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLineSeg2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeRay2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCircArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeEllipArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePolyline2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePosition3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePointOnSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLine3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeRay3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeLineSeg3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePlane&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundedPlane&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCircArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeEllipArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGePolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCone&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCylinder&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeTorus&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeOffsetSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeNurbSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeSphere&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus inFields(AcDbDwgFiler*, AcGeCurveCurveInt3d&);

    static const AcGeLibVersion  AcGeDwgIOVersion;
};

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePoint2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeVector2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeMatrix2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeScale2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePoint2dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeVector2dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePoint3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeVector3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeMatrix3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeScale3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePoint3dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeVector3dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeTol& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeInterval& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeKnotVector& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeDoubleArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeIntArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCurveBoundary& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePosition2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePointOnCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeLine2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeLineSeg2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeRay2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCircArc2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeEllipArc2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeExternalCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCubicSplineCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeNurbCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCompositeCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeOffsetCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePolyline2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePosition3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePointOnCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePointOnSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeLine3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeRay3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeLineSeg3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCircArc3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeEllipArc3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCubicSplineCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeNurbCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCompositeCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeOffsetCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePolyline3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeAugPolyline3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeExternalCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGePlane& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeBoundedPlane& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCone& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCylinder& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeTorus& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeExternalSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeOffsetSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeNurbSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeExternalBoundedSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeSphere& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeBoundBlock2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeBoundBlock3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCurveCurveInt2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::outFields(AcDbDwgFiler* filer, const AcGeCurveCurveInt3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePoint2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeVector2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeMatrix2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeScale2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePoint2dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeVector2dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePoint3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeVector3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeMatrix3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeScale3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePoint3dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeVector3dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeTol& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeInterval& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeKnotVector& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeDoubleArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeIntArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCurveBoundary& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePosition2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePointOnCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeLine2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeLineSeg2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeRay2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCircArc2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeEllipArc2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeExternalCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCubicSplineCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeNurbCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCompositeCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeOffsetCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePolyline2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePosition3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePointOnCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePointOnSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeLine3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeRay3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeLineSeg3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCircArc3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeEllipArc3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCubicSplineCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeNurbCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCompositeCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeOffsetCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePolyline3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeAugPolyline3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeExternalCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGePlane& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeBoundedPlane& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCone& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCylinder& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeTorus& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeExternalSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeOffsetSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeNurbSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeExternalBoundedSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeSphere& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeBoundBlock2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeBoundBlock3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCurveCurveInt2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}

inline Acad::ErrorStatus
AcGeDwgIO::inFields(AcDbDwgFiler* filer, AcGeCurveCurveInt3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDwgIO::AcGeDwgIOVersion );
}


#endif
