#ifndef AC_GELENT3D_H
#define AC_GELENT3D_H
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
// This file contains the class AcGeLinearEnt3d - A mathematical entity
// used to represent a line in 3-space.

#include "gecurv3d.h"
#include "gevec3d.h"
#include "gepnt3d.h"

class AcGeLine3d;
class AcGeCircArc3d;
class AcGePlanarEnt;
class
#ifdef AC_GELENT3D_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeLinearEnt3d : public AcGeCurve3d
{
public:
    // Intersection with other geometric objects.
    //
    Adesk::Boolean intersectWith (const AcGeLinearEnt3d&,
                                  AcGePoint3d& intPt,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith (const AcGePlanarEnt&, AcGePoint3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Projection-intersection with other geometric objects.
    //
    Adesk::Boolean projIntersectWith(const AcGeLinearEnt3d&,
                                  const AcGeVector3d& projDir,
                                  AcGePoint3d& pntOnThisLine,
                                  AcGePoint3d& pntOnOtherLine,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Find the overlap with other AcGeLinearEnt object
    //
    Adesk::Boolean overlap       (const AcGeLinearEnt3d&,
                                  AcGeLinearEnt3d*& overlap,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Containment tests.
    //
    Adesk::Boolean isOn          (const AcGePoint3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isOn          (const AcGePoint3d& pt, double& param,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isOn          (double param,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isOn          (const AcGePlane&,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Direction tests.
    //
    Adesk::Boolean isParallelTo  (const AcGeLinearEnt3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isParallelTo  (const AcGePlanarEnt&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo(const AcGeLinearEnt3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo(const AcGePlanarEnt&,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Test if two lines are colinear.
    //
    Adesk::Boolean isColinearTo  (const AcGeLinearEnt3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;

    // Perpendicular through a given point
    //
    void          getPerpPlane   (const AcGePoint3d&, AcGePlane&) const;

    // Definition of line.
    //
    AcGePoint3d    pointOnLine   () const;
    AcGeVector3d   direction     () const;
    void           getLine       (AcGeLine3d&) const;

    // Assignment operator.
    //
    AcGeLinearEnt3d& operator =  (const AcGeLinearEnt3d&);

protected:
    AcGeLinearEnt3d ();
    AcGeLinearEnt3d (const AcGeLinearEnt3d&);
};

#endif
