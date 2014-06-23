#ifndef AC_BRVTX_H
#define AC_BRVTX_H 1
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
// The AcBrVertex class is the interface class for brep vertices.
// All the functionality supported by this class is implemented by
// the class AcBrImpVertex.
//
// This class defines the functions that are pertinent to the vertex
// level of a brep, and thus serves as a mapping between AutoCAD
// vertex subentities and AcBr.
//
// Vertices are primary brep elements and thus have associated geometry
// (i.e., points). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrVertex, call setSubentPath() using the object ID for the AutoCAD
// (solid, region or body) entity along with a vertex subentity.
//
// The getPoint() function returns the vertex' underlying point as an
// AcGe 3d point, with the entire chain of transforms from the object
// ID array applied. The point is passed as a null AcGePoint3d reference
// pointer for getPoint() to instantiate. If the object is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the object's subentity path was last set,
// eBrepChanged is returned and the object is invalidated. If the point
// geometry is missing, eMissingGeometry is returned. If the AcGe point
// comes back null, eOutOfMemory is returned. If any of the associated
// AutoCAD database objects from the chained transforms cannot be opened,
// eWrongObjectType is returned. In the event of an error, the point
// reference pointer is unchanged and thus likely points to a null object.
//
// The getPointRelationToVertex() and getCurveRelationToVertex() functions
// return the relation of an external point or curve to the vertex, and
// are deprecated in favour of the new classifyPoint() and classifyLine().


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGePoint3d;
class AcGeCurve3d;


class AcBrVertex : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrVertex);
    AcBrVertex();
    AcBrVertex(const AcBrVertex&);
    ~AcBrVertex();

    // Assignment operator
    AcBrVertex&         operator =      (const AcBrVertex&);

    // Geometry
    AcBr::ErrorStatus   getPoint        (AcGePoint3d*&) const;

    // Relation of external geometry to internal topology
    AcBr::ErrorStatus   getPointRelationToVertex(const AcGePoint3d&,
                                                 AcBr::Relation&) const;
    AcBr::ErrorStatus   getCurveRelationToVertex(const AcGeCurve3d&,
                                                 AcBr::Relation&) const;
};


#endif

