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
// Source file for the ObjectARX application command "BRPTCNT".


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbmain.h"
#include "dbsubeid.h"

// AcGe
#include "gepnt3d.h"
#include "geassign.h"

// AcBr 
#include "brgbl.h"
#include "brent.h"
#include "brbrep.h"
#include "brface.h"
#include "bredge.h"
#include "brvtx.h"

// AcBr sample app support
#include "brreport.h"
#include "brdbutl.h"
#include "brptcnt.h"

// Abbreviations
#include "acdbabb.h"


void
pointContainment()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path after querying type
	AcDbFullSubentPath* subPath = NULL;
	int adsError = getPathAndType(subPath);
	if ((adsError == RTERROR) || (adsError == RTCAN)) return;

	ads_point testPt;
	ads_getpoint(NULL, "\n Pick point for containment test: \n", testPt);

	// Call the appropriate subentity constructor
	AcDb::SubentType subType = subPath->subentId().type();
	AcBrEntity* entity = NULL;
	switch (subType) {
	case AcDb::kNullSubentType:
    	entity = new AcBrBrep;
		break;
    case AcDb::kFaceSubentType:
    	entity = new AcBrFace();
        break;
    case AcDb::kEdgeSubentType:
    	entity = new AcBrEdge();
		break;  
    case AcDb::kVertexSubentType:
    	entity = new AcBrVertex();
		break;  
    default:
        ads_printf("\n pointContainment: unsupported subentity type: %d\n", subType);
        return;
	}

    returnValue = entity->setSubentPath(*subPath);
    if (returnValue != AcBr::eOk) {
    	ads_printf("\n Error in AcBrEntity::setSubentPath:");
    	errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
    	return;
    }

	const AcGePoint3d pt(asPnt3d(testPt));
    AcGe::PointContainment containment = AcGe::kOutside;
    AcBrEntity* container = NULL;

    returnValue = entity->getPointContainment(pt, containment, container);
    if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEntity::getPointContainment:");
		errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
    	return;
    }

    ptContainmentReport(containment, container);

    // a subent path is "newed" only in the case of a brep, where one
	// does not already exist in AutoCAD (as it does for face, edge).
	if ((subType == 0) && (subPath != NULL)) delete subPath;
	if (entity != NULL) delete entity;
	if (container != NULL) delete container;

	return;
}
