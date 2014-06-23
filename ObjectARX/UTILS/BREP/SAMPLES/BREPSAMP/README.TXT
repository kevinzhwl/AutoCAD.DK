The Autodesk Boundary Representation Library Sample Application
---------------------------------------------------------------

Building brsample.arx:

An ObjectARX sample application for the Autodesk Boundary
Representation Library (brepsamp) is contained in the
ObjectARX\utils\brep\samples tree. The makefile
brsamplevc4x.mak is used to build the sample application.


Running brsample.arx:

The sample application is called brsample.arx, and is loaded
in the standard way using the "arx" command in AutoCAD. It
implements several commands:

BRDUMP exemplifies topological traversal as well as extraction
and evaluation of geometric data from a solid model. All results
are annotated on the screen.

BRTRMSRF displays trimmed surface data, based on a face pick in
AutoCAD. This command generates informational error messages on
unbounded surfaces (planes, spheres, tori) and at the apex of a
cone, where no trimmed data exists.

BRBBLOCK returns the model space coordinates of the lower left
and upper right corners of the bounding box for the selected
subentity in the solid model.

BRPTCNT returns the containment of a selected point with respect
to the selected subentity in the solid model.

BRLNCNT returns the containment of a selected line with respect
to the selected subentity in the solid model. The information
from the returned array of AcBrHits is annotated on the screen.


Standard AutoCAD entity selection is used in all of the commands.
Any selected entity which is not an AcDb3dSolid, AcDbBody or
AcDbRegion is rejected.

Points and lines may either be selected from the screen or
entered directly as coordinates. The latter will give more
accurate and predictable results.


The purpose of these registered commands is to familiarise people
with the behaviour of various functions within libacbr.dll, and
to exemplify proper usage of the functions in an integrated
environment.

Particular attention is paid to how the library interacts with
libacge.dll to provide useful boundary data and definition data
for external curves and surfaces. The sample app is often used
to exemplify temporary workarounds for known problems in the
various modeling libraries that it interacts with.

The sample app should be thought of as a template for any serious
application requiring boundary information of a model. It is not
guaranteed to be perfect, and for MAI partners email is an
appropriate vehicle for discussing problems or requesting
additional examples or workarounds.
 

The Structure of the sample application code:

brsample.cpp
This is the main program for the sample application.

brdump.cpp
This is the top level code for the brdump command, which dumps
topological and geometric data associated with the selected solid
or subentity.

brbdump.cpp
This module contains the code for enumerating all the topological
elements of a solid object.

brfdump.cpp
This module contains the code for dumping the surface data
associated with a selected face subentity.

bredump.cpp
This module contains the code for dumping the curve data
associated with a selected edge subentity.

brvdump.cpp
This module contains the code for dumping the point data
associated with a selected vertex subentity. Note that it is not
currently possible to select a vertex in AutoCAD as it is not
part of the display list, but it is possible to write a function
which takes a known vertex and feeds it into the vertex dump.

brtrmsrf.cpp
This is the top level code for the brtrmsrf command, which dumps
a parameter space 2d nurb curve list corresponding to the
boundary of the selected face. If the selected face has no loops
(such as a full sphere or torus), eUnsuitableTopology is
returned.

brbblock.cpp
This is the top level code for the brbblock command, which
computes a 3d model space bounding block for the selected solid
or subentity.

brptcnt.cpp
This is the top level code for the brptcnt command, which
determines the containment of a selected point with respect to
a selected subentity.

brlncnt.cpp
This is the top level code for the brlncnt command, which
determines the containment of a selected line with respect to
a selected subentity.

brdbutl.cpp
This module contains the AutoCAD/ObjectARX/ADS interface for the
application: primarily the processing of picks and the return of
a full subentity path.

brgeutl.cpp
This module contains the AcGe object conversion utilities. This
code serves as a reference for how to turn an external curve or
surface returned by an AcBr method into an AcGe native curve or
surface to query for definition data.

brreport.cpp
This module contains the utilities that dump AcBr error codes as
well as specialised functions that annotate the results of more
complex analysis (such as line containment).

