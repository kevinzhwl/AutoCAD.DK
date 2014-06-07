// (C) Copyright 1996-1999 by Autodesk, Inc. 
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


#include "acutads.h"	// acutPrintf

// AcGe support
#include "geintrvl.h"
#include "geblok3d.h"
#include "gepnt3d.h"

// AcBr support 
#include "brent.h"

// AcBr sample app support
#include "brreport.h"
#include "brselect.h"
#include "brbblock.h"

void
dumpBblock()
{ 
    AcBr::ErrorStatus returnValue = AcBr::eOk;

	// Select the entity by type
	AcBrEntity* pEnt = NULL;
	AcDb::SubentType subType = AcDb::kNullSubentType;
	returnValue = selectEntityByType(pEnt, subType);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in selectEntityByType:");
		errorReport(returnValue);
		delete pEnt;
    	return;
    }

	AcGeBoundBlock3d bblock;

	returnValue = pEnt->getBoundBlock(bblock);
	if (returnValue != AcBr::eOk) {
		acutPrintf("\n Error in AcBrEntity::getBoundBlock:"); 
		errorReport(returnValue);
		delete pEnt;
		return;
	}
	delete pEnt;

	AcGePoint3d min, max;
	bblock.getMinMaxPoints(min, max);
	bblockReport(min, max);

	return;
}
