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
// Source file for the ObjectARX application command "BRBBLOCK".


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbmain.h"
#include "dbsubeid.h"

// AcGe support
#include "geintrvl.h"
#include "geblok3d.h"
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
#include "brdbutl.h"
#include "brbblock.h"

// Abbreviations
#include "acdbabb.h"


void
dumpBblock()
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path after querying type
	AcDbFullSubentPath* subPath = NULL;
	int adsError = getPathAndType(subPath);
	if ((adsError == RTERROR) || (adsError == RTCAN)) return;

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
        ads_printf("\n dumpBblock: unsupported subentity type: %d\n", subType);
        return;
	}

    returnValue = entity->setSubentPath(*subPath);
    if (returnValue != AcBr::eOk) {
    	ads_printf("\n Error in AcBrEntity::setSubentPath:");
    	errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
    	return;
    }

	AcGeBoundBlock3d bblock;

	returnValue = entity->getBoundBlock(bblock);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEntity::getBoundBlock:"); 
		errorReport(returnValue);
		if ((subType == 0) && (subPath != NULL)) delete subPath;
		return;
	}

	AcGePoint3d min, max;
	bblock.getMinMaxPoints(min, max);
    ads_printf("\n Bounding Block lower corner is (");
	ads_printf ("%lf, ", min.x);	
	ads_printf ("%lf, ", min.y);
	ads_printf ("%lf", min.z);
	ads_printf(")\n");	
    ads_printf("\n Bounding Block upper corner is (");
	ads_printf ("%lf, ", max.x);	
	ads_printf ("%lf, ", max.y);
	ads_printf ("%lf", max.z);
	ads_printf(")\n");	

    // a subent path is "newed" only in the case of a brep, where one
	// does not already exist in AutoCAD (as it does for face, edge).
	if ((subType == 0) && (subPath != NULL)) delete subPath;
	if (entity != NULL) delete entity;

	return;
}
