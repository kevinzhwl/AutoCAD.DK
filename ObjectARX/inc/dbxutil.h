#ifndef AD_DBXUTIL_H
#define AD_DBXUTIL_H 1
//
// (C) Copyright 1993-2010 by Autodesk, Inc.
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
// DESCRIPTION: Header for homeless utilities exported to the API.
//
#include "adesk.h"
#include "acadstrc.h"
#include "adesk.h"
#include "adsdef.h"
#include "dbidar.h"
#include "dbid.h"
#include "acutmem.h"
#ifdef _ADESK_WINDOWS_
#include "windows.h"
#endif
#include "acgi.h"

#pragma pack (push, 8)

class AcGeMatrix3d;
class AcDbObject;
class AcDbOle2Frame;
class AcCmColor;
class AcDbViewport;
struct AcConstrainedGeometryDraggingInfo;

// --------- Coordinate-system conversions ---------

bool    acdbWcs2Ucs(ads_point p, ads_point q, bool vec);
bool    acdbWcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbUcs2Wcs(ads_point p, ads_point q, bool vec);
bool    acdbUcs2Ecs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Wcs(ads_point p, ads_point q, ads_point norm, bool vec);
bool    acdbEcs2Ucs(ads_point p, ads_point q, ads_point norm, bool vec);

AcGeVector3d     ucsXDir();
AcGeVector3d     ucsYDir();
void             ucsNormalVector(AcGeVector3d& ucsNormalVec);

// --------- Miscellaneous ---------

AcDbObjectId      acdbGetCurVportTableRecordId(AcDbDatabase* pDb);
AcDbObjectId      acdbGetCurVportId(AcDbDatabase* pDb);
Acad::ErrorStatus acdbGetProxyInfo(AcDbObject *pObj, ACHAR*& dxfName,
                                   ACHAR*& className, ACHAR*& appName);
bool    acdbUcsMatrix(AcGeMatrix3d& mat, AcDbDatabase * pDb = NULL);

Acad::ErrorStatus acdbGetExtnames(bool &value, AcDbDatabase *pDb);
Acad::ErrorStatus acdbSetExtnames(AcDbDatabase *pDb, bool value);

bool acdbGetPreviewBitmapFromDwg(const ACHAR* pszDwgfilename,
                                 HBITMAP* pPreviewBmp,
                                 HPALETTE* pRetPal);

const ACHAR* acdbGetReservedString(AcDb::reservedStringEnumType reservedType,
    bool bGetLocalized = true);
const ACHAR* acdbXlateReservedString(const ACHAR* strSource,
    bool bGetLocalized = true);
bool acdbIsReservedString(const ACHAR* strString,
    AcDb::reservedStringEnumType reservedType);

/// <summary>
/// Verify that an object and an objectId belongs to the same database,
/// and that no cross database references exist.
/// For database resident objects the database of the objectId will be compared
/// with the objects database.
/// For non database resident objects the objects intended database will be
/// used. If the object has no intended database it will be set by this function.
/// </summary>
/// <param name="pHostObject">The object holding the object Id.</param>
/// <param name="objId">The object Id to validate.</param>
/// <param name="es">Optional. Previous Acad::ErrorStatus.
///     That allows you to compute multiple results and chain them
///     while preserving the first bad error status.</param>
/// <returns>
///     Returns Acad::eOk if the operation completed sucessfully.
///     Returns Acad::eWrongDatabase if the databases are different.
///     Returns the 'es' argument directly if es != Acad::eOk
/// </returns>
Acad::ErrorStatus acdbValidateDbConsistency(AcDbObject*     pHostObject,
                                            AcDbObjectId    objId,
                                            Acad::ErrorStatus   es = Acad::eOk);

/// <summary>
/// Verify that an object does not have cross database references.
/// For database resident objects the database will be compared with the
/// objects database.
/// For non database resident objects the objects intended database will be
/// used. If the object has no intended database it will be set by this function.
/// </summary>
/// <param name="pHostObject">The object holding the object Id.</param>
/// <param name="pDatabase">The target database to validate.</param>
/// <param name="es">Optional. Previous Acad::ErrorStatus.
///     That allows you to compute multiple results and chain them
///     while preserving the first bad error status.</param>
/// <returns>
///     Returns Acad::eOk if the operation completed sucessfully.
///     Returns Acad::eWrongDatabase if the databases are different
///     Returns the 'es' argument directly if es != Acad::eOk
/// </returns>
Acad::ErrorStatus acdbValidateDbConsistency(AcDbObject*     pHostObject,
                                            AcDbDatabase*   pDatabase,
                                            Acad::ErrorStatus   es = Acad::eOk);

/// <summary>
/// Map the font that will be used given a font name.
/// </summary>
/// <param name="fontName">Input font name.</param>
/// <returns>A mapped(substitute) font name or NULL if there is no substitution.
/// </returns>
ACDB_PORT const ACHAR* acdbGetMappedFontName(const ACHAR *fontName);

/// <summary>
///   Queue an entity in model space for regen if it is:
///   1) annotative, or
///   2) a block reference with some nested annotative entity
///   3) an attribute on an annotative block reference
/// </summary>
/// <param name="pDb">Input database to get the model space from.</param>
/// <returns>Returns Acad::eOk if the operation completed sucessfully.</returns>
Acad::ErrorStatus acdbQueueAnnotationEntitiesForRegen(AcDbDatabase* pDb);

/// <summary>
/// Determines whether the sysvar ANNOALLVISIBLE is set for the layout that
/// owns the viewport whose objectId is viewportEntityId.
/// </summary>
/// <param name="viewportEntityId">Input objectId of a viewport whose owning layout is to be checked for ANNOALLVISIBLE.</param>
/// <returns>Returns 1 if ANNOALLVISIBLE is set and 0 if ANNOALLVISIBLE is not set for the layout.</returns>
bool acdbPSLayoutAnnoAllVisible(AcDbObjectId viewportEntityId);

/// <summary>
/// Determines whether the sysvar ANNOALLVISIBLE is set for the layout that
/// owns the viewport pointed to by pVport.
/// </summary>
/// <param name="pVport">Input pointer to an AcDbViewport whose owning layout is to be checked for ANNOALLVISIBLE.</param>
/// <returns>Returns 1 if ANNOALLVISIBLE is set and 0 if ANNOALLVISIBLE is not set for the layout.</returns>
bool acdbPSLayoutAnnoAllVisible(AcDbViewport* pVport);

/// <summary>
/// This function returns the object ID of the AcDbViewport that was current before
/// any draw methods are called on any entity in the database.  The entity draw methods
/// can manipulte what is the current viewport.
/// </summary>
/// <param name="pDb">Input database to get the object ID of the AcDbViewport from.</param>
/// <param name="vpId">Output object ID of the AcDbViewport.</param>
/// <returns>Returns Acad::eOk if completed sucessfully.</returns>
Acad::ErrorStatus acdbGetCurUserViewportId(AcDbDatabase* pDb,  AcDbObjectId& vpId);

////////////////////////////////////////////////////////////////////////
// class AcDbAnnotationScale
////////////////////////////////////////////////////////////////////////

/// <summary>
/// AcDbAnnotationScale is a helper class.
/// By instantiating a local variable to use this class, the constructor of the class,
/// saves off the current value of the sysvar, ANNOAUTOSCALE, and sets ANNOAUTOSCALE
/// to zero.  Then when the local variable goes out of scope the destructor of this
/// class returns ANNOAUTOSCALE to its original value.
/// </summary>
///

class AcDbDisableAnnoAutoScale
{
public:
    AcDbDisableAnnoAutoScale ();
    ~AcDbDisableAnnoAutoScale ();

private:
    short mSaveAnnoAutoScale;
    short mSaveAnnoAutoScaleLayout;
};

// acdbGetUnitsConversion
//
// Obtains the double value that represents the differnce in scale between two
// AcDb::UnitsValue enumerations. The returned conversion factor provides the
// multiplier needed to convert units measured in "from" units to the units
// measured in "to" units. 
// 
//   toValue = conversionFactor * fromValue
//
// (For example, if the "to" units are millimeters and the "from" units are
// inches the conversion factor is 25.4).
//   
// Returns eOk if succesful. Returns eInvalidInput if either of the UnitsValue
// enums are invalid.

Acad::ErrorStatus acdbGetUnitsConversion (AcDb::UnitsValue from,
                                          AcDb::UnitsValue to,
                                          double& conversionFactor);

// See if a filename has a corresponding .dwk file next to it.
bool ADESK_STDCALL acdbDwkFileExists(const ACHAR *pszFileName);

// Returns number of ids that were queued for regen.
//
int ADESK_STDCALL acdbQueueForRegen(const AcDbObjectId *pIdArray,
                                    int nNumIds);

// --------- Dynamic Dimension dimstyle manipulations ---------

AcDbObjectId  acdbGetDynDimStyleId( AcDbDatabase* pDb = NULL );

// --------- View and Viewport Management ---------------------


// This function creates a view from the given viewport.  It is a view of
// the viewport in its layout.  The size of the view are stretched to
// include any associated label block as well as some desirable padding
// around the sum of the viewport and label block extents.
Acad::ErrorStatus
acdbCreateViewByViewport( AcDbDatabase *pDb,
                          AcDbObjectId viewportId, 
                          const ACHAR* name, 
                          const ACHAR* categoryName,
                          AcDbObjectId labelBlockId,
                          AcDbObjectId& view);



// OLE

// Below is a wrapper for AcDbImpOle2Frame::hitTest(..) to make it 
// accessible from within the coreads\acadapp arx app for OLE object
// face selection support.  It returns Acad::eOk if the passed pickpoint
// is within the bounds of the OLE object, any other return value should
// be interpreted as if the pickpoint is not within the bounds of the 
// object.
Acad::ErrorStatus
acdbOleHitTest(const AcDbOle2Frame* pOleEnt,     
               const AcGePoint3d&  wvpt, 
               const AcGeVector3d& wvwdir);

Acad::ErrorStatus
acdbOleGetRotationMatrix(const AcDbOle2Frame* pOleEnt,
                         AcGeMatrix3d& rotMat);

// Original width and height is used in
// calculating reset scale
Acad::ErrorStatus
acdbOleGetOriginalWidthHeight(const AcDbOle2Frame* pOleEnt,
                              double& width, 
                              double& height);

Acad::ErrorStatus
acdbOleSetOriginalWidthHeight(const AcDbOle2Frame* pOleEnt,
                              const double width, 
                              const double height);

// Selected font name, point size and size in Acad units
// is to persist the selected font name from the 
// OLE Text Size dialog
Acad::ErrorStatus
acdbOleGetSelectedFontName(const AcDbOle2Frame* pOleEnt,
                           ACHAR*& fontName);

Acad::ErrorStatus
acdbOleSetSelectedFontName(const AcDbOle2Frame* pOleEnt,
                           const ACHAR* fontName);

Acad::ErrorStatus
acdbOleGetSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                int& pointSize);

Acad::ErrorStatus
acdbOleSetSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                const int pointSize);

Acad::ErrorStatus
acdbOleGetSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                      double& sizeInAcadUnits);

Acad::ErrorStatus
acdbOleSetSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                      const double sizeInAcadUnits);

// Originally selected font name, point size and size in Acad units
// is to support Reset.  
Acad::ErrorStatus
acdbOleGetOriginalSelectedFontName(const AcDbOle2Frame* pOleEnt,
                                   ACHAR*& fontName);

Acad::ErrorStatus
acdbOleSetOriginalSelectedFontName(const AcDbOle2Frame* pOleEnt,
                                   const ACHAR* fontName);

Acad::ErrorStatus
acdbOleGetOriginalSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                        int& pointSize);

Acad::ErrorStatus
acdbOleSetOriginalSelectedFontPointSize(const AcDbOle2Frame* pOleEnt,
                                        const int pointSize);

Acad::ErrorStatus
acdbOleGetOriginalSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                              double& sizeInAcadUnits);

Acad::ErrorStatus
acdbOleSetOriginalSelectedTextSizeInAcadUnits(const AcDbOle2Frame* pOleEnt,
                                              const double sizeInAcadUnits);

// Dimension text background fill utility functions (for internal use)
// 
// pObj must be a AcDbDimension or AcDbDimStyleTableRecord derived object
// which stores dim text background fill in xData.
// bgFlag = 0: No fill for dimension text 
// bgFlag = 1: Use Acad drawing background color for dim text fill
// bgFlag = 2: Use specified color for dim text fill
// Internal use only. 
bool 
acdbGetDimTextBackground(AcDbObject *pObj, 
                         int& bgFlag, 
                         AcCmColor& bgColor);

// Internal use only. 
bool 
acdbSetDimTextBackground(AcDbObject *pObj, 
                         int bgFlag, 
                         AcCmColor* pBgColor,
                         bool autoClearOverride = true);

// Internal use only. 
bool 
acdbGetDimExtensionLength(AcDbObject *pObj, 
                          double& fValue);

// Internal use only. 
bool 
acdbSetDimExtensionLength(AcDbObject *pObj, 
                          double fValue,
                          bool autoClearOverride = true);
                          
// Internal use only. 
bool 
acdbGetFixedLengthExtLineEnabled(AcDbObject *pObj,
                   int& nValue);

// Internal use only. 
bool 
acdbSetFixedLengthExtLineEnabled(AcDbObject *pObj, 
                        int nValue, 
                        bool autoClearOverride=true);

// Internal use only. 
bool 
acdbGetArcLengthSymbolPlacement(AcDbObject *pObj,
                                int& nValue);

// Internal use only. 
bool 
acdbSetArcLengthSymbolPlacement(AcDbObject *pObj, 
                          int nValue,
                          bool autoClearOverride = true);
                          
// Internal use only.                           
bool 
acdbGetDimLineLinetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimLineLinetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);

// Internal use only. 
bool 
acdbGetDimExt1Linetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimExt1Linetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);
                       
// Internal use only.                        
bool 
acdbGetDimExt2Linetype(AcDbObject *pObj,
                       AcDbObjectId& oidValue);

// Internal use only. 
bool 
acdbSetDimExt2Linetype(AcDbObject *pObj,
                       AcDbObjectId oidValue,
                       bool autoClearOverride = true);
                       
// Internal use only.                        
bool 
acdbGetLargeRadDimJogAngle(AcDbObject *pObj,
                           double& fJogAngle);

// Internal use only. 
bool 
acdbSetLargeRadDimJogAngle(AcDbObject *pObj, 
                           double fJogAngle,
                           bool autoClearOverride = true);
                                
// Internal use only.                                 
bool 
acdbGetDimFlipArrow(AcDbObject *pObj,
                    int& nValue);

// Internal use only. 
bool 
acdbSetDimFlipArrow(AcDbObject *pObj, 
                    int nValue,
                    bool autoClearOverride = true);

// Internal use only.                                 
bool 
acdbGetDimTextDirection(AcDbObject *pObj,
                    int& nValue);

// Internal use only. 
bool 
acdbSetDimTextDirection(AcDbObject *pObj, 
                    int nValue,
                    bool autoClearOverride = true);
                    
// Internal use only.                     
bool 
acdbGetDimFlipArrowWhich(AcDbObject *pObj,
                         int& nValue);
                         
// Internal use only.                          
bool 
acdbSetDimFlipArrowWhich(AcDbObject *pObj, 
                          int nValue,
                          bool autoClearOverride = true);

// get/set a flag for dimstyle, linetype and layer object to exempt from
// CAD STANDARD check.
// pObj: pointer to AcDbObject
// bitFlags = 0x00:   No Exemption  
// bitFlags = 0x01:   Exempt from CAD Standard check
// 
bool acdbGetExemptCheckFlag(AcDbObject *pObj, int& bitFlags);

bool acdbSetExemptCheckFlag(AcDbObject *pObj, int bitFlags);

// Spago "DIMJAG" feature extension.
// Internal use only. 
bool
acdbGetDimJogSymbolSize(AcDbObject *pObj, 
                        int& dimJagFlag, 
                        double& dimJagSize);
// Internal use only.
bool
acdbSetDimJogSymbolSize(AcDbObject *pObj, 
                        int dimJagFlag, 
                        const double dimJagSize,
                        bool autoClearOverride = true);
// Internal use only.
bool
acdbGetDimJogSymbolPosition(AcDbObject *pObj, 
                        int& dimJagFlag, 
                        AcGePoint3d& pos);
// Internal use only.
bool
acdbSetDimJogSymbolPosition(AcDbObject *pObj, 
                        int& dimJagFlag, 
                        const AcGePoint3d& pos,
                        bool autoClearOverride = true);

// Spago "DIMRADIUS" arc extension.
// Internal use only. 
bool
acdbGetRadialExtensionAngles(AcDbObject *pObj,
                             int& dimExtFlag,
                             double& dimExtAng1,
                             double& dimExtAng2);

// Internal use only. 
bool
acdbSetRadialExtensionAngles(AcDbObject *pObj,
                             int dimExtFlag,
                             double dimExtAng1,
                             double dimExtAng2);

// Spago "DIMANGULAR" quadrant extension.
// Internal use only. 
bool
acdbGetDimAngExtOn(AcDbObject *pObj,
                             int& dimExtFlag);

// Internal use only. 
bool
acdbSetDimAngExtOn(AcDbObject *pObj,
                             int dimExtFlag);

// Spago Tolerance Dimension Alignment extension.
// Internal use only. 
bool
acdbGetDimTolAlign(AcDbObject *pObj,
                             int& dimTolAlignFlag);

// Internal use only. 
bool
acdbSetDimTolAlign(AcDbObject *pObj,
                             int dimTolAlignFlag,
                             bool autoClearOverride = true);


// Spago "DIMBREAK" feature extension.
// Internal use only. 
bool
acdbGetDimBreakSize(AcDbObject *pObj, 
                    double& dimBreakSize);
// Internal use only.
bool
acdbSetDimBreakSize(AcDbObject *pObj, 
                    double dimBreakSize,
                    bool autoClearOverride = true);

// Visual Style from viewport
AcDbObjectId acdbGetViewportVisualStyle();
Acad::ErrorStatus acdbSetViewportVisualStyle(AcDbObjectId visualStyleId);

// acdbForceTextAdjust()
// Forces the text to be adjusted in all text objects in the objectid array.
// objIds: input array of AcDbObjectId objects whose text will be adjusted.
//         Supported objects are AcDbText, AcDbBlockReference and AcDbBlockTableRecord.
Acad::ErrorStatus acdbForceTextAdjust(const AcDbObjectIdArray& objIds);

// Returns true if this object is in a long transaction.
bool acdbIsInLongTransaction(AcDbObjectId id);

/// <summary>
///  This API can be used to push the dragging info of an constraint 
///  geometry into the AutoCAD dragger. Basically, it allows client
///  to add additional sub entities that needs to be transformed 
///  along with actual sub entities that are moved through grip or
///  stretch operation.
///  This API should be used only when host application is AutoCAD.
///  Also, this should be called only during the dragging.
///  </summary>
///  <param name="pDraggingInfo"> dragging info of the constraint geometry
///  </param>
///  <returns> Error Status. For cases where host application is not 
///  a AutoCAD and it's not in the middle of dragger, it would return 
///  eNotApplicable.
///  </returns>
ACDB_PORT Acad::ErrorStatus acdbAddConstrainedGeometryDraggingInfo(
                const AcConstrainedGeometryDraggingInfo* pDraggingInfo);

#pragma pack (pop)
#endif // AD_DBXUTIL_H
