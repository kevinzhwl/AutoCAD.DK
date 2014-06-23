/* 
   ADS.H   -    Definitions of the AutoCAD functions for Applications 
                This takes the place of xlacad.h (from LISP) and contains
                the changes to the function definitions to make them
                compatible with the application interface.


   Copyright (C) 1989-1997 by Autodesk, Inc.
 
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
    
*/

#ifndef _ads_h
#define _ads_h 1

#ifdef _MSC_VER
#ifndef RADPACK
#define RADPACK	1
#endif
#endif

/* Ensure that C++ modules use the right linking conventions when calling
   functions contained in C. */
#ifdef __cplusplus
    extern /*MSG0*/"C" {
#endif

#include "adsdef.h"

#if defined(RADPACK)
#pragma pack(1)
#endif /* RADPACK */

/*  Tricky macro for declaration of function types with optional
    prototype (i.e., declaration of argument types).  The way the
    macro "_()" is defined, the following declaration:

       int fcn _((int i, char c));

    will expand into either

       int fcn (int i, char c);
       or
       int fcn ();

    depending on whether the symbol PROTOTYPES is defined. */

#ifndef _
#ifdef PROTOTYPES
#define   _(x)  x
#else
#define   _(x)  ()
#endif /* PROTOTYPES */
#endif

/* External function definitions accessible from applications */

/* The following functions are only supported in Rx ADS */
#ifdef ACRXAPP
void           acrx_abort (const char * format, ...);
char*          ads_getappname _(());
int            ads_update(int vport, ads_point p1, ads_point p2);
#endif  /* ACRXAPP */

/* The following functions are not supported in Rx ADS */
#ifndef ACRXAPP
/* General abort mechanism.  Return RSABORT to Lisp. */
void           ads_abort _((const char *str));
/* ADS exit() function used for transparent exit of programs */
void           ads_exit _((int status));
/* Link back to host with request code */
int            ads_link _((int cbc));
/* Application initialization  function */
void           ads_init _((int argc, char *argv[]));

#ifdef WIN
/* Call before termination to clean up Windows, DDE, memory, etc */
void           adsi_machexit(int exitval);
void           adsi_farcq(struct farclb *fclb, int retcode);

#if defined(_WINDEF_)

/* AutoCAD main window handle */
extern HWND adsw_hwndAcad;
#endif /* _WINDOWS_ */

#endif /* WIN */

#endif  /* !ACRXAPP */


#if defined(ACRXAPP) && defined(_WINDEF_)
/* AutoCAD graphics window handle */
HWND           adsw_acadMainWnd();
#ifndef adsw_hwndAcad
#define adsw_hwndAcad adsw_acadMainWnd()
#endif

/* MFC "Document View" window handle */
HWND           adsw_acadDocWnd();

#endif  /* ACRXAPP && WIN && _WINDOWS_ */


#if defined(ACRXAPP)

#ifndef _SIZE_T
#define	_SIZE_T
/* so far, both solaris and NT define size_t as unsigned int.  We continue
   to use a typedef, however, in case some platform does not  */
typedef unsigned int	size_t;
#endif

void*          acad_malloc(size_t sz);
void           acad_free(void *);
int            acad__msize(void *);
void*          acad_realloc(void *, size_t ns);
void*          acad_calloc(size_t sz1, size_t sz2);
char*          acad__strdup(const char*);

/* so that existing ads/ads-arx applications can still find these */

#define ads_malloc	acad_malloc
#define ads_free	acad_free
#define ads__msize	acad__msize
#define ads_realloc acad_realloc
#define ads_calloc	acad_calloc
#define ads_strdup	acad__strdup

#endif  /* defined(ACRXAPP) */


/* The following functions are supported in traditional ADS and Rx ADS */
int            ads_command _((int rtype, ...));
int            ads_cmd _((const struct resbuf *rbp));

/* General failure (prints message) mechanism */
void           ads_fail _((const char *str));

/* Register an ADS function handler */
int            ads_regfunc _((int (*fhdl) (void), int fcode));

/* Get a new result buffer */
struct resbuf *ads_newrb _((int v));

/* Release a result buffer as well as those linked to it */
int            ads_relrb _((struct resbuf *rb));

/* Check for a console break */
int            ads_usrbrk _((void));


/* Define an external subroutine in AutoLISP */
int            ads_defun _((const char *sname, short funcno));

/* Define help for that external subroutine */
int            ads_setfunhelp (const char* pszFunctionName, 
                               const char* pszHelpfile,
                               const char* pszTopic, int iCmd);

/* Undefine an external subroutine in AutoLISP */
int            ads_undef _((const char *sname, short funcno));

/* Unitilies for external subroutine interface */
int            ads_getfuncode _((void));
struct resbuf *ads_getargs _((void));

/* Return the specified type as a result of external subroutine */
int            ads_retlist _((const struct resbuf *rbuf));
int            ads_retval _((const struct resbuf *rbuf));
int            ads_retpoint _((const ads_point pt));
int            ads_retstr _((const char *s));
int            ads_retname _((const ads_name aname, int type));
int            ads_retint _((int ival));
int            ads_retreal _((ads_real rval));
int            ads_rett _((void));
int            ads_retnil _((void));
int            ads_retvoid _((void));


/* AutoCAD Entity access routines */

int            ads_entdel _((const ads_name ent));
struct resbuf *ads_entgetx _((const ads_name ent, const struct resbuf *args));
struct resbuf *ads_entget _((const ads_name ent));
int            ads_entlast _((ads_name result));
int            ads_entnext _((const ads_name ent, ads_name result));
int            ads_entupd _((const ads_name ent));
int            ads_entmod _((const struct resbuf *ent));
int            ads_entmake _((const struct resbuf *ent));
int            ads_entmakex _((const struct resbuf *entm, ads_name result));
int            ads_entsel _((const char *str, ads_name entres,
                             ads_point ptres));
int            ads_nentsel _((const char *str, ads_name entres,
                              ads_point ptres, ads_point xformres[4],
                              struct resbuf **refstkres));
int            ads_nentselp _((const char *str, ads_name entres,
                              ads_point ptres, int pickflag,
                              ads_matrix xformres,
                              struct resbuf **refstkres));
int            ads_ssget _((const char *str, const void *pt1,
                            const void *pt2, const struct resbuf *filter,
                            ads_name ss));
int            ads_ssgetfirst _((struct resbuf** gset, struct resbuf** pset));
int            ads_sssetfirst _((const ads_name gset, const ads_name pset));
int            ads_ssfree _((const ads_name sname));
int            ads_sslength _((const ads_name sname, long *len));
int            ads_ssadd _((const ads_name ename, const ads_name sname,
                            ads_name result));
int            ads_ssdel _((const ads_name ename, const ads_name ss));
int            ads_ssmemb _((const ads_name ename, const ads_name ss));
int            ads_ssname _((const ads_name ss, long i, ads_name entres));
int            ads_ssnamex _((struct resbuf **rbpp, const ads_name ss,
                              const long i));
#ifdef ACRXAPP
int            ads_ssGetKwordCallbackPtr(struct resbuf* (**pFunc)(const char*));
int            ads_ssSetKwordCallbackPtr(struct resbuf* (*pFunc)(const char*));
int            ads_ssGetOtherCallbackPtr(struct resbuf* (**pFunc)(const char*));
int            ads_ssSetOtherCallbackPtr(struct resbuf* (*pFunc)(const char*));
#endif /* ACRXAPP */


/* Extended Entity data utilities */
int            ads_xdroom _((const ads_name ent, long *result));
int            ads_xdsize _((const struct resbuf *rb, long *result));

/* AutoCAD table access routines */
struct resbuf *ads_tblnext _((const char *tblname, int rewind));
struct resbuf *ads_tblsearch _((const char *tblname, const char *sym,
                                int setnext));

int	       ads_namedobjdict _((ads_name result));
struct resbuf *ads_dictsearch _((const ads_name tblname, const char* sym, 
                                 int setnext));
struct resbuf *ads_dictnext _((const ads_name tblname, int rewind));
int            ads_dictrename _((const ads_name dictname, const char* oldsym,
                                 const char* newsym));
int            ads_dictremove _((const ads_name dictname, const char* symname));
int            ads_dictadd _((const ads_name dictname, const char* symname,
                              const ads_name newobj));

int	       ads_tblobjname _((const char *tblname, const char *sym, 
                                 ads_name result));



/* Drawing database utilities */
int            ads_handent _((const char *handle, ads_name entres));
int            ads_trans _((const ads_point pt, const struct resbuf *from,
                            const struct resbuf *to, int disp,
                            ads_point result));

/* General AutoCAD utility routines */
int            ads_angtos _((ads_real v, int unit, int prec, char *str));
int            ads_cvunit _((ads_real value, const char *oldunit,
                             const char *newunit, ads_real *result));
int            ads_wcmatch _((const char *string, const char *pattern));
int            ads_rtos _((ads_real val, int unit, int prec, char *str));
int            ads_angtof _((const char *str, int unit, ads_real *v));
int            ads_distof _((const char *str, int unit, ads_real *v));
int            ads_setvar _((const char *sym, const struct resbuf *val));
int            ads_initget _((int val, const char *kwl));

int            ads_getsym _((const char *sname, struct resbuf **value));
int            ads_putsym _((const char *sname, struct resbuf *value));

int            ads_help _((char* szFilename, char* szTopic, int iCmd));
/*  These values are identical to those for the WinHelp() call in the 
    Microsoft Windows(tm) SDK.  If you are using ads_help() to call AutoCAD 
    platform-independent Help these are the only values available to you.  
    If you are using ads_help() to call WinHelp() you can include the Windows 
    header file winuser.h and use the full WinHelp() API.  */
#define HELP_CONTENTS     0x0003L  /* display first topic */
#define HELP_HELPONHELP   0x0004L  /* Display help on using help */
#define HELP_PARTIALKEY   0x0105L  /* Display Search dialog */

struct resbuf  *ads_loaded _((void));
int            ads_xload _((const char *app));
int            ads_xunload _((const char *app));
struct resbuf  *ads_arxloaded _((void));
int            ads_arxload _((const char *app));
int            ads_arxunload _((const char *app));

struct resbuf *ads_buildlist _((int rtype, ...));
int            ads_printf _((const char *format, ...));
int            ads_invoke _((const struct resbuf *args,
                             struct resbuf **result));
int            ads_inters _((const ads_point from1, const ads_point to1,
                             const ads_point from2, const ads_point to2,
                             int teston, ads_point result));

/* Functions that get system variables */
int            ads_getvar _((const char *sym, struct resbuf *result));
int            ads_findfile _((const char *fname, char *result));

/* Functions that get/set environment variables */
int            ads_agetenv _((const char *sym, char  *var));
int            ads_asetenv _((const char *sym, const char *val));
/*  Synonyms  */
#define        ads_getenv(s, v)  ads_agetenv(s, v)
#define        ads_setenv(s, v)  ads_asetenv(s, v)

/* Functions that get/set configurations  variables */
int            ads_agetcfg _((const char *sym, char  *var, int len));
int            ads_asetcfg _((const char *sym, const char *val));
/*  Synonyms  */
#define        ads_getcfg(s, v, l)  ads_agetcfg(s, v, l)
#define        ads_setcfg(s, v)  ads_asetcfg(s, v)

/* Function to test a table name */
int            ads_snvalid _((const char *tbstr, int pipetest));

/* Function to save a string ensuring no buffer overflow if, */
/* when converted, characters expand to \U+ sequences */
char *         ads_xstrsave _((char *pSource, char **pDest));

/* Function to uppercase a table name */
int            ads_xstrcase _((char *str));

/* Functions that get a string */
int            ads_getstring _((int cronly, const char *prompt, char *result));
int            ads_getstringb _((int cronly, const char *prompt,
                                    char *result, int bufsize));

/* Functions that pass AutoCAD a single string  */
int            ads_menucmd _((const char *str));
int            ads_prompt _((const char *str));
int            ads_alert _((const char *str));

/* Functions to register an application with AutoCAD */
int            ads_regapp _((const char *appname));
int            ads_regappx _((const char *appname, int xsave12));

/* Functions used to get user input  */
int            ads_getangle _((const ads_point pt, const char *prompt,
                               ads_real *result));
int            ads_getcorner _((const ads_point pt, const char *prompt,
                                ads_point result));
int            ads_getdist _((const ads_point pt, const char *prompt,
                              ads_real *result));
int            ads_getorient _((const ads_point pt, const char *prompt,
                                ads_real *result));
int            ads_getpoint _((const ads_point pt, const char *prompt,
                               ads_point result));
int            ads_getint _((const char *prompt, int *result));
int            ads_getkword _((const char *prompt, char *result));
int            ads_getreal _((const char *prompt, ads_real *result));
int            ads_getinput _((char *str));
int            ads_vports _((struct resbuf **vlist));

/* Functions for screen flipping */
int            ads_textscr _((void));
int            ads_graphscr _((void));
int            ads_textpage _((void));

/* Graphics related functions */
int            ads_redraw _((const ads_name ent, int mode));
int            ads_osnap _((const ads_point pt, const char *mode,
                            ads_point result));
int            ads_grread _((int track, int *type, struct resbuf *result));
int            ads_grtext _((int box, const char *text, int hl));
int            ads_grdraw _((const ads_point from, const ads_point to,
                             int color, int hl));
int            ads_grvecs _((const struct resbuf *vlist, ads_matrix mat));
int            ads_xformss _((const ads_name ssname,
                              ads_matrix genmat));
int            ads_draggen _((const ads_name ss, const char *pmt, int cursor,
                              int (*scnf) _((ads_point pt, ads_matrix mt)),
                              ads_point p));
int            ads_setview _((const struct resbuf *view, int vport));


/* Geometry utilities */
ads_real       ads_angle _((const ads_point pt1, const ads_point pt2));
ads_real       ads_distance _((const ads_point pt1, const ads_point pt2));
void           ads_polar _((const ads_point pt, ads_real angle,
                            ads_real dist, ads_point ptres));

/* Functions that put up standard dialogs for user input */
int            ads_getfiled _((const char *title, const char *defawlt,
                               const char *ext, int flags,
                               struct resbuf *result));

int            ads_textbox _((const struct resbuf *args,
                              ads_point pt1, ads_point pt2));

/*  Function to retrieve or establish AutoCAD's tablet transformation: */
int            ads_tablet  _((const struct resbuf *args,
                              struct resbuf **result));

/* Functions to support ADS / ADI communications */
int            ads_recfgport _((int *idvc, int iotype, int baudrate,
                                int parity, int databits, int stopbits,
                                int hhflag, char *devname));
void           ads_adiinfo   _((void *dsinfoptr));
void           ads_dscfg     _((void *dspktptr));
void           ads_dsxqt     _((void *dspktptr));
void           ads_dispt     _((void *dspktptr));
void           ads_adistart  _((void *dsactptr));
void           ads_adiend    _((void *dsactptr));

/* Functions for character handling */
int            ads_isalpha _((int c));
int            ads_isupper _((int c));
int            ads_islower _((int c));
int            ads_isdigit _((int c));
int            ads_isxdigit _((int c));
int            ads_isspace _((int c));
int            ads_ispunct _((int c));
int            ads_isalnum _((int c));
int            ads_isprint _((int c));
int            ads_isgraph _((int c));
int            ads_iscntrl _((int c));
int            ads_toupper _((int c));
int            ads_tolower _((int c));

/* Function for retrieving the localized or the language independent
   name of a command. */
int            ads_getcname _((const char *cmd, char **result));

/* When you want something that's explicitly a pointer type and not an array
   type, use ads_pointp and ads_namep.  Remember that if your function takes an
   *array* of points, it still declares ads_point[] foo; */
typedef ads_real *ads_pointp;
typedef long     *ads_namep;

/* Define macros to copy them.  NOTE that the result is the SECOND argument,
   consistent with ADS usage.  The standard C ones require <string.h> */
#ifdef __STDC__
#define ads_name_set(from, to)  (memcpy(to, from, sizeof(ads_name)))
#define ads_point_set(from,to)  (memcpy(to, from, sizeof(ads_point)))
#else
#define ads_name_set(from, to)  (*(to)= *(from), (to)[1]=(from)[1])
#define ads_point_set(from, to) (*(to)= *(from), (to)[1]=(from)[1], (to)[2]=(from)[2])
#endif  /* !__STDC__ */

/* Define null value for ads_names.  These values are NOT guaranteed valid;
   that is, there is no actual guarantee (such as C gives with NULL) that the
   system will never under any circumstances generate the values as valid data.
   The correct values will be created as part of the Lisp reinitialization
   project, if we go through with that one, and will then be inserted here.
   */
#define ads_name_clear(name)    name[0] = name[1] = 0
#define ads_name_nil(name)      (name[0] == 0 && name[1] == 0)
#define ads_name_equal(name1, name2)  (name1[0]==name2[0] \
                                       && name1[1]==name2[1])

#ifdef RADPACK
#pragma pack( )
#endif

#ifdef __cplusplus
    }
#endif

#endif  /* !_ads_h */
