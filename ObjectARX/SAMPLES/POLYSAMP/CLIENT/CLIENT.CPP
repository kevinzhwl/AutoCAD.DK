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

#include "aced.h"
#include "rxregsvc.h"

// Client commands defined in clntcmd.cpp
//
extern void polyeditCommandClient();
extern void polyCommandClient();


extern "C" {

// locally defined entry point invoked by Rx.

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);

}

AcRxDictionary * polyCmds = NULL;


// Initialization Function

Adesk::Boolean initModule()
{
    if (!acrxServiceIsRegistered( "ASDK_POLYSAMP" ))
        if (!acrxDynamicLinker->loadModule( "POLYSAMP.ARX", 0 )) {
            ads_printf("unable to load polysamp.arx.  This application"
                " will now unload\n");
            return Adesk::kFalse;
        }
    
    // increment the dependency counter.
    //
    AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
        ->at("ASDK_POLYSAMP");
    if (pSvc)
        pSvc->addDependency();

    
    acedRegCmds->addCommand("ASDK_CLIENT",
                            "ASDKCLIENTPOLY",
                            "CLIENTPOLY",
                            ACRX_CMD_MODAL,
                            polyCommandClient);

    acedRegCmds->addCommand("ASDK_CLIENT",
                            "ASDKCLIENTPOLYEDIT",
                            "CLIENTPOLYEDIT",
                            ACRX_CMD_MODAL,
                            polyeditCommandClient);
    return Adesk::kTrue;
}



AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch(msg)
    {
	case AcRx::kInitAppMsg:
	    if (!initModule())
            return AcRx::kRetError;

        acrxUnlockApplication(pkt);		// Try to allow unloading
        break;
	case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup( "ASDK_CLIENT" );
	    delete polyCmds;
        // decrement the dependency counter.
        //
        AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
            ->at("ASDK_POLYSAMP");
        if (pSvc)
            pSvc->removeDependency();
    }
    return AcRx::kRetOK;
}
