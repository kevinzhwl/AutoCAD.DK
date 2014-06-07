(C) Copyright 1998 by Autodesk, Inc.

Description:                       

viewportDraw() (transforms)        

This example demonstrates the use of isPerspective(), doPerspective(),  getBackAndFrontClippingValues(), polygonDc(), polygonEye(), and polygon().

To do this, it takes an original line segment in model coordinates and creates its equivalents in eye coordinates and display coordinates. When displayed, all the lines will overlap exactly.

Procedure:
1. Load coordsys.arx.
2. Command: ASDKCOORDSAMP

The ObjectARX Developer's Guide and the source code explain what takes place in more detail. You can find this information by browsing to "ObjectARX Graphics, Geometry, and Boundary Representation Libraries" => "The Graphics Interface Library" => "Transformations" => "Transformation Examples" => "Example 2: Determining Hidden Lines for an Object for Standard Display"