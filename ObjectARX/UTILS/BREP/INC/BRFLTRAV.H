#ifndef AC_BRFLTRAV_H
#define AC_BRFLTRAV_H 1
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
// The AcBrFaceLoopTraverser class is the interface class for face
// loop traversers. It is used to get access to edges through their
// loop uses. All the functionality supported by this class is
// implemented by the class AcBrImpFaceLoopTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrFaceLoopTraverser, call setFace() and/or setLoop() using valid,
// previously instantiated face and loop objects.
//
// The setFace() function is used to (re)set the traverser to 
// a specific face loop list, starting at the first loop in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error.
// If the face reference object is uninitialised or invalidated
// (i.e., empty), eInvalidInput is returned. If the owning AutoCAD
// entity changed since the face reference object's subentity path
// was last set, eInvalidInput is returned and the face reference
// object is invalidated (side effect). If the face reference
// object's subentity path fails to map to a valid subentity pointer,
// eMissingTopology is returned. If the face is neither edge-bounded
// nor vertex-bounded (e.g., a sphere or a true torus, where there
// are no loops nor boundary curve geometry), eUnsuitableTopology
// is returned.
//
// The getFace() function returns the face owner of the loop list.
// The face object is instantiated by the caller and passed by
// reference for getFace() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the
// owning AutoCAD entity changed since the traverser's face loop
// list was last set, eBrepChanged is returned and the traverser is
// invalidated. If the face fails to map to a valid subentity ID,
// eMissingSubentity is returned. In the event of an error, the face
// reference object is unchanged and is thus likely to be uninitialised
// (i.e., empty).
//
// The setLoop() function is used to (re)set the traverser to a
// specific starting position in the face loop list (i.e., change
// the first loop marker from the default to the specified loop). This
// initialises a traverser instantiated with the default constructor,
// and resets the criteria for next() and done(). It must be called
// after setFace(), in order to have a valid list to set position.
// If the traverser is uninitialised or invalidated (i.e., empty),
// eInvalidObject is returned. If the owning AutoCAD entity changed
// since the traverser's face loop list was last set, eBrepChanged
// is returned and the traverser is invalidated. If the loop reference
// object is uninitialised or invalidated (i.e., empty), eInvalidInput
// is returned. If the owning AutoCAD entity changed since the loop
// reference object's subentity path was last set, eInvalidInput is
// returned and the loop reference object is invalidated (side effect).
// If the traverser and the loop reference object do not have the same
// owning AutoCAD entity, eObjectIdMismatch is returned. If the loop
// reference object's subentity ID fails to map to a valid subentity
// pointer, eMissingTopology is returned. If the loop is not in the
// face loop list, eTopologyMismatch is returned.
//
// The getLoop() function returns the current position in the face loop
// list. The loop object is instantiated by the caller and passed by
// reference for getLoop() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the traverser's face loop list was last
// set, eBrepChanged is returned and the traverser is invalidated. If
// there is no loop at the current position in the face loop list,
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
class AcBrFace;
class AcBrLoop;


class AcBrFaceLoopTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrFaceLoopTraverser);
    AcBrFaceLoopTraverser();
    AcBrFaceLoopTraverser(const AcBrFaceLoopTraverser&);
    ~AcBrFaceLoopTraverser();

    // Assignment operator
    AcBrFaceLoopTraverser& operator =   (const AcBrFaceLoopTraverser&);

    // Queries & Initialisers
    AcBr::ErrorStatus   setFace         (AcBrFace&);
    AcBr::ErrorStatus   getFace         (AcBrFace&) const;
    AcBr::ErrorStatus   setLoop         (AcBrLoop&);
    AcBr::ErrorStatus   getLoop         (AcBrLoop&) const;
};


#endif

