//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:  Lightweight polyline API header file.
//

#ifndef AD_DBPL_H
#define AD_DBPL_H 1

#include "dbmain.h"
#include "dbcurve.h"

#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "gept2dar.h"
#include "dbboiler.h"

#pragma pack(push, 8)

class AcDb2dPolyline;

class AcDbPolyline : public AcDbCurve
{

public:
                      AcDbPolyline();
                      AcDbPolyline(unsigned int num_verts);
    virtual          ~AcDbPolyline();


    ACDB_DECLARE_MEMBERS(AcDbPolyline);


    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************

    virtual Acad::ErrorStatus convertFrom(AcDbEntity*& pPline, 
                                          Adesk::Boolean transferId = Adesk::kTrue);
    Acad::ErrorStatus convertTo(AcDb2dPolyline*&  pPline,
                                Adesk::Boolean transferId = Adesk::kTrue) const;

    Acad::ErrorStatus getPointAt(unsigned int, AcGePoint3d& pt) const;

    enum SegType {
        kLine,
        kArc,
        kCoincident,
        kPoint,
        kEmpty
    };

    SegType           segType           (unsigned int index) const;

    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg2d& ln) const;
    Acad::ErrorStatus getLineSegAt      (unsigned int index,
                                         AcGeLineSeg3d& ln) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc2d& arc) const;
    Acad::ErrorStatus getArcSegAt       (unsigned int index,
                                         AcGeCircArc3d& arc) const;
    virtual Adesk::Boolean onSegAt      (unsigned int index, const AcGePoint2d& pt2d,
                                         double& param) const;

    //**********************************************************************
    // AcDbPolyline methods.
    //**********************************************************************
   
    virtual void      setClosed       (Adesk::Boolean);
    void              setPlinegen     (Adesk::Boolean);
    virtual void      setElevation    (double);
    virtual Acad::ErrorStatus setThickness (double);
    virtual Acad::ErrorStatus setConstantWidth (double);
    virtual Acad::ErrorStatus setNormal (const AcGeVector3d&);

    Adesk::Boolean    isOnlyLines     ()                        const;
    Adesk::Boolean    hasPlinegen     ()                        const;
    double            elevation       ()                        const;
    double            thickness       ()                        const;
    Acad::ErrorStatus getConstantWidth(double&)                 const;
    AcGeVector3d      normal          ()                        const;

    virtual Acad::ErrorStatus addVertexAt (unsigned int index,
                                           const AcGePoint2d& pt,
                                           double bulge = 0.,
                                           double startWidth = -1.,
                                           double endWidth = -1.,
                                           Adesk::Int32 vertexIdentifier = 0);

    virtual Acad::ErrorStatus removeVertexAt (unsigned int index);

    unsigned int      numVerts        ()                        const;

    Acad::ErrorStatus getPointAt        (unsigned int index,
                                       AcGePoint2d& pt)         const;
    Acad::ErrorStatus getBulgeAt      (unsigned int index,
                                       double&      bulge)      const;
    Acad::ErrorStatus getVertexIdentifierAt(unsigned int index,
                                            Adesk::Int32& vertexIdentifier) const;
    Acad::ErrorStatus getWidthsAt     (unsigned int index,
                                       double&      startWidth,
                                       double&      endWidth)   const;

    virtual Acad::ErrorStatus setPointAt (unsigned int index,
                                          const AcGePoint2d& pt);
    virtual Acad::ErrorStatus setBulgeAt (unsigned int index,
                                          double       bulge);
    virtual Acad::ErrorStatus setVertexIdentifierAt (unsigned int index,
                                                     Adesk::Int32 suggestedValue);
    virtual Acad::ErrorStatus setWidthsAt (unsigned int index,
                                           double       startWidth,
                                           double       endWidth);

    Acad::ErrorStatus minimizeMemory  ();
    Acad::ErrorStatus maximizeMemory  ();

    virtual void      reset           (Adesk::Boolean reuse,
                                       unsigned int numVerts);


    Adesk::Boolean     hasBulges       ()        const;
    Adesk::Boolean     hasVertexIdentifiers()    const;
    Adesk::Boolean     hasWidth        ()        const;

    // Does nothing and returns Acad::eOk if already closed or the start and end 
    // vertices do not coincide
    //
    ACDB_PORT Acad::ErrorStatus makeClosedIfStartAndEndVertexCoincide(double distTol);

    //**********************************************************************
    // AcDbCurve methods.
    //**********************************************************************

    DBCURVE_METHODS

    //*************************************************************************
    // Overridden methods from AcDEntity
    //*************************************************************************


    virtual void              getEcs(AcGeMatrix3d& retVal) const;

    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* filer,
                                               AcRxClass*    classobj);

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;

    virtual void              saveAs(AcGiWorldDraw* mode,
                                     AcDb::SaveType st);


protected:

    //*************************************************************************
    // Overridden methods from AcDEntity
    //*************************************************************************

    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
};


inline Adesk::Boolean AcDbPolyline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbPolyline::getStartParam(double& startParam) const
{
    startParam = 0.;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbPolyline::getSpline(AcDbSpline*& spline) const
{
    spline;     // unreferenced parameter
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif /*AD_DBPL_H*/
