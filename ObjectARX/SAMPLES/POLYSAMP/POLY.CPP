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
// POLY.CPP 
//
// DESCRIPTION:
//
// This file contains the body of the class AsdkPolygon.

#include <stdlib.h>

#include "assert.h"
#include "math.h"

#include "actrans.h"

#include "gepnt3d.h"
#include "gevec3d.h"
#include "gelnsg3d.h"
#include "gearc3d.h"

#include "dbents.h"
#include "dbsymtb.h"
#include "dbcfilrs.h"
#include "dbspline.h"
#include "dbproxy.h"

#include "util.h"
#include "poly.h"

#include "acdb.h"
#include "dbidmap.h"
#include "adesk.h"

// Object Version
#define VERSION 1

// extern "C" char* strdup(const char*);

//*************************************************************************
// Statics functions used in this file. 
//*************************************************************************

static Acad::ErrorStatus drawFacets(const AsdkPoly*         poly,
                                          AcGiWorldDraw*    worldDraw,
                                          AcGiViewportDraw* vportDraw);

static Acad::ErrorStatus drawEdges (const AsdkPoly*         poly,
                                          AcGiWorldDraw*    worldDraw,
                                          AcGiViewportDraw* vportDraw);

static Acad::ErrorStatus intLine   (const AsdkPoly*         poly, 
                                    const AcGeLine3d        line,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intLine   (const AsdkPoly*         poly, 
                                    const AcDbLine*         line,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intLine   (const AsdkPoly*         poly, 
                                    const AcGeLineSeg3d     line,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intArc    (const AsdkPoly*         poly, 
                                    const AcDbArc*          arc,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intArc    (const AsdkPoly*         poly, 
                                    const AcGeCircArc3d     arc,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intCircle (const AsdkPoly*         poly, 
                                    const AcDbCircle*       circle,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intCircle (const AsdkPoly*         poly, 
                                    const AcGeCircArc3d     circle,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intPline  (const AsdkPoly*         poly, 
                                          AcDb2dPolyline*   pline,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus intPline  (const AsdkPoly*         poly, 
                                          AcDb3dPolyline*   pline,
                                          AcDb::Intersect   intType,
                                    const AcGePlane*        projPlane,
                                          AcGePoint3dArray& points);

static Acad::ErrorStatus drawName(const AsdkPoly*           poly,
                                        AcGiWorldDraw*      worldDraw);


//*************************************************************************
// Code for the Class Body. 
//*************************************************************************


ACRX_DXF_DEFINE_MEMBERS(AsdkPoly, AcDbCurve,
AcDbProxyEntity::kAllAllowedBits, POLYGON, 
"AsdkPolyCAD\
|Product Desc:     PolyCAD ARX App For Polygon Entity\
|Company:          Autodesk,Inc.\
|WEB Address:      www.autodesk.com");
       

//*************************************************************************
// Constructors and destructors 
//*************************************************************************

AsdkPoly::AsdkPoly()
{
    mCenter.set(0.0, 0.0, 0.0);
    mStartPoint.set(0.0, 0.0, 0.0);
    mNumSides = 0;
    mPlaneNormal.set(0.0, 0.0, 1.0);
    mTextStyle = AcDbObjectId::kNull;
    mpName = NULL;
}

AsdkPoly::AsdkPoly(const AcGePoint3d&   center,
                   const AcGePoint3d&   startPoint,
                         int            numSides, 
                   const AcGeVector3d&  normal,
                   const char*          name)
{
    mCenter        = center;
    mStartPoint    = startPoint;
    mNumSides      = numSides;
    mPlaneNormal   = normal;
    mpName         = strdup(name);
    mTextStyle     = AcDbObjectId::kNull;
}

AsdkPoly::AsdkPoly(const AcGePoint3d&   center,
                   const AcGePoint3d&   startPoint,
                         int            numSides, 
                   const AcGeVector3d&  normal,
                   const char*          name,
                         AcDbObjectId   styleId)
{
    mCenter        = center;
    mStartPoint    = startPoint;
    mNumSides      = numSides;
    mPlaneNormal   = normal;
    mpName         = strdup(name);
    mTextStyle     = styleId;
}

AsdkPoly::~AsdkPoly()
{
    if (mpName != NULL)
        delete mpName;
}


//*************************************************************************
// Methods specific to AsdkPoly 
//*************************************************************************

const char*
AsdkPoly::name() const
{
    assertReadEnabled();
    return (mpName == NULL) ? "" : mpName;
}

AcDbObjectId
AsdkPoly::styleId() const
{
    assertReadEnabled();
    return mTextStyle;
}


Acad::ErrorStatus
AsdkPoly::setName(const char* pName)
{
    assertWriteEnabled();
    
    if (mpName != NULL)
    {
        delete mpName;
        mpName = NULL;
    }

    if(pName != NULL)
    {
        mpName = strdup(pName);
    }

    return Acad::eOk;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus  
AsdkPoly::setNumSides(int numSides)    
{
    if (mNumSides == numSides)
        return Acad::eOk;

    assertWriteEnabled(Adesk::kFalse, Adesk::kTrue);
    
    // There are situations under which AutoCAD doesn't
    // want to do undo recording, so it won't create an
    // undo filer. Check for the existence of the filer
    // before starting to write into it.
    //
    AcDbDwgFiler *pFiler = NULL;
    if ((pFiler = undoFiler()) != NULL) {
        undoFiler()->writeItem((long)AsdkPoly::desc());
        undoFiler()->writeItem((Adesk::Int16)kSetNumSides);
        undoFiler()->writeItem((Adesk::Int32)mNumSides);
    }

    mNumSides = numSides; 
    return Acad::eOk;
}

// END CODE APPEARING IN SDK DOCUMENT.

Acad::ErrorStatus
AsdkPoly::setTextStyle(AcDbObjectId tsId)
{
    assertWriteEnabled();
    mTextStyle = tsId;
    return Acad::eOk;
}


AcGeVector3d       
AsdkPoly::sideVector(int whichSide) const
{
    assertReadEnabled();

    AcGePoint3dArray vertexArray;
    getVertices(vertexArray);

    AcGeVector3d vec = vertexArray[whichSide + 1] - vertexArray[whichSide];
    assert(!vec.isZeroLength());
    vec.normalize();

    return vec;
}


Acad::ErrorStatus 
AsdkPoly::getCoordSys(AcGeMatrix3d& mat) const
{
    assertReadEnabled();

    AcGeVector3d x, y;

    x = mStartPoint - mCenter;
    x.normalize();
    y = mPlaneNormal.crossProduct(x);

    mat.setCoordSystem(mCenter, x, y, mPlaneNormal);

    return Acad::eOk;
}


Acad::ErrorStatus 
AsdkPoly::getVertices(AcGePoint3dArray& vertexArray) const
{
    assertReadEnabled();

    // Calculate the polygon vertices assuming the center of the 
    // polygon to be at the origin and the start point being on the
    // x axis. Then calculate a transformation between the coordinate
    // system that can be formed using the center, start point and 
    // the normal and the world. Apply the transformation to all
    // the points.
    //
    // This may not be the most efficient way of getting the points
    // as far as computation is concerned, but it sure is easy to
    // implement, and it's chosen for that reason.

    double circumRadius = (mStartPoint - mCenter).length();
    double sideLength = 2.0 * circumRadius * cos(3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides);

    AcGePoint3d vertex(circumRadius, 0.0, 0.0);
    double rotateBy, increment;
    
    vertexArray.append(vertex);
    rotateBy = increment = 2.0 * 3.14159265358979323846 / mNumSides;

    for (int i = 0; i < mNumSides - 1; i++) {
        
        vertex[X] = circumRadius * cos(rotateBy); 
        vertex[Y] = circumRadius * sin(rotateBy); 
        vertexArray.append(vertex);
        rotateBy += increment;
    }

    vertex.set(circumRadius, 0.0, 0.0);
    vertexArray.append(vertex);

    // Now calculate the transformation matrix and transform all the points.

    AcGeMatrix3d mat;
    this->getCoordSys(mat);

    for (i = 0; i < vertexArray.length(); i++) {
        vertexArray[i].transformBy(mat);
    }

    return Acad::eOk;
}


//*************************************************************************
// Overridden methods from AcDbCurve
//*************************************************************************


Acad::ErrorStatus 
AsdkPoly::getPointAtParam(double param, AcGePoint3d& point) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Find out how many included angles "param" contains.
    // Find that vertex, and the direction of the line defined
    // by that vertex and the following vertex. Add the appropriate
    // distance along that line direction to get the new point.

    rx_fixangle(param);

    double circumRadius      = (mStartPoint - mCenter).length();
    double includedAngle     = 6.28318530717958647692 / mNumSides;
    int    numIncludedAngles = int(param / includedAngle);
    double theta             = param - numIncludedAngles * includedAngle;

    double gamma             = 3.14159265358979323846 * 0.5 + 3.14159265358979323846 / mNumSides - theta;
    double distToGo          = circumRadius * sin(theta) / sin(gamma);

    AcGeVector3d lineDir     = this->sideVector(numIncludedAngles);

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    if (theta > 1.0e-10) {
        point = vertexArray[numIncludedAngles] + (distToGo * lineDir);
    } else {
        point = vertexArray[numIncludedAngles];
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getParamAtPoint(const AcGePoint3d& point, double& param) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Check to see if the point is the same as one of the vertices of
    // the polygon. If so, great. Otherwise, see if it lies in between 
    // two consecutive vertices. If neither is true, the point if
    // not on the polygon.

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }
   
    double includedAngle = 6.28318530717958647692 / mNumSides;
    double circumRadius  = (mStartPoint - mCenter).length();

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        if (point == vertexArray[i]) {
            param = i * includedAngle;
            return Acad::eOk;
        } else if (point == vertexArray[i + 1]) {
            param = (i + 1) * includedAngle;
            return Acad::eOk;
        } else {
            
            AcGeVector3d v1, v2;
            v1 = point - vertexArray[i];
            v2 = vertexArray[i + 1] - point;

            if (v2.isCodirectionalTo(v1)) {

                double alpha          = 3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides;
                double halfSideLength = circumRadius * cos(alpha);
                double delta          = atan(
                                        fabs(v1.length() - halfSideLength) /
                                        (circumRadius * sin(alpha)));

                param = v1.length() > halfSideLength ? 
                        ((i + 0.5) * includedAngle + delta)  :
                        ((i + 0.5) * includedAngle - delta);

                return Acad::eOk;
            }
        }
    }

    return Acad::ePointNotOnEntity;
}


Acad::ErrorStatus 
AsdkPoly::getDistAtParam(double param, double& dist)  const
{
    assertReadEnabled();

    rx_fixangle(param);

    double circumRadius = (mStartPoint - mCenter).length();
    double alpha        = 3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides;
    double sideLength   = 2.0 * circumRadius * cos(alpha);

    double includedAngle     = 6.28318530717958647692 / mNumSides;
    int    numIncludedAngles = int(param / includedAngle);
    double theta             = param - numIncludedAngles * includedAngle;

    if (theta > 1.0e-10) {
        dist = sideLength * numIncludedAngles +
               circumRadius * sin(theta) / sin(3.14159265358979323846 - theta - alpha);
    } else {
        dist = sideLength * numIncludedAngles;
    }

    return Acad::eOk;
}


Acad::ErrorStatus 
AsdkPoly::getParamAtDist(double dist, double& param) const 
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    double circumRadius  = (mStartPoint - mCenter).length();
    double alpha         = 3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides;
    double sideLength    = 2.0 * circumRadius * cos(alpha);

    int    numSides      = int(dist / sideLength);
    double distToGo      = dist - numSides * sideLength;

    double includedAngle = 6.28318530717958647692 / mNumSides;

    if (distToGo > 1.0e-10) {

        double delta          = atan(
                                fabs(distToGo - sideLength * 0.5) /
                                (circumRadius * sin(alpha)));
        param = distToGo > sideLength * 0.5? 
                ((numSides + 0.5) * includedAngle + delta)  :
                ((numSides + 0.5) * includedAngle - delta);

    } else {
        param = numSides * includedAngle;
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getDistAtPoint(const AcGePoint3d& point, double& dist)  const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    double param;

    if ((es = this->getParamAtPoint(point, param)) != Acad::eOk) {
        return es;
    }
    if ((es = this->getDistAtParam(param, dist)) != Acad::eOk) {
        return es;
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getPointAtDist(double dist, AcGePoint3d& point) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    double param;

    if((es = this->getParamAtDist(dist, param)) != Acad::eOk) {
        return es;
    }
    if ((es = this->getPointAtParam(param, point)) != Acad::eOk) {
        return es;
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getFirstDeriv(double param, AcGeVector3d& firstDeriv) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }
   
    double includedAngle     = 6.28318530717958647692 / mNumSides;
    int    numIncludedAngles = int(param / includedAngle);
    double theta             = param - numIncludedAngles * includedAngle;

    if (theta > 1.0e-10) {              // On a side

        firstDeriv = vertexArray[numIncludedAngles + 1] -
                     vertexArray[numIncludedAngles];
        firstDeriv.normalize();

    } else {                            // On a vertex
        return Acad::eSingularPoint;
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getFirstDeriv(const AcGePoint3d&  point, 
                              AcGeVector3d& firstDeriv) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    double param;
    if ((es = this->getParamAtPoint(point, param)) != Acad::eOk) {
        return es;
    }

    return this->getFirstDeriv(param, firstDeriv);
}


Acad::ErrorStatus 
AsdkPoly::getClosestPointTo (const AcGePoint3d&   givenPoint,
                                   AcGePoint3d&   pointOnCurve,
                                   Adesk::Boolean /*extend*/) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeLineSeg3d lnsg(vertexArray[0], vertexArray[1]);
    double dist = lnsg.distanceTo(givenPoint);
    int index = 0;

    double dist2;
    for (int i = 1; i < vertexArray.length() - 1; i++) {

        lnsg.set(vertexArray[i], vertexArray[i + 1]);
        if ((dist2 = lnsg.distanceTo(givenPoint)) < dist) {
            dist = dist2;
            index = i;
        }
    }

    lnsg.set(vertexArray[index], vertexArray[index + 1]);
    pointOnCurve = lnsg.closestPointTo(givenPoint);

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getClosestPointTo (const AcGePoint3d&   givenPoint,
                             const AcGeVector3d&  normal,
                                   AcGePoint3d&   pointOnCurve,
                                   Adesk::Boolean /*extend*/) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Project the polygon as well as the point onto a plane
    // defined by the polygon center and the normal.

    AcGePlane plane(mCenter, normal);
    AcDbCurve* curve = NULL;
    if ((es = this->getOrthoProjectedCurve(plane, curve)) != Acad::eOk) {
        return es;
    }
    assert(curve != NULL);
    AcGePoint3d pt = givenPoint.orthoProject(plane);

    // Find the nearest point on the projected curve from the
    // projected point.

    AcGePoint3d newPt;
    if ((es = curve->getClosestPointTo(pt, newPt)) != Acad::eOk) {
        return es;
    }

    // Project the point back onto the polygon.
    //
    // Define a line starting from the newPt and along the normal.
    // Intersect the polygon with that line. Find all the points
    // and pick the one closest to the given point.

    AcGePoint3dArray pts;
    AcGeLine3d line(newPt, normal);
    if ((es = intLine(this, line, pts)) != Acad::eOk) {
        return es;
    }

    pointOnCurve = pts[0];
    double length = (givenPoint - pts[0]).length();
    double length2;
    for (int i = 1; i < pts.length(); i++) {
        if ((length2 = (givenPoint - pts[i]).length()) < length) {
            pointOnCurve = pts[i];
            length = length2;
        }
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getOrthoProjectedCurve(const AcGePlane&  plane,
                                       AcDbCurve*& projectedCurve) const
{
    assertReadEnabled();

    AcGeVector3d projDir = plane.normal();
    return this->getProjectedCurve(plane, projDir, projectedCurve);
}


Acad::ErrorStatus 
AsdkPoly::getProjectedCurve(const AcGePlane&    plane,
                            const AcGeVector3d& projDir,
                                  AcDbCurve*&   projectedCurve) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // project the start point and the center and create a new polygon.
    // The normal becomes the normal of the plane.

    if (projDir.isPerpendicularTo(plane.normal()))
        return Acad::eInvalidInput;
    
    if (projDir.isPerpendicularTo(mPlaneNormal)) {

        // Poly becomes a polyline.

        AcGePoint3dArray vertexArray;
        if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
            return es;
        }

        for (int i = 0; i < vertexArray.length(); i++) {
            vertexArray[i] = vertexArray[i].project(plane, projDir);
        }
        AcDbSpline* pSpline;
        if ((es = rx_makeSpline(vertexArray, pSpline)) != Acad::eOk) {
            return es;
        }
        pSpline->setPropertiesFrom(this);

        projectedCurve = pSpline;

    } else {

        // Poly becomes another poly.

        AcGePoint3d center, startPoint;
        center = mCenter.project(plane, projDir);
        startPoint = mStartPoint.project(plane, projDir);

        AsdkPoly* newPoly = new AsdkPoly(center, startPoint, 
                                         mNumSides, plane.normal(), 
                                         mpName);

        newPoly->setPropertiesFrom(this);
        projectedCurve = newPoly;
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getOffsetCurves(double            offsetDist, 
                          AcDbVoidPtrArray& offsetCurves) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Offset distance is measured perpendicular to each side.

    double theta = 3.14159265358979323846 / mNumSides;
    double extendBy = offsetDist / cos(theta);

    AcGeVector3d x = mStartPoint - mCenter;
    x.normalize();
    x *= extendBy;

    AcGePoint3d startPt = mStartPoint + x;

    AsdkPoly* offsetPoly = new AsdkPoly(mCenter, startPt, mNumSides,
                                                 mPlaneNormal, mpName);
    assert(offsetPoly != NULL);
    offsetPoly->setPropertiesFrom(this);
    offsetCurves.append(offsetPoly);

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getSplitCurves(const AcGeDoubleArray&  parameters,
                               AcDbVoidPtrArray& curveSegments) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Since this is a closed periodic curve, the number of segemnts
    // that will result from splitting will be the same as the number
    // parameters we are splitting at. Each of the segments will be
    // a 2d polyline.

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    double param, nextParam, includedAngle = 6.28318530717958647692 / mNumSides;
    int    thisIndex, nextIndex;

    AcGePoint3dArray pts;
    AcGePoint3d   pt;

    AcDbSpline* pSpline = NULL;

    for (int i = 0; i < parameters.length(); i++) {
        
        param = parameters[i];
        if (i < parameters.length() - 1) {
            nextParam = parameters[i + 1];
        } else {
            nextParam = parameters[0];
        }

        rx_fixangle(param);
        rx_fixangle(nextParam);

        thisIndex = int(param / includedAngle) + 1;
        nextIndex = int(nextParam / includedAngle);

        double theta = nextParam - nextIndex * includedAngle;
        if (theta < 1.0e-10) {
            
            // Reduce nextIndex by one since we are going to evaluate
            // at nextParam anyway. Since integer division truncates,
            // we cannot decrement nextIndex all the time.

            nextIndex -= 1;
        }

        if (nextIndex < thisIndex)
            nextIndex += mNumSides;

        if ((es = this->getPointAtParam(param, pt)) != Acad::eOk) {
            return es;
        }
        pts.append(pt);

        int idx;
        for (int j = thisIndex; j <= nextIndex; j++) {

            idx = j;
            rx_fixindex(idx, mNumSides);
            pts.append(vertexArray[idx]);
        }
        AOK(this->getPointAtParam(nextParam, pt));
        pts.append(pt);

        AOK(rx_makeSpline(pts, pSpline));
        pSpline->setPropertiesFrom(this);
        pts.setPhysicalLength(0);
        curveSegments.append(pSpline);
    }

    return es;
}


Acad::ErrorStatus 
AsdkPoly::getSplitCurves(const AcGePoint3dArray& points,
                               AcDbVoidPtrArray& curveSegments) const
{
    assertReadEnabled();

    AcGeDoubleArray params;
    params.setLogicalLength(points.length());
    for (int i = 0; i < points.length(); i++) 
    {
        this->getParamAtPoint(points[i], params[i]);
    }

    return this->getSplitCurves(params, curveSegments);
}


Acad::ErrorStatus 
AsdkPoly::getArea(double& area) const
{
    assertReadEnabled();

    double circumRadius = (mStartPoint - mCenter).length();

    area = mNumSides * circumRadius * cos(3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides)
                     * circumRadius * sin(3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides);

    return Acad::eOk;
}


//*************************************************************************
// Overridden methods from AcDbEntity
//*************************************************************************


Acad::ErrorStatus 
AsdkPoly::getSubentPathsAtGsMarker(AcDb::SubentType     type, 
                                   int                  gsMark,
                             const AcGePoint3d&         pickPoint,
                             const AcGeMatrix3d&        viewXform,
                                   int&                 numPaths, 
                                   AcDbFullSubentPath*& subentPaths,
                                   int                  numInserts,
                                   AcDbObjectId*        entAndInsertStack) const
{
    assertReadEnabled();

    assert(numInserts == 0);
    assert(entAndInsertStack == NULL);

    numPaths    = 0;
    subentPaths = NULL;
    
    if (gsMark == 0)
        return Acad::eInvalidInput;

    switch (type) 
    {
    case AcDb::kVertexSubentType:
        if (gsMark > 0) 
        {
            numPaths       = 2;
            subentPaths    = new AcDbFullSubentPath[2];
            subentPaths[0] = AcDbFullSubentPath(objectId(), 
                                          AcDb::kVertexSubentType, gsMark - 1);
            subentPaths[1] = AcDbFullSubentPath(objectId(), 
                                          AcDb::kVertexSubentType, gsMark);
        } else {
            assert(Adesk::kFalse);
        }
        break;
        
    case AcDb::kEdgeSubentType:
        
        if (gsMark > 0) 
        {
            numPaths       = 1;
            subentPaths    = new AcDbFullSubentPath[1];
            subentPaths[0] = AcDbFullSubentPath(objectId(), 
                                          AcDb::kEdgeSubentType, gsMark - 1);
        } else {
            assert(Adesk::kFalse);
        }
        
        break;
        
    default:
        assert(Adesk::kFalse);
    }
    return Acad::eOk;
}


Acad::ErrorStatus 
AsdkPoly::getGsMarkersAtSubentPath(const AcDbFullSubentPath& path, 
                                         AcDbIntArray&       gsMarkers) const
{
    Acad::ErrorStatus es;

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcDbSubentId subEntId = path.subentId();

    switch (subEntId.type()) {
        
    case AcDb::kVertexSubentType:

        if (subEntId.index() == 0) 
            gsMarkers.append(subEntId.index() + 1);
        else
            gsMarkers.append(subEntId.index());
        break;

    case AcDb::kEdgeSubentType:

        gsMarkers.append(subEntId.index() + 1);
        break;
        
    default:
        assert(Adesk::kFalse);
    }

    return Acad::eOk;
}


AcDbEntity* 
AsdkPoly::subentPtr(const AcDbFullSubentPath& path) const
{
    Acad::ErrorStatus es;

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return NULL;
    }

    AcDbSubentId subEntId = path.subentId();
    AcDbPoint *pt;
    AcDbLine *line;

    switch (subEntId.type()) {
        
    case AcDb::kVertexSubentType:

        pt = new AcDbPoint();
        pt->setPosition(vertexArray[subEntId.index()]);
        pt->setNormal(this->normal());
        pt->setPropertiesFrom(this);
        return pt;

    case AcDb::kEdgeSubentType:

        line = new AcDbLine();
        line->setStartPoint(vertexArray[subEntId.index()]);
        line->setEndPoint(vertexArray[subEntId.index() + 1]);
        line->setNormal(this->normal());
        line->setPropertiesFrom(this);
        return line;
        
    default:
        assert(Adesk::kFalse);
    }

    return NULL;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus
AsdkPoly::getOsnapPoints(
    AcDb::OsnapMode       osnapMode,
    int                   gsSelectionMark,
    const AcGePoint3d&    pickPoint,
    const AcGePoint3d&    lastPoint,
    const AcGeMatrix3d&   viewXform,
    AcGePoint3dArray&     snapPoints,
    AcDbIntArray&         /*geomIds*/) const
{
    assertReadEnabled();
    Acad::ErrorStatus es = Acad::eOk;

    if (gsSelectionMark == 0)
        return Acad::eOk;

    if (   osnapMode != AcDb::kOsModeEnd
        && osnapMode != AcDb::kOsModeMid
        && osnapMode != AcDb::kOsModeNear
        && osnapMode != AcDb::kOsModePerp
        && osnapMode != AcDb::kOsModeCen
		&& osnapMode != AcDb::kOsModeIns)
    {
        return Acad::eOk;
    }

	// First, check to see if gsSelection marker is the
	// text geometry. If so, handle center and insertion 
	// modes then return. No need to go into perp, mid, etc.
	if (gsSelectionMark == (mNumSides + 1)) {
		if (osnapMode == AcDb::kOsModeIns)
			snapPoints.append(mCenter);
		else if (osnapMode == AcDb::kOsModeCen)
			snapPoints.append(mCenter);
		
		return es;
	}

    int startIndex = gsSelectionMark - 1;

    AcGePoint3dArray vertexArray;
    if ((es = getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeLineSeg3d lnsg(vertexArray[startIndex],
            vertexArray[startIndex + 1]);
    AcGePoint3d pt;

    AcGeLine3d line, perpLine;
    AcGeVector3d vec;

    AcGeVector3d viewDir(viewXform(Z, 0), viewXform(Z, 1),
            viewXform(Z, 2));

    switch (osnapMode) {
    case AcDb::kOsModeEnd:
        snapPoints.append(vertexArray[startIndex]);
        snapPoints.append(vertexArray[startIndex + 1]);
        break;

    case AcDb::kOsModeMid:
        pt.set(
            ((vertexArray[startIndex])[X]
                + (vertexArray[startIndex + 1])[X]) * 0.5,
            ((vertexArray[startIndex])[Y]
                + (vertexArray[startIndex + 1])[Y]) * 0.5,
            ((vertexArray[startIndex])[Z]
                + (vertexArray[startIndex + 1])[Z]) * 0.5);
        snapPoints.append(pt);
        break;

    case AcDb::kOsModeNear:
        pt = lnsg.projClosestPointTo(pickPoint, viewDir);
        snapPoints.append(pt);
        break;

    case AcDb::kOsModePerp:

        // Create semi-infinite line and find a point on it.
        //
        vec = vertexArray[startIndex + 1]
            - vertexArray[startIndex];
        vec.normalize();
        line.set(vertexArray[startIndex], vec);
        pt = line.closestPointTo(lastPoint);
        snapPoints.append(pt);
        break;

    case AcDb::kOsModeCen:
        snapPoints.append(mCenter);
        break;

    default:
        return Acad::eOk;

    }
    return es;
}

Acad::ErrorStatus
AsdkPoly::getGripPoints(
    AcGePoint3dArray& gripPoints,
    AcDbIntArray& osnapModes,
    AcDbIntArray& geomIds) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;
    if ((es = this->getVertices(gripPoints)) != Acad::eOk) {
        return es;
    }

    // Remove the duplicate point at the start/end and add
    // center as the last point.
    //
    gripPoints.removeAt(gripPoints.length() - 1);

    return es;
}

Acad::ErrorStatus
AsdkPoly::moveGripPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();
    Acad::ErrorStatus es = Acad::eOk;
    AcDbIntArray move;

    int numGripPoints = mNumSides + 1;

    move.setLogicalLength(numGripPoints);
    move.setAll(Adesk::kFalse);
    for (int j = 0; j < indices.length(); j++) {
        if (indices[j] < numGripPoints) {
            move[indices[j]] = Adesk::kTrue;
        }
    }

    for (int i = 0; i < numGripPoints; i++) {
        if (move[i]) {

            // If one of the vertices of the polygon is
            // moved, find out the new start point from that
            // movement and set it.
            // 
            // One way to do that would be to define a new
            // polygon taking the moved point as the start
            // point. Get the vertices of that polygon, and
            // the start point of the old polygon would be
            // one of the vertices of the new polygon at the
            // appropriate index.
            //
            // If the center is moved, just translate the
            // polygon.
            //
            if (i < mNumSides) {  // Vertex movement.

                AcGePoint3dArray oldVertexArray;
                AOK(this->getVertices(oldVertexArray));

                AcGePoint3d vertex = oldVertexArray[i];
                vertex += offset;

                if (vertex == mCenter) {
                    return Acad::eOk;
                }

                AsdkPoly *pNewPoly = new AsdkPoly(mCenter,
                    vertex, mNumSides, mPlaneNormal,mpName);
                AcGePoint3dArray newVertexArray;
                AOK(pNewPoly->getVertices(newVertexArray));

                delete pNewPoly;

                mStartPoint = newVertexArray[mNumSides - i];

            } else { // Center movement.

                AcGeMatrix3d mat;
                mat.entry[0][3] = offset[X];
                mat.entry[1][3] = offset[Y];
                mat.entry[2][3] = offset[Z];
                this->transformBy(mat);
            }
        }
    }
    return es;
}

// Stretch points are the same as grip points except
// for the center of the polygon.
//
Acad::ErrorStatus
AsdkPoly::getStretchPointsAt(
    AcGePoint3dArray& stretchPoints) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = this->getVertices(stretchPoints))
        != Acad::eOk)
    {
        return es;
    }

    // Remove the duplicate point at the start/end.
    stretchPoints.removeAt(stretchPoints.length() - 1);
    return es;
}

Acad::ErrorStatus
AsdkPoly::moveStretchPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();
    Acad::ErrorStatus es = Acad::eOk;

    if (indices.length() == 0 || offset.isZeroLength()) {
        return Acad::eOk;
    }

    // If all the stretch points are selected call
    // transfomBy(), otherwise call moveGripPoints().
    //
    if (indices.length() >= mNumSides) {
        AcGeMatrix3d mat;
        mat(0, 3) = offset[0];
        mat(1, 3) = offset[1];
        mat(2, 3) = offset[2];
        return transformBy(mat);
    } else {
        return moveGripPointsAt(indices, offset);
    }
}

// Transform points and create a polyline out of them.
//
Acad::ErrorStatus AsdkPoly::getTransformedCopy(
    const AcGeMatrix3d& mat,
    AcDbEntity*& ent) const
{
    assertReadEnabled();
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray))
        != Acad::eOk)
    {
        return es;
    }

    for (int i = 0; i < vertexArray.length(); i++) {
        vertexArray[i].transformBy(mat);
    }

    AcDbSpline *pSpline = NULL;
    if ((es = rx_makeSpline(vertexArray, pSpline))
        != Acad::eOk)
    {
        return es;
    }
    assert(pSpline != NULL);
    pSpline->setPropertiesFrom(this);

    ent = pSpline;
    return es;
}

Acad::ErrorStatus
AsdkPoly::intersectWith(
    const AcDbEntity* ent,
    AcDb::Intersect intType,
    AcGePoint3dArray& points,
    int /*thisGsMarker*/,
    int /*otherGsMarker*/) const
{
    assertReadEnabled();
    Acad::ErrorStatus es = Acad::eOk;
    if (ent == NULL)
        return Acad::eNullEntityPointer;

    // The idea is to intersect each side of the polygon
    // with the given entity and return all the points.
    // 
    // For non-R12-entities, i.e. the ones that have their
    // intersection methods defined, we call that method for
    // each of the sides of the polygon. For R12-entities,
    // we use the locally defined intersectors since their
    // protocols are not implemented.

    if (ent->isKindOf(AcDbLine::desc())) {
        if ((es = intLine(this, AcDbLine::cast(ent),
            intType, NULL, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDbArc::desc())) {
        if ((es = intArc(this, AcDbArc::cast(ent), intType,
            NULL, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDbCircle::desc())) {
        if ((es = intCircle(this, AcDbCircle::cast(ent),
            intType, NULL, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDb2dPolyline::desc())) {
        if ((es = intPline(this, AcDb2dPolyline::cast(ent),
            intType, NULL, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDb3dPolyline::desc())) {
        if ((es = intPline(this, AcDb3dPolyline::cast(ent),
            intType, NULL, points)) != Acad::eOk)
        {
            return es;
        }
    } else {
        AcGePoint3dArray vertexArray;
        if ((es = this->getVertices(vertexArray))
            != Acad::eOk)
        {
            return es;
        }
        if (intType == AcDb::kExtendArg
            || intType == AcDb::kExtendBoth)
        {
            intType = AcDb::kExtendThis;
        }

        int startLength = points.length();
        AcDbLine *pAcadLine;
        for (int i = 0; i < vertexArray.length() - 1; i++) {
            pAcadLine = new AcDbLine();
            pAcadLine->setStartPoint(vertexArray[i]);
            pAcadLine->setEndPoint(vertexArray[i + 1]);
            pAcadLine->setNormal(this->normal());

            if ((es = ent->intersectWith(pAcadLine, intType,
                points)) != Acad::eOk)
            {
                for (int j = points.length(); j > startLength; j--)
                    points.removeLast();
                delete pAcadLine;
                return es;
            }
            delete pAcadLine;
        }
    }
    return es;
}

Acad::ErrorStatus
AsdkPoly::intersectWith(
    const AcDbEntity* ent,
    AcDb::Intersect intType,
    const AcGePlane& projPlane,
    AcGePoint3dArray& points,
    int /*thisGsMarker*/,
    int /*otherGsMarker*/) const
{
    assertReadEnabled();
    Acad::ErrorStatus es = Acad::eOk;
    if (ent == NULL)
        return Acad::eNullEntityPointer;

    // The idea is to intersect each side of the polygon
    // with the given entity and return all the points.
    // 
    // For non-R12-entities, i.e. the ones that have their
    // intersection methods defined, we call that method for
    // each of the sides of the polygon. For R12-entities,
    // we use the locally defined intersectors since their
    // protocols are not implemented.

    if (ent->isKindOf(AcDbLine::desc())) {
        if ((es = intLine(this, AcDbLine::cast(ent),
            intType, &projPlane, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDbArc::desc())) {
        if ((es = intArc(this, AcDbArc::cast(ent), intType,
            &projPlane, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDbCircle::desc())) {
        if ((es = intCircle(this, AcDbCircle::cast(ent),
            intType, &projPlane, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDb2dPolyline::desc())) {
        if ((es = intPline(this, AcDb2dPolyline::cast(ent),
            intType, &projPlane, points)) != Acad::eOk)
        {
            return es;
        }
    } else if (ent->isKindOf(AcDb3dPolyline::desc())) {
        if ((es = intPline(this, AcDb3dPolyline::cast(ent),
            intType, &projPlane, points)) != Acad::eOk)
        {
            return es;
        }
    } else {
        AcGePoint3dArray vertexArray;
        if ((es = this->getVertices(vertexArray))
            != Acad::eOk)
        {
            return es;
        }
        if (intType == AcDb::kExtendArg
            || intType == AcDb::kExtendBoth)
        {
            intType = AcDb::kExtendThis;
        }

        int startLength = points.length();
        AcDbLine *pAcadLine;
        for (int i = 0; i < vertexArray.length() - 1; i++) {
            pAcadLine = new AcDbLine();
            pAcadLine->setStartPoint(vertexArray[i]);
            pAcadLine->setEndPoint(vertexArray[i + 1]);
            pAcadLine->setNormal(this->normal());

            if ((es = ent->intersectWith(pAcadLine, intType,
                projPlane, points)) != Acad::eOk)
            {
                for (int j = points.length(); j > startLength; j--)
                    points.removeLast();
                delete pAcadLine;
                return es;
            }
            delete pAcadLine;
        }

        // All the points that we got in this process are on
        // the other curve and we are dealing with apparent
        // intersection. If the other curve is 3D or is not
        // on the same plane as poly, the points are not on
        // poly.
        // 
        // So we need to do some more work. Project the
        // points back onto the plane. They should lie on
        // the projected poly. Find points on real poly
        // corresponding to the projected points.

        AcGePoint3d projPt, planePt;
        AcGePoint3dArray pts;
        AcGeLine3d line;
        AcGePlane polyPlane(mCenter, mPlaneNormal);

        for (i = startLength; i < points.length(); i++) {

            // Define a line starting from the projPt and
            // along the normal.  Intersect the polygon with
            // that line. Find all the points and pick the
            // one closest to the given point.

            pts.setLogicalLength(0);  // reset array to empty
            projPt = points[i].orthoProject(projPlane);
            line.set(projPt, projPlane.normal());
            if ((es = intLine(this, line, pts))
                != Acad::eOk)
            {
                for (int j = points.length(); j > startLength; j--)
                    points.removeLast();
                return es;
            }
            // If the points involved have coordinates that are
            // very small (i.e. 1e-9 or less), then it's possible
            // for floating point inaccuracies to cause the
            // intLine() call above to fail to find any points
            // even though there was a point appended to the points
            // array earlier.  In this case we need to remove the
            // point from the points array and move on.
            //
            if (pts.length() == 0) {
                points.removeAt(i);
                continue;
            }
            // If the plane containing the polygon is perpendicular
            // to the projection plane, it is possible to get more
            // than one intersection point back.  We only want to
            // return one intersection point, so we need to select
            // which one to return.  For this example we will return
            // the point closest to the projection plane.
            //
            points[i] = pts[0];
            double length = (projPt - pts[0]).length();
            double length2;

            for (int j = 1; j < pts.length(); j++) {
                if ((length2 = (projPt - pts[j]).length())
                    < length)
                {
                    points[i] = pts[j];
                    length = length2;
                }
            }
        }
    }
    return es;
}

// END CODE APPEARING IN SDK DOCUMENT.

void            
AsdkPoly::list() const
{
    assertReadEnabled();

    AcDbEntity::list();

    double circumRadius = (mStartPoint - mCenter).length();
    double sideLength = 2.0 * circumRadius * cos(3.14159265358979323846 * 0.5 - 3.14159265358979323846 / mNumSides);

    ads_printf("%18s%16s %d \n", /*MSG0*/"",
                          "Number Of Sides:", mNumSides);

    ads_printf("%18s%16s %-9.16q0 \n", /*MSG0*/"",
                          "Circumference:", sideLength * mNumSides);

    double areaVal;
    this->getArea(areaVal);
    ads_printf("%18s%16s %-9.16q0 \n", /*MSG0*/"", "Area:", areaVal);
    
    ads_printf("%18s%16s ", /*MSG0*/"", "Center:");

    ads_point center;
    center[0] = mCenter[0]; center[1] = mCenter[1]; center[2] = mCenter[2];
    rx_wc2uc(center, center, Adesk::kFalse);
    ads_printf( "X = %-9.16q0, Y = %-9.16q0, Z = %-9.16q0\n", 
                      center[0], center[1], center[2]);

    ads_point startPt;
    startPt[0] = mStartPoint[0]; 
    startPt[1] = mStartPoint[1]; 
    startPt[2] = mStartPoint[2];
    rx_wc2uc(startPt, startPt, Adesk::kFalse);
    ads_printf("%18s%16s ", /*MSG0*/"", "Start Point:");

    ads_printf( "X = %-9.16q0, Y = %-9.16q0, Z = %-9.16q0\n", 
                      startPt[0], startPt[1], startPt[2]);

    ads_point normal;
    normal[0] = mPlaneNormal[0]; 
    normal[1] = mPlaneNormal[1]; 
    normal[2] = mPlaneNormal[2];
    rx_wc2uc(normal, normal, Adesk::kFalse);
    ads_printf("%18s%16s ", /*MSG0*/"", "Normal:");

    ads_printf( "X = %-9.16q0, Y = %-9.16q0, Z = %-9.16q0\n", 
                      normal[0], normal[1], normal[2]);

}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus
AsdkPoly::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    mCenter.transformBy(xform);
    mStartPoint.transformBy(xform);
    mPlaneNormal.transformBy(xform);
    mPlaneNormal.normalize();
    return Acad::eOk;
}

// END CODE APPEARING IN SDK DOCUMENT.

Acad::ErrorStatus       
AsdkPoly::explode(AcDbVoidPtrArray& entitySet) const
{
    assertReadEnabled();

    Acad::ErrorStatus es = Acad::eOk;

    // Exploding a polygon produces a set of lines which
    // are the sides of the polygon.

    AcGePoint3dArray vertexArray;
    if ((es = this->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcDbLine* line;

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        line = new AcDbLine();
        line->setStartPoint(vertexArray[i]);
        line->setEndPoint(vertexArray[i + 1]);
        line->setNormal(mPlaneNormal);

        entitySet.append(line);
    }

    return es;
}

Adesk::Boolean 
AsdkPoly::worldDraw(AcGiWorldDraw* worldDraw)
{
    assertReadEnabled();

    if (worldDraw->regenAbort()) {
        return Adesk::kTrue;
    }

    AOK(drawName(this, worldDraw));

    switch (worldDraw->regenType()) {
        
    case kAcGiHideOrShadeCommand:
    case kAcGiRenderCommand:
        
        AOK(drawFacets(this, worldDraw, NULL));
        AOK(drawEdges (this, worldDraw, NULL));
        break;
        
    case kAcGiStandardDisplay:
    case kAcGiSaveWorldDrawForR12:
    case kAcGiSaveWorldDrawForProxy:
        
        AOK(drawEdges (this, worldDraw, NULL));
        break;
        
    default:
        assert(Adesk::kFalse);

    }
    
    return Adesk::kTrue; // Don't call viewportDraw().
}


void            
AsdkPoly::viewportDraw(AcGiViewportDraw* vportDraw)
{
    assertReadEnabled();

    if (vportDraw->regenAbort()) {
        return;
    }

	// Make sure a selection marker is put out first, to inform graphics system
	// that selection markers are being used by this entity.
	//
    vportDraw->subEntityTraits().setSelectionMarker(0);

    switch (vportDraw->regenType()) {
        
    case kAcGiHideOrShadeCommand:
    case kAcGiRenderCommand:
        
        AOK(drawFacets(this, NULL, vportDraw));
        AOK(drawEdges (this, NULL, vportDraw));
        break;
        
    case kAcGiStandardDisplay:
    case kAcGiSaveWorldDrawForR12:
        
        AOK(drawEdges (this, NULL, vportDraw));
        break;
        
    default:
        assert(Adesk::kFalse);

    }
}



//*************************************************************************
// Overridden methods from AcDbObject
//*************************************************************************

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus 
AsdkPoly::applyPartialUndo(AcDbDwgFiler* filer,
                           AcRxClass*    classObj)
{
    // First thing we do is see if the class matches with
    // ours. If it doesn't, we call base class's
    // applyPartialUndo(), and, hopefully, one of them will
    // take care of it.
    //
    if (classObj != AsdkPoly::desc())
        return AcDbCurve::applyPartialUndo(filer, classObj);

    // Read the op-code and call the appropriate "set"
    // method to undo what was done. The "set" does the
    // filing again for redo.
    //
    Adesk::Int16 shortCode;
    filer->readItem(&shortCode);

    PolyOpCodeForPartialUndo code;
    code = (PolyOpCodeForPartialUndo)shortCode;

    Adesk::UInt32 value32;
    switch (code) {
    case kSetNumSides:
        filer->readItem(&value32);
        AOK(setNumSides(value32));
        break;
    default:
        assert(Adesk::kFalse);
        break;
    }
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkPoly::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbCurve::dwgInFields(filer)) != Acad::eOk) 
    {
        return es;
    }
    
	// Object Version - must always be the first item
    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > VERSION)
      return Acad::eMakeMeProxy;
	
	filer->readItem(&mCenter);
    filer->readItem(&mStartPoint);
    filer->readInt32((long*) &mNumSides);
    filer->readItem(&mPlaneNormal);
    if(mpName != NULL)
    {
        delete mpName;
    }
    filer->readItem(&mpName);
    filer->readItem(&mTextStyle);

    return es;
}

Acad::ErrorStatus
AsdkPoly::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbCurve::dwgOutFields(filer))
        != Acad::eOk)
    {
        return es;
    }

    // Object Version - must always be the first item
    Adesk::Int16 version = VERSION;
    filer->writeItem(version);
	
	filer->writeItem(mCenter);
    filer->writeItem(mStartPoint);
    filer->writeInt32(mNumSides);
    filer->writeItem(mPlaneNormal);
    filer->writeItem(mpName);

    // mTextStyle is a hard pointer id, so filing it out to
    // the purge filer (kPurgeFiler) prevents purging of
    // this object.
    //
    filer->writeItem(mTextStyle);

    return es;
}


#ifdef ORDER_DEPENDENT

Acad::ErrorStatus
AsdkPoly::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();

    if ((AcDbCurve::dxfInFields(filer) != Acad::eOk) ||
         !filer->atSubclassData("AsdkPoly") )
    {
        return filer->filerStatus();
    }

    struct resbuf rb;

	// Object Version
    filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfInt16) {
	    Adesk::Int16 version;
	    version = rb.resval.rint;
	    if (version > VERSION)
          return Acad::eMakeMeProxy;
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfInt16);
        return filer->filerStatus();
    }

    filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfXCoord) {
        mCenter.set(rb.resval.rpoint[X],
            rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfXCoord);
        return filer->filerStatus();
    }
    filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfXCoord + 1) {
        mStartPoint.set(rb.resval.rpoint[X],
            rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfXCoord + 1);
        return filer->filerStatus();
    }
    filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfInt32) {
        mNumSides = rb.resval.rlong;
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfInt32);
        return filer->filerStatus();
    }
	filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfNormalX) {
        mPlaneNormal.set(rb.resval.rpoint[X],
            rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfNormalX);
        return filer->filerStatus();
    }
    filer->readItem(&rb);
    if (rb.restype == AcDb::kDxfText) 
    {
        setName(rb.resval.rstring);
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfText);
        return filer->filerStatus();
    }
    filer->readItem(&rb);
    if (rb.restype == kDxfHardPointerId) {
        acdbGetObjectId(mTextStyle, rb.resval.rlname);
    } else {
        filer->pushBackItem();
        filer->setError(Acad::eInvalidDxfCode,
            "\nError: expected group code %d",
            AcDb::kDxfHardPointerId);
        return filer->filerStatus();
    }
    return filer->filerStatus();
}

#else

Acad::ErrorStatus
AsdkPoly::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();
    Acad::ErrorStatus es = Acad::eOk;
    resbuf rb;

    if ((AcDbCurve::dxfInFields(filer) != Acad::eOk)
        || !filer->atSubclassData("AsdkPoly"))
    {
        return filer->filerStatus();
    }

    while ((es == Acad::eOk)
        && ((es = filer->readResBuf(&rb)) == Acad::eOk))
    {
        switch (rb.restype) {

		// Object Version
        case AcDb::kDxfInt16:
	        Adesk::Int16 version;
	        version = rb.resval.rint;
	        if (version > VERSION)
		        return Acad::eMakeMeProxy;
	        break;

        case AcDb::kDxfXCoord:
            mCenter = asPnt3d(rb.resval.rpoint);
            break;

        case AcDb::kDxfXCoord + 1:
            mStartPoint = asPnt3d(rb.resval.rpoint);
            break;

        case AcDb::kDxfInt32:
            mNumSides = rb.resval.rlong;
            break;
        case AcDb::kDxfNormalX:
            mPlaneNormal = asVec3d(rb.resval.rpoint);
            break;

        case AcDb::kDxfText:
            setName(rb.resval.rstring);
            break;

        case AcDb::kDxfHardPointerId:
            acdbGetObjectId(mTextStyle, rb.resval.rlname);
            break;

        default:
            // An unrecognized group. Push it back so that
            // the subclass can read it again.
            filer->pushBackItem();
            es = Acad::eEndOfFile;
            break;
        }
    }

    // At this point the es variable must contain eEndOfFile
    // - either from readResBuf() or from pushback. If not,
    // it indicates that an error happened and we should
    // return immediately.
    //
    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return es;
}

#endif /* ORDER_DEPENDENT */


Acad::ErrorStatus
AsdkPoly::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbCurve::dxfOutFields(filer))
        != Acad::eOk)
    {
        return es;
    }
    filer->writeItem(AcDb::kDxfSubclass, "AsdkPoly");

	// Object Version
    Adesk::Int16 version = VERSION;
    filer->writeItem(AcDb::kDxfInt16, version);
    
	filer->writeItem(AcDb::kDxfXCoord, mCenter);
    filer->writeItem(AcDb::kDxfXCoord + 1, mStartPoint);
    filer->writeInt32(AcDb::kDxfInt32, mNumSides);
    filer->writeItem(AcDb::kDxfNormalX, mPlaneNormal);
    filer->writeItem(AcDb::kDxfText, mpName);
    filer->writeItem(AcDb::kDxfHardPointerId, mTextStyle);

    return es;
}


Acad::ErrorStatus
AsdkPoly::deepClone(AcDbObject*    pOwner,
                    AcDbObject*&   pClonedObject,
                    AcDbIdMapping& idMap,
                    Adesk::Boolean isPrimary) const
{
    // You should always pass back pClonedObject == NULL
    // if, for any reason, you do not actually clone it
    // during this call.  The caller should pass it in
    // as NULL, but to be safe, we set it here as well.
    //
    pClonedObject = NULL;

    // If this object is in the idMap and is already
    // cloned, then return.
    //
    AcDbIdPair idPair(objectId(), (AcDbObjectId)NULL,
                      Adesk::kFalse, isPrimary);
    if (idMap.compute(idPair) && (idPair.value() != NULL))
        return Acad::eOk;    

    // STEP 1:
    // Create the clone
    //
    AsdkPoly *pClone = (AsdkPoly*)isA()->create();
    if (pClone != NULL)
        pClonedObject = pClone;    // set the return value
    else
        return Acad::eOutOfMemory;

    // STEP 2:
    // Append the clone to its new owner.  In this example,
    // we know that we are derived from AcDbEntity, so we
    // can expect our owner to be an AcDbBlockTableRecord.
    //
    // If an INSERT* operation is in progress pOwner will
    // point to an AcDbBlockTable rather than the actual
    // AcDbBlockTableRecord that is to be the owner.  In
    // this case we just append the clone to the database
    // and don't deal with establising ownership (ownership
    // will be established later on in the INSERT* process).
    //
    // If we have set up an ownership relationship with
    // another of our objects rather than an AcDbBlockTableRecord,
    // then we need to establish how we connect to that owner in
    // our own way.  This sample shows a generic method using
    // setOwnerId().
    // 
    AcDbBlockTableRecord *pBTR =
        AcDbBlockTableRecord::cast(pOwner);
    if (pBTR != NULL) {
        pBTR->appendAcDbEntity(pClone);

    } else if (pOwner->isKindOf(AcDbBlockTable::desc())) {
        pOwner->database()->addAcDbObject(pClone);

    } else {
        if (isPrimary)
            return Acad::eInvalidOwnerObject;

        // Some form of this code is only necessary if
        // anyone has set up an ownership for our object
        // other than with an AcDbBlockTableRecord.
        //
        pOwner->database()->addAcDbObject(pClone);
        pClone->setOwnerId(pOwner->objectId());
    }
    
    // STEP 3:
    // Now we copy our contents to the clone.  This is done
    // using an AcDbDeepCloneFiler.  This filer keeps a
    // list of all AcDbHardOwnershipIds and
    // AcDbSoftOwnershipIds we, and any classes we derive
    // from,  have.  This list is then used to know what
    // additional, "owned" objects need to be cloned below.
    //
    AcDbDeepCloneFiler filer;
    dwgOut(&filer);

    // STEP 4:
    // Rewind the filer and read the data into the clone.
    //
    filer.seek(0L, AcDb::kSeekFromStart);
    pClone->dwgIn(&filer);

    // STEP 5:
    // This must be called for all newly created objects
    // in deepClone.  It is turned off by endDeepClone()
    // after it has translated the references to their
    // new values.
    //
    pClone->setAcDbObjectIdsInFlux();

    // STEP 6:
    // Add the new information to the idMap.  We can use
    // the idPair started above.
    //
    idPair.setValue(pClonedObject->objectId());
    idPair.setIsCloned(Adesk::kTrue);
    idMap.assign(idPair);

    // STEP 7:
    // Using the filer list created above, find and clone
    // any owned objects.
    //
    AcDbObjectId id;
    while (filer.getNextOwnedObject(id)) {

        AcDbObject *pSubObject;
        AcDbObject *pClonedSubObject;

        // Some object's references may be set to NULL, 
        // so don't try to clone them.
        //
        if (id == NULL)
            continue;

        // Open the object and clone it.  Note that we now
        // set "isPrimary" to kFalse here because the object
        // is being cloned, not as part of the primary set,
        // but because it is owned by something in the
        // primary set.
        //
        acdbOpenAcDbObject(pSubObject, id, AcDb::kForRead);
        pClonedSubObject = NULL;
        pSubObject->deepClone(pClonedObject,
                              pClonedSubObject,
                              idMap, Adesk::kFalse);

        // If this is a kDcInsert context, the objects
        // may be "cheapCloned".  In this case, they are
        // "moved" instead of cloned.  The result is that
        // pSubObject and pClonedSubObject will point to
        // the same object.  So, we only want to close
        // pSubObject if it really is a different object
        // than its clone.
        //
        if (pSubObject != pClonedSubObject)
            pSubObject->close();
        
        // The pSubObject may either already have been
        // cloned, or for some reason has chosen not to be
        // cloned.  In that case, the returned pointer will
        // be NULL.  Otherwise, since we have no immediate
        // use for it now, we can close the clone.
        //
        if (pClonedSubObject != NULL)
            pClonedSubObject->close();
    }

    // Leave pClonedObject open for the caller
    //
    return Acad::eOk;
}


Acad::ErrorStatus
AsdkPoly::wblockClone(AcRxObject*    pOwner,
                      AcDbObject*&   pClonedObject,
                      AcDbIdMapping& idMap,
                      Adesk::Boolean isPrimary) const
{
    // You should always pass back pClonedObject == NULL
    // if, for any reason, you do not actually clone it
    // during this call.  The caller should pass it in
    // as NULL, but to be safe, we set it here as well.
    //
    pClonedObject = NULL;

    // If this is a fast wblock operation then no cloning
    // should take place, so we simply call the base class's
    // wblockClone() and return whatever it returns.
    //
    // For fast wblock, the source and destination databases
    // are the same, so we can use that as the test to see
    // if a fast wblock is in progress.
    //
    AcDbDatabase *pDest, *pOrig;
    idMap.destDb(pDest);
    idMap.origDb(pOrig);
    if (pDest == pOrig)
        return AcDbCurve::wblockClone(pOwner, pClonedObject,
            idMap, isPrimary);

    // If this is an Xref bind operation and this AsdkPoly
    // entity is in Paper Space,  then we don't want to
    // clone because Xref bind doesn't support cloning
    // entities in Paper Space.  So we simply return
    // Acad::eOk
    //
    static AcDbObjectId pspace = AcDbObjectId::kNull;
    if (pspace == AcDbObjectId::kNull) {
        AcDbBlockTable *pTable;
        database()->getBlockTable(pTable, AcDb::kForRead);
        pTable->getAt(ACDB_PAPER_SPACE, pspace);
        pTable->close(); 
    }
    if (   idMap.deepCloneContext() == AcDb::kDcXrefBind
        && ownerId() == pspace)
        return Acad::eOk;
    
    // If this object is in the idMap and is already
    // cloned, then return.
    //
    AcDbIdPair idPair(objectId(), (AcDbObjectId)NULL,
                      Adesk::kFalse, isPrimary);
    if (idMap.compute(idPair) && (idPair.value() != NULL))
        return Acad::eOk;    

    // The owner object can be either an AcDbObject, or an
    // AcDbDatabase.  AcDbDatabase is used if the caller is
    // not the owner of the object being cloned (because it
    // is being cloned as part of an AcDbHardPointerId
    // reference).  In this case, the correct ownership
    // will be set during reference translation.  So, if
    // the owner is an AcDbDatabase, then pOwn will be left
    // NULL here, and is used as a "flag" later.
    //
    AcDbObject   *pOwn = AcDbObject::cast(pOwner);
    AcDbDatabase *pDb = AcDbDatabase::cast(pOwner);
    if (pDb == NULL) 
        pDb = pOwn->database();

    // STEP 1:
    // Create the clone
    //
    AsdkPoly *pClone = (AsdkPoly*)isA()->create();
    if (pClone != NULL)
        pClonedObject = pClone;    // set the return value
    else
        return Acad::eOutOfMemory;

    // SSTEP 2:
    // If the owner is an AcDbBlockTableRecord, go ahead
    // and append the clone.  If not, but we know who the
    // owner is, set the clone's ownerId to it.  Otherwise,
    // we set the clone's ownerId to our own ownerId (in
    // other words, the original owner Id).  This Id will
    // then be used later, in reference translation, as
    // a key to finding who the new owner should be.  This
    // means that the original owner must also be cloned at
    // some point during the wblock operation. 
    // EndDeepClone's reference translation aborts if the
    // owner is not found in the idMap.
    //
    // The most common situation where this happens is
    // AcDbEntity references to Symbol Table Records, such
    // as the Layer an Entity is on.  This is when you will
    // have to pass in the destination database as the owner
    // of the Layer Table Record.  Since all Symbol Tables
    // are always cloned in Wblock, you do not need to make
    // sure that Symbol Table Record owners are cloned. 
    //
    // However, if the owner is one of your own classes,
    // then it is up to you to make sure that it gets
    // cloned.  This is probably easiest to do at the end
    // of this function.  Otherwise you may have problems
    // with recursion when the owner, in turn, attempts
    // to clone this object as one of its subObjects.
    // 
    AcDbBlockTableRecord *pBTR = NULL;
    if (pOwn != NULL)
        pBTR = AcDbBlockTableRecord::cast(pOwn);
    if (pBTR != NULL) {
        pBTR->appendAcDbEntity(pClone);
    } else {
        pDb->addAcDbObject(pClonedObject);
        pClone->setOwnerId(  (pOwn != NULL)
                           ? pOwn->objectId() : ownerId());
    }

    // STEP 3:
    // The AcDbWblockCloneFiler makes a list of
    // AcDbHardOwnershipIds and AcDbHardPointerIds.  These
    // are the references which must be cloned during a
    // Wblock operation.
    //
    AcDbWblockCloneFiler filer;
    dwgOut(&filer);

    // STEP 4:
    // Rewind the filer and read the data into the clone.
    //
    filer.seek(0L, AcDb::kSeekFromStart);
    pClone->dwgIn(&filer);

    // STEP 5:
    // This must be called for all newly created objects
    // in wblockClone.  It is turned off by endDeepClone()
    // after it has translated the references to their
    // new values.
    //
    pClone->setAcDbObjectIdsInFlux();

    // STEP 6:
    // Add the new information to the idMap.  We can use
    // the idPair started above.  We must also let the
    // idMap entry know whether the clone's owner is
    // correct, or needs to be translated later.
    //
    idPair.setIsOwnerXlated((Adesk::Boolean)(pOwn != NULL));
    idPair.setValue(pClonedObject->objectId());
    idPair.setIsCloned(Adesk::kTrue);
    idMap.assign(idPair);

    // STEP 7:
    // Using the filer list created above, find and clone
    // any hard references.
    //
    AcDbObjectId id;
    while (filer.getNextHardObject(id)) {

        AcDbObject *pSubObject;
        AcDbObject *pClonedSubObject;

        // Some object's references may be set to NULL, 
        // so don't try to clone them.
        //
        if (id == NULL)
            continue;

        // If the referenced object is from a different
        // database, such as an xref, do not clone it.
        //
        acdbOpenAcDbObject(pSubObject, id, AcDb::kForRead);
        if (pSubObject->database() != database()) {
            pSubObject->close();
            continue;
        }

        // We can find out if this is an AcDbHardPointerId
        // verses an AcDbHardOwnershipId, by seeing if we
        // are the owner of the pSubObject.  If we are not,
        // then we cannot pass our clone in as the owner
        // for the pSubObject's clone.  In that case, we
        // pass in our clone's database (the destination
        // database).
        // 
        // Note that we now set "isPrimary" to kFalse here
        // because the object is being cloned, not as part
        // of the primary set, but because it is owned by
        // something in the primary set.
        //
        pClonedSubObject = NULL;
        if (pSubObject->ownerId() == objectId()) {
            pSubObject->wblockClone(pClone,
                                    pClonedSubObject,
                                    idMap, Adesk::kFalse);
        } else {
            pSubObject->wblockClone(pClone->database(),
                                    pClonedSubObject,
                                    idMap, Adesk::kFalse);
        }
        pSubObject->close();
        
        // The pSubObject may either already have been
        // cloned, or for some reason has chosen not to be
        // cloned.  In that case, the returned pointer will
        // be NULL.  Otherwise, since we have no immediate
        // use for it now, we can close the clone.
        //
        if (pClonedSubObject != NULL)
            pClonedSubObject->close();
    }

    // Leave pClonedObject open for the caller.
    //
    return Acad::eOk;
}


// END CODE APPEARING IN SDK DOCUMENT.


//*************************************************************************
// Statics functions used in this file. 
//*************************************************************************

static Acad::ErrorStatus drawFacets(const AsdkPoly*         poly,
                                          AcGiWorldDraw*    worldDraw,
                                          AcGiViewportDraw* vportDraw)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }
        
    // Since GS interface handles polygons with more than three sides,
    // we will pass in the whole thing. No need of triangulation.

    Adesk::UInt32 faceListSize = vertexArray.length() + 1; // one face + 
                                                           // num Vertices for
                                                           // the face.
    Adesk::Int32* faceList = new Adesk::Int32[faceListSize];

    faceList[0] = vertexArray.length();
    for (int i = 0; i < vertexArray.length(); i++) {
        faceList[i + 1] = i;
    }

    // If we wanted to do anything special for edges and faces, e.g. making
    // edges invisible, setting face color, etc., we would have bothered
    // with these two objects.

    AcGiEdgeData* edgeData = NULL;
    AcGiFaceData* faceData = NULL;
    
    if (worldDraw != NULL) {
        
        worldDraw->geometry().shell(vertexArray.length(),
                                    vertexArray.asArrayPtr(),
                                    faceListSize,
                                    faceList,
                                    edgeData,
                                    faceData);
    } else {
        assert(Adesk::kFalse);
    }
    
    delete [] faceList;
    delete    edgeData;
    delete    faceData;

    return es;
}


static Acad::ErrorStatus drawEdges(const AsdkPoly*         poly,
                                         AcGiWorldDraw*    worldDraw,
                                         AcGiViewportDraw* vportDraw)
{
    Acad::ErrorStatus es = Acad::eOk;

    // Draw each edge of the polygon as a line. We could have drawn
    // the whole polygon as a polyline, but we want to attach subEntity
    // traits (e.g. which line it is) to each line which will be used
    // for snap.
    //
    // Since we are drawing the polygon line by line, we also have the
    // control over setting the linetype and color of each line (via
    // subEntity traits), but we won't get that fancy.


    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGePoint3d ptArray[2];

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        if (worldDraw != NULL) {
            worldDraw->subEntityTraits().setSelectionMarker(i + 1);
        } else {
            assert(Adesk::kFalse);
            //vportDraw->subEntityTraits().setSelectionMarker(i + 1);
        }

        ptArray[0] = vertexArray[i];
        ptArray[1] = vertexArray[i + 1];

        if (worldDraw != NULL) {
            worldDraw->geometry().polyline(2, ptArray);
        } else {
            assert(Adesk::kFalse);
            //vportDraw->geometry().polyline3d(2, ptArray);
        }
    }

    return es;
}


static Acad::ErrorStatus drawName(const AsdkPoly*      poly,
                                        AcGiWorldDraw* worldDraw)
{
    const char *pName = poly->name();
    AcDbObjectId styleId = poly->styleId();

    AcGiTextStyle textStyle;

    if (styleId != NULL)
        if (rx_getTextStyle(textStyle, styleId) != Acad::eOk)
            styleId = AcDbObjectId::kNull;

    if ((pName != NULL) && (pName[0] != '\0'))
    {
        worldDraw->subEntityTraits().setSelectionMarker(poly->numSides() + 1);

        AcGeVector3d direction = poly->startPoint() - poly->center();
        AcGePoint3d center = poly->center();
        AcGeVector3d normal = poly->normal();
        Adesk::Boolean ok;

        if (styleId)
            ok = 
                worldDraw->geometry().text(center, normal, direction,
                 pName, -1, 0, textStyle);
        else
            ok = 
                worldDraw->geometry().text(center, normal, direction,
                 direction.length() / 20, 1, 0, pName);
    }
    return Acad::eOk;
}


static Acad::ErrorStatus intLine(const AsdkPoly*         poly, 
                                 const AcGeLine3d        line,
                                       AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeLineSeg3d tlnsg;
    AcGePoint3d   pt;

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        tlnsg.set(vertexArray[i], vertexArray[i + 1]);

        if (!tlnsg.intersectWith(line, pt)) {
            continue;
        } else {
            points.append(pt);
        }
    }

    return es;
}


static Acad::ErrorStatus intLine(const AsdkPoly*         poly, 
                                 const AcDbLine*         line,
                                       AcDb::Intersect   intType,
                                 const AcGePlane*        projPlane,
                                       AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGeLineSeg3d lnsg(line->startPoint(), line->endPoint());
    es = intLine(poly, lnsg, intType, projPlane, points);

    return es;
}


static Acad::ErrorStatus intLine(const AsdkPoly*         poly, 
                                 const AcGeLineSeg3d     lnsg,
                                       AcDb::Intersect   intType,
                                 const AcGePlane*        projPlane,
                                       AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeLine3d aline(lnsg.startPoint(), lnsg.endPoint());
    AcGeLineSeg3d tlnsg;
    AcGePoint3d   pt;
    AcGePoint3d   dummy;

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        tlnsg.set(vertexArray[i], vertexArray[i + 1]);

        if (intType == AcDb::kExtendArg || intType == AcDb::kExtendBoth) {
            if (projPlane == NULL) {
                if (!tlnsg.intersectWith(aline, pt)) {
                    continue;
                } else {
                    points.append(pt);
                }
            } else {
                if (!tlnsg.projIntersectWith(aline, projPlane->normal(),
                    pt, dummy))
                {
                    continue;
                } else {
                    points.append(pt);
                }
            }
        } else {
            if (projPlane == NULL) {
                if (!tlnsg.intersectWith(lnsg, pt)) {
                    continue;
                } else {
                    points.append(pt);
                }
            } else {
                if (!tlnsg.projIntersectWith(lnsg, projPlane->normal(),
                    pt, dummy))
                {
                    continue;
                } else {
                    points.append(pt);
                }
            }
        }
    }

    return es;
}

static Acad::ErrorStatus intArc(const AsdkPoly*         poly, 
                                const AcDbArc*          arc,
                                      AcDb::Intersect   intType,
                                const AcGePlane*        projPlane,
                                      AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGeCircArc3d aarc(arc->center(), arc->normal(), 
                       arc->normal().perpVector(), arc->radius(), 
                       arc->startAngle(), arc->endAngle());
    es = intArc(poly, aarc, intType, projPlane, points);

    return es;
}


static Acad::ErrorStatus intArc(const AsdkPoly*         poly, 
                                const AcGeCircArc3d     arc,
                                      AcDb::Intersect   intType,
                                const AcGePlane*        projPlane,
                                      AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeCircArc3d  acircle(arc.center(), arc.normal(), arc.radius());
    AcGeLineSeg3d lnsg;
    AcGePoint3d   pt1, pt2;
    AcGePoint3d   dummy1, dummy2;
    int           howMany;

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        lnsg.set(vertexArray[i], vertexArray[i + 1]);

        if (intType == AcDb::kExtendArg || intType == AcDb::kExtendBoth) {
            if (projPlane == NULL) {
                if (!acircle.intersectWith(lnsg, howMany, pt1, pt2)) {
                    continue;
                } else {
                    if (howMany > 1) {
                        points.append(pt1);
                        points.append(pt2);
                    } else {
                        points.append(pt1);
                    }
                }
            } else {
                if (!acircle.projIntersectWith(lnsg, projPlane->normal(),
                    howMany, pt1, pt2, dummy1, dummy2))
                {
                    continue;
                } else {
                    if (howMany > 1) {
                        points.append(pt1);
                        points.append(pt2);
                    } else {
                        points.append(pt1);
                    }
                }
            }
        } else {
            if (projPlane == NULL) {
                if (!arc.intersectWith(lnsg, howMany, pt1, pt2)) {
                    continue;
                } else {
                    if (howMany > 1) {
                        points.append(pt1);
                        points.append(pt2);
                    } else {
                        points.append(pt1);
                    }
                }
            } else {
                if (!arc.projIntersectWith(lnsg, projPlane->normal(),
                    howMany, pt1, pt2, dummy1, dummy2))
                {
                    continue;
                } else {
                    if (howMany > 1) {
                        points.append(pt1);
                        points.append(pt2);
                    } else {
                        points.append(pt1);
                    }
                }
            }
        }
    }

    return es;
}


static Acad::ErrorStatus intCircle(const AsdkPoly*         poly, 
                                   const AcDbCircle*       circle,
                                         AcDb::Intersect   intType,
                                   const AcGePlane*        projPlane,
                                         AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGeCircArc3d  acircle(circle->center(), circle->normal(),
                          circle->radius());
    es = intCircle(poly, acircle, intType, projPlane, points);

    return es;
}


static Acad::ErrorStatus intCircle(const AsdkPoly*         poly, 
                                   const AcGeCircArc3d     circle,
                                         AcDb::Intersect   intType,
                                   const AcGePlane*        projPlane,
                                         AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcGeLineSeg3d lnsg;
    AcGePoint3d   pt1, pt2;
    AcGePoint3d   dummy1, dummy2;
    int           howMany;

    for (int i = 0; i < vertexArray.length() - 1; i++) {

        lnsg.set(vertexArray[i], vertexArray[i + 1]);

        if (projPlane == NULL) {
            if (!circle.intersectWith(lnsg, howMany, pt1, pt2)) {
                continue;
            } else {
                if (howMany > 1) {
                    points.append(pt1);
                    points.append(pt2);
                } else {
                    points.append(pt1);
                }
            }
        } else {
            if (!circle.projIntersectWith(lnsg, projPlane->normal(), 
               howMany, pt1, pt2, dummy1, dummy2))
            {
                continue;
            } else {
                if (howMany > 1) {
                    points.append(pt1);
                    points.append(pt2);
                } else {
                    points.append(pt1);
                }
            }
        }
    }

    return es;
}


static Acad::ErrorStatus intPline(const AsdkPoly*         poly, 
                                        AcDb2dPolyline*   pline,
                                        AcDb::Intersect   intType,
                                  const AcGePlane*        projPlane,
                                        AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcDbSpline*      spline = NULL;
    AcDbLine*        acadLine = NULL;

    AcGePoint3dArray    pts;
    AcGeDoubleArray  bulges;
    int              numPoints, i;
    AcGePoint3d      pt1, pt2;

    AcGeCircArc3d    arc;
    AcGeLineSeg3d    lnsg;

    AcGeVector3d entNorm = pline->normal();
    AcDb::Intersect type = AcDb::kOnBothOperands;

    switch (pline->polyType()) {

    case AcDb::k2dSimplePoly:
    case AcDb::k2dFitCurvePoly:

        // Intersect with each line or arc segment of the polyline. 
        // Depending on the intType, extend the last segment.

        if ((es = rx_scanPline(pline, pts, bulges)) != Acad::eOk) {
            return es;
        }
        numPoints = pts.length();

        for (i = 0; i < numPoints - 1; i++) {

            pt1 = pts[i]; pt2 = pts[i + 1];
            if (i == numPoints - 2)
                type = intType;

            if (bulges[i] > 1.0e-10) {     // create an arc

                rx_wc2ec(asDblArray(pt1), asDblArray(pt1), asDblArray(entNorm), 
                                                              Adesk::kFalse);
                rx_wc2ec(asDblArray(pt2), asDblArray(pt2), asDblArray(entNorm), 
                                                              Adesk::kFalse);

                AOK(rx_makeArc(pt1, pt2, bulges[i], entNorm, arc));
                AOK(intArc(poly, arc, type, projPlane, points));

            } else {                       // create a line

                lnsg.set(pt1, pt2);
                AOK(intLine(poly, lnsg, type, projPlane, points));
            }
        }
        break;

    case AcDb::k2dQuadSplinePoly:
    case AcDb::k2dCubicSplinePoly:

        if ((es = pline->getSpline(spline)) != Acad::eOk) {
            return es;
        }

        if (intType == AcDb::kExtendArg || intType == AcDb::kExtendBoth) {
            intType = AcDb::kExtendThis;
        }

        for (i = 0; i < vertexArray.length() - 1; i++) {

            acadLine = new AcDbLine();
            acadLine->setStartPoint(vertexArray[i]);
            acadLine->setEndPoint(vertexArray[i + 1]);
            acadLine->setNormal(poly->normal());

            if (projPlane == NULL) {
                AOK(spline->intersectWith(acadLine, intType, points));
            } else {
                AOK(spline->intersectWith(acadLine, intType, 
                                                          *projPlane, points));
            }

            delete acadLine;
        }

        delete spline;
        break;

    default:
       return Acad::eInvalidInput;
    }

    return es;
}


static Acad::ErrorStatus intPline(const AsdkPoly*         poly, 
                                        AcDb3dPolyline*   pline,
                                        AcDb::Intersect   intType,
                                  const AcGePlane*        projPlane,
                                        AcGePoint3dArray& points)
{
    Acad::ErrorStatus es = Acad::eOk;

    AcGePoint3dArray vertexArray;
    if ((es = poly->getVertices(vertexArray)) != Acad::eOk) {
        return es;
    }

    AcDbSpline*      spline = NULL;
    AcDbLine*        acadLine = NULL;

    AcGePoint3dArray    pts;
    int              numPoints, i;

    AcGeLineSeg3d    lnsg;
    AcDb::Intersect  type = AcDb::kOnBothOperands;

    switch (pline->polyType()) {

    case AcDb::k3dSimplePoly:

        if ((es = rx_scanPline(pline, pts)) != Acad::eOk) {
            return es;
        }
        numPoints = pts.length();

        // Intersect with each line segment of the polyline. 
        // Depending on the intType, extend the last segment.

        for (i = 0; i < numPoints - 1; i++) {

            if (i == numPoints - 2)
                type = intType;

            lnsg.set(pts[i], pts[i + 1]);
            if ((es = intLine(poly, lnsg, type, projPlane, points)) 
                   != Acad::eOk) {
                return es;
            }
        }

    case AcDb::k3dQuadSplinePoly:
    case AcDb::k3dCubicSplinePoly:

        if ((es = pline->getSpline(spline)) != Acad::eOk) {
            delete spline;
            return es;
        }

        if (intType == AcDb::kExtendArg || intType == AcDb::kExtendBoth) {
            intType = AcDb::kExtendThis;
        }

        for (i = 0; i < vertexArray.length() - 1; i++) {

            acadLine = new AcDbLine();
            acadLine->setStartPoint(vertexArray[i]);
            acadLine->setEndPoint(vertexArray[i + 1]);
            acadLine->setNormal(poly->normal());

            if (projPlane == NULL) {
                AOK(spline->intersectWith(acadLine, intType, points));
            } else {
                AOK(spline->intersectWith(acadLine, intType, 
                                                          *projPlane, points));
            }

            delete acadLine;
        }

        delete spline;
        break;

    default:
       return Acad::eInvalidInput;
    }

    return es;
}
