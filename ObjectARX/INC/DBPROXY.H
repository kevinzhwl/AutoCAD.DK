
#ifndef AD_DBPROXY_H
#define AD_DBPROXY_H 1
//
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

#include <rxobject.h>
#include <dbintar.h>

class AcDbProxyObject : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbProxyObject);
    
    virtual ~AcDbProxyObject() {};
    
    virtual int   proxyFlags() = 0;
    virtual const char* originalClassName() = 0;
    virtual const char* originalDxfName() = 0;
    virtual const char* applicationDescription() = 0;
    virtual Acad::ErrorStatus getReferences(AcDbObjectIdArray&,
        AcDbIntArray&) = 0;

    enum {kNoOperation          = 0,
          kEraseAllowed         = 0x1,
          kCloningAllowed       = 0x80,
          kAllButCloningAllowed = 0x1,
          kAllAllowedBits       = 0x81 };
};

class AcDbProxyEntity : public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbProxyEntity);
    
    virtual ~AcDbProxyEntity() {};
    
    virtual int   proxyFlags() = 0;
    virtual const char* originalClassName() = 0;
    virtual const char* originalDxfName() = 0;
    virtual const char* applicationDescription() = 0;
    virtual Acad::ErrorStatus getReferences(AcDbObjectIdArray&,
        AcDbIntArray&) = 0;

    enum GraphicsMetafileType {
        kNoMetafile   = 0,
        kBoundingBox  = 1,
        kFullGraphics = 2 };

    virtual AcDbProxyEntity::GraphicsMetafileType graphicsMetafileType()
        const = 0;

    virtual Acad::ErrorStatus   explode(AcDbVoidPtrArray& entitySet) const;
    virtual Acad::ErrorStatus   transformBy(const AcGeMatrix3d& xform);
	virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;
 
    enum  {kNoOperation                = 0,
           kEraseAllowed               = 0x1,
           kTransformAllowed           = 0x2,
           kColorChangeAllowed         = 0x4,
           kLayerChangeAllowed         = 0x8,
           kLinetypeChangeAllowed      = 0x10,
           kLinetypeScaleChangeAllowed = 0x20,
           kVisibilityChangeAllowed    = 0x40,
           kCloningAllowed             = 0x80,
           kAllButCloningAllowed       = 0x7F,
           kAllAllowedBits             = 0xFF };
};


#endif // AD_DBPROXY_H
