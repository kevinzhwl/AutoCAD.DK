#ifndef ACDB_DBGROUP_H
#define ACDB_DBGROUP_H
//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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
//
// AcDbGroup
//
// Maintains an ordered collection of database objects with a related iterator.
// An iterator can be obtained via an existing AcDbGroup object with
// the newIterator() method.  See below for class descriptions for both
// AcDbGroup and AcDbGroupIterator.
//
// AcDbGroup objects are contained in a special group table (actually a
// dictionary).  This dictionary can be obtained like this:
//
//     AcDbDictionary* pGrpDict = 
//         acdbHostApplicationServices()->workingDatabase()->groupTable();
//
// The AcDbGroup constructor does not add the group to the group dictionary;
// this must be done explicitly, using the AcDbDictionary protocol.
//
// When an entity is erased, it is automatically removed from
// the groups that contain it.

#include "dbmain.h"
#include "dbapserv.h"

#pragma pack(push, 8)

class AcDbGroupIterator;

class AcDbGroup: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbGroup);
    AcDbGroup();
    AcDbGroup(const ACHAR * grpDesc, bool selectable = true);
    virtual ~AcDbGroup();

    AcDbGroupIterator*  newIterator();

    const ACHAR *       description() const;
    Acad::ErrorStatus   setDescription(const ACHAR * grpDesc);

    bool                isSelectable() const;
    Acad::ErrorStatus   setSelectable(bool selectable);

    const ACHAR *       name() const;    //deprecated. New code should use getName.
    Acad::ErrorStatus   getName(ACHAR *& name) const;
    Acad::ErrorStatus   setName(const ACHAR * newName);

    bool                isNotAccessible() const;

    bool                isAnonymous() const;
    Acad::ErrorStatus   setAnonymous();

    Acad::ErrorStatus   append(AcDbObjectId id);
    Acad::ErrorStatus   append(AcDbObjectIdArray ids);
    Acad::ErrorStatus   prepend(AcDbObjectId id);
    Acad::ErrorStatus   prepend(AcDbObjectIdArray ids);
    Acad::ErrorStatus   insertAt(Adesk::UInt32 idx, AcDbObjectId id);
    Acad::ErrorStatus   insertAt(Adesk::UInt32 idx, AcDbObjectIdArray ids);
    Acad::ErrorStatus   remove(AcDbObjectId id);
    Acad::ErrorStatus   removeAt(Adesk::UInt32 idx);
    Acad::ErrorStatus   remove(AcDbObjectIdArray ids);
    Acad::ErrorStatus   removeAt(Adesk::UInt32 idx, AcDbObjectIdArray ids);
    Acad::ErrorStatus   replace(AcDbObjectId oldId, AcDbObjectId newId);
    Acad::ErrorStatus   transfer(Adesk::UInt32 fromIndex, 
                                 Adesk::UInt32 toIndex, 
                                 Adesk::UInt32 numItems);

    Acad::ErrorStatus   clear();
    Adesk::UInt32       numEntities() const;
    bool                has(const AcDbEntity* pEntity) const;
    Adesk::UInt32       allEntityIds(AcDbObjectIdArray& ids) const;
    Acad::ErrorStatus   getIndex(AcDbObjectId id, Adesk::UInt32& idx) const;
    Acad::ErrorStatus   reverse();

    Acad::ErrorStatus   setColor(const AcCmColor& color);
    Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color);
    Acad::ErrorStatus   setLayer(const ACHAR * newVal);
    Acad::ErrorStatus   setLayer(AcDbObjectId newVal);
    Acad::ErrorStatus   setLinetype(const ACHAR * newVal);
    Acad::ErrorStatus   setLinetype(AcDbObjectId newVal);
    Acad::ErrorStatus   setLinetypeScale(double newval);
    Acad::ErrorStatus   setVisibility(AcDb::Visibility newVal);
    Acad::ErrorStatus   setHighlight(bool newVal);

    Acad::ErrorStatus   setMaterial(const ACHAR * newVal);
    Acad::ErrorStatus   setMaterial(AcDbObjectId newVal);
    // Overridden methods from AcDbObject
    //
    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler,
                                               AcRxClass*    classObj);

    virtual Acad::ErrorStatus subClose();
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing = true);

    virtual void              erased(const AcDbObject* dbObj,
                                     Adesk::Boolean erasing = true);
    virtual void              goodbye(const AcDbObject* dbObj);

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus getClassID(CLSID* pClsid) const;
};


// The group iterator class.
//
class ADESK_NO_VTABLE AcDbGroupIterator: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGroupIterator);
    virtual ~AcDbGroupIterator() {}

    virtual Acad::ErrorStatus getObject(AcDbObject*& pObject,
        AcDb::OpenMode) = 0;
    virtual AcDbObjectId      objectId () const = 0;

    virtual bool              done     () const = 0;
    virtual bool              next     () = 0;

protected:
    AcDbGroupIterator() {}
};

#pragma pack(pop)

#endif
