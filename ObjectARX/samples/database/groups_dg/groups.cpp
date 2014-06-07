// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// This program demonstrates the use of some of the
// AcDbGroup protocol

#include <stdlib.h>
#include <string.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbgroup.h>
#include <dbsymtb.h>
#include <dbents.h>
#include <dbapserv.h>
#include <adslib.h>

void groups();
void makeGroup(AcDbObjectId groupId);
void removeAllButLines(AcDbObjectId groupId);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// This is the main function of this app.  It will first
// create a new AcDbGroup object and add it to the groups
// dictionary with the key "grouptest".  Then it will call
// makeGroup() to prompt the user to select some entities
// which it will place into the "grouptest" group.  Then it
// will call the function removeAllButLines() to iterate
// over the group created removing all entities that are
// not AcDbLines and change all remaining entities in the
// group to color red.
//
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
groups()
{
    AcDbGroup *pGroup = new AcDbGroup("grouptest");

    AcDbDictionary *pGroupDict;
    acdbHostApplicationServices()->workingDatabase()
        ->getGroupDictionary(pGroupDict, AcDb::kForWrite);

    AcDbObjectId groupId;
    pGroupDict->setAt("ASDK_GROUPTEST", pGroup, groupId);
    pGroupDict->close();
    pGroup->close();

    makeGroup(groupId);
    removeAllButLines(groupId);
}


// Prompts the user to select objects to add to the group,
// opens the group identified by "groupId" passed in as
// an argument, then adds the selected objects to the group.
//
void
makeGroup(AcDbObjectId groupId)
{
    ads_name sset;
    int err = acedSSGet(NULL, NULL, NULL, NULL, sset);
    if (err != RTNORM) {
        return;
    }

    AcDbGroup *pGroup;
    acdbOpenObject(pGroup, groupId, AcDb::kForWrite);

    // Traverse the selection set, exchanging each ads_name
    // for an object ID, then adding the object to the group.
    //
    long i, length;
    ads_name ename;
    AcDbObjectId entId;
    acedSSLength(sset, &length);
    for (i = 0; i < length; i++) {
        acedSSName(sset, i, ename);
        acdbGetObjectId(entId, ename);
        pGroup->append(entId);
    }
    pGroup->close();
    acedSSFree(sset);
}

// Accepts an object ID of an AcDbGroup object, opens it,
// then iterates over the group, removing all entities that
// are not AcDbLines and changing all remaining entities in
// the group to color red.
//
void
removeAllButLines(AcDbObjectId groupId)
{
    AcDbGroup *pGroup;
    acdbOpenObject(pGroup, groupId, AcDb::kForWrite);

    AcDbGroupIterator *pIter = pGroup->newIterator();
    AcDbObject *pObj;
    for (; !pIter->done(); pIter->next()) {
        pIter->getObject(pObj, AcDb::kForRead);

        // If it is not a line or descended from a line,
        // close it and remove it from the group.  Otherwise,
        // just close it.
        //
        if (!pObj->isKindOf(AcDbLine::desc())) {
            // AcDbGroup::remove() requires that the object
            // to be removed be closed, so close it now.
	//
            pObj->close();
            pGroup->remove(pIter->objectId());
        } else {
            pObj->close();
        }
    }
    delete pIter;

    // Now change the color of all the entities in the group
    // to red (AutoCAD color index number 1).
    //
    pGroup->setColorIndex(1);

    pGroup->close();
}

// END CODE APPEARING IN SDK DOCUMENT.

// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
//
void
initApp()
{
    acedRegCmds->addCommand("ASDK_GROUP_TEST",
        "ASDK_GROUPTST","GROUPTST", ACRX_CMD_MODAL, groups);
}


// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this app's
// command set from the command stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_GROUP_TEST");
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}

