// (C) Copyright 2004 by Autodesk, Inc. 
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
// This is the main DLL file.

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
#include <gcroot.h>
#include <dbdate.h>
#include "mgdinterop.h"

//////////////////////////////////////////////////////////////////////////
// constructor
Autodesk::ObjectDbxSample::Poly::Poly() 
:Autodesk::AutoCAD::DatabaseServices::Curve(new AsdkPoly(), true)
{
	acutPrintf("\n*********************Constructor");
}

//////////////////////////////////////////////////////////////////////////
Autodesk::ObjectDbxSample::Poly::Poly(System::IntPtr unmanagedPointer, bool autoDelete)
: Autodesk::AutoCAD::DatabaseServices::Curve(unmanagedPointer,autoDelete)
{
}

//////////////////////////////////////////////////////////////////////////
// set the centre of the poly
void Autodesk::ObjectDbxSample::Poly::set_Center(Point2d point)
{
  Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setCenter(GETPOINT2D(point)));
}
//////////////////////////////////////////////////////////////////////////
// get the center point
Point2d Autodesk::ObjectDbxSample::Poly::get_Center()
{
    return ToPoint2d (GetImpObj()->center());
}

//////////////////////////////////////////////////////////////////////////
// set the start point
void Autodesk::ObjectDbxSample::Poly::set_StartPoint2d(Point2d point)
{
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setStartPoint(GETPOINT2D(point)));
}
//////////////////////////////////////////////////////////////////////////
// get the start point
Point2d Autodesk::ObjectDbxSample::Poly::get_StartPoint2d()
{
    return ToPoint2d (GetImpObj()->startPoint());
}

//////////////////////////////////////////////////////////////////////////
// set number of polygon sides
void Autodesk::ObjectDbxSample::Poly::set_NumberOfSides(long value)
{
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setNumSides(value));
}
//////////////////////////////////////////////////////////////////////////
// get the number of polygon sides
long Autodesk::ObjectDbxSample::Poly::get_NumberOfSide()
{
    return GetImpObj()->numSides();
}

//////////////////////////////////////////////////////////////////////////
// set the normal vector
void Autodesk::ObjectDbxSample::Poly::set_Normal(Vector3d vector)
{
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setNormal(GETVECTOR3D(vector)));
}
//////////////////////////////////////////////////////////////////////////
// get the normal vector
Vector3d Autodesk::ObjectDbxSample::Poly::get_Normal()
{
    return ToVector3d(GetImpObj()->normal());
}

//////////////////////////////////////////////////////////////////////////
// set the elevation
void Autodesk::ObjectDbxSample::Poly::set_Elevation(double value)
{
    GetImpObj()->setElevation(value);
}
//////////////////////////////////////////////////////////////////////////
// get the elevation
double Autodesk::ObjectDbxSample::Poly::get_Elevation()
{
    return GetImpObj()->elevation();
}

//////////////////////////////////////////////////////////////////////////
// set the string name
void Autodesk::ObjectDbxSample::Poly::set_Name(String* value)
{
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setName(StringToCIF(value)));
}
//////////////////////////////////////////////////////////////////////////
// get the string name
String* Autodesk::ObjectDbxSample::Poly::get_Name()
{
    return CIFToString(GetImpObj()->name());
}

//////////////////////////////////////////////////////////////////////////
// set the text style record 
void Autodesk::ObjectDbxSample::Poly::set_TextStyle(Autodesk::AutoCAD::DatabaseServices::ObjectId value)
{
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->setTextStyle(GETOBJECTID(value)));
}

//////////////////////////////////////////////////////////////////////////
// get the vertices into a 2d point array
Point2dCollection* Autodesk::ObjectDbxSample::Poly::get_Vertices()
{
    AcGePoint2dArray* pArr = new AcGePoint2dArray();
    Autodesk::AutoCAD::Runtime::Interop::Check(GetImpObj()->getVertices2d(*pArr));

    Point2dCollection* ret = 
        __try_cast<Point2dCollection*>(Autodesk::AutoCAD::Runtime::DisposableWrapper::Create(__typeof(Point2dCollection),pArr,true));

    return ret;
}
