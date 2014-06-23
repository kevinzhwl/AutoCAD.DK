#ifndef AC_GESURF_H
#define AC_GESURF_H
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
// AcGeSurface class is an abstract base class for all other parametric
// surfaces.

#include "geent3d.h"

class AcGeVector3dArray;
class AcGePoint2d;
class AcGeCurve3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGePointOnSurfaceData;
class AcGeInterval;


class
#ifdef AC_GESURF_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeSurface : public AcGeEntity3d
{
public:
    // Parameter related.
    //
    AcGePoint2d     paramOf        (const AcGePoint3d&,
                                    const AcGeTol& = AcGeContext::gTol) const;
    // Point containment
    //
    Adesk::Boolean  isOn           (const AcGePoint3d&,
                                    const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean  isOn           (const AcGePoint3d&, AcGePoint2d& paramPoint,
                                    const AcGeTol& = AcGeContext::gTol ) const;
    // Operations.
    //
    AcGePoint3d closestPointTo(const AcGePoint3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;

    void getClosestPointTo(const AcGePoint3d&, AcGePointOnSurface&,
                           const AcGeTol& = AcGeContext::gTol) const;
	
    double          distanceTo     (const AcGePoint3d&,
                                    const AcGeTol& = AcGeContext::gTol) const;

    Adesk::Boolean  isNormalReversed () const;
    AcGeSurface&    reverseNormal    ();

    // Assignment operator.
    //
    AcGeSurface&    operator =     (const AcGeSurface&);

    // Bounds in parameter space.
    //
    void   getEnvelope  (AcGeInterval& u, AcGeInterval& v) const;

    // Evaluators.
    // Derivative arrays are indexed partialU, partialV followed by
    // the mixed partial.
    //
    AcGePoint3d   evalPoint   (const AcGePoint2d& param) const;
    AcGePoint3d   evalPoint   (const AcGePoint2d& param, int NumDeriv,
                               AcGeVector3dArray& derivatives) const;
    AcGePoint3d   evalPoint   (const AcGePoint2d& param, int NumDeriv,
                               AcGeVector3dArray& derivatives,
                               AcGeVector3d& normal) const;
protected:
    AcGeSurface ();
    AcGeSurface (const AcGeSurface&);
};

#endif
