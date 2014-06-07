//
// (C) Copyright 2002-2003 by Autodesk, Inc. 
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
//  DESCRIPTION:  
//
//  Interface and classes that implements pickfirst based sub selection
//  and 'picking in space' for entities in a pickfirst set through
//  using a callback mechanism with the AcEdInputPointManager and
//  a specific kind of AcEdInputContextReactor.

#include "acedinpt.h"


typedef AcArray<AcDbFullSubentPath,
        AcArrayObjectCopyReallocator<AcDbFullSubentPath> > AcSubentPathArray;

class AcGiViewport;

// This is the main class which contains all the implementation for
// 'pick in space' hit testing and 'sub-entity-selection' based on
// callbacks from the AcEdInputPointManager. This is a Filter class,
// i.e. needs to be registered with the AcEdInputPointManager
// through addSubSelectFilter(), and likewise removed by 
// removeSubSelectFilter() when the application is unloaded.
// 
// For each type of entity that supports this kind of sub-selection
// it is expected that they will derive a concrete SubSelect filter
// from AcEdSSetSubSelectFilter, and implement the necessary methods
// indicated below.
//
class AcEdSubSelectFilter
{
public:

    enum SubSelectStatus
    {
        kSubSelectionNone = 0,  // No selection found
        kSubSelectionAugment,   // Add to the pickfirst set
        kSubSelectionExclusive, // Remove other entities from the pickfirst set
        kSubSelectAll           // Select the full entity        
    };

    /**
     * Gets called by the AcEdInputPointManager instance when
     * the Filter is registered. This method is used to determine
     * which Filter to call back for doing 'pick in face' selection
     * for a candidate entity in the pickfirst set or ssget.
     *
     * In case of multiple filters registering themselves for the
     * same class, the first one wins.
     *
     * The internal tests use isKindOf(), i.e. derivation, to check
     * if a filter applies to a candidate entity or not.
     *
     * @param   clsIds  list of classes associated with the filter.
     *
     * @returns eOk if successful.
     */
    virtual Acad::ErrorStatus subSelectClassList(AcArray<AcRxClass*>& clsIds)
    { return Acad::eOk; }


    // The following three methods do the subselection and sub-highlight.

    /**
     * This method is used to ask the application to do the actual
     * hit test, testing for the point in an entity.
     *
     * @param   wvpt    world pick point
     * 
     * @param   wvwdir   world view direction (-z axis of view coord system)
     *
     * @param   wvwxdir  world x axis direction of view coordinate system
     *
     * @param   wxaper  aperture x rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   wyaper  aperture y rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   pEnt    AcDbEntity that is to be tested.
     *
     * @returns true if point is in the entity.
     */
    virtual bool selectEntity(
            const AcGePoint3d&  wvpt, 
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
            double              wxaper,
            double              wyaper,
            const AcGiViewport* pCurVp,
            AcDbEntity*         pEnt) const
    { return false; }

    /**
     * If the above method, i.e. hitTestEntity() returns true, 
     * then createSubSelect() will be invoked by the Input Point Manager,
     * requesting a list of sub-selections that will get highlighted.
     *
     * @param   wpt1    corner1 of box in world coordinates
     *
     * @param   wpt2    corner2 of box in world coordinates 
     *
     * @param   wvdir   world view direction
     *
     * @param   wvwxdir  world Xaxis direction of view coordinate system
     *
     * @param   wxaper  aperture x rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   wyaper  aperture y rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   seltype one of AcDb::kCrossing or AcDb::kWindow.
     * 
     * @param   bAugment if true, add to current subselection instead of
     *                   replacing it.
     *
     * @param   bIsInPickfirst if true - the entity is already in the pickfirst
     *                  set. If false, the pickfirst logic will attempt
     *                  to subselect the entity directly if desired.
     * 
     * @param   pCurVP  current viewport in which selection is occurring
     * 
     * @param   pEnt    Entity to be sub-select tested against
     *
     * @param   paths   Result set of subentity paths.
     *
     * @result one of kSubSelectionNone, kSubSelectionAugment,
     *         kSubSelectionExclusive. kSubSelectionExclusive
     *         will remove any other selection in the pickfirst
     *         set, while kSubSelectionAugment will not change
     *         existing contents of the set.
     */
    virtual SubSelectStatus subSelectEntity(
            const AcGePoint3d&  wpt1,
            const AcGePoint3d&  wpt2,
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
            double wxaper,
            double wyaper,                             
            AcDb::SelectType    seltype,
            bool                bAugment,
            bool                bIsInPickfirstSet,
            const AcGiViewport* pCurVP,
            AcDbEntity*         pEnt,
            AcSubentPathArray&  paths)
    { return kSubSelectionNone; }


    /**
     * Invoked to re-select, if necessary, based on the current entity
     * sub-selection state. Where the state is remembered is really upto
     * the Filter/Entity implementation.
     *
     * If the entity needs to have its sub-selection recomputed, this
     * method should modify paths to reflect the correct new subselection.
     * If the entity does not need to make any changes, paths will be left
     * alone.
     * 
     * @param pEnt   the entity whose subselection is being refreshed
     *
     * @param paths  the current list of Full Subent paths that reflect the
     *               current subselection state of the entity. This is both
     *               and input and output argument. The entity can modify this
     *               to reflect the true subentity paths for its current
     *               subselection state. Else it can leave them alone.
     *
     * @returns   true if the entity altered the paths argument. False if not
     */
    virtual bool reSubSelectEntity(AcDbEntity* pEnt,
            AcSubentPathArray& paths)
    { return false; }
    /**
     * In case the sub-selection is cancelled, the reactor is notified
     * by this method. Typical uses of this filter include tracking
     * sub selection state within the reactor. So this method says
     * to clear that state.
     *
     * @param    id    entity whose state is to be cancelled.
     *
     * @returns true if the entity was actually sub-selected.
     */
    virtual bool cancelSubSelect(AcDbEntity* pEnt)
    { return false; }

    /**
     * Similar method to cancelSubSelect, except - all entities
     * have been un-subselected, and the filter must take
     * appropriate action
     *
     * @returns true if an entity was actually sub-selected.
     */
    virtual bool cancelAllSubSelect()
    { return false; }


    /**
     * React to keyboard input - and take appropriate action,
     * if necessary. This is invoked only for the currently active filters.
     *
     * @param wMsg  windows message, one of
     *              WM_SYSKEYDOWN
     *              WM_SYSKEYUP
     *              WM_KEYDOWN
     *              WM_KEYUP
     *              WM_CHAR
     *              etc.
     *              
     * @param char  character typed
     *
     * @param rptcnt repetition count
     *
     * @param flags  windows flags (see OnKeyDown())
     *
     * @returns true if message was intercepted and no more processing
     *   by other filters must happen. False if it is ok for the controlling
     *   logic to invoke other filters' onKeyDown() message handling.
     */
    virtual bool onKey(unsigned long wMsg, unsigned int nChar, 
            unsigned int rptCnt, unsigned int flags)
    { return false; }


    /**
     * @returns true if the entity is subselected.
     */
    virtual bool isSubSelected(AcDbEntity* pEnt) const
    { return false; }

};

