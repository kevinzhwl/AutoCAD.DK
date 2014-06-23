/* Next available MSG number is   1 */
/*
      .
   Copyright (C) 1997 by Autodesk, Inc.
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

/* ========= cmdcount.cpp:  AutoCAD Command and LISP expression counter	& timer

    This program counts the number of times each AutoCAD command, AcEd-registered
    command, or unique LISP expression through its first white space, is invoked,
    and records it in a file named whatever STAT_FILENAME is defined to
    below, along with the elapsed time in seconds spent in each command.

    Note that elapsed time is recorded to 0.1 second, and additional invocation
    times are truncated to 0.1 second.  In theory, this program is measuring
    human interactive time, for which 0.1 second precision should suffice.
    
    It attempts to find the stat file on the %ACAD% path, and if it cannot,
    will attempt to create the stat file in the same directory as ACAD.EXE (again,
    the first occurence of such on the %ACAD% path).  If it cannot find ACAD.EXE,
    it will create the stat file in the current working directory.

*/

/*	Notes on modifications made subsequent to program's creation

  STAT_FILENAME_VERSION = 1.0 of STAT_FILENAME:

  v01.0
  Created:				 [date]
  Last modified:		 [date]
  AUTOCad serial number: [###-########]
  [Command name]		[Hits]		[Total elapsed time, to 1/100 seconds]
  ...					...			...

  =======================

  STAT_FILENAME_VERSION = 1.1 of STAT_FILENAME:

  v01.1
  Created:				 [date]
  Last modified:		 [date]
  LOGINNAME:			 [LOGINNAME]
  AUTOCad serial number: [###-########]
  [Command name]		[Hits]		[Total elapsed time, to 1/100 seconds]
  ...					...			...

  Write STAT_FILE to location of ACAD_NT_CFG or ACAD_CFG, if they can be found.
  (They should be in the path specified by the system variable ACADCFG,
  which is not necessarily on the ACAD search path.
  statFileName is now <LOGINNAME>.txt, where LOGINNAME is set by each user
  at initial configuration, or using "config" from the command prompt.

  ========================

  STAT_FILENAME_VERSION = 1.2 of STAT_FILENAME:

  v01.2
  Created:				 [date]
  Last modified:		 [date]
  LOGINNAME:			 [LOGINNAME]
  AutoCAD serial number: [###-########]
  AutoCAD version:	     [S.0.37, for example]
  [Command name]		[Hits]		[Total elapsed time, to 1/100 seconds]
  ...					...			...

  Also, write accumulated statistics after each SAVE, SAVEAS, WBLOCK,
  and AUTOSAVE, using AcEditorReactor's member functions.

*/

#include  <stdio.h>
#include  <stdlib.h>

#include "adslib.h"
#include "rxobject.h"
#include "rxdict.h"
#include "rxkernel.h"
#include "rxditer.h"

#include "aced.h"
#include "adesk.h"
#include "dbmain.h"
#include "dbsymtb.h"
#include "dbidmap.h"
#include "dbents.h"
#include "dbidar.h"
#include "string.h"


extern "C" {
// locally defined entry point invoked by Rx.
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);
}


// Forward declarations

class CommandReactor;
void updateCumulativeStats();

//********* CommandRecord --  Simple AcRxObject stored in stat dictionaries
//                            to maintain statistics.

class CommandRecord : public AcRxObject {

  public:
    int count;
    double elapsedTime;     // Including tenths of seconds.

    CommandRecord(int initialCount, double initialTime);
};

CommandRecord::CommandRecord(int initialCount, double initialTime)
  : count(initialCount),
    elapsedTime(initialTime)
{  }


//********* Defined values

#define ACAD_EXEC_NAME			"acad.exe" // Unless the user outsmarts us
                                           // and renames it...
#define ACAD_NT_CFG_NAME		"acadnt.cfg"
#define ACAD_CFG_NAME			"acad.cfg"
#define ACAD_INI_NAME			"acad.ini"
#define MAX_PATH_LENGTH			512   // based on ads_findfile() documentation

/* maximum length of recorded command strings and LISP expressions.
   Should suffice for commands of most languages, but beware of Kelvinated
   (or otherwise compressed) LISP files.  We truncate strings that aren't
   turally broken by this length. */
#define MAX_CMD_LENGTH			60
#define DATE_TIME_LENGTH		40    // More than enough for date/time string
#define SECONDS_PER_DAY			86400 // Number of seconds in a day
#define STAT_FILENAME_VERSION	1.2   // Version of statistics file format
#define VERSION_LENGTH			5     // Length of version string
#define LOGINNAME_LENGTH		10    // Length of LOGINNAME that we use.

//********* Static Structures

CommandReactor* cmdr = NULL;         // Gets notification of command and LISP
                                     // evaluation events.  Always in use.

AcRxDictionary* sessionStats = NULL; // Running statistics for this AutoCAD
                                     // session, or since last query.
                                     // Always in use.

AcRxDictionary* cumulativeStats = NULL;
                                     /* Cumulative Invocation counts.  All
                                        queries of cumulative stats are
                                        preceded by a merge, and resetting
                                        of session stats.  Active only
                                        during query and update operations.
                                        NULL otherwise. */


//********* CommandReactor --  Command Event Notification class

class CommandReactor : public AcEditorReactor {

  public:

    virtual void commandWillStart(const char * cmdStr);
    virtual void commandEnded(const char * cmdStr);
    virtual void commandCancelled(const char * cmdStr);
    virtual void commandFailed(const char * cmdStr);

    virtual void lispWillStart(const char * firstLine);
    virtual void lispEnded();
    virtual void lispCancelled();

    virtual void beginSave(AcDbDatabase* pDwg, const char* pIntendedName);

    virtual void beginWblock(AcDbDatabase* pTo,
                             AcDbDatabase* pFrom,
                             const AcGePoint3d*& insertionPoint);
    virtual void beginWblock(AcDbDatabase* pTo,
                             AcDbDatabase* pFrom,
                             AcDbObjectId blockId);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom);

};


// BUMPcOUNT:  common guts for commands and lisp expressions. Returns pointer
//             to affected CommandRcd, for use by caller.

CommandRecord* bumpCount(const char* cmdStr)
{
    CommandRecord* cmdRcd = (CommandRecord*) sessionStats->at(cmdStr);

    if (cmdRcd)
        cmdRcd->count++;
    else {
        // here is where we create the official command stat entry names, so
        // we apply da rules here:
        // 1)  Keep it short
        // 2) first blank or tab termintates the string.
        char truncatedStr[MAX_CMD_LENGTH + 1];
        if (strlen(cmdStr) > MAX_CMD_LENGTH) {
            strncpy(truncatedStr, cmdStr, MAX_CMD_LENGTH);
            truncatedStr[MAX_CMD_LENGTH] = EOS;   // Not all implementations
                                                  //  of strncpy() add the 
                                                  // EOS.
	} else
	    strcpy(truncatedStr, cmdStr);
	// Truncate string at first blank or tab.
	char* blankChar = strchr(truncatedStr, ' ');
	if (blankChar)
	    *blankChar = EOS;
    /* Now look for a TAB character. If you have detabbed the file,
       the character in the quote probably needs fixing. */
	blankChar = strchr(truncatedStr, '	');
	if (blankChar)
	    *blankChar = EOS;
	    
        // Put in dictionary, with a count of one.
        sessionStats->atPut(truncatedStr, cmdRcd = (new CommandRecord(1, 0)));
    }

    return cmdRcd;
}


// GETcURtIME:  return double representing Julian Date, values of which
//              may be directly subtracted for elapsed time measurement.
double getCurTime()
{
    resbuf currentTime;

    if (ads_getvar("DATE", &currentTime) != RTNORM)
        // This should never happen.
        acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
    return currentTime.resval.rreal;
}

// ELAPSEDtIMEiNsECONDS:
//               return an integer indicating number of elased time in
//               seconds between input startTime and endTime, which are
//               assumed to represent Julian dates, as described in
//               Autodesk Customization guides, as the "DATE" variable format
//               as opposed to "CDATE" format.
//
double elapsedTimeInSeconds(double endTime, double startTime)
{
    return ((endTime - startTime) * SECONDS_PER_DAY);
}

static int            cmdIndex = 0;   // To handle "nested" commands
#define MAX_CMD_DEPTH 5               // Max combination I think we now
                                      // support is 3 (main->dim->xparent),
                                      // so this is playing it safe.

static CommandRecord* cmdRcd[MAX_CMD_DEPTH];
static double         cmdStartTime[MAX_CMD_DEPTH];
static CommandRecord* lispRcd = NULL;
static double         lispStartTime;

// create date for cumulative file
static char           createDate[DATE_TIME_LENGTH + 1];
// Name of stat file.  "+5" means one for EOS, four for .txt
static char           statFileName[LOGINNAME_LENGTH + 5];


// Indicates that a SAVE/WBLOCK has occurred, which we take as a signal to
// save the stats file also, after waiting for active commands to finish up
// JMC
static Adesk::Boolean bStatsFileUpdatePending = Adesk::kFalse;

void CommandReactor::commandWillStart(const char* cmdStr)
{
    cmdRcd[cmdIndex] = bumpCount(cmdStr);
    cmdStartTime[cmdIndex++] = getCurTime();
}

void recordElapsedCmdTime(CommandRecord*& commandRecord, double startTime)
{
    commandRecord->elapsedTime += elapsedTimeInSeconds(getCurTime(),
                                                       startTime); 
}

void recordCommandDuration()
{
    if (cmdIndex > 0 ) {
        cmdIndex--;
        recordElapsedCmdTime(cmdRcd[cmdIndex], cmdStartTime[cmdIndex]);

        // Active command stack has been fully popped and we have a pending
        // statistics file update?
        if ((cmdIndex == 0) && (bStatsFileUpdatePending))  {
           /* We have completed an operation such as SAVE or WBLOCK since
              this command began, and this is a convenient time to update the
              stats file with the current counts.  This must be marked pending
              and done after command completion because cmdRcd[] points to a
              CommandRecord object in *sessionStats which is deleted in
              updateCumulativeStats()called below.  JMC */
            ::updateCumulativeStats();
            delete cumulativeStats;
            cumulativeStats = NULL;
            bStatsFileUpdatePending = Adesk::kFalse;
        }
    }  // else, the app was probably just loaded via ARX Command, i.e. it
       // woke up in mid-command.
}

// Note that we COULD verify the string input to these "end of command/lisp"
// against the string passed into the "balancing" xxxWillStart() call, but
// there is no known reason why they wouldn't be, short of corrupted memory.
// So we assume our cmdRcd and lispRcd static pointers are being accurately
// maintained.

void CommandReactor::commandEnded(const char*)
{
    recordCommandDuration();
}

void CommandReactor::commandCancelled(const char*)
{
    recordCommandDuration();
}

void CommandReactor::commandFailed(const char*)
{
    recordCommandDuration();
}

void CommandReactor::lispWillStart(const char* firstLine)
{
    lispRcd = bumpCount(firstLine);
    lispStartTime = getCurTime();
}

void CommandReactor::lispEnded()
{
    if (lispRcd != NULL)
        recordElapsedCmdTime(lispRcd, lispStartTime); 
}

void CommandReactor::lispCancelled()
{
    if (lispRcd != NULL)
        recordElapsedCmdTime(lispRcd, lispStartTime); 
}

void CommandReactor::beginSave(AcDbDatabase* pDwg, const char* pIntendedName)
{
    bStatsFileUpdatePending = Adesk::kTrue; // Set pending flag for update
                                            // in recordCommandDuration() JMC
}

void CommandReactor::beginWblock(      AcDbDatabase* pTo,
                                       AcDbDatabase* pFrom,
                                 const AcGePoint3d*& insertionPoint)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

void CommandReactor::beginWblock(AcDbDatabase* pTo,
                                 AcDbDatabase* pFrom,
                                 AcDbObjectId blockId)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

void CommandReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    bStatsFileUpdatePending = Adesk::kTrue; // JMC
}

//********* Utility Functions

// cmdcount_findfile: return int representing whether file was found (RTNORM)
//                    or not. Looks in the directory where .cfg/.ini files
//                    live. If it doesn't find the file there, it looks along
//                    the AutoCAD search path, according to ads_findfile().
int cmdcount_findfile (const char *fname, char *result)
{
	char statFilePath[MAX_PATH_LENGTH];

	if (ads_getenv("ACADCFG", statFilePath) != RTNORM)
		acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
	if (statFilePath[strlen(statFilePath) - 1] != '\\') 
		strcat(statFilePath, "\\");
	strcat(statFilePath, fname);
	if (fopen(statFilePath, "r") != NULL) {
		strcpy(result, statFilePath);
		return RTNORM;
	}
	else 
		return ads_findfile(fname, result);
}

// INITsTATdICTIONARY:  create a dictionary that will delete its content
//                      objects when it is deleted.
AcRxDictionary* initStatDictionary() {
    return acrxKernel->newAcRxDictionary(0, Adesk::kTrue);
}

// READcUMULATIVEsTATS: Read ACCOUNT.TXT into the cumulativeStats dictionary
//                      or if that can't be done, return an empty dictionary.
Adesk::Boolean readCumulativeStats()
{
    // If we got any hanging around, get rid of 'em.
    if (cumulativeStats)
        delete cumulativeStats;

    cumulativeStats = initStatDictionary();

    // Open the file
    FILE* statFile = NULL;
    char statFilePath[MAX_PATH_LENGTH];

    if (cmdcount_findfile(statFileName, statFilePath) == RTNORM)
        // find it, open it
        statFile = fopen(statFilePath, "r");
    else {
        *createDate = NULL;
        return Adesk::kFalse; // Most likely, it hasn't been created yet.
                              // one other likely reason is 
                              // that another process has it open for write,
                              // but we're talkin' a millisecond window...
    }

    char cmdName[MAX_CMD_LENGTH + 1 /*for the EOS*/ ];
    int cmdCount;
    double cmdElapsedTime;

    char dummyString[DATE_TIME_LENGTH + 1];

    char versionString[VERSION_LENGTH + 1];
    
    // Read line containing STAT_FILENAME_VERSION
    fscanf(statFile, "%s", versionString);
    if (  (  (versionString[1] - '0') * 10.0
           + (versionString[2] - '0')
           + (versionString[4] - '0') / 10.0)
        != STAT_FILENAME_VERSION) {
   
        // Whoops, you've got an old version of the statfile...
        ads_printf("\nWarning: Incompatible version of STATFILE.\n");
        fclose(statFile);
        return Adesk::kFalse;
    }
   
    // Read line containing Date File Created
    fscanf(statFile, "\n%[^\n]", createDate);

    // Read line containing Date File Last Modified
    fscanf(statFile, "\n%[^\n]", dummyString);

    // Read line containing LOGINNAME
    fscanf(statFile, "\n%[^\n]", dummyString);
    
    // Read line containing AutoCAD serial number
    fscanf(statFile, "\n%[^\n]", dummyString);

    // Read line containing AutoCAD version
    fscanf(statFile, "\n%[^\n]", dummyString);
    fscanf(statFile, "%[\n]", dummyString);
       
    while (fscanf(statFile, "%s %i %le", cmdName, &cmdCount, &cmdElapsedTime)
           != EOF) {
        if (cumulativeStats->atPut(cmdName,
                                   new CommandRecord(cmdCount,
                                   cmdElapsedTime)))
            // Shake 'em up a little, but don't die over it.
            // But hell, this suggests sabatoge or stupidity...
            ads_printf("\nCommand Statistics Error 1:  Duplicate Entry.\n");
    }
    fclose(statFile);
    return Adesk::kTrue;
}

void printCurrentDateTime(FILE* statFile)
{
    resbuf tempRes;
    int jtd_day;
    double jtd_msec;
    int ctd_year, ctd_month, ctd_day, ctd_hour, ctd_minute, ctd_second;
    double rem;
    long t, j, y, d;

    // Get Julian date and convert it to calendar time and date
    // As in Calendar Time and Date, in case you were wondering what
    // the "ctd_" prefix used pervasively in this routine stands for.
    if (ads_getvar("DATE", &tempRes) != RTNORM)
        acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 2");
    jtd_day = (int)tempRes.resval.rreal;
    jtd_msec = tempRes.resval.rreal - (int)tempRes.resval.rreal;
    j = jtd_day - 1721119L;
    t = 4 * j - 1;
    y = t / 146097L;
    j = t - 146097L * y;
    d = j / 4;
    j = (4 * d + 3) / 1461;
    d = (4 * d - 1461L * j + 7) / 4;
    ctd_month = (5 * d - 3) / 153;
    ctd_day = ((5 * d) - 3 - 153 * ctd_month + 5) / 5;
    ctd_year = (short)((100 * y) + j);
    if (ctd_month >= 10) {
        ctd_month -= 9;
        ctd_year++;
    } else
        ctd_month += 3;

    ctd_hour = (short)(jtd_msec * 24);
    rem = (jtd_msec * 24) - ctd_hour;
    ctd_minute = (short)(rem * 60);
    rem = (rem * 60) - ctd_minute;
    ctd_second = (short)(rem * 60);
    
    // print current date and time
    fprintf(statFile, "%0*d/%0*d/%0*d %0*d:%0*d:%0*d", 
            2, ctd_month,
            2, ctd_day,
            4, ctd_year,
            2, ctd_hour,
            2, ctd_minute,
            2, ctd_second);
}

void updateCumulativeStats()
{
    if (!readCumulativeStats()) {
        ads_printf("\nWarning: Could not find Command Statistics file.\n");
        ads_printf("Will try to create it.\n");
    }

    AcRxDictionaryIterator* iter;

    // Loop over current session stats, and merge them into cumulative stats.
    for (iter = sessionStats->newIterator(); !iter->done(); iter->next()) {
        CommandRecord* sessionCmdRcd = (CommandRecord*) iter->object();
        CommandRecord* cumulativeCmdRcd = (CommandRecord*)
                                          cumulativeStats->at(iter->key());
        if (!cumulativeCmdRcd)
            // First time, add it.
            cumulativeStats->atPut(iter->key(),
                                   new CommandRecord(sessionCmdRcd->count,
                                                     sessionCmdRcd->elapsedTime));
        else {
            // Not the first time, so bump it.
            cumulativeCmdRcd->count += sessionCmdRcd->count;
            cumulativeCmdRcd->elapsedTime += sessionCmdRcd->elapsedTime;
        }
    }

    delete iter;

    // Now that it has been added in, wipe out the current session Stats;
    delete sessionStats;
    sessionStats = initStatDictionary();

    // Open the cumulative stat file, creating it if necessary.
    char statFilePath[MAX_PATH_LENGTH];

    if (cmdcount_findfile(statFileName, statFilePath) != RTNORM) {
        // The file wasn't found.  Let's create it in the same directory as
        // acadnt.cfg first. If that fails, try the directory of 
        // acad.cfg. If that also fails, try the directory of
        // acad.exe.  If the user was clever enough to rename acad.exe,
        // then use the current working directory.
        if (cmdcount_findfile(ACAD_NT_CFG_NAME, statFilePath) == RTNORM) {
            // Found it. Truncate the acadnt.cfg and add in our filename
            statFilePath[strlen(statFilePath)-strlen(ACAD_NT_CFG_NAME)] = EOS;
        } else if (cmdcount_findfile(ACAD_CFG_NAME, statFilePath) == RTNORM) {
            // Found it. Truncate the acad.cfg and add in our filename
            statFilePath[strlen(statFilePath)-strlen(ACAD_CFG_NAME)] = EOS;
        } else if (ads_findfile(ACAD_EXEC_NAME, statFilePath) == RTNORM) {
            // Found it.  Truncate the acad.exe, and add in our filename
            statFilePath[strlen(statFilePath)-strlen(ACAD_EXEC_NAME)] = EOS;
        } else {
            // Create it in the CWD
            statFilePath[0] = EOS;
            strcat(statFilePath, ".\\");
        }
        strcat(statFilePath, statFileName);
    }

    // Open the file
    FILE* statFile = fopen(statFilePath, "w");

    if (statFile == NULL) {
        // Bad permission in our chosen directory.  Give up.
        ads_alert("Warning: Could not create Command Statistics file.");
        return;
    }

    // Print version number of STATFILE
    fprintf(statFile, "v%04.1f\n", STAT_FILENAME_VERSION);

    // Print create date of STATFILE
    if (!*createDate) {
        fprintf(statFile, "Created:               ");
        printCurrentDateTime(statFile);
        fprintf(statFile, "\n");
    } else
        fprintf(statFile, "%s\n", createDate);

    // Print date last modified for STATFILE
    fprintf(statFile, "Last Modified:         ");
    printCurrentDateTime(statFile);
    fprintf(statFile, "\n");

    resbuf tempRes;
    // Print LOGINNAME
    if (ads_getvar("loginname", &tempRes) != RTNORM)
        acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
    fprintf(statFile, "LOGINNAME:             %s\n", tempRes.resval.rstring);

    // Print ACAD serial number
    if (ads_getvar("_pkser", &tempRes) != RTNORM)
        acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
    fprintf(statFile, "AutoCAD Serial Number: %s\n", tempRes.resval.rstring);

    // Print ACAD version
    if (ads_getvar("_vernum", &tempRes) != RTNORM)
        acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
    fprintf(statFile, "AutoCAD version:       %s\n", tempRes.resval.rstring);

    for (iter = cumulativeStats->newIterator(); !iter->done(); iter->next()) {
        // Write out the command string.
        fprintf(statFile, "%s", iter->key());

        // Try for reasonable text alignment, such as allowing 24 chars
        // for the command name.  But have at least 1 space as a delimiter.
        int nbrOfSpaces = 24 - strlen(iter->key());
        do
            fprintf(statFile, " ");
        while (--nbrOfSpaces > 0);

        // Now the count and elapsed time in seconds (assume 1 billion seconds
        // maximum, which should exceed a typical beta survey period).
        fprintf(statFile, "%7i   %12.2f\n",
                ((CommandRecord*) iter->object())->count,
                ((CommandRecord*) iter->object())->elapsedTime);
    }

    fclose(statFile);

    delete iter;
}

void printStats(AcRxDictionary* statDict) {
    AcRxDictionaryIterator* iter;
    
    ads_printf("\n\nCommand                 Count     Elapsed Time\n");
    ads_printf("----------------------  -------   ----------\n");
    for (iter = statDict->newIterator(); !iter->done(); iter->next()) {
        // Write out the command string.
        ads_printf("%s", iter->key());

    // Try for a little reasonable text alignment,
    // assuming 24 characters for a command or lisp name is sufficient.
    // But, we'll go to the MAX_CMD_LENGTH, plus one blank, if we must.
    int nbrOfSpaces = 24 - strlen(iter->key());
    do
        ads_printf(" ");
    while (--nbrOfSpaces > 0);

        // Now the count, plus elapsed time, in primate-comprehensible form.
    int TempElapsedTime = (int)
                          (((CommandRecord*) iter->object())->elapsedTime);
    int hours = TempElapsedTime / 3600;
    int minutes = (TempElapsedTime % 3600) / 60;
    ads_printf("%7i   %4d:%0*d:%0*.*f\n",
               ((CommandRecord*)iter->object())->count,
               hours,
               2, minutes,
               5, 2,
               ((CommandRecord*) iter->object())->elapsedTime
			   - (hours * 3600) - (minutes * 60));
		   
    }

    delete iter;
}


void commandStats() {

    char option_str[132];

    // specific prompt.
    ads_initget(0, "Cumulative Session");

    option_str[0] = 'S';
    option_str[1] = '\0';

    switch (ads_getkword("\nCumulative/<Session>:", option_str)) {
        case RTKWORD:
            ads_getinput(option_str);
        /* Deliberate fallthrough */
        default:
            break;
    } 

    if (((option_str[0] == 'C') || (option_str[0] == 'c'))) {
        updateCumulativeStats();
        ads_printf("\n\nCumulative Command Usage Statistics");
        printStats(cumulativeStats);
        ads_printf("\nNOTE: Session Statistics have been recorded and reset.\n");
        delete cumulativeStats;
        cumulativeStats = NULL;
    } else {
        ads_printf("\n\nCurrent Session Command Usage Statistics");
        printStats(sessionStats);
    }
}


//********* Main Functions & Session Control

// commandStats:  Print out current Session and Cumulative Stats
void initStats()
{
    cmdr   = new CommandReactor();
    cmdIndex = 0;

    // Define dictionary to delete all its entries when it is deleted.
    sessionStats = acrxKernel->newAcRxDictionary(0, Adesk::kTrue);
    acedEditor->addReactor(cmdr);
    acedRegCmds->addCommand("ACAD_COMMAND_STATS",
                            "CMDSTAT",
                            "CMDSTAT",
                            ACRX_CMD_TRANSPARENT,
                            &commandStats);
    // set the statFileName to be <LOGINNAME>.txt
    // remove blanks and tabs from LOGINNAME, so we have a more 
    // reasonable statFileName.
    resbuf tempRes;
    int i, j;
    if (ads_getvar("LOGINNAME", &tempRes) != RTNORM)
    acrx_abort("AutoCAD Command\nStatistics Gatherer\nFailure 1");
    statFileName[0] = EOS;
    strcat(statFileName, tempRes.resval.rstring);
    for (i = 0, j = 0;
         (statFileName[i] != EOS) && (j < LOGINNAME_LENGTH);
         i++) {
        if ((statFileName[i] != ' ') && (statFileName[i] != '\t')) {
            statFileName[j] = statFileName[i];
            j++;
        }
    }
    statFileName[j] = EOS;
    strcat(statFileName, ".txt");
}

void termStats()
{
    // Add 'em in, if you can.
    updateCumulativeStats();

    acedEditor->removeReactor(cmdr);
    delete cmdr;
    
    acedRegCmds->removeGroup("ACAD_COMMAND_STATS");
}


/* =================== Arx Interface Functions ================ */

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void*) {
    switch(msg) {
        case AcRx::kInitAppMsg:
            initStats();
            break;
        case AcRx::kUnloadAppMsg:
            termStats();
        default:
        break;
    }
    return AcRx::kRetOK;
}
