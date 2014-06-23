/*****************************************************************************
   Name: asiclass.h                           ast_asi_inc_appl_asiclass_h

   Description:  Header file for AutoCAD SQL Interface.
                 ASI C++ User Interface.

   Copyright 1991-1997 by Autodesk, Inc.

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
#ifndef ASI_ASICLASS_HH
#define ASI_ASICLASS_HH asiclasshh

///////////////////////////////////////////////////////////////////////////
// INCLUDES 
///////////////////////////////////////////////////////////////////////////
#include <asisdata.h>


///////////////////////////////////////////////////////////////////////////
// DEFINES 
///////////////////////////////////////////////////////////////////////////
#define ASI_TRY           { \
                            CAsiExceptionHandler AsiExceptionHandler; \
                            if ( ::setjmp(AsiExceptionHandler.jbBuffer) == 0 )
#define ASI_CATCH(x)      else { \
                            CAsiException* x = AsiExceptionHandler.pException;
#define ASI_END_CATCH     }}
#define ASI_THROW(x)      AsiExceptionThrow(x);
#define ASI_THROW_LAST    AsiExceptionThrow(0);


///////////////////////////////////////////////////////////////////////////
// FORWARD DEFINITIONS 
///////////////////////////////////////////////////////////////////////////

// ASI Class Hierarchy
//
class CAsiObject;                           // Superclass for all classes
    class CAsiIdent;                        // Identifier
    class CAsiData;                         // ASI Data generic class
        class CAsiNum;                      // Numeric data
        class CAsiExactNum;                 // Exact numeric data
            class CAsiSmallInt;             // Small Integer
            class CAsiInt;                  // Integer
            class CAsiNumeric;              // Numeric
            class CAsiDecimal;              // Decimal
        class CAsiApproxNum;                // Approximate numeric data
            class CAsiFloat;                // Float
            class CAsiReal;                 // Real
            class CAsiDouble;               // Double precision
        class CAsiChar;                     // Character
        class CAsiBinary;                   // Binary 
        class CAsiIQualifier;               // Interval qualifier
            class CAsiInterval;             // Interval
                class CAsiYM;               // Year month intervals
                class CAsiDT;               // Day Time intervals
        class CAsiDatetime;                 // Datetime data
            class CAsiDate;                 // Date
            class CAsiTime;                 // Time
            class CAsiTimeStamp;            // Timestamp
        class CAsiPoint;                    // Euclidean point
        class CAsiImplDef;                  // Implementation defined data

    class CAsiColumn;                       // Column definition
    class CAsiRow;                          // Array of columns
    class CAsiHostBuffer;                   // Host program buffer
        class CAsiParameter;                // Parameter desriptor
    class CAsiImplDefFunc;                  // Function
    
    // Class collections
    class CAsiIRow;                         // Array of data pointers
    class CAsiList;                         // List of CAsiObject's
  
    class CAsiException;                    // ASI Exception

    class CAsiSQLObject;                    // ASI User Interface base class
        class CAsiSession;                  // SQL Session
        class CAsiStm;                      // Generic SQL statement functionality
            class CAsiExecStm;              // Executable SQL statement
                class CAsiNativeStm;        // Native DBMS statement 
                class CAsiInterDBStm;       // InterDB statement
        class CAsiCsr;                      // Cursor

class CAsiUcStr;                            // Unicode string
class CAsiUcChar;                           // Unicode character
class CAsiExceptionHandler;                 // Exception handler
class CAsiCollation;                        // Collation

class CAsiObjPack;            // Communication buffer access

///////////////////////////////////////////////////////////////////////////
//     TYPEDEFS 
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
class CAsiExceptionHandler
// This class is used internaly to support asi exception handling 
// feature
{
public:
    // Constrution/destruction
    // 
    CAsiExceptionHandler(void);
    ~CAsiExceptionHandler(void);

    // Internal data for support TRY/CATCH
    // 
    CAsiException*        pException;
    CAsiExceptionHandler* pPrevHandler;
    jmp_buf               jbBuffer;
    EAsiBoolean           wasThrown;
};


//////////////////////////////////////////////////////////////////////
class CAsiException : public CAsiObject
//
// This class provides functionality of the SQL exception condition
// It is thrown by ASI member function when an exception condition was 
// raised. (ASI_TRY, ASI_CATCH, ASI_THROW facility).
//
{
public:
    // Constrution/destruction
    // 
            CAsiException (void);
    virtual ~CAsiException (void);

    // Getting Diagnostics Information   
    //
            int           CondQty    (void) const;       // Number of conditions in diag
            AsiError      Err        (int d = 0) const;  // get completion code
            CAsiUcStr    *ErrMsg     (int d = 0) const;  // get error message
            char         *SQLSTATE   (int d = 0) const;  // get SQLSTATE
  
            // Get Diagnostics Parameter
            //
            EAsiBoolean getDiagPar (int, AsiDiag, integer *) const;
            EAsiBoolean getDiagPar (int, AsiDiag, CAsiUcStr *) const;

     // Setting Diagnostics information

            EAsiBoolean setErr      (AsiError);           // set completion code
            EAsiBoolean setErrMsg   (const CAsiUcStr &);  // set error message
            EAsiBoolean setSQLSTATE (const char *);       // set SQLSTATE

            // Set Diagnostics Parameter
            //
            EAsiBoolean setDiagPar (AsiDiag, integer);
            EAsiBoolean setDiagPar (AsiDiag, const CAsiUcStr &);

        
            EAsiBoolean pushCond   (void);       // Push diagnostics information
            EAsiBoolean flushCond  (void);       // Clear diagnostics

    ////////////////////////////////////////////////////
    // Utility
    //
    void*       getDiagData (void) const;

    virtual CAsiObject * duplicate (void) const;         

private:
    void* pExceptionBody;
};





////////////////////////////////////////////////////////////////////////////////
class CAsiSQLObject : public CAsiObject
//
// This is a base class for classes that support SQL Connection-Session-
// Statement-Cursor functionality. It provides storage for the diagnostics 
// information generated by the derived classes.
// Besides diagnostics this class allows to get information about foreground
// DBMS driver, and the current ASI version.
//
// MEMBER FUNCTIONS
// ----------------
//
//  
// Getting Statement Information
//
// EAsiStatement StmType       (void) const    
// EAsiStatement CmdStmType    (void) const    
// long          RowCount      (void) const    
//
// These function retrieve SQL statement type, SQL Command statement type,
// number of rows affected by the <update:searched>, <delete: searched>, or 
// insert statements
//
//
// Syntax error position
//
// int ErrPosition   (void) const     
//
// Getting Diagnostics Information   
//
// int CondQty (void) const
//
// This function returns number of conditions stored in diagnostics area
// associated with the SQL object. Diagnostics area can hold several items
// belonging to the same or different conditions. Eash new condition in the
// diagnostics area introduces a new condition or clarifies a previouss one.
//
//
// EAsiError Err(
//   int icond) const       // Condition number
//
// This function returns error code associated with the condition specified 
// by its number. Condition codes are listed in the asiconst.h header file.
// If a wrong condition number was passed,  kAsiERUndefined is returned.
//
//
// CAsiUcStr *ErrMsg (
//   int icond) const       // Condition number
//
// This function returns pointer to the Unicode string object that contains
// message associated with specified condition. If invalid condition number 
// was specified, 0 is returned instead of it.
//
//
// char * SQLSTATE (
//   int icond) const       // Condition number
//
// This function returns pointer to the character ASCII string containing
// SQLSTATE diagnostics parameter associated with the specified condition.
// (SQLSTATE parameter is a 5 bytes null terminated charater string,
// consisting of class and subclass codes). If an invalid condition number
// was specified, NULL is returned instead of pointer.
//
//
// EAsiBoolean getDiagPar (int icond,              // Condition number
//     EAsiDiag pCode,         // Parameter code
//     integer *ivalue         // Integer parameter value
//    ) const
// EAsiBoolean getDiagPar (int icond,              // Condition number
//     EAsiDiag pCode,         // Parameter code
//     CAsiUcStr *ucvalue      // Character parameter value
//    ) const;
//
// These functions store value of diagnostics parameter specified by its
// code (pCode) for the specified condition into integer or Unicode 
// character string buffers. Return kAsiTrue if succeeded, or kAsiFalse 
// if an invalid condition number was specified.
//
// Parameters
//
// icond      Condition number
// pCode      Diagnostics parameter code
// ivalue     Destination for an integer value
// ucvalue    Destination for an Unicode character string
//
//
// Linked DBMS information
//
// The following functions allow to get information about DBMS driver 
// that maintains link between ASI application and DBMS server.
//
// EAsiBoolean DBMS (
//   CAsiUcStr & dbms         // DBMS Name
//  ) const    
//
// Stores DBMS name into Ucode string. Reference to the Unicode string 
// shall be provided by caller.
//
//
// EAsiBoolean SQLObject (
//   CAsiUcStr &objid         // SQL object identifier
//  ) const    
//
// Stores SQL object identifier into Ucode string. Reference to the destination
// Unicode string shall be provided by caller.
//
//
// EAsiBoolean DrvMessage (
//   CAsiUcStr &mess          // Driver message
//  ) const
//
// Stores driver message into Ucode string. Reference to the destination
// Unicode string shall be provided by caller.
//
//
// EAsiBoolean CheckOp (
//    ulong operation        // Operation codes
//   )                
//
// Return kAsiTrue if operations specified in the parameter are supported 
// by DBMS driver. Operation codes are a bit coded fields, that can be ored.
// kAsiFalse is returned if at least one operation is not supported.
//
//
// ASI version
//
// EAsiBoolean Version (
//    CAsiUcStr*             // Pointer for store ASI version string
//   ) const
//
// const char* Version (void) const
//
// Return pointer to the unocode string containing ASI version.
//
//
{
public:
    // Constrution/destruction
    // 
            CAsiSQLObject();
    virtual ~CAsiSQLObject();

    // Getting Statement Information
    //
            EAsiStatement StmType       (void) const;    // statement type
            EAsiStatement CmdStmType    (void) const;    // command stm type
            long          RowCount      (void) const;    // get row count

    // Syntax error position
            int           ErrPosition   (void) const;     

    // Getting Diagnostics Information   
    //
            int        CondQty     (void) const;       // Number of conditions in diag
            EAsiError  Err         (int d = 0) const;  // get completion code
            CAsiUcStr *ErrMsg      (int d = 0) const;  // get error message
            char      *SQLSTATE    (int d = 0) const;  // get SQLSTATE

            // Get Diagnostics Parameter
            //
            EAsiBoolean getDiagPar (int d,       // Integer condition
                                    EAsiDiag,
                                    integer *) const;
            EAsiBoolean getDiagPar (int d,       // character condition
                                    EAsiDiag,
                                    CAsiUcStr *) const;
            

    // Linked DBMS information
    //
            EAsiBoolean DBMS       (CAsiUcStr *) const;        // DBMS type
            EAsiBoolean SQLObject  (CAsiUcStr *) const;        // SQL object identifier
            EAsiBoolean DrvMessage (CAsiUcStr *) const;        // Driver message
            EAsiBoolean CheckOp    (ulong);                    // Check base operation
            EAsiBoolean GetStatus  (EAsiStatInfo, ulong *);    // Get check status

    //  ASI version
    //
            EAsiBoolean Version    (CAsiUcStr*) const;
            const char* Version    (void) const;

protected:
            EAsiBoolean isInit     (void) const;

protected:
    // Methods for setting diagnosticss information. It may just consist of
    // linking object with DDA.
    //
            ulong        objIdSes;     // Session id
            ulong        objIdStm;     // Statement id
            ulong        objIdCsr;     // Cursor id
            CAsiObject * diag;         // Diagnostics and Descriptors
            CAsiObject * control;      // Control 

private:
    // ASI version string
    //
    static const char* pAsiVersion;

};


////////////////////////////////////////////////////////////////////////////
class CAsiAppl: public CAsiSQLObject
// This class is introduces functionality of ASI application 
// initialization/termination and disconnectinf from all 
// SQL environments. It is derived from the CAsiSQLObject class
// to provide caller with diagnostics info.
//
{
friend class CAsiSession;

public:
      //  Construction/destruction
      //
              CAsiAppl  ();  
      virtual ~CAsiAppl ();

      //  Application initialization/termination, Disconnect all
      //
      EAsiBoolean   Init             (void);  // Initialize application
      EAsiBoolean   Term             (void);  // Terminate application
      EAsiBoolean   Abort            (void);  // Abort application (rollback 
                                              // all active transactions
      EAsiBoolean   DisconnectAll    (void);  // Disconnect from all environmants

protected:
      EAsiBoolean   addConnection    (CAsiSession *);
      EAsiBoolean   removeConnection (CAsiSession *);
      EAsiBoolean   deleteConnection (CAsiSession *);

private: 
      EAsiBoolean   rollbackAll      (void);

private:
      CAsiObject  * cncList;     // Connections
};



////////////////////////////////////////////////////////////////////////////////
class CAsiSession: public CAsiSQLObject
//
// This class provides services of the SQL connection and session management.
// Besides natural connection functionality (connect to and disconnect
// from SQL environment), this class provides straightforward way of executing
// transaction management and session management statements. Of course they
// can be also executed as a ordinary SQL statements by means of prepare and
// execute.
//
// MEMBER FUNCTIONS
// ----------------
//
// Construction/Destruction
//
// CAsiSession (CAsiAppl *)
//
// CAsiSession constructor constructs SQL-session object, but doesn't start
// the SQL session. Session is started when connecting to SQL environemnt
// is performed by means of the Connect () method provided by this class.
//
//
// ~CAsiSession ()
//
// Destroy CAsiSession object. If SQL-session is active when destructor is
// called, then terminate current transaction by ROLLBACK.
//
//
// Starting/Terminating Session
//
// EAsiBoolean Connect (
//   const CAsiUcStr &envname,        // SQL environment name
//   const CAsiUcStr &usrname,        // User name
//   const CAsiUcStr &password)       // Password
//
// Connect ot SQL environment and start SQL-session. Environment name
// is a section in the ASI Configuration File. This function can throw
// ASI exception and sets complition condition. Return kAsiTrue if succeeded
// and kAsiFalse otherwise.
//
//
// EAsiBoolean Disconnect (void)
//
// Terminate SQL session and disconnect from SQL environment if there is
// mo active transaction associated with the session. Otherwise throw
// exception condition (if ASI_TRY was established), and store complition
// condition.
//
//
// Setting Session Context
//
// The function listed below are provided to set context of the current 
// SQL session. Session context items that can be set by means of them 
// comprise the following items:
//
//   catalog name,
//   schema name,
//   character set name,
//   time zone displacement, and
//   authorization
//
// These function can throw ASI exception and set complition condition.
// They return kAsiTrue if succeeded and kAsiFalse otherwise.
//
// EAsiBoolean SetCatalog  (
//   const CAsiUcStr &catalog)     // Catalog name
//
// EAsiBoolean SetSchema   (
//   const CAsiUcStr &schema)      // Schema name
//
// EAsiBoolean SetNames    (
//   const CAsiUcStr &name)        // Character set name
//
// EAsiBoolean SetTimeZone (
//   const CAsiDT &timezone)   // Time Zone 
//
// EAsiBoolean SetAuthor   (
//   const CAsiUcStr & user);      // Authorization
//
//
// Transaction management
//
// EAsiBoolean SetTrans (
//   EAsiTILevel ilevel,         // Isolation level
//   EAsiTMode tmpode,           // Transaction mode
//   uint size                   // Diagnostics area size 
//  )
// Set transaction isolation level and transaction mode for the
// next transaction. If transaction is currently active, then throw ASI
// exception. Store complition condition. 
//
//
// EAsiBoolean DeferrConstr (
//   CAsiIdent *consname)        // Constraint name
//
// Change constraint checking mode to deffered.
//
// EAsiBoolean ImmConstr (
//   const CAsiIdent &consname)  // Constraint name
//
// Change constraint checking mode to immediate
//
// EAsiBoolean Commit       (void);                   // Commit work
//
// Terminate transaction by commit
//
// EAsiBoolean Rollback     (void);                   // Rollback
//
// Terminate transaction by rollback
//            
//
// Misceleneous
//
// EAsiBoolean Cancel (void)
//
// Break execution of the SQL statment (asynchronous break)
//
{
friend class CAsiExecStm;
friend class CAsiNativeStm;
friend class CAsiInterDBStm;
friend class CAsiAppl;

public:
    // Construction/Destruction
    //
            CAsiSession (CAsiAppl *);
    virtual ~CAsiSession ();

    // Starting/Terminating Session
    //
            EAsiBoolean Connect    (const CAsiUcStr &, const CAsiUcStr &,
                                    const CAsiUcStr &);
            EAsiBoolean Disconnect (void);
           
    // Setting Session Context
    //
            EAsiBoolean SetCatalog  (const CAsiUcStr &);
            EAsiBoolean SetSchema   (const CAsiUcStr &);
            EAsiBoolean SetNames    (const CAsiUcStr &);
            EAsiBoolean SetTimeZone (const CAsiDT &);
            EAsiBoolean SetTimeZone (void);          // Set local time zone 
            EAsiBoolean SetAuthor   (const CAsiUcStr &);

    // Transaction management
    //
            EAsiBoolean SetTrans     (EAsiTILevel, EAsiTMode, uint dSize = 64);  // Set transaction
            EAsiBoolean DeferrConstr (CAsiIdent * cnst = 0);   // Deffer constraint
            EAsiBoolean ImmConstr    (CAsiIdent * cnst = 0);   // Immediate constraint

            EAsiBoolean Commit       (void);                   // Commit work
            EAsiBoolean Rollback     (void);                   // Rollback

    // Misceleneous
    //
            EAsiBoolean Cancel       (void);                   // Break execution
     const  CAsiUcStr & Name         (void) const;             // Session/connection name

protected:
            EAsiBoolean Disconnect (CAsiObject *);
            EAsiBoolean iexecute   (const CAsiUcStr &);

private:
    virtual CAsiObject * duplicate (void) const;             // Duplicate

private: 
    EAsiBoolean   isconnected;
    CAsiAppl    * Appl;           // Aplication
    CAsiUcStr     sname;          // Environment name 

};


////////////////////////////////////////////////////////////////////////////////
class CAsiStm: public CAsiSQLObject
//
// This class introduces functionality of the SQL statement descriptors
// Basic categories of services provided by this class are listed below:
//  - Input parameters manipulation (bind buffers)
//  - Output parameter manipulation (resulting columns)
//
//  MEMBER FUNCTIONS
//  ----------------
//
// Construction/Destruction
//
//  CAsiStm (void)
//
//  Allocate SQL statement descriptor.
//
//  virtual ~CAsiStm                   (void);
//
//  Destroy statement descriptor.
//
//
// Input Parameters Manipulation
//
// int ParamQty (void)
//
// Return number of input parameters (bind variables) in the original
// SQL statement. Number of parameter becomes available after SQL statement
// was prepared.
//
//
// CAsiParameter * ParamDsc (
//   int ipar                // Parameter number
//  ) const
//
// Get parameter descriptor. ipar shall be greater than or equal to 0 and 
// less than number of parameters returned by the ParamQty ().
// If wrong parameter number was specified return 0 instead of pointer to it.
//
//
// Bind parameter with host buffer
//
// EAsiBoolean Bind ( ... )
//
// Two basic methods for binding input paramters with the host variable
// buffers are provided by the CAsiStm class. They are
//
// - by parameter number
// - by parameter name
//
// Input parameter is bound with CAsiData object
//
//
// Output Column Descriptors / Column Values
//
// This set of services are provided in order to get description and 
// values of the resulting columns for the single row select statement
// and cursor. For other types of statements these services have no sence
// and always return kAsiBad.
//
// int ColQty (void) const
//
// Return number of columns in resuting rowset. 
//
//
// CAsiColumn *ColDsc (
//   int colnum                    // Column number
// ) const;         
//
// Return pointer to descripttor of the specified column.
//
//
// Two basic methods are provided to retrieve values of the resulting 
// columns:
//
//  - bind output column with the host buffer, and
//  - retrieve column value from descriptor
//
// These two methods are incompatible, i.e. if one method is used, another
// is not allowed.
//
// Both methods are simular and allow to store output value into 
// CAsiData object
//
// EAsiBoolean Sob ( ... )
//
// Bind output column with the host program buffer
//
//
// EAsiBoolean Cvl (...)
//
// Retrieve column data from descriptor
//
//
{

public:
    // Construction/Destruction
    //
            CAsiStm                    (void);
    virtual ~CAsiStm                   (void);


    // Input Parameters Manipulation
    //
    //
            int             ParamQty    (void) const; // Parameter quantity
            CAsiParameter * ParamDsc    (int) const;  // Get parameter descriptor

         // Bind input parameter by number with
         //
    virtual EAsiBoolean Bind (int, CAsiData *);    // CAsiData object
    virtual EAsiBoolean Bind (int, void *, short *,
                              int, EAsiHostType);  // Host buffer

         // Bind input parameter by name with
         //
    virtual EAsiBoolean Bind (const CAsiIdent &, CAsiData *); // CAsiData object
    virtual EAsiBoolean Bind (const CAsiIdent &, void *, short *,
                              int, EAsiHostType);    // Host buffer

    // Output Column Descriptors / Column Values
    //
    //
            int         ColQty (void) const;      // Column quantity
            CAsiColumn *ColDsc (int) const;       // Get column descriptor

            // Bind output parameter (column) with 
            EAsiBoolean Sob    (int, CAsiData *);    // CAsiData object
            EAsiBoolean Sob    (int, void *, short *,// Host buffer
                                int, EAsiHostType); 

            // Retrieve value of output parameter (column) into
            EAsiBoolean Cvl    (int, CAsiData *);    // CAsiData object
            EAsiBoolean Cvl    (int, void *, short *,// Host buffer
                                int, EAsiHostType); 

            // Some methods for recive raw data
    virtual long        Read   (int, char *, long, long) const = 0;
    virtual long        Size   (int) const = 0;

protected:
            EAsiBoolean CvlInt (int, CAsiData *) const;    // CAsiData object
            EAsiBoolean pInput (void);

protected:
    CAsiObject * input;     
    CAsiObject * output;
};


class CAsiExecStm: public CAsiStm
//
// This class introduces functionality of the executable SQL statement. 
// Another type of statement is a cursor that can't be executed, and 
// should be opend.
// Basic categories of services provided by this class are listed below:
//  - Statement preparing
//  - Statement execution
//
//  MEMBER FUNCTIONS
//  ----------------
//
// Construction/Destruction
//
//  CAsiExecStm (void)
//
//  Constructs SQL statement object
//
//  virtual ~CAsiExecStm  (void);
//
//  Destroy statement. If statement was not deallocated explicitly by
//  means of Dealocate method, then statement is deallocated implicitly.
//  
//
// Preparing/Deallocating
//
// EAsiBoolean Prepare (
//   CAsiSession *session,       // Session
//   const CAsiUcStr &stm        // Statement
//  )   

// Prepare standard SQL statement. Associate
// SQL statement with the session and prepares it.
// This function stores complition condtion and 
// throws ASI exception if error condition was encounted. 
//
// EAsiBoolean Deallocate  (void)
//
// Deallocate either standard or interdatabase SQL statement. If statement is 
// a cursor specification associated with cursor in the open state, then
// ASI exception is raised.
//
//
// Execute statement
//
// EAsiBoolean Execute (void)
//
// Execute prepared SQL statement. Complition condition is always set and  
// ASI exception can be thrown.
//
//
// Immediate SQL and Native statement execution
//
// EAsiBoolean ImmediateExecute (
//   CAsiSession *session,     // session
//   const CAsiUcStr &stm)     // SQL statement
//
// Immediate execute standard SQL statement 
// Successful execution results is returning kAsiGood. If execution fails, 
// then ASI exception is thrown, complition
// conditon is stored CAsiSQLObject and kAsiBad is returned. Execution
// of this statement can start transaction.
//
{
friend class CAsiCsr;

public:
    // Construction/Destruction
    //
            CAsiExecStm                 (void);
    virtual ~CAsiExecStm                (void);

    // Preparing/Deallocating
    //
    virtual EAsiBoolean Prepare          (CAsiSession *, const CAsiUcStr &);
    virtual EAsiBoolean Deallocate       (void);  // Deallocate statement

    // Prepared and execute statement (immediate execution)
    //
    virtual EAsiBoolean Execute          (void);
    virtual EAsiBoolean ImmediateExecute (CAsiSession *, const CAsiUcStr &);

    virtual EAsiBoolean Bind (int, CAsiData *);
    virtual EAsiBoolean Bind (int, void *, short *, int, EAsiHostType);
    virtual EAsiBoolean Bind (const CAsiIdent &, CAsiData *);
    virtual EAsiBoolean Bind (const CAsiIdent &, void *, short *, int, EAsiHostType);

            // Some methods for recive raw data
    virtual long        Read   (int, char *, long, long) const;
    virtual long        Size   (int) const;

private:
    virtual CAsiObject * duplicate (void) const;

};  

////////////////////////////////////////////////////////////////////////////
//
// class CAsiNativeStm
//
////////////////////////////////////////////////////////////////////////////
class CAsiNativeStm: public CAsiExecStm
//
//  This class represents functionality of the Native DBMS statement 
//  processing. Native statements are passed to DBMS driver 
//  without preliminary preprocessing. Native statements can be 
//  just immediate executed.
//  CAsiNativeStm is derived from the CAsiExecStm class and inherits 
//  functionality of the statement immediate execution. 
//  
{
public:
    // Construction/Destruction
    //
            CAsiNativeStm                 (void);
    virtual ~CAsiNativeStm                (void);

    // Statement procession
    virtual EAsiBoolean ImmediateExecute (CAsiSession *, const CAsiUcStr &);

private:
    // Overload these methods just to signal that they are not supported
    // by the Native statement
    virtual EAsiBoolean Prepare          (CAsiSession *, const CAsiUcStr &);
    virtual EAsiBoolean Execute          (void);
    virtual EAsiBoolean Deallocate       (void);
};


////////////////////////////////////////////////////////////////////////////
//
// class CAsiInterDBStm
//
////////////////////////////////////////////////////////////////////////////
class CAsiInterDBStm: public CAsiExecStm
{
public:
            CAsiInterDBStm ();
    virtual ~CAsiInterDBStm ();


    virtual EAsiBoolean Prepare          (CAsiSession *, const CAsiUcStr &);

    // Immediate execute
    //
    virtual EAsiBoolean ImmediateExecute (CAsiSession *, const CAsiUcStr &);

};



////////////////////////////////////////////////////////////////////////////
class CAsiCsr: public CAsiStm
//
// This class proivides functionality of cursor 
//
// Construction/Destruction
//
// CAsiCsr (void);
//
// Construct cusror object
//
// ~CAsiCsr (void);
//
// Destroy cursor object. If cursor was in open state, close cursor implicitly.
//
//
// Allocate/Deallocate Cursor
//
// EAsiBoolean Allocate  (
//   CAsiExecStm * statement,         // Prepared cursor specification
//   const CAsiIdent & name,          // Cursor name
//   EAsiCurScr Scrollability,        // Cursor Scrollability
//   EAsiCurSns Sensivity);           // Cursor Sensitivity
//
// Allocate cursor. Statement shall be a prepared cursor specification.
// Otherwise ASI exception is thrown.
//
//
//
// Open/Close Cursor
//     
// EAsiBoolean Open (void)
//
// Open cursor. Cursor state becomes open and cursor position becomes before
// the first row of the selection set.
//
//
// EAsiBoolean Close (void)
//
// Close cursor. Cursor state is set to 'close'.
//
//
// Fetching Resulting Rowset        
//
// These services allow to fetch
//   - Next row
//   - Prior row
//   - First row
//   - Last row
//   - by the Relative row number (offset)
//   - by the Absolute row number (direct)
//
//   EAsiBoolean Fetch (void)
//
//   EAsiBoolean FetchPrior (void)
//
//   EAsiBoolean FetchFirst (void)
//   
//   EAsiBoolean FetchLast (void)
//
//   EAsiBoolean FetchRelative (
//     long rrow)                  // Relative row number
//
//   EAsiBoolean FetchAbsolute (
//     long row)                   // Absolute row number
//
//
// Storing Resulting Column Values
//
// CAsiRow   * getCurrentRow (void) const 
//
// Return pointer to the CAsiRow object containing current row 
//
//
// Delete/Update Current Row (Delete: positioned, Update: positioned)
//
// EAsiBoolean Delete  (void)
//
// Delete current row
//
//
// EAsiBoolean Update  (const CAsiRow &) 
//
// Update current row. Only columns that are present in the CAsiRow 
// object are updated. Association is done by column name
//
//
// Misceleneous 
// 
// EAsiBoolean is_updatable  (void);      // Is cursor updatable
// EAsiBoolean is_scrollable (void);      // Is cursor scrollable
// EAsiBoolean is_open       (void);      // Is cursor in open state
//
{
public:
    // Construction/Destruction
    //
             CAsiCsr (void);
    virtual ~CAsiCsr (void);

    // Allocate Cursor
    //
            EAsiBoolean Allocate      (CAsiExecStm *, const CAsiIdent &, 
                                       EAsiCurScr sc = kAsiNonScroll, 
                                       EAsiCurSns sn = kAsiSnsUndef);

    // Open/Close Cursor
    //     
            EAsiBoolean Open          (void);     // Open cursor
            EAsiBoolean Close         (void);     // Close

    // Fetching Resulting Rowset        
    //
            EAsiBoolean Fetch         (void);   // Fetch next row
            EAsiBoolean FetchPrior    (void);   // Fetch Prior row
            EAsiBoolean FetchFirst    (void);   // Fetch First row
            EAsiBoolean FetchLast     (void);   // Fetch Last row
            EAsiBoolean FetchRelative (long);   // Fetch Relative row
            EAsiBoolean FetchAbsolute (long);   // Fetch Absolute row

    // Storing Resulting Column Values
    //
            CAsiRow   * getCurrentRow (void) const;   // Get pointer to current row

    // Delete/Update Current Row (Delete: positioned, Update: positioned)
    //
            EAsiBoolean Delete        (void);            // Delete current row
            EAsiBoolean Update        (const CAsiRow &); // Update current row

    // Misceleneous 
    // 
            EAsiBoolean is_updatable   (void);      // Is cursor updatable
            EAsiBoolean is_scrollable  (void);      // Is cursor scrollable
            EAsiBoolean is_insensitive (void);      // Is cursor insensitive
            EAsiBoolean is_open        (void);      // Is cursor in open state
            EAsiCurPos  position       (void);      // Cursor position

            // Some methods for recive raw data
    virtual long        Read   (int, char *, long, long) const;
    virtual long        Size   (int) const;

private:
    virtual CAsiObject * duplicate (void) const;

private:
            CAsiIdent   csrname;
            EAsiBoolean opnFlag;
            EAsiCurScr  scrFlag;
            EAsiCurSns  snsFlag;
};








////////////////////////////////////////////////
//  Extern function prototypes
//
extern "C" {
void                      AsiExceptionThrow (CAsiException*);
}


#endif /* ASI_ASICLASS_HH */
/*EOF*/
