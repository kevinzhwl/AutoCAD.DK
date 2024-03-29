//
// (C) Copyright 1997-1999 by Autodesk, Inc. 
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
// appinfo.h
//
// DESCRIPTION: Definition of class AcadAppInfo.  Used as part of the
//              unknown command demand load notification mechanism.

#ifndef _appinfo_h
#define _appinfo_h 1

//#if defined(__cplusplus)

#include "acdb.h"
#include "rxdlinkr.h"
#pragma pack (push, 8)

class AcadAppInfoImp;

class AcadAppInfo: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcadAppInfo);

    enum CmdStatus {
        kNoAction    = 0,
        kRetry       = 1,
        kShowMsg     = 2,
        kNoModule    = 3
    };
    typedef AcadAppInfo::CmdStatus (*LoaderFunPtr)(void *);

    AcadAppInfo();
    virtual ~AcadAppInfo();

    const char *appName();
    void setAppName(const char *);

    const char *regPath();
    void setRegPath(const char *);

    const char *moduleName();
    void setModuleName(const char *);

    const char *appDesc();
    void setAppDesc(const char *);

    int rootAppKey();
    void setRootAppKey(int);

    bool appImplements(const char *);

    AcadApp::ErrorStatus writeToRegistry(bool bObjDbx = false);
    AcadApp::ErrorStatus readFromRegistry();
    AcadApp::ErrorStatus delFromRegistry(bool bObjDbx = false);

    AcadAppInfo::CmdStatus runAppLoader();
    void setAppLoader(LoaderFunPtr);

    AcadApp::LoadReasons loadReason();
    void setLoadReason(AcadApp::LoadReasons);
    AcadApp::ErrorStatus status();

private:
    AcadAppInfoImp	*mpImp;
};

#pragma pack (pop)
//#endif /* defined (__cplusplus) */
#endif /* _appinfo_h */
