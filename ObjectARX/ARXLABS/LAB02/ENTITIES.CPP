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
//
// entities.cpp - Rx app to manipulate AutoCAD AcDb entities
//
// The minimal Rx program manipulating AutoCAD entities
// using the Rx C++ API. All we do is create a line or
// circle entity and manipulate its start rep. center point.
//
// We define an AutoCAD command ENTS to do so.
//
#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>

#define streq(s,t) (strcmp((s),(t))==0)

// Function Prototypes
//
void ents( void );
AcDbEntity* selectEntity( AcDbObjectId& eId, AcDb::OpenMode openMode );
void getZucs( AcDbDatabase * pDb, AcGeVector3d& v );
int getPoint( AcGePoint3d& pF, char* pMessage, AcGePoint3d& pT );
int getPoint( char* pMessage, AcGePoint3d& pT );
int sa_u2w( ads_point p1, ads_point p2 );
int sa_w2u( ads_point p1, ads_point p2 );
void initApp( void );
void unloadApp( void );
extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* );

// ents - AutoCAD command to create new entity:
//
// We chose the simplest entity of them all ...
// the circle -- or should we create a line?
//
// All entites now belong to some block, since both
// model and paper space are also represented as blocks.
// To add an entity to the database, you first need to 
// get the block table from the database, then get the
// block from the block table, then get the current record
// from the block, and then add the entity to it.
//
// We create either a circle or a line entity, and then
// make use of polymorphism to handle them both as generic
// entities.
//
void
ents()
{
    int rc;
    char kw[20];
    ads_initget(0, "Modify Circle Line");
    rc = ads_getkword("Modify group 10/Circle/<Line>: ", kw);

    if (rc == RTNONE) {
        strcpy(kw, "Line");
        rc = RTNORM;
    }
    if (rc != RTNORM) {
        ads_printf("Nothing selected.\n");
        return;
    }

    AcDbDatabase *pDb = acdbCurDwg();
    AcGeVector3d normal;
    getZucs(pDb, normal);

    AcGePoint3d p;
    AcDbEntity *pObj;
    if (streq(kw, "Line")) {

        // get line parameters from user.  getPoint() will
        // set the point passed in in WCS coordinates:

        AcGePoint3d q;
        rc = getPoint("From point: ", p);
        if (rc != RTNORM) { return; }

        rc = getPoint(p, "To point: ", q);
        if (rc != RTNORM) { return; }

        // create a line:
        //
        // instantiate a new AcDbLine
        // set it to database defaults
        // set its normal vector
        // set its start point
        // set its endpoint

        AcDbLine *pLine = new AcDbLine;

        pLine->setDatabaseDefaults(pDb);

        // ...

        pObj = pLine;

        // continue below to add obj to database ...
    } else if (streq(kw, "Circle")) {

        // get circle parameters from user.  getPoint() will
        // set the point passed in to WCS coordinates

        rc = getPoint("Center point: ", p);
        if (rc != RTNORM) { return; }

        ads_point ptUCS = {p.x, p.y, p.z};

        double r;
        rc = ads_getdist(ptUCS, "Radius: ", &r);
        if (rc != RTNORM) { return; }

        // create a circle:
        //
        // instantiate a new AcDbCircle
        // set it to database defaults
        // set its normal vector
        // set its center point
        // set its radius

        AcDbCircle *pCircle = new AcDbCircle;

        pCircle->setDatabaseDefaults(pDb);

        // ...

        pObj = pCircle;

        // continue below to add obj to database ...
    } else if (streq(kw, "Modify")) {

        AcDbObjectId eId;
        pObj = selectEntity(eId, AcDb::kForRead);
        if (!pObj) { return; }

        // if it is a circle or line,
        // modify start/center point:
        //
        AcDbLine *pLine;
        AcDbCircle *pCircle;
        if ((pCircle = AcDbCircle::cast(pObj)) != NULL) {
            // set p to the original circle center:
            //
            // ...
            
            rc = getPoint(p, "New center point: ", p);
            pCircle->upgradeOpen();
            if (rc == RTNORM) { 
                // set the circle center to the new point:
                //
                // ...
            }
          pCircle->close();
        } else if ((pLine = AcDbLine::cast(pObj)) != NULL) {
            // set p to the original line start point:
            //
            // ...

            rc = getPoint(p, "New start point: ", p);
            pLine->upgradeOpen();
            if (rc == RTNORM) { 
                // set the line start point to the new point:
                //
                // ...
            }
            pLine->close();
        } else {
            ads_printf("Not a circle or line.\n");
        }
    return;
    }
    //
    // we are creating a new entity, either line or circle,
    // and now the generic AcDbEntity *pObj is pointing to it ...
    //
    // open block table to search for model space block:
    //

    AcDbBlockTable *pDbTable;
    Acad::ErrorStatus es = pDb->getBlockTable(pDbTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        ads_printf("Unable to open block table.\n");
        delete pObj;
        return;
    }
    
    // open current record in model space block:
    //
    AcDbBlockTableRecord *pDbRecord;
    es = pDbTable->getAt(ACDB_MODEL_SPACE, pDbRecord, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ads_printf("Unable to open model space block.\n");
        if (pDbTable->close() != Acad::eOk) {
            acrx_abort("Unable to close block table.\n");
        }
        delete pObj;
        return;
    }

    if (pDbTable->close() != Acad::eOk) {
        acrx_abort("Unable to close block table.\n");
    }    

    // append new entity to model space block:
    //
    es = pDbRecord->appendAcDbEntity(pObj);
    if (es != Acad::eOk) {
        ads_printf("Unable to append entity.\n");
        if (pDbRecord->close() != Acad::eOk) {
            acrx_abort("Unable to close database record.\n");
        }
        delete pObj;
        return;
    }

    if (pObj->close() != Acad::eOk) {
        acrx_abort("Unable to close entity.\n");
    }

    if (pDbRecord->close() != Acad::eOk) {
        acrx_abort("Unable to close database record.\n");
    }
}

// selectEntity - utility function to select entity
//
// Select entity, retrieve object Id and open it,
// creating and returning a valid object pointer.
//
AcDbEntity*
selectEntity(AcDbObjectId& eId, AcDb::OpenMode openMode)
{

    ads_name en;
    ads_point pt;
    int rc = ads_entsel("\nSelect an entity: ", en, pt);
    if (rc != RTNORM) {
        ads_printf("Nothing selected.\n", rc);
        return NULL;
    }
    
    Acad::ErrorStatus es = acdbGetObjectId(eId, en);
    if (es != Acad::eOk) {
        ads_printf("Either acdbGetObjectId or ads_entsel failed: "
            "Entity name <%lx,%lx>, error %d.\n", en[0], en[1], es);
        return NULL;
    }
    AcDbEntity* entObj;

    es = acdbOpenObject(entObj, eId, openMode);
    if (es != Acad::eOk) {
        ads_printf("acdbOpenObject failed with error %d.\n", es);
    return NULL;
    }
    return entObj;
}

// getZucs - retrieve UCS Z coordinate:
//
void
getZucs(AcDbDatabase * pDb, AcGeVector3d& v)
{
    AcGeVector3d x = pDb->pucsxdir();
    AcGeVector3d y = pDb->pucsydir();
    v = x.crossProduct(y);
    v.normalize();
}

// getPoint - acquire WCS point from user:
//
int
getPoint(AcGePoint3d& pF, char* pMessage, AcGePoint3d& pT)
{
    int rc;
    ads_point pFrom = {pF.x, pF.y, pF.z},
              pTo;

    if ((rc = sa_w2u(pFrom, pFrom)) == RTNORM
        && (rc = ads_getpoint(pFrom, pMessage, pTo)) == RTNORM) 
    {
        rc = sa_u2w(pTo, pTo);
        pT.x = pTo[X];
        pT.y = pTo[Y];
        pT.z = pTo[Z];
    }
    return rc;
}

int
getPoint(char* pMessage, AcGePoint3d& pT)
{
    int rc;
    ads_point pTo;

    if ((rc = ads_getpoint(NULL, pMessage, pTo)) == RTNORM) {
        rc = sa_u2w(pTo, pTo);
        pT[X] = pTo[X];
        pT[Y] = pTo[Y];
        pT[Z] = pTo[Z];
    }
    return rc;
}

int
sa_u2w(ads_point p1, ads_point p2)
{
    struct resbuf wcs,ucs;

    wcs.restype     = RTSHORT;
    wcs.resval.rint = 0;
    ucs.restype     = RTSHORT;
    ucs.resval.rint = 1;

    return ads_trans(p1, &ucs, &wcs, 0, p2);
}

int
sa_w2u(ads_point p1, ads_point p2)
{
    struct resbuf wcs,ucs;

    wcs.restype     = RTSHORT;
    wcs.resval.rint = 0;
    ucs.restype     = RTSHORT;
    ucs.resval.rint = 1;

    return ads_trans(p1, &wcs, &ucs, 0, p2);
}

void
initApp()
{
    acedRegCmds->addCommand("ENTITY_CMDS", "ASDKENTS", "ENTS",
        ACRX_CMD_MODAL, ents);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("ENTITY_CMDS");
}

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}

