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
// File Name: cmd.cpp
//
// DESCRIPTION:
//
// This file contains the command interface code for Arx sample app -
// FILER.




#include "dbmain.h"	
#include "dbents.h"
#include "accmd.h"
#include "dbelipse.h"
#include "dbray.h"
#include "dbxline.h"
#include "dbspline.h"
#include "dbfcf.h"
#include "tstfiler.h"
#include "util.h"
#include "adslib.h"



void
writeEntityData()
{

  Acad::ErrorStatus   es ;

  ads_name ename;
  ads_name  ss;

  char  fileName[256];
  if (ads_getstring(FALSE, "Enter the file name: ", fileName) != RTNORM)
  	  return;
  	   
  if (ads_ssget(NULL, NULL, NULL, NULL, ss) != RTNORM)
  		return;
  
  AsdkDwgFiler   *pTestFiler = new AsdkDwgFiler (); 
  if (pTestFiler->setFileName(fileName,0) != Acad::eOk){
  		  delete pTestFiler;
		  return;
  }

  long  i = 0L;

  while (ads_ssname(ss, i, ename) == RTNORM){
 	 AcDbObjectId  objId;
  	 es = acdbGetObjectId (objId, ename) ;   
  	 if (es != Acad::eOk){
          ads_printf("Failed: getAcDbEntity::getObject Id\n");
          return ; 
	 }
  	 AcDbEntity  *pEnt = NULL;
     es = acdbOpenAcDbEntity (pEnt, objId, AcDb::kForRead) ;
 
     if(es != Acad::eOk) {
          ads_printf("Failed: getAcDbEntity::acdbOpenAcDbEntity\n");
          return;
      }
	int  entCode = classNameToEntityType((pEnt->isA())->name());
	pTestFiler->setEntityType(entCode);
	pTestFiler->writeClassHeader();
	es = pEnt->dwgOut(pTestFiler);
	if (es != Acad::eOk){
		 pEnt->close();
	  	 pTestFiler->writeClassEnd();
	 	 ads_printf("Error in writing entity data\n");
	 	 delete pTestFiler;
	 	 return;
	}
	pTestFiler->writeClassEnd();
  	pEnt->close();
  
  i++;
 } // while 
  
  delete pTestFiler;
  return;

}


void
readEntity()
{
  char   fileName[256];
  if (ads_getstring(FALSE,"Enter the file name: ", fileName)!= RTNORM)
    return;
  
  AsdkDwgFiler   *pTestFiler = new AsdkDwgFiler (); 
  if (pTestFiler->setFileName(fileName,1) != Acad::eOk){
  		  delete pTestFiler;
		  return;
  }

  int  count=0;
  Acad::ErrorStatus  es = Acad::eOk;
  AcDbEntity*  pEnt=NULL;

  int  classId;
  while((es = pTestFiler->readClassHeader(&classId)) == Acad::eOk){
 	es = getObject(classId, pEnt);
	if (es == Acad::eOk){
   		es = pEnt->dwgIn(pTestFiler);
		if (es != Acad::eOk){
			  delete pTestFiler;
			  return;
		}
		es = pTestFiler->readClassEnd();
		AcDbObjectId entId;
		es = postToDatabase(pEnt, entId);
		if (es != Acad::eOk){
			  delete pTestFiler;
			  return;
		}
    }
    else {
		count++;
   		pTestFiler->readEndOfEntity();
   }
  } // while

  if (count >0)
  	ads_printf("%d Unknown/Unsupported Entity\n", count);
  delete pTestFiler;
  return;
}


/****************************************************************************/
/* Main Rx Entry Point */
/****************************************************************************/
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr)
{
   switch (msg) {
   case AcRx::kInitAppMsg:
		acrxUnlockApplication(ptr);
        AsdkDwgFiler::rxInit();
        acedRegCmds->addCommand ("TEST_COMMAND",
                                "ASDK_WRITEFILE",
                                "WRITEFILE",
                                ACRX_CMD_MODAL,
                                &writeEntityData);

         acedRegCmds->addCommand ("TEST_COMMAND",
                                "ASDK_READENTITY",
                                "READENTITY",
                                ACRX_CMD_MODAL,
                                &readEntity);

		acrxBuildClassHierarchy();
     break;

   case AcRx::kUnloadAppMsg:
	   deleteAcRxClass(AsdkDwgFiler::desc());
       acedRegCmds->removeGroup("TEST_COMMAND");
   }

   return AcRx::kRetOK;
}
