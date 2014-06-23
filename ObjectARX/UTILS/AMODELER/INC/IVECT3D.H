#ifndef AMODELER_INC_IVEC3D_H
#define AMODELER_INC_IVEC3D_H


///////////////////////////////////////////////////////////////////////////////
//
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
//  Declares class IntVector3d keeping a 3D vector in integer space.
//
///////////////////////////////////////////////////////////////////////////////

#include "global.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp IntVector3d
{
public:

    // Note: No default constructor
    IntVector3d(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}

    IntVector3d operator  +(IntVector3d v) const { return IntVector3d(x+v.x, y+v.y, z+v.z); }
    IntVector3d operator  -(IntVector3d v) const { return IntVector3d(x-v.x, y-v.y, z-v.z); }

    int         operator [](int index)     const { return (&x)[index]; }
    int&        operator [](int index)           { return (&x)[index]; }

    bool        operator ==(IntVector3d v) const { return x == v.x && y == v.y && z == v.z; }
    bool        operator !=(IntVector3d v) const { return !(*this == v); }

    void        operator +=(IntVector3d v)       { x += v.x; y += v.y; z += v.z; }
    void        operator -=(IntVector3d v)       { x -= v.x; y -= v.y; z -= v.z; }
        
    // Public data members
    //
    int x, y, z;

};  // Class IntVector3d


AMODELER_NAMESPACE_END
#endif
