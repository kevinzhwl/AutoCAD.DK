#ifndef AMODELER_INC_PLANE_H
#define AMODELER_INC_PLANE_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
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
// Declaration of a class Plane, keeping a definition of an oriented plane in 
// 3D. The plane is defined by its (unit) normal vector and parameter 'd', 
// which is the signed distance of the plane from the origin of the coordinate 
// system.
//
// For all points on the plane holds:
//
//   normal * point + d = 0
//
// The plane parameters are accessed via public data members 'normal' and 'd'.
//
// If the plane is invalid (cannot be constructed), the plane normal is set to 
// a null vector.
//
///////////////////////////////////////////////////////////////////////////////

#include "point3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Plane
{
public:

    Plane()                                 : normal(Vector3d::kNull), d(0) {}
    Plane(Vector3d nn, double dd)           : normal(nn), d(dd)             {}
    Plane(Point3d, Vector3d); 
    Plane(const Point3d&, const Point3d&,  const Point3d&);
    Plane(const Point3d&, const Vector3d&, const Vector3d&);

    // Create plane from a polygon of vertices (n >=3). All polygon vertices
    // are used to calculate the plane coefficients to make the formula
    // symetrical.
    //
    Plane(const Point3d plg[], int n);

    // The plane normal is given, just calculate the 'd' parameter from all 
    // polygon vertices.
    //
    Plane(const Point3d plg[], int n, const Vector3d& normal);

    Plane    operator -()                const { return Plane(-normal, -d); }
    double   dist      (Point3d p)       const { return p % normal + d; }
    Point3d  project   (const Point3d& ) const;
    Vector3d project   (const Vector3d&) const;
    Line3d   project   (const Line3d&  ) const;

    Point3d  operator* (const Line3d&  ) const;

    bool     isValid   () const { return fabs(normal.length() - 1) < epsNor(); }

    bool     isEqual   (Plane) const;

    void     orthoPlane(int& i1, int& i2)          const;
    void     orthoPlane(int& i1, int& i2, int& i3) const;

    // Public data members
    //    
    Vector3d normal;
    double   d;

}; // class Plane



inline Plane::Plane(Point3d p, Vector3d norm)
  : normal(norm)
{
    normal = normal.normalize();
    d = -p % normal;
}


inline bool Plane::isEqual(Plane pla) const 
{ 
    return normal.isEqual(pla.normal) && fabs(d-pla.d) <= epsAbs(); 
}


AMODELER_NAMESPACE_END
#endif
