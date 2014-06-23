#ifndef AD_DBDATE_H
#define AD_DBDATE_H
//
// (C) Copyright 1994-1997 by Autodesk, Inc.
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
// DESCRIPTION: API for date class.

#include "acdb.h"

#ifdef target
#undef target
#endif

class AcDbDwgFiler;

class AcDbDate
{
public:
    AcDbDate();
    AcDbDate(const AcDbDate&);
    virtual ~AcDbDate();

    AcDbDate& operator= (const AcDbDate&);

    // Get and set the date.
    //
    void  getDate (short& month, short& day, short& year) const;
    void  setDate (short month, short day, short year);
    short month   () const;
    void  setMonth(short);
    short day     () const;
    void  setDay  (short);
    short year    () const;
    void  setYear (short);

    // Get and set the time.
    //
    void  getTime  (short& hour, short& min, short& sec, short& msec) const;
    void  setTime  (short hour, short min, short sec, short msec);
    short hour     () const;
    void  setHour  (short);
    short minute   () const;
    void  setMinute(short);
    short second   () const;
    void  setSecond(short);
    short millisecond() const;
    void  setMillisecond(short);
 
    // Get/Set Julian representation for the date.
    //
    long   julianDay           () const;
    long   msecsPastMidnight   () const;
    void   setJulianDay        (long julianDay);
    void   setMsecsPastMidnight(long msec);
    void   setJulianDate       (long julianDay, long msec);
    double julianFraction      () const;
    void   setJulianFraction   (double);
 
    // Equality test.
    //
    Adesk::Boolean operator== (const AcDbDate&) const;

    // Simple date arithmetic.
    //
    virtual AcDbDate& add      (const AcDbDate &date);
    virtual AcDbDate& subtract (const AcDbDate &date);

    // Internal use.
    //
    Adesk::Boolean isNormalized() const;
    void normalize();

    // Dwg in and out.
    //
    Acad::ErrorStatus dwgOut(AcDbDwgFiler *outFiler) const;
    Acad::ErrorStatus dwgIn (AcDbDwgFiler *inFiler);

private:
    friend class AcDbImpDate;
    AcDbImpDate *mpImpDate;
};

#endif
