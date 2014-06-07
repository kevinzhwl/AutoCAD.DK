// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// UTILUI.CPP 
//
// DESCRIPTION:
//
// This file contains utility routines needed for implementing 
// rx sample app - POLY.


#include "assert.h"
#include "math.h"
#include "adslib.h"

#include "gepnt3d.h"
#include "gearc2d.h"
#include "gearc3d.h"

#include "dbspline.h"
#include "dbents.h"
#include "dbsymtb.h"

#include "poly.h"
#include "util.h"

#include "dbapserv.h"


// Given the name of a text style, look up that name and
// return the db id of the TextStyleTableRecord.
//
Acad::ErrorStatus 
rx_getTextStyleId(const char         *styleName,
                        AcDbDatabase *db,
                        AcDbObjectId &styleId)
{
    AcDbTextStyleTable *pStyleTable;
    Acad::ErrorStatus es = db->getSymbolTable(
                              pStyleTable, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pStyleTable->getAt(styleName, styleId, Adesk::kFalse);
        pStyleTable->close();
    }
    return es;
}


//*************************************************************************
// Database related utility routines 
//*************************************************************************


Acad::ErrorStatus 
postToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return postToDb(ent, objId);
}


Acad::ErrorStatus 
postToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbHostApplicationServices()->workingDatabase()->
           getSymbolTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->close()) != Acad::eOk) {
        return es;
    }

    return ent->close();
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return addToDb(ent, objId);
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbHostApplicationServices()->workingDatabase()->
           getSymbolTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }


    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }
    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    return pSpaceRecord->close();
}

