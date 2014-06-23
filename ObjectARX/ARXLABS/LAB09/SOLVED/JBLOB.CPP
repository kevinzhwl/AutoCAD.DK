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
// jblob.cpp - jblob entity, a line with a filled circle at 
// its endpoint.


#include <acdb.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "adslib.h"
#include "rxregsvc.h"
#include "jblob.h"

const char* kClassName = "Jblob";

// define a DXF class body for the entity using the
// appropriate ACRX boilerplate macro.  The DXF class name
// *MUST* be all uppercase.
//
// ... The following line completes ...
ACRX_DXF_DEFINE_MEMBERS(Jblob, AcDbEntity, 0, JBLOB, JBLOB);

Jblob::Jblob() : mnormal(0,0,1)
{
}

Jblob::~Jblob()
{
}

Adesk::Boolean
Jblob::worldDraw(AcGiWorldDraw* wd)
{
    AcGePoint3d line[2];
    
    // Give the line a GS marker of 1
    //
    wd->subEntityTraits().setSelectionMarker(1);
    line[0] = mp;
    line[1] = mpblob;
    wd->geometry().polyline(2, line);

    if (wd->isDragging()) {
        // set filltype to never fill
        //
        wd->subEntityTraits().setFillType(kAcGiFillNever);
    } else {
        // ask for circle to be filled:
        //
        wd->subEntityTraits().setFillType(kAcGiFillAlways);
    }
    // Give the circle a GS marker of 2
    //
    wd->subEntityTraits().setSelectionMarker(2);
    wd->geometry().circle(mpblob, mrblob, mnormal);
    return Adesk::kTrue;
}

Acad::ErrorStatus
Jblob::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();

    AcDbEntity::dwgInFields(filer);

    // read in the start point,
    // blob point, blob radius
    // and normal vector
    //
    // ... The following 4 lines complete ...

    filer->readItem(&mp);
    filer->readItem(&mpblob);
    filer->readItem(&mrblob);
    filer->readItem(&mnormal);

    return filer->filerStatus();
}

Acad::ErrorStatus
Jblob::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();

    AcDbEntity::dwgOutFields(filer);

    // write out the start point,
    // blob point, blob radius
    // and normal vector
    //
    // ... The following 4 lines complete...

    filer->writeItem(mp);
    filer->writeItem(mpblob);
    filer->writeItem(mrblob);
    filer->writeItem(mnormal);

    return filer->filerStatus();
}

Acad::ErrorStatus
Jblob::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();

    struct resbuf rb;

    Acad::ErrorStatus es = AcDbEntity::dxfInFields(filer);

    if (es != Acad::eOk) {
        return es;
    }

    // check that we are at the correct subclass data
    //
    // ... The following 3 lines complete ...

    if (!filer->atSubclassData(kClassName)) {
        return Acad::eBadDxfSequence;
    }

    // set the normal's default value in case it's not in the
    // DXF information coming in
    //
    // ... The following line completes ...

    mnormal = AcGeVector3d(0, 0, 1); // set default value:

    // loop as long as you can read in items
    // from the filer. Depending on the group
    // code read, set the start point,
    // blob point, blob radius and normal 
    // vector
    //
    // ... The following 20 lines complete ...

    while (es == Acad::eOk) {
        if ((es = filer->readItem(&rb)) == Acad::eOk) {
            switch(rb.restype) {
            case AcDb::kDxfXCoord:
                mp.set(rb.resval.rpoint[X], rb.resval.rpoint[Y],
                    rb.resval.rpoint[Z]);
                break;
            case AcDb::kDxfXCoord+1:
                mpblob.set(rb.resval.rpoint[X], rb.resval.rpoint[Y],
                    rb.resval.rpoint[Z]);
                break;
            case AcDb::kDxfReal:
                mrblob = rb.resval.rreal;
                break;
            case AcDb::kDxfNormalX:
                mnormal.set(rb.resval.rpoint[X], rb.resval.rpoint[Y],
                    rb.resval.rpoint[Z]);
            }
        }
    }
    return filer->filerStatus();
}

Acad::ErrorStatus
Jblob::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();

    AcDbEntity::dxfOutFields(filer);

    // write out the subclass name,
    // start point, blob point, blob radius
    // and normal vector.
    //
    // You may want to check 
    // filer->includesDefaultValues()
    // and mnormal != AcGeVector3d(0,0,1)
    // before writing out the normal vector.
    //
    // ... The following 9 lines complete ...

    filer->writeItem(AcDb::kDxfSubclass, kClassName);
    filer->writeItem(AcDb::kDxfXCoord, mp);
    filer->writeItem(AcDb::kDxfXCoord + 1, mpblob);
    filer->writeItem(AcDb::kDxfReal, mrblob);
    if (filer->includesDefaultValues()
        || mnormal != AcGeVector3d(0,0,1))
    {
        filer->writeItem(AcDb::kDxfNormalX, mnormal);
    }
    return filer->filerStatus();
}


// This function is called when an Audit is being performed on a
// database containing Jblob entities.  Each object audits itself.
// If everything is OK, this function should return Acad::eOk.  If
// there's an internal problem, the object should call the auditor
// argument's fixErrors() member.  If Adesk::kTrue is returned, and the
// object can successfully repair itself, it should do so, and return
// Acad::eFixedAllErrors.  If the object cannot successfully repair itself,
// it should return Acad::eUnrecoverableErrors.   If Adesk::kFalse is
// returned from fixErrors(), and the object has internal errors, it
// should leave them be, and return Acad::eLeftErrorsUnfixed.
//
Acad::ErrorStatus
Jblob::audit(AcDbAuditInfo* auditor)
{
    if (mrblob <= 0.0) {
        auditor->errorsFound(1);
        if (auditor->fixErrors() == Adesk::kTrue) {
            char buff[50];
            sprintf(buff, "%f", mrblob);
            auditor->printError("JBLOB", buff, "> 0.0", "0.2 * line length");
            // no way to know what the radius really should be
            // so make it about 0.2 of the line length as a
            // reasonable guess so that it'll at least be visible
            // on screen.
            //
            mrblob = 0.2 * mpblob.distanceTo(mp);
            auditor->errorsFixed(1);
            return Acad::eFixedAllErrors;
        } else
            return Acad::eLeftErrorsUnfixed;
    } else
        return Acad::eOk;
}

// For explode,  create the objects that will be the result of the
// explode,  append them to the "entities" array,  then return.
// AutoCAD will take care of the rest.
//
Acad::ErrorStatus
Jblob::explode(AcDbVoidPtrArray& entities) const
{
    assertReadEnabled();

    // explode the Jblob by creating 
    // an appropriately positioned
    // line and circle
    //
    // ... The following 11 lines complete this ...

    AcDbLine *pLine = new AcDbLine;
    pLine->setStartPoint(mp);
    pLine->setEndPoint(mpblob);
    pLine->setNormal(mnormal);
    entities.append(pLine);

    AcDbCircle *pCircle = new AcDbCircle;
    pCircle->setCenter(mpblob);
    pCircle->setRadius(mrblob);
    pCircle->setNormal(mnormal);
    entities.append(pCircle);

    return Acad::eOk;
}

void
Jblob::list() const
{
    assertReadEnabled();

    AcDbEntity::list();

    // list your Jblob data with ads_printf:
    //
    // ... The following 6 lines complete this...

    ads_printf("%19sPOINT\n"
        "%16sat point, X=%9.16q0 Y=%9.16q0 Z=%9.16q0\n",
        "", "", mp[X], mp[Y], mp[Z]);
    ads_printf("%19sBLOB\n"
        "%16sat point, X=%9.16q0 Y=%9.16q0 Z=%9.16q0 R=%9.16q0\n",
        "", "", mpblob[X], mpblob[Y], mpblob[Z], mrblob);
}

Acad::ErrorStatus
Jblob::getOsnapPoints(
    AcDb::OsnapMode   osnapMode,
    int         gsSelectionMark,
    const AcGePoint3d&  pickPoint,
    const AcGePoint3d&  lastPoint,
    const AcGeMatrix3d& viewXform,
    AcGePoint3dArray&    snapPoints,
    AcDbIntArray&   geomIds) const
{
    assertReadEnabled();

    switch(osnapMode) {

    case AcDb::kOsModeEnd:
        return osnapEnd(pickPoint, snapPoints);
    case AcDb::kOsModeNear:
        return osnapNear(pickPoint, snapPoints);
    case AcDb::kOsModeMid:
        return osnapMid(pickPoint, snapPoints);
    case AcDb::kOsModeCen:
        return osnapCen(pickPoint, snapPoints);
    case AcDb::kOsModeQuad:
        return osnapQuad(pickPoint, snapPoints);
    case AcDb::kOsModeNode:
    case AcDb::kOsModeIns:
    case AcDb::kOsModePerp:
    case AcDb::kOsModeTan:
    default:
        break;
    }
    return Acad::eInvalidInput;
}

Acad::ErrorStatus
Jblob::getGripPoints(
    AcGePoint3dArray& gripPoints,
    AcDbIntArray& osnapMasks,
    AcDbIntArray& geomIds) const
{
    assertReadEnabled();

    // add all the grip points of a line and a circle, i.e. line endpoints
    // and circle center and quad points. Make use of AcGeVector3d features.
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following 9 lines complete this...

    gripPoints.append(mp);
    gripPoints.append(mp + 0.5 * (mpblob - mp));
    gripPoints.append(mpblob);
    AcGeVector3d xoff(mrblob, 0, 0);
    AcGeVector3d yoff(0, mrblob, 0);
    gripPoints.append(mpblob + xoff);
    gripPoints.append(mpblob + yoff);
    gripPoints.append(mpblob - xoff);
    gripPoints.append(mpblob - yoff);

    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::moveGripPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    AcGePoint3d oldquad, newquad;

    assertWriteEnabled();

    for (int i = 0; i < indices.length(); i++) {
        int idx = indices[i];
        switch(idx) {
        case 0:
            mp += offset;
            continue; // stretch begin point
        case 1:
            mp += offset;
            mpblob += offset;
            continue; // move
        case 2:
            mpblob += offset;
            continue; // stretch blob center

        // stretch blob radius:
        //
        case 3:
            oldquad = mpblob + AcGeVector3d(mrblob, 0, 0);
            break;
        case 4:
            oldquad = mpblob + AcGeVector3d(0, mrblob, 0);
            break;
        case 5:
            oldquad = mpblob - AcGeVector3d(mrblob, 0, 0);
            break;
        case 6:
            oldquad = mpblob - AcGeVector3d(0, mrblob, 0);
            break;
        }
        newquad = oldquad + offset;
        mrblob = newquad.distanceTo(mpblob);

        // update other grip points as well?
    }
    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::getStretchPoints(AcGePoint3dArray& stretchPoints) const
{
    AcDbIntArray osnapModes;
    AcDbIntArray geomIds;

    assertReadEnabled();

    //  getStretchPoints == getGripPoints
    //
    return getGripPoints(stretchPoints, osnapModes, geomIds);
}

Acad::ErrorStatus
Jblob::moveStretchPointsAt(const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();

    //  moveStretchPointsAt == moveGripPointsAt
    //
    return moveGripPointsAt(indices, offset);
}

Acad::ErrorStatus
Jblob::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

    AcGePoint3d xquad = mpblob + AcGeVector3d(mrblob, 0, 0);
    xquad.transformBy(xform);
    mp.transformBy(xform);
    mpblob.transformBy(xform);
    mrblob = mpblob.distanceTo(xquad);

    return Acad::eOk;
}


// This function is called whenever a saveasr12 command is executed
// in AutoCAD or a DWG save is occurring that requires proxy graphics
// to be saved.  Overriding this function allows control of the graphics
// that will be stored in these two cases.
//
// For this sample,  when a Jblob is being saved for R12,  the text
// "R12JBLOB" is written in the middle of the Jblob's circle.  For
// proxy graphics,  the word "PROXY" is written in the circle instead.
//
void
Jblob::saveAs(AcGiWorldDraw* wd, AcDb::SaveType saveType)
{
    AcGePoint3d line[2];

    line[0] = mp;
    line[1] = mpblob;
    wd->geometry().polyline(2, line);
    wd->subEntityTraits().setFillType(kAcGiFillNever);
    wd->geometry().circle(mpblob, mrblob, mnormal);

    // saveType == AcDb::kR12Save for saveasr12
    // saveType == AcDb::kR13Save for proxy graphics save
    //
    char buff[9];
    short len;
    if (saveType == AcDb::kR12Save) {
        strcpy(buff, "R12JBLOB");
        len = 8;
    } else if (saveType == AcDb::kR13Save) {
        strcpy(buff, "PROXY");
        len = 5;
    }
    AcGePoint3d position((mpblob[0] - mrblob) + (0.2 * mrblob),
        mpblob[1] - 1.2 * mrblob/len, mpblob[2]);

    wd->geometry().text(position, mnormal, AcGeVector3d(1.0,0.0,0.0),
        2.3 * mrblob/len, 0.8, 0.0, buff);
}


Acad::ErrorStatus
Jblob::osnapNear(const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // for osnap near, define the same points as the grip points.
    // This definitely not the proper implementation,  but it is
    // adequate for this simple sample.
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following 9 lines complete this...

    snapPoints.append(mp);
    snapPoints.append(mp + 0.5 * (mpblob - mp));
    snapPoints.append(mpblob);
    AcGeVector3d xoff(mrblob, 0, 0);
    AcGeVector3d yoff(0, mrblob, 0);
    snapPoints.append(mpblob + xoff);
    snapPoints.append(mpblob + yoff);
    snapPoints.append(mpblob - xoff);
    snapPoints.append(mpblob - yoff);
    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::osnapEnd(const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // osnap end to the two endpoints of the line
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following 2 lines complete this...

    snapPoints.append(mp);
    snapPoints.append(mpblob);

    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::osnapMid(const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // osnap mid to the line midpoint
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following line completes this...

    snapPoints.append(mp + 0.5 * (mpblob - mp));

    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::osnapCen(const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // osnap center to the circle's center
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following line completes this...

    snapPoints.append(mpblob);

    return Acad::eOk;
}

Acad::ErrorStatus
Jblob::osnapQuad(const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // osnap quad to the circle's quad points
    //
    // NOTE:  The AcGePoint3dArray passed into this function may not be
    // empty,  so be sure to append points to it instead of assigning values
    // to existing elements.
    //
    // ... The following 6 lines complete this...

    AcGeVector3d xoff(mrblob, 0, 0);
    AcGeVector3d yoff(0, mrblob, 0);
    snapPoints.append(mpblob + xoff);
    snapPoints.append(mpblob + yoff);
    snapPoints.append(mpblob - xoff);
    snapPoints.append(mpblob - yoff);

    return Acad::eOk;
}
