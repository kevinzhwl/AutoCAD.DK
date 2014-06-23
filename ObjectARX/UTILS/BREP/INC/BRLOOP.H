#ifndef AC_BRLOOP_H
#define AC_BRLOOP_H 1
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
// The AcBrLoop class is the interface class for brep loops. All the
// functionality supported by this class is implemented by the class
// AcBrImpLoop.
//
// This class defines the functions that are pertinent to the loop
// level of a brep, which is not exposed in AutoCAD and thus cannot
// be directly set to anything meaningful; it is (re)set indirectly
// by the traversers. It is also used to set the first loop of an
// AcBrFaceLoopTraverser. 
//
// Loops are secondary brep elements and thus have no associated
// geometry. They do, however, provide context for parameter space
// curves (via AcBrLoopEdgeTraverser). 
//
// The default constructor instantiates an empty object. The function
// isNull() returns kTrue on an object created this way. To (re)set an
// AcBrLoop, call AcBrFaceLoopTraverser::getLoop() or AcBrEdgeLoopTraverser
// ::getLoop() using the current object.
//
// The getFace() function returns the face that is bounded by the loop
// (always unique). The face is instantiated by the caller and passed
// by reference for getFace() to (re)set. If the object is uninitialised
// or invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the object's subentity path was last set,
// eBrepChanged is returned and the object is invalidated. If the face is
// missing, eMissingTopology is returned. If the face fails to map to a
// valid subentity ID, eMissingSubentity is returned. In the event of an
// error, the face reference object is unchanged and is thus likely to be
// uninitialised (i.e., empty).

#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"
#include "brent.h"


// forward class declarations
class AcBrFace;


class AcBrLoop : public AcBrEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrLoop);
    AcBrLoop();
    AcBrLoop(const AcBrLoop&);
    ~AcBrLoop();

    // Assignment operator
    AcBrLoop&           operator =      (const AcBrLoop&);

    // Upward links
    // Face usage by loop (1::1)
    AcBr::ErrorStatus   getFace         (AcBrFace&) const;
};


#endif
