//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#ifndef __IMGENT_H
#define __IMGENT_H

#include "dbents.h"
#include "dbimage.h"
#include "acgi.h"
#include "gept3dar.h"
#include "gebndpln.h"
#include "geplin2d.h"
#include "dbproxy.h"
#pragma pack (push, 8)

const double kEpsilon = 1.0e-7;

const int kAllEntityProxyFlags =
    AcDbProxyEntity::kEraseAllowed         |
    AcDbProxyEntity::kTransformAllowed     |
    AcDbProxyEntity::kColorChangeAllowed         |
    AcDbProxyEntity::kLayerChangeAllowed         |
    AcDbProxyEntity::kLinetypeChangeAllowed      |
    AcDbProxyEntity::kMaterialChangeAllowed      |
    AcDbProxyEntity::kLinetypeScaleChangeAllowed |
    AcDbProxyEntity::kVisibilityChangeAllowed;

// Opaque types
//
class RasterImageImp;

// Make compiler shut up
//
#pragma warning( disable : 4275 ) 

#ifdef ISMDLLACCESS
#undef ISMDLLACCESS
#endif
#ifdef ISMDLLACCESSDATA
#undef ISMDLLACCESSDATA
#endif
#ifdef ISM_OBJ // For DwgUnplugged ISMobj.arx:
// Classes to be exported have to have ISMDLLACCESS definition in its header.
// Example: class ISMDLLACCESS AcDbImpRasterImageDef
#define ISMDLLACCESS __declspec(dllexport)
#define ISMDLLACCESSDATA
#else
#define ISMDLLACCESS 
#define ISMDLLACCESSDATA __declspec(dllimport)
#endif

////////////////////// AcDbRasterImage ///////////////////
//
class ISMDLLACCESS AcDbRasterImage : public AcDbImage 
{
public:

    static ClassVersion         classVersion();

    ACRX_DECLARE_MEMBERS(AcDbRasterImage);

                                AcDbRasterImage();
    virtual                     ~AcDbRasterImage();

    RasterImageImp*             ptrImp() const;
    RasterImageImp*             setPtrImp(RasterImageImp* pImp);
    //////////////////// AcDbObject overrides ////////////////////
    //
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

    virtual Acad::ErrorStatus   subSwapIdWith(
                                    AcDbObjectId otherId,
                                    Adesk::Boolean swapXdata = Adesk::kFalse,
                                    Adesk::Boolean swapExtDict = Adesk::kFalse
                                );

    //////////////////// AcDbEntity overrides ////////////////////
    // 
    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    virtual bool                castShadows() const;
    virtual void                setCastShadows(bool newVal);
    virtual bool                receiveShadows() const;
    virtual void                setReceiveShadows(bool newVal);

    ////////////////////// AcDbImage specific protocol ////////////////////
    //
    virtual AcGiSentScanLines*  getScanLines(
                                    const AcGiRequestScanLines& req
                                ) const;
    virtual Adesk::Boolean      freeScanLines(
                                    AcGiSentScanLines* pSSL
                                ) const;


    ////////////////////// AcDbRasterImage specific protocol ////////////////////
    //
    virtual Acad::ErrorStatus   setImageDefId(AcDbObjectId imageId);
    virtual AcDbObjectId        imageDefId() const;

    virtual void                setReactorId(AcDbObjectId reactorId);
    virtual AcDbObjectId        reactorId() const;

    // Image plane orientation
    //
    virtual Adesk::Boolean      setOrientation(
                                    const AcGePoint3d& origin,
                                    const AcGeVector3d& uCorner,
                                    const AcGeVector3d& vOnPlane);
    virtual void                getOrientation(
                                    AcGePoint3d& origin,
                                    AcGeVector3d& u,
                                    AcGeVector3d& v) const;

    virtual AcGeVector2d        scale() const;
    virtual AcGeVector2d        imageSize(Adesk::Boolean bGetCachedValue
                                        = Adesk::kFalse) const;

    // Clip boundary management protocol
    //
    enum ClipBoundaryType
    {
        kInvalid,
        kRect,
        kPoly
    };
#ifndef _ADESK_MAC_
    virtual Acad::ErrorStatus   setClipBoundaryToWholeImage(
                                    AcGeVector2d& size = AcGeVector2d(0,0));
#else
    virtual Acad::ErrorStatus   setClipBoundaryToWholeImage(
															AcGeVector2d& size);
	virtual Acad::ErrorStatus   setClipBoundaryToWholeImage()
    {
        AcGeVector2d size(0, 0);
        return setClipBoundaryToWholeImage(size);
    }
#endif // Nodef _ADESK_MAC_
    virtual Acad::ErrorStatus   setClipBoundary(
                                    ClipBoundaryType type,
                                    const AcGePoint2dArray&
                                    );
    virtual const AcGePoint2dArray&  clipBoundary() const;
    virtual ClipBoundaryType    clipBoundaryType() const;
    Adesk::Boolean              isClipped() const;

    // Returns either clip boundary or image extents vertices.
    // Used for object snapping and intersection.
    //
    virtual Acad::ErrorStatus   getVertices(
                                    AcGePoint3dArray& verts
                                ) const;

    // Image pixel to model coordinate transform 
    //
    virtual Acad::ErrorStatus   getPixelToModelTransform(AcGeMatrix3d&) const;

    // Per-entity image display and plot options.
    //
    enum ImageDisplayOpt
    {
        kShow                   = 1,
        kShowUnAligned          = 2,
        kClip                   = 4,
        kTransparent            = 8
    };

    virtual void                setDisplayOpt(
                                    ImageDisplayOpt option, 
                                    Adesk::Boolean bValue
                                );
    virtual Adesk::Boolean      isSetDisplayOpt(ImageDisplayOpt option) const;

    virtual Acad::ErrorStatus   setBrightness( Adesk::Int8 value );
    virtual Adesk::Int8         brightness() const;

    virtual Acad::ErrorStatus   setContrast( Adesk::Int8 value );
    virtual Adesk::Int8         contrast() const;

    virtual Acad::ErrorStatus   setFade( Adesk::Int8 value );
    virtual Adesk::Int8         fade() const;

    virtual Adesk::Boolean      isClipInverted() const;
    virtual void                setClipInverted(Adesk::Boolean newVal);

    double                      width() const;
    double                      height() const;

    double                      imageHeight() const;
    double                      imageWidth() const;
    Acad::ErrorStatus           setHeight(double);
    Acad::ErrorStatus           setWidth(double);
    AcGePoint3d                 position() const;

    double                      rotation() const;
    Acad::ErrorStatus           setRotation(double rotation);

    //aliases for setDisplayOpt/isSetDisplayOpt
    bool                        isImageShown() const;
    void                        setShowImage(bool value);

    bool                        isImageTransparent() const;
    void                        setImageTransparency(bool value);

    bool                        isShownClipped() const;
    void                        setShowClipped(bool value);

protected:
    virtual Acad::ErrorStatus   subExplode(AcDbVoidPtrArray& entitySet) const;
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* mode);
    virtual void                subViewportDraw(AcGiViewportDraw* mode);

    virtual void                subList() const;
    virtual Acad::ErrorStatus   subGetOsnapPoints(
                                        AcDb::OsnapMode     osnapMode,
                                        Adesk::GsMarker     gsSelectionMark,
                                        const AcGePoint3d&  pickPoint,
                                        const AcGePoint3d&  lastPoint,
                                        const AcGeMatrix3d& viewXform,
                                        AcGePoint3dArray&   snapPoints,
                                        AcDbIntArray &   geomIds
                                ) const;
    virtual Acad::ErrorStatus subGetGripPoints(
                                        AcDbGripDataPtrArray& grips,
                                        const double curViewUnitSize,
                                        const int gripSize,
                                        const AcGeVector3d& curViewDir,
                                        const int bitflags
                                ) const;
    virtual Acad::ErrorStatus   subGetGripPoints(
                                        AcGePoint3dArray&   gripPoints,
                                        AcDbIntArray&       osnapModes,
                                        AcDbIntArray &   geomIds
                                ) const;
    virtual void                subGripStatus (const AcDb::GripStat status);
    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                        const AcDbVoidPtrArray& gripAppData,
                                        const AcGeVector3d& offset, 
                                        const int bitflags);
    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                        const AcDbIntArray& indices,
                                        const AcGeVector3d& offset);
    virtual Acad::ErrorStatus   subGetStretchPoints(
                                    AcGePoint3dArray&  stretchPoints
                                ) const;
    virtual Acad::ErrorStatus   subMoveStretchPointsAt(
                                        const AcDbIntArray& indices,
                                        const AcGeVector3d& offset
                                );
    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus   subGetTransformedCopy(
                                    const AcGeMatrix3d& xform,
                                        AcDbEntity*& ent
                                ) const;   
    virtual Acad::ErrorStatus   subGetSubentPathsAtGsMarker(
                                    AcDb::SubentType      type,
                                    Adesk::GsMarker       gsMark,
                                    const AcGePoint3d&    pickPoint,
                                    const AcGeMatrix3d&   viewXform,
                                    int&                  numPaths,
                                    AcDbFullSubentPath*&  subentPaths,
                                    int                   numInserts = 0,
                                    AcDbObjectId*         entAndInsertStack = 0
                                ) const;
    virtual Acad::ErrorStatus   subGetGsMarkersAtSubentPath(
                                    const AcDbFullSubentPath& subPath, 
                                    AcArray<Adesk::GsMarker>& gsMarkers
                                ) const;
    virtual AcDbEntity*         subSubentPtr(const AcDbFullSubentPath& id) const;
    
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;

    virtual Acad::ErrorStatus   subIntersectWith(
                                    const AcDbEntity*   ent,
                                    AcDb::Intersect     intType,
                                    AcGePoint3dArray&   points,
                                    Adesk::GsMarker     thisGsMarker  = 0,
                                    Adesk::GsMarker     otherGsMarker = 0
                                ) const;
 
    virtual Acad::ErrorStatus   subIntersectWith(
                                    const AcDbEntity*   ent,
                                    AcDb::Intersect     intType,
                                    const AcGePlane&    projPlane,
                                    AcGePoint3dArray&   points,
                                    Adesk::GsMarker     thisGsMarker  = 0,
                                    Adesk::GsMarker     otherGsMarker = 0
                                ) const;
    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;

    friend class AcDbImpRasterImage;
            void                baseList() const;

private:

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them
    // private in order to prevent usage of them.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](size_t nSize) { return (void*)0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) { return (void*)0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

    RasterImageImp*         mpImp;
    static ClassVersion     mVersion;
};


//////////////////// inlines ////////////////////
//
//returns the implementation class pointer
inline RasterImageImp*
AcDbRasterImage::ptrImp() const
{
    return mpImp;
}

//sets the implementation class pointer
inline RasterImageImp*             
AcDbRasterImage::setPtrImp(RasterImageImp* pImp)
{
    RasterImageImp* oldImp=mpImp;
    mpImp=pImp;
    return oldImp;
}

inline ClassVersion
AcDbRasterImage::classVersion()
{   return mVersion; }

inline void 
pixelToModel(
  const AcGeMatrix3d&   pixToMod,
  const AcGePoint2d&    pixPt,
  AcGePoint3d&          modPt)
{
    // Transform pixel coordinates to model space.
    //
    modPt.set(pixPt.x, pixPt.y, 0);
    modPt.transformBy(pixToMod);
}

inline void 
modelToPixel(
  const AcGeMatrix3d&   modToPix,
  const AcGePoint3d&    modPt,
  AcGePoint2d&          pixPt)
{
    // Transform model coordinates to pixel space.
    //
    AcGePoint3d modelPt = modPt;
    modelPt.transformBy(modToPix);
    pixPt.set(modelPt.x, modelPt.y);
}

inline void
modelToPixel(
  const AcGeVector3d& viewDir,
  const AcGeMatrix3d& modToPix,
  const AcGePlane& plane,
  const AcGePoint3d& modPt,
  AcGePoint2d& pixPt)
{
    // Project the point in the viewpoint direction
    // onto the plane of the image.
    //
    AcGePoint3d ptOnPlane = modPt.project(plane, viewDir);
    ptOnPlane.transformBy(modToPix);
    pixPt.set(ptOnPlane.x, ptOnPlane.y);
}


#pragma warning( default : 4275 ) 

#pragma pack (pop)
#endif // __IMGENT_H
