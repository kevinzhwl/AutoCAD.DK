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
// Brep dump utilities.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// AcDb support
#include "acdb.h"
#include "dbsubeid.h"

// AcGe support
#include "geintrvl.h"
#include "gepnt3d.h"
#include "gecurv2d.h"
#include "geextc2d.h"
#include "genurb2d.h"
#include "gecurv3d.h"
#include "geextc3d.h"
#include "gesurf.h"

// AcBr support 
#include "brgbl.h"
#include "brbrep.h"
#include "brface.h"	
#include "brloop.h"
#include "bredge.h"	
#include "brvtx.h"
#include "brbftrav.h"	 
#include "brfltrav.h" 
#include "brletrav.h"
#include "brlvtrav.h"
#include "breltrav.h"

// AcBr sample app support
#include "brreport.h"
#include "brgeutl.h"
#include "brbdump.h"
#include "brvdump.h"

// Abbreviations
#include "acdbabb.h"


AcBr::ErrorStatus
brepDump (AcBrBrep& brepEntity)
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// make a global face traverser
	AcBrBrepFaceTraverser brepFaceTrav;
	returnValue = brepFaceTrav.setBrep(brepEntity);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrBrepFaceTraverser::setBrep:");
		errorReport(returnValue);
		return returnValue;
	}

	// count the faces
	int faceCount = 0;
	while (!brepFaceTrav.done() && (returnValue == AcBr::eOk)) {
	    faceCount++;
	    ads_printf("\n ***Face No: %d \n", faceCount);

		AcBrFace currentFace;
		returnValue = brepFaceTrav.getFace(currentFace);
		if (returnValue != AcBr::eOk) {
		    ads_printf("\n Error in AcBrBrepFaceTraverser::getFace:");
			errorReport(returnValue);
			return returnValue;
		}

    	// validate the surface associated with this face
    	AcGeSurface* surfaceGeometry = NULL;
        AcGeSurface* nativeGeometry = NULL;

    	returnValue =getNativeSurface(currentFace, surfaceGeometry, nativeGeometry);  
    	if (returnValue != AcBr::eOk) {
    		ads_printf("\n Error in getNativeSurface:");
    		errorReport(returnValue);
            if (surfaceGeometry != NULL) delete surfaceGeometry;
            if (nativeGeometry != NULL) delete nativeGeometry;
            return returnValue;
    	}
        if (surfaceGeometry != NULL) delete surfaceGeometry;
        if (nativeGeometry != NULL) delete nativeGeometry;

    	int loopCount = 0;
		AcBrFaceLoopTraverser faceLoopTrav;
		returnValue = faceLoopTrav.setFace(currentFace);
		if (returnValue != AcBr::eOk) {
            // eUnsuitableTopology means intrinsically bounded (e.g., sphere, torus)  
			if (returnValue != AcBr::eUnsuitableTopology) {
			    ads_printf("\n Error in AcBrFaceLoopTraverser::setFace:"); 
				errorReport(returnValue);
				return returnValue;
            } else returnValue = AcBr::eOk;
		} else while (!faceLoopTrav.done() && (returnValue == AcBr::eOk)) { 
		    loopCount++;
		    ads_printf("\n ****Loop No: %d \n", loopCount);

			AcBrLoop loop;
			returnValue = faceLoopTrav.getLoop(loop);
		     if (returnValue != AcBr::eOk) {	
			    ads_printf("\n Error in AcBrFaceLoopTraverser::getLoop:"); 
			    errorReport(returnValue);
			    return returnValue;
		    }
		    AcBrFace loopFace;
		    returnValue = loop.getFace(loopFace);
		    if (returnValue != AcBr::eOk) {	
			    ads_printf("\n Error in AcBrFaceLoopTraverser::getFace:"); 
			    errorReport(returnValue);
			    return returnValue;
		    }
		    if (!currentFace.isEqualTo((AcRxObject*)(&loopFace))) {
			    ads_printf("\n globalCount: face owner of loop inconsistent with current brep face\n");
                return AcBr::eTopologyMismatch;
            }

            int edgeCount = 0;
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
					    AcBrVertex loopPoint;
					    returnValue = loopVertexTrav.getVertex(loopPoint);
				    	if (returnValue != AcBr::eOk) {
						    ads_printf("\n Error in AcBrLoopVertex::getVertex:");
						    errorReport(returnValue);
						    return returnValue;
					    }
                		ads_printf("\nCoordinate of loop vertex: ");
					    returnValue = vertexDump(loopPoint);
				    	if (returnValue != AcBr::eOk) {
						    ads_printf("\n Error in vertexDump:");
						    errorReport(returnValue);
						    return returnValue;
					    }
            	        ads_printf("\n *****Loop No. %d is a loop vertex\n", loopCount);	  
				    } // end loop vertex
			    }
		    } else while (!loopEdgeTrav.done() && (returnValue == AcBr::eOk)) { 
                edgeCount++; 
		        ads_printf("\n *****Edge No: %d \n", edgeCount);

			    AcBrEdge edgeEntity;
			    returnValue = loopEdgeTrav.getEdge(edgeEntity);
			    if (returnValue != AcBr::eOk) {
				    ads_printf("\n Error in AcBrLoopEdgeTraverser::getEdge:");
				    errorReport(returnValue);
				    return returnValue;
			    }

    			// validate the 3d model space curve associated with this edge
            	AcGeCurve3d* curveGeometry = NULL;
                AcGeCurve3d* nativeGeometry = NULL;

            	returnValue = getNativeOrientedCurve(loopEdgeTrav, curveGeometry, nativeGeometry);  
            	if (returnValue != AcBr::eOk) {
            		ads_printf("\n Error in getNativeOrientedCurve:");
            		errorReport(returnValue);
                    if (curveGeometry != NULL) delete curveGeometry;
                    if (nativeGeometry != NULL) delete nativeGeometry;
                    return returnValue;
            	}
		
    			// validate the 2d parameter space curve associated with this edge
    		    AcGeCurve2d* pcurveGeometry =  NULL;
    			AcGeNurbCurve2d nurbGeometry;
    		    returnValue = getNativeParamCurve(loopEdgeTrav, pcurveGeometry, nurbGeometry);
    		    if (returnValue != AcBr::eOk) {
    			    ads_printf("\n Error in getNativeParamCurve:");
    			    errorReport(returnValue);
                    if (pcurveGeometry != NULL) delete pcurveGeometry;
                    return returnValue;
    		    }
                if (pcurveGeometry != NULL) {
					// Determine if the model space curve and parameter space curve
					// agree in their orientation (2d curves are presented in loop perspective)
            		AcGeInterval crvIntrvl;
            		((AcGeExternalCurve3d*)curveGeometry)->getInterval(crvIntrvl);
            		AcGeInterval pcrvIntrvl;
            		((AcGeExternalCurve2d*)pcurveGeometry)->getInterval(pcrvIntrvl);
					if (crvIntrvl != pcrvIntrvl) {
						if ((crvIntrvl.upperBound() == -pcrvIntrvl.lowerBound())
							&& (crvIntrvl.lowerBound() == -pcrvIntrvl.upperBound())) {
                			ads_printf("\n ******Edge No. %d: Curve and Pcurve Orientations Oppose\n",
                				edgeCount);
						} else {
                			ads_printf("\n ******Edge No. %d: Curve and Pcurve Parameter Bounds Differ\n",
                				edgeCount);
                			ads_printf(" *******Curve Parameterisation is (");
							ads_printf("%lf, ", crvIntrvl.lowerBound());
							ads_printf("%lf ", crvIntrvl.upperBound());
							ads_printf(")\n");
                			ads_printf(" *******Parameter Curve Parameterisation is (");
							ads_printf("%lf, ", pcrvIntrvl.lowerBound());
							ads_printf("%lf ", pcrvIntrvl.upperBound());
							ads_printf(")\n");
						}
					}
                }

                if (pcurveGeometry != NULL) delete pcurveGeometry;

                if (curveGeometry != NULL) delete curveGeometry;
                if (nativeGeometry != NULL) delete nativeGeometry;

			    AcBrEdgeLoopTraverser edgeLoopTrav;
		    	returnValue = edgeLoopTrav.setEdgeAndLoop(loopEdgeTrav);
		    	if (returnValue != AcBr::eOk) {
				    ads_printf("\n Error in AcBrEdgeLoopTraverser::setEdgeAndLoop:");
			    	errorReport(returnValue);
				    return returnValue;
			    }

                // count the radial faces around an edge
		    	int adjacentFaces = 0;
			    while (!edgeLoopTrav.done() && (returnValue == AcBr::eOk)) {
			        adjacentFaces++;
			    	returnValue  = edgeLoopTrav.next();
    			    if (returnValue != AcBr::eOk) {
    				    ads_printf("\n Error in AcBrEdgeLoopTraverser::next:");
    				    errorReport(returnValue);
    				    return returnValue;
                    }
			    } // end radial face while	 

		        ads_printf("\n ******Edge No. %d has %d adjacent faces\n",
		            edgeCount, adjacentFaces);

                // Inform of any negated orientations, since the model space curve
                // is returned as is (no curve reversal for usage by surface boundary)
            	Adesk::Boolean edgeOriented, loopOriented;
            	returnValue = loopEdgeTrav.getEdgeOrientToLoop(loopOriented);
            	if (returnValue != AcBr::eOk) {
            		ads_printf("\n Error in AcBrLoopEdgeTraverser::getEdgeOrientToLoop:");
                    errorReport(returnValue);
            		return returnValue;
            	} 
            	returnValue = edgeEntity.getOrientToCurve(edgeOriented);
            	if (returnValue != AcBr::eOk) {
            		ads_printf("\n Error in AcBrEdge::getOrientToCurve:");
                    errorReport(returnValue);
            		return returnValue;
            	} 
            	if (!loopOriented ^ !edgeOriented) {
            	    ads_printf("\n ******Edge No. %d: Curve Orientation in Loop is Negative\n",
            	        edgeCount);
            	}

			    returnValue = loopEdgeTrav.next();
			    if (returnValue != AcBr::eOk) {
				    ads_printf("\n Error in AcBrLoopEdgeTraverser::next:");
				    errorReport(returnValue);
				    return returnValue;
		    	}
		    } // end edge while

	        ads_printf("\n *****Loop No. %d has %d edges\n", loopCount, edgeCount);	  

	    	returnValue = faceLoopTrav.next();
	    	if (returnValue != AcBr::eOk) {
		    	ads_printf("\n Error in AcBrFaceLoopTraverser::next:");
			    errorReport(returnValue);
			    return returnValue;
		    }
    	}	// end loop while

	    ads_printf("\n ****Face No. %d has %d loops\n", faceCount, loopCount);	  

		returnValue = brepFaceTrav.next();
		if (returnValue != AcBr::eOk) {
			ads_printf("\n Error in AcBrBrepFaceTraverser::next:");  
			errorReport(returnValue);
			return returnValue;
		}

	}  // end face while

	ads_printf("\n ***Brep has %d faces\n", faceCount);	  

	return returnValue;
}
