#ifndef AD_DBLYFILT_H
#define AD_DBLYFILT_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// Default implementation for Layer Filter.
//

#include "dbfilter.h"

#pragma pack (push, 8)

class AcDbLayerFilter: public  AcDbFilter
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerFilter);
	     AcDbLayerFilter();
    virtual ~AcDbLayerFilter();

    virtual AcRxClass* indexClass() const;
    virtual Adesk::Boolean isValid() const;

    Acad::ErrorStatus add(const char* pLayer);
    Acad::ErrorStatus remove(const char* pLayer);
    Acad::ErrorStatus getAt(int index, const char*& pName) const;
    int layerCount() const;
};

#pragma pack (pop)

#endif // AD_DBLYFILT_H
