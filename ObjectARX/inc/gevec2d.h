//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// This file contains the class AcGeVector2d - a mathematical entity
// used to represent a direction and magnitude in 2-space, or
// alternatively to represent a linear translation in 2-space.

#ifndef AC_GEVEC2D_H
#define AC_GEVEC2D_H

#include "adesk.h"
#include "gegbl.h"
#include "gegblabb.h"
#pragma pack (push, 8)

class AcGeMatrix2d;

class 
GE_DLLEXPIMPORT
AcGeVector2d
{
public:
    AcGeVector2d();
    AcGeVector2d(const AcGeVector2d& vec);
    AcGeVector2d(double x, double y);

    // The additive identity, x-axis, and y-axis.
    //
    static const   AcGeVector2d kIdentity;
    static const   AcGeVector2d kXAxis;
    static const   AcGeVector2d kYAxis;

    // Matrix multiplication.
    //
    friend
GE_DLLEXPIMPORT
    AcGeVector2d   operator *  (const AcGeMatrix2d& mat, const AcGeVector2d& vec);
    AcGeVector2d&  setToProduct(const AcGeMatrix2d& mat, const AcGeVector2d& vec);
    AcGeVector2d&  transformBy (const AcGeMatrix2d& leftSide);
    AcGeVector2d&  rotateBy    (double angle);
    AcGeVector2d&  mirror      (const AcGeVector2d& line );


    // Scale multiplication.
    //
    AcGeVector2d   operator *  (double scl) const;
    friend
GE_DLLEXPIMPORT
    AcGeVector2d   operator *  (double scl, const AcGeVector2d& vec);
    AcGeVector2d&  operator *= (double scl);
    AcGeVector2d&  setToProduct(const AcGeVector2d& vec, double scl);
    AcGeVector2d   operator /  (double scl) const;
    AcGeVector2d&  operator /= (double scl);

    // Addition and subtraction of vectors.
    //
    AcGeVector2d   operator +  (const AcGeVector2d& vec) const;
    AcGeVector2d&  operator += (const AcGeVector2d& vec);
    AcGeVector2d   operator -  (const AcGeVector2d& vec) const;
    AcGeVector2d&  operator -= (const AcGeVector2d& vec);
    AcGeVector2d&  setToSum    (const AcGeVector2d& vec1, const AcGeVector2d& vec2);
    AcGeVector2d   operator -  () const;
    AcGeVector2d&  negate      ();

    // Perpendicular vector
    //
    AcGeVector2d   perpVector  () const;

    // Angle argument.
    //
    double         angle       () const;
    double         angleTo     (const AcGeVector2d& vec) const;

    // Vector length operations.
    //
    AcGeVector2d   normal      (const AcGeTol& tol = AcGeContext::gTol) const;
    AcGeVector2d&  normalize   (const AcGeTol& tol = AcGeContext::gTol);
    AcGeVector2d&  normalize   (const AcGeTol& tol, AcGeError& flag);
        // Possible errors:  k0This.  Returns object unchanged on error. 
    double         length      () const;
    double         lengthSqrd  () const;
    Adesk::Boolean isUnitLength(const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isZeroLength(const AcGeTol& tol = AcGeContext::gTol) const;

    // Direction tests.
    //
    Adesk::Boolean isParallelTo(const AcGeVector2d& vec,
                                const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isParallelTo(const AcGeVector2d& vec,
                                const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors:  k0This, k0Arg1. 
        // Returns kFalse on error.
    Adesk::Boolean isCodirectionalTo(const AcGeVector2d& vec,
                                const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isCodirectionalTo(const AcGeVector2d& vec,
                        const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors:  k0This, k0Arg1. 
        // Returns kFalse on error.
    Adesk::Boolean isPerpendicularTo(const AcGeVector2d& vec,
                                     const AcGeTol& tol = AcGeContext::gTol) const;
    Adesk::Boolean isPerpendicularTo(const AcGeVector2d& vec,
                        const AcGeTol& tol, AcGeError& flag) const;
        // Possible errors:  k0This, k0Arg1. 
        // Returns kFalse on error.

    // Dot product.
    //
    double         dotProduct  (const AcGeVector2d& vec) const;

    // Tests for equivalence using the Euclidean norm.
    //
    bool operator == (const AcGeVector2d& vec) const;
    bool operator != (const AcGeVector2d& vec) const;
    bool isEqualTo   (const AcGeVector2d& vec,
                      const AcGeTol& tol = AcGeContext::gTol) const;

    // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int i) ;
    AcGeVector2d&  set         (double x, double y);

    // Convert to/from matrix form.
    //
    operator       AcGeMatrix2d() const;

    // Co-ordinates.
    //
    double         x, y;
};

// Creates the identity translation vector.
//
ADESK_FORCE_INLINE
AcGeVector2d::AcGeVector2d() : x(0.0), y(0.0)
{
}

ADESK_FORCE_INLINE
AcGeVector2d::AcGeVector2d(const AcGeVector2d& src) : x(src.x), y(src.y)
{
}

// Creates a vector intialized to ( xx, yy ).
//
ADESK_FORCE_INLINE
AcGeVector2d::AcGeVector2d(double xx, double yy) : x(xx), y(yy)
{
}

ADESK_FORCE_INLINE bool
AcGeVector2d::operator == (const AcGeVector2d& v) const
{
    return this->isEqualTo(v);
}

// This operator is the logical negation of the `==' operator.
//
ADESK_FORCE_INLINE bool
AcGeVector2d::operator != (const AcGeVector2d& v) const
{
    return !this->isEqualTo(v);
}

// This operator returns a vector that is the scalar product of
// `s' and this vector.
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::operator * (double s) const
{
    return AcGeVector2d (x * s, y * s);
}

// This is equivalent to the statement `v = v * s'.
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::operator *= (double s)
{
    x *= s;
    y *= s;
    return *this;
}

ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::setToProduct(const AcGeVector2d& v, double s)
{
    x = s * v.x;
    y = s * v.y;
    return *this;
}

// Returns a vector such that each of the coordinates of this vector
// have been divided by val.
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::operator / (double val) const
{
    return AcGeVector2d (x/val, y/val);
}

// This is equivalent to the statement `v = v / val;'
// Each coordinate of this vector is divided by val.
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::operator /= (double val)
{
    x /= val;
    y /= val;
    return *this;
}

// Returns a vector that is formed from adding the components of
// this vector with `v'.
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::operator + (const AcGeVector2d& v) const
{
    return AcGeVector2d (x + v.x, y + v.y);
}

// This is equivalent to the statement `thisVec = thisVec + v;'
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::operator += (const AcGeVector2d& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

// Using this operator is equivalent to using `thisVec + (-v);'
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::operator - (const AcGeVector2d& v) const
{
    return AcGeVector2d (x - v.x, y - v.y);
}

// This is equivalent to the statement `thisVec = thisVec - v;'
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::operator -= (const AcGeVector2d& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::setToSum(const AcGeVector2d& v1, const AcGeVector2d& v2)
{
    x = v1.x + v2.x;
    y = v1.y + v2.y;
    return *this;
}

// Returns a vector that is formed by negating each of the components
// of this vector.
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::operator - () const
{
    return AcGeVector2d (-x, -y);
}

// `v.negate()' is equivalent to the statement `v = -v;'
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::negate()
{
    x = -x;
    y = -y;
    return *this;
}

// Returns a vector orthogonal to this vector.
//
ADESK_FORCE_INLINE AcGeVector2d
AcGeVector2d::perpVector() const
{
    return AcGeVector2d (-y, x);
}

// Returns the square of the Euclidean length of this vector.
//
ADESK_FORCE_INLINE double
AcGeVector2d::lengthSqrd() const
{
    return x*x + y*y;
}

// Returns the dot product of this vector and `v'.
//
ADESK_FORCE_INLINE double
AcGeVector2d::dotProduct(const AcGeVector2d& v) const
{
    return x * v.x + y * v.y;
}

// Sets the vector to ( xx, yy ).
//
ADESK_FORCE_INLINE AcGeVector2d&
AcGeVector2d::set(double xx, double yy)
{
    x = xx;
    y = yy;
    return *this;
}

// Indexes the vector as if it were an array.  `x' is index `0',
// `y' is index `1'.
//
ADESK_FORCE_INLINE double
AcGeVector2d::operator [] (unsigned int i) const
{
    return *(&x+i);
}

ADESK_FORCE_INLINE double&
AcGeVector2d::operator [] (unsigned int i)
{
    return *(&x+i);
}

#define ADSK_ACGEVECTOR2D_DEFINED
#include "acarrayhelper.h"

#pragma pack (pop)
#endif
