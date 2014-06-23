#ifndef AD_DBXUTIL_H
#define AD_DBXUTIL_H 1
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
// DESCRIPTION: Header for homeless utilities exported to the API.
//
// The following functions are used to handle string values returned
// to from (or passed into) the acdb API.  newString() is analogous
// to strdup() except that it uses new instead of malloc() and it
// returns an error status.  updString() performs the same job as
// new string except that it first frees any string already pointed
// to by the output argument.  delString() uses delete to free up
// a string if the input pointer is non NULL and then sets the
// pointer to NULL.
//
// Yes, of course a decent string class would be better.

#include "acdb.h"

extern Acad::ErrorStatus newBuffer(char *&pOutput, int size);
extern Acad::ErrorStatus newString(const char* pInput, char*& pOutput);
extern Acad::ErrorStatus updString(const char* pInput, char*& pOutput);
extern void              delString(char*& pString);
#define delBuffer(x)     delString(x)
extern Acad::ErrorStatus newAcDbBuffer(char *&pOutput, int size);
extern Acad::ErrorStatus newAcDbString(const char* pInput, char*& pOutput);
extern Acad::ErrorStatus freeAcDbBuffer(void *pBuffer);
extern Acad::ErrorStatus freeAcDbString(char*& szString);

#endif
