// (C) Copyright 2003-2007 by Autodesk, Inc. 
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

#include "dbtable.h"
#include "dbTablestyle.h"
#include "acgiutil.h"
#include "DbTableTemplate.h"

#define NEWTBLSTYLE _T("<New Table Style>")

// Vector classes to hold the table data
typedef AcArray <TCHAR *> FieldData;
typedef AcArray <FieldData *> RowData;

typedef std::map <TCHAR *,TCHAR *> HdrRwMap;
typedef std::pair <TCHAR *,TCHAR *> Char_Pair;

void deleteFieldData(FieldData *pFldData);
void deleteRowData(RowData *pRwData);
void deleteHdrRwMap(HdrRwMap *pHdrRw);

// To Print error messages
#define PRTMSGRETES(es) if (Acad::eOk != es){acutPrintf(_T("\n%s."),acadErrorStatusText(es));return es;}
#define PRTMSGRET(msg) {acutPrintf(_T("\n%s."),msg);return;}

// Main function to create a new table for a block definition
void buildTableFromBlock(const TCHAR *pBlkName, const TCHAR *pStyleName, bool bLink);

// Update existing table
void updateExistingTable(const TCHAR *pBlkName, const TCHAR *pStyleName, bool bLink);

// Adds new Table style
Acad::ErrorStatus addTableStyle(const TCHAR *pStyleName);

// Create table for the Block's BOM
Acad::ErrorStatus generateTableFromBlock(const TCHAR *pBlkName, RowData *&pRwData, bool bLink);

// Get the attribute object given the TAG value
TCHAR *getAttTextByTag(const TCHAR*pAttTag,AcDbObjectIterator *&pAttItr);

// Create an empty table
Acad::ErrorStatus createTable(AcDbTable *&pTbl, const TCHAR *pTblStyle, 
							  const int nColLen, const int nRowLen);
// Update existing table
Acad::ErrorStatus updateTable(AcDbTable *&pTbl, const TCHAR *pTblStyle, 
							  const int nColLen, const int nRowLen);
							  							  
// Set the number of columns and rows
Acad::ErrorStatus setTableColAndRows(AcDbTable *&pTbl, int nColLen, int nRowLen);
							  							  
// Create the table with the data provided
void populateTable(AcDbTable *&pTbl, const RowData *pRwData);

// add entity to the database
Acad::ErrorStatus addEntToDwg(AcDbDatabase *pDb, AcDbEntity *pEnt );

// Select entity on the screen
AcDbEntity* selectEntity(const TCHAR *pPrompt);

// Merge cells for Title and Header for sample table
Acad::ErrorStatus mergeCellsForTitleAndHeader(AcDbTable *&pTbl, const TCHAR *pBlkName);

// Set fit column with text width
Acad::ErrorStatus fitColumnWidth(AcDbTable *&pTbl,double maxWidth);

// Set fit row height with text height
Acad::ErrorStatus fitRowHeight(AcDbTable *&pTbl,double maxHeight);


//////////////////////////////////////////////////////////////////////////
//	Table Enhancements
//////////////////////////////////////////////////////////////////////////

// Create a data link and embed it into a table.
void createAndSetDataLink();

// Break a table.
void breakTable();

// Create a table template from a table, and create a table style to hold the template.
void createTemplate();

// Create multiple contents in a single cell.
void createMultipleContent();

// Restore a broken table.
void restoreTable();

