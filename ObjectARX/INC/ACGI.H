#ifndef _ACGI_H
#define _ACGI_H 1
//
// (C) Copyright 1994-1997 by Autodesk, Inc. 
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
// This is the Graphics Interface for view independent and dependent
// elaboration of AcDb Entities.
//
// The AutoCAD Graphics Interface (AcGi) is a set of objects comprising 
// an API for elaborating the graphics representation of new AutoCAD
// entitites.  These objects support many geometric primitives, 
// transformation matrix querying, and graphical attributes. 
 
// Required for RX
//
#define ACGI_SERVICES  /*MSG0*/"AcGiServices"


// These are the current kinds of viewport regeneration modes.
// This mode is not settable by the user, but it can be queried 
// in case you need to take different actions for different
// regeneration modes.
//
typedef enum {
    eAcGiRegenTypeInvalid = 0,
    kAcGiStandardDisplay = 2,
    kAcGiHideOrShadeCommand,
    kAcGiRenderCommand,
    kAcGiSaveWorldDrawForR12,
    kAcGiSaveWorldDrawForProxy
} AcGiRegenType;

// These are the current face filling modes
//
typedef enum {
     kAcGiFillAlways = 1,
     kAcGiFillNever
} AcGiFillType;

// These are the edge visibility types
//
typedef enum {
    kAcGiInvisible = 0,
    kAcGiVisible,
    kAcGiSilhouette
} AcGiVisibility;

// These are the types of arcs
//
typedef enum {
    kAcGiArcSimple = 0,                 // just the arc (not fillable)
    kAcGiArcSector,                     // area bounded by the arc and its center of curvature
    kAcGiArcChord                       // area bounded by the arc and its end points
} AcGiArcType;

// These are the possible types of vertex orientation 
// 
typedef enum {
    kAcGiCounterClockwise = -1,
    kAcGiNoOrientation = 0,
    kAcGiClockwise = 1
} AcGiOrientationType;

// This signifies how to calculate maximum deviation for tesselation
//
typedef enum {
    kAcGiMaxDevForCircle = 0,
    kAcGiMaxDevForCurve,
    kAcGiMaxDevForBoundary,
    kAcGiMaxDevForIsoline,
    kAcGiMaxDevForFacet
} AcGiDeviationType;

// Raster image organization
//
typedef enum {
    kAcGiBitonal,
    kAcGiPalette,
    kAcGiGray,
    kAcGiRGBA,
    kAcGiBGRA,
    kAcGiARGB,
    kAcGiABGR,
    kAcGiBGR,
    kAcGiRGB                              
} AcGiImageOrg;

// Raster image orientation
//
typedef enum {
    kAcGiXLeftToRightTopFirst,
    kAcGiXLeftToRightBottomFirst,
    kAcGiXRightToLeftTopFirst,
    kAcGiXRightToLeftBottomFirst,
    kAcGiYTopToBottomLeftFirst,
    kAcGiYTopToBottomRightFirst,
    kAcGiYBottomToTopLeftFirst,
    kAcGiYBottomToTopRightFirst
} AcGiImageOrient;

#include "rxobject.h"
#include "dbpl.h"
#include "gemat3d.h"
#include "gemat2d.h"
#include "gepnt2d.h"
#include "acdb.h"

struct AcGiSentScanLines 
{
    Adesk::Int8* mpPixelBuffer;            // one pointer per scan line
    Adesk::UInt32 mRowBytes;               // number of bytes per scan line
    void*  	 mpImageId;                // image id ptr
    Adesk::Int16 mIsCancelled;             // boolean: user cancelled
    Adesk::Int16 mHasFailed;               // boolean: request failed
};

struct AcGiRequestScanLines 
{
    Adesk::UInt32 mPixelMinX;               // requested pixel corners
    Adesk::UInt32 mPixelMinY;
    Adesk::UInt32 mPixelMaxX;
    Adesk::UInt32 mPixelMaxY;
    AcGePoint2d  mLowerLeft;               // requested lower left corner
    AcGePoint2d  mUpperRight;              // requested upper right corner
    void         *mpImageId;               // image handle
    AcGiImageOrg mImageOrg;                // enum type: palette, RGB 
    AcGiImageOrient mImageOrient;          // enum type
    Adesk::Int16 mWindowId;                // acad window id
    Adesk::Int16 mColorDepth;              // bits per pixel
    union {
        Adesk::Int16 mBackgroundIndex;
        Adesk::Int8 mBackgroundRGB[3];
    } mBackgroundColor;                    // current background color
    union {
        Adesk::Int16 mTransparentIndex;
        Adesk::Int8 mTransparentRGB[3];
    } mTransparentColor;                   // current background color
    union {
        Adesk::Int16 mEntityIndex;
        Adesk::Int8 mEntityRGB[3];
    } mEntityColor;                        // bitonal image foregrnd color
    Adesk::Int32 mPaletteIncarnation;      // unique palette indentifier
    Adesk::Int8* mpPalette;                // pointer to 256 RGB triples
    Adesk::Int16 mIsDisplay;               // boolean: TRUE=dsply, FALSE=hrdcpy
    Adesk::Int16 mRasterRatio;             // raster resolution
    AcGeMatrix2d mPixelToDc;               // source pixel-to-dc transform
};

class AcGiSubEntityTraits;
class AcGiSubEntityTraitsImp;
class AcGiWorldGeometry;
class AcGiViewport;
class AcGiViewportGeometry;
class AcGiImpEdgeData;
class AcGiImpFaceData;
class AcGiImpVertexData;
class AcGiImpTextStyle;
class AcGiTextStyle;
class AcGiEdgeData;
class AcGiFaceData;
class AcGiVertexData;

class OwnerDraw;

class AcGiWorldDraw: public AcRxObject
//
// This class provides an API for generating graphics
// in model coordinates.  These graphics cannot be
// controlled by any viewport, as can AcGiViewportDraw.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldDraw);
    virtual AcGiRegenType           regenType() const = 0;
    virtual Adesk::Boolean          regenAbort() const = 0;
    virtual AcGiSubEntityTraits&    subEntityTraits() const = 0;
    virtual AcGiWorldGeometry&      geometry() const = 0;
    virtual Adesk::Boolean          isDragging() const = 0;
    virtual double                  deviation(const AcGiDeviationType, 
                                              const AcGePoint3d&) const = 0;
    virtual Adesk::UInt32           numberOfIsolines() const = 0;
};

class AcGiViewportDraw: public AcRxObject 
//
// This class provides an API for generating graphics
// that can be sent to a particular viewport.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportDraw);
    virtual AcGiRegenType        regenType() const = 0;
    virtual Adesk::Boolean       regenAbort() const = 0;
    virtual AcGiViewport&        viewport() const = 0;
    virtual AcGiSubEntityTraits& subEntityTraits() const = 0;
    virtual AcGiViewportGeometry& geometry() const = 0;
    virtual Adesk::Boolean       isDragging() const = 0;
    virtual double               deviation(const AcGiDeviationType, 
                                           const AcGePoint3d&) const = 0;
    virtual Adesk::UInt32        numberOfIsolines() const = 0;
    virtual Adesk::UInt32        sequenceNumber() const = 0;
    virtual Adesk::Boolean       isValidId(const Adesk::UInt32 acgiId) const =0;
    virtual AcDbObjectId         viewportObjectId() const = 0;
};

class AcGiViewport: public AcRxObject 
//
// This class returns viewport info.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewport);

    // Get various view transformations.
    //
    virtual void getModelToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToModelTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToWorldTransform(AcGeMatrix3d&) const = 0;

    // Perspective information.
    //
    virtual Adesk::Boolean isPerspective() const = 0;
    virtual Adesk::Boolean doPerspective(AcGePoint3d&) const = 0;
    virtual Adesk::Boolean doInversePerspective(AcGePoint3d&) const = 0;

    // Pixel information.
    //
    virtual void getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,
                                  AcGePoint2d& pixelArea) const = 0;

    // Camera information.
    //
    virtual void getCameraLocation(AcGePoint3d& loc_vec) const = 0;
    virtual void getCameraTarget(AcGePoint3d& targ_vec) const = 0;
    virtual void getCameraUpVector(AcGeVector3d& up_vec) const = 0;

    // Viewport information.
    //
    virtual Adesk::UInt32 viewportId() const = 0;
    virtual Adesk::Int16  acadWindowId() const = 0;
    virtual void getViewportDcCorners(AcGePoint2d& lower_left,
                                      AcGePoint2d& upper_right) const = 0;
    virtual Adesk::Boolean getFrontAndBackClipValues(Adesk::Boolean& clip_front,
                                         Adesk::Boolean& clip_back,
                                         double& front,
                                         double& back) const = 0;
};

class AcGiSubEntityTraits: public AcRxObject 
//
// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiSubEntityTraits);

    // Set properties of drawn objects.
    //
    virtual void setColor(const Adesk::UInt16 color) = 0;
    virtual void setLayer(const AcDbObjectId layerId) = 0;
    virtual void setLineType(const AcDbObjectId linetypeId) = 0;
    virtual void setSelectionMarker(const Adesk::Int32 markerId) = 0;
    virtual void setFillType(const AcGiFillType) = 0;

    // Return current settings.
    //
    virtual Adesk::UInt16       color() const = 0;
    virtual AcDbObjectId        layerId() const = 0;
    virtual AcDbObjectId        lineTypeId() const = 0;
    virtual AcGiFillType        fillType() const = 0;
};

class AcGiWorldGeometry: public AcRxObject 
//
// This class contains the view independent, model coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldGeometry);

    // Coordinate transformations.
    //
    virtual void getModelToWorldTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToModelTransform(AcGeMatrix3d&) const = 0;

    virtual void setExtents(AcGePoint3d *pNewExtents) const = 0;

    // For drawing various primitives.
    //
    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal) const = 0;
    virtual Adesk::Boolean  circle(const AcGePoint3d&, const AcGePoint3d&,
                                   const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal,
                                   const AcGeVector3d& startVector,
                                   const double sweepAngle,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                                   const AcGePoint3d& point,
                                   const AcGePoint3d& end,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList,
				   const AcGeVector3d* pNormal = NULL) const = 0;
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList) const = 0;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL
                                 ) const = 0;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL
                                 ) const = 0;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const char* pMsg) const = 0;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const char* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle
                                 ) const = 0;

    virtual Adesk::Boolean  xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  ray(const AcGePoint3d&,
                                const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const = 0;
};

class AcGiViewportGeometry: public AcRxObject 
//
// This class contains the view dependent, model and drawing coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportGeometry);

    // Coordinate transformations.
    //
    virtual void getModelToWorldTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToModelTransform(AcGeMatrix3d&) const = 0;

    // For drawing various primitives.
    //
    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                                 const double radius,
                                 const AcGeVector3d& normal) const = 0;
    virtual Adesk::Boolean  circle(const AcGePoint3d& pt1,
                                 const AcGePoint3d& pt2,
                                 const AcGePoint3d& pt3) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                                 const double radius,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& startVector,
                                 const double sweepAngle,
                                 const AcGiArcType arcType = kAcGiArcSimple) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                                 const AcGePoint3d& point,
                                 const AcGePoint3d& end,
                                 const AcGiArcType arcType = kAcGiArcSimple) const = 0;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                                 const AcGePoint3d* pVertexList,
				 const AcGeVector3d* pNormal = NULL) const = 0;
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                                 const AcGePoint3d* pVertexList) const = 0;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL) const = 0;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf= NULL) const = 0;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const char* pMsg) const = 0;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const char* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle) const = 0;

    virtual Adesk::Boolean  xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  ray(const AcGePoint3d& start,
                                const AcGePoint3d&
) const = 0;

    virtual Adesk::Boolean  polylineEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    virtual Adesk::Boolean  polylineDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    virtual Adesk::Boolean  rasterImageDc(
                const AcGePoint3d& origin,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                const AcGeMatrix2d& pixelToDc,
                AcDbObjectId entityId,
                AcGiImageOrg imageOrg,
                Adesk::UInt32 imageWidth,
                Adesk::UInt32 imageHeight,
                Adesk::Int16 imageColorDepth,
                Adesk::Boolean transparency
                ) const = 0;

    virtual Adesk::Boolean  ownerDrawDc(
                long                       vpnumber, 
                long                       left, 
                long                       top, 
                long                       right, 
                long                       bottom, 
                const OwnerDraw*           pOwnerDraw
                ) const = 0;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const = 0;
};

class AcGiEdgeData: public AcRxObject 
//
// This class contains arrays of edge attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiEdgeData);

    ~AcGiEdgeData();
    AcGiEdgeData();

    virtual void            setColors(const short *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setLineTypes(const AcDbObjectId *linetypes);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setVisibility(const Adesk::UInt8* pVisibility);

    virtual short*          colors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual AcDbObjectId*   linetypeIds() const;
    virtual Adesk::Int32*   selectionMarkers() const;
    virtual Adesk::UInt8*   visibility() const;

private:
    AcGiImpEdgeData *mpAcGiImpEdgeData;
};

class AcGiFaceData: public AcRxObject 
//
// This class contains arrays of face attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiFaceData);

    ~AcGiFaceData();
    AcGiFaceData();
    virtual void            setColors(const short *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setSelectionMarkers(const Adesk::Int32* pSelectionMarkers);
    virtual void            setNormals(const AcGeVector3d* pNormals);
    virtual void            setVisibility(const Adesk::UInt8* vis);

    virtual short*          colors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual Adesk::Int32*   selectionMarkers() const;
    virtual AcGeVector3d*   normals() const;
    virtual Adesk::UInt8*   visibility() const;
private:
    AcGiImpFaceData *mpAcGiImpFaceData;
};

class AcGiVertexData: public AcRxObject 
//
// This class contains arrays of vertex attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiVertexData);
    ~AcGiVertexData();
    AcGiVertexData();
    virtual void setNormals(const AcGeVector3d* pNormals);
    virtual AcGeVector3d* normals() const;
    virtual void setOrientationFlag(const AcGiOrientationType oflag); 
    virtual AcGiOrientationType orientationFlag() const;

private:
    AcGiImpVertexData *mpAcGiImpVertexData;
};

class AcGiTextStyle: public AcRxObject 
// 
// This class contains methods to create and modify a text
// style object
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiTextStyle);
    ~AcGiTextStyle();
    AcGiTextStyle();

    AcGiTextStyle(
        const char*  fontName, 
        const char*  bigFontName, 
        const double textSize, 
        const double xScale, 
        const double obliqueAngle, 
        const double trPercent,

        const Adesk::Boolean isBackward,
        const Adesk::Boolean isUpsideDown,
        const Adesk::Boolean isVertical, 

        const Adesk::Boolean isOverlined,
        const Adesk::Boolean isUnderlined,
        
        const char*          styleName = NULL);

    virtual char loadStyleRec() const;
    virtual void setTextSize(const double size);
    virtual void setXScale(const double xScale);
    virtual void setObliquingAngle(const double obliquingAngle);

    virtual void setTrackingPercent(const double trPercent);

    virtual void setBackward(const Adesk::Boolean isBackward);
    virtual void setUpsideDown(const Adesk::Boolean isUpsideDown);
    virtual void setVertical(const Adesk::Boolean isVertical);

    virtual void setUnderlined(const Adesk::Boolean isUnderlined);
    virtual void setOverlined(const Adesk::Boolean isOverlined);

    virtual void setFileName(const char* fontName);
    virtual void setBigFontFileName(const char* bigFontFileName);

    virtual double textSize() const;
    virtual double xScale() const;
    virtual double obliquingAngle() const;

    virtual double trackingPercent() const;

    virtual Adesk::Boolean isBackward() const;
    virtual Adesk::Boolean isUpsideDown() const;
    virtual Adesk::Boolean isVertical() const;

    virtual Adesk::Boolean isUnderlined() const;
    virtual Adesk::Boolean isOverlined() const;

    virtual const char* fileName() const;
    virtual const char* bigFontFileName() const;

    virtual AcGePoint2d extents(const char* pStr, 
                const Adesk::Boolean penups,
                const int len,
                const Adesk::Boolean raw) const;

    virtual const char* styleName();
    virtual Acad::ErrorStatus setStyleName(const char*);
    
    virtual Acad::ErrorStatus setFont(const char* pTypeface, BOOL bold, BOOL italic, 
		                      int charset, int pitchAndFamily);
    virtual Acad::ErrorStatus font(char*& pTypeface, BOOL& bold, BOOL& italic,
	                        int& charset, int& pitchAndFamily) const;
private:
    AcGiImpTextStyle *mpAcGiImpTextStyle;
};

#endif
