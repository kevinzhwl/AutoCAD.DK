// (C) Copyright 1997-1999 by Autodesk, Inc. 
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
// Mesh node dump utilities.

#include "acutads.h"	// acutPrintf

// AcBr support 
#include "brent.h"

// AcBr sample app support
#include "brreport.h"
#include "brndump.h"



AcBr::ErrorStatus
nodeDump(const AcBrNode& node)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Determine the entity which contains this node
	AcBrEntity* entityAssociated = NULL;
	returnValue = node.getEntityAssociated(entityAssociated);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrNode::getEntityAssociated:");
		errorReport(returnValue);
		delete entityAssociated;
		return returnValue;
	}
	entityAssociatedReport(entityAssociated);
	delete entityAssociated;

	AcGePoint3d nodePoint;
	returnValue = node.getPoint(nodePoint);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrNode::getPoint:");
        errorReport(returnValue);
		return returnValue;
	}
	acutPrintf("\n Node Point is (");
	acutPrintf ("%lf, ", nodePoint.x);	
	acutPrintf ("%lf, ", nodePoint.y);
	acutPrintf ("%lf", nodePoint.z);
	acutPrintf(")\n");	
	
	return returnValue;
}


AcBr::ErrorStatus
nodeDisplay(const AcBrNode& node, AcGePoint3dArray& pts)
{
	AcBr::ErrorStatus returnValue = AcBr::eOk;

	AcGePoint3d nodePoint;	
	returnValue = node.getPoint(nodePoint);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrNode::getPoint:");
        errorReport(returnValue);
		return returnValue;
	}
    pts.append((const AcGePoint3d&)nodePoint);
    
	return returnValue;
}

