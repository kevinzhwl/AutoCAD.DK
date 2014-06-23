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
// Source file for the ObjectARX application command "BRDUMP".


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbmain.h"
#include "dbsubeid.h"

// AcBr support 
#include "brgbl.h"
#include "brbrep.h"
#include "brface.h"	
#include "bredge.h"
#include "brvtx.h"	

// AcBr sample app support
#include "brreport.h"
#include "brdbutl.h"
#include "brdump.h"
#include "brbdump.h"
#include "brfdump.h"
#include "bredump.h"
#include "brvdump.h"

// Abbreviations
#include "acdbabb.h"


void
dumpModel()
{
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path after querying type
	AcDbFullSubentPath* subPath = NULL;
	int adsError = getPathAndType(subPath);
	if ((adsError == RTERROR) || (adsError == RTCAN)) return;

    // Call the appropriate subentity dump routine
	AcDb::SubentType subType = subPath->subentId().type();
	switch (subType) {
	case AcDb::kNullSubentType:
    {
		// brep
    	AcBrBrep brepEntity;
    	returnValue = brepEntity.setSubentPath(*subPath);
    	if (returnValue != AcBr::eOk) {
    		ads_printf("\n Error in AcBrBrep::setSubentPath:");
    		errorReport(returnValue);
			if (subPath != NULL) delete subPath;
    		return;
    	}
		returnValue	= brepDump(brepEntity);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in brepDump:"); 
			errorReport(returnValue);
			if (subPath != NULL) delete subPath;
			return;
		}
		break;
    }
    case AcDb::kFaceSubentType:
    {
		// face
		AcBrFace faceEntity;
		returnValue = faceEntity.setSubentPath(*subPath);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrFace::setSubentPath:"); 
			errorReport(returnValue);
			return;
		}
		returnValue = faceDump(faceEntity);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in faceDump:");
			errorReport(returnValue);
			return;
		}
        break;
	}
    case AcDb::kEdgeSubentType:
    {
	    // edge
		AcBrEdge edgeEntity;
		returnValue = edgeEntity.setSubentPath(*subPath);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrEdge::setSubentPath:");
			errorReport(returnValue);
			return;
		}
		returnValue = edgeDump(edgeEntity);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in edgeDump:");
			errorReport(returnValue);
			return;
		}
		break;  
	}
    case AcDb::kVertexSubentType:
    {
	    // vertex
		AcBrVertex vertexEntity;
		returnValue = vertexEntity.setSubentPath(*subPath);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrVertex::setSubentPath:");
			errorReport(returnValue);
			return;
		}
		returnValue = vertexDump(vertexEntity);
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in vertexDump:");
			errorReport(returnValue);
			return;
		}
		break;  
    }
    default:
        ads_printf("\n dumpModel: unsupported subentity type: %d\n", subType);
        return;
	}

    // a subent path is "newed" only in the case of a brep, where one
	// does not already exist in AutoCAD (as it does for face, edge).
	if ((subType == 0) && (subPath != NULL)) delete subPath;

	return;
}
