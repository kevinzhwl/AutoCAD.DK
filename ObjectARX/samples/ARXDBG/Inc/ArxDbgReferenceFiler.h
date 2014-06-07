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

#ifndef ARXDBGREFERENCEFILER_H
#define ARXDBGREFERENCEFILER_H

/****************************************************************************
**
**	CLASS ArxDbgReferenceFiler:
**
**	**jma
**
*************************************/

class ArxDbgReferenceFiler: public AcDbDwgFiler {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgReferenceFiler);

				ArxDbgReferenceFiler()	{}
    virtual		~ArxDbgReferenceFiler()	{}

    virtual Acad::ErrorStatus   filerStatus() const							{ return Acad::eOk; }
    virtual AcDb::FilerType		filerType() const							{ return AcDb::kIdFiler; }
    virtual void                setFilerStatus(Acad::ErrorStatus)			{}
    virtual void                resetFilerStatus()							{}

    virtual Acad::ErrorStatus   readHardOwnershipId(AcDbHardOwnershipId*)	{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeHardOwnershipId(const AcDbHardOwnershipId&);

    virtual Acad::ErrorStatus   readSoftOwnershipId(AcDbSoftOwnershipId*)	{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeSoftOwnershipId(const AcDbSoftOwnershipId&);

    virtual Acad::ErrorStatus   readHardPointerId(AcDbHardPointerId*)	    { return Acad::eOk; }
    virtual Acad::ErrorStatus   writeHardPointerId(const AcDbHardPointerId&);

    virtual Acad::ErrorStatus   readSoftPointerId(AcDbSoftPointerId*)		{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeSoftPointerId(const AcDbSoftPointerId&);

    virtual Acad::ErrorStatus   readChar(char*)								{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeChar(char)								{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readString(char**)							{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeString(const char*)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readBChunk(ads_binary*)						{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeBChunk(const ads_binary&)				{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readAcDbHandle(AcDbHandle*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeAcDbHandle(const AcDbHandle&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readInt32(Adesk::Int32*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeInt32(Adesk::Int32)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readInt16(Adesk::Int16*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeInt16(Adesk::Int16)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readUInt32(Adesk::UInt32*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeUInt32(Adesk::UInt32)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readUInt16(Adesk::UInt16*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeUInt16(Adesk::UInt16)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readUInt8(Adesk::UInt8*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeUInt8(Adesk::UInt8)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readBoolean(Adesk::Boolean*)				{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeBoolean(Adesk::Boolean)				{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readBool(bool*)								{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeBool(bool)								{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readDouble(double*)							{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeDouble(double)							{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readPoint2d(AcGePoint2d*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writePoint2d(const AcGePoint2d&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readPoint3d(AcGePoint3d*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writePoint3d(const AcGePoint3d&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readVector2d(AcGeVector2d*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeVector2d(const AcGeVector2d&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readVector3d(AcGeVector3d*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeVector3d(const AcGeVector3d&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readScale3d(AcGeScale3d*)					{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeScale3d(const AcGeScale3d&)			{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readBytes(void*, Adesk::UInt32)				{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeBytes(const void*, Adesk::UInt32)		{ return Acad::eOk; }

    virtual Acad::ErrorStatus   readAddress(void**)							{ return Acad::eOk; }
    virtual Acad::ErrorStatus   writeAddress(const void*)					{ return Acad::eOk; }

    virtual Acad::ErrorStatus   seek(long offset, int method)				{ return Acad::eOk;; }
    virtual long                tell() const								{ return 0L; }

	void						reset();	// set all arrays to empty

		// data members
    AcDbObjectIdArray	m_hardPointerIds;  
    AcDbObjectIdArray	m_softPointerIds;  
    AcDbObjectIdArray	m_hardOwnershipIds;  
    AcDbObjectIdArray	m_softOwnershipIds;  
};


#endif    // ARXDBGREFERENCEFILER_H
