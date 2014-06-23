#ifndef AC_BRFACE_H
#define AC_BRFACE_H 1
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
// The AcBrFace class is the interface class for brep faces. All the
// functionality supported by this class is implemented by the class
// AcBrImpFace.
//
// This class defines the functions that are pertinent to the face
// level of a brep, and thus serves as a mapping between AutoCAD
// face subentities and AcBr. It is also used to set the first
// face of a global AcBrBrepFaceTraverser or the face owner of
// an AcBrFaceLoopTraverser.
//
// Faces are primary brep elements and thus have associated geometry
// (i.e., surfaces). This class provides an indirect link between AcGe
// and AcDb3dSolid, AcDbRegion and AcDbBody.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrFace, call setSubentPath() using the object ID for the AutoCAD
// (solid, region or body) entity along with a face subentity.
//
// The getSurfaceType() function is used to determine the best match
// between the face's underlying surface and the surface types supported
// in AcGe. This is the same as the type returned by the convertor
// function AcGeExternalSurface::isNativeSurface() invoked on the surface
// returned by AcBrFace::getSurface(), and thus serves as a short cut
// for filtering surfaces by type. If the surface type is not supported
// as a native type in AcGe, kExternalBoundedSurface is returned. If the
// object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. If the surface geometry is missing, eMissingGeometry
// is returned. In the event of an error, the surface type reference
// parameter's value is unchanged and is thus meaningless.
//
// The getSurface() function returns the face's underlying surface as an
// AcGe external bounded surface (cast to the AcGeSurface base class), with
// the entire chain of transforms from the object ID array applied. The
// surface is passed as a null AcGeSurface base class reference pointer
// for getSurface() to instantiate. If the object is uninitialised or
// invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the object's subentity path was last set,
// eBrepChanged is returned and the object is invalidated. If the surface
// geometry is missing, eMissingGeometry is returned. If the AcGe surface
// comes back null, eOutOfMemory is returned. If any of the associated
// AutoCAD database objects from the chained transforms cannot be opened,
// eWrongObjectType is returned. In the event of an error, the surface
// reference pointer is unchanged and thus likely points to a null object.
//
// The getOrientToSurface() function returns a simple Boolean indicating
// whether the outside of the face is in the direction of the surface normal
// (kTrue) or in the opposite direction (kFalse), at any position. If the
// object is uninitialised or invalidated (i.e., empty), eInvalidObject is
// returned. If the owning AutoCAD entity changed since the object's subentity
// path was last set, eBrepChanged is returned and the object is invalidated.
// If the surface geometry is missing, eMissingGeometry is returned. In
// the event of an error, the orientation reference parameter's value is
// unchanged and is thus meaningless.
//
// The getPointRelationToFace() and getCurveRelationToFace() functions
// return the relation of an external point or curve to the face, and are
// deprecated in favour of the new classifyPoint() and classifyLine().


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcGeSurface;
class AcGeCurve3d;
class AcGePoint3d;


class AcBrFace : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrFace);
    AcBrFace();
    AcBrFace(const AcBrFace&);
    ~AcBrFace();

    // Assignment operator
    AcBrFace&           operator =      (const AcBrFace&);

    // Geometry
    AcBr::ErrorStatus   getSurfaceType  (AcGe::EntityId&) const;
    AcBr::ErrorStatus   getSurface      (AcGeSurface*&) const;
    AcBr::ErrorStatus   getOrientToSurface(Adesk::Boolean&) const;

    // Relation of external geometry to internal topology
    AcBr::ErrorStatus   getPointRelationToFace(const AcGePoint3d&,
                                               AcBr::Relation&) const;
    AcBr::ErrorStatus   getCurveRelationToFace(const AcGeCurve3d&,
                                               AcBr::Relation&) const;
};


#endif

