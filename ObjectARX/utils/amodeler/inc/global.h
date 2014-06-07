#ifndef AMODELER_INC_GLOBAL_H
#define AMODELER_INC_GLOBAL_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2002 by Autodesk, Inc.
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
// The basic include file to be included into any modeler file. It contains
// some very basic stuff, needed almost everywhere in the modeler.
//
///////////////////////////////////////////////////////////////////////////////


// The same header files are used both to build the DLL and to use the DLL
//
#if !defined(LIB_VERSION_OF_AMODELER) && !defined(unix)
#ifdef BUILD_AMODELER_DLL
#define DllImpExp __declspec(dllexport)
#else
#define DllImpExp __declspec(dllimport)
#endif
#else
#define DllImpExp
#endif



// If ve are using VC++4.0 compiler or newer, we define namespace AModeler 
// to contain all AModeler symbols. VC++2.2 compiler and older versions do 
// not support namespaces.
//
#if _MSC_VER >= 1000
#define AMODELER_NAMESPACE         AModeler
#define AMODELER_NAMESPACE_BEGIN   namespace AModeler {
#define AMODELER_NAMESPACE_END     }
#else
#define AMODELER_NAMESPACE         
#define AMODELER_NAMESPACE_BEGIN  
#define AMODELER_NAMESPACE_END
#endif


#ifndef hpux
#pragma warning(disable: 4514 4355 4039 4201 4237 4204)
#endif

// NOTE: This is the "inline function not expanded" warning. This warning is 
// meaningful and serious (shows a serious defficiency in VC++4.0)
//
#pragma warning(disable: 4710)



AMODELER_NAMESPACE_BEGIN

// Let us define 'bool' to look the same as the proposed standard C++ 
// data type 'bool'. Try to avoid redefining it if some other header 
// file already defined it.
//
#if _MSC_VER < 1100
#if !defined(true) && !defined(__GNUC__)
typedef int bool;     
const   int true  = 1;
const   int false = 0;
#endif
#endif

AMODELER_NAMESPACE_END


// Include some very frequently used header files so that they do not have
// to be included every time
//
#include <stdio.h>
#include <stdlib.h>
#include "massert.h"   // Our own assert
#include "errcodes.h"
#include "epsilon.h"
#include "flags.h"



AMODELER_NAMESPACE_BEGIN

// The values of the following constants are assigned in global.cpp. Otherwise 
// the VC++4.0 compiler would generate the same initialization code in 
// each file into which "global.h" is included.
//
DllImpExp extern const double kPi;      
DllImpExp extern const double kTwoPi;    
DllImpExp extern const double kHalfPi;

DllImpExp extern const double kMaxReal;  // A very big number, but not too big
DllImpExp extern const double kMinReal;
DllImpExp extern const double kDeg2Rad;  // Degrees --> radians coefficient
DllImpExp extern const double kEpsZero;  // Really a very small value

const int kTooBigInt = 10000000;    // Too big number of anything is 10 million



// We, Pascal people, used to have sqr() function and some other goodies
//
#ifndef hpux
inline double sqr (double a) { return a * a;                      }
#endif
inline int    sign(double a) { return a > 0 ? 1 : a < 0 ? -1 : 0; }
inline bool   odd (int    a) { return a & 0x1;                    }

inline int round(double d)  // Is there is a C function doing this?
{
    return d >= 0 ? (int)(d + 0.5) : (int)(d - 0.5);
}

#ifdef unix
#define __max(a,b)  ((a) >= (b) ? (a) : (b))
#define __min(a,b)  ((a) <= (b) ? (a) : (b))
#endif


inline int prevIndex(int i, int n) { return i ==   0 ? n-1 : i-1; }
inline int nextIndex(int i, int n) { return i == n-1 ? 0   : i+1; }


// Forward declaration of some commonly used classes so that we do not have to
// forward-declare them in header files every time they are needed.
//
class Point2d;
class Vector2d;
class Point3d;
class Vector3d;
class IntPoint2d;
class IntVector2d;
class IntPoint3d;
class IntVector3d;
class Transf3d;
class Line3d;
class Circle3d;
class Plane;
class Interval1d;
class Interval2d;
class Interval3d;
class IntInterval1d;
class IntInterval2d;
class IntInterval3d;
class Entity;
class Body;
class Face;
class Edge;
class Vertex;
class Surface;
class CylinderSurface;
class ConeSurface;
class SphereSurface;
class TorusSurface;
class Curve;
class CircleCurve;
class PolygonVertexData;
class OutputPolylineCallback;
class OutputTriangleCallback;
class SaveRestoreCallback;
class SaveToSatCallback;
class TopologyChangeCallback;
class TriangleCache;
class Darray;
class MorphingMapElem;
class MorphingMap;
class VertexSurfaceData;
class HideIntegerTransform;

typedef bool abool; // TODO Jiri Kripac: Why has this been added? Remove it

AMODELER_NAMESPACE_END
#endif
