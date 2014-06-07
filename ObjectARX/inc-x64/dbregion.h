#ifndef GEOMENT_DBREGION_H
#define GEOMENT_DBREGION_H
//
// (C) Copyright 1993-2007 by Autodesk, Inc.
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
// The AcDbRegion class is the interface class for representing
// regions inside AutoCAD.  All the functionality supported by
// this class is implemented in the class AcDbImpRegion and its
// base classes.

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"

#pragma pack(push, 8)

class AcDbRegion: public  AcDbEntity
{
public:
    AcDbRegion();
    virtual ~AcDbRegion();
    ACDB_DECLARE_MEMBERS(AcDbRegion);

    static  
    Acad::ErrorStatus createFromCurves(const AcDbVoidPtrArray& curveSegments, 
                                       AcDbVoidPtrArray& regions);

    virtual Acad::ErrorStatus getPerimeter(double&) const;
    virtual Acad::ErrorStatus getArea(double& regionArea) const;
    virtual void*             body() const;   // INTERNAL USE ONLY
    virtual Acad::ErrorStatus getAreaProp(
                                 const AcGePoint3d&  origin,
                                 const AcGeVector3d& xAxis,
                                 const AcGeVector3d& yAxis,
                                 double&             perimeter,
                                 double&             area,
                                 AcGePoint2d&        centroid,
                                 double              momInertia[2],
                                 double&             prodInertia,
                                 double              prinMoments[2],
                                 AcGeVector2d        prinAxes[2],
                                 double              radiiGyration[2],
                                 AcGePoint2d&        extentsLow,
                                 AcGePoint2d&        extentsHigh)const;

    
    virtual Acad::ErrorStatus getPlane(AcGePlane& regionPlane) const;

    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                             AcDb::Intersect   intType, 
                                             AcGePoint3dArray& points,
                                             Adesk::GsMarker   thisGsMarker, 
                                             Adesk::GsMarker   otherGsMarker) const;
    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
                                             AcDb::Intersect   intType, 
                                             const AcGePlane&  projPlane,
                                             AcGePoint3dArray& points, 
                                             Adesk::GsMarker   thisGsMarker, 
                                             Adesk::GsMarker   otherGsMarker) const;

    virtual Adesk::Boolean    isNull () const;
    virtual Acad::ErrorStatus getNormal(AcGeVector3d&) const;

    virtual AcDbSubentId      internalSubentId      (void* ent) const;                // INTERNAL USE ONLY
    virtual void*             internalSubentPtr     (const AcDbSubentId& id) const;   // INTERNAL USE ONLY

    // Subentity acquisition.
    //
    virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(AcDb::SubentType     type,
                                                        Adesk::GsMarker      gsMark, 
                                                        const AcGePoint3d&   pickPoint,
                                                        const AcGeMatrix3d&  viewXform, 
                                                        int&                 numPaths,
                                                        AcDbFullSubentPath*& subentPaths, 
                                                        int                  numInserts = 0,
                                                        AcDbObjectId* entAndInsertStack = NULL) const;

    virtual Acad::ErrorStatus getGsMarkersAtSubentPath(
                                 const AcDbFullSubentPath& subPath, 
                                 AcArray<Adesk::GsMarker>& gsMarkers) const;

    virtual AcDbEntity*       subentPtr(const AcDbFullSubentPath& id) const;
 
    virtual Acad::ErrorStatus booleanOper(AcDb::BoolOperType operation, AcDbRegion* otherRegion);
    virtual Acad::ErrorStatus setBody(const void* modelerBody);   // INTERNAL USE ONLY

    virtual Adesk::UInt32 numChanges() const;

    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
