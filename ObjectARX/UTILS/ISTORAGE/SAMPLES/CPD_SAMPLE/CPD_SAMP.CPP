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

#include <afxcoll.h>
#include <afxole.h>
#include <windows.h>
#include <AcCoStg.h>
#include <string.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include "cpd_samp.h"
#include <adslib.h>

#define INIT_VARS   HRESULT hr = NOERROR; \
    IStorage* pStorage = NULL; \
    char *pcStgName = new char [NAMELEN]; \
wchar_t *pwStgName = NULL


#define RELEASE_VARS    if (pcStgName) {delete pcStgName;} \
if (pwStgName) {delete pwStgName;}

#define GET_DATA if (RTNORM != ads_getstring(1, "Enter project name : ", pcStgName)) break; \
pwStgName = wideString(pcStgName)

TestObj *pTestObj = NULL;

TestObj::TestObj ()
    {
    }

TestObj::~TestObj ()
    {
    }

HRESULT 
TestObj::addToList(const wchar_t *pStorageName, 
                   IStorage* pStorage)
    {
    HRESULT hr = NOERROR;
    char *pString = charString(pStorageName);
    mStorageList.SetAt(pString, (void*&)pStorage);
    if (pString) {delete pString;}
    return hr;
    }

HRESULT 
TestObj::lookupList(const wchar_t *pStorageName, 
                    IStorage** ppStorage)
    {
    HRESULT hr = NOERROR;
    char *pString = charString(pStorageName);
    if (!mStorageList.Lookup(pString, (void*&)*ppStorage)) {
        hr = E_NOINTERFACE;
        }
    if (pString) {delete pString;}
    return hr;
    }

HRESULT 
TestObj::delFromList(const wchar_t *pStorageName)
    {
    HRESULT hr = NOERROR;
    char *pString = charString(pStorageName);
    if (!(mStorageList.RemoveKey(pString))) {
        hr = E_FAIL;
        }
    if (pString) {delete pString;}
    return hr;
    }

HRESULT
TestObj::printList()
    {
    POSITION pos;
    CString key;
    IStorage* pa;
    
    for( pos = mStorageList.GetStartPosition(); pos != NULL; )
        {
        mStorageList.GetNextAssoc( pos, key, (void*&)pa );
#ifdef _DEBUG
        afxDump << key << " : " << pa << "\n";
#endif
        ads_printf(key);
        }
    return NOERROR;
    }

HRESULT 
writeData (IStorage *pStorage) {
    HRESULT hr = NOERROR;
    IStream* pStream = NULL;
    int aNumber, strLength, strWLength;
    char *apString;
    wchar_t *apWideString;
    
    char *pcStgName = new char [NAMELEN];
    
    //  Enter some data.
    ads_getint("\nEnter an int : ", &aNumber);
    ads_getstring(1, "Enter String : ", pcStgName);
    strLength = strlen(pcStgName);
    apString = new char [strLength + 1];
    strcpy(apString, pcStgName);
    
    ads_getstring(1, "Enter Another String : ", pcStgName);
    apWideString = wideString(pcStgName);
    strWLength = wcslen(apWideString);
    
    while (TRUE) {
        if (FAILED(hr = pStorage->CreateStream(L"data", STGM_WRITE_MODE,0,0,&pStream))) {
            ads_printf("CreateStream Failed \n");
            break;
            }
        if (FAILED(hr = pStream->Write(&aNumber, sizeof(aNumber), NULL))) {
            ads_printf("Write Number Failed\n");
            break;
            }
        if (FAILED(hr = pStream->Write(&strLength, sizeof(strLength), NULL))) {
            ads_printf("Write Number Failed\n");
            break;
            }
        if (FAILED(hr = pStream->Write(apString, strLength, NULL))) {
            ads_printf("Write String Failed\n");
            break;
            }
        if (FAILED(hr = pStream->Write(&strWLength, sizeof(strWLength), NULL))) {
            ads_printf("Write Number Failed\n");
            break;
            }
        if (FAILED(hr = pStream->Write(apWideString, sizeof(wchar_t)*strWLength, NULL))) {
            ads_printf("Write Wide String Failed\n");
            break;
            }
        
        break;
        }
    
    pStream->Release();
    delete pcStgName;
    delete apString;
    delete apWideString;
    return hr;
    }

HRESULT 
readData (IStorage *pStorage) {
    HRESULT hr = NOERROR;
    IStream* pStream = NULL;
    
    //  Read some data.
    int aNumber;
    int strLength;
    int strWLength;
    char *apString;
    wchar_t *apWideString;
    
    while (TRUE) {
        if (FAILED(hr = pStorage->OpenStream(L"data", NULL, STGM_OPEN_MODE,0,&pStream))) {
            ads_printf("OpenStream Failed \n");
            break;
            }
        if (FAILED(hr = pStream->Read(&aNumber, sizeof(aNumber), NULL))) {
            ads_printf("Read Number Failed\n");
            break;
            }
        if (FAILED(hr = pStream->Read(&strLength, sizeof(strLength), NULL))) {
            ads_printf("Read Number Failed\n");
            break;
            }
        apString = new char[strLength+1];
        if (FAILED(hr = pStream->Read(apString, strLength, NULL))) {
            ads_printf("Read String Failed\n");
            break;
            }
        apString[strLength] = '\0';
        if (FAILED(hr = pStream->Read(&strWLength, sizeof(strWLength), NULL))) {
            ads_printf("Read Number Failed\n");
            break;
            }
        apWideString = new wchar_t[strWLength+1];
        if (FAILED(hr = pStream->Read(apWideString, sizeof(wchar_t)*strWLength, NULL))) {
            ads_printf("Read Wide String Failed\n");
            break;
            }
        apWideString[strWLength] = '\0';
        
        ads_printf("\n aNumber is:  %d", aNumber);
        ads_printf("\n String Length is: %d", strLength);
        ads_printf("\n aString is:  %s", apString);
        ads_printf("\n Wide String Length is: %d", strWLength);
        char *pString = charString(apWideString);
        ads_printf("\n a Wide String is:  %s", pString);
        if (pString) {delete pString;}
        
        break;
        }
    
    pStream->Release();
    delete apString;
    delete apWideString;
    return hr;
    }

//--------------------------------------------------------------------------------------
//client of the following two functions is responsible for deleting the allocated memory
//--------------------------------------------------------------------------------------
char *charString(const wchar_t *pInWideString)
    {
    
    // first call is just obtaining the size for the new string 
    int i = WideCharToMultiByte(CP_ACP, 0, pInWideString, wcslen(pInWideString), NULL, 0, NULL, NULL);
    char *pString = new char[i+1];
    WideCharToMultiByte(CP_ACP, 0, pInWideString, -1, pString, i, NULL, NULL);
    pString[i] = '\0';
    
    return pString;
    }

wchar_t *wideString(const char *pInCharString)
    {
   
    
    int strLen = MultiByteToWideChar(CP_ACP, 0, pInCharString, -1, NULL, 0);
    wchar_t *pWideString = new wchar_t [strLen + 1];
    MultiByteToWideChar(CP_ACP, 0, pInCharString, -1, pWideString, strLen);
    pWideString[strLen] = '\0';
    
    return pWideString;
    }
//-----------------------------------------------------------------------------------------

void initApp() 
    {
    pTestObj = new TestObj();
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "createStg", "createStg",
        ACRX_CMD_MODAL, createStg);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "closeStg", "closeStg",
        ACRX_CMD_MODAL, closeStg);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "addData", "addData",
        ACRX_CMD_MODAL, addData);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "showData", "showData",
        ACRX_CMD_MODAL, showData);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "openStg", "openStg",
        ACRX_CMD_MODAL, openStg);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "hasStg", "hasStg",
        ACRX_CMD_MODAL, hasStg);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "deleteStg", "deleteStg",
        ACRX_CMD_MODAL, deleteStg);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "saveToXFile", "saveToXFile",
        ACRX_CMD_MODAL, saveToXFile);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "getXFileName", "getXFileName",
        ACRX_CMD_MODAL, getXFileName);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "setStgName", "setStgName",
        ACRX_CMD_MODAL, setStgName);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "getStgName", "getStgName",
        ACRX_CMD_MODAL, getStgName);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "saveToDb", "saveToDb",
        ACRX_CMD_MODAL, saveToDb);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "loadFromXFile", "loadFromXFile",
        ACRX_CMD_MODAL, loadFromXFile);
    acedRegCmds->addCommand("PERSISTANCE_COMMANDS", "listStgOpen", "listStgOpen",
        ACRX_CMD_MODAL, listStgOpen);
    }

void unloadApp() 
    {
    acedRegCmds->removeGroup("PERSISTANCE_COMMANDS");
    delete pTestObj;
    }

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch (msg) {
        case AcRx::kInitAppMsg:
        {    
            if (!acrxServiceIsRegistered("AsdkIStorage"))
                if (!acrxDynamicLinker->loadModule( "cpd.arx", 0 )) {
                    ads_printf("\nUnable to load cpd.arx which must be loaded"
                        " for this program to work.\nPlease load cpd.arx and try"
                        " again.\n");
                    return AcRx::kRetError;
                }
            // increment the dependency counter.
            //
            AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
                ->at("AsdkIStorage");
            if (pSvc)
                pSvc->addDependency();

            acrxDynamicLinker->unlockApplication(pkt);
            initApp();
            break;
        }
        case AcRx::kUnloadAppMsg:
        {
            unloadApp();
            // decrement the dependency counter.
            //
            AcRxService *pSvc = (AcRxService*)acrxServiceDictionary
                ->at("AsdkIStorage");
            if (pSvc)
                pSvc->removeDependency();
        }
    }
    return AcRx::kRetOK;
}

// ===  Tests
void createStg()  //  Create a fresh storage
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;        
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->createStorage(pwStgName, &pStorage))) {
            ads_printf("Create Storage Failed \n");
            break;
            }
        if (FAILED(pTestObj->addToList(pwStgName, pStorage))) break;   
        
        ads_printf("Create Storage Successful \n");
        break;
        }
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void openStg()  //  Open an existing storage
    {
    INIT_VARS;
        IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;        
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (SUCCEEDED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage already open \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->getStorage(pwStgName, &pStorage))) {
            ads_printf("Get Storage Failed \n");
            break;
            }
        if (FAILED(pTestObj->addToList(pwStgName, pStorage))) break;        
        
        ads_printf("Open Storage Successful \n");
        break;
        }
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void hasStg()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;        
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (SUCCEEDED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage already open \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->hasStorage(pwStgName))) {
            ads_printf("Get Storage Failed \n");
            break;
            }
        
        ads_printf("Has Storage Successful \n");
        break;
        }
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void closeStg()
    {
    INIT_VARS;    
    while (TRUE) {
        GET_DATA;        
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage is not open \n");
            break;
            }
        if (FAILED(hr = pTestObj->delFromList(pwStgName))) break;
        pStorage->Release();
        
        ads_printf("Close Storage Successful \n");
        break;
        }
    RELEASE_VARS
    }

void addData ()
    {
    INIT_VARS;
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) break;
        writeData(pStorage);
        break;
        }
    RELEASE_VARS
    }

void showData ()
    {
    INIT_VARS;
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage is not open \n");
            break;
            }
        readData(pStorage);
        break;
        }
    RELEASE_VARS
    }

void deleteStg()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;
        
        if (SUCCEEDED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage in use \n");
            break;
            }
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->purgeStorage(pwStgName))) {
            ads_printf("purgeStorage Failed");
            break;
            }
        if (SUCCEEDED(hr = pCoComDoc->hasStorage(pwStgName))) {
            ads_printf ("has Storage Succeeded after purge \n");
            break;
            }
        
        ads_printf("Purge Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void saveToXFile()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    wchar_t *pwXFile = NULL;
    
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage not open \n");
            break;
            }
        if (RTNORM != ads_getstring(1, "Enter XFile name : ", pcStgName)) break; 
        pwXFile = wideString(pcStgName);
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->saveToExternalFile(pStorage, pwXFile))) {
            ads_printf("save to xfile Failed");
            break;
            }
        ads_printf("save to xfile Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    if (pwXFile) {delete pwXFile;}
    RELEASE_VARS
    }

void getXFileName()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    wchar_t *pwXFile = NULL;
    
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage not open \n");
            break;
            }
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->getExternalFileName(pStorage, &pwXFile))) {
            ads_printf("save to xfile Failed");
            break;
            }
        ads_printf("getXFileName Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    if (pwXFile) {
        char *pString = charString(pwXFile);
        ads_printf("File Name is %s \n", pString);
        delete pString;
        CoTaskMemFree(pwXFile);
        }
    RELEASE_VARS
    }

void getStgName()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage not open \n");
            break;
            }

        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        wchar_t *pName = NULL;
        if (FAILED(hr = pCoComDoc->getStorageName(pStorage, &pName))) {
            ads_printf("getStorageName Failed \n");
            break;
            }
        char *pString = charString(pName);
        ads_printf("Storage Name is %s\n", pString);
        delete pString;
        CoTaskMemFree(pName);
        ads_printf("getDataName Successful \n");
        
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void setStgName()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    wchar_t *pwNewName = NULL;
    
    while (TRUE) {
        GET_DATA;
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage not open \n");
            break;
            }

        if (RTNORM != ads_getstring(1, "Enter New name : ", pcStgName)) break; 
        pwNewName = wideString(pcStgName);

        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        if (FAILED(hr = pCoComDoc->setStorageName(pStorage, pwNewName))) {
            ads_printf("setStorageName Failed");
            break;
            }

        if (FAILED(hr = pTestObj->delFromList(pwStgName))) break;
        if (FAILED(hr = pTestObj->addToList(pwNewName, pStorage))) break;

        ads_printf("setStgName Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    if (pwNewName) {delete pwNewName;}
    RELEASE_VARS
    }

void saveToDb()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    
    while (TRUE) {
        GET_DATA;        
        if (FAILED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage not open \n");
            break;
            }
        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        
        if (FAILED(hr = pCoComDoc->saveToDb(pStorage))) {
            ads_printf("saveToDb Failed \n");
            break;
            }
        ads_printf("saveToDb is Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    RELEASE_VARS
    }

void loadFromXFile()
    {
    INIT_VARS;
    IAcCoCompoundDoc *pCoComDoc = NULL;
    wchar_t *pwXFile = NULL;
    
    while (TRUE) {
        GET_DATA;        
        if (SUCCEEDED(hr = pTestObj->lookupList(pwStgName, &pStorage))) {
            ads_printf("Storage in use \n");
            break;
            }
        hr = NOERROR;

        if (RTNORM != ads_getstring(1, "Enter XFile : ", pcStgName)) break; 
        pwXFile = wideString(pcStgName);

        if (FAILED(hr = accoGetCompoundDoc(&pCoComDoc))) {
            ads_printf ("accoGetCompoundDoc Failed \n");
            break;
            }
        
        if (FAILED(hr = pCoComDoc->loadFromExternalFile(pwXFile, pwStgName))) {
            ads_printf("loadFromExternalFile Failed \n");
            break;
            }
        ads_printf("loadFromExternalFile is Successful \n");
        break;
        }
    
    if (pCoComDoc) pCoComDoc->Release();
    if (pStorage) pStorage->Release();
    if (pwXFile) {delete pwXFile;}
    RELEASE_VARS
    }

void listStgOpen()
    {
    pTestObj->printList();
    }
