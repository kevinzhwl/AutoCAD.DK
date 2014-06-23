#ifndef NOTFSAMP_H
#define NOTFSAMP_H

// Next available MSG number is   1
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
// ========= notfsamp.h:  Arx Notification Sample ================ 
//
//
// DESCRIPTION:
//
// This file derives a set of reactors from the AutoCAD transient 
// reactor classes:
//    AcRxDLinkerReactor
//    AcEditorReactor
//    AcDbDatabaseReactor
//    AcTransactionReactor
//    AcDbObjectReactor
//      AcDbEntityReactor
// 
// It also derives a persistent reactor object from AcDbObject.
//
// Finally, reactors derived from AcEditorReactor and AcDbDatabase
// reactor are created for use in the "inscribe" command of notfsamp.
//
// These classes are implemented in the file notfsamp.cc, which also
// demonstrates their use.  
// 


#include "dbmain.h"
#include "aced.h"
#include "actrans.h"

class AsdkSimpleObjReactor : public AcDbObjectReactor 
// This minimal reactor implements only a few of the possible
// methods from AcDbObjectReactor. 
//
{

  public:
    virtual void erased(const AcDbObject *pDbObj,
                              Adesk::Boolean erasing = Adesk::kTrue);
    virtual void modified(const AcDbObject *pDbObj);
    virtual void copied(const AcDbObject *pDbObj, const AcDbObject* pNewObj);

  private:

    // Most Real reactors will have the address of their owner,
    // if they have one.
};

class AsdkAppReactor : public AcRxDLinkerReactor
{

  public:

    virtual void rxAppLoaded(const char *pModuleName);
    virtual void rxAppUnloaded(const char *pModuleName);
};

class AsdkTransReactor : public AcTransactionReactor
{

  public:

    virtual void transactionStarted(int& numTransactions);
    virtual void transactionEnded(int& numTransactions);
    virtual void transactionAborted(int& numTransactions);
    virtual void endCalledOnOutermostTransaction(int& numTransactions);
};

class AsdkSysVarReactor : public AcEditorReactor 
// This reactor implements only the SysVar related notification
// reactions from AcEditorReactor.
//
{

  public:

    virtual void sysVarChanged(const char          *pVarName,
                                     Adesk::Boolean success);
    virtual void sysVarWillChange(const char *pVarName);
};


class AsdkCommandReactor : public AcEditorReactor 
// This reactor implements only the Command related notification 
// reactions from AcEditorReactor.
//
{

  public:

    virtual void commandWillStart(const char *pCmdStr);
    virtual void commandEnded(const char *pCmdStr);
    virtual void commandCancelled(const char *pCmdStr);
    virtual void commandFailed(const char *pCmdStr);
};

class AsdkUnknownCommandReactor : public AcEditorReactor 
// This reactor implements only the UnknownCommand notification 
// reaction from AcEditorReactor.
//
{

  public:

    virtual void unknownCommand  (const char* cmdStr, AcDbVoidPtrArray *al);
};

class AsdkDbReactor : public AcDbDatabaseReactor 
{

  public:

    virtual void objectAppended(const AcDbDatabase *pDwg,
                                const AcDbObject   *pDbObj);
    virtual void objectModified(const AcDbDatabase *pDwg,
                                const AcDbObject   *pDbObj);
    virtual void objectErased(const AcDbDatabase   *pDwg,
                              const AcDbObject     *pDbObj,
                                    Adesk::Boolean erased);
};

class AsdkPersReactor : public AcDbObject
{
    public:

    ACRX_DECLARE_MEMBERS(AsdkPersReactor);
    AsdkPersReactor();
    ~AsdkPersReactor();
    virtual void erased(const AcDbObject    *pObj, 
                              Adesk::Boolean erasing = Adesk::kTrue);
    virtual void copied(const AcDbObject *pObj, const AcDbObject *pNewObj);
    virtual void custom();
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler *pFiler) const;
    Acad::ErrorStatus dwgInFields(AcDbDwgFiler *pFiler);
};

class AsdkInscribeReactor : public AcEditorReactor
{
    public:

    virtual void commandEnded(const char *cmdStr);
};

class AsdkDbInscribeReactor : public AcDbDatabaseReactor
{
    public:

    virtual void objectAppended(const AcDbDatabase *pDb, 
                                const AcDbObject   *pObj);
    
};

#endif // NOTFSAMP_H
