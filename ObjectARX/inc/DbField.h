//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2004-2006  by Autodesk, Inc.
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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
// 
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            DbField.h
//
// Description:     AcDbObject derived API classes for fields. 
//                  Contains the following classes: 
//                      AcDbField
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"
#include "AcField.h"
#include "acstring.h"

class AcDbField;


typedef AcArray<AcDbField*> AcDbFieldArray;


//*************************************************************************
// AcFd
//*************************************************************************

typedef struct AcFd
{
    // Enum for acdbEvaluateFields
    enum EvalFields
    {
        kEvalRecursive      = (0x1 << 0),       // Recursively evaluate complex objects
    };

    // Options for function acdbConvertFieldsToText()
    enum ConvertFieldToText
    {
        kConvertFieldToTextNone         = 0,
        kEvaluateBeforeConversion       = (0x1 << 0),
        kExcludeEvaluatorsInList        = (0x1 << 1),
        kIgnoreEvaluatorVersion         = (0x1 << 2),
    };

} AcFd;


//*************************************************************************
// AcHyperlink
//*************************************************************************

typedef struct AcHyperlink
{
    AcString                msUrl;
    AcString                msSubLocation;
    AcString                msDescription;
    long                    mlFlag;

} AcHyperlink;


//*************************************************************************
// AcDbField
//*************************************************************************

class AcDbField : public AcDbObject
{
public:
    enum State
    {
        kInitialized        = (0x1 << 0),       // Field has been initialized by the evaluator
        kCompiled           = (0x1 << 1),       // Field has beene compiled
        kModified           = (0x1 << 2),       // Field code has been modified, but not yet evaluated
        kEvaluated          = (0x1 << 3),       // Field has been evaluated
        kHasCache           = (0x1 << 4),       // Field has evaluated cache
        kHasFormattedString = (0x1 << 5),       // For internal use only. Field has cached formatted string. 
    };

    enum EvalOption
    {
        kDisable            = 0,                // Disable evaluation of field
        kOnOpen             = (0x1 << 0),       // Evaluate on drawing open
        kOnSave             = (0x1 << 1),       // Evaluate on drawing save
        kOnPlot             = (0x1 << 2),       // Evaluate on drawing plot
        kOnEtransmit        = (0x1 << 3),       // Evaluate on drawing etransmit
        kOnRegen            = (0x1 << 4),       // Evaluate on drawing regen
        kOnDemand           = (0x1 << 5),       // Evaluate on demand
        kAutomatic          = (kOnOpen | kOnSave | kOnPlot | 
                               kOnEtransmit | kOnRegen | kOnDemand),    // No restriction
    };

    enum EvalContext
    {
        kOpen               = (0x1 << 0),       // Field is being evaluated during open
        kSave               = (0x1 << 1),       // Field is being evaluated during save
        kPlot               = (0x1 << 2),       // Field is being evaluated during plot
        kEtransmit          = (0x1 << 3),       // Field is being evaluated during etransmit
        kRegen              = (0x1 << 4),       // Field is being evaluated during regen
        kDemand             = (0x1 << 5),       // Field is being evaluated on demand
        kPreview            = (0x1 << 6),       // Field is being evaluated for preview of field result
        kPlotPreview        = (0x1 << 7),       // Field is being evaluated during plot preview
    };

    enum EvalStatus
    {
        kNotYetEvaluated    = (0x1 << 0),       // Not yet evaluated
        kSuccess            = (0x1 << 1),       // Evaluated successfully
        kEvaluatorNotFound  = (0x1 << 2),       // Evaluator not found
        kSyntaxError        = (0x1 << 3),       // Field code syntax error
        kInvalidCode        = (0x1 << 4),       // Invalid field code
        kInvalidContext     = (0x1 << 5),       // Invalid context to evaluate field
        kOtherError         = (0x1 << 6),       // Evaluation error
    };

    enum FieldCodeFlag
    {
        kFieldCode          = (0x1 << 0),       // Get raw field code. Used only in getFieldCode().
        kEvaluatedText      = (0x1 << 1),       // Get evaluated text. Used only in getFieldCode().
        kEvaluatedChildren  = (0x1 << 2),       // Get field code with evaluated text for child fields. Used only in getFieldCode().
        kObjectReference    = (0x1 << 3),       // Get child fields as object references if this is text field or 
                                                // this field as object reference if this is not text field. Used only in getFieldCode().
        kAddMarkers         = (0x1 << 4),       // Include markers around field codes. Used only in getFieldCode().
        kEscapeBackslash    = (0x1 << 5),       // Convert single backslashes to double backslashes. Used only in getFieldCode().
        kStripOptions       = (0x1 << 6),       // Strip the standard options from field code. Used only in getFieldCode().
        kPreserveFields     = (0x1 << 7),       // Try to preserve existing fields. Used only in setFieldCode().
        kTextField          = (0x1 << 8),       // Treat the field as text with embedded fields. Used only in setFieldCode().
        kPreserveOptions    = (0x1 << 9),       // Preserve the current standard options. Used only in setFieldCode(). For internal use.
        kDetachChildren     = (0x1 << 10),      // For internal use. Detach the child fields without erasing/deleting them. 
                                                // Used only in setFieldCode().
        kChildObjectReference = (0x1 << 11),    // For internal use. Get child fields as object references. 
                                                // Used only in getFieldCode().
        kForExpression      = (0x1 << 12),      // For internal use. Used with kEvaluatedText/kEvaluatedChildren.
                                                // Get the value in a format which can be used in arithmatic expressions. Used only in getFieldCode().
    };

    enum FilingOption
    {
        kSkipFilingResult   = (0x1 << 0),       // Don't file field value
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbField);

    ACDB_PORT AcDbField(void);
    ACDB_PORT AcDbField(const ACHAR * pszFieldCode, bool bTextField = false);
    ACDB_PORT ~AcDbField(void);

    ACDB_PORT Acad::ErrorStatus setInObject (AcDbObject* pObj, 
                                             const ACHAR * pszPropName);
    ACDB_PORT Acad::ErrorStatus postInDatabase(AcDbDatabase* pDb);
    ACDB_PORT AcDbField::State state        (void) const;
    ACDB_PORT AcDbField::EvalStatus evaluationStatus(int* pnErrCode = NULL, 
                                             ACHAR ** pszErrMsg = NULL) const;
    ACDB_PORT AcDbField::EvalOption evaluationOption(void) const;
    ACDB_PORT Acad::ErrorStatus setEvaluationOption(AcDbField::EvalOption nEvalOption);
    ACDB_PORT AcDbField::FilingOption filingOption(void) const;
    ACDB_PORT Acad::ErrorStatus setFilingOption(AcDbField::FilingOption nOption);

    ACDB_PORT const ACHAR  * evaluatorId    (void) const;
    ACDB_PORT Acad::ErrorStatus setEvaluatorId(const ACHAR * pszEvaluatorId);
    bool            isTextField             (void) const;
    Acad::ErrorStatus convertToTextField    (void);

    ACDB_PORT const ACHAR * getFieldCode     (AcDbField::FieldCodeFlag nFlag,
                                             AcArray<AcDbField*>* pChildFields = NULL, 
                                             AcDb::OpenMode mode = AcDb::kForRead) const;
    ACDB_PORT Acad::ErrorStatus getFieldCode(ACHAR*& pszFieldCode, 
                                             AcDbField::FieldCodeFlag nFlag,
                                             AcArray<AcDbField*>* pChildFields = NULL, 
                                             AcDb::OpenMode mode = AcDb::kForRead) const;
    ACDB_PORT Acad::ErrorStatus setFieldCode(const ACHAR* pszFieldCode, 
                                             AcDbField::FieldCodeFlag nFlag = (AcDbField::FieldCodeFlag) 0,
                                             AcDbFieldArray* pChildFields = NULL);

    ACDB_PORT int   childCount              (void) const;
    ACDB_PORT Acad::ErrorStatus getChild    (int iIndex, 
                                             AcDbField*& pField, 
                                             AcDb::OpenMode mode);

    ACDB_PORT const ACHAR * getFormat       (void) const;
    ACDB_PORT Acad::ErrorStatus getFormat   (ACHAR*& pszFormat) const;
    ACDB_PORT Acad::ErrorStatus setFormat   (const ACHAR* pszFormat);

    ACDB_PORT Acad::ErrorStatus evaluate    (int nContext, 
                                             AcDbDatabase* pDb, 
                                             int* pNumFound     = NULL,
                                             int* pNumEvaluated = NULL);
    ACDB_PORT AcValue::DataType dataType    (void) const;

    ACDB_PORT const ACHAR * getValue        (void) const;
    ACDB_PORT Acad::ErrorStatus getValue    (ACHAR*& pszValue) const;
    ACDB_PORT Acad::ErrorStatus getValue    (AcValue& value) const;
    ACDB_PORT Acad::ErrorStatus getValue    (AcFdFieldValue& value) const;

    ACDB_PORT bool  hasHyperlink            (void) const;
    ACDB_PORT Acad::ErrorStatus getHyperlink(AcHyperlink& hlink) const;
    ACDB_PORT Acad::ErrorStatus getHyperlink(ACHAR** pszName,
                                             ACHAR** pszDescription, 
                                             ACHAR** pszSubLocation,
                                             ACHAR** pszDisplayString,
                                             long* pFlag) const;
    ACDB_PORT Acad::ErrorStatus setHyperlink(const AcHyperlink& hlink);
    ACDB_PORT Acad::ErrorStatus setHyperlink(const ACHAR* pszName, 
                                             const ACHAR* pszDescription, 
                                             const ACHAR* pszSubLocation = NULL);
    ACDB_PORT Acad::ErrorStatus setHyperlink(const ACHAR* pszName, 
                                             const ACHAR* pszDescription, 
                                             const ACHAR* pszSubLocation,
                                             long lFlag);
    ACDB_PORT Acad::ErrorStatus removeHyperlink(void);

    ACDB_PORT Acad::ErrorStatus getData     (const ACHAR* pszKey, 
                                             AcValue* pData) const;
    ACDB_PORT Acad::ErrorStatus setData     (const ACHAR* pszKey, 
                                             const AcValue* pData);
    ACDB_PORT Acad::ErrorStatus setData     (const ACHAR* pszKey, 
                                             const AcValue* pData,
                                             bool bRecursive);

public:
    // Base class overrides
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus subClose();
};


//*************************************************************************
// Global exported functions
//*************************************************************************

ACDB_PORT AcFdFieldEngine* acdbGetFieldEngine(void);
ACDB_PORT bool      acdbGetFieldMarkers     (const ACHAR*& pszPrefix, 
                                             const ACHAR*& pszSuffix);
ACDB_PORT bool      acdbHasFields           (const ACHAR * pszText);
ACDB_PORT bool      acdbFindField           (const ACHAR * pszText, 
                                             int iSearchFrom, 
                                             int& nStartPos, 
                                             int& nEndPos);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectId& objId, 
                                             int nContext, 
                                             const ACHAR* pszPropName = NULL, 
                                             AcDbDatabase* pDb        = NULL, 
                                             AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive,
                                             int* pNumFound           = NULL,
                                             int* pNumEvaluated       = NULL);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectId& objId, 
                                             int nContext, 
                                             const AcDbObjectIdArray* pFieldsToEvaluate, 
                                             const ACHAR* pszEvaluatorId, 
                                             AcDbDatabase* pDb, 
                                             AcFd::EvalFields nEvalFlag, 
                                             int* pNumFound, 
                                             int* pNumEvaluated);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectIdArray& objIds, 
                                             int nContext, 
                                             const ACHAR* pszPropName  = NULL, 
                                             AcDbDatabase* pDb         = NULL, 
                                             AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive, 
                                             int* pNumFound            = NULL, 
                                             int* pNumEvaluated        = NULL);
ACDB_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectIdArray& objIds, 
                                             int nContext, 
                                             const AcDbObjectIdArray* pFieldsToEvaluate, 
                                             const ACHAR* pszEvaluatorId, 
                                             AcDbDatabase* pDb, 
                                             AcFd::EvalFields nEvalFlag, 
                                             int* pNumFound, 
                                             int* pNumEvaluated);
ACDB_PORT Acad::ErrorStatus acdbConvertFieldsToText(AcDbDatabase* pDb, 
                                             const AcStringArray* pEvalIds, 
                                             AcFd::ConvertFieldToText nOption);
ACDB_PORT Acad::ErrorStatus acdbConvertFieldsToText(const AcDbObjectIdArray& objIds, 
                                             const AcStringArray* pEvalIds, 
                                             AcFd::ConvertFieldToText nOption);
ACDB_PORT Acad::ErrorStatus acdbMakeFieldCode(const ACHAR * pszFieldExpr, 
                                             ACHAR*& pszFieldCode);
ACDB_PORT Acad::ErrorStatus acdbMakeFieldCode(const ACHAR * pszFieldExpr, 
                                             ACHAR*& pszFieldCode, 
                                             const ACHAR * pszEvalId, 
                                             const ACHAR * pszFormat, 
                                             const AcHyperlink* pHyperlink);
