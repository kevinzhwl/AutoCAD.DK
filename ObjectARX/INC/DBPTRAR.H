#ifndef AC_DBPTRAR_H
#define AC_DBPTRAR_H
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
// AcDbVoidPtrArray, of objects of type "void*".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "void*" in the
// usual manner.  For example declaring "void* myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcDbVoidPtrArray, you need to understand
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
//     sizeOf(void*) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of void* have been placed into the array
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

class AcDbVoidPtrArray
{
public:
    AcDbVoidPtrArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcDbVoidPtrArray(const AcDbVoidPtrArray&);
    ~AcDbVoidPtrArray();

    // Copy operator.
    //
    AcDbVoidPtrArray&   operator =  (const AcDbVoidPtrArray&);

    // Indexing into the array.
    //
    void*&              operator [] (int);
    const void*         operator [] (int) const;

    // More access to array-elements.
    //
    void*               at          (int) const;
    AcDbVoidPtrArray&   setAt       (int, void*);
    AcDbVoidPtrArray&   setAll      (void*);
    void*&              first       ();
    const void*         first       () const;
    void*&              last        ();
    const void*         last        () const;

    // Adding array-elements.
    //
    int                 append      (void*);
    AcDbVoidPtrArray&   append      (const AcDbVoidPtrArray& array);
    AcDbVoidPtrArray&   insertAt    (int, void*);

    // Removing array-elements.
    //
    AcDbVoidPtrArray&   removeAt    (int);
    Adesk::Boolean      remove      (void*, int start = 0);
    AcDbVoidPtrArray&   removeFirst ();
    AcDbVoidPtrArray&   removeLast  ();

    // Query about array-elements.
    //
    Adesk::Boolean      contains    (void*, int start = 0) const;
    Adesk::Boolean      find        (void*, int& foundAt,
                                     int start = 0) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    Adesk::Boolean      isEmpty     () const;
    int                 logicalLength() const;
    AcDbVoidPtrArray&   setLogicalLength(int);
    int                 physicalLength() const;
    AcDbVoidPtrArray&   setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcDbVoidPtrArray&   setGrowLength(int);

    // Utility.
    //
    AcDbVoidPtrArray&   reverse     ();
    AcDbVoidPtrArray&   swap        (int i1, int i2);

    // Treat as simple array of void*.
    //
    const void**        asArrayPtr  () const;
    void**              asArrayPtr  ();

protected:
    void**              mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    Adesk::Boolean      isValid     (int) const;
};

// Inline methods.

inline Adesk::Boolean
AcDbVoidPtrArray::contains(void* value, int start) const
{ int dummy; return find(value, dummy, start); }

inline int
AcDbVoidPtrArray::length() const
{ return mLogicalLen; }

inline Adesk::Boolean
AcDbVoidPtrArray::isEmpty() const
{ return mLogicalLen == 0; }

inline int
AcDbVoidPtrArray::logicalLength() const
{ return mLogicalLen; }

inline int
AcDbVoidPtrArray::physicalLength() const
{ return mPhysicalLen; }

inline int
AcDbVoidPtrArray::growLength() const
{ return mGrowLen; }

inline const void**
AcDbVoidPtrArray::asArrayPtr() const
{ return (const void**)mpArray; }

inline void**
AcDbVoidPtrArray::asArrayPtr()
{ return mpArray; }

inline Adesk::Boolean
AcDbVoidPtrArray::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

inline void*&
AcDbVoidPtrArray::operator [] (int i)
{ assert(isValid(i)); return mpArray[i]; }

inline const void*
AcDbVoidPtrArray::operator [] (int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline void*
AcDbVoidPtrArray::at(int i) const
{ assert(isValid(i)); return mpArray[i]; }

inline AcDbVoidPtrArray&
AcDbVoidPtrArray::setAt(int i, void* value)
{ assert(isValid(i)); mpArray[i] = value; return *this; }

inline void*&
AcDbVoidPtrArray::first()
{ assert(!isEmpty()); return mpArray[0]; }

inline const void*
AcDbVoidPtrArray::first() const
{ assert(!isEmpty()); return mpArray[0]; }

inline void*&
AcDbVoidPtrArray::last()
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline const void*
AcDbVoidPtrArray::last() const
{ assert(!isEmpty()); return mpArray[mLogicalLen-1]; }

inline int
AcDbVoidPtrArray::append(void* value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

inline AcDbVoidPtrArray&
AcDbVoidPtrArray::removeFirst()
{ assert(!isEmpty()); return removeAt(0); }

inline AcDbVoidPtrArray&
AcDbVoidPtrArray::removeLast()
{ assert(!isEmpty()); mLogicalLen--; return *this; }

inline AcDbVoidPtrArray&
AcDbVoidPtrArray::setGrowLength(int glen)
{ assert(glen > 0); mGrowLen = glen; return *this; }

#endif
