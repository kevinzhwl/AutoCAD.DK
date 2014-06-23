#ifndef AD_DBLEAD_H
#define AD_DBLEAD_H 1
//
//  (C) Copyright 1994-1997 by Autodesk, Inc.  All rights reserved.
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

#include "dbmain.h"
#include "dbcurve.h"
#include "gescl3d.h"
#include "gepnt2d.h"
#include "geplane.h"

class AcDbLeader: public  AcDbCurve
{
public:
    AcDbLeader();
    ~AcDbLeader();
    ACDB_DECLARE_MEMBERS(AcDbLeader);
    DBCURVE_METHODS

    // Leader orientation.
    //
    virtual void              setPlane          (const AcGePlane&);
    virtual AcGeVector3d      normal            () const;

    // Vertex manipulation.
    //
    virtual  int numVertices() const;
    virtual  Adesk::Boolean appendVertex(const AcGePoint3d&);
    virtual  void              removeLastVertex  ();
    virtual  AcGePoint3d firstVertex() const;
    virtual  AcGePoint3d lastVertex() const;
    virtual  AcGePoint3d vertexAt(int) const;
    virtual  Adesk::Boolean setVertexAt(int, const AcGePoint3d&);

    // Display characteristics.
    //
    virtual Adesk::Boolean    hasArrowHead      () const;
    virtual void              enableArrowHead   ();
    virtual void              disableArrowHead  ();
    virtual Adesk::Boolean    hasHookLine       () const;
    //
    virtual void              setToSplineLeader ();
    virtual void              setToStraightLeader();
    virtual Adesk::Boolean    isSplined         () const;
    //
    virtual AcDbHardPointerId dimensionStyle    () const;
    virtual void              setDimensionStyle (const AcDbHardPointerId&);
    virtual void              setDimVars        ();
    virtual Acad::ErrorStatus setColorIndex     (Adesk::UInt16,
                                 Adesk::Boolean doSubents = Adesk::kTrue);

    // Associativity support.
    //
    virtual Acad::ErrorStatus attachAnnotation  (const AcDbObjectId&);
    virtual Acad::ErrorStatus detachAnnotation  ();
    virtual AcDbObjectId      annotationObjId   () const;
    virtual Acad::ErrorStatus evaluateLeader    ();

    // Trim and extend support.
    //
    virtual  Acad::ErrorStatus intersectWith    (const AcDbEntity*,
	                                         AcDb::Intersect, 
                                                 AcGePoint3dArray&,
                                                 int thisGsMarker = 0,
	                                         int otherGsMarker = 0) const;
    virtual  Acad::ErrorStatus intersectWith    (const AcDbEntity*,
	                                         AcDb::Intersect, 
                                                 const AcGePlane& projPlane, 
                                                 AcGePoint3dArray&,
	                                         int thisGsMarker = 0, 
                                                 int otherGsMarker = 0) const;

    // other AcDbEntity support
    //
    virtual Acad::ErrorStatus explode           (AcDbVoidPtrArray& entitySet) const;

    // Support for persistant reactor to annotation.
    //
    virtual void              modified          (const AcDbObject*);
    virtual void              erased            (const AcDbObject*,
                                                 Adesk::Boolean = Adesk::kTrue);
    virtual void              goodbye           (const AcDbObject*);
    virtual void              copied            (const AcDbObject*,
                                                 const AcDbObject*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLeader);

#endif
