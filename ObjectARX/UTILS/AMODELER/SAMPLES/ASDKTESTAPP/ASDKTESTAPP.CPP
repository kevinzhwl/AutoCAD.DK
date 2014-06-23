// 
// (C) Copyright 1993-1997 by Autodesk, Inc. 
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
// ---------------------------------------------------------------------
// File:        AsdkTestApp.CPP
// Description: Facet Modeler Test Application
// Creation:    July, 1996
// -------------------------
//    includes
//

#include "stdarx.h"

#include "AsdkTestApp.h"

#define VSS_REVISION "$Revision: 5 $"
static const char * s_kpcAppName = "AcObjectARX_AsdkTestApp";

// 
// Function prototypes
// 
void printHelp();

// Call the prog main of the non-ARX code
//
void MainTest();

extern "C" 
{
    AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);
}


// -------------------------------------------------
// -------------------------------------------------
//    Initialization
// -------------------------------------------------
// -------------------------------------------------
//  This data structure holds info about commands to be
//  registered and to be listed by the ifcHelp command
//
CommandInfo commandInfo[] =
{
    // 
    // commands
    // 
    "AHELP",                &printHelp,                 "Display this command table",
    "AsdkTest",                &MainTest,                  "Run the main modeler test",
    0,                      0,                          0
};



static void 
initClasses()
{
    // Ensure modeler is fully loaded
    //
    if(!acrxServiceIsRegistered("AsdkAModeler"))
    {
        acrxLoadModule("AModeler.arx",1);
    }
    
    // 
    // Register Server
    // 
    acrxRegisterService((char*)s_kpcAppName);

    // 
    // init all objects derived from AcDbObject
    // 
    //


    // 
    // call to AcRx to add these new classes in its runtime tree
    // 
    //  acrxBuildClassHierarchy();
}


void 
initModule()
{
    ads_printf( "\n" VSS_REVISION "[%s, %s]", __DATE__, __TIME__ );
    initClasses();

    for (CommandInfo * pInfo = commandInfo;  pInfo->commandName != NULL; pInfo++)
    {
        if (acedRegCmds->addCommand(s_kpcAppName, pInfo->commandName,
            pInfo->commandName, ACRX_CMD_MODAL, pInfo->fn ) 
            != Acad::eOk )
        {
            ads_printf ( "There was a problem with addCommand()." );
            break;
        }
    }
}


void 
cleanUpModule()
{
    // 
    // Clean up the commands that were registered with the editor.
    //
    acedRegCmds->removeGroup ( s_kpcAppName );
    delete acrxServiceDictionary->remove((char*)s_kpcAppName);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint( AcRx::AppMsgCode msg, void *pkt )
{
    switch(msg)
    {
    case AcRx::kInitAppMsg:
        initModule();

        // 
        // Try to allow unloading
        // 
        acrxUnlockApplication(pkt);
        printHelp();
        break;

    case AcRx::kUnloadAppMsg:
        cleanUpModule();
        break;
    }

    return AcRx::kRetOK;
}


//
//  ArxAppHelp()
//
//  Print out the short descriptions of all application commands.
//
void 
printHelp()
{
    ads_printf("\n\n%-20s%s\n", "Commands", "Descriptions");
    ads_printf("--------------------------------------------------------\n");

    for (CommandInfo * pInfo = commandInfo; pInfo->commandName != NULL;  pInfo++)
        ads_printf ( "%-20s%s\n", pInfo->commandName, pInfo->desc );
}


