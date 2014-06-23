//
// (C) Copyright 1994-1997 by Autodesk, Inc. 
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
//
// MAIN.CPP 
//
// DESCRIPTION:
//
// This file contains the code for interfacing to AutoCAD.

#include "windows.h"
#include "objbase.h"
#include "rxregsvc.h"

#include "poly.h"
#include "command.h"
#include "match.h"


extern "C" {

// locally defined entry point invoked by Rx.

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);

}

AcRxDictionary * polyCmds = NULL;

//----------------------------------------------------------------------------
// Match Property
// Pointer for protocol Extension Objects. Pointers are global so that they
// can be accessed during initialization and cleanup.
//
static AsdkPolyMatchProp *pMatchPoly;


// Forward declaration for the AppEventCatcher class
//
Adesk::Boolean addMatchPoly();

short AppEventCatcher::thisAppLoaded = 0;

//----------------------------------------------------------------------------

void
AppEventCatcher::rxAppLoaded(const char* moduleName)
{
    if (!thisAppLoaded) 
    {
        addMatchPoly();
    }
}

//----------------------------------------------------------------------------

Adesk::Boolean
addMatchPoly()
{
    AcRxObject *pTemp;

    if (pTemp = acrxServiceDictionary->at("MatchProperties"))
    {
        ads_printf ("MatchProperties is now available.\n"
                    "Now adding match prop protocol extension to AsdkPoly.\n");
        acedPostCommandPrompt();


        AcRxService *pSvc = AcRxService::cast(pTemp);
  
        if (pSvc == NULL)
          // something's terribly wrong so abort
          acrx_abort("\nProblem with service dictionary\n");

        // now to add the dependency to match.arx
        pSvc->addDependency();
        
        pMatchPoly = new AsdkPolyMatchProp;
        AsdkPoly::desc()->addX(AcDbMatchProperties::desc(), pMatchPoly);
       
        AppEventCatcher::thisAppLoaded = 1;
        
        return Adesk::kTrue;
    }

    return Adesk::kFalse;
}

//----------------------------------------------------------------------------

void
AsdkPolyMatchProp::copyProperties(AcDbEntity *pSrcEntity, AcDbEntity *pTrgEntity, 
                                  unsigned int gMatchFlag) const
{
    AsdkPoly *pPoly = AsdkPoly::cast(pTrgEntity);

    //Do Poly property related property painting....
    if (pSrcEntity->isKindOf(AsdkPoly::desc())) {
      AsdkPoly *pSrcPoly = AsdkPoly::cast(pSrcEntity);

      // copy num sides
      pPoly->setNumSides(pSrcPoly->numSides());

      // add more polysamp properties to match here 
    }

    //Do basic property painting
    
    // COLOR
    if (gMatchFlag & kColorFlag)
        pTrgEntity->setColorIndex(pSrcEntity->colorIndex());

    //LAYER
    if (gMatchFlag & kLayerFlag)
        pTrgEntity->setLayer(pSrcEntity->layerId());

    // LINETYPE
    if (gMatchFlag & kLtypeFlag)
        pTrgEntity->setLinetype(pSrcEntity->linetypeId());

        // LINETYPESCALE
    if (gMatchFlag & kLtscaleFlag)
        pTrgEntity->setLinetypeScale(pSrcEntity->linetypeScale());

    // VISIBILITY. copied always. Should be transparent. 
    pTrgEntity->setVisibility(pSrcEntity->visibility());
}

//----------------------------------------------------------------------------

// Initialization Function

void initModule()
{
    AsdkPoly::rxInit();
    acrxBuildClassHierarchy();

    // add match prop protocol extension to AsdkPoly
    //
    if (!addMatchPoly()) 
    {
        ads_printf ("MatchProperties has not been registered.\n"
                    "Protocol extension will be added when MATCHPROP is used\n");
        acedPostCommandPrompt();
    }

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_POLY",
                            "POLY",
                            ACRX_CMD_MODAL,
                            &polyCommand);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_DRAGPOLY",
                            "DRAGPOLY",
                            ACRX_CMD_MODAL,
                            &dragPolyCommand);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_POLYEDIT",
                            "POLYEDIT",
                            ACRX_CMD_MODAL,
                            &polyeditCommand);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_TRANSACT",
                            "TRANSACT",
                            ACRX_CMD_MODAL,
                            &transactCommand);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_HILITPOLY",
                            "HILITPOLY",
                            ACRX_CMD_MODAL,
                            &hilitPoly);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_HILITSOLID",
                            "HILITSOLID",
                            ACRX_CMD_MODAL,
                            &hilitSolid);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_CREATEINSERT",
                            "CREATEINSERT",
                            ACRX_CMD_MODAL,
                            &createInsert);

    acedRegCmds->addCommand("ASDK_POLYGON",
                            "ASDK_HILITINSERT",
                            "HILITINSERT",
                            ACRX_CMD_MODAL,
                            &hilitInsert);
}

void
updateRegistry()
{
    const char *pKey = acrxProductKey();
    if (!pKey)
        return;

    char *pCookie = strrchr(pKey, '\\');
    if (!pCookie)
        return;

    const char *pDataPath = "Software\\Autodesk\\ObjectARX\\2.0\\SampleApps\\PolySamp";
    char *pAppInfoLoc = (char*)malloc(strlen(pDataPath) + strlen(pCookie) + 1);
    if (!pAppInfoLoc)
        return;

    strcpy(pAppInfoLoc, pDataPath);
    strcat(pAppInfoLoc, pCookie);

    acrxRegisterApp((AcadApp::LoadReasons)(AcadApp::kOnProxyDetection
        | AcadApp::kOnCommandInvocation | AcadApp::kOnLoadRequest), "AsdkPolyCAD",
        pAppInfoLoc  , 2);

    // Now to write out the application specific information
    //
    // We will install our "application specific" data in:
    // Software\Autodesk\ObjectARX\2.0\SampleApps\Polysamp\ACAD-TTTTTTT:ttttttt\AsdkPolyCAD
    // where ACAD-TTTTTTT:ttttttt would be something like: ACAD-606348324:606348324

    HKEY rkey;
    DWORD result;
    LONG status = RegCreateKeyEx(HKEY_LOCAL_MACHINE, pAppInfoLoc, 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rkey, &result);
    free (pAppInfoLoc);
    if (status != ERROR_SUCCESS)
        return;

    HKEY prodKey;
    status = RegCreateKeyEx(rkey, "AsdkPolyCAD", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &prodKey, &result);
    RegCloseKey(rkey);
    if (status != ERROR_SUCCESS)
        return;

    HKEY groupKey;
    status = RegCreateKeyEx(prodKey, "Groups", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &groupKey, &result);
    if (status == ERROR_SUCCESS) {
        RegSetValueEx(groupKey, "ASDK_POLYGON", 0, REG_SZ,
            (const unsigned char*)"ASDK_POLYGON", 13);
        RegCloseKey(groupKey);
    }

    HKEY cmdKey;
    status = RegCreateKeyEx(prodKey, "Commands", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &cmdKey, &result);
    if (status == ERROR_SUCCESS) {
        RegSetValueEx(cmdKey, "ASDK_POLY", 0, REG_SZ,
            (const unsigned char*)"POLY", 5);
        RegSetValueEx(cmdKey, "ASDK_DRAGPOLY", 0, REG_SZ,
            (const unsigned char*)"DRAGPOLY", 9);
        RegSetValueEx(cmdKey, "ASDK_POLYEDIT", 0, REG_SZ,
            (const unsigned char*)"POLYEDIT", 9);
        RegSetValueEx(cmdKey, "ASDK_TRANSACT", 0, REG_SZ,
            (const unsigned char*)"TRANSACT", 9);
        RegSetValueEx(cmdKey, "ASDK_HILITPOLY", 0, REG_SZ,
            (const unsigned char*)"HILITPOLY", 10);
        RegSetValueEx(cmdKey, "ASDK_HILITSOLID", 0, REG_SZ,
            (const unsigned char*)"HILITSOLID", 11);
        RegSetValueEx(cmdKey, "ASDK_CREATEINSERT", 0, REG_SZ,
            (const unsigned char*)"CREATEINSERT", 13);
        RegSetValueEx(cmdKey, "ASDK_HILITINSERT", 0, REG_SZ,
            (const unsigned char*)"HILITINSERT", 12);
        RegCloseKey(cmdKey);
    }

    HKEY loaderKey;
    status = RegCreateKeyEx(prodKey, "Loader", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &loaderKey, &result);
    
    if (status == ERROR_SUCCESS) {
        HMODULE modHandle = GetModuleHandle("polysamp.arx");
        if (modHandle) {
            // long filenames have a max length of 255.  total directory path
            // length is also 255 or less,  so a buffer of 512 bytes should be
            // fine.
            //
            char modulePath[512];
            DWORD pathLength = GetModuleFileName(modHandle, modulePath, 512);
            if (pathLength)
                RegSetValueEx(loaderKey, "MODULE", 0, REG_SZ,
                    (const unsigned char*)modulePath, pathLength + 1);
        }
        RegCloseKey(loaderKey);
    }

    HKEY nameKey;
    status = RegCreateKeyEx(prodKey, "Name", 0, "",
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &nameKey, &result);
    RegCloseKey(prodKey);
    if (status != ERROR_SUCCESS)
        return;

    RegSetValueEx(nameKey, "AsdkPolyCAD", 0, REG_SZ,
        (const unsigned char*)"AsdkPolyCAD", 12);
    RegCloseKey(nameKey);
}

typedef HRESULT (*DllCanUnloadNowFunc)();
STDAPI DllCanUnloadNow(void);


AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    static AppEventCatcher* appEventCatcher = NULL;
    static void *pSvc, *moduleHandle;
    
    switch(msg) {

    case AcRx::kInitAppMsg:

        acrxUnlockApplication(pkt);		// Try to allow unloading
        moduleHandle = pkt;
        // If match app server isn't present, then create and attach
        // a dynamic linker reactor to watch to see if ever loads up
        //
        if (!acrxClassDictionary->at("MatchProperties")) {
            appEventCatcher = new AppEventCatcher();
            acrxDynamicLinker->addReactor(appEventCatcher);
        }

        initModule();
        updateRegistry();
        pSvc = acrxRegisterService( "ASDK_POLYSAMP" );
        break;

    case AcRx::kUnloadAppMsg:

        if (appEventCatcher != NULL)
            acrxDynamicLinker->removeReactor(appEventCatcher);

        acedRegCmds->removeGroup("ASDK_POLYGON");
        delete polyCmds;

        // If we are unloading because AutoCAD is shutting down,
        // then it's possible that the match.arx application is
        // already gone,  so we need to check to see if it's still
        // there.  If it's not,  then we can't remove the protocol
        // extension nor decrement the dependency counter.
        //
        AcRxObject *pTemp;
        if (pTemp = acrxServiceDictionary->at("MatchProperties"))
        {
            // remove the protocol extension.
            AsdkPoly::desc()->delX(AsdkPolyMatchProp::desc());
            delete pMatchPoly;

            AcRxService *pSvc = AcRxService::cast(pTemp);
          
            if (pSvc != NULL)
                pSvc->removeDependency();
        }

        deleteAcRxClass(AsdkPoly::desc());
        delete acrxServiceDictionary->remove("ASDK_POLYSAMP");
        break;

    case AcRx::kOleUnloadAppMsg:
    {
        // take care OLE Automation aka ActiveX Automation
        HMODULE hModule = LoadLibrary("polyolea.dll");
        
        // if loading failed, it means that OLE/A dll is not there.
        // presumely, users not doing  OLE/A work. So just returns
        // default return value, which should be AcRx::kRetOK
        if (hModule != NULL)
        {
            // Get the proc addr of exported DllCanUnloadNow
            // See Win32 API help file for more info on this function
            DllCanUnloadNowFunc funcPtr = 
              (DllCanUnloadNowFunc) GetProcAddress(hModule, "DllCanUnloadNow");

            if (funcPtr != NULL)
            {
                if (GetScode((*funcPtr)()) == S_FALSE)
                {
                  FreeLibrary(hModule);
                  return AcRx::kRetError;
                }
            }
            FreeLibrary(hModule);
            CoFreeUnusedLibraries(); // Force OLE to unload unused lib immediately.
        }
        break;
    }
    // The kDependencyMsg gets sent when a service this app has registered
    // has it's dependency count incremented from 0 to 1 (via a call to
    // the service's addDependency() method).  When this message is sent,
    // the pkt argument is a pointer to the AcRxService object that has had
    // the dependency count bumped.  This allows an app with multiple
    // services registered to tell which one is sending the message.
    //
    case AcRx::kDependencyMsg:
        // Since we only have one service registered, this should
        // always be true,  but it doesn't hurt to be sure.
        // So,  we've got a dependency. Lock ourself so we can't be
        // unloaded.
        //
        if (pSvc == pkt)
            acrxDynamicLinker->lockApplication(moduleHandle);
        break;

    // The kNoDependencyMsg gets sent when a service this app has registered
    // has it's dependency count decremented from 1 to 0 (via a call to
    // the service's removeDependency() method).  When this message is sent,
    // the pkt argument is a pointer to the AcRxService object that has had
    // the dependency count zero'd.  As with the kDependency method, this
    // allows an app with multiple services registered to tell which one is
    // sending the message.
    //
    case AcRx::kNoDependencyMsg:
        // No more dependency,  so unlock to make it possible to be
        // unloaded.
        //
        if (pSvc == pkt)
            acrxDynamicLinker->unlockApplication(moduleHandle);
        break;
    }
    return AcRx::kRetOK;
}
