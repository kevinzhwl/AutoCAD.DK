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
// Description:
//
// This program demonstrates how to use AcEdJig to provide a user interface
// for AcDbCircle creation.
//
// To get the AcEdJig mechanism to work with any of the "R12" entity classes
// requires the use of a "dummy" class that is derived from AcDbEntity
// (although it does not need be added to the ARX runtime class tree) and
// contains an implemented worldDraw() method to provide the graphics during
// the drag process.
//
// Within the class derived from AcEdJig,  an object of the "dummy" class is
// used during the drag process to properly display what's going on.  When
// all data acquisition is complete and the entity is to be appended to the
// database, an actual AcEb entity object of the appropriate type is
// instantiated,  filled in with the data acquired,  and then is appended to
// the database.
//
// In this example the "dummy" class is called AsdkCircle.  It provides just
// enough functionality to display a circle and set the radius.
//
// In order to make the switch from the AsdkCircle object to an AcDbCircle
// object when it's time to append to the database,  a new function is
// defined in the class derived from AcEdJig.  The new function is called
// appendCircle().  appendCircle() instantiates a new AcDbCircle object fills
// it in, and calls the AcEdJig::append() method to add it to the database.
// The trick here is how do you get the AcEdJig::entity() method to return
// a pointer to the proper object?  During the drag operation,  the
// AcEdJig::entity() method is called from within the jig mechanism to get
// a pointer to the object that needs to have its worldDraw() method called.
// But,  the AcEdJig::append() method also calls the AcEdJig::entity() method
// to get a pointer to the entity object to append to the database.
//
// To make this all work,  the AsdkCircleJig class (the class derived from
// AcedJig) has two pointer data members, one for an AcDbCircle object and
// one for an AsdkCircle object.  Initially the pointer to the AcDbCircle
// is set to NULL.  The AsdkCircleJig::entity() method tests to see if this
// pointer is NULL.  If it is,  then AsdkCircleJig::entity() returns a pointer
// to the AsdkCircle object for dragging purposes.  When the
// AsdkCircleJig::appendCircle() function instantiates a new AcDbCircle object,
// the pointer is no longer NULL,  so when the AsdkCircleJig::entity() method
// is called by the AcEdJig::append() method,  a pointer to the AcDbCircle
// object is returned and all is well with the world.

#include <adslib.h>
#include <dbjig.h>
#include <dbents.h>
#include <aced.h>
#include <geassign.h>
#include <acgi.h>

class AsdkCircle : public AcDbEntity
//
// dummy line class to provide the drag graphics.  Notice that because objects
// of this class will never be database resident and do not need to be class
// identifiable by the ARX mechanism,  we do not need to use the ACRX macros.
//
{
public:
    AsdkCircle(AcGePoint3d& cp = AcGePoint3d(0,0,0),
    AcGeVector3d& normal = AcGeVector3d(0,0,1));
    virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
    void setRadius(double);
private:
    AcGePoint3d mCenterPoint;
    AcGeVector3d mNormal;
    double mRadius;
};

AsdkCircle::AsdkCircle(AcGePoint3d& cp, AcGeVector3d& normal)
    : mCenterPoint(cp), mNormal(normal)
{}

Adesk::Boolean
AsdkCircle::worldDraw(AcGiWorldDraw* pWd)
{
    pWd->geometry().circle(mCenterPoint, mRadius, mNormal);

    return Adesk::kTrue;
}

void
AsdkCircle::setRadius(double radius)
{
    mRadius = radius;
}

class AsdkCircleJig : public AcEdJig
//
// This class allows the user to create a circle by dragging
// to select the circle's radius.  During the drag operations,
// the user will be able to visually see what the circle looks
// like at any time.
//
// To allow this to work for the AcDbCircle class which does
// not have an implemented worldDraw() method,  an object of
// the class AsdkCircle is used for the dragging operations
// and then replaced with a true AcDbCircle object when it's
// time to append to the database.
//
{
public:
    AsdkCircleJig(const AcGePoint3d&, const AcGeVector3d&);
    virtual ~AsdkCircleJig();
    void doIt();
    virtual DragStatus sampler();
    virtual Adesk::Boolean update();
    virtual AcDbEntity* entity() const;
    virtual void appendCircle();

private:
    AsdkCircle *mpCircle;
    AcDbCircle *mpDbCircle;
    AcGePoint3d mCenterPoint;
    AcGeVector3d mNormal;
    double mRadius;
};

AsdkCircleJig::AsdkCircleJig(const AcGePoint3d& pt, const AcGeVector3d& normal)
: mCenterPoint(pt), mNormal(normal), mpDbCircle(NULL)
{ }

AsdkCircleJig::~AsdkCircleJig()
{
    delete mpCircle;
}


// This function creates an AsdkCircle object and gets the
// jig started acquiring the necessary info to properly fill
// it in.
//
void
AsdkCircleJig::doIt()
{
    mpCircle = new AsdkCircle(mCenterPoint, mNormal);

    // get the circle's radius from the user.
    //
    setDispPrompt("\nCircle radius: ");
    drag();

    // Now add the circle to the database's current space using
    // the special function provided that will replace the
    // AsdkCircle object with an AcDbCircle object before calling
    // the AcEdJig::append() method.
    //
    appendCircle();
}

// This function is called by the drag function in order to
// acquire a sample input
//
AcEdJig::DragStatus
AsdkCircleJig::sampler()
{
    DragStatus stat;

    setUserInputControls((UserInputControls)
        (AcEdJig::kAccept3dCoordinates
         | AcEdJig::kNoNegativeResponseAccepted
         | AcEdJig::kNoZeroResponseAccepted));

    // Acquire the radius.  Check to see if the input has changed
    // since the last sample.  If not,  then return AcEdJig::kNoChange
    // to indicate that no graphics update is required.  This will
    // allow the circle to finish drawing on screen.
    //
    static double radiusTemp = -1;
    stat = acquireDist(mRadius, mCenterPoint);
    if (radiusTemp != mRadius)
        radiusTemp = mRadius;
    else if (stat == AcEdJig::kNormal)
        return AcEdJig::kNoChange;

    return stat;
}

// This function is called to update the entity based on the
// input values
//
Adesk::Boolean
AsdkCircleJig::update()
{
    mpCircle->setRadius(mRadius);

    return Adesk::kTrue;
}

// This function must be implemented to return a pointer to
// the entity being manipulated by the jig.
//
// Because the jig must work with an object that has an implemented
// worldDraw method,  this function checks to see if the pointer
// for the AcDbCircle object is NULL.  If it is,  then dragging
// is in progress and the AsdkCircle object must be used.  When
// the pointer to the AcDbCircle object is not NULL,  then it's
// the pointer that must be returned because it's going to be
// used to append to the database.
//
AcDbEntity*
AsdkCircleJig::entity() const
{
    if (mpDbCircle == NULL)
        return mpCircle;
    else
        return mpDbCircle;
}

// This function encapsulates the creation of an AcDbCircle object
// and the calling of the AcEdJig::append() method.  It works together
// with the AsdkCircleJig::entity() method which returns a pointer to
// the AsdkCircleJig's AsdkCircle object until this function instantiates
// a new AcDbCircle object and sets the appropriate pointer in the
// AsdkCircleJig object to point to it.  Once that's been done,  the
// AsdkCircleJig::entity() method will return a pointer to the newly
// created AcDbCircle object which is just what the AcEdJig::append()
// method wants.
// 
void
AsdkCircleJig::appendCircle()
{
    mpDbCircle = new AcDbCircle(mCenterPoint, mNormal, mRadius);
    append();

}


void
createCircle()
{
    // First have the user select the circle's center point.
    // We don't use the Jig for this because there is
    // nothing to see yet.
    //
    AcGePoint3d tempPt;
    struct resbuf rbFrom, rbTo;

    ads_getpoint(NULL, "\nCircle center point: ",
        asDblArray(tempPt));

    // The point we just got is in UCS coords, but
    // AcDbCircle works in WCS so convert the point.
    //
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0; // to WCS

    ads_trans(asDblArray(tempPt), &rbFrom, &rbTo,
        Adesk::kFalse, asDblArray(tempPt));

    // Now need to get the current UCS Z-Axis to be used
    // as the normal vector for the circle.  For this sample
    // we'll assume we're only working in model space.  So,
    // we get the model space normal.
    //
    AcGeVector3d x = acdbCurDwg()->ucsxdir();
    AcGeVector3d y = acdbCurDwg()->ucsydir();
    AcGeVector3d normalVec = x.crossProduct(y);
    normalVec.normalize();

    // Create an AsdkCircleJig object passing in the center point
    // just selected by the user and the model space normal vector.
    //
    AsdkCircleJig *pJig
        = new AsdkCircleJig(tempPt, normalVec);

    // Now start up the jig to interactively get the circle's radius
    //
    pJig->doIt();

    // Now delete the jig since it's no longer needed
    //
    delete pJig;
}

void
initApp()
{
    acedRegCmds->addCommand("ASDK_VISUAL_CIRCLE",
        "ASDK_VCIRCLE", "VCIRCLE", ACRX_CMD_MODAL,
        createCircle);
}

void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_VISUAL_CIRCLE");
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
