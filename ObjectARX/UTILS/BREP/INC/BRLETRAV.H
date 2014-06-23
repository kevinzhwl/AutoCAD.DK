#ifndef AC_BRLETRAV_H
#define AC_BRLETRAV_H 1
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
// The AcBrLoopEdgeTraverser class is the interface class for loop
// edge traversers. It is used to get access to edge-bound data
// that requires the context of a specific face/loop usage, such
// as parameter curves. In order to provide the tightest coupling 
// with radial edge traversals (i.e., AcBrEdgeLoopTraverser), the
// face is represented by its loop boundary at the shared edge.
// All the functionality supported by this class is implemented
// by the class AcBrImpLoopEdgeTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrLoopEdgeTraverser, call setLoop() or setLoopAndEdge() using a
// valid, previously instantiated face-loop or edge-loop traverser.
//
// The setLoopAndEdge() function is used to (re)set the traverser
// to a specific loop edge list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error. If the edge-loop reference
// object is uninitialised or invalidated (i.e., empty), eInvalidInput
// is returned. If the owning AutoCAD entity changed since the edge-
// loop reference object's edge owner was last set, eInvalidInput is
// returned and the edge-loop reference object is invalidated (side
// effect). If the edge-loop reference object's edge owner or current
// loop fails to map to a valid subentity pointer, eMissingTopology
// is returned.
//
// The setLoop() function is used to (re)set the traverser to a
// specific loop edge list, starting at the first edge in the list.
// This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error.
// If the face-loop reference object is uninitialised or invalidated
// (i.e., empty), eInvalidInput is returned. If the owning AutoCAD
// entity changed since the face-loop reference object's face owner
// was last set, eInvalidInput is returned and the face-loop
// reference object is invalidated (side effect). If the face-loop
// reference object's face owner fails to map to a valid subentity
// pointer, eMissingTopology is returned. If the loop represents a
// singularity (such as at the apex of a cone), eUnsuitableTopology
// is returned; use the loop to (re)set an AcBrLoopVertexTraverser
// instead.
//
// The getLoop() function returns the loop owner of the edge list. The
// loop object is instantiated by the caller and passed by reference
// for getLoop() to (re)set. If the traverser is uninitialised or
// invalidated (i.e., empty), eInvalidObject is returned. If the
// owning AutoCAD entity changed since the traverser's loop edge
// list was last set, eBrepChanged is returned and the traverser is
// invalidated. If the loop fails to map to a valid subentity ID,
// eMissingSubentity is returned. In the event of an error, the loop
// reference object is unchanged and is thus likely to be
// uninitialised (i.e., empty).
//
// The setEdge() function is used to (re)set the traverseran to a
// specific starting position in the loop edge list (i.e., change
// the first edge marker from the default to the specified edge).
// This initialises a traverser instantiated with the default
// constructor, and resets the criteria for next() and done(). It
// must be called after setLoop() or setLoopAndEdge(), in order
// to have a valid list to set position. If the traverser is
// uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the
// traverser's loop edge list was last set, eBrepChanged is
// returned and the traverser is invalidated. If the edge
// reference object is uninitialised or invalidated (i.e.,
// empty), eInvalidInput is returned. If the owning AutoCAD
// entity changed since the edge reference object's subentity
// path was last set, eInvalidInput is returned and the edge
// reference object is invalidated (side effect). If the
// traverser and the edge reference object do not have the
// same owning AutoCAD entity, eObjectIdMismatch is returned.
// If the edge reference object's subentity ID fails to map to
// a valid subentity pointer, eMissingTopology is returned. If
// the edge is not in the loop edge list, eTopologyMismatch is
// returned.
//
// The getEdge() function returns the current position in the
// loop edge list. The edge object is instantiated by the caller
// and passed by reference for getEdge() to (re)set. If the
// traverser is uninitialised or invalidated (i.e., empty),
// eInvalidObject is returned. If the owning AutoCAD entity
// changed since the traverser's loop edge list was last set,
// eBrepChanged is returned and the traverser is invalidated.
// If there is no edge at the current position in the loop edge
// list, eMissingTopology is returned. If the edge fails to map
// to a valid subentity ID, eMissingSubentity is returned. In
// the event of an error, the edge reference object is unchanged
// and is thus likely to be uninitialised (i.e., empty).
//
// The getEdgeOrientToLoop() function returns a simple Boolean
// indicating whether the natural orientation of the edge from
// vertex1 to vertex2 is in the direction of the loop (kTrue)
// or in the opposite direction (kFalse). If the traverser is
// uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the
// traverser's loop edge list was last set, eBrepChanged is
// returned and the traverser is invalidated. In the event of
// an error, the orientation reference parameter's value is
// unchanged and is thus meaningless.
//
// The getParamCurve() function returns an oriented parameter
// space curve (unique to the current edge in the loop edge list)
// as an AcGe external 2d curve (cast to the AcGeCurve2d base
// class), with the entire chain of transforms from the object
// ID array ignored as they are only pertinent to model space
// and not to parameter space. The parameter curve is passed
// as a null AcGeCurve2d base class reference pointer for
// getParamCurve() to instantiate. If the traverser is
// uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since
// the traverser's loop edge list was last set, eBrepChanged
// is returned and the traverser is invalidated. If the
// parameter curve is missing (such as may sometimes happen
// if an edge crosses a seam), eMissingGeometry is returned.
// If the AcGe parameter curve comes back null, eOutOfMemory
// is returned. In the event of an error, the parameter curve
// reference pointer is unchanged and thus likely points to
// a null object.
//
// The getOrientedCurve() function returns an oriented model
// space curve (unique to the current edge in the loop edge list)
// as an AcGe external 3d curve (cast to the AcGeCurve3d base
// class), with the entire chain of transforms from the object ID
// array applied. The curve is passed as a null AcGeCurve3d base
// class reference pointer for getOrientedCurve() to instantiate.
// If the traverser is uninitialised or invalidated (i.e., empty),
// eInvalidObject is returned. If the owning AutoCAD entity changed
// since the traverser's loop edge list was last set, eBrepChanged
// is returned and the traverser is invalidated. If the curve
// geometry is missing, eMissingGeometry is returned. If the AcGe
// curve comes back null, eOutOfMemory is returned. If any of the
// associated AutoCAD database objects from the chained transforms
// cannot be opened, eWrongObjectType is returned. In the event of
// an error, the curve reference pointer is unchanged and thus
// likely points to a null object.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcGeCurve2d;
class AcGeCurve3d;
class AcBrLoop;
class AcBrEdge;
class AcBrFaceLoopTraverser;
class AcBrEdgeLoopTraverser;


class AcBrLoopEdgeTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoopEdgeTraverser);
    AcBrLoopEdgeTraverser();
    AcBrLoopEdgeTraverser(const AcBrLoopEdgeTraverser&);
    ~AcBrLoopEdgeTraverser();

    // Assignment operator
    AcBrLoopEdgeTraverser& operator =   (const AcBrLoopEdgeTraverser&);

    // Queries & Initialisers
    AcBr::ErrorStatus   setLoopAndEdge  (AcBrEdgeLoopTraverser&);
    AcBr::ErrorStatus   setLoop         (AcBrFaceLoopTraverser&);
    AcBr::ErrorStatus   getLoop         (AcBrLoop&) const;
    AcBr::ErrorStatus   setEdge         (AcBrEdge&);
    AcBr::ErrorStatus   getEdge         (AcBrEdge&) const;

    // Downward links
    // Edge usage by loop (n::1)
    AcBr::ErrorStatus   getEdgeOrientToLoop(Adesk::Boolean&) const;
    AcBr::ErrorStatus   getParamCurve   (AcGeCurve2d*&) const;
	AcBr::ErrorStatus	getOrientedCurve(AcGeCurve3d*&) const;
};


#endif
