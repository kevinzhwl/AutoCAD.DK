#ifndef AC_BRTRAV_H
#define AC_BRTRAV_H 1
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
// The AcBrTraverser class is the interface base class for topology
// traversers. All the functionality supported by this class is
// implemented by the class AcBrImpTraverser.
//
// This class defines the functions that are common to all topology
// traversers, and cannot be instantiated as it has no meaning on
// its own. It is derived from AcRxObject in order to provide full
// service run-time type-checking for all derived traverser classes.
//
// The AcRxObject inherited isEqualTo() function is redefined to check
// content equality between two traverser objects. If either object is
// invalid or is not a traverser object, the function returns kFalse;
// kTrue is returned when the object is valid and has been equated to
// another valid traverser object of the same subclass. Equivalence is
// defined as having the same subentity path.
//
// The isNull() function tests whether the traverser has been set to
// anything meaningful. kTrue is returned if the object is uninitialised
// or invalidated (i.e., empty).
//
// The done() function returns kTrue if the entire topological adjacency
// list has been traversed (using the next() function); as determined by
// the list owner and the most recently set starting position.
//
// The next() function adjusts the traverser to point to the next object
// in the topological adjacency list. All lists are treated as circular,
// ordered lists. If the traverser is uninitialised or invalidated
// (i.e., empty), eInvalidObject is returned. If the owning AutoCAD
// entity changed since the traverser's list owner was last set,
// eBrepChanged is returned and the traverser is invalidated. If
// the next object in the topological adjacency list is missing,
// eMissingTopology is returned.
//
// The restart() function adjusts the traverser to point to the first object
// in the topological adjacency list. If the traverser is uninitialised or
// invalidated (i.e., empty), eInvalidObject is returned. If the owning
// AutoCAD entity changed since the traverser's list owner was last set,
// eBrepChanged is returned and the traverser is invalidated.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "brgbl.h"


// forward class declarations
class AcBrImpTraverser;


class AcBrTraverser : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcBrTraverser);
    virtual ~AcBrTraverser();
    
    // Equivalence                    
    Adesk::Boolean      isEqualTo       (const AcRxObject* other) const;
                        
    // Queries & Initialisers
    Adesk::Boolean      isNull          () const;

    // Topological traversal
    Adesk::Boolean      done            () const;
    AcBr::ErrorStatus   next            ();
    AcBr::ErrorStatus   restart         ();

protected:
    AcBrTraverser();
    AcBrTraverser(const AcBrTraverser&);
    AcBrTraverser&      operator =      (const AcBrTraverser&);

    AcBrImpTraverser*   mpImp;
};


#endif

