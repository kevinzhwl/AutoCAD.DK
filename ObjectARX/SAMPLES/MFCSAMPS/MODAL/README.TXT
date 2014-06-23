This sample ARX application uses MFC to put up a modal dialog with 
just two buttons: Ok and Cancel.
The ARX command to be invoked is 'modal'

This sample uses MFC dll. It expects to have the same MFC DLL
as AutoCAD. 
The consequences of this for Production AutoCAD, which uses non-debug MFC, 
is the following:
- Debug target.
  The makefile will build debug version of this sample with _non-debug_ 
  MFC & C Runtime libraries.

If you browse the codes, you'll notice the following:

// Turn off the _DEBUG symbol if it's defined, before including
// MFC header files.
#if defined(_DEBUG) && !defined(DEBUG_AUTOCAD)
    #define _DEBUG_WAS_DEFINED
    #undef _DEBUG
#endif

#include <MFC_HEADER_FILES>

// Turn on the _DEBUG symbol if it was defined, before including
// non-MFC header files.
//
#ifdef _DEBUG_WAS_DEFINED
    #define _DEBUG
    #undef _DEBUG_WAS_DEFINED
#endif

#include <other header files here>

Above code section is used to turn off _DEBUG symbol for all MFC headers 
when we're building debug version. When _DEBUG is not defined for MFC headers,
it will pull in non-debug MFC library. Because debug code in MFC is turned off,
your MFC code should not contain MFC debugging facility, such as CDump, 
AssertValid, etc. However, it's still possible to debug into MFC source code.

DEBUG_AUTOCAD symbol is for Autodesk internal use only.

