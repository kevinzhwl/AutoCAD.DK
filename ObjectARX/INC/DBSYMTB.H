#ifndef AD_DBSYMTB_H
#define AD_DBSYMTB_H
//
// Copyright 1997 by Autodesk, Inc.
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
// DESCRIPTION: Exported protocol for AutoCAD's built in symbol
//		tables, thier table  specific record types, and
//		thier iterators.

#include "dbmain.h"
#include "dbdict.h"
#include "dbdate.h"
#include "gevec2d.h"

#ifdef target
# undef target 
#endif

class AcDbSymbolTableRecord;
class AcDbSymbolTableIterator;

class AcDbSymbolTable: public AcDbObject
//
// (... and Subclasses)
//
// Note that there is both overloading of functions within each
// class defined by these macros and overriding of non virtual
// functions between classes.  The overriding of these functions
// is necessary to allow some member functions to take arguments
// that are appropriate for a given table.
//
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSymbolTable);
    AcDbSymbolTable();
    virtual ~AcDbSymbolTable();

    Acad::ErrorStatus getAt (const char* entryName,
                             AcDbSymbolTableRecord*& pRec,
                             AcDb::OpenMode,
                             Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt (const char* entryName,
                             AcDbObjectId& recordId,
                             Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has(const char* name) const;
    Acad::ErrorStatus newIterator(AcDbSymbolTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add(AcDbSymbolTableRecord*);
    Acad::ErrorStatus add(AcDbObjectId& recordId, AcDbSymbolTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbSymbolTable);

class AcDbBlockTableRecord;
class AcDbBlockTableIterator;

class AcDbBlockTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBlockTable);
    AcDbBlockTable();
    virtual ~AcDbBlockTable();
    Acad::ErrorStatus getAt (const char* entryName,
                             AcDbBlockTableRecord*& pRec,
                             AcDb::OpenMode,
                             Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt (const char* entryName,
                             AcDbObjectId& recordId,
                             Adesk::Boolean getErasedRec = Adesk::kFalse) const;
    Adesk::Boolean    has   (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbBlockTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add   (AcDbBlockTableRecord*);
    Acad::ErrorStatus add   (AcDbObjectId& recordId, AcDbBlockTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbBlockTable);

class AcDbLayerTableRecord;
class AcDbLayerTableIterator;

class AcDbLayerTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerTable);
    AcDbLayerTable();
    virtual ~AcDbLayerTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbLayerTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbLayerTableIterator*& pIterator,
                                 Adesk::Boolean atBeginning = Adesk::kTrue,
                                 Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add (AcDbLayerTableRecord*);
    Acad::ErrorStatus add (AcDbObjectId& recordId, AcDbLayerTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLayerTable);

class AcDbTextStyleTableRecord;
class AcDbTextStyleTableIterator;

class AcDbTextStyleTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTextStyleTable);
    AcDbTextStyleTable();
    virtual ~AcDbTextStyleTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbTextStyleTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt (const char* entryName,
                             AcDbObjectId& recordId,
                             Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has   (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbTextStyleTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add   (AcDbTextStyleTableRecord*);
    Acad::ErrorStatus add   (AcDbObjectId&  recordId, AcDbTextStyleTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbTextStyleTable);

class AcDbLinetypeTableRecord;
class AcDbLinetypeTableIterator;

class AcDbLinetypeTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinetypeTable);
    AcDbLinetypeTable();
    virtual ~AcDbLinetypeTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbLinetypeTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRec = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbLinetypeTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add  (AcDbLinetypeTableRecord*);
    Acad::ErrorStatus add  (AcDbObjectId& recordId, AcDbLinetypeTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLinetypeTable);

class AcDbAbstractViewTableRecord;
class AcDbAbstractViewTableIterator;

class AcDbAbstractViewTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbAbstractViewTable);
    AcDbAbstractViewTable();
    virtual ~AcDbAbstractViewTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbAbstractViewTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbAbstractViewTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add  (AcDbAbstractViewTableRecord*);
    Acad::ErrorStatus add  (AcDbObjectId&  recordId, AcDbAbstractViewTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbAbstractViewTable);

class AcDbViewTableRecord;
class AcDbViewTableIterator;

class AcDbViewTable: public AcDbAbstractViewTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewTable);
    AcDbViewTable();
    virtual ~AcDbViewTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbViewTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRec = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbViewTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add  (AcDbViewTableRecord*);
    Acad::ErrorStatus add  (AcDbObjectId&  recordId, AcDbViewTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbViewTable);

class AcDbUCSTableRecord;
class AcDbUCSTableIterator;

class AcDbUCSTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUCSTable);
    AcDbUCSTable();
    virtual ~AcDbUCSTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbUCSTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbUCSTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add  (AcDbUCSTableRecord*);
    Acad::ErrorStatus add  (AcDbObjectId&  recordId, AcDbUCSTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbUCSTable);

class AcDbViewportTableRecord;
class AcDbViewportTableIterator;

class AcDbViewportTable: public AcDbAbstractViewTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewportTable);
    AcDbViewportTable();
    virtual ~AcDbViewportTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbViewportTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRecord = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbViewportTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus add  (AcDbViewportTableRecord*);
    Acad::ErrorStatus add  (AcDbObjectId& recordId, AcDbViewportTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbViewportTable);

class AcDbRegAppTableRecord;
class AcDbRegAppTableIterator;

class AcDbRegAppTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbRegAppTable);
    AcDbRegAppTable();
    virtual ~AcDbRegAppTable();
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbRegAppTableRecord*& pRec,
                            AcDb::OpenMode,
                            Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus getAt(const char* entryName,
                            AcDbObjectId& recordId,
                            Adesk::Boolean getErasedRec = Adesk::kFalse) const;
    Adesk::Boolean    has  (const char* name) const;
    Acad::ErrorStatus newIterator(AcDbRegAppTableIterator*& pIterator,
                                  Adesk::Boolean atBeginning = Adesk::kTrue,
                                  Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus   add     (AcDbRegAppTableRecord*);
    Acad::ErrorStatus   add     (AcDbObjectId&  recordId, AcDbRegAppTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbRegAppTable);

class AcDbDimStyleTableRecord;
class AcDbDimStyleTableIterator;

class AcDbDimStyleTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimStyleTable);
    AcDbDimStyleTable();
    virtual ~AcDbDimStyleTable();
    Acad::ErrorStatus   getAt   (const char* entryName,
                                 AcDbDimStyleTableRecord*& pRec,
                                 AcDb::OpenMode,
                                 Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus   getAt   (const char* entryName,
                                 AcDbObjectId& recordId,
                                Adesk::Boolean getErasedRec = Adesk::kFalse) const;
    Adesk::Boolean      has     (const char* name) const;
    Acad::ErrorStatus   newIterator(AcDbDimStyleTableIterator*& pIterator,
                                    Adesk::Boolean atBeginning = Adesk::kTrue,
                                    Adesk::Boolean skipDeleted = Adesk::kTrue) const;
    Acad::ErrorStatus   add     (AcDbDimStyleTableRecord*);
    Acad::ErrorStatus   add     (AcDbObjectId&  recordId, AcDbDimStyleTableRecord*);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbDimStyleTable);

///// AcDbSymbolTableIterator
//
// This class is responsible for iterating over the records in a symbol
// table.
//
// This is a completely "generic" symbol table iterator in that it can 
// be used to iterate over the contents of any AcDbSymbolTable subclass.
// However, symbol table specific iterators are defined below.
//
// One major item of note.  The creation of one of these iterators
// requires the opening (for read) of the table being iterated over.
// This read stays in effect until the iterator is destroyed.
//
class AcDbSymbolTableIterator
{
public:
    virtual ~AcDbSymbolTableIterator();

    void 		start	(Adesk::Boolean atBeginning = Adesk::kTrue,
				 Adesk::Boolean skipDeleted = Adesk::kTrue);

    Adesk::Boolean	done	() const;


    Acad::ErrorStatus 	getRecordId(AcDbObjectId& id) const;

    Acad::ErrorStatus	getRecord(AcDbSymbolTableRecord*& pRec,
				 AcDb::OpenMode,
				 Adesk::Boolean openErasedRec = Adesk::kFalse) const;

    void	 	step    (Adesk::Boolean forward = Adesk::kTrue,
				 Adesk::Boolean skipDeleted = Adesk::kTrue);

    Acad::ErrorStatus   seek	(AcDbObjectId id);

    Acad::ErrorStatus   seek	(const AcDbSymbolTableRecord*);
protected:
    void* mpImp;
    AcDbSymbolTableIterator();
    friend AcDbSymbolTable;
};

class AcDbBlockTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbBlockTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbBlockTableRecord*);

protected:
    AcDbBlockTableIterator();
    friend class AcDbBlockTable;
};

class AcDbLayerTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbLayerTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbLayerTableRecord*);

protected:
    AcDbLayerTableIterator();
    friend class AcDbLayerTable;
};

class AcDbTextStyleTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbTextStyleTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbTextStyleTableRecord*);

protected:
    AcDbTextStyleTableIterator();
    friend class AcDbTextStyleTable;
};

class AcDbLinetypeTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbLinetypeTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbLinetypeTableRecord*);

protected:
    AcDbLinetypeTableIterator();
    friend class AcDbLinetypeTable;
};

class AcDbAbstractViewTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbAbstractViewTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbAbstractViewTableRecord*);

protected:
    AcDbAbstractViewTableIterator();
    friend class AcDbAbstractViewTable;
};

class AcDbViewTableIterator : public AcDbAbstractViewTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbViewTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbViewTableRecord*);

protected:
    AcDbViewTableIterator();
    friend class AcDbViewTable;
};

class AcDbUCSTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbUCSTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbUCSTableRecord*);

protected:
    AcDbUCSTableIterator();
    friend class AcDbUCSTable;
};

class AcDbViewportTableIterator : public AcDbAbstractViewTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbViewportTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbViewportTableRecord*);

protected:
    AcDbViewportTableIterator();
    friend class AcDbViewportTable;
};

class AcDbRegAppTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbRegAppTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbRegAppTableRecord*);

protected:
    AcDbRegAppTableIterator();
    friend class AcDbRegAppTable;
};

class AcDbDimStyleTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbDimStyleTableRecord*&, AcDb::OpenMode,
			Adesk::Boolean openErasedRec = Adesk::kFalse) const;
    Acad::ErrorStatus seek(AcDbObjectId);
    Acad::ErrorStatus seek(const AcDbDimStyleTableRecord*);

protected:
    AcDbDimStyleTableIterator();
    friend class AcDbDimStyleTable;
};

class AcDbSymbolTableRecord: public  AcDbObject
{
public:
    AcDbSymbolTableRecord();
    virtual ~AcDbSymbolTableRecord();

    ACDB_DECLARE_MEMBERS(AcDbSymbolTableRecord);

    Acad::ErrorStatus getName(char*&) const;
    Acad::ErrorStatus getName(const char*&) const;
    Acad::ErrorStatus setName(const char*);

    Adesk::Boolean isDependent() const;

    Adesk::Boolean isResolved() const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbSymbolTableRecord);


class AcDbBlockTableRecordIterator
{
public:
    virtual ~AcDbBlockTableRecordIterator();

    void 	      start (Adesk::Boolean atBeginning = Adesk::kTrue,
		   	     Adesk::Boolean skipDeleted = Adesk::kTrue);

    Adesk::Boolean    done  () const;

    Acad::ErrorStatus getEntityId (AcDbObjectId& entityId) const;

    Acad::ErrorStatus getEntity(AcDbEntity*& pEntity, AcDb::OpenMode,
				Adesk::Boolean openErasedEntity = Adesk::kFalse) const;

    AcDbBlockTableRecord* blockTableRecord() const;

    void	      step (Adesk::Boolean forward = Adesk::kTrue,
			    Adesk::Boolean skipDeleted = Adesk::kTrue);

    Acad::ErrorStatus seek (AcDbObjectId id);

    Acad::ErrorStatus seek (const AcDbEntity* entity);

protected:
    class AcDbImpBlockTableRecordIterator* mpImp;
private:
    AcDbBlockTableRecordIterator();
    friend class AcDbImpBlockTableRecord;
};

class AcDbIdBuffer;

class AcDbBlockReferenceIdIterator
{
public:
    ~AcDbBlockReferenceIdIterator();

    void              start () { mPos = 0; }
        
    Adesk::Boolean    done  () const;

    Acad::ErrorStatus getBlockReferenceId (AcDbObjectId& id) const;

    Acad::ErrorStatus getDatabase (AcDbDatabase*&) const;

    Acad::ErrorStatus getBlockReference(AcDbBlockReference*&,
				        AcDb::OpenMode,
					Adesk::Boolean openErasedEntity = Adesk::kFalse) const;

    void              step () { mPos++; }

    Acad::ErrorStatus seek (AcDbObjectId id);

private:
    Adesk::Boolean    getId (AcDbObjectId& id) const;

    AcDbBlockReferenceIdIterator(AcDbIdBuffer* pBuf,
                                 const AcDbObjectIdArray* pAry);
    friend class AcDbBlockTableRecord;

    int		      mPos;
    int               mBufLen;
    AcDbIdBuffer*     mpBuf;
    const AcDbObjectIdArray* mpAry;
};

class AcDbBlockTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBlockTableRecord);

    AcDbBlockTableRecord();
    virtual ~AcDbBlockTableRecord();

    Acad::ErrorStatus appendAcDbEntity(AcDbEntity* entity);

    Acad::ErrorStatus appendAcDbEntity(AcDbObjectId& pOutputId, AcDbEntity* entity);

    Acad::ErrorStatus newIterator(
	AcDbBlockTableRecordIterator*& pIterator,
	Adesk::Boolean atBeginning = Adesk::kTrue,
	Adesk::Boolean skipDeleted = Adesk::kTrue);

    Acad::ErrorStatus pathName(char*& pPath) const;
    Acad::ErrorStatus setPathName(const char* pathStr);
	 
    AcGePoint3d       origin() const;
    Acad::ErrorStatus setOrigin(const AcGePoint3d& pt);

    Acad::ErrorStatus openBlockBegin(AcDbBlockBegin*& pBlockBegin,
				     AcDb::OpenMode   openMode);
 
    Acad::ErrorStatus openBlockEnd(AcDbBlockEnd*& pBlockEnd,
				   AcDb::OpenMode openMode);

    Adesk::Boolean    hasAttributeDefinitions() const;

    Adesk::Boolean    isAnonymous() const;

    Adesk::Boolean    isFromExternalReference() const;

    Adesk::Boolean    isFromOverlayReference() const;

#ifdef ACDBLIB
    // These four functions are not available in the ARX API
    //
    void              setHasAttributeDefinitions(Adesk::Boolean);
    void              setIsAnonymous(Adesk::Boolean);
    void              setIsFromExternalReference(Adesk::Boolean);
    void              setIsFromOverlayReference(Adesk::Boolean);
#endif /* ACDBLIB */


    Acad::ErrorStatus newBlockReferenceIdIterator(AcDbBlockReferenceIdIterator*&) const;
    AcDbDatabase*     xrefDatabase(Adesk::Boolean incUnres = Adesk::kFalse) const;

    Adesk::Boolean    isUnloaded() const;
    Acad::ErrorStatus setIsUnloaded(Adesk::Boolean isUnloaded);

    AcDb::XrefStatus  xrefStatus() const;

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbBlockTableRecord);

class AcDbLayerTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerTableRecord);

    AcDbLayerTableRecord();
    virtual ~AcDbLayerTableRecord();

    Adesk::Boolean isFrozen() const;
    Acad::ErrorStatus setIsFrozen(Adesk::Boolean);

    Adesk::Boolean isOff() const;
    void           setIsOff(Adesk::Boolean);

    Adesk::Boolean VPDFLT() const;
    void           setVPDFLT(Adesk::Boolean);

    Adesk::Boolean isLocked() const;
    void           setIsLocked(Adesk::Boolean);

    AcCmColor      color() const;
    void           setColor(const AcCmColor &color);

    AcDbObjectId   linetypeObjectId() const;
    void           setLinetypeObjectId(AcDbObjectId);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLayerTableRecord);

// Utility for changing Layer Table Records in the Current Drawing
Acad::ErrorStatus applyCurDwgLayerTableChanges();

// AcDbTextStyleTableRecord:

class AcDbTextStyleTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTextStyleTableRecord);

    AcDbTextStyleTableRecord();
    virtual ~AcDbTextStyleTableRecord();

    Adesk::Boolean isShapeFile() const;
    void setIsShapeFile(Adesk::Boolean);

    Adesk::Boolean isVertical() const;
    void setIsVertical(Adesk::Boolean);

    double textSize() const;
    Acad::ErrorStatus setTextSize(double size);

    double xScale() const;
    Acad::ErrorStatus setXScale(double xScale);

    double obliquingAngle() const;
    Acad::ErrorStatus setObliquingAngle(double obliquingAngle);

    Adesk::UInt8 flagBits() const;
    void setFlagBits(Adesk::UInt8 flagBits);

    double priorSize() const;
    Acad::ErrorStatus setPriorSize(double priorSize);

    Acad::ErrorStatus fileName(char*&) const;
    Acad::ErrorStatus fileName(const char*&) const;
    Acad::ErrorStatus setFileName(const char*);

    Acad::ErrorStatus bigFontFileName(char*&) const;
    Acad::ErrorStatus bigFontFileName(const char*&) const;
    Acad::ErrorStatus setBigFontFileName(const char*);

    Acad::ErrorStatus setFont(const char* pTypeface, BOOL bold, BOOL italic, 
		              int charset, int pitchAndFamily);
    Acad::ErrorStatus font   (char*& pTypeface, BOOL& bold, BOOL& italic,
	                      int& charset, int& pitchAndFamily) const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbTextStyleTableRecord);

class AcDbLinetypeTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinetypeTableRecord);

    AcDbLinetypeTableRecord();
    virtual ~AcDbLinetypeTableRecord();

    Acad::ErrorStatus asciiDescription(char*&) const;
    Acad::ErrorStatus asciiDescription(const char*&) const;
    Acad::ErrorStatus setAsciiDescription(const char*);

    double patternLength() const;
    void   setPatternLength(double);

    int    numDashes() const;
    void   setNumDashes(int count);

    double dashLengthAt(int index ) const;
    void   setDashLengthAt(int index , double);

    AcDbObjectId shapeStyleAt(int index) const;
    void         setShapeStyleAt(int index, AcDbObjectId);

    int    shapeNumberAt(int index) const;
    void   setShapeNumberAt(int index, int);

    AcGeVector2d shapeOffsetAt(int index) const;
    void         setShapeOffsetAt(int index, const AcGeVector2d&);

    double shapeScaleAt(int index) const;
    void   setShapeScaleAt(int index, double);

    Adesk::Boolean isScaledToFit() const;
    void           setIsScaledToFit(Adesk::Boolean);

    Adesk::Boolean shapeIsUcsOrientedAt(int index) const;
    void           setShapeIsUcsOrientedAt(int index, Adesk::Boolean);

    double         shapeRotationAt(int index) const;
    void           setShapeRotationAt(int index, double);

    Acad::ErrorStatus textAt(int index, char*&) const;
    Acad::ErrorStatus textAt(int index, const char*&) const;
    Acad::ErrorStatus setTextAt(int index, const char*);

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLinetypeTableRecord);

class AcDbAbstractViewTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbAbstractViewTableRecord);

    AcDbAbstractViewTableRecord();
    virtual ~AcDbAbstractViewTableRecord();

    AcGePoint2d    centerPoint() const;
    void           setCenterPoint(const AcGePoint2d&);

    double         height() const;
    void           setHeight(double);

    double         width() const;
    void           setWidth(double);

    AcGePoint3d    target() const;
    void           setTarget(const AcGePoint3d&);

    AcGeVector3d   viewDirection() const;
    void           setViewDirection(const AcGeVector3d&);

    double         viewTwist() const;
    void           setViewTwist(double);

    double         lensLength() const;
    void           setLensLength(double);

    double         frontClipDistance() const;
    void           setFrontClipDistance(double);

    double         backClipDistance() const;
    void           setBackClipDistance(double);

    Adesk::Boolean perspectiveEnabled() const;
    void           setPerspectiveEnabled(Adesk::Boolean);

    Adesk::Boolean frontClipEnabled() const;
    void           setFrontClipEnabled(Adesk::Boolean);

    Adesk::Boolean backClipEnabled() const;
    void           setBackClipEnabled(Adesk::Boolean);

    Adesk::Boolean frontClipAtEye() const;
    void           setFrontClipAtEye(Adesk::Boolean);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbAbstractViewTableRecord);

class AcDbViewTableRecord: public  AcDbAbstractViewTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewTableRecord);

    AcDbViewTableRecord();
    virtual ~AcDbViewTableRecord();

    Adesk::Boolean isPaperspaceView() const;
    void           setIsPaperspaceView(Adesk::Boolean);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbViewTableRecord);

class AcDbUCSTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUCSTableRecord);

    AcDbUCSTableRecord();
    virtual ~AcDbUCSTableRecord();

    AcGePoint3d  origin() const;
    void         setOrigin(const AcGePoint3d&);

    AcGeVector3d xAxis() const;
    void         setXAxis(const AcGeVector3d&);

    AcGeVector3d yAxis() const;
    void         setYAxis(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbUCSTableRecord);

class AcDbViewportTableRecord: public  AcDbAbstractViewTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewportTableRecord);

    AcDbViewportTableRecord();
    virtual ~AcDbViewportTableRecord();

    AcGePoint2d    lowerLeftCorner() const;
    void           setLowerLeftCorner(const AcGePoint2d&);

    AcGePoint2d    upperRightCorner() const;
    void           setUpperRightCorner(const AcGePoint2d&);

    Adesk::Boolean ucsFollowMode() const;
    void           setUcsFollowMode(Adesk::Boolean);

    Adesk::UInt16  circleSides() const;
    void           setCircleSides(Adesk::UInt16);

    Adesk::Boolean fastZoomsEnabled() const;
    void           setFastZoomsEnabled(Adesk::Boolean);

    Adesk::Boolean iconEnabled() const;
    void           setIconEnabled(Adesk::Boolean);

    Adesk::Boolean iconAtOrigin() const;
    void           setIconAtOrigin(Adesk::Boolean);

    Adesk::Boolean gridEnabled() const;
    void           setGridEnabled(Adesk::Boolean);

    AcGePoint2d    gridIncrements() const;
    void           setGridIncrements(const AcGePoint2d&);

    Adesk::Boolean snapEnabled() const;
    void           setSnapEnabled(Adesk::Boolean);

    Adesk::Boolean isometricSnapEnabled() const;
    void           setIsometricSnapEnabled(Adesk::Boolean);

    Adesk::Int16   snapPair() const;
    void           setSnapPair(Adesk::Int16);

    double         snapAngle() const;
    void           setSnapAngle(double);

    AcGePoint2d    snapBase() const;
    void           setSnapBase(const AcGePoint2d&);

    AcGePoint2d    snapIncrements() const;
    void           setSnapIncrements(const AcGePoint2d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbViewportTableRecord);

class AcDbRegAppTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbRegAppTableRecord);

    AcDbRegAppTableRecord();
    virtual ~AcDbRegAppTableRecord();

    Adesk::Boolean excludeFromSaveAsR12() const;
    void           setExcludeFromSaveAsR12(Adesk::Boolean);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbRegAppTableRecord);

class AcDbDimStyleTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimStyleTableRecord);

    AcDbDimStyleTableRecord();
    virtual ~AcDbDimStyleTableRecord();

    Adesk::Boolean dimtol() const;
    void           setDimtol(Adesk::Boolean);

    Adesk::Boolean dimlim() const;
    void           setDimlim(Adesk::Boolean);

    Adesk::Boolean dimtih() const;
    void           setDimtih(Adesk::Boolean);

    Adesk::Boolean dimtoh() const;
    void           setDimtoh(Adesk::Boolean);

    Adesk::Boolean dimse1() const;
    void           setDimse1(Adesk::Boolean);

    Adesk::Boolean dimse2() const;
    void           setDimse2(Adesk::Boolean);

    Adesk::Boolean dimalt() const;
    void           setDimalt(Adesk::Boolean);

    Adesk::Boolean dimtofl() const;
    void           setDimtofl(Adesk::Boolean);

    Adesk::Boolean dimsah() const;
    void           setDimsah(Adesk::Boolean);

    Adesk::Boolean dimtix() const;
    void           setDimtix(Adesk::Boolean);

    Adesk::Boolean dimsoxd() const;
    void           setDimsoxd(Adesk::Boolean);

    Adesk::Boolean dimsd1() const;
    void           setDimsd1(Adesk::Boolean);

    Adesk::Boolean dimsd2() const;
    void           setDimsd2(Adesk::Boolean);

    Adesk::Int8    dimtolj() const;
    void           setDimtolj(Adesk::Int8);

    Adesk::Boolean dimupt() const;
    void           setDimupt(Adesk::Boolean);

    int            dimaltd() const;
    void           setDimaltd(int);

    int            dimzin() const;
    void           setDimzin(int);

    int            dimjust() const;
    void           setDimjust(int);

    int            dimfit() const;
    void           setDimfit(int);

    int            dimtzin() const;
    void           setDimtzin(int);

    int            dimaltz() const;
    void           setDimaltz(int);

    int            dimalttz() const;
    void           setDimalttz(int);

    int            dimtad() const;
    void           setDimtad(int);

    int            dimunit() const;
    void           setDimunit(int);

    int            dimaunit() const;
    void           setDimaunit(int);

    int            dimdec() const;
    void           setDimdec(int);

    int            dimtdec() const;
    void           setDimtdec(int);

    int            dimaltu() const;
    void           setDimaltu(int);

    int            dimalttd() const;
    void           setDimalttd(int);

    AcDbObjectId   dimtxsty() const;
    void           setDimtxsty(AcDbObjectId);

    double         dimscale() const;
    void           setDimscale(double);

    double         dimasz() const;
    void           setDimasz(double);

    double         dimexo() const;
    void           setDimexo(double);

    double         dimdli() const;
    void           setDimdli(double);

    double         dimexe() const;
    void           setDimexe(double);

    double         dimrnd() const;
    void           setDimrnd(double);

    double         dimdle() const;
    void           setDimdle(double);

    double         dimtp() const;
    void           setDimtp(double);

    double         dimtm() const;
    void           setDimtm(double);

    double         dimtxt() const;
    void           setDimtxt(double);

    double         dimcen() const;
    void           setDimcen(double);

    double         dimtsz() const;
    void           setDimtsz(double);

    double         dimaltf() const;
    void           setDimaltf(double);

    double         dimlfac() const;
    void           setDimlfac(double);

    double         dimtvp() const;
    void           setDimtvp(double);

    double         dimtfac() const;
    void           setDimtfac(double);

    double         dimgap() const;
    void           setDimgap(double);

    Acad::ErrorStatus getDimpost(char*&) const;
    Acad::ErrorStatus setDimpost(const char*);

    Acad::ErrorStatus getDimapost(char*&) const;
    Acad::ErrorStatus setDimapost(const char*);

    Acad::ErrorStatus getDimblk(char*&) const;
    Acad::ErrorStatus setDimblk(const char*);

    Acad::ErrorStatus getDimblk1(char*&) const;
    Acad::ErrorStatus setDimblk1(const char*);

    Acad::ErrorStatus getDimblk2(char*&) const;
    Acad::ErrorStatus setDimblk2(const char*);

    AcCmColor dimclrd() const;
    void      setDimclrd(const AcCmColor&);

    AcCmColor dimclre() const;
    void      setDimclre(const AcCmColor&);

    AcCmColor dimclrt() const;
    void      setDimclrt(const AcCmColor&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbDimStyleTableRecord);

#endif
