#ifndef AC_GEDBLAR_H
#define AC_GEDBLAR_H
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
// AcGeDoubleArray, of objects of type "double".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "double" in the
// usual manner.  For example declaring "double myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcGeDoubleArray, you need to understand
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
//     sizeOf(double) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of double have been placed into the array
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

#ifndef unix
#include <stdlib.h>
#endif
#include "adesk.h"
#include "assert.h"

class
#ifdef AC_GEDBLAR_CPP
GE_DLLEXPORT
#else
GE_DLLIMPORT
#endif
AcGeDoubleArray
{
public:
    AcGeDoubleArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcGeDoubleArray(const AcGeDoubleArray&);
    ~AcGeDoubleArray();

    // Copy operator.
    //
    AcGeDoubleArray&    operator =  (const AcGeDoubleArray&);

    // Indexing into the array.
    //
    double&             operator [] (int);
    const double        operator [] (int) const;

    // More access to array-elements.
    //
    double              at          (int) const;
    AcGeDoubleArray&    setAt       (int, double);
    AcGeDoubleArray&    setAll      (double);
    double&             first       ();
    const double        first       () const;
    double&             last        ();
    const double        last        () const;

    // Adding array-elements.
    //
    int                 append      (double);
    AcGeDoubleArray&    append      (const AcGeDoubleArray& array);
    AcGeDoubleArray&    insertAt    (int, double);

    // Removing array-elements.
    //
    AcGeDoubleArray&    removeAt      (int);
    Adesk::Boolean      remove        (double, int start = 0);
    AcGeDoubleArray&    removeFirst   ();
    AcGeDoubleArray&    removeLast    ();
    AcGeDoubleArray&    removeSubArray(int startIndex, int endIndex);

    // Query about array-elements.
    //
    Adesk::Boolean      contains    (double, int start = 0) const;
    Adesk::Boolean      find        (double, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcGeDoubleArray&    setLogicalLength(int);
    int                 physicalLength() const;
    AcGeDoubleArray&    setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcGeDoubleArray&    setGrowLength(int);

    // Utility.
    //
    AcGeDoubleArray&    reverse     ();
    AcGeDoubleArray&    swap        (int i1, int i2);

    // Treat as simple array of double.
    //
    const double*       asArrayPtr  () const;
    double*             asArrayPtr  ();

protected:
    double*             mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcGeDoubleArray::contains(double value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcGeDoubleArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcGeDoubleArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcGeDoubleArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcGeDoubleArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcGeDoubleArray::growLength() const
{ return mGrowLen; }

inline const double*
AcGeDoubleArray::asArrayPtr() const
{ return mpArray; }

inline double*
AcGeDoubleArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcGeDoubleArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline double&
AcGeDoubleArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const double
AcGeDoubleArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline double
AcGeDoubleArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcGeDoubleArray&
AcGeDoubleArray::setAt(int i, double value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline double&
AcGeDoubleArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const double
AcGeDoubleArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline double&
AcGeDoubleArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const double
AcGeDoubleArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcGeDoubleArray::append(double value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcGeDoubleArray&
AcGeDoubleArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcGeDoubleArray&
AcGeDoubleArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcGeDoubleArray&
AcGeDoubleArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
