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
//  clones.cpp

#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbsymtb.h"          // symboltables
#include "clones.h"           // this project
#include "rxregsvc.h"         // unlock application
#include "dbidmap.h"
#include "gemat3d.h"
#include <stdlib.h>

// function prototypes
//
Adesk::Boolean append     (AcDbEntity* pEntity, AcDbObjectId& objId);
Adesk::Boolean append     (AcDbEntity* pEntity);
AcDbObjectId   getBlockId (const char* pBlockName);
int            getFile    (const char* pCmdAsk, const char* pDiaAsk,
                           const char* pExt, char* pResult);
static void unloadApp(void);
static void initApp  (void);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr);


// Copies the entire current space (either model- or paper space)
// using AcDbObject::clone(). The cloned entities are inserted
// into model space. You might notice that calling clone() doesn't
// work for "complex entities" like Polylines or Blocks.
//
void
clone1()
{
    ads_name ss;
    if (RTNORM != ads_ssget( "_x", NULL, NULL, NULL, ss ))
    {
        ads_printf( "ads_ssget cancelled\n" );
        return;
    }

    long length;
    if (RTNORM != ads_sslength( ss, &length ) || 0 == length)
    {
        ads_printf( "empty selection set\n" );
        ads_ssfree( ss );
        return;
    }

    ads_name     ent;
    AcDbObjectId id;

    for (long i = 0; i < length; i++) {
        if (RTNORM != ads_ssname( ss, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;
        AcDbEntity* pObj;
        if (Acad::eOk != acdbOpenAcDbEntity( pObj, id, AcDb::kForRead ))
            continue;

        AcDbEntity* pClone = AcDbEntity::cast( pObj->clone() );
        if (NULL != pClone) {
            if (append( pClone ))
                pClone->close();
            else
                delete pClone;
        }
        pObj->close();
    }
    ads_ssfree( ss );
}


// Copies the entire current space (either model- or paper space)
// using AcDbDatabase::deepCloneObjects(). The cloned entities are
// inserted into model space. This version works well with
// Polylines and Blocks.
//
void
clone2()
{
    ads_name ss;
    if (RTNORM != ads_ssget( "_x", NULL, NULL, NULL, ss ))
    {
        ads_printf( "ads_ssget cancelled\n" );
        return;
    }

    long length;
    if (RTNORM != ads_sslength( ss, &length ) || 0 == length)
    {
        ads_printf( "empty selection set\n" );
        ads_ssfree( ss );
        return;
    }

    ads_name          ent;
    AcDbObjectId      id;
    AcDbObjectIdArray list;
    AcDbIdMapping     pIdMap;

    for (long i = 0; i < length; i++) {
        if (RTNORM != ads_ssname( ss, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;

        list.append( id );
    }
    ads_ssfree( ss );

    AcDbObjectId blockId = getBlockId( ACDB_MODEL_SPACE );
    if (blockId != 0) {
        if (Acad::eOk != acdbCurDwg()->deepCloneObjects( list, blockId, pIdMap ))
            ads_printf( "Error on deepCloneObjects\n" );
    }
    else
        ads_printf( "Error in getting ModelSpace ID\n" );
}


// Copies an external drawing into the current model space
// using AcDbDatabase::deepCloneObjects. As this function
// doesn't support trans-database cloning, all the symbol
// tables are not merged in, and all the references of
// incoming entities are set to null. That's why we call
// setLayer and setLinetype on each incoming entity to set
// the default values.
// The behaviour of this example is undefined if there
// are block references in the incoming database.
//
void
clone3()
{
    AcDbObjectId id;
    AcDbObjectIdArray list;
    AcDbDatabase chromaDwg( Adesk::kFalse );
    char dwgName[_MAX_PATH];

    if (RTNORM != getFile( "Enter DWG name", "Select Drawing", "dwg",
                           dwgName ))
    {
        return;
    }
    if (Acad::eOk != chromaDwg.readDwgFile( dwgName ))
    {
        ads_alert( "Error reading DWG!" );
        return;
    }
    AcDbBlockTable* pBT;
    if (Acad::eOk != chromaDwg.getBlockTable( pBT, AcDb::kForRead ))
    {
        ads_alert( "Error getting BlockTable of DWG" );
        return;
    }
    AcDbBlockTableRecord* pBTR;
    Acad::ErrorStatus es = pBT->getAt( ACDB_MODEL_SPACE, pBTR, AcDb::kForRead );
    pBT->close();
    if (Acad::eOk != es) {
        ads_alert( "Error getting model space of DWG" );
        return;
    }

    AcDbBlockTableRecordIterator* pIT;
    if (Acad::eOk != pBTR->newIterator( pIT )) {
        ads_alert( "Error iterating model space of DWG" );
        pBTR->close();
        return;
    }

    for ( ; !pIT->done(); pIT->step()) {
        if (Acad::eOk == pIT->getEntityId( id ))
            list.append( id );
    }

    delete pIT;
    pBTR->close();

    if (list.isEmpty()) {
        ads_alert( "No entities found in model space of DWG" );
        return;
    }

    AcDbObjectId  blockId = getBlockId( ACDB_MODEL_SPACE );
    AcDbIdMapping pIdMap;
    if (blockId != 0) {
        if (Acad::eOk != chromaDwg.deepCloneObjects( list, blockId, pIdMap ))
            ads_printf( "Error on deepCloneObjects\n" );
    }
    else
        ads_printf( "Error in getting ModelSpace ID\n" );

    AcDbIdMappingIter iter( pIdMap );
    for (iter.start(); !iter.done(); iter.next()) {
        AcDbIdPair idPair;
        if (!iter.getMap( idPair ))
            continue;
        if (!idPair.isCloned())
            continue;
        id = idPair.value();
        if (id == 0)
            continue;

        AcDbEntity* pEnt;
        if (Acad::eOk != acdbOpenAcDbEntity( pEnt, id, AcDb::kForWrite ))
            continue;
        pEnt->setLayer( "0" );
        pEnt->setLinetype( "CONTINUOUS" );
        pEnt->close();
    }
}


// Copies an external drawing into the current model space.
// This time by using the supported way: a combination of
// AcDbDatabase::insert and AcDbDatabase::wblock.
// First, we wblock the external database into a temporary
// in-memory database. We can't wblock directly into the
// current drawing, because wblock is destructive on the
// target database.
// Then we use insert to insert the temporary database into
// the current drawing. We can't use insert to insert the
// external drawing directly, because insert uses
// cheapClone, which moves the objects from the source to
// the target database.
//
// Using this approach, all the symbol table gets merged
// correctly into the current drawing database.
//
void
clone4()
{
    AcDbObjectId id;
    AcDbObjectIdArray list;
    AcDbDatabase extDatabase( Adesk::kFalse );
    char dwgName[_MAX_PATH];

    if (RTNORM != getFile( "Enter DWG name", "Select Drawing", "dwg",
                           dwgName ))
    {
        return;
    }
    if (Acad::eOk != extDatabase.readDwgFile( dwgName ))
    {
        ads_alert( "Error reading DWG!" );
        return;
    }
    AcDbBlockTable* pBT;
    if (Acad::eOk != extDatabase.getBlockTable( pBT, AcDb::kForRead ))
    {
        ads_alert( "Error getting BlockTable of DWG" );
        return;
    }
    AcDbBlockTableRecord* pBTR;
    Acad::ErrorStatus es = pBT->getAt( ACDB_MODEL_SPACE, pBTR, AcDb::kForRead );
    pBT->close();
    if (Acad::eOk != es) {
        ads_alert( "Error getting model space of DWG" );
        return;
    }

    AcDbBlockTableRecordIterator* pIT;
    if (Acad::eOk != pBTR->newIterator( pIT )) {
        ads_alert( "Error iterating model space of DWG" );
        pBTR->close();
        return;
    }

    for ( ; !pIT->done(); pIT->step()) {
        if (Acad::eOk == pIT->getEntityId( id )) {
            list.append( id );

            // There is a bug in ARX that causes extension dictionaries
            // to appear to be soft owners of their contents.  This causes
	    // the contents to be skipped during wblock.  To fix this we
	    // must explicitly tell the extension dictionary to be a hard
	    // owner of it's entries.
            //
            AcDbEntity *pEnt;
            if ( Acad::eOk == pIT->getEntity(pEnt, AcDb::kForRead)) {
                AcDbObjectId obj;
                if ((obj = pEnt->extensionDictionary())
                    != AcDbObjectId::kNull)
                {
                    AcDbDictionary *pDict = NULL;
                    acdbOpenObject(pDict, obj, AcDb::kForWrite);
                    if (pDict) {
                        pDict->setTreatElementsAsHard(Adesk::kTrue);
                        pDict->close();
                    }
                }
                pEnt->close();
            }
        }
    }

    delete pIT;
    pBTR->close();

    if (list.isEmpty()) {
        ads_alert( "No entities found in model space of DWG" );
        return;
    }

    AcDbDatabase *pTempDb;

    if (Acad::eOk != extDatabase.wblock( pTempDb, list, AcGePoint3d::kOrigin ))
    {
        ads_alert( "wblock failed!" );
        return;
    }
    if (Acad::eOk != acdbCurDwg()->insert( AcGeMatrix3d::kIdentity, pTempDb ))
        ads_alert( "insert failed!" );

    delete pTempDb;
}


// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity, AcDbObjectId& objId )
{
	AcDbDatabase* pDb = acdbCurDwg();
	AcDbBlockTable* pBlockTable = NULL;
	AcDbBlockTableRecord* pBlockRec = NULL;

	if( pDb == NULL ) {
		ads_alert( "No database!" );
		return Adesk::kFalse;
	}
	if( pDb->getBlockTable( pBlockTable, AcDb::kForRead ) != Acad::eOk ) {
		ads_alert( "Failed to get block table!" );
		return Adesk::kFalse;
	}
	if( pBlockTable->getAt( ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite )
		!= Acad::eOk )
	{
		ads_alert( "Failed to get block table record!" );
		pBlockTable->close();
		return Adesk::kFalse;
	}
	if( pBlockRec->appendAcDbEntity( objId, pEntity ) != Acad::eOk ) {
		ads_alert( "Failed to append entity!" );
		pBlockTable->close();
		pBlockRec->close();
		return Adesk::kFalse;
	}
	pBlockRec->close();
	pBlockTable->close();
	return Adesk::kTrue;
}

// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity )
{
	AcDbObjectId objId;
	return append( pEntity, objId );
}


AcDbObjectId
getBlockId( const char* pBlockName )
{
    AcDbDatabase* pCurDwg = acdbCurDwg();
    if (NULL == pCurDwg)
        return AcDbObjectId( 0 );
    AcDbBlockTable* pBlockTable;
    if (Acad::eOk != pCurDwg->getBlockTable( pBlockTable, AcDb::kForRead ))
        return AcDbObjectId( 0 );
    AcDbObjectId returnId;
    pBlockTable->getAt( pBlockName, returnId );
    pBlockTable->close();
    return returnId;
}

// getFile
//
// Returns: RTNORM if sucessfully
//          RTERROR if failure
//          The selected file in pResult
//
int
getFile(
    // input:
    const char* pCmdAsk,  // prompt for command line mode
    const char* pDiaAsk,  // prompt for dialog box mode
    const char* pExt,     // file extension
    // output:
    char* pResult)        // selected file returned to the caller.
                          // must be an allocated buffer!
{
    char tmpResult[134];
    int res = RTERROR;
    char drive[_MAX_DRIVE], dir[_MAX_DIR];
    char fname[_MAX_FNAME], ext[_MAX_EXT];

    struct resbuf fileDia;

    // is "filedia" set to 1?
    //
    ads_getvar( "filedia", &fileDia );
    if (1 == fileDia.resval.rint) {
        // yes, display dialog box
        //
        struct resbuf fileRes;

        res = ads_getfiled( pDiaAsk, NULL, pExt, 0, &fileRes );
        if (RTNORM != res) return res;
        if (RTSTR == fileRes.restype) {
            // user selected valid file
            //
            strcpy( pResult, fileRes.resval.rstring );
            free( fileRes.resval.rstring );
            return RTNORM;
        }
    }
    // Prompt at command line required. Either
    // filedia = 0, or "type it" button in dialog was pressed.
    //
    res = ads_getstring( 0, pCmdAsk, tmpResult );
    if (RTNORM != res) return res;

    // look if there's already the file extension attached
    //
    _splitpath( tmpResult, drive, dir, fname, ext );
    // if not, append file extension
    //
    if (stricmp( ext, pExt ) != 0)
        _makepath( tmpResult, drive, dir, fname, pExt );

    // look if file exists (only if not in dialog mode)
    //
    res = ads_findfile( tmpResult, pResult );
    if (RTNORM != res)
        ads_printf( "\nUnable to open %s.\n", tmpResult );
    return res;
}


static void
initApp(void)
{
  acedRegCmds->addCommand("MKR", "CLONE1", "CLONE1", ACRX_CMD_TRANSPARENT, clone1);
  acedRegCmds->addCommand("MKR", "CLONE2", "CLONE2", ACRX_CMD_TRANSPARENT, clone2);
  acedRegCmds->addCommand("MKR", "CLONE3", "CLONE3", ACRX_CMD_TRANSPARENT, clone3);
  acedRegCmds->addCommand("MKR", "CLONE4", "CLONE4", ACRX_CMD_TRANSPARENT, clone4);
}

static void
unloadApp(void)
{
  acedRegCmds->removeGroup("MKR");
}


// acrxEntryPoint(internal)
// This function is the entry point for your application.
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr)
{
  switch (msg) {
    case AcRx::kInitAppMsg:
      acrxUnlockApplication(ptr);
      initApp();
      break;

    case AcRx::kUnloadAppMsg:
      unloadApp();
	break;
}
  return AcRx::kRetOK;
}