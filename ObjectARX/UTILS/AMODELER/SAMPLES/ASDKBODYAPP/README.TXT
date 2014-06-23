ObjectARX 28th January 1997

This application is an ARX application which tests and demonstrates the
use of the AModeler.ARX

It defines a custom entity AsdkBody and a number of commands to create
and manipulate these entities

To use these applications, amodeler.arx must be in the AutoCAD directory.
This is because of the simple way the modeler gets loaded. First the OS
must find it and second AutoCAD must find it for the acrxLoadModule("AModeler.arx",1); 
call to succeed.


 

