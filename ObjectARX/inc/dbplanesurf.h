//
//
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
// DESCRIPTION:
//
// The AcDbPlaneSurface class is the interface class for representing
// ASM plane surfaces.  

#pragma once
#ifndef DBPLANESURF_H
#define DBPLANESURF_H

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

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    virtual bool isDependent() const;

protected:
    
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};
#pragma pack(pop)

#endif // DBPLANESURF_H
