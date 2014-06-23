#ifndef AC_BRGBLABB_H
#define AC_BRGBLABB_H 1
// (C) Copyright 1995-1997 by Autodesk, Inc.
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
// BRGBLABB.H:  
//
// DESCRIPTION:
//
// This file contains abbreviated definitions for the Autodesk Boundary
// Representation library, as defined in brgbl.h.
//
// Using the fully qualified names from the "AcBr" struct can be
// cumbersome. If there are no global name conflicts use the following
// synonyms for convenience.
//
// Note:  All interface descriptions must use fully qualified names.
//        That is, header files MUST NOT include this file and MUST
//        NOT use these abbreviations.
//
// Note:  If any of the following abbreviations cause conflicts and
//        this file cannot be included, then the acceptable abbreviations
//        (those that do not cause conflicts) will have to be manually
//        introduced, or another abbreviation header file will have to
//        be created containing only the acceptable abbreviations.
//
// Note:  When this file is included in a source file, it MUST BE
//        included AFTER all other include files (except possibly
//        other abbreviation include files).
//        For example:
//            #include "adesk.h"
//            #include "brgbl.h"
//            #include "foo.h"
//            #include "bar.h"
//            #include "adeskabb.h"
//            #include "brgblabb.h" // <- Must be last!
//
// Note:  This abbreviation file cannot coexist with acdbabb.h or
//        any other abbreviation file that abbreviates error codes.


#include "brgbl.h"


typedef AcBr::ErrorStatus AcBrErrorStatus;
typedef AcBr::Relation    AcBrRelation;


const AcBr::ErrorStatus eOk                 = AcBr::eOk;
const AcBr::ErrorStatus eNotImplementedYet  = AcBr::eNotImplementedYet;
const AcBr::ErrorStatus eNotApplicable      = AcBr::eNotApplicable;
const AcBr::ErrorStatus eInvalidInput       = AcBr::eInvalidInput;
const AcBr::ErrorStatus eOutOfMemory        = AcBr::eOutOfMemory;
const AcBr::ErrorStatus eNullObjectPointer  = AcBr::eNullObjectPointer;
const AcBr::ErrorStatus eWrongObjectType    = AcBr::eWrongObjectType;
const AcBr::ErrorStatus eWrongSubentityType = AcBr::eWrongSubentityType;
const AcBr::ErrorStatus eBrepChanged        = AcBr::eBrepChanged;
const AcBr::ErrorStatus eNullObjectId       = AcBr::eNullObjectId;
const AcBr::ErrorStatus eNullSubentityId    = AcBr::eNullSubentityId;
const AcBr::ErrorStatus eObjectIdMismatch   = AcBr::eObjectIdMismatch;
const AcBr::ErrorStatus eTopologyMismatch   = AcBr::eTopologyMismatch;
const AcBr::ErrorStatus eUnsuitableTopology = AcBr::eUnsuitableTopology;
const AcBr::ErrorStatus eUnsuitableGeometry = AcBr::eUnsuitableGeometry;
const AcBr::ErrorStatus eMissingTopology    = AcBr::eMissingTopology;
const AcBr::ErrorStatus eMissingGeometry    = AcBr::eMissingGeometry;
const AcBr::ErrorStatus eMissingSubentity   = AcBr::eMissingSubentity;
const AcBr::ErrorStatus eInvalidObject		= AcBr::eInvalidObject;
const AcBr::ErrorStatus eAmbiguousOutput    = AcBr::eAmbiguousOutput;


#endif
