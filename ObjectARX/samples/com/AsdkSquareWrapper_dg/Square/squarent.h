// (C) Copyright 1999 by Autodesk, Inc. 
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

#include "dbents.h"
#include "acgi.h"

#define SIN45  0.7071067811865
#define HALFPI 3.14159265358979323846/2.0

class AsdkSquare : public AcDbCurve
{
public:
    ACRX_DECLARE_MEMBERS(AsdkSquare);
    AsdkSquare();
    virtual ~AsdkSquare();

    // AcDbEntity overrides
    //

    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;

    virtual Adesk::Boolean worldDraw(AcGiWorldDraw* wd);

    virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode       osnapMode,
                                                int                   gsSelectionMark,
                                                const AcGePoint3d&    pickPoint,
                                                const AcGePoint3d&    lastPoint,
                                                const AcGeMatrix3d&   viewXform,
                                                AcGePoint3dArray&     snapPoints,
                                                AcDbIntArray&         geomIds
                                                ) const;

    virtual Acad::ErrorStatus getGripPoints(AcGePoint3dArray& gripPoints,
                                            AcDbIntArray& osnapModes,
                                            AcDbIntArray& geomIds) const;

    virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
                                            const AcGeVector3d& offset);

    virtual Acad::ErrorStatus dwgInFields( AcDbDwgFiler* filer );
    virtual Acad::ErrorStatus dwgOutFields( AcDbDwgFiler* filer ) const;

    virtual Acad::ErrorStatus dxfInFields( AcDbDxfFiler* filer );
    virtual Acad::ErrorStatus dxfOutFields( AcDbDxfFiler* filer ) const;

    virtual void list() const;

    virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    virtual Adesk::Boolean isPlanar() const 
    {
        assertReadEnabled();
        return Adesk::kTrue;
    }

    virtual Acad::ErrorStatus getPlane
        (AcGePlane& plane, AcDb::Planarity&  type) const 
    {
        assertReadEnabled();
        plane.set(mCenter, mNormal);
        type = AcDb::kPlanar;
        return Acad::eOk;
    }
    
    void squareCenter(AcGePoint3d& p) const;
    void setSquareCenter(const AcGePoint3d& p );

    void squareOrient(AcGeVector3d& p) const;
    void setSquareOrient(const AcGeVector3d& p );

    void squareNormal(AcGeVector3d& d) const;
    void setSquareNormal(const AcGeVector3d& d);

    void squareSideLength(double& l) const;
    void setSquareSideLength(const double l);

    void squareId(int& i) const;
    void setSquareId(const int i);

private:

    // Our square is defined by it's center, direction vector (where it
    // also gets it's size), and a normal.
    AcGePoint3d  mCenter;
    AcGeVector3d mOrient;
    AcGeVector3d mNormal;
    int mId;

};

inline void AsdkSquare::squareCenter(AcGePoint3d& p) const
    { assertReadEnabled();
        p = mCenter;} // Square center

inline void AsdkSquare::setSquareCenter( const AcGePoint3d& p ) 
    { assertWriteEnabled();
        mCenter = p; } // Square center

inline void AsdkSquare::squareOrient(AcGeVector3d& p) const
    {assertReadEnabled();
        p = mOrient;} // Square Orientation in 3dspace

inline void AsdkSquare::setSquareOrient( const AcGeVector3d& p ) 
    { assertWriteEnabled();
        mOrient = p; } // Square Orientation in 3dspace

inline void AsdkSquare::squareNormal(AcGeVector3d& d) const
    {assertReadEnabled();
        d = mNormal;} // Square Normal

inline void AsdkSquare::setSquareNormal( const AcGeVector3d& d ) 
    { assertWriteEnabled();
        mNormal = d; } // Square Normal

inline void AsdkSquare::squareSideLength(double& l) const
    {assertReadEnabled();
        l = (mOrient.length() *  SIN45) * 2.0; } // Square side length

inline void AsdkSquare::setSquareSideLength(const double l) 
    { assertWriteEnabled();
    // Calculate the new vector based on the side length.
      mOrient = mOrient.normalize();
      mOrient.x = mOrient.x * ((l / 2.0) / SIN45 );  
      mOrient.y = mOrient.y * ((l / 2.0) / SIN45 );  
      mOrient.z = mOrient.z * ((l / 2.0) / SIN45 ); }

inline void AsdkSquare::squareId(int& i) const
    {assertReadEnabled();
        i = mId; } // Square side length

inline void AsdkSquare::setSquareId(const int i) 
    { assertWriteEnabled();
    // Calculate the new vector based on the side length.
        mId = i;}
