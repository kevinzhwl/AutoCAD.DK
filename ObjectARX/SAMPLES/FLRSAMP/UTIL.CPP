//
// (C) Copyright 1996 by Autodesk, Inc. 
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
// File Name: UTIL.CPP 
//
// DESCRIPTION:
//
// This file contains utility routines needed for implementing 
// rx sample app - FILER.


#include "dbents.h"
#include "dbspline.h"
#include "dbelipse.h"
#include "dbray.h"
#include "dbxline.h"
#include "dbsol3d.h"
#include "dbregion.h"
#include "dbmtext.h"
#include "dbfcf.h"
#include "dbmline.h"
#include "dblead.h"
#include "dbsymtb.h"
#include "util.h"
#include <stdio.h>

Acad::ErrorStatus 
postToDatabase(AcDbEntity* ent, AcDbObjectId& objId)
{

	Acad::ErrorStatus	  es;
	AcDbBlockTable*		pBlockTable;
	AcDbBlockTableRecord*  pSpaceRecord;

	es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead);
	if (es != Acad::eOk)
		 return es;

	es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite);
	if (es != Acad::eOk){
		 pBlockTable->close();
		 return es;
	}

	es = pBlockTable->close();
	if (es != Acad::eOk){
		 return es;
	}

	es = pSpaceRecord->appendAcDbEntity(objId, ent);
	if (es != Acad::eOk){
		 return es;
	}

	es = ent->close();
	if (es != Acad::eOk){
		 pSpaceRecord->close();
		 return es;
	}

	es = pSpaceRecord->close();
	if (es != Acad::eOk){
		 return es;
	}

	return es;
}


int 
classNameToEntityType(const char* cName){
	 int  ecode = 0;

 	if (_stricmp(cName, "AcDbLine")==0){
    	ecode =100;
  	}
 	else if (_stricmp(cName, "AcDbCircle")==0){
    	ecode =101;
  	}
 	else if (_stricmp(cName, "AcDbArc")==0){
    	ecode =102;
  	}
 	else if (_stricmp(cName, "AcDbEllipse")==0){
    	ecode =103;
  	}
 	else if (_stricmp(cName, "AcDbRay")==0){
    	ecode = 114;
  	}
 	else if (_stricmp(cName, "AcDbXline")==0){
    	ecode = 115;
  	}
 	else if (_stricmp(cName, "AcDbSpline")==0){
    	ecode = 116;
  	}
 	else if (_stricmp(cName, "AcDb3dSolid")==0){
    	ecode = 117;
  	}
 	else if (_stricmp(cName, "AcDbRegion")==0){
    	ecode = 118;
  	}
  	else if (_stricmp(cName, "AcDbText")==0){
    	ecode = 119;
  	}
  	else if (_stricmp(cName, "AcDbFcf")==0){
    	ecode = 120;
  	}
	else 
    	ecode = 0;
 return ecode ;
}


Acad::ErrorStatus
getObject(int classId, AcDbEntity*& ent){

Acad::ErrorStatus  es = Acad::eOk;
switch(classId){
		case 100:
				ent = new AcDbLine;
				break;
		case 101:
				ent = new AcDbCircle;
				break;
		case 102:
				ent = new AcDbArc;
				break;
		case 103:
				ent = new AcDbEllipse;
				break;
		case 114:
				ent = new AcDbRay;
				break;
		case 115:
				ent = new AcDbXline;
				break;
		case 116:
				ent = new AcDbSpline;
				break;
		case 117:
				ent = new AcDb3dSolid;
				break;
		case 118:
				ent = new AcDbRegion;
				break; 
		case 119:
				ent = new AcDbText;
				break; 
		case 120:
				ent = new AcDbFcf;
				break; 
		case   0:
		default:
				 es = Acad::eAmbiguousOutput;
				 break;

	} // switch

 return es;

}
