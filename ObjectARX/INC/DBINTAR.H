#ifndef AC_DBINTAR_H
#define AC_DBINTAR_H
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
// AcDbIntArray, of objects of type "int".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "int" in the
// usual manner.  For example declaring "int myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcDbIntArray, you need to understand
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
//     sizeOf(int) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of int have been placed into the array
// with, for example, append() or insertAt().  Many member-functions
// are only valid for indicies that are greater than or equal to
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

class AcDbIntArray
{
public:
    AcDbIntArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcDbIntArray(const AcDbIntArray&);
    ~AcDbIntArray();

    // Copy operator.
    //
    AcDbIntArray&       operator =  (const AcDbIntArray&);

    // Indexing into the array.
    //
    int&                operator [] (int);
    const int           operator [] (int) const;

    // More access to array-elements.
    //
    int                 at          (int index) const;
    AcDbIntArray&       setAt       (int index, int value);
    AcDbIntArray&       setAll      (int value);
    int&                first       ();
    const int           first       () const;
    int&                last        ();
    const int           last        () const;

    // Adding array-elements.
    //
    int                 append      (int value);
    AcDbIntArray&       append      (const AcDbIntArray& array);
    AcDbIntArray&       insertAt    (int index, int value);

    // Removing array-elements.
    //
    AcDbIntArray&       removeAt    (int index);
    Adesk::Boolean      remove      (int value, int start = 0);
    AcDbIntArray&       removeFirst ();
    AcDbIntArray&       removeLast  ();

    // Query about array-elements.
    //
    Adesk::Boolean      contains    (int value, int start = 0) const;
    Adesk::Boolean      find        (int value, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcDbIntArray&       setLogicalLength(int);
    int                 physicalLength() const;
    AcDbIntArray&       setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcDbIntArray&       setGrowLength(int);

    // Utility.
    //
    AcDbIntArray&       reverse     ();
    AcDbIntArray&       swap        (int i1, int i2);

    // Treat as simple array of int.
    //
    const int*          asArrayPtr  () const;
    int*                asArrayPtr  ();

protected:
    int*                mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcDbIntArray::contains(int value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcDbIntArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcDbIntArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcDbIntArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcDbIntArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcDbIntArray::growLength() const
{ return mGrowLen; }

inline const int*
AcDbIntArray::asArrayPtr() const
{ return mpArray; }

inline int*
AcDbIntArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcDbIntArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline int&
AcDbIntArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const int
AcDbIntArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline int
AcDbIntArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcDbIntArray&
AcDbIntArray::setAt(int i, int value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline int&
AcDbIntArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const int
AcDbIntArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline int&
AcDbIntArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const int
AcDbIntArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcDbIntArray::append(int value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcDbIntArray&
AcDbIntArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcDbIntArray&
AcDbIntArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcDbIntArray&
AcDbIntArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
