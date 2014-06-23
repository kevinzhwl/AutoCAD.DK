#ifndef   _ACTRANS_H
#define   _ACTRANS_H
//
//  (C) Copyright 1993-1996 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION: Header for Transaction Modeler.

#include "rxnames.h"
#include "aced.h"
#include "dbptrar.h"

// Name of Registered Service Object for constructing AutoCAD-specific
// instances.
//
#define AC_TRANSACTION_MANAGER_OBJ    "AcTransactionManager"

class AcTransaction: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransaction);
    virtual 
    Acad::ErrorStatus getObject(AcDbObject*&, 
                                AcDbObjectId   objectId, AcDb::OpenMode, 
                                Adesk::Boolean openErasedObject = Adesk::kFalse) = 0; 

    virtual 
    Acad::ErrorStatus markObjectPageable(AcDbObject* pObject) = 0;
};

class AcTransactionReactor: public AcRxObject 
//
// Reactor for transaction management.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransactionReactor);

    virtual void transactionAboutToStart (int& numTransactions);
    virtual void transactionStarted      (int& numTransactions);
    virtual void transactionAboutToEnd   (int& numTransactions);
    virtual void transactionEnded        (int& numTransactions);
    virtual void transactionAboutToAbort (int& numTransactions);
    virtual void transactionAborted      (int& numTransactions);
    virtual void endCalledOnOutermostTransaction (int& numTransactions);
};

class AcTransactionManager: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransactionManager);

    virtual AcTransaction*      startTransaction() = 0;
    virtual Acad::ErrorStatus   endTransaction  () = 0;
    virtual Acad::ErrorStatus   abortTransaction() = 0;

    virtual int                 numActiveTransactions() = 0;
    virtual AcTransaction*      topTransaction() = 0;
    virtual Acad::ErrorStatus   addNewlyCreatedDBRObject(AcDbObject*, 
                                     Adesk::Boolean add = Adesk::kTrue) = 0;

    virtual Acad::ErrorStatus   getAllObjects(AcDbVoidPtrArray&) = 0;

    virtual Acad::ErrorStatus   queueForGraphicsFlush() = 0;
    virtual Acad::ErrorStatus   enableGraphicsFlush(Adesk::Boolean doEnable) = 0;

    virtual void                flushGraphics() = 0;
 
    virtual void                addReactor(AcTransactionReactor*) = 0;
    virtual void                removeReactor(AcTransactionReactor*) = 0;

    virtual Acad::ErrorStatus   getObject(AcDbObject*&, AcDbObjectId,
                                          AcDb::OpenMode, Adesk::Boolean openErasedObj 
                                          = Adesk::kFalse) = 0; 

    virtual Acad::ErrorStatus   markObjectPageable(AcDbObject* pObject) = 0;
};

extern AcTransactionManager* acTransactionManagerPtr(); 

#define actrTransactionManager  acTransactionManagerPtr()

#endif
