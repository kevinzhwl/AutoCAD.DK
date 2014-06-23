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
// Source file for the ObjectARX application command "BRLNCNT".


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbmain.h"
#include "dbsubeid.h"

// AcGe
#include "gelent3d.h"
#include "geline3d.h"
#include "geray3d.h"
#include "gelnsg3d.h"
#include "gepnt3d.h"
#include "geassign.h"

// AcBr 
#include "brgbl.h"
#include "brent.h"
#include "brbrep.h"
#include "brface.h"	
#include "bredge.h"
#include "brvtx.h"
#include "brhit.h"	

// AcBr sample app support
#include "brreport.h"
#include "brdbutl.h"
#include "brlncnt.h"

// Abbreviations
#include "acdbabb.h"


void
lineContainment()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path after querying type
	AcDbFullSubentPath* subPath = NULL;
	int adsError = getPathAndType(subPath);
	if ((adsError == RTERROR) || (adsError == RTCAN)) return;

	ads_point startPt, endPt;
	int hitCount;
	ads_printf("\n Pick line for containment test, by selecting two points: \n");
	ads_getpoint(NULL, "\n Pick origin of line: \n", startPt);
	ads_getpoint(NULL, "\n Pick another point on line: \n", endPt);
 	ads_getint("\n Number of hits wanted: ", &hitCount);

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
        ads_printf("\n lineContainment: unsupported subentity type: %d\n", subType);
        return;
	}

    returnValue = entity->setSubentPath(*subPath);
    if (returnValue != AcBr::eOk) {
    	ads_printf("\n Error in AcBrEntity::setSubentPath:");
    	errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
    	return;
    }

	// Query the line type
	const AcGeLinearEnt3d* line = NULL;
    char opt[128];
   	while (Adesk::kTrue) {
		ads_printf("\nEnter Line Type: ");
		ads_initget(NULL, "Infinite Ray Segment");
		if (ads_getkword("Infinite/Ray/<Segment>: ", opt) == RTCAN) return;

        // Map the user input to a valid line type
		if ((strcmp(opt, "Segment") == 0) || (strcmp(opt, "") == 0)) {
			line = new AcGeLineSeg3d(asPnt3d(startPt), asPnt3d(endPt));
			break;
		} else if (strcmp(opt, "Ray") == 0) {
			line = new AcGeRay3d(asPnt3d(startPt), asPnt3d(endPt));
			break;
		} else if (strcmp(opt, "Infinite") == 0) {
			line = new AcGeLine3d(asPnt3d(startPt), asPnt3d(endPt));
			break;
		}
	}

	if (line == NULL) {
		ads_printf("\n lineContainment: unable to allocate memory for line\n");
		return;
	}

    Adesk::UInt32 numHitsWanted = hitCount;
    Adesk::UInt32 numHitsFound = 0;
    AcBrHit* hits = NULL;

    returnValue = entity->getLineContainment(*line, numHitsWanted, numHitsFound, hits);
    if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEntity::getLineContainment:");
		errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
    	return;
    }

	ads_printf("\n Number of hits found: %d", numHitsFound);

	for (Adesk::UInt32 i = 0; i < numHitsFound; i++) {
		AcGePoint3d* pt = NULL;
		returnValue = hits[i].getPoint(pt);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrHit::getPoint:");
			errorReport(returnValue);
			if ((subType == 0) && (subPath != NULL)) delete subPath;
			if (pt != NULL) delete pt;
    		return;
		}

		AcBrEntity* entityHit = NULL;
		returnValue = hits[i].getEntityHit(entityHit);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrHit::getEntityHit:");
			errorReport(returnValue);
			if ((subType == 0) && (subPath != NULL)) delete subPath;
			if (pt != NULL) delete pt;
			if (entityHit != NULL) delete entityHit;
    		return;
		}

		AcBrEntity* entityEntered = NULL;
		returnValue = hits[i].getEntityEntered(entityEntered);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrHit::getEntityEntered:");
			errorReport(returnValue);
			if ((subType == 0) && (subPath != NULL)) delete subPath;
			if (pt != NULL) delete pt;
			if (entityHit != NULL) delete entityHit;
			if (entityEntered != NULL) delete entityEntered;
    		return;
		}

		lnContainmentReport(i, pt, entityHit, entityEntered);

		if (pt != NULL) delete pt;
		if (entityHit != NULL) delete entityHit;
		if (entityEntered != NULL) delete entityEntered;
	}

    // a subent path is "newed" only in the case of a brep, where one
	// does not already exist in AutoCAD (as it does for face, edge).
    if ((subType == 0) && (subPath != NULL)) delete subPath;
	if (entity != NULL) delete entity;

	return;
}
