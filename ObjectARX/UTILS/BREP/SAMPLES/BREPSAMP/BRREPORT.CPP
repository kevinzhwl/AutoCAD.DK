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
// Source file for the report utilities.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcGe support
#include "gepnt3d.h"

// AcBr support 
#include "brgbl.h"
#include "brent.h"
#include "brbrep.h"
#include "brface.h"
#include "bredge.h"
#include "brvtx.h"

// AcBr sample app support
#include "brreport.h"


void
errorReport (AcBr::ErrorStatus errorCode)
{
    switch (errorCode) {
    case(AcBr::eNotImplementedYet):
		ads_printf(" Not Implemented Yet\n");
		break;
	case(AcBr::eNotApplicable):
		ads_printf(" Not Applicable\n");
		break;
	case(AcBr::eInvalidInput):
		ads_printf(" Invalid Input\n");
		break;     
	case(AcBr::eOutOfMemory):
		ads_printf(" Out of Memory\n");
		break;        
	case(AcBr::eNullObjectPointer):
		ads_printf(" Null Object Pointer\n");
		break;    
	case(AcBr::eWrongObjectType):
		ads_printf(" Wrong Object Type\n");
		break;   
	case(AcBr::eWrongSubentityType):			 
		ads_printf(" Wrong Subentity Type\n");
		break; 
	case(AcBr::eBrepChanged):
		ads_printf(" Brep Changed\n");
		break;        
    case(AcBr::eNullObjectId):
		ads_printf(" Null Object Id\n");
		break;        
    case(AcBr::eNullSubentityId):
		ads_printf(" Null Subentity Id\n");
		break;        
    case(AcBr::eObjectIdMismatch):
		ads_printf(" Object Mismatch\n");
		break;        
    case(AcBr::eTopologyMismatch):
		ads_printf(" Topology Mismatch\n");
		break;        
    case(AcBr::eUnsuitableTopology):
		ads_printf(" Unsuitable Topology\n");
		break;        
    case(AcBr::eUnsuitableGeometry):
		ads_printf(" Unsuitable Geometry\n");
		break;        
    case(AcBr::eMissingTopology):
		ads_printf(" Missing Topology\n");
		break;        
    case(AcBr::eMissingGeometry):
		ads_printf(" Missing Geometry\n");
		break;
    case(AcBr::eMissingSubentity):
		ads_printf(" Missing Subentity\n");
		break;
    case(AcBr::eInvalidObject):
		ads_printf(" Invalid Object\n");
		break;
    case(AcBr::eAmbiguousOutput):
		ads_printf(" Ambiguous Output\n");
		break;
	default: 
		ads_printf(" External Error Code: %d\n", errorCode);
		break;    
	}

	return;
}


void
ptContainmentReport(AcGe::PointContainment containment,
				    AcBrEntity*			   container)
{
    switch (containment) {
	case(AcGe::kOutside):
		ads_printf("\n Point is outside entity boundary\n");
		break;
	case(AcGe::kInside):
		ads_printf("\n Point is inside entity boundary\n");
		break;     
	case(AcGe::kOnBoundary):
		if (container != NULL) {
			if (container->isKindOf(AcBrFace::desc())) {
				ads_printf("\n Point is on a face boundary of entity\n");
			} else if (container->isKindOf(AcBrEdge::desc())) {
				ads_printf("\n Point is on an edge boundary of entity\n");
			} else if (container->isKindOf(AcBrVertex::desc())) {
				ads_printf("\n Point is on a vertex boundary of entity\n");
			} else ads_printf("\n Indeterminate point containment\n");
		}
		break;        
	default: 
		ads_printf("\n Indeterminate point containment\n");
		break;    
	}

	return;
}


void
lnContainmentReport(Adesk::UInt32& hitIndex,
					AcGePoint3d*   hitPoint,
					AcBrEntity*    entityHit,
					AcBrEntity*    entityEntered)
{
	if (hitPoint != NULL) {
		ads_printf("\n Hit point %d is (", hitIndex+1);
		ads_printf ("%lf , ", hitPoint->x);	
		ads_printf ("%lf , ", hitPoint->y);
		ads_printf ("%lf ", hitPoint->z);
		ads_printf(")\n");
	}

    if (entityHit != NULL) {
		if (entityHit->isKindOf(AcBrBrep::desc())) {
			ads_printf("\n Hit is inside solid\n");
		} else if (entityHit->isKindOf(AcBrFace::desc())) {
			ads_printf("\n Hit is on a face\n");
		} else if (entityHit->isKindOf(AcBrEdge::desc())) {
			ads_printf("\n Hit is on an edge\n");
		} else if (entityHit->isKindOf(AcBrVertex::desc())) {
			ads_printf("\n Hit is on a vertex\n");
		} else ads_printf("\n Indeterminate hit containment\n");
	}

    if (entityEntered != NULL) {
		if (entityEntered->isKindOf(AcBrBrep::desc())) {
			ads_printf("\n Segment is inside solid\n");
		} else if (entityEntered->isKindOf(AcBrFace::desc())) {
			ads_printf("\n Segment is on a face\n");
		} else if (entityEntered->isKindOf(AcBrEdge::desc())) {
			ads_printf("\n Segment is on an edge\n");
		} else ads_printf("\n Indeterminate segment containment\n");
	}

	return;
}

