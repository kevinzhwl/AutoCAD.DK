#ifndef AC_GEGBL_H
#define AC_GEGBL_H
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
// This file contains the struct "AcGe" containing run time identificators,
// as well as some other enums. This file contains a strusture
// AcGeContext that contains all global variables needed by the 2d
// and 3d Geometry Library.


#ifndef unix
#include <stdlib.h>
#endif
#include "gedll.h"
#include "adesk.h"
#include "getol.h"
#include "gelibver.h"

struct
#ifdef AC_GEGBL_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGe
{
    static const AcGeLibVersion gLibVersion;
    static int   gLastError;
    enum { eGood, eBad };

    enum EntityId {
        kEntity2d,
        kEntity3d,
        kPointEnt2d,
        kPointEnt3d,
        kPosition2d,
        kPosition3d,
        kPointOnCurve2d,
        kPointOnCurve3d,
        kPointOnSurface,
        kBoundedPlane,
        kCircArc2d,
        kCircArc3d,
        kConic2d,
        kConic3d,
        kCurve2d,
        kCurve3d,
        kEllipArc2d,
        kEllipArc3d,
        kLine2d,
        kLine3d,
        kLinearEnt2d,
        kLinearEnt3d,
        kLineSeg2d,
        kLineSeg3d,
        kPlanarEnt,
        kPlane,
        kRay2d,
        kRay3d,
        kSurface,
        kSphere,
        kCylinder,
        kTorus,
        kCone,
        kSplineEnt2d,
        kPolyline2d,
        kAugPolyline2d,
        kNurbCurve2d,
        kDSpline2d,
        kCubicSplineCurve2d,
        kSplineEnt3d,
        kPolyline3d,
        kAugPolyline3d,
        kNurbCurve3d,
        kDSpline3d,
        kCubicSplineCurve3d,
        kTrimmedCrv2d,
        kCompositeCrv2d,
        kCompositeCrv3d,
        kExternalSurface,
        kNurbSurface,
        kTrimmedSurface,
        kOffsetSurface,
        kEnvelope2d,
        kCurveBoundedSurface,
        kExternalCurve3d,
        kExternalCurve2d,
        kSurfaceCurve2dTo3d,
        kSurfaceCurve3dTo2d,
	    kExternalBoundedSurface,
        kCurveCurveInt2d,
        kCurveCurveInt3d,
	    kBoundBlock2d,
	    kBoundBlock3d,
        kOffsetCurve2d,
        kOffsetCurve3d,
        kPolynomCurve3d,
        kBezierCurve3d,
	    kObject,
	    kFitData3d,
        kHatch,
        kTrimmedCurve2d,
        kTrimmedCurve3d,
		kCurveSampleData,
		kEllipCone,
		kEllipCylinder,
		kIntervalBoundBlock,
		kClipBoundary2d
    };

    enum ExternalEntityKind {kAcisEntity= 0, kExternalEntityUndefined};

    enum PointContainment {kInside, kOutside, kOnBoundary};

    enum NurbSurfaceProperties {kOpen=0x01, kClosed=0x02, kPeriodic=0x04,
                                kRational=0x08, kNoPoles=0x10, kPoleAtMin=0x20,
                                kPoleAtMax=0x40, kPoleAtBoth=0x80};

    enum OffsetCrvExtType {kFillet, kChamfer, kExtend};

    enum AcGeXConfig
    {
        kNotDefined = 1 << 0,
        kUnknown = 1 << 1,
        kLeftRight = 1 << 2,
        kRightLeft = 1 << 3,
        kLeftLeft = 1 << 4,
        kRightRight = 1 << 5,
        kPointLeft = 1 << 6,
        kPointRight = 1 << 7,
        kLeftOverlap = 1 << 8,
        kOverlapLeft = 1 << 9,
        kRightOverlap = 1 << 10,
        kOverlapRight = 1 << 11,
        kOverlapStart = 1 << 12,
        kOverlapEnd = 1 << 13,
        kOverlapOverlap = 1 << 14
    };

    enum BooleanType {kUnion, kSubtract, kCommon};
    
	enum ClipError 
	{
        eOk, 
        eInvalidClipBoundary,
        eNotInitialized
    };

    enum ClipCondition 
	{
        kInvalid, 
        kAllSegmentsInside,
        kSegmentsIntersect,
        kAllSegmentsOutsideZeroWinds,
        kAllSegmentsOutsideOddWinds,
        kAllSegmentsOutsideEvenWinds
    };
};


class AcGeVector3d;


struct
#ifdef AC_GEGBL_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeContext
{
    // System wide default tolerance.
    //
    static AcGeTol      gTol;

    static void (*gErrorFunc)();

#ifndef GELIB2D
    // Function to calculate a vector which is orthogonal to the given vector.
    //
    static void (*gOrthoVector)(const AcGeVector3d&,AcGeVector3d&);
#endif

#ifndef unix
    static void* (*gAllocMem)(size_t);
#ifdef LEAKCHECK
    static void* (*gAllocMemLeak)(size_t, const char *, int);
#endif
    static void  (*gFreeMem)(void*);
#endif
};

#endif
