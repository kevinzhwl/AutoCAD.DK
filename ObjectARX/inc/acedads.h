//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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

#ifndef _acedads_h
#define _acedads_h 1

// Ensure that C++ modules use the right linking conventions when calling
// functions contained in C.

#ifdef __cplusplus
    extern "C" {
#endif

#include "adsdef.h"
#include "acmem.h"

#pragma pack (push, 8)
/* External function definitions accessible from applications */

void           acrx_abort (const char * format, ...);
char*          acedGetAppName ();
int            acedUpdate(int vport, ads_point p1, ads_point p2);


#if defined(_WINDEF_)
/* AutoCAD graphics window handle */
HWND           adsw_acadMainWnd();
#ifndef adsw_hwndAcad
#define adsw_hwndAcad adsw_acadMainWnd()
#endif

/* MFC "Document View" window handle */
HWND           adsw_acadDocWnd();

#endif  // _WINDOWS_

/* The following functions are supported in traditional ADS and Rx ADS */
int            acedCommand (int rtype, ...);
int            acedCmd (const struct resbuf *rbp);

/* Register an ADS function handler */
int            acedRegFunc (int (*fhdl) (void), int fcode);

/* Check for a console break */
int            acedUsrBrk (void);


/* Define an external subroutine in AutoLISP */
int            acedDefun (const char *sname, short funcno);

/* Define help for that external subroutine */
int            acedSetFunHelp (const char* pszFunctionName, 
                               const char* pszHelpfile,
                               const char* pszTopic, int iCmd);

/* Undefine an external subroutine in AutoLISP */
int            acedUndef (const char *sname, short funcno);

/* Unitilies for external subroutine interface */
int            acedGetFunCode (void);
struct resbuf *acedGetArgs (void);

/* Return the specified type as a result of external subroutine */
int            acedRetList (const struct resbuf *rbuf);
int            acedRetVal (const struct resbuf *rbuf);
int            acedRetPoint (const ads_point pt);
int            acedRetStr (const char *s);
int            acedRetName (const ads_name aname, int type);
int            acedRetInt (int ival);
int            acedRetReal (ads_real rval);
int            acedRetT (void);
int            acedRetNil (void);
int            acedRetVoid (void);

/* AutoCAD Entity access routines */

int            acedEntSel (const char *str, ads_name entres,
                             ads_point ptres);
int            acedNEntSel (const char *str, ads_name entres,
                              ads_point ptres, ads_point xformres[4],
                              struct resbuf **refstkres);
int            acedNEntSelP (const char *str, ads_name entres,
                              ads_point ptres, int pickflag,
                              ads_matrix xformres,
                              struct resbuf **refstkres);
int            acedSSGet (const char *str, const void *pt1,
                            const void *pt2, const struct resbuf *filter,
                            ads_name ss);
int            acedSSGetFirst (struct resbuf** gset, struct resbuf** pset);
int            acedSSSetFirst (const ads_name gset, const ads_name pset);
int            acedSSFree (const ads_name sname);
int            acedSSLength (const ads_name sname, long *len);
int            acedSSAdd (const ads_name ename, const ads_name sname,
                            ads_name result);
int            acedSSDel (const ads_name ename, const ads_name ss);
int            acedSSMemb (const ads_name ename, const ads_name ss);
int            acedSSName (const ads_name ss, long i, ads_name entres);
int            acedSSNameX (struct resbuf **rbpp, const ads_name ss,
                              const long i);
int            acedSSGetKwordCallbackPtr(struct resbuf* (**pFunc)(const char*));
int            acedSSSetKwordCallbackPtr(struct resbuf* (*pFunc)(const char*));
int            acedSSGetOtherCallbackPtr(struct resbuf* (**pFunc)(const char*));
int            acedSSSetOtherCallbackPtr(struct resbuf* (*pFunc)(const char*));

int            acedTrans (const ads_point pt, const struct resbuf *from,
                            const struct resbuf *to, int disp,
                            ads_point result);

/* General AutoCAD utility routines */
int            acedSetVar (const char *sym, const struct resbuf *val);
int            acedInitGet (int val, const char *kwl);

int            acedGetSym (const char *sname, struct resbuf **value);
int            acedPutSym (const char *sname, struct resbuf *value);

int            acedHelp (char* szFilename, char* szTopic, int iCmd);
int            acedFNSplit (const char *pathToSplit, char *prebuf,
                            char *namebuf, char *extbuf);

/*  These values are identical to those for the WinHelp() call in the 
    Microsoft Windows(tm) SDK.  If you are using acedHelp() to call AutoCAD 
    platform-independent Help these are the only values available to you.  
    If you are using acedHelp() to call WinHelp() you can include the Windows 
    header file winuser.h and use the full WinHelp() API.  */
#define HELP_CONTENTS     0x0003L  /* display first topic */
#define HELP_HELPONHELP   0x0004L  /* Display help on using help */
#define HELP_PARTIALKEY   0x0105L  /* Display Search dialog */

struct resbuf  *acedArxLoaded (void);
int            acedArxLoad (const char *app);
int            acedArxUnload (const char *app);

int            acedInvoke (const struct resbuf *args,
                             struct resbuf **result);
/* Functions that get system variables */
int            acedGetVar (const char *sym, struct resbuf *result);
int            acedFindFile (const char *fname, char *result);

/* Functions that get/set environment variables */
int            acedGetEnv (const char *sym, char  *var);
int            acedSetEnv (const char *sym, const char *val);

/* Functions that get/set configurations  variables */
int            acedGetCfg (const char *sym, char  *var, int len);
int            acedSetCfg (const char *sym, const char *val);

/* Functions that get a string */
int            acedGetString (int cronly, const char *prompt, char *result);
int            acedGetStringB (int cronly, const char *prompt,
                                    char *result, int bufsize);

/* Functions that pass AutoCAD a single string  */
int            acedMenuCmd (const char *str);
int            acedPrompt (const char *str);
int            acedAlert (const char *str);

/* Functions used to get user input  */
int            acedGetAngle (const ads_point pt, const char *prompt,
                               ads_real *result);
int            acedGetCorner (const ads_point pt, const char *prompt,
                                ads_point result);
int            acedGetDist (const ads_point pt, const char *prompt,
                              ads_real *result);
int            acedGetOrient (const ads_point pt, const char *prompt,
                                ads_real *result);
int            acedGetPoint (const ads_point pt, const char *prompt,
                               ads_point result);
int            acedGetInt (const char *prompt, int *result);
int            acedGetKword (const char *prompt, char *result);
int            acedGetReal (const char *prompt, ads_real *result);
int            acedGetInput (char *str);
int            acedVports (struct resbuf **vlist);

/* Functions for screen flipping */
int            acedTextScr (void);
int            acedGraphScr (void);
int            acedTextPage (void);

/* Graphics related functions */
int            acedRedraw (const ads_name ent, int mode);
int            acedOsnap (const ads_point pt, const char *mode,
                            ads_point result);
int            acedGrRead (int track, int *type, struct resbuf *result);
int            acedGrText (int box, const char *text, int hl);
int            acedGrDraw (const ads_point from, const ads_point to,
                             int color, int hl);
int            acedGrVecs (const struct resbuf *vlist, ads_matrix mat);
int            acedXformSS (const ads_name ssname,
                              ads_matrix genmat);
int            acedDragGen (const ads_name ss, const char *pmt, int cursor,
                              int (*scnf) (ads_point pt, ads_matrix mt),
                              ads_point p);
int            acedSetView (const struct resbuf *view, int vport);


/* Functions that put up standard dialogs for user input */
int            acedGetFileD (const char *title, const char *defawlt,
                               const char *ext, int flags,
                               struct resbuf *result);
int            acedGetFileNavDialog (const char *title, const char *defawlt,
                             const char *ext, const char *dlgname, int flags,
                             struct resbuf **result);

int            acedTextBox (const struct resbuf *args,
                              ads_point pt1, ads_point pt2);

/*  Function to retrieve or establish AutoCAD's tablet transformation: */
int            acedTablet  (const struct resbuf *args,
                              struct resbuf **result);

/* Function for retrieving the localized or the language independent
   name of a command. */
int            acedGetCName (const char *cmd, char **result);


// The following are AcDb related, but were not able to be moved over
// to AcDb at this time.  They will be moved in a future release.  7/14/98

int            acdbEntDel (const ads_name ent);
struct resbuf *acdbEntGetX (const ads_name ent, const struct resbuf *args);
struct resbuf *acdbEntGet (const ads_name ent);
int            acdbEntLast (ads_name result);
int            acdbEntNext (const ads_name ent, ads_name result);
int            acdbEntUpd (const ads_name ent);
int            acdbEntMod (const struct resbuf *ent);
int            acdbEntMake (const struct resbuf *ent);
int            acdbEntMakeX (const struct resbuf *entm, ads_name result);
int            acdbRegApp (const char *appname);
struct resbuf *acdbTblNext (const char *tblname, int rewind);
struct resbuf *acdbTblSearch (const char *tblname, const char *sym,
                              int setnext);
int	           acdbNamedObjDict (ads_name result);
struct resbuf *acdbDictSearch (const ads_name dict, const char* sym, 
                               int setnext);
struct resbuf *acdbDictNext (const ads_name dict, int rewind);
int            acdbDictRename (const ads_name dictname, const char* oldsym,
                               const char* newsym);
int            acdbDictRemove (const ads_name dictname, const char* symname);
int            acdbDictAdd (const ads_name dictname, const char* symname,
                            const ads_name newobj);

int	           acdbTblObjName (const char *tblname, const char *sym, 
                               ads_name result);

int            acdbAngToS (ads_real v, int unit, int prec, char *str);
int            acdbRToS (ads_real val, int unit, int prec, char *str);
int            acdbAngToF (const char *str, int unit, ads_real *v);
int            acdbDisToF (const char *str, int unit, ads_real *v);
int            acdbInters (const ads_point from1, const ads_point to1,
                             const ads_point from2, const ads_point to2,
                             int teston, ads_point result);
int            acdbSNValid (const char *tbstr, int pipetest);



#pragma pack (pop)

#ifdef __cplusplus
    }
#endif  /* __cplusplus */

#pragma pack (push, 8)
#ifdef __cplusplus
extern "C++" {

int            acedGetFullInput(char *&pStr);
int            acedGetFullKword(const char * pString, char *&pStr);
int            acedGetFullString(int cronly, const char *pString,
                                 char *&pResult);
int            acedSSNameXEx (struct resbuf **rbpp, const ads_name ss,
                              const long i, unsigned int flags = 0);
}

#endif  /* __cplusplus */

#pragma pack (pop)

#endif  /* !_acedads_h */
