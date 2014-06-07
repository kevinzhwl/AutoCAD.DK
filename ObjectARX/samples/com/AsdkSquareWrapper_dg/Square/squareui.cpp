//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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
// squareui.cpp
// 
// Example square custom entity UI
//

#ifdef _DEBUG
#undef _DEBUG
#define _DEBUG_WAS_DEFINED_
#endif

#include <afxwin.h>

// ATL includes for sqareCmd.h
#include <atlbase.h>
CComModule _Module;
#include <atlcom.h>

#ifdef  _DEBUG_WAS_DEFINED_
#define _DEBUG
#undef _DEBUG_WAS_DEFINED_
#endif

#include <acdocman.h>
#include <aced.h>
#include <acdb.h>
#include <adslib.h>
#include <rxmfcapi.h>

// Acad COM and Automation interfaces
#include <acadi.h>
#include <axtempl.h>
#include <axpnt3d.h>

#include "asdksquarelib.h"
#include "asdksquarelib_i.c"

#include "squarent.h"
#include "squarecmd.h"

bool append(AcDbEntity* pEntity)
{
    AcDbBlockTable *pBlockTable;

	AcApDocument* pDoc = acDocManager->curDocument();

	Acad::ErrorStatus es = acDocManager->lockDocument(pDoc);
    if (es != Acad::eOk) {
        acedAlert("Failed to lock the document...");
        return false;
    }

	AcDbDatabase* pDb = pDoc->database();
    
    es = pDb->getBlockTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        acedAlert("Failed to get block table...");
        return false;
    }

    AcDbBlockTableRecord *pBlockRec;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite);
    if (es != Acad::eOk) {
        acedAlert("Failed to get block table record...");
        pBlockTable->close();
        return false;
    }

    es = pBlockRec->appendAcDbEntity(pEntity);
    if (es != Acad::eOk) {
        acedAlert("Failed to append entity...");
        pBlockTable->close();
        pBlockRec->close();
        delete pEntity;
        return false;
    }
    pBlockRec->close();
    pBlockTable->close();
    return true;

}


// Adds a square to model space using only the command line
void aSquare()
{
	
	AsdkSquare* mySquare = new AsdkSquare();

	if( !mySquare ) {
		acutPrintf("\n Memory allocation error.");
		return;
	}

	ads_point pt1, pt2, pt3;
	struct resbuf UCS, WCS;
	
	WCS.restype = RTSHORT;
	WCS.resval.rint = 0;

	UCS.restype = RTSHORT;
	UCS.resval.rint = 1;

	acedGetPoint(NULL, "\nPick a point for the center: ", pt1);
	acedGetPoint(pt1, "\nPick a direction for corner and size: ", pt2);

	pt2[X] = pt2[X] - pt1[X];
	pt2[Y] = pt2[Y] - pt1[Y];
	pt2[Z] = pt2[Z] - pt1[Z];

	pt3[X] = pt3[Y] = 0.0;
	pt3[Z] = 1.0;

	acedTrans(pt1, &UCS, &WCS, 0, pt1);
	acedTrans(pt2, &UCS, &WCS, 1, pt2);
	acedTrans(pt3, &UCS, &WCS, 1, pt3);

	mySquare->setSquareCenter(AcGePoint3d(pt1[X],pt1[Y],pt1[Z]));
	mySquare->setSquareOrient(AcGeVector3d(pt2[X],pt2[Y],pt2[Z]));	
	mySquare->setSquareNormal(AcGeVector3d(pt3[X],pt3[Y],pt3[Z]));

	append(mySquare);

	mySquare->close();

	return;

}

// Adds a square to the current space using both the command line and OPM
void addSquare()
{
	CComPtr<IAsdkSquareWrapper> pSquare;
    CComQIPtr<IAcadBaseObject2> pSquareBase;
    CComQIPtr<IConnectionPointContainer> pConnectionPts;
    CComPtr<IConnectionPoint> pConnection;

    CComObject<CAsdkSquareCmd> *pSquareCmdObj;
    CComPtr<IUnknown> pSquareCmd;

    DWORD connectionId = 0;
    HRESULT hr = S_OK;
    
    try {

        
        // Create the wrapper object which we will place into OPM
        // to display the square's properties
        if (FAILED(hr = pSquare.CoCreateInstance(CLSID_AsdkSquareWrapper)))
            throw hr;

        pSquareBase = pSquare;
        
        // Create the underlying square object
        if (FAILED(hr = pSquareBase->CreateObject()))
            throw hr;

        // Create the square modification listener which we use to
        // synchronize changes in OPM and the command line
        if (FAILED(hr = CComObject<CAsdkSquareCmd>::CreateInstance(&pSquareCmdObj)))
            throw hr;

        pSquareCmdObj->QueryInterface(IID_IUnknown, (void **)&pSquareCmd);

        // Attach the square modification listener to the wrapper
        pConnectionPts = pSquare;

        if (!pConnectionPts)
            throw E_POINTER;
        
        if (FAILED(hr = pConnectionPts->FindConnectionPoint(IID_IPropertyNotifySink, &pConnection)))
            throw hr;

        if (FAILED(hr = pConnection->Advise(pSquareCmd, &connectionId)))
            throw hr;
    }
    catch (HRESULT) {
        acutPrintf("\n Error initializing command.");
		acutPrintf("\n Please compile and register the AsdkSquareWrap module prior to use this command. (see readme for instructions)");
        return;
    }

    // Set the square object up for OPM
    acedSetIUnknownForCurrentCommand(pSquare);

    // Now process the command line input by 
    // looping for all required parameters
   	ads_point pt0, pt1;
    ads_real size = 0.0;
	struct resbuf UCS, WCS;
    int retval;
	
	WCS.restype = RTSHORT;
	WCS.resval.rint = 0;

	UCS.restype = RTSHORT;
	UCS.resval.rint = 1;

    while (true) {
        if (!pSquareCmdObj->GotCenterPoint())
        {
	        retval = acedGetPoint(NULL, "\nPick a point for the center: ", pt0);
            if (retval == RTCAN)
                break;
            else if (retval != RTNORM)
                continue;

            acedTrans(pt0, &UCS, &WCS, 0, pt1);
            AcAxPoint3d pnt3d(pt1[X], pt1[Y], pt1[Z]);
            pSquare->put_CenterPoint(*(pnt3d.asVariantPtr()));
        }

        if (!pSquareCmdObj->GotSquareSize())
        {
	        retval = acedGetDist(pt0, "\nPick the square size : ", &size);
            if (retval == RTCAN)
                break;
            else if (retval != RTNORM)
                continue;

        	pSquare->put_SquareSize(size);
        }

        AcDbObjectId squareId;
	    if (FAILED(hr = pSquareBase->AddToDb(squareId, curDoc()->database()->currentSpaceId()))) 
        {
            acutPrintf("\n Error appending object to database.");
            break;
        }

        break;
    }

    // Unadvise the square modified listener
    pConnection->Unadvise(connectionId);

	return;
}

void
initApp()
{
    acutPrintf("AsdkSquare ARX application; Type SQ or ADDSQ to execute");

    // register a command with the AutoCAD command mechanism
    //
    acedRegCmds->addCommand("SQUARE_COMMANDS", "ASDKSQUARE", 
							"SQ", ACRX_CMD_MODAL, aSquare);
    acedRegCmds->addCommand("SQUARE_COMMANDS", "ASDKADDSQUARE", 
							"ADDSQ", ACRX_CMD_MODAL | ACRX_CMD_INTERRUPTIBLE, addSquare);

}


void unloadApp()
{
    
    // Remove the command group added via acedRegCmds->addCommand
    //
    acedRegCmds->removeGroup("SQUARE_COMMANDS");

}

extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		acrxDynamicLinker->loadModule("square.dbx", true);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    case AcRx::kLoadDwgMsg:

        break;
    case AcRx::kUnloadDwgMsg:

        break;
	case AcRx::kInvkSubrMsg:

		break;
    default:
		;
    }
    return AcRx::kRetOK;
}

