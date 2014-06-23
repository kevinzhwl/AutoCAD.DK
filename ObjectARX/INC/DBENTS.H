#ifndef AD_DBENTS_H
#define AD_DBENTS_H
//
//  dbents.h - Exported pre-R13 objects
//
//  Copyright 1993-1997 by Autodesk, Inc.
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
//  DESCRIPTION: Exported pre-R13 Entity classes
//
//  AcRxObject
//    AcDbObject
//      AcDbEntity
//        AcDbText
//          AcDbAttribute
//          AcDbAttributeDefinition
//        AcDbBlockBegin
//        AcDbBlockEnd
//        AcDbSequenceEnd
//        AcDbBlockReference
//          AcDbMInsertBlock
//        AcDbVertex
//          AcDb2dVertex
//          AcDb3dPolylineVertex
//          AcDbPolygonMeshVertex
//          AcDbPolyFaceMeshVertex
//          AcDbFaceRecord
//        AcDbCurve
//          AcDb2dPolyline
//          AcDb3dPolyline
//          AcDbArc
//          AcDbCircle
//          AcDbLine
//        AcDbDimension
//          AcDbOrdinateDimension
//          AcDbAlignedDimension
//            AcDbRotatedDimension
//          AcDb3PointAngularDimension
//          AcDb2LineAngularDimension
//          AcDbRadialDimension
//          AcDbDiametricDimension
//        AcDbPoint
//        AcDbFace
//        AcDbPolyFaceMesh
//        AcDbPolygonMesh
//        AcDbTrace
//        AcDbSolid
//        AcDbShape
//        AcDbViewport
//

#include "dbmain.h"
#include "dbcurve.h"
#include "gescl3d.h"
#include "gepnt2d.h"
#include "dbmtext.h"

class AcDbAttribute;
class AcDbSequenceEnd;
class AcDb3dPolylineVertex;
class AcDb2dVertex;
class AcGePoint2dArray;
class AcGeDoubleArray;

class AcDbText: public AcDbEntity
{
public:
    AcDbText();
    AcDbText(
        const AcGePoint3d&  position,
        const char*         text,
        AcDbObjectId        style = AcDbObjectId::kNull,
        double              height = 0,
        double              rotation = 0);
    ~AcDbText();
    ACDB_DECLARE_MEMBERS(AcDbText);

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&);

    AcGePoint3d         alignmentPoint() const;
    Acad::ErrorStatus   setAlignmentPoint(const AcGePoint3d&);
    Adesk::Boolean      isDefaultAlignment() const;

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    double              rotation() const; 
    Acad::ErrorStatus   setRotation(double);

    double              height() const; 
    Acad::ErrorStatus   setHeight(double);

    double              widthFactor() const; 
    Acad::ErrorStatus   setWidthFactor(double);

    char*               textString() const;
    Acad::ErrorStatus   setTextString(const char*);
     
    AcDbObjectId        textStyle() const;
    Acad::ErrorStatus   setTextStyle(AcDbObjectId);
    
    Adesk::Boolean      isMirroredInX() const;
    Acad::ErrorStatus   mirrorInX(Adesk::Boolean);
     
    Adesk::Boolean      isMirroredInY() const;
    Acad::ErrorStatus   mirrorInY(Adesk::Boolean);
     
    AcDb::TextHorzMode  horizontalMode() const;
    Acad::ErrorStatus   setHorizontalMode(AcDb::TextHorzMode);
     
    AcDb::TextVertMode  verticalMode() const;
    Acad::ErrorStatus   setVerticalMode(AcDb::TextVertMode);

    int                 correctSpelling();
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbText);

class AcDbAttribute: public AcDbText
{
public:
    AcDbAttribute();
    AcDbAttribute(
        const AcGePoint3d& position,
        const char*        text,
        const char*        tag,
        AcDbObjectId       style = AcDbObjectId::kNull);
    ~AcDbAttribute();
    ACDB_DECLARE_MEMBERS(AcDbAttribute);

    char*		tag() const;
    Acad::ErrorStatus   setTag(const char* newTag);

    Adesk::Boolean	isInvisible() const;
    Acad::ErrorStatus   setInvisible(Adesk::Boolean);

    Adesk::Boolean      isConstant() const;
    Adesk::Boolean      isVerifiable() const;
    Adesk::Boolean      isPreset() const;

    Adesk::UInt16	fieldLength() const;
    Acad::ErrorStatus   setFieldLength(Adesk::UInt16);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbAttribute);

class AcDbAttributeDefinition: public AcDbText
{
public:
    AcDbAttributeDefinition();
    AcDbAttributeDefinition(
        const AcGePoint3d& position,
        const char*        text,
        const char*        tag,
        const char*        prompt,
        AcDbObjectId       style = AcDbObjectId::kNull);
    ~AcDbAttributeDefinition();
    ACDB_DECLARE_MEMBERS(AcDbAttributeDefinition);

    char*		prompt() const;
    Acad::ErrorStatus   setPrompt(const char*);
     
    char*		tag() const;
    Acad::ErrorStatus   setTag(const char*);
 
    Adesk::Boolean	isInvisible() const;
    Acad::ErrorStatus   setInvisible(Adesk::Boolean);
 
    Adesk::Boolean	isConstant() const;
    Acad::ErrorStatus   setConstant(Adesk::Boolean);
 
    Adesk::Boolean	isVerifiable() const;
    Acad::ErrorStatus   setVerifiable(Adesk::Boolean);
 
    Adesk::Boolean      isPreset() const;
    Acad::ErrorStatus   setPreset(Adesk::Boolean);
     
    Adesk::UInt16	fieldLength() const;
    Acad::ErrorStatus   setFieldLength(Adesk::UInt16);

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbAttributeDefinition);

class AcDbBlockReference: public AcDbEntity
{
public:
    AcDbBlockReference();
    AcDbBlockReference(const AcGePoint3d&  position,
                             AcDbObjectId  blockTableRec);
    ~AcDbBlockReference();
    ACDB_DECLARE_MEMBERS(AcDbBlockReference);

    AcDbObjectId      blockTableRecord() const;
    Acad::ErrorStatus setBlockTableRecord(AcDbObjectId);

    AcGePoint3d       position() const;
    Acad::ErrorStatus setPosition(const AcGePoint3d&);

    AcGeScale3d       scaleFactors() const;
    Acad::ErrorStatus setScaleFactors(const AcGeScale3d& scale);
 
    double            rotation() const;
    Acad::ErrorStatus setRotation(double newVal);
 
    AcGeVector3d      normal() const;
    Acad::ErrorStatus setNormal(const AcGeVector3d& newVal);

    AcGeMatrix3d      blockTransform() const;
    Acad::ErrorStatus setBlockTransform(const AcGeMatrix3d&);

    Acad::ErrorStatus appendAttribute(AcDbAttribute*);
    Acad::ErrorStatus appendAttribute(AcDbObjectId&, AcDbAttribute*);

    Acad::ErrorStatus openAttribute(AcDbAttribute*&, AcDbObjectId,
                                    AcDb::OpenMode,
                                    Adesk::Boolean  openErasedOne = Adesk::kFalse);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  attributeIterator() const;

    // Subentity acquisition.
    //
    virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(
                                  AcDb::SubentType,
	                          int                   gsMark,
                                  const AcGePoint3d&    pickPoint,
	                          const AcGeMatrix3d&   viewXform,
                                  int&                  numPaths,
	                          AcDbFullSubentPath*&  subentPaths,
                                  int                   numInserts = 0,
	                          AcDbObjectId*         entAndInsertStack = NULL) const;

    virtual  Acad::ErrorStatus getGsMarkersAtSubentPath(
	                          const AcDbFullSubentPath& subPath,
                                  AcDbIntArray&             gsMarkers) const;

    virtual Acad::ErrorStatus highlight  (const AcDbFullSubentPath&
					  = kNullSubent) const;

    virtual Acad::ErrorStatus unhighlight(const AcDbFullSubentPath&
					  = kNullSubent) const;

    virtual AcDbEntity*       subentPtr  (const AcDbFullSubentPath&) const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbBlockReference);

class AcDbMInsertBlock: public AcDbBlockReference
{
public:
    AcDbMInsertBlock();
    AcDbMInsertBlock(
        const AcGePoint3d&  position,
        AcDbObjectId        blockTableRec,
        Adesk::UInt16       columns,
        Adesk::UInt16       rows,
        double              colSpacing,
        double              rowSpacing);
    ~AcDbMInsertBlock();
    ACDB_DECLARE_MEMBERS(AcDbMInsertBlock);

    Adesk::UInt16      columns() const;
    Acad::ErrorStatus  setColumns(Adesk::UInt16);
 
    Adesk::UInt16      rows() const;
    Acad::ErrorStatus  setRows(Adesk::UInt16);
 
    double	       columnSpacing() const;
    Acad::ErrorStatus  setColumnSpacing(double);
 
    double	       rowSpacing() const;
    Acad::ErrorStatus  setRowSpacing(double);
};

class AcDbBlockBegin: public AcDbEntity
{
public:
    AcDbBlockBegin();
    ~AcDbBlockBegin();
    ACDB_DECLARE_MEMBERS(AcDbBlockBegin);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbBlockBegin);

class AcDbBlockEnd: public AcDbEntity
{
public:
    AcDbBlockEnd();
    ~AcDbBlockEnd();
    ACDB_DECLARE_MEMBERS(AcDbBlockEnd);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbBlockEnd);

class AcDbSequenceEnd: public AcDbEntity
{
public:
    AcDbSequenceEnd();
    ~AcDbSequenceEnd();
    ACDB_DECLARE_MEMBERS(AcDbSequenceEnd);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbSequenceEnd);

class AcDbVertex: public AcDbEntity
{
public:
    AcDbVertex();
    ~AcDbVertex();
    ACDB_DECLARE_MEMBERS(AcDbVertex);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbVertex);

class AcDb2dVertex: public AcDbVertex
{
public:
    AcDb2dVertex();
    ~AcDb2dVertex();
    ACDB_DECLARE_MEMBERS(AcDb2dVertex);
    AcDb2dVertex(
        const AcGePoint3d&  position,
	double   bulge      = 0,
	double   startWidth = 0,
	double   endWidth   = 0,
	double   tangent    = 0);

    AcDb::Vertex2dType vertexType() const;

#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    void               setVertexType(AcDb::Vertex2dType newType);
#endif /* ACDBLIB */

    // This method accesses the position in ECS.  See AcDb2dPolyline for WCS.
    //
    AcGePoint3d		position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

    double		startWidth() const; 
    Acad::ErrorStatus   setStartWidth(double newVal);

    double		endWidth() const; 
    Acad::ErrorStatus   setEndWidth(double newVal);

    double		bulge() const; 
    Acad::ErrorStatus   setBulge(double newVal);

    Adesk::Boolean	isTangentUsed() const;
    Acad::ErrorStatus   useTangent();
    Acad::ErrorStatus   ignoreTangent();

    double		tangent() const; 
    Acad::ErrorStatus   setTangent(double newVal);

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb2dVertex);

class AcDb3dPolylineVertex: public AcDbVertex
{
public:
    AcDb3dPolylineVertex();
    ~AcDb3dPolylineVertex();
    ACDB_DECLARE_MEMBERS(AcDb3dPolylineVertex);
    AcDb3dPolylineVertex(const AcGePoint3d&);

    AcDb::Vertex3dType vertexType() const;

#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    void            setVertexType(AcDb::Vertex3dType newType);
#endif /* ACDBLIB */

    AcGePoint3d		position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb3dPolylineVertex);

class AcDbPolygonMeshVertex: public AcDbVertex
{
public:
    AcDbPolygonMeshVertex();
    AcDbPolygonMeshVertex(const AcGePoint3d&  position);
    ~AcDbPolygonMeshVertex();
    ACDB_DECLARE_MEMBERS(AcDbPolygonMeshVertex);

    AcDb::Vertex3dType vertexType() const;

#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    void            setVertexType(AcDb::Vertex3dType newType);
#endif /* ACDBLIB */

    AcGePoint3d		position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbPolygonMeshVertex);

class AcDbPolyFaceMeshVertex: public AcDbVertex
{
public:
    AcDbPolyFaceMeshVertex();
    AcDbPolyFaceMeshVertex(const AcGePoint3d&  position);
    ~AcDbPolyFaceMeshVertex();
    ACDB_DECLARE_MEMBERS(AcDbPolyFaceMeshVertex);

    AcDb::Vertex3dType vertexType() const;

#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    void            setVertexType(AcDb::Vertex3dType newType);
#endif /* ACDBLIB */


    AcGePoint3d		position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbPolyFaceMeshVertex);

class AcDbFaceRecord: public AcDbVertex
{
public:
    AcDbFaceRecord();
    // Use negative values to indicate invisible faces
    AcDbFaceRecord(Adesk::Int16 vtx0, Adesk::Int16 vtx1,
		   Adesk::Int16 vtx2, Adesk::Int16 vtx3);
    ~AcDbFaceRecord();
    ACDB_DECLARE_MEMBERS(AcDbFaceRecord);

    // Input index must be 0-3.
    //
    Acad::ErrorStatus getVertexAt(Adesk::UInt16 faceIdx,
                                  Adesk::Int16& vtxIdx) const;
    Acad::ErrorStatus setVertexAt(Adesk::UInt16 faceIdx,
                                  Adesk::Int16  vtxIdx);

    Acad::ErrorStatus isEdgeVisibleAt(Adesk::UInt16 faceIndex,
                                      Adesk::Boolean& visible) const;

    Acad::ErrorStatus makeEdgeVisibleAt(Adesk::UInt16 faceIndex);
    Acad::ErrorStatus makeEdgeInvisibleAt(Adesk::UInt16 faceIndex);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbFaceRecord);

class AcDb2dPolyline: public AcDbCurve
{
public:
    AcDb2dPolyline();
    ~AcDb2dPolyline();
    ACDB_DECLARE_MEMBERS(AcDb2dPolyline);
    AcDb2dPolyline (
        AcDb::Poly2dType  type,
        AcGePoint3dArray& vertices,
        double            elevation     = 0,
        Adesk::Boolean    closed        = Adesk::kFalse,
        double            defStartWidth = 0,
        double            defEndWidth   = 0,
        AcGeDoubleArray*  bulges        = NULL);

    DBCURVE_METHODS

    AcDb::Poly2dType	polyType() const;
    Acad::ErrorStatus   setPolyType(AcDb::Poly2dType);

    Acad::ErrorStatus   makeClosed();
    Acad::ErrorStatus   makeOpen();
 
    double		defaultStartWidth() const;
    Acad::ErrorStatus   setDefaultStartWidth(double);

    double              defaultEndWidth() const;
    Acad::ErrorStatus   setDefaultEndWidth(double);

    double		thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double		elevation() const;
    Acad::ErrorStatus   setElevation(double);

    Adesk::Boolean	isLinetypeGenerationOn() const;
    Acad::ErrorStatus   setLinetypeGenerationOn();
    Acad::ErrorStatus   setLinetypeGenerationOff();

    // Vertex access
    Acad::ErrorStatus appendVertex(AcDb2dVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDb2dVertex*);
    Acad::ErrorStatus openVertex(AcDb2dVertex*&, AcDbObjectId    vertId,
                                 AcDb::OpenMode,
                                 Adesk::Boolean openErasedOne = Adesk::kFalse);
    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;

    // Vertex position in WCS
    //
    AcGePoint3d       vertexPosition(const AcDb2dVertex& vert) const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb2dPolyline);

class AcDb3dPolyline: public AcDbCurve
{
public:
    AcDb3dPolyline();
    ~AcDb3dPolyline();
    ACDB_DECLARE_MEMBERS(AcDb3dPolyline);
    AcDb3dPolyline(AcDb::Poly3dType, AcGePoint3dArray& vertices,
		   Adesk::Boolean closed = Adesk::kFalse);

    DBCURVE_METHODS

    Acad::ErrorStatus   makeClosed();
    Acad::ErrorStatus   makeOpen();
 
    AcDb::Poly3dType    polyType() const;
    Acad::ErrorStatus   setPolyType(AcDb::Poly3dType);

    // Vertex access
    //
    Acad::ErrorStatus appendVertex(AcDb3dPolylineVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDb3dPolylineVertex*);

    Acad::ErrorStatus openVertex(AcDb3dPolylineVertex*&, AcDbObjectId vertId,
                                 AcDb::OpenMode,
                                 Adesk::Boolean openErasedOne = Adesk::kFalse);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator* vertexIterator() const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb3dPolyline);

class AcDbArc: public AcDbCurve
{
public:
    AcDbArc();
    AcDbArc(const AcGePoint3d& center, double radius,
            double startAngle, double endAngle);
    AcDbArc(const AcGePoint3d& center, const AcGeVector3d& normal,
            double radius, double startAngle, double endAngle);
    ~AcDbArc();
    ACDB_DECLARE_MEMBERS(AcDbArc);

    DBCURVE_METHODS

    Acad::ErrorStatus getTransformedCopy(
	              const AcGeMatrix3d& xform, 
                      AcDbEntity*& ent) const;

    AcGePoint3d         center() const;
    Acad::ErrorStatus	setCenter(const AcGePoint3d&); 

    double              radius() const;
    Acad::ErrorStatus	setRadius(double);

    double              startAngle() const;
    Acad::ErrorStatus	setStartAngle(double);

    double              endAngle() const;
    Acad::ErrorStatus	setEndAngle(double);

    double              thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbArc);

class AcDbCircle: public AcDbCurve
{
public:
    AcDbCircle();
    AcDbCircle(const AcGePoint3d& cntr, const AcGeVector3d& nrm, double radius);
    ~AcDbCircle();
    ACDB_DECLARE_MEMBERS(AcDbCircle);

    DBCURVE_METHODS

    Acad::ErrorStatus getTransformedCopy(
                         const AcGeMatrix3d& xform, 
                         AcDbEntity*& ent) const;

    AcGePoint3d         center() const;
    Acad::ErrorStatus	setCenter(const AcGePoint3d&); 

    double              radius() const;
    Acad::ErrorStatus	setRadius(double);

    double              thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbCircle);


class AcDbLine: public AcDbCurve
{
public:
    AcDbLine();
    AcDbLine(const AcGePoint3d& start, const AcGePoint3d& end);
    ~AcDbLine();
    ACDB_DECLARE_MEMBERS(AcDbLine);

    DBCURVE_METHODS

    Acad::ErrorStatus getTransformedCopy(
	                    const AcGeMatrix3d& xform, 
                            AcDbEntity*& ent) const;

    AcGePoint3d         startPoint() const;
    Acad::ErrorStatus	setStartPoint(const AcGePoint3d&); 

    AcGePoint3d         endPoint() const;
    Acad::ErrorStatus	setEndPoint(const AcGePoint3d&); 

    double              thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbLine);

class AcDbDimension: public AcDbEntity
{
public:
    AcDbDimension();
    ~AcDbDimension();
    ACDB_DECLARE_MEMBERS(AcDbDimension);

    AcGePoint3d      	textPosition() const; 
    Acad::ErrorStatus	setTextPosition(const AcGePoint3d&); 

    Adesk::Boolean	isUsingDefaultTextPosition() const;
    Acad::ErrorStatus	useSetTextPosition();
    Acad::ErrorStatus	useDefaultTextPosition();

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);

    char*		dimensionText() const; 
    Acad::ErrorStatus	setDimensionText(const char*);
     
    double		textRotation() const;
    Acad::ErrorStatus	setTextRotation(double);
 
    AcDbObjectId	dimensionStyle() const;
    Acad::ErrorStatus	setDimensionStyle(AcDbObjectId);
 
    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& getData) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* newData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newData);

    virtual void	erased(AcDbObject* dbObj, Adesk::Boolean bErasing);
    virtual void        objectClosed(const AcDbObjectId dbObj);

    double              horizontalRotation() const;
    Acad::ErrorStatus	setHorizontalRotation(double newVal);
 
    // Functions for accessing the Dimension's defining block
    //
    AcDbObjectId     	dimBlockId() const;
    Acad::ErrorStatus	setDimBlockId(const AcDbObjectId&);
    AcGePoint3d      	dimBlockPosition() const;
    Acad::ErrorStatus	setDimBlockPosition(const AcGePoint3d&);
    Acad::ErrorStatus	recomputeDimBlock(Adesk::Boolean forceUpdate = Adesk::kTrue);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbDimension);

class AcDbOrdinateDimension: public AcDbDimension
{
public:
    AcDbOrdinateDimension();
    AcDbOrdinateDimension(
        Adesk::Boolean     useXAxis,
        const AcGePoint3d& definingPoint,
	const AcGePoint3d& leaderEndPoint,
	char*              dimText = NULL,
	AcDbObjectId       dimStyle  = AcDbObjectId::kNull);
    ~AcDbOrdinateDimension();
    ACDB_DECLARE_MEMBERS(AcDbOrdinateDimension);

    Adesk::Boolean	isUsingXAxis() const;
    Adesk::Boolean	isUsingYAxis() const;
    Acad::ErrorStatus	useXAxis();
    Acad::ErrorStatus	useYAxis();

    AcGePoint3d		origin() const;
    Acad::ErrorStatus	setOrigin(const AcGePoint3d&);

    AcGePoint3d		definingPoint() const; 
    Acad::ErrorStatus	setDefiningPoint(const AcGePoint3d&); 

    AcGePoint3d		leaderEndPoint() const; 
    Acad::ErrorStatus	setLeaderEndPoint(const AcGePoint3d&); 

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbOrdinateDimension);

class AcDbRotatedDimension: public AcDbDimension
{
public:
    AcDbRotatedDimension();
    AcDbRotatedDimension(
        double             rotation,
	const AcGePoint3d& xLine1Point,
	const AcGePoint3d& xLine2Point,
	const AcGePoint3d& dimLinePoint,
	char*              dimText = NULL,
	AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRotatedDimension();
    ACDB_DECLARE_MEMBERS(AcDbRotatedDimension);

    AcGePoint3d		xLine1Point() const; 
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&); 

    AcGePoint3d		xLine2Point() const; 
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&); 

    AcGePoint3d		dimLinePoint() const; 
    Acad::ErrorStatus	setDimLinePoint(const AcGePoint3d&); 

    double		oblique() const;
    Acad::ErrorStatus	setOblique(double);

    double		rotation() const;
    Acad::ErrorStatus	setRotation(double);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbRotatedDimension);

class AcDbAlignedDimension: public AcDbDimension
{
public:
    AcDbAlignedDimension();
    AcDbAlignedDimension(
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& dimLinePoint,
        char*              dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbAlignedDimension();
    ACDB_DECLARE_MEMBERS(AcDbAlignedDimension);

    AcGePoint3d		xLine1Point() const; 
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&); 

    AcGePoint3d		xLine2Point() const; 
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&); 

    AcGePoint3d		dimLinePoint() const; 
    Acad::ErrorStatus	setDimLinePoint(const AcGePoint3d&); 

    double		oblique() const;
    Acad::ErrorStatus	setOblique(double);

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbAlignedDimension);

class AcDb3PointAngularDimension: public AcDbDimension
{
public:
    AcDb3PointAngularDimension();
    AcDb3PointAngularDimension(
        const AcGePoint3d& centerPoint,
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& arcPoint,
        char*              dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb3PointAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb3PointAngularDimension);

    AcGePoint3d		arcPoint() const; 
    Acad::ErrorStatus	setArcPoint(const AcGePoint3d&); 

    AcGePoint3d         xLine1Point() const; 
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&); 

    AcGePoint3d         xLine2Point() const; 
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&); 

    AcGePoint3d         centerPoint() const; 
    Acad::ErrorStatus	setCenterPoint(const AcGePoint3d&); 
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb3PointAngularDimension);

class AcDb2LineAngularDimension: public AcDbDimension
{
public:
    AcDb2LineAngularDimension();
    AcDb2LineAngularDimension(
        const AcGePoint3d& xLine1Start,
        const AcGePoint3d& xLine1End,
        const AcGePoint3d& xLine2Start,
        const AcGePoint3d& xLine2End,
        const AcGePoint3d& arcPoint,
        char*              dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb2LineAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb2LineAngularDimension);

    AcGePoint3d		arcPoint() const; 
    Acad::ErrorStatus	setArcPoint(const AcGePoint3d&); 

    AcGePoint3d		xLine1Start() const; 
    Acad::ErrorStatus	setXLine1Start(const AcGePoint3d&); 

    AcGePoint3d		xLine1End() const; 
    Acad::ErrorStatus	setXLine1End(const AcGePoint3d&); 

    AcGePoint3d		xLine2Start() const; 
    Acad::ErrorStatus	setXLine2Start(const AcGePoint3d&); 

    AcGePoint3d		xLine2End() const; 
    Acad::ErrorStatus	setXLine2End(const AcGePoint3d&); 
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDb2LineAngularDimension);

class AcDbRadialDimension: public AcDbDimension
{
public:
    AcDbRadialDimension();
    AcDbRadialDimension(
        const AcGePoint3d& center,
        const AcGePoint3d& chordPoint,
        double             leaderLength,
        char*              dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRadialDimension();
    ACDB_DECLARE_MEMBERS(AcDbRadialDimension);

    double		leaderLength() const;
    Acad::ErrorStatus	setLeaderLength(double);

    AcGePoint3d		center() const;
    Acad::ErrorStatus	setCenter(const AcGePoint3d&);

    AcGePoint3d		chordPoint() const;
    Acad::ErrorStatus	setChordPoint(const AcGePoint3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbRadialDimension);

class AcDbDiametricDimension: public AcDbDimension
{
public:
    AcDbDiametricDimension();
    AcDbDiametricDimension(
        const AcGePoint3d& chordPoint,
        const AcGePoint3d& farChordPoint,
        double             leaderLength,
        char*              dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbDiametricDimension();
    ACDB_DECLARE_MEMBERS(AcDbDiametricDimension);

    double		leaderLength() const;
    Acad::ErrorStatus	setLeaderLength(double);

    AcGePoint3d		chordPoint() const;
    Acad::ErrorStatus	setChordPoint(const AcGePoint3d&);

    AcGePoint3d		farChordPoint() const;
    Acad::ErrorStatus	setFarChordPoint(const AcGePoint3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbDiametricDimension);

class AcDbPoint: public AcDbEntity
{
public:
    AcDbPoint();
    AcDbPoint(const AcGePoint3d&   position);
    ~AcDbPoint();
    ACDB_DECLARE_MEMBERS(AcDbPoint);

    AcGePoint3d		position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&);

    double		thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);

    double		ecsRotation() const;
    Acad::ErrorStatus	setEcsRotation(double);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbPoint);

class AcDbFace: public AcDbEntity
{
public:                
    AcDbFace();
    AcDbFace(const AcGePoint3d&   pt0,
             const AcGePoint3d&   pt1,
             const AcGePoint3d&   pt2,
             const AcGePoint3d&   pt3,
                   Adesk::Boolean e0vis = Adesk::kTrue,
                   Adesk::Boolean e1vis = Adesk::kTrue,
                   Adesk::Boolean e2vis = Adesk::kTrue,
                   Adesk::Boolean e3vis = Adesk::kTrue);
    AcDbFace(const AcGePoint3d&   pt0,
             const AcGePoint3d&   pt1,
             const AcGePoint3d&   pt2,
                   Adesk::Boolean e0vis = Adesk::kTrue,
                   Adesk::Boolean e1vis = Adesk::kTrue,
                   Adesk::Boolean e2vis = Adesk::kTrue,
                   Adesk::Boolean e3vis = Adesk::kTrue);
    ~AcDbFace();
    ACDB_DECLARE_MEMBERS(AcDbFace);

    Acad::ErrorStatus getVertexAt(Adesk::UInt16, AcGePoint3d&) const;
    Acad::ErrorStatus setVertexAt(Adesk::UInt16, const AcGePoint3d&);

    Acad::ErrorStatus isEdgeVisibleAt(Adesk::UInt16, Adesk::Boolean&) const;
    Acad::ErrorStatus makeEdgeVisibleAt(Adesk::UInt16);
    Acad::ErrorStatus makeEdgeInvisibleAt(Adesk::UInt16);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbFace);

class AcDbPolyFaceMesh: public AcDbEntity
{
public:
    AcDbPolyFaceMesh();
    ~AcDbPolyFaceMesh();
    ACDB_DECLARE_MEMBERS(AcDbPolyFaceMesh);

    Adesk::Int16 numVertices() const;
    Adesk::Int16 numFaces() const;

    Acad::ErrorStatus appendVertex(AcDbPolyFaceMeshVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDbPolyFaceMeshVertex*);

    Acad::ErrorStatus appendFaceRecord(AcDbFaceRecord*);
    Acad::ErrorStatus appendFaceRecord(AcDbObjectId&, AcDbFaceRecord*);

    Acad::ErrorStatus openVertex(AcDbVertex*&, AcDbObjectId subObjId,
                                 AcDb::OpenMode,
                                 Adesk::Boolean openErasedOne = Adesk::kFalse);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbPolyFaceMesh);

class AcDbPolygonMesh: public AcDbEntity
{
public:
    AcDbPolygonMesh();
    AcDbPolygonMesh(AcDb::PolyMeshType pType,
                    Adesk::Int16       mSize,
                    Adesk::Int16       nSize,
                    const AcGePoint3dArray& vertices,
                    Adesk::Boolean     mClosed = Adesk::kTrue,
                    Adesk::Boolean     nClosed = Adesk::kTrue);
    ~AcDbPolygonMesh();
    ACDB_DECLARE_MEMBERS(AcDbPolygonMesh);

    AcDb::PolyMeshType	polyMeshType() const;
    Acad::ErrorStatus	setPolyMeshType(AcDb::PolyMeshType);

    Adesk::Int16	mSize() const;
    Acad::ErrorStatus	setMSize(Adesk::Int16);

    Adesk::Int16	nSize() const;
    Acad::ErrorStatus	setNSize(Adesk::Int16);
 
    Adesk::Boolean	isMClosed() const;
    Acad::ErrorStatus	makeMClosed();
    Acad::ErrorStatus	makeMOpen();
 
    Adesk::Boolean	isNClosed() const;
    Acad::ErrorStatus	makeNClosed();
    Acad::ErrorStatus	makeNOpen();
 
    Adesk::Int16	mSurfaceDensity() const;
    Acad::ErrorStatus	setMSurfaceDensity(Adesk::Int16);

    Adesk::Int16	nSurfaceDensity() const;
    Acad::ErrorStatus	setNSurfaceDensity(Adesk::Int16);

    // Vertex access
    //
    Acad::ErrorStatus appendVertex(AcDbPolygonMeshVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDbPolygonMeshVertex*);

    Acad::ErrorStatus openVertex(AcDbPolygonMeshVertex*&, AcDbObjectId vertId,
                                 AcDb::OpenMode,
                                 Adesk::Boolean openErasedOne = Adesk::kFalse);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;

};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbPolygonMesh);

class AcDbSolid: public AcDbEntity
{
public:
    AcDbSolid();
    AcDbSolid(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2,
              const AcGePoint3d&    pt3);
    AcDbSolid(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2);
    ~AcDbSolid();
    ACDB_DECLARE_MEMBERS(AcDbSolid);

    Acad::ErrorStatus transformBy(const AcGeMatrix3d& pXform);
    Acad::ErrorStatus getTransformedCopy(
              const AcGeMatrix3d& xform,
              AcDbEntity*&  pEnt) const;

    Acad::ErrorStatus getPointAt(Adesk::UInt16 idx, AcGePoint3d& pntRes) const;
    Acad::ErrorStatus setPointAt(Adesk::UInt16 idx, const AcGePoint3d&);

    double		thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbSolid);

class AcDbTrace: public AcDbEntity
{
public:
    AcDbTrace();
    AcDbTrace(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2,
              const AcGePoint3d&    pt3);
    ~AcDbTrace();
    ACDB_DECLARE_MEMBERS(AcDbTrace);

    // returns eInvalidIndex if index is out of range
    Acad::ErrorStatus getPointAt(Adesk::UInt16 idx, AcGePoint3d& PntRes) const;
    Acad::ErrorStatus setPointAt(Adesk::UInt16 idx, const AcGePoint3d&);

    double		thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbTrace);

class AcDbShape: public AcDbEntity
{
public:
    AcDbShape();
    AcDbShape(const AcGePoint3d&  position,
                    double        size,
              const char*         name,
                    double        rotation    = 0,
                    double        widthFactor = 0);
    ~AcDbShape();
    ACDB_DECLARE_MEMBERS(AcDbShape);

    AcGePoint3d		position() const;
    Acad::ErrorStatus	setPosition(const AcGePoint3d&); 
    
    double		size() const;
    Acad::ErrorStatus	setSize(double);
    
    char*            name() const;
    Acad::ErrorStatus setName(const char*); 
    
    double		rotation() const;
    Acad::ErrorStatus	setRotation(double);
    
    double		widthFactor() const;
    Acad::ErrorStatus	setWidthFactor(double);
    
    double		oblique() const;
    Acad::ErrorStatus	setOblique(double);

    double		thickness() const;
    Acad::ErrorStatus	setThickness(double);

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);

#ifdef ACDBLIB
    // These four functions are not available in the ARX API
    //
    Adesk::Int16 shapeNumber() const;
    void         setShapeNumber(Adesk::Int16);
 
    AcDbHardPointerId shapeIndex() const;
    void              setShapeIndex(AcDbHardPointerId);
#endif /* ACDBLIB */
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbShape);

class AcDbViewport: public AcDbEntity
{
public:
    AcDbViewport();
    ~AcDbViewport();
    ACDB_DECLARE_MEMBERS(AcDbViewport);

    // Set methods will return eCannotChangeActiveViewport if called
    // when the Viewport is currently active.  

    double            height() const;
    Acad::ErrorStatus setHeight(double);

    double            width() const;
    Acad::ErrorStatus setWidth(double);

    AcGePoint3d       centerPoint() const;
    Acad::ErrorStatus setCenterPoint(const AcGePoint3d&);

    Adesk::Int16      number() const;

#ifdef ACDBLIB
    // This function is not available in the ARX API
    //
    Adesk::Boolean    isOn();
#endif /* ACDBLIB */
    Acad::ErrorStatus setOn();
    Acad::ErrorStatus setOff();

    AcGePoint3d       viewTarget() const;
    Acad::ErrorStatus setViewTarget(const AcGePoint3d&); 

    AcGeVector3d      viewDirection() const;
    Acad::ErrorStatus setViewDirection(const AcGeVector3d&);

    // Model Space height, and center in Display coordinates
    //
    double            viewHeight() const;
    AcGePoint2d       viewCenter() const;

    double            twistAngle() const;
    Acad::ErrorStatus setTwistAngle(double);

    double            lensLength() const;
    Acad::ErrorStatus setLensLength(double);

    Adesk::Boolean    isFrontClipOn() const;
    Acad::ErrorStatus setFrontClipOn();
    Acad::ErrorStatus setFrontClipOff();

    Adesk::Boolean    isBackClipOn() const;
    Acad::ErrorStatus setBackClipOn();
    Acad::ErrorStatus setBackClipOff();

    Adesk::Boolean    isFrontClipAtEyeOn() const;
    Acad::ErrorStatus setFrontClipAtEyeOn();
    Acad::ErrorStatus setFrontClipAtEyeOff();

    // FrontZ 
    //
    double            frontClipDistance() const;
    Acad::ErrorStatus setFrontClipDistance(double newVal);

    // BackZ 
    //
    double            backClipDistance() const;
    Acad::ErrorStatus setBackClipDistance(double newVal);

    Adesk::Boolean    isPerspectiveOn() const;
    Acad::ErrorStatus setPerspectiveOn();
    Acad::ErrorStatus setPerspectiveOff();

    Adesk::Boolean    isUcsFollowModeOn() const;
    Acad::ErrorStatus setUcsFollowModeOn();
    Acad::ErrorStatus setUcsFollowModeOff();

    Adesk::Boolean    isUcsIconVisible() const;
    Acad::ErrorStatus setUcsIconVisible();
    Acad::ErrorStatus setUcsIconInvisible();

    Adesk::Boolean    isUcsIconAtOrigin() const;
    Acad::ErrorStatus setUcsIconAtOrigin();
    Acad::ErrorStatus setUcsIconAtCorner();

    Adesk::Boolean    isFastZoomOn() const;
    Acad::ErrorStatus setFastZoomOn();
    Acad::ErrorStatus setFastZoomOff();

    Adesk::UInt16     circleSides() const;
    Acad::ErrorStatus setCircleSides(Adesk::UInt16);

    Adesk::Boolean    isSnapOn() const;
    Acad::ErrorStatus setSnapOn();
    Acad::ErrorStatus setSnapOff();

    Adesk::Boolean    isSnapIsometric() const;
    Acad::ErrorStatus setSnapIsometric();
    Acad::ErrorStatus setSnapStandard();

    double            snapAngle() const;
    Acad::ErrorStatus setSnapAngle(double);

    AcGePoint2d       snapBasePoint() const;
    Acad::ErrorStatus setSnapBasePoint(const AcGePoint2d&); 

    AcGeVector2d      snapIncrement() const;
    Acad::ErrorStatus setSnapIncrement(const AcGeVector2d&);

    Adesk::UInt16     snapIsoPair() const;
    Acad::ErrorStatus setSnapIsoPair(Adesk::UInt16);

    Adesk::Boolean    isGridOn() const;
    Acad::ErrorStatus setGridOn();
    Acad::ErrorStatus setGridOff();

    AcGeVector2d      gridIncrement() const;
    Acad::ErrorStatus setGridIncrement(const AcGeVector2d&);

    Adesk::Boolean    hiddenLinesRemoved() const;
    Acad::ErrorStatus showHiddenLines();
    Acad::ErrorStatus removeHiddenLines();
    
};
MAKE_ACDBOPENOBJECT_FUNCTION(AcDbViewport);

#endif
