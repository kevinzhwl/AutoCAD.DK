This sample implements a simple drag-drop sample to AutoCAD
drawing window. It creates a window where users can pick a
predefined drawing they want to insert. To insert the drawing,
users left click on the drawing name, drag it to AutoCAD drawing
window and release the left mouse button. After that, the users
are prompted with the regular INSERT command prompt.
 
Command:
- ddinsert - to bring up the drag-drop window.

  Don't forget to copy site.dwg, circle.dwg, shuttle.dwg and logo.dwg to
  AutoCAD directory, or somewhere in AutoCAD support path.


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


ARX CUSTOM DRAG AND DROP:
-------------------------

The fundamental of OLE/COM drag and drop is the IDropTarget and IDropSource
interfaces. In order for a window to become a drop target, it must have an 
IDroptarget associated with it. The AutoCAD dwg window has its own IDropTarget
registered to it at startup time.  However, when 3rd party applications want to
implement new behaviour of Drag&Drop operation, like pallette dragging 
(Visio's style), they need to somehow get involved in receiving Drag&Drop
events. 
The only way to recieve these events it to register their own IDropTarget
interface to the AutoCAD dwg window. By doing this, the 3rd apps have to write
their own IDropTarget and implement what kind of behaviors they want. They lose
the default Drag&Drop behaviors of AutoCAD dwg window, since only one IDropTarget
can be associated/registerd with a window. The registration of new IDropTarget
should be done before the 3rd party's DoDragDrop call and immediately switch it
back to default AutoCAD IDropTarget after the call.


The API:
--------
Only two functions provided:
BOOL acedRegisterCustomDropTarget(IDroptarget*);
BOOL acedRevokeCustomDropTarget();


The Pseudo Code:

Usually in Drag&Drop operation, a call is made to DoDragDrop(). This function 
basically takes care the whole process of Drag&Drop events. Before calling this 
function, IDropSource & IDataObject are prepared and sent as an argument to that function.
* Prepare an IDropSource
* Call DoDragDrop()


For custom drag drop, before we call DoDragDrop, we need to set the Acad Dwg
Window IDropTarget and immediately reset it afterwards.
* Prepare an IDropSource
* Call acedRegisterCustomDropTarget(IDroptarget*);
* Call DoDragDrop()
* Call acedRevokeCustomDropTarget();


The Sample:
The sample is a very simple one. basically it replaces AutoCAD IDropTarget with
its own. The new IDroptarget basically inserts a dwg/block from the small
window.

RoadMap:

Files that really matter:
- ArxDrawView.cpp
  In this file, at the OnLButtonDown event, an IDataObject is created and pass it
  to DoDragDrop call. Notice that it registers its own IDroptarget before the call
  and immediately revokes it. 
  The dwg file is stored inside the IDataObject, and it's passed in as one of
  arguments in DoDragDrop() call.
  
  Notice that the CArxdrawView register a dummy IDroptarget to its window during 
  OnInitialUpdate so that no Drop event can be done on its window.

- droptarget.cpp
  This is the implementation of IDroptarget that replaces the one from Acad Dwg view.
  Nothing fancy here, basically it reads IDataObject, figure out the dwg/block name.
  
  Well, ads_command doesn't work when it's not called/originated from ads_defun()
  command. To work around this, SendMessage() is used to send "INSERT" command
  to the AutoCAD input throat.

  During the DragDrop events (DoDragDrop() call), Windows messages can't be processed 
  by AutoCAD. DragDrop events should stop first before AutoCAD processes the MSGS 
  from SendMessage. 

  To work this around, the IDroptarget::DropEnter() should cancel/stop
  DoDragDrop loop. It can be only done inside IDropSource::QueryCOntinueDrag().
  Well, since Idroptarget and IDropSource are implemented in one ARX app,
  We can just use a global variable to let QueryContinueDrag() to cancel DragDrop
  events.
  After cancelling the DragDrop events, the MSG will be immediatley processed.
  The insert dragging event takes over.

  The behavior we wantis that when LButton mouse is up, the drawing is inserted at 
  that point. However, the Autocad Insert dragging doesn't behave like that. We need
  to click/LButtonDown. Here comes the pretranslate message hooks.
  At IDroptarget::DragEnter(), we insert a hook to translate LButtonUP to LButtonDown 
  so that AutoCAD will insert the drawing at the place where user release the LButton. 

  Don't forget to copy site.dwg, circle.dwg, shuttle.dwg and logo.dwg to
  AutoCAD directory, or somewhere in AutoCAD support path.









