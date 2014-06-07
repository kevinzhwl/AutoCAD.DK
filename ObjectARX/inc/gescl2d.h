#ifndef AC_GESCL2D_H
#define AC_GESCL2D_H
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
// This file contains the class AcGeScale2d - a mathematical entity used
// to represent scaling transformations in 2-space.
// Contract:  The scale vector components must never be set to zero
// (or near zero within floating point tolerances).

#include "adesk.h"
#include "gegbl.h"
#pragma pack (push, 8)

class AcGeMatrix2d;
class AcGeScale3d;

class 
GE_DLLEXPIMPORT
AcGeScale2d
{
public:
    AcGeScale2d();
    AcGeScale2d(const AcGeScale2d& src);
    AcGeScale2d(double factor);
    AcGeScale2d(double xFactor, double yFactor);

    // The identity scaling operation.
    //
    static const   AcGeScale2d kIdentity;

    // Multiplication.
    //
    AcGeScale2d    operator *  (const AcGeScale2d& sclVec) const;
    AcGeScale2d&   operator *= (const AcGeScale2d& scl);
    AcGeScale2d&   preMultBy   (const AcGeScale2d& leftSide);
    AcGeScale2d&   postMultBy  (const AcGeScale2d& rightSide);
    AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec1, const AcGeScale2d& sclVec2);
    AcGeScale2d    operator *  (double s) const;
    AcGeScale2d&   operator *= (double s);
    AcGeScale2d&   setToProduct(const AcGeScale2d& sclVec, double s);
    friend
GE_DLLEXPIMPORT
    AcGeScale2d    operator *  (double, const AcGeScale2d& scl);

    // Multiplicative inverse.
    //
    AcGeScale2d    inverse        () const;
    AcGeScale2d&   invert         ();

    Adesk::Boolean isProportional(const AcGeTol& tol = AcGeContext::gTol) const;

    // Tests for equivalence using the infinity norm.
    //
    Adesk::Boolean operator == (const AcGeScale2d& sclVec) const;
    Adesk::Boolean operator != (const AcGeScale2d& sclVec) const;
    Adesk::Boolean isEqualTo   (const AcGeScale2d& scaleVec,
                                const AcGeTol& tol = AcGeContext::gTol) const;

     // For convenient access to the data.
    //
    double         operator [] (unsigned int i) const;
    double&        operator [] (unsigned int i);
    AcGeScale2d&   set         (double sc0, double sc1);

    // Conversion to/from matrix form.
    //
    operator       AcGeMatrix2d   () const;
    void           getMatrix      (AcGeMatrix2d& mat) const;
    AcGeScale2d&   extractScale   ( const AcGeMatrix2d& mat );
    AcGeScale2d&   removeScale    ( AcGeMatrix2d& mat );

    // Cast up to 3d scale.
    //
    operator       AcGeScale3d    () const;

    // The scale components in x and y.
    //
    double         sx, sy;
};

inline double
AcGeScale2d::operator [] (unsigned int i) const
{
    return *(&sx+i);
}

inline double&
AcGeScale2d::operator [] (unsigned int i)
{
    return *(&sx+i);
}

#pragma pack (pop)
#endif
