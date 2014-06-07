#ifndef ACDB_DBDWFHOST_H
#define ACDB_DBDWFHOST_H
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

#include "dbmain.h"
#include "acstring.h"

#pragma pack (push, 8)

/// <summary>
/// Provides additional information for drawing an underlay.
/// </summary>
struct AcDbUnderlayDrawContext
{
     ///<summary>Contrast at which the item should be drawn.</summary>
     Adesk::UInt8 contrast; 
     ///<summary>The fade for the item to be drawn.</summary>
     Adesk::UInt8 fade;
     ///<summary>True if the item should be drawn monochrome.</summary>
     bool monochrome;
     ///<summary>True if the item should consider changing some of the colors to make them more visible on the current background.</summary>
     bool adjustColorForBackground;
};

/// <summary>
/// used by the AcDbUnderlayItem::version() function as the version at the time the application was
/// compiled.
/// </summary>
const int kItemVersionNumber = 1;

/// <summary>
/// This interface is implemented by host applications that wish to support underlays.
/// AcDbUnderlayDefinition and AcDbUnderlayReference uses this interface to accomplish their mission.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayItem
{
public:
        /// <summary>
    /// Destroys the item. All resources related to item should be freed.
    /// </summary>
    virtual ~AcDbUnderlayItem() = 0;
    /// <summary>
    /// Gets the unique name (within the file) for the item.
    /// </summary>
    /// <returns>Returns the name of the item.</returns>
    virtual AcString getName() const = 0;
    /// <summary>
    /// Gets the preview bitmap for the item.
    /// </summary>
    /// <param name="thumbnail">Contains the bitmap upon successful return. The caller is repsonsible for freeing this data structure using GlobalFree().</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus getThumbnail(
                                BITMAPINFO*& thumbnail) const = 0;
    /// <summary>
    /// Gets the extents in item-model coordinates. AcDbUnderlayReference::transform() provides the transformation matrix from item-model coordinates to
    /// block space coordinates (block space coordinates usually equal to WCS coordinates unless the AcDbUnderlayReference is part of a block).
    /// </summary>
    /// <param name="min">Minimum point.</param>
    /// <param name="max">Maximum point.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus getExtents(
                                AcGePoint2d& min, 
                                AcGePoint2d& max) const = 0;
    /// <summary>
    /// Gets the units used by the item.
    /// </summary>
    /// <returns>Returns the units used by the item.</returns>
    virtual AcDb::UnitsValue getUnits() const = 0;
    /// <summary>
    /// Specifies whether or not the item is using only some of the content of the sheet/model represented
    /// by the item
    /// </summary>
    /// <returns>Returns true if the item is not using all of the content, otherwise returns false.</returns>
    virtual bool usingPartialContent() const = 0;
    /// <summary>
    /// Draws the item for all viewports or for a given viewport. The <paramref name="pWorldDraw"/> and  <paramref name="pViewportdraw"/> parameters cannot be both
    /// non-null at the same time.
    /// </summary>
    /// <param name="pWorldDraw">NULL if no viewport-independent drawing should be done. Otherwise non-null.</param>
    /// <param name="pViewportDraw">NULL if no dependent drawing should be done. Otherwise non-null.</param>
    /// <param name="context">Additional parameters on how the underlay should be drawn.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus draw(
        AcGiWorldDraw* pWorldDraw, 
        AcGiViewportDraw* pViewportDraw, 
        const AcDbUnderlayDrawContext& context) const = 0;

    /// <summary>
    /// Provides a transformation matrix that transforms underlay geometry to the item-model coordinates. This is usually an identity matrix or
    /// a simple translation that "rebases" the geometry to a "base point".
    /// </summary>
    /// <returns>Returns a transformation matrix that transforms underlay geometry to the item-model coordinates.</returns>
    virtual AcGeMatrix3d modelTransform() const = 0;

    /// <summary>
    /// Obtains osnap points for the underlay item. See also AcDbEntity::getOsnapPoints.
    /// </summary>
    /// <param name="modelToWorld">transformation matrix from "item-model" to block space coordinates (block space coordinates usually equal to WCS coordinates unless the AcDbUnderlayReference is part of a block).</param>
    /// <param name="osnapMode">Input osnap mode being requested.</param>
    /// <param name="gsSelectionMark">Input GS marker of the subentity involved in the object snap operation.</param>
    /// <param name="pickPoint">Input point (in WCS coordinates) picked during the object snap operation.</param>
    /// <param name="lastPoint">Input point (in WCS coordinates) selected just before pickPoint.</param>
    /// <param name="viewXform">Input transformation matrix to transform from WCS to DCS.</param>
    /// <param name="snapPoints">Input pre-existing array to append osnap points to (may already contain points); output with object snap points appended.</param>
    /// <param name="geomIds">Not in use</param>
    /// <returns>Returns Acad::eOk if successful</returns>
    virtual Acad::ErrorStatus getOsnapPoints(const AcGeMatrix3d& modelToWorld,
                                             AcDb::OsnapMode osnapMode,
                                             int   gsSelectionMark,
                                             const AcGePoint3d&  pickPoint,
                                             const AcGePoint3d&  lastPoint,
                                             const AcGeMatrix3d& viewXform,
                                             AcGePoint3dArray&      snapPoints,
                                             AcDbIntArray&   geomIds)
                                             const = 0;

    /// <summary>
    /// Obtains the subentity at a given selection marker. See also: AcDbEntity::subentPtr and AcDbEntity::getFullSubentPathsAtGsMarker.
    /// </summary>
    /// <param name="modelToWorld">Transformation matrix from "item-model" to block space coordinates (block space coordinates usually equal to WCS coordinates unless the AcDbUnderlayReference is part of a block).</param>
    /// <param name="gsSelectionMark">The selection marker for which the subentity is requested. Underlays do not support multiple subentities for a gs marker.</param>
    /// <returns>Returns Acad::eOk if successful</returns>
    virtual AcDbEntity* getSubEntityAtGsMarker(const AcGeMatrix3d& modelToWorld,int gsSelectionMark) const = 0;

    /// <summary>
    /// Intersect the underlay item with another object. See also AcDbEntity::intersectWith.
    /// </summary>
    /// <param name="modelToWorld">Transformation matrix from "item-model" to block space coordinates (block space coordinates usually equal to WCS coordinates unless the AcDbUnderlayReference is part of a block).</param>
    /// <param name="pEnt">Input entity with which "this" entity is to intersect.</param>
    /// <param name="intType">Input type of intersection requested.</param>
    /// <param name="projPlane">Input projection plane for the apparent intersection of the two entities.</param>
    /// <param name="points">Output with the points of intersection appended.</param>
    /// <param name="thisGsMarker">Input GS marker of subentity of "this" entity that's involved in the intersection operation. Use the 0 default if not applicable.</param>
    /// <param name="otherGsMarker">Input GS marker of subentity of the entity pointed to by pEnt that's involved in the intersection operation. Use the 0 default if not applicable.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus intersectWith(const AcGeMatrix3d& modelToWorld,
                                            const AcDbEntity* pEnt,
                                            AcDb::Intersect intType,
                                            const AcGePlane* projPlane,
                                            AcGePoint3dArray& points,
                                            int thisGsMarker,
                                            int otherGsMarker) const = 0;
    /// <summary>
    /// Used to determine the version of the underlayItem.
    /// </summary>
    /// <returns> Returns the version number in effect when the application was compiled.
    int version() const;
};

/// <summary>
/// This interface is implemented by host applications that wish to support underlays.
/// AcDbUnderlayDefinition and AcDbUnderlayReference use this interface to accomplish their mission.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayFile
{
public:
    /// <summary>
    /// Destroys the file. All resources related to file should be freed.
    /// </summary>
    virtual ~AcDbUnderlayFile() = 0;
    /// <summary>
    /// Gets the number of items in the file.
    /// </summary>
    /// <returns>Returns the number of items in the file.</returns>
    virtual int getItemCount() const = 0;
    /// <summary>
    /// Gets an item by index.
    /// </summary>
    /// <param name="i">Index of the item to be retrieved.</param>
    /// <param name="pItem">Variable that receives the item upon successful return.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus getItem(
                                int i, 
                                AcDbUnderlayItem*& pItem) const = 0;
    /// <summary>
    /// Gets an item by name.
    /// </summary>
    /// <param name="name">Name of the item to be retrieved.</param>
    /// <param name="pItem">Variable that receives the item upon successful return.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus getItem(
                                const ACHAR* name, 
                                AcDbUnderlayItem*& pItem) const = 0;
};

/// <summary>
/// This interface is implemented by host applications that wish to support underlays.
/// AcDbUnderlayDefinition and AcDbUnderlayReference use this interface to accomplish their mission.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayHost
{
public:
    /// <summary>
    /// Gets an underlay file.
    /// </summary>
    /// <param name="fullPath">Fully qualified path to the file to open.</param>
    /// <param name="password">Optional password. If the password is NULL but is required then getFile will prompt the user for password.</param>
    /// <param name="pFile">Variable that recieves the file upon successful return.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus getFile(
                                const ACHAR* fullPath, 
                                const wchar_t* password, 
                                AcDbUnderlayFile*& pFile) const = 0;

    /// <summary>
    /// Implements the uniform underlay color adjustment algorithm. 
    /// The algorithm performs the following operations:
    /// 1. Interpolates <paramref name="rgbInputColor"/> towards <paramref name="rgbCurrentBackgroundColor"/> in RGB space <paramref name="drawContext.fade"/> percent.
    /// 2. Converts the resulting RGB color to HSL.
    /// 3. Interpolates the lightness of the resulting color towards <paramref name="hslFadedContrastColor"/> <paramref name="drawContext.contrast"/> percent.
    /// 4. If <paramref name="drawContext.monochrome"/> is true it sets the hue and saturation of the resulting color to 0.
    /// 5. Converst the resulting HSL value to RGB and stores it in <paramref name="rgbResult"/>.
    /// </summary>
    /// <param name="rgbResult">The resulting RGB value where x is red [0,1], y is green and z [0,1] is blue [0,1].</param>
    /// <param name="rgbInputColor">The input RGB value where x is red [0,1], y is green [0,1] and z is blue [0,1].</param>
    /// <param name="rgbCurrentBackgroundColor">The current background color in RGB that the underlay content will be renderred against.</param>
    /// <param name="hslFadedContrastColor">The contrast color in HSL.</param>
    /// <param name="drawContext">Provides additional input parameters for the color adjustment algorithm.</param>
    static void getAdjustedColor(
                               AcGeVector3d& rgbResult, 
                               const AcGeVector3d& rgbInputColor, 
                               const AcGeVector3d& rgbCurrentBackgroundColor, 
                               const AcGeVector3d& hslFadedContrastColor,
                               const AcDbUnderlayDrawContext& drawContext);
protected:
    ///<summary>Destructor.</summary>
    virtual ~AcDbUnderlayHost() = 0;
};
/// <summary>
/// Gets the current DWF underlay host.
/// </summary>
/// <returns>returns the DWF underlay host.</returns>
ACDB_PORT AcDbUnderlayHost* 
acdbGetCurrentDwfHost();
/// <summary>
/// Sets the current DWF underlay host.
/// </summary>
/// <param name="pHost">The new host application to use.</param>
/// <returns>Returns the previous DWF underlay host.</returns>
ACDB_PORT AcDbUnderlayHost* 
acdbSetCurrentDwfHost(
    AcDbUnderlayHost* pHost);

/// <summary>
/// Gets the current DGN underlay host.
/// </summary>
/// <returns>returns the DGN underlay host.</returns>
ACDB_PORT AcDbUnderlayHost* 
acdbGetCurrentDgnHost();
/// <summary>
/// Sets the current DGN underlay host.
/// </summary>
/// <param name="pHost">The new host application to use.</param>
/// <returns>Returns the previous DGN underlay host.</returns>
ACDB_PORT AcDbUnderlayHost* 
acdbSetCurrentDgnHost(
    AcDbUnderlayHost* pHost);

/// <summary>
/// Converts a color from RGB to HSL (also known as HLS) color space.
/// </summary>
/// <param name="rgb">The resulting RGB value where x is red [0,1], y is green and z [0,1] is blue [0,1].</param>
/// <param name="hsl">The input HSL value where x is the hue [0,1], y is the saturation [0,1] and z is lightness [0,360].</param>
ACDB_PORT void 
acdbConvertRgbToHsl(
           const AcGeVector3d& rgb,
           AcGeVector3d& hsl
           );
           

/// <summary>
/// Converts a color from HSL(also known as HLS) RGB color space.
/// </summary>
/// <param name="hsl">The resulting HSL value where x is the hue [0,1], y is the saturation [0,1] and z is lightness [0,360].</param>
/// <param name="rgb">The input RGB value where x is red [0,1], y is green [0,1] and z is blue [0,1].</param>
ACDB_PORT void 
acdbConvertHslToRgb(
           const AcGeVector3d& hsl,
           AcGeVector3d& rgb);

#pragma pack (pop)

#endif
