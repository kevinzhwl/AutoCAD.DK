#ifndef AC_BRLVTRAV_H
#define AC_BRLVTRAV_H 1
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
// The AcBrLoopVertexTraverser class is the interface class for
// loop vertex traversers. It is used to get access to vertices
// that are at isolated points in a model (i.e., singularities,
// such as the apex of a cone). Although the loop-vertex is
// essentially a 1::1 query, it is isolated to a traverser
// rather than being offered as a query on the AcBrLoop class,
// as it represents a special case and is part of the boundary
// information of a face (via face-loop traversal). All the
// functionality supported by this class is implemented by the
// class AcBrImpLoopVertexTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrLoopVertexTraverser, call setLoop() using a valid, previously
// instantiated face-loop traverser.
//
// The next() function is a no-op, and done() is immediately set
// The next() and restart() functions are both no-ops that return
// eNotApplicable, and done() is immediately (re)set to kTrue every
// time setLoop() is called. 
//
// The setLoop() function is used to (re)set the traverser to a
// specific loop-vertex. This initialises a traverser instantiated
// with the default constructor, and resets the criteria for the
// eBrepChanged error. If the face-loop reference object is
// uninitialised or invalidated (i.e., empty), eInvalidInput is
// returned. If the owning AutoCAD entity changed since the face-
// loop reference object's face owner was last set, eInvalidInput
// is returned and the face-loop reference object is invalidated
// (side effect). If the face-loop reference object's face owner
// fails to map to a valid subentity pointer, eMissingTopology is
// returned. If there is an edge list on the loop (that is, if the
// loop does not represent a singularity), eUnsuitableTopology
// is returned; use the loop to (re)set an AcBrLoopEdgeTraverser
// instead.
//
// The getLoop() function returns the loop owner of the loop-
// vertex. The loop object is instantiated by the caller and
// passed by reference for getLoop() to (re)set. If the traverser
// is uninitialised or invalidated (i.e., empty), eInvalidObject
// is returned. If the owning AutoCAD entity changed since the
// traverser's loop edge list was last set, eBrepChanged is
// returned and the traverser is invalidated. If the loop fails
// to map to a valid subentity ID, eMissingSubentity is returned.
// In the event of an error, the loop reference object is
// unchanged and is thus likely to be uninitialised (i.e., empty).
//
// The getVertex() function returns the loop-vertex. The vertex
// object is instantiated by the caller and passed by reference
// for getVertex() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If
// the owning AutoCAD entity changed since the traverser's loop-
// vertex was last set, eBrepChanged is returned and the traverser
// is invalidated. If there is no loop-vertex, eMissingTopology
// is returned. If the vertex fails to map to a valid subentity
// ID, eMissingSubentity is returned. In the event of an error,
// the vertex reference object is unchanged and is thus likely
// to be uninitialised (i.e., empty).
//
// The getParamPoint() function returns a parameter space point
// (representative of a degenerate parameter space curve, which
// is what a singularity/loop-vertex is) as an AcGe 2d point
// (which is more representative of face boundary data than the
// u,v parameter pair), with the chain of transforms from the
// object ID array ignored as they are only pertinent to model
// space geometry. The parameter point is passed as a null
// AcGePoint2d reference pointer for getParamPoint() to
// instantiate. If the traverser is uninitialised or invalidated
// (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the traverser's loop-vertex
// was last set, eBrepChanged is returned and the traverser
// is invalidated. If the either the point geometry or surface
// geometry is missing, eMissingGeometry is returned. If the
// AcGe parameter point comes back null, eOutOfMemory is
// returned. In the event of an error, the parameter point
// reference pointer is unchanged and thus likely points to
// a null object.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcGePoint2d;
class AcBrLoop;
class AcBrVertex;
class AcBrFaceLoopTraverser;


class AcBrLoopVertexTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoopVertexTraverser);
    AcBrLoopVertexTraverser();
    AcBrLoopVertexTraverser(const AcBrLoopVertexTraverser&);
    ~AcBrLoopVertexTraverser();

    // Assignment operator
    AcBrLoopVertexTraverser& operator = (const AcBrLoopVertexTraverser&);

    // Queries & Initialisers
    AcBr::ErrorStatus   setLoop         (AcBrFaceLoopTraverser&);
    AcBr::ErrorStatus   getLoop         (AcBrLoop&) const;
    AcBr::ErrorStatus   getVertex       (AcBrVertex&) const;

    // Downward links
    // Vertex usage by loop (1::1)
    AcBr::ErrorStatus   getParamPoint	(AcGePoint2d*&) const;
};


#endif
