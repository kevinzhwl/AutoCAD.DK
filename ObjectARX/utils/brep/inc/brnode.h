#ifndef AC_BRNODE_H
#define AC_BRNODE_H 1
// (C) Copyright 1997-1999 by Autodesk, Inc.
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
// The AcBrNode class is the interface class for nodes in a mesh.
// All the functionality supported by this class is implemented
// by the class AcBrImpNode.
//
// This class defines the functions that are pertinent to the node
// level of a mesh, and cannot be directly set by the user as the
// initialisation requirements are only available internally at
// the time of a call to AcBrMesh2d::generate().
//
// A node is the intersection or terminating point of two or more
// edges in a mesh, and thus has associated geometry (i.e., a point).
// A mapping back to the original brep topology is provided in the
// form of a backpointer to the dimensionally lowest topology object
// that contains this node (cf. AcBrMeshEntity::getEntityAssociated()).
// If this node is part of a 2d mesh, the associated entity type
// can be used to classify interior (i.e., face) vs. boundary
// (i.e., edge or vertex) nodes. Surface usage data (such as uv
// parameters and surface normals) must be queried in the context
// of 2d elements using AcBrElement2dNodeTraverser.
//
// This class generally is accessed by the user via an element node
// traverser. The only way to delete the node referenced by this class
// from the mesh data cache is to delete the mesh object that owns it,
// or to regenerate the mesh.
//
// The set() node data initialiser is for internal use only. It is used
// to set this mesh node's internal data using an unexported type.
//
// The get() node data query is for internal use only. It retrieves
// this mesh node's internal data using an unexported type.
//
// The getPoint() model space point query returns this node's underlying
// point as an AcGePoint3d, with the entire chain of transforms from 
// the associated topology object's subentity path applied. The point 
// is instantiated by the caller and passed by reference for getPoint()
// to set. If this node object is uninitialised, eUninitialisedObject
// is returned. In the event of an error, the point reference argument's
// value is unchanged.


#include "adesk.h"
#include "rxobject.h"
#include "rxboiler.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brment.h"


// forward class declarations
class AcGePoint3d;
class AcBrMeshEntity;
class AcBrNodeData;


class AcBrNode : public AcBrMeshEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcBrNode);
    AcBrNode();
    AcBrNode(const AcBrNode& src);
    ~AcBrNode();
    
    // Assignment operator
    AcBrNode&           operator =      (const AcBrNode& src);

    // Queries & Initialisers
    AcBr::ErrorStatus   set				(AcBrNodeData* nodeData);
    AcBr::ErrorStatus   get				(AcBrNodeData*& nodeData) const;

    // Geometry
    AcBr::ErrorStatus   getPoint        (AcGePoint3d& point) const;
};


#endif

