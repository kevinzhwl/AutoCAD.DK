// Next available MSG number is   1
//
// (C) Copyright 1992-1997 by Autodesk, Inc.
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

struct AcadApp
{
    enum LoadReasons {
        kOnProxyDetection    = 0x01,
        kOnAutoCADStartup    = 0x02,
        kOnCommandInvocation = 0x04,
        kOnLoadRequest       = 0x08,
        kLoadDisabled        = 0x10
    };

    enum ErrorStatus {
        eOk		= 0,
        eInvalidKey     = 1,
        eInvalidSubKey  = 2,
        eKeyNotFound    = 3,
        eOutOfMemory    = 4,
        eInvalidValue   = 5,
        eValueNotFound  = 6,
        eKeyExists      = 7,
        eRegAccessDenied= 8,
        eRejected       = 9
    };
};





class AcRxDynamicLinker: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxDynamicLinker);

    virtual void*          getSymbolAddress (const char* serviceName,
                                             const char* symbol) const = 0;
    virtual Adesk::Boolean initListedModules(const char* fileName) = 0;
    virtual Adesk::Boolean loadModule       (const char* fileName, int printit) = 0;

    virtual Adesk::Boolean loadApp          (const char * appName,
                                             AcadApp::LoadReasons al,
                                             int printit) = 0;

    virtual AcRxObject*    registerService  (char* serviceName,
					     AcRxService* serviceObj) = 0;
    virtual Adesk::Boolean unloadModule     (const char* fileName) = 0;
    virtual Adesk::Boolean unloadApp        (const char * appName) = 0;

    virtual void           addReactor       (AcRxDLinkerReactor* newReactor) =0;

    virtual void           removeReactor    (AcRxDLinkerReactor* oldReactor) =0;

    virtual int            isApplicationLocked(const char* modulename) const =0;
    virtual int            lockApplication  (void* appId) const = 0;
    virtual int            unlockApplication(void* appId) const = 0;
    virtual const char     *ProductKey      () const = 0;
    virtual Adesk::UInt32  ProductLcid() const =0;

};


//  The kernel creates the one and only dynamic linker, at
//
#define acrxDynamicLinker                                               \
AcRxDynamicLinker::cast(acrxSysRegistry()->at(ACRX_DYNAMIC_LINKER))

class AcRxDLinkerReactor: public AcRxObject
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
    virtual void rxAppLoaded(const char * moduleName);
    virtual void rxAppUnloaded(const char * moduleName);
};


#endif
