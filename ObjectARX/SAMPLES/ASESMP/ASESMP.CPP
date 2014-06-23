#ifndef _ASESMP_CPP
#define _ASESMP_CPP

// (C) Copyright 1993-1997 by Autodesk, Inc. 
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

/* 
    Name: asesmp.cpp

    Description:
            This file contains the source code 
            demonstrating how to use ASE C++ API

    Notes:

  This sample application has the following command registered:

   Command             What it demonstrates
   -------             --------------------
  ASESMP_DIAG          - Gets access to ASE global diagnostics area,
                       demonstrates how to map ASE global error,
                       how get access to diagnostics parameters and
                       how to clear global diagnostics area by means of
                       CAseAppl::clearAseErr()
  
  ASESMP_CONNECTASE    - Connects ASE to DB3 environment by means of
                       CAseLinkPath::connectAse()
  
  ASESMP_DISCONNECTASE - Disconnects ASE from DB3 environment by means of
                       CAseLinkPath::disconnectAse()
  
  ASESMP_CREATETABLE   - Creates the database table by means of 
                       CAseLinkPath::createTable().
                       The created table path is DB3.ASE.DB3SAMPLE.NEWTBL.
                       The created table structure is the following:
                       
                       EMP_ID      INTEGER  (maps to DECIMAL(11) under DB3)
                       LAST_NAME   CHAR(25)
                       FIRST_NAME  CHAR(15)
                       
                       EMP_ID is considered to be a key column to 
                       address the table rows.
  
  ASESMP_DROPTABLE     - Drops the database table DB3.ASE.DB3SAMPLE.NEWTBL by
                       means of CAseLinkPath::dropTable().
  
  ASESMP_CREATELPN     - Creates the LPN NEWLPN to the database table
                       DB3.ASE.DB3SAMPLE.NEWTBL with EMP_ID as the key column.
                       Gets the table structure by means of
                       CAseLinkPath::getTableDsc().
  
  ASESMP_ADDROW        - Adds row to the database table DB3.ASE.DB3SAMPLE.NEWTBL 
                       by means of CAseLinkPath::addRow().
  
  ASESMP_UPDROW        - Updates the row(s) with the specified key
                       in the database table
                       DB3.ASE.DB3SAMPLE.NEWTBL by means of
                       CAseLinkPath::updRow().
  
  ASESMP_DELROW        - Deletes the row(s) with the specified key from 
                       the database table DB3.ASE.DB3SAMPLE.NEWTBL by 
                       means of CAseLinkPath::delRow().
  
  ASESMP_MAKELINK      - Links the selected entity and row from the
                       database table with the specified key by means 
                       of LPN NEWLPN.
  
  ASESMP_GETROWS       - Prints rows from the database table 
                       linked with the selected entity by 
                       means of NEWLPN.
                       Demonstrates the correspondence
                       [graphics -> extern database]
  
  ASESMP_GETENTS       - Highlights the entities linked by means of LPN
                       NEWLPN with the database table with the rows
                       defined by the specified SQL WHERE condition.
                       Demonstrates the correspondence
                       [extern database -> graphics]

*****************************************************************************/

/***************************************************************************/
/* INCLUDES */
/***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rxdefs.h>
#include <adslib.h>
#include <adesk.h>

#include <asiappl.h>
#include <ase.h>

#include <accmd.h>

/***************************************************************************/
/* DEFINES */
/***************************************************************************/

/***************************************************************************/
/* TYPEDEFS */
/***************************************************************************/
// Definition of commands
typedef struct {
    char *pCmdName;
    AcRxFunctionPtr cmdfunc;
} CMDDEF;

/****************************************************************************/
/* FUNCTION PROTOTYPES */
/****************************************************************************/
// Utility functions
static void          printAseErr(CAseApiObj& pObj);
static EAsiBoolean   editRow(CAsiRow *pRow);
static void          printRow(const CAsiRow *pRow);


// Command processing functions
static void          asesmp_diag();
static void          asesmp_connectAse();
static void          asesmp_disconnectAse();
static void          asesmp_createTable();
static void          asesmp_dropTable();
static void          asesmp_createLpn();
static void          asesmp_addRow();
static void          asesmp_updRow();
static void          asesmp_delRow();
static void          asesmp_makeLink();
static void          asesmp_getRows();
static void          asesmp_getEnts();

/****************************************************************************/
/* LOCAL VARIABLES */
/****************************************************************************/
static CMDDEF cmddef[] = 
{
    {"ASESMP_DIAG",         asesmp_diag},
    {"ASESMP_CONNECTASE",   asesmp_connectAse},
    {"ASESMP_DISCONNECTASE",asesmp_disconnectAse},
    {"ASESMP_CREATETABLE",  asesmp_createTable},
    {"ASESMP_DROPTABLE",    asesmp_dropTable},
    {"ASESMP_CREATELPN",    asesmp_createLpn},
    {"ASESMP_ADDROW",       asesmp_addRow},
    {"ASESMP_UPDROW",       asesmp_updRow},
    {"ASESMP_DELROW",       asesmp_delRow},
    {"ASESMP_MAKELINK",     asesmp_makeLink},
    {"ASESMP_GETROWS",      asesmp_getRows},
    {"ASESMP_GETENTS",      asesmp_getEnts}
};

// ASE Application
static CAseAppl *pAppl=NULL ;		    

/****************************************************************************/
/* UTILITY FUNCTIONS */
/****************************************************************************/

static void
printAseErr(
    CAseApiObj& pObj)
{
    char buf[120] ;	// The error message buffer
    int index ; 	// Error index
    if ( (index=pObj.errQty()) ) {
	    ads_printf("\nERRORs : %d", index) ;
        for ( index=0 ; index < pObj.errQty() ; index++ ) {
			pObj.errMsg(index, buf, 119) ;
			buf[119] = '\0' ;
			ads_printf("\n#%d  Msg: [%s]", index, buf) ;
			ads_printf(" ErrCode: %d, ErrDsc: %d",
				       pObj.errCode(index), pObj.errDsc(index)) ;
        }
    }
}
                                            
static EAsiBoolean
editRow(
    CAsiRow *pRow)
{
    char buf[256] ;    // The buffer for printing values
    int index ;        // The row column scanning index 
    CAsiColumn col;    // The column descrition
    CAsiIdent ident;   // Column name identifier
    CAsiData *pData;   // The column value pointer
              
      // Check the argument
    if ( pRow == NULL ) {
        return kAsiBad;
    }
    for ( index = 0 ; index < pRow->ColNum() ; index++ ) {
          // Get the column description
        col = (*pRow)[index];  
          // Get the column name identifier
        ident = col.Name();
          // Print the column name string
	    ads_printf("\n%s <", ident.Body().getToChar(buf,255));
          // Get the existing column value
        if ( (pData=col.getData()) == NULL ) {
            ads_printf("\nData are not described");
            break;
        }
        if ( pData->isNull() == kAsiGood ) {
            strcpy(buf, ".");
        } else {
            pData->getValue(buf, 255);
        }
          // Print the existing column value
        ads_printf("%s", buf);  
          // Ask for the new value
        if ( ads_getstring(1, "> : ", buf) != RTNORM ) {
            ads_printf("\nNo input") ;
            break ;
        }
          // Check the user input
        if ( buf[0] == NULL ) {
              // No changes
            continue;
        } else if ( buf[0] == '.' ) {
              // Null sign was specified
            col.setDataDsc(NULL);
        } else if ( buf[0] != '\0' ) {
              // Update the value
            if ( pData->storeValue(buf) != kAsiGood ) {
                ads_printf("\nInappropriate value is entered") ;
                break;
            }
        }    
          // Update the column description
        (*pRow)[index] = col;  
    }
      // Check the exit condition
    if ( index < pRow->ColNum() ) {
        return kAsiBad ;
    }
    return kAsiGood ;
}    


/****************************************************************************/
/* COMMANDS */
/****************************************************************************/

static void
printRow(
    const CAsiRow *pRow)
{
    char buf[256] ;    // The buffer for printing values
    int index ;        // The row column scanning index 
    CAsiColumn col;    // The column descrition
    CAsiIdent ident;   // Column name identifier
    CAsiData *pData;   // The column value pointer
              
      // Check the argument
    if ( pRow != NULL ) {
        for ( index = 0 ; index < pRow->ColNum() ; index++ ) {
              // Get the column description
            col = (*pRow)[index];  
              // Get the column name identifier
            ident = col.Name();
              // Print the column name string
		    ads_printf("\n%s : ", ident.Body().getToChar(buf,255));
              // Get the existing column value
            if ( (pData=col.getData()) == NULL ||
                 pData->isNull() == kAsiGood ) {
                strcpy(buf, ".");
            } else {
                pData->getValue(buf, 255);
            }
              // Print the existing column value
            ads_printf("%s", buf);  
        }
    }
}    

static void
asesmp_diag()
{
      // Get ASE global error diagnostics
    pAppl->getAseErr();
      // Print the error data
    printAseErr(*pAppl);
      // Clear ASE global error diagnostics
    pAppl->clearAseErr();  
}

static void
asesmp_connectAse()
{
    CAseLinkPath envPath(pAppl);    // The environment container
    
      // Specify the Environment name
    envPath.setName("DB3", kAseEnvCode);
    
      // Check whether Environment is already connected
    if ( envPath.getStatus() & ASE_DO_CON ) {
        ads_printf("\nASE is already connected to DB3 environment");
        return;
    }
      
      // Do the dialogue connection
    if ( envPath.connectAse() != kAsiGood ) {
        ads_printf("\nConnection failed");
        printAseErr(envPath);
        return;
    }  
    ads_printf("\nConnection to DB3 has just established");
      // Set just connected Env as the current
    envPath.setCurrent();  
}

static void
asesmp_disconnectAse()
{
    CAseLinkPath envPath(pAppl);    // The environment container
    
      // Specify the Environment name
    envPath.setName("DB3", kAseEnvCode);
    
      // Check whether Environment is already disconnected
    if ( !(envPath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nASE is already disconnected from DB3 environment");
        return;
    }
      
      // Do the disconnection
    if ( envPath.disconnectAse() != kAsiGood ) {
        ads_printf("\nDisconnection failed");
        printAseErr(envPath);
        return;
    }  
    ads_printf("\nConnection to DB3 has just terminated");
}

static void
asesmp_createTable()
{
    CAseLinkPath  tablePath(pAppl); // The Table path
    CAsiIdent     colIdent;         // The column name identifier
    CAsiUcStr     colName;          // Unicode container for column name
    
      // Specify the path to the Schema where the table will be created
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check Environment is connected in ASE
    if ( ! (tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( tablePath.getStatus() & ASE_DO_EXIST ) {
        ads_printf("\nTable NEWTBL already exists");
        return;
    }  
    
      // Describe the first column
    CAsiInt  firstData;    // The character data descriptor
    colName = "EMP_ID";  
    colIdent.setBody(colName);  
    CAsiColumn col1 = CAsiColumn(colIdent, firstData);
      
      // Describe the second column
    CAsiChar  secondData(25);    // The character data descriptor
    colName = "LAST_NAME";  
    colIdent.setBody(colName);  
    CAsiColumn col2 = CAsiColumn(colIdent, secondData);
    
      // Describe the third column
    CAsiChar  thirdData(15);    // The character data descriptor
    colName = "FIRST_NAME";  
    colIdent.setBody(colName);  
    CAsiColumn col3 = CAsiColumn(colIdent, thirdData);
    
      // The columns pointers array
    const CAsiColumn *pCols[]={&col1, &col2, &col3};  
    
      // Create the table
    if ( tablePath.createTable(pCols, 3) != kAsiGood ) {
        ads_printf("\nCannot create the table");
        printAseErr(tablePath);
    } else {
        ads_printf("\nTable was created successfully");
          // Set just created table as the current
        tablePath.setCurrent();  
    }
}


static void
asesmp_dropTable()
{
    CAseLinkPath  tablePath(pAppl); // The Table path
    
      // Specify the path to the Schema where the table will be created
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check Environment is connected in ASE
    if ( ! (tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Drop the table
    if ( tablePath.dropTable() != kAsiGood ) {
        ads_printf("\nCannot delete the table");
        printAseErr(tablePath);
    } else {
        ads_printf("\nTable was deleted successfully");
    }
}

static void
asesmp_createLpn()
{
    CAseLinkPath  tablePath(pAppl); // The Table path
    CAsiRow     *pRowDsc=NULL;       // The table description
    CAsiRow      Key(1);             // The key column description
    
      // Check whether LPN already exists
    if ( tablePath.initName("NEWLPN") == kAsiGood ) {
        ads_printf("\nLPN NEWLPN already exists");
        return;
    }
      // Specify the path to the Schema where the table will be created
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check Environment is connected in ASE
    if ( ! (tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Get the table columns description
    tablePath.getTableDsc(&pRowDsc);
      // Consider the first column is the key
    Key[0] = (*pRowDsc)[0];
      // Deallocate the columns description
    delete pRowDsc;      
    
      // Create LPN
    tablePath.setName("NEWLPN");
    if ( tablePath.create(&Key) != kAsiGood ) {
        ads_printf("\nCannot create LPN NEWLPN");
        printAseErr(tablePath);
    } else {
        ads_printf("\nLPN NEWLPN is successfully created");
          // Set just created LPN as the current
        tablePath.setCurrent();  
    }
}

static void
asesmp_addRow()
{
    CAseLinkPath tablePath(pAppl);   // The table path
    CAsiRow     *pRowDsc=NULL;       // The table description
    
      // Specify the path to the table
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check whether ASE is connected to DB3 environment
    if ( !(tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Get the table columns description
    tablePath.getTableDsc(&pRowDsc);
      // Edit the values
    ads_printf("\nEnter new column values");  
    if ( editRow(pRowDsc) == kAsiGood ) {
          // Add row to the table
        if ( tablePath.addRow(pRowDsc) != kAsiGood ) {
            ads_printf("\nCannot add row to the table");
            printAseErr(tablePath);
        } else {
            ads_printf("\nRow is added successfully");
        }
    }
      // Deallocate the columns description
    delete pRowDsc;      
}

static void
asesmp_updRow()
{
    CAseLinkPath tablePath(pAppl);   // The table path
    CAsiRow     *pRowDsc=NULL;       // The table description
    CAsiRow      Key(1);             // The key column description
    long         rowQty;             // The quantity of rows updated
    
      // Specify the path to the table
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check whether ASE is connected to DB3 environment
    if ( !(tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Get the table columns description
    tablePath.getTableDsc(&pRowDsc);
      // Consider the first column is the key
    Key[0] = (*pRowDsc)[0];
      // Specify the key value
    ads_printf("\nEnter key value");  
    if ( editRow(&Key) == kAsiGood ) {
          // Edit the row values
        ads_printf("\nEnter the column values to be updated");  
        if ( editRow(pRowDsc) == kAsiGood ) {
              // Update the row
            if ( tablePath.updRow(&Key, pRowDsc, &rowQty) != kAsiGood ) {
                ads_printf("\nCannot update the table row");
                printAseErr(tablePath);
            } else {
                ads_printf("\n#%ld rows are updated successfully", rowQty);
            }
        }
    }
      // Deallocate the columns description
    delete pRowDsc;      
}

static void
asesmp_delRow()
{
    CAseLinkPath tablePath(pAppl);   // The table path
    CAsiRow     *pRowDsc=NULL;       // The table description
    CAsiRow      Key(1);             // The key column description
    long         rowQty;             // The quantity of rows deleted
    
      // Specify the path to the table
    tablePath.initPath("DB3.ASE.DB3Sample.NEWTBL");  
    
      // Check whether ASE is connected to DB3 environment
    if ( !(tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Get the table columns description
    tablePath.getTableDsc(&pRowDsc);
      // Consider the first column is the key
    Key[0] = (*pRowDsc)[0];
      // Deallocate the columns description
    delete pRowDsc;      
      // Specify the key value
    ads_printf("\nEnter key value");  
    if ( editRow(&Key) == kAsiGood ) {
          // Delete the row
        if ( tablePath.delRow(&Key, &rowQty) != kAsiGood ) {
            ads_printf("\nCannot delete the table row");
            printAseErr(tablePath);
        } else {
            ads_printf("\n#%ld rows are deleted successfully", rowQty);
        }
    }
}

static void
asesmp_makeLink()
{
    CAseLinkPath  tablePath(pAppl);  // The Table path
    CAseLink      link(pAppl);       // The link pointer
    CAsiRow      *pKeyDsc=NULL;      // The LPN description
    ads_name      ename;             // Entity name
    ads_point     pt;                // Point of selection
    
      // Check whether LPN already exists
    if ( tablePath.initName("NEWLPN") != kAsiGood ) {
        ads_printf("\nCreate LPN NEWLPN first");
        return;
    }
      // Get the LPN descrption
    tablePath.getKeyDsc(&pKeyDsc);
     
      // Specify the key values
    if ( editRow(pKeyDsc) == kAsiGood ) {
          // Specify the entity
        if ( ads_entsel("\nSelect object:", ename, pt) == RTNORM ) {
            link.initEnt("NEWLPN", pKeyDsc, ename);
              // Create the link
            if ( link.create() == kAsiGood ) {
                ads_printf("\nLink is successfully created");
            } else {
                ads_printf("\nCannot make link");
                printAseErr(link);
            }
        } else {
            ads_printf("\nNo input") ;
        }    
    }  
      // Deallocate the key
    delete pKeyDsc;
}

static void
asesmp_getRows()
{
    CAseLinkPath  tablePath(pAppl);  // The Table path
    CAseLinkSel   linkSel(pAppl);    // The link selection pointer
    CAsiRow      *pKeyDsc=NULL;      // The LPN description
    CAsiRow      *pRow=NULL;         // The row values
    ads_name      ename;             // Entity name
    ads_point     pt;                // Point of selection
    
      // Check whether LPN already exists
    if ( tablePath.initName("NEWLPN") != kAsiGood ) {
        ads_printf("\nCreate LPN NEWLPN first");
        return;
    }
      // Check Environment is connected in ASE
    if ( ! (tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Check whether the table already exists
    if ( !(tablePath.getStatus() & ASE_DO_EXIST) ) {
        ads_printf("\nTable NEWTBL does not exist");
        return;
    }  
      // Specify the entity
    if ( ads_entsel("\nSelect object:", ename, pt) != RTNORM ) {
        ads_printf("\nNo input") ;
        return;
    }
      // Initialize the link selection
    if ( linkSel.initLpEnt(tablePath, ename) != kAsiGood ) {
          // Check the error condition
        if ( linkSel.errQty() ) {
            ads_printf("\nLink Selection creating problem") ;
            printAseErr(linkSel) ;
        } else {
              // No related links
            ads_printf("\nNo links of NEWLPN for selected entity") ;
        }
        return;
    } 
    
      // Get the LPN descrption
    tablePath.getKeyDsc(&pKeyDsc);
    
      // Get the table description
    tablePath.getTableDsc(&pRow);  
      
    long linksQty=linkSel.getQty();  // Links quantity
    
      // Print the row values
    ads_printf("\nLinks #%ld", linksQty);  
    
      // Print the linked row values
    for ( long index=0 ; index < linksQty ; index++) {
          // Print the separator
        ads_printf("\n****** # %ld", index);
          // Get the link key value
        linkSel.getLinkKey(index, pKeyDsc); 
          // Get row for the given key
        if ( tablePath.getRow(pKeyDsc, pRow) == kAsiGood ) {
            printRow(pRow);  
        } else {
            ads_printf("\nLinked row is not found");
            printAseErr(tablePath);
        }
    }
      // Deallocate the key
    delete pKeyDsc;
      // Deallocate the row values
    delete pRow;
}

static void
asesmp_getEnts()
{
    CAseLinkPath  tablePath(pAppl);  // The Table path
    CAseLinkSel   linkSel(pAppl);    // The link selection pointer
    char          where[256];        // Where condition
    ads_name      ename;             // Entity name
    
      // Check whether LPN already exists
    if ( tablePath.initName("NEWLPN") != kAsiGood ) {
        ads_printf("\nCreate LPN NEWLPN first");
        return;
    }
      // Check whether ASE is connected to DB3 environment
    if ( !(tablePath.getStatus() & ASE_DO_CON) ) {
        ads_printf("\nConnect ASE to DB3 first");
        return;
    }
      // Specify WHERE condition
    if ( ads_getstring(1, "\nWHERE:", where) != RTNORM ) {
        ads_printf("\nNo input");
        return;
    }  
      // Initialize the link selection
    if ( linkSel.initLpCond(tablePath, where) != kAsiGood ) {
          // Check the error condition
        if ( linkSel.errQty() ) {
            ads_printf("\nLink Selection creating problem") ;
            printAseErr(linkSel) ;
        } else {
              // No related links
            ads_printf("\nNo links of NEWLPN for specified condition") ;
        }
        return;
    } 
    
    long linksQty=linkSel.getQty();  // Links quantity
    
      // Scan selection and redraw the linked entities
    for ( long index=0 ; index < linksQty ; index++) {
          // Get the entity name
        linkSel.getLinkEnt(index, ename); 
          // Highlight the entity
        ads_redraw(ename, 3);
    }
    ads_printf("\nLinked entities are highlighted, perform REDRAW to unhighlight them");
}

/****************************************************************************/
/* ARX STARTUP FUNCTIONS */
/****************************************************************************/

static AcRx::AppRetCode
initModule()
{
      // Initialize ASE interface
	if ( (pAppl=new CAseAppl()) == NULL ) {
	    ads_printf("\nNo memory");
	    return AcRx::kRetError;
	}
	if ( pAppl->init() != kAsiGood ) {
	    ads_printf("\nASE is not loaded");
	    return AcRx::kRetError;
	}
      // Load commands
    int ii = sizeof(cmddef) /
            sizeof(CMDDEF);        // Number of commands

    while (ii--) {
        acedRegCmds->addCommand ("ASESMP_COMMANDS", 
                                 cmddef[ii].pCmdName,
                                 cmddef[ii].pCmdName,
                                 ACRX_CMD_MODAL |
                                 ACRX_CMD_USEPICKSET |
                                 ACRX_CMD_REDRAW,
                                 cmddef[ii].cmdfunc);
    }
    return AcRx::kRetOK;
} /* end of initModule() */

void
termModule()
{
	  // Delete ASE application
	delete pAppl;
    pAppl = NULL;
}

AcRx::AppRetCode 
acrxEntryPoint(
    AcRx::AppMsgCode msg, 
    void *pAppid)
{
    switch(msg) {
    case AcRx::kInitAppMsg: 	
          // Initialize the module
	    if ( initModule() != AcRx::kRetOK ) {
            ads_fail("\nCan't initialize the module");
            return AcRx::kRetError;
        }
          // Unlock the application
        acrxDynamicLinker->unlockApplication(pAppid);
        break;
    case AcRx::kLoadDwgMsg: 	
	    break;		  	
    case AcRx::kUnloadDwgMsg:
	    break;		  	
    case AcRx::kInvkSubrMsg:
	    break;		  	
    case AcRx::kSaveMsg: 	
	    break;		  	
    case AcRx::kEndMsg:  	
	    break;		  	
    case AcRx::kQuitMsg:	
	    break;		  	
    case AcRx::kCfgMsg:		
	    break;		  	
    case AcRx::kUnloadAppMsg:
          // Terminate the related resources
        termModule();
	    break;			
    default:
	    break;
    }
    return AcRx::kRetOK;
}


#endif /*_ASESMP_CPP*/
