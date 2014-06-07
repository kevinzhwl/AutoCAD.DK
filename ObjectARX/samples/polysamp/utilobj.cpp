// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// UTILOBJ.CPP 
//
// DESCRIPTION:
//
// This file contains utility routines needed for implementing 
// rx sample app - POLY.


#include "assert.h"
#include "math.h"

#include "gepnt3d.h"
#include "gearc2d.h"
#include "gearc3d.h"

#include "dbspline.h"
#include "dbents.h"
#include "dbsymtb.h"

#include "poly.h"
#include "util.h"

#include "dbxutil.h"

#include "dbapserv.h"


// Return integer part of number.  Truncates towards 0 

double 
aint(double x)
{
    long l;

    // Note that this routine cannot handle the full floating point
    // number range.  This function should be in the machine-dependent
    // floating point library!

    l = long(x);
    if ((int) (-0.5) != 0 && l < 0)
        l++;
    x = l;
    return x;
}


// Range reduce angle to 0 <= angle < 2 * PI 

double 
rx_fixangle(double angle)
{
    return angle - (2 * 3.14159265358979323846) * aint((angle / (2 * 3.14159265358979323846)) -
                     (angle < 0.0));
}

void 
rx_fixindex(int& index, int maxIndex)
{
    if (index > maxIndex)
	index -= maxIndex;

    if (index < 0)
	index += maxIndex;
}


//*************************************************************************
// Database related utility routines 
//*************************************************************************


Acad::ErrorStatus 
rx_scanPline(AcDb2dPolyline*        pline,
             AcGePoint3dArray&      points,
             AcGeDoubleArray&       bulges)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcDb2dVertex*  vert   = NULL;
    AcDbObjectId   vId;

    AcDbObjectIterator *vIter;
    vIter = pline->vertexIterator();

    for (; !vIter->done(); vIter->step()) {
	vId = vIter->objectId();

	AOK(pline->openVertex(vert, vId, AcDb::kForRead));

	points.append(vert->position());
	bulges.append(vert->bulge());
    }

    delete vIter;
    
    return es;
}


Acad::ErrorStatus 
rx_scanPline(AcDb3dPolyline* pline, AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcDb3dPolylineVertex*  vert   = NULL;
    AcDbObjectId           vId;

    AcDbObjectIterator *vIter;
    vIter = pline->vertexIterator();

    for (; !vIter->done(); vIter->step()) {
	vId = vIter->objectId();

	AOK(pline->openVertex(vert, vId, AcDb::kForRead));

	points.append(vert->position());
    }

    delete vIter;
    
    return es;
}


Acad::ErrorStatus 
rx_makeArc(const AcGePoint3d    pt1, 
           const AcGePoint3d    pt2, 
                 double         bulge,
           const AcGeVector3d   entNorm,
                 AcGeCircArc3d& arc)
{
    Acad::ErrorStatus es = Acad::eOk;

    // The points that are coming in are in ECS. These are actually
    // 2d points, may be with an elevation in the z coord.
    //
    // Therefore, let's create a 2d arc from these values and transform
    // the relevant data of the arc for creating a 3d arc.

    AcGeCircArc2d arc2d;
    AcGePoint2d p1, p2;

    assert(fabs(pt1[Z] - pt2[Z]) < 1.0e-10);

    p1.set(pt1[X], pt1[Y]); p2.set(pt2[X], pt2[Y]);
    arc2d.set(p1, p2, bulge);

    AcGePoint3d center((arc2d.center())[X], (arc2d.center())[Y], pt1[Z]);
    AcGePoint3d startPnt((arc2d.startPoint())[X], 
                         (arc2d.startPoint())[Y], pt1[Z]);
    AcGePoint3d endPnt((arc2d.endPoint())[X], (arc2d.endPoint())[Y], pt1[Z]);

    // If the arc is CW, flip the normal.

    AcGeVector3d norm;

    if (arc2d.startAng() > arc2d.endAng()) {
	norm.set(0, 0, -1);
    } else {
	norm.set(0, 0, 1);
    }

    double incAng = fabs(arc2d.endAng() - arc2d.startAng());

    // Transform all the data to WCS.

    acdbEcs2Wcs(asDblArray(center), asDblArray(center), asDblArray(entNorm), 
							    Adesk::kFalse);
    acdbEcs2Wcs(asDblArray(startPnt), asDblArray(startPnt), asDblArray(entNorm), 
							    Adesk::kFalse);
    acdbEcs2Wcs(asDblArray(endPnt), asDblArray(endPnt), asDblArray(entNorm), 
							    Adesk::kFalse);
    acdbEcs2Wcs(asDblArray(norm), asDblArray(norm), asDblArray(entNorm), 
							    Adesk::kTrue);

    arc.set(center, norm, norm.perpVector(),
	(startPnt - center).length(), 0, incAng);

    return es;
}


// Get an AcGiTextStyle from an AcDbTextStyleTableRecord.
// Try to map as many characteristics as we can.
//
Acad::ErrorStatus
rx_getTextStyle(AcGiTextStyle &newStyle, AcDbObjectId styleId)
{
    AcDbTextStyleTableRecord *oldStyle;
    Acad::ErrorStatus es = acdbOpenAcDbObject((AcDbObject *&)oldStyle,
                             styleId, AcDb::kForRead);
    if (es == Acad::eOk) {
        const char *tmpStr;
        if ((es = oldStyle->fileName(tmpStr)) != Acad::eOk) {
            oldStyle->close();
            return es;
        }
        newStyle.setFileName(tmpStr);

        if ((es = oldStyle->bigFontFileName(tmpStr)) != Acad::eOk) {
            oldStyle->close();
            return es;
        }
        newStyle.setBigFontFileName(tmpStr);

        newStyle.setTextSize(oldStyle->textSize());
        newStyle.setXScale(oldStyle->xScale());
        newStyle.setObliquingAngle(oldStyle->obliquingAngle());

        oldStyle->close();
        newStyle.loadStyleRec();
    }
    return es;
}

Acad::ErrorStatus rx_makeSpline(const AcGePoint3dArray&  pts,
			              AcDbSpline*&       pSpline)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGeDoubleArray knots, weights;
    for (int i = 0; i < pts.length(); i++) {
        weights.append(1.0);
    }

    getUniformKnots(pts.length(), 1, 0, knots);

    pSpline = new AcDbSpline(1, Adesk::kFalse, Adesk::kFalse,
                                Adesk::kFalse, pts, knots, weights);
 
    return es;
}

Acad::ErrorStatus
getUniformKnots(int numCtrlPts, int degree, int form, AcGeDoubleArray& knots)
{
    Acad::ErrorStatus ecode = Acad::eOk;
    int i, nspans;

    nspans = numCtrlPts - degree; 

    knots.setLogicalLength(nspans + (2*degree) + 1);

    double dt = 1.0; // (tn - t0) / n. Usually tn = n and t0 = 0

    for (i = 0; i < degree; i++) {
        if (form == 2) {
            knots[i] = -(degree - i) * dt;
        } else { 
            knots[i] = 0.0;
	}
    }

    knots[degree] = 0.0;
    for (i = degree + 1; i < nspans + degree + 1; i++) {
        knots[i] = knots[i - 1] + dt; 
    }

    for (i = 1; i <= degree; i++) {
        if (form == 2) {
            knots[nspans + degree + i] = 
		knots[nspans + degree] + i * dt;
        } else {
            knots[nspans + degree + i] = knots[nspans + degree]; 
	}
    }

    return ecode;
}
