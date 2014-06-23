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
// Vertex and point dump utilities.


// Autodesk standard types 
#include "adesk.h"

// ADS support
#include "adslib.h"

// ObjectARX support
#include "rxobject.h"

// AcGe support
#include "gegbl.h"
#include "gepnt3d.h"

// AcBr support 
#include "brgbl.h"
#include "brvtx.h"

// AcBr sample app support
#include "brreport.h"
#include "brvdump.h"

// Abbreviations
#include "gegblabb.h"


AcBr::ErrorStatus
vertexDump(const AcBrVertex& vertexEntity)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	AcGePoint3d* vertexPoint;	
	returnValue = vertexEntity.getPoint(vertexPoint);
	if (returnValue != AcBr::eOk) {
		ads_printf("\n Error in AcBrVertex::getPoint:");
        errorReport(returnValue);
        if (vertexPoint != NULL) delete vertexPoint;
		return returnValue;
	}
	ads_printf("\n Vertex Point is (");
	ads_printf ("%lf, ", vertexPoint->x);	
	ads_printf ("%lf, ", vertexPoint->y);
	ads_printf ("%lf", vertexPoint->z);
	ads_printf(")\n");	
	
    if (vertexPoint != NULL) delete vertexPoint;

	return returnValue;
}
