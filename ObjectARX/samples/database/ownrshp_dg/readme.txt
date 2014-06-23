
Description:
(C) Copyright 1998-2002 by Autodesk, Inc.

This program demonstrates deriving from AcDbObject and establishing ownership trees.
 
In order to show all aspects of this mechanism, a custom object class that has two data members is used. One data member stores an integer (simulating real data), and the other stores a hard ownership object ID.
 
Ownership consists of two parts:
 
1) The owner object stores the owned object's object ID and files it out/in to DWG and DXF.
 
2) The owned object has its setOwnerId() member called with the owned object's object ID as the parameter. This sets up the backpointer link so that the owned object knows who its owner is. This is used by such things as WBLOCK to walk "up" the ownership tree.
 
AutoCAD sets backpointers during operations that use the DWG and DXF filers, so a custom object/entity class doesn't need to worry about this for its dwgInFields and dxfInFields members. However, any class member functions that set any ownership ID data members in the class should take care of setting the owned object's backpointers by opening the owned objects and calling their setOwnerId() member functions using the owner object's object ID as the parameter for the calls.

1. Load ownrshp.arx.
2. Command: ASDK_CREATE
3. Command: ASDK_LISTREE

Output similar to the following should be printed:

Intdata: 1  ObjId: 38012248  Backpointer: 38012240 OwnedObj: 38012232
Intdata: 2  ObjId: 38012232  Backpointer: 38012248 OwnedObj: 38012224
Intdata: 3  ObjId: 38012224  Backpointer: 38012232 OwnedObj: 0

The ObjectARX Developer's Guide and the source code explain what took place in more detail.

