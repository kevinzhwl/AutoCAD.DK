The polysamp application demonstrates several things:

 1) How to implement a custom entity class

 2) How transactions work

 3) How to use the AcDbEntity::highlight() and AcDbEntity::unHighlight()
    methods

 4) How to export a custom entity class to a fourth party

 5) How to implement an OLE Automation interface for a custom
    class


The subdirectory "client" contains a "fourth party" application
which makes use of the exported AsdkPoly class.

This client application defines two commands, CLIENTPOLY and
CLIENTPOLYEDIT, which are the same as the POLY and POLYEDIT commands
in the POLYSAMP application.

In order to build the client.arx program, you must first build the
polysamp.arx program to generate the polysamp.lib file that is
needed by client.arx.

Since client.arx relies on polysamp.arx,  it will not run without
polysamp.arx loaded.  So,  if client.arx is loaded while polysamp.arx
is not,  client.arx will attempt to load polysamt.arx.

****

The subdirectory "polyolea" contains the files that demonstrate how
to implement an OLE Automation interface for the polysamp application.

In order to build the polyolea.dll, you must first build the
polysamp.arx program to generate th polysamp.lib file that is needed
by polyolea.dll.

And before starting to play with Polsamp OLE automation support, you
need to edit polyolea.reg file to specify the location of the type
library (generated automatically when you build polyolea.dll) and
polyolea.dll. Polysamp.arx should be put in the same directory
as the polyolea.dll. After modifying the .reg file, don't forget
to register it.

