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
//  DESCRIPTION:
//
//  This header file contains general-purpose memory allocation
//  functions.  They are deprecated in favor of newBuffer, freeBuffer,
//  etc. declared in acutmem.h.

#ifndef _ACMEM_H
#define _ACMEM_H

#include <stddef.h>
#include "AdAChar.h"

#pragma pack (push, 8)

#ifdef __cplusplus
extern "C" {
#endif

void  *acad_malloc  (size_t size);
void   acad_free    (void *p);
size_t acad__msize  (void *p);
void  *acad_realloc (void *p, size_t size);
void  *acad_calloc  (size_t num, size_t size);
ACHAR *acad__strdup (const ACHAR *p);

#ifdef __cplusplus
} // "C"
#endif

#pragma pack (pop)
#endif // _ACMEM_H
