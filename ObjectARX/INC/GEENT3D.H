#ifndef AC_GEENT3D_H
#define AC_GEENT3D_H
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
// This file contains the class GeEntity3d - An abstract base class
// for all Geometry Library 3d entities.

#include "gegbl.h"
#include "gepnt3d.h"
#include "geent2d.h"
#include "geintrvl.h"

class
#ifdef AC_GEENT3D_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeEntity3d
{
public:
    ~AcGeEntity3d();

    // Run time type information.
    //
    Adesk::Boolean   isKindOf    (AcGe::EntityId) const;
    AcGe::EntityId   type        () const;

    // Make a copy of the entity.
    //
    AcGeEntity3d*    copy        () const;
    AcGeEntity3d&    operator =  (const AcGeEntity3d&);

    // Equivalence
    //
    Adesk::Boolean   operator == (const AcGeEntity3d&) const;
    Adesk::Boolean   operator != (const AcGeEntity3d&) const;
    Adesk::Boolean   isEqualTo   (const AcGeEntity3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    // Matrix multiplication
    //
    AcGeEntity3d&    transformBy (const AcGeMatrix3d&);
    AcGeEntity3d&    translateBy (const AcGeVector3d&);
    AcGeEntity3d&    rotateBy    (double, const AcGeVector3d&,
                                  const AcGePoint3d& = AcGePoint3d::kOrigin);
    AcGeEntity3d&    mirror      (const AcGePlane&);
    AcGeEntity3d&    scaleBy     (double scaleFactor,
                                  const AcGePoint3d& wrtPoint
                                  = AcGePoint3d::kOrigin);
    // Point containment
    //
    Adesk::Boolean   isOn        (const AcGePoint3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
protected:
    friend class AcGeImpEntity3d;
    AcGeImpEntity3d  *mpImpEnt;
    int              mDelEnt;
    AcGeEntity3d ();
    AcGeEntity3d (const AcGeEntity3d&);
    AcGeEntity3d (AcGeImpEntity3d&, int);
    AcGeEntity3d (AcGeImpEntity3d*);
    AcGeEntity2d* newEntity2d (AcGeImpEntity3d*) const;
    AcGeEntity2d* newEntity2d (AcGeImpEntity3d&, int) const;
    AcGeEntity3d* newEntity3d (AcGeImpEntity3d*) const;
    AcGeEntity3d* newEntity3d (AcGeImpEntity3d&, int) const;
};

inline AcGeEntity2d*
AcGeEntity3d::newEntity2d (AcGeImpEntity3d *impEnt ) const
{
    return new AcGeEntity2d ( impEnt );
}

inline AcGeEntity3d*
AcGeEntity3d::newEntity3d (AcGeImpEntity3d *impEnt ) const
{
    return new AcGeEntity3d ( impEnt );
}

inline AcGeEntity3d*
AcGeEntity3d::newEntity3d(AcGeImpEntity3d& impEnt, int dummy) const
{
    return new AcGeEntity3d(impEnt, dummy);
}

inline AcGeEntity2d*
AcGeEntity3d::newEntity2d(AcGeImpEntity3d& impEnt, int dummy) const
{
    return new AcGeEntity2d(impEnt, dummy);
}

#endif
