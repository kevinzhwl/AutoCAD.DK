#ifndef AC_GEPLANE_H
#define AC_GEPLANE_H
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
// This file contains the class AcGePlane - A mathematical entity
// used to represent a plane in 3-space.

#include "geplanar.h"

class AcGeBoundedPlane;
class AcGeLine3d;

class
#ifdef AC_GEPLANE_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGePlane : public AcGePlanarEnt
{
public:
    // Global plane objects.
    //
    static const AcGePlane kXYPlane;
    static const AcGePlane kYZPlane;
    static const AcGePlane kZXPlane;

    AcGePlane();
    AcGePlane(const AcGePlane&);
    AcGePlane(const AcGePoint3d&, const AcGeVector3d&);
    AcGePlane(const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&);
    AcGePlane(const AcGePoint3d&, const AcGeVector3d& uAxis,
              const AcGeVector3d& vAxis);
    AcGePlane(double, double, double, double);

    // Signed distance from a point to a plane.
    //
    double         signedDistanceTo (const AcGePoint3d&) const;

    // Intersection
    //
    Adesk::Boolean intersectWith    (const AcGeLinearEnt3d&, AcGePoint3d&,
                                     const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith    (const AcGePlane&, AcGeLine3d&,
                                     const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean intersectWith    (const AcGeBoundedPlane&, AcGeLineSeg3d&,
                                     const AcGeTol& = AcGeContext::gTol) const;

    // Geometry redefinition.
    //
    AcGePlane&     set              (const AcGePoint3d&, const AcGeVector3d&);
    AcGePlane&     set              (const AcGePoint3d&, const AcGePoint3d&,
                                     const AcGePoint3d&);
    AcGePlane&     set              (double, double, double, double);
    AcGePlane&     set              (const AcGePoint3d&,
                                     const AcGeVector3d& uAxis,
                                     const AcGeVector3d& vAxis);
    // Assignment operator.
    //
    AcGePlane&     operator =       (const AcGePlane&);
};

#endif
