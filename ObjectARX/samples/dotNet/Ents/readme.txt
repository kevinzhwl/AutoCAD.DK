(c) Copyright 2004 by Autodesk, Inc.

Description: This application implements a command called MKENTS. It will create a line and a circle, append them to an object ID array, change the circle's color to red, and then make a group of the line and circle using ASDK_TEST_GROUP as the group's name. The MKENTS command also creates a new layer named ASDK_MYLAYER.

To use Ents.dll:

1. Start AutoCAD and open a new drawing.
2. Type netload and select Ents.dll.
3. Execute the MKENTS command.

Autodesk references added to this project are the acdbmgd.dll and acmgd.dll .NET components, and the AutoCAD Type Library COM component.