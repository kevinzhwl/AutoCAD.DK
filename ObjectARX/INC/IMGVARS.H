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
#ifndef __IMGVARS_H
#define __IMGVARS_H

#include "dbmain.h"
#include "imgdef.h"

// Opaque types
//
class AcDbImpRasterVariables;

// Silence compiler
//
#pragma warning( disable : 4275 ) 

class 
#ifdef ISM_API_LIBRARY
__declspec(dllexport) 
#else
__declspec(dllimport)
#endif
AcDbRasterVariables : public AcDbObject
{
public:

    static ClassVersion        classVersion();

	ACRX_DECLARE_MEMBERS(AcDbRasterVariables);

	// Enums, for the allowable variable values
	enum FrameSettings {
		kImageFrameInvalid = -1,
		kImageFrameOff   = 0,
		kImageFrameAbove = 1,
		kImageFrameBelow = 2
	};
	enum ImageQuality {
		kImageQualityInvalid = -1,
		kImageQualityDraft = 0,
		kImageQualityHigh  = 1
	};

    static AcDbRasterVariables* create(); 
								AcDbRasterVariables();
	virtual						~AcDbRasterVariables();

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;

	virtual FrameSettings		imageFrame() const;
	virtual Acad::ErrorStatus	setImageFrame( FrameSettings value );

	virtual ImageQuality		imageQuality() const;
	virtual Acad::ErrorStatus	setImageQuality( ImageQuality value );

	virtual AcDbRasterImageDef::Units
								userScale() const;
	virtual Acad::ErrorStatus	setUserScale(
									AcDbRasterImageDef::Units units );

	static AcDbRasterVariables*	openRasterVariables(
									AcDb::OpenMode mode,
									AcDbDatabase* pDatabase = 0
								);

private:

	// Data members
	//
	AcDbImpRasterVariables*		mpImp;
    static ClassVersion         mVersion;
};

inline ClassVersion
AcDbRasterVariables::classVersion()
{   return mVersion; }

#pragma warning( default : 4275 ) 


#endif  // __IMGVARS_H
