#ifndef ACDB_XRECORD_H
#define ACDB_XRECORD_H
//
// (C) Copyright 1993-1997 by Autodesk, Inc.
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
// DESCRIPTION: AcDbXrecord class definition.

#define ACDB_XRECORD_CLASS          /*MSG0*/"AcDbXrecord"
#define ACDB_XRECORD_ITERATOR_CLASS /*MSG0*/"AcDbXrecordClass"

#include "dbmain.h"

class AcDbXrecord: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbXrecord);
    AcDbXrecord();
    virtual ~AcDbXrecord();

    // auxDb parameter only useded when working with
    // non-Database-resident instances.

    Acad::ErrorStatus rbChain(resbuf** ppRb, AcDbDatabase* auxDb = NULL) const;
    Acad::ErrorStatus setFromRbChain(resbuf& pRb, AcDbDatabase* auxDb = NULL);

    Adesk::Boolean    isXlateReferences();
    void              setXlateReferences(Adesk::Boolean translate);

    // Overridden methods from AcDbObject
    //
    virtual Acad::ErrorStatus subClose();
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
};

class AcDbImpXrecordIterator;

class AcDbXrecordIterator: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbXrecordIterator);
 
    AcDbXrecordIterator(const AcDbXrecord* pXrecord);
    virtual ~AcDbXrecordIterator();

    void              start();
    Adesk::Boolean    done() const;
    Acad::ErrorStatus next();
    int               curRestype() const;
    Acad::ErrorStatus getCurResbuf(resbuf& outItem, AcDbDatabase* db) const;

protected:
    AcDbXrecordIterator() {};
private:
    friend class AcDbXrecord;
    friend class AcDbImpXrecord;
    AcDbImpXrecordIterator* mpImpIter;
};

#endif
