#ifndef AC_GEDXFIO_H
#define AC_GEDXFIO_H
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
// This file contains the class AcGeDxfIO - an utility class that
// performs DXF file IO.

#include "dbfiler.h"
#include "gefileio.h"
#include "gelibver.h"

class
#ifdef AC_GEDXFIO_CPP
GE_DLLEXPORT
#elif !defined(ACGE_XENTLIB)
GE_DLLIMPORT
#endif
AcGeDxfIO
{
public:

    // Write to file
    //
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3dArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTol&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeInterval&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeKnotVector&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeDoubleArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeIntArray&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveBoundary&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePlane&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundedPlane&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCone&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCylinder&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTorus&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbSurface&);
    static
   Acad::ErrorStatus outFields(AcDbDxfFiler*,const AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeSphere&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt3d&);

    // Read from file
    //
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3dArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTol&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeInterval&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeKnotVector&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeDoubleArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeIntArray&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveBoundary&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePlane&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundedPlane&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeAugPolyline3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCone&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCylinder&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTorus&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalBoundedSurface&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeSphere&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock3d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt2d&);
    static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt3d&);

    static const AcGeLibVersion  AcGeDxfIOVersion;
};

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePoint2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeVector2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeMatrix2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeScale2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePoint2dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeVector2dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePoint3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeVector3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeMatrix3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeScale3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePoint3dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeVector3dArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeTol& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeInterval& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeKnotVector& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeDoubleArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeIntArray& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCurveBoundary& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePosition2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePointOnCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeLine2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeLineSeg2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeRay2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCircArc2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeEllipArc2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeExternalCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCubicSplineCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeNurbCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCompositeCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeOffsetCurve2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePolyline2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePosition3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePointOnCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePointOnSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeLine3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeRay3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeLineSeg3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCircArc3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeEllipArc3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCubicSplineCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeNurbCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCompositeCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeOffsetCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePolyline3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeAugPolyline3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeExternalCurve3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGePlane& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeBoundedPlane& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCone& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCylinder& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeTorus& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeExternalSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeOffsetSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeNurbSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeExternalBoundedSurface& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeSphere& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeBoundBlock2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeBoundBlock3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCurveCurveInt2d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::outFields(AcDbDxfFiler* filer, const AcGeCurveCurveInt3d& ent)
{
    return AcGeFileIO::outFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePoint2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeVector2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeMatrix2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeScale2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePoint2dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeVector2dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePoint3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeVector3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeMatrix3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeScale3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePoint3dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeVector3dArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeTol& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeInterval& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeKnotVector& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeDoubleArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeIntArray& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCurveBoundary& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePosition2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePointOnCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeLine2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeLineSeg2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeRay2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCircArc2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeEllipArc2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeExternalCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCubicSplineCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeNurbCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCompositeCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeOffsetCurve2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePolyline2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePosition3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePointOnCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePointOnSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeLine3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeRay3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeLineSeg3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCircArc3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeEllipArc3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCubicSplineCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeNurbCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCompositeCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeOffsetCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePolyline3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeAugPolyline3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeExternalCurve3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGePlane& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeBoundedPlane& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCone& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCylinder& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeTorus& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeExternalSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeOffsetSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeNurbSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeExternalBoundedSurface& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeSphere& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeBoundBlock2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeBoundBlock3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCurveCurveInt2d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}

inline Acad::ErrorStatus
AcGeDxfIO::inFields(AcDbDxfFiler* filer, AcGeCurveCurveInt3d& ent)
{
    return AcGeFileIO::inFields ( (AcGeFiler*) filer, ent,
                                   AcGeDxfIO::AcGeDxfIOVersion );
}


#endif
