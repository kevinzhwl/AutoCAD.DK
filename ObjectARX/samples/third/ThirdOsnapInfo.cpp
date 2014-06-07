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
#pragma warning( disable : 4101 )  // Disable warning message for unreferenced local variables

#include <dbpl.h>
#include <dbcurve.h>
#include <dbosnap.h>

#include "ThirdOsnapInfo.h"

extern bool bSnapToSegments;

ACRX_NO_CONS_DEFINE_MEMBERS( AsdkThirdOsnapInfo, AcDbCustomOsnapInfo );

Acad::ErrorStatus
AsdkThirdOsnapEntityInfo::getOsnapInfo(
	AcDbEntity*				pickedObject,
	int						gsSelectionMark,
	const AcGePoint3d&		pickPoint,
	const AcGePoint3d&		lastPoint,
	const AcGeMatrix3d&		viewXform,
	AcArray<AcGePoint3d>&	snapPoints,
	AcArray<int>&			geomIdsForPts,
	AcArray<AcGeCurve3d*>&	snapCurves,
	AcArray<int>&			geomIdsForLines)
{
    // Base definition with no functionality
    return Acad::eOk;
}

Acad::ErrorStatus
AsdkThirdOsnapCurveInfo::getOsnapInfo(
	AcDbEntity*				pickedObject,
	int						gsSelectionMark,
	const AcGePoint3d&		pickPoint,
	const AcGePoint3d&		lastPoint,
	const AcGeMatrix3d&		viewXform,
	AcArray<AcGePoint3d>&	snapPoints,
	AcArray<int>&			geomIdsForPts,
	AcArray<AcGeCurve3d*>&	snapCurves,
	AcArray<int>&			geomIdsForLines)
{
    // Generic curve function for all AcDbCurves (except AcDbPolylines)

    // Protocol Extension insures that the following assertion is always
    // true, but check in non-prod versions just to be safe.
    assert( pickedObject->isKindOf( AcDbCurve::desc() ));

    // but in production, a hard cast is fastest
    AcDbCurve *pCurve = (AcDbCurve*)pickedObject;

    double startParam, endParam;
    AcGePoint3d pt;

    assert( Acad::eOk == pCurve->getStartParam( startParam ));
    assert( Acad::eOk == pCurve->getEndParam( endParam ));
    assert( Acad::eOk == pCurve->getPointAtParam( startParam + ((endParam - startParam) / 3), pt ));
    snapPoints.append( pt );
    assert( Acad::eOk == pCurve->getPointAtParam( startParam + ((endParam - startParam) * 2 / 3), pt ));
    snapPoints.append( pt );
    if ( pCurve->isClosed() )
    {
        assert( Acad::eOk == pCurve->getStartPoint( pt ));
        snapPoints.append( pt );
    }
    return Acad::eOk;
}

Acad::ErrorStatus
AsdkThirdOsnapPolylineInfo::getOsnapInfo(
	AcDbEntity*				pickedObject,
	int						gsSelectionMark,
	const AcGePoint3d&		pickPoint,
	const AcGePoint3d&		lastPoint,
	const AcGeMatrix3d&		viewXform,
	AcArray<AcGePoint3d>&	snapPoints,
	AcArray<int>&			geomIdsForPts,
	AcArray<AcGeCurve3d*>&	snapCurves,
	AcArray<int>&			geomIdsForLines)
{
    // Specialised implementation for AcDbPolylines:
    //  Parametrisation of AcDbPolylines is different: each whole numbered paramater appears
    //  at a vertex, so we cannot simply divide by three to get the correct parameter.

    // Protocol Extension insures that the following assertion is always
    // true, but check in non-prod versions just to be safe.
    assert( pickedObject->isKindOf( AcDbPolyline::desc() ));

    // but in production, a hard cast is fastest
    AcDbPolyline *pPline = (AcDbPolyline*)pickedObject;

    if ( bSnapToSegments )
    {
        // Snap to a third of each of the segments
        unsigned int numSegs = pPline->numVerts() - 1;
        AcGeLineSeg3d segLn;
        AcGeCircArc3d segArc;
        double startParam, endParam, newParam, dist;
        AcGePoint3d pt;

        for ( unsigned int idx = 0; idx < numSegs; idx++ )
        {
            switch( pPline->segType( idx ))
            {
            case AcDbPolyline::kLine:
                assert( Acad::eOk == pPline->getLineSegAt( idx, segLn ));
                startParam = segLn.paramOf( segLn.startPoint() );
                endParam = segLn.paramOf( segLn.endPoint() );
                snapPoints.append( segLn.evalPoint( startParam + ((endParam - startParam) / 3 )));
                snapPoints.append(  segLn.evalPoint( startParam + ((endParam - startParam) * 2 / 3 )));
                break;
            case AcDbPolyline::kArc:
                assert( Acad::eOk == pPline->getArcSegAt( idx, segArc ));
                startParam = segArc.paramOf( segArc.startPoint() );
                endParam = segArc.paramOf( segArc.endPoint() );
                dist = segArc.length( startParam, endParam );
                newParam = segArc.paramAtLength( startParam, dist / 3 );
                snapPoints.append( segArc.evalPoint( newParam ));
                newParam = segArc.paramAtLength( startParam, dist * 2 / 3 );
                snapPoints.append( segArc.evalPoint( newParam ));
                break;
            default:
                break;
            }
        }
    }
    else {
        double endParam;
        AcGePoint3d pt;
        double dist;

        assert( Acad::eOk == pPline->getEndParam( endParam ));
        assert( Acad::eOk == pPline->getDistAtParam( endParam, dist ));
        assert( Acad::eOk == pPline->getPointAtDist( dist / 3, pt ));
        snapPoints.append( pt );
        assert( Acad::eOk == pPline->getPointAtDist( dist * 2 / 3, pt ));
        snapPoints.append( pt );
        if ( pPline->isClosed() )
        {
            assert( Acad::eOk == pPline->getStartPoint( pt ));
            snapPoints.append( pt );
        }
    }
    return Acad::eOk;
}
