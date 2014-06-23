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
// UTIL.CPP 
//
// DESCRIPTION:
//
// This file contains utility routines needed for implementing 
// rx sample app - POLY.


#include "assert.h"
#include "math.h"
#include "adslib.h"

#include "gepnt3d.h"
#include "gearc2d.h"
#include "gearc3d.h"

#include "dbspline.h"
#include "dbents.h"
#include "dbsymtb.h"

#include "poly.h"
#include "util.h"





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

//
// The following six routines map points and vectors among
// combinations of world, user, and entity coordinate systems.
// 
// In all cases, the Boolean "vec" should be true if the conversion
// is supposed to treat the arguments as vectors, false if they
// are to be treated as points.
//



// transform world point p into ucs point q

Adesk::Boolean 
rx_wc2uc(ads_point p, ads_point q, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RTSHORT;
    rbto.restype = RTSHORT;
    rbfrom.resval.rint = 0;     // from world
    rbto.resval.rint = 1;       // to ucs
    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"world (%f, %f, %f) maps to ucs (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Transform world point p into ecs point q defined by extrusion norm

Adesk::Boolean 
rx_wc2ec(ads_point p, ads_point q, ads_point norm, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RTSHORT;
    rbfrom.resval.rint = 0;             // from world

    rbto.restype = RT3DPOINT;
    rbto.resval.rpoint[X] = norm[X];    // to ecs
    rbto.resval.rpoint[Y] = norm[Y];
    rbto.resval.rpoint[Z] = norm[Z];

    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"world (%f, %f, %f) maps to ecs (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Transform ucs point p into world point q

Adesk::Boolean 
rx_uc2wc(ads_point p, ads_point q, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RTSHORT;
    rbto.restype = RTSHORT;
    rbfrom.resval.rint = 1;     // from ucs
    rbto.resval.rint = 0;       // to world
    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"ucs (%f, %f, %f) maps to world (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Transform ucs point p into ecs point q defined by extrusion vec

Adesk::Boolean 
rx_uc2ec(ads_point p, ads_point q, ads_point norm, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RTSHORT;
    rbfrom.resval.rint = 1;             // from ucs

    rbto.restype = RT3DPOINT;
    rbto.resval.rpoint[X] = norm[X];    // to ecs
    rbto.resval.rpoint[Y] = norm[Y];
    rbto.resval.rpoint[Z] = norm[Z];

    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"ucs (%f, %f, %f) maps to ecs (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Transform ecs point p defined by extrusion norm into world point q

Adesk::Boolean 
rx_ec2wc(ads_point p, ads_point q, ads_point norm, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RT3DPOINT;
    rbfrom.resval.rpoint[X] = norm[X];  // from ecs
    rbfrom.resval.rpoint[Y] = norm[Y];
    rbfrom.resval.rpoint[Z] = norm[Z];

    rbto.restype = RTSHORT;
    rbto.resval.rint = 0;               // to world

    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"ecs (%f, %f, %f) maps to world (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Transform ecs point p defined by extrusion norm into ucs point q

Adesk::Boolean 
rx_ec2uc(ads_point p, ads_point q, ads_point norm, Adesk::Boolean vec)
{
    struct resbuf rbfrom, rbto;
    int status;

    rbfrom.restype = RT3DPOINT;
    rbfrom.resval.rpoint[X] = norm[X];  // from ecs
    rbfrom.resval.rpoint[Y] = norm[Y];
    rbfrom.resval.rpoint[Z] = norm[Z];

    rbto.restype = RTSHORT;
    rbto.resval.rint = 1;               // to ucs

    status = ads_trans(p, &rbfrom, &rbto, vec, q);
    if (status != RTNORM)
        return FALSE;
#ifdef DEBUG
    ads_printf(/* NT */"ecs (%f, %f, %f) maps to ucs (%f, %f, %f)\n",
        p[X], p[Y], p[Z], q[X], q[Y], q[Z]);
#endif
    return TRUE;
}


// Create a matrix reflecting current ucs

Adesk::Boolean 
rx_ucsmat(AcGeMatrix3d& mat)
{
    AcGeVector3d x, y, z;
    AcGePoint3d t;

    struct resbuf rb;
    int status;

    mat.setToIdentity();

// CT!  Translate the next string ONLY if AutoCAD system variables
//      are translated

    status = ads_getvar("UCSORG", &rb);
    if (status != RTNORM)
        return FALSE;
    if(rb.restype != RT3DPOINT)
        ads_printf("UCSORG not a point.\n");
    t[X] = rb.resval.rpoint[X];
    t[Y] = rb.resval.rpoint[Y];
    t[Z] = rb.resval.rpoint[Z];

// CT!  Translate the next string ONLY if AutoCAD system variables
//      are translated

    status = ads_getvar("UCSXDIR", &rb);
    if (status != RTNORM)
        return FALSE;
    if(rb.restype != RT3DPOINT)
        ads_printf("UCSXDIR not a point.\n");
    x[X] = rb.resval.rpoint[X];
    x[Y] = rb.resval.rpoint[Y];
    x[Z] = rb.resval.rpoint[Z];

// CT!  Translate the next string ONLY if AutoCAD system variables
//      are translated

    status = ads_getvar("UCSYDIR", &rb);
    if (status != RTNORM)
        return FALSE;
    if(rb.restype != RT3DPOINT)
        ads_printf("UCSYDIR not a point.\n");
    y[X] = rb.resval.rpoint[X];
    y[Y] = rb.resval.rpoint[Y];
    y[Z] = rb.resval.rpoint[Z];

    z = x.crossProduct(y);

    mat.setCoordSystem(t, x, y, z);

    return TRUE;
}




//*************************************************************************
// Database related utility routines 
//*************************************************************************


Acad::ErrorStatus 
postToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return postToDb(ent, objId);
}


Acad::ErrorStatus 
postToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    if ((es = pSpaceRecord->close()) != Acad::eOk) {
        return es;
    }

    return ent->close();
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent)
//
//  Append specified entity to current space of current drawing.
//
{
    AcDbObjectId objId;

    return addToDb(ent, objId);
}


Acad::ErrorStatus 
addToDb(AcDbEntity* ent, AcDbObjectId& objId)
{

    Acad::ErrorStatus      es;
    AcDbBlockTable*        pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;

    if ((es = acdbCurDwg()->getBlockTable(pBlockTable, AcDb::kForRead))
           != Acad::eOk) {
        return es;
    }

    if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, 
                                 pSpaceRecord,
                                 AcDb::kForWrite)) != Acad::eOk) {
        return es;
    }


    if ((es = pBlockTable->close()) != Acad::eOk) {
        return es;
    }
    if ((es = pSpaceRecord->appendAcDbEntity(objId, ent)) != Acad::eOk) {
        return es;
    }

    return pSpaceRecord->close();
}


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

    rx_ec2wc(asDblArray(center), asDblArray(center), asDblArray(entNorm), 
							    Adesk::kFalse);
    rx_ec2wc(asDblArray(startPnt), asDblArray(startPnt), asDblArray(entNorm), 
							    Adesk::kFalse);
    rx_ec2wc(asDblArray(endPnt), asDblArray(endPnt), asDblArray(entNorm), 
							    Adesk::kFalse);
    rx_ec2wc(asDblArray(norm), asDblArray(norm), asDblArray(entNorm), 
							    Adesk::kTrue);

    arc.set(center, norm, norm.perpVector(),
	(startPnt - center).length(), 0, incAng);

    return es;
}


// Given the name of a text style, look up that name and
// return the db id of the TextStyleTableRecord.
//
Acad::ErrorStatus 
rx_getTextStyleId(const char         *styleName,
                        AcDbDatabase *db,
                        AcDbObjectId &styleId)
{
    AcDbTextStyleTable *pStyleTable;
    Acad::ErrorStatus es = db->getTextStyleTable(
                              pStyleTable, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pStyleTable->getAt(styleName, styleId, Adesk::kFalse);
        pStyleTable->close();
    }
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
        char *tmpStr;
        if ((es = oldStyle->fileName(tmpStr)) != Acad::eOk) {
            oldStyle->close();
            return es;
        }
        newStyle.setFileName(tmpStr);
        delete tmpStr;

        if ((es = oldStyle->bigFontFileName(tmpStr)) != Acad::eOk) {
            oldStyle->close();
            return es;
        }
        newStyle.setBigFontFileName(tmpStr);
        delete tmpStr;

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
