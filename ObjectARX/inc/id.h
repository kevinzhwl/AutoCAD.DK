//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef   _ID_H
#define   _ID_H

/*              ID.H

    Define AutoCAD version numbers       

    !!! IMPORTANT !!! IMPORTANT !!! IMPORTANT !!!

        Text-filtering scripts process this file to extract the version
        information.  You should only change the values for the ACADV_*,
        ACADVFULL, and ACADVNUM macros.

        DO NOT MAKE OTHER CHANGES TO THIS FILE.

    The ACADV_* macros below have the following valid ranges. 
    They implement a specific naming convention (see R160BPLT1 for
    details).  Changing the naming convention will require changing
    IDVER.H, which depends on these ACADV_* values.
    (The ranges that include letters are case-sensitive.)

    !!! All numbers need to be expressed as decimal numbers.
        Not octal, 03, and not hexadecimal, 0x03.

    ACADV_RELMAJOR  a nonnegative number, e.g., 13, 14, 15.
    ACADV_RELMINOR  0 .. 9
    
    ACADV_BLDSTREAM A .. Z
    ACADV_BLDMAJOR  0 .. 9 .. 99
    ACADV_BLDMINOR  0 .. 9 .. 99
    

 */

#define ACADV_RELMAJOR  19 /*ReleaseMajor*/
#define ACADV_RELMINOR  1  /*ReleaseMinor*/

#define ACADV_BLDSTREAM I   /*BuildStream*/
#define ACADV_BLDMAJOR  18   /*BuildMajor*/
#define ACADV_BLDMINOR  0   /*BuildMinor*/
#define ACADV_BLDBRANCH 0   //BuildBranch


/* The ASM_ values below should be updated whenever we get a new ASM drop.
   Check the File Version and Product Version on any asm dll. */
#define ASM_FILE_RELMAJOR  219
#define ASM_FILE_RELMINOR  0
#define ASM_FILE_RELPOINT  0
#define ASM_FILE_RELPATCH  5600
#define ASM_PROD_RELMAJOR  219
#define ASM_PROD_RELMINOR  0
#define ASM_PROD_RELPOINT  0
#define ASM_PROD_RELPATCH  5600
#endif /* _ID_H */
