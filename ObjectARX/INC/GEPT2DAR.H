#ifndef AC_GEPT2DAR_H
#define AC_GEPT2DAR_H
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
// AcGePoint2dArray, of objects of type "AcGePoint2d".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "AcGePoint2d" in the
// usual manner.  For example declaring "AcGePoint2d myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcGePoint2dArray, you need to understand
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
//     sizeOf(AcGePoint2d) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of AcGePoint2d have been placed into the array
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
#include "gepnt2d.h"

class 
#ifdef AC_GEPT2DAR_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGePoint2dArray
{
public:
    AcGePoint2dArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcGePoint2dArray(const AcGePoint2dArray&);
    ~AcGePoint2dArray();

    // Copy operator.
    //
    AcGePoint2dArray&   operator =  (const AcGePoint2dArray&);

    // Indexing into the array.
    //
    AcGePoint2d&        operator [] (int);
    const AcGePoint2d   operator [] (int) const;

    // More access to array-elements.
    //
    AcGePoint2d         at          (int) const;
    AcGePoint2dArray&   setAt       (int, const AcGePoint2d&);
    AcGePoint2dArray&   setAll      (const AcGePoint2d&);
    AcGePoint2d&        first       ();
    const AcGePoint2d   first       () const;
    AcGePoint2d&        last        ();
    const AcGePoint2d   last        () const;

    // Adding array-elements.
    //
    int                 append      (const AcGePoint2d&);
    AcGePoint2dArray&   append      (const AcGePoint2dArray& array);
    AcGePoint2dArray&   insertAt    (int, const AcGePoint2d&);

    // Removing array-elements.
    //
    AcGePoint2dArray&   removeAt    (int);
    Adesk::Boolean      remove      (const AcGePoint2d&, int start = 0);
    AcGePoint2dArray&   removeFirst ();
    AcGePoint2dArray&   removeLast  ();
    AcGePoint2dArray&   removeSubArray(int startIndex, int endIndex);

    // Query about array-elements.
    //
    Adesk::Boolean      contains    (const AcGePoint2d&, int start = 0) const;
    Adesk::Boolean      find        (const AcGePoint2d&, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcGePoint2dArray&   setLogicalLength(int);
    int                 physicalLength() const;
    AcGePoint2dArray&   setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcGePoint2dArray&   setGrowLength(int);

    // Utility.
    //
    AcGePoint2dArray&   reverse     ();
    AcGePoint2dArray&   swap        (int i1, int i2);

    // Treat as simple array of AcGePoint2d.
    //
    const AcGePoint2d*  asArrayPtr  () const;
    AcGePoint2d*        asArrayPtr  ();

protected:
    AcGePoint2d*        mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcGePoint2dArray::contains(const AcGePoint2d& value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcGePoint2dArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcGePoint2dArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcGePoint2dArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcGePoint2dArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcGePoint2dArray::growLength() const
{ return mGrowLen; }

inline const AcGePoint2d*
AcGePoint2dArray::asArrayPtr() const
{ return mpArray; }

inline AcGePoint2d*
AcGePoint2dArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcGePoint2dArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline AcGePoint2d&
AcGePoint2dArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const AcGePoint2d
AcGePoint2dArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGePoint2d
AcGePoint2dArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGePoint2dArray&
AcGePoint2dArray::setAt(int i, const AcGePoint2d& value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline AcGePoint2d&
AcGePoint2dArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const AcGePoint2d
AcGePoint2dArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline AcGePoint2d&
AcGePoint2dArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const AcGePoint2d
AcGePoint2dArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcGePoint2dArray::append(const AcGePoint2d& value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcGePoint2dArray&
AcGePoint2dArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcGePoint2dArray&
AcGePoint2dArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcGePoint2dArray&
AcGePoint2dArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
