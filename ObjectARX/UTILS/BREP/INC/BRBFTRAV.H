#ifndef AC_BRBFTRAV_H
#define AC_BRBFTRAV_H 1
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
// The AcBrBrepFaceTraverser class is the interface class for brep
// face traversers. It is used to start a downward hierarchical
// traversal of the brep portion of an AutoCAD solid, region or
// body, or to traverse all of the unique faces in the brep. All
// the functionality supported by this class is implemented by the
// class AcBrImpBrepFaceTraverser.
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrBrepFaceTraverser, call setBrep() and/or setFace() using valid,
// previously instantiated brep and face objects.
//
// The setBrep() function is used to (re)set the traverser to 
// a specific brep face list, starting at the first face in the
// list. This initialises a traverser instantiated with the default
// constructor, and resets the criteria for the eBrepChanged error.
// If the brep reference object is uninitialised or invalidated
// (i.e., empty), eInvalidInput is returned. If the owning AutoCAD
// entity changed since the brep reference object's subentity path
// was last set, eInvalidInput is returned and the brep reference
// object is invalidated (side effect). If the brep reference
// object's subentity path fails to map to a valid subentity pointer,
// eMissingTopology is returned. If the brep is not face-bounded
// (e.g., a wireframe or an empty/deleted model), eUnsuitableTopology
// is returned.
//
// The getBrep() function returns the brep owner of the face list.
// The brep object is instantiated by the caller and passed by
// reference for getBrep() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the
// owning AutoCAD entity changed since the traverser's brep face
// list was last set, eBrepChanged is returned and the traverser is
// invalidated. If the brep fails to map to a valid subentity ID,
// eMissingSubentity is returned. In the event of an error, the brep
// reference object is unchanged and is thus likely to be uninitialised
// (i.e., empty).
//
// The setFace() function is used to (re)set the traverser to a
// specific starting position in the brep face list (i.e., change
// the first face marker from the default to the specified face). This
// initialises a traverser instantiated with the default constructor,
// and resets the criteria for next() and done(). It must be called
// after setBrep(), in order to have a valid list to set position.
// If the traverser is uninitialised or invalidated (i.e., empty),
// eInvalidObject is returned. If the owning AutoCAD entity changed
// since the traverser's brep face list was last set, eBrepChanged
// is returned and the traverser is invalidated. If the face reference
// object is uninitialised or invalidated (i.e., empty), eInvalidInput
// is returned. If the owning AutoCAD entity changed since the face
// reference object's subentity path was last set, eInvalidInput is
// returned and the face reference object is invalidated (side effect).
// If the traverser and the face reference object do not have the same
// owning AutoCAD entity, eObjectIdMismatch is returned. If the face
// reference object's subentity ID fails to map to a valid subentity
// pointer, eMissingTopology is returned. If the face is not in the
// brep face list, eTopologyMismatch is returned.
//
// The getFace() function returns the current position in the brep face
// list. The face object is instantiated by the caller and passed by
// reference for getFace() to (re)set. If the traverser is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the traverser's brep face list was last
// set, eBrepChanged is returned and the traverser is invalidated. If
// there is no face at the current position in the brep face list,
// eMissingTopology is returned. If the face fails to map to a valid
// subentity ID, eMissingSubentity is returned. In the event of an error,
// the face reference object is unchanged and is thus likely to be
// uninitialised (i.e., empty).


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brtrav.h"


// forward class declarations
class AcBrBrep;
class AcBrFace;


class AcBrBrepFaceTraverser : public AcBrTraverser
{
public:
    ACRX_DECLARE_MEMBERS(AcBrBrepFaceTraverser);
    AcBrBrepFaceTraverser();
    AcBrBrepFaceTraverser(const AcBrBrepFaceTraverser&);
    ~AcBrBrepFaceTraverser();

    // Assignment operator
    AcBrBrepFaceTraverser& operator =   (const AcBrBrepFaceTraverser&);

    // Queries & Initialisers
    AcBr::ErrorStatus   setBrep         (AcBrBrep&);
    AcBr::ErrorStatus   getBrep         (AcBrBrep&) const;
    AcBr::ErrorStatus   setFace         (AcBrFace&);
    AcBr::ErrorStatus   getFace         (AcBrFace&) const;
};


#endif

