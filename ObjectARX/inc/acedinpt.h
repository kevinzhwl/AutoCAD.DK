//
// (C) Copyright 1998-2008 by Autodesk, Inc. 
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
//  acedinpt.h - Definition of AcEdInputPointManager and related stuff

#ifndef _ACEDINPT_H
#define _ACEDINPT_H

#include "rxobject.h"
#include "dbmain.h"

#pragma pack (push, 8)

#pragma warning (disable: 4786)

class AcEdInputPointFilter;
class AcEdInputPointMonitor;
class AcApDocument;
class AcEdInputContextReactor;
class AcDbCustomOsnapMode;
class AcEdSubSelectFilter;

// AcEdInputPointManager defines the manager object for registered
// custom OSNAP modes, custom AutoSnap callbacks and point filter callbacks.
//
class AcEdInputPointManager
{
  public:

    // registerPointFilter
    //
    // Invoke to register a point filter.  returns Acad::eOK if no filter
    // is currently in use, else returns Acad::eIllegalReplacement.  It's
    // not nice to hog the filter slot!
    //
    virtual Acad::ErrorStatus     registerPointFilter(AcEdInputPointFilter* pFilter) = 0;

    // revokePointFilter
    //
    // Used to revoke the current Point Filter.  Returns Acad::eOk if there
    // was an active point filter, and Acad::eNullObjectPointer if there wasn't
    // one.  It's not nice to revoke someone else's filter!   If you must
    // do so, find out what it is (see currentPointFilter) and put it back,
    // right quick!
    //
    virtual Acad::ErrorStatus     revokePointFilter() = 0;

    // currentPointFilter
    //
    // Returns the active point filter, if there is one, and NULL otherwise.
    //
    virtual AcEdInputPointFilter* currentPointFilter() const = 0;

    // addPointMonitor
    //
    // Used to add a point monitor to the active set.  Adding the same
    // point monitor twice (as compared by address) will cause Acad::eDuplicateKey
    // to be returned.  Each monitor will be invoked once and only once
    // per input point event. Otherwise, Acad::eOk will be returned.
    //
    virtual Acad::ErrorStatus addPointMonitor(AcEdInputPointMonitor* pMonitor) = 0;

    // removePointMonitor
    //
    // Used in remove a Point Monitor from the active set.
    // Returns Acad::eOk if the monitor indicated by the input address
    // was in the set, and Acad::eInvalidKey if it wasn't.
    //
    virtual Acad::ErrorStatus removePointMonitor(AcEdInputPointMonitor* pMonitor) = 0;

    // addInputContextReactor
    //
    // Add an input context reactor.  Find out what the user is currently
    // being prompted for via the AutoCAD Input mechanism (Windows dialogs
    // excluded).  Any number can be added, each reactor can only be added
    // once, same as input point monitors. Adding the same
    // reactor twice (as compared by address) will cause Acad::eDuplicateKey
    // to be returned. Otherwise, Acad::eOk will be returned.
    //
    virtual Acad::ErrorStatus addInputContextReactor(AcEdInputContextReactor* pReactor) = 0;

    // removeInputContextReactor
    //
    // Used in remove an input context reactor from the active set.
    // Returns Acad::eOk if the reactor indicated by the input address
    // was in the set, and Acad::eInvalidKey if it wasn't.
    //
    virtual Acad::ErrorStatus removeInputContextReactor(AcEdInputContextReactor* pReact) = 0;

 
    // Enable and disable cursor graphics for the associated document.
    // Intended for use in conjunction with custom cursor graphics.
    // IMPORTANT: This pair of calls operates on an internal counter, so
    // the system can keep track of multiple applications that wish to
    // suppress the system cursor.

    // disableSystemCursorGraphics
    //
    // Will either return Acad::eOk if it
    // works or Acad::eInvalidContext if there the cursor cannot be
    // disabled.
    //
    // Currenly Acad::eOk is always returned.
    //
    virtual Acad::ErrorStatus disableSystemCursorGraphics() = 0;

    // enableSystemCursorGraphics
    //
    // Returns Acad::eOk unless the disble count was already 0, in which
    // case Acad::eInvalidContext is returned.
    //
    virtual Acad::ErrorStatus enableSystemCursorGraphics() = 0;

    // systemCursorDisableCount
    //
    // Returns the count of callers who have the cursor disabled.
    //
    virtual int systemCursorDisableCount() const = 0;

    // turnOnForcedPick
    //
    // This call causes the AutoCAD input event mechanism to do a pick under the
    // prevailing pick aperture on all digitizer events, regardless of whether a
    // point is being acquired or whether any OSNAP modes are currently active.
    // If a point is being acquired AND OSNAP is active, the (osnap) $APERTURE
    // dimensions define the pickbox size, otherwise the normal $PICKBOX
    // will be used.  In the Acad::PointHistory enum, the following enum values
    // are related to this capability, as indicated by their related comments:
    // eForcedPick, ePickMask, eDidNotPick, eUsedPickBox, eUsedOsnapBox.
    //
    // A count is maintained, so that if multiple apps want to force picking,
    // it occurs until they are all done.
    //
    // Currenly Acad::eOk is always returned.
    //
    virtual Acad::ErrorStatus turnOnForcedPick() = 0;

    // turnOffForcedPick
    //
    // decrements the forced pick counter, and if the counter hits 0,
    // disables forced picking, which means entity picking occurs in "normal
    // circumstances, such as when input points are being acquired and
    // an OSNAP mode is active, or normal entity selection operations.
    // 
    // Returns Acad::eOk unless the forced pick count was already 0, in which
    // case Acad::eInvalidContext is returned.
    //
    virtual Acad::ErrorStatus turnOffForcedPick() = 0;

    // forcedPickCount
    //
    // Returns the count of callers who have forced picking turned on.
    //
    virtual int forcedPickCount() const = 0;

    virtual int mouseHasMoved() const = 0;

    virtual Acad::ErrorStatus turnOnSubentityWindowSelection() = 0;
    virtual Acad::ErrorStatus turnOffSubentityWindowSelection() = 0;

    /**
     * This method registers a sub-selection filter
     *
     *  @param  pSSSubFilter    the sub-selection filter to be registered.
     *  
     *  @returns eSelectFilterError if there is an error when trying to
     *  initialize the filter data, e.g. get a list of AcRxClass* that this
     *  filter applies to. Otherwise, eOk.
     */
    virtual Acad::ErrorStatus addSubSelectFilter(
            AcEdSubSelectFilter* pSSSubFilter) = 0;

    /**
     * This method unregisters a sub-selection filter
     *
     * @param   pSSubFilter   the sub-selection filter to be unregistered.
     *
     * @returns eKeyNotFound if the object does not exist. eOk otherwise.
     */
    virtual Acad::ErrorStatus removeSubSelectFilter(
            AcEdSubSelectFilter* pSSSubFilter) = 0;

};


// AcEdInputPointFilter
//
// This callback protocol defines a combination 
// "Input Point Notification and Input Point filter" mechanism.


class AcEdInputPointFilter : public AcRxObject
{

  public:
    ACRX_DECLARE_MEMBERS(AcEdInputPointFilter);
   
    // processInputPoint
    //
    // This callback is made every time an input event results in an
    // 3D point in the prevailing geometric space.  Such events include:
    // - digitizer motion with the cursor over the active viewport of the
    //   active document window
    // - digitizer motion in TABLET mode in the active document window,
    // - A string entered representing a point, either interactively, by
    //   script, (command) input, menu macro expansion, and Windows Message
    //   loop stuffing.
    // - A LISP expression that evaluates to be a 2D or 3D point.
    //
    // The callback is made after the AutoCAD user input complex has
    // fully processed the point except for XYZ coordinate filtering,
    // at which time AutoCAD will either
    // return the point to a caller, or accept the coordinate(s) being
    // prompted for and return for another point if XYZ coordinage filtering
    // is happening.
    //
    // Output Values
    //
    // The function can return a new "final" point, a new tooltip string, and/or
    // tell the system to reprompt for another point, essentially not returning the
    // the point to the caller.  This reprompting capability can allow things like,
    // say, a polar coordinate filter (first the direction, then the distance).
    //
    // Graphics Output.
    //
    // Graphics output to the current viewport is facilitated by passing in an
    // instance of AcGiViewportDraw*, the viewport drawing context.  This yields
    // the same graphics capability that AcDbEntity::viewportDraw() has at its
    // disposal.
    //
    // Input Values
    //
    // A set of arguments that together described the
    // history of the point computed so far for this particular event,
    // which could be either a digitizer motion or string entered by various
    // means.  Each of the arguments is described in comments below, but the
    // key arguments are:
    // - the "pointComputed" bool, which indicates whether points
    // could even be computed at all (they can't be under certain view conditions
    // where forced picking is enabled, and a pick could be made in spite of the
    // view conditions.  Otherwise, pointComputed will return TRUE.
    // - A "history" mask has bits set indicating what actually happened out
    // of the builtin AutoCAD point processing, plus the point filter, for monitor
    // callbacks.
    // - the point(s) computed by AutoCAD by various builtin filters
    // - entities under the prevailing cursor aperture, if any.
    // - and there are more arguments, as listed and described below.
    //
    // Return Status:  Acad::eOk should always be returned.
    //
    virtual Acad::ErrorStatus processInputPoint(
          // Ouput Values:

          // If changedPoint is kTrue
          // then newPoint has the new point value in it.
          // if pointComputed input was FALSE, then this
          // flag and newPoint are ignored.
          //
          bool&                        changedPoint,
          AcGePoint3d&                 newPoint,
          bool&                        displayOsnapGlyph,

          // If changedTooltipStr is kTrue
          // then newTooltipString has the new tooltip string in it.
          //
          bool&                        changedTooltipStr,
          ACHAR*&                       newTooltipString,

          // retry:  Just as coordinate filters and cursor motion be the
          //         only things that go back and re-prompt/track
          //         for another point?  This way, an app can demand
          //         that the user try again also.
          //
          bool&                        retry,

          // Input/Output
          //
          // drawContext:
          // Input view transform, pixel sizes, etc.
          // Output whatever visible graphics you want to display on
          // drawContext, using AcGi library.
          //
          // NOTE: Used in tandem with
          // AcEdInputPointManager::disableSystemCursorGraphics()
          // and enableSystemCorsorGraphics(), one can effectively draw a
          // custom cursor
          //
          AcGiViewportDraw*           drawContext,

          // Input parameters:
          //
          // Basically a cumulative history of what happened on
          // point during the current input throat event, be it
          // digitizer event or mouse click, from raw cursor
          // location (or tablet mode digitizer UCS point)
          // through snap grid, ortho/alignment mode, OSNAP and
          // Autosnap (aka "Alignment")
          //
          // Not all of the interim points may be deemed worth passing back,
          // but whatever ones wind up here appear in the order that they are
          // computed in.  See "finalPoint", etc. for where things end up.

          // document:  the document object that this callback emanates from.
          //            makes it easier to plant one instance on all input point
          //            managers, and determine which one is making the callback.
          //
          AcApDocument*              document,

          // pointComputed: TRUE if the points below are valid, FALSE if they
          //                are not, in which case forced picking is enabled, and
          //                there may be entities in the pickedEntities argument
          //                below.
          bool                       pointComputed,

          // history:  an integer with bit fields as defined in the
          //           PointHistory enum above.
          //
          int                        history,

          // lastPoint:  valid iff (history & eLastPoint)
          //
          const AcGePoint3d&               lastPoint,

          // rawPoint: what the point is as tracked by the cursor position
          //           before subsequent filtering,
          //           or as entered in via alternate means, which is subject
          //           to far less filtering. valid if pointComputed above
          //           is TRUE
          //
          const AcGePoint3d&               rawPoint,

          // grippedPoint: differs from rawPoint if (history & eGripped)
          //
          const AcGePoint3d&               grippedPoint,

          // cartesianSnappedPoint:  "Old style" snap  differs from grippedPoint
          //                         if (history & eCartSnapped)
          //
          const AcGePoint3d&               cartesianSnappedPoint,

          // OSNAP Info:  Current OSNAP point and the modes in effect,
          // iff pointComputed is TRUE.  if osnapModes is 0 and customOsnapModes
          // is empty, then OSNAP wasn't done (and since the modes are passed in,
          // a bit in history would be redundant, so there isn't one).
   
          const AcGePoint3d&               osnappedPoint,
          AcDb::OsnapMask                  osnapMask,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,

          // OSNAP overrides
          //
          AcDb::OsnapMask                  osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,

          // OSNAP or Forced Pick Info: all the entities in the aperture
          // if ((history & ePickMask) != eDidNotPick)
          // { /* then system tried to pick, either because of OSNAP or
          //      forced picking.  Doesn't necessarily imply anything was
          //      actually picked, but if it did, then results will be in next
          //      two arguments */
          // }
          // and the corresponding gsSelectionMark
          //              
          const AcArray<AcDbObjectId>&     pickedEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedPickedEntities,
          const AcArray<Adesk::GsMarker>&  gsSelectionMark,

          // AutoSnap Info:
          const AcArray<AcDbObjectId>&     keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                           nestedKeyPointEntities,
          const AcArray<Adesk::GsMarker>&  keyPointGsSelectionMark,

          const AcArray<AcGeCurve3d*>&       alignmentPaths,

          // computedPoint:
          // This is where the point ends up for AutoCAD iff pointComputed
          // is TRUE.  It is always set, whether
          // any builtin filters are performed or not.
          // AutoSnap computations could alter it from osnappedPoint.
          // Can be altered by
          // returning new point, as described above.

          const AcGePoint3d&               computedPoint,

          // tooltipString:
          // the final tooltip string, as determined by AutoCAD.  Can be altered by
          // returning new string, as described above.
          const ACHAR*                      tooltipString) = 0;


    // --- end of processInputPoint (big one, eh?)

    // revokeInputFilter
    //
    // This callback is made whenever a filter is revoked.  If another filter
    // has "chained" a registered filter, it should forward this call, and compare
    // the input "revokedFilter" with its own "this" address.  If they match, the
    // filter returns its embedded filter, if there is any, so the calling filter
    // (or AutoCAD) can update its own filter pointer with it.  If they don't match,
    // the filter should forward the call to its embedded filter, if there is any,
    // and return its "this" pointer, which effectively leaves its nesting status
    // unchanged (Note that this is the default behavior).
    // The net effect is to remove the revoked filter from the chain,
    // and leave the rest of the chain alone.  Of course, if an outer filter
    // detects its immediate nested filter as being changed (i.e. removed), it
    // can query the new filter's class and take whatever action is necessary.
    // which is hopefully nothing, else you have an unstable sequence.
    //
    virtual AcEdInputPointFilter* revokeInputFilter
        (AcEdInputPointFilter* revokedFilter)                { return this; }
};

// AcEdInputPointMonitor
//
// This callback Is like point filter, except it cannot alter the point, tooltip
// string, or ask the system to retry.


class AcEdInputPointMonitor : public AcRxObject
{
    public:
    ACRX_DECLARE_MEMBERS(AcEdInputPointMonitor);
    // monitorInputPoint
    //
    // This callback is under the exact same conditions as AcEdInputPointFilter,
    // except that the point filter is invoked first, and can affect the
    // "computed point".
    //
    // The callback is made after the AutoCAD user input complex has
    // fully processed the point except for XYZ coordinate filtering,
    // AND after an app-defined input point filter has processed the point,
    // if one is registered.  After invoking all registered instances of
    // AcEdInputPointMonitor, AutoCAD will either
    // return the point to a caller, or accept the coordinate(s) being
    // prompted for and return for another point if XYZ coordinage filtering
    // is happening.
    //
    // Output Values
    //
    // Unlike AcEdInpoutPointFilter, this function cannot affect the point or
    // influence the prompting, and therefore has none of the Output Value
    // parameters of AcEdInputPointFilter.  However, see graphics output, which
    // is the same for monitors as for filters.
    //
    // Graphics Input/Output.
    //
    // Same as AcEdInputPointFilter
    //
    // Input Values
    //
    // Same as AcEdInputPointFilter, except where noted.
    //
    // Return Status:  Acad::eOk should always be returned.
    //
    virtual Acad::ErrorStatus monitorInputPoint(
 
          // Output
          // If changedTooltipStr is kTrue
          // then newTooltipString has the new tooltip string in it.
          //
          bool&                             appendToTooltipStr,
          ACHAR*&                            additionalTooltipString,

          // Input/Output
          //
          AcGiViewportDraw*                   drawContext,

          // Input parameters:
          //
          AcApDocument*                       document,
          bool                                pointComputed,
          int                                 history,
          const AcGePoint3d&                  lastPoint,
          const AcGePoint3d&                  rawPoint,
          const AcGePoint3d&                  grippedPoint,
          const AcGePoint3d&                  cartesianSnappedPoint,
          const AcGePoint3d&                  osnappedPoint,
          AcDb::OsnapMask                     osnapMask,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
          AcDb::OsnapMask                     osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
          const AcArray<AcDbObjectId>&        apertureEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& 
                                              nestedApertureEntities,
          const AcArray<Adesk::GsMarker>&     gsSelectionMark,
          const AcArray<AcDbObjectId>&        keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                              nestedKeyPointEntities,
          const AcArray<Adesk::GsMarker>&     keyPointGsSelectionMark,
          const AcArray<AcGeCurve3d*>&        alignmentPaths,
          const AcGePoint3d&                  computedPoint,
          const ACHAR*                         tooltipString) = 0;

    virtual bool
        excludeFromOsnapCalculation (const AcArray<AcDbObjectId>& nestedEntity,
                                     Adesk::GsMarker gsSelectionMark)
                                    { return false; }
};

class AcEdInputContextReactor
{

// Notification that user prompts are starting and completing.  
//
// The parameters ALL have the same meaning as the corresponding parameters
// in the corresponding "acedGet*()" functions.  As far as apps are concerned,
// that is exactly what we are monitoring, although internally, the values
// will be taken from the prevailing upkt struct.
//
// Note that the inputs can only be discerned from the "beginGetXxx" callbacks
// and the outputs are returned to the "endGetXxx" callbacks.  This eliminates
// redundancy, and obviously, the timing is right.   Within a given
// document, these callbacks can be nested, but an "endGetXxx" callback will
// always balance with a "beginGetXxx" callback within a document.
//
// Note also that the acedInitGet() parameters are folded into the beginGetXxx
// callbacks, and if a keyword is specified and entered, they PromptStatus
// will be set accordingly and and the pKeyword parameter will point to the
// keyword.
//

public:
    virtual void beginGetPoint(const AcGePoint3d* pointIn,
                               const ACHAR* promptString,
                               int   initGetFlags,
                               const ACHAR* pKeywords) { }

    virtual void endGetPoint(Acad::PromptStatus returnStatus,
                             const AcGePoint3d& pointOut,
                             const ACHAR*& pKeyword) { }

    virtual void beginGetAngle(const AcGePoint3d* pointIn,
                               const ACHAR* promptString,
                               int   initGetFlags,
                               const ACHAR* pKeywords) { }

    virtual void endGetAngle(Acad::PromptStatus returnStatus,
                             double& angle,
                             const ACHAR*& pKeyword) { }

    virtual void beginGetDistance(const AcGePoint3d* pointIn,
                                  const ACHAR* promptString,
                                  int   initGetFlags,
                                  const ACHAR* pKeywords) { }

    virtual void endGetDistance(Acad::PromptStatus returnStatus,
                                double& distance,
                                const ACHAR*& pKeyword) { }

    virtual void beginGetOrientation(const AcGePoint3d* pointIn,
                                     const ACHAR* promptString,
                                     int   initGetFlags,
                                     const ACHAR* pKeywords) { }

    virtual void endGetOrientation(Acad::PromptStatus returnStatus,
                                   double& angle,
                                   const ACHAR*& pKeyword) { }

    virtual void beginGetCorner(const AcGePoint3d* firstCorner,
                                const ACHAR* promptString,
                                int   initGetFlags,
                                const ACHAR* pKeywords) { }
    
    virtual void endGetCorner(Acad::PromptStatus returnStatus,
                              AcGePoint3d& secondCorner,
                              const ACHAR*& pKeyword) { }

    // *ScaleFactor is the same as *Distance, except a negative
    // value can be returned.  There is no exported ADS/LISP/ActiveX equivalent.
    //
    virtual void beginGetScaleFactor(const AcGePoint3d* pointIn,
                                     const ACHAR* promptString,
                                     int   initGetFlags,
                                     const ACHAR* pKeywords) { }

    virtual void endGetScaleFactor(Acad::PromptStatus returnStatus,
                                   double& distance,
                                   const ACHAR*& pKeyword) { }

    // Begin Nongeometric value input contexts.
    // Design note:  No mistake, getstring() does NOT do keywords!
    //
    virtual void beginGetString(const ACHAR* promptString,
                                int   initGetFlags) { }

    virtual void endGetString (Acad::PromptStatus returnStatus,
                               ACHAR* pString) { }

    virtual void beginGetKeyword(const ACHAR* promptString,
                                 int   initGetFlags,
                                 const ACHAR* pKeywords) { }

    virtual void endGetKeyword (Acad::PromptStatus returnStatus,
                                const ACHAR*& pKeyword) { }



    virtual void beginGetInteger(const int* dfault, // NULL implies no default
                                const ACHAR* promptString,
                                int   initGetFlags,
                                const ACHAR* pKeywords) { }

    virtual void endGetInteger(Acad::PromptStatus returnStatus,
                               int& retValue,
                               const ACHAR*& pKeyword) { }

    // *Color() is effectively a ranged-checked *Integer()
    virtual void beginGetColor(const int* dfault, // NULL implies no default
                               const ACHAR* promptString,
                               int   initGetFlags,
                               const ACHAR* pKeywords) { }

    virtual void endGetColor(Acad::PromptStatus returnStatus,
                             int& retValue,
                             const ACHAR*& pKeyword) { }

    virtual void beginGetReal(const double* dfault, // NULL implies no default
                              const ACHAR* promptString,
                              int   initGetFlags,
                              const ACHAR* pKeywords) { }

    virtual void endGetReal(Acad::PromptStatus returnStatus,
                            double& returnValue,
                            const ACHAR*& pKeyword) { }

    virtual void beginEntsel(const ACHAR* promptString,
                             int   initGetFlags,
                             const ACHAR* pKeywords) { }

    virtual void endEntsel(Acad::PromptStatus returnStatus,
                           AcDbObjectId& entPicked,
                           AcGePoint3d& pickPoint,
                           const ACHAR* pKeyword) { }

    // These two callbacks service both acedNEntSel() and acedNEntSelP()
    // calls.  The differences are immaterial with regard to monitoring
    // input.
    //
    virtual void beginNentsel(const ACHAR*    promptString,
                              Adesk::Boolean pickFlag,
                              int            initGetFlags,
                              const ACHAR*    pKeywords) { }

    virtual void endNentsel(Acad::PromptStatus returnStatus,
                            AcDbObjectId entPicked,
                            const AcGePoint3d&  pickPoint,
                            const AcGeMatrix3d& xform,
                            const resbuf* referenceStack,
                            const ACHAR*   pKeyword) { }

    virtual void beginSSGet(const ACHAR*  pPrompt,
                            int          initGetFlags,
                            const ACHAR*  pKeywords,
                            const ACHAR*  pSSControls, // str in ADS
                            const AcArray<AcGePoint3d>& points,
                            const resbuf*               entMask) { }

    virtual void endSSGet(Acad::PromptStatus returnStatus,
                          const AcArray<AcDbObjectId>& ss) { }
                    
    // These two callbacks cover internal AutoCAD drag sequences, acedDraggen()
    // and AcEdJig drag sequences also.
    //
    virtual void beginDragSequence(const ACHAR*  promptString) { }

    virtual void endDragSequence(Acad::PromptStatus returnStatus,
                                 AcGePoint3d&  pickPoint,
                                 AcGeVector3d& vec) { }

    // Quiescent state begin/end notification
    virtual void beginQuiescentState() { }

    virtual void endQuiescentState() { }
};

#pragma pack (pop)
#endif  // _ACEDINPT_H
