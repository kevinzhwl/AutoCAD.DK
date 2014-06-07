#ifndef AD_DBMAIN_H
#define AD_DBMAIN_H
//
// (C) Copyright 1993-2003 by Autodesk, Inc.
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
// DESCRIPTION: Main Exported Database Library Definitions

#include <stddef.h>
#include <share.h>
#include "gepnt3d.h"
#include "gevec3d.h"
#include "geline3d.h"
#include "AcHeapOpers.h"
#include "rxobject.h"
#include "rxdlinkr.h"
#include "rxiter.h"
#include "rxditer.h"
#include "rxsrvice.h"
#include "dbptrar.h"
#include "dbcolor.h"
#include "dbidar.h"
#include "drawable.h"
#include "dbsecurity.h"

class AcCmEntityColor;
class AcCmColor;
class AcDbBlockBegin;
class AcDbBlockEnd;
class AcDbDatabase;
class AcDbDatabaseIterator;
class AcDbDatabaseReactor;
class AcDbEntity;
class AcDbEntityReactor;
class AcDbImpDatabase;
class AcDbImpObject;
class AcDbObject;
class AcDbObjectReactor;
class AcDbServices;
class AcDbSpaceIterator;
class AcDbSystemInternals;
class AcDbXObject;
class AcDbBlockReference;
class AcDbSymbolTable;
class AcDbBlockTable;
class AcDbBlockTableRecord;    // (Used in AcDbExtents)
class AcDbLayerTable;
class AcDbTextStyleTable;
class AcDbLinetypeTable;
class AcDbAbstractViewTable;
class AcDbViewTable;
class AcDbUCSTable;
class AcDbViewportTable;
class AcDbRegAppTable;
class AcDbDimStyleTable;
class AcDbDimStyleTableRecord;
class AcDbIdMapping;
class AcDbDictionary;
class AcDbDictionaryWithDefault;
class AcDbMline;
class AcDbMlineStyle;
class AcDbCurve;
class AcDbEllipse;
class AcDbSpline;
class AcDbRegion;
class AcDb3dSolid;
class AcDbBody;
class AcDbDate;
class AcDbExtents;
class AcDbAuditInfo;
class AcDbUndoController;
class AcDbTransactionManager;
class AcDbSpatialFilter;
class AcDbLayerFilter;
class AcGeFastTransform;
class AcGsNode;
class AcGsModel;
class AcGiContext;
class AcDbObjectIdGraph;
class AcDbLayerStateManager;
class AcDwgFileHandle;
class AcFileDependencyManager;
class AcDbTableStyle;
class AcFdFieldValue;
class AcDbField;

#include "acdb.h"
#include "dbhandle.h"
#include "dbfiler.h"
#include "ads.h"
#include "gept3dar.h"
#include "dbintar.h"
#include "dbsubeid.h"
#include "dbaudita.h"

#pragma pack(push, 8)

// For getClassID without pulling in wtypes.h
//
struct _GUID;
typedef struct _GUID CLSID;

class AcDbGripData;
typedef AcArray<AcDbGripData*> AcDbGripDataPtrArray;

extern const AcDbFullSubentPath kNullSubent;

// Global Variables: API exports as functions.
//
AcDbServices* acdbServices();

// DXF Code --> Data Type mapping function
//
AcDb::DwgDataType acdbGroupCodeToType(AcDb::DxfCode pCode);
void              acdbFreeResBufContents(resbuf* pField);
bool              acdbIsPersistentReactor(void *pSomething);
AcDbObjectId      acdbPersistentReactorObjectId(void *pSomething);

bool   acdbDisplayPreviewFromDwg(const char *pszDwgfilename,
                                 void* pPreviewWnd,
                                 const Adesk::UInt32* pBgColor = NULL);

bool acdbIsCustomObject(const AcDbObjectId& id);

// Object Open Functions:  Exchange an object Id and 
// open mode for a pointer to the corresponding object.
//
Acad::ErrorStatus
acdbOpenAcDbObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode,
                   bool openErasedObject = false);
 
Acad::ErrorStatus ADESK_STDCALL
acdbOpenAcDbObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode,
                   const AcRxClass *pClass, bool openErasedObject = false);
 
Acad::ErrorStatus
acdbOpenAcDbEntity(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode,
                   bool openErasedEntity = false);

template<class T_OBJECT> inline Acad::ErrorStatus
acdbOpenObject(
    T_OBJECT *& pObj, AcDbObjectId id, AcDb::OpenMode mode,
    bool openErased = false)
{
    return ::acdbOpenAcDbObject((AcDbObject * &)pObj, id, mode,
                                T_OBJECT::desc(), openErased);
}
 
//
// Special case the open functions for AcDbObject and AcDbEntity,
// since we can open them without calling desc() to get an AcRxClass
// descriptor.
//
inline Acad::ErrorStatus acdbOpenObject(
    AcDbObject *& pObj, AcDbObjectId id, AcDb::OpenMode mode)
{
    return ::acdbOpenAcDbObject(pObj, id, mode, false);
}

inline Acad::ErrorStatus acdbOpenObject(
    AcDbEntity *& pEnt, AcDbObjectId id, AcDb::OpenMode mode)
{
    return ::acdbOpenAcDbEntity(pEnt, id, mode, false);
}

inline Acad::ErrorStatus acdbOpenObject(
    AcDbObject *& pObj, AcDbObjectId id, AcDb::OpenMode mode,
    bool openErased)
{
    return ::acdbOpenAcDbObject(pObj, id, mode, openErased);
}

inline Acad::ErrorStatus acdbOpenObject(
    AcDbEntity *& pEnt, AcDbObjectId id, AcDb::OpenMode mode,
    bool openErased)
{
    return ::acdbOpenAcDbEntity(pEnt, id, mode, openErased);
}

Acad::ErrorStatus acdbResurrectMeNow(const AcDbObjectId& id);
 
// Translate between AcDbObjectName and ads_name, for use
// with ADS library functions.
//
Acad::ErrorStatus acdbGetAdsName(ads_name&  objName, AcDbObjectId objId);
Acad::ErrorStatus acdbGetObjectId(AcDbObjectId& objId,
                                         const ads_name objName);

//  Mark an object as referenced, so it doesn't get automatically
//  purged after initial regen.
//
Acad::ErrorStatus acdbSetReferenced(AcDbObjectId objId);

// Get an AcDbVoidPtrArray to all currently active Databases
//
AcDbVoidPtrArray* acdbActiveDatabaseArray();

class AcDbViewTableRecord;
class AcDbViewport;

// Load an mline style file by name.
Acad::ErrorStatus acdbLoadMlineStyleFile(
                const char *sname, const char *fname);

// Load a linetype file by ltype name, and file name.  ltname may be wild.
Acad::ErrorStatus acdbLoadLineTypeFile(const char *ltname,
                                       const char *fname,
                                       AcDbDatabase *pDb);

//  Allocate memory from, and release it to, the AcDbObject
//  memory pool.  Any memory which will be freed by deleting an
//  AcDbObject should be allocated from this pool.   
//
void* acdbAlloc(size_t);
void* acdbRealloc(void *, size_t);
#ifdef MEM_DEBUG
void*             acdbAlloc_dbg(size_t ACDBG_FORMAL);
void*             acdbRealloc_dbg(void *, size_t ACDBG_FORMAL);
#define acdbAlloc(a) acdbAlloc_dbg(a, __FILE__, __LINE__)
#define acdbRealloc(a, b) acdbRealloc_dbg(a, b, __FILE__, __LINE__)
#endif
void  acdbFree(void*);

// ObjectDBX Host Apps must call this startup code after fulfilling
// all relevant contracts, eg registering a HostAppService object
//
Acad::ErrorStatus acdbValidateSetup(long lcid);

// ObjectDBX Host Apps must call this shutdown code before exiting
//
Acad::ErrorStatus acdbCleanUp();

const char* acdbOriginalXrefFullPathFor(const AcDbDatabase*);

//  sets the default graphics context for an application.
//  return value is the previous default graphics context (may be NULL).
AcGiContext * acdbSetDefaultAcGiContext(AcGiContext *);

//  DXF
Acad::ErrorStatus 
acdbGetThumbnailBitmapFromDxfFile(const char* filename, void*& pBitmap);

//  Backward compatibility.
Acad::ErrorStatus acdbSaveAs2000(AcDbDatabase* pDb, const char* fileName);

Acad::ErrorStatus acdbDxfOutAs2000(AcDbDatabase* pDb, const char* fileName,
                                         const int precision = 16);
Acad::ErrorStatus acdbDxfOutAsR12(AcDbDatabase* pDb, const char* fileName,
                                         const int precision = 16);

class ADESK_NO_VTABLE AcDbServices: public AcRxService
{
public:
    ACRX_DECLARE_MEMBERS(AcDbServices);
};


class AcDbDatabase: public AcRxObject, public AcHeapOperators
//
// A class whose instances represent an  entire DWG file,
// aka database itself.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabase);

    // constructor & destructor
    AcDbDatabase(bool buildDefaultDrawing = true,
                 bool noDocument = false);
    virtual ~AcDbDatabase();

    // Add objects (but not entities) to database

    Acad::ErrorStatus addAcDbObject(AcDbObject*    pObj);
    Acad::ErrorStatus addAcDbObject(AcDbObjectId&  objId,
                                    AcDbObject*    pObj);

    // Symbol Tables

    Acad::ErrorStatus getBlockTable     (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getLayerTable     (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getTextStyleTable (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getLinetypeTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getViewTable      (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getUCSTable       (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getViewportTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getRegAppTable    (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getDimStyleTable  (AcDbSymbolTable*& pTable,
                                         AcDb::OpenMode    mode);

    Acad::ErrorStatus getSymbolTable    (AcDbBlockTable*&     pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbLayerTable*&     pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbTextStyleTable*& pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbLinetypeTable*&  pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbViewTable*&      pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbUCSTable*&       pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbViewportTable*&  pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbRegAppTable*&    pTable,
                                         AcDb::OpenMode       mode);
    Acad::ErrorStatus getSymbolTable    (AcDbDimStyleTable*&  pTable,
                                         AcDb::OpenMode       mode);

    Acad::ErrorStatus getGroupDictionary   (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getMLStyleDictionary (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getLayoutDictionary  (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getPlotStyleNameDictionary(
                                            AcDbDictionaryWithDefault*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getMaterialDictionary(AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getColorDictionary   (AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);
    Acad::ErrorStatus getNamedObjectsDictionary(
                                            AcDbDictionary*& pDict,
                                            AcDb::OpenMode mode);

    // The following getXXXTable(AcDbXXXTable*& ...) functions exist
    // for backwards compatibility and may be removed in future
    // releases.
    Acad::ErrorStatus getBlockTable     (AcDbBlockTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getLayerTable     (AcDbLayerTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getTextStyleTable (AcDbTextStyleTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getLinetypeTable  (AcDbLinetypeTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getViewTable      (AcDbViewTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getUCSTable       (AcDbUCSTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getViewportTable  (AcDbViewportTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getRegAppTable    (AcDbRegAppTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getDimStyleTable  (AcDbDimStyleTable*& pTable,
                                         AcDb::OpenMode    mode);
    Acad::ErrorStatus getPlotSettingsDictionary(AcDbDictionary*& pTable,
                                         AcDb::OpenMode    mode);


    // Todo: change all these xxxTableId() and xxxDictionaryId()
    // methods to const.
    //
    AcDbObjectId  blockTableId();
    AcDbObjectId  layerTableId();
    AcDbObjectId  textStyleTableId();
    AcDbObjectId  linetypeTableId();
    AcDbObjectId  viewTableId();
    AcDbObjectId  UCSTableId();
    AcDbObjectId  viewportTableId();
    AcDbObjectId  regAppTableId();
    AcDbObjectId  dimStyleTableId();
    AcDbObjectId  mLStyleDictionaryId();
    AcDbObjectId  groupDictionaryId();
    AcDbObjectId  layoutDictionaryId();
    AcDbObjectId  plotStyleNameDictionaryId();
    AcDbObjectId  materialDictionaryId();
    AcDbObjectId  colorDictionaryId();
    AcDbObjectId  namedObjectsDictionaryId();
    AcDbObjectId  plotSettingsDictionaryId();

    AcDbObjectId layerZero() const;
    AcDbObjectId continuousLinetype() const;
    AcDbObjectId byLayerLinetype() const;
    AcDbObjectId byBlockLinetype() const;

    AcDbObjectId paperSpaceVportId() const;
    AcDbObjectId currentSpaceId() const;

    // Traverse the db and remove non-purgeable ids from the array
    Acad::ErrorStatus purge(AcDbObjectIdArray& ids);
    Acad::ErrorStatus purge(AcDbObjectIdGraph& idGraph);
    Acad::ErrorStatus countHardReferences(const AcDbObjectIdArray& ids,
                                          Adesk::UInt32* pCount);

    // Exchange (handle, xrefId) or name for AcDbObjectId 
    //
    Acad::ErrorStatus getAcDbObjectId(AcDbObjectId& retId,
                                      bool createIfNotFound,
                                      const AcDbHandle& objHandle,
                                      Adesk::UInt32 xRefId = 0);
    // Class Dxf Name for this database.
    //
    const char* classDxfName(const AcRxClass* pClass);

    // Filing Operations
    //
    Acad::ErrorStatus readDwgFile(const char* fileName,
                                  const int shmode = _SH_DENYWR,
                                  bool bAllowCPConversion = false,
                                  const wchar_t* wszPassword = NULL);
    Acad::ErrorStatus readDwgFile(AcDwgFileHandle *pDwgFile,
                                  bool bAllowCPConversion = false,
                                  const wchar_t* wszPassword = NULL);
    Acad::ErrorStatus saveAs(const char* fileName,
                             const SecurityParams* pSecParams = 0);
    Acad::ErrorStatus save();
    Acad::ErrorStatus dxfIn(const char* dxfFilename,
                            const char* logFilename=NULL);
    Acad::ErrorStatus dxfOut(const char* fileName,
                             const int precision = 16,
                             const bool saveThumbnailImage = false);

    Acad::ErrorStatus closeInput(bool bCloseFile = false);

    int approxNumObjects() const;
    Adesk::Int32 numberOfSaves() const;
    const char * originalFileName() const;
    AcDb::AcDbDwgVersion lastSavedAsVersion() const;
    AcDb::AcDbDwgVersion originalFileVersion() const;
    AcDb::AcDbDwgVersion originalFileSavedByVersion() const;
    AcDb::MaintenanceReleaseVersion lastSavedAsMaintenanceVersion() const;
    AcDb::MaintenanceReleaseVersion originalFileMaintenanceVersion() const;
    AcDb::MaintenanceReleaseVersion originalFileSavedByMaintenanceVersion() const;

    AcDwgFileHandle * inputFiler() const;

    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb,
                             const AcDbObjectIdArray& outObjIds,
                             const AcGePoint3d& basePoint);

    Acad::ErrorStatus wblock(AcDbDatabase* pOutputDb,  // pre-existing (template) db
                             const AcDbObjectIdArray& outObjIds,
                             const AcGePoint3d& basePoint,
                             AcDb::DuplicateRecordCloning drc);  // kDrcIgnore

    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb, AcDbObjectId blockId);
    Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb);

    // This will force the current WBLOCK* operation to result in
    // a database copy.  Only use this method if your application
    // does some special handling during WBLOCK* notifications and
    // you can only do that correctly if the WBLOCK* results in a
    // database copy.  Needless to say, a database copy will slow
    // down WBLOCK* and increase memory requirements.
    //
    void              forceWblockDatabaseCopy();

    // If preserveSourceDatabase is true, the contents of pDb will not
    // be changed.  If it is false, objects from pDb could be physically
    // moved into the database on which insert() is called.  The latter
    // is much faster.  But pDb will be left in a state where it depends
    // on "this" database (the one on which insert() was called) for vital
    // data.  So pDb should be deleted before "this" database is deleted.
    //
    Acad::ErrorStatus insert(AcDbObjectId& blockId, const char* pBlockName,
        AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    Acad::ErrorStatus insert(const AcGeMatrix3d& xform, AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    Acad::ErrorStatus insert(AcDbObjectId& blockId, 
        const char* pSourceBlockName,
        const char* pDestinationBlockName,
        AcDbDatabase* pDb,
        bool preserveSourceDatabase = true);

    Acad::ErrorStatus deepCloneObjects(AcDbObjectIdArray& objectIds,
        AcDbObjectId& owner, AcDbIdMapping& idMap,
        bool deferXlation = false);
       
    Acad::ErrorStatus wblockCloneObjects(AcDbObjectIdArray& objectIds,
        AcDbObjectId& owner, AcDbIdMapping& idMap,
        AcDb::DuplicateRecordCloning drc,
        bool deferXlation = false);

    void              abortDeepClone(AcDbIdMapping& idMap);

    void              addReactor(AcDbDatabaseReactor* pReactor) const;
    void              removeReactor(AcDbDatabaseReactor* pReactor) const;

    Acad::ErrorStatus audit(AcDbAuditInfo* pInfo);
    Acad::ErrorStatus auditXData(AcDbAuditInfo* pInfo);

    AcDbUndoController* undoController() const;
    void              disableUndoRecording(bool disable);
    bool              undoRecording() const ;

    AcDbTransactionManager* transactionManager() const;

    AcFileDependencyManager* fileDependencyManager() const;

    Adesk::UInt8      maintenanceReleaseVersion() const;

    Acad::ErrorStatus restoreOriginalXrefSymbols();
    Acad::ErrorStatus restoreForwardingXrefSymbols();

    AcDbObjectId      xrefBlockId() const;

    // Access to ThumbnailImage (preview)
    // These functions take a windows BITMAPINFO*
    //
    void*             thumbnailBitmap() const;
    Acad::ErrorStatus setThumbnailBitmap(void* pBmp);
    bool              retainOriginalThumbnailBitmap() const;
    void              setRetainOriginalThumbnailBitmap(bool retain);
    bool              isEMR() const;

    // methods to set and retrieve security-related information
    bool                  setSecurityParams(const SecurityParams* pSecParams,
                                            bool bSetDbMod = true);
    const SecurityParams* cloneSecurityParams();
    static void           disposeSecurityParams(const SecurityParams* pSecParams);

    // Header variables exposed via DXF and/or SETVAR
    //
    bool dimaso() const;
    Acad::ErrorStatus setDimaso(bool aso);

    bool dimsho() const;
    Acad::ErrorStatus setDimsho(bool sho);

    bool plinegen() const;
    Acad::ErrorStatus setPlinegen(bool gen);

    bool orthomode() const;
    Acad::ErrorStatus setOrthomode(bool mode);

    bool regenmode() const;
    Acad::ErrorStatus setRegenmode(bool mode);

    bool fillmode() const;
    Acad::ErrorStatus setFillmode(bool mode);

    bool qtextmode() const;
    Acad::ErrorStatus setQtextmode(bool mode);

    bool psltscale() const;
    Acad::ErrorStatus setPsltscale(bool scale);

    bool limcheck() const;
    Acad::ErrorStatus setLimcheck(bool check);

    bool blipmode() const;
    Acad::ErrorStatus setBlipmode(bool mode);

    Adesk::Int16 saveproxygraphics() const;
    Acad::ErrorStatus setSaveproxygraphics(Adesk::Int16 saveimg);

    bool delUsedObj() const;
    Acad::ErrorStatus setDelUsedObj(bool deleteObj);

    bool dispSilh() const;
    Acad::ErrorStatus setDispSilh(bool silh);

    bool plineEllipse() const;
    Acad::ErrorStatus setPlineEllipse(bool pline);

    bool usrtimer() const;
    Acad::ErrorStatus setUsrtimer(bool timer);

    bool skpoly() const;
    Acad::ErrorStatus setSkpoly(bool asPoly);

    bool angdir() const;
    Acad::ErrorStatus setAngdir(bool dir);

    bool splframe() const;
    Acad::ErrorStatus setSplframe(bool disp);

    bool attreq() const;
    Acad::ErrorStatus setAttreq(bool req);

    bool attdia() const;
    Acad::ErrorStatus setAttdia(bool dia);

    bool mirrtext() const;
    Acad::ErrorStatus setMirrtext(bool mirror);

    bool worldview() const;
    Acad::ErrorStatus setWorldview(bool view);

    bool tilemode() const;
    Acad::ErrorStatus setTilemode(bool mode);

    bool plimcheck() const;
    Acad::ErrorStatus setPlimcheck(bool check);

    bool visretain() const;
    Acad::ErrorStatus setVisretain(bool retain);

    Adesk::Int16 dragmode() const;
    Acad::ErrorStatus setDragmode(Adesk::Int16 mode);

    Adesk::Int16 treedepth() const;
    Acad::ErrorStatus setTreedepth(Adesk::Int16 depth);

    Adesk::Int16 lunits() const;
    Acad::ErrorStatus setLunits(Adesk::Int16 lunits);

    Adesk::Int16 luprec() const;
    Acad::ErrorStatus setLuprec(Adesk::Int16 prec);

    Adesk::Int16 aunits() const;
    Acad::ErrorStatus setAunits(Adesk::Int16 aunits);

    Adesk::Int16 auprec() const;
    Acad::ErrorStatus setAuprec(Adesk::Int16 auprec);

    Adesk::Int16 osmode() const;
    Acad::ErrorStatus setOsmode(Adesk::Int16 mode);

    Adesk::Int16 attmode() const;
    Acad::ErrorStatus setAttmode(Adesk::Int16 mode);

    Adesk::Int16 coords() const;
    Acad::ErrorStatus setCoords(Adesk::Int16 coords);

    Adesk::Int16 pdmode() const;
    Acad::ErrorStatus setPdmode(Adesk::Int16 mode);

    Adesk::Int16 pickstyle() const;
    Acad::ErrorStatus setPickstyle(Adesk::Int16 style);

    Adesk::Int16 useri1() const;
    Acad::ErrorStatus setUseri1(Adesk::Int16 val);

    Adesk::Int16 useri2() const;
    Acad::ErrorStatus setUseri2(Adesk::Int16 val);

    Adesk::Int16 useri3() const;
    Acad::ErrorStatus setUseri3(Adesk::Int16 val);

    Adesk::Int16 useri4() const;
    Acad::ErrorStatus setUseri4(Adesk::Int16 val);

    Adesk::Int16 useri5() const;
    Acad::ErrorStatus setUseri5(Adesk::Int16 val);

    Adesk::Int16 splinesegs() const;
    Acad::ErrorStatus setSplinesegs(Adesk::Int16 segs);

    Adesk::Int16 surfu() const;
    Acad::ErrorStatus setSurfu(Adesk::Int16 u);

    Adesk::Int16 surfv() const;
    Acad::ErrorStatus setSurfv(Adesk::Int16 v);

    Adesk::Int16 surftype() const;
    Acad::ErrorStatus setSurftype(Adesk::Int16 type);

    Adesk::Int16 surftab1() const;
    Acad::ErrorStatus setSurftab1(Adesk::Int16 tab1);

    Adesk::Int16 surftab2() const;
    Acad::ErrorStatus setSurftab2(Adesk::Int16 tab2);

    Adesk::Int16 splinetype() const;
    Acad::ErrorStatus setSplinetype(Adesk::Int16 type);

    Adesk::Int16 shadedge() const;
    Acad::ErrorStatus setShadedge(Adesk::Int16 mode);

    Adesk::Int16 shadedif() const;
    Acad::ErrorStatus setShadedif(Adesk::Int16 dif);

    AcDb::MeasurementValue measurement() const;
    Acad::ErrorStatus setMeasurement(AcDb::MeasurementValue type);

    Adesk::Int16 unitmode() const;
    Acad::ErrorStatus setUnitmode(Adesk::Int16 mode);

    Adesk::Int16 maxactvp() const;
    Acad::ErrorStatus setMaxactvp(Adesk::Int16 max);

    Adesk::Int16 isolines() const;
    Acad::ErrorStatus setIsolines(Adesk::Int16 isolines);

    double ltscale() const;
    Acad::ErrorStatus setLtscale(double scale);

    double textsize() const;
    Acad::ErrorStatus setTextsize(double size);

    double tracewid() const;
    Acad::ErrorStatus setTracewid(double width);

    double sketchinc() const;
    Acad::ErrorStatus setSketchinc(double inc);

    double filletrad() const;
    Acad::ErrorStatus setFilletrad(double radius);

    double thickness() const;
    Acad::ErrorStatus setThickness(double thickness);

    AcDb::LineWeight  celweight() const;
    Acad::ErrorStatus setCelweight(AcDb::LineWeight weight);

    static bool       isValidLineWeight(int weight);
    static AcDb::LineWeight getNearestLineWeight(int weight);

    AcDb::EndCaps endCaps() const;
    Acad::ErrorStatus setEndCaps(AcDb::EndCaps type);

    AcDb::JoinStyle joinStyle() const;
    Acad::ErrorStatus setJoinStyle(AcDb::JoinStyle style);

    bool lineWeightDisplay() const;
    Acad::ErrorStatus setLineWeightDisplay(bool display);

    bool xrefEditEnabled() const;
    Acad::ErrorStatus setXrefEditEnabled(bool enable);

    bool oleStartUp() const;
    Acad::ErrorStatus setOleStartUp(bool val);

    double angbase() const;
    Acad::ErrorStatus setAngbase(double angle);

    double pdsize() const;
    Acad::ErrorStatus setPdsize(double size);

    double plinewid() const;
    Acad::ErrorStatus setPlinewid(double width);

    double userr1() const;
    Acad::ErrorStatus setUserr1(double val);

    double userr2() const;
    Acad::ErrorStatus setUserr2(double val);

    double userr3() const;
    Acad::ErrorStatus setUserr3(double val);

    double userr4() const;
    Acad::ErrorStatus setUserr4(double val);

    double userr5() const;
    Acad::ErrorStatus setUserr5(double val);

    double chamfera() const;
    Acad::ErrorStatus setChamfera(double val);

    double chamferb() const;
    Acad::ErrorStatus setChamferb(double val);

    double chamferc() const;
    Acad::ErrorStatus setChamferc(double val);

    double chamferd() const;
    Acad::ErrorStatus setChamferd(double val);

    double facetres() const;
    Acad::ErrorStatus setFacetres(double facetres);

    Acad::ErrorStatus getMenu(char*& pOutput) const;

    const AcDbDate tdcreate() const;     // returns a local time
    const AcDbDate tdupdate() const;

    const AcDbDate tducreate() const;    // returns a universal time
    const AcDbDate tduupdate() const;

    const AcDbDate tdindwg() const;      // returns a time delta
    const AcDbDate tdusrtimer() const;

    AcCmColor cecolor() const;
    Acad::ErrorStatus setCecolor(const AcCmColor& color);

    AcDbHandle handseed() const;
    Acad::ErrorStatus setHandseed(const AcDbHandle& handle);

    AcDbObjectId clayer() const;
    Acad::ErrorStatus setClayer(AcDbObjectId objId);

    AcDb::PlotStyleNameType getCePlotStyleNameId(AcDbObjectId& id) const;
    Acad::ErrorStatus       setCePlotStyleName(AcDb::PlotStyleNameType,
                            AcDbObjectId newId = AcDbObjectId::kNull);
    
    AcDbObjectId textstyle() const;
    Acad::ErrorStatus setTextstyle(AcDbObjectId objId);

    AcDbObjectId celtype() const;
    Acad::ErrorStatus setCeltype(AcDbObjectId objId);

    AcDbObjectId dimstyle() const;
    Acad::ErrorStatus setDimstyle(AcDbObjectId styleId);

    Acad::ErrorStatus getDimstyleData(AcDbDimStyleTableRecord*& pRec) const;
    Acad::ErrorStatus getDimstyleChildData(const AcRxClass *pDimClass,
                                           AcDbDimStyleTableRecord*& pRec,
                                           AcDbObjectId &style) const;
    AcDbObjectId getDimstyleChildId(const AcRxClass *pDimClass,
                                    AcDbObjectId &parentStyle) const;

    AcDbObjectId getDimstyleParentId(AcDbObjectId &childStyle) const;
                                           
    Acad::ErrorStatus setDimstyleData(AcDbDimStyleTableRecord* pRec);
    Acad::ErrorStatus setDimstyleData(AcDbObjectId id);

    AcDbObjectId cmlstyleID() const;
    Acad::ErrorStatus setCmlstyleID(AcDbObjectId objId);

    Adesk::Int16 cmljust() const;
    Acad::ErrorStatus setCmljust(Adesk::Int16 just);

    double cmlscale() const;
    Acad::ErrorStatus setCmlscale(double scale);

    double celtscale() const;
    Acad::ErrorStatus setCeltscale(double scale);

    // Paper space variable access

    AcGePoint3d pinsbase() const;
    Acad::ErrorStatus setPinsbase(const AcGePoint3d& base);

    AcGePoint3d pextmin() const;

    AcGePoint3d pextmax() const;

    Acad::ErrorStatus setPextmin(const AcGePoint3d& min);
    Acad::ErrorStatus setPextmax(const AcGePoint3d& max);

    AcGePoint2d plimmin() const;
    Acad::ErrorStatus setPlimmin(const AcGePoint2d& min);

    AcGePoint2d plimmax() const;
    Acad::ErrorStatus setPlimmax(const AcGePoint2d& max);

    double pelevation() const;
    Acad::ErrorStatus setPelevation(double elev);

    AcGePoint3d pucsorg() const;

    AcGeVector3d pucsxdir() const;

    AcGeVector3d pucsydir() const;

    AcDbObjectId pucsname() const;

    AcDbObjectId pucsBase() const;
    Acad::ErrorStatus setPucsBase(const AcDbObjectId &ucsid);

    AcGePoint3d worldPucsBaseOrigin(AcDb::OrthographicView orthoView) const;
    Acad::ErrorStatus setWorldPucsBaseOrigin(const AcGePoint3d& origin,
                                             AcDb::OrthographicView orthoView);

    bool isPucsOrthographic(AcDb::OrthographicView& orthoView) const;


    // Model space variable access

    AcGePoint3d insbase() const;
    Acad::ErrorStatus setInsbase(const AcGePoint3d& base);

    AcGePoint3d extmin() const;

    AcGePoint3d extmax() const;

    Acad::ErrorStatus updateExt(bool doBestFit = FALSE);

    Acad::ErrorStatus setExtmin(const AcGePoint3d& min);
    Acad::ErrorStatus setExtmax(const AcGePoint3d& max);

    AcGePoint2d limmin() const;
    Acad::ErrorStatus setLimmin(const AcGePoint2d& min);

    AcGePoint2d limmax() const;
    Acad::ErrorStatus setLimmax(const AcGePoint2d& max);

    double elevation() const;
    Acad::ErrorStatus setElevation(double elev);

    AcGePoint3d ucsorg() const;

    AcGeVector3d ucsxdir() const;

    AcGeVector3d ucsydir() const;

    AcDbObjectId ucsname() const;

    AcDbObjectId ucsBase() const;
    Acad::ErrorStatus setUcsBase(AcDbObjectId ucsid);

    AcGePoint3d worldUcsBaseOrigin(AcDb::OrthographicView orthoView) const;
    Acad::ErrorStatus setWorldUcsBaseOrigin(const AcGePoint3d& origin,
                                            AcDb::OrthographicView orthoView);

    bool isUcsOrthographic(AcDb::OrthographicView& orthoView) const;


    // Dimension variable api:
    //
    #undef DBDIMVAR_H                   // force the file to get read again
    #include "dbdimvar.h"

    // DEPRECATED METHODS!
    // These are supported but will be removed in future releases:
    //
    Acad::ErrorStatus getDimpost(char*& pOutput) const;
    Acad::ErrorStatus getDimapost(char*& pOutput) const;
    Acad::ErrorStatus getDimblk(char*& pOutput) const;
    Acad::ErrorStatus getDimblk1(char*& pOutput) const;
    Acad::ErrorStatus getDimblk2(char*& pOutput) const;

    int dimfit() const;
    int dimunit() const;

    Acad::ErrorStatus setDimfit(int fit);
    Acad::ErrorStatus setDimunit(int unit);
    //
    // end DEPRECATED METHODS!


    Acad::ErrorStatus getDimRecentStyleList(AcDbObjectIdArray& objIds) const;

    Acad::ErrorStatus loadLineTypeFile(const char *ltn, const char *filename);

    Acad::ErrorStatus getProjectName(char*& pOutput) const;
    Acad::ErrorStatus setProjectName(const char*);
    Acad::ErrorStatus getHyperlinkBase(char*& pOutput) const;
    Acad::ErrorStatus setHyperlinkBase(const char*);
    Acad::ErrorStatus getStyleSheet(char*& pOutput) const;
    Acad::ErrorStatus setStyleSheet(const char*);
    Acad::ErrorStatus getFilename(const char* & pOutput) const;

    bool              isPartiallyOpened() const;
    Acad::ErrorStatus applyPartialOpenFilters(
        const AcDbSpatialFilter* pSpatialFilter,
        const AcDbLayerFilter* pLayerFilter);
    // This will abort the current partial open operation and
    // continue in a full open of the database.
    //
    void              disablePartialOpen();

    Acad::ErrorStatus getFingerprintGuid(char*& guidString) const;
    Acad::ErrorStatus setFingerprintGuid(const char *pNewGuid);

    Acad::ErrorStatus getVersionGuid(char*& guidString) const;
    Acad::ErrorStatus setVersionGuid(const char *pNewGuid);


    // New text sysvars
    //
    int tstackalign() const;
    Acad::ErrorStatus setTStackAlign(int val);

    int tstacksize() const;
    Acad::ErrorStatus setTStackSize(int val);

    AcDb::UnitsValue insunits() const;
    Acad::ErrorStatus setInsunits(const AcDb::UnitsValue units);

    // Graphics cache
    //
    void                setGsModel(AcGsModel*);
    AcGsModel*          gsModel() const;

    // Plot Style Legacy
    bool           plotStyleMode() const;

    // Default paperspace viewport scale
    double viewportScaleDefault() const;
    Acad::ErrorStatus setViewportScaleDefault(double newDefaultVPScale);

    // dwg watermark
    bool           dwgFileWasSavedByAutodeskSoftware() const;

    // Layer state manager API
    AcDbLayerStateManager *getLayerStateManager() const;

    // When entity traversals are sorted (AcDb::kSortEnts*).
    Adesk::UInt8        sortEnts() const;
    Acad::ErrorStatus   setSortEnts(Adesk::UInt8 sortEnts);

    Adesk::UInt8        drawOrderCtl() const;
    Acad::ErrorStatus   setDrawOrderCtl(Adesk::UInt8 val);
    
    Adesk::UInt8        dimAssoc() const;
    Acad::ErrorStatus setDimAssoc(Adesk::UInt8 val);

    Adesk::UInt8 hideText() const;
    Acad::ErrorStatus setHideText(Adesk::UInt8 val);

    Adesk::UInt8  haloGap() const;
    Acad::ErrorStatus setHaloGap(Adesk::UInt8 val);

    Adesk::UInt16 obscuredColor() const;
    Acad::ErrorStatus setObscuredColor(Adesk::UInt16 val);

    Adesk::UInt8 obscuredLineType() const;
    Acad::ErrorStatus setObscuredLineType(Adesk::UInt8 val);

    Adesk::UInt8  intersectDisplay() const;
    Acad::ErrorStatus setIntersectDisplay(Adesk::UInt8 val);

    Adesk::UInt16 intersectColor() const;
    Acad::ErrorStatus setIntersectColor(Adesk::UInt16 val);

    // For the ACAD_TABLESTYLE dictionary
    Acad::ErrorStatus getTableStyleDictionary(AcDbDictionary*& pDict,
                                              AcDb::OpenMode mode);
    AcDbObjectId  tableStyleDictionaryId() const;

    // The following functions are similar to setDimstyle/dimstyle
    //
    AcDbObjectId tablestyle() const;
    Acad::ErrorStatus setTablestyle(AcDbObjectId objId);

    Acad::ErrorStatus evaluateFields(int nContext,
                                     const char* pszPropName= NULL,
                                     AcDbDatabase* pDb      = NULL,
                                     int* pNumFound         = NULL,
                                     int* pNumEvaluated     = NULL);

    // Get all AcDbViewports in all AcDbLayouts in the database
    Acad::ErrorStatus getViewportArray(AcDbObjectIdArray& vportIds,
                                       bool bGetPaperspaceVports = true) const;


private:
    friend class AcDbSystemInternals;
    AcDbImpDatabase* mpImpDb;
};

class AcDbObjectIterator: public AcRxObject, public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectIterator);
    virtual ~AcDbObjectIterator();

    bool           done() const;
    void           step(bool backwards = false, bool skipDeleted = true);
    void           setPosition(AcDbEntity*  pEnt);
    void           setPosition(AcDbObjectId  pObj);
    void           start(bool atEnd = false);
    AcDbEntity*    entity();
    AcDbObjectId   objectId();

private:
    friend class AcDbSystemInternals;
    AcDbObjectIterator();
    AcDbSpaceIterator* mpImpIterator;
};


class ADESK_NO_VTABLE AcDbObject: public AcGiDrawable, public AcHeapOperators
{
public:
    ACDB_DECLARE_MEMBERS(AcDbObject);

    virtual ~AcDbObject();

    // Associated Objects
    //
    AcDbObjectId      objectId() const;
    AcDbObjectId      ownerId() const;
    virtual Acad::ErrorStatus setOwnerId(AcDbObjectId objId);
    void              getAcDbHandle(AcDbHandle& handle) const;
    AcDbDatabase*     database() const;
    Acad::ErrorStatus createExtensionDictionary();
    AcDbObjectId      extensionDictionary() const;
    Acad::ErrorStatus releaseExtensionDictionary();

    // Open/Close/Cancel/Undo/Erase
    //
    Acad::ErrorStatus upgradeOpen();
    Acad::ErrorStatus upgradeFromNotify(Adesk::Boolean& wasWritable);
    Acad::ErrorStatus downgradeOpen();
    Acad::ErrorStatus downgradeToNotify(Adesk::Boolean wasWritable);
    virtual Acad::ErrorStatus subOpen(AcDb::OpenMode mode);

    Acad::ErrorStatus cancel();
    virtual Acad::ErrorStatus subCancel();

    Acad::ErrorStatus close();
    Acad::ErrorStatus closeAndPage(Adesk::Boolean onlyWhenClean = true);
    virtual Acad::ErrorStatus subClose();

    Acad::ErrorStatus erase(Adesk::Boolean erasing = true);
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing);

    Acad::ErrorStatus handOverTo(AcDbObject* newObject,
                                 Adesk::Boolean keepXData = true,
                                 Adesk::Boolean keepExtDict = true);
    virtual Acad::ErrorStatus subHandOverTo(AcDbObject* newObject);

    Acad::ErrorStatus swapIdWith(AcDbObjectId otherId, 
                                 Adesk::Boolean swapXdata = false,
                                 Adesk::Boolean swapExtDict = false);
    virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId,
                                 Adesk::Boolean swapXdata = false,
                                 Adesk::Boolean swapExtDict = false);

    virtual Acad::ErrorStatus swapReferences (const AcDbIdMapping& idMap);

    // Audit
    //
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    // Filing
    //
    Acad::ErrorStatus         dwgIn       (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    Acad::ErrorStatus         dwgOut      (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    Acad::ErrorStatus         dxfIn       (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);
    Acad::ErrorStatus         dxfOut      (AcDbDxfFiler* pFiler,
                                           Adesk::Boolean allXdFlag,
                                           Adesk::uchar* regAppTable) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    // Merge style for insert-style operations. Defaults to kDrcIgnore.
    //
    virtual AcDb::DuplicateRecordCloning mergeStyle () const;

    // XData
    //
    virtual resbuf*           xData   (const char* regappName = NULL) const;
    virtual Acad::ErrorStatus setXData(const resbuf* xdata);
            Acad::ErrorStatus xDataTransformBy(const AcGeMatrix3d& xform);

    // Binary chunks
    //
    Acad::ErrorStatus         setBinaryData(const char * key,
                                            long         size,
                                            const char * data);
    Acad::ErrorStatus         getBinaryData(const char * key,
                                            long &       size,
                                            char*&       data) const;

    // XObject
    // Open/Notify/Undo/Modified State Predicates
    //
    Adesk::Boolean isEraseStatusToggled() const;
    Adesk::Boolean isErased() const;
    Adesk::Boolean isReadEnabled() const;
    Adesk::Boolean isWriteEnabled() const;
    Adesk::Boolean isNotifyEnabled() const;
    Adesk::Boolean isModified() const;
    Adesk::Boolean isModifiedXData() const;
    Adesk::Boolean isModifiedGraphics() const;
    Adesk::Boolean isNewObject() const;
    Adesk::Boolean isNotifying() const;
    Adesk::Boolean isUndoing() const;
    Adesk::Boolean isCancelling() const;
    Adesk::Boolean isReallyClosing() const;
    Adesk::Boolean isTransactionResident() const;

    // Formerly isAZombie()
    //
    Adesk::Boolean isAProxy() const;

    // Access State Assertions
    //
    void assertReadEnabled() const;
    void assertWriteEnabled(Adesk::Boolean autoUndo = true,
                            Adesk::Boolean recordModified = true);
    void assertNotifyEnabled() const;

    // Undo 
    //
    void                      disableUndoRecording(Adesk::Boolean disable);
    AcDbDwgFiler*             undoFiler();
    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler,
                                               AcRxClass*    classObj);

    // Notification
    //
    void                      addReactor(AcDbObjectReactor* newObj) const;
    void                      removeReactor(AcDbObjectReactor* newObj) const;
    virtual void              addPersistentReactor(AcDbObjectId objId);
    virtual Acad::ErrorStatus removePersistentReactor(AcDbObjectId objId);
    bool                      hasPersistentReactor(AcDbObjectId objId) const;
    AcDbVoidPtrArray*         reactors();

    virtual void              recvPropagateModify(const AcDbObject* subObj);
    virtual void              xmitPropagateModify() const;

    virtual Acad::ErrorStatus deepClone(AcDbObject* pOwnerObject,
                                        AcDbObject*& pClonedObject,
                                        AcDbIdMapping& idMap,
                                        Adesk::Boolean isPrimary = true) const;
 
    virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject,
                                          AcDbObject*& pClonedObject,
                                          AcDbIdMapping& idMap,
                                          Adesk::Boolean isPrimary = true) const;

    void              setAcDbObjectIdsInFlux();
    Adesk::Boolean    isAcDbObjectIdsInFlux() const;

    // Notification for persistent reactors.
    //
    virtual void cancelled       (const AcDbObject* dbObj);
    virtual void copied          (const AcDbObject* dbObj,
                                  const AcDbObject* newObj);
    virtual void erased          (const AcDbObject* dbObj,
                                  Adesk::Boolean pErasing = true);
    virtual void goodbye         (const AcDbObject* dbObj);
    virtual void openedForModify (const AcDbObject* dbObj);
    virtual void modified        (const AcDbObject* dbObj);
    virtual void subObjModified  (const AcDbObject* dbObj,
                                  const AcDbObject* subObj);
    virtual void modifyUndone    (const AcDbObject* dbObj);
    virtual void modifiedXData   (const AcDbObject* dbObj);
    virtual void unappended      (const AcDbObject* dbObj);
    virtual void reappended      (const AcDbObject* dbObj);
    virtual void objectClosed    (const AcDbObjectId objId);
    virtual void modifiedGraphics(const AcDbEntity* dbEnt);

    // AcRxObject Protocol
    // Derived classes should not override these member implementations.
    //
    virtual AcRxObject*        clone() const;
    virtual Acad::ErrorStatus  copyFrom(const AcRxObject* pSrc);

    // Save to previous versions.
    //
    bool       hasSaveVersionOverride();
    void       setHasSaveVersionOverride(bool bSetIt);

    virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDwgFiler* pFiler, 
                                 AcDb::AcDbDwgVersion& ver,
                                 AcDb::MaintenanceReleaseVersion& maintVer);
    virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDxfFiler* pFiler, 
                                 AcDb::AcDbDwgVersion& ver,
                                 AcDb::MaintenanceReleaseVersion& maintVer);
            Acad::ErrorStatus getObjectBirthVersion(
                                 AcDb::AcDbDwgVersion& ver,
                                 AcDb::MaintenanceReleaseVersion& maintVer);

    // Saving as previous versions.
    //
    virtual Acad::ErrorStatus   decomposeForSave(
                                AcDb::AcDbDwgVersion ver,
                                AcDbObject*& replaceObj,
                                AcDbObjectId& replaceId,
                                Adesk::Boolean& exchangeXData);

    virtual AcGiDrawable*       drawable();

    // AcGiDrawable interface
    //
    virtual Adesk::UInt32       setAttributes(AcGiDrawableTraits* pTraits);
    virtual Adesk::Boolean      worldDraw(AcGiWorldDraw* pWd);
    virtual void                viewportDraw(AcGiViewportDraw* pVd);
    virtual Adesk::Boolean      isPersistent() const;
    virtual AcDbObjectId        id() const;
    virtual void                setGsNode(AcGsNode* pNode);
    virtual AcGsNode*           gsNode() const;

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;

    bool              hasFields(void) const;
    Acad::ErrorStatus getField(const char* pszPropName, 
                               AcDbObjectId& fieldId) const;
    Acad::ErrorStatus getField(const char* pszPropName, AcDbField*& pField,
                               AcDb::OpenMode mode) const;

    Acad::ErrorStatus setField(const char* pszPropName, AcDbField* pField,
                               AcDbObjectId& fieldId);

    Acad::ErrorStatus removeField(AcDbObjectId fieldId);
    Acad::ErrorStatus removeField(const char* pszPropName, AcDbObjectId& returnId);
    Acad::ErrorStatus removeField(const char* pszPropName);
    AcDbObjectId      getFieldDictionary(void) const;
    Acad::ErrorStatus getFieldDictionary(AcDbDictionary*& pFieldDict, 
                             AcDb::OpenMode mode) const;

protected:
    AcDbObject();
private:
    friend class AcDbSystemInternals;
    AcDbImpObject*            mpImpObject;
};

class ADESK_NO_VTABLE AcDbXObject: public AcRxObject
//
// AcRxObject which recognizes filer protocol,
// and has a ACRX_DXF_CLASS_OBJ_BODY
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbXObject);

    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    Acad::ErrorStatus dwgIn(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    protected:
    AcDbXObject();
};

class AcCmComplexColor: public  AcDbXObject
{
public:
    ACRX_DECLARE_MEMBERS(AcCmComplexColor); 

    virtual AcCmComplexColor* incReference();
    virtual void              decReference();

    virtual Acad::ErrorStatus getDescription(char*& desc) const;
    virtual Acad::ErrorStatus getExplanation(char*& expl) const;

    virtual AcCmEntityColor::ColorMethod  colorMethod() const;
    virtual Acad::ErrorStatus setColorMethod(
        AcCmEntityColor::ColorMethod eColorMethod);

    virtual bool              isByColor() const;
    virtual bool              isByLayer() const;
    virtual bool              isByBlock() const;
    virtual bool              isByACI()   const;
    virtual bool              isByPen ()  const;
    virtual bool              isForeground()   const;

    virtual Adesk::UInt32     color() const;
    virtual Acad::ErrorStatus setColor(Adesk::UInt32 color);

    virtual Acad::ErrorStatus setRGB  (Adesk::UInt8 red, 
                                       Adesk::UInt8 green, 
                                       Adesk::UInt8 blue);
    virtual Acad::ErrorStatus setRed  (Adesk::UInt8 red);
    virtual Acad::ErrorStatus setGreen(Adesk::UInt8 green);
    virtual Acad::ErrorStatus setBlue (Adesk::UInt8 blue);
    virtual Adesk::UInt8      red  () const;
    virtual Adesk::UInt8      green() const;
    virtual Adesk::UInt8      blue () const;

    virtual Adesk::UInt16     colorIndex() const;
    virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex);
    virtual Adesk::UInt16     penIndex() const;   
    virtual Acad::ErrorStatus setPenIndex (Adesk::UInt16 penIndex);


    // --- AcRxObject protocol
    //
    virtual Acad::ErrorStatus copyFrom(const AcRxObject*);

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

private:
    Adesk::UInt16 refCount;
    AcCmEntityColor mColor;
};

class AcCmColor : public AcCmColorBase
{
public:
    AcCmColor();
    AcCmColor(const AcCmColor&);
    AcCmColor(const AcCmColorBase&);
    AcCmColor& operator=(const AcCmColor& inputColor);
    AcCmColor& operator=(const AcCmColorBase& inputColor);
    ~AcCmColor();

    bool operator ==(const AcCmColor& color) const;
    bool operator !=(const AcCmColor& color) const;
    bool operator ==(const AcCmColorBase& color) const;
    bool operator !=(const AcCmColorBase& color) const;
    
    Acad::ErrorStatus getDescription(char*& desc) const;
    Acad::ErrorStatus getExplanation(char*& expl) const;

    virtual AcCmEntityColor::ColorMethod  colorMethod() const;
    virtual Acad::ErrorStatus setColorMethod(AcCmEntityColor::ColorMethod eColorMethod);

    virtual bool    isByColor() const;
    virtual bool    isByLayer() const;
    virtual bool    isByBlock() const;
    virtual bool    isByACI()   const;
    virtual bool    isByPen () const;
    virtual bool    isForeground()   const;

    bool            isNone() const;

    virtual Adesk::UInt32     color() const;
    virtual Acad::ErrorStatus setColor(Adesk::UInt32 color);

    virtual Acad::ErrorStatus setRGB  (Adesk::UInt8 red, 
                               Adesk::UInt8 green, 
                               Adesk::UInt8 blue);
    virtual Acad::ErrorStatus setRed  (Adesk::UInt8 red);
    virtual Acad::ErrorStatus setGreen(Adesk::UInt8 green);
    virtual Acad::ErrorStatus setBlue (Adesk::UInt8 blue);
    virtual Adesk::UInt8      red  () const;
    virtual Adesk::UInt8      green() const;
    virtual Adesk::UInt8      blue () const;

    virtual Adesk::UInt16     colorIndex() const;
    virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex);
    virtual Adesk::UInt16     penIndex() const;   
    virtual Acad::ErrorStatus setPenIndex (Adesk::UInt16 penIndex);

    virtual Acad::ErrorStatus setNames(const char *colorName,
                                       const char *bookName = NULL);
    virtual const char *      colorName(void) const;
    virtual const char *      bookName(void) const;
    virtual const char *      colorNameForDisplay(void);
    virtual bool              hasColorName(void) const;
    virtual bool              hasBookName(void) const;

    AcCmEntityColor           entityColor(void) const;
    int                       dictionaryKeyLength(void) const;
    void                      getDictionaryKey(char *) const;
    Acad::ErrorStatus         setNamesFromDictionaryKey(const char *);

    // --- AcRxObject protocol
    //
    Acad::ErrorStatus dwgIn(AcDbDwgFiler* pInputFiler);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler *pOutputFiler) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler, int groupCodeOffset = 0);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler, int groupCodeOffset = 0) const;

    Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);

    Acad::ErrorStatus serializeOut(void *pBuff, int *pBuflen) const;
    Acad::ErrorStatus serializeIn(const void *pBuff, int *pBuflen);

    static const Adesk::UInt16 MaxColorIndex; 

    AcCmComplexColor* complexColor() const;
    void setComplexColor(AcCmComplexColor* pComplex);

    Acad::ErrorStatus dwgInAsTrueColor(AcDbDwgFiler* pInputFiler); // For internal use only
    Acad::ErrorStatus dwgOutAsTrueColor(AcDbDwgFiler *pOutputFiler) const; // For internal use only

private:

    enum NameFlags {    kNoNames            = 0x00,
                        kHasColorName       = 0x01,
                        kHasBookName        = 0x02
                    };


    static const Adesk::UInt16 ComplexColorFlag; 
    bool isComplex() const;


    AcCmEntityColor::RGBM   mRGBM;
    char *                  mColorName;
    char *                  mBookName;
    Adesk::UInt8            mNameFlags;

};

// the following functions convert strings to AcCmColor instances
// Parameters:
//        clr  - reference to an instance of AcCmColor.  This instance
//               will be filled out with the color value corresponding
//             to pInput or pBookName, pColorName
//      pInput - pointer to a string representation of a color.  This
//             can be an ACI color [ByBlock, red, 70] or an RGB color
//             [120,12,36]
//        pBookName - pointer to a string specifying the name of a
//               colorbook
//        pColorName - pointer to a string specifying the name of a
//             color in the colorbook identified by pBookName
//
// Return values:
//        Acad::eOk                    for success
//        Acad::eBadColor                for an invalid string or strings
//      Acad::eInvalidInput            if no colorbooks are present
//      Acad::eNotImplementedYet    if certain dlls are not present
//
Acad::ErrorStatus accmGetColorFromACIName(AcCmColor& clr, const char *pInput);
Acad::ErrorStatus accmGetColorFromRGBName(AcCmColor& clr, const char *pInput);
Acad::ErrorStatus accmGetColorFromColorBookName(AcCmColor& clr, const char *pBookName, const char *pColorName);

// the following function gets localized names for the standard
//  AutoCAD colors: ByBlock, red, yellow, green, ..., ByLayer
void accmGetLocalizedColorNames( const char* colors[9] );

class AcDbColor: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbColor);

    AcDbColor();
    virtual ~AcDbColor();

    void getColor(AcCmColor& color) const;
    void setColor(const AcCmColor& color);
    const AcCmEntityColor& entityColor(void) const;

    // Saving as previous versions.
    //
    virtual Acad::ErrorStatus   decomposeForSave(
                                AcDb::AcDbDwgVersion ver,
                                AcDbObject*& replaceObj,
                                AcDbObjectId& replaceId,
                                Adesk::Boolean& exchangeXData);


    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const;

    virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject,
                                          AcDbObject*& pClonedObject,
                                          AcDbIdMapping& idMap,
                                          Adesk::Boolean isPrimary
                                          = true) const;
    
private:

    AcCmColor           m_color;    // main storage
    AcCmEntityColor     m_ecol;     // quick reference

};


class ADESK_NO_VTABLE AcDbEntity: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbEntity);

    virtual ~AcDbEntity();

    AcDbObjectId                blockId() const;

    AcCmColor                   color() const;
    virtual Acad::ErrorStatus   setColor(const AcCmColor& color,
                                  Adesk::Boolean doSubents = true);
    Adesk::UInt16               colorIndex() const;
    virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color,
                                  Adesk::Boolean doSubents = true);
    AcCmEntityColor             entityColor() const;

    AcCmTransparency            transparency() const;
    virtual Acad::ErrorStatus   setTransparency(const AcCmTransparency& trans,
                                  Adesk::Boolean doSubents = true);


    char*                       plotStyleName() const;
    AcDb::PlotStyleNameType     getPlotStyleNameId(AcDbObjectId& id) const;
    virtual Acad::ErrorStatus   setPlotStyleName(const char* newName,
                                  Adesk::Boolean doSubents = true);
    virtual Acad::ErrorStatus   setPlotStyleName(AcDb::PlotStyleNameType,
                                AcDbObjectId newId = AcDbObjectId::kNull,
                                Adesk::Boolean doSubents = true);
    
    char*                       layer() const;
    AcDbObjectId                layerId() const;
    virtual Acad::ErrorStatus   setLayer(const char* newVal,
                                  Adesk::Boolean doSubents = true);
    virtual Acad::ErrorStatus   setLayer(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = true);

    char*                       linetype() const;
    AcDbObjectId                linetypeId() const;
    virtual Acad::ErrorStatus   setLinetype(const char* newVal,
                                  Adesk::Boolean doSubents = true);
    virtual Acad::ErrorStatus   setLinetype(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = true);

    double                      linetypeScale() const;
    virtual Acad::ErrorStatus   setLinetypeScale(double newval,
                                  Adesk::Boolean doSubents = true);

    AcDb::Visibility            visibility() const;
    virtual Acad::ErrorStatus   setVisibility(AcDb::Visibility newVal,
                                  Adesk::Boolean doSubents = true);

    AcDb::LineWeight            lineWeight() const;
    virtual Acad::ErrorStatus   setLineWeight(AcDb::LineWeight newVal,
                                  Adesk::Boolean doSubents = true);

    Acad::ErrorStatus           setPropertiesFrom(const AcDbEntity* pEntity,
                                  Adesk::Boolean doSubents = true);

    virtual Adesk::Boolean      isPlanar() const { return false; }
    virtual Acad::ErrorStatus   getPlane(AcGePlane&, AcDb::Planarity&) const
                                    { return Acad::eNotApplicable; }

    virtual void                getEcs(AcGeMatrix3d& retVal) const;

    virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;

    // Subentity acquisition.
    //
    virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(
                                  AcDb::SubentType       type,
                                  int                    gsMark, 
                                  const AcGePoint3d&     pickPoint,
                                  const AcGeMatrix3d&    viewXform, 
                                  int&                   numPaths,
                                  AcDbFullSubentPath*&   subentPaths, 
                                  int                    numInserts = 0,
                                  AcDbObjectId*          entAndInsertStack
                                                           = NULL) const;

    virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(
                                  AcDb::SubentType       type,
                                  int                    gsMark, 
                                  const AcGePoint3d&     pickPoint,
                                  const AcGeFastTransform&  viewXform, 
                                  int&                   numPaths,
                                  AcDbFullSubentPath*&   subentPaths, 
                                  int                    numInserts = 0,
                                  AcDbObjectId*          entAndInsertStack
                                                           = NULL) const;

    virtual  Acad::ErrorStatus getGsMarkersAtSubentPath(
                               const AcDbFullSubentPath& subPath, 
                               AcDbIntArray& gsMarkers) const;

    virtual Acad::ErrorStatus highlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll 
                        = false) const;
    virtual Acad::ErrorStatus unhighlight(const AcDbFullSubentPath& subId 
                                        = kNullSubent, const Adesk::Boolean highlightAll  
                        = false) const;
    virtual AcDbEntity*       subentPtr(const AcDbFullSubentPath& id) const;
 
    virtual Acad::ErrorStatus   getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 int                 gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeMatrix3d& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray&       geomIds) const;

    virtual Acad::ErrorStatus   getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 int                 gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeFastTransform& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray&       geomIds) const;

    virtual Acad::ErrorStatus   getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 int                 gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeMatrix3d& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray&       geomIds,
                                 const AcGeMatrix3d& insertionMat) const;

    virtual Acad::ErrorStatus   getOsnapPoints(
                                 AcDb::OsnapMode     osnapMode,
                                 int                 gsSelectionMark,
                                 const AcGePoint3d&  pickPoint,
                                 const AcGePoint3d&  lastPoint,
                                 const AcGeFastTransform& viewXform,
                                 AcGePoint3dArray&   snapPoints,
                                 AcDbIntArray&       geomIds,
                                 const AcGeMatrix3d& insertionMat) const;

    virtual Acad::ErrorStatus   getGripPoints(
                                   AcGePoint3dArray&  gripPoints,
                                   AcDbIntArray&  osnapModes,
                                   AcDbIntArray&  geomIds) const;

    virtual  Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    virtual Acad::ErrorStatus   getGripPoints(AcDbGripDataPtrArray& grips,
        const double curViewUnitSize, const int gripSize, 
        const AcGeVector3d& curViewDir, const int bitflags) const;

    virtual  Acad::ErrorStatus moveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
        const AcGeVector3d& offset, const int bitflags);
    
    virtual Acad::ErrorStatus getStretchPoints(
        AcGePoint3dArray& stretchPoints) const;
    virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                    AcDb::Intersect intType, 
                                    AcGePoint3dArray& points,
                                    int thisGsMarker = 0, 
                                    int otherGsMarker = 0) const;
 
    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                             AcDb::Intersect intType, 
                                             const AcGePlane& projPlane,
                                             AcGePoint3dArray& points, 
                                             int thisGsMarker = 0,
                                             int otherGsMarker = 0) const;

    Acad::ErrorStatus          boundingBoxIntersectWith(
                                             const AcDbEntity*   pEnt,
                                             AcDb::Intersect     intType,
                                             AcGePoint3dArray&   points,
                                             int                 thisGsMarker,
                                             int                 otherGsMarker) const;

    Acad::ErrorStatus          boundingBoxIntersectWith(
                                             const AcDbEntity*   pEnt,
                                             AcDb::Intersect     intType,
                                             const AcGePlane&    projPlane,
                                             AcGePoint3dArray&   points,
                                             int                 thisGsMarker,
                                             int                 otherGsMarker) const;

    virtual void                list() const;

    virtual Acad::ErrorStatus   transformBy(const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus   transformBy(const AcGeFastTransform& xform);
    virtual Acad::ErrorStatus   getTransformedCopy(const AcGeMatrix3d& xform,
                                                   AcDbEntity*& pEnt) const;
    virtual Acad::ErrorStatus   explode(AcDbVoidPtrArray& entitySet) const;

    void                        recordGraphicsModified(
                                    Adesk::Boolean setModified = true);

    Acad::ErrorStatus           draw();
    virtual Adesk::Boolean      worldDraw(AcGiWorldDraw*        mode);
    virtual void                viewportDraw(AcGiViewportDraw*  mode);
    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    virtual Acad::ErrorStatus   getCompoundObjectTransform(AcGeMatrix3d & xMat) const;

    void                        setDatabaseDefaults();
    void                        setDatabaseDefaults(AcDbDatabase* pDb);
    virtual void                subSetDatabaseDefaults(AcDbDatabase* pDb);

    virtual Acad::ErrorStatus   applyPartialUndo(AcDbDwgFiler* undoFiler,
                                                 AcRxClass*    classObj);

    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const;


    virtual AcGiDrawable*       drawable();

    // AcGiDrawable interface
    //
    virtual Adesk::UInt32       setAttributes(AcGiDrawableTraits* pTraits);
    virtual void                setGsNode(AcGsNode* pNode);
    virtual AcGsNode*           gsNode() const;

    virtual Adesk::Boolean      cloneMeForDragging();

    virtual void                dragStatus(const AcDb::DragStat status);
    virtual void                gripStatus(const AcDb::GripStat status);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;

protected:
    // Makes AcDbEntity an abstract class.
    AcDbEntity();
};

// Note: makes sense to put this inline, even though it's
// a virtual, because all derived classes' dtors will call
// this dtor directly.
//
inline AcDbEntity::~AcDbEntity()
{
    // Do Nothing, AcDbObject destructor takes care of imp object.
}

class ADESK_NO_VTABLE AcDbObjectReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectReactor);

    virtual void cancelled      (const AcDbObject* dbObj);
    virtual void copied         (const AcDbObject* dbObj,
                                 const AcDbObject* newObj);
    virtual void erased         (const AcDbObject* dbObj,
                                 Adesk::Boolean pErasing = true);
    virtual void goodbye        (const AcDbObject* dbObj);
    virtual void openedForModify(const AcDbObject* dbObj);
    virtual void modified       (const AcDbObject* dbObj);
    virtual void subObjModified (const AcDbObject* dbObj,
                                 const AcDbObject* subObj);
    virtual void modifyUndone   (const AcDbObject* dbObj);
    virtual void modifiedXData  (const AcDbObject* dbObj);
    virtual void unappended     (const AcDbObject* dbObj);
    virtual void reappended     (const AcDbObject* dbObj);
    virtual void objectClosed   (const AcDbObjectId objId);

protected:
    AcDbObjectReactor();
};

class ADESK_NO_VTABLE AcDbEntityReactor: public AcDbObjectReactor
{
public:
    ACRX_DECLARE_MEMBERS(AcDbEntityReactor);
    virtual void modifiedGraphics(const AcDbEntity* dbObj);
    virtual void dragCloneToBeDeleted (const AcDbEntity* pOriginalObj,
                                       const AcDbEntity* pClone);
protected:
    AcDbEntityReactor();
};

class ADESK_NO_VTABLE AcDbDatabaseReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabaseReactor);

    virtual void objectAppended       (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectUnAppended     (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectReAppended     (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectOpenedForModify(const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectModified       (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectErased         (const AcDbDatabase* dwg, const AcDbObject* dbObj,
                                        Adesk::Boolean pErased = true);
    virtual void headerSysVarWillChange(const AcDbDatabase* dwg, const char* name);
    virtual void headerSysVarChanged   (const AcDbDatabase* dwg, const char* name,
                                        Adesk::Boolean bSuccess);
    virtual void proxyResurrectionCompleted(const AcDbDatabase* dwg,
                                            const char* appname, 
                                            AcDbObjectIdArray& objects);
    virtual void goodbye              (const AcDbDatabase* dwg);
};

class AcDbExtents : public AcHeapOperators
{
public:
    AcDbExtents();                                      
    AcDbExtents(const AcDbExtents& src);           
    AcDbExtents(const AcGePoint3d& min, const AcGePoint3d& max);  
 
    AcGePoint3d       minPoint() const { return mMinPoint; }
    AcGePoint3d       maxPoint() const { return mMaxPoint; }
    Acad::ErrorStatus set(const AcGePoint3d& min, const AcGePoint3d& max);

    void              addPoint (const AcGePoint3d& pt);
    void              addExt   (const AcDbExtents& src);
    Acad::ErrorStatus addBlockExt(AcDbBlockTableRecord* pBTR);

    void expandBy(const AcGeVector3d& vec);
    void transformBy(const AcGeMatrix3d& mat);

private:
    AcGePoint3d    mMinPoint;
    AcGePoint3d    mMaxPoint;
};

// The following getXXXTable inlined functions exist for backward
// compatibility and may be removed in future releases.

inline Acad::ErrorStatus
AcDbDatabase::getBlockTable(
    AcDbBlockTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getLayerTable(
    AcDbLayerTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getTextStyleTable(
    AcDbTextStyleTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getLinetypeTable(
    AcDbLinetypeTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getViewTable(
    AcDbViewTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getUCSTable(
    AcDbUCSTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getViewportTable(
    AcDbViewportTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getRegAppTable(
    AcDbRegAppTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

inline Acad::ErrorStatus
AcDbDatabase::getDimStyleTable(
    AcDbDimStyleTable*& pTable,
    AcDb::OpenMode mode)
{
    return getSymbolTable(pTable, mode);
}

/////////////////////////////////////////////////////////////////////////
// Text Finder API.
#define AC_SRCH_BLOCK         0x01
#define AC_SRCH_DIM_TEXT      0x02
#define AC_SRCH_TEXT          0x04
#define AC_SRCH_LINK_DESC     0x08
#define AC_SRCH_LINK_URL      0x10
#define AC_SRCH_MATCH_CASE    0x20
#define AC_SRCH_WHOLE_WORD    0x40

#define AC_SRCH_DEFAULT       0x1F

bool acdbTextFind(AcDbDatabase* pDatabase,
                  AcDbObjectIdArray& resultSet,
                  const char* findString,
                  const char* replaceString = NULL,
                  Adesk::UInt8 searchOptions = AC_SRCH_DEFAULT,
                  const AcDbObjectIdArray& selSet = 0);

#pragma pack(pop)

#endif
