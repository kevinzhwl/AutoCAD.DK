#ifndef AC_GEPT3DAR_H
#define AC_GEPT3DAR_H
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
// AcGePoint3dArray, of objects of type "AcGePoint3d".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "AcGePoint3d" in the
// usual manner.  For example declaring "AcGePoint3d myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcGePoint3dArray, you need to understand
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
//     sizeOf(AcGePoint3d) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of AcGePoint3d have been placed into the array
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
#include "gepnt3d.h"

class
#ifdef AC_GEPT3DAR_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGePoint3dArray
{
public:
    AcGePoint3dArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcGePoint3dArray(const AcGePoint3dArray&);
    ~AcGePoint3dArray();

    // Copy operator.
    //
    AcGePoint3dArray&   operator =  (const AcGePoint3dArray&);

    // Indexing into the array.
    //
    AcGePoint3d&        operator [] (int);
    const AcGePoint3d   operator [] (int) const;

    // Equal to operator.
    //
    Adesk::Boolean      operator ==  (const AcGePoint3dArray&);

    // More access to array-elements.
    //
    AcGePoint3d         at          (int) const;
    AcGePoint3dArray&   setAt       (int, const AcGePoint3d&);
    AcGePoint3dArray&   setAll      (const AcGePoint3d&);
    AcGePoint3d&        first       ();
    const AcGePoint3d   first       () const;
    AcGePoint3d&        last        ();
    const AcGePoint3d   last        () const;

    // Adding array-elements.
    //
    int                 append      (const AcGePoint3d&);
    AcGePoint3dArray&   append      (const AcGePoint3dArray& array);
    AcGePoint3dArray&   insertAt    (int, const AcGePoint3d&);

    // Removing array-elements.
    //
    AcGePoint3dArray&   removeAt      (int);
    Adesk::Boolean      remove        (const AcGePoint3d&, int start = 0);
    AcGePoint3dArray&   removeFirst   ();
    AcGePoint3dArray&   removeLast    ();
    AcGePoint3dArray&   removeSubArray(int startIndex, int endIndex);

    // Query about array-elements.
    //
    Adesk::Boolean      contains    (const AcGePoint3d&, int start = 0) const;
    Adesk::Boolean      find        (const AcGePoint3d&, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcGePoint3dArray&   setLogicalLength(int);
    int                 physicalLength() const;
    AcGePoint3dArray&   setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcGePoint3dArray&   setGrowLength(int);

    // Utility.
    //
    AcGePoint3dArray&   reverse     ();
    AcGePoint3dArray&   swap        (int i1, int i2);

    // Treat as simple array of AcGePoint3d.
    //
    const AcGePoint3d*  asArrayPtr  () const;
    AcGePoint3d*        asArrayPtr  ();

protected:
    AcGePoint3d*        mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcGePoint3dArray::contains(const AcGePoint3d& value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcGePoint3dArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcGePoint3dArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcGePoint3dArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcGePoint3dArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcGePoint3dArray::growLength() const
{ return mGrowLen; }

inline const AcGePoint3d*
AcGePoint3dArray::asArrayPtr() const
{ return mpArray; }

inline AcGePoint3d*
AcGePoint3dArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcGePoint3dArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline AcGePoint3d&
AcGePoint3dArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const AcGePoint3d
AcGePoint3dArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGePoint3d
AcGePoint3dArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGePoint3dArray&
AcGePoint3dArray::setAt(int i, const AcGePoint3d& value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline AcGePoint3d&
AcGePoint3dArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const AcGePoint3d
AcGePoint3dArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline AcGePoint3d&
AcGePoint3dArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const AcGePoint3d
AcGePoint3dArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcGePoint3dArray::append(const AcGePoint3d& value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcGePoint3dArray&
AcGePoint3dArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcGePoint3dArray&
AcGePoint3dArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcGePoint3dArray&
AcGePoint3dArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
