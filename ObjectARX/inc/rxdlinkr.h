//
//
// (C) Copyright 1992-2007 by Autodesk, Inc.
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

#ifndef _rxdlinkr_h
#define _rxdlinkr_h 1

class AcRxDLinkerReactor;
class AcRxService;

#include "rxobject.h"
#include "AdAChar.h"
#pragma pack (push, 8)

struct AcadApp
{
    enum LoadReasons {
        kOnProxyDetection       = 0x01,
        kOnAutoCADStartup       = 0x02,
        kOnCommandInvocation    = 0x04,
        kOnLoadRequest          = 0x08,
        kLoadDisabled           = 0x10,
        kTransparentlyLoadable  = 0x20,
        kOnIdleLoad             = 0x40
    };

    enum ErrorStatus {
        eOk             = 0,
        eInvalidKey     = 1,
        eInvalidSubKey  = 2,
        eKeyNotFound    = 3,
        eOutOfMemory    = 4,
        eInvalidValue   = 5,
        eValueNotFound  = 6,
        eKeyExists      = 7,
        eRegAccessDenied= 8,
        eRejected       = 9,
        eUnknownError   = 10
    };
};





class ADESK_NO_VTABLE AcRxDynamicLinker: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxDynamicLinker);

    virtual void*          getSymbolAddress (const ACHAR * serviceName,
                                             const char * symbol) const = 0;
#ifdef AD_UNICODE
    // Overload it for convenience of callers that want to
    // put _T() around all literals.
    virtual void*          getSymbolAddress (const ACHAR * serviceName,
                                             const ACHAR * symbol) const = 0;
#endif

    virtual bool           initListedModules(const ACHAR * fileName) = 0;

    virtual bool           loadModule       (const ACHAR * fileName, 
                                             bool printit,
                                             bool asCmd=false) = 0;
    virtual bool           loadApp          (const ACHAR  * appName,
                                             AcadApp::LoadReasons al,
                                             bool printit,
                                             bool asCmd=false) = 0;

    virtual AcRxObject*    registerService  (const ACHAR * serviceName,
                                             AcRxService* serviceObj) = 0;

    virtual bool           unloadModule     (const ACHAR * fileName,
                                            bool asCmd=false) = 0;
    virtual bool           unloadApp        (const ACHAR * appName,
                                            bool asCmd=false) = 0;

    virtual void           addReactor       (AcRxDLinkerReactor* newReactor) =0;

    virtual void           removeReactor    (AcRxDLinkerReactor* oldReactor) =0;

    virtual bool           isApplicationLocked(const ACHAR * modulename) const =0;
    virtual bool           lockApplication  (void* appId) const = 0;
    virtual bool           unlockApplication(void* appId) const = 0;

    virtual bool           isAppMDIAware(const ACHAR * modulename) const =0;
    virtual bool           registerAppMDIAware(void* appId) const =0;
    virtual bool           registerAppNotMDIAware(void* appId) const =0;
 
    virtual bool           isAppBusy(const ACHAR * modulename) const =0;
    virtual void           setAppBusy(const ACHAR * modulename, bool bBusyFlag) const =0;

    virtual const ACHAR    *ProductKey      () const = 0;
    virtual Adesk::UInt32  ProductLcid() const =0;

};


//  The kernel creates the one and only dynamic linker, at
//
#define acrxDynamicLinker                                               \
AcRxDynamicLinker::cast(acrxSysRegistry()->at(ACRX_DYNAMIC_LINKER))

class ADESK_NO_VTABLE AcRxDLinkerReactor: public AcRxObject
//
// Class defining notification events from the dynamic linker,
// specifically the loading and unloading of Arx applications.
//
// Recipients of these calls can and should also
// check the registered services, class and objects to find out
// what happened to logical elements of the system, rather
// than be bound to file name.
//
{
  public:
    ACRX_DECLARE_MEMBERS(AcRxDLinkerReactor);

    virtual void rxAppWillBeLoaded(const ACHAR  * moduleName);
    virtual void rxAppLoaded(const ACHAR  * moduleName);
    virtual void rxAppLoadAborted(const ACHAR  * moduleName);

    virtual void rxAppWillBeUnloaded(const ACHAR  * moduleName);
    virtual void rxAppUnloaded(const ACHAR  * moduleName);
    virtual void rxAppUnloadAborted(const ACHAR  * moduleName);
};


#pragma pack (pop)
#endif
