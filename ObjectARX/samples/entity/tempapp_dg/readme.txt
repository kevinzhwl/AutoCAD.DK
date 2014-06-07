(C) Copyright 1998-2002 by Autodesk, Inc.

Description: 

This sample program implements a protocol extension for AcDbCircles, AcDbEllipses, and AcDbRegions.

1. Create a few lines, circles, regions, etc. in AutoCAD.
2. Load the arx application.
3. Command: ENERGY 
This command works on circles and regions only. For entities that are neither regions nor circles, a default value of -1 is displayed. The value of the calculated energy changes when an entity is converted from a circle to a region.
