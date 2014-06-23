#ifndef _ASE_H
#define _ASE_H
/*****************************************************************************
    Name: ase.h                                       

    Description:  
                  This file describes the ASE Program Interface
                  functions for AutoCAD C applications.

   Copyright (C) 1993 - 1997 by Autodesk, Inc.
 
   Permission to use, copy, modify, and distribute this software in 
   object code form for any purpose and without fee is hereby granted, 
   provided that the above copyright notice appears in all copies and 
   that both that copyright notice and the limited warranty and 
   restricted rights notice below appear in all supporting 
   documentation.
 
   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.  
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF 
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE 
   UNINTERRUPTED OR ERROR FREE.
 
   Use, duplication, or disclosure by the U.S. Government is subject to 
   restrictions set forth in FAR 52.227-19 (Commercial Computer 
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
   (Rights in Technical Data and Computer Software), as applicable.

*****************************************************************************/

/***************************************************************************/
/* INCLUDES */
/***************************************************************************/
#include <aseconst.h>
#include <asi.h>

#if defined(__cplusplus)
#include <aseclass.h>
#endif  /* __cplusplus */

/***************************************************************************/
/* DEFINES */
/***************************************************************************/
#define ASE_DSC_NULL     0L        /* Null descriptor */

/***************************************************************************/
/* TYPEDEFS */
/***************************************************************************/
typedef ulong ASE_DSC ;          /* The base API */
typedef ASE_DSC ASE_APPLDSC ;    /* The  application descriptor */
typedef ASE_DSC ASE_LPDSC ;      /* The Link Path descriptor */
typedef ASE_DSC ASE_LINKDSC ;    /* The link descriptor */
typedef ASE_DSC ASE_LSDSC ;    /* The link selection descriptor */

/***************************************************************************/
/* FUNCTION PROTOTYPES */
/***************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

ASE_DSC            ase_dsc_alloc(ASE_DSC dsc, EAseApiClassId Code) ;
void               ase_dsc_free(ASE_DSC *pDsc) ;
EAsiBoolean        ase_dsc_init(ASE_DSC dsc) ;
EAsiBoolean        ase_dsc_isInit(ASE_DSC dsc) ;
const char        *ase_dsc_version(ASE_DSC dsc) ;
EAseApiClassId     ase_dsc_isA(ASE_DSC dsc) ;
ASE_DSC            ase_dsc_clone(ASE_DSC dsc) ;
EAsiBoolean        ase_dsc_copyFrom(ASE_DSC dsc, 
                                    ASE_DSC source) ;
int                ase_dsc_cmp(ASE_DSC dsc, 
                               ASE_DSC dsc2) ;
int                ase_dsc_errQty(ASE_DSC dsc) ;
EAseErrDsc         ase_dsc_errDsc(ASE_DSC dsc, 
                                  int ErrNum) ;
int                ase_dsc_errCode(ASE_DSC dsc, 
                                   int ErrNum) ;
EAsiBoolean        ase_dsc_errMsg(ASE_DSC dsc, 
                                  int ErrNum,
                                  char *pBuf, 
                                  int BufLen) ;
EAsiBoolean        ase_dsc_errClear(ASE_DSC dsc) ;
const char*        ase_dsc_errDiagParNameCode(ASE_DSC dsc,
                                              int ParNum,
                                              int *pParCode,
                                              int *pIsStr) ;
EAsiBoolean        ase_dsc_errDiagParInt(ASE_DSC dsc,
                                         int ErrNum, 
                                         int ParCode,
                                         int *pIntValue) ;
EAsiBoolean        ase_dsc_errDiagParStr(ASE_DSC dsc,
                                         int ErrNum, 
                                         int ParCode,
                                         char *pStrValue,
                                         int BufLen) ;

ASE_APPLDSC        ase_appl_init(void) ;
void               ase_appl_term(ASE_APPLDSC *pApplDsc) ;
EAsiBoolean        ase_appl_getAseErr(ASE_APPLDSC applDsc) ;

EAsiBoolean        ase_lp_initPath(ASE_LPDSC lpDsc, 
                                   const char *pPath) ;
EAsiBoolean        ase_lp_initName(ASE_LPDSC lpDsc,
                                   const char *pName) ;
EAsiBoolean        ase_lp_initCurrent(ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_lp_setName(ASE_LPDSC lpDsc,
                                  const char *pName,
                                  EAseDoNameCode NameCode) ;
EAsiBoolean        ase_lp_getName(ASE_LPDSC lpDsc,
                                  char *pBuf, 
                                  int BufLen,
                                  EAseDoNameCode NameCode) ;
int                ase_lp_getNameSize(ASE_LPDSC lpDsc,
                                      EAseDoNameCode NameCode) ;
int                ase_lp_cmpName(ASE_LPDSC lpDsc,
                                    const char *pName, 
                                    EAseDoNameCode NameCode) ;
int                ase_lp_cmpDscName(ASE_LPDSC lpDsc,
                                     ASE_LPDSC lpDsc2,
                                     EAseDoNameCode NameCode) ;
EAseDoNameCode     ase_lp_getPathCode(ASE_LPDSC lpDsc) ;
int                ase_lp_getStatus(ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_lp_isUpdatable(ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_lp_getKeyDsc(ASE_LPDSC lpDsc, 
                                    ASICOLDSC *pKeyDsc[], int *pColQty) ;
EAsiBoolean        ase_lp_create(ASE_LPDSC lpDsc,
                                 const ASICOLDSC pKeyDsc[], 
                                 int ColQty) ;
EAsiBoolean        ase_lp_erase(ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_lp_rename(ASE_LPDSC lpDsc,
                                const char *pName) ;
EAsiBoolean        ase_lp_setCurrent(ASE_LPDSC lpDsc) ;
struct resbuf     *ase_lp_getLinkNames(ASE_LPDSC lpDsc) ;
struct resbuf     *ase_lp_getPaths(ASE_LPDSC lpDsc, int Status) ;

EAsiBoolean        ase_link_initType(ASE_LINKDSC linkDsc, 
                                     EAseLinkType LinkType) ;
EAsiBoolean        ase_link_initId(ASE_LINKDSC linkDsc, 
                                   LinkID LinkId) ;
EAsiBoolean        ase_link_initEntityLink(ASE_LINKDSC linkDsc, 
                                           const char *pName, 
                                           const ASICOLDSC pKeyValue[], 
                                           int ColQty,
                                           ads_name EntName) ;
EAsiBoolean        ase_link_initDALink(ASE_LINKDSC linkDsc, 
                                       const char *pName, 
                                       const ASICOLDSC pKeyValue[], 
                                       int ColQty,
                                       const ASICOLDSC pDACols[], 
                                       int DAColQty,
                                       const struct resbuf *pDAParms) ;
LinkID             ase_link_getId(ASE_LINKDSC linkDsc) ;
EAseLinkType       ase_link_getType(ASE_LINKDSC linkDsc) ;
EAsiBoolean        ase_link_getName(ASE_LINKDSC linkDsc, 
                                    char *pBuf, 
                                    int len) ;
EAsiBoolean        ase_link_setName(ASE_LINKDSC linkDsc, 
                                    const char *pName) ;
int                ase_link_getNameSize(ASE_LINKDSC linkDsc) ;
EAsiBoolean        ase_link_getEntity(ASE_LINKDSC linkDsc, 
                                      ads_name EntName) ;
EAsiBoolean        ase_link_setEntity(ASE_LINKDSC linkDsc, 
                                      ads_name EntName) ;
EAsiBoolean        ase_link_getKey (ASE_LINKDSC linkDsc,
                                    ASICOLDSC pKeyValue[], 
                                    int ColQty) ;
EAsiBoolean        ase_link_setKey (ASE_LINKDSC linkDsc, 
                                    const ASICOLDSC pKeyValue[], 
                                    int ColQty);
EAsiBoolean        ase_link_getDACols (ASE_LINKDSC linkDsc,
                                       ASICOLDSC *pCols[], 
                                       int *pColQty) ;
EAsiBoolean        ase_link_setDACols (ASE_LINKDSC linkDsc, 
                                       ASICOLDSC pCols[], 
                                       int ColQty) ;
EAsiBoolean        ase_link_setDAParms (ASE_LINKDSC linkDsc, 
                                        const struct resbuf *pParms) ;
EAsiBoolean        ase_link_setDAValues (ASE_LINKDSC linkDsc, 
                                         ASICOLDSC pCols[], 
                                         int ColQty) ;
EAsiBoolean        ase_link_create(ASE_LINKDSC linkDsc) ;
EAsiBoolean        ase_link_remove (ASE_LINKDSC linkDsc) ;
EAsiBoolean        ase_link_update (ASE_LINKDSC linkDsc) ;
EAsiBoolean        ase_link_getXName(ASE_LINKDSC linkDsc, 
                                     char *pBuf, 
                                     int len) ;
EAsiBoolean        ase_link_isUpdatable(ASE_LINKDSC linkDsc) ;

EAsiBoolean        ase_ls_initType(ASE_LSDSC lsDsc,
                                   EAseLinkType LinkType) ;
EAsiBoolean        ase_ls_initSel(ASE_LSDSC lsDsc,
                                  ads_name EntSelName) ;
EAsiBoolean        ase_ls_initEnt(ASE_LSDSC lsDsc,
                                  ads_name EntName) ;
EAsiBoolean        ase_ls_initXName(ASE_LSDSC lsDsc,
                                    const char *pXName) ;
EAsiBoolean        ase_ls_initLp(ASE_LSDSC lsDsc, 
                                 const char *pName) ;
EAsiBoolean        ase_ls_initLpDsc(ASE_LSDSC lsDsc,
                                    ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_ls_initLpEnt(ASE_LSDSC lsDsc, 
                                    const char *pName, 
                                    ads_name EntName) ;
EAsiBoolean        ase_ls_initLpDscEnt(ASE_LSDSC lsDsc,
                                       ASE_LPDSC lpDsc, 
                                       ads_name EntName) ;
EAsiBoolean        ase_ls_initLpSel(ASE_LSDSC lsDsc,
                                    const char *pName, 
                                    ads_name EntSelName) ;
EAsiBoolean        ase_ls_initLpDscSel(ASE_LSDSC lsDsc, 
                                       ASE_LPDSC lpDsc, 
                                       ads_name EntSelName) ;
EAsiBoolean        ase_ls_initLpCond(ASE_LSDSC lsDsc, 
                                     const char *pName, 
                                     const char *pTextCondition) ;
EAsiBoolean        ase_ls_initLpDscCond(ASE_LSDSC lsDsc, 
                                        ASE_LPDSC lpDsc, 
                                        const char *pTextCondition) ;
EAsiBoolean        ase_ls_initLpKey(ASE_LSDSC lsDsc, 
                                    const char *pName, 
                                    const ASICOLDSC pKeyValue[], 
                                    int ColQty) ;
EAsiBoolean        ase_ls_initLpDscKey(ASE_LSDSC lsDsc, 
                                       ASE_LPDSC lpDsc, 
                                       const ASICOLDSC pKeyValue[], 
                                       int ColQty) ;
EAsiBoolean        ase_ls_isUpdatable(ASE_LSDSC lsDsc) ;
long               ase_ls_getQty(ASE_LSDSC lsDsc) ;
LinkID             ase_ls_getId(ASE_LSDSC lsDsc, 
                                long ItemNum) ;
EAsiBoolean        ase_ls_addId(ASE_LSDSC lsDsc,
                                LinkID linkId) ;
EAsiBoolean        ase_ls_delId(ASE_LSDSC lsDsc,
                                long ItemNum) ;
long               ase_ls_membId(ASE_LSDSC lsDsc, 
                                 LinkID linkId) ;
EAsiBoolean        ase_ls_unite(ASE_LSDSC lsDsc,
                                ASE_LSDSC lsDsc2) ;
EAsiBoolean        ase_ls_subtract(ASE_LSDSC lsDsc,
                                   ASE_LSDSC lsDsc2) ;
EAsiBoolean        ase_ls_intersect(ASE_LSDSC lsDsc,
                                    ASE_LSDSC lsDsc2) ;
EAsiBoolean        ase_ls_intersectType(ASE_LSDSC lsDsc, 
                                        EAseLinkType LinkType) ;
EAsiBoolean        ase_ls_intersectEnt(ASE_LSDSC lsDsc, 
                                       ads_name EntName) ;
EAsiBoolean        ase_ls_intersectSel(ASE_LSDSC lsDsc, 
                                       ads_name EntSelName) ;
EAsiBoolean        ase_ls_intersectXName(ASE_LSDSC lsDsc, 
                                         const char *pXName) ;
EAsiBoolean        ase_ls_intersectLp(ASE_LSDSC lsDsc, 
                                         const char *pName) ;
EAsiBoolean        ase_ls_intersectLpDsc(ASE_LSDSC lsDsc, 
                                      ASE_LPDSC lpDsc) ;
EAsiBoolean        ase_ls_intersectLpKey(ASE_LSDSC lsDsc, 
                                         const char *pName, 
                                         const ASICOLDSC pKeyValue[], 
                                         int ColQty) ;
EAsiBoolean        ase_ls_intersectLpDscKey(ASE_LSDSC lsDsc,
                                            ASE_LPDSC lpDsc, 
                                            const ASICOLDSC pKeyValue[], 
                                            int ColQty) ;
EAsiBoolean        ase_ls_intersectLpCond(ASE_LSDSC lsDsc, 
                                          const char *pName, 
                                          const char *pTextCondition) ;
EAsiBoolean        ase_ls_intersectLpDscCond(ASE_LSDSC lsDsc, 
                                            ASE_LPDSC lpDsc, 
                                            const char *pTextCondition) ;
struct resbuf     *ase_ls_getXNames(ASE_LSDSC lsDsc) ;
struct resbuf     *ase_ls_getLinkNames(ASE_LSDSC lsDsc) ;
EAsiBoolean        ase_ls_getEntSel(ASE_LSDSC lsDsc,
                                    ads_name EntSelName) ;
EAsiBoolean        ase_ls_erase(ASE_LSDSC lsDsc) ;

/**********************************************************************/
/* Un-documented functions serving to supplement ASI C functionality  */
/**********************************************************************/

                     /* Creates the copy of the ASICOLDSC descriptor */
ASICOLDSC          asei_dupl_cdsc(ASICOLDSC coldsc) ;

                     /* Destroys the created ASICOLDSC descriptor */
void               asei_destroy_cdsc(ASICOLDSC *pcoldsc) ;

                     /* Constructs the array of the ASICOLDSC descriptors */
                     /* all of the descriptors are 0L */
ASICOLDSC*         asei_constr_cdscpack(int ColQty) ;

                     /* Clones the array of the ASICOLDSC descriptors */
ASICOLDSC*         asei_dupl_cdscpack(ASICOLDSC coldscs[], int ColQty) ;

                     /* Destroys the array of the ASICOLDSC descriptors */
void               asei_destroy_cdscpack(ASICOLDSC *coldscs[], int ColQty) ;

                     /* Makes the column descriptor nullable */
EAsiBoolean        asei_cdsc_setnull(ASICOLDSC coldsc) ;

                     /* Copies the data descriptor */
                     /* from the source ASICOLDSC into coldsc */
EAsiBoolean        asei_cdsc_setdata(ASICOLDSC coldsc, ASICOLDSC source) ;

                     /* Compares the names of the two ASICOLDSC descritpors */
                     /* returns 1 if they are similar */
int                asei_cdsc_cmpname(ASICOLDSC coldsc1, ASICOLDSC coldsc2) ;

                     /* Initializes the identifier by its name */
                     /* If the first character and last one */
                     /* are the double quotes, */
                     /* the delimited identifier is initialized */
EAsiBoolean        asei_ident_init(ASIIDENT ident, char *pName) ;

                     /* Compares two ASIIDENT identifiers */
                     /* returns 1 if they are similar */
int                asei_ident_cmp(ASIIDENT ident1, ASIIDENT ident2) ;

                     /* Gets the Result Type of the data in the column desc*/
                     /* Returns the types: RTREAL, RTLONG, RTSTR, RTVOID */
                     /*  RTSTR:                                           */
                     /* kAsiChar, kAsiCharVar, kAsiDateTime, kAsiInterval*/
                     /*  RTLONG:                                         */
                     /* kAsiSmallInt, kAsiInteger                        */
                     /*  RTREAL:                                         */
                     /* kAsiNumeric,kAsiDecimal,kAsiFloat,kAsiReal,      */
                     /* kAsiDouble                                       */
                     /*  RTVOID:                                         */
                     /* kAsiVector,kAsiImplDefined,kAsiTUnknown,kAsiBit, */
                     /* kAsiBitVar                                       */
                     /* or if error was occured                          */
                     /* The arguemnt pIsNull retreives kAsiTrue if       */
                     /* no data exist, kAsiFalse otherwise               */
int                asei_cdsc_rtype(ASICOLDSC coldsc, EAsiBoolean *pIsNull) ;

                     /* Gets the long data from the column desc */
EAsiBoolean        asei_cdsc_getlong(ASICOLDSC coldsc, long *pLong) ;

                     /* Sets the long data into the column desc */
EAsiBoolean        asei_cdsc_setlong(ASICOLDSC coldsc, long RLong) ;

                     /* Gets the real data from the column desc */
EAsiBoolean        asei_cdsc_getreal(ASICOLDSC coldsc, ads_real *pReal) ;

                     /* Sets the real data into the column desc */
EAsiBoolean        asei_cdsc_setreal(ASICOLDSC coldsc, ads_real RReal) ;

                     /* Gets the string data from the column desc */
                     /* The result is retreived in the */
                     /* default character set */
                     /* Gets the Binary data as the hex string */
EAsiBoolean        asei_cdsc_getstr(ASICOLDSC coldsc, char *pBuf, int bufLen);

                     /* Sets the string data into the column desc */
                     /* The specified strings has to be */
                     /* in the current character set */
                     /* Binary data should be represented as the hex string */
EAsiBoolean        asei_cdsc_setstr(ASICOLDSC coldsc, char *pStr);

                     /* Gets the data & column description */
                     /* from the specified cursor's column */
                     /* If the function returns kAsiGood, then */
                     /* the retreived column descriptor should */
                     /* be released later */
EAsiBoolean        asei_cds(ASICURSOR csr, int ColNum, ASICOLDSC *pcoldsc);

                     /* Binds the data from the column descriptor */
                     /* with the input parameter of the SQL statement */
EAsiBoolean        asei_bnd(ASIHANDLE stm, int parnum, ASICOLDSC col) ;

                     /* Converts ASI diagnostics into into */
                     /* ASE diagnostics area */
EAsiBoolean        ase_dsc_errInitAsi(ASE_DSC dsc,
                                      ASIHANDLE diag) ;
                                      
#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif /*_ASE_H*/
/*EOF*/
