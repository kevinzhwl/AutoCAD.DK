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
// dbreactr.cpp - Rx app to keep track of changes to entities
//
// This minimal Rx program attaches a reactor to the database
// to receive notification each time an entity changes.  It also
// attaches a reactor to the AutoCAD editor to monitor drawing
// loads and inform the user the name of the drawing being loaded.


#include <stdio.h>
#include <stdlib.h>  // for free() calls
#include <string.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "dbmr.h" // DbModReactor
#include "dwgr.h" // DwgLoadReactor
#include "adeskabb.h"

// Function Prototypes
//
void reactorControl( void );
void attachDbmr( void );
Adesk::Boolean getYorN( const char* pStr );
void initApp( void );
void unloadApp( void );
extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* );

// global reactor object pointers and boolean to monitor if
// reactor should be attached or not.  The reactors need to
// be global, so that they can be deleted if the application
// is unloaded.
//
DwgLoadReactor *dwgr;
DbModReactor *dbmr = NULL;
Boolean dbmrOn = Adesk::kFalse;

// reactorControl - AutoCAD command to watch database modifications:
//
// We offer options switch on and off the database 
// modification reactor, which sets a global 
// boolean switch and calls attachDbmr to do the 
// dirty deed.
//
void
reactorControl()
{
    dbmrOn = getYorN("Start watching entity modifications");
    attachDbmr();
}

void
attachDbmr()
{
    AcDbDatabase *pDb = acdbCurDwg();
    
    // If pDb is NULL then AutoCAD is quitting and the database has
    // already been unloaded so we cannot access it.
    //
    if (pDb == NULL) {
        return;
    }

    if (dbmrOn) {
        // 1. if reactor does not already exist create one using dbmr var
        // 2. add it to the current database
        // 3. Use ads_printf() to display message informing user about
        //    what's just been done.
        // ... Next 5 lines complete this ...
        if (dbmr == NULL) {
            dbmr = new DbModReactor();
        }
        pDb->addReactor(dbmr);
        ads_printf("Attached DbModReactor to database.\n");
    } else if (dbmr) {
        // 1. delete it from database
        // 2. delete it from memory
        // 3. reset it to NULL
        // 4. Use ads_printf() to display message informing user about
        //    what's just been done.
        // ... Next 4 lines complete this ...
        pDb->removeReactor(dbmr);
        delete dbmr;
        dbmr = NULL;
        ads_printf("Detached DbModReactor from database.\n");
    } else {
        ads_printf("DbModReactor pointer was NULL - not removed.\n");
    }
}

// ----- DbModReactor -----

void
DbModReactor::objectAppended(const AcDbDatabase* dwg,
    const AcDbObject* dbObj)
{
    objDisplay("appended", dbObj);
}

void
DbModReactor::objectModified(const AcDbDatabase* dwg,
    const AcDbObject* dbObj)
{
    objDisplay("modified", dbObj);
}

void
DbModReactor::objectErased(const AcDbDatabase* dwg,
    const AcDbObject* dbObj, Adesk::Boolean pErased)
{
    char buf[40];
    sprintf(buf, "%serased", (pErased ? "" : "not "));
    objDisplay(buf, dbObj);
}

void
DbModReactor::objDisplay(const char* what, const AcDbObject* dbObj) const
{
    AcDbObjectId id = dbObj->objectId();

    AcDbHandle h;
    dbObj->getAcDbHandle(h);

    char hstr[20];
    h.getIntoAsciiBuffer(hstr);
    const char *cname = dbObj->isA()->name();

    ads_printf("\nDbModReactor: obj %s: class %s, id %lx, handle %s.\n",
        what, cname, id, hstr);
}

// ----- DwgLoadReactor -----

void
DwgLoadReactor::dwgFileOpened(AcDbDatabase* pDwg, char* fileName)
{
    // The DWGNAME system variable is not part of the AcDbDatabase
    // header,  so the ads_getvar() function must be used to obtain
    // it's value.
    //
    resbuf rb;
    int es = ads_getvar("dwgname", &rb);
    if (es == RTNORM)
        ads_printf("DwgLoadReactor: drawing %s was loaded.\n",
            rb.resval.rstring);
    else
        ads_printf ("Unable to obtain drawing name in openComplete call\n");
}

// getYorN - utility function to get boolean from user:
//
Boolean
getYorN(const char* pStr)
{
    char yorn_str[132];

    yorn_str[0] = 'Y';
    yorn_str[1] = '\0';
    ads_printf("\n%s", pStr);
    ads_initget(0, "No Yes");
    ads_getkword(" -- No/<Yes>:  ", yorn_str);
    return(yorn_str[0] != 'N');
}

void
initApp()
{
    // Create a new DwgLoadReactor object assigning it's address to
    // the global pointer variable "dwgr".  Then add this reactor to
    // the AutoCAD editor.  Remember the macro "acedEditor" returns a
    // pointer to the editor object which is of class AcEditor.
    //
    //... Next two lines complete ...
    dwgr = new DwgLoadReactor();
    acedEditor->addReactor(dwgr);
    
    ads_printf("Added DwgLoadReactor to acedEditor.\n");

    acedRegCmds->addCommand("REACTOR_CMDS", "REACTOR", "REACTOR",
        ACRX_CMD_MODAL, reactorControl);
}

void
unloadApp()
{
    // detach and delete the AcEditor reactor pointed to by dwgr
    //
    //... next two lines complete...
    acedEditor->removeReactor(dwgr);
    delete dwgr;

    // detach and delete dbmr
    //
    dbmrOn = kFalse;
    attachDbmr();

    // remove command group
    //
    acedRegCmds->removeGroup("REACTOR_CMDS");
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
        break;
    case AcRx::kLoadDwgMsg:
        // a NEW drawing is started so if user has elected to
        // have a database reactor attached,  attach one to
        // the new database.
        //
        attachDbmr(); 
    }
    return AcRx::kRetOK;
}
