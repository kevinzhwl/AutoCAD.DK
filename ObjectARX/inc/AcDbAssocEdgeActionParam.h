//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright � 2009-2011 by Autodesk, Inc. 
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
// CREATED BY: Jiri Kripac                                 March 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocActionParam.h"
#include "AcDbGeomRef.h"
#pragma pack (push, 8)


/// <summary><para>
/// Action parameter that keeps reference to an edge, i.e. to a subentity whose 
/// geometry is a simple AcDbCurve3d. 
/// </para><para>
/// It uses AcDbAssocGeomDependency to define a persistent reference to an edge 
/// subentity, such as to a segment of a polyline or to an edge of an AcDbSurface 
/// or of an AcDb3dSolid. Alternatively, it may keep AcDbAssocDependency to the 
/// whole entity that itself is just a simple edge, such as AcDbLine, AcDbCircle 
/// or AcDbArc. It may also directly keep the curve geometry in the action parameter 
/// in the form of an AcGeCurve3d*, instead of referencing some other AcDbEntity.
/// </para><para>
/// If the edge is part of a face of an AcDbSurface or AcDb3dSolid, it may also 
/// keep information about the face of the edge. This allows the edges to be used 
/// in input profiles in actions like AcDbAssocLoftedSurfaceActionBody or 
/// AcDbAssocBlendSurfaceActionBody that may take as input continuity information 
/// (G0, G1, G2) relative to the face of the edge.
/// </para></summary>
///
class ACDB_PORT AcDbAssocEdgeActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocEdgeActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocEdgeActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary><para>
    /// The input AcDbEdgeRef is a non-persistent reference to an edge geometry, 
    /// the AcDbAssocEdgeActionParam will make a persistent reference to that edge 
    /// and also to the face of the edge, if face information is also provided.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced edge subentity. In case the whole AcDbEntity 
    /// is referenced, not its subentity, an AcDbAssocDependency is used. If it 
    /// is constant geometry in the form of an AcGeCurve3d, no dependency is created.
    /// </para></summary>
    /// <param name="edgeRef"> 
    /// Reference to an "edge" subentity of an entity, to a whole entity, or to 
    /// an AcGeCurve3d constant geometry. See AcDbEdgeRef for details.
    /// </param>
    /// <param name="isReadDependency">  Read-dependency on the entity should be created.  </param>
    /// <param name="isWriteDependency"> Write-dependency on the entity should be created. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus setEdgeRef(const AcDbEdgeRef& edgeRef, bool isReadDependency = true, bool isWriteDependency = false);

    /// <summary> <para>
    /// Returns references to the transient subentities of an AcDbEntity, that 
    /// correspond to the persistent subentity that this edge action parameter 
    /// references. It can also be reference to the whole AcDbEntity  or to 
    /// constant AcGeCurve3d geometry. See AcDbEdgeRef for details.
    /// </para><para>
    /// When a single edge (such as edge of a solid or surface) is referenced by 
    /// this AcDbAssocEdgeActionParam and some parameters of the solid/surface 
    /// are changed and the solid/surface is re-evaluated from its actions, this 
    /// single edge may then correspond to any number of edges, because the original 
    /// edge might have gotten split, merged, or even may have disappeared. That 
    /// is why the output is an array of EdgeRefs, but in typical case the array 
    /// will contain just a single element.
    /// </para><para>
    /// Refer to AcDbAssocGeomDependency class that is used to create a persistent 
    /// dependency on the referenced edge subentity. In case the whole AcDbEntity 
    /// is referenced, not its subentity, an AcDbAssocDependency is used. If it 
    /// is constant geometry in the form of an AcGeCurve3d, no dependency is created.
    /// </para></summary>
    /// <param name="edgeRefs"> 
    /// References to the transient subentities of an AcDbEntity, that correspond 
    /// to the persistent subentity that this edge action parameter references. 
    /// It can also be reference to the whole AcDbEntity or to constant AcGeCurve3d 
    /// geometry. See AcDbEdgeRef for details.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getEdgeRef(AcArray<AcDbEdgeRef>& edgeRefs) const;

    /// <summary>
    /// If this action parameter depends on an AcDbEntity via an AcDbAssocDependency
    /// or AcDbAssocGeomDependency, it returns AcDbCompoundObjectId of the entity 
    /// this dependency depends on.
    /// </summary>
    /// <param name="compoundId"> 
    /// The AcDbCompoundObjectId of the entity this action parameter depends on,
    /// or an empty compound object id if the action parameter does not depend
    /// on any entity.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentOnCompoundObject(AcDbCompoundObjectId& compoundId) const;
};

#pragma pack (pop)

