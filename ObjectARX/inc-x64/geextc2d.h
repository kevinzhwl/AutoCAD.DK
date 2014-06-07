#ifndef AC_GEEXTC2D_H
#define AC_GEEXTC2D_H
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
// This file contains the class AcGeExternalCurve2d - A
// representation for a curve that has its definition external to
// gelib.

#include "gecurv2d.h"
#include "gearc2d.h"
#include "gevec2d.h"
#include "gepnt2d.h"
#pragma pack (push, 8)

class AcGeNurbCurve2d;
class AcGeExternalCurve2d;
class AcGeExternalCurve2d;

class
GX_DLLEXPIMPORT
AcGeExternalCurve2d : public AcGeCurve2d
{
public:
    AcGeExternalCurve2d();
    AcGeExternalCurve2d(const AcGeExternalCurve2d&);
    AcGeExternalCurve2d(void* curveDef, AcGe::ExternalEntityKind curveKind,
                        Adesk::Boolean makeCopy = Adesk::kTrue);

    Adesk::Boolean isNurbCurve() const;
    Adesk::Boolean isNurbCurve(AcGeNurbCurve2d& nurbCurve) const;
    Adesk::Boolean isDefined  () const;

    void           getExternalCurve(void*& curveDef) const;

    // Type of the external curve.
    //
    AcGe::ExternalEntityKind externalCurveKind() const;

    // Reset surface
    //
    AcGeExternalCurve2d& set(void* curveDef, AcGe::ExternalEntityKind curveKind,
                             Adesk::Boolean makeCopy = Adesk::kTrue);
    // Assignment operator
    //
    AcGeExternalCurve2d& operator = (const AcGeExternalCurve2d& src);

    // Ownership of curve
    //
    Adesk::Boolean       isOwnerOfCurve() const;
    AcGeExternalCurve2d& setToOwnCurve();
};

#pragma pack (pop)
#endif
