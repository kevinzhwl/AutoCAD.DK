// (C) Copyright 1996 by Autodesk, Inc. 
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
//
// jblob.h - jblob entity
//
#ifndef _JBLOB_H
#define _JBLOB_H

#include "dbents.h"
#include "acgi.h"

class Jblob : public  AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(Jblob);
    Jblob();
    virtual ~Jblob();

    virtual Adesk::Boolean    worldDraw(AcGiWorldDraw* mode);
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
        virtual Acad::ErrorStatus audit(AcDbAuditInfo* auditor);

    // AcDbEntity overrides
    //
    virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
    virtual void              list() const;
    virtual Acad::ErrorStatus getOsnapPoints(
        AcDb::OsnapMode osnapMode,
        int gsSelectionMark,
        const AcGePoint3d& pickPoint,
        const AcGePoint3d& lastPoint,
        const AcGeMatrix3d& viewXform,
        AcGePoint3dArray& snapPoints,
        AcDbIntArray& geomIds) const;
        virtual Acad::ErrorStatus getGripPoints(
        AcGePoint3dArray& gripPoints,
        AcDbIntArray& osnapMasks,
        AcDbIntArray& geomIds) const;
        virtual Acad::ErrorStatus moveGripPointsAt(
        const AcDbIntArray& indices,
        const AcGeVector3d& offset);
        virtual Acad::ErrorStatus getStretchPoints(
        AcGePoint3dArray& stretchPoints) const;
        virtual Acad::ErrorStatus moveStretchPointsAt(
        const AcDbIntArray& indices,
        const AcGeVector3d& offset);
        virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
        virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType saveType);


    // Jblob specific protocol
    //
    void endpoint(AcGePoint3d& p) const;
    void setEp(const AcGePoint3d& p); // endpoint

    void center(AcGePoint3d& p) const;
    void setBp(const AcGePoint3d& p); // blob center

    void radius(double& r) const;
    void setBr(const double r); // blob radius

    void normal(AcGeVector3d& v) const;
    void setNormal(const AcGeVector3d& v); // blob normal

private:

    Acad::ErrorStatus osnapNear(const AcGePoint3d&  pickPoint,
        AcGePoint3dArray&   snapPoints) const;
    Acad::ErrorStatus osnapEnd(const AcGePoint3d&   pickPoint,
        AcGePoint3dArray& snapPoints) const;
    Acad::ErrorStatus osnapMid(const AcGePoint3d&   pickPoint,
        AcGePoint3dArray& snapPoints) const;
    Acad::ErrorStatus osnapCen(const AcGePoint3d&   pickPoint,
        AcGePoint3dArray& snapPoints) const;
    Acad::ErrorStatus osnapQuad(const AcGePoint3d&  pickPoint,
        AcGePoint3dArray& snapPoints) const;

    // data members
    //
    AcGePoint3d  mp;      // one endpoint
    AcGePoint3d  mpblob;  // other endpoint == blob center
    double       mrblob;  // blob radius
    AcGeVector3d mnormal; // blob normal vector

};

MAKE_ACDBOPENOBJECT_FUNCTION(Jblob);


inline void Jblob::endpoint(AcGePoint3d& p) const
{
    assertReadEnabled();
    p = mp;
}

inline void Jblob::setEp(const AcGePoint3d& p) 
{
    assertWriteEnabled();
    mp = p;
    recordGraphicsModified();
} // endpoint

inline void Jblob::center(AcGePoint3d& p) const
{
    assertReadEnabled();
    p = mpblob;
}

inline void Jblob::setBp(const AcGePoint3d& p) 
{
    assertWriteEnabled();
    mpblob = p;
    recordGraphicsModified();
} // blob center

inline void Jblob::radius(double& r) const
{
    assertReadEnabled();
    r = mrblob;
}

inline void Jblob::setBr(const double r)       
{
    assertWriteEnabled();
    mrblob = r;
    recordGraphicsModified();
} // blob radius

inline void Jblob::normal(AcGeVector3d& v) const
{
    assertReadEnabled();
    v = mnormal;
}

inline void Jblob::setNormal(const AcGeVector3d& v)
{
    assertWriteEnabled();
    mnormal = v;
    recordGraphicsModified();
} // blob normal

#endif // _JBLOB_H
