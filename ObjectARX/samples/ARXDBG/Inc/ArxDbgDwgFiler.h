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

#ifndef ARXDBGDWGFILER_H
#define ARXDBGDWGFILER_H

/****************************************************************************
**
**	CLASS ArxDbgDwgFiler:
**
**	**jma
**
*************************************/

class ArxDbgDwgFiler: public AcDbDwgFiler {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgDwgFiler);

                ArxDbgDwgFiler();
    virtual		~ArxDbgDwgFiler();

    virtual Acad::ErrorStatus   filerStatus() const;
    virtual AcDb::FilerType		filerType() const;
    virtual void                setFilerStatus(Acad::ErrorStatus);
    virtual void                resetFilerStatus();

    virtual Acad::ErrorStatus   readHardOwnershipId(AcDbHardOwnershipId*);
    virtual Acad::ErrorStatus   writeHardOwnershipId(const AcDbHardOwnershipId&);

    virtual Acad::ErrorStatus   readSoftOwnershipId(AcDbSoftOwnershipId*);
    virtual Acad::ErrorStatus   writeSoftOwnershipId(const AcDbSoftOwnershipId&);

    virtual Acad::ErrorStatus   readHardPointerId(AcDbHardPointerId*) ;
    virtual Acad::ErrorStatus   writeHardPointerId(const AcDbHardPointerId&);

    virtual Acad::ErrorStatus   readSoftPointerId(AcDbSoftPointerId*) ;
    virtual Acad::ErrorStatus   writeSoftPointerId(const AcDbSoftPointerId&);

    virtual Acad::ErrorStatus   readChar(char*);
    virtual Acad::ErrorStatus   writeChar(char);

    virtual Acad::ErrorStatus   readString(char**);
    virtual Acad::ErrorStatus   writeString(const char*);

    virtual Acad::ErrorStatus   readBChunk(ads_binary*);
    virtual Acad::ErrorStatus   writeBChunk(const ads_binary&);

    virtual Acad::ErrorStatus   readAcDbHandle(AcDbHandle*);
    virtual Acad::ErrorStatus   writeAcDbHandle(const AcDbHandle&);

    virtual Acad::ErrorStatus   readInt32(Adesk::Int32*);
    virtual Acad::ErrorStatus   writeInt32(Adesk::Int32);

    virtual Acad::ErrorStatus   readInt16(Adesk::Int16*);
    virtual Acad::ErrorStatus   writeInt16(Adesk::Int16);

    virtual Acad::ErrorStatus   readUInt32(Adesk::UInt32*);
    virtual Acad::ErrorStatus   writeUInt32(Adesk::UInt32);

    virtual Acad::ErrorStatus   readUInt16(Adesk::UInt16*);
    virtual Acad::ErrorStatus   writeUInt16(Adesk::UInt16);

    virtual Acad::ErrorStatus   readUInt8(Adesk::UInt8*);
    virtual Acad::ErrorStatus   writeUInt8(Adesk::UInt8);

    virtual Acad::ErrorStatus   readBoolean(Adesk::Boolean*);
    virtual Acad::ErrorStatus   writeBoolean(Adesk::Boolean);

    virtual Acad::ErrorStatus   readBool(bool*);
    virtual Acad::ErrorStatus   writeBool(bool);

    virtual Acad::ErrorStatus   readDouble(double*);
    virtual Acad::ErrorStatus   writeDouble(double);

    virtual Acad::ErrorStatus   readPoint2d(AcGePoint2d*);
    virtual Acad::ErrorStatus   writePoint2d(const AcGePoint2d&);

    virtual Acad::ErrorStatus   readPoint3d(AcGePoint3d*);
    virtual Acad::ErrorStatus   writePoint3d(const AcGePoint3d&);

    virtual Acad::ErrorStatus   readVector2d(AcGeVector2d*);
    virtual Acad::ErrorStatus   writeVector2d(const AcGeVector2d&);

    virtual Acad::ErrorStatus   readVector3d(AcGeVector3d*);
    virtual Acad::ErrorStatus   writeVector3d(const AcGeVector3d&);

    virtual Acad::ErrorStatus   readScale3d(AcGeScale3d*);
    virtual Acad::ErrorStatus   writeScale3d(const AcGeScale3d&);

    virtual Acad::ErrorStatus   readBytes(void*, Adesk::UInt32);
    virtual Acad::ErrorStatus   writeBytes(const void*, Adesk::UInt32);

    virtual Acad::ErrorStatus   readAddress(void**);
    virtual Acad::ErrorStatus   writeAddress(const void*);

    virtual Acad::ErrorStatus   seek(long offset, int method);
    virtual long                tell() const;

    void    setFilerType(AcDb::FilerType newType)    { m_filerType = newType; }

private:
    Acad::ErrorStatus	m_stat;  
    CString             m_str;
    AcDb::FilerType     m_filerType;

        // helper functions
    void    printIt(LPCTSTR labelStr);
    void    objIdToStr(const AcDbObjectId& objId, CString& str);
};


#endif    // ARXDBGDWGFILER_H
