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
//    chglyr.cpp
//

#include  <stdio.h>
#include  <string.h>
#include  "adslib.h"
#include  "rxdefs.h"

#define malloc acad_malloc
#define free   acad_free

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))

int      dofun          (void);
int      funcload       (void);
int      change         (void);
void     changeLayerADS (ads_name, const char*);

struct func_entry { char *func_name; int (*func) (); };
static struct func_entry func_table[] = {{"c:asdk_ads_chlayer", change}};

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr)
{
    switch(msg) {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(ptr);
        break;
    case AcRx::kInvkSubrMsg:
        dofun();
        break;
    case AcRx::kLoadDwgMsg:
        funcload();
    }
    return AcRx::kRetOK;
}


// Define this application's external functions.  Return
// RTERROR on error, else RTNORM.
//
static int
funcload()
{
    short i;

    for (i = 0; i < ELEMENTS(func_table); i++) {
        if (!ads_defun(func_table[i].func_name, i))
            return RTERROR;
    }
    
    return RTNORM;
}


// Execute external function (called upon an RQSUBR request).  
// Return value from the function executed, RTNORM or RTERROR.

static int
dofun()
{
    int val;

    // Get the function code and check that it's within range.
    //   (It can't fail to be, but paranoia doesn't hurt.)
    //
    if ((val = ads_getfuncode()) < 0 || val >= ELEMENTS(func_table)) {
        ads_fail("Received nonexistent function code.");
        return RTERROR;
    }

    // Call the handler and return its success-failure status.
    //
    return (*func_table[val].func)();
}


int
change()
{
    ads_name ent = {0L, 0L};
    ads_point pt;
    char pNewLayerName[33] = "0";

    ads_entsel("\nselect an entity to change the layer of: ", ent, pt);

    if (ent[0]) {
        ads_getstring(0, "\nNew layer name (32 char max): ", pNewLayerName);
        changeLayerADS(ent, pNewLayerName);
    }
    return RTNORM;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
void
changeLayerADS(ads_name entityName,
    const char* pNewLayerName)
{
    struct resbuf *pRb, *pTempRb;
    pRb = ads_entget(entityName);

    // No need to check for rb == NULL since all
    // entities have a layer.
    //
    for (pTempRb = pRb; pTempRb->restype != 8;
        pTempRb = pTempRb->rbnext)
    { ; }

    free(pTempRb->resval.rstring);
    pTempRb->resval.rstring
        = (char*) malloc(strlen(pNewLayerName) + 1);
    strcpy(pTempRb->resval.rstring, pNewLayerName);
    ads_entmod(pRb);
    ads_relrb(pRb);
    ads_retvoid();
}
// END CODE APPEARING IN SDK DOCUMENT.
