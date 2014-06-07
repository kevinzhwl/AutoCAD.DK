// (C) Copyright 2001 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////////////////////
//
// MultilineTooltipSamp.cpp : Initialization functions
#include "StdAfx.h"

void MTooltipOn()
{
  if (!gDocVars.docData().m_pIPM)
    new CSampleIPM;
}

void MTooltipOff()
{
  if (gDocVars.docData().m_pIPM)
    delete gDocVars.docData().m_pIPM;
}

// Init this application. Register your
// commands, reactors...
void InitApplication()
{
	acedRegCmds->addCommand("ASDK", "MTOOPTIPON", "MTON", ACRX_CMD_MODAL, MTooltipOn);
	acedRegCmds->addCommand("ASDK", "MTOOPTIPOFF", "MTOFF", ACRX_CMD_MODAL, MTooltipOff);

	acutPrintf("\nCommands are: MTOOPTIPON (MTON) and MTOOPTIPOFF (MTOFF).");
	MTooltipOn();
	acutPrintf("\nSample multiline tooltip is on.");
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
		acedRegCmds->removeGroup("ASDK");
		break;
	}
	return AcRx::kRetOK;
}


