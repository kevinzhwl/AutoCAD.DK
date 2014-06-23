#ifndef AMODELER_INC_MASSERT_H
#define AMODELER_INC_MASSERT_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
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
// DESCRIPTION:
//
// Our own assert function. We can set a break point inside the assertFunction
// so that the execution will stop just before the assertion kills the process 
// and we can investigate all variables at that point. We can also choose not 
// to kill the process at that time.
//
///////////////////////////////////////////////////////////////////////////////

AMODELER_NAMESPACE_BEGIN


#ifndef NDEBUG

#define MASSERT(x) AModeler::assertFunction(x, __FILE__, __LINE__, #x)

#define FAIL       AModeler::assertFunction(0, __FILE__, __LINE__, "FAIL")
#define TODO       AModeler::assertFunction(0, __FILE__, __LINE__, "TODO")

#else

#define MASSERT(x)
#define FAIL
#define TODO

#endif


DllImpExp extern void assertFunction(int ex, char* file, int line, char* str = 0);


AMODELER_NAMESPACE_END
#endif






