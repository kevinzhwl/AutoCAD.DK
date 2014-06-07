#ifndef _ASECLASS_H
#define _ASECLASS_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc. 
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
//    Name: aseclass.h
//
//    Description:
//            This file describes the ASE Program Interface
//            classes for C++ AutoCAD applications.


/***************************************************************************/
/* INCLUDES */
/***************************************************************************/
#include <asiappl.h>
#include <aseconst.h>
#include <dbmain.h>
#include "adsdef.h"

/***************************************************************************/
/* DEFINES */
/***************************************************************************/
#define CASEAPPL(x)       ((CAseAppl*)x)
#define CASELINKPATH(x)   ((CAseLinkPath*)x)
#define CASELINK(x)       ((CAseLink*)x)
#define CASELINKSEL(x)    ((CAseLinkSel*)x)

// Can be used to throw ASI exception with the 
// diagnostic parameters, containing in the specified 
// CAseApiObj-derived object
#define ASE_THROW(x)  {((CAseApiObj*)x)->appThrow() ;}
#define WORKINGDWG()  NULL


/***************************************************************************/
/* TYPEDEFS */
/***************************************************************************/

/***************************************************************************/
/* CLASS DESCRIPTION */
/***************************************************************************/


#pragma pack (push, 8)
#if defined(__cplusplus)

class CAseApiErr ;
class CAseApiObj ;
  class CAseAppl ;
  class CAseLinkPath ;
  class CAseLinkSel ;
  class CAseReactor ;

class CAseApiObj 
//
//  This class defines the properties of the
//  all ASE classes and has to be inherited by the all
//  other concrete ASE API classes.
//
{
  public:
                         CAseApiObj(CAseApiObj *pObj) ;
                         CAseApiObj(CAseApiObj &Obj) ;
  virtual                ~CAseApiObj() ;
  virtual EAsiBoolean    init() ;
  virtual EAseApiClassId isA() const = 0 ;
  virtual CAseApiObj    *clone() const = 0 ;
  virtual EAsiBoolean    copyFrom(const CAseApiObj *pObj) ;
  virtual CAseApiObj&    operator=(const CAseApiObj &Obj) ;
  virtual int            operator==(const CAseApiObj *pObj) const = 0 ;
  virtual int            operator==(const CAseApiObj &Obj) const = 0 ;
  virtual EAsiBoolean    isInit() const ;
  const char            *version() const ;
  const CAsiException   *errGet() const ;
  int                    errQty() const ;
  EAseErrDsc             errDsc(int ErrNum) const ;
  int                    errCode(int ErrNum) const ;
  EAsiBoolean            errMsg(int ErrNum,
                                char *pBuf,
                                int BufLen) const;
  EAsiBoolean            errClear() ;
  void                   appThrow() const ;
  const char            *errDiagParNameCode(int ParNum,
                                            int *pParCode,
                                            int *pIsStr) const ;
  EAsiBoolean            errDiagPar(int ErrNum, 
                                    int ParCode,
                                    int *pIntValue) const ;
  EAsiBoolean            errDiagPar(int ErrNum, 
                                    int ParCode,
                                    char *pStrValue,
                                    int BufLen) const ;

  // Initialize the diagnostics area by ASI errors.
  EAsiBoolean            errInitAsi(CAsiException *pErr) ;
  EAsiBoolean            errInitAsi(CAsiSQLObject *pSQLObj) ;
  EAsiBoolean            errInitAsi(CAsiSQLObject &sqlObj) ;

  friend class CAseApiErr ;
  friend class CAseAppl ;
  protected:
  struct resbuf         *getLast(const struct resbuf *bufptr) const ;
  struct resbuf         *allocAttr(EAseLinkAttr attr, const char *pStr=NULL) const ;
  struct resbuf         *copyBuf(const struct resbuf *bufptr, 
                                 const struct resbuf *pBorder=NULL) const ;
  struct resbuf         *nextAttr(const struct resbuf *bufptr) const ;
  struct resbuf         *getAttrType(const struct resbuf *bufptr,
                                     EAseLinkAttr lattr) const ;
  const struct resbuf   *getAttrPtr(const struct resbuf *bufptr,
                                    EAseLinkAttr lattr) const ;
  EAsiBoolean            setAttrPtr(struct resbuf *bufptr,
                                    EAseLinkAttr LinkAttr,
                                    struct resbuf *pAttrValue) const ;
  struct resbuf         *delAttrPtr(struct resbuf *bufptr,
                                    struct resbuf *pAttr) const ;
  EAsiBoolean            parseLisp(struct resbuf *bufptr) ;
  CAseAppl              *getAppl() const ;
  void                   freeStr(struct resbuf *pBuf) const ;
  EAsiBoolean            isDiffChar() const ;

  void                  *mpErr ;       // The error descriptor pointer
} ;

class CAseAppl : public CAseApiObj 
//
//            This class is responsible for the interface
//            with the ASE main module.
//
{
  public:
                         CAseAppl(CAseApiObj *pObj=NULL) ;
                         CAseAppl(CAseApiObj &Obj) ;
  virtual                ~CAseAppl() ;
  virtual EAsiBoolean    init() ;
  virtual EAseApiClassId isA() const ;
  virtual CAseApiObj    *clone() const ;
  virtual EAsiBoolean    copyFrom(const CAseApiObj *pObj) ;
  virtual CAseApiObj&    operator=(const CAseApiObj &Obj) ;
  virtual int            operator==(const CAseApiObj *pObj) const ;
  virtual int            operator==(const CAseApiObj &Obj) const ;
  virtual EAsiBoolean    isInit() const ;
  void                   term() ;

  //get the AutoCAD data source location
  //this location remains unchanged throughout
  //one AutoCAD session
  LPCSTR                 getAcadDsPath();

    // Maps ASE global diagnostics area into the target CAseAppl object
  EAsiBoolean            getAseErr() ;
    // Clears ASE global diagnostics area
  EAsiBoolean            clearAseErr();

    // This function returns the ASI session
    // allocated in the current application
  CAsiSession*           connectAse(CAsiAppl *pAppl,
                                    const char *pEnvName,
                                    const char *pUserName=NULL,
                                    const char *pPassWord=NULL,
									EAsiBoolean fPrompt = kAsiFalse) ;

    // Checks whether the ASE index exists and it is up to date for
    // the drawing database specified
  EAsiBoolean            isIndexExist(AcDbDatabase *pDwg=NULL);                                  
  EAsiBoolean            isIndexUpToDate(AcDbDatabase *pDwg=WORKINGDWG());
    // Creates (writes) the ASE index in the drawing database specified
  EAsiBoolean            createIndex(AcDbDatabase *pDwg=WORKINGDWG());
    // Erases the ASE index from the drawing database specified
  EAsiBoolean            removeIndex(AcDbDatabase *pDwg=WORKINGDWG());

  // Overwrites global AutoCAD "save index" variable
  // mode argument controls ASE index save mode:
  //		0 - use AutoCAD setting for ASE index 
  //	1 - always save ASE index regardless AutoCAd setting
  //	2 - do not save index. Ignore AutoCAD setting
  //	3 - return current index save setting
  // Function returns ASE "save index" setting before calling this 
  // function.
  int					 setIndexSaveMode (int mode);
  
  EAsiBoolean            openDwg(AcDbDatabase *pDwg=WORKINGDWG()) ;
  EAsiBoolean            openLazyDwg(AcDbDatabase *pDwg=WORKINGDWG()) ;
  EAsiBoolean            isDwgOpened(AcDbDatabase *pDwg=WORKINGDWG()) ;
  EAsiBoolean            isDwgLazyOpened(AcDbDatabase *pDwg=WORKINGDWG()) ;
  EAsiBoolean            closeDwg(AcDbDatabase *pDwg=WORKINGDWG()) ;
    // Swaps the references to linked entities
    // Should be followed right after AcDbObject::swapIdWith() call
  EAsiBoolean            swapEntIds(AcDbObjectId objectId, 
                                    AcDbObjectId otherId,
                                    AcDbDatabase *pDwg=WORKINGDWG());
    // Swaps the references to BTR
    // Should be followed right after AcDbObject::swapIdWith() call
    // for BTR
  EAsiBoolean            swapBTRIds(AcDbObjectId blockId, 
                                    AcDbObjectId otherId,
                                    AcDbDatabase *pDwg=WORKINGDWG());
    // Makes ASE store unread ASE link information from the entity,
    // for lazy opened source drawing
  EAsiBoolean            loadLinks(AcDbEntity *pObj);
  EAsiBoolean            loadLinks(AcDbObjectId objId);
  EAsiBoolean            translateDataSource(DatasourceTranslationCode xCode,
                                             unsigned int buflen,
                                             const char * szFromEnv,
                                             const char * szFromCat, 
                                             const char * szFromSchema,
                                             const char * szFromTable,
                                             const char * szFromLpn,
                                             char * szToEnv, 
                                             char * szToCat, 
                                             char * szToSchema,
                                             char * szToTable,
                                             char * szToLpn);

  // ASE Transactions - controls how ASE objects are stored into ASE link memory
  //   UserManaged Transactions require that begin/commit/abort are used
  //   Automatic Transactions are the default and are provided for backward compatibility
  //   for every ASE object created/modified/deleted, a transaction is automatically 
  //   created around each ASE operation.
  //   UserManaged Transactions provide better performance since the user can control
  //   where to commit the ASE objects into ASE memory. 
  EAsiBoolean           beginAseTransaction();
  EAsiBoolean           commitAseTransaction();
  EAsiBoolean           abortAseTransaction();
 
  typedef enum {
      kTransAutomatic = 0,      // automatic commit ASE objects per ASE operation [DEFAULT]
      kTransUserManaged,        // user must specify begin/commit/abort around ASE operations
  } ETransactionMode;

  void                  setAseTransactionMode( ETransactionMode eMode );
  ETransactionMode      getAseTransactionMode();

  protected:
  
    // ASE call
  struct resbuf *        aseiCallAse(int funCode,
                                     struct resbuf* pParms,
                                     void *pErr,
                                     void *pAcDbDatabase=NULL,
                                     EAsiBoolean needFullOpen=kAsiFalse)  ;

    // RX-RX communication
  struct resbuf *        ase_invoke(int funCode,
                                    struct resbuf* pParms,
                                    void *pErr,
                                    void *pAse)  ;
  struct resbuf *        ase_fromAse(struct resbuf *pBuf) ;
  EAsiBoolean            ase_toAse(struct resbuf *pBuf) ;
  EAsiBoolean            addObj(const CAseApiObj *pObj) ;
  EAsiBoolean            remObj(const CAseApiObj *pObj) ;

  EAsiBoolean            mapErrFromAse(void *pAse, void *pErr);
  
  friend class CAseApiObj ;
  friend class CAseLinkPath ;
  friend class CAseLink ;
  friend class CAseLinkSel ;
  friend class CAseApiErr ;
  char                  *mpVersion ;    // The ASE version
  void                  *mpRes ;        // XMF file reference
  void                  *mpObjs ;       // Attached objects list
  EAsiBoolean            mIsDiffChar ;  // ASE & ASE appl have the
                                        // different character sets (kAsiTrue)
  char                  *mpDefChar ;    // ASE default character set
                                        // (NULL if the same as ASE has)
  ETransactionMode      meTransMode;    // Automatically committing ASE transactions
                                        // on Link/Label inserts, deletes, etc.

} ;


class CAseLinkPath : public CAseApiObj
//
//            This class is responsible for the manipulations
//            with the Link Paths. The class can refer to the
//            one Link Path is its name is set or provide the
//            caller with the group manipulations with the
//            several Link Paths related with the Database
//            Object Path. The procesing functions execute
//            the actions over the single Link Path, if its
//            name is specified. Otherwise, some of the
//            functions execute the actions for all of Link
//            Paths, related with the Database Object for
//            specified path. If the Database Object Path is
//            empty or wasn't specified, some of the
//            functions execute the actions for all of Link
//            Paths in the current drawing.
//
{
  public:
                         CAseLinkPath(CAseApiObj *pObj) ;
                         CAseLinkPath(CAseApiObj &Obj) ;
  virtual                ~CAseLinkPath() ;
  virtual EAsiBoolean    init() ;
  virtual EAseApiClassId isA() const ;
  virtual CAseApiObj    *clone() const ;
  virtual EAsiBoolean    copyFrom(const CAseApiObj *pObj) ;
  virtual CAseApiObj&    operator=(const CAseApiObj &Obj) ;
  virtual int            operator==(const CAseApiObj *pObj) const ;
  virtual int            operator==(const CAseApiObj &Obj) const ;
  virtual EAsiBoolean    isInit() const ;

  EAsiBoolean            initPath(const char *pPath) ;
  EAsiBoolean            initName(const char *pName) ;
  EAsiBoolean            initCurrent() ;
  EAsiBoolean            reInit();
  EAsiBoolean            setName(const char *pName,
                                 EAseDoNameCode NameCode=kAseLpnCode) ;
  EAsiBoolean            getName(char *pBuf, int BufLen,
                                 EAseDoNameCode NameCode=kAseLpnCode) const ;
  int                    getNameSize(EAseDoNameCode NameCode=kAseLpnCode) const;
  int                    cmpName(const char *pName, 
                                 EAseDoNameCode NameCode=kAseLpnCode) const ;
  int                    cmpName(const CAseLinkPath *pLinkPath, 
                                 EAseDoNameCode NameCode=kAseLpnCode) const ;
  EAseDoNameCode         getPathCode() const;
  int                    getStatus() const;
  EAsiBoolean            isUpdatable() const ;
  EAsiBoolean            getKeyDsc(CAsiRow **pKeyDsc) const;
  EAsiBoolean            getKeyDsc(CAsiColumn **pKeyDsc[], int *pColQty) const;
  EAsiBoolean            create(const CAsiRow *pKeyDsc) ;
  EAsiBoolean            create(const CAsiRow &KeyDsc) ;
  EAsiBoolean            create(const CAsiColumn *pKeyDsc[], int ColQty) ;
  EAsiBoolean            erase() ;
  EAsiBoolean            rename(const char *pLinkPathName) ;
  EAsiBoolean            setCurrent() const ;
  struct resbuf         *getLinkNames() const ;
  struct resbuf         *getPaths(int Status) const ;
  
    // Manages the ASE connection
  EAsiBoolean            connectAse(const char *pUsername=NULL,
                                    const char *pPassword=NULL,
									EAsiBoolean fPrompt=kAsiFalse) ;

  EAsiBoolean            connectAseIniString (const char *pIniString);

  EAsiBoolean            disconnectAse();  
  
    // Check which ASI functionality is supported by the connected Env
  EAsiBoolean            checkOp(ulong status) const;  
  
    // Gets the description of the databas table
  EAsiBoolean            getTableDsc(CAsiRow **pColumns) const;  
  EAsiBoolean            getTableDsc(CAsiColumn **pKeyDsc[], 
                                     int *pColQty) const;
    // Creates the table
  EAsiBoolean            createTable(const CAsiRow *pCols);
  EAsiBoolean            createTable(const CAsiColumn *pCols[],
                                     int colNum);
    // Deletes the table from the database                           
  EAsiBoolean            dropTable();
  
    // Updates the values of the table row specified by the key values                     
  EAsiBoolean            updRow(const CAsiRow *pKey,
                                const CAsiRow *pValue,
                                long *pRowsQty=NULL) const;
  EAsiBoolean            updRow(const CAsiColumn *pKey[],
                                int numKeys,
                                const CAsiColumn *pValue[],
                                int numValues,
                                long *pRowsQty=NULL) const;
    // Deletes the row specified by the key values
  EAsiBoolean            delRow(const CAsiRow *pValue,
                                long *pRowsQty=NULL) const;
  EAsiBoolean            delRow(const CAsiColumn *pValue[],
                                int numKeys,
                                long *pRowsQty=NULL) const;
    // Adds the row to the table                      
  EAsiBoolean            addRow(const CAsiRow *pValue) const;
  EAsiBoolean            addRow(const CAsiColumn *pValue[],
                                int numValues) const;
  
    // Gets the values of the table row specified by the key
    // values into the specified buffer
  EAsiBoolean            getRow(const CAsiRow *pKeyValue,
                                CAsiRow *pRowBuffer) const;  
                                
    // This function has to be called to specify the drawing
    // database where the Link Paths are be processed in
  EAsiBoolean            setDwg(const AcDbDatabase *pDwg=WORKINGDWG()) ;
  
    // Gets the drawing database which the processed
    // Link Paths are situated in
  const AcDbDatabase*    getDwg() const ;

    // Allocates the cursor. ASE has to be already connected to
    // the correspondent Env.
    // pKeyDsc contains the input values description,
    // pRowBuffer describes the output values
    // This method puts the cursor number by the pCursorNum address.
  EAsiBoolean            allocCursor(const CAsiRow *pKeyDsc,
                                     const CAsiRow *pRow,
                                     long *pCursorNum) const;
    // Gets the values which were previously described in
    // allocCursor() call. Input key values
    // are specified by pKeyValue. The data types of 
    // pKeyValue and pRowBuffer should correspond to the
    // pKeyDsc and pRowBuffer arguments of allocCursor().
  EAsiBoolean            getCursorRow(long cursorNum,
                                      const CAsiRow *pKeyValue,
                                      CAsiRow *pRow) const;                           
    // Deallocates the cursor.                                  
  EAsiBoolean            delCursor(long cursorNum) const;

  protected:
  void                   *mpPath ;    // The internal data pointer
  void                   *mpDwg ;     // The drawing database pointer
} ;

class CAseLink : public CAseApiObj
//
//  This is the base class, defining the common
//  responsibility of the concrete links.
//
{
  public:
                         CAseLink(CAseApiObj *pObj) ;
                         CAseLink(CAseApiObj &Obj) ;
  virtual                ~CAseLink() ;
  virtual EAsiBoolean    init() ;
  EAsiBoolean            initType(EAseLinkType lType) ;
  EAsiBoolean            initId(LinkID linkId) ;
  EAsiBoolean            initEnt(const char *pName, 
                                 const CAsiRow *pKeyValue, 
                                 ads_name EntName) ;
  EAsiBoolean            initEnt(const char *pName, 
                                 const CAsiRow &KeyValue, 
                                 ads_name EntName) ;
  EAsiBoolean            initEnt(const char *pName, 
                                 const CAsiColumn *pKeyValue[],
                                 int ColQty,
                                 ads_name EntName) ;
  EAsiBoolean            initDA(const char *pName, 
                                const CAsiRow *pKeyValue,
                                const CAsiRow *pDACols,
                                const struct resbuf *pDAParms) ;
  EAsiBoolean            initDA(const char *pName, 
                                const CAsiRow &KeyValue,
                                const CAsiRow &DACols,
                                const struct resbuf *pDAParms) ;
  EAsiBoolean            initDA(const char *pName, 
                                const CAsiColumn *pKeyValue[],
                                int ColQty,
                                const CAsiColumn *pDACols[],
                                int DAColQty,
                                const struct resbuf *pDAParms) ;
  virtual EAseApiClassId isA() const ;
  virtual CAseApiObj    *clone() const ;
  virtual EAsiBoolean    copyFrom(const CAseApiObj *pObj) ;
  virtual CAseApiObj&    operator=(const CAseApiObj &Obj) ;
  virtual int            operator==(const CAseApiObj *pObj) const ;
  virtual int            operator==(const CAseApiObj &Obj) const ;
  virtual EAsiBoolean    isInit() const ;

  LinkID                 getId () const ;
  EAseLinkType           getType() const ;
  EAsiBoolean            getName(char *pBuf, int len) const;
  int                    getNameSize() const ;
  EAsiBoolean            setName(const char *pName) ;
  EAsiBoolean            getEntity(ads_name EntName) const ;
  EAsiBoolean            setEntity(ads_name EntName) ;
  EAsiBoolean            getKey(CAsiRow *pKeyValue) const ;
  EAsiBoolean            getKey(CAsiRow &KeyValue) const ;
  EAsiBoolean            getKey(CAsiColumn *pKeyValue[], int ColQty) const ;
  EAsiBoolean            setKey(const CAsiRow *pKeyValue) ;
  EAsiBoolean            setKey(const CAsiRow &KeyValue) ;
  EAsiBoolean            setKey(const CAsiColumn *pKeyValue[], int ColQty) ;
  EAsiBoolean            setDACols (const CAsiRow *pCols) ;
  EAsiBoolean            setDACols (const CAsiRow &Cols) ;
  EAsiBoolean            setDACols(CAsiColumn *pCols[], int ColQty) ;
  EAsiBoolean            getDACols (CAsiRow **pCols) const ;
  EAsiBoolean            getDACols(CAsiColumn **pCols[], int *pColQty) const ;
  EAsiBoolean            setDAParms(const struct resbuf *pParms) ;
  EAsiBoolean            setDAValues(const CAsiRow *pDAValues) ;
  EAsiBoolean            setDAValues(const CAsiRow &DAValues) ;
  EAsiBoolean            setDAValues(CAsiColumn *pCols[], int ColQty) ;
  EAsiBoolean            create () ;
  EAsiBoolean            remove () ;
  EAsiBoolean            update () ;
  EAsiBoolean            getXName(char *pBuf, int len) const ;
  EAsiBoolean            isUpdatable() const ;

    // This function has to be called to specify the drawing
    // database where the Link Paths are be processed in
  EAsiBoolean            setDwg(const AcDbDatabase *pDwg=WORKINGDWG()) ;
  
    // Gets the drawing database which the processed
    // Link Paths are situated in
  const AcDbDatabase*    getDwg() const ;
  
    // Un-documented
    // Gets/sets the link attribute values in the internal representation
  struct resbuf         *getAttr(EAseLinkAttr LinkAttr) const ;
  EAsiBoolean            setAttr(EAseLinkAttr LinkAttr,
                                 const struct resbuf *pAttrValue) ;
  private:
  struct resbuf      *mpBuf ;    // The link result buffer representation
  void               *mpDwg ;     // The drawing database pointer
} ;

class CAseLinkSel : public CAseApiObj 
//
//  This class describes the link selection.
//
{
  public:
                         CAseLinkSel(CAseApiObj *pObj) ;
                         CAseLinkSel(CAseApiObj &Obj) ;
  virtual                ~CAseLinkSel() ;
  virtual EAsiBoolean    init() ;
  EAsiBoolean            initType(EAseLinkType LinkType) ;
  EAsiBoolean            initSel(ads_name EntSelName,
                                 EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initEnt(ads_name EntName,
                                 EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initXName(const char *pXName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLp(const char *pName,
                                EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLp(const CAseLinkPath *pLinkPath,
                                EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLp(const CAseLinkPath &LinkPath,
                                EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpEnt(const char *pName,
                                   ads_name EntName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpEnt(const CAseLinkPath *pLinkPath,
                                   ads_name EntName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpEnt(const CAseLinkPath &LinkPath,
                                   ads_name EntName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const char *pName,
                                   const CAsiRow *pKeyValue,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const char *pName,
                                   const CAsiRow &KeyValue,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const CAseLinkPath *pLinkPath, 
                                   const CAsiRow *pKeyValue,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const CAseLinkPath &LinkPath, 
                                   const CAsiRow &KeyValue,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const char *pName,
                                   const CAsiColumn *pKeyValue[],
                                   int ColQty,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpKey(const CAseLinkPath *pLinkPath, 
                                   const CAsiColumn *pKeyValue[],
                                   int ColQty,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpCond(const char *pName,
                                    const char *pTextCondition,
                                    EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpCond(const CAseLinkPath *pLinkPath, 
                                    const char *pTextCondition,
                                    EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpCond(const CAseLinkPath &LinkPath, 
                                    const char *pTextCondition,
                                    EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpSel(const char *pName,
                                   ads_name EntSelName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpSel(const CAseLinkPath *pLinkPath, 
                                   ads_name EntSelName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initLpSel(const CAseLinkPath &LinkPath, 
                                   ads_name EntSelName,
                                   EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initPartialKey(const char *pName,
                                        const CAsiRow *pKeyValue,
                                        EAseLinkType LinkType=kAseUnknownLinkType) ;
  EAsiBoolean            initPartialKey(const CAseLinkPath *pLinkPath, 
                                        const CAsiRow *pKeyValue,
                                        EAseLinkType LinkType=kAseUnknownLinkType) ;

  virtual EAseApiClassId isA() const ;
  virtual CAseApiObj    *clone() const ;
  virtual EAsiBoolean    copyFrom(const CAseApiObj *pObj) ;
  virtual CAseApiObj&    operator=(const CAseApiObj &Obj) ;
  virtual int            operator==(const CAseApiObj *pObj) const ;
  virtual int            operator==(const CAseApiObj &Obj) const ;
  virtual EAsiBoolean    isInit() const ;
  EAsiBoolean            isUpdatable() const ;

  long                   getQty() const ;
  LinkID                 getId(long ItemNum) const ;
  EAsiBoolean            addId(LinkID linkId) ;
  EAsiBoolean            delId(long ItemNum) ;
  long                   membId(LinkID linkId) const ;
  
  EAsiBoolean            unite(const CAseLinkSel *pSel) ;
  EAsiBoolean            unite(const CAseLinkSel &Sel) ;
  EAsiBoolean            subtract(const CAseLinkSel *pSel) ;
  EAsiBoolean            subtract(const CAseLinkSel &Sel) ;
  EAsiBoolean            intersect(const CAseLinkSel *pSel) ;
  EAsiBoolean            intersect(const CAseLinkSel &Sel) ;

  EAsiBoolean            intersectType(EAseLinkType LinkType) ;
  EAsiBoolean            intersectEnt(ads_name EntName) ;
  EAsiBoolean            intersectSel(ads_name EntSelName) ;
  EAsiBoolean            intersectXName(const char *pXName) ;
  EAsiBoolean            intersectLp(const char *pName) ;
  EAsiBoolean            intersectLp(const CAseLinkPath *pLinkPath) ;
  EAsiBoolean            intersectLp(const CAseLinkPath &LinkPath) ;
  EAsiBoolean            intersectLpKey(const char *pName,
                                        const CAsiRow *pKeyValue) ;
  EAsiBoolean            intersectLpKey(const char *pName,
                                        const CAsiRow &KeyValue) ;
  EAsiBoolean            intersectLpKey(const CAseLinkPath *pLinkPath, 
                                        const CAsiRow *pKeyValue) ;
  EAsiBoolean            intersectLpKey(const CAseLinkPath &LinkPath, 
                                        const CAsiRow &KeyValue) ;
  EAsiBoolean            intersectLpKey(const char *pName,
                                        const CAsiColumn *pKeyValue[],
                                        int ColQty) ;
  EAsiBoolean            intersectLpKey(const CAseLinkPath *pLinkPath, 
                                        const CAsiColumn *pKeyValue[],
                                        int ColQty);
  EAsiBoolean            intersectLpCond(const char *pName,
                                         const char *pTextCondition) ;
  EAsiBoolean            intersectLpCond(const CAseLinkPath *pLinkPath, 
                                         const char *pTextCondition) ;
  EAsiBoolean            intersectLpCond(const CAseLinkPath &LinkPath, 
                                         const char *pTextCondition) ;

  EAsiBoolean            intersectPartialKey(const char *pName,
                                             const CAsiRow *pKeyValue) ;
  EAsiBoolean            intersectPartialKey(const CAseLinkPath *pLinkPath, 
                                             const CAsiRow *pKeyValue) ;
                                             
    // Gets the LPN of the link which identifier are specified
    // by means of ItemNum position in the link selection
  EAsiBoolean            getLinkName(long ItemNum,
                                     char *pNameBuf,
                                     int nameBufLen) const;
                                     
    // Get the key value of the link 
    // which identifier is specified by means of ItemNum position
    // in the link selection
  EAsiBoolean            getLinkKey(long ItemNum, CAsiRow *pKeyValue);
  
    // Get the name of the entity having the link
    // which identifier is specified by means of ItemNum position
    // in the link selection
  EAsiBoolean            getLinkEnt(long ItemNum, ads_name ename);                                   
  
    // Adds the identifiers of the drawing objects
    // having the links which identifiers are contained
    // in the link selection
  int                    getIdArray(AcDbObjectIdArray *pLinkedEntities) const;
  
    // Get the identifier of the entity having the link
    // which identifier is specified by means of ItemNum position
    // in the link selection
  EAsiBoolean            getLinkEnt(long ItemNum, AcDbObjectId *pId);                                   
    // This function has to be called to specify the drawing
    // database where the links are processed in
  EAsiBoolean            setDwg(const AcDbDatabase *pDwg=WORKINGDWG()) ;
  
    // Gets the drawing database which the processed
    // links are situated in
  const AcDbDatabase*    getDwg() const ;

  struct resbuf         *getXNames() const ;
  struct resbuf         *getLinkNames() const ;
  EAsiBoolean            getEntSel(ads_name EntSelName) const ;
  EAsiBoolean            erase() ;

  // Un-documented
  // Initializes the link selection by the 
  // internal link filter
  virtual EAsiBoolean    initFilter(struct resbuf *pLinkFilter,
                                    EAsiBoolean needFullOpen=kAsiFalse) ;
  // Filters the link selection by the 
  // internal link filter
  virtual EAsiBoolean    intersectFilter(const struct resbuf *pLinkFilter) ;

  protected:
  void                   freeSel() ;
  struct resbuf         *makeFilter(EAseLinkType LinkType,
                                    const char *pXName,
                                    ads_name EntName,
                                    ads_name EntSelName,
                                    const char *pName,
                                    const CAseLinkPath *pLinkPath,
                                    const CAsiRow *pKeyValue,
                                    const char *pTextCondition,
                                    const CAsiRow *pParKeyValue = NULL) ;

  LinkSelID              mSelId ;    // The link selection identifier
  void                   *mpDwg ;     // The drawing database pointer
} ;

#endif /* __cplusplus */
#pragma pack (pop)
#endif /*_ASECLASS_H*/

