loadApp.arx readme.

What is loadApp ?
-----------------

There are two ways to benefit from this application. The first and primary
intent is as an example MFC/ARX application. The second is as a tool to
replace the existing AutoCAD "appload" application to easily load and
unload ARX, ADS and LISP applications.

This example shows :

	- the use of modal and modeless MFC dialogs in an ARX application.
	- how to use the CToolbar MFC object in ARX applications
	- how an ARX application can unload itself.
	- how to modify the AutoCAD window title.
	- how to to intercept Windows messages.
	- how to register an ARX application for demand loading.

This application is an ARX/MFC implementation of the AutoLISP "appload"
feature that comes with AutoCAD (accessible through the menu pull down:
Tools->Load Application...). LoadApp facilitates the loading and unloading
of ADS or ARX applications and the loading of AutoLisp applications
(AutoLisp applications cannot be unloaded). In addition, loadApp is capable
of unloading itself using ads_queueexpr().

In the process of developing an ADS or ARX application, the developer needs
to unload its application from AutoCAD each time he rebuilds it. LoadApp makes
the loading/unloading operation easy by storing the fully qualified path name
of the current application. The current application is defined by selecting it
in the combo box of the loadApp toolbar, or by using the "Browse" button.
This current application can then be loaded/unloaded with one click of the mouse
on the corresponding icon in the loadApp toolbar, or by typing "lca" (for 
"load current application") or "ulca" (for "unload current application")
on the command line. Typing "loadapp" will call the loadApp dialog box.													 

The current application file name can be displayed in the AutoCAD window 
title (command "ShowTitle"). LoadApp shows how to access and modify the AutoCAD
window title. Please note that this may have some side effect on applications 
that rely on the original title to find the AutoCAD window handle.

The loadApp dialog box displays a list of all the currently loaded ADS or ARX
applications, even if they have not been loaded through loadApp. LoadApp maintains
a list of the last 15 used applications, a list of the hidden applications
(applications that will not show up in the loaded applications list even if loaded),
and the current application. This information is saved in the system registry and 
therefore remains across AutoCAD sessions.


How to install loadApp :
------------------------
1- Build the application in Visual C++, the project files are supplied.
2- Copy or move the executable (loadApp.arx) in the AutoCAD directory 
   (the directory that contains ACAD.EXE). This is a requirement if you
   want to benefit from the demand loading mechanism.
3- Load loadApp "manually" by using the AutoCAD "arx" command or simply
   by drag'n droping loadApp.arx from the Windows Explorer to the AutoCAD
   graphic Window.

   When it loads for the first time, loadApp creates its entry in the system
   registry (in HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\ObjectARX\2.0\SampleApps\loadApp).
   The loadApp entry in the registry contains the necessary subkeys for the demand
   loading mechnism, and next time AutoCAD will be loaded, loadApp will start
   automatically (the loadApp toolbar should appear at the bottom left corner
   of the AutoCAD Window). The "loadReasons" for loadApp are kOnAutoCADStartup
   and kOnCommandInvocation (see acrxRegisterApp() function in the ARX help file).
   If you do not want to have loadApp being loaded automatically each time AutoCAD
   starts, the easiest is to manually edit the registry:
   1- In the Startup menu, choose "run" and enter "regedit", click OK.
   2- In HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R14.x\ACAD-XXXXXXX:XXXXXXXX\
      Applications\loadApp, select the "LOADCTRLS" subkey and change its value
	  to 0x04 for kOnCommandInvocation only.

The loadApp toolbar :
---------------------
The loadApp toolbar is an MFC toolbar (LaMfcToolbar is derived from class CToolBar)
that docks in the AutoCAD window but NOT with the AutoCAD toolbars. You can move it
to another location or undock it. It contains 4 icons, a red right arrow to load 
the current application, a blue left arrow to unload the current application, 
the dialog icon that open the loadApp dialog, and finaly the icon that controls
the display af the current application path name in the AutoCAD Window title (toggle).
