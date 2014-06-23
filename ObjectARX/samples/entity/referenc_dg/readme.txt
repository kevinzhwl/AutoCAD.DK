(C) Copyright 1998 by Autodesk, Inc.

Description:

This program demonstrates interobject references.
	
It creates a class that extends AcDbEllipse by adding functionality to store a dynamic array of hard pointer object IDs.

The subErase() member function has been overriden and implemented such that whenever an object of this class is erased, the objects pointed to by the hard pointer IDs stored within the object will also be erased.

1. Load referenc.arx.
2. Command: ASDK_ELLIPSES

Several concentric ellipses centered at 4,4,0 should appear in the graphics screen.

Listing one of the ellipses using the LIST command should print:

10 ReferenceId.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.

