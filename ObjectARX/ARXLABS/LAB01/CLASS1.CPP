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

//    class1.cpp
//
//    The minimal ARX program defining and exporting a class.
//    It defines a class Class1 with a method Class1::hello(),
//    which appropriately enough also says hello.
//
//    The application defines an AutoCAD command CLASS1
//    which invokes Class1::hello through the ARX mechanisms.

#include <rxregsvc.h>
#include <aced.h>
#include <adslib.h>
#include "class1.h"

// Class1 implementation:
//
ACRX_CONS_DEFINE_MEMBERS(Class1, AcRxObject, 0);

void
Class1::hello()
{
    ads_printf("Class1::hello: Hi there!\n");
}

void
class1()
{
    ads_printf("This is class1() in Class1 ...\n");

    Class1 *h = new Class1;
    ads_printf("Survived creation of a Class1 object. "
        "Let's call its hello function:\n");
    if(!h) {
        ads_printf("Unfortunately, it's a null pointer ...\n");
        return;
    }
    h->hello();
    delete h;
    ads_printf("Survived deletion of Class1 object.\n");
}

void
initApp()
{
    ads_printf("Class1 Rx Sample -- initApp\n");

    // Step 1:
    //
    //   Add classes to the runtime-identifiable class hierarchy.
    //
    //   This call was defined by use of the ACRX_CONS_DEFINE_MEMBERS()
    //   macro on Class1.
    //
    Class1::rxInit();

    // Step 2:
    //
    //   Build class relationships before proceeding.  Use after
    //   making a set of <Classname>::rxInit() calls which add a
    //   contiguous growth onto the inheritance tree.
    //
    acrxBuildClassHierarchy();

    // Step 3:
    //
    //   Do any other initialization you need.  The point is that it is
    //   best to do the classes first, since the rest of the initialization
    //   is usually concerned with them.
    //
    //   This example application registers a service name, needed for
    //   symbolic function export,  and a handy object for verifying the
    //   presence of this application.
    //
    acrxRegisterService(SERVICE);

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("CLASS1_COMMANDS", "CLASS1", "CLASS1",
                    ACRX_CMD_MODAL, class1);
}

void unloadApp()
{
    ads_printf("Class1 Rx Sample -- kUnloadAppMsg\n");

    // Remove the service that was registered via acrxRegisterService()
    //
    delete acrxServiceDictionary->remove(SERVICE);
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("CLASS1_COMMANDS");

    // remove Class1 from the AcRx runtime tree
    //
    deleteAcRxClass(Class1::desc());
}

extern "C" AcRx::AppRetCode 
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
        ads_printf("Class1 Rx Sample -- kLoadDwgMsg\n");
        break;
    case AcRx::kUnloadDwgMsg:
        ads_printf("Class1 Rx Sample -- kUnloadDwgMsg\n");
        break;
    default:
        ads_printf("Class1 Rx Sample -- <unknown message %d>\n", msg);
    }
    return AcRx::kRetOK;
}

