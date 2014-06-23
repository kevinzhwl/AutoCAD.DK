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
//  main.cpp


#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbdict.h"           // dictionaries
#include "dbsymtb.h"          // symboltables
#include "acgi.h"             // graphical definitions
#include "main.h"             // this project
#include "edreact.h"          // the dynamiclinkerreactor
#include "MkrEnti.h"          // new entity AsdkMkrEntity
#include "MKROBJE.h"          // new entity AsdkMkrObject
#include "rxregsvc.h"         // unlock application
#include "arxutils.h"


// function prototypes
//
static void initApp   ();
static void unloadApp ();
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr);


void
mkraddobjects()
{
    ads_point pt;
    if (RTNORM != ads_getpoint( NULL, "\nEnter position:", pt ))
        return;

    AsdkMkrEntity* pEnt = new AsdkMkrEntity;
    if (NULL == pEnt)
        return;

    pEnt->setPos( asPnt3d( pt ) );
    if (!append( pEnt )) {
        delete pEnt;
        return;
    }

    AcDbObjectId objId;
    AsdkMkrObject *pObj = new AsdkMkrObject;
    if (NULL == pObj) {
        pEnt->erase();
        pEnt->close();
        return;
    }

#ifdef DIRECT
    acdbCurDwg()->addAcDbObject( objId, pObj );
    pObj->close();
#else
#ifdef NOD
    AcDbDictionary* pMyDict = getDict( "MYDICT", AcDb::kForWrite );
#else
    AcDbDictionary* pMyDict = getExtDict( pEnt, "MYDICT", AcDb::kForWrite );
#endif  // NOD
    if (NULL == pMyDict) {
        delete pObj;
        pEnt->erase();
        pEnt->close();
        return;
    }

#ifdef DICTHARDOWN
    pMyDict->setTreatElementsAsHard( Adesk::kTrue );
#endif

    Acad::ErrorStatus es;
    if (pMyDict->has( "MYENTRY" ))
        es = pMyDict->setAt( "*", pObj, objId );
    else
        es = pMyDict->setAt( "MYENTRY", pObj, objId );
    pMyDict->close();
    if (Acad::eOk == es)
        pObj->close();
    else {
        delete pObj;
        pEnt->erase();
        pEnt->close();
        return;
    }

#endif  // DIRECT
    pEnt->setId( objId );
    pEnt->close();

    ads_printf( "\nEverything OK\n" );
}


static void
initApp(void)
{
    // register your own entities
    //
    AsdkMkrEntity::rxInit();
    AsdkMkrObject::rxInit();
    acrxBuildClassHierarchy();

    // register your autocad commands
    //
    acedRegCmds->addCommand( "MKR", "ADDOBJECTS", "ADDOBJECTS",
        ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, mkraddobjects );
}


static void
unloadApp(void)
{
    // unregister your own entities
    //
    deleteAcRxClass(AsdkMkrEntity::desc());
    deleteAcRxClass(AsdkMkrObject::desc());

    // unregister your autocad commands
    //
    acedRegCmds->removeGroup("MKR");
    erase_EditorReactor();
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
    case AcRx::kLoadDwgMsg:
        create_EditorReactor();
#ifdef DIRECT
        ads_printf( "\nHardOwnership & addAcDbObject\n" );
#else
#ifdef XLATE
        ads_printf( "\nDeepCloneXlation activated.\n" );
#else
        ads_printf( "\nDeepCloneXlation de-activated.\n" );
#endif  // XLATE
#ifdef NOD
        ads_printf( "Custom object will be stored in the"
            " NamedObjectsDictionary.\n" );
#else
        ads_printf( "Custom object will be stored in the"
            " Extension Dictionary.\n" );
#endif  // NOD
#ifdef HARDPOINTER
        ads_printf( "Entity keeps HardPointerId of custom object.\n" );
#else
        ads_printf( "Entity keeps SoftPointerId of custom object.\n" );
#endif  // HARDPOINTER
#endif  // DIRECT
#ifdef DICTHARDOWN
        ads_printf( "Private Dictionary hardowns entries.\n" );
#endif
        ads_printf( "Start with 'addobjects'.\n" );
    }
    return AcRx::kRetOK;
}
