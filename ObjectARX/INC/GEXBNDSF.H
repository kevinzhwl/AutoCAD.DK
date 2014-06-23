#ifndef AC_GEXBNDSF_H
#define AC_GEXBNDSF_H
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
// Description:
//
// This files implements the AcGeExternalBoundedSurface class,
// which is a representation of the geometry associated with a
// face entity.
//

#include "gegbl.h"
#include "gesurf.h"

class AcGeExternalSurface;
class AcGeCurveBoundary;

class
#ifdef AC_GEXBNDSF_CPP
GE_DLLEXPORT
#elif !defined(ACGE_XENTLIB)
GE_DLLIMPORT
#endif
AcGeExternalBoundedSurface : public AcGeSurface
{
public:
   AcGeExternalBoundedSurface();
   AcGeExternalBoundedSurface(void* surfaceDef, AcGe::ExternalEntityKind,
                              Adesk::Boolean makeCopy = Adesk::kTrue);
   AcGeExternalBoundedSurface(const AcGeExternalBoundedSurface&);

   // Surface data.
   //
   AcGe::ExternalEntityKind   externalSurfaceKind  () const;
   Adesk::Boolean             isDefined            () const;
   void                       getExternalSurface   (void*&) const;

    // Access to unbounded surface.
    //
    void getBaseSurface        (AcGeExternalSurface&) const;

         // Access to the boundary data.
    //
    int          numContours  () const;
    void         getContours  (int&, AcGeCurveBoundary*&) const;

    // Set methods
    //
    AcGeExternalBoundedSurface& set  (void* surfaceDef,
                                      AcGe::ExternalEntityKind,
                                      Adesk::Boolean makeCopy = Adesk::kTrue);

    // Assignment operator.
    //
    AcGeExternalBoundedSurface& operator = (const AcGeExternalBoundedSurface&);

    // Surface ownership.
    //
        Adesk::Boolean               isOwnerOfSurface() const;
    AcGeExternalBoundedSurface&  setToOwnSurface();
};

#endif
