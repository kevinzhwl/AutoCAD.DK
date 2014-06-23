#ifndef _adslib_h
#define _adslib_h 1
/*    
   (C) Copyright 1989-1997 by Autodesk, Inc.
 
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
 
   DESCRIPTION:
   ADS definitions and system dependent controls.
   This also contains a substitute for stdlib.h on some systems.
   If we know the system has stdlib.h, just include it.
*/

#ifdef  _MAXSTRING
#undef  _MAXSTRING
#define _MAXSTRING  (~0)
#endif

/* Note: As of this writing, Sun ANSI C defines __STDC__, but
   sets it to a non-numeric value.  This is contrary to the
   ANSI standard, but we'll live with it for now.  Hence the
   unusual handling of __STDC__.
 */
#ifdef __STDC__
#define STDC_DEFINED 1
#else
#define STDC_DEFINED 0
#endif

#ifdef _WINDOWS
#define WIN 1
#endif

#ifdef WINVER
#define WIN 1
#endif

#ifdef _MSC_VER
#define MICROSOFT 1
#endif

#ifdef __TURBOC__
#define TURBOC 1
#endif

#ifdef WIN
#define main(a,b) ads_main(a,b)
#define PROTOTYPES 1
#endif	/* WIN */

#ifndef PROTOTYPES
#if STDC_DEFINED || defined(__cplusplus) 
#define PROTOTYPES 1
#endif
#endif

#ifdef PROTOTYPES
#define   _(x)	x
#else
#define   _(x)	()
#endif

/* Substitute for STDLIB.H on systems that do NOT have it.
   Also enable use of const in adsxxx.h declarations. 
 */
#ifndef ACRXAPP

#if	  STDC_DEFINED || defined(__cplusplus) || WIN || MICROSOFT
#include  <stdlib.h>
#else

/* Declaration for ?alloc() was set to char * because that caused us fewer
   compiler warnings in some substandard systems.  Now we declare it as ANSI
   standard by default.  The Sparc compiler works fine with this, though the
   obsolete lint on Unix screams its ancient head off.	(Serious programmers
   use Gimpel's PC-Lint.)

   Any exceptions to the proper ANSI-style declaration must be explicitly
   machine by machine. 
*/
void *malloc _((size_t size));
void *calloc _((unsigned int nelem, size_t elsize));
void free    _((void *ptr));
void *realloc(void *, size_t);
#ifndef TURBOC
double atof _((char *nptr));
#endif
int    atoi _((char *nptr));
void   exit _((int status));
double fmod _((double x, double y));

/* Enable the use of const on machines that support it (by making it disappear
   on these non-standard machines).
 */
#ifndef const
#define const
#define _adslib_h_const
#endif
#endif

#endif

#include "ads.h"
#include "adscodes.h"

#ifdef _adslib_h_const
#undef const
#undef _adslib_h_const
#endif

#ifndef _rxsvc_applockfun
#define _rxsvc_applockfun 1

#if defined(__cplusplus)
extern "C" {
#endif

/* Unlocks an application to enable it from being unloaded in mid-session.
   The default is that applications are locked, and hence unloadable in
   mid-session. The appId argument is the Id passed in as a void* during
   the AcRx::kInitAppMsg call back when the application is loaded. Return
   of non-zero means success.
*/
extern int acrxUnlockApplication(void* appId);

/* Returns non-zero if the specified app is locked.
 */
extern int acrxApplicationIsLocked(const char* modulename);

/* Symmetric to acrxUnlockApplication. Locks it, and hence prevents it from
   being unloaded in mid-session. Return of non-zero means success.
 */
extern int acrxLockApplication(void* appId);

#if defined(__cplusplus)
}
#endif

#endif
#endif
