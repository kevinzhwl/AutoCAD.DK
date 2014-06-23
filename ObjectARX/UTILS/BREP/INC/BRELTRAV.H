#ifndef AC_BRELTRAV_H
#define AC_BRELTRAV_H 1
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
// The AcBrEdgeLoopTraverser class is the interface class for edge
// loop traversers. It is used to get access to upward hierarchical
// topological adjacencies, or to radially traverse the faces sharing
// a common edge. In order to provide the tightest coupling with
// edge list traversals (i.e., AcBrLoopEdgeTraverser), the face
// is represented by its loop boundary at the shared edge. All the
// functionality supported by this class is implemented by the class
// AcBrImpEdgeLoopTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrEdgeLoopTraverser, call setEdge() or setEdgeAndLoop() using a
// valid, previously instantiated edge object or loop-edge traverser.
//
// The setEdgeAndLoop() function is used to (re)set the traverser to 
// a specific edge loop list and starting position. This initialises
// a traverser instantiated with the default constructor, and resets
// the criteria for the eBrepChanged error. If the loop-edge reference
// object is uninitialised or invalidated (i.e., empty), eInvalidInput
// is returned. If the owning AutoCAD entity changed since the loop-edge
// reference object's loop owner was last set, eInvalidInput is returned
// and the loop-edge reference object is invalidated (side effect).
// If the loop-edge reference object's loop owner or current edge fails
// to map to a valid subentity pointer, eMissingTopology is returned.
//
// The setEdge() function is used to (re)set the traverser to 
// a specific edge loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error.
// If the edge reference object is uninitialised or invalidated
// (i.e., empty), eInvalidInput is returned. If the owning AutoCAD
// entity changed since the edge reference object's subentity path
// was last set, eInvalidInput is returned and the edge reference
// object is invalidated (side effect). If the edge reference
// object's subentity path fails to map to a valid subentity
// pointer, eMissingTopology is returned.
//
// The getEdge() function returns the edge owner of the loop list.
// The edge object is instantiated by the caller and passed by
// reference for getEdge() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the
// owning AutoCAD entity changed since the traverser's edge loop
// list was last set, eBrepChanged is returned and the traverser is
// invalidated. If the edge fails to map to a valid subentity ID,
// eMissingSubentity is returned. In the event of an error, the edge
// reference object is unchanged and is thus likely to be uninitialised
// (i.e., empty).
//
// The getLoop() function returns the current position in the edge loop
// list. The loop object is instantiated by the caller and passed by
// reference for getLoop() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the traverser's edge loop list was last
// set, eBrepChanged is returned and the traverser is invalidated. If
// there is no loop at the current position in the edge loop list,
// eMissingTopology is returned. If the loop fails to map to a valid
// subentity ID, eMissingSubentity is returned. In the event of an error,
// the loop reference object is unchanged and is thus likely to be
// uninitialised (i.e., empty).


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrLoop;
class AcBrEdge;
class AcBrLoopEdgeTraverser;


class AcBrEdgeLoopTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrEdgeLoopTraverser);
    AcBrEdgeLoopTraverser();
    AcBrEdgeLoopTraverser(const AcBrEdgeLoopTraverser&);
    ~AcBrEdgeLoopTraverser();

    // Assignment operator
    AcBrEdgeLoopTraverser& operator =   (const AcBrEdgeLoopTraverser&);

    // Queries & Initialisers
    AcBr::ErrorStatus   setEdgeAndLoop  (AcBrLoopEdgeTraverser&);
    AcBr::ErrorStatus   setEdge         (AcBrEdge&);
    AcBr::ErrorStatus   getEdge         (AcBrEdge&) const;
    AcBr::ErrorStatus   getLoop         (AcBrLoop&) const;
};


#endif

