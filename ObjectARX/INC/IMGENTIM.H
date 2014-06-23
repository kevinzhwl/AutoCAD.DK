//  (C) Copyright 1996 by Autodesk, Inc.  All rights reserved.
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
#ifndef __IMGENTIM_H
#define __IMGENTIM_H

#include "imgent.h"

// Boundary points are stored in PIXEL coordinates.
// Pixel-X is column progression (col1, col2...) direction,
// Pixel-Y is row progression direction.
//
class
#ifdef ISM_API_LIBRARY
__declspec(dllexport)
#else
__declspec(dllimport)
#endif
ClipBndy
{
public:

	                            ClipBndy();
	                            ClipBndy(const ClipBndy&);

    // AcDbEntity helpers used by RasterImageImp
    //
    Acad::ErrorStatus	        dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus	        dwgOutFields(AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus	        dxfInFields(AcDbDxfFiler* pFiler);
    Acad::ErrorStatus	        dxfOutFields(AcDbDxfFiler* pFiler) const;

    Acad::ErrorStatus	        getExtent(
                                    AcGePoint2d& min, 
                                    AcGePoint2d& max
                                ) const;
	void				        clear();
	Adesk::Boolean		        isValid() const;
	Acad::ErrorStatus	        trimToRect(
                                    const AcGePoint2d& cornerA, 
                                    const AcGePoint2d& cornerB
                                );

    Acad::ErrorStatus	        setType(AcDbRasterImage::ClipBoundaryType type);
	AcDbRasterImage::ClipBoundaryType type() const;
    
    Acad::ErrorStatus	        setRectangle(const AcGePoint2d& cornerA, const AcGePoint2d& cornerB);
    Acad::ErrorStatus           setBoundary(const AcGePoint2dArray&);

	int					        length() const;	// Returns number of points in mArray.

    ClipBndy&                   transformBy(const AcGeMatrix2d& leftSide);

    // Cast operators
    //
    operator const AcGePoint2dArray& () const;
    operator const AcGePoint2dArray* () const;

private:

	// Data members
    //
	AcDbRasterImage::ClipBoundaryType mType;
    AcGePoint2dArray            mArray;
};

////////////////////// RasterImageImp ///////////////////
//
class 
#ifdef ISM_API_LIBRARY
__declspec(dllexport)
#else
__declspec(dllimport)
#endif
RasterImageImp
{
public:
    		                    RasterImageImp(AcDbRasterImage* pSelf = 0);
    virtual                     ~RasterImageImp();

	typedef RasterImageImp*		(*CreateInstance)(AcDbRasterImage* pSelf);

	static void					setCreateInstance(
									CreateInstance pCreateInstance
								);
	static CreateInstance		getCreateInstance();

	virtual AcDbRasterImage*	self() const;

    //////////////////// AcDbObject functions ////////////////////
    // 
    Acad::ErrorStatus	        dwgInFields(AcDbDwgFiler* filer);
    Acad::ErrorStatus	        dwgOutFields(AcDbDwgFiler* filer) const;

    Acad::ErrorStatus	        dxfInFields(AcDbDxfFiler* filer);
    Acad::ErrorStatus	        dxfOutFields(AcDbDxfFiler* filer) const;

    virtual Acad::ErrorStatus   subSwapIdWith(
                                    AcDbObjectId otherId,
                                    Adesk::Boolean swapXdata,
                                    Adesk::Boolean swapExtDict
                                ) = 0;

    // Override for paging or undo filing.
    //
    virtual Acad::ErrorStatus   subDwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus	subDwgOutFields(AcDbDwgFiler* filer) const;

    //////////////////// AcDbEntity methods ////////////////////
    //
    virtual Adesk::Boolean      worldDraw(AcGiWorldDraw* mode) = 0;
    virtual void		        viewportDraw(AcGiViewportDraw* mode) = 0;

    virtual void				list() const = 0;
    virtual Acad::ErrorStatus	getOsnapPoints(
								   AcDb::OsnapMode 	osnapMode,
								   int 			gsSelectionMark,
								   const AcGePoint3d& 	pickPoint,
								   const AcGePoint3d& 	lastPoint,
								   const AcGeMatrix3d& 	viewXform,
								   AcGePoint3dArray& 	snapPoints,
								   AcDbIntArray& 	    geomIds
                                ) const = 0;
    virtual Acad::ErrorStatus	getGripPoints(
								   AcGePoint3dArray& 	gripPoints,
								   AcDbIntArray& 	    osnapModes,
								   AcDbIntArray& 	    geomIds
                                ) const = 0;
    virtual Acad::ErrorStatus	moveGripPointsAt(
								   const AcDbIntArray& indices,
								   const AcGeVector3d&     offset) = 0;
    virtual Acad::ErrorStatus	getStretchPoints(
                                    AcGePoint3dArray&  stretchPoints
                                ) const = 0;
    virtual Acad::ErrorStatus	moveStretchPointsAt(
								   const AcDbIntArray& indices,
								   const AcGeVector3d&     offset
                                ) = 0;
    virtual Acad::ErrorStatus	transformBy(const AcGeMatrix3d& xform) = 0;
    virtual Acad::ErrorStatus   getTransformedCopy(
                                    const AcGeMatrix3d& xform,
						            AcDbEntity*& ent
                                ) const = 0;    
    virtual Acad::ErrorStatus   explode(AcDbVoidPtrArray& entitySet) const = 0;
    virtual Acad::ErrorStatus	getGeomExtents(AcDbExtents& extents) const = 0;
    virtual Acad::ErrorStatus   getSubentPathsAtGsMarker(
                                    AcDb::SubentType      type,
                                    int                   gsMark,
                                    const AcGePoint3d&    pickPoint,
                                    const AcGeMatrix3d&   viewXform,
                                    int&                  numPaths,
                                    AcDbFullSubentPath*&  subentPaths,
                                    int                   numInserts = 0,
				                    AcDbObjectId*         entAndInsertStack = 0
                                ) const = 0;
    virtual Acad::ErrorStatus   getGsMarkersAtSubentPath(
                                    const AcDbFullSubentPath& subPath, 
                                    AcDbIntArray&         gsMarkers
                                ) const = 0;
    virtual AcDbEntity*         subentPtr(const AcDbFullSubentPath& id) const = 0;
    virtual void				saveAs(AcGiWorldDraw* mode, AcDb::SaveType st) = 0;
    virtual Acad::ErrorStatus	intersectWith(
				                    const AcDbEntity*   ent,
				                    AcDb::Intersect     intType,
				                    AcGePoint3dArray&   points,
				                    int                 thisGsMarker  = 0,
				                    int                 otherGsMarker = 0
                                ) const = 0;
 
    virtual Acad::ErrorStatus	intersectWith(
				                    const AcDbEntity*   ent,
				                    AcDb::Intersect     intType,
				                    const AcGePlane&    projPlane,
				                    AcGePoint3dArray&      points,
				                    int                 thisGsMarker  = 0,
				                    int                 otherGsMarker = 0
                                ) const = 0;

    ////////////////////// AcDbImage specific protocol ////////////////////
    //
    virtual AcGiSentScanLines*  getScanLines(
                                    const AcGiRequestScanLines& req
                                ) const = 0;
    virtual Adesk::Boolean      freeScanLines(
                                    AcGiSentScanLines* pSSL
                                ) const = 0;


    ////////////////////// RasterImageImp specific protocol ////////////////////
    //
    virtual Acad::ErrorStatus	setImageDefId(AcDbObjectId imageId) = 0;
    virtual AcDbObjectId		imageDefId() const = 0;

	virtual	void				setReactorId(AcDbObjectId reactorId) = 0;
	virtual AcDbObjectId		reactorId() const = 0;

    // Image plane orientation
    //
	virtual Adesk::Boolean		setOrientation(
			    				   const AcGePoint3d&	origin,
			    				   const AcGeVector3d&	uCorner,
			    				   const AcGeVector3d&	vOnPlane)= 0;
    virtual void				getOrientation(
			    				   AcGePoint3d&		origin,
								   AcGeVector3d&	u,
								   AcGeVector3d&	v) const = 0;

	virtual AcGeVector2d		scale() const = 0;
	virtual AcGeVector2d		imageSize(Adesk::Boolean bGetCachedValue
											= Adesk::kFalse) const = 0;

    virtual Acad::ErrorStatus	setClipBoundaryToWholeImage(
                                    AcGeVector2d& size = AcGeVector2d(0,0)) = 0;
    virtual Acad::ErrorStatus   setClipBoundary(
									AcDbRasterImage::ClipBoundaryType type,
									const AcGePoint2dArray&
								) = 0;
    virtual const AcGePoint2dArray&
								clipBoundary() const = 0;
	virtual AcDbRasterImage::ClipBoundaryType
								clipBoundaryType() const = 0;
	virtual Adesk::Boolean		isClipped() const = 0;

    // Returns either clip boundary or image extents vertices.
	// Used for object snapping and intersection.
    //
    virtual Acad::ErrorStatus   getVertices(
                                    AcGePoint3dArray& verts
                                ) const = 0;

	// Image pixel to model coordinate transform 
    //
	virtual Acad::ErrorStatus	getPixelToModelTransform(AcGeMatrix3d&) const = 0;

	virtual void				setDisplayOpt(
									AcDbRasterImage::ImageDisplayOpt option, 
                                    Adesk::Boolean bValue
                                ) = 0;
	virtual Adesk::Boolean		isSetDisplayOpt(
									AcDbRasterImage::ImageDisplayOpt option
								) const = 0;

	virtual Acad::ErrorStatus	setBrightness( Adesk::Int8 value ) = 0;
	virtual Adesk::Int8			brightness() const = 0;
	
	virtual Acad::ErrorStatus	setContrast( Adesk::Int8 value ) = 0;
	virtual Adesk::Int8			contrast() const = 0;

	virtual Acad::ErrorStatus	setFade( Adesk::Int8 value ) = 0;
	virtual Adesk::Int8			fade() const = 0;


protected:

	AcDbRasterImage*			mpSelf;
	static CreateInstance		mpCreateInstance;

	// Persistent data members
    //
	AcDbHardPointerId			mImageDefId;    // AcDbRasterImageDef ID
	AcDbHardOwnershipId			mReactorId;     // AcDbRasterImageDefReactor ID
	AcGePoint3d					mOrigin;        // Image origin
	AcGeVector3d				mUPixel;        // Size and orientation of a single pixel
	AcGeVector3d				mVPixel;        // "-
	AcGeVector2d				mSize;          // Cached image size (in pixels)
	ClipBndy					mClipBndy;      // Clip boundary (pixel coordinates)
    Adesk::UInt16				mDisplayOpt;    // Display option flags
    Adesk::Boolean				mIsClipped;     // Clipping flag
	Adesk::Int8					mBrightness;    // Image brightness
	Adesk::Int8					mContrast;      // Image contrast
	Adesk::Int8					mFade;          // Image fade
};


//////////////////// ClipBndy inlines ////////////////////
//
inline 
AcDbRasterImage::ClipBoundaryType ClipBndy::type() const 
{   return mType; }

inline
Adesk::Boolean ClipBndy::isValid() const 
{   return mType != AcDbRasterImage::kInvalid; }

inline
int ClipBndy::length() const 
{   return mArray.length(); }

inline
ClipBndy::operator const AcGePoint2dArray& () const
{   return mArray; }

inline
ClipBndy::operator const AcGePoint2dArray* () const
{   return &mArray; }

//////////////////// RasterImageImp inlines ////////////////////
//
inline
AcDbRasterImage*
RasterImageImp::self() const
{	return mpSelf; }

inline
RasterImageImp::CreateInstance
RasterImageImp::getCreateInstance()
{	return mpCreateInstance; }

#endif  //__IMGENTIM_H
