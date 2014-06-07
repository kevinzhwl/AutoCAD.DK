// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// HILIT.CPP 
//
// DESCRIPTION:
//
// This file contains the sample code exercising the highlight
// methods.


#include "adslib.h"
#include "dbents.h"
#include "dbsol3d.h"

#include "gepnt3d.h"

#include "poly.h"
#include "util.h"


// Static functions used in this file
//
static int extractEntityInfo(struct resbuf *rb,
                             int&           sel_method,
                             ads_name       ename,
                             ads_name       subname,
                             short&         marker,
                             AcGePoint3d&   pickpnt,
                             AcGeVector3d&  pickvec);

static void pressEnterToContinue();

void 
hilitPoly()
{
	Adesk::Boolean interrupted = Adesk::kFalse;
    ads_printf("\nSelect a poly");

    AsdkPoly    *poly = NULL;
    AcDbEntity  *ent = NULL;
    AcDbObjectId polyId;
    ads_name     ename, sset;

    for (;;) {

        switch (ads_ssget(NULL, NULL, NULL, NULL, sset)) {

        case RTNORM:

        // Get the poly from the selection set and do some subentity
        // highlighting testing.
        //
        // This code assumes that the user selected only one item.

        {
            struct resbuf *rb;
            if (ads_ssnamex(&rb, sset, 0) != RTNORM) {
                ads_ssfree(sset);
                return;
            }
            int            sel_method;
            ads_name       subname;
            short          marker;
            AcGePoint3d    pickpnt;
            AcGeVector3d   pickvec;

            if (!extractEntityInfo(rb,
                              sel_method,
                              ename,
                              subname,
                              marker,
                              pickpnt,
                              pickvec)) {
                ads_ssfree(sset);
                return;
            }

            AOK(acdbGetObjectId(polyId, ename));

            AOK(acdbOpenAcDbEntity(ent, polyId, AcDb::kForRead));
            assert(ent != NULL);

            poly = AsdkPoly::cast(ent);
            if (poly == NULL) {
                ads_printf("\nNot a polygon.");
                AOK(ent->close());
                ads_ssfree(sset);
                continue;
            }

            // Get the subentity and highlight it.

            int                  numPaths;
            AcDbFullSubentPath*  subentPaths;
            AcGeMatrix3d         xform;
            poly->getSubentPathsAtGsMarker( AcDb::kEdgeSubentType,
                                            marker,
                                            pickpnt,
                                            xform,
                                            numPaths,
                                            subentPaths);
            if(numPaths == 1)
            {
                // Highlight and unhighlight the subentity.
                //
                ads_printf("\nHighlighting the subentity");
                poly->highlight(subentPaths[0]);
                pressEnterToContinue();
                poly->unhighlight(subentPaths[0]);
            }
            else
            {
                // No path, user selected a section without a marker,
                // the text label for example
                //
                ads_printf("\nNo subentity to highlight");
            }

            // Highlight and unhighlight the whole entity.
            //
            ads_printf("\nHighlighting the whole entity");
            poly->highlight();
            pressEnterToContinue();
            poly->unhighlight();

            delete []subentPaths;
            ads_ssfree(sset);
        }
        break;

        case RTNONE:
        case RTCAN:
            return;
        default:
            continue;
        }
        ads_ssfree(sset);
        break;
    }
    AOK(ent->close());
    return;
}
 
void 
hilitSolid()
{
	Adesk::Boolean interrupted = Adesk::kFalse;
    ads_printf("\nSelect a solid");

    Acad::ErrorStatus es = Acad::eOk;

    AcDb3dSolid *solid = NULL;
    AcDbEntity  *ent = NULL;
    AcDbObjectId solidId;
    ads_name     ename, sset;

    for (;;) {

        switch (ads_ssget(NULL, NULL, NULL, NULL, sset)) {

        case RTNORM:
        {
            struct resbuf *rb;
            if (ads_ssnamex(&rb, sset, 0) != RTNORM) {
                ads_ssfree(sset);
                return;
            }
            int            sel_method;
            ads_name       subname;
            short          marker;
            AcGePoint3d    pickpnt;
            AcGeVector3d   pickvec;

            if (!extractEntityInfo(rb,
                              sel_method,
                              ename,
                              subname,
                              marker,
                              pickpnt,
                              pickvec)) {
                ads_ssfree(sset);
                return;
            }

            AOK(acdbGetObjectId(solidId, ename));

            AOK(acdbOpenAcDbEntity(ent, solidId, AcDb::kForRead));
            assert(ent != NULL);

            solid = AcDb3dSolid::cast(ent);
            if (solid == NULL) {
                ads_printf("\nNot a solid.");
                AOK(ent->close());
                ads_ssfree(sset);
                continue;
            }

            int                  numPaths;
            AcDbFullSubentPath*  subentPaths;
            AcGeMatrix3d         xform;
            es = solid->getSubentPathsAtGsMarker( AcDb::kEdgeSubentType,
                                            marker,
                                            pickpnt,
                                            xform,
                                            numPaths,
                                            subentPaths);
            // For objects with no edges (such as a sphere) the code to
            // highlight an edge is meaningless and must be skipped.
            //
            if (numPaths > 0) {

                // Highlight and unhighlight the selected edge of the solid.
                //
                ads_printf("\nHighlighting the selected edge.");
                es = solid->highlight(subentPaths[0]);
                pressEnterToContinue();
                es = solid->unhighlight(subentPaths[0]);
            } else
                ads_printf("\nNo edges to highlight.");
            delete []subentPaths;

            // Highlight and unhighlight the faces corresponding to the
            // first edge of the solid.
            //
            es = solid->getSubentPathsAtGsMarker( AcDb::kFaceSubentType,
                                            marker,
                                            pickpnt,
                                            xform,
                                            numPaths,
                                            subentPaths);
            for (int i = 0; i < numPaths; i++) {
                ads_printf("\nHighlighting face %d of %d", i + 1, numPaths);
                es = solid->highlight(subentPaths[i]);
                pressEnterToContinue();
                es = solid->unhighlight(subentPaths[i]);
            }
            delete []subentPaths;
            ads_ssfree(sset);

            // Highlight the entire solid, then unhighlight it.
            //
            ads_printf("\nHighlighting the entire solid");
            es = solid->highlight();
            pressEnterToContinue();
            es = solid->unhighlight();
        }
        break;
        case RTNONE:
        case RTCAN:
            return;
        default:
            continue;
        }
        ads_ssfree(sset);
        break;
    }

    AOK(ent->close());
    return;
}

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void 
createInsert()
{
    // Create a nested insert and try highlighting its
    // various subcomponents.
    //
    // There are six entities in total -- three polys and
    // three boxes (solids). We,ve named them: poly1, poly2,
    // poly3, and box1, box2, box3. We also have three
    // inserts: ins1, ins2, ins3.
    //
    // ins3 is insert of a block that contains (poly3, box3)
    // ins2 is insert of a block that contains (poly2, box2,
    // ins3).
    // ins1 is insert of a block that contains (poly1, box1,
    // ins2).
    //
    // Let's create these entities first.
    //

    // Polys
    //
    AsdkPoly *poly1, *poly2, *poly3;
    AcGeVector3d norm(0, 0, 1);
    if ((poly1=new AsdkPoly)==NULL){
        ads_printf("\nOut of Memory.");
        return;
    }
    if (poly1->set(AcGePoint2d(2, 8),AcGePoint2d(4, 8), 6, norm, "POLY1",0)!=Acad::eOk){
        ads_printf("\nCannot create object with given parameters.");
        delete poly1;
        return;
    }
    if ((poly2=new AsdkPoly)==NULL){
        ads_printf("\nOut of Memory.");
        delete poly1;
        return;
    }
    if (poly2->set(AcGePoint2d(7, 8), AcGePoint2d(9, 8), 6, norm, "POLY2",0)!=Acad::eOk){
        ads_printf("\nCannot create object with given parameters.");
        delete poly1;
        delete poly2;
        return;
    }
    if ((poly3=new AsdkPoly)==NULL){
        ads_printf("\nOut of Memory.");
        delete poly1;
        delete poly2;
        return;
    }
    if (poly3->set(AcGePoint2d(12, 8),AcGePoint2d(14, 8), 6, norm, "POLY3",0)!=Acad::eOk){
        ads_printf("\nCannot create object with given parameters.");
        delete poly1;
        delete poly2;
        delete poly3;
        return;
    }
    postToDb(poly1);
    postToDb(poly2);
    postToDb(poly3);

    // Boxes
    //
    AcDb3dSolid *box1, *box2, *box3;
    box1 = new AcDb3dSolid(); 
    box2 = new AcDb3dSolid();
    box3 = new AcDb3dSolid();

    box1->createBox(2, 2, 2);
    box2->createBox(2, 2, 2);
    box3->createBox(2, 2, 2);

    AcGeMatrix3d mat;

    mat(0, 3) = 2; mat(1, 3) = 2;
    box1->transformBy(mat);
    mat(0, 3) = 7; mat(1, 3) = 2;
    box2->transformBy(mat);
    mat(0, 3) = 12; mat(1, 3) = 2;
    box3->transformBy(mat);

    postToDb(box1);
    postToDb(box2);
    postToDb(box3);

    // Inserts
    //
    // Arguments to BLOCK are:
    //      blockname,
    //      insert point, 
    //      select objects,
    //      empty string for selection complete
    // Arguments to INSERT are:
    //      blockname,
    //      insertion point,
    //      xscale,
    //      yscale,
    //      rotation angle
    //
    ads_command(RTSTR, "_globcheck", RTSHORT, 0, RTNONE);

    ads_command(RTSTR, "BLOCK", RTSTR, "blk3", RTSTR, "0,0",
                RTSTR, "14,8", RTSTR, "11,1", RTSTR, "",
                RTNONE);

    ads_command(RTSTR, "INSERT", RTSTR, "blk3", RTSTR,
                "0,0", RTSHORT, 1, RTSHORT, 1, RTSHORT,
                0, RTNONE);

    ads_command(RTSTR, "BLOCK", RTSTR, "blk2", RTSTR, "0,0",
                RTSTR, "9,8", RTSTR, "6,1", RTSTR, "11,1",
                RTSTR, "", RTNONE);

    ads_command(RTSTR, "INSERT", RTSTR, "blk2", RTSTR,
                "0,0", RTSHORT, 1, RTSHORT, 1, RTSHORT,
                0, RTNONE);

    ads_command(RTSTR, "BLOCK", RTSTR, "blk1", RTSTR, "0,0",
                RTSTR, "4,8", RTSTR, "1,1", RTSTR, "6,1",
                RTSTR, "", RTNONE);

    ads_command(RTSTR, "INSERT", RTSTR, "blk1", RTSTR,
                "0,0", RTSHORT, 1, RTSHORT, 1, RTSHORT,
                0, RTNONE);

    return;
}

void 
hilitInsert()
{
	Adesk::Boolean interrupted = Adesk::kFalse;
    ads_printf("\nSelect an insert");

    Acad::ErrorStatus es = Acad::eOk;
    AcDbEntity  *ent = NULL;
    AcDbEntity  *ent2 = NULL;
    AcDbBlockReference *blRef = NULL;
    AcDbObjectId objectId, blRefId;
    ads_name     ename, sset;

    for (;;) {
        switch (ads_ssget(NULL, NULL, NULL, NULL, sset)) {
        case RTNORM:
        {
            struct resbuf *rb;
            if (ads_ssnamex(&rb, sset, 0) != RTNORM) {
                ads_printf("\nads_ssnamex failed");
                ads_ssfree(sset);
                return;
            }

            int            sel_method;
            ads_name       subname;
            short          marker;
            AcGePoint3d    pickpnt;
            AcGeVector3d   pickvec;

            if (!extractEntityInfo(rb,
                              sel_method,
                              ename,
                              subname,
                              marker,
                              pickpnt,
                              pickvec)) {
                ads_printf("\nextractEntityInfo failed");
                ads_ssfree(sset);
                return;
            }

            ads_ssfree(sset);

            assert(marker != 0);
            if (marker == 0) {
                ads_printf("\nmarker == 0");
                return;
            }

            // Get the insert first.
            //
            AOK(acdbGetObjectId(blRefId, ename));
            AOK(acdbOpenAcDbEntity(ent, blRefId,
                AcDb::kForRead));
            assert(ent != NULL);

            blRef = AcDbBlockReference::cast(ent);
            if (blRef == NULL) {
                ads_printf("\nNot an insert.");
                AOK(ent->close());
                continue;
            }

            struct resbuf *insStack;
            ads_point pickpoint;
            ads_matrix adsmat;

            pickpoint[0] = pickpnt[0];
            pickpoint[1] = pickpnt[1];
            pickpoint[2] = pickpnt[2];
           
            // Now get details on the entity that was
            // selected.
            // 
            if (ads_nentselp(NULL, ename, pickpoint, TRUE,
                adsmat, &insStack) != RTNORM)
            {
                ads_printf("\nFailure in ads_nentselp");
                return;
            }
            assert(insStack != NULL);

            AOK(acdbGetObjectId(objectId, ename));
            AOK(acdbOpenAcDbEntity(ent2, objectId,
                AcDb::kForRead));
            assert(ent2 != NULL);

            // Make an array of AcDbObjectIds from the
            // insertStack.  Don't use the "smart array" 
            // AcDbObjectIdArray class, because the 
            // getSubentPathsAtGsMarker() function expects argument
            // eight to be of type AcDbObjectId*. Just 
            // make room for approximately 100 IDs in the array.
            //
            AcDbObjectId *idArray = new AcDbObjectId[100];
            int count = 0;
            struct resbuf *rbIter = insStack; 
            AcDbObjectId objId;
            acdbGetObjectId(objId, ename);
            idArray[count++] = objId;

            while (rbIter != NULL) {
                ename[0] = rbIter->resval.rlname[0];
                ename[1] = rbIter->resval.rlname[1];
                acdbGetObjectId(objId, ename);
                idArray[count++] = objId;

                rbIter = rbIter->rbnext;
            }
            count--;

            ads_relrb(insStack);

            // First, we'll highlight an edge.
            //
            int                  numPaths;
            AcDbFullSubentPath  *subentPaths;
            AcGeMatrix3d         xform;
            es = blRef->getSubentPathsAtGsMarker(
                AcDb::kEdgeSubentType,
                marker,
                pickpnt,
                xform,
                numPaths,
                subentPaths,
                count,
                idArray);

            assert(numPaths == 1);

            // Highlight and unhighlight the selected edge.
            //
            ads_printf("\nHighlighting the first edge.");
            es = blRef->highlight(subentPaths[0]);
            pressEnterToContinue();
            es = blRef->unhighlight(subentPaths[0]);

            // If this is a solid, it will have faces.
            // In this case, let's highlight them.
            //
            if(ent2->isKindOf(AcDb3dSolid::desc())) {
                es = blRef->getSubentPathsAtGsMarker(
                    AcDb::kFaceSubentType,
                    marker,
                    pickpnt,
                    xform,
                    numPaths,
                    subentPaths,
                    count,
                    idArray);
                assert(numPaths == 2);

                // Highlight and unhighlight the selected
                // faces.
                //
                ads_printf("\nHighlighting the first"
                    " face.");
                es = blRef->highlight(subentPaths[0]);
                pressEnterToContinue();
                es = blRef->unhighlight(subentPaths[0]);

                ads_printf("\nHighlighting the next face.");
                es = blRef->highlight(subentPaths[1]);
                pressEnterToContinue();
                es = blRef->unhighlight(subentPaths[1]);
            }
            delete []subentPaths;

            // Now, let's highlight the whole entity.
            //
            ads_printf("\nHighlighting the entire entity");

            AcDbFullSubentPath subPath;

            for (int i = count; i >= 0; i--) {
                subPath.objectIds().append(idArray[i]);
            }
            es = blRef->highlight(subPath);
            pressEnterToContinue();
            es = blRef->unhighlight(subPath);

            // Finally, let's highlight each enclosing
            // insert.
            //
            for (i = count -1; i >= 0; i --) {
                subPath.objectIds().removeAt(
                    subPath.objectIds().length() - 1);
                ads_printf("\nHighlighting insert layer %d",
                    i + 1);
                blRef->highlight(subPath);
                pressEnterToContinue();
                es = blRef->unhighlight(subPath);
            }

        } // case RTNORM
            break;
        case RTNONE:
        case RTCAN:
            return;
        default:
            continue;
        } // switch
        break;
    } //for (;;)

    AOK(ent->close());
    AOK(ent2->close());
    return;
}

// END CODE APPEARING IN SDK DOCUMENT.

/************************************************************************
 Function:      extractEntityInfo()

 Description:   This function searches through the given resbuf list
                describing the entity and returns entity information.  The
                list must conform to the format returned by ads_ssnamex.
                It is assumed that ads_ssnamex() is being called to retrieve
                one entity at a time, not the entire selection set.

 Inputs:        rb - The resbuf which we are seaching through. It is expected
                     that this point to the beginning of the list or sublist 
                     (RTLB).  This routine will assert if it doesn't.  rb is 
                     used to traverse the list, but since the pointer itself 
                     is passed by value, the caller's pointer will not change.

 Outputs:       sel_method - will be filled with the selection method.
                ename -   will be filled with the name of the entity 
                          (corresponds to the top level container block).  
                          If ename is returned (0,0), then no ename info 
                          was in the list (indicates the list referred to 
                          polygon/window points only).
                subname - will be filled with the name of the subentity that
                          was picked (PICK method only).  If entity is not
                          complex (no subentities), or a method other than PICK
                          was used, then subname will equal ename.
                marker -  the GS marker for the selected entity.
                pickpt -  will be filled with the pick point if selection method
                          concerns location; otherwise, it is not modified.
                          Caller must test selection method to determine how to
                          deal with the pickpt.
                pickvec - will be filled with the pick point's projection vector
                          if selection method concerns location; otherwise, it
                          is not modified.
                          Caller must test selection method to determine how to
                          deal with the pickvec.

                Return value - CONTINUE if entity info was extracted, CANCEL if
                               there was an error.  If CANCEL is returned, then
                               the other outputs are not set.
  //
  // ads_ssnamex list format.  The restype of each resbuf is shown.
  //
  // For pick method:
  //    5016 -- start of entity
  //    5003 -- selection method
  //    5006 -- picked entity's name (could be subname)
  //    5003 -- GS marker
  //    5016 -- start of list for pick point
  //    5003 -- point description, not used.
  //    5009 -- pick location (WCS)
  //    5009 -- (only if view is not XY) normal vector for point
  //    5017 -- end of list for pick point
  //    5009 -- xform data (X vector in rotation matrix)
  //    5009 -- xform data (Y vector in rotation matrix)
  //    5009 -- xform data (Z vector in rotation matrix)
  //    5009 -- xform data (Translation vector)
  //    5006 -- (only if applicable) first block in ads_nentselp-style list
  //             of containing blocks.
  //    :    -- (only if applicable) etc. for rest of containing blocks.
  //    5017 -- end of entity
  //
  // For fence method:
  //    5016 -- start of entity
  //    5003 -- selection method
  //    5006 -- picked entity's name (could be subname)
  //    5003 -- GS marker
  //    5016 -- start of list for first fence intersection with entity.
  //    5003 -- point description, not used.
  //    5009 -- pick location (WCS)
  //    5009 -- (only if view is not XY) normal vector for point
  //    5017 -- end of list for first fence intersection with entity.
  //    :    -- etc. for rest of fence points
  //    5017 -- end of entity
  //
  // For crossing, window, crossing polygon, and window polygon methods:
  //    5016 -- start of entity
  //    5003 -- selection method
  //    5006 -- pick entity's name
  //    5003 -- GS marker
  //    5003 -- polygon/window ID.
  //    5017 -- end of entity
  //    5016 -- Start of polygon/window pick points
  //    5003 -- Polygon/Window ID.
  //    5016 -- Start of first point
  //    5003 -- point description, not used.
  //    5009 -- pick location (WCS)
  //    5009 -- (only if view is not XY) normal vector for point
  //    5017 -- end of first point.
  //    :    -- etc. for rest of polygon/window pick points.
  //    5017 -- end of polygon/window pick points.
  //
  // For all method and groups (no location or container information):
  //    5016 -- start of entity
  //    5003 -- selection method
  //    5006 -- picked entity's name
  //    5003 -- GS marker
  //    5017 -- end of entity
  //
  // Note that the crossing methods currently have a bug that returns the
  // the subentities in block entities instead of only the block entity.
  // Each subentity returned will have containing block information.
  //

***********************************************************************/

#define CONTINUE 1
#define CANCEL   0

#define PICK_METH 1
#define FENCE_METH 4

static int extractEntityInfo(struct resbuf *rb,
                             int&          sel_method,
                             ads_name      ename,
                             ads_name      subname,
                             short&	   marker,
                             AcGePoint3d&  pickpnt,
                             AcGeVector3d& pickvec)
{
   if ( rb == NULL || rb->restype != RTLB )
   {
     assert(0);
     return 0;
   }
   
   // Get the selection method.
   //
   rb = rb->rbnext;  // Bump up to the selection method, always after RTLB.
   sel_method = rb->resval.rint;

   // Get the first ename (could be either the actual entity name or
   // subentity name).
   //
   rb = rb->rbnext;  // Bump up to the first name, always after sel method.
   ename[0] = rb->resval.rlname[0];
   ename[1] = rb->resval.rlname[1];
   subname[0] = rb->resval.rlname[0];
   subname[1] = rb->resval.rlname[1];

   // Get marker info.
   //
   rb = rb->rbnext;
   marker = rb->resval.rint;

   // Get the pick location and vector, only for PICK and FENCE.  For FENCE,
   // we take the first intersection with the entity as the pick location.
   //
   if ( sel_method == PICK_METH || 
        sel_method == FENCE_METH)
   {
      rb = rb->rbnext;  // Skip to RTLB for pick location.
      rb = rb->rbnext;  // Skip to point description info.
      rb = rb->rbnext;  // Skip to the pick location.
      pickpnt.set( rb->resval.rpoint[0],
                   rb->resval.rpoint[1],
                   rb->resval.rpoint[2] );

      rb = rb->rbnext;  // Will be normal vector if we're not in XY view.
                        // Otherwise, it'll be an RTLE for pick location.

      if ( rb->restype == RT3DPOINT )
      {
        pickvec.set( rb->resval.rpoint[0],
                     rb->resval.rpoint[1],
                     rb->resval.rpoint[2] );
        rb = rb->rbnext;  // Make it point to the RTLE for the pick location.
      }
   }

   return CONTINUE;
}

/************************************************************************
 Function:      pressReturnToContinue

 Description:   This function displays the prompt "Press RETURN to continue."
                any waits for the user to press return.  

 Inputs:        None.

 Outputs:       None.

***********************************************************************/
static void
pressEnterToContinue()
{
   char tempBuf[133];
   ads_getstring(0, "\nPress <ENTER> to continue.", tempBuf);
}
