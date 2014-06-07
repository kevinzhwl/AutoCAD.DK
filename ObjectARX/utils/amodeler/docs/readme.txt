
                                AModeler
                                ======== 
               
                          Faceted Solid Modeler

                                   by

                              Jiri Kripac

 
                              Revision 1.2

AutoCAD 2004 Updates
====================

AModeler has been updated for VC 7.0 and has been converted to an
ObjectDBX application.  This version of AModeler is compatible with
AutoCAD 2004.  However, additional enhancements are in progress and an
updated AModeler will be posted at a later time. 

Please watch the ObjectARX Web page for updates. 


Installation
============
 
- Add the "amodeler\bin" subdirectory to your PATH variable.

- The modeler has been compiled with Microsoft VC++ 7.0 compiler and is
  using Multithreaded DLL runtime library.


Overview
========

AModeler is a faceted solid modeling system. It provides the following 
functionality:

-  B-Rep data structure for the faceted representation of solid bodies.

-  Combination of bodies using the regularized Boolean operations -- union,
   intersection, and difference -- and sectioning bodies with a plane.

-  Perspective or parallel projection with hidden lines removed.

-  Box, cylinder, cone, sphere, torus, pipe, rectangleToCircleReducer, 
   convex hull and other primitives.

-  Set of sweep operations including general extrusion along the path, 
   allowing one profile to morph to another profile while being extruded. 
   Importing and sweeping 2D polylines from a DXF files.

-  Geometric transformations translation, rotation, scaling, stretching, and
   mirroring; general alignment of bodies in space.

-  Calculation of area, volume, centroid, moments of inertia and products of
   inertia for bodies; calculation of area, perimeter, and centroid for faces.

-  Checking interference of bodies; testing location of a point with respect
   to a body.

-  Picking entities (vertices, edges, faces, and bodies) in projected views.

-  Storing bodies in a native format; storing projected or triangulated bodies
   in DXF files.

-  Modern object-oriented software architecture.


File Structure
==============

The modeler is located in the "amodeler" directory which contains the
following subdirectories:

amodeler\inc            ... All the header files of the modeler. 

amodeler\lib            ... File "amodeler.lib".

amodeler\bin            ... File "amodeler.dll".

amodeler\sample         ... Sample code "sample.cpp," demonstrating the
                            usage of the modeler. Sample file "dxfout.cpp."

amodeler\doc            ... Picture of the B-Rep topological data structure
                            "topology.dwg" and this file "readme.txt".


The modeler is documented in the header files located in the "amodeler\inc"
subdirectory. To begin studying the system, start with the "sample\sample.cpp"
and "inc\body.h" files. These files contain examples of the usage of the 
modeler and an overall description of the B-Rep data structure. 

