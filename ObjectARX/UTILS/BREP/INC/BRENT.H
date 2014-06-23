#ifndef AC_BRENT_H
#define AC_BRENT_H 1
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
// The AcBrEntity class is the interface base class for topology
// objects. All the functionality supported by this class is
// implemented by the class AcBrImpEntity.
//
// This class defines the functions that are common to all topology
// objects, and cannot be instantiated as it has no meaning on 
// its own. It is derived from AcRxObject in order to provide full
// service run-time type-checking for all derived topology classes.
//
// The AcRxObject inherited isEqualTo() function is redefined to check
// object equality between two topology objects. If either object is
// invalid or is not a topology object, the function returns kFalse;
// kTrue is returned when the object is valid and has been equated to
// another valid topology object of the same subclass. Equivalence is
// defined as having the same subentity path.
//
// The isNull() function tests whether the object has been set to
// anything meaningful. kTrue is returned if the object is uninitialised
// or invalidated (i.e., empty).
//
// The setSubentPath() function is used to (re)set the object to a
// specific subentity path in AutoCAD. This initialises an object
// instantiated with the default constructor, and resets the criteria
// for the eBrepChanged error. If the subentity path is null, or the
// object ID array is empty or contains a null final entry, eNullObjectId
// is returned. If the subentity ID is null, eNullSubentityId is returned
// (exception: AcBrBrep, for which this is the only legitimate value).
// If the subentity is the wrong type for the given subclass,
// eWrongSubentityType is returned. If the AutoCAD entity is not an
// AcDb3dSolid, AcDbRegion or AcDbBody, or the associated database
// object cannot be opened, eWrongObjectType is returned. If the
// subentity ID fails to map to a valid subentity pointer,
// eMissingTopology is returned.
//
// The getSubentPath() function returns the full subentity path in
// AutoCAD for the current object. If the object is uninitialised or
// invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the object's subentity path was last
// set, eBrepChanged is returned and the object is invalidated.
//
// The getBoundBlock() function returns the model space bounding
// box for the current topology object. The box is returned as
// an AcGeBoundBlock3d, with the entire chain of transforms from
// the object ID array applied. The box is instantiated by the caller
// and passed by reference for getBoundBlock() to (re)set. If the
// object is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the object's
// subentity path was last set, eBrepChanged is returned and the object
// is invalidated. If the bounding box is missing, empty or infinite/
// unbounded, eMissingGeometry is returned. If the full subentity path
// contains any null objects, eNullObjectId is returned. If any of the
// associated AutoCAD database objects from the chained transforms
// cannot be opened, eWrongObjectType is returned. In the event of an
// error, the bounding block reference parameter's value is unchanged.
//
// The getPointContainment() function determines whether a point lies
// inside or outside the current object's topological boundary. If it lies
// outside, AcGe::kOutside is returned along with a null container object.
// If inside, AcGe::kInside is returned along with a copy of the current
// object. If the point lies on the topological boundary of the current
// object, AcGe::kOnBoundary is returned along with the lowest-level
// topology object which corresponds to a containment of the point (e.g.,
// if the point lies along an edge boundary of a face, the edge is returned).
// In order for the point and the current topology object to be in the same
// evaluation space, the entire inverted chain of transforms from the object
// ID array is applied to the point before testing for point containment.
// The container object is passed as a null AcBrEntity base class reference
// pointer for getPointContainment() to instantiate. If the object is
// uninitialised or invalidated (i.e., empty), eInvalidObject is returned.
// If the owning AutoCAD entity changed since the object's subentity path
// was last set, eBrepChanged is returned and the object is invalidated.
// If the containment cannot be determined, eAmbiguousOutput is returned.
// If the container entity comes back null, eOutOfMemory is returned. In
// the event of an error, the containment reference parameter's value is
// unchanged and is thus meaningless, and the container object reference
// pointer is unchanged and thus likely points to a null object.
//
// The getLineContainment() function determines whether a line lies inside
// or outside the current object's topological boundary. If it lies entirely
// outside, a null hit array is returned (with numHitsFound=0). Similarly,
// the start or end point of a line segment and the end point of a ray are
// part of the hit array only when they are contained by the object being
// tested. The hit array thus defines a segmentation of the subset of the
// line which is contained. The line may be either a line segment, a ray
// or an infinite line, cast to AcGeLinearEnt3d. In order for the line and
// the current topology object to be in the same evaluation space, the entire
// inverted chain of transforms from the object ID array is applied to the
// line before testing for line containment. Specify numHitsWanted=0 to find
// all hits; specify numHitsWanted=1 to find just the first hit. The hit
// array is passed as a null reference pointer for getLineContainment() to
// instantiate. If the object is uninitialised or invalidated (i.e., empty),
// eInvalidObject is returned. If the owning AutoCAD entity changed since
// the object's subentity path was last set, eBrepChanged is returned and
// the object is invalidated. If the containment cannot be determined,
// eAmbiguousOutput is returned. If the hit array allocation comes back
// null, eOutOfMemory is returned. In the event of an error, the hit array
// reference pointer is unchanged and thus likely points to a null object,
// and the number of hits found is returned as zero.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"


// forward class declarations
class AcDbFullSubentPath;
class AcGeBoundBlock3d;
class AcGePoint3d;
class AcGeLinearEnt3d;
class AcBrHit;
class AcBrImpEntity;


class AcBrEntity : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEntity);
    virtual ~AcBrEntity();
    
    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
    
    // Queries & Initialisers
    Adesk::Boolean      isNull          () const;
    AcBr::ErrorStatus   setSubentPath   (AcDbFullSubentPath&);
    AcBr::ErrorStatus   getSubentPath   (AcDbFullSubentPath&) const;

    // Geometric bounds (i.e., model space bounding box)
    AcBr::ErrorStatus   getBoundBlock   (AcGeBoundBlock3d&) const;

	// Topological Containment
    AcBr::ErrorStatus   getPointContainment(const AcGePoint3d&,
		                                    AcGe::PointContainment&,                                    
		                                    AcBrEntity*& container) const;
    AcBr::ErrorStatus   getLineContainment(const AcGeLinearEnt3d&,
                                           const Adesk::UInt32& numHitsWanted,
                                           Adesk::UInt32&       numHitsFound,
                                           AcBrHit*&            hits) const;

protected:
    AcBrEntity();
    AcBrEntity(const AcBrEntity&);
    AcBrEntity&         operator =      (const AcBrEntity&);

    AcBrImpEntity*      mpImp;
};


#endif

