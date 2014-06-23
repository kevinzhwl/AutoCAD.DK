#ifndef   _ACCMD_H
#define   _ACCMD_H
//
//  (C) Copyright 1993-1997 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION: Definitions for the AutoCAD native command definition
//               mechanism.
//

// NOTE: before adding any new command constants here,
// check with the undocumented ACRX_CMD_... constants
// defined in coresrc/command.cpp to make sure that
// there is no overlap.
//
#define ACRX_CMD_MODAL  	    0x00000000
#define ACRX_CMD_TRANSPARENT	0x00000001
#define ACRX_CMD_USEPICKSET	    0x00000002
#define ACRX_CMD_REDRAW	        0x00000004
#define ACRX_CMD_UNDEFINED      0x00000008
#define ACRX_CMD_NOMULTIPLE     0x00000010
#define ACRX_CMD_INPROGRESS	    0x00000400
#define ACRX_CMD_NONEWSTACK     0x00010000  //For internal use only
#define ACRX_CMD_NOINTERNALLOCK	0x00020000

#define ACRX_MAX_CMDNAME_LEN  	64

#define ACRX_COMMAND_DOCK  	"ACAD_REGISTERED_COMMANDS"

typedef void (*AcRxFunctionPtr) ();

struct AcEdCommandStruc {
    AcRxFunctionPtr fcnAddr;
    long            flags;
    void	    *app;
};

#if defined(__cplusplus)

#include "dbmain.h"
#include "rxobject.h"

class AcRxDictionary;

class AcEdCommand: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommand);

    virtual void            commandUndef(Adesk::Boolean undefIt) = 0;
    virtual Adesk::Int32    commandFlags() const = 0;
    virtual AcRxFunctionPtr functionAddr() const = 0;
    virtual void            *commandApp() const = 0;

    virtual const char*     globalName() const = 0;
    virtual const char*     localName() const = 0;

};

class AcEdCommandIterator: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandIterator);

    virtual Adesk::Boolean     done() const = 0;
    virtual Adesk::Boolean     next() = 0;
    virtual const AcEdCommand* command() const = 0;
    virtual const char*        commandGroup() const = 0;
};

#define acedRegCmds \
AcEdCommandStack::cast(acrxSysRegistry()->at(ACRX_COMMAND_DOCK))

class AcEdCommandStack: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandStack);

    virtual Adesk::Boolean    atPut(const char* cmdGroupName,
                                    AcRxDictionary*& cmdsGlobal,
                                    AcRxDictionary*& cmdsLocal) = 0;

    virtual Acad::ErrorStatus addCommand(const char* cmdGroupName,
                                         const char* cmdGlobalName,
                                         const char* cmdLocalName,
                                         Adesk::Int32 commandFlags,
                                         AcRxFunctionPtr FunctionAddr) = 0;

    virtual AcEdCommandIterator* iterator() = 0;

    virtual AcEdCommand* lookupGlobalCmd(const char* cmdName) = 0;
    virtual AcEdCommand* lookupLocalCmd(const char* cmdName) = 0;
    virtual AcEdCommand* lookupCmd(const char* cmdName,
                                   Adesk::Boolean globalFlag) = 0;
    virtual AcEdCommand* lookupCmd(const char* cmdName,
                                   Adesk::Boolean globalFlag,
                                   Adesk::Boolean allGroupsFlag) = 0;
    virtual AcEdCommand* lookupCmd(const char* cmdName,
                                   Adesk::Boolean globalFlag,
                                   Adesk::Boolean allGroupsFlag,
                                   Adesk::Boolean skipUndefed) = 0;

    virtual Acad::ErrorStatus popGroupToTop(const char* cmdGroupName) = 0;

    virtual Acad::ErrorStatus removeCmd(const char* cmdGroupName,
                                        const char* cmdGlobalName) = 0;

    virtual Acad::ErrorStatus removeGroup(const char* groupName) = 0;

};

#endif
#endif
