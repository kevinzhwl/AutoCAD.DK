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
// Source file for Autocad entity/subentity selection.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"
#include "ol_errno.h"

// ObjectARX support
#include "rxobject.h"

// AcDb support
#include "acdb.h"
#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "dbsol3d.h"
#include "dbregion.h"
#include "dbbody.h"
#include "dbid.h"
#include "dbidar.h"
#include "dbsubeid.h"

// AcGe support
#include "gepnt3d.h"
#include "gemat3d.h"

// AcBr sample app support
#include "brdbutl.h"

// Abbreviations
#include "acdbabb.h"


int
getPathAndType(AcDbFullSubentPath*& subPath)
{
	int adsError = RTERROR;

	// Query the subentity type
	AcDb::SubentType subType;
    char opt[128];
   	while (Adesk::kTrue) {
		ads_printf("\nEnter Subent Type: ");
		ads_initget(NULL, "Edge Face Brep");
		if ((adsError = ads_getkword("Edge/Face/<Brep>: ", opt))
			== RTCAN) return adsError;

        // Map the user input to a valid subentity type
		if ((strcmp(opt, "Brep") == 0) || (strcmp(opt, "") == 0)) {
			subType = kNullSubentType;
			break;
        } else if (strcmp(opt, "Face") == 0) {
			subType = kFaceSubentType;
			break;
        } else if (strcmp(opt, "Edge") == 0) {
			subType = kEdgeSubentType;
			break;
		}
    }

	// Get the subentity path for the picked subentity
	Acad::ErrorStatus acadReturnValue = getPath(subPath, subType);
	if (acadReturnValue != eOk) {
		ads_printf("\n Error in getPath: %d", acadReturnValue);
        return RTERROR;
    }
	if (subPath == NULL) {
		ads_printf("\n getPathAndType: null subpath\n");	
		return RTERROR;
	}

	return RTNORM;
}


Acad::ErrorStatus
getPath(AcDbFullSubentPath*& subPath, const AcDb::SubentType& subType)
{
  	Acad::ErrorStatus acadReturnValue = eOk;

	int adsError = RTERROR;
	ads_name sset;
	ads_point adsPick;

	struct resbuf org_osnap;
	ads_getvar("OSMODE", &org_osnap);
	struct resbuf new_osnap = org_osnap;
	new_osnap.resval.rint = 0;
	ads_setvar("OSMODE", &new_osnap);

    while ((adsError != RTNORM) && (adsError != RTCAN) && (adsError != RTREJ)
        && (adsError != RTNONE)) {
        ads_name ent_name;
        switch(subType) {
		case kNullSubentType:
			adsError = ads_entsel("\n Pick a solid\n", ent_name, adsPick);
			break;
		case kFaceSubentType:
			adsError = ads_entsel("\n Pick a face\n", ent_name, adsPick);
			break;
		case kEdgeSubentType:
			adsError = ads_entsel("\n Pick an edge\n", ent_name, adsPick);
			break;
		case kVertexSubentType:
		default:
			ads_printf("\n getPath: unsupported subentity type: %d\n", subType);
			return eInvalidInput;
		}

        if (adsError == RTERROR) {
            struct resbuf buf_errno;
			ads_getvar("ERRNO", &buf_errno);
	        if (buf_errno.resval.rint == OL_ENTSELNULL) adsError = RTNONE;
        }
    }

	if (adsError == RTNORM) {
	    adsError = ads_ssget(NULL, adsPick, NULL, NULL, sset);
	}
    ads_setvar("OSMODE", &org_osnap);

	if (adsError != RTNORM) return eAmbiguousInput;

	// Get the entity name
	struct resbuf* rb;
	adsError = ads_ssnamex(&rb, sset, 0L);
    if (adsError != RTNORM) {
		ads_ssfree(sset);
    	return eAmbiguousInput;
    }  

	// Free the selection set
    ads_ssfree(sset);

	int i;
    struct resbuf* pTemp;
	for (i=1, pTemp=rb; i<3; i++, pTemp=pTemp->rbnext)
		;
	ads_name ename;
	ads_name_set(pTemp->resval.rlname, ename);

	// Get the GsMarker
	pTemp = pTemp->rbnext;
	short marker = pTemp->resval.rint;

	// Free the rb resbuf entity
	ads_relrb(rb);

	// Get the object ID of the selected entity
	AcDbObjectId objId;
	acadReturnValue = acdbGetObjectId(objId, ename);
    if (acadReturnValue != eOk) {
		ads_printf("\n acdbGetObjectId failed\n");
		return acadReturnValue;
	}

    // Open the entity for read
	AcDbEntity* pEnt;
    acadReturnValue = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
	if (acadReturnValue != eOk) {
		ads_printf("\n acdbOpenAcdbEntity failed\n");	
		return acadReturnValue;
	}
  
    // Get the subentity ID
	AcGeMatrix3d xform;
	int numIds;
	AcDbFullSubentPath* subentIds;

	AcGePoint3d pickpnt;                                           
    pickpnt.set(adsPick[0], adsPick[1], adsPick[2]);

	if (pEnt->isKindOf(AcDbBlockReference::desc())) {	
		struct resbuf* insertStack;
		ads_matrix adsMatrix;

		adsError = ads_nentselp(NULL, ename, adsPick, Adesk::kTrue, adsMatrix, &insertStack);
		if (adsError != RTNORM) {
			ads_printf("\n %d nentselp failed\n", adsError); 
			return acadReturnValue;
		} 
		
		// ename should be the solid
		acadReturnValue = acdbGetObjectId(objId, ename);
    	if (acadReturnValue != eOk) {
			ads_printf("\n acdbGetObjectId failed\n");
			return acadReturnValue;
		}

    	acadReturnValue = acdbOpenAcDbEntity(pEnt, objId, AcDb::kForRead);
		if (acadReturnValue != eOk) {
			ads_printf("\n acdbOpenAcDbEntity failed\n");	
			return acadReturnValue;
		}

		int count = 0;
		AcDbObjectId* idArray = new AcDbObjectId[100];
		idArray[count++] = objId;
		
		while (insertStack != NULL) {
        	ename[0] = insertStack->resval.rlname[0];
       		ename[1] = insertStack->resval.rlname[1];

			acadReturnValue = acdbGetObjectId(objId, ename);
			if (acadReturnValue != eOk) {
				ads_printf("\n acdbGetObjectId failed\n");
				return acadReturnValue;
			}

			idArray[count++] = objId;
			insertStack = insertStack->rbnext;
		}

		// Invert the list
		AcDbObjectIdArray objIdList;
		for (int j=(count-1); j>=0; j--) objIdList.append(idArray[j]);

		if (subType != kNullSubentType) {
    		acadReturnValue = pEnt->getSubentPathsAtGsMarker(subType,
    		    marker, pickpnt, xform, numIds, subentIds);
			if (acadReturnValue != eOk) {
				ads_printf("\n getSubentPathsAtGsMarker failed\n");
				pEnt->close();
				return acadReturnValue;
			}
			subPath = &(subentIds[0]);
			subPath->objectIds() = objIdList;
		} else {
			// Make a subent path for a brep object (object ID array w/ null subent)
			subPath = new AcDbFullSubentPath(objIdList, kNullSubentId);
			if (subPath == NULL) {
				pEnt->close();
				return eOutOfMemory;
			} else {
				pEnt->close();
				return acadReturnValue;
			}
		}
	} else {
		if (subType != kNullSubentType) {
			acadReturnValue = pEnt->getSubentPathsAtGsMarker(subType, marker,
    			pickpnt, xform, numIds, subentIds); 
			if (acadReturnValue != eOk) {
				ads_printf("\n getSubentPathsAtGsMarker failed\n");
				pEnt->close();
				return acadReturnValue;
			}
			subPath = &(subentIds[0]);
		} else {
		    // Check to see if entity is a supported solid, region or body  
			if (pEnt->isKindOf(AcDb3dSolid::desc())
				|| pEnt->isKindOf(AcDbRegion::desc())
			 	|| pEnt->isKindOf(AcDbBody::desc())) {
				// Make a subent path for a brep object (object ID array w/ null subent)
				subPath = new AcDbFullSubentPath(objId, kNullSubentId);
				if (subPath == NULL) {	
					pEnt->close();
					return eOutOfMemory;
				} else { 
					pEnt->close();
					return acadReturnValue;
				}
			} else	{
				ads_printf("\n Selected object not a brep object\n");
				pEnt->close();
				return eIllegalEntityType;
			}
		}
	}

	acadReturnValue = pEnt->close();
    if (acadReturnValue != eOk) {
		ads_printf("\n close() failed\n");
	}
	
	return acadReturnValue;
}
