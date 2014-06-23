#ifndef AMODELER_INC_ERRCODES_H
#define AMODELER_INC_ERRCODES_H


///////////////////////////////////////////////////////////////////////////////
//
// � Autodesk, Inc. 1998-2008. All rights reserved.
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
// The modeler throws an exception of type ErrorCode anytime it encounters an 
// error condition.
//
// To indicate an error (throw an exception), use the checkError() function.
// For example:
//
//   checkError(factor > epsNor(), eScaleFactorMustBePositive);
//
///////////////////////////////////////////////////////////////////////////////
#include <tchar.h>

AMODELER_NAMESPACE_BEGIN

// An enum of all ErrorCodes which can be thrown by AModeler. When adding a new 
// ErrorCode, do not forget to update the errorCodeStrings[] array in file
// errcodes.cpp so that the errorString(ErrorCode) function can return the 
// ErrorCode as a string.
// 
enum ErrorCode
{
    eOk = 0,                    // This value should never be thrown
    eFail,                      
    eViewPointLiesInsideScene,
    eBadBodyGeometry,
    eBadSurfaceType,
    eBadCurveType,
    eBadInput,
    eNullVector,
    eNullNormalVector,
    eBadPlane,
    eBadLine,
    eBadAxis,
    eBadTransform,
    ePointLiesInPlane,
    eInputBodiesMustNotBeNegated,
    eRadiusMustBePositive,                                 
    eRadiusMustBeNonNegative,
    eRadiusMustNotBeZero,
    eApproximationMustBeAtLeastFour,
    eScaleFactorMustBePositive,
    eAngleMustNotBeZero,
    eBodyPointerIsNull,
    eFacePointerIsNull,
    eEdgePointerIsNull,
    eVertexPointerIsNull,
    ePolygonPointerIsNull,
    eProfilePolygonPointerIsNull,
    ePathPolygonPointerIsNull,
    eBodyIsNegative,
    eIntervalIsNull,
    eFileNameIsNull,
    eBadFile,
    eIncorrectFile,
    eFilePointerIsNull,
    eFileOpenError,                                        
    eFileReadError,
    eFileWriteError,
    eSaveError,
    eRestoreError,
    eBadDataRestored,
    eFileIsNewerThanCurrentVersionOfModeler,
    eBoxSizesMustNotBeZero,
    eMajorRadiusMustBeGreaterThanMinorRadius,
    eInnerRadiusMustBeSmallerThanOuterRadius,
    eInnerRadiusCanBeZeroOnlyIfOuterRadiusIsZero,
    eViewPointCoincidesWithTargetPoint,                    
    eEpsilonMustBePositive,
    eCallbackObjectPointerIsNull,
    ePickingNotPossible,
    eAtLeast4NonCoplanarPointsRequired,
    ePointsDoNotDefineConvexPolyhedron,
    eApexMustNotLieInPolygon,
    eExtrusionVectorMustNotBeParallelToPolygon,
    eAxisOfRevolutionMustLieInPolygonPlane,
    eAxisOfRevolutionIntersectsPolygon,
    eBadNormal,                                            
    eBadPolygon,
    ePolygonIsSelfIntersectingOrTouching,
    eBadRelativePolygonPosition,
    eCannotCreateFillet,
    eBadArcCenter,
    eRadiusTooSmall,
    eFilletRadiusMustBePositive,
    eCannotFilletVerticesBelongingToArcs,
    eFirstAndLastVertexInEndpointRevolutionMustNotBeFilleted,      
    eArcBetweenLastAndFirstVertexNotAllowedForEndpointRevolution,  
    eEntitiesSectionNotFoundInDxfFile,
    ePolylineEntityNotFoundInDxfFile,
    ePolylineMustBeClosed,
    e3dPolylineOrMeshNotAllowed,
    eBadDxfFile,
    ePointsAreColinearOrCoincident,
    eSourceArgumentsAreColinearOrCoincident,
    eDestinationArgumentsAreColinearOrCoincident,
    ePointsAreCoplanar,
    eChamferingDistanceMustBePositive,
    eOnlyManifoldEdgesCanBeFilletedAndChamfered,
    eOnlyStraightAndCircularEdgesCanBeFilletedAndChamfered,
    ePlanarEdgesCannotBeFilletedAndChamfered,
    eAtLeastOneEdgeExpected,
    eFilletRadiusTooLarge,
    eChamferDistanceTooLarge,
    eCannotFilletEdge,
    eCannotMitreEdgesOfDifferentConvexity,
    eTooComplexMixedConvexityCap,
    eNotYetImplemented,
    eCircleIsNotValid,
    eBaseNormalPerpendicularToAxisVector,
    eEndCentersMustHaveEqualDistance,
    eFaceMustNotBelongToABody,
    eFaceHasNoEdges,
    eOneSidedFaceExpected,
    eProfileFacesMustHaveTheSameNumberOfEdges,
    eAtLeastTwoProfilesExpected,
    eBodyProfileMustContainExactlyOneFace,
    eProfileFaceHasNoEdges,
    eBadMorphingMap,
    eEdgesOfFirstProfileCannotBeMarkedApproximating,
    eBaseSizesMustBePositive,
    eTopCircleMustLieAboveBaseRectangle,
    eFilletByRadiusOrArcByBulgeTypeExpected,
    eArcByRadiusTypeExpected,
    eArc3dTypeExpected,
    eCannotCreateTouchingCircle,
    eNonPlanarPolygon,
    eNonPlanarProfileFace,
    eFaceMustHaveAtLeastThreeEdges,
    ePolygonPointsCoincide,
    eBadPath,
    eBadProfileAndPathOrientation,
    eFirstPathPointMustLieInStartProfilePlane,
    eLastPathPointMustLieInEndProfilePlane,
    eWidthTooSmall,
    eHeightTooSmall,
    eEndProfileNotAllowedWhenPathIsClosed,
    eScaleFactorNotAllowedWhenPathIsClosed,
    eTwistAngleNotAllowedWhenPathIsClosed,
    eMorphingMustBeIdentityWhenPathIsClosed,
    eExtrusionBodyLooksSelfIntersecting,
    eMorphingMapRequiresEndProfile,
    eNegativeIndexInMorphingMap,
    eFixedPointMustLieInPolygonPlane,
    eTriStripsMayBeGeneratedOnlyWhenCachingTriangles,
    eStartProfileNormalHasOppositeDirectionThanFirstPathSegment,
    eEndProfileNormalHasOppositeDirectionThanLastPathSegment,
    eStartProfileIsParallelWithFirstPathSegment,
    eEndProfileIsParallelWithLastPathSegment,
    eProfilePolygonMustContainAtLeastOnePoint,
    eArcByRadiusNotAllowedForPathPolygons_UseArc3d,
    eArcByBulgeNotAllowedForPathPolygons_UseArc3d,
    eNumberOfLinearSegmentsMustBeAtLeastOne,
    eZeroBulgeNotAllowed,
    eFixedPointMustLieInStartProfilePlane,
    eBodyCannotBeClosed,
    ePolygonNormalNotPerpendicularToPolygonPlane,
    eSizeMustBePositive,
    ePointerIsNull,
    eToleranceMustBePositive,
    eValueMustBePositive,
    ePartnerEdgesOfNonManifoldEdgeCannotBeOrdered,
    eNonManifoldEdgesMustHaveEvenNumberOfPartners,
    eFaceMustHaveManifoldEdgesOnly,
    eStitchingFacesDidNotProduceAValidBody,
    eFaceCanNotBeMoved,
    eManifoldEdgeExpected,
    eEdgeSharedByTwoDifferentFacesExpected,
    eCoplanarFacesExpected,
    eInvalidVector,
    eAngleMustBePositive,
    eMinNumberOfFacesInSurfaceMustBeAtLeastTwo,
    eUnspecifiedCurveTypeExpected,
    eInvalidTerrainBody,
    eHeightMustBePositive,
    eCannotCreateLoopOfEdges,
    eTerrainSurfaceContainsHole,
    eBadIndexInMorphingMap,
    eStartProfileIsWrong,
    eEndProfileIsWrong,
    eExtrusionPathIsWrong,
    eStartProfileMustHaveOnlySingleLoop,
    eEndProfileMustHaveOnlySingleLoop,
    eInternalError                                         = 1000
}; // enum ErrorCode


#ifdef _DEBUG

#define checkError(testExpr, err) checkErrorFunc(testExpr, err, _T(__FILE__), __LINE__)

DllImpExp void checkErrorFunc(bool testExpr, ErrorCode, const wchar_t* file, int line);

#else

inline void checkError(bool testExpr, ErrorCode err)
{
    if (!testExpr)
        throw err;
}
#endif


// Returns the error string corresponding to the ErrorCode or a string "nnn" 
// where "nnn" is the error number if there is no error string for the given 
// ErrorCode
//
DllImpExp wchar_t* errorString(ErrorCode);


AMODELER_NAMESPACE_END
#endif
