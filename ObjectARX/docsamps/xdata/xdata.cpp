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
// This program demonstrates the use of the AcDBObject Xdata
// member functions.

#include <stdlib.h>
#include <string.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>

#include "acestext.h"

void         printXdata();
void         addXdata();
void         printList(struct resbuf* pRb);
AcDbObject*  selectObject(AcDb::OpenMode openMode);
void         initApp();
void         unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// This function calls the
// selectObject() function to allow the user to pick an
// object; then it accesses the xdata of the object and
// sends the list to the printList() function that lists the
// restype and resval values.
// 
void
printXdata()
{
    // Select and open an object.
    //
    AcDbObject *pObj;
    if ((pObj = selectObject(AcDb::kForRead)) == NULL) {
        return;
    }

    // Get the application name for the xdata.
    //
    char appname[133];
    if (acedGetString(NULL,
        "\nEnter the desired Xdata application name: ",
        appname) != RTNORM)
    {
        return;
    }

    // Get the xdata for the application name.
    //
    struct resbuf *pRb;
    pRb = pObj->xData(appname);

    if (pRb != NULL) {

        // Print the existing xdata if any is present.
        // Notice that there is no -3 group, as there is in
        // LISP. This is ONLY the xdata, so
        // the -3 xdata-start marker isn't needed.
        // 
        printList(pRb);
        acutRelRb(pRb);

    } else {
        acutPrintf("\nNo xdata for this appname");
    }
    pObj->close();
}

void 
addXdata() 
{
    AcDbObject* pObj = selectObject(AcDb::kForRead);
    if (!pObj) {
        acutPrintf("Error selecting object\n");
        return;
    }

    
    // Get the application name and string to be added to
    // xdata.
    //
    char appName[132], resString[200];
    appName[0] = resString[0] = '\0';

    acedGetString(NULL, "Enter application name: ",
        appName);
    acedGetString(NULL, "Enter string to be added: ",
        resString);

    
    struct  resbuf  *pRb, *pTemp;
    
    pRb = pObj->xData(appName);

    if (pRb != NULL) {

        // If xdata is present, then walk to the
        // end of the list.
        //
        for (pTemp = pRb; pTemp->rbnext != NULL;
                pTemp = pTemp->rbnext)
                { ; }
    } else {
        // If xdata is not present, register the application
        // and add appName to the first resbuf in the list.
        // Notice that there is no -3 group as there is in
        // AutoLISP. This is ONLY the xdata so
        // the -3 xdata-start marker isn't needed.
        // 
        acdbRegApp(appName);

        pRb = acutNewRb(AcDb::kDxfRegAppName);
        pTemp = pRb;
        pTemp->resval.rstring
            = (char*) malloc(strlen(appName) + 1);
        strcpy(pTemp->resval.rstring, appName);
    }

    // Add user-specified string to the xdata.
    //
    pTemp->rbnext = acutNewRb(AcDb::kDxfXdAsciiString);
    pTemp = pTemp->rbnext;
    pTemp->resval.rstring
        = (char*) malloc(strlen(resString) + 1);
    strcpy(pTemp->resval.rstring, resString);

    // The following code shows the use of upgradeOpen()
    // to change the entity from read to write.
    //
    pObj->upgradeOpen();
    pObj->setXData(pRb);
    
    pObj->close();
    acutRelRb(pRb);
}

// END CODE APPEARING IN SDK DOCUMENT.

// This function accepts a linked list of resbufs as it's
// argument and runs through the list printing out the
// restype and resval values one set per line.
// 
void
printList(struct resbuf* pRb)
{
    int rt, i;
    char buf[133];

    for (i = 0;pRb != NULL;i++, pRb = pRb->rbnext) {
        if (pRb->restype < 1010) {
            rt = RTSTR;
        } else if (pRb->restype < 1040) {
            rt = RT3DPOINT;
        } else if (pRb->restype < 1060) {
            rt = RTREAL;
        } else if (pRb->restype < 1071) {
            rt = RTSHORT;
        } else if (pRb->restype == 1071) {
            rt = RTLONG;
        } else {// restype is already RTSHORT, RTSTR,...
            rt = pRb->restype; // or else it is unknown.
        }

        switch (rt) {
        case RTSHORT:
            if (pRb->restype == RTSHORT) {
                acutPrintf(
                    "RTSHORT : %d\n", pRb->resval.rint);
            } else {
                acutPrintf("(%d . %d)\n", pRb->restype,
                    pRb->resval.rint);
            };
            break;

        case RTREAL:
            if (pRb->restype == RTREAL) {
                acutPrintf("RTREAL : %0.3f\n",
                    pRb->resval.rreal);
            } else {
                acutPrintf("(%d . %0.3f)\n", pRb->restype,
                    pRb->resval.rreal);
            };
            break;

        case RTSTR:
            if (pRb->restype == RTSTR) {
                acutPrintf("RTSTR : %s\n",
                    pRb->resval.rstring);
            } else {
                acutPrintf("(%d . \"%s\")\n", pRb->restype,
                    pRb->resval.rstring);
            };
            break;

        case RT3DPOINT:
            if (pRb->restype == RT3DPOINT) {
                acutPrintf(
                    "RT3DPOINT : %0.3f, %0.3f, %0.3f\n",
                    pRb->resval.rpoint[X],
                    pRb->resval.rpoint[Y],
                    pRb->resval.rpoint[Z]);
            } else {
                acutPrintf("(%d %0.3f %0.3f %0.3f)\n",
                    pRb->restype,
                    pRb->resval.rpoint[X],
                    pRb->resval.rpoint[Y],
                    pRb->resval.rpoint[Z]);
            }
            break;

        case RTLONG:
            acutPrintf("RTLONG : %dl\n", pRb->resval.rlong);
            break;
        }

        if ((i == 23) && (pRb->rbnext != NULL)) {
            i = 0;
            acedGetString(0,
                "Press <ENTER> to continue...", buf);
        }
    }
}

// This function prompts the user to select an entity or
// enter an object's handle.  It then proceeds to open the
// object/entity and return a pointer to it.
// 
AcDbObject*
selectObject(AcDb::OpenMode openMode)
{
    // Allow user to either pick an entity, or type in the
    // object handle.
    //
    int ss;
    ads_name en;
    ads_point pt;
    acedInitGet(RSG_OTHER, "Handle _Handle");
    ss = acedEntSel("\nSelect an Entity or enter"
        " 'H' to enter its handle:  ", en, pt);

    char handleStr[132];
    AcDbObjectId eId;
    switch (ss) {
    case RTNORM:   // got it!
        break;
    case RTKWORD:
        if ((acedGetString(Adesk::kFalse,
            "Enter Valid Object Handle: ",
            handleStr) == RTNORM)
            && (acdbHandEnt(handleStr, en) == RTNORM))
        {
            break;
        }
    // Fall-through intentional
    //
    default:
       acutPrintf("Nothing Selected, Return Code==%d\n",ss);
       return NULL;
    }
    // Now, exchange the ads_name for the object Id...
    //
    Acad::ErrorStatus retStat;
    retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) {
        acutPrintf("\nacdbGetObjectId failed");
        acutPrintf("\nen==(%lx,%lx), retStat==%d\n",
            en[0], en[1], eId);
        return NULL;
    }

    AcDbObject* obj;

    if ((retStat = acdbOpenObject(obj, eId, openMode))
        != Acad::eOk)
    {
        acutPrintf("acdbOpenEntity failed: ename:(%lx,%lx),"
            " mode:%d retStat:%d", en[0], en[1],
            openMode, retStat);
        return NULL;
    }
    return obj;
}


// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand("ASDK_XDATA_DEMO",
        "ASDK_PRINTX", "PRINTX", ACRX_CMD_MODAL,
        printXdata);
    acedRegCmds->addCommand("ASDK_XDATA_DEMO",
        "ASDK_ADDXDATA", "ADDXDATA", ACRX_CMD_MODAL,
        addXdata);

}


// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this app's
// command set from the command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_XDATA_DEMO");
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
