#ifndef AC_GECURV3D_H
#define AC_GECURV3D_H
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
// DESCRIPTION:
//
// This file contains the class AcGeCurve3d - An abstract base class
// from which all 3d curves are derived.

#include "adesk.h"
#include "geent3d.h"
#include "geponc3d.h"

class AcGeCurve2d;
class AcGeSurface;
class AcGePoint3d;
class AcGePlane;
class AcGeVector3d;
class AcGeLinearEnt3d;
class AcGeLine3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGeInterval;
class AcGeMatrix3d;
class AcGePointOnCurve3dData;
class AcGePoint3dArray;
class AcGeVector3dArray;
class AcGeDoubleArray;
class AcGeBoundBlock3d;
class AcGeVoidPointerArray;
class AcGeIntArray;

class
#ifdef AC_GECURV3D_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeCurve3d : public AcGeEntity3d
{
public:

    // Parametrization.
    //
    void           getInterval(AcGeInterval&) const;
    void           getInterval(AcGeInterval&, AcGePoint3d& start,
                               AcGePoint3d& end) const;
    AcGeCurve3d&   reverseParam();
	AcGeCurve3d&   setInterval();
	Adesk::Boolean setInterval(const AcGeInterval& intrvl);

    // Distance to other geometric objects.
    //
    double       distanceTo(const AcGePoint3d&,
                            const AcGeTol& = AcGeContext::gTol) const;
    double       distanceTo(const AcGeCurve3d&,
                            const AcGeTol& = AcGeContext::gTol) const;

    // Return the point on this object that is closest to the other object.
    // These methods return point on this curve as a simple 3d point.
    //
    AcGePoint3d closestPointTo(const AcGePoint3d&,
                               const AcGeTol& = AcGeContext::gTol) const;
    AcGePoint3d closestPointTo(const AcGeCurve3d& curve3d,
                               AcGePoint3d& pntOnOtherCrv,
                               const AcGeTol& = AcGeContext::gTol) const;

    // Alternate signatures for above functions.  These methods return point
    // on this curve as an AcGePointOnCurve3d.
    //
    void getClosestPointTo(const AcGePoint3d& pnt, AcGePointOnCurve3d&,
                           const AcGeTol& = AcGeContext::gTol) const;
    void getClosestPointTo(const AcGeCurve3d& curve3d,
                           AcGePointOnCurve3d& pntOnThisCrv,
                           AcGePointOnCurve3d& pntOnOtherCrv,
                           const AcGeTol& = AcGeContext::gTol) const;

    // Return closest points when projected in a given direction.
    // These methods return point on this curve as a simple 3d point.
    //
    AcGePoint3d projClosestPointTo(const AcGePoint3d& pnt,
                                   const AcGeVector3d& projectDirection,
                                   const AcGeTol& = AcGeContext::gTol) const;
    AcGePoint3d projClosestPointTo(const AcGeCurve3d& curve3d,
                                   const AcGeVector3d& projectDirection,
                                   AcGePoint3d& pntOnOtherCrv,
                                   const AcGeTol& = AcGeContext::gTol) const;

    // Alternate signatures for above functions.  These methods return point
    // on this curve as an AcGePointOnCurve3d.
    //
    void getProjClosestPointTo(const AcGePoint3d& pnt,
                               const AcGeVector3d& projectDirection,
                               AcGePointOnCurve3d&,
                               const AcGeTol& = AcGeContext::gTol) const;
    void getProjClosestPointTo(const AcGeCurve3d& curve3d,
                               const AcGeVector3d& projectDirection,
                               AcGePointOnCurve3d& pntOnThisCrv,
                               AcGePointOnCurve3d& pntOnOtherCrv,
                               const AcGeTol& = AcGeContext::gTol) const;

    // Return point on curve whose normal vector passes thru input point.
    // Second parameter contains initial guess value and also 
    // contains output point.

	// Returns true or false depending on whether a normal point was found.
        //
	Adesk::Boolean getNormalPoint(const AcGePoint3d& pnt,
	                              AcGePointOnCurve3d& pntOnCrv,
                                      const AcGeTol& = AcGeContext::gTol) const;

    // Return oriented bounding box of curve.
    //
    AcGeBoundBlock3d  boundBlock() const;
    AcGeBoundBlock3d  boundBlock(const AcGeInterval& range) const;

    // Return bounding box whose sides are parallel to coordinate axes.
    //
    AcGeBoundBlock3d  orthoBoundBlock() const;
    AcGeBoundBlock3d  orthoBoundBlock(const AcGeInterval& range) const;

    // Project methods.
    //
    AcGeEntity3d*  project(const AcGePlane& projectionPlane,
                           const AcGeVector3d& projectDirection,
                           const AcGeTol& = AcGeContext::gTol) const;
    AcGeEntity3d*  orthoProject(const AcGePlane& projectionPlane,
                                const AcGeTol& = AcGeContext::gTol) const;

    // Tests if point is on curve.
    //
    Adesk::Boolean isOn(const AcGePoint3d&,
                        const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isOn(const AcGePoint3d& pt, double& param,
                        const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isOn(double param,
                        const AcGeTol& = AcGeContext::gTol) const;

    // Parameter of the point on curve.  Contract: point IS on curve
    //
    double paramOf(const AcGePoint3d&, const AcGeTol& = AcGeContext::gTol)const;

	// Return the offset of the curve.
	//
	void getTrimmedOffset(double distance,
		              const AcGeVector3d& planeNormal,
			      AcGeVoidPointerArray& offsetCurveList,
			      AcGe::OffsetCrvExtType = AcGe::kFillet,
                              const AcGeTol& = AcGeContext::gTol) const;

    // Geometric inquiry methods.
    //
    Adesk::Boolean isClosed      (const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isPlanar      (AcGePlane&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isLinear      (AcGeLine3d&,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isCoplanarWith(const AcGeCurve3d& curve3d,
                                  AcGePlane& plane,
                                  const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isPeriodic    (double& period) const;

    // Length based methods.
    //
    double         length       (double fromParam, double toParam,
                                 double = AcGeContext::gTol.equalPoint()) const;
    double         paramAtLength(double datumParam, double length,
                                 Adesk::Boolean posParamDir = Adesk::kTrue,
                                 double = AcGeContext::gTol.equalPoint()) const;
    Adesk::Boolean area         (double startParam, double endParam,
                                 double& value,
                                 const AcGeTol& = AcGeContext::gTol) const;

    // Degeneracy.
    //
    Adesk::Boolean isDegenerate(AcGe::EntityId& degenerateType,
                                const AcGeTol& = AcGeContext::gTol) const;
    Adesk::Boolean isDegenerate(AcGeEntity3d*& pConvertedEntity,
                                const AcGeTol& = AcGeContext::gTol) const;

    // Modify methods.
    //
    void getSplitCurves(double param, AcGeCurve3d* & piece1,
                        AcGeCurve3d* & piece2) const;

	// Explode curve into its component sub-curves.
	//
	Adesk::Boolean explode       (AcGeVoidPointerArray& explodedCurves,
	                              AcGeIntArray& newExplodedCurve,
				      const AcGeInterval* intrvl = NULL ) const;

    // Local closest points
    //
    void getLocalClosestPoints(const AcGePoint3d& point,
                               AcGePointOnCurve3d& approxPnt,
                               const AcGeInterval* nbhd = 0,
                               const AcGeTol& = AcGeContext::gTol) const;
    void getLocalClosestPoints(const AcGeCurve3d& otherCurve,
                               AcGePointOnCurve3d& approxPntOnThisCrv,
                               AcGePointOnCurve3d& approxPntOnOtherCrv,
                               const AcGeInterval* nbhd1 = 0,
                               const AcGeInterval* nbhd2 = 0,
                               const AcGeTol& = AcGeContext::gTol) const;

    // Return start and end points.
    //
    Adesk::Boolean hasStartPoint(AcGePoint3d& startPoint) const;
    Adesk::Boolean hasEndPoint  (AcGePoint3d& endPoint) const;

    // Evaluate methods.
    //
    AcGePoint3d    evalPoint(double param) const;
    AcGePoint3d    evalPoint(double param, int numDeriv,
                             AcGeVector3dArray& derivArray) const;

    // Polygonize curve to within a specified tolerance.
    //
    void           getSamplePoints(double fromParam, double toParam,
                                   double approxEps, AcGePoint3dArray& 
 		                   pntArr, AcGeDoubleArray& paramArr) const;
    void           getSamplePoints(int numSample, AcGePoint3dArray& ) const;

    // Assignment operator.
    //
    AcGeCurve3d&   operator =  (const AcGeCurve3d&);

protected:

    // Private constructors so that no object of this class can be instantiated.
    AcGeCurve3d();
    AcGeCurve3d(const AcGeCurve3d&);
};

#endif
