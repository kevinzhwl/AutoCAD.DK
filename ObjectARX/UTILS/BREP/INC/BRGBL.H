#ifndef AC_BRGBL_H
#define AC_BRGBL_H 1
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
// DESCRIPTION:
//
// The AcBr struct contains definitions for the Autodesk Boundary
// Representation library, which are shared between internal and
// 3rd-party developers.
//
// This struct holds error codes that are specific to AcBr, using
// a starting base of 3000 so as not to conflict with AutoCAD, the
// Mechanical API or the Mechanical Desktop.
//
// Also included is an enum field for relation of bounded geometry
// to topology (e.g., point in solid, curve on face). The kInside
// and kOutside values are relative to the object's boundary.


#include "adesk.h"


struct AcBr
{
    enum ErrorStatus    { eOk                   = 0,
                          eNotImplementedYet    = 3001,
                          eNotApplicable        = 3002,
                          eInvalidInput         = 3003,
                          eOutOfMemory          = 3004,
                          eNullObjectPointer    = 3005,
                          eWrongObjectType      = 3006,
                          eWrongSubentityType   = 3007,
                          eBrepChanged          = 3008,
                          eNullObjectId         = 3009,
                          eNullSubentityId      = 3010,
                          eObjectIdMismatch     = 3011,
                          eTopologyMismatch     = 3012,
                          eUnsuitableTopology   = 3013,
                          eUnsuitableGeometry   = 3014,
                          eMissingTopology      = 3015,
                          eMissingGeometry      = 3016,
						  eMissingSubentity		= 3017,
						  eInvalidObject        = 3018,
						  eAmbiguousOutput		= 3019
                        };

    enum Relation       { kUnknown              = 0,
                          kOutside              = 1,
                          kInside               = 2,
                          kBoundary             = 3,	// for point relation; curve relation returns kInside
                          kCoincident           = 4,	// obsolete; now returns kInside
                          kTangent              = 5,	// obsolete; now returns kUnknown
                          kIntersect            = 6		// obsolete; now returns kUnknown
                        };
};


#endif

