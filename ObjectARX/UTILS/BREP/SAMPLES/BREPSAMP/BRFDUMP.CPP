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
// Face and surface dump utilities.


// C-RTL
#include <math.h>

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
#include "gesurf.h"
#include "geextsf.h"
#include "gexbndsf.h"
#include "geplane.h"
#include "gesphere.h"
#include "getorus.h"
#include "gecylndr.h"
#include "gecone.h"
#include "genurbsf.h"
#include "gelnsg3d.h"

// AcBr support 
#include "brgbl.h"
#include "brface.h"	

// AcBr sample app support
#include "brreport.h"
#include "brgeutl.h"
#include "brfdump.h"

// Abbreviations
#include "gegblabb.h"


// Math constants (used for evaluating external bounded surfaces)
const double kPi      = 3.14159265358979323846;
const double kTwoPi   = 6.28318530717958647692;
const double kHalfPi  = 1.57079632679489661923;


AcBr::ErrorStatus
faceDump(const AcBrFace& faceEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Verify that AcBr was explicitly and not implicitly loaded,
	// by testing ObjectARX functions (which are unavailable unless
	// explicitly loaded)
    if (faceEntity.isA() == NULL) {
        ads_printf("\n faceDump: AcBrEntity::isA() failed\n");
        return returnValue;
    }
    if (!faceEntity.isKindOf(AcBrFace::desc())) {
        ads_printf("\n faceDump: AcBrEntity::isKindOf() failed\n");
        return returnValue;
    }
	AcBrEntity* entClass = (AcBrEntity*)(&faceEntity);
	AcBrEdge* pEdge = AcBrEdge::cast(entClass);  
	if (pEdge != NULL) {
		ads_printf("\n faceDump: AcBrEntity::cast() failed\n");
        return returnValue;
	} 

	AcGe::EntityId entId;
	returnValue = faceEntity.getSurfaceType(entId);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrFace::getSurfaceType:");
		errorReport(returnValue);
        return returnValue;
	}

	AcGeSurface* surfaceGeometry = NULL;
    AcGeSurface* nativeGeometry = NULL;

	// NOTE: ignore unsuitable geometry for now, since we already know that
	// elliptic cylinders and elliptic cones are rejected by AcGe, but we can
	// still perform useful evaluations on the external bounded surface.
	returnValue = getNativeSurface(faceEntity, surfaceGeometry, nativeGeometry);  
	if ((returnValue != AcBr::eOk) && (returnValue != AcBr::eUnsuitableGeometry)) {
		ads_printf("\n Error in getNativeSurface:");
		errorReport(returnValue);
        if (surfaceGeometry != NULL) delete surfaceGeometry;
        if (nativeGeometry != NULL) delete nativeGeometry;
        return returnValue;
	}

	switch (entId) {
	case(kPlane):
	{ 
		ads_printf("\nSurface Type: Plane\n");
        AcGePlane* planeGeometry = (AcGePlane*)nativeGeometry;
        AcGePoint3d pt = planeGeometry->pointOnPlane();
        AcGeVector3d normal = planeGeometry->normal();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Point on Plane is (");
		ads_printf ("%lf , ", pt.x);	
		ads_printf ("%lf , ", pt.y);
		ads_printf ("%lf ", pt.z);
		ads_printf(")\n");	
		ads_printf(" Plane normal direction is (");
		ads_printf ("%lf , ", normal.x);	
		ads_printf ("%lf , ", normal.y);
		ads_printf ("%lf ", normal.z);
		ads_printf(")\n");	
		ads_printf("Surface Definition Data End\n");
		break;
    } 
	
	case(kSphere):
    {
		ads_printf("\nSurface Type: Sphere\n");
        AcGeSphere* sphereGeometry = (AcGeSphere*)nativeGeometry;
        AcGePoint3d centre = sphereGeometry->center();
		double ang1, ang2, ang3, ang4;
        sphereGeometry->getAnglesInU(ang1, ang2);
        sphereGeometry->getAnglesInV(ang3, ang4);
        AcGePoint3d north = sphereGeometry->northPole();
        AcGePoint3d south = sphereGeometry->southPole();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Sphere centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Sphere radius is %lf\n", sphereGeometry->radius());
		ads_printf(" Sphere start angle in U is %lf\n", ang1);
		ads_printf(" Sphere end angle in U is %lf\n", ang2);
		ads_printf(" Sphere start angle in V is %lf\n", ang3);
		ads_printf(" Sphere end angle in V is %lf\n", ang4);
		ads_printf(" Sphere north pole is (");
		ads_printf ("%lf , ", north.x);	
		ads_printf ("%lf , ", north.y);
		ads_printf ("%lf ", north.z);
		ads_printf(")\n");	
		ads_printf(" Sphere south pole is (");
		ads_printf ("%lf , ", south.x);	
		ads_printf ("%lf , ", south.y);
		ads_printf ("%lf ", south.z);
		ads_printf(")\n");	
		ads_printf("Surface Definition Data End\n");
		break;
    }
	
	case(kTorus):
    {
		ads_printf("\nSurface Type: Torus\n");
        AcGeTorus* torusGeometry = (AcGeTorus*)nativeGeometry;
        AcGePoint3d centre = torusGeometry->center();
		double ang1, ang2, ang3, ang4;
        torusGeometry->getAnglesInU(ang1, ang2);
        torusGeometry->getAnglesInV(ang3, ang4);
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Torus centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Torus major radius is %lf\n", torusGeometry->majorRadius());
		ads_printf(" Torus minor radius is %lf\n", torusGeometry->minorRadius());
		ads_printf(" Torus start angle in U is %lf\n", ang1);
		ads_printf(" Torus end angle in U is %lf\n", ang2);
		ads_printf(" Torus start angle in V is %lf\n", ang3);
		ads_printf(" Torus end angle in V is %lf\n", ang4);
		ads_printf("Surface Definition Data End\n");
		break;	
	}	
	
	case(kCylinder):
    {
		ads_printf("\nSurface Type: Circular Cylinder\n");
        AcGeCylinder* cylinderGeometry = (AcGeCylinder*)nativeGeometry;
        AcGePoint3d origin = cylinderGeometry->origin();
		double ang1, ang2;
        cylinderGeometry->getAngles(ang1, ang2);
        AcGeInterval ht;
        cylinderGeometry->getHeight(ht);
		AcGePoint2d high(0.0, ht.upperBound());
		AcGePoint3d top =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(high);
		AcGePoint2d low(0.0, ht.lowerBound());
		AcGePoint3d bot =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(low);
		AcGeLineSeg3d dist(bot, top);
        double height = dist.length();
        AcGeVector3d refAxis = cylinderGeometry->refAxis();
        AcGeVector3d symAxis = cylinderGeometry->axisOfSymmetry();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Circular Cylinder origin is (");
		ads_printf ("%lf , ", origin.x);	
		ads_printf ("%lf , ", origin.y);
		ads_printf ("%lf ", origin.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cylinder radius is %lf\n", cylinderGeometry->radius());
		ads_printf(" Circular Cylinder start angle is %lf\n", ang1);
		ads_printf(" Circular Cylinder end angle is %lf\n", ang2);
		if (cylinderGeometry->isClosedInU())
			ads_printf(" Circular Cylinder height is %lf\n", height);
        else ads_printf(" Circular Cylinder is not closed in U\n");
		ads_printf(" Circular Cylinder reference axis is (");
		ads_printf ("%lf , ", refAxis.x);	
		ads_printf ("%lf , ", refAxis.y);
		ads_printf ("%lf ", refAxis.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cylinder axis of symmetry is (");
		ads_printf ("%lf , ", symAxis.x);	
		ads_printf ("%lf , ", symAxis.y);
		ads_printf ("%lf ", symAxis.z);
		ads_printf(")\n");	
		ads_printf("Surface Definition Data End\n");
		break;
    }

	case(kCone):
    {
		ads_printf("\nSurface Type: Circular Cone\n");
        AcGeCone* coneGeometry = (AcGeCone*)nativeGeometry;
        AcGePoint3d centre = coneGeometry->baseCenter();
		double ang1, ang2;
        coneGeometry->getAngles(ang1, ang2);
        AcGeVector3d axis1 = coneGeometry->axisOfSymmetry();
        AcGeVector3d axis2 = coneGeometry->refAxis();
        AcGePoint3d apex = coneGeometry->apex();
		double cosAng, sinAng;
        coneGeometry->getHalfAngle(cosAng, sinAng);
        AcGeInterval ht;
        coneGeometry->getHeight(ht);
		AcGePoint2d high(0.0, ht.upperBound());
		AcGePoint3d top =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(high);
		AcGePoint2d low(0.0, ht.lowerBound());
		AcGePoint3d bot =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(low);
		AcGeLineSeg3d dist(bot, top);
        double height = dist.length();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Circular Cone base centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cone base radius is %lf\n", coneGeometry->baseRadius());
		ads_printf(" Circular Cone start angle is %lf\n", ang1);
		ads_printf(" Circular Cone end angle is %lf\n", ang2);
		ads_printf(" Circular Cone axis of symmetry is (");
		ads_printf ("%lf , ", axis1.x);	
		ads_printf ("%lf , ", axis1.y);
		ads_printf ("%lf ", axis1.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cone reference axis is (");
		ads_printf ("%lf , ", axis2.x);	
		ads_printf ("%lf , ", axis2.y);
		ads_printf ("%lf ", axis2.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cone apex is (");
		ads_printf ("%lf , ", apex.x);	
		ads_printf ("%lf , ", apex.y);
		ads_printf ("%lf ", apex.z);
		ads_printf(")\n");	
		ads_printf(" Circular Cone cosine of major half-angle is %lf\n", cosAng);
		ads_printf(" Circular Cone sine of major half-angle is %lf\n", sinAng);
		if (coneGeometry->isClosedInU())
			ads_printf(" Circular Cone height is %lf\n", height);
        else ads_printf(" Circular Cone is not closed in U\n");
		ads_printf("Surface Definition Data End\n");
		break;
    }
	
	case(kNurbSurface):
    {
		ads_printf("\nSurface Type: NURB Surface\n");
        AcGeNurbSurface* nurbGeometry = (AcGeNurbSurface*)nativeGeometry;
		int nCtrlPtsU = nurbGeometry->numControlPointsInU();
		int nCtrlPtsV = nurbGeometry->numControlPointsInV();
		int nKnotsU = nurbGeometry->numKnotsInU();
		int nKnotsV = nurbGeometry->numKnotsInV();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" NURB Surface degree in U is %d\n", nurbGeometry->degreeInU());
		ads_printf(" NURB Surface degree in V is %d\n", nurbGeometry->degreeInV());
		ads_printf(" NURB Surface number of control points in U is %d\n", nCtrlPtsU);
		ads_printf(" NURB Surface number of control points in V is %d\n", nCtrlPtsV);
		ads_printf(" NURB Surface number of knots in U is %d\n", nKnotsU);
		ads_printf(" NURB Surface number of knots in V is %d\n", nKnotsV);
		ads_printf("Surface Definition Data End\n");
		break;
    }
	
	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCylinder):
	{
		ads_printf("\nSurface Type: Elliptic Cylinder\n");
        AcGePoint3d p0 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, 0.0));
        AcGePoint3d p1 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kPi));
        AcGePoint3d p2 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kHalfPi));
        AcGePoint3d origin(((p0.x + p1.x) / 2.0),
			               ((p0.y + p1.y) / 2.0),
						   ((p0.z + p1.z) / 2.0));
        AcGeVector3d majAxis = p0 - origin;
        AcGeVector3d minAxis = p2 - origin;
        AcGeVector3d symAxis = (majAxis.crossProduct(minAxis)).normalize();
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Elliptic Cylinder origin is (");
		ads_printf ("%lf , ", origin.x);	
		ads_printf ("%lf , ", origin.y);
		ads_printf ("%lf ", origin.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cylinder major radius is %lf\n", majAxis.length());
		ads_printf(" Elliptic Cylinder minor radius is %lf\n", minAxis.length());
		ads_printf(" Elliptic Cylinder major axis is (");
		ads_printf ("%lf , ", majAxis.x);	
		ads_printf ("%lf , ", majAxis.y);
		ads_printf ("%lf ", majAxis.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cylinder minor axis is (");
		ads_printf ("%lf , ", minAxis.x);	
		ads_printf ("%lf , ", minAxis.y);
		ads_printf ("%lf ", minAxis.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cylinder axis of symmetry is (");
		ads_printf ("%lf , ", symAxis.x);	
		ads_printf ("%lf , ", symAxis.y);
		ads_printf ("%lf ", symAxis.z);
		ads_printf(")\n");	
		ads_printf("Surface Definition Data End\n");
		break;
	}

	// NOTE: This surface is not yet supported in AcGe, so we infer the definition
	// data by analysing evaluated data on the external bounded surface.
	case(kEllipCone):
	{
		ads_printf("\nSurface Type: Elliptic Cone\n");
        AcGePoint3d p0 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, 0.0));
        AcGePoint3d p1 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kPi));
        AcGePoint3d p2 = surfaceGeometry->evalPoint(AcGePoint2d(0.0, kHalfPi));
        AcGePoint3d p3 = surfaceGeometry->evalPoint(AcGePoint2d(1.0, 0.0));
        AcGePoint3d centre(((p0.x + p1.x) / 2.0),
			               ((p0.y + p1.y) / 2.0),
						   ((p0.z + p1.z) / 2.0));
        AcGeVector3d majAxis = p0 - centre;
        AcGeVector3d minAxis = p2 - centre;
        AcGeVector3d symAxis = (majAxis.crossProduct(minAxis)).normalize();
		double halfAng = kHalfPi - majAxis.angleTo(p3 - p0);
		ads_printf("\nSurface Definition Data Begin:\n");
		ads_printf(" Elliptic Cone base centre is (");
		ads_printf ("%lf , ", centre.x);	
		ads_printf ("%lf , ", centre.y);
		ads_printf ("%lf ", centre.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cone base major radius is %lf\n", majAxis.length());
		ads_printf(" Elliptic Cone base minor radius is %lf\n", minAxis.length());
		ads_printf(" Elliptic Cone major axis is (");
		ads_printf ("%lf , ", majAxis.x);	
		ads_printf ("%lf , ", majAxis.y);
		ads_printf ("%lf ", majAxis.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cone minor axis is (");
		ads_printf ("%lf , ", minAxis.x);	
		ads_printf ("%lf , ", minAxis.y);
		ads_printf ("%lf ", minAxis.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cone axis of symmetry is (");
		ads_printf ("%lf , ", symAxis.x);	
		ads_printf ("%lf , ", symAxis.y);
		ads_printf ("%lf ", symAxis.z);
		ads_printf(")\n");	
		ads_printf(" Elliptic Cone cosine of major half-angle is %lf\n", cos(halfAng));
		ads_printf(" Elliptic Cone sine of major half-angle is %lf\n", sin(halfAng));
		ads_printf("Surface Definition Data End\n");
		break;
	}

	default:
		ads_printf("\nSurface Type: Unexpected Non Surface\n");
		return AcBr::eUnsuitableGeometry;
	} // end switch(entId)	

    if (nativeGeometry != NULL) delete nativeGeometry;

	// Evaluate the surface - note that the u,v bounds will not consider any
	// holes in the surface. To compute a u,v zone of exclusion for evaluation,
	// check for additional (i.e., inner) loops and get the bounding boxes for
	// the loops, then convert those to parameter space boxes. There is no
	// particular guarantee that outer loop(s) are the first in the face-loop
	// list, however, and we currently have no way to query a loop to find out
	// which type it is. Still, the maximal u,v parameter range will be useful
	// for most surfaces and most evaluation purposes.
	AcGeInterval uParam;
	AcGeInterval vParam;
	((AcGeExternalBoundedSurface*)surfaceGeometry)->getEnvelope(uParam, vParam);
    // Make sure the u,v values are legal and the envelope is bounded
    if ((uParam.isBounded()) && (vParam.isBounded())) {
		AcGePoint2d midRange;
		midRange.x = uParam.lowerBound() + (uParam.length() / 2.0);
		midRange.y = vParam.lowerBound() + (vParam.length() / 2.0);
		AcGePoint3d pointOnSurface =
			((AcGeExternalBoundedSurface*)surfaceGeometry)->evalPoint(midRange);
		ads_printf("\nSurface Evaluation Begin:\n");
		ads_printf(" Parameter space bounds are ((");
        ads_printf("%lf, ", uParam.lowerBound());
        ads_printf("%lf ", uParam.upperBound());
        ads_printf("), (\n");
        ads_printf("%lf, ", vParam.lowerBound());
        ads_printf("%lf ", vParam.upperBound());
        ads_printf("))\n");
		ads_printf(" Parameter space mid-range is (");
        ads_printf(" %lf, ", midRange.x);
        ads_printf("%lf ", midRange.y);
        ads_printf(")\n");
		ads_printf(" Point on surface is (");
		ads_printf ("%lf , ", pointOnSurface.x);	
		ads_printf ("%lf , ", pointOnSurface.y);
		ads_printf ("%lf ", pointOnSurface.z);
		ads_printf(")\n");	
		ads_printf("Surface Evaluation End\n");
    }

	if (surfaceGeometry != NULL) delete surfaceGeometry;

	Adesk::Boolean oriented;
	returnValue = faceEntity.getOrientToSurface(oriented);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrFace::getOrientToSurface:");
        errorReport(returnValue);
		return returnValue;
	} 
	oriented ? ads_printf("\nSurface Orientation is Positive\n")
	    : ads_printf("\nSurface Orientation is Negative\n");

	return returnValue;
}
