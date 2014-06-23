#ifndef AD_ACDB_H
#define AD_ACDB_H 1
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
// acdb.h:   Definitions for AutoCAD Database Library which are
//           shared between Internal and 3rd party Developers

#include "adesk.h"
#include "rxobject.h"
#include "gepnt3d.h"

#ifdef ACAD_OBJID_INLINE_INTERNAL
#    include "dbidinln.h"
#else
#    include "dbidapps.h"
#endif

#include "dbboiler.h"

// String Constants
//
#define ACDB_SERVICES              /*MSG0*/"AcDbServices"
#define ACDB_MODEL_SPACE           /*MSG0*/"*MODEL_SPACE"
#define ACDB_PAPER_SPACE           /*MSG0*/"*PAPER_SPACE"
#define ACDB_NULL_HANDLE           /*MSG0*/"\0\0\0\0\0\0\0"
#define ACDB_BROKEN_HANDLE         /*MSG0*/"FFFFFFFF"
#define ACDB_OPEN_BRACE_STR        /*MSG0*/"{"
#define ACDB_OPEN_BRACE_CHAR       /*MSG0*/'{'
#define ACDB_CLOSE_BRACE_STR       /*MSG0*/"}"
#define ACDB_CLOSE_BRACE_CHAR      /*MSG0*/'}'
#define ACDB_GROUP_DICTIONARY      /*MSG0*/"ACAD_GROUP"
#define ACDB_MLINESTYLE_DICTIONARY /*MSG0*/"ACAD_MLINESTYLE"

#define eNotImplemented eNotImplementedYet

struct Acad
{
    enum ErrorStatus       { eOk                        =  0,

                             eNotImplementedYet         =  1,
                             eNotApplicable             =  2,
                             eInvalidInput              =  3,
                             eAmbiguousInput            =  4,
                             eAmbiguousOutput           =  5,
                             eOutOfMemory               =  6,
			     eBufferTooSmall            =  7,
			     eInvalidOpenState          =  8,

                             eHandleExists              = 10,
                             eNullHandle                = 11,
                             eBrokenHandle              = 12,
                             eUnknownHandle             = 13,
                             eHandleInUse               = 14,
                             eNullObjectPointer         = 15,
                             eNullObjectId              = 16,
                             eNullBlockName             = 17,
			     eContainerNotEmpty	        = 18,

                             eNullEntityPointer         = 20,
                             eIllegalEntityType         = 21,
                             eKeyNotFound               = 22,
                             eDuplicateKey              = 23,
                             eInvalidIndex              = 24,
                             eDuplicateIndex            = 25,
                             eAlreadyInDb               = 26,
                             eOutOfDisk                 = 27,
                             eDeletedEntry              = 28,
                             eNegativeValueNotAllowed   = 29,
                             eInvalidExtents            = 30,
                             eInvalidAdsName            = 31,
                             eInvalidSymbolTableName    = 32,
			     eInvalidKey                = 33,
			     eWrongObjectType           = 34,
			     eWrongDatabase             = 35,
			     eObjectToBeDeleted         = 36,
			     eInvalidDwgVersion         = 37,
			     eAnonymousEntry            = 38,
                             eIllegalReplacement        = 39,

                             eEndOfObject               = 40,
                             eEndOfFile                 = 41,
                             eIsReading                 = 42,
                             eIsWriting                 = 43,
                             eNotOpenForRead            = 44,
                             eNotOpenForWrite           = 45,
                             eNotThatKindOfClass        = 46,
                             eInvalidBlockName          = 47,
                             eMissingDxfField           = 48,
                             eDuplicateDxfField         = 49,

                             eInvalidDxfCode            = 50,
                             eInvalidResBuf     = 51,
                             eBadDxfSequence            = 52,
                             eFilerError                = 53,
                             eVertexAfterFace           = 54,
                             eInvalidFaceVertexIndex    = 55,
                             eInvalidMeshVertexIndex    = 56,
                             eOtherObjectsBusy          = 57,
                             eMustFirstAddBlockToDb     = 58,
                             eCannotNestBlockDefs       = 59,

                             eDwgRecoveredOK            = 60,
                             eDwgNotRecoverable         = 61,
                             eDxfPartiallyRead          = 62,
                             eDxfReadAborted            = 63,
                             eDxbPartiallyRead          = 64,
                             eDwgCRCDoesNotMatch        = 65,
                             eDwgSentinelDoesNotMatch   = 66,
                             eDwgObjectImproperlyRead   = 67,
                             eNoInputFiler              = 68,
			     eDwgNeedsAFullSave         = 69,

                             eDxbReadAborted            = 70,
                             eFileLockedByACAD          = 71,
                             eFileAccessErr             = 72,
                             eFileSystemErr             = 73,
                             eFileInternalErr           = 74,
                             eFileTooManyOpen           = 75,

                             eWasErased                 = 80,
                             ePermanentlyErased         = 81,
                             eWasOpenForRead            = 82,
                             eWasOpenForWrite           = 83,
                             eWasOpenForUndo            = 84,
                             eWasNotifying              = 85,
			     eWasOpenForNotify          = 86,
			     eOnLockedLayer             = 87,
			     eMustOpenThruOwner         = 88,
                             eSubentitiesStillOpen      = 89,

                             eAtMaxReaders              = 90,
                             eIsWriteProtected          = 91,
                             eIsXRefObject              = 92,
                             eNotAnEntity               = 93,
                             eHadMultipleReaders        = 94,
			     eDuplicateRecordName       = 95,
                             eXRefDependent             = 96,
			     eSelfReference             = 97,
			     eMissingSymbolTable        = 98,
                             eMissingSymbolTableRec     = 99,

                             eWasNotOpenForWrite        = 100,
                             eCloseWasNotifying         = 101,
                             eCloseModifyAborted        = 102,
                             eClosePartialFailure       = 103,
                             eCloseFailObjectDamaged    = 104,
                             eCannotBeErasedByCaller    = 105,

			     eInsertAfter               = 110,

                             eFixedAllErrors            = 120,
                             eLeftErrorsUnfixed         = 122,
                             eUnrecoverableErrors       = 123,
                             eNoDatabase                = 124,
                             eXdataSizeExceeded         = 125,
                             eRegappIdNotFound          = 126,
                             eRepeatEntity              = 127,
                             eRecordNotInTable          = 128,
                             eIteratorDone              = 129,
                             eNullIterator              = 130,
                             eNotInBlock                = 131,
                             eOwnerNotInDatabase        = 132,
                             eOwnerNotOpenForRead       = 133,
                             eOwnerNotOpenForWrite      = 134,
                             eExplodeBeforeTransform    = 135,
                             eCannotScaleNonUniformly   = 136,
                             eNotInDatabase             = 137,
                             eNotCurrentDatabase        = 138,
                             eIsAnEntity                = 139,

			     eCannotChangeActiveViewport = 140,
			     eNotInPaperspace           = 141,
			     eCommandWasInProgress      = 142,
                             
                             eGeneralModelingFailure    = 150,
                             eOutOfRange                = 151,
                             eNonCoplanarGeometry       = 152,
                             eDegenerateGeometry        = 153,
                             eInvalidAxis               = 154,
                             ePointNotOnEntity          = 155,
                             eSingularPoint             = 156,
                             eInvalidOffset             = 157,
			     eNonPlanarEntity           = 158,
			     eCannotExplodeEntity       = 159,

                             eStringTooLong             = 160,
                             eInvalidSymTableFlag       = 161,
                             eUndefinedLineType         = 162,
                             eInvalidTextStyle          = 163,
                             eTooFewLineTypeElements    = 164,
                             eTooManyLineTypeElements   = 165,
                             eExcessiveItemCount        = 166,
                             eIgnoredLinetypeRedef      = 167,
                             eBadUCS                    = 168,
                             eBadPaperspaceView         = 169,

                             eSomeInputDataLeftUnread   = 170,
                             eNoInternalSpace           = 171,
                             eInvalidDimStyle           = 172,
                             eInvalidLayer              = 173,

                             eUserBreak                 = 180,

			     eDwgNeedsRecovery          = 190,
			     eDeleteEntity              = 191,
			     eInvalidFix                = 192,
                             eFSMError                  = 193,

			     eBadLayerName              = 200,
			     eLayerGroupCodeMissing     = 201,
			     eBadColorIndex             = 202,
			     eBadLinetypeName           = 203,
			     eBadLinetypeScale          = 204,
			     eBadVisibilityValue        = 205,
                             eProperClassSeparatorExpected = 206,

                             ePagerError                = 210,
                             eOutOfPagerMemory          = 211,
                             ePagerWriteError           = 212,
			     eWasNotForwarding          = 213,

			     eInvalidIdMap              = 220,
			     eInvalidOwnerObject        = 221,
			     eOwnerNotSet               = 222,

			     eWrongSubentityType        = 230,

                             eNoActiveTransactions      = 250,
                             eNotTopTransaction         = 251,
			     eTransactionOpenWhileCommandEnded =  252,
			     eInProcessOfCommitting     = 253,
			     eNotNewlyCreated           = 254,

			     eAlreadyInGroup            = 260,
			     eNotInGroup                = 261,

                             eInvalidREFIID             = 290,
                             eInvalidNormal             = 291,
                             eInvalidStyle              = 292,

                             eCannotRestoreFromAcisFile = 300,
			     eMakeMeProxy		= 301,
                             eNLSFileNotAvailable       = 302,
                             eNotAllowedForThisProxy    = 303,

                             eNotSupportedInDwgApi      = 310,
                             ePolyWidthLost             = 311,
                             eNullExtents               = 312,
                             eExplodeAgain              = 313

            };
};

struct AcDb
{
    enum OpenMode          { kForRead           = 0,
                             kForWrite          = 1,
                             kForNotify         = 2 };

    enum FileVersion       { kR12               = 0,
                             kR13               = 1,
                             kR13Custom         = 2,
                             kMaxVersion        = 500 }; 

    enum CoordAxis         { kX                 = 0,
                             kY                 = 1,
                             kZ                 = 2 };

    enum CoordSystem       { kWorldCS           = 0,
                             kUserCS            = 1,
                             kCurDisplayCS      = 2,
                             kPaperDisplayCS    = 3,
                             kEntityCS          = 4 };

    enum Intersect         { kOnBothOperands    = 0,
                             kExtendThis        = 1,
                             kExtendArg         = 2,
                             kExtendBoth        = 3 };

    enum Visibility        { kInvisible         = 1,
                             kVisible           = 0 };

    typedef Adesk::Int16 DxfCode;
    enum                   { kDxfInvalid        = -9999,
			     kDxfXDictionary     = -6,
			     kDxfPReactors       = -5,
                             kDxfUndo            = -4,
                             kDxfXDataStart      = -3,
                             kDxfHeaderId        = -2,
                             kDxfFirstEntId      = -2,
                             kDxfEnd             = -1,
                             kDxfStart           = 0,
                             kDxfText            = 1,
                             kDxfShapeName       = 2,
                             kDxfBlockName       = 2,
                             kDxfAttributeTag    = 2,
			     kDxfSymbolTableName = 2,
                             kDxfMstyleName      = 2,
			     kDxfSymTableRecName = 2,
                             kDxfAttributePrompt = 3,
                             kDxfDimStyleName    = 3,
                             kDxfXRefPath        = 3,
			     kDxfLinetypeProse   = 3,
			     kDxfTextFontFile    = 3,
                             kDxfDescription     = 3,
			     kDxfDimPostStr      = 3,
			     kDxfTextBigFontFile = 4,
			     kDxfDimAPostStr     = 4,
			     kDxfCLShapeName     = 4,
                             kDxfHandle          = 5,
			     kDxfDimBlk          = 5,
			     kDxfDimBlk1         = 6,
                             kDxfLinetypeName    = 6,
			     kDxfDimBlk2         = 7,
                             kDxfTextStyleName   = 7,
                             kDxfLayerName       = 8,
			     kDxfCLShapeText     = 9,

                             kDxfXCoord         = 10,
    
                             kDxfYCoord         = 20,
    
                             kDxfZCoord         = 30,

                             kDxfElevation      = 38,
                             kDxfThickness      = 39,

                             kDxfReal           = 40,
			     kDxfViewportHeight = 40,
			     kDxfTxtSize        = 40,
			     kDxfTxtStyleXScale = 41,
			     kDxfViewWidth      = 41,
			     kDxfViewportAspect = 41,
			     kDxfTxtStylePSize  = 42,
			     kDxfViewLensLength = 42,
			     kDxfViewFrontClip  = 43,
			     kDxfViewBackClip   = 44,
			     kDxfShapeXOffset   = 44,
			     kDxfShapeYOffset   = 45,
			     kDxfShapeScale     = 46,
			     kDxfPixelScale     = 47,

                             kDxfLinetypeScale  = 48,

			     kDxfDashLength     = 49,
                             kDxfMlineOffset    = 49,
                             kDxfLinetypeElement = 49,

                             kDxfAngle          = 50,
			     kDxfViewportSnapAngle = 50,
			     kDxfViewportTwist  = 51,

			     kDxfVisibility     = 60,
                             kDxfLayerLinetype  = 61,
                             kDxfColor          = 62,
                             // Removed codes intended
                             // only for internal
                             // use:  63-65
                             kDxfHasSubentities = 66,
                             kDxfViewportVisibility = 67,
                             kDxfViewportActive = 68,
                             kDxfViewportNumber = 69,

                             kDxfInt16          = 70,
			     kDxfViewMode       = 71,
			     kDxfCircleSides    = 72,
			     kDxfViewportZoom   = 73,
			     kDxfViewportIcon   = 74,
			     kDxfViewportSnap   = 75,
			     kDxfViewportGrid   = 76,
			     kDxfViewportSnapStyle= 77,
			     kDxfViewportSnapPair= 78,

                             kDxfRegAppFlags    = 71,

                             kDxfTxtStyleFlags  = 71,
			     kDxfLinetypeAlign  = 72,
			     kDxfLinetypePDC    = 73,

			     kDxfInt32          = 90,

                             // Subclass Section Marker
                             //
                             // to be followed by subclass name.
                             //
                             kDxfSubclass       = 100,
			     kDxfControlString  = 102,

			     // DimVarTableRecords have been using 5 for a
			     // string value.  With R13, they get a handle
			     // value as well.  Since 5 is already in use,
			     // we use 105 for this special case.
                             //
			     kDxfDimVarHandle = 105,

                             kDxfXReal          = 140,

                             kDxfXInt16         = 170,

                             kDxfNormalX        = 210,
                             kDxfNormalY        = 220,
                             kDxfNormalZ        = 230,

			     kDxfXXInt16        = 270,

                             kDxfInt8           = 280,

			     //  More string values 300-309
                             kDxfXTextString    = 300,

			     //  Arbitrary Binary Chunks 310-319
                             kDxfBinaryChunk   = 310,
                 
			     //  Arbitrary Object Handles 320-329
			     kDxfArbHandle  = 320,

                             kDxfSoftPointerId   = 330,  // 330-339
                             kDxfHardPointerId   = 340,  // 340-349
                             kDxfSoftOwnershipId = 350,  // 350-359
                             kDxfHardOwnershipId = 360,  // 360-369

                             kDxfComment        = 999,

                             kDxfXdAsciiString  = 1000,
                             kDxfRegAppName     = 1001,
                             kDxfXdControlString = 1002,
                             kDxfXdLayerName    = 1003,
                             kDxfXdBinaryChunk  = 1004,
                             kDxfXdHandle       = 1005,

                             kDxfXdXCoord       = 1010,
                             kDxfXdYCoord       = 1020,
                             kDxfXdZCoord       = 1030,

                             kDxfXdWorldXCoord  = 1011,
                             kDxfXdWorldYCoord  = 1021,
                             kDxfXdWorldZCoord  = 1031,

                             kDxfXdWorldXDisp   = 1012,
                             kDxfXdWorldYDisp   = 1022,
                             kDxfXdWorldZDisp   = 1032,

                             kDxfXdWorldXDir    = 1013,
                             kDxfXdWorldYDir    = 1023,
                             kDxfXdWorldZDir    = 1033,

                             kDxfXdReal         = 1040,
                             kDxfXdDist         = 1041,
                             kDxfXdScale        = 1042,

                             kDxfXdInteger16    = 1070,
                             kDxfXdInteger32    = 1071 };

    // Primitives.
    //
    enum DwgDataType       { kDwgNull            = 0,
                             kDwgReal            = 1,
                             kDwgInt32           = 2,
                             kDwgInt16           = 3,
                             kDwgInt8            = 4,
                             kDwgText            = 5,
                             kDwgBChunk          = 6,
                             kDwgHandle          = 7,
                             kDwgHardOwnershipId = 8,
                             kDwgSoftOwnershipId = 9,
                             kDwgHardPointerId   = 10,
                             kDwgSoftPointerId   = 11,
                             kDwg3Real           = 12,
                             kDwgNotRecognized   = 19 };

#if defined(RADPACK)
#pragma pack(1)
#endif /* RADPACK */

#ifdef RADPACK
#pragma pack( )
#endif
                             
    // OsnapMask:  Specifies Osnap Operation.
    //
    enum OsnapMask         { kOsMaskEnd          = 1,
			     kOsMaskMid          = 2,
			     kOsMaskCen          = 4,
			     kOsMaskNode         = 8,
			     kOsMaskQuad         = 0x10,
			     kOsMaskInt          = 0x20,
			     kOsMaskIns          = 0x40,
			     kOsMaskPerp         = 0x80,
			     kOsMaskTan          = 0x100,
			     kOsMaskNear         = 0x200,
			     kOsMaskQuick        = 0x400,
			     kOsMaskApint        = 0x800,
			     kOsMaskImmediate    = 0x10000,
			     kOsMaskAllowTan     = 0x20000,
			     kOsMaskDisablePerp  = 0x40000,
			     kOsMaskRelCartesian = 0x80000,
			     kOsMaskRelPolar     = 0x100000 };

    // OsnapMode:  Specifies Object query.
    //             Binary and Virtual Operations not represented.
    //
    enum OsnapMode         { kOsModeEnd          = 1,
			     kOsModeMid          = 2,
			     kOsModeCen          = 3,
			     kOsModeNode         = 4,
			     kOsModeQuad         = 5, 
			     kOsModeIns          = 7,
			     kOsModePerp         = 8,
			     kOsModeTan          = 9,
			     kOsModeNear         = 10 };

    enum ShowImagesMode    { kNeverShow     = 0,
			     			 kAlwaysShow      = 1,
                             kBoundingBoxShow = 2 };

    enum SaveImagesMode    { kNeverSave     = 0,
			     			 kAlwaysSave      = 1 };

    enum TextHorzMode      { kTextLeft    = 0,   // TH_LEFT,
			     kTextCenter  = 1,   // TH_CENT,
			     kTextRight   = 2,   // TH_RIGHT,
			     kTextAlign   = 3,   // THV_ALIGN,
			     kTextMid     = 4,   // THV_MID,
			     kTextFit     = 5 }; // THV_FIT
 
    enum TextVertMode      { kTextBase    = 0,   // TV_BASE,
                             kTextBottom  = 1,   // TV_BOT,
                             kTextVertMid = 2,   // TV_MID,
                             kTextTop     = 3 }; // TV_TOP
 
    enum Planarity         { kNonPlanar = 0,
			     kPlanar    = 1,
			     kLinear    = 2 };

    enum PointIndex        { kMPoint1    = 0,
                             kMPoint2    = 1,
                             kMPoint3    = 2,
                             kMPoint4    = 3 };

    enum EdgeIndex         { kMEdge1    = 0,
                             kMEdge2    = 1,
                             kMEdge3    = 2,
                             kMEdge4    = 3 };

    enum Poly2dType        { k2dSimplePoly      = 0,
                             k2dFitCurvePoly    = 1,
                             k2dQuadSplinePoly  = 2,
                             k2dCubicSplinePoly = 3 };

    enum Poly3dType        { k3dSimplePoly      = 0,
                             k3dQuadSplinePoly  = 1,
                             k3dCubicSplinePoly = 2 };

    enum PolyMeshType      { kSimpleMesh        = 0,
                             kQuadSurfaceMesh   = 5,
                             kCubicSurfaceMesh  = 6,
                             kBezierSurfaceMesh = 8 };

    enum Vertex2dType      { k2dVertex          = 0,
                             k2dSplineCtlVertex = 1,
                             k2dSplineFitVertex = 2,
                             k2dCurveFitVertex =  3 };

    enum Vertex3dType      { k3dSimpleVertex    = 0,
                             k3dControlVertex   = 1,
                             k3dFitVertex       = 2 };

    enum SpaceValueType    { kUndefined,
                             kStubPtr,
                             kEndOfFile,
                             kBackwardBranch,
                             kForwardBranch,
                             kDetour };

    enum BoolOperType      { kBoolUnite      = 0, 
			     kBoolIntersect  = 1, 
			     kBoolSubtract   = 2 };

    typedef Adesk::UInt32    SubentType;
    enum                   { kNullSubentType   = 0,
			     kFaceSubentType   = 1,
			     kEdgeSubentType   = 2,
			     kVertexSubentType = 3, 

////////////////////////////////////////////////////////////
                                                          //
                   // Mline specific type                 //
                                                          //
                             kMlineSubentCache = 4        //  Beauty is in the eye
                                                          //   of the beholder.
                                                          //
////////////////////////////////////////////////////////////
    
};

    typedef Adesk::UInt32    GeomId;
    enum                   { kNoGeom = 0 };

    enum GeomType          { kInvalidGeom = 0,
			     kPointGeom,
			     kLineGeom,
			     kCircleGeom,
			     kPlaneGeom };

    enum FilerType         { kFileFiler     = 0,
			     kCopyFiler     = 1,
			     kUndoFiler     = 2,
			     kBagFiler      = 3,
                             kIdXlateFiler      = 4,
                             kPageFiler         = 5,
			     kDeepCloneFiler    = 6,
			     kIdFiler           = 7,
			     kPurgeFiler        = 8,
			     kWblockCloneFiler  = 9 };

    enum FilerSeekType     { kSeekFromStart   = 0,
                             kSeekFromCurrent = 1,
                             kSeekFromEnd     = 2 };

    enum AcDbDwgVersion    { kDHL_MC0_0   = 0,
                             kDHL_AC1_2   = 1,
                             kDHL_AC1_40  = 2,
                             kDHL_AC1_50  = 3,
                             kDHL_AC2_20  = 4,
                             kDHL_AC2_10  = 5,
                             kDHL_AC2_21  = 6,
                             kDHL_AC2_22  = 7,
                             kDHL_1001    = 8,
                             kDHL_1002    = 9,      // AutoCAD 2.5
                             kDHL_1003    = 10,     // AutoCAD 2.6
                             kDHL_1004    = 11,     // Release 9
                             kDHL_1005    = 12,
                             kDHL_1006    = 13,     // Release 10
                             kDHL_1007    = 14,
                             kDHL_1008    = 15,
                             kDHL_1009    = 16,     // R11 and R12
                             kDHL_1010    = 17,
                             kDHL_1011    = 18,
                             kDHL_1012    = 19,     // R13
                             kDHL_1013    = 20,     // R14 mid version.
                             kDHL_1014    = 21,     // R14 final version.
                             kDHL_CURRENT = kDHL_1014,
                             kDHL_Unknown = 32766,
                             kDHL_Max     = 32767 };

    enum MaintenanceReleaseVersion
                           { kMRelease0         = 0,  // kDHL_1012 = R13c0-3
                             kMRelease1         = 1,  // kDHL_1012 = R13c0-3
                             kMRelease2         = 2,
                             kMRelease3         = 3,
			     kMRelease4         = 4,    // kDHL_1012 = R13c4
                             // kDHL_1013, kMRelease0 = Sedona s000..s045
                             // kDHL_1013, kMRelease1 = Sedona s046..s050
                             // kDHL_1013, kMRelease2 = Sedona s051..s052
                             // kDHL_1013, kMRelease3 = Sedona s053..s054
                             // kDHL_1013, kMRelease4 = Sedona s055..s059
                             // kDHL_1013, kMRelease5 = Sedona s060..s063
                             // kDHL_1013, kMRelease6 = Sedona s064..
			     kMRelease5         = 5,    // kDHL_1012 = R13c4_m
			     kMRelease6         = 6,    // kDHL_1012 = R13c4a
                             kMReleaseCurrent   = kMRelease0,
                             kMReleaseUnknown   = 126,
                             kMReleaseMax       = 127 };

    enum SaveType          { kNoSave = 0,
                             kR12Save,
                             kR13Save };

    enum GroupOperType     { kNoOp           = 0,
			     kAdd            = 1,
                             kRemove         = 2,
                             kRename         = 3,
                             kOrdered        = 4,       // Members reordered
                             kGrpDesc        = 5,       // Description Modified
                             kSelect         = 6,       // Selectibility flag
                             kCreate         = 7,       // New group creation
                             kPrepend        = 8,
                             kInsert         = 9,
                             kGrpFlags       = 10 };     

    // kDcInsert     => Database INSERT in which entities from the source
    //                  database could be moved into the destination database.
    // kDcInsertCopy => Database INSERT in which the source database is left
    //                  intact. Objects are copied to the destination database.
    //
    enum DeepCloneType     { kDcCopy           = 0,
			     kDcExplode        = 1,
			     kDcBlock          = 2,
			     kDcXrefBind       = 3,
			     kDcSymTableMerge  = 4,
			     kDcInsert         = 6,
			     kDcWblock         = 7,
			     kDcObjects        = 8,
			     kDcXrefInsert     = 9,
			     kDcInsertCopy     = 10 };

    enum XrefStatus        { kXrfNotAnXref     = 0,
                             kXrfResolved      = 1,
			     kXrfUnloaded      = 2,
			     kXrfUnreferenced  = 3,
			     kXrfFileNotFound  = 4,
			     kXrfUnresolved    = 5 };

    enum MeasurementValue {
		kEnglish = 0,
		kMetric	 = 1,
    };


};

#endif
