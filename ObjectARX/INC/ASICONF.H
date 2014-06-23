/*****************************************************************************
   Name: asiconf.h

   Description:  Windows initialization file and asi configuration file classes

   Copyright (C) 1991-1997 by Autodesk, Inc.

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

*****************************************************************************/
#ifndef ASI_ASICONF_HH
#define ASI_ASICONF_HH asiconfhh

/* //////////////////////////////////////////////////////////////////////// */
/* */
/* TYPEDEFS */
/* */
/* //////////////////////////////////////////////////////////////////////// */
#if defined(__cplusplus)

#ifndef REG_ASIINI
#  define     REG_ASIINI        "Software\\Autodesk\\AutoCAD\\R14.0\\AST"
#endif

//class CAsiList;

class CAsiWinIni: public CAsiObject
// This class allows to get access to the windows initialization file
//
//
//  CAsiWinIni (const CAsiUcStr &fname)
//
//  Description
//
//   Constructs a windows initialization file object. Windows initialization
//   file name is passed to constructor. File is located on disk according
//   to rules used to locate any AutoCAD (ASI) system file.
//
//
//   int openCfgFile (const CAsiUcStr & section)
//
//  This function reads data from the Windows initialization file.
//  It allows to read all entries of the specified section.
//  These function stores entry  names and corresponding value into
//  internal selection set of entries.
//  Entry name and value can be retrieved from it by means of getEntry
//  member function.
//
//  Parameters
//
//    section   section name containing an entry
//
//  Return Value
//
//    Number of entried read. 0 if there are no enties.
//
//   EAsiBoolean readCfgString (const CAsiUcStr & section,
//                              const CAsiUcStr & entry,
//                  CAsiUcStr * )
//
//  This function reads data from the Windows initialization file.
//  It allows to read value of specified entry. These function stores entry
//  names and corresponding value into internal selection set of entries.
//
//
//  Parameters
//
//    section   section name containing an entry
//
//    entry     name of entry whose associated string is to be retrieved.
//
//  Return Value
//
//    kAsiTrue if succeded and kAsiFalse otherwise
//
//
//   EAsiBoolean getEntry (int item,
//                         CAsiUcStr *entry,
//                         CAsiUcStr *value)
//
//   This functions retieves entry name and its value from the entries
//   selection set
//
//
//   EAsiBoolean writeCfgString (const CAsiUcStr &section,
//                               const CAsiUcStr &entry,
//                               const CAsiUcStr &value)
//
//   Description
//
//  This function copies a string into the specified entry of the
//  Windows Initialization File.
//  If Windows Initialization file doesn't exist, it is created in the
//  current directory. If specified section doesn't exist, it is created.
//  If specified entry doesn't exist in specified section, it is created.
//  If the value string is void (length of data equal to 0), the specified
//  entry is deleted.  If the last entry in section was deleted, then container
//  section is also deleted.
//
//
//   Parameters
//
//    section  section name to which the string is to be copied.
//
//    entry    entry name which have to be modified.
//
//    str      Value to be associated with the entry in file.
//
//
//  Return Value
//
//    kAsiTrue if succeded and kAsiFalse otherwise
//
//
//
{
public:
    // Constrcution/Destrcution
    //
             CAsiWinIni (const CAsiUcStr &cfgname);
             CAsiWinIni (const char *);
    virtual ~CAsiWinIni (void);

    // Read/Write configuration file entry
    //
virtual       int           openCfgFile (const CAsiUcStr &);
virtual       int           openCfgFile (const char *);

virtual       EAsiBoolean readCfgString (const CAsiUcStr &,
                                         const CAsiUcStr &,
                                         CAsiUcStr * );
virtual       EAsiBoolean readCfgString (const char *,
                                         const char *,
                                         CAsiUcStr * );


virtual       EAsiBoolean getEntry      (int,
                                        CAsiUcStr *,
                                        CAsiUcStr *);


virtual      EAsiBoolean writeCfgString (const CAsiUcStr &,
                                         const CAsiUcStr &,
                                         const CAsiUcStr &);
virtual      EAsiBoolean writeCfgString (const char *,
                                         const char *,
                                         const char *);

protected:

       CAsiUcStr        FileName;   // Config file object
       ulong            LupTimeL;   // First part of Time of least file modification
       ulong            LupTimeH;   // Second part of Time of least file modification
       CAsiObject       *Sections;  // Sections
       CAsiObject       *Strings;   // Strings of the file
       int              cursect;    // Current section in list of section

};


class CAsiConfigOld : public CAsiWinIni
//
// This class allows to get access to the ASI configuration file (asi.ini).
// This class is derived from the CAsiWinIni class.
//
//
// EAsiBoolean createEnv (const CAsiUcStr &env, const CAsiUcStr &drv)
//
// This function creates environment section in the AST configuration
// file. Created environment will be driven by the specified DBMS driver,
// which description shall be present in the configuration file.
//
//  Return value
//
//  kAsiFalse if environment can't be created. kAsiTrue after successful
//  complition.
//
//
//  EAsiBoolean dropEnv   (const CAsiUcStr &env)
//
// This function drops environment section from the asi.ini file.
//
// If environment cannot be droped, kAsiFalse is returned.
//
//
{
public:
    // Constrcution/Destrcution
    //

             CAsiConfigOld (void);
    virtual ~CAsiConfigOld (void);

    // Read/Write asi.ini configuration file entry
    //
virtual       int           openCfgFile (const CAsiUcStr &);
virtual       int           openCfgFile (const char *);

virtual       EAsiBoolean readCfgString (const CAsiUcStr &,
                                        const CAsiUcStr &,
                                        CAsiUcStr * );
virtual       EAsiBoolean readCfgString (const char *,
                                         const char *,
                                         CAsiUcStr * );

virtual       EAsiBoolean getEntry      (int,
                                        CAsiUcStr *,
                                        CAsiUcStr *);

virtual      EAsiBoolean writeCfgString (const CAsiUcStr &,
                                         const CAsiUcStr &,
                                         const CAsiUcStr &);
virtual      EAsiBoolean writeCfgString (const char *,
                                         const char *,
                                         const char *);


    // Create/Drop environment section
    //
             EAsiBoolean createEnv (const CAsiUcStr &env, const CAsiUcStr &drv);
             EAsiBoolean createEnv (const char *, const char *);

             EAsiBoolean dropEnv   (const CAsiUcStr &env);
             EAsiBoolean dropEnv   (const char *);

};


/************************************************************/
/* CAsiRegValue                                             */
/************************************************************/
class CAsiRegValueList;

class CAsiRegValue
{
    friend class CAsiRegValueList;

public:
    CAsiRegValue();
    CAsiRegValue(char *, unsigned long, unsigned long, unsigned char *);
    ~CAsiRegValue();

private:
    char *value_name;
    unsigned long value_type;
    unsigned long value_size;
    unsigned char *value;
    CAsiRegValue *next;
};

/************************************************************/
/* CAsiRegValueList                                         */
/************************************************************/
class CAsiRegValueList
{
public:
    CAsiRegValueList();
    ~CAsiRegValueList();

    void AddValue(CAsiRegValue *);
    EAsiBoolean FindValue(CAsiUcStr *, const char *);
    EAsiBoolean FindValue(int, CAsiUcStr *, CAsiUcStr *);

private:
    CAsiRegValue *head;
};

/*********************************************************/
/* CAsiConfig                                            */
/*********************************************************/
class CAsiConfig : public CAsiWinIni
{
public:
    // Constrcution/Destrcution
    CAsiConfig(void);
    virtual ~CAsiConfig(void);

    // Read/Write asi.ini configuration file entry
    virtual int openCfgFile(const CAsiUcStr &);
    virtual int openCfgFile(const char *);

    virtual EAsiBoolean readCfgString(const CAsiUcStr &,
                                      const CAsiUcStr &,
                                      CAsiUcStr *);
    virtual EAsiBoolean readCfgString(const char *,
                                      const char *,
                                      CAsiUcStr *);

    virtual EAsiBoolean getEntry(int, CAsiUcStr *, CAsiUcStr *);

    virtual EAsiBoolean writeCfgString(const CAsiUcStr &,
                                       const CAsiUcStr &,
                                       const CAsiUcStr &);
    virtual EAsiBoolean writeCfgString(const char *,
                                       const char *,
                                       const char *);

    virtual EAsiBoolean writeCfgString(const CAsiUcStr &,
                                       const CAsiUcStr &,
                                       const CAsiUcStr &,
                                       const CAsiUcStr &);
    virtual EAsiBoolean writeCfgString(const char *,
                                       const char *,
                                       const char *,
                                       const char *);

    // Create/Drop environment section
    EAsiBoolean createEnv(const CAsiUcStr &env, const CAsiUcStr &drv);
    EAsiBoolean createEnv(const char *, const char *);
    EAsiBoolean createEnv(const CAsiUcStr &env, const CAsiUcStr &dsc, const CAsiUcStr &drv);
    EAsiBoolean createEnv(const char *, const char *, const char *);

    EAsiBoolean dropEnv(const CAsiUcStr &env);
    EAsiBoolean dropEnv(const char *);

protected:
    CAsiRegValueList *values;
};

#endif /* __cplusplus */

#endif /* ASI_ASICONF_HH */
/*EOF*/
