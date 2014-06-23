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
// Source file for AcGe curve and surface utilities.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// ObjectARX support
#include "rxobject.h"

// AcGe support
#include "gegbl.h"
#include "gecurv2d.h"
#include "geextc2d.h"
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
#include "brletrav.h"

// AcBr sample app support
#include "brreport.h"
#include "brgeutl.h"

// Abbreviations
#include "gegblabb.h"


// Utility function to extract a useful, unbounded surface with native
// surface definition data, from the external bounded surface
AcBr::ErrorStatus
getNativeSurface(const AcBrFace& faceEntity,
                 AcGeSurface*&   surfaceGeometry,
                 AcGeSurface*&   nativeGeometry)
{
    AcBr::ErrorStatus returnValue = faceEntity.getSurface(surfaceGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrFace::getSurface:");
    	errorReport(returnValue);
        return returnValue;
	}
	if (surfaceGeometry == NULL) {
		ads_printf("\n getNativeSurface: external bounded surface is undefined\n");
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (surfaceGeometry->type() != kExternalBoundedSurface) {
		ads_printf("\n getNativeSurface: surface is not an external bounded surface\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	AcGeExternalSurface baseGeometry;
	((AcGeExternalBoundedSurface*)surfaceGeometry)->getBaseSurface(baseGeometry);
	if (!baseGeometry.isDefined()) {
		ads_printf("\n getNativeSurface: external surface is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!baseGeometry.isNativeSurface(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		ads_printf("\n getNativeSurface: native surface is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful, bounded curve with native
// curve definition data, from the external (bounded) curve
AcBr::ErrorStatus
getNativeCurve(const AcBrEdge& edgeEntity,
               AcGeCurve3d*&   curveGeometry,
               AcGeCurve3d*&   nativeGeometry)
{
    AcBr::ErrorStatus returnValue = edgeEntity.getCurve(curveGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrEdge::getCurve:");
        errorReport(returnValue);
        return returnValue;
	}
	if (curveGeometry == NULL) {
		ads_printf("\n getNativeCurve: external 3d curve is undefined\n");
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (curveGeometry->type() != kExternalCurve3d) {
		ads_printf("\n getNativeCurve: curve is not an external 3d curve\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isDefined()) {
		ads_printf("\n getNativeCurve: external 3d curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isNativeCurve(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		ads_printf("\n getNativeCurve: native 3d curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful, bounded and oriented curve
// with native curve definition data, from the external (bounded) curve
AcBr::ErrorStatus
getNativeOrientedCurve(const AcBrLoopEdgeTraverser& loopEdge,
                       AcGeCurve3d*&                curveGeometry,
                       AcGeCurve3d*&                nativeGeometry)
{
    AcBr::ErrorStatus returnValue = loopEdge.getOrientedCurve(curveGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrLoopEdgeTraverser::getOrientedCurve:");
        errorReport(returnValue);
        return returnValue;
	}
	if (curveGeometry == NULL) {
		ads_printf("\n getNativeOrientedCurve: external 3d curve is undefined\n");
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (curveGeometry->type() != kExternalCurve3d) {
		ads_printf("\n getNativeOrientedCurve: curve is not an external 3d curve\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isDefined()) {
		ads_printf("\n getNativeOrientedCurve: external 3d curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve3d*)curveGeometry)->isNativeCurve(nativeGeometry)
	    || (nativeGeometry == NULL)) {
		ads_printf("\n getNativeOrientedCurve: native 3d curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
    return returnValue;
}


// Utility function to extract a useful 2d nurb curve with native
// definition data, from the external paramcurve
AcBr::ErrorStatus
getNativeParamCurve(const AcBrLoopEdgeTraverser& loopEdge,
                    AcGeCurve2d*&                pcurveGeometry,
                    AcGeNurbCurve2d&             nurbGeometry)
{
    AcBr::ErrorStatus returnValue = loopEdge.getParamCurve(pcurveGeometry);  
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrLoopEdgeTraverser::getParamCurve:");
        errorReport(returnValue);
        return returnValue;
	}
	if (pcurveGeometry == NULL) {
		ads_printf("\n getNativeParamCurve: external param curve is undefined\n");
        returnValue = AcBr::eMissingGeometry;
        return returnValue;
	}
	if (pcurveGeometry->type() != kExternalCurve2d) {
		ads_printf("\n getNativeParamCurve: parameter curve is not an external 2d curve\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve2d*)pcurveGeometry)->isDefined()) {
		ads_printf("\n getNativeParamCurve: external param curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
	if (!((AcGeExternalCurve2d*)pcurveGeometry)->isNurbCurve(nurbGeometry)) {
		ads_printf("\n getNativeParamCurve: native 2d nurb curve is undefined\n");
        returnValue = AcBr::eUnsuitableGeometry;
        return returnValue;
	}
    return returnValue;
}
