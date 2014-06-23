#ifndef _adsdef_h
#define _adsdef_h 1
/* 
   (C) Copyright 1994-1997 by Autodesk, Inc.
 
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

#ifdef _MSC_VER
#ifndef RADPACK
#define RADPACK	1
#endif
#endif

#ifdef RADPACK
#pragma pack(1)
#endif

#define TRUE    1
#define FALSE   0
#define EOS     '\0'

typedef double   ads_real;
typedef ads_real ads_point[3];
typedef long     ads_name[2];
typedef ads_real ads_matrix[4][4];

/* To protect macro-redefinition of the X, Y, Z, and T enumerated
   constants by legacy #define's, we remove their definition. */

#ifdef X
#undef X
#endif
#ifdef Y
#undef Y
#endif
#ifdef Z
#undef Z
#endif
#ifdef T
#undef T
#endif

#ifndef _XYZT_DEFINED
#define _XYZT_DEFINED
enum { X = 0, Y = 1, Z = 2 }; /* The coordinates of a point. */
enum { T = 3 };               /* The translation vector of a 3D matrix */
#endif // !_XYZT_DEFINED

/* The PAUSE token for ads_command and ads_cmd
 */
#define PAUSE "\\"

/* The ADS_INITGET control bits
 */

#define RSG_NONULL 0x01   /* Disallow null input */
#define RSG_NOZERO 0x02   /* Disallow zero input */
#define RSG_NONEG  0x04   /* Disallow negative input */
#define RSG_NOLIM  0x08   /* Do not check limits */
#define RSG_GETZ   0x10   /* Get Z coordinate */
#define RSG_DASH   0x20   /* Draw dashed rubber band/box (not a GEDIT control bit) */
#define RSG_2D     0x40   /* Restrict (getdist) to 2D (causes the
                             UD_GETZ control bit to be cleared) */
#define RSG_OTHER  0x80   /* Return input string if unknown */

/* Binary data stream structure
 */

struct ads_binary {    /* Binary data chunk structure */
    short clen;        /* length of chunk in bytes */
    char *buf;         /* binary data */
};

/*  Union for storing different ADS data types.
 */
 
union ads_u_val {
   ads_real rreal;
   ads_real rpoint[3];
   short rint;
   char *rstring;
   long rlname[2];
   long rlong;   
   struct ads_binary rbinary;
/* TEMPORARY probably, for internal use only at the moment */
   unsigned char ihandle[8];
}; 
 
/* The following is the structure definition of the general result buffer.
   This is used for both passing back results from functions, as well
   as exotic applications like entity lists, and command function lists.
   It is as close as we come to the AutoLISP node structure.
 */
struct resbuf {                                                  
        struct resbuf *rbnext; /* Allows them to be "linked" */
        short restype;
        union ads_u_val resval;
};

typedef struct resbuf *pResbuf;
typedef const struct resbuf *kpResbuf;  /* for declarations */

#ifdef RADPACK
#pragma pack( )
#endif

#endif
