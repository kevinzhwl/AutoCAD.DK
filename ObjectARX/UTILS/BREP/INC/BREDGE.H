#ifndef AC_BREDGE_H
#define AC_BREDGE_H 1
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
// The AcBrEdge class is the interface class for brep edges. All the
// functionality supported by this class is implemented by the class
// AcBrImpEdge.
//
// This class defines the functions that are pertinent to the edge
// level of a brep, and thus serves as a mapping between AutoCAD
// edge subentities and AcBr. It is also used to set the first
// edge of an AcBrLoopEdgeTraverser or the edge owner of an
// AcBrEdgeLoopTraverser.
//
// Edges are primary brep elements and thus have associated geometry
// (i.e., curves). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrEdge, call setSubentPath() using the object ID for the AutoCAD
// (solid, region or body) entity along with an edge subentity.
//
// The getCurveType() function is used to determine the best match
// between the edge's underlying curve and the curve types supported
// in AcGe. This is the same as the type returned by the convertor
// function AcGeExternalCurve3d::isNativeCurve() invoked on the curve
// returned by AcBrEdge::getCurve(), and thus serves as a short cut
// for filtering curves by type. If the curve type is not supported
// as a native type in AcGe, kExternalCurve3d is returned. If the
// object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. If the curve geometry is missing, eMissingGeometry
// is returned. In the event of an error, the curve type reference
// parameter's value is unchanged and is thus meaningless.
//
// The getCurve() function returns the edge's underlying curve as an
// AcGe external 3d curve (cast to the AcGeCurve3d base class), with
// the entire chain of transforms from the object ID array applied. The
// curve is passed as a null AcGeCurve3d base class reference pointer for
// getCurve() to instantiate. If the object is uninitialised or invalidated
// (i.e., empty), eInvalidObject is returned. If the owning AutoCAD entity
// changed since the object's subentity path was last set, eBrepChanged is
// returned and the object is invalidated. If the curve geometry is missing,
// eMissingGeometry is returned. If the AcGe curve comes back null,
// eOutOfMemory is returned. If any of the associated AutoCAD database
// objects from the chained transforms cannot be opened, eWrongObjectType
// is returned. In the event of an error, the curve reference pointer
// is unchanged and thus likely points to a null object.
//
// The getOrientToCurve() function returns a simple Boolean indicating
// whether the natural orientation of the edge from vertex1 to vertex2
// is in the direction of the curve parameterisation (kTrue) or in the
// opposite direction (kFalse). The orientation may be directly applied
// to the underlying curve using AcGeCurve3d::reverseParam(). If the
// object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. If the curve geometry is missing, eMissingGeometry
// is returned. In the event of an error, the orientation reference
// parameter's value is unchanged and is thus meaningless.
//
// The getVertex1() function returns the start vertex of the edge in its
// natural orientation from vertex1 to vertex2. The vertex is instantiated
// by the caller and passed by reference for getVertex1() to (re)set. If
// the object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. Null vertices represent specialised rather than missing
// topology, so return eUnsuitableTopology. If the vertex fails to map to
// a valid subentity ID, eMissingSubentity is returned. In the event of
// an error, the vertex reference object is unchanged and is thus likely
// to be uninitialised (i.e., empty).
//
// The getVertex2() function returns the end vertex of the edge in its
// natural orientation from vertex1 to vertex2. The vertex is instantiated
// by the caller and passed by reference for getVertex2() to (re)set. If
// the object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. Null vertices represent specialised rather than missing
// topology, so return eUnsuitableTopology. If the vertex fails to map to
// a valid subentity ID, eMissingSubentity is returned. In the event of
// an error, the vertex reference object is unchanged and is thus likely
// to be uninitialised (i.e., empty).
//
// The getPointRelationToEdge() and getCurveRelationToEdge() functions
// return the relation of an external point or curve to the edge, and are
// deprecated in favour of the new classifyPoint() and classifyLine().


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGePoint3d;
class AcGeCurve3d;
class AcBrVertex;


class AcBrEdge : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEdge);
    AcBrEdge();
    AcBrEdge(const AcBrEdge&);
    ~AcBrEdge();

    // Assignment operator
    AcBrEdge&           operator =      (const AcBrEdge&);

    // Geometry
    AcBr::ErrorStatus   getCurveType    (AcGe::EntityId&) const;
    AcBr::ErrorStatus   getCurve        (AcGeCurve3d*&) const;
    AcBr::ErrorStatus   getOrientToCurve(Adesk::Boolean&) const;

    // Downward links
    // Vertex usage by edge (2::1, 1::1 or 0::1)
    AcBr::ErrorStatus   getVertex1      (AcBrVertex&) const;
    AcBr::ErrorStatus   getVertex2      (AcBrVertex&) const;

    // Relation of external geometry to internal topology
    AcBr::ErrorStatus   getPointRelationToEdge(const AcGePoint3d&,
                                               AcBr::Relation&) const;
    AcBr::ErrorStatus   getCurveRelationToEdge(const AcGeCurve3d&,
                                               AcBr::Relation&) const;
};


#endif

