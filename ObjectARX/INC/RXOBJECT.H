#ifndef AD_RXOBJECT_H
#define AD_RXOBJECT_H 1
//
// Copyright (C) 1992-1997 by Autodesk, Inc.
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

#include "rxsys.h"
#include "rxdefs.h"
#include "rxcom.h"
#include "rxboiler.h"

class AcRxClass;

class AcRxObject : public IUnknown
{
public:
    virtual ~AcRxObject();

    static AcRxClass*      desc();
    static AcRxObject*     cast(const AcRxObject * inPtr);

    inline Adesk::Boolean  isKindOf(const AcRxClass * aClass) const;

    AcRxObject*	    	   x(AcRxClass* protocolClass) const;
    AcRxObject*	    	   queryX(AcRxClass* protocolClass) const;
    virtual AcRxClass*     isA() const;

    virtual AcRxObject*    clone() const;
    virtual void           copyFrom(const AcRxObject* other);
    virtual Adesk::Boolean isEqualTo(const AcRxObject * other) const;
    virtual AcRx::Ordering comparedTo(const AcRxObject * other) const;

    // COM support. This is a no-op for any class not derived from AcDbObject.
    //
    virtual HRESULT __stdcall QueryInterface(REFIID, void**);
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();

#ifdef ACDBLIB
    // These two functions are not available in the ARX API
    //
    void* operator new(unsigned nSize);
    void operator delete(void* p);
#endif

protected:
    AcRxObject();
};

#include "rxclass.h"

#define ACRX_X_CALL(a,b) b::cast(a->x(b::desc()))

#include "rxdict.h"

#endif
