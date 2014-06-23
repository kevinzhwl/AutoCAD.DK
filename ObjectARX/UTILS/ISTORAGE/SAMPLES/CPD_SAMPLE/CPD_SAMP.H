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

#ifndef __CPD_SAMP_H__
#define __CPD_SAMP_H__

#define STGM_WRITE_MODE STGM_DIRECT | STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE
#define STGM_OPEN_MODE STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE

#define NAMELEN 50
#define NUMLIST 5

class TestObj
    {
    public:
        TestObj();
        ~TestObj();
        HRESULT addToList(const wchar_t *, IStorage*);
        HRESULT lookupList(const wchar_t *, IStorage**);
        HRESULT delFromList(const wchar_t *);
        HRESULT printList();
        
    private:
        CMapStringToPtr mStorageList;
    };

//  Command Functions
void createStg();
void closeStg();
void addData();
void showData();
void openStg();
void hasStg();
void deleteStg();
void saveToXFile();
void getXFileName();
void loadFromXFile();
void getStgName();
void setStgName();
void saveToDb();
void loadFromXFile();
void listStgOpen();

char *charString(const wchar_t *pInWideString);
wchar_t *wideString(const char *pString);
void initApp();
void unloadApp();
HRESULT writeData(IStorage *);
HRESULT readData(IStorage *);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

#endif //__CPD_SAMP_H__
