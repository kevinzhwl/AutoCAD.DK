#ifndef AC_BRBREP_H
#define AC_BRBREP_H 1
// (C) Copyright 1995-1997 by Autodesk, Inc.
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
// The AcBrBrep class is the interface class for the brep portion
// of an AutoCAD database entity. All the functionality supported
// by this class is implemented by the class AcBrImpBrep.
//
// This class defines the functions that are pertinent to the highest
// level of a brep, and serves as a mapping between an AutoCAD (solid,
// region or body) entity and AcBr. It is also used to set the brep
// owner of an AcBrBrepFaceTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrBrep, call setSubentPath() using the object ID for the AutoCAD
// (solid, region or body) entity along with kNullSubentId.
//
// The getPointRelationToBrep() and getCurveRelationToBrep() functions
// return the relation of an external point or curve to the brep, and are
// deprecated in favour of the new classifyPoint() and classifyLine().


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGePoint3d;
class AcGeCurve3d;


class AcBrBrep : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrep);
    AcBrBrep();
    AcBrBrep(const AcBrBrep&);
    ~AcBrBrep();

    // Assignment operator
    AcBrBrep&           operator =      (const AcBrBrep&);

    // Relation of external geometry to internal topology
    AcBr::ErrorStatus   getPointRelationToBrep(const AcGePoint3d&,
                                               AcBr::Relation&) const;
    AcBr::ErrorStatus   getCurveRelationToBrep(const AcGeCurve3d&,
                                               AcBr::Relation&) const;
};


#endif

