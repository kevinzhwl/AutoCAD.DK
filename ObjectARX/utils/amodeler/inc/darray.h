#ifndef AMODELER_INC_DARRAY_H
#define AMODELER_INC_DARRAY_H


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
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
// The "Darray" class defines a dynamic array of void pointers.
//
// The lower index of the array starts from 0, the upper index is flexible. 
// When an array index greater than the current maximum index is used, the 
// array is automatically expanded.
//
// Access to and assigning to the individual elements of the array is 
// via the overloaded subscript operator [].
//
// The methods add(), del(), merge(), length(), find() provide "list-like"
// operations on the dynamic array. However, operations del(), merge() and
// find() are less efficient for larger arrays ( > 1000 elements).
//
// The Darray class is optimized for arrays of smaller lengths (less than 
// kMinLength elements). In this case no malloc() is called and the 
// fixedArray[] inside the Darray class is directly used.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include "global.h"

AMODELER_NAMESPACE_BEGIN


class DllImpExp Darray
{
public:

    Darray             ();
    Darray             (const Darray& da);
    Darray             (int len);
    Darray             (void* ptr);
    ~Darray            ();
    
    Darray& operator  =(const Darray& da);
    
    void*&  operator [](int index);
    void*   operator [](int index) const;
    
    int     add        (void* ptr);
    void    add        (int index, void* ptr);
    void    add        (const Darray& da);
    void    del        (int index);
    int     del        (void* ptr);
    int     merge      (void* ptr);
    int     merge      (const Darray& da);
    int     find       (const void* ptr, int startIndex = 0) const;
    int     contains   (const void* ptr) const;
    void    swap       (int index1, int index2);
    void    intersectWith(const Darray&);
    
    int     length     ();
    int     length     () const;
    
    void    resize     (int len);
    void    init       ();
    void    init       (int len);

    void    fixAfterMemcopy(void* newAddress);
    
private:

    enum { kMinLength = 4 };       // Minimum allocated array length

    void  **mArray;                // Pointer to the array of void pointers 
    int   mAllocLength;            // Length of the allocated array 
    int   mUsedLength;             // Length of the array actually used
    void* mFixedArray[kMinLength]; // A short array of void pointers
    
    void  extendArray(int len);
    int   findLength () const;

}; // class Darray



// Inline methods

#ifndef hpux
#pragma warning(disable: 4068)
#pragma C-Cover off
#endif


inline Darray::Darray() : mAllocLength(0), mUsedLength(0) {}


inline Darray::Darray(int len) : mAllocLength(0), mUsedLength(0)
{ 
    resize(len); 
}


inline Darray::Darray(void* ptr) : mAllocLength(0), mUsedLength(0)
{ 
    resize(1); 
    mArray[0] = ptr; 
    mUsedLength = 1; 
}


inline int Darray::contains(const void* ptr) const 
{ 
    return (find(ptr) != -1); 
}


inline int Darray::length() const 
{
    if ((mUsedLength == 0) || (mArray[mUsedLength - 1] != NULL)) {
	return mUsedLength;    // Fast and easy way used in most cases
    } else {
	return findLength();  // Finding the actual length
    }
}


inline int Darray::length()
{
    if ((mUsedLength != 0) && (mArray[mUsedLength - 1] == NULL)) {
	mUsedLength = findLength();
    }
    return mUsedLength;   
}


inline void Darray::init() { resize(0); }

inline Darray::~Darray()   { init();    }


inline void*& Darray::operator [](int index) 
{
    MASSERT(index >= 0);
    
    if (index >= mUsedLength) {
	mUsedLength = index + 1;
	
	if (index >= mAllocLength)
	    extendArray(index + 1);
    }
    
    return mArray[index];
} // []


inline void* Darray::operator [](int index) const
{
    MASSERT(index >= 0);
    
    if (index >= mUsedLength) {
	return NULL;
    } else {
	return mArray[index];
    }
} // []


#ifndef hpux
#pragma C-Cover on
#pragma warning(default: 4068)
#endif


AMODELER_NAMESPACE_END
#endif 





