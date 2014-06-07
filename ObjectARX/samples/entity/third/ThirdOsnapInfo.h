//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
// Abstract parent class for the protocol extensions

class AsdkThirdOsnapInfo : public AcDbCustomOsnapInfo
{
public:
    ACRX_DECLARE_MEMBERS(AsdkThirdOsnapInfo);

    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*			pickedObject,
				 int					gsSelectionMark,
				 const AcGePoint3d&		pickPoint,
				 const AcGePoint3d&		lastPoint,
				 const AcGeMatrix3d&	viewXform,
				 AcArray<AcGePoint3d>&	snapPoints,
				 AcArray<int>&			geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&			geomIdsForLines) = 0;
};

// AcDbEntity level protocol extension

class AsdkThirdOsnapEntityInfo : public AsdkThirdOsnapInfo 
{ 
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*			pickedObject,
				 int					gsSelectionMark,
				 const AcGePoint3d&		pickPoint,
				 const AcGePoint3d&		lastPoint,
				 const AcGeMatrix3d&	viewXform,
				 AcArray<AcGePoint3d>&	snapPoints,
				 AcArray<int>&			geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&			geomIdsForLines);
};

// AcDbCurve level protocol extension

class AsdkThirdOsnapCurveInfo : public AsdkThirdOsnapInfo 
{ 
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*			pickedObject,
				 int					gsSelectionMark,
				 const AcGePoint3d&		pickPoint,
				 const AcGePoint3d&		lastPoint,
				 const AcGeMatrix3d&	viewXform,
				 AcArray<AcGePoint3d>&	snapPoints,
				 AcArray<int>&			geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&			geomIdsForLines);
};

// AcDbPolyline level protocol extension

class AsdkThirdOsnapPolylineInfo : public AsdkThirdOsnapInfo
{
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*			pickedObject,
				 int					gsSelectionMark,
				 const AcGePoint3d&		pickPoint,
				 const AcGePoint3d&		lastPoint,
				 const AcGeMatrix3d&	viewXform,
				 AcArray<AcGePoint3d>&	snapPoints,
				 AcArray<int>&			geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&			geomIdsForLines);
};
