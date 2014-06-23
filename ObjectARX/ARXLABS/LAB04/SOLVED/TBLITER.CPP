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
// tbliter.cpp
//
// This program demonstrates iterating over a symbol table...specifically
// the linetype table.


#include <stdlib.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>

// function prototypes

void iterateLinetypes();
void initApp();
void unloadApp();
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// Opens the linetype table and iterates through all the entries
// printing the name of each linetype.
//
void
iterateLinetypes()
{
    AcDbLinetypeTable *pLinetypeTbl;

    // get the linetypeTable for the current drawing opened for
    // read and set pLinetypeTbl to point to it.
    //
    // ...
    acdbCurDwg()->getLinetypeTable(pLinetypeTbl, AcDb::kForRead);
   
    AcDbLinetypeTableIterator *pLtIterator;
    // Ask the Linetype Table to create a new iterator that
    // starts at table beginning and skips deleted.  Use
    // pLtIterator to point to it.
    //
    // ...
    pLinetypeTbl->newIterator(pLtIterator);

    // walk the linetype table getting every table record and printing
    // the linetype name of each.
    //
    // pLtName is used instead of ltName when asking linetype record
    // for it's name in order to get past compiler typecheck error.
    //
    AcDbLinetypeTableRecord *pLtTableRcd;
    char *pLtName;
    for(; !pLtIterator->done(); pLtIterator->step()) {
      
        // get the current linetype record from the iterator,  opened
        // for read
        //
        // ...
        pLtIterator->getRecord(pLtTableRcd, AcDb::kForRead);

        // get the linetype name from the linetype record and store
        // it in pLtName
        //
        // ...
        pLtTableRcd->getName(pLtName);

        // close the linetype record
        //
        // ...
        pLtTableRcd->close();
      
        // print the linetype name stored in pLtName
        //
        // ...
        ads_printf("\nLinetype name is:  %s", pLtName);

        // The table record mallocs memory for the name string,  so
        // this must be free'd
        //
        free (pLtName);
    }

    // delete the iterator
    //
    // ...
    delete pLtIterator;

    // close the linetype table
    //
    // ...
    pLinetypeTbl->close();
}


// Initialization function called from acrxEntryPoint during kInitAppMsg
// case.  This function is used to add commands to the command stack.
//
void
initApp()
{
    acedRegCmds->addCommand("TABLETEST_COMMANDS", "ITERATE", "ITERATE",
        ACRX_CMD_MODAL, iterateLinetypes);
}


// Clean up function called from acrxEntryPoint during the kUnloadAppMsg
// case.  This function removes this apps command set from the command
// stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("TABLETEST_COMMANDS");
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch(msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
