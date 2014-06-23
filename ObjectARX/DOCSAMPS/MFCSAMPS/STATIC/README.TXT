
Refer to the ARX Developer's Guide
The sample demonstrate how to use static MFC in an ARX application.

To use static.arx:

1. Start AutoCAD

2. Type the ARX command and load static.arx.

4. Type the staticmfc command, defined by static.arx.

5. A simple modal dialog box will be shown.

This sample uses static MFC lib that requires static runtime lib.
You need to replace CObject operator new and delete and link with
rxheap.lib.
This will generate duplicate definitions and you have to use
linker option /FORCE to produce the .arx file.
If you want to get rid of the duplicate definitions, you
can include rxdbgheap.cpp and rxafxmem.cpp into your project and
remove CObject's operator new and delete overrides from rxtemplt.cpp
becasue they are in rxafxmem.cpp already.
These two files are in this project directory but they are
not included the project makefile.
The use of these two files are not officially supported by
Autodesk since they are not fully tested yet. However, since
they are source files, you can easily modify them if you find
problems.
