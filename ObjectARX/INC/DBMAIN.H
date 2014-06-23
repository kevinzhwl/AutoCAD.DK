#ifndef AD_DBMAIN_H
#define AD_DBMAIN_H
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
// DESCRIPTION: Main Exported Database Library Definitions

#include <stddef.h>
#include "gepnt3d.h"
#include "gevec3d.h"
#include "geline3d.h"
#include "rxobject.h"
#include "rxdlinkr.h"
#include "rxiter.h"
#include "rxditer.h"
#include "rxsrvice.h"
#include "dbptrar.h"

class AcGiWorldDraw;
class AcGiViewportDraw;
class AcDbBlockBegin;
class AcDbBlockEnd;
class AcDbDatabase;
class AcDbDatabaseIterator;
class AcDbDatabaseReactor;
class AcDbEntity;
class AcDbEntityReactor;
class AcDbImpDatabase;
class AcDbImpObjectIterator;
class AcDbImpObject;
class AcDbObject;
class AcDbObjectReactor;
class AcDbPersistentObjectReactor;
class AcDbServices;
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
class AcDbMline;
class AcDbMlineStyle;
class AcDbCurve;
class AcDbEllipse;
class AcDbSpline;
class AcDbRegion;
class AcDb3dSolid;
class AcDbBody;
class AcDbDate;
class AcCmColor;
class AcDbExtents;
class AcDbAuditInfo;

#include "acdb.h"
#include "dbhandle.h"
#include "dbfiler.h"
#ifndef _
#define _(x) x
#endif
#include "ads.h"
#include "gept3dar.h"
#include "dbintar.h"
#include "dbsubeid.h"
#include "dbaudita.h"

#include "rxcom.h"

extern const AcDbFullSubentPath kNullSubent;

// Global Variables: API exports as functions.
//
extern AcDbDatabase* acdbCurDwg();
extern AcDbServices* acdbServices();

// DXF Code --> Data Type mapping function
//
extern AcDb::DwgDataType acdbGroupCodeToType(AcDb::DxfCode pCode);
extern void              acdbFreeResBufContents(resbuf* pField);
extern Adesk::Boolean    acdbIsPersistentReactor(void *pSomething);
extern AcDbObjectId      acdbPersistentReactorObjectId(void *pSomething);
extern Acad::ErrorStatus acdbGetCurrentSelectionSet(AcDbObjectIdArray& sset);

Adesk::Boolean   acdbDisplayPreviewFromDwg(const char *pszDwgfilename, void* pPreviewWnd);

Adesk::Boolean acdbIsCustomObject(const AcDbObjectId&);

// Object Open Functions:  Exchange an object Id and 
// open mode for a pointer to the corresponding object.
//
extern Acad::ErrorStatus 
acdbOpenAcDbObject(AcDbObject*&, AcDbObjectId, AcDb::OpenMode,
		   Adesk::Boolean openErasedObject = Adesk::kFalse);
 
extern Acad::ErrorStatus 
acdbOpenAcDbEntity(AcDbEntity*&, AcDbObjectId, AcDb::OpenMode,
		   Adesk::Boolean openErasedEntity = Adesk::kFalse);
 
#ifdef ACDB_COM_SUPPORT
extern Acad::ErrorStatus acdbOpenAndQueryInterfaceOnObject(
		AcDbObjectId     objId,
		AcDb::OpenMode   openMode,
		REFIID           riid,
		AcDbObject**     ppvObj,
		Adesk::Boolean   openErasedObject = Adesk::kFalse );
#endif

// Translate between AcDbObjectName and ads_name, for use
// with ADS library functions.
//
extern Acad::ErrorStatus acdbGetAdsName(ads_name&  objName, AcDbObjectId objId);
extern Acad::ErrorStatus acdbGetObjectId(AcDbObjectId& objId, ads_name  objName);

//  Mark an object as referenced, so it doesn't get automatically
//  purged after initial regen.
//
extern Acad::ErrorStatus acdbSetReferenced(AcDbObjectId objId);

// Set the current UCS from a 3D matrix.
extern Acad::ErrorStatus acdbSetCurrentUCS(AcGeMatrix3d mat);

class AcDbViewTableRecord;
class AcDbViewport;

// Set the current view from an AcDbViewTableRecord.
extern Acad::ErrorStatus
acdbSetCurrentView(AcDbViewTableRecord *pVwRec, AcDbViewport *pVP);

// Set the current viewport from an AcDbViewport.
extern Acad::ErrorStatus acdbSetCurrentVPort(AcDbViewport *pVP);
extern Acad::ErrorStatus acdbSetCurrentVPort(int vpn);

// Get the current viewport ObjectId for the current viewport.
extern AcDbObjectId acdbGetCurViewportObjectId();

// Load an mline style file by name.
extern Acad::ErrorStatus acdbLoadMlineStyleFile(
		const char *sname, const char *fname);

// Load a linetype file by ltype name, and file name.  ltname may be wild.
extern Acad::ErrorStatus acdbLoadLineTypeFile(const char *ltname,
					      const char *fname,
					      AcDbDatabase *pDb);

//  Allocate memory from, and release it to, the AcDbObject
//  memory pool.  Any memory which will be freed by deleting an
//  AcDbObject should be allocated from this pool.   
//
extern void* acdbAlloc(size_t);
#ifdef LEAKCHECK
extern void*             acdbAlloc(size_t DBG_FORMAL);
#define acdbAlloc(a) acdbAlloc(a ,__FILE__, __LINE__)
#endif
extern void  acdbFree(void*);

//  AutoCAD color to RGB conversion function
//
extern unsigned long     acdbGetRGB(int color);

class AcDbServices: public AcRxService
{
public:
    ACRX_DECLARE_MEMBERS(AcDbServices);
};

class AcDbObjectIdArray;

class AcDbDatabase: public AcRxObject
//
// A class whose instances represent an  entire DWG file,
// aka database itself.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabase);

    // Add objects (but not entities) to database

    Acad::ErrorStatus addAcDbObject(AcDbObject*    pObj);
    Acad::ErrorStatus addAcDbObject(AcDbObjectId&  objId,
		     	            AcDbObject*    pObj);

    // Symbol Tables

    Acad::ErrorStatus getBlockTable(AcDbBlockTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getLayerTable(AcDbLayerTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getTextStyleTable(AcDbTextStyleTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getLinetypeTable(AcDbLinetypeTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getViewTable(AcDbViewTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getUCSTable(AcDbUCSTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getViewportTable(AcDbViewportTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getRegAppTable(AcDbRegAppTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getDimStyleTable(AcDbDimStyleTable*&, AcDb::OpenMode);
    Acad::ErrorStatus getGroupDictionary(AcDbDictionary*&, AcDb::OpenMode);
    Acad::ErrorStatus getMLStyleDictionary(AcDbDictionary*&, AcDb::OpenMode);
    Acad::ErrorStatus getNamedObjectsDictionary(AcDbDictionary*&, 
						AcDb::OpenMode);
    AcDbObjectId      mLStyleDictionaryId();
    AcDbObjectId      groupDictionaryId();
    AcDbObjectId      namedObjectsDictionaryId();

    // Traverse the db and remove non-purgeable ids from the array
    Acad::ErrorStatus purge(AcDbObjectIdArray&);
    Acad::ErrorStatus countHardReferences(const AcDbObjectIdArray&,
                                          Adesk::UInt32 *);

    // Exchange (handle, xrefId) or name for AcDbObjectId 
    //
    Acad::ErrorStatus getAcDbObjectId(AcDbObjectId& retId,
				      Adesk::Boolean createIfNotFound,
				      const AcDbHandle& objHandle,
				      Adesk::UInt32 xRefId = 0);
    // Class Dxf Name for this database.
    //
    const char* classDxfName(const AcRxClass* pClass);

    // Filing Operations
    //
    Acad::ErrorStatus readDwgFile(const char* fileName);
    Acad::ErrorStatus saveAs(const char* fileName);
    Acad::ErrorStatus save();

    Acad::ErrorStatus closeInput();

    int approxNumObjects() const;

    AcDbDwgFiler*     inputFiler() const;
    static Acad::ErrorStatus open(AcDbDatabase*& pNewDb, AcDbDwgFiler*  pInputFiler,
				  Adesk::Boolean enableUndo = Adesk::kFalse);
    static Acad::ErrorStatus salvage(AcDbDatabase*& pNewDb, AcDbDwgFiler*  pInputFiler);
    Acad::ErrorStatus        saveAs(AcDbDwgFiler* pOutputFiler);

    Acad::ErrorStatus wblock(AcDbDatabase*&, const AcDbObjectIdArray&,
	                     const AcGePoint3d&);

    Acad::ErrorStatus wblock(AcDbDatabase*&, AcDbObjectId);
    Acad::ErrorStatus wblock(AcDbDatabase* &);

    // This will force the current WBLOCK* operation to result in
    // a database copy.  Only use this method if your application
    // does some special handling during WBLOCK* notifications and
    // you can only do that correctly if the WBLOCK* results in a
    // database copy.  Needless to say, a database copy will slow
    // down WBLOCK* and increase memory requirements.
    //
    void              forceWblockDatabaseCopy();

    // If preserveSourceDatabase is kTrue, the contents of pDb will not
    // be changed.  If it is kFalse, objects from pDb could be physically
    // moved into the database on which insert() is called.  The latter
    // is much faster.  But pDb will be left in a state where it depends
    // on "this" database (the one on which insert() was called) for vital
    // data.  So pDb should be deleted before "this" database is deleted.
    //
    Acad::ErrorStatus        insert(AcDbObjectId& blockId, const char* pBlockName,
				    AcDbDatabase* pDb,
				    Adesk::Boolean preserveSourceDatabase
						   = Adesk::kTrue);
    Acad::ErrorStatus        insert(const AcGeMatrix3d& xform, AcDbDatabase* pDb,
				    Adesk::Boolean preserveSourceDatabase
						   = Adesk::kTrue);
 
    Acad::ErrorStatus        deepCloneObjects(AcDbObjectIdArray& objectIds,
					      AcDbObjectId& owner,
					      AcDbIdMapping& idMap,
					      Adesk::Boolean deferXlation
						     = Adesk::kFalse);
			       
    void                     abortDeepClone(AcDbIdMapping& idMap);

    void                     addReactor(AcDbDatabaseReactor* pReactor) const;
    void                     removeReactor(AcDbDatabaseReactor* pReactor) const;

    Acad::ErrorStatus        audit(AcDbAuditInfo*);
    Acad::ErrorStatus        auditXData(AcDbAuditInfo*);

    void                     disableUndoRecording(Adesk::Boolean disable);
    Adesk::UInt8             maintenanceReleaseVersion() const;
 
#ifdef ACDBLIB
    // Access to ThumbnailImage (preview)
    // These functions are not available in the ARX API
    //
    void*             getThumbnailBitmap() const;
    Acad::ErrorStatus setThumbnailBitmap(void* pBmp);
    void              resetThumbnailImage();
    void              setThumbnailClearOnSave(Adesk::Boolean);
#endif /* ACDBLIB */

    // Header variables exposed via DXF and/or SETVAR
    //
    Adesk::Boolean dimaso() const;
    Acad::ErrorStatus setDimaso(Adesk::Boolean);

    Adesk::Boolean dimsho() const;
    Acad::ErrorStatus setDimsho(Adesk::Boolean);

    Adesk::Boolean plinegen() const;
    Acad::ErrorStatus setPlinegen(Adesk::Boolean);

    Adesk::Boolean orthomode() const;
    Acad::ErrorStatus setOrthomode(Adesk::Boolean);

    Adesk::Boolean regenmode() const;
    Acad::ErrorStatus setRegenmode(Adesk::Boolean);

    Adesk::Boolean fillmode() const;
    Acad::ErrorStatus setFillmode(Adesk::Boolean);

    Adesk::Boolean qtextmode() const;
    Acad::ErrorStatus setQtextmode(Adesk::Boolean);

    Adesk::Boolean psltscale() const;
    Acad::ErrorStatus setPsltscale(Adesk::Boolean);

    Adesk::Boolean limcheck() const;
    Acad::ErrorStatus setLimcheck(Adesk::Boolean);

    Adesk::Boolean blipmode() const;
    Acad::ErrorStatus setBlipmode(Adesk::Boolean);

    Adesk::Int16 saveproxygraphics() const;
    Acad::ErrorStatus setSaveproxygraphics(Adesk::Int16);

    Adesk::Boolean delUsedObj() const;
    Acad::ErrorStatus setDelUsedObj(Adesk::Boolean);

    Adesk::Boolean dispSilh() const;
    Acad::ErrorStatus setDispSilh(Adesk::Boolean);

    Adesk::Boolean plineEllipse() const;
    Acad::ErrorStatus setPlineEllipse(Adesk::Boolean);

    Adesk::Boolean usrtimer() const;
    Acad::ErrorStatus setUsrtimer(Adesk::Boolean);

    Adesk::Boolean skpoly() const;
    Acad::ErrorStatus setSkpoly(Adesk::Boolean);

    Adesk::Boolean angdir() const;
    Acad::ErrorStatus setAngdir(Adesk::Boolean);

    Adesk::Boolean splframe() const;
    Acad::ErrorStatus setSplframe(Adesk::Boolean);

    Adesk::Boolean attreq() const;
    Acad::ErrorStatus setAttreq(Adesk::Boolean);

    Adesk::Boolean attdia() const;
    Acad::ErrorStatus setAttdia(Adesk::Boolean);

    Adesk::Boolean mirrtext() const;
    Acad::ErrorStatus setMirrtext(Adesk::Boolean);

    Adesk::Boolean worldview() const;
    Acad::ErrorStatus setWorldview(Adesk::Boolean);

    Adesk::Boolean tilemode() const;
    Acad::ErrorStatus setTilemode(Adesk::Boolean);

    Adesk::Boolean plimcheck() const;
    Acad::ErrorStatus setPlimcheck(Adesk::Boolean);

    Adesk::Boolean visretain() const;
    Acad::ErrorStatus setVisretain(Adesk::Boolean);

    Adesk::Int16 dragmode() const;
    Acad::ErrorStatus setDragmode(Adesk::Int16);

    Adesk::Int16 treedepth() const;
    Acad::ErrorStatus setTreedepth(Adesk::Int16);

    Adesk::Int16 lunits() const;
    Acad::ErrorStatus setLunits(Adesk::Int16);

    Adesk::Int16 luprec() const;
    Acad::ErrorStatus setLuprec(Adesk::Int16);

    Adesk::Int16 aunits() const;
    Acad::ErrorStatus setAunits(Adesk::Int16);

    Adesk::Int16 auprec() const;
    Acad::ErrorStatus setAuprec(Adesk::Int16);

    Adesk::Int16 osmode() const;
    Acad::ErrorStatus setOsmode(Adesk::Int16);

    Adesk::Int16 attmode() const;
    Acad::ErrorStatus setAttmode(Adesk::Int16);

    Adesk::Int16 coords() const;
    Acad::ErrorStatus setCoords(Adesk::Int16);

    Adesk::Int16 pdmode() const;
    Acad::ErrorStatus setPdmode(Adesk::Int16);

    Adesk::Int16 pickstyle() const;
    Acad::ErrorStatus setPickstyle(Adesk::Int16);

    Adesk::Int16 useri1() const;
    Acad::ErrorStatus setUseri1(Adesk::Int16);

    Adesk::Int16 useri2() const;
    Acad::ErrorStatus setUseri2(Adesk::Int16);

    Adesk::Int16 useri3() const;
    Acad::ErrorStatus setUseri3(Adesk::Int16);

    Adesk::Int16 useri4() const;
    Acad::ErrorStatus setUseri4(Adesk::Int16);

    Adesk::Int16 useri5() const;
    Acad::ErrorStatus setUseri5(Adesk::Int16);

    Adesk::Int16 splinesegs() const;
    Acad::ErrorStatus setSplinesegs(Adesk::Int16);

    Adesk::Int16 surfu() const;
    Acad::ErrorStatus setSurfu(Adesk::Int16);

    Adesk::Int16 surfv() const;
    Acad::ErrorStatus setSurfv(Adesk::Int16);

    Adesk::Int16 surftype() const;
    Acad::ErrorStatus setSurftype(Adesk::Int16);

    Adesk::Int16 surftab1() const;
    Acad::ErrorStatus setSurftab1(Adesk::Int16);

    Adesk::Int16 surftab2() const;
    Acad::ErrorStatus setSurftab2(Adesk::Int16);

    Adesk::Int16 splinetype() const;
    Acad::ErrorStatus setSplinetype(Adesk::Int16);

    Adesk::Int16 shadedge() const;
    Acad::ErrorStatus setShadedge(Adesk::Int16);

    Adesk::Int16 shadedif() const;
    Acad::ErrorStatus setShadedif(Adesk::Int16);

    AcDb::MeasurementValue measurement() const;
    Acad::ErrorStatus setMeasurement(AcDb::MeasurementValue);

    Adesk::Int16 unitmode() const;
    Acad::ErrorStatus setUnitmode(Adesk::Int16);

    Adesk::Int16 maxactvp() const;
    Acad::ErrorStatus setMaxactvp(Adesk::Int16);

    Adesk::Int16 isolines() const;
    Acad::ErrorStatus setIsolines(Adesk::Int16);

    double ltscale() const;
    Acad::ErrorStatus setLtscale(double);

    double textsize() const;
    Acad::ErrorStatus setTextsize(double);

    double tracewid() const;
    Acad::ErrorStatus setTracewid(double);

    double sketchinc() const;
    Acad::ErrorStatus setSketchinc(double);

    double filletrad() const;
    Acad::ErrorStatus setFilletrad(double);

    double thickness() const;
    Acad::ErrorStatus setThickness(double);

    double angbase() const;
    Acad::ErrorStatus setAngbase(double);

    double pdsize() const;
    Acad::ErrorStatus setPdsize(double);

    double plinewid() const;
    Acad::ErrorStatus setPlinewid(double);

    double userr1() const;
    Acad::ErrorStatus setUserr1(double);

    double userr2() const;
    Acad::ErrorStatus setUserr2(double);

    double userr3() const;
    Acad::ErrorStatus setUserr3(double);

    double userr4() const;
    Acad::ErrorStatus setUserr4(double);

    double userr5() const;
    Acad::ErrorStatus setUserr5(double);

    double chamfera() const;
    Acad::ErrorStatus setChamfera(double);

    double chamferb() const;
    Acad::ErrorStatus setChamferb(double);

    double chamferc() const;
    Acad::ErrorStatus setChamferc(double);

    double chamferd() const;
    Acad::ErrorStatus setChamferd(double);

    double facetres() const;
    Acad::ErrorStatus setFacetres(double);

    Acad::ErrorStatus getMenu(char* &) const;

    AcDbDate tdcreate() const;

    AcDbDate tdupdate() const;

    AcDbDate tdindwg() const;

    AcDbDate tdusrtimer() const;

    AcCmColor cecolor() const;
    Acad::ErrorStatus setCecolor(const AcCmColor&);

    AcDbHandle handseed() const;
#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    Acad::ErrorStatus setHandseed(const AcDbHandle&);
#endif

    AcDbObjectId clayer() const;
    Acad::ErrorStatus setClayer(AcDbObjectId);

    AcDbObjectId textstyle() const;
    Acad::ErrorStatus setTextstyle(AcDbObjectId);

    AcDbObjectId celtype() const;
    Acad::ErrorStatus setCeltype(AcDbObjectId);

    AcDbObjectId dimstyle() const;
    Acad::ErrorStatus setDimstyle(AcDbObjectId);

    void getDimstyleData(AcDbDimStyleTableRecord*&) const;
    Acad::ErrorStatus setDimstyleData(AcDbDimStyleTableRecord*);
    Acad::ErrorStatus setDimstyleData(AcDbObjectId);

    AcDbObjectId cmlstyleID() const;
    Acad::ErrorStatus setCmlstyleID(AcDbObjectId);

    Adesk::Int16 cmljust() const;
    Acad::ErrorStatus setCmljust(Adesk::Int16);

    double cmlscale() const;
    Acad::ErrorStatus setCmlscale(double);

    double celtscale() const;
    Acad::ErrorStatus setCeltscale(double);

    // Paper space variable access

    AcGePoint3d pinsbase() const;
    Acad::ErrorStatus setPinsbase(const AcGePoint3d&);

    AcGePoint3d pextmin() const;

    AcGePoint3d pextmax() const;

    Acad::ErrorStatus setPextmin(const AcGePoint3d&);
    Acad::ErrorStatus setPextmax(const AcGePoint3d&);

    AcGePoint2d plimmin() const;
    Acad::ErrorStatus setPlimmin(const AcGePoint2d&);

    AcGePoint2d plimmax() const;
    Acad::ErrorStatus setPlimmax(const AcGePoint2d&);

    double pelevation() const;
    Acad::ErrorStatus setPelevation(double);

    AcGePoint3d pucsorg() const;

    AcGeVector3d pucsxdir() const;

    AcGeVector3d pucsydir() const;

    AcDbObjectId pucsname() const;


    // Model space variable access

    AcGePoint3d insbase() const;
    Acad::ErrorStatus setInsbase(const AcGePoint3d&);

    AcGePoint3d extmin() const;

    AcGePoint3d extmax() const;

    Acad::ErrorStatus updateExt();

    Acad::ErrorStatus setExtmin(const AcGePoint3d&);
    Acad::ErrorStatus setExtmax(const AcGePoint3d&);

    AcGePoint2d limmin() const;
    Acad::ErrorStatus setLimmin(const AcGePoint2d&);

    AcGePoint2d limmax() const;
    Acad::ErrorStatus setLimmax(const AcGePoint2d&);

    double elevation() const;
    Acad::ErrorStatus setElevation(double);

    AcGePoint3d ucsorg() const;

    AcGeVector3d ucsxdir() const;

    AcGeVector3d ucsydir() const;

    AcDbObjectId ucsname() const;


    // Dimvar access
    //
    Adesk::Boolean dimtol() const;
    Acad::ErrorStatus setDimtol(Adesk::Boolean);

    Adesk::Boolean dimlim() const;
    Acad::ErrorStatus setDimlim(Adesk::Boolean);

    Adesk::Boolean dimtih() const;
    Acad::ErrorStatus setDimtih(Adesk::Boolean);

    Adesk::Boolean dimtoh() const;
    Acad::ErrorStatus setDimtoh(Adesk::Boolean);

    Adesk::Boolean dimse1() const;
    Acad::ErrorStatus setDimse1(Adesk::Boolean);

    Adesk::Boolean dimse2() const;
    Acad::ErrorStatus setDimse2(Adesk::Boolean);

    Adesk::Boolean dimupt() const;
    Acad::ErrorStatus setDimupt(int);

    int dimtad() const;
    Acad::ErrorStatus setDimtad(int);

    Adesk::Boolean dimalt() const;
    Acad::ErrorStatus setDimalt(Adesk::Boolean);

    Adesk::Boolean dimtofl() const;
    Acad::ErrorStatus setDimtofl(Adesk::Boolean);

    Adesk::Boolean dimsah() const;
    Acad::ErrorStatus setDimsah(Adesk::Boolean);

    Adesk::Boolean dimtix() const;
    Acad::ErrorStatus setDimtix(Adesk::Boolean);

    Adesk::Boolean dimsoxd() const;
    Acad::ErrorStatus setDimsoxd(Adesk::Boolean);

    Adesk::Boolean dimsd1() const;
    Acad::ErrorStatus setDimsd1(Adesk::Boolean);

    Adesk::Boolean dimsd2() const;
    Acad::ErrorStatus setDimsd2(Adesk::Boolean);

    Adesk::Int8 dimtolj() const;
    Acad::ErrorStatus setDimtolj(Adesk::Int8);

    int dimaltd() const;
    Acad::ErrorStatus setDimaltd(int);

    int dimzin() const;
    Acad::ErrorStatus setDimzin(int);

    int dimfit() const;
    Acad::ErrorStatus setDimfit(int);

    int dimjust() const;
    Acad::ErrorStatus setDimjust(int);

    int dimtzin() const;
    Acad::ErrorStatus setDimtzin(int);

    int dimaltz() const;
    Acad::ErrorStatus setDimaltz(int);

    int dimalttz() const;
    Acad::ErrorStatus setDimalttz(int);

    int dimunit() const;
    Acad::ErrorStatus setDimunit(int);

    int dimaunit() const;
    Acad::ErrorStatus setDimaunit(int);

    int dimdec() const;
    Acad::ErrorStatus setDimdec(int);

    int dimadec() const;
    Acad::ErrorStatus setDimadec(int);

    int dimtdec() const;
    Acad::ErrorStatus setDimtdec(int);

    int dimaltu() const;
    Acad::ErrorStatus setDimaltu(int);

    int dimalttd() const;
    Acad::ErrorStatus setDimalttd(int);

    AcDbObjectId dimtxsty() const;
    Acad::ErrorStatus setDimtxsty(AcDbObjectId);

    double dimscale() const;
    Acad::ErrorStatus setDimscale(double);

    double dimasz() const;
    Acad::ErrorStatus setDimasz(double);

    double dimexo() const;
    Acad::ErrorStatus setDimexo(double);

    double dimdli() const;
    Acad::ErrorStatus setDimdli(double);

    double dimexe() const;
    Acad::ErrorStatus setDimexe(double);

    double dimrnd() const;
    Acad::ErrorStatus setDimrnd(double);

    double dimdle() const;
    Acad::ErrorStatus setDimdle(double);

    double dimtp() const;
    Acad::ErrorStatus setDimtp(double);

    double dimtm() const;
    Acad::ErrorStatus setDimtm(double);

    double dimtxt() const;
    Acad::ErrorStatus setDimtxt(double);

    double dimcen() const;
    Acad::ErrorStatus setDimcen(double);

    double dimtsz() const;
    Acad::ErrorStatus setDimtsz(double);

    double dimaltf() const;
    Acad::ErrorStatus setDimaltf(double);

    double dimlfac() const;
    Acad::ErrorStatus setDimlfac(double);

    double dimtvp() const;
    Acad::ErrorStatus setDimtvp(double);

    double dimtfac() const;
    Acad::ErrorStatus setDimtfac(double);

    double dimgap() const;
    Acad::ErrorStatus setDimgap(double);

    Acad::ErrorStatus getDimpost(char* & pOutput) const;
    Acad::ErrorStatus setDimpost(const char*);

    Acad::ErrorStatus getDimapost(char* & pOutput) const;
    Acad::ErrorStatus setDimapost(const char*);

    Acad::ErrorStatus getDimblk(char* & pOutput) const;
    Acad::ErrorStatus setDimblk(const char*);

    Acad::ErrorStatus getDimblk1(char* & pOutput) const;
    Acad::ErrorStatus setDimblk1(const char*);

    Acad::ErrorStatus getDimblk2(char* & pOutput) const;
    Acad::ErrorStatus setDimblk2(const char*);

    AcCmColor dimclrd() const;
    Acad::ErrorStatus setDimclrd(const AcCmColor&);

    AcCmColor dimclre() const;
    Acad::ErrorStatus setDimclre(const AcCmColor&);

    AcCmColor dimclrt() const;
    Acad::ErrorStatus setDimclrt(const AcCmColor&);

    AcDbDatabase(Adesk::Boolean buildDefaultDrawing = Adesk::kTrue);

    Acad::ErrorStatus loadLineTypeFile(const char *ltn, const char *filename);

    virtual ~AcDbDatabase();

private:
    friend class AcDbSystemInternals;
    AcDbImpDatabase* mpImpDb;
};

class AcDbObjectIterator: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectIterator);
    virtual ~AcDbObjectIterator();

    Adesk::Boolean done() const;
    void           step(Adesk::Boolean backwards = Adesk::kFalse,
			Adesk::Boolean skipDeleted = Adesk::kTrue);
    void           setPosition(AcDbEntity*  pEnt);
    void           setPosition(AcDbObjectId  pObj);
    void           start(Adesk::Boolean atEnd = Adesk::kFalse);
    AcDbEntity*    entity();
    AcDbObjectId   objectId();

private:
    friend class AcDbSystemInternals;
    AcDbObjectIterator();
    AcDbImpObjectIterator* mpImpIterator;
};

class AcDbObject: public AcRxObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbObject);

    virtual ~AcDbObject();

#ifdef new
#define SAVEDEF_NEW new
#define SAVEDEF_DELETE delete
#undef new
#undef delete
#endif

    void* operator new(size_t);
#ifdef LEAKCHECK
    void* operator new(size_t DBG_FORMAL);
#endif
    void  operator delete(void*);

#ifdef SAVEDEF_NEW
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif

    // Associated Objects
    //
    AcDbObjectId      objectId() const;
    AcDbObjectId      ownerId() const;
    virtual Acad::ErrorStatus setOwnerId(AcDbObjectId);
    void              getAcDbHandle(AcDbHandle&) const;
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
    virtual Acad::ErrorStatus subOpen(AcDb::OpenMode);

    Acad::ErrorStatus cancel();
    virtual Acad::ErrorStatus subCancel();

    Acad::ErrorStatus close();
    Acad::ErrorStatus closeAndPage(Adesk::Boolean onlyWhenClean = Adesk::kTrue);
    virtual Acad::ErrorStatus subClose();

    Acad::ErrorStatus erase(Adesk::Boolean erasing = Adesk::kTrue);
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing);

    Acad::ErrorStatus handOverTo(AcDbObject* newObject,
				 Adesk::Boolean keepXData = Adesk::kTrue,
				 Adesk::Boolean keepExtDict = Adesk::kTrue);
    virtual Acad::ErrorStatus subHandOverTo(AcDbObject* newObject);

    Acad::ErrorStatus swapIdWith(AcDbObjectId otherId, 
                 Adesk::Boolean swapXdata = Adesk::kFalse,
				 Adesk::Boolean swapExtDict = Adesk::kFalse);
    virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId,
                 Adesk::Boolean swapXdata = Adesk::kFalse,
				 Adesk::Boolean swapExtDict = Adesk::kFalse);

    // Audit
    //
    virtual Acad::ErrorStatus audit(AcDbAuditInfo*);

    // Filing
    //
    Acad::ErrorStatus         dwgIn       (AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* filer);
    Acad::ErrorStatus         dwgOut      (AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    Acad::ErrorStatus         dxfIn       (AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* filer);
    Acad::ErrorStatus         dxfOut      (AcDbDxfFiler* filer,
				           Adesk::Boolean allXdFlag,
				           Adesk::uchar* regAppTable) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    // XData
    //
    virtual resbuf*           xData   (const char* regappName = NULL) const;
    virtual Acad::ErrorStatus setXData(const resbuf* xdata);

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
    void assertWriteEnabled(Adesk::Boolean autoUndo =
			    Adesk::kTrue,
			    Adesk::Boolean recordModified =
			    Adesk::kTrue);
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
    AcDbVoidPtrArray*         reactors();

    virtual void              recvPropagateModify(const AcDbObject* subObj);
    virtual void              xmitPropagateModify() const;

    virtual Acad::ErrorStatus deepClone(AcDbObject* pOwnerObject,
					AcDbObject*& pClonedObject,
					AcDbIdMapping& idMap,
					Adesk::Boolean isPrimary
					= Adesk::kTrue) const;
 
    virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject,
					  AcDbObject*& pClonedObject,
					  AcDbIdMapping& idMap,
					  Adesk::Boolean isPrimary
					  = Adesk::kTrue) const;

    void              setAcDbObjectIdsInFlux();
    Adesk::Boolean    isAcDbObjectIdsInFlux() const;

    // Notification for persistent reactors.
    //
    virtual void cancelled       (const AcDbObject* dbObj);
    virtual void copied          (const AcDbObject* dbObj,
                                  const AcDbObject* newObj);
    virtual void erased          (const AcDbObject* dbObj,
				  Adesk::Boolean pErasing = Adesk::kTrue);
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
    virtual AcRxObject* clone() const;
    virtual void        copyFrom(const AcRxObject* pSrc);

    // COM
    //
    virtual HRESULT __stdcall QueryInterface ( REFIID riid, void ** ppvObject );
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();

    // saveasr13.
    //
    virtual Acad::ErrorStatus   decomposeForSave(
				AcDb::AcDbDwgVersion ver,
		                AcDbObject*& replaceObj,
				AcDbObjectId& replaceId,
			        Adesk::Boolean& exchangeXData);

protected:
    AcDbObject();
private:
    friend class AcDbSystemInternals;
    AcDbImpObject*            mpImpObject;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbObject);

class AcDbXObject: public AcRxObject
//
// AcRxObject which recognizes filer protocol,
// and has a ACRX_DXF_CLASS_OBJ_BODY
//
{
public:
    ACRX_DECLARE_MEMBERS(AcDbXObject);

    virtual Acad::ErrorStatus audit(AcDbAuditInfo*);

    Acad::ErrorStatus dwgIn(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* filer) const;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    protected:
    AcDbXObject();
};

class AcCmComplexColor: public  AcDbXObject
{
public:
    ACRX_DECLARE_MEMBERS(AcCmComplexColor); 

    virtual AcCmComplexColor* incReference();
    virtual void              decReference();

    virtual Acad::ErrorStatus getDescription(char *&) const;
    virtual Acad::ErrorStatus getExplanation(char *&) const;


    virtual Adesk::UInt16     colorIndex() const;
    virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16);

    // --- AcRxObject protocol
    //
    void copyFrom(const AcRxObject*);

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    virtual Acad::ErrorStatus audit(AcDbAuditInfo*);

private:
    Adesk::UInt16 refCount;
    Adesk::UInt16 mIndex;
};

class AcCmColor
{
public:
    AcCmColor();
    AcCmColor(const AcCmColor&);
    AcCmColor& operator=(const AcCmColor& inputColor);
    ~AcCmColor();
    
    Acad::ErrorStatus getDescription(char *&) const;
    Acad::ErrorStatus getExplanation(char *&) const;


    Adesk::UInt16     colorIndex() const;
    Acad::ErrorStatus setColorIndex(Adesk::UInt16);

    Acad::ErrorStatus dwgIn(AcDbDwgFiler* pInputFiler);
    Acad::ErrorStatus dwgOut(AcDbDwgFiler *pOutputFiler) const;

    Acad::ErrorStatus dxfIn(AcDbDxfFiler* filer);
    Acad::ErrorStatus dxfOut(AcDbDxfFiler* filer) const;

    virtual Acad::ErrorStatus audit(AcDbAuditInfo*);

    static const Adesk::UInt16 MaxColorIndex; 

protected:
    AcCmComplexColor* complexColor() const;
    void setComplexColor(AcCmComplexColor *);
private:
    static const Adesk::UInt16 ComplexColorFlag; 
    Adesk::Boolean isComplex() const;
    AcCmComplexColor *mpValue;
};

class AcDbEntity: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbEntity);

    virtual ~AcDbEntity();

    AcDbObjectId                blockId() const;

    AcCmColor                   color() const;
    virtual Acad::ErrorStatus   setColor(const AcCmColor &color,
                                  Adesk::Boolean doSubents = Adesk::kTrue);
    Adesk::UInt16               colorIndex() const;
    virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    char*                       layer() const;
    AcDbObjectId                layerId() const;
    virtual Acad::ErrorStatus   setLayer(const char* newVal,
                                  Adesk::Boolean doSubents = Adesk::kTrue);
    virtual Acad::ErrorStatus   setLayer(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    char*                       linetype() const;
    AcDbObjectId                linetypeId() const;
    virtual Acad::ErrorStatus   setLinetype(const char* newVal,
                                  Adesk::Boolean doSubents = Adesk::kTrue);
    virtual Acad::ErrorStatus   setLinetype(AcDbObjectId newVal,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    double                      linetypeScale() const;
    virtual Acad::ErrorStatus   setLinetypeScale(double newval,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    AcDb::Visibility            visibility() const;
    virtual Acad::ErrorStatus   setVisibility(AcDb::Visibility newVal,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    Acad::ErrorStatus           setPropertiesFrom(const AcDbEntity* entity,
                                  Adesk::Boolean doSubents = Adesk::kTrue);

    virtual void                getEcs(AcGeMatrix3d& retVal) const;

    virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;

    // Subentity acquisition.
    //
    virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(
                                  AcDb::SubentType type,
	                          int                    gsMark, 
                                  const AcGePoint3d&     pickPoint,
	                          const AcGeMatrix3d&    viewXform, 
                                  int&                   numPaths,
	                          AcDbFullSubentPath*&   subentPaths, 
                                  int                    numInserts = 0,
	                          AcDbObjectId*          entAndInsertStack
                                                           = NULL) const;

    virtual  Acad::ErrorStatus getGsMarkersAtSubentPath(
	                       const AcDbFullSubentPath& subPath, 
                               AcDbIntArray& gsMarkers) const;

    virtual Acad::ErrorStatus highlight(const AcDbFullSubentPath& subId 
				        = kNullSubent) const;
    virtual Acad::ErrorStatus unhighlight(const AcDbFullSubentPath& subId 
				        = kNullSubent) const;
    virtual AcDbEntity*       subentPtr(const AcDbFullSubentPath& id) const;
 
    virtual Acad::ErrorStatus   getOsnapPoints(
				 AcDb::OsnapMode     osnapMode,
				 int                 gsSelectionMark,
				 const AcGePoint3d&  pickPoint,
				 const AcGePoint3d&  lastPoint,
				 const AcGeMatrix3d& viewXform,
				 AcGePoint3dArray&   snapPoints,
				 AcDbIntArray&       geomIds) const;

    virtual Acad::ErrorStatus   getGripPoints(
                                   AcGePoint3dArray&  gripPoints,
				   AcDbIntArray&  osnapModes,
				   AcDbIntArray&  geomIds) const;

    virtual  Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
	const AcGeVector3d& offset);

    virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray&) const;
    virtual Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices,
                        	const AcGeVector3d& offset);

    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
	                            AcDb::Intersect intType, 
                                    AcGePoint3dArray& points,
	                            int thisGsMarker = 0, 
                                    int otherGsMarker = 0) const;
 
    virtual  Acad::ErrorStatus intersectWith(const AcDbEntity* ent,
	                                     AcDb::Intersect intType, 
                                             const AcGePlane& projPlane,
	                                     AcGePoint3dArray& points, 
                                             int thisGsMarker = 0,
	                                     int otherGsMarker = 0) const;
 
    Acad::ErrorStatus          boundingBoxIntersectWith(
				             const AcDbEntity*   ent,
				             AcDb::Intersect     intType,
				             AcGePoint3dArray&   points,
				             int                 thisGsMarker,
				             int                 otherGsMarker) const;

    Acad::ErrorStatus          boundingBoxIntersectWith(
			           	     const AcDbEntity*   ent,
				             AcDb::Intersect     intType,
				             const AcGePlane&      projPlane,
				             AcGePoint3dArray&   points,
				             int                 thisGsMarker,
				             int                 otherGsMarker) const;

    virtual void                list() const;

    virtual Acad::ErrorStatus   transformBy(const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus   getTransformedCopy(const AcGeMatrix3d& xform,
						   AcDbEntity*& ent) const;
    virtual Acad::ErrorStatus   explode(AcDbVoidPtrArray& entitySet) const;

    void                        recordGraphicsModified(Adesk::Boolean autoUndo
						       = Adesk::kTrue);

    Acad::ErrorStatus           draw();
    virtual Adesk::Boolean      worldDraw(AcGiWorldDraw*        mode);
    virtual void                viewportDraw(AcGiViewportDraw*  mode);
    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    void                        setDatabaseDefaults();
    void                        setDatabaseDefaults(AcDbDatabase* pDb);
    virtual void                subSetDatabaseDefaults(AcDbDatabase* pDb);

    virtual Acad::ErrorStatus   applyPartialUndo(AcDbDwgFiler* undoFiler,
						 AcRxClass*    classObj);

    virtual Acad::ErrorStatus   audit(AcDbAuditInfo*);

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

protected:
    // Makes AcDbEntity an abstract class.
    AcDbEntity();
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbEntity);

class AcDbObjectReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectReactor);

    virtual void cancelled      (const AcDbObject* dbObj);
    virtual void copied         (const AcDbObject* dbObj,
                                 const AcDbObject* newObj);
    virtual void erased         (const AcDbObject* dbObj,
                                 Adesk::Boolean pErasing = Adesk::kTrue);
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

class AcDbEntityReactor: public AcDbObjectReactor
{
public:
    ACRX_DECLARE_MEMBERS(AcDbEntityReactor);
    virtual void modifiedGraphics(const AcDbEntity* dbObj);
protected:
    AcDbEntityReactor();
};

class AcDbDatabaseReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabaseReactor);

    virtual void objectAppended       (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectUnAppended     (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectReAppended     (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectOpenedForModify(const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectModified       (const AcDbDatabase* dwg, const AcDbObject* dbObj);
    virtual void objectErased         (const AcDbDatabase* dwg, const AcDbObject* dbObj,
			               Adesk::Boolean pErased = Adesk::kTrue);
};

class AcDbExtents
{
public:
    AcDbExtents();                                      
    AcDbExtents(const AcDbExtents& );           
    AcDbExtents(const AcGePoint3d& min, const AcGePoint3d& max);  
 
    AcGePoint3d       minPoint() const { return mMinPoint; }
    AcGePoint3d       maxPoint() const { return mMaxPoint; }
    Acad::ErrorStatus set(const AcGePoint3d& min, const AcGePoint3d& max);

    void              addPoint (const AcGePoint3d& );
    void              addExt   (const AcDbExtents& src);
    Acad::ErrorStatus addBlockExt(AcDbBlockTableRecord* );

    void expandBy(const AcGeVector3d& );
    void transformBy(const AcGeMatrix3d& );

private:
    AcGePoint3d    mMinPoint;
    AcGePoint3d    mMaxPoint;
};

#endif
