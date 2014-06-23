//
// (C) Copyright 1996 by Autodesk, Inc. 
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
// POLYJIG.CPP
//
//

#include "polyjig.h"
#include "dbmain.h"
#include "poly.h"
#include "adslib.h"


extern Adesk::Boolean rx_uc2wc(ads_point p, ads_point q, Adesk::Boolean vec);

AsdkPolyJig::AsdkPolyJig() : mPoly(NULL) 
{
}


AsdkPolyJig::~AsdkPolyJig()
{
}


void               
AsdkPolyJig::initializePoly(AcGePoint3d  cen,
                            AcGeVector3d norm,
                            int          numSides)
{
    mPoly = new AsdkPoly();
    mPoly->setNumSides(numSides);
    mPoly->setCenter(cen);
    mPoly->setNormal(norm);
}


void 
AsdkPolyJig::acquire(AcGePoint3d  cen,
                     AcGeVector3d norm,
                     char*        name,
                     AcDbObjectId tsId)
{
    int numSides = 0;
    while (numSides < 3) {
        switch (ads_getint("\nEnter number of sides: ", &numSides)) {
        case RTNORM:
            if (numSides < 3)
               ads_printf("\nNeed at least 3 sides.");
            break;
        default:
            return;
        }
    } 
    initializePoly(cen, norm, numSides);
    dragAcquire("\nLocate start point of polygon: ", name, tsId);
}


AcDbEntity* AsdkPolyJig::entity() const
{
    return mPoly;
}


AcEdJig::DragStatus	 
AsdkPolyJig::sampler()
{
    // set the special cursor type. If no cursor type is 
    // specified then acquireXXX method selects one for you.
    //
    setSpecialCursorType(AcEdJig::kCrosshair);

    // set the user input controls. This specifies how the
    // various user actions affect the drag sequence.
    //
    setUserInputControls((UserInputControls)
	                 (kNullResponseAccepted|kAccept3dCoordinates |
	                  kDontUpdateLastPoint));
    
    AcGePoint3d   secondPoint;
    DragStatus stat = AcEdJig::acquirePoint(secondPoint, mPoly->center());
    if (stat == kNormal) {
	if (mPoly->center() == secondPoint)
	    stat = kOther;
	else if (mPoly->startPoint() == secondPoint)
	    stat = kNoChange;
	else 
	    mPoly->setStartPoint(secondPoint) ;
    } else 
	stat = kNoChange ;

    return stat ;
}


Adesk::Boolean 
AsdkPolyJig::dragAcquire(char* promptString,
                         char* name,
                         AcDbObjectId tsId)
{
    setDispPrompt(promptString);
    AcEdJig::DragStatus stat = drag();

    switch(stat) {
    case kNormal:
        mPoly->setName(name);
        mPoly->setTextStyle(tsId);
        append();
        break ;
    case kNoChange:
        delete mPoly;
        ads_printf("The drag status is kNoChange\n");
        break ;
    case kCancel:
        delete mPoly;
        ads_printf("The drag status is kCancel\n");
        break ;
    case kOther:
        delete mPoly;
        ads_printf("The drag status is kOther\n");
        ads_printf("Invalid Instance\n");
        break ;
    case kNull:
        delete mPoly;
        ads_printf("The drag status is kNull\n");
        break ;
    default:
        delete mPoly;
        ads_printf("The drag status is %d\n", stat);
        break ;
    }

    mPoly = NULL;
    return (stat == kNormal) || (stat == kOther) ;
}


Adesk::Boolean	
AsdkPolyJig::update()
{
    return Adesk::kTrue;
}
