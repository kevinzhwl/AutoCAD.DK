//
//
// (C) Copyright 2007-2010 by Autodesk, Inc.
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

#pragma once

#include "acstring.h"
#include "acadstrc.h"

typedef UINT64    AcDgnRefFileId;

struct AcDbDgnRefFileData {
    enum FileType{
        kDgnFile   = 1,
        kDwgFile   = 2,
        kImageFile = 3,
        kOtherFile = 4
    };
    FileType type;
    AcString savedPathAndName;
    AcString foundPathAndName;
    AcDgnRefFileId refId;
};

typedef AcArray<AcDbDgnRefFileData*> AcDbRefFileDataPtrArray;
typedef AcArray<AcDgnRefFileId>     AcDbDgnRefFileIdArray;

Acad::ErrorStatus
acdbGetDgnFileReferences(const ACHAR* fileName, const ACHAR* pwd,
    AcDbRefFileDataPtrArray& files);

class AcDbDgnRefFileRepath
{
public:
    AcDbDgnRefFileRepath() : m_fileHandle(NULL)  {};
    Acad::ErrorStatus setFile(const AcString& dgnPathAndFilename, const ACHAR* pwd);
    ~AcDbDgnRefFileRepath();
    Acad::ErrorStatus getReferenceFilePaths(AcDbRefFileDataPtrArray& refFiles);
    Acad::ErrorStatus rePath(const AcDbDgnRefFileIdArray& refFileIds,
        const AcStringArray& newRefFileNames);

private:
    void* m_fileHandle;
};