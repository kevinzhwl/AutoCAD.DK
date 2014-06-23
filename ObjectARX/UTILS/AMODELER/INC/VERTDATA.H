#ifndef AMODELER_INC_VERTDATA_H
#define AMODELER_INC_VERTDATA_H


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
// Polygons are used as input to sweep operations.
//
// Each polygon may have PolygonVertexData attributes attached to its vertices. 
// We call such polygons "augmented polygons." The type of the attached 
// PolygonVertexData object may be:
// 
//    kArc3d         ...  There is an arc between this polygon vertex and the 
//                        next one. The Circle3d object and the approximation
//                        are given as parameters to the constructor when 
//                        creating the PolygonVertexData object.
//                        
//                        To represent a full circle, use an augmented polygon  
//                        containing just a single vertex with a kArc3d 
//                        PolygonVertexData object. 
//
//    kArcByRadius   ...  There is an arc between this polygon vertex and the
//                        next one. The radius or the arc and the approximation
//                        are given as parameters to the constructor when creating
//                        the PolygonVertexData object. Radius > 0 means CCW, < 0 
//                        means CW orientation of the arc with reference to the
//                        polygon normal. The isCenLeft argument tells whether the
//                        center of the arc lies to the left from the edge of the
//                        polygon (in other words, it is inside the polygon). The 
//                        default is "true."
//
//    kArcByBulge    ...  There is an arc between this polygon vertex and the
//                        next one. The bulge and the approximation are given 
//                        as parameters to the constructor when creating the
//                        PolygonVertexData object.
//
//    kFilletByRadius ... The polygon vertex is filleted. The filleting radius 
//                        and the approximation are given as parameters to the
//                        constructor when creating the PolygonVertexData object.
//
// Any operation which accepts polygons first expands the augmented polygon
// to a simple polygon by generating additional vertices approximating the
// arcs, as defined by the PolygonVertexData objects.
//
// Note: The kArcByRadius and kArcByBulge options cannot be used when the 
//       polygon is used as a path for the extrusion along the path because  
//       the path may be non-planar and the polygon normal may not be defined.
//
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// NOTE: In the previous version of AModeler, the PolygonVertexData was 
//       related to the segment coming TO the current vertex. 
//
//       This has changed: Now the PolygonVertexData relates to the segment 
//       coming FROM the current vertex.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
///////////////////////////////////////////////////////////////////////////////

#include "circle3d.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp PolygonVertexData
{
public:

    enum Type { kArc3d, kArcByRadius, kArcByBulge, kFilletByRadius };

    PolygonVertexData(Type, const Circle3d&, int apprx);             // kArc3d
    PolygonVertexData(Type, double rad, bool isCenLeft, int apprx);  // kArcByRadius
    PolygonVertexData(Type, double bulgeOrRadius, int apprx);        // kArcByBulge or kFilletByRadius

    Type     type;
    Circle3d circle;
    int      approx;
    bool     isCenterLeft;
    double   bulge;
    Curve*   curve;
    Surface* surface;

}; // class PolygonVertexData


AMODELER_NAMESPACE_END
#endif
