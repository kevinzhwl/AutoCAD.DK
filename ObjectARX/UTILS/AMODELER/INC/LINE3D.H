#ifndef AMODELER_INC_LINE3D_H
#define AMODELER_INC_LINE3D_H


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
// Declaration of class Line3d keeping a definition of an oriented line and/or 
// an axis. The Line3d class keeps a Point3d and a Vector3d. For the Line3d 
// object to be valid, the vector must not be null.
//
// The parameters of the Line3d class are accessed via public data members
// 'point' and 'vector'.
//
///////////////////////////////////////////////////////////////////////////////

#include "point3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Line3d
{
public:
    Line3d()                                     : point (Point3d::kNull), 
                                                   vector(Vector3d::kNull)  {}
    Line3d(const Point3d&  p, const Vector3d& v) : point( p), vector(v)     {}
    Line3d(const Point3d& p1, const Point3d& p2) : point(p1), vector(p2-p1) {}

    double  dist   (const Point3d&) const;
    Point3d project(const Point3d&) const;

    void operator *=(const Transf3d&);

    bool isValid() const                          { return !vector.isNull(); }

    // Public data members
    //
    Point3d  point;
    Vector3d vector;

    static const Line3d kNull;
    static const Line3d kXAxis;
    static const Line3d kYAxis;
    static const Line3d kZAxis;

};  // class Line3d


AMODELER_NAMESPACE_END
#endif

