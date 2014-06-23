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
#ifndef _UTIL_H
#define _UTIL_H

#ifdef unix
#define _stricmp(x, y) strcmp(x, y)
#endif

#include "dbmain.h"

int classNameToEntityType(const char* cName);
char* entityTypeToClassName(int entCode);
Acad::ErrorStatus postToDatabase(AcDbEntity* ent, AcDbObjectId& objId);
Acad::ErrorStatus createLine(char *dataPoints);
Acad::ErrorStatus createCircle(char *dataPoints);
Acad::ErrorStatus createCircularArc(char *dataPoints);
Acad::ErrorStatus createEllipse(char *dataPoints);
Acad::ErrorStatus createRay(char *dataPoints);
Acad::ErrorStatus createXline(char *dataPoints);
Acad::ErrorStatus createSpline(char *dataPoints);
Acad::ErrorStatus create3dSolid(char *dataPoints);
Acad::ErrorStatus createRegion(char *dataPoints);
Acad::ErrorStatus createSplineFromFitData(int colNo, int visib, char *dataPoints);
Acad::ErrorStatus createSplineFromNurbsData(int colNo, int visib, char *dataPoints);
Acad::ErrorStatus getObject(int classId, AcDbEntity*& ent);


#endif
