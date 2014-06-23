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

#ifndef __PACKCORE_H
#define __PACKCORE_H


// the following to undefine the DEBUG_DELETE business from dbmain.h
#define DEBUG_DELETE delete

int getDrawingVersion(char *path, char *version);

int getDependencyNames(int countorupdate);
void updateFile(char *fname, int ftype);
int addFile(char *path,int ftype);
int updateSubstTable(int countorupdate);
void getSubstPath(char *fname);
int findFontfile(char *path,char *path_buffer);
int makeDir(char *path);
int makeDirs(char *path);
void sysError(int mderr);
int checkDiskspace(char *path);
void doReport(char *path);

void doScript(char *path,char *filebasepath,int iwhat);


void getRenderDependencies();

char *getTimedate(char *path);

char *trimString(char *string);
char *leftTrim(char *string);

int fileexists(char *fnm);


// let us create a struct to hold the number of
// dependencies of each type.  This will help
// us create a report.
typedef struct
{
	short nxref;
	short nimage;
	short nshx;
	short npfb;
	short nttf;
	short ismissing;
	// the isfmp and isalt variable store the 
	// index for file name in the pFile array.
	short isfmp;
	short isalt;
}
DependencyStatus;



typedef struct
{
	char fname[_MAX_PATH];
	CTime mtime;	//The date and time the file was last modified.
	LONG size;	//The logical size of the file in bytes, as reported by the DIR command.

	unsigned char  ftype;
	unsigned char  found;
	char dwgVersion[16];  // store the drawing version number

	char szPath[_MAX_PATH];
}
depend_type;


typedef struct
{
	char fname[_MAX_PATH];  // original filename
	char sname[_MAX_PATH];  // substituted filename

}
subst_type;



// globals follow...

extern DependencyStatus status; // struct to hold status info
extern depend_type *pFile; // struct to hold file info
extern int nFile;  // counter for number of files
extern subst_type *pSubst;
extern int nSubst;
extern DWORD totalsize;  // saves size of all files
extern int overwrite; // variable to control if overwriting is allowed
extern char copypath[_MAX_PATH]; // path where files will be copied to.


#endif // __PACKCORE_H
