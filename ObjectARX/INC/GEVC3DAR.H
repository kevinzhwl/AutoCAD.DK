#ifndef AC_GEVC3DAR_H
#define AC_GEVC3DAR_H
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
// This file contains the definition for a dynamic array, called
// AcGeVector3dArray, of objects of type "AcGeVector3d".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "AcGeVector3d" in the
// usual manner.  For example declaring "AcGeVector3d myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcGeVector3dArray, you need to understand
// a couple of simple, yet key, concepts:
//
//     1) The logical length of the array.
//            - How many entries have been placed into the array,
//              initially always zero.
//     2) The physical length of the array.
//            - How many entries the array will hold before it
//              automatically "grows" larger.
//     3) The grow length of the array.
//            - How much the array will grow when required.
//
// The physical length of the array is the actual length of the
// physically allocated, but perhaps not fully used, array.
// As a point of clarification, the size in bytes of the array
// buffer for an array called `myArray' would be:
//
//     sizeOf(AcGeVector3d) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of AcGeVector3d have been placed into the array
// with, for example, append() or insertAt().  Many member-functions
// are only valid for indices that are greater than or equal to
// zero AND less than length().  For example, indexing into the
// array with the operator[] is only valid for indices in this range.
//
// You can explicitly set the logical length() to any value and
// if the physical length is not large enough the array will grow to
// that length.  Note that if the logical length is explicitly reset
// to a larger value, then all the entries from the old length up
// to the new length may contain garbage values, therefor they must be
// initialized explicitly.
//
// The logical length is always less than or equal to the physical
// length.  NOTE that the array ALWAYS starts out empty, i.e., the
// length() always starts at zero regardless of the initial physical
// length.
//
// If you add an element to the array causing the logical length
// to become greater than the physical length of the array then
// the "grow length" determines how much additional space to
// allocate, and the physical length will increase by the grow length.
//
// The grow length must be a positive number, that is, zero is an illegal
// grow length.

#include "adesk.h"
#include "assert.h"
#include "gevec3d.h"

class 
#ifdef AC_GEVC3DAR_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeVector3dArray
{
public:
    AcGeVector3dArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcGeVector3dArray(const AcGeVector3dArray&);
    ~AcGeVector3dArray();

    // Copy operator.
    //
    AcGeVector3dArray&  operator =  (const AcGeVector3dArray&);

    // Indexing into the array.
    //
    AcGeVector3d&       operator [] (int);
    const AcGeVector3d  operator [] (int) const;

    // More access to array-elements.
    //
    AcGeVector3d        at          (int) const;
    AcGeVector3dArray&  setAt       (int, const AcGeVector3d&);
    AcGeVector3dArray&  setAll      (const AcGeVector3d&);
    AcGeVector3d&       first       ();
    const AcGeVector3d  first       () const;
    AcGeVector3d&       last        ();
    const AcGeVector3d  last        () const;

    // Adding array-elements.
    //
    int                 append      (const AcGeVector3d&);
    AcGeVector3dArray&  append      (const AcGeVector3dArray& array);
    AcGeVector3dArray&  insertAt    (int, const AcGeVector3d&);

    // Removing array-elements.
    //
    AcGeVector3dArray&  removeAt    (int);
    Adesk::Boolean      remove      (const AcGeVector3d&, int start = 0);
    AcGeVector3dArray&  removeFirst ();
    AcGeVector3dArray&  removeLast  ();
    AcGeVector3dArray&  removeSubArray(int startIndex, int endIndex);


    // Query about array-elements.
    //
    Adesk::Boolean      contains    (const AcGeVector3d&, int start = 0) const;
    Adesk::Boolean      find        (const AcGeVector3d&, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcGeVector3dArray&  setLogicalLength(int);
    int                 physicalLength() const;
    AcGeVector3dArray&  setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcGeVector3dArray&  setGrowLength(int);

    // Utility.
    //
    AcGeVector3dArray&  reverse     ();
    AcGeVector3dArray&  swap        (int i1, int i2);

    // Treat as simple array of AcGeVector3d.
    //
    const AcGeVector3d* asArrayPtr  () const;
    AcGeVector3d*       asArrayPtr  ();

protected:
    AcGeVector3d*       mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcGeVector3dArray::contains(const AcGeVector3d& value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcGeVector3dArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcGeVector3dArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcGeVector3dArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcGeVector3dArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcGeVector3dArray::growLength() const
{ return mGrowLen; }

inline const AcGeVector3d*
AcGeVector3dArray::asArrayPtr() const
{ return mpArray; }

inline AcGeVector3d*
AcGeVector3dArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcGeVector3dArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline AcGeVector3d&
AcGeVector3dArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const AcGeVector3d
AcGeVector3dArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGeVector3d
AcGeVector3dArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGeVector3dArray&
AcGeVector3dArray::setAt(int i, const AcGeVector3d& value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline AcGeVector3d&
AcGeVector3dArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const AcGeVector3d
AcGeVector3dArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline AcGeVector3d&
AcGeVector3dArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const AcGeVector3d
AcGeVector3dArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcGeVector3dArray::append(const AcGeVector3d& value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcGeVector3dArray&
AcGeVector3dArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcGeVector3dArray&
AcGeVector3dArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcGeVector3dArray&
AcGeVector3dArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
