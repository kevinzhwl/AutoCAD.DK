#ifndef ACDB_DBUNDERLAYDEF_H
#define ACDB_DBUNDERLAYDEF_H
#pragma once
//
// (C) Copyright 2005-2006 by Autodesk, Inc.
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
// DESCRIPTION: Exported class for underlay definitions in dwg file - AcDbUnderlayDefintion

#include "dbmain.h"
#include "acstring.h"

#pragma pack (push, 8)

class AcDbUnderlayItem;
class AcDbUnderlayHost;

/// <summary>
/// Abstract class that handles the linkage to the external underlay content. Underlays are similar to raster images
/// but their content is snappable. An AcDbUnderlayDefinition is referenced by 0 or more AcDbUnderlayReferences.
/// The AcDbUnderlayRefernece is responsible for the placement of the content within the drawing while AcDbUnderlayDefinition
/// handles the linkage to the underlay content. 
/// Instances of AcDbUnderlayReference derived concrete classes are inserted in a block table record.
/// Instances of AcDbUnderlayDefinition derived concrete classes are inserted into a dictionay off of the named object dictionary.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayDefinition: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUnderlayDefinition);
    ///<summary>Default constructor.</summary>
    AcDbUnderlayDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbUnderlayDefinition() = 0;
    /// <summary>
    /// Sets the name of the file that this underlay references. This name can be the following form:
    /// 1. relative path (relative to the host drawing) 
    /// 2. file name only (will be searched on the support search path)
    /// 3. full path
    /// </summary>
    /// <param name="file">Name of the file</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setSourceFileName(const ACHAR* file);
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is in the form (relative or full path) that the user specified.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the source file path.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const ACHAR* getSourceFileName() const;
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is always a full path.
    /// </summary>
    /// <param name="file">Variable that is set to point to the internal datamember that holds the active file path upon successful return.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getActiveFileName(const ACHAR*& file) const;
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is always a full path.
    /// </summary>
    /// <param name="file">Variable that is set to hold the source file path upon successful return.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getActiveFileName(AcString& file) const;
    /// <summary>
    /// Sets the name of the underlay item that this underlay should reference.
    /// </summary>
    /// <param name="item">Name of the item</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setItemName(const ACHAR* item);
    /// <summary>
    /// Gets the name of the underlay item that this underlay currently references.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the item name.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const ACHAR* getItemName() const;
    /// <summary>
    /// Sets the source path and underlay item that this underlay should reference. Calls unload() to unload any previous underlay item.
    /// </summary>
    /// <param name="sourceFileName">Source file path.</param>
    /// <param name="activeFileName">Current or active file path. This points to the file where it is currently found.</param>
    /// <param name="pItem">The item to be referenced. The underlay definition takes ownership of the item and it should *not* be deleted by the client.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setUnderlayItem(const ACHAR* sourceFileName, const ACHAR* activeFileName, AcDbUnderlayItem* pItem);
    /// <summary>
    /// Gets the underlay item that this underlay currently references.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the item.
    /// The object should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const AcDbUnderlayItem* getUnderlayItem() const;
    /// <summary>
    /// Attempts to load the file returned by getActiveFileName().
    /// </summary>
    /// <param name="password">Optional password. I password is NULL but is necessary to open file this function will prompt the user.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus load(const wchar_t* password);
    /// <summary>
    /// Unloads the underlay file. References will behave as the file was never loaded.
    /// </summary>
    void unload();
    /// <summary>
    /// Gets a boolean indicating whether the underlay is currently loaded.
    /// </summary>
    /// <returns>Returns true, if the underlay is loaded.</returns>
    bool isLoaded() const;
    /// <summary>
    /// Gets the name of the dictionary that holds the AcDbUnderlayDefinition objects in the named objects dictionary.
    /// </summary>
    /// <param name="underlayDefinitionType">The class descriptor of the underlay type for which to retrive the dictionary name for.</param>
    /// <returns>Returns the name of the dictionary that holds the AcDbUnderlayDefinition objects in the named objects dictionary.</returns>
    static AcString dictionaryKey(const AcRxClass* underlayDefinitionType);
private:
    /// <summary>
    /// When overridden in derived classes it gets the underlay host to be used by this underlay definition.
    /// </summary>
    /// <returns>Returns the underlay host to be used by this underlay definition.</returns>
    virtual const AcDbUnderlayHost* getUnderlayHost() const = 0;
};
/// <summary>
/// Represents DWF underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDwfDefinition: public AcDbUnderlayDefinition
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDwfDefinition);
    ///<summary>Default constructor.</summary>
    AcDbDwfDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbDwfDefinition();
private:
    virtual  const AcDbUnderlayHost* getUnderlayHost() const;
};
/// <summary>
/// Represents DGN underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDgnDefinition: public AcDbUnderlayDefinition
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDgnDefinition);
    ///<summary>Default constructor.</summary>
    AcDbDgnDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbDgnDefinition();
private:
    virtual const AcDbUnderlayHost* getUnderlayHost() const;

};
#pragma pack (pop)

#endif
