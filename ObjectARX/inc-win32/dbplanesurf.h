//
//
#pragma once
#ifndef DBPLANESURF_H
#define DBPLANESURF_H
//
// (C) Copyright 2005-2007 by Autodesk, Inc.
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
// DESCRIPTION:
//
// The AcDbPlaneSurface class is the interface class for representing
// ASM plane surfaces.  

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbPlaneSurface: public AcDbSurface
{
public:
    AcDbPlaneSurface ();
    virtual ~AcDbPlaneSurface();
    ACDB_DECLARE_MEMBERS(AcDbPlaneSurface);

    // Create plane surface from region.
    virtual Acad::ErrorStatus createFromRegion ( AcDbRegion *pRegion );

    // AcDbEntity methods
    virtual void list() const;

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;

    virtual Acad::ErrorStatus getGripPoints ( AcGePoint3dArray&  gripPoints,
                                              AcDbIntArray&  osnapModes,
                                              AcDbIntArray &  geomIds ) const;
    virtual Acad::ErrorStatus getGripPoints ( AcDbGripDataPtrArray& grips,
                                              const double curViewUnitSize,
                                              const int gripSize,
                                              const AcGeVector3d& curViewDir,
                                              const int bitflags ) const;
    virtual Acad::ErrorStatus moveGripPointsAt ( const AcDbIntArray& indices,
                                                 const AcGeVector3d& offset );
    virtual Acad::ErrorStatus moveStretchPointsAt ( const AcDbIntArray& indices,
                                                    const AcGeVector3d& offset );

    virtual bool isDependent() const;

};
#pragma pack(pop)

#endif // DBPLANESURF_H
