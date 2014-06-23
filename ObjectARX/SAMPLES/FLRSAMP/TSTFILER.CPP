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
// tstfiler.cpp 
//
// DESCRIPTION:
//
// This file contains the implementation of the class AsdkDwgFiler.

#include "acdb.h"    
#include "dbfiler.h" 
#include "tstfiler.h"
#ifndef unix
#include <io.h>
#endif
#include "util.h"
#include "adslib.h"

ACRX_CONS_DEFINE_MEMBERS(AsdkDwgFiler, AcDbDwgFiler, 0);


AsdkDwgFiler::AsdkDwgFiler(void)
 : mStat(Acad::eOk),fp(NULL),mEntType(0)
{
}


AsdkDwgFiler::~AsdkDwgFiler()
{
  if (fp != NULL)
  	 fclose(fp);
}

Acad::ErrorStatus 
AsdkDwgFiler::setFileName(const char*  fileName, int option){
 // if option is 0 then the file will be opened for write
 // if option is 1 then the file will be opened for read

 if (option ==0){
	if ((fp = fopen(fileName, "w")) ==NULL){
 	  ads_printf("Error opening in %s\n", fileName);
	  return Acad::eUnrecoverableErrors;
    }
 }
 else if (option==1){
	if ((fp = fopen(fileName, "r")) ==NULL){
 	  ads_printf("Error opening in %s\n", fileName);
	  return Acad::eUnrecoverableErrors;
    }
 }
 else 
 	  return Acad::eInvalidInput;

  return Acad::eOk;
}

void
AsdkDwgFiler::setEntityType(int  ecode){
 mEntType = ecode;
}


// _____________________  Data Reading	_____________________

Acad::ErrorStatus
AsdkDwgFiler::readBytes(void *buf, Adesk::UInt32 cnt)
{
   // no implementation 
   return Acad::eFilerError;

}

Acad::ErrorStatus
AsdkDwgFiler::readAddress(void** pp)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lu", (Adesk::UInt32)pp))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readChar(char *pVal)
{
	if (mStat != Acad::eOk)
		return mStat;
    if ((fread(pVal, sizeof(char),1,fp)==1)
         && (fgets(mBuffer, 512,fp)!= NULL))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readString(char **pVal)
{
	if (mStat != Acad::eOk)
		return mStat;
	size_t len;
	char  var[512];
	var[0]='\0';
	int   temp;
	if (fread(&len, sizeof(size_t),1,fp)==1){
	   if ((fread(var,sizeof(char),len,fp)==len)
	   && (fgets(mBuffer,512,fp)!=NULL)){
		temp = strlen(var);
		*pVal = strdup(var); 
		mStat = Acad::eOk;
	   }
	   else 
	   	 mStat = Acad::eFilerError;
	}
	else
		mStat = Acad::eFilerError;
    return mStat;

}


Acad::ErrorStatus
AsdkDwgFiler::readBChunk(ads_binary *pVal)
{
   ads_printf("readBChunk called\n");
   if (mStat != Acad::eOk)
		return mStat;

	size_t len;
	char  buff[512];
	short  clen;
	buff[0]='\0';

    if ((mStat == Acad::eOk) 
		&& (fread(&len, sizeof(size_t),1,fp)==1)
    	&& (fread(&clen, sizeof(short), 1, fp)==1) 
		&& (fread(buff, sizeof(char), len, fp)==len)
		&& (fgets(mBuffer,512,fp)!=NULL)){
		pVal->clen = clen;
		pVal->buf = strdup(buff);
		mStat = Acad::eOk;
	}
	else
	   mStat = Acad::eFilerError;
	return mStat;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readAcDbHandle(AcDbHandle *pVal)
{
	// no implementation 
	ads_printf("ReadAcDbHandle\n");

    return Acad::eFilerError;
}

Acad::ErrorStatus
AsdkDwgFiler::readInt32(Adesk::Int32 *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%ld",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat ;
}

Acad::ErrorStatus
AsdkDwgFiler::readInt16(Adesk::Int16 *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%d",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat ;
}


Acad::ErrorStatus
AsdkDwgFiler::readUInt32(Adesk::UInt32 *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lu",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readUInt16(Adesk::UInt16 *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%hu",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat ;
}


Acad::ErrorStatus
AsdkDwgFiler::readUInt8(Adesk::UInt8 *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%c",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readBoolean(Adesk::Boolean *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%d",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readHardOwnershipId(AcDbHardOwnershipId* pId)
{
	long  temp;
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%ld",&temp))==1)){
		pId->setFromOldId(temp);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readSoftOwnershipId(AcDbSoftOwnershipId* pId)
{
	long  temp;
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%ld",&temp))==1)){
		pId->setFromOldId(temp);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readHardPointerId(AcDbHardPointerId* pId)
{
	long  temp;
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%ld",&temp))==1)){
		pId->setFromOldId(temp);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readSoftPointerId(AcDbSoftPointerId* pId)
{
	long  temp;
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%ld",&temp))==1)){
		pId->setFromOldId(temp);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;

    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readDouble(double *pVal)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf",pVal))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readPoint2d(AcGePoint2d *pVal)
{
	int   count;
	double x,y;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf %lf",&x,&y))==2)){
		pVal->set(x,y);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;
    return mStat ;
}


Acad::ErrorStatus
AsdkDwgFiler::readPoint3d(AcGePoint3d *pVal)
{
	int   count;
	double x,y,z;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf %lf %lf",&x,&y,&z))==3)){
		pVal->set(x,y,z);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;
    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readVector2d(AcGeVector2d *pVal)
{
	int   count;
	double x,y;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf %lf",&x,&y))==2)){
		pVal->set(x,y);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readVector3d(AcGeVector3d *pVal)
{
	int   count;
	double x,y,z;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf %lf %lf",&x,&y,&z))==3)){
		pVal->set(x,y,z);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;
    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readScale3d(AcGeScale3d *pVal)
{
	int   count;
	double x,y,z;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%lf %lf %lf",&x,&y,&z))==3)){
		pVal->set(x,y,z);
		mStat = Acad::eOk;
	}
	else
		mStat = Acad::eFilerError;
    return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readClassHeader(int *classId)
{
	int   count;
	if (mStat != Acad::eOk)
		return mStat;
    if ((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%d",classId))==1))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

 return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::readClassEnd()
{
	int   count;
	char  endStr[256];	
 
    if (((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%s",endStr))==1)
			&& (_stricmp(endStr, "end;")==0)))
		return mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

////
    if (((fgets(mBuffer, 512,fp)!= NULL)
		&&((count = sscanf(mBuffer,"%s",endStr))==1)
			&& (_stricmp(endStr, "end;")==0)))
		mStat = Acad::eOk;
	else
		mStat = Acad::eFilerError;

 return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::readEndOfEntity()
{
	int   count;
	char  endStr[5120];
	Acad::ErrorStatus  es=Acad::eOk;
	Adesk::Boolean  found = FALSE;

 while (found ==FALSE){
	if ((fgets(mBuffer,5120,fp)!= NULL)
		&& ((count = sscanf(mBuffer, "%s", endStr) ==1)
		&& (_stricmp(endStr, "end;")==0))){
		found = TRUE;
	}
 }

 return Acad::eOk;
}



// _____________________  Data Writting  _____________________


Acad::ErrorStatus
AsdkDwgFiler::writeBytes(const void *buf, Adesk::UInt32 cnt)
{
	// no implementation
	return mStat = Acad::eFilerError;    
}

Acad::ErrorStatus
AsdkDwgFiler::writeAddress(const void* p)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%lu\n", (Adesk::UInt32)p) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
	return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeChar(char val)
{  
   	if ((mStat == Acad::eOk) 
   		&&(fwrite(&val, sizeof(char),1,fp)==1)
   		&&(fprintf(fp,"\n") >0))
	     mStat = Acad::eOk;
	else
	     mStat = Acad::eFilerError;

	return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::writeString(const char *pVal)
{
	size_t len = strlen(pVal)+1;
   	if ((mStat == Acad::eOk)
		&& (fwrite(&len, sizeof( size_t),1,fp)==1)
		&& (fwrite(pVal, sizeof(char),len,fp)==len)
		&& (fprintf(fp, "\n")>0))
	     mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat ;
}



Acad::ErrorStatus
AsdkDwgFiler::writeBChunk(const ads_binary &val)
{
	size_t  len = strlen(val.buf)+1;
    ads_printf("writeBChunk\n");
    if ((mStat == Acad::eOk) 
		&& (fwrite(&len, sizeof(size_t),1,fp)==1)
    	&& (fwrite(&val.clen, sizeof(short), 1, fp)==1) 
		&& (fwrite(val.buf, sizeof(char), len, fp)==len)
		&& (fprintf(fp,"\n") >=0))
		mStat = Acad::eOk;
	else
	   mStat = Acad::eFilerError;
	return mStat;
  }


Acad::ErrorStatus
AsdkDwgFiler::writeAcDbHandle(const AcDbHandle& val)
{
	// no implementation
    ads_printf("writeAcDbHandle\n");
    return Acad::eFilerError;
}

Acad::ErrorStatus
AsdkDwgFiler::writeInt32(Adesk::Int32 val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%ld\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::writeInt16(Adesk::Int16 val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%d\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;
}


Acad::ErrorStatus
AsdkDwgFiler::writeUInt32(Adesk::UInt32 val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%lu\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;

}

Acad::ErrorStatus
AsdkDwgFiler::writeUInt16(Adesk::UInt16 val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%hu\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;

}

Acad::ErrorStatus
AsdkDwgFiler::writeUInt8(Adesk::UInt8 val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%c\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeBoolean(Adesk::Boolean val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%d\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeHardOwnershipId(const AcDbHardOwnershipId& id)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%ld\n", id.asOldId()) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeSoftOwnershipId(const AcDbSoftOwnershipId& id)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%ld\n", id.asOldId()) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeHardPointerId(const AcDbHardPointerId& id)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%ld\n", id.asOldId()) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeSoftPointerId(const AcDbSoftPointerId& id)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%ld\n", id.asOldId()) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeDouble(double val)
{
    if (( mStat == Acad::eOk)
		&& (fprintf(fp, "%lf\n", val) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writePoint2d(const AcGePoint2d& val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%f %f\n", val.x, val.y) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writePoint3d(const AcGePoint3d& val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%f %f %f\n", val.x, val.y, val.z) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
  
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeVector2d(const AcGeVector2d& val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%f %f\n", val.x, val.y) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeVector3d(const AcGeVector3d& val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%f %f %f\n", val.x, val.y, val.z) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeScale3d(const AcGeScale3d& val)
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%f %f %f\n", val.sx, val.sy, val.sz) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeClassHeader()
{
    if (( mStat == Acad::eOk)
	&& (fprintf(fp, "%d\n", mEntType) >0))
	   mStat = Acad::eOk;
	else 
	   mStat = Acad::eFilerError;
    return mStat;
}

Acad::ErrorStatus
AsdkDwgFiler::writeClassEnd()
{
  if (fprintf(fp, "end;\n")>0)
  	  return Acad::eOk;
  else
      return Acad::eFilerError;
}


long 
AsdkDwgFiler::tell() const
{
   return ftell(fp);
}

Acad::ErrorStatus
AsdkDwgFiler::seek(long pos, int mode)
{
    ads_printf("Seek does nothing\n");
    return mStat;
}



Acad::ErrorStatus AsdkDwgFiler::filerStatus(void) const
{
    return mStat;
}

AcDb::FilerType AsdkDwgFiler::filerType(void) const
{
     return AcDb::kCopyFiler;
}

void AsdkDwgFiler::setFilerStatus(Acad::ErrorStatus status)
{
    mStat = status;
}

void AsdkDwgFiler::resetFilerStatus(void)
{
    setFilerStatus(Acad::eOk);
}
