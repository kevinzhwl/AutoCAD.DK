///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
// DESCRIPTION:
//
// Example of using amodeler API 
//
// See the file "inc\body.h" for the list of public methods of the Body class 
// and for the description of the B-Rep data structure.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdarx.h"


#include "amodeler.h"  // The main include file of the modeler
#include "dxfout.h"    // Sample file, containing a sample callback class

#pragma warning(disable: 4702)  // Disable a bogus VC++4.0 warning

// Use the following statement to avoid typing the "AModeler::" prefix
//
#if _MSC_VER >= 1000
using namespace AModeler;
#endif  


static Body makeTetrahedron(const Point3d& p1, 
                            const Point3d& p2, 
                            const Point3d& p3, 
                            const Point3d& p4)
//
// Sample function creating a model of a tetrahedron
//
{
    checkError(!areCoplanar(p1, p2, p3, p4), ePointsAreCoplanar);

    Body b;  // Create an empty body variable on the stack

    // Create four vertex objects and add them to the body
    //
    Vertex* v1 = new Vertex(p1, &b);
    Vertex* v2 = new Vertex(p2, &b);
    Vertex* v3 = new Vertex(p3, &b);
    Vertex* v4 = new Vertex(p4, &b);

    // Make sure the orientation if correct
    //
    if (det(p2-p1, p3-p1, p4-p1) < 0)
    {
        Vertex* v = v1;  // Swap v1 and v2
        v1 = v2;
        v2 = v;
    }

    // Create four face objects and add them to the body. The faces initially 
    // have no edges
    //
    Face* const f1 = new Face(&b);
    Face* const f2 = new Face(&b);
    Face* const f3 = new Face(&b);
    Face* const f4 = new Face(&b);

    // Create all edges. Each me() function creates a pair of edge objects 
    // between the two given faces and with the two given end vertices
    //
    me(f1, f2, v2, v1);
    me(f1, f3, v3, v2);
    me(f1, f4, v1, v3);
    me(f2, f3, v2, v4);
    me(f3, f4, v3, v4);
    me(f4, f2, v1, v4);

    // Return the body. Notice that we are returning the body by value
    //
    return b; 

} // makeTetrahedron()



static Body makeExtrAlongPath1()
//
// Sample function showing how the Body::extrusionAlongPath() method can 
// change the geometry of the profile being extruded from one shape to another
//
{
    // One rectangle
    //
    Point3d profPts1[]  = { Point3d(0,3,0), 
                            Point3d(0,3,1), 
                            Point3d(0,7,1), 
                            Point3d(0,7,0) };

    Body startProfile;
    new Face(profPts1, 4, 0, false, &startProfile);

    // Another rectangle
    //
    Point3d profPts2[]  = { Point3d(3,0,0), 
                            Point3d(3,0,4), 
                            Point3d(4,0,4), 
                            Point3d(4,0,0) };

    Body endProfile;
    new Face(profPts2, 4, 0, false, &endProfile);
    
    Point3d pathPts[]   = { Point3d(0,3,0),
                            Point3d(3,0,0) };

    PolygonVertexData vd1(PolygonVertexData::kArc3d, Circle3d(Line3d(Point3d(0,0,0), Vector3d(0,0,1)), 3), 48);

    PolygonVertexData* vd[] = { &vd1, NULL };

    return Body::extrusionAlongPath(startProfile, endProfile, pathPts, vd, 2, false);

} // makeExtrAlongPath1()



static Body makeExtrAlongPath2()
//
// Sample function showing a closed extrusion along a path. The path is rotated 
// while being extruded
//
{
    Point3d profPts1[] = { Point3d(1,0,0), 
                           Point3d(1,0,1), 
                           Point3d(2,0,1), 
                           Point3d(2,0,0) };

    Body startProfile;
    new Face(profPts1, 4, 0, false, &startProfile);
    
    // The path is a full circle. The path polygon contains just a single 
    // point on the circle, the PolygonVertexData(kArc3d, ...) defines the 
    // circle
    //
    Point3d pathPts[] = { Point3d(1.5,0,0.5) };

    PolygonVertexData vd0(PolygonVertexData::kArc3d, Circle3d(Line3d(Point3d(0,0,0.5), Vector3d(0,0,1)), 1.5), 48);

    PolygonVertexData* vd[] = { &vd0 };

    return Body::extrusionAlongPath(startProfile, 
                                    Body(), 
                                    pathPts, 
                                    vd, 
                                    1, 
                                    true, 
                                    true,
                                    pathPts[0],  // Scale/twist fixed point
                                    1.0,         // Scale factor
                                    kTwoPi);     // Twist angle

} // makeExtrAlongPath2()



static Body makeRectangleToCircleReducer(const Point3d&  baseCorner, 
                                         const Vector2d& baseSizes,
                                         const Circle3d& topCircle,
                                         int             approx)
//
// Show the usage of the Body::skin() method and the MorphingMap used to
// morph the topology of one profile to another
//
{
    checkError(baseSizes.x > epsAbs() && 
               baseSizes.y > epsAbs(), eBaseSizesMustBePositive);
    checkError(topCircle.radius > epsAbs(),  eRadiusMustBePositive);
    checkError(approx >= 4,                  eApproximationMustBeAtLeastFour);
    checkError(topCircle.axis.point.z > baseCorner.z + epsAbs(),
                                             eTopCircleMustLieAboveBaseRectangle);

    Circle3d cir    = topCircle;
    cir.axis.vector = Vector3d(0,0,1);  // Set the circle normal to point up

    // Create ptsArray[] to be the array of the corners of the base rectangle
    //
    Interval2d interv(baseCorner.toPoint2d(), baseCorner.toPoint2d()+baseSizes);

    Point3d ptsArray[4] = { baseCorner, baseCorner, baseCorner, baseCorner };

    ptsArray[1].x += baseSizes.x;
    ptsArray[2].x += baseSizes.x;
    ptsArray[2].y += baseSizes.y;
    ptsArray[3].y += baseSizes.y;

    // Round approx up to the nearest nultiple of 4
    //
    approx = ((approx + 3) / 4) * 4;
    
    // Make two profile bodies, each containing just one profile face
    //
    Body prof0, prof1;
    Body* profiles[2] = { &prof0, &prof1 };

    Face* const fBottom = new Face(ptsArray, 4, 0, false, &prof0);  // Rectangular profiles face
    Face* const fTop    = new Face(cir, 0, approx,        &prof1);  // Circular profile face

    // Create a map which defines how the vertices of the base rectangle
    // map to the edges of the approximated top circle
    //
    MorphingMap morphingMap;
    
    morphingMap.add(0, approx/2);
    morphingMap.add(0, (approx/4)*3);
    morphingMap.add(1, (approx/4)*3);
    morphingMap.add(1, 0);
    morphingMap.add(2, 0);
    morphingMap.add(2, approx/4);
    morphingMap.add(3, approx/4);
    morphingMap.add(3, approx/2);

    MorphingMap* morphingMaps[] = { &morphingMap, NULL };
    
    // Perform the skin operation which takes the two profiles and generates
    // faces between them
    //
    Body b = Body::skin(profiles,      // Array of profile bodies
                        2,             // Number of profiles
                        false,         // Not closed
                        false,         // Do not check planarity of faces
                        morphingMaps); // Array of pointers to morphing maps

    // Assign UnspecifiedSurface to all faces except the bottom and the top one
    // (which are planar)
    //
    Surface* const s = new UnspecifiedSurface(&b);

    for (Face* f = b.faceList(); f != NULL; f = f->next())
    {
        if (f != fBottom && f != fTop)
        {
            f->setSurface(s);
        }
    }

    return b;

} // Body::makeRectangleToCircleReducer()



static void ads_printfaceVertices(const Body& b)
//
// Sample function printing coordinates of vertices of all faces of a given 
// body
//
{
    ads_printf("Body:\n");

    for (Face* f = b.faceList(); f != NULL; f = f->next())
    {
        ads_printf(" Face:\n");

        if (f->edgeLoop() == NULL)
        {
            ads_printf(" Face has no edges, this is illegal!\n");
            continue;
        }

        Edge* e = f->edgeLoop();
        do {
            const Vertex* const v = e->vertex();
            const Point3d       p = v->point();

            ads_printf("  Vertex %6x: %8.3f %8.3f %8.3f\n", (int)v, p.x, p.y, p.z); 

        } while ((e = e->next()) != f->edgeLoop());
    }
    ads_printf("\n");
} // ads_printfaceVertices()



static void printEdges(const Body& b)
//
// Sample function printing all "real" edges of a body. Similar code can be 
// used, for example, to draw edges of a body. 
//
// The isEulerEdge() predicate makes sure that always only one edge object of 
// all partner edge objects is printed. In this example, we skip bridge edges.
//
{
    ads_printf("Body:\n");

    for (Face* f = b.faceList(); f != NULL; f = f->next())
    {
        if (f->edgeLoop() == NULL)
            continue;

        Edge* e = f->edgeLoop();
        do {
            if (e->isEulerEdge() && !e->isBridge())
            {
                const Point3d p1 = e->point();
                const Point3d p2 = e->next()->point();
                
                ads_printf(" Edge:%8.3f %8.3f %8.3f   %8.3f %8.3f %8.3f\n",
                       p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
            }
        } while ((e = e->next()) != f->edgeLoop());
    }
    ads_printf("\n");
} // printEdges()

void MainTest()
{
    ads_printf("AModeler sample program\n\n");
    
    try
    {
        Body body1;
        {
            // Create a pipe primitive, make two rotated copies

            Body  b1 = Body::pipe(Line3d(Point3d(0,0,-1.5), Vector3d(0,0,3)), 1, 0.8, 32);
            
            Body  b2 = b1.copy().rotate(Line3d::kXAxis, kHalfPi);
            
            Body  b3 = b1.copy().rotate(Line3d::kYAxis, kHalfPi);
            
            Plane pl = Plane(Point3d(1,0,0), Point3d(0,1,0), Point3d(0,0,1));
            
            // Add all three bodies together and section them with a plane
            //
            body1 = b1 + b2 + b3 - pl;
        }
        
        Body body2;
        {
            // Create a box
            //
            Body box = Body::box(Point3d(0,0,0), Vector3d(4,2,1));
            
            // Repeatedly keep adding rotated and moved copies of the box
            // to body2. Note that when variable body2 is declared, it is
            // initialized to an empty body.
            //
            for (int i = 0; i < 20; i++)
            {
                Body boxCopy = box.copy();
                
                boxCopy.rotate   (Line3d::kZAxis, i*kTwoPi/20);
                boxCopy.translate(Vector3d(0,0,0.3*i));
                
                body2 += boxCopy;
            }
            
            // Subtract a cylinder from body2
            //
            body2 -= Body::cylinder(Line3d(Point3d(0,0,-1), Vector3d(0,0,8)), 0.5, 24);
        }
        
        Body body3, body4;
        {
            // This example shows how to create bodies by sweeping a planar 
            // profile

            // Create a polygon and PolygonVertexData 
            // (together called "augmented polygon")
            //
            Point3d plg[] = { Point3d(0,0,0), Point3d(1,0,0), Point3d(0,1,0) };

            PolygonVertexData vd0(PolygonVertexData::kFilletByRadius, .3, 32);
            PolygonVertexData vd1(PolygonVertexData::kFilletByRadius, .2, 32);
            PolygonVertexData vd2(PolygonVertexData::kFilletByRadius, .1, 32);
            
            PolygonVertexData* vd[] = { &vd0, &vd1, &vd2 };
            
            // Create body3 and body4 by sweeping the polygon
            //
            body3 = Body::pyramid       (plg, vd, 3, Vector3d(0,0,1), Point3d(0,0,1));

            body4 = Body::axisRevolution(plg, vd, 3, Vector3d(0,0,1),
                                         Line3d(Point3d(1,0,0), Vector3d::kYDir),
                                         kTwoPi, 
                                         32);
        }
        
        // Create body5 to be the convex hull of body2
        //
        Body body5 = body2.convexHull();

        // Create body6 to be a tetrahedron
        //
        Body body6 = makeTetrahedron(Point3d(0,0,0), 
                                     Point3d(1,0,0), 
                                     Point3d(0,1,0), 
                                     Point3d(0,0,1));

        // Use the two sample functions we have just written
        //
        ads_printfaceVertices(body6);
        printEdges       (body6);
        
        // Save body2 to file "body2.bdy"
        //    
        FILE* fp = fopen("body2.bdy", "wb");
        body2.save(fp);
        fclose(fp);
        
        // Restore body2 from the file
        //
        fp = fopen("body2.bdy", "rb");
        Body body22 = Body::restore(fp);
        fclose(fp);
        
        // Check that the restored body is the same as the saved one (their 
        // subtraction must produce a null body)
        //
        MASSERT((body2.copy() - body22).isNull());
        
        // Triangulate all bodies, save the generated triangles to DXF files

        // Use the provided sample callback class (see files inc\dxfout.h and
        // sample\dxfout.cpp). 
        //
        // We bracketed the following two statements because we want the 
        // destructor of the callback object to be called. The constructor 
        // opens and the destructor closes the DXF file.
        //
        {
            OutputToDxfFileCallback callback("triang1");
            body1.triangulate(&callback);
        }

        // For the rest use shortcuts, doing the same thing as above
        //
        body2.triangulateDxf("triang2", kGenerateQuadrilaterals);
        body3.triangulateDxf("triang3", kGenerateQuadrilaterals);
        body4.triangulateDxf("triang4", kGenerateQuadrilaterals);
        body5.triangulateDxf("triang5", kGenerateQuadrilaterals);
        
        // Display all bodies with hidden lines removed. Save the generated
        // lines to DXF files. Set various display parameters
        //
        body1.setHiddenLineParams(kHiddenLinesInvisible, true);
        body4.setHiddenLineParams(kHiddenLinesInvisible, true);
        
        // The following setting will cause the hidden lines to be sotred on
        // a separate layer called AMODELER_HIDDEN. To see only the visible
        // lines, turn this layer off when viewing the DXF file in AutoCAD.
        //
        body3.setHiddenLineParams(kHiddenLinesDashed);
        
        const Transf3d proj2 = Transf3d(Transf3d::kParallelProjection,
                                        Point3d(3,3,2));
        const Transf3d proj3 = Transf3d(Transf3d::kPerspectiveProjection, 
                                        Point3d(2,2,8),
                                        Point3d(0,0,0));
        const Transf3d proj4 = Transf3d(Transf3d::kParallelProjection,
                                        Point3d(4,5,6));

        // Explicitly use the sample callback class
        //
        {
            OutputToDxfFileCallback callback("hide1");
            body1.hideDisplay(Transf3d::kDimetricView, &callback);
        }

        // Use shortcuts for the rest
        //
        body2.hideDisplayDxf(proj2,                    "hide2");
        body3.hideDisplayDxf(proj3,                    "hide3");
        body4.hideDisplayDxf(proj4,                    "hide4");
        body5.hideDisplayDxf(Transf3d::kIsometricView, "hide5");

        // Create a few more bodies and save them to DXF files
        //
        Body reducer = makeRectangleToCircleReducer(Point3d(0,0,0), Vector2d(1,1), 
                                                Circle3d(Line3d(Point3d(.5,.5,1), Vector3d(0,0,1)), .4),
                                                24);
        Body expth1  = makeExtrAlongPath1();
        Body expth2  = makeExtrAlongPath2();
        
        reducer.triangulateDxf("reducer");
        expth1 .triangulateDxf("expth1");
        expth2 .triangulateDxf("expth2", kGenerateQuadrilaterals);

        // Test whether Point3d(1,2,3) is inside body1. It should not be.
        //
        PointInBodyLocation pib = body1 && Point3d(1,2,3);
        
        if (pib == kPointOutsideBody)
            ads_printf("Point3d(1,2,3) lies outside body1\n");
        else
            ads_printf("Point3d(1,2,3) does NOT lie outside body1\n");
        
        // Test whether body2 and body5 interfere. They should interfere.
        //
        BodyInterferenceType interf = body2 && body5; 

        switch (interf)
        {
        case kBodiesDoNotInterfere:
            ads_printf("Bodies body2 and body5 do not interfere\n");
            break;

        case kBodiesTouch:
            ads_printf("Bodies body2 and body5 touch\n");
            break;

        case kBodiesInterfere:
            ads_printf("Bodies body2 and body5 interfere\n");
            break;

        default:
            checkError(false, eFail);  // This should never happen
        } // switch

        ads_printf("\n");
    }
    catch (ErrorCode err)
    {
        ads_printf("AModeler has thrown an exception: ErrorCode=%d\n", err);
        return;
    }

    ads_printf("AModeler sample program finished\n");
    return;
} // main()



