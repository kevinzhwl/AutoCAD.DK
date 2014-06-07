#ifndef _ACUTMEM_H
#define _ACUTMEM_H
//
//
//  acutmem.h - General memory allocation functions.
//
// (C) Copyright 1998-1999-2005 by Autodesk, Inc. 
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
//  DESCRIPTION:
//
//  The following functions are used to handle string values and memory
//  returned to or from (or passed into) the ObjectARX API.  Function
//  acutNewString() makes a copy of a string and returns an error status.
//  Function acutUpdString() performs the same job as acutNewString(),
//  except that it first frees any string already pointed to by the
//  output argument.  acutDelString() frees up a string allocated by
//  acutNewString() or acutUpdString() if the input pointer is non
//  NULL and then sets the pointer to NULL.
//

#include <stddef.h>
#include "acadstrc.h"
#include "AdAChar.h"

#pragma pack (push, 8)

Acad::ErrorStatus acutNewBuffer(ACHAR *&pOutput, size_t size);
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);
Acad::ErrorStatus acutUpdString(const ACHAR* pInput, ACHAR*& pOutput);
void              acutDelString(ACHAR*& pString);

inline void
acutDelBuffer(ACHAR*& pString)
{ acutDelString(pString); }

#pragma pack (pop)
#endif // _ACUTMEM_H
