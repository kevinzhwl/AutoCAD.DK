/*****************************************************************************
    Name: asi.h                                       ast_asi_inc_appl_asi_h

    Description:  Header file for AutoCAD SQL Interface.
                  "C" call interface

   Copyright (C) 1991-1997 by Autodesk, Inc.

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
#ifndef ASI_ASI_H
#define ASI_ASI_H asih

#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

/***************************************************************************/
/* INCLUDES */
/***************************************************************************/

/***************************************************************************/
/* TYPEDEFS */
/***************************************************************************/

typedef ulong ASIHANDLE;               /* Generic ASI handle */
typedef ulong ASIENV;                  /* Asi Environment handle */
typedef ulong ASISESSION;              /* Session handle */
typedef ulong ASISTATEMENT;            /* Statement handle */
typedef ulong ASICURSOR;               /* Cursor */
typedef ulong ASIPARDSC;               /* Input parameter handle */
typedef ulong ASICOLDSC;               /* Column descriptor handle */
typedef ulong ASIIDENT;                /* Identifier */
typedef ulong ASIDATADSC;              /* Data descriptor */
typedef ulong ASICONFIG;               /* Configuration file descriptor */

/* Cast sesison, statement, or cursor to generic handle */
#define ASI_CASTTODIAG(x)     ((ASIHANDLE)(x))

/* Cursor status */
#define ASI_CUPDATABLE     0x00000001      /* updatable cursor */
#define ASI_CINSENSITIVE   0x00000002      /* insensitive cursor */
#define ASI_CSCROLL        0x00000004      /* scrollable cursor */
#define ASI_COPEN          0x00000008      /* open cursor */



/***************************************************************************/
/* FUNCTION PROTOTYPES */
/***************************************************************************/

/* identifier management functions */
EAsiBoolean    asi_constr_ident       (ASIIDENT *);              /* Construct Identifier */
EAsiBoolean    asi_destroy_ident      (ASIIDENT *);              /* Destroy Identifier object */
EAsiBoolean    asi_dupl_ident         (ASIIDENT, ASIIDENT *);    /* Duplicate identifier */
EAsiBoolean    asi_init_regular_ident (ASIIDENT, char *);        /* Initialize regular identifier */
EAsiBoolean    asi_init_delimit_ident (ASIIDENT, char *);        /* Initialize delimited identifier */
char *         asi_get_ident          (ASIIDENT, char *, int); /* Get identifier body */

/* Data descriptor */
EAsiBoolean      asi_destroy_ddsc       (ASIDATADSC *);
EAsiDataType     asi_ddsc_type          (ASIDATADSC);             /* type */
EAsiDTType       asi_ddsc_datetimetype  (ASIDATADSC);             /* datetime type */
EAsiIType        asi_ddsc_intervaltype  (ASIDATADSC);             /* interval type */
uint             asi_ddsc_precision     (ASIDATADSC);             /* Precison */
uint             asi_ddsc_scale         (ASIDATADSC);             /* Scale */
uint             asi_ddsc_length        (ASIDATADSC);             /* Length */
uint             asi_ddsc_timeprec      (ASIDATADSC);             /* Time precision */
uint             asi_ddsc_lfp           (ASIDATADSC);             /* Interval leading field precision */
uint             asi_ddsc_fsp           (ASIDATADSC);             /* Interval fractional second precison */
uint             asi_ddsc_ret_length    (ASIDATADSC);             /* Return length */
char *           asi_ddsc_sqltype       (ASIDATADSC, char *, int); /* Return SQL type as a string */

/* Input parmaeter manipulation */
EAsiBoolean      asi_pdsc_name          (ASIPARDSC, ASIIDENT *);   /* Parameter name */
EAsiBoolean      asi_pdsc_ddsc          (ASIPARDSC, ASIDATADSC *); /* Parameter data descriptor */
EAsiBoolean      asi_pdsc_nullable      (ASIPARDSC);               /* Is nullable */

/* Column descriptor */
EAsiBoolean      asi_cdsc_name          (ASICOLDSC, ASIIDENT *);   /* Parameter name */
EAsiBoolean      asi_cdsc_ddsc          (ASICOLDSC, ASIDATADSC *); /* Parameter data descriptor */
EAsiBoolean      asi_cdsc_nullable      (ASICOLDSC);               /* Is nullable */


/* ASI initialization and termination functions */
EAsiBoolean    asi_initasi         (ASIENV *);
EAsiBoolean    asi_termasi         (ASIENV *);
EAsiBoolean    asi_abortasi        (ASIENV *);

/* ASI connection management functions */
EAsiBoolean    asi_constr_session  (ASISESSION *, ASIENV);
EAsiBoolean    asi_destroy_session (ASISESSION *, ASIENV);
EAsiBoolean    asi_connect         (ASISESSION, char *, char *, char *);
EAsiBoolean    asi_disconnect      (ASISESSION);
EAsiBoolean    asi_disconnectall   (ASIENV);

/* Driver information */
EAsiBoolean    asi_version       (ASIENV, char *, int);
EAsiBoolean    asi_dbms          (ASIHANDLE, char *, int);
EAsiBoolean    asi_sqlobject     (ASIHANDLE, char *, int);
EAsiBoolean    asi_message       (ASIHANDLE, char *, int);
EAsiBoolean    asi_checkop       (ASIHANDLE, ulong);

/* ASI session management functions */
EAsiBoolean    asi_setcatalog      (ASISESSION, char *);
EAsiBoolean    asi_setschema       (ASISESSION, char *);
EAsiBoolean    asi_setnames        (ASISESSION, char *);
EAsiBoolean    asi_settimezone     (ASISESSION, ASI_IHOURTOMINUTE *);
EAsiBoolean    asi_setauthor       (ASISESSION, char *);
EAsiBoolean    asi_settrans        (ASISESSION, EAsiTILevel, EAsiTMode, uint);
EAsiBoolean    asi_setdefconstr    (ASISESSION, ASIIDENT);
EAsiBoolean    asi_setimmconstr    (ASISESSION, ASIIDENT);
EAsiBoolean    asi_commit          (ASISESSION);
EAsiBoolean    asi_rollback        (ASISESSION);

/* ASI diagnostics functions */
EAsiStatement  asi_opr           (ASIHANDLE);
EAsiStatement  asi_stm           (ASIHANDLE);
long           asi_rowqty        (ASIHANDLE);
EAsiBoolean    asi_getcuropt     (ASICURSOR, ulong *);
int            asi_synerrpos     (ASIHANDLE);
int            asi_condqty       (ASIHANDLE);
EAsiError      asi_err           (ASIHANDLE, int);
char *         asi_errmsg        (ASIHANDLE, char *, int, int);
char*          asi_sqlstate      (ASIHANDLE, int);
EAsiBoolean    asi_getdiagpar    (ASIHANDLE, EAsiDiag, void *, int, int);

/* Statement descriptors */
int            asi_parcount      (ASIHANDLE);
EAsiBoolean    asi_pds           (ASIHANDLE, int, ASIPARDSC *);
EAsiBoolean    asi_bndname       (ASIHANDLE, ASIIDENT, void*, short*, int, EAsiHostType);
EAsiBoolean    asi_bndnum        (ASIHANDLE, int, void*, short*, int, EAsiHostType);
int            asi_colcount      (ASIHANDLE);
EAsiBoolean    asi_cds           (ASIHANDLE, int, ASICOLDSC *);
EAsiBoolean    asi_sob           (ASIHANDLE, int, void*, short*, int, EAsiHostType);
EAsiBoolean    asi_cvl           (ASIHANDLE, int, void*, short*, int, EAsiHostType);


/* Statement processing functions */
EAsiBoolean    asi_constr_stm      (ASISTATEMENT *);
EAsiBoolean    asi_constr_native_stm (ASISTATEMENT *);
EAsiBoolean    asi_destroy_stm     (ASISTATEMENT *);
EAsiBoolean    asi_prepare         (ASISTATEMENT, ASISESSION, char *);
EAsiBoolean    asi_execute         (ASISTATEMENT);
EAsiBoolean    asi_iexecute        (ASISTATEMENT, ASISESSION, char *);
EAsiBoolean    asi_dealloc_stm     (ASISTATEMENT);


/* Cursor Manipulation Functions */
EAsiBoolean    asi_constr_csr      (ASICURSOR *);
EAsiBoolean    asi_destroy_csr     (ASICURSOR *);
EAsiBoolean    asi_alloc_csr       (ASICURSOR, ASISTATEMENT, char *,
                                    EAsiCurScr, EAsiCurSns);
EAsiBoolean    asi_open            (ASICURSOR);
EAsiBoolean    asi_close           (ASICURSOR);
EAsiBoolean    asi_fetch           (ASICURSOR);
EAsiBoolean    asi_fetchPrior      (ASICURSOR);
EAsiBoolean    asi_fetchFirst      (ASICURSOR);
EAsiBoolean    asi_fetchLast       (ASICURSOR);
EAsiBoolean    asi_fetchAbsolute   (ASICURSOR, long);
EAsiBoolean    asi_fetchRelative   (ASICURSOR, long);
EAsiBoolean    asi_delete          (ASICURSOR);
EAsiBoolean    asi_update          (ASICURSOR, ...);


/* Asi configuration access */
EAsiBoolean asi_constr_cfg   (ASICONFIG *);
EAsiBoolean asi_destroy_cfg  (ASICONFIG *);
int         asi_getcfgstring (ASICONFIG, char *, char *, char *, char *, int);
EAsiBoolean asi_setcfgstring (ASICONFIG, char *, char *, char *);
EAsiBoolean asi_createenv    (ASICONFIG, char *, char *);
EAsiBoolean asi_dropenv      (ASICONFIG, char *);
#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif /* ASI_ASI_H */
/*EOF*/
