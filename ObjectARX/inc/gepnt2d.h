#ifndef AC_GEPNT2D_H
#define AC_GEPNT2D_H
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
// DESCRIPTION:
//
// This file contains the class AcGePoint2d - A mathematical entity
// used to represent a location in 2-space (implicitly) using
// homogeneous co-ordinates.

#include "gevec2d.h"
#pragma pack (push, 8)

class AcGeMatrix2d;
class AcGeVector2d;
class AcGeLinearEnt2d;
class AcGeLine2d;

class
#ifdef AC_GEPNT2D_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGePoint2d
{
public:
    AcGePoint2d();
    AcGePoint2d(const AcGePoint2d& pnt);
    AcGePoint2d(double x, double y);

    // The origin, or (0, 0).
    //
    static const   AcGePoint2d kOrigin;

    // Matrix multiplication.
    //
    friend
#ifdef AC_GEPNT2D_CPP
    GE_DLLEXPORT
#else
    GE_DLLIMPORT
#endif
    AcGePoint2d    operator *  (const AcGeMatrix2d& mat, const AcGePoint2d& pnt);
    AcGePoint2d&   setToProduct(const AcGeMatrix2d& mat, const AcGePoint2d& pnt);
    AcGePoint2d&   transformBy (const AcGeMatrix2d& leftSide);
    AcGePoint2d&   rotateBy    (double angle, const AcGePoint2d& wrtPoint
                                = AcGePoint2d::kOrigin);
    AcGePoint2d&   mirror      (const AcGeLine2d& line);
    AcGePoint2d&   scaleBy     (double scaleFactor, const AcGePoint2d& wrtPoint
                                = AcGePoint2d::kOrigin);

    // Scale multiplication.
    //
    AcGePoint2d    operator *  (double) const;
    friend
    AcGePoint2d    operator *  (double, const AcGePoint2d& scl);
    AcGePoint2d&   operator *= (double scl);
    AcGePoint2d    operator /  (double scl) const;
    AcGePoint2d&   operator /= (double scl);

    // Translation by a vector.
    //
    AcGePoint2d    operator +  (const AcGeVector2d& vec) const;
    AcGePoint2d&   operator += (const AcGeVector2d& vec);
    AcGePoint2d    operator -  (const AcGeVector2d& vec) const;
    AcGePoint2d&   operator -= (const AcGeVector2d& vec);
    AcGePoint2d&   setToSum    (const AcGePoint2d& pnt, const AcGeVector2d& vec);

    // Get vector between two points.
    //
    AcGeVector2d   operator -  (const AcGePoint2d& pnt) const;
    AcGeVector2d   asVector    () const;

    // Distance to other geometric objects.
    //
    double         distanceTo  (const AcGePoint2d& pnt) const;

    // Tests for equivalence using the Euclidean norm.
    //
    Adesk::Boolean operator == (const AcGePoint2d& pnt) const;
    Adesk::Boolean operator != (const AcGePoint2d& pnt) const;
    Adesk::Boolean isEqualTo   (const AcGePoint2d& pnt,
                                const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int idx);
    AcGePoint2d&   set         (double x, double y);

    // The co-ordinates of the point.
    //
    double         x, y;
};

// Creates a point at the origin.
//
inline
AcGePoint2d::AcGePoint2d() : x(0.0), y(0.0)
{
}

inline
AcGePoint2d::AcGePoint2d(const AcGePoint2d& src) : x(src.x), y(src.y)
{
}

// Creates a point intialized to ( xx, yy ).
//
inline
AcGePoint2d::AcGePoint2d(double xx, double yy) : x(xx), y(yy)
{
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
//
inline AcGePoint2d
AcGePoint2d::operator * (double val) const
{
    return AcGePoint2d(x*val, y*val);
}

// Returns a point such that each of the coordinates of this point
// have been multiplied by val.
//
inline AcGePoint2d
operator * (double val, const AcGePoint2d& p)
{
    return AcGePoint2d(p.x*val, p.y*val);
}

// This is equivalent to the statement `p = p * val;'
// Each coordinate of this point is multiplied by val.
//
inline AcGePoint2d&
AcGePoint2d::operator *= (double val)
{
    x *= val;
    y *= val;
    return *this;
}

// Returns a point such that each of the coordinates of this point
// have been divided by val.
//
inline AcGePoint2d
AcGePoint2d::operator / (double val) const
{
    return AcGePoint2d (x/val, y/val);
}

// This is equivalent to the statement `p = p / val;'
// Each coordinate of this point is divided by val.
//
inline AcGePoint2d&
AcGePoint2d::operator /= (double val)
{
    x /= val;
    y /= val;
    return *this;
}

// Returns a point that is equivalent to the result of translating
// this point by the vector `v'.  (It yields the same result as if
// the vector had been cast to a translation matrix and then
// multiplied with the point.)
//
inline AcGePoint2d
AcGePoint2d::operator + (const AcGeVector2d& v) const
{
    return AcGePoint2d(x + v.x, y + v.y);
}

// This is equivalent to the statement `p = p + v;'
//
inline AcGePoint2d&
AcGePoint2d::operator += (const AcGeVector2d& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

// This is equivalent to the statement `p + (-v);'
//
inline AcGePoint2d
AcGePoint2d::operator - (const AcGeVector2d& v) const
{
    return AcGePoint2d(x - v.x, y - v.y);
}

// This is equivalent to the statement `p = p - v;'
//
inline AcGePoint2d&
AcGePoint2d::operator -= (const AcGeVector2d& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

// This operator returns a vector such that if `v = p1 - p0',
// then, `v' is equivalent to the translation that takes
// `p0' to `p1'.  (This point is `p1').
//
inline AcGeVector2d
AcGePoint2d::operator - (const AcGePoint2d& p) const
{
    return AcGeVector2d(x - p.x, y - p.y);
}

// This operator returns the vector that would have resulted
// from the operation `p1 - AcGePoint2d::kOrigin', which is
// a common operation to perform.
//
inline AcGeVector2d
AcGePoint2d::asVector() const
{
    return AcGeVector2d(x, y);
}

// Sets the point to ( xx, yy ).
//
inline AcGePoint2d&
AcGePoint2d::set(double xx, double yy)
{
    x = xx;
    y = yy;
    return *this;
}

//     Indexes the point as if it were an array.  `x' is index `0',
//     `y' is index `1'.
//
inline double
AcGePoint2d::operator [] (unsigned int i) const
{
    return *(&x+i);
}

inline double&
AcGePoint2d::operator [] (unsigned int i)
{
    return *(&x+i);
}

#pragma pack (pop)
#endif
