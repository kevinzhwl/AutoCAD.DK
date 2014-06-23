#ifndef AD_DBIDMAP_H
#define AD_DBIDMAP_H 1
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
// DESCRIPTION:  Mapping class for object id's.

#include "acdb.h"
#include "rxobject.h"

class AcDbDatabase;

class AcDbIdPair
{
public:
    AcDbIdPair();
    AcDbIdPair(const AcDbIdPair&);
    AcDbIdPair(AcDbObjectId key, AcDbObjectId value,
	Adesk::Boolean isCloned,
	Adesk::Boolean isPrimary = Adesk::kFalse,
	Adesk::Boolean isOwnerXlated = Adesk::kTrue);

    AcDbObjectId   key() const;
    AcDbObjectId   value() const;
    Adesk::Boolean isCloned() const;
    Adesk::Boolean isPrimary() const;
    Adesk::Boolean isOwnerXlated() const;

    void 	   setKey(AcDbObjectId);
    void	   setValue(AcDbObjectId);
    void	   setIsCloned(Adesk::Boolean isCloned);
    void	   setIsPrimary(Adesk::Boolean isPrimary);
    void	   setIsOwnerXlated(Adesk::Boolean isOwnerXlated);

private:
    AcDbObjectId   mKey;
    AcDbObjectId   mValue;
    Adesk::Boolean mIsCloned : 1;
    Adesk::Boolean mIsPrimary : 1;
    Adesk::Boolean mIsOwnerXlated : 1;
};

class AcDbIdMappingIter;
class AcDbImpIdMapping;
class AcDbImpIdMappingIter;

class AcDbIdMapping: public  AcRxObject
{
public:
    AcDbIdMapping();
    virtual ~AcDbIdMapping();
    ACRX_DECLARE_MEMBERS(AcDbIdMapping);

    virtual Acad::ErrorStatus		assign(const AcDbIdPair&);
    virtual Adesk::Boolean		compute(AcDbIdPair&) const;
    virtual Adesk::Boolean              change(const AcDbIdPair&);
    virtual Adesk::Boolean    		del(AcDbObjectId key);

	    Acad::ErrorStatus	destDb(AcDbDatabase*& db) const;
	    Acad::ErrorStatus	setDestDb(AcDbDatabase* db);
	    Acad::ErrorStatus	origDb(AcDbDatabase*& db) const;

	    AcDb::DeepCloneType deepCloneContext() const;

    virtual void                copyFrom(const AcRxObject* other);

private:
    friend class AcDbSystemInternals;
    friend class AcDbImpIdMappingIter;
    AcDbIdMapping(const AcDbIdMapping&);
    AcDbIdMapping& operator= (const AcDbIdMapping&);
    AcDbImpIdMapping* mpImp;
};


class AcDbIdMappingIter: public  AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbIdMappingIter);
    AcDbIdMappingIter(const AcDbIdMapping&);
    virtual ~AcDbIdMappingIter();

    virtual Acad::ErrorStatus	iterateOn(const AcDbIdMapping&);

    virtual void		start();
    virtual Adesk::Boolean 	getMap(AcDbIdPair&);
    virtual Adesk::Boolean 	next();
    virtual Adesk::Boolean	done();

private:
    friend class		AcDbSystemInternals;
    AcDbImpIdMappingIter*	mpImp;
};

inline
AcDbObjectId AcDbIdPair::key() const
{ return mKey; }

inline
AcDbObjectId AcDbIdPair::value() const
{ return mValue; }

inline
Adesk::Boolean AcDbIdPair::isCloned() const
{ return mIsCloned; }

inline
Adesk::Boolean AcDbIdPair::isPrimary() const
{ return mIsPrimary; }

inline
Adesk::Boolean AcDbIdPair::isOwnerXlated() const
{ return mIsOwnerXlated; }

inline
void AcDbIdPair::setKey(AcDbObjectId key)
{ mKey = key; }

inline
void AcDbIdPair::setValue(AcDbObjectId value)
{ mValue = value; }

inline
void AcDbIdPair::setIsCloned(Adesk::Boolean isCloned)
{ mIsCloned = isCloned; }

inline
void AcDbIdPair::setIsPrimary(Adesk::Boolean isPrimary)
{ mIsPrimary = isPrimary; }

inline
void AcDbIdPair::setIsOwnerXlated(Adesk::Boolean isOwnerXlated)
{ mIsOwnerXlated = isOwnerXlated; }

#endif
