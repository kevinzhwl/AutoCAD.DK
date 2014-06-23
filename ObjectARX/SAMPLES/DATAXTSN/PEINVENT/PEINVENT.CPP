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

/* ========= peinvent.cc:  ARX Protocol Extension Example ================ 

    Test App for ARX Usage of Protocol Extension in conjunction with the AcDb
    library.

    This specific app features a demonstration of using Xdata along with a
    protocol extension class to store and retrieve per-instance state.  The
    "inventory Id" string managed by this application shows the effective
    addition of a new common member variable to AcDbObject, without affecting
    existing clients of AcDbObject.

    This app defines the AsdkInventoryProtXtsn Protocol extension class for
    AcDbObject,  and a default implementation.

    In this example, the protocol extension is not really meant to be
    overridden for derived classes.   There is nothing to prevent use of
    XData with protocol extension applications that require a set of
    protocol extension classes to implement polymorphic behavior across
    various classes for a given protocol extension class definition.


    To Use this application:

    There are two commands, GETID and SETID.  For either one, you can either
    pick an entity, or type "H" at the pick prompt, then enter in the
    hexadecimal representation of any object handle (remember, entities are
    objects too!).

    GETID
      will ask the user to select an object,  then print the last known
      inventory Id, or else print a message stating that the object doesn't
      have an Id yet.

    SETID
      will prompt for an object first, then a string to be attached to it as
      the Inventory Id.

    For either command, you can either pick an entity, or type "H" at the
    pick prompt, then enter in the hexadecimal representation of any object
    handle (remember, entities are objects too!).

    The code checks for most things that can go wrong, but if something does
    go wrong, the resulting messages may not be very informative.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "rxregsvc.h"
#include "aced.h"

#include "adslib.h"

// This app's exported Protocol Extension Class

#include "peinvent.h"


extern "C" {
    // locally defined entry point invoked by ARx.
    //
    AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);
}


//  STRSAVE  --  Allocate a duplicate of a string.  */
//
static char*
strsave(const char *t)
{
    char *s = (char*) t;

    char *c = (char*)malloc((unsigned) (strlen(s) + 1));

    if (c == NULL) {
        ads_printf ("Application %s FATAL ERROR: Out of memory\n",
            ads_getappname());
        return c;
    }
    (void) strcpy(c, s);
    return c;
}

// Status checking
//
Adesk::Boolean
statOk(Acad::ErrorStatus stat)
{
    if (stat == Acad::eOk)
        return Adesk::kTrue;
    ads_printf("\nStatus Check Failed:  %d\n", stat);
    return Adesk::kFalse;
}

AcDbObject*
selectObject(AcDbObjectId& eId, AcDb::OpenMode openMode)
{
    // Allow user to either pick an entity, or type in the object handle.
    ads_name en;
    ads_point pt;
    ads_initget(RSG_OTHER, "Handle _Handle");
    int ss = ads_entsel("\nSelect an Entity or enter 'H' to any enter"
        " object handle:  ", en, pt);

    char handleStr[132];
    switch (ss) {
    case RTNORM:   // got it!
        break;
    case RTKWORD:
        if ((ads_getstring(Adesk::kFalse, "Enter Valid Object Handle: ",
            handleStr) == RTNORM) && (ads_handent(handleStr, en) == RTNORM))
            break;
    //
    // Fall-through intentional
    //
    default:
        ads_printf("Nothing Selected, Return Code==%d\n", ss);
        return NULL;
    }

    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id...
    //
    Acad::ErrorStatus retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        ads_printf("\nacdbGetObjectId failed");
        ads_printf("\nen==(%lx,%lx), retStat==%d\n", en[0], en[1], eId);
        return NULL;
    }

    AcDbObject *pObj;
    if ((retStat = acdbOpenObject(pObj, eId, openMode)) != Acad::eOk) {
        ads_printf("\nacdbOpenEntity failed: ename=(%lx,%lx), mode==%d"
	        " retStat==%d\n", en[0], en[1], openMode, retStat);
        return NULL;
    }
    return pObj;
}


// ========= AsdkInventoryProtXtsn Protocol Extension Class  =========

static Adesk::Boolean haveRegisteredRegappName = Adesk::kFalse;

// Make sure the REGAPP name is in the current drawing.
//
static void
ensureNameIsRegistered()
{
    if (!haveRegisteredRegappName) {
        ads_regapp(PE_INVENTORY_SERVICE);
        haveRegisteredRegappName = Adesk::kTrue;
    }
}


// defines an effective "Inventory Id" member for AcDbObject, using
// Xdata for storage of the per-instance value.


ACRX_NO_CONS_DEFINE_MEMBERS(AsdkInventoryProtXtsn, AcRxObject);

class ObjectInventory : public AsdkInventoryProtXtsn
{
public:

    virtual Acad::ErrorStatus inventoryId(const AcDbObject* pObj,
        char*& inventoryId) const;
    virtual Acad::ErrorStatus setInventoryId(AcDbObject* pObj,
        char* inventoryId);
};

Acad::ErrorStatus
ObjectInventory::inventoryId(const AcDbObject* pObj, char*& pIdStr) const
{
    // start off assuming this is null.
    //
    pIdStr = NULL;
    struct resbuf *pRb = pObj->xData(PE_INVENTORY_SERVICE);
    if (pRb != NULL) {
        struct resbuf* pIdRb = pRb->rbnext;
        if ((pRb->restype != AcDb::kDxfRegAppName) ||
            ((pIdRb != NULL) && (pIdRb->restype != AcDb::kDxfXdAsciiString)))
        {
            pIdStr = NULL;
            return Acad::eBadDxfSequence;
        }
        // No 2nd resbuf implies no inventory string.
        //
        if (pIdRb != NULL)
            pIdStr = strsave(pIdRb->resval.rstring);
        ads_relrb(pRb);
    }
    return Acad::eOk;
}


Acad::ErrorStatus
ObjectInventory::setInventoryId(AcDbObject* pObj, char* pInventoryId)
{
    struct resbuf* pRb;
    if (pInventoryId == NULL)
        pRb = ads_buildlist(1001, PE_INVENTORY_SERVICE, RTNONE);
    else
        pRb = ads_buildlist(1001, PE_INVENTORY_SERVICE, 1000,
            pInventoryId, RTNONE);
    ensureNameIsRegistered();

    statOk(pObj->setXData(pRb));

    ads_relrb(pRb);
    return Acad::eOk;
}

// --- Protocol Extension Objects ---

ObjectInventory *pObjectInventory;

// =================== Commands defined in this Module ================

void
listInventoryId()
{
    AcDbObject *pObj;
    AcDbObjectId pObjId;
    if ((pObj = selectObject(pObjId, AcDb::kForRead)) == NULL)
        return;

    char *pIdStr;
    statOk(AsdkInventoryProtXtsn::cast(pObj->x(AsdkInventoryProtXtsn::desc()))
        ->inventoryId(pObj, pIdStr));

    statOk(pObj->close());

    if (pIdStr == NULL)
        ads_printf("\nNo Inventory Id for selected object.\n");
    else {
        ads_printf("\nInventory Id for selected object is: %s\n", pIdStr);
        free(pIdStr);
    }
}

void setInventoryId()
{
    AcDbObject *pObj;
    AcDbObjectId pObjId;
    char inventoryId[132];
    if (((pObj = selectObject(pObjId, AcDb::kForWrite)) == NULL) ||
        (ads_getstring(Adesk::kFalse, "Enter Inventory Id: ",
        inventoryId) != RTNORM))
        return;

    statOk(AsdkInventoryProtXtsn::cast(pObj->x(AsdkInventoryProtXtsn::desc()))
        ->setInventoryId(pObj, inventoryId));
    statOk(pObj->close());
}

// =================== ARx Module Interface Functions ================
 
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) {
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);

        // Register the class
        //
        AsdkInventoryProtXtsn::rxInit();
        acrxBuildClassHierarchy();

        // Create the protocol extension object.
	    //
	    pObjectInventory = new ObjectInventory();

        // Register the protocol extension object
        // with rightful class object.  Note that defining
        // class is used as key, always.
        //
        AcDbObject::desc()->addX(AsdkInventoryProtXtsn::desc(),
            pObjectInventory);

        // Register a couple of commands to set and list
        // inventory Id for objects
        //
        acedRegCmds->addCommand(PE_INVENTORY_SERVICE,
                                "GETID",
                                "GETID",
                                ACRX_CMD_TRANSPARENT,
                                listInventoryId);

        acedRegCmds->addCommand(PE_INVENTORY_SERVICE,
                                "SETID",
                                "SETID",
                                ACRX_CMD_TRANSPARENT,
                                setInventoryId);

        acrxRegisterService(PE_INVENTORY_SERVICE);
        break;
	case AcRx::kLoadDwgMsg:
        // Will register REGAPP upon first actual need.
        //
        haveRegisteredRegappName = Adesk::kFalse;
        break;
	case AcRx::kUnloadAppMsg:
        // Clean up after ourselves.
        
        // unregister commands
        //
        acedRegCmds->removeGroup(PE_INVENTORY_SERVICE);

        // Unregister, then delete protocol extension object
        //
        AcDbObject::desc()->delX(AsdkInventoryProtXtsn::desc());
        delete pObjectInventory;
        
        // remove the protocol extension class definition.
        //
        deleteAcRxClass(AsdkInventoryProtXtsn::desc());
        
        // unregister the service
        //
        delete acrxServiceDictionary->remove(PE_INVENTORY_SERVICE);
    }
    return AcRx::kRetOK;
}
