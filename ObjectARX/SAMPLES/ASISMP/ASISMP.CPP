/*****************************************************************************
   ASISMP.CPP

   Copyright (C) 1994-1997 by Autodesk, Inc.

   Permission to use, copy, modify, and distribute this software in
   object code form for any purpose and without fee is hereby granted,
   provided that the above copyright notice appears in all copies and
   that both that copyright notice and the limited warranty and
   restricted rights notice below appear in all supporting
   documentation.

   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
   UNINTERRUPTED OR ERROR FREE.

   Use, duplication, or disclosure by the U.S. Government is subject to
   restrictions set forth in FAR 52.227-19 (Commercial Computer
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
   (Rights in Technical Data and Computer Software), as applicable.


          DESCRIPTION:
          This ARX application demonstrates usage of the ASI C functions.
          It defines the following Lisp commands:

          C:ASISETUP              Configures the sample program.
          C:ASICONNECT            Connects to an SQL environment
          C:ASIDISCONNECT         Disconnect from an SQL Environment
          C:ASISQLED              Interactive SQL editor
          C:ASISCRIPT             SQL script processor
          C:ASICREATEENV          Creates an SQL Environment
          C:ASIDROPENV            Drops an SQL Environment

          In order to run SQL statement, you have to connect to SQL environment first,
          using ASICONNECT command, and then invoke ASISQLED command.

*****************************************************************************/

/****************************************************************************/
/* INCLUDES */
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rxdefs.h"
#include "adslib.h"
#include "adesk.h"
#include "aced.h"
#include "asiappl.h"




/****************************************************************************/
/* TYPEDEFS */
/****************************************************************************/


static int              loadfuncs();
static int              unloadfunc ();
static int              execfunc ();

extern "C" {
/****************************************************************************/
/*  LOCALLY DEFINED ENTRY POINT INVOKED BY Arx                              */
/****************************************************************************/
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* );
}

/****************************************************************************/
/* Helper functions                                                                                                                     */
/****************************************************************************/

char      * bittoXstr       _((char *, int,  unsigned char *, int));
void        write_string    _((char *));
EAsiBoolean initParams      _((ASIHANDLE, struct hbinds **));
void        readParams      _((ASIHANDLE, struct hbinds *));
void        termParams      _((struct hbinds *));
EAsiBoolean initDst         _((ASIHANDLE, struct hbinds **));
void        nullbody        _((void));
char    **      make_formats    _((ASICURSOR));
void            print_header    _((ASICURSOR, char **));


/* Display section of ASI configuration */
void        display_section _((char *));

/* Prints diagnosts from the SQL disagnostics area */
void            print_diag              _((ASIHANDLE));

/* Process SQL statement */
void        do_statement    _((char *));

/* Process cursor */
void        do_cursor       _((ASISTATEMENT));

/* Process single row select statement*/
void        do_single_select _((ASISTATEMENT));

/* Process other SQL statements (not cursor and single row select statement */
void        do_ordinary     _((ASISTATEMENT));

/* Print column descriptors of cursor */
void        print_coldsc    _((ASIHANDLE));

/* Print input parameters descriptors (bind variable descriptors) */
void        print_pardsc    _((ASIHANDLE));

/* Print all rows of cursor. */
void        print_rowset    _((ASICURSOR));

/* Print each row at one line. Called by print_rowset */
void        print_row       _((ASICURSOR, char **));

/* Scan through cursor. Print row and wait for user command for update, delete, or */
/* navigate */
void        scan_rowset     _((ASICURSOR));

/* Print current row of cursor. Each column on separate line. Called from scan_rowset */
void        print_currow    _((ASICURSOR  csr));

/* Perform positioned update statement. Called from scan_rowset () */
EAsiBoolean do_csr_update   _((ASICURSOR csr));




/* Process C:ASISETUP command */
void        do_settings     _((void));

/* Process C:ASICONNECT command */
void        do_connect      _((void));

/* Process C:ASIDISCONNECT command */
void        do_disconnect   _((void));

/* Process C:ASISQLED command */
void        do_sqled        _((void));

/* Process C:ASISCRIPT command */
void        do_script       _((void));

/* Process C:ASICREATEENV command */
void        create_env      _((void));

/* Process C:ASIDROPENV command */
void        drop_env        _((void));


/**************************************************************************/
/*  TYPEDEFS */
/**************************************************************************/
/* The following structure defines buffers to be bound with input SQL
   statement parameters */
struct hbinds {
        char      buffer [256];  // Host buffer
        short     indp;          // Indicator variable
};

/****************************************************************************/
/* GLOBALS */
/****************************************************************************/


typedef struct {
    char *cmdname;
    void (*cmdfunc)();
} CMDRX;                              /* Typedef for command definition */

/* Command definitions */
static CMDRX cmd[] =  {
                        {"C:ASISETUP",      do_settings},
                        {"C:ASISQLED",      do_sqled},
                        {"C:ASISCRIPT",     do_script},
                        {"C:ASICONNECT",    do_connect},
                        {"C:ASIDISCONNECT", do_disconnect},
                        {"C:ASICREATEENV",  create_env},
                        {"C:ASIDROPENV",    drop_env}
                      };

/* Diagnostics parameters */
struct {
        EAsiDiag dPar;       // Diagnostics parameter
        char     name[32];   // Name
} diag [10] =
{
        { kAsiServerName,         "Server"             },
        { kAsiConnectionName,     "Connection"         },
        { kAsiConstraintCatalog,  "Constraint catalog" },
        { kAsiConstraintSchema,   "Constraint schema"  },
        { kAsiConstraintName,     "Constraint"         },
        { kAsiCatalogName,        "Catalog"            },
        { kAsiSchemaName,         "Schema"             },
        { kAsiTableName,          "Table"              },
        { kAsiColumnName,         "Column"             },
        { kAsiCursorName,         "Cursor"             }
};


static ASIENV           appl                    = 0;          /* Asi application */
static ASISESSION       session                 = 0;          /* Asi session */
static EAsiBoolean      isConnected             = kAsiFalse;  /* Connection is active */

static char                     EnvName  [128];           /* Current environment name */
static char                     UserName [128];           /* Current user name */


/* These parameters can be altered by C:ASISETUP command */
static EAsiBoolean      oldScrFile  = kAsiFalse;     // Old style script file
static EAsiBoolean      askCsrMode  = kAsiFalse;     // Ask for cursor mode
static EAsiBoolean      showDsc     = kAsiFalse;     // Show result descriptor

// Default cursor type
static EAsiCurSns       csrSns      = kAsiSnsUndef; // Sensitivity
static EAsiCurScr       csrScr      = kAsiNonScroll;// Scrollabilty

static EAsiBoolean      showOne     = kAsiFalse;     // Scroll by one row
static EAsiBoolean      stopPage    = kAsiTrue;      // Stop after each page
static EAsiBoolean      pauseAfter  = kAsiFalse;     // Pause after statement execution
static EAsiBoolean      pauseAfterE = kAsiTrue;      // Pause after error
static EAsiBoolean      doAgain     = kAsiFalse;     // Ask for statement reexecution
static EAsiBoolean      echoToFile  = kAsiFalse;     // Echo to file
static char                     FileName[128];               // Echo file namne
static EAsiBoolean      timeMeasure = kAsiFalse;     // Print elapsed time
static FILE      *      efDsc       = 0;             // Echo file handle

// Temporary buffers
static  char      buffer [128];       // Buffer for line input
static  char      buff   [1024];      // another buffer
static  char      stm    [1024];      // SQL statement

// Temporary buffer for build character strings
static  char      bufgen [1024];      // Buffer for convert Unicode string
                                      // to character string



/****************************************************************************/
/* FUNCTIONS */
/****************************************************************************/

/**************************************************************************
  Switch boolean value
**************************************************************************/
EAsiBoolean switch_boolean (EAsiBoolean t)
{
        return (t == kAsiTrue) ? kAsiFalse : kAsiTrue;
}

/***************************************************************************
  This function displays string on the screen and echoes it to the protocol
  file (if selected by C:ASISETUP)
***************************************************************************/
void write_string (char * buffer)
{
        ads_printf (buffer);

        if (echoToFile == kAsiTrue && efDsc != 0) {
                fprintf (efDsc, buffer);
        }
}

/****************************************************************************
  This function converts bit buffer to hexadecimal string
****************************************************************************/
char * bittoXstr (
        char          * buffer,   // Destination buffer
        int             len,      // Length of destination buffer
        unsigned char * bbuffer,  // source bit buffer
        int             blen      // Number of bits in bbuffer
)
{
        int    bytelength = 0;
        char * p = 0;
        int    ii;

        bytelength = blen / 8 + ((blen % 8 > 0) ? 1 : 0);

        for (ii = 0, p = buffer; ii < bytelength && p - buffer < len - 2; ii ++) {
                sprintf (p, "%02X", bbuffer[ii]);
                p +=2;
        }
        return buffer;

}



/***************************************************************************
        This function displays section contents of asi configuration
****************************************************************************/
void display_section (
        char            *       section                 /* Section of interest */
)
{
        char            *       buffer  = 0;    /* Destination buffer */
        char            *       pEntry  = 0;    /* Entry name */
        char                    pValue [128];   /* Entry value */
        ASICONFIG               config;                 /* ASI configuration handle */

        /* Construct ASI configuration. Initialize access to it */
        if (asi_constr_cfg (&config) == kAsiBad) {
                ads_printf ("\nCannot construct ASI configuration file handle");
                return ;
        }

        buffer = (char *) malloc (sizeof (char) * 4096);
        if (buffer == 0) {
                asi_destroy_cfg (&config);
                ads_printf ("\nInsufficient memory for temporary buffer");
                return ;
        }
        /* Display contents */

        /* Get section contents.  */
        if (asi_getcfgstring (config, section, NULL, "", buffer, 4096) > 0) {
                for (pEntry = buffer; * pEntry != '\0'; pEntry += strlen (pEntry) + 1) {
                        asi_getcfgstring (config, section, pEntry, "", pValue, 128);
                        ads_printf ("\n%-16s %s", pEntry, pValue);
                }
        }
        ads_printf ("\n");
        free (buffer);
        asi_destroy_cfg (&config);   /* Destroy configuration handle */
        return;
}

/*************************************************************************
  This function displays the ENVIRONMENTS defined in ASI configuration
**************************************************************************/
void display_env (void)
{
        ads_printf ("\nAvailable environments:\n");
        display_section ("ENVIRONMENTS");
}


/***************************************************************************
  This function prints out diagnostics info from the SQL diagnostics area.
  ASIHANDLE can be either session, statement, or cursor
****************************************************************************/
static void print_diag (
        ASIHANDLE       handle
)
{
        int         iCount;                // Temp variables
        int         ii, jj;                // Indexing variable
        char        buff [128];

        // Print number of conditions in diagnostics area
        if ((iCount = asi_condqty (handle)) > 0) {
                ads_printf("\nNumber of conditions: %d",iCount);

                // Print position where sybtax error was detected
                if (asi_synerrpos (handle) != 0) {
                        ads_printf("\nError position:       %d",asi_synerrpos (handle));
                }

                /* Print all set diagnostics parameters */
                ads_printf("\n#        SQLSTATE    Message");
                for (jj = 0; jj < iCount; jj++ ) {
                        asi_errmsg (handle, buff, 256, jj);
                        ads_printf("\n%10d%-12s%s", jj, asi_sqlstate (handle, jj), buff);

                        // Print diagnostics parameters
                        for (ii = 0; ii < 10; ii ++) {
                                if (asi_getdiagpar (handle, diag[ii].dPar, buff, 256, jj) == kAsiTrue) {
                                        ads_printf ("\n%20s: ", diag[ii].name);
                                        ads_printf ("%s", buff);
                                }
                        }
                }
        }

} // print_diag()

/*******************************************************************************************
  This function prints resulting table descriptor. The descriptor of
  the table is returned for cursor and single row select statment
*******************************************************************************************/
static void print_coldsc (
        ASIHANDLE       handle          /* Cursor or Statement */
)
{
        int         iCount, ii;              // Temp variables
        ASICOLDSC   coldsc;                  /* Column descriptoir handle */
        ASIDATADSC  datadsc;                 /* Data descriptor handle */
        ASIIDENT    name;                    /* Identifier: column name */


        if (showDsc == kAsiFalse) {  /* Do not display if not configured by C:ASISETUP */
                return;
        }

        iCount = asi_colcount (handle);        /* Get number of resulting columns */

        ads_printf("\n     Table structure");

        /* Print each column descriptor */
        for (ii = 0; ii < iCount; ii ++) {

                /* Get column descriptor */
                if (asi_cds (handle, ii, &coldsc) == kAsiGood) { /* Get column descriptor */

                        // Print column name
            asi_cdsc_name (coldsc, &name);              /* Get column name */
            ads_printf("\n %30S", asi_get_ident (name, buff, 128));
            asi_destroy_ident (&name);

            /* Get column data descriptor and print it */
            asi_cdsc_ddsc (coldsc, &datadsc);
            if (asi_cdsc_ddsc (coldsc, &datadsc) == kAsiGood) {
                                ads_printf("   %s", asi_ddsc_sqltype (datadsc, buff, 256));
                asi_destroy_ddsc (&datadsc);
            }
        }
        }
}


/*******************************************************************************************
  This function prints input parameters descriptor. Parameter descriptors are
  returned after preparation of the SQL statement which contains references to them.
  For example:

        Select * from employee where last_name = :var1


*******************************************************************************************/
static void print_pardsc (
        ASIHANDLE       handle          /* Cursor or Statement */
)
{
        int                     iCount, ii;        /* Temp variables */
        ASIPARDSC               pardsc;            /* Parameter descriptor */
        ASIDATADSC              datadsc;           /* Data descriptor */
        ASIIDENT                name;              /* Parameter name */

        iCount = asi_parcount (handle);   /* Number of parameters */
        if (iCount == 0) {
                return ;      /* No parameters */
        }

        ads_printf("\n     Parameters in statement");
        ads_printf("\n %30s%15s%s","Name","Nulability","   SQL Type");

        /* Print each parameter */
        for (ii = 0; ii < iCount; ii ++) {
                /* Get parameter descriptor */
        if (asi_pds (handle, ii, &pardsc) != kAsiBad) {

                        /* Print parameter name */
            asi_pdsc_name (pardsc, &name);
            ads_printf("\n %30s", asi_get_ident (name,  buff, 256));
            asi_destroy_ident (&name);

            /* Print parameter nullability (can it be NULL) */
            if (asi_pdsc_nullable (pardsc) == kAsiTrue ) {
                ads_printf("%15s","yes");
            } else {
                ads_printf("%15s","no");
            }
            /* Get parameter data descriptor and print it */
            if (asi_pdsc_ddsc (pardsc, &datadsc) == kAsiGood) {
                ads_printf("   %s", asi_ddsc_sqltype (datadsc, buff, 256));
                asi_destroy_ddsc (&datadsc);
            }
        }
        }
}



/****************************************************************************
  This function initializes input parameters and binds them with
  the host program buffers.
  It allocates character buffer for each paramter in the input SQL statement
  and binds this memory buffer with parameter. Buffer type is specified as
  kAsiHChar, because character buffer can be converted to SQL type.
****************************************************************************/
EAsiBoolean initParams (
        ASIHANDLE  Stm,
        struct hbinds   **  hosts
)
{
        int             iCount;
        int             ii;
        struct hbinds * buffers;

        iCount = asi_parcount (Stm);
        if (iCount != 0) {
                // Allocate host buffers
                buffers = (struct hbinds *) malloc (sizeof (struct hbinds) * iCount);
                if (buffers == 0) {
                        return kAsiBad;
                }
                // bind them with SQL statement
                for (ii = 0; ii < iCount; ii ++) {
                        asi_bndnum (Stm, ii, buffers[ii].buffer, & buffers[ii].indp, 256, kAsiHchar);
                }
                * hosts = buffers;
        }
        return kAsiGood;
}



/****************************************************************************
   This function reads values for input parameters and places them
   into buffers bound with SQL statement parameters
****************************************************************************/
void readParams (
        ASIHANDLE  Stm,
        struct hbinds   *  buffers
)
{
        int           iCount;
        int           ii;
        ASIPARDSC     pardsc;
        ASIIDENT      name;

        iCount = asi_parcount (Stm);
        for (ii = 0; ii < iCount; ii ++) {
                if (asi_pds (Stm, ii, &pardsc) != kAsiBad) {
                        // Print parameter name
                        asi_pdsc_name (pardsc, &name);
                        ads_printf("\n %-30s", asi_get_ident (name, buff, 256));
                        asi_destroy_ident (&name);

                        // Get parameter value
                        ads_getstring (1, ": ", buffer);
                        if (*buffer == '.' && * (buffer + 1) == '\0') {
                                buffers[ii].indp = -1;    /* NULL Value */
                        } else {
                                strncpy (buffers[ii].buffer, buffer, 128);
                        }
                }
        }
        return;
}

/***************************************************************************
        This function releases host buffers
***************************************************************************/
void termParams (
        struct hbinds *  buffers
)
{
        if (buffers != 0) {
                free (buffers);
                buffers = 0;
        }
}



/***************************************************************************
  This function initializes destinations for output values and bind them with
  the output parameters. Resulting columns of the single row select statement
  or cursor
***************************************************************************/
EAsiBoolean initDst (
        ASIHANDLE  Stm,    /* Statement or Cursor */
        struct hbinds **   hosts
)
{
        int             iCount;
        int             ii;
        struct hbinds * buffers;

        iCount = asi_colcount (Stm);
        if (iCount != 0) {
                // Allocate host buffers
                buffers = (struct hbinds *) malloc (sizeof (struct hbinds) * iCount);
                if (buffers == 0) {
                        return kAsiBad;
                }
                // bind them with output parameters of SQL statement
                // All SQL data type can be converted to char.
                // Therefore use kAsiHChar buffer as destination
                for (ii = 0; ii < iCount; ii ++) {
                        asi_sob (Stm, ii, buffers[ii].buffer, & buffers[ii].indp, 256, kAsiHchar);
                }
                * hosts = buffers;
        }
        return kAsiGood;
}


/*************************************************************************
  This function does positioned update
*************************************************************************/
static EAsiBoolean do_csr_update (
        ASICURSOR csr                   /* Updateable cursor in the open state, positioned on row */
)
{
        ASICOLDSC    coldsc;          // Column descriptor
        ASIIDENT     name;            // Column name
        EAsiHostType type;            // Type of buffer

        int          ii;
        int          iCount;

        iCount = asi_colcount (csr);            /* Number of columns */
        for (ii = 0; ii < iCount; ii++) {
                if (asi_cds (csr, ii, &coldsc) == kAsiGood) {
                        // Print column name
                        asi_cdsc_name (coldsc, &name);
                        ads_printf("%-30s", asi_get_ident (name, buff, 128));
                        ads_getstring (1, ": ", buffer);
                        if (* buffer == '\0') {
                                continue;
                        }
                        if (*buffer == '.' && *(buffer + 1) == '\0') {
                                type = kAsiHnull;                       /* Set column to NULL */
                        } else {
                                type = kAsiHchar;                       /* Char can converted to any SQL type */
                        }
                        if (asi_update (csr, name, type, strlen (buffer), buffer, (ASIIDENT) 0) == kAsiBad) {
                                print_diag (csr);
                                ads_printf ("\nColumn %s update error", asi_get_ident (name, buff, 128));
                        }
                        asi_destroy_ident (&name);
                }
        }
        return kAsiTrue;
}

/****************************************************************************
  This function prints current row, each column on separate line
****************************************************************************/
static void print_currow (
        ASICURSOR  csr          /* Cursor in the open state */
)
{
        // Column descriptor and name
        ASICOLDSC          coldsc;
        ASIIDENT           name;

        // Value of the column
        char               buffer [128];
        unsigned char      bbuffer[128];   // Destination for bits
        short              indp;

        // Temporary variables
        int                ii;

        ASIDATADSC         ddsc;                        /* Data descriptor */
        EAsiBoolean        rCode = kAsiBad;


        ads_printf ("\n");
        for (ii = 0; ii < asi_colcount (csr); ii ++) {
                // Print column name
        if (asi_cds (csr, ii, &coldsc) == kAsiGood) {
                        asi_cdsc_name (coldsc, &name);
            ads_printf("\n%-30s: ", asi_get_ident (name, buff, 128));
            asi_destroy_ident (&name);
        }

        // Print column data
        asi_cdsc_ddsc (coldsc, &ddsc);   // Get data descriptor
        if (asi_ddsc_type (ddsc) == kAsiBit || asi_ddsc_type (ddsc) == kAsiBitVar) {
                        /* Bit type is a special case */
            if ((rCode = asi_cvl (csr, ii, bbuffer, &indp, 128*8, kAsiHbinary)) == kAsiGood) {
                                // Indicator holds the actual number of bits
                // stored in the destination buffer
                if (indp >= 0) {
                                        ads_printf("[%s]", bittoXstr ((char *) buffer, 256, bbuffer, (int) indp));
                } else {
                                        ads_printf(".");
                }
            }
        } else {
            // Get result as char
            if ((rCode = asi_cvl (csr, ii, buffer, &indp, 128, kAsiHchar)) == kAsiGood) {
                                if (indp >= 0) {
                                        ads_printf("[%s]", buffer);
                                } else {
                                        ads_printf(".");
                                }
            }
        }
        if (rCode == kAsiBad) {
            // Print diagnostics
            print_diag (csr);
        }
        asi_destroy_ddsc (&ddsc);
        }
        return;
}


/**************************************************************************
  This function prepares formats for browsing selection rowset
**************************************************************************/
static char **make_formats (
        ASICURSOR csr
)
{
        char       ** formats  = 0;
        ASICOLDSC     coldsc;       // Column descriptor
        ASIDATADSC    dDsc;        // Data descriptor
        ASIIDENT      name;
        int           ii;


        formats = (char **) malloc (sizeof (char *) * asi_colcount (csr));

        if (formats == 0) {
                return 0;
        }

        for (ii = 0; ii < asi_colcount (csr); ii ++) {
                asi_cds (csr, ii, &coldsc);
                asi_cdsc_name (coldsc, &name);
                asi_get_ident (name, buff, 256);
                asi_cdsc_ddsc (coldsc, & dDsc);
                if (dDsc != 0) {
                        formats[ii] = (char *) malloc (32);
                        if (formats [ii] != 0) {

                                if (asi_ddsc_type (dDsc) == kAsiChar || asi_ddsc_type (dDsc) == kAsiCharVar) {
                                        sprintf (formats[ii], "  %%-%ds",
                                                        ASI_MAX (strlen (buff), asi_ddsc_length (dDsc)));

                                } else if (asi_ddsc_type (dDsc) == kAsiBit ||
                                        asi_ddsc_type (dDsc) == kAsiBitVar) {
                                        sprintf (formats[ii], "b  %%-%ds",
                                                        ASI_MAX (strlen (buff), asi_ddsc_length (dDsc) / 4 + 1));

                                } else {
                                        sprintf (formats[ii], " %%%ds ",
                                                        ASI_MAX ( strlen (buff), asi_ddsc_length (dDsc)));
                                }
                        }
                        asi_destroy_ddsc (&dDsc);
                }
                asi_destroy_ident (&name);
        }
        return formats;
}


/***************************************************************************
  This function prints rowset header
***************************************************************************/
static void print_header (
        ASICURSOR               csr,            /* Cursor */
        char            **      formats
)
{
        ASICOLDSC     coldsc;           /* Column descriptor */
        ASIIDENT      name;                             /* Column name */
        int           ii;

        write_string ("\n");
        for (ii = 0; ii < asi_colcount (csr); ii ++) {
                asi_cds (csr, ii, &coldsc);
                asi_cdsc_name (coldsc, &name);
                sprintf (buffer, formats[ii]+1, asi_get_ident (name, buff, 256));
                write_string (buffer);
                asi_destroy_ident (&name);
        }
        write_string ("\n");
        write_string ("========================================================");
}

/**********************************************************************
  This function prints row on one line
***********************************************************************/
static void print_row (
        ASICURSOR               csr,            /* Cursor */
        char            **      formats         /* Formats for each value */)
{
        short           indp;
        int             ii;
        unsigned char   bbuffer [256];      // Bit destination
        EAsiBoolean     rCode = kAsiBad;

        write_string ("\n");
        for (ii = 0; ii < asi_colcount (csr); ii ++) {
        if (*formats[ii] == 'b') {
                        if ((rCode = asi_cvl (csr, ii, bbuffer, &indp, 128*8, kAsiHbinary)) == kAsiGood &&
                indp > 0) {
                                bittoXstr (buff, 256, bbuffer, (int) indp);
            }
        } else {
            // Get result as char buffer
            rCode = asi_cvl (csr, ii, buff, &indp, 128, kAsiHchar);
        }
        if (indp < 0 || rCode == kAsiBad) {
            buff [0] = 0;
        }
        if (*formats[ii] == 'b') {
            sprintf(buffer, formats[ii]+1, buff);
        } else {
            sprintf(buffer, formats[ii]+1, buff);
        }
        write_string (buffer);
        }
}


/**********************************************************************
  This function browses resulting rowset
***********************************************************************/
static void print_rowset (
        ASICURSOR csr           /* Cursor */
)
{
    char        **      formats  = 0;
    int                 ii       = 0;

    formats = make_formats (csr);       /* Make formats for each column */
    print_header (csr, formats);        /* Print page header */
        /* Fetch untill end of selection set */
    while (asi_fetch (csr) == kAsiGood) {
                print_row (csr, formats);       /* Print row on line */
                ii ++;
                if (ii == 21 && stopPage == kAsiTrue) { /* Pause after each page */
                        ads_getstring (0, "\nPress return to continue or [e] to exit immediatelly ...", buffer);
                        if (*buffer == 'e') {
                                break;
                        }
                        print_header (csr, formats);
                        ii = 0;
                }
    }
        /* Release fromats */
    for (ii = 0; ii < asi_colcount (csr); ii ++) {
                if (formats[ii] != 0) {
                        free (formats[ii]);
                }
    }
    free (formats);
        return;
}

/**************************************************************************
  This functions scans selction set row by row and prompting
  user for positioned cursor operations.
**************************************************************************/
void scan_rowset (
        ASICURSOR csr           /* Cursor in the open state */
)
{
    char        cBuffer[127];                 // Temporary buffer
    EAsiBoolean rCode         = kAsiFalse;     // Return code
    long        lOffset;                      // Relative and absolute fetch value

    cBuffer[0] = 'n';
    for (;;) {
                switch ( cBuffer[0] ) {
        case 'n':                   // Fetch next
                        rCode = asi_fetch (csr);
            break;
        case 'f':                   // Fetch first
            rCode = asi_fetchFirst (csr);
            break;
        case 'p':                  // Fetch prior
            rCode = asi_fetchPrior (csr);
            break;
        case 'l':                  // Fetch last
            rCode = asi_fetchLast (csr);
            break;
        case 'r':                  // Fetch relative
            ads_getint ("\nEnter relative row number: ", (int*)&lOffset);
            rCode = asi_fetchRelative (csr, lOffset);
            break;
        case 'a':                 // Fetch absolute
            ads_getint ("\nEnter absolute row number: ", (int*)&lOffset);
            rCode = asi_fetchAbsolute (csr, lOffset);
            break;
        case 'd':                 // Delete current row
            rCode = asi_delete (csr);
            break;
        case 'u':                // Update current row
            rCode = do_csr_update (csr);
            break;
        default:
            cBuffer[0] = 'e';
            break;
        }
        if ( cBuffer[0] == 'e' ) {
                        break;
        }
        if ( rCode == kAsiGood ) {
                        print_currow (csr);
        }
        print_diag(csr);
        ads_getstring(0, "\nEnter [n]ext/[f]irst/[p]revios/[l]ast/[r]elative/[a]bsolute/[d]elete/[u]pdate: ", cBuffer);
        }
    return;
}


/**************************************************************************
        This function processes prepared cursor specification
**************************************************************************/
void do_cursor (
        ASISTATEMENT Stm                /* Prepared cursor specification */
)
{
    ASICURSOR   Csr;                          // Cursor
    char        cBuffer[127];                 // Temporary buffer

    // Cursor attributes
    EAsiCurScr  scr          = csrScr;
    EAsiCurSns  sns          = csrSns;

    struct hbinds * iparams  = 0;

        /* If prompting for cursor type was configured via ASISETUP, */
        /* Prompt for cursor scrollabnility and sensitivity */
    if (askCsrMode == kAsiTrue) {
                ads_getstring(0, "\nEnter [s] for scrollable cursor: ", cBuffer);
                if (cBuffer[0] == 's') {        /* Secollable ? */
                        scr = kAsiScroll;
                        sns = kAsiInsensitive;
                        ads_printf("\nScrollable cursor is assumed insensitive");
                }
                if (scr != kAsiScroll) {        /* Insensitive ? */
                        ads_getstring(0, "\nEnter [i] for insensitive cursor: ", cBuffer);
                        if (cBuffer[0] == 'i') {
                                sns = kAsiInsensitive;
                        }
                }
    }
    /* Construct cursor */
    asi_constr_csr (&Csr);      /* Construct cursor handke */

    /* Allocate cursor */
    if ( asi_alloc_csr (Csr, Stm, "MyCursor", scr, sns) == kAsiGood ) {

                // Bind parameters
        if (initParams (Csr, & iparams) == kAsiBad) {
                        asi_destroy_csr (&Csr);
                        return;
        }
        /* Get parameter values from user and open cursor repeatedly */
        do {
                        readParams (Csr, iparams);                              /* Read parameters if any */
            if ( asi_open (Csr) == kAsiBad ) {          /* Open cursor */
                print_diag(Csr);                                        /* Print diagnostics */
            } else {
                if (showOne == kAsiFalse) {
                                        print_rowset (Csr);     /* Display all rows */
                } else {
                    scan_rowset (Csr);  /* Scan cursor row by row */
                }
                if ( asi_close (Csr) == kAsiBad ) {    /* close cursor */
                    print_diag(Csr);
                }
            }
            * cBuffer = '\0';
            if (doAgain == kAsiTrue) {  /* Open again ? */
                ads_getstring(0, "\nEnter [r] for re-open cursor: ", cBuffer);
            }
        } while ( cBuffer[0] == 'r' );
        termParams (iparams);
    } else {
        print_diag(Csr);
    }
    /* Destroy cursor */
    asi_destroy_csr (&Csr);

        return;
}

/***************************************************************************
  This function executes single row select statement. For example:
  Select f1 into :a from tab;
***************************************************************************/
static void do_single_select (
        ASISTATEMENT  Stm                     /* Prepared single row select statement */
)
{
    struct hbinds       *       iparams  = 0;
    struct hbinds       *       oparams  = 0;
    char                                cBuffer[127];
    int                                 ii;

        /* Initialize input parameter buffers (if any) */
    if (initParams (Stm, & iparams) == kAsiBad) {
        return;
    }
    /* Initialize output buffer and bind them with output columns */
    if (initDst (Stm, & oparams) == kAsiBad) {
        termParams (iparams);
        return;
    }

    do {
        readParams (Stm, iparams);
                /* Execute single row select statement */
        if (asi_execute (Stm) == kAsiBad ) {
            print_diag(Stm);
        } else {
                        /* If success, print column values */
            for (ii = 0; ii < asi_colcount (Stm); ii ++) {
               if (oparams[ii].indp >= 0) {
                  ads_printf ("\n%s", oparams[ii].buffer);
               }  else {
                  ads_printf ("\nNull value");
               }
            }
        }
                /* Ask for re-execution, if configured */
        if (doAgain == kAsiTrue) {
           ads_getstring(0, "\nEnter [r] to re-execute: ", cBuffer);
        }
    } while ( cBuffer[0] == 'r' );

        /* Release input/output buffers */
    termParams (iparams);
    termParams (oparams);

        return;
}


/**************************************************************************
   This function executes statements other than cursor and single
   row select statement
**************************************************************************/
static void do_ordinary (
        ASISTATEMENT  Stm             /* Prepared SQL statement */
)
{
    struct hbinds       *       iparams  = 0;
    char                                cBuffer[127];


    if (initParams (Stm, & iparams) == kAsiBad) {
                return;
    }
    do {
                /* Read input */
        readParams (Stm, iparams);

                /* Execute SQL statement */
        if (asi_execute (Stm) == kAsiBad ) {
            print_diag(Stm);

        } else {
                /* Print number of rows affected in case of the following statemens :*/
            if (asi_stm (Stm) == kAsiINSERT ||                  /* INSERT */
                asi_stm (Stm) == kAsiDELETE_WHERE ||    /* DELETE Searched */
                asi_stm (Stm) == kAsiUPDATE_WHERE) {    /* UPDATE Searched */
                ads_printf("\n %d row(s) affected", asi_rowqty (Stm));
            }
        }
                /* Ask for re-execution, if configured */
        if (doAgain == kAsiTrue) {
           ads_getstring (0, "\nEnter [r] to re-execute: ", cBuffer);
        }
    } while ( cBuffer[0] == 'r' );

    termParams (iparams);

        return;
}



/******************************************************************************
        This function processes SQL statement. This function illustrates
        the principal steps of SQL statement processing:
        1. construct statement
        2. prepare statement
        3. define type of prepared statement
        4. dependent from statement type process prepared statement
        5. destroy statement
******************************************************************************/
void do_statement (
        char *  stm             /* SQL statement */
)
{
        ASISTATEMENT    Stm;    /* SQL statement handle */

   // Write to protocol file
   if (echoToFile == kAsiTrue) {
      fprintf (efDsc, "\n%s", stm);
   }
   /* If statement is prefixed by "N ", then the native DBMS statement is
      assummed. It is directly passed to driver for immediate execution  */

   if (stm[0]  == 'N' && stm[1] == ' ') {
      asi_constr_native_stm (&Stm);             /* construct native statement */
          /* immediate execute it */
      if (asi_iexecute  (Stm, session, stm + 2) == kAsiBad) {
          ads_printf ("\nExecution of the native statement failed");
          print_diag(Stm);
      }

   } else {

      asi_constr_stm (&Stm);  /* Construct ordinary statement */

      /* Prepare SQL statement */
      if ( asi_prepare (Stm, session,  stm) == kAsiBad ) {
          print_diag(Stm);
          ads_printf ("\n%s", stm + asi_synerrpos (Stm));
          if (pauseAfterE == kAsiTrue && pauseAfter == kAsiFalse) {
              ads_getstring (0, "\nPress return to continue ...", buffer);
          }
      } else {
                  /* Print statement type */

          ads_printf("\nSQL statement type: %d", asi_stm (Stm));
                  /* Print input parameter ddesciptors */
          print_pardsc(Stm);

                  /* Switch by statement type */
          switch (asi_stm (Stm)) {
          case kAsiCURSOR:        /* Cursor */
             print_coldsc(Stm);
             do_cursor (Stm);
             break;
          case kAsiSELECT:       /* Single row select statement */
             print_coldsc(Stm);
             do_single_select(Stm);
             break;
          default:              /* Other types of statements */
             do_ordinary(Stm);
             break;
          }
      }
   }
   if (pauseAfter == kAsiTrue) {
       ads_getstring (0, "\nPress return to continue ...", buffer);
   }

   /* destroy statement */
   asi_destroy_stm (&Stm);

   return;
}

/**************************************************************************
  This function creates environment description in registry
**************************************************************************/

void create_env ()
{
        static char env [128];
        static char drv [128];
        ASICONFIG   config;

        display_section ("ENVIRONMENTS");
        ads_getstring (0, "\nEnter new environemnt name : ", env);
        if (*env == '\0') {
                return;
        }
        display_section ("ASI DRIVERS");
        ads_getstring (0, "\nEnter driver name : ", drv);
        if (*drv == '\0') {
                ads_printf ("\nDriver that runs environment must be specified");
                return;
        }
        if (asi_constr_cfg (&config) == kAsiBad) {
                ads_printf ("\nCan't construct configuration handle");
                return ;
        }
        if (asi_createenv(config, env, drv) == kAsiBad) {
                ads_printf ("\nError during environment creation");
        }
        asi_destroy_cfg (&config);

        return;

}

/****************************************************************************
  This function drops environment description from registry
****************************************************************************/
void drop_env ()
{
        static char env [128];
        ASICONFIG   config;

        display_section ("ENVIRONMENTS");
        ads_getstring (0, "\nEnter environemnt name to drop: ", env);
        if (*env == '\0') {
                return;
        }
        if (asi_constr_cfg (&config) == kAsiBad) {
                ads_printf ("\nCan't construct configuration handle");
                return ;
        }
        if (asi_dropenv(config, env) == kAsiBad) {
                ads_printf ("\nCannot drop environment");
        }
        asi_destroy_cfg (&config);

        return;
}


/**************************************************************************
  This function tunes ast sample program.
***************************************************************************/
void do_settings ()
{
    static char buffer [128];
    EAsiBoolean keepDoing = kAsiTrue;

    for (keepDoing = kAsiTrue; keepDoing == kAsiTrue;) {
        // Print current settings
        ads_printf ("\nCurrent settings:\n");
        ads_printf ("\n1.  Script file format              <%s>", oldScrFile == kAsiTrue ? "Old" : "New");
        ads_printf ("\n2.  Show resulting table descriptor <%s>", showDsc == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n3.  Prompt for cursor type          <%s>", askCsrMode == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n4.  Scroll selection set            <%s>", showOne == kAsiTrue ? "By one row" : "Browse");
        ads_printf ("\n5.  Stop at page end                <%s>", stopPage == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n6.  Pause after statement execution <%s>", pauseAfter == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n7.  Pause after error               <%s>", pauseAfterE == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n8.  Prompt for re-execution         <%s>", doAgain == kAsiTrue ? "Yes" : "No");
        ads_printf ("\n");
        ads_printf ("\nDefault cursor type:");
        ads_printf ("\n9.  Insensitive                     <%s>", csrSns == kAsiInsensitive ? "Yes": "No");
        ads_printf ("\n10. Scroll                          <%s>", csrScr == kAsiScroll ? "Yes": "No");
        ads_printf ("\n");
        if (echoToFile == kAsiFalse) {
            ads_printf ("\n11. Do not write output to protocol file");
        } else {
            ads_printf ("\n11. Write to protocol file          <%s>", FileName);
        }

        ads_getstring (0, "\n\nEnter number to switch item or return to exit: ", buffer);

        switch (atoi (buffer)) {
        case 1:
             oldScrFile = switch_boolean (oldScrFile);
             break;
        case 2:
             showDsc = switch_boolean (showDsc);
             break;
        case 3:
             askCsrMode = switch_boolean (askCsrMode);
             break;
        case 4:
             showOne = switch_boolean (showOne);
             break;
        case 5:
             stopPage = switch_boolean (stopPage);
             break;

        case 6:
             pauseAfter = switch_boolean (pauseAfter);
             break;

        case 7:
             pauseAfterE = switch_boolean (pauseAfterE);
             break;

        case 8:
             doAgain = switch_boolean (doAgain);
             break;

        case 9:
             if (csrSns == kAsiInsensitive)
                csrSns = kAsiSnsUndef;
             else
                csrSns = kAsiInsensitive;
             break;

        case 10:
             if (csrScr == kAsiScroll)
                csrScr = kAsiNonScroll;
             else
                csrScr = kAsiScroll;
             break;

        case 11:
             if (echoToFile == kAsiTrue) {
                if (efDsc != 0) {
                   fclose (efDsc);
                   efDsc = 0;
                }
                echoToFile = kAsiFalse;
             } else {
                ads_getstring (0, "\nEnter protocol file name: ", FileName);
                if (*FileName == '\0') {
                   break;
                }
                efDsc = fopen (FileName, "at");
                if (efDsc == 0) {
                    ads_printf ("\nCan't open file for append");
                    break;
                }
                {
                   char t[32], d[32];
                   echoToFile = kAsiTrue;
                   fprintf (efDsc, "\nStart writing %s, %s", _strdate (d), _strtime (t));
                }
             }
             break;
        case 0:
             keepDoing = kAsiFalse;
             break;

        }
    }

        return;
}


/***********************************************************************
  This functions connects to SQL environment
***********************************************************************/
void do_connect (void)
{
        // SQL environment name, username, and password.
        // Environment name is equal to the name of the DBMS driver executable.
        //
        static   char Password [128];

        static   char buffer[128];      // Temporary buffer

        if (session == 0) {
                /* Construct session */
                if (asi_constr_session (&session, appl) == kAsiBad) {
                        ads_printf ("\nUnable to construct session");
                        return;
                }
        }


        // Disconnect if already connection exists
        if (isConnected == kAsiTrue) {
                if (asi_disconnect (session) == kAsiBad) {
                        ads_printf ("\nCan't terminate SQL session. Fix problems and try again ...");
                        print_diag(session);
                        return;
                }
                isConnected = kAsiFalse;
        }

        for (;;) {
                display_env ();    // Display available environments

                ads_getstring (0, "\nEnvironment: ", buffer);
                if ( * buffer == '\0' ) {
                        break;
                }

                strncpy (EnvName, buffer, 128);

                ads_getstring (0, "User       : ", buffer);
                strncpy (UserName, buffer, 128);

                ads_getstring (0, "Password   : ", Password);

                if ( asi_connect (session, EnvName, UserName, Password) == kAsiGood ) {
                        /* display driver information */
                        asi_dbms (session, buffer, 128);
                        ads_printf ("\nDBMS:          %s", buffer);

                        asi_sqlobject (session, buffer, 128);
                        ads_printf ("\nSQL Object Id: %s", buffer);

                        asi_message (session, buffer, 128);
                        ads_printf ("\nMessage:       %s", buffer);
                        isConnected = kAsiTrue;
                        break;
                }
                /* Error found check diagnostic information... */
                print_diag(session);
        }
        return ;
}

/****************************************************************************
        This function disconnects from SQL environment
****************************************************************************/
void do_disconnect ()
{
        if (isConnected == kAsiFalse) {
                ads_printf ("\nNo current connection. Use ASICONNECT");
                return;
        }
        if (asi_disconnect (session) == kAsiBad) {
                print_diag (session);
                return;
        }
        /* Destroy session */
        asi_destroy_session (&session, appl);
        isConnected = kAsiFalse;

        return;
}

/***************************************************************************
   This function prompt user for SQL statement and pass it to
   statment processing function.
***************************************************************************/
void do_sqled ()
{
        EAsiBoolean      isNeedNew = kAsiTrue;  // End of read loop

        if (isConnected == kAsiFalse) {
                ads_printf ("\nNo current connection. Use ASICONNECT");
                return;
        }

        /* Read SQL statements and process them */

        for (isNeedNew = kAsiTrue; isNeedNew == kAsiTrue; ) {
                * stm = '\0';
                ads_printf ("\n%s/%s", EnvName, UserName);
                for (;;) {
                        /* Print prompt and get line */
                        ads_getstring (1, "> ", buffer);

                        /* Test for end and return if void response */
                        if ( * stm == '\0' && * buffer == '\0' ) {
                                isNeedNew = kAsiFalse;
                                break;
                        }

                        if ( buffer[strlen(buffer) - 1] == '\n' ) {
                                buffer[strlen(buffer) - 1] = '\0';
                        }
                        if ( buffer[strlen(buffer) - 1] == ';' ) {
                                buffer[strlen(buffer) - 1] = '\0';
                                strcat (stm, buffer);
                                do_statement (stm);
                                * stm = 0;
                                break;

                        } else {
                                strcat (stm, buffer);
                                strcat (stm, " ");
                        }
                }
        }

        return;
}

/****************************************************************************
   This function processes a new script file.
   Statement is terminated by ; symbol
****************************************************************************/
void do_new_file (FILE * fh)
{
        char        * p;

        * stm = '\0';
        while (fgets (buffer, 127, fh) != 0) {
                if (strncmp (buffer, "//", 2) == 0) {
                        continue;                       // Skip comments
                }
                if (strncmp (buffer, "@@", 2) == 0) {
                        ads_printf ("%s", buffer + 2);
                        continue;                       // Echo
                }
                if ( buffer[strlen(buffer) - 1] == '\n' ) {
                        buffer[strlen(buffer) - 1] = '\0';    // Kill LF
                }
                if (*buffer == '\0') {
                        continue;                       // Skip empty line
                }

                ads_printf ("%s\n", buffer);              // Echo line

                // Kill trailing blanks
                for (p = buffer + strlen (buffer) - 1; p != buffer; p --) {
                        if (* p == ' ') {
                                * p = '\0';
                        } else {
                                break;
                        }
                }
                if (*buffer == '\0') {
                        continue;                       // Skip empty line
                }

                if ( buffer[strlen(buffer) - 1] == ';' ) {
                        buffer[strlen(buffer) - 1] = '\0';
                        strcat (stm, buffer);
                        do_statement (stm);
                        ads_printf ("\n");
                        *stm = '\0';
                } else {
                        strcat (stm, buffer);
                        strcat (stm, " ");
                }
   }

   return;
}


/*****************************************************************************
  This function reads the old script file (R12)
  (Line continuation symbol is & at the end of line)
*****************************************************************************/
void do_old_file (FILE * fh)
{
        char        * p;

        * stm = '\0';
        while (fgets (buffer, 127, fh) != 0) {
                if (*buffer == '$') {
                        continue;                       // Skip comments
                }
                if ( buffer[strlen(buffer) - 1] == '\n' ) {
                        buffer[strlen(buffer) - 1] = '\0';    // Kill LF
                }
                if (*buffer == '\0') {
                        continue;                       // Skip empty line
                }

                /* Kill trailing blanks */
                for (p = buffer + strlen (buffer) - 1; p != buffer; p --) {
                        if (* p == ' ') {
                                * p = '\0';
                        } else {
                                break;
                        }
                }

                if (*buffer == '\0') {
                        continue;                          // Skip empty line
                }

                ads_printf ("%s\n", buffer);              // Echo line
                if ( buffer[strlen(buffer) - 1] == '&' ) {
                        buffer[strlen(buffer) - 1] = '\0';
                        strcat (stm, " ");
                        strcat (stm, buffer);
                        ads_printf ("\n");
                } else {
                        strcat (stm, buffer);
                        do_statement (stm);
                        * stm = '\0';
                }
        }
        return;
}


/***************************************************************************
  This function processes the script file
***************************************************************************/
void do_script (void)
{

        FILE        * fh = 0;

        if (isConnected == kAsiFalse) {
                ads_printf ("\nNo current connection. Use ASICONNECT");
                return;
        }

        ads_getstring (0, "\nEnter file name or return to exit: ", buffer);
        if (*buffer == 0) {
                return;
        }

        fh = fopen (buffer, "rt");
        if (fh == 0) {
                ads_printf ("\nCannot open file <%s>", buffer);
                return;
        }

        if (oldScrFile == kAsiFalse) {
                do_new_file (fh);
        } else {
                do_old_file (fh);
        }
        fclose (fh);
}


/****************************************************************************
  This function reads program setting from the REGISTRY
****************************************************************************/
void readSettings ()
{
        ASICONFIG   config;        /* configuration file handle */


        /* Construct configuration file */
        if (asi_constr_cfg (&config) == kAsiBad) {
                ads_printf ("\nCannot construct ASI configuration file handle");
                return ;
        }

        /* Script file version */
        if (asi_getcfgstring (config, "ASISAMPLE", "ScriptVersion", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "OLD") == 0) {
                        oldScrFile = kAsiTrue;
                }
        }

        /* Cursor mode query */
        if (asi_getcfgstring (config, "ASISAMPLE", "AskCursor", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        askCsrMode = kAsiTrue;
                }
        }

        /* Show result descriptor */
        if (asi_getcfgstring (config, "ASISAMPLE", "ShowTableDsc", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        showDsc = kAsiTrue;
                }
        }

        /* Read default cursor declartions */
        if (asi_getcfgstring (config, "ASISAMPLE", "CsrSensitivity", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Insensitive") == 0) {
                        csrSns = kAsiInsensitive;
                }
        }
        if (asi_getcfgstring (config, "ASISAMPLE", "CsrScrollability", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Scroll") == 0) {
                        csrScr = kAsiScroll;
                }
        }

        /* Read browse mode */
        if (asi_getcfgstring (config, "ASISAMPLE", "Browse", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "No") == 0) {
                        showOne = kAsiTrue;
                }
        }

        /* Read page stop flag */
        if (asi_getcfgstring (config, "ASISAMPLE", "PageStop", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "No") == 0) {
                        stopPage = kAsiFalse;
                }
        }

        /* Read "pause after statement execution" flag */
        if (asi_getcfgstring (config, "ASISAMPLE", "PauseAfterExecution", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        pauseAfter = kAsiTrue;
                }
        }

        /* Read "pause after error" flag */
        if (asi_getcfgstring (config, "ASISAMPLE", "PauseAfterError", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "No") == 0) {
                        pauseAfterE = kAsiFalse;
                }
        }

        /* Re-execute statement */
        if (asi_getcfgstring (config, "ASISAMPLE", "Re-execute", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        doAgain = kAsiTrue;
                }
        }

        /* Echo to file */
        if (asi_getcfgstring (config, "ASISAMPLE", "EchoToFile", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        echoToFile = kAsiTrue;
                }
        }

        /* Echo file name */
        if (asi_getcfgstring (config, "ASISAMPLE", "EchoFile", "", buffer, 128) > 0) {
                strcpy (FileName, buffer);
        }

        /* Time statistics */
        if (asi_getcfgstring (config, "ASISAMPLE", "ElapseTime", "", buffer, 128) > 0) {
                if (strcmpi (buffer, "Yes") == 0) {
                        timeMeasure = kAsiTrue;
                }
        }
        asi_destroy_cfg (&config);   /* Destroy configuration handle */

        return;

}

/***********************************************************************
  This function writes its configuration to the registry
***********************************************************************/
void writeSettings ()
{
        ASICONFIG config = 0;

        /* Construct configuration file */
        if (asi_constr_cfg (&config) == kAsiBad) {
                ads_printf ("\nCannot construct ASI configuration file handle");
                return ;
        }

        // Script file version
        if (oldScrFile == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "ScriptVersion", "Old");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "ScriptVersion", "New");
        }

        // Cursor mode query
        if (askCsrMode == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "AskCursor", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "AskCursor", "No");
        }

        // Show result descriptor
        if (showDsc == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "ShowTableDsc", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "ShowTableDsc", "No");
        }

        // Read default cursor declartions
        if (csrSns == kAsiInsensitive) {
                asi_setcfgstring (config, "ASISAMPLE", "CsrSensitivity", "Insensitive");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "CsrSensitivity", "");
        }
        if (csrScr == kAsiScroll) {
                asi_setcfgstring (config, "ASISAMPLE", "CsrScrollability", "Scroll");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "CsrScrollability", "");
        }

        //  browse mode
        if (showOne == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "Browse", "No");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "Browse", "Yes");
        }

        // page stop flag
        if (stopPage == kAsiFalse) {
                asi_setcfgstring (config, "ASISAMPLE", "PageStop", "No");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "PageStop", "Yes");
        }

        // "pause after statement execution" flag
        if (pauseAfter == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "PauseAfterExecution", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "PauseAfterExecution", "No");
        }

        // Read "pause after error" flag
        if (pauseAfterE == kAsiFalse) {
                asi_setcfgstring (config, "ASISAMPLE", "PauseAfterError", "No");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "PauseAfterError", "Yes");
        }

        // Re-execute statement
        if (doAgain == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "Re-execute", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "Re-execute", "No");
        }

        // Echo to file
        if (echoToFile == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "EchoToFile", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "EchoToFile", "No");
        }

        // Echo file name
        if (*FileName != '\0') {
                asi_setcfgstring (config, "ASISAMPLE", "EchoFile", FileName);
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "EchoFile", "");
        }

        // Time stattistics
        if (timeMeasure == kAsiTrue) {
                asi_setcfgstring (config, "ASISAMPLE", "ElapseTime", "Yes");
        } else {
                asi_setcfgstring (config, "ASISAMPLE", "ElapseTime", "No");
        }

        asi_destroy_cfg (&config);

        return;


}

/***********************************************************************
    This function is called to load external functions into AutoLISP.
    It also initializes asi application and reads program settings
    from the ASISAMPLE section in the Registry.
***********************************************************************/
static int loadfuncs ()
{
    short i = sizeof(cmd) /
              sizeof(CMDRX);          /* Number of functions */


    /* Initialize Asi application */
    if (asi_initasi (&appl) == kAsiBad) {
       ads_printf ("\nCannot initialize ASI");
       return RSERR;
    }

    /* Display ASI version */
    asi_version (appl, buff, 128);
    ads_printf ("\n%s", buff);
    ads_printf ("\n--------------------------------------\n");

    readSettings ();           /* Read ASISAMPLE section from the registry */

    while (i--)                       /* For every function from cmd */
    if (ads_defun(cmd[i].cmdname, i) != RTNORM)
        return RSERR;                 /* Wrong function definition */

    return RSRSLT;                    /* All functions were defined right */
}                                     /* End of loadfunc () */


/****************************************************************************
    This function is called to unload external functions into AutoLISP.
****************************************************************************/
static int unloadfunc ()
{
    short i = sizeof(cmd) /
              sizeof(CMDRX);          /* Number of functions */

    writeSettings ();                 /* Write settings to registry */

    if (asi_termasi (&appl) == kAsiBad) {     /* Terminate ASI */
       /* Application cannot be terminated. (For example if session was not
          terminated). Print diagnostics info and abort ASI nevertheless */
       if (appl != 0) {
          /* Avoid passing appl handle to print_diag if appl is NULL.
             asi_termasi can return kAsiBad if appl was NULL */
          print_diag (appl);      /* Print diagnostics */
          asi_abortasi (&appl);   /* Abort ASI */
       }
    }
    while (i--)                       /* For every function from cmd */
    if (ads_undef(cmd[i].cmdname, i) != RTNORM)
        return RSERR;                 /* Wrong function definition */

    return RTNORM ;                    /* All functions were defined right */
}                                     /* End of unloadfunc () */

/****************************************************************************
    This function is called to start external function.
****************************************************************************/
static int execfunc ()
{
    int i = ads_getfuncode ();        /* Function number */

    ads_retvoid ();                   /* command returns void */
    if (i == RTERROR)
        return RSERR;                 /* Error */

    (cmd[i].cmdfunc)();               /* Call function */

    return RSRSLT;                    /* OK */
}                                     /* End of execfunc () */


/****************************************************************************/
/*  ENTRY POINT INVOKED BY Arx                                              */
/****************************************************************************/
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg,  void * pAppid)
{
    switch(msg) {
    case AcRx::kInitAppMsg:     // Sent when Arx Application is loaded.
        // allow application unloading
        if ( pAppid != NULL ) {
            acrxDynamicLinker->unlockApplication(pAppid) ;
        }

        break;                  //   except for list of functions not
                                //   related to drawing state or LISP.
                                //   Detailed List of ADS functions
                                //   valid at this point forthcoming.
    case AcRx::kLoadADSMsg:     // Sent at same time
        loadfuncs();            // ADS Apps receive RQXLOAD code, i.e.
        break;                  // once per drawing Open. At this time
                                // you call:
                                //
                                // - All ADS Library functions are now
                                //   valid including
                                //   ads_defun(), ads_regfunc() , and
                                //   drawing access functions are now
                                //   operational.  Usage of them
                                //   automatically registers an Rx
                                //   application with the ADS
                                //   environment, so that LISP and
                                //   ADS can dispatch their calls
                                //   to this application.

    case AcRx::kUnloadADSMsg:
        unloadfunc ();
        break;                  // Sent at same time when ADS Apps
                                // receive RQXUNLD code.  App will
                                // not be unloaded, but signals that
                                // a drawing is being closed.
                                // - Cleanup and release for all
                                //   DWG and LISP related resources.
                                // - Last time in drawing edit session
                                //   that all ADS functions are valid.

    case AcRx::kInvkSubrMsg:
        execfunc ();            /* Call function */

        break;                  // Sent when RQSUBR is sent to ADS apps
                                //
                                // NOTE: Arx facilities and new Arx App
                                //       libraries all define direct
                                //       callback mechanisms.  This
                                //       message code is strictly for
                                //       ads_defun  compability.

    case AcRx::kSaveMsg:        // Sent when RQSAVE is sent to ADS apps
        break;

    case AcRx::kEndMsg:         // Sent when RQEND is sent to ADS apps
        break;

    case AcRx::kQuitMsg:        // Sent when RQQUIT is sen to ADS apps
        break;

    case AcRx::kCfgMsg:         // Sent when RQCFG is sent to ADS apps
        break;                  // Not yet implemented.

    case AcRx::kUnloadAppMsg:
        break;                  // The Arx Application is being unloaded.
                                // Free remaining resources registered
                                // with Rx.
                                //
                                // At this point, LISP and the drawing
                                // may or may not be long gone, and
                                // related ADS functions will no
                                // longer be valid.
                                //
                                // Perform all related cleanup in
                                // kUnloadADSMsg case.
    default:
        break;
    }
    return AcRx::kRetOK;
}

/*EOF*/

