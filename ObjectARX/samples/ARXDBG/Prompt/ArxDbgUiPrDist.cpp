//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//

#include "stdafx.h"
#include "ArxDbgUiPrDist.h"

/****************************************************************************
**
**  ArxDbgUiPrDist::init
**      handle the common work for the constructors
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::init()
{
    m_value = 0.0;
    m_minVal = 0.0;
    m_maxVal = 0.0;
    m_useDashedLine = false;
    m_2dOnly = false;
    m_unit = -1;
    m_precision = -1;
    m_allowNone = false;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::ArxDbgUiPrDist
**
**  **jma
**
*************************************/

ArxDbgUiPrDist::ArxDbgUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_distType(type),
    m_basePt(AcGePoint3d::kOrigin),
    m_useBasePt(false)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrDist::ArxDbgUiPrDist
**
**  **jma
**
*************************************/

ArxDbgUiPrDist::ArxDbgUiPrDist(LPCTSTR msg, LPCTSTR keyWordList, DistType type, const AcGePoint3d& basePt)
:   ArxDbgUiPrBase(msg, keyWordList),
    m_distType(type),
    m_basePt(basePt),
    m_useBasePt(true)
{
    init();
}

/****************************************************************************
**
**  ArxDbgUiPrDist::~ArxDbgUiPrDist
**
**  **jma
**
*************************************/

ArxDbgUiPrDist::~ArxDbgUiPrDist()
{
}

/****************************************************************************
**
**  ArxDbgUiPrDist::go
**
**  **jma
**
*************************************/

ArxDbgUiPrBase::Status
ArxDbgUiPrDist::go()
{
    CString prompt;
    int initFlag = 0;

        // set up prompt
    prompt.Format(_T("\n%s: "), message());

        // set up init flag
    if (m_allowNone == false)
        initFlag += RSG_NONULL;

    if (m_distType == kNoZero)
        initFlag += RSG_NOZERO;
    else if (m_distType == kNoNeg)
        initFlag += RSG_NONEG;
    else if (m_distType == kNoNegNoZero)
        initFlag += (RSG_NOZERO+RSG_NONEG);

    int result;
    while (1) {
        acedInitGet(initFlag, keyWords());
        if (m_useBasePt)
            result = acedGetDist(asDblArray(m_basePt), prompt, &m_value);
        else
            result = acedGetDist(NULL, prompt, &m_value);

        if (result == RTNORM) {
            if (inRange())
                return ArxDbgUiPrBase::kOk;
        }
        else if (result == RTKWORD) {
            acedGetInput(m_keyWordPicked.GetBuffer(512));
            m_keyWordPicked.ReleaseBuffer();
            return ArxDbgUiPrBase::kKeyWord;
        }
        else
            return ArxDbgUiPrBase::kCancel;
    }
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setRange
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setRange(double minVal, double maxVal)
{
    ASSERT(maxVal >= minVal);

    m_minVal = minVal;
    m_maxVal = maxVal;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::inRange
**
**  **jma
**
*************************************/

bool
ArxDbgUiPrDist::inRange()
{
    if (m_distType == ArxDbgUiPrDist::kRange) {
        ASSERT(m_minVal != m_maxVal);    // make sure they set ranges!
        if ((m_value >= m_minVal) && (m_value <= m_maxVal))
            return true;
        else {
            char str1[512], str2[512];
            acdbRToS(m_minVal, m_unit, m_precision, str1);
            acdbRToS(m_maxVal, m_unit, m_precision, str2);
            acutPrintf(_T("\nValue must be in range %s to %s."), str1, str2);
            return false;
        }
    }
    else
        return true;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::value
**
**  **jma
**
*************************************/

double
ArxDbgUiPrDist::value()
{
    return m_value;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setDistType
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setDistType(DistType newType)
{
    m_distType = newType;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setBasePt(const AcGePoint3d& basePt)
{
    m_basePt = basePt;
    m_useBasePt = Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setUseBasePt
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setUseBasePt(bool useIt)
{
    m_useBasePt = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setUseDashedLine
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setUseDashedLine(bool useIt)
{
    m_useDashedLine = useIt;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::set2dOnly
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::set2dOnly(bool only2d)
{
    m_2dOnly = only2d;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setUnit
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setUnit(int unit)
{
    m_unit = unit;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setPrecision
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setPrecision(int precision)
{
    m_precision = precision;
}

/****************************************************************************
**
**  ArxDbgUiPrDist::setAllowNone
**
**  **jma
**
*************************************/

void
ArxDbgUiPrDist::setAllowNone(bool allowIt)
{
    m_allowNone = allowIt;
}


