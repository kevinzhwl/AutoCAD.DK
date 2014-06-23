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
// Description:
//
// Demonstrates changing the layer of an entity.

#include <stdlib.h>
#include <string.h>
#include <rxregsvc.h>
#include <aced.h>
#include <adslib.h>
#include <geassign.h>

void initApp();
void unloadApp();
void changeLayer(const AcDbObjectId&, const char*);
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

void
change()
{
    ads_name ent = {0L, 0L};
    AcGePoint3d pt;
    ads_entsel(
        "\nselect an entity to change the layer of: ",
        ent, asDblArray(pt));

    if (ent[0] != NULL) {
        AcDbObjectId eId;
        acdbGetObjectId(eId, ent);

        char pNewLayerName[33] = "0";
        ads_getstring(0, "\nNew layer name (32 char max): ",
            pNewLayerName);

        changeLayer(eId, pNewLayerName);
    }
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
void
changeLayer(const AcDbObjectId& entId,
    const char* pNewLayerName)
{
    AcDbEntity *pEntity;
    acdbOpenObject(pEntity, entId, AcDb::kForWrite);
    pEntity->setLayer(pNewLayerName);
    pEntity->close();
}
// END CODE APPEARING IN SDK DOCUMENT.

// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
//
void
initApp()
{
    acedRegCmds->addCommand("ASDK_LAYERTEST",
        "ASDK_CHLAYER", "CHLAYER", ACRX_CMD_MODAL, change);
}

// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this app's
// command set from the command stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_LAYERTEST");
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
