// (C) Copyright 1996-1997 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// Edge and curve dump utilities.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// ObjectARX support
#include "rxobject.h"

// AcGe support
#include "gegbl.h"
#include "geintrvl.h"
#include "gepnt3d.h"
#include "gecurv3d.h"
#include "geextc3d.h"
#include "gelent3d.h"
#include "geline3d.h"
#include "geray3d.h"
#include "gelnsg3d.h"
#include "gearc3d.h"
#include "geell3d.h"
#include "gesent3d.h"
#include "genurb3d.h"

// AcBr support 
#include "brgbl.h"
#include "bredge.h"
#include "brvtx.h"

// AcBr sample app support
#include "brreport.h"
#include "brgeutl.h"
#include "bredump.h"
#include "brvdump.h"

// Abbreviations
#include "gegblabb.h"


AcBr::ErrorStatus
edgeDump(const AcBrEdge& edgeEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Verify that AcBr was explicitly and not implicitly loaded,
	// by testing ObjectARX functions (which are unavailable unless
	// explicitly loaded)
    if (edgeEntity.isA() == NULL) {
        ads_printf("\n edgeDump: AcBrEntity::isA() failed\n");
        return returnValue;
    }
    if (!edgeEntity.isKindOf(AcBrEdge::desc())) {
        ads_printf("\n edgeDump: AcBrEntity::isKindOf() failed\n");
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)(&edgeEntity);
	AcBrFace* pFace = AcBrFace::cast(entClass);  
	if (pFace != NULL) {
		ads_printf("\n edgeDump: AcBrEntity::cast() failed\n");
        return returnValue;
	} 

	AcGe::EntityId entId;
	returnValue = edgeEntity.getCurveType(entId);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEdge::getCurveType:");
        errorReport(returnValue);
		return returnValue;
	}  

	AcGeCurve3d* curveGeometry = NULL;
    AcGeCurve3d* nativeGeometry = NULL;

	returnValue = getNativeCurve(edgeEntity, curveGeometry, nativeGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in getNativeCurve:");
		errorReport(returnValue);
        if (curveGeometry != NULL) delete curveGeometry;
        if (nativeGeometry != NULL) delete nativeGeometry;
        return returnValue;
	}

	switch (entId) {
    case(kLine3d):
	{ 
		ads_printf("\nCurve Type: Line\n");
        AcGeLine3d* lineGeometry = (AcGeLine3d*)nativeGeometry;
        AcGePoint3d pt = lineGeometry->pointOnLine();
        AcGeVector3d dir = lineGeometry->direction();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" Point on Line is (");
		ads_printf ("%lf , ", pt.x);	
		ads_printf ("%lf , ", pt.y);
		ads_printf ("%lf ", pt.z);
		ads_printf(")\n");	
		ads_printf(" Line direction is (");
		ads_printf ("%lf , ", dir.x);	
		ads_printf ("%lf , ", dir.y);
		ads_printf ("%lf ", dir.z);
		ads_printf(")\n");	
		ads_printf("Curve Definition Data End\n");
		break;
    }

	case(kRay3d):
	{ 
		ads_printf("\nCurve Type: Ray\n");
        AcGeRay3d* rayGeometry = (AcGeRay3d*)nativeGeometry;
        AcGePoint3d pt = rayGeometry->pointOnLine();
        AcGeVector3d dir = rayGeometry->direction();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" Point on Ray is (");
		ads_printf ("%lf , ", pt.x);	
		ads_printf ("%lf , ", pt.y);
		ads_printf ("%lf ", pt.z);
		ads_printf(")\n");	
		ads_printf(" Ray direction is (");
		ads_printf ("%lf , ", dir.x);	
		ads_printf ("%lf , ", dir.y);
		ads_printf ("%lf ", dir.z);
		ads_printf(")\n");	
		ads_printf("Curve Definition Data End\n");
		break;
    }

    case(kLineSeg3d):
	{ 
		ads_printf("\nCurve Type: Line Segment\n");
        AcGeLineSeg3d* segGeometry = (AcGeLineSeg3d*)nativeGeometry;
        AcGePoint3d pt = segGeometry->pointOnLine();
        AcGeVector3d dir = segGeometry->direction();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" Point on Line Segment is (");
		ads_printf ("%lf , ", pt.x);	
		ads_printf ("%lf , ", pt.y);
		ads_printf ("%lf ", pt.z);
		ads_printf(")\n");	
		ads_printf(" Line Segment direction is (");
		ads_printf ("%lf , ", dir.x);	
		ads_printf ("%lf , ", dir.y);
		ads_printf ("%lf ", dir.z);
		ads_printf(")\n");	
		ads_printf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		ads_printf("\nCurve Subset Data Begin:\n");
        if (segGeometry->hasStartPoint(pt1)) {
            ads_printf("\n Line Segment start point is(");
    		ads_printf ("%lf , ", pt1.x);	
    		ads_printf ("%lf , ", pt1.y);
    		ads_printf ("%lf ", pt1.z);
    		ads_printf(")\n");	
        }
        if (segGeometry->hasEndPoint(pt2)) {
            ads_printf("\n Line Segment end point is(");
    		ads_printf ("%lf , ", pt2.x);	
    		ads_printf ("%lf , ", pt2.y);
    		ads_printf ("%lf ", pt2.z);
    		ads_printf(")\n");	
        }
		ads_printf("Curve Subset Data End\n");
		break;
    }

	case(kEllipArc3d):
    {
		ads_printf("\nCurve Type: Elliptic Arc\n");
        AcGeEllipArc3d* ellipGeometry = (AcGeEllipArc3d*)nativeGeometry;
        AcGePoint3d centre = ellipGeometry->center();
        AcGePoint3d start = ellipGeometry->startPoint();
        AcGePoint3d end = ellipGeometry->endPoint();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" Elliptic Arc centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Arc major radius is %lf\n", ellipGeometry->majorRadius());
		ads_printf(" Elliptic Arc minor radius is %lf\n", ellipGeometry->minorRadius());
		ads_printf(" Elliptic Arc start angle is %lf\n", ellipGeometry->startAng());
		ads_printf(" Elliptic Arc end angle is %lf\n", ellipGeometry->endAng());
		ads_printf(" Elliptic Arc start point  is (");
		ads_printf ("%lf , ", start.x);	
		ads_printf ("%lf , ", start.y);
		ads_printf ("%lf ", start.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Arc end point is (");
		ads_printf ("%lf , ", end.x);	
		ads_printf ("%lf , ", end.y);
		ads_printf ("%lf ", end.z);
		ads_printf(")\n");	
		ads_printf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		ads_printf("\nCurve Subset Data Begin:\n");
        if (ellipGeometry->hasStartPoint(pt1)) {
            ads_printf("\n Elliptic Arc start point is(");
    		ads_printf ("%lf , ", pt1.x);	
    		ads_printf ("%lf , ", pt1.y);
    		ads_printf ("%lf ", pt1.z);
    		ads_printf(")\n");	
        }
        if (ellipGeometry->hasEndPoint(pt2)) {
            ads_printf("\n Elliptic Arc end point is(");
    		ads_printf ("%lf , ", pt2.x);	
    		ads_printf ("%lf , ", pt2.y);
    		ads_printf ("%lf ", pt2.z);
    		ads_printf(")\n");	
        }
		ads_printf("Curve Subset Data End\n");
		break;
    }

	case(kCircArc3d):
    {
		ads_printf("\nCurve Type: Circular Arc\n");
        AcGeCircArc3d* circGeometry = (AcGeCircArc3d*)nativeGeometry;
        AcGePoint3d centre = circGeometry->center();
        AcGePoint3d start = circGeometry->startPoint();
        AcGePoint3d end = circGeometry->endPoint();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" Circular Arc centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Circular Arc radius is %lf\n", circGeometry->radius());
		ads_printf(" Circular Arc start angle is %lf\n", circGeometry->startAng());
		ads_printf(" Circular Arc end angle is %lf\n", circGeometry->endAng());
		ads_printf(" Circular Arc start point  is (");
		ads_printf ("%lf , ", start.x);	
		ads_printf ("%lf , ", start.y);
		ads_printf ("%lf ", start.z);
		ads_printf(")\n");	
		ads_printf(" Circular Arc end point is (");
		ads_printf ("%lf , ", end.x);	
		ads_printf ("%lf , ", end.y);
		ads_printf ("%lf ", end.z);
		ads_printf(")\n");	
		ads_printf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		ads_printf("\nCurve Subset Data Begin:\n");
        if (circGeometry->hasStartPoint(pt1)) {
            ads_printf("\n Circular Arc start point is(");
    		ads_printf ("%lf , ", pt1.x);	
    		ads_printf ("%lf , ", pt1.y);
    		ads_printf ("%lf ", pt1.z);
    		ads_printf(")\n");	
        }
        if (circGeometry->hasEndPoint(pt2)) {
            ads_printf("\n Circular Arc end point is(");
    		ads_printf ("%lf , ", pt2.x);	
    		ads_printf ("%lf , ", pt2.y);
    		ads_printf ("%lf ", pt2.z);
    		ads_printf(")\n");	
        }
		ads_printf("Curve Subset Data End\n");
		break;
    }

	case(kNurbCurve3d):
    {
		ads_printf("\nCurve Type: NURB Curve\n");
        AcGeNurbCurve3d* nurbGeometry = (AcGeNurbCurve3d*)nativeGeometry;
		int nCtrlPts = nurbGeometry->numControlPoints();
		int nKnots = nurbGeometry->numKnots();
		int nWeights = nurbGeometry->numWeights();
		ads_printf("\nCurve Definition Data Begin:\n");
		ads_printf(" NURB Curve degree is %d\n", nurbGeometry->degree());
		ads_printf(" NURB Curve order is %d\n", nurbGeometry->order());
		ads_printf(" NURB Curve number of control points is %d\n", nCtrlPts);
        int i;
		for(i=0; i<nCtrlPts; i++) {
			ads_printf("\n ***Control point [%d] (%lf, %lf)\n", i,
				nurbGeometry->controlPointAt(i).x, nurbGeometry->controlPointAt(i).y);
		}
		ads_printf(" NURB Curve number of knots is %d\n", nKnots);
	   	for (i=0; i<nKnots; i++) {
			ads_printf("\n ***Knot point [%d] %lf\n", i, nurbGeometry->knotAt(i));
		}
		ads_printf(" NURB Curve number of weights is %d\n", nWeights);
		for (i=0; i<nWeights; i++) {
			ads_printf("\n ***Weight [%d] %lf\n", i, nurbGeometry->weightAt(i));
		}	  
		ads_printf("Curve Definition Data End\n");
        AcGePoint3d pt1, pt2;
		ads_printf("\nCurve Subset Data Begin:\n");
        if (nurbGeometry->hasStartPoint(pt1)) {
            ads_printf("\n NURB Curve start point is(");
    		ads_printf ("%lf , ", pt1.x);	
    		ads_printf ("%lf , ", pt1.y);
    		ads_printf ("%lf ", pt1.z);
    		ads_printf(")\n");	
        }
        if (nurbGeometry->hasEndPoint(pt2)) {
            ads_printf("\n NURB Curve end point is(");
    		ads_printf ("%lf , ", pt2.x);	
    		ads_printf ("%lf , ", pt2.y);
    		ads_printf ("%lf ", pt2.z);
    		ads_printf(")\n");	
        }
		ads_printf("Curve Subset Data End\n");
		break;
    }

	default:
		ads_printf("\nCurve Type: Unexpected Non Curve\n");
		return AcBr::eUnsuitableGeometry;
		break;
	} // end switch(entId)	
	
    if (nativeGeometry != NULL) delete nativeGeometry;

    // Evaluate the curve 
	AcGeInterval intrvl;
	((AcGeExternalCurve3d*)curveGeometry)->getInterval(intrvl);
    // Make sure the interval is legal and bounded
    if ((intrvl.isBounded()) && (intrvl.length() >= 0.0)) {
		double midParam = intrvl.lowerBound() + (intrvl.length() / 2.0);
		AcGePoint3d pointOnCurve =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(midParam);
		AcGePoint3d startPoint =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(intrvl.lowerBound());
		AcGePoint3d endPoint =
			((AcGeExternalCurve3d*)curveGeometry)->evalPoint(intrvl.upperBound());
		ads_printf("\nCurve Evaluation Begin:\n");
		ads_printf(" Parameterisation is (");
        ads_printf("%lf, ", intrvl.lowerBound());
        ads_printf("%lf ", intrvl.upperBound());
        ads_printf(")\n");
		ads_printf(" Parameter space mid-point is %lf\n", midParam);
		ads_printf(" Point on curve is (");
		ads_printf ("%lf , ", pointOnCurve.x);	
		ads_printf ("%lf , ", pointOnCurve.y);
		ads_printf ("%lf ", pointOnCurve.z);
		ads_printf(")\n");	
		ads_printf(" Curve start point is (");
		ads_printf ("%lf , ", startPoint.x);	
		ads_printf ("%lf , ", startPoint.y);
		ads_printf ("%lf ", startPoint.z);
		ads_printf(")\n");	
		ads_printf(" Curve end point is (");
		ads_printf ("%lf , ", endPoint.x);	
		ads_printf ("%lf , ", endPoint.y);
		ads_printf ("%lf ", endPoint.z);
		ads_printf(")\n");	
		ads_printf("Curve Evaluation End\n");
    }

    if (curveGeometry != NULL) delete curveGeometry;

	Adesk::Boolean oriented;
	returnValue = edgeEntity.getOrientToCurve(oriented);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEdge::getOrientToCurve:");
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? ads_printf("\nCurve Orientation is Positive\n")
	    : ads_printf("\nCurve Orientation is Negative\n");

	AcBrVertex startVertex;
	returnValue	= edgeEntity.getVertex1(startVertex);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEdge::getVertex1:");
        errorReport(returnValue);
        return returnValue;
	}
	if (!startVertex.isNull()) {
		ads_printf("\nCoordinate of vertex1 : ");
		returnValue	= vertexDump(startVertex);
		if (returnValue != AcBr::eOk) {
		    ads_printf("\n Error in vertexDump:");
		    errorReport(returnValue);
			return returnValue;
		}
	}
	
	AcBrVertex endVertex;
	returnValue	= edgeEntity.getVertex2(endVertex);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEdge::getVertex2:");
        errorReport(returnValue);
        return returnValue;
	}
	if (!endVertex.isNull()) {
		ads_printf("\nCoordinate of vertex2: ");
		returnValue = vertexDump(endVertex);
		if (returnValue != AcBr::eOk) {
		    ads_printf("\n Error in vertexDump:");
		    errorReport(returnValue);
			return returnValue;
		}
	}

	return returnValue;
}
