// Project.cpp : Initialization functions
#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"

HINSTANCE _hdllInstance =NULL ;

// This command registers an ARX command.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal = -1);

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_MSG
void InitApplication();
void UnloadApplication();
//}}AFX_ARX_MSG

// NOTE: DO NOT edit the following lines.
//{{AFX_ARX_ADDIN_FUNCS
//}}AFX_ARX_ADDIN_FUNCS

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
        _hdllInstance = hInstance;
	} else if (dwReason == DLL_PROCESS_DETACH) {
	}
	return TRUE;    // ok
}



/////////////////////////////////////////////////////////////////////////////
// ObjectARX EntryPoint
extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg) {
	case AcRx::kInitAppMsg:
		// Comment out the following line if your
		// application should be locked into memory
		acrxDynamicLinker->unlockApplication(pkt);
		acrxDynamicLinker->registerAppMDIAware(pkt);
		InitApplication();
		break;
	case AcRx::kUnloadAppMsg:
		UnloadApplication();
		break;
	}
	return AcRx::kRetOK;
}


// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_INIT
	AddCommand("ASDK", "MYINPUT", "MYINPUT", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkmyinput);
	AddCommand("ASDK", "MYSELECT", "MYSELECT", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkmyselect);
	AddCommand("ASDK", "CREATE", "CREATE", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkcreate);
	AddCommand("ASDK", "SETLAYER", "SETLAYER", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdksetlayer);
	AddCommand("ASDK", "ADDENTRY", "ADDENTRY", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkaddentry);
	AddCommand("ASDK", "REMOVEENTRY", "REMOVEENTRY", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, asdkremoveentry);
	AddCommand("ASDK", "LISTENTRIES", "LISTENTRIES", ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET | ACRX_CMD_NOINTERNALLOCK, asdklistentries);
	//}}AFX_ARX_INIT

	// TODO: add your initialization functions

}

// Unload this application. Unregister all objects
// registered in InitApplication.
void UnloadApplication()
{
	// NOTE: DO NOT edit the following lines.
	//{{AFX_ARX_EXIT
	acedRegCmds->removeGroup("ASDK");
	//}}AFX_ARX_EXIT

	// TODO: clean up your application
}

// This functions registers an ARX command.
// It can be used to read the localized command name
// from a string table stored in the resources.
void AddCommand(const char* cmdGroup, const char* cmdInt, const char* cmdLoc,
				const int cmdFlags, const AcRxFunctionPtr cmdProc, const int idLocal)
{
	char cmdLocRes[65];

	// If idLocal is not -1, it's treated as an ID for
	// a string stored in the resources.
	if (idLocal != -1) {

		// Load strings from the string table and register the command.
		::LoadString(_hdllInstance, idLocal, cmdLocRes, 64);
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLocRes, cmdFlags, cmdProc);

	} else
		// idLocal is -1, so the 'hard coded'
		// localized function name is used.
		acedRegCmds->addCommand(cmdGroup, cmdInt, cmdLoc, cmdFlags, cmdProc);
}
