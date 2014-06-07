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
#include "ArxDbgDbAdeskLogoStyle.h"
#include "ArxDbgUtils.h"

     // MDI safe statics
Adesk::Int16    ArxDbgDbAdeskLogoStyle::m_version = 0;
LPCTSTR			ArxDbgDbAdeskLogoStyle::m_dictName = _T("ARXDBG_ADESK_LOGO_STYLES");


ACRX_DXF_DEFINE_MEMBERS(ArxDbgDbAdeskLogoStyle, ArxDbgDbDictRecord,
						AcDb::kDHL_1015, AcDb::kMRelease0,
						0, ARXDBG_ADESK_LOGO_STYLE, ArxDbg)

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::ArxDbgDbAdeskLogoStyle
**
**  **jma
**
*************************************/

ArxDbgDbAdeskLogoStyle::ArxDbgDbAdeskLogoStyle()
:   m_solidFill(true),
    m_label(_T("Autodesk"))
{
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::ArxDbgDbAdeskLogoStyle
**
**  **jma
**
*************************************/

ArxDbgDbAdeskLogoStyle::~ArxDbgDbAdeskLogoStyle()
{
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::isSolidFill
**
**  **jma
**
*************************************/

bool
ArxDbgDbAdeskLogoStyle::isSolidFill() const
{
    assertReadEnabled();
    return m_solidFill;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::setSolidFill
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::setSolidFill(bool doIt)
{
    if (m_solidFill != doIt) {
        assertWriteEnabled();
        m_solidFill = doIt;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::label
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgDbAdeskLogoStyle::label() const
{
    assertReadEnabled();
    return m_label;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::setLabel
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::setLabel(LPCTSTR newLabel)
{
        // we allow a null string label, so check for NULL
        // and turn it into NullString
    if (newLabel == NULL) {
        if (m_label.IsEmpty() == FALSE) {   // make sure it will actually change
            assertWriteEnabled();
            m_label.Empty();
        }
        return Acad::eOk;
    }

        // don't allow to be longer than 255 for DXF simplicity
    int len = _tcslen(newLabel);
    if (len > 255)
        return Acad::eStringTooLong;

    if (m_label.Compare(newLabel)) {
        assertWriteEnabled();
        m_label = newLabel;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::textStyleId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgDbAdeskLogoStyle::textStyleId() const
{
    assertReadEnabled();
    return m_textStyleId;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::setTextStyleId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::setTextStyleId(const AcDbObjectId& styleId)
{
    if (styleId == AcDbObjectId::kNull)
        return Acad::eNullObjectId;

    if (styleId != m_textStyleId) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_textStyleId = styleId;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbDictRecord::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    char* tmpStr = NULL;    // must explicitly set to NULL or readItem() crashes!

    filer->readItem(&tmpStr);
    m_label = tmpStr;
    acutDelString(tmpStr);

    filer->readItem(&m_solidFill);
    filer->readItem(&m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbDictRecord::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    filer->writeItem(static_cast<const char*>(m_label));
    filer->writeItem(m_solidFill);
    filer->writeItem(m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxDbgDbDictRecord::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfSolidFill) {
			bool doSolidFill = (rb.resval.rint == 0) ? false : true;
            setSolidFill(doSolidFill);
		}
        else if (rb.restype == kDxfLabel)
            setLabel(rb.resval.rstring);        // NOTE: normally have to free string from resbuf... not in this case, DXF Filer does
        else if (rb.restype == kDxfTextStyle) {
            AcDbObjectId tmpId;
            tmpId.setFromOldId(rb.resval.rlong);
            setTextStyleId(tmpId);
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogoStyle::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbDictRecord::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeItem(kDxfLabel, static_cast<const char*>(m_label));
    filer->writeItem(kDxfSolidFill, static_cast<int>(m_solidFill));
    filer->writeItem(kDxfTextStyle, m_textStyleId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::subSetDatabaseDefaults
**      if text style id hasn't yet been initialized, then set it to be
**  whatever the current textstyle is for this database.
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogoStyle::subSetDatabaseDefaults(AcDbDatabase* pDb)
{
        // get past ARX bug of calling this on Undo/Redo
        // without opening for Write!  See AecDbAdeskLogo.cpp
        // for details.
    if (isWriteEnabled() == Adesk::kFalse)
        return;

    ASSERT(pDb != NULL);
    if (m_textStyleId == AcDbObjectId::kNull)
        m_textStyleId = pDb->textstyle();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogoStyle::getStandardStyle
**		look up the style "STANDARD" so that we can set it as the default
**	logoStyle for new objects.
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgDbAdeskLogoStyle::getStandardStyle(AcDbDatabase* db, bool makeIfNotThere)
{
    Acad::ErrorStatus es;
    AcDbObjectId styleId;
    AcDbDictionary* dict;

	const char* standardStrPtr = acdbGetReservedString(AcDb::kStandard, false);
	ASSERT(standardStrPtr != NULL);
	
	dict = ArxDbgUtils::openDictionaryForRead(m_dictName, db);
    if (dict) {
        es = dict->getAt(standardStrPtr, styleId);
		dict->close();

		if (es == Acad::eOk)
			return styleId;

		if (makeIfNotThere == false)
			return AcDbObjectId::kNull;
	}

		// wasn't already there, so we need to make it
	dict = ArxDbgUtils::openDictionaryForWrite(m_dictName, true, db);
	if (dict) {
        ArxDbgDbAdeskLogoStyle* newRec = new ArxDbgDbAdeskLogoStyle;
        es = dict->setAt(standardStrPtr, newRec, styleId);
		dict->close();
        if (es == Acad::eOk) {
            newRec->close();
			return styleId;
        }
        else {
            acutPrintf("\nERROR: Could not add new ArxDbgDbAdeskLogoStyle (%s)", ArxDbgUtils::rxErrorStr(es));
            delete newRec;
        }
    }

	return AcDbObjectId::kNull;
}



