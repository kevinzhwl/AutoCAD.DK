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
// Source file for the ObjectARX application command "BRTRMSRF".


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbsubeid.h"

// AcGe support 
#include "gegbl.h"
#include "gepnt3d.h"
#include "gecurv2d.h"
#include "geextc2d.h"
#include "gesent2d.h"
#include "genurb2d.h"
#include "gecurv3d.h"
#include "geextc3d.h"
#include "gesurf.h"
#include "geextsf.h"
#include "gexbndsf.h"

// AcBr support 
#include "brgbl.h"
#include "brface.h"	
#include "bredge.h"	
#include "brfltrav.h" 
#include "brletrav.h"
#include "brlvtrav.h"

// AcBr sample app support
#include "brreport.h"
#include "brdbutl.h"
#include "brgeutl.h"
#include "brtrmsrf.h"

// Abbreviations
#include "acdbabb.h"
#include "gegblabb.h"


void
trimSurface()
{								  
    AcBr::ErrorStatus returnValue = AcBr::eOk;
    Acad::ErrorStatus acadReturnValue = eOk;

    // Get the subentity path for a face
	AcDbFullSubentPath* subPath = NULL;
	AcDb::SubentType subType = AcDb::kFaceSubentType;
	acadReturnValue = getPath(subPath, subType);
	if (acadReturnValue != eOk) {
		ads_printf("\n Error in getPath: %d", acadReturnValue);
		return;
	}
	if (subPath == NULL) {
		ads_printf("\n trimSurface: null subpath\n");	
		return;
	}

	// Make a face entity to access the surface
	AcBrFace faceEntity;
	returnValue = faceEntity.setSubentPath(*subPath);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrFace::setSubentPath:");
		errorReport(returnValue);
		return;
	}

	returnValue = faceToTrimmedSurface(faceEntity);
	if (returnValue != AcBr::eOk)  {
		ads_printf("\n Error in faceToTrimmedSurface:");
		errorReport(returnValue);
        return;
    }

	return;
}


AcBr::ErrorStatus
faceToTrimmedSurface (AcBrFace& faceEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// validate the surface associated with this face
	AcGeSurface* surfaceGeometry = NULL;
    AcGeSurface* nativeGeometry = NULL;

	returnValue = getNativeSurface(faceEntity, surfaceGeometry, nativeGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in getNativeSurface:");
		errorReport(returnValue);
        if (surfaceGeometry != NULL) delete surfaceGeometry;
        if (nativeGeometry != NULL) delete nativeGeometry;
        return returnValue;
	}
    if (surfaceGeometry != NULL) delete surfaceGeometry;
    if (nativeGeometry != NULL) delete nativeGeometry;

	// make a face loop traverser to access the surface boundary
	AcBrFaceLoopTraverser faceLoopTrav;
	returnValue = faceLoopTrav.setFace(faceEntity);
	if (returnValue != AcBr::eOk) {
        // eUnsuitableTopology means intrinsically bounded (e.g., sphere, torus)  
		if (returnValue != AcBr::eUnsuitableTopology) {
		    ads_printf("\n Error in AcBrFaceLoopTraverser::setFace:"); 
			errorReport(returnValue);
			return returnValue;
        } else {
		    ads_printf("\n faceToTrimmedSurface: trimmed data unavailable on intrinsically bounded surfaces\n"); 
			errorReport(returnValue);
			return returnValue;
        }
	} else while (!faceLoopTrav.done() && (returnValue == AcBr::eOk)) { 
    	// make a loop edge traverser to access the trimming data
	    AcBrLoopEdgeTraverser loopEdgeTrav;
    	returnValue = loopEdgeTrav.setLoop(faceLoopTrav);
	    if (returnValue != AcBr::eOk) {	 
            // eUnsuitableTopology means loop vertex (special case and go to next loop) 
        	if (returnValue != AcBr::eUnsuitableTopology) {
			    ads_printf("\n Error in AcBrLoopEdgeTraverser::setLoop:"); 
    		    errorReport(returnValue);
    		    return returnValue;
			} else {
				AcBrLoopVertexTraverser loopVertexTrav;
				returnValue = loopVertexTrav.setLoop(faceLoopTrav);
				if (returnValue != AcBr::eOk) {
					ads_printf("\n Error in AcBrLoopVertex::setLoop:");
					errorReport(returnValue);
					return returnValue;
				} else {
					AcGePoint2d* ppointGeometry = NULL;
					returnValue = loopVertexTrav.getParamPoint(ppointGeometry);
				    if ((returnValue != AcBr::eOk) || (ppointGeometry == NULL)) {
						ads_printf("\n Error in AcBrLoopVertex::getParamPoint:");
						errorReport(returnValue);
						if (ppointGeometry != NULL) delete ppointGeometry;
						return returnValue;
					}
                	ads_printf("\n*** Parameters (u,v) at loop vertex: ");
					ads_printf("%lf,%lf\n", ppointGeometry->x, ppointGeometry->y);

					if (ppointGeometry != NULL) delete ppointGeometry;
				} // end loop vertex
			}
	    } else while (!loopEdgeTrav.done() && (returnValue == AcBr::eOk)) { 
			// validate and query the 2d parameter space curve associated with this edge
		    AcGeCurve2d* pcurveGeometry =  NULL;
			AcGeNurbCurve2d nurbGeometry;
		    returnValue = getNativeParamCurve(loopEdgeTrav, pcurveGeometry, nurbGeometry);
		    if (returnValue != AcBr::eOk) {
			    ads_printf("\n Error in getNativeParamCurve:");
			    errorReport(returnValue);
                if (pcurveGeometry != NULL) delete pcurveGeometry;
                return returnValue;
		    }

			ads_printf("\n ***2D NURB curve of degree %d and order %d\n",
			    nurbGeometry.degree(), nurbGeometry.order());

			int i;
			int nCtrlPts = nurbGeometry.numControlPoints();
			ads_printf("\n ****Curve has %d control points\n", nCtrlPts);
			for(i=0; i<nCtrlPts; i++) {
				ads_printf("\n *****Control point [%d] (%lf, %lf)\n", i,
					nurbGeometry.controlPointAt(i).x, nurbGeometry.controlPointAt(i).y);
			}

			int nKnots = nurbGeometry.numKnots();
		   	ads_printf("\n ****Curve has %d knot points\n", nKnots);
		   	for (i=0; i<nKnots; i++) {
				ads_printf("\n *****Knot point [%d] %lf\n", i, nurbGeometry.knotAt(i));
			}

			int nWeights = nurbGeometry.numWeights();
			ads_printf("\n ****Curve has %d weights\n", nWeights);
			for (i=0; i<nWeights; i++) {
				ads_printf("\n *****Weight [%d] %lf)\n", i, nurbGeometry.weightAt(i));
			}	  

            if (pcurveGeometry != NULL) delete pcurveGeometry;

			returnValue = loopEdgeTrav.next();
		    if (returnValue != AcBr::eOk) {
			    ads_printf("\n Error in AcBrLoopEdgeTraverser::next:");
			    errorReport(returnValue);
			    return returnValue;
	    	}
	    } // end edge while

    	returnValue = faceLoopTrav.next();
    	if (returnValue != AcBr::eOk) {
	    	ads_printf("\n Error in AcBrFaceLoopTraverser::next:");
		    errorReport(returnValue);
		    return returnValue;
	    }
	}	// end loop while

    return returnValue;
}
