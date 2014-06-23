// (C) Copyright 1997 by Autodesk, Inc. 
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
#include "PackDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" HWND adsw_acadMainWnd();

#include <imgdef.h>
#include <imgent.h>
#include <imgentim.h>
#include <imgdefim.h>
#include <dbmain.h>

#include <imgvars.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aced.h>
#include <dbents.h>
#include <dbelipse.h>
#include <dbsymtb.h>
#include <adslib.h>
#include "actrans.h"
#include "adeskabb.h"
#include "acgi.h"
#include "math.h"
#include <time.h>
#include <xgraph.h>

#include "winnt.h"
#include "time.h"

#include "direct.h"
#include "io.h"
#include "fcntl.h"
#include "errno.h"
#include <direct.h>


#include "packutil.h"
#include "packcore.h"


int
getDependencyNames(int countorupdate)
{

	int filecount = 0;

	nFile = 0;
	struct resbuf rb;

	// check if fontalt exists. if it does add to list.
	ads_getvar(/*MSG0*/"FONTALT",&rb);
	if(strlen(rb.resval.rstring))
	{
		if(countorupdate)
			{
			updateFile(rb.resval.rstring,3);
			status.isalt = nFile-1;	
			}
		else
			filecount++;
	}
	
	// check if fontmap file is specified and add to list

	ads_getvar(/*MSG0*/"FONTMAP",&rb);

	if(strlen(rb.resval.rstring))
	{
		if(countorupdate)
			{
			updateFile(rb.resval.rstring,16);
			}
		else
			filecount++;
	}

	// update current file and make sure that it gets appended.

	ads_getvar(/*MSG0*/"DWGNAME",&rb);
	if(strlen(rb.resval.rstring))
	{
		if(countorupdate)
			{
			updateFile(rb.resval.rstring,0);
			}
		else
			filecount++;
	}



	// start with text fonts.
	// the good part is that the text style table gets populated
	// with everyting in the xrefs (fair assumtion?)
	AcDbTextStyleTable *pTxtStlTbl;

	acdbCurDwg()->getTextStyleTable(pTxtStlTbl, AcDb::kForRead);

	AcDbTextStyleTableIterator *pTxtStlIterator;
	pTxtStlTbl->newIterator(pTxtStlIterator);

	AcDbTextStyleTableRecord  *pTxtStlTblRcd;
	char *pFontName;
	char *pStyleName;
	char *pBigFontName;

	for(; !pTxtStlIterator->done(); pTxtStlIterator->step())
	{
		pTxtStlIterator->getRecord(pTxtStlTblRcd, AcDb::kForRead);

		if(pTxtStlTblRcd->fileName(pFontName) == Acad::eOk)
		{
			if(countorupdate)
				updateFile(pFontName, 3);
			filecount++;
		}

		//Acad::ErrorStatus  esbf = pTxtStlTblRcd->bigFontFileName(pBigFontName);

		if(pTxtStlTblRcd->bigFontFileName(pBigFontName) == Acad::eOk)
		{
			if(pBigFontName)
			{
				if(countorupdate)
					updateFile(pBigFontName,3);
				filecount++;
			}

		}

		pTxtStlTblRcd->getName(pStyleName);

		pTxtStlTblRcd->close();

			free(pFontName);
		free(pStyleName);
	}

	delete pTxtStlIterator;
	pTxtStlTbl->close();

	// let us now get images in the current drawing
	 
	AcDbObjectId        ImagedictId;
    AcDbDictionary*     pRasDict = 0;
    int                 nCount = 0;
	AcDbDatabase* pDb = acdbCurDwg();

	ImagedictId = AcDbRasterImageDef::imageDictionary(pDb);

    if (ImagedictId.asOldId() != 0)
	{
        if (acdbOpenObject((AcDbObject*&)pRasDict, ImagedictId, AcDb::kForRead) != Acad::eOk)
		{
            return filecount;
		}
	}

    if (pRasDict) 
	{

		nCount = pRasDict->numEntries();

		AcDbDictionaryIterator* pDictIter = pRasDict->newIterator();

		AcDbRasterImageDef *pRasDef;
		for(; !pDictIter->done(); pDictIter->next())
		{
			Acad::ErrorStatus es = pDictIter->getObject((AcDbObject*&)pRasDef,AcDb::kForRead);
			filecount++;

			CFileStatus fileStatus;
			Acad::ErrorStatus errorStatus = pRasDef->getFileStatus(fileStatus);

			if(errorStatus == Acad::eKeyNotFound)
			{
				if(countorupdate && (es == Acad::eOk))
				{
					updateFile((char*)pRasDef->sourceFileName(),-2);
				}
			}
			else
				{
					// here is a funny problem
					// i am in a state where pRasDef = 0;
					// assume that es got set to a correct value
					if(countorupdate && (es== Acad::eOk))
						updateFile((char *)pRasDef->activeFileName(), 2);
				}

		}
		delete pDictIter;

		pRasDict->close();
	}



// Xref Stuff....
// Traverse the XrefGraph and for every node get
// the Xref drawing information and then 
// look for all images in the xref.


	AcDbXrefGraph	XrefGraph;

	getCurDwgXrefGraph(XrefGraph,Adesk::kFalse);

	if(XrefGraph.numNodes() > 1)
	{
		for(int i=1; i < XrefGraph.numNodes(); i++)
		{
			AcDbXrefGraphNode *pXrefGraphNode;
			pXrefGraphNode = XrefGraph.xrefNode(i);

			AcDbBlockTableRecord *pBlkTblRcd;

			AcDbObjectId id = pXrefGraphNode->btrId();

			acdbOpenObject((AcDbObject*&)pBlkTblRcd, pXrefGraphNode->btrId(), AcDb::kForRead);
			if(pBlkTblRcd)
			{
				char *XrefPath;
				pBlkTblRcd->pathName(XrefPath);

				if(countorupdate)
					updateFile(XrefPath, 1);

				filecount++;
				AcDbDatabase *pXrefDb = pBlkTblRcd->xrefDatabase();
				if(pXrefDb)
				{
					ImagedictId = AcDbRasterImageDef::imageDictionary(pXrefDb);
					if (ImagedictId.asOldId() != 0)
					{
						pRasDict = NULL;
						if (acdbOpenObject((AcDbObject*&)pRasDict, ImagedictId, AcDb::kForRead) != Acad::eOk)
						{
							CString cstr;

							cstr.LoadString(IDS_ERR_RAS_DICT);
							ads_alert((LPCTSTR)cstr);
							continue;
						}

						if (pRasDict) 
						{
							AcDbDictionaryIterator* pDictIter = pRasDict->newIterator();
							AcDbRasterImageDef *pRasDef;
							for(; !pDictIter->done(); pDictIter->next())
							{
								Acad::ErrorStatus es = pDictIter->getObject((AcDbObject*&)pRasDef,AcDb::kForRead);
								filecount++;


									CFileStatus fileStatus;
									Acad::ErrorStatus errorStatus = pRasDef->getFileStatus(fileStatus);

									if(errorStatus == Acad::eKeyNotFound)
									{
										if(countorupdate && (es == Acad::eOk))
										{
											updateFile((char*)pRasDef->sourceFileName(),-2);
										}
									}
									else
									{
										if(countorupdate && (es== Acad::eOk))
											updateFile((char *)pRasDef->activeFileName(), 2);
									}
		
							}
							delete pDictIter;
	
							pRasDict->close();
						}

					}

				}
			pBlkTblRcd->close();
			}
		}
	}
return filecount;
}





void updateFile( char *filename, int ftype)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char path[_MAX_PATH];

	char  currentpath[_MAX_PATH];

	int fonttype = 0;



	CString cstr;


// replace all / in path with \ as ads_findfile will fail.

	for(int k=0; k<strlen(filename); k++)
	{
		if(filename[k] == '/')
			filename[k] = '\\';
	}

	 _getcwd( currentpath, _MAX_PATH );

	switch (ftype)
	{
	case 0 :
	case 1 : //xref
		strcpy(path_buffer,filename);
		_splitpath( path_buffer, drive, dir, fname, ext );

		if(!strlen(ext))
			strcat(path_buffer,/*MSG0*/".dwg");

		if(!strlen(drive) && ftype == 1)
		{
			if(dir[0] != '\\')
			{
				strcpy(path_buffer,currentpath);
				if(path_buffer[strlen(path_buffer)-1] != '\\')
					strcat(path_buffer,"\\");
				strcat(path_buffer,filename);
				if(!strlen(ext))
					strcat(path_buffer,/*MSG0*/".dwg");

				if(ads_findfile(path_buffer,path) == RTNORM)
				{
					addFile(path,ftype);
					if(ftype)
						status.nxref++;
					return;
				}

				
			}
		}

		strcpy(path_buffer,filename);
		_splitpath( path_buffer, drive, dir, fname, ext );

		if(!strlen(ext))
			strcat(path_buffer,/*MSG0*/".dwg");

		if(fileexists(path_buffer))
		{
			if(!strlen(drive) || !strlen(dir))
			{
				if(ads_findfile(path_buffer,path) != RTNORM)
				{
					strcpy(path_buffer,fname);
					strcat(path_buffer,/*MSG0*/".dwg");
					ads_findfile(path_buffer,path);
				}
			}
			else
			{
				strcpy(path,path_buffer);
			}
			addFile(path,ftype);
			if(ftype)
				status.nxref++;
			return;
		}

		if(ads_findfile(path_buffer,path) == RTNORM)
		{
			addFile(path,ftype);
			if(ftype)
				status.nxref++;
			return;
		}
		strcpy(path_buffer,fname);
		strcat(path_buffer,/*MSG0*/".dwg");
		if(ads_findfile(path_buffer,path) == RTNORM)
		{
			addFile(path,ftype);
			if(ftype)
				status.nxref++;
			return;
		}
		else
		{
			addFile(path_buffer,-1*ftype);

			cstr.LoadString(IDS_CANT_LOCATE);
			
			ads_printf((char*)(LPCTSTR)cstr,path_buffer);
		}
		return;
	case 2 : // image
	case -2 :
		addFile(filename,ftype);
		status.nimage++;
		break;
	case 3 : // fonts
		// find the path where truetype fonts will live
		// depending on the operating system

		// now that we have created our substitution table,
		// let us process fonts in this order...
		// shx, pfb, ttf
		// this order will be followed if an extention is not
		// provided with the font.


		strcpy(path_buffer,filename);
		_splitpath( path_buffer, drive, dir, fname, ext );
		if(!strlen(ext))
		{
			strcpy(path,fname);
			strcat(path,/*MSG0*/".shx");
			getSubstPath(path);
			fonttype = 0;

			if((fonttype = findFontfile(path,path_buffer)) == 0)
			{
				strcpy(path,fname);
				strcat(path,/*MSG0*/".pfb");
				getSubstPath(path);
				if((fonttype = findFontfile(path,path_buffer)) == 0)
				{
					strcpy(path,fname);
					strcat(path,/*MSG0*/".ttf");
					getSubstPath(path);
					fonttype = findFontfile(path,path_buffer);
				}

			}
		}
		else
		{
			strcpy(path,fname);
			strcat(path,ext);
			getSubstPath(path);
			fonttype = findFontfile(path,path_buffer);
		}

		if(!fonttype)
		{
			addFile(strcat(fname,/*MSG0*/".(shx,pfb,ttf)"), -1*(ftype+fonttype));
			ads_printf((char*)(LPCTSTR)cstr,fname);
			return;
		}
		else
		{
			addFile(path_buffer,ftype+fonttype);
			switch (fonttype)
			{
			case 1 :
				status.nshx++;
				break;
			case 2 :
				status.npfb++;
				break;
			case 3 :
				status.nttf++;
				break;
			default :
				break;
			}
		}

		break;

	case 16 :
		strcpy(path_buffer,filename);
		if(!fileexists(path_buffer))
		{
			if(ads_findfile(path_buffer,path) == RTNORM)
			{
				addFile(path,ftype);
				status.isfmp = nFile-1;	
			}
			else
				addFile(path_buffer,-1*ftype);
		}
		else
		{
			addFile(path_buffer,ftype);
			status.isfmp = nFile-1;	
		}
		break;
	default :
		return;
	}

}


int findFontfile(char *path,char *path_buffer)
{
	char pathbuffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	int fonttype = 0;

	strcpy(pathbuffer,path);
	_splitpath( pathbuffer, drive, dir, fname, ext );

	if(!stricmp(ext,".ttf"))
	{

		// font location is os version dependent...

        OSVERSIONINFO   osvers;          // all about Windows

        osvers.dwOSVersionInfoSize = sizeof(osvers);
		GetVersionEx(&osvers); 

		switch(osvers.dwMajorVersion)
		{
		case 4 :
			GetWindowsDirectory(pathbuffer, _MAX_PATH);
			strcat(pathbuffer,/*MSG0*/"\\FONTS\\");
			break;
		case 3 :
			GetWindowsDirectory(pathbuffer, _MAX_PATH);
			strcat(pathbuffer,/*MSG0*/"\\SYSTEM\\");
			break;
		default :
			break;
		}

		strcat(pathbuffer,fname);
		strcat(pathbuffer,ext);

		if(ads_findfile(pathbuffer,path_buffer) != RTNORM)
		{
			// add code to create /lookup table and find font file.....
		    // procedure should be as follows.
			// create lookup table of full name and font file
			// get fontname from lookup
			// go back and get path by querying the registry.
			// in this case. The font is not found in the system
			// designated directory.  Hence a valid path should always
			// be returned.
		}
		fonttype = 3;

	}
	else
	{
		strcpy(pathbuffer,fname);
		strcat(pathbuffer,ext);
		ads_findfile(pathbuffer,path_buffer);
		if(!stricmp(ext,/*MSG0*/".shx"))
			fonttype = 1;
		if(!stricmp(ext,/*MSG0*/".pfb"))
			fonttype = 2;

	}

	if(!strlen(path_buffer))
	{
		return 0;
	}
	return fonttype;
}





int addFile(char *path,int ftype)
{
	int mismatch = 1;	

	// do not append file if file name is null or blank

	if(!strlen(trimString(path)))
		return nFile;

	CFileStatus fstatus;

	int found = 1;
	if(ftype < 0)
	{
		status.ismissing = 1;
		found = 0;
		ftype *= -1;
	}

/////////////////////////////////////////////////////////////////////////////////////////////////
// adding code here to pick all drive and path informaiton and setting it to the file info.
// 	CString csPath holds the path for the file and CString csDrive holds the drive or UNC path
/////////////////////////////////////////////////////////////////////////////////////////////////

	char *tokn;
	char tpath[_MAX_PATH];

	char *savpath;

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	CString cstr;

	CString csPath, csDrive;

	char dpath[_MAX_DRIVE];

	memset(dpath,0,_MAX_DRIVE);

	savpath = strdup(path);
    _splitpath( savpath, drive, dir, fname, ext );


	int isunc=0;

	if((savpath[0] == /*MSG0*/'\\') && (savpath[1] ==/*MSG0*/'\\'))
	{
		strcpy(tpath,/*MSG0*/"\\\\");
		savpath[0] = savpath[1] = ' ';
		leftTrim(savpath);
		tokn = strtok(savpath,/*MSG0*/"\\/");
		if((tokn != NULL) && (strlen(trimString(tokn))))
			strcat(tpath,tokn);
		else
		{
			ads_alert("\nbad UNC path...");
			return 0;
		}

		while((tokn != NULL) && (!isunc))
		{
			tokn = strtok(NULL,/*MSG0*/"\\/");
			if ((tokn !=NULL) || (isunc))
			{
				if(strlen(trimString(tokn)))
				{
					strcat(tpath,/*MSG0*/"\\");
					strcat(tpath,tokn);
					if(chdir (tpath) == 0)
					{
						isunc = 1;
					}

					if(isunc)
					{

						if(!strlen(dpath))
							strcpy(dpath,tpath);
						else
						{
							strcat(dpath,"\\");
							strcat(dpath,tpath);
						}
							

					}
				}
			}
		}

		if(!isunc)
		{
			cstr.LoadString(IDS_BAD_UNC);
			sprintf(savpath,(char*)(LPCTSTR)cstr,tpath);
			ads_alert(savpath);
			return 0;
				
		}

		dpath[0] = dpath[1] = ' ';
		leftTrim(dpath);
		csPath = "UNC_";
		csPath += dpath;

		char delpath[_MAX_PATH];

		strcpy(delpath,(LPCTSTR) csPath);

		if(delpath[strlen(delpath)-1] != /*MSG0*/'\\')
			strcat(delpath,/*MSG0*/"\\");

		csPath = delpath;
	}


	if(savpath[0] == /*MSG0*/'\\') // relative path being used
	{
		int curdrive;
   
		/* Save current drive. */
		curdrive = _getdrive();
		sprintf(tpath,/*MSG0*/"%c:\\",curdrive + 'A' -1);
		// get the path and do the split thing so we will not have to bother with the
		// code that follows.
		strcat(tpath,savpath);
	    _splitpath( tpath, drive, dir, fname, ext );

		csPath = "DRIVE_";
		drive[1] = ' ';
		trimString(drive);
		csPath += drive;
		csPath += dir;
	}

	if(strlen(drive))
	{

		csPath = "DRIVE_";
		drive[1] = ' ';
		trimString(drive);
		csPath += drive;
		csPath += dir;
	}


/////////////////////////////////////////////////////////////////////////////////////////////////


	if(!nFile)
	{

		CFile::GetStatus( (LPCTSTR) path,fstatus );
		strcpy(pFile[0].fname,path);
		pFile[0].ftype = ftype;
		pFile[0].found = found;
		pFile[0].mtime = fstatus.m_mtime;
		pFile[0].size  = fstatus.m_size;
		strcpy(pFile[0].szPath,(LPCTSTR)csPath);
		nFile++;
		int fh;
		fh = _open( path, _O_RDONLY );
		totalsize += _lseek( fh, 0L, SEEK_END );
		_close( fh );
	}
	else
	{
		for(int i=0; i<nFile; i++)
		{
			if(!stricmp(path, pFile[i].fname) && (pFile[i].ftype == ftype))
				mismatch = 0;
		}
		if(mismatch)
		{
			CFile::GetStatus( (LPCTSTR) path,fstatus );
			strcpy(pFile[nFile].fname,path);
			pFile[nFile].ftype = ftype;

			if((pFile[nFile].ftype == 1) || (pFile[nFile].ftype == 0))
			{
				getDrawingVersion(pFile[nFile].fname, pFile[nFile].dwgVersion);
			}

			pFile[nFile].found = found;
			pFile[nFile].mtime = fstatus.m_mtime;
			pFile[nFile].size  = fstatus.m_size;
			strcpy(pFile[nFile].szPath,(LPCTSTR)csPath);


			nFile++;
 
			int fh;
			fh = _open( path, _O_RDONLY );
			totalsize += _lseek( fh, 0L, SEEK_END );
			_close( fh );

		}
	}	

	


	return nFile;
}



void getSubstPath(char *fname)
{
	for(int i=0; i<nSubst; i++)
	{
		if(!stricmp(pSubst[i].fname,fname))
		{
			strcpy(fname,pSubst[i].sname);
			return;
		}
	}

}

int updateSubstTable(int countorupdate)
{
	FILE *fp;

	CString cstr;

	struct resbuf rb;
	ads_getvar(/*MSG0*/"FONTMAP",&rb);

	char buffer[256];
	char path[_MAX_PATH];
	int count = 0;
	// nSubst is initialized here (again) 
	// this will take care of cases when 
	// the send dialog is invoked many times.
	nSubst = 0;

	if(strlen(rb.resval.rstring))
	{
		if(ads_findfile(rb.resval.rstring,path) != RTNORM)
			return 0;
	}
	else
		return 0;
		
	if((fp=fopen(path,"rt")) == NULL)
	{
		cstr.LoadString(IDS_ERROR_OPENING);
		sprintf(buffer,(char*)(LPCTSTR)cstr,path);
		ads_alert(buffer);
		return 0;
	}
	
	while(!feof(fp))
	{
		memset(buffer,256,0);
		fgets(buffer,256,fp);
		if(strlen(trimString(buffer)))
		{
			if(countorupdate)
			{
				char* tokn = NULL;
				char* tokn1 = NULL;
				tokn = strtok(buffer,/*MSG0*/";");
				tokn1 = strtok(NULL,/*MSG0*/" ");
				if((tokn != NULL) && tokn1 != NULL)
				{
					strcpy(pSubst[nSubst].fname,tokn);
					strcpy(pSubst[nSubst].sname,tokn1);
					nSubst++;
					count++;
				}
			}
			else
				count++;
		}
	}
	fclose(fp);
	return count;
}




int getDrawingVersion(char *path, char *version)
{

	if(!strlen(path) || path == NULL)
	{
		strcpy(version,"Unknown");
		return 0;
	}

	FILE *fv;

	if((fv = fopen(path,"rb")) == NULL)
	{
		strcpy(version,"Unknown");
		return 0;
	}

	char buffer[16];

	fread( buffer, 6, 1, fv );

	buffer[6] = 0;

	if(!strcmp(buffer,"AC1.2"))
		sprintf(version,"Release 1.2");
	else if(!strcmp(buffer,"AC1.40"))
		sprintf(version,"Release 1.4");	
	else if(!strcmp(buffer,"AC1.50"))
		sprintf(version,"Release 1.5");	
	else if(!strcmp(buffer,"AC2.10"))
		sprintf(version,"Release 2.1");	
	else if(!strcmp(buffer,"AC2.20"))
		sprintf(version,"Release 2.2");	
	else if(!strcmp(buffer,"AC2.21"))  
		sprintf(version,"Release 2.21");	
	else if(!strcmp(buffer,"AC2.22"))
		sprintf(version,"Release 2.x");	
	else if(!strcmp(buffer,"AC1001"))
		sprintf(version,"Release 2.x");
	else if(!strcmp(buffer,"AC1002"))
		sprintf(version,"Release 2.5");
	else if(!strcmp(buffer,"AC1003"))
		sprintf(version,"Release 2.6");
	else if(!strcmp(buffer,"AC1004"))
		sprintf(version,"Release 9");
	else if(!strcmp(buffer,"AC1005"))
		sprintf(version,"Release 9.x");
	else if(!strcmp(buffer,"AC1006"))
		sprintf(version,"Release 10");
	else if(!strcmp(buffer,"AC1007"))
		sprintf(version,"Release 11");
	else if(!strcmp(buffer,"AC1008"))
		sprintf(version,"Release 11");
	else if(!strcmp(buffer,"AC1009"))
		sprintf(version,"Release 12");
	else if(!strcmp(buffer,"AC1010"))
		sprintf(version,"Release 13");
	else if(!strcmp(buffer,"AC1011"))
		sprintf(version,"Release 13");
	else if(!strcmp(buffer,"AC1012"))
		sprintf(version,"Release 13");
	else if(!strcmp(buffer,"AC1013"))
		sprintf(version,"Release 14");
	else
		sprintf(version,"Unknown");
	
	fclose(fv);

	return 0;

}


void getRenderDependencies()
{
//TBC
}


