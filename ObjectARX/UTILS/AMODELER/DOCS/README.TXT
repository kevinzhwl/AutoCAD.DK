
                    Autodesk Inc. Facetted Solid Modeler

                              August-15-1996

                              Revision 1.1

OVERVIEW
========

AModeler is a faceted solid modeling system. It provides the following 
functionality:

-  B-Rep data structure for the faceted representation of solid bodies.

-  Combination of bodies using the regularized Boolean operations -- union,
   intersection, and difference -- and sectioning bodies with a plane.

-  Perspective or parallel projection with hidden lines removed.

-  Box, cylinder, cone, sphere, torus, pipe, reducingElbow, 
   rectangleToCircleReducer, convex hull and other primitives.

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

-  Modern object oriented software architecture.


FILE STRUCTURE
==============

The modeler is located in the "amodeler" directory which contains the
following subdirectories:

amodeler\inc            ... All the header files of the modeler. 

amodeler\lib            ... File "AModeler.lib".

amodeler\sample         ... Sample projects,

amodeler\doc            ... Picture of the B-Rep topological data structure
                            ("topology.dwg"), this file ("readme.txt") and 
                            the list of the new features in this release of 
                            the modeler ("newfeat.txt").


The file AModeler.arx is located in the redist directory of the ObjectARX
installation

The modeler is documented in the header files located in the "amodeler\inc"
subdirectory. To begin studying the system, start with the 
"AsdkTestApp\sample.cpp"and "inc\body.h" files. These files contain examples 
of the usage of the modeler and an overall description of the B-Rep data 
structure. 

The modeler header files are listed below, grouped by functionality.


Topological classes
-------------------

Topological classes are used to define the topology of the model. The "body.h"
file and the "topology.dwg" figure contain the overall description of the 
B-Rep data structure.

inc\body.h        ... Class Body
inc\face.h        ... Class Face
inc\edge.h        ... Class Edge
inc\vertex.h      ... Class Vertex
inc\surface.h     ... All surface classes
inc\curve.h       ... All curve classes
inc\entity.h      ... Base class Entity


Other functionality
-------------------

inc\amodeler.h    ... Main include file, including all other header files
inc\errcodes.h    ... List of modeler error codes, error setting function
inc\epsilon.h     ... Epsilon handling
inc\color.h       ... Color handling 
inc\vertdata.h    ... Declaration of PolygonVertexData class
inc\morphmap.h    ... Class MorphingMap
inc\deviat.h      ... Function deviationToApprox() 
inc\dxfinpln.h    ... Function for reading a polyline from a DXF file
inc\callback.h    ... Abstract callback base classes
inc\dxfout.h      ... Sample DXF output callback class
inc\util.h        ... Various utility routines
inc\flags.h       ... Bit flag set/reset code
inc\global.h      ... A basic include file
inc\check.h       ... A few checking routines
inc\wallcrnr.h    ... Wall corner body creation function
inc\darray.h      ... Dynamic array 
inc\massert.h     ... Customized assert function (not for public use)


Mathematical classes
--------------------

inc\circle3d.h    ... Class Circle3d
inc\point2d.h     ... Class Point2d
inc\point3d.h     ... Class Point3d
inc\vector2d.h    ... Class Vector2d
inc\vector3d.h    ... Class Vector3d
inc\ipoint2d.h    ... Class IntPoint2d
inc\ipoint3d.h    ... Class IntPoint3d
inc\ivect2d.h     ... Class IntVector2d
inc\ivect3d.h     ... Class IntVector3d
inc\interval.h    ... Class Interval1d, Interval2d, Interval3d, IntInterval3d
inc\line3d.h      ... Class Line3d
inc\plane.h       ... Class Plane
inc\transf3d.h    ... Class Transf3d

