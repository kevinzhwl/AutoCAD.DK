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
//  Description:   Image definition implementation classes.
//  
#ifndef __IMGDEFIM_H
#define __IMGDEFIM_H    1

#include "imgdef.h"

// Interface to the Image Engine (or equivalent) component
class 
#ifdef ISM_API_LIBRARY
__declspec(dllexport) 
#else
__declspec(dllimport)
#endif
ImagingServicesImp
{
public:

    typedef unsigned int        (*ProgressHandler)(long countRemaining);

    virtual Acad::ErrorStatus   initialize() = 0;

    // Register callback function to monitor progress of image processing
	// operation (load, save, resample etc.) and allow user to cancel.
    virtual ProgressHandler     setProgressHandler(ProgressHandler) = 0;

    // File format list
    virtual const char*         readFilterString() = 0;

    // Reads and clears the user abort flag set by the progress handler function
    // when the user aborts.  This must be called after any Image Engine operation 
    // during which the user might abort.  
    virtual Adesk::Boolean      userAborted() = 0;
};

// Interface to the AcDbRasterImageDef implementation
class 
#ifdef ISM_API_LIBRARY
__declspec(dllexport) 
#else
__declspec(dllimport)
#endif
RasterImageDefImp
{
public:

			                    RasterImageDefImp(AcDbRasterImageDef* pSelf);
    virtual                     ~RasterImageDefImp();

    AcDbRasterImageDef*         self() const;

    // Construction management
    typedef RasterImageDefImp* (*CreateInstance)(AcDbRasterImageDef* pSelf);
    typedef AcDbRasterImageDefReactor* (*CreateReactor)();

    static void                 setCreateInstance(CreateInstance);
    static CreateInstance       getCreateInstance();

    static void                 setCreateReactor(CreateReactor);
    static CreateReactor        getCreateReactor();

    // Implementation services
    static void                 setImagingServices(ImagingServicesImp*);
    static ImagingServicesImp*  getImagingServices();

    // AcDbObject overrides
    virtual Acad::ErrorStatus   subErase(Adesk::Boolean erasing) = 0;
	virtual Acad::ErrorStatus	subClose() = 0;

    Acad::ErrorStatus	        dwgInFields(AcDbDwgFiler* filer);
    Acad::ErrorStatus	        dwgOutFields(AcDbDwgFiler* filer) const;
    Acad::ErrorStatus	        dxfInFields(AcDbDxfFiler* filer);
    Acad::ErrorStatus	        dxfOutFields(AcDbDxfFiler* filer) const;

    virtual Acad::ErrorStatus	subDwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus	subDwgOutFields(AcDbDwgFiler* filer) const;

	// AcDbImpRasterImageDef-specific protocol
	virtual AcGiSentScanLines*	makeScanLines(	
                                    const AcGiRequestScanLines* pReq,
									const AcGeMatrix2d& pixToScreen,
									AcGePoint2dArray* pActiveClipBndy,     // Data will be modified!
                                    Adesk::Boolean draftQuality,
									Adesk::Boolean isTransparent,
                                    const double brightness,
                                    const double contrast,
                                    const double fade
                                ) const = 0;

    // File handling
	virtual Acad::ErrorStatus	setSourceFileName(const char* pPathName) = 0;
	virtual Acad::ErrorStatus	setActiveFileName(const char* pPathName) = 0;
	virtual const char*			searchForActivePath() = 0;
	virtual const char*			sourceFileName() const = 0;
	virtual const char*			activeFileName() const = 0;

    // Persistent load status
	virtual Acad::ErrorStatus	load() = 0;
	virtual Acad::ErrorStatus	unload() = 0;
    virtual Adesk::Boolean		isLoaded() const = 0;

    // Image attributes
    virtual Acad::ErrorStatus   setSize(const AcGeVector2d& size) = 0;
	virtual AcGeVector2d	    size() const = 0;
    virtual AcGiImageOrg	    organization() const = 0;
    virtual int			        colorDepth() const = 0;
    virtual Acad::ErrorStatus   setResolutionMMPerPixel(
                                    const AcGeVector2d& resMMPerPixel
                                ) = 0;
	virtual AcGeVector2d		resolutionMMPerPixel() const = 0;
    virtual void                setResolutionUnits(
                                    AcDbRasterImageDef::Units units
                                ) = 0;
	virtual AcDbRasterImageDef::Units resolutionUnits() const = 0;

    // File status
	virtual Acad::ErrorStatus	getFileStatus(
									CFileStatus& fileStatus
								) const = 0;
	virtual const char*	        fileType() const = 0;

    // Image instance management
	virtual int					entityCount(
									Adesk::Boolean* pbLocked
								) const = 0;
	virtual void				updateEntities() const = 0;

    // Thumbnail functions
	virtual Acad::ErrorStatus	loadThumbnail(
									Adesk::UInt16& maxWidth,
									Adesk::UInt16& maxHeight,
									Adesk::UInt8* pPalette,
									int nPaletteEntries
								) = 0;
	virtual Acad::ErrorStatus	unloadThumbnail() = 0;
	virtual void*				createThumbnailBitmap(
									BITMAPINFO*& pBitmapInfo,
									Adesk::UInt8 brightness,
									Adesk::UInt8 contrast,
									Adesk::UInt8 fade
								) = 0;

	// Image engine access
	//
	virtual IeImg*				imageCopy() const = 0;
	virtual Acad::ErrorStatus	openImage(IeImg*& pImage) = 0;
	virtual Acad::ErrorStatus	closeImage() = 0;
	virtual Acad::ErrorStatus	setImage(const IeImg* pImage, const IeFileDesc* pFileDesc) = 0;

    virtual Acad::ErrorStatus	setUndoStoreSize(unsigned int maxImages) = 0;
    virtual unsigned int		undoStoreSize() const = 0;

    // Get/set "image modified" flag
    //
    virtual Adesk::Boolean      imageModified() const = 0;
    virtual Acad::ErrorStatus   setImageModified(Adesk::Boolean modified) = 0;

protected:

    static CreateInstance       mpCreateInstance;
    static CreateReactor        mpCreateReactor;
    static ImagingServicesImp*  mpServices;
    AcDbRasterImageDef*         mpSelf;

    // Persistent data members
    //
	CString                     mSourceFile;
	AcDbRasterImageDef::Units	mResolutionUnits;
	AcGeVector2d				mResolutionMMPerPixel;
	Adesk::Boolean				mIsLoaded;
	AcGeVector2d				mCachedSize;
};

inline AcDbRasterImageDef*
RasterImageDefImp::self() const
{   return mpSelf; }

inline
RasterImageDefImp::CreateInstance
RasterImageDefImp::getCreateInstance()
{   return mpCreateInstance; }

inline
RasterImageDefImp::CreateReactor
RasterImageDefImp::getCreateReactor()
{   return mpCreateReactor; }

inline
ImagingServicesImp*
RasterImageDefImp::getImagingServices()
{   return mpServices; }


// Orientation-corrected image load utility function.
//
class IeFileDesc;
#ifdef ISM_API_LIBRARY
__declspec(dllexport) 
#else
__declspec(dllimport)
#endif
Acad::ErrorStatus	
LoadImageOriented(IeFileDesc& inFile, IeImg*& pOutImg);


#endif // __IMGDEFIM_H
