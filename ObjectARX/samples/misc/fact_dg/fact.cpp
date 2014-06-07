/* Next available MSG number is   8 */

/*    FACT.CPP

   (C) Copyright 1998-1999 by Autodesk, Inc.
 
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

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

#include  <stdio.h>
#include  "adslib.h"
#include  "rxregsvc.h"
#include  "rxdefs.h"


/* Utility definition to get an  array's  element  count  (at  compile
   time).   For  example:  

       int  arr[] = {1,2,3,4,5};
       ... 
       printf("%d", ELEMENTS(arr));

   would print a five.  ELEMENTS("abc") can also be used to  tell  how
   many  bytes are in a string constant INCLUDING THE TRAILING NULL. */

#define ELEMENTS(array) (sizeof(array)/sizeof((array)[0]))


/* All the functions that we'll define will be listed in a single table,
   together with the internal function that we call to handle each.  The
   functions all take a single argument (the resbuf that has the
   arguments) and return an integer (RTNORM or RTERROR for good or bad
   status).  */


/* First, define the structure of the table: a string giving the AutoCAD name
   of the function, and a pointer to a function returning type int. */
struct func_entry { char *func_name; int (*func) (struct resbuf *); };

/* Here we declare the functions that handle the calls; at the moment there are
   two of them. */
int fact       (struct resbuf *rb);
int squareroot (struct resbuf *rb);

/* Here we define the array of function names and handlers. */
static struct func_entry func_table[] = { {/*MSG0*/"fact", fact},
                                          {/*MSG0*/"sqr", squareroot},
                                        };
/* To add more functions to this table, just put them in the list, after
   declaring the function names.  Note that in standard C it's all right to
   have a superfluous comma after the last item.  */


/* The code from here to the end of dofun() is UNCHANGED when you add or delete
   functions. */


/*  Declarations of other local functions  */
void     main       (int, char **);
int      dofun      (void);
int      funcload   (void);
ads_real rfact      (int x);
ads_real rsqr       (ads_real x);

/*-----------------------------------------------------------------------*/
/* ACRXENTRYPOINT -- This function replaces main() for an ARX program. */

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch(msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        break;
    case AcRx::kInvkSubrMsg:
        dofun();
        break;
    case AcRx::kLoadDwgMsg:
        funcload();
    }
    return AcRx::kRetOK;
}



/*-----------------------------------------------------------------------*/
/* FUNCLOAD  --  Define this application's external functions.  Return
                 RTERROR on error, else RTNORM.                   */

static int funcload()
{
    int i;

    for (i = 0; i < ELEMENTS(func_table); i++) {
        if (!acedDefun(func_table[i].func_name, (short)i))
            return RTERROR;
    }
    return RTNORM;
}

/*-----------------------------------------------------------------------*/
/* DOFUN -- Execute external function (called upon an RQSUBR request).  
            Return value from the function executed, RTNORM or RTERROR. */

static int dofun()
{
    struct resbuf *rb;
    int val;

    /* Get the function code and check that it's within range.
       (It can't fail to be, but paranoia doesn't hurt.) */
    if ((val = acedGetFunCode()) < 0 || val >= ELEMENTS(func_table)) {
        acdbFail(/*MSG2*/"Received nonexistent function code.");
        return RTERROR;
    }

    /* Fetch the arguments, if any. */
    rb = acedGetArgs();

    /* Call the handler and return its success-failure status. */
    val = (*func_table[val].func)(rb);
    acutRelRb(rb);
    return val;
}


/* The code from the beginning of main() to here is UNCHANGED when you add or
   delete functions.  */

/*-----------------------------------------------------------------------*/
/* FACT -- First set up the argument, then call the factorial function */
static int
fact(struct resbuf *rb)
{
    int x;

    if (rb == NULL)
        return RTERROR;

    if (rb->restype == RTSHORT) {
        x = rb->resval.rint;          /* Save in local variable */
    } else {
        acdbFail(/*MSG3*/"Argument should be an integer.");
        return RTERROR;
    }

    if (x < 0) {                      /* Check argument range */
        acdbFail(/*MSG4*/"Argument should be positive.");
        return RTERROR;
    } else if (x > 170) {             /* Avoid floating-point overflow */
        acdbFail(/*MSG5*/"Argument should be 170 or less.");
        return RTERROR;
    }

    acedRetReal(rfact(x));            /* Call the function itself, and
                                         return the value to AutoLISP */
    return RTNORM;
}

/*-----------------------------------------------------------------------*/
/* This is the implementation of the actual external factorial function */

static ads_real rfact(int n)
{
    ads_real ans = 1.0;

    while (n)
        ans *= n--;

    return ans;
}

/*-----------------------------------------------------------------------*/
/* SQUAREROOT -- First set up the argument, then call the root function */
static int
squareroot(struct resbuf *rb)
{
    ads_real x;

    if (rb == NULL)
        return RTERROR;               /* A proper error msg would be better */

    if (rb->restype == RTSHORT) {     /* Save in local variable */
        x = (ads_real) rb->resval.rint;
    } else if (rb->restype == RTREAL) {
        x = rb->resval.rreal;         /* Can accept either real
                                         or integer */
    } else {
        acdbFail(/*MSG6*/"Argument should be a real or integer value.");
        return RTERROR;
    }

    if (x < 0) {                      /* Check argument range */
        acdbFail(/*MSG7*/"Argument should be positive.");
        return RTERROR;
    }

    ads_retreal(rsqr(x));             /* Call the function itself, and
                                         return the value to AutoLISP */

    return RTNORM;
}

/*-----------------------------------------------------------------------*/
/* This is the implementation of the actual external function */

static ads_real rsqr(ads_real x)       /* Square root by Newton's method */
{
    int n = 50;
    ads_real y, c, cl;

    if (x == 0.0) {
        return 0.0;
    }

    y = (x * 2 + .1) / (x + 1.0);
    c = (y - x / y) / 2;
    cl= 0.0;

    while ((c != cl) && (n-- > 0)) {
        y -= c;
        cl = c;
        c  = (y - x / y) / 2;
    }
    return y;
}

// END CODE APPEARING IN SDK DOCUMENT.
