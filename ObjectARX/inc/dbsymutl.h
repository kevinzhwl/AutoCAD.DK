#ifndef AD_DBSYMUTL_H
#define AD_DBSYMUTL_H 1
//
// (C) Copyright 1998-2007 by Autodesk, Inc. 
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
//  DESCRIPTION:
//
//  Namespace AcDbSymbolUtilities contains various utilities for
//  working with symbol names, symbol records, and symbol tables.
//  The main access to the utility functions is through
//  "acdbSymUtil()", which you dereference to call the member
//  functions of AcDbSymbolUtilities::Services.

#include <assert.h>
#include <stddef.h>
#include "dbsymtb.h"

#pragma pack (push, 8)

#define ACDBSYMUTIL_SERVICES_CURRENT_VERSION 106

namespace AcDbSymbolUtilities
{

enum CompatibilityMode {
    kExtendedNames    = true,
    kPreExtendedNames = false
};

enum NameCaseMode {
    kPreserveCase     = true,
    kForceToUpper     = false
};

enum NewNameMode {
    kAsNewName        = true,
    kAsExistingName   = false
};

enum VerticalBarMode {
    kAllowVerticalBar = true,
    kNoVerticalBar    = false
};

class Services
{
public:
    enum { kCurrentVersion = ACDBSYMUTIL_SERVICES_CURRENT_VERSION };
    virtual int version() const = 0;

    // --------- Pre-defined symbols ---------

    virtual bool isBlockLayoutName        (const ACHAR * name) const = 0;
    virtual bool isBlockModelSpaceName    (const ACHAR * name) const = 0;
    virtual bool isBlockPaperSpaceName    (const ACHAR * name) const = 0;
    virtual bool isLayerDefpointsName     (const ACHAR * name) const = 0;
    virtual bool isLayerZeroName          (const ACHAR * name) const = 0;
    virtual bool isLinetypeByBlockName    (const ACHAR * name) const = 0;
    virtual bool isLinetypeByLayerName    (const ACHAR * name) const = 0;
    virtual bool isLinetypeContinuousName (const ACHAR * name) const = 0;
    virtual bool isRegAppAcadName         (const ACHAR * name) const = 0;
    virtual bool isTextStyleStandardName  (const ACHAR * name) const = 0;
    virtual bool isViewportActiveName     (const ACHAR * name) const = 0;

    virtual AcDbObjectId blockModelSpaceId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId blockPaperSpaceId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId layerDefpointsId     (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId layerZeroId          (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeByBlockId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeByLayerId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeContinuousId (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId regAppAcadId         (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId textStyleStandardId  (AcDbDatabase * pDb) const = 0;

    virtual const ACHAR * blockModelSpaceName    () const = 0;
    virtual const ACHAR * blockPaperSpaceName    () const = 0;
    virtual const ACHAR * layerDefpointsName     () const = 0;
    virtual const ACHAR * layerZeroName          () const = 0;
    virtual const ACHAR * linetypeByBlockName    () const = 0;
    virtual const ACHAR * linetypeByLayerName    () const = 0;
    virtual const ACHAR * linetypeContinuousName () const = 0;
    virtual const ACHAR * regAppAcadName         () const = 0;
    virtual const ACHAR * textStyleStandardName  () const = 0;
    virtual const ACHAR * viewportActiveName     () const = 0;

    // --------- Symbol names ---------

    virtual int               compareSymbolName(
                                      const ACHAR * thisName,
                                      const ACHAR * otherName) const = 0;
    virtual bool              hasVerticalBar(
                                      const ACHAR * name) const = 0;
    virtual Acad::ErrorStatus makeDependentName(
                                      ACHAR *&      pNewName,
                                      const ACHAR * dwgName,
                                      const ACHAR * symbolName) const = 0;
    virtual Acad::ErrorStatus repairPreExtendedSymbolName(
                                      ACHAR *&      pNewName,
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const = 0;
    virtual Acad::ErrorStatus repairSymbolName(
                                      ACHAR *&      pNewName,
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const = 0;
    virtual bool              splitDependentName(
                                      size_t &      numLeftBytes,
                                      const ACHAR *& pRight,
                                      const ACHAR *  symbolName) const = 0;
    virtual Acad::ErrorStatus validatePreExtendedSymbolName(
                                      const ACHAR * name,
                                      bool         allowVerticalBar) const = 0;
    virtual Acad::ErrorStatus validateSymbolName(
                                      const ACHAR * name,
                                      bool         allowVerticalBar) const = 0;

    // --------- Compatibility ---------

    virtual bool              compatibilityMode(
                                      AcDbDatabase * pDb) const = 0;
    virtual Acad::ErrorStatus getBlockNameFromInsertPathName(
                                      ACHAR *&      pBlockName,
                                      const ACHAR * pathName) const = 0;
    virtual Acad::ErrorStatus getInsertPathNameFromBlockName(
                                      ACHAR *&      pPathName,
                                      const ACHAR * blockName) const = 0;
    virtual bool              getMaxSymbolNameLength(
                                      size_t &     maxLength,
                                      size_t &     maxSize,
                                      bool         isNewName,
                                      bool         compatibilityMode) const = 0;
    virtual Acad::ErrorStatus getPathNameFromSymbolName(
                                      ACHAR *&      pPathName,
                                      const ACHAR * symbolName,
                                      const ACHAR * extensions) const = 0;
    virtual Acad::ErrorStatus getSymbolNameFromPathName(
                                      ACHAR *&      pSymbolName,
                                      const ACHAR * pathName,
                                      const ACHAR * extensions) const = 0;
    virtual Acad::ErrorStatus preValidateSymbolName(
                                      ACHAR *&      pSymbolName,
                                      bool         preserveCase) const = 0;
    virtual Acad::ErrorStatus validateCompatibleSymbolName(
                                      const ACHAR * name,
                                      bool         isNewName,
                                      bool         allowVerticalBar,
                                      bool         compatibilityMode) const = 0;

}; // end Services

inline Acad::ErrorStatus
getSymbolName(
    ACHAR      *&pName,
    AcDbObjectId objId)
{
    AcDbSymbolTableRecord *pRec = NULL;
    Acad::ErrorStatus es = acdbOpenObject(pRec, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pRec->getName(pName);
        Acad::ErrorStatus closeStatus = pRec->close();
        assert(closeStatus == Acad::eOk);
    }
    return es;
}

// For use by AcDbSymbolUtilities only!
#define ACDBSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v) n ## v
#define ACDBSYMUTIL_SERVICESNAME_WITH_VERSION(n,v) \
        ACDBSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v)
#define ACDBSYMUTIL_SERVICES_NAME \
        ACDBSYMUTIL_SERVICESNAME_WITH_VERSION( \
            servicesPtr, \
            ACDBSYMUTIL_SERVICES_CURRENT_VERSION)
extern const Services * ACDBSYMUTIL_SERVICES_NAME();

// --------- Inline definitions ---------

inline const Services *
servicesPtr()
{
    const Services * pSymUtil = ACDBSYMUTIL_SERVICES_NAME();
    assert(pSymUtil != NULL);
    assert(pSymUtil->version() == Services::kCurrentVersion);
    return pSymUtil;
}

// The get<TABLE>Id() functions retrieve the AcDbObjectId for a symbol
// record given the name of the symbol (parameter "name") and a pointer
// to the database (parameter pDb) that contains the specified table.
// If the function succeeds, it returns the AcDbObjectId in parameter "rId"
// and returns Acad::eOk.
//
// We provide a get<TABLE>Id() function for all the basic symbol tables
// except for the viewport table, which may have duplicate records.
// The following inlined functions are available.
//
// getBlockId
// getDimStyleId
// getLayerId
// getLinetypeId
// getRegAppId
// getTextStyleId
// getUCSId
// getViewId
//
// These functions open up the table and look for the specified record.
// If you need to make successive calls for a particular table, you should
// open the table yourself instead of invcurring the overhead of
// repeatedly opening and closing the tables using these functions.

#define DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(T_TABLE) \
inline Acad::ErrorStatus \
get ## T_TABLE ## Id( \
    AcDbObjectId &objId, \
    const ACHAR  *name, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return Acad::eNullObjectPointer; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        es = pTable->getAt(name, objId); \
        Acad::ErrorStatus closeStatus = pTable->close(); \
        assert(closeStatus == Acad::eOk); \
    } \
    return es; \
}
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Block)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(DimStyle)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Layer)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Linetype)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(RegApp)

inline Acad::ErrorStatus
getTextStyleId(
    AcDbObjectId &objId,
    const ACHAR  *name,
    AcDbDatabase *pDb)
{
    if (pDb == NULL)
        return Acad::eNullObjectPointer;
    AcDbTextStyleTable *pTable = NULL;
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead);
    if (es == Acad::eOk) {
        AcDbTextStyleTableRecord *pRec = NULL;
        es = pTable->getAt(name, pRec, AcDb::kForRead);
        if (es == Acad::eOk) {
            if (pRec->isShapeFile())
                es = Acad::eKeyNotFound;
            else
                objId = pRec->objectId();
            Acad::ErrorStatus closeStatus = pRec->close();
            assert(closeStatus == Acad::eOk);
        }
        Acad::ErrorStatus closeStatus = pTable->close();
        assert(closeStatus == Acad::eOk);
    }
    return es;
}

DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(UCS)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(View)
#undef DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION

// The has<TABLE>() functions return a boolean value indicating
// whether a symbol record with the given name (parameter "name") or
// AcDbObjectId (parameter objId) in a particular database's symbol table
// exists.  Parameter pDb points to the database to use for accessing
// the symbol table.  The functions return Adesk::kTrue if it finds
// the record.  Otherwise, it returns Adesk::kFalse.
// 
// We provide a has<TABLE>() function for all the basic symbol tables.
// The functions overload on the type of the first parameter.  If it is
// an AcDbObjectId, we look for the AcDbObjectId in the table.  If it is a
// string, we look for the specified name in the table.
// The following inlined functions are available.
//
// hasBlock
// hasDimStyle
// hasLayer
// hasLinetype
// hasRegApp
// hasTextStyle
// hasUCS
// hasView
// hasViewport
//
// These functions open up the table and looks for the specified record.
// IF you need to make successive calls for a particular table, you should
// open the table yourself instead of invcurring the overhead of
// repeatedly opening and closing the tables using these functions.

#define DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(T_TABLE) \
inline bool \
has ## T_TABLE( \
    AcDbObjectId  objId, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return false; \
    bool hasSymbol = false; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        hasSymbol = !!pTable->has(objId); \
        Acad::ErrorStatus closeStatus = pTable->close(); \
        assert(closeStatus == Acad::eOk); \
    } \
    return hasSymbol; \
}
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Block)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(DimStyle)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Layer)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Linetype)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(RegApp)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(TextStyle)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(UCS)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(View)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Viewport)
#undef DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION

#define DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(T_TABLE) \
inline bool \
has ## T_TABLE( \
    const ACHAR  *name, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return false; \
    bool hasSymbol = false; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        hasSymbol = !!pTable->has(name); \
        Acad::ErrorStatus closeStatus = pTable->close(); \
        assert(closeStatus == Acad::eOk); \
    } \
    return hasSymbol; \
}
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Block)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(DimStyle)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Layer)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Linetype)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(RegApp)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(TextStyle)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(UCS)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(View)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Viewport)
#undef DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION

} // end AcDbSymboUtilities

namespace AcDbSymUtil = AcDbSymbolUtilities;

Acad::ErrorStatus  getTableStyleNameFromDbById(const AcDbObjectId& objId,
                                               ACHAR*& pName);

typedef AcDbSymbolUtilities::Services AcDbSymUtilServices;

inline const AcDbSymUtilServices *
acdbSymUtil()
{
    return AcDbSymbolUtilities::servicesPtr();
}

#pragma pack (pop)
#endif // !AD_DBSYMUTL_H
