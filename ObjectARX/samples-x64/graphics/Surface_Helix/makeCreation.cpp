// (C) Copyright 2002-2007 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include ".\makeCreation.h"



#define szRDS _RXST("ADSK")
#define KPI	3.14159265

CMakeCreation::CMakeCreation(void)
{
}

CMakeCreation::~CMakeCreation(void)
{
}

void CMakeCreation::AddPlaneSurface()
{
	// Add a plane surfaces  using AcDbPlaneSurface Class
	AcDbVoidPtrArray entities, regions;

	// In memory circle is used to form the base of a bowl on a spring (Helix)on the table.		
	AcDbCircle *pCirc1 = new AcDbCircle(AcGePoint3d(10.0,3.0,12.5),AcGeVector3d::kZAxis,1.0);
	pCirc1->setDatabaseDefaults();		

	// In memory polyline is used to form a floor surface
	AcDbPolyline *pLine;
	AcGePoint2d pt0(-10,-10); 
	AcGePoint2d pt1(-10,20); 
	AcGePoint2d pt2(30,20); 
	AcGePoint2d pt3(30,-10); 

	pLine = new AcDbPolyline;
	pLine->setDatabaseDefaults();
	pLine->reset (Adesk::kFalse, 0);

	pLine->addVertexAt (0, pt0);
	pLine->addVertexAt (1, pt1);
	pLine->addVertexAt (2, pt2);
	pLine->addVertexAt (3, pt3);
	pLine->setClosed (Adesk::kTrue);

	entities.append(pLine);
	entities.append(pCirc1);

	// Create regions for a Bowl base(circle) and floor (polyline)
	Acad::ErrorStatus es = AcDbRegion::createFromCurves(entities, regions);
	assert(es == Acad::eOk);

	delete pLine;
	delete pCirc1;

	AcDbPlaneSurface *pSurf = NULL;
	// After Regions, create the surfaces and set the colors
	for(int ctr=0;ctr < regions.length();ctr++)
	{
		pSurf = new AcDbPlaneSurface();
		pSurf->setDatabaseDefaults();
		AcDbRegion *pRegion = (AcDbRegion*)regions[ctr];
		pSurf->createFromRegion(pRegion);
		if(0 == ctr)
		{
			AcCmColor col;
			col.setRGB(40,216,251);
			pSurf->setColor(col);
		}
		else
		{
			AcCmColor col;
			col.setRGB(160,158,209);
			pSurf->setColor(col);
		}
		delete pRegion;
		AddEntityToDatabase(pSurf);
		pSurf->close();

	}
}


void CMakeCreation::AddExtrudedSurface()
{
	// Using AcDbExtrudedSurface class to create a extruded surface , 
	// creating a Table which has 4 legs and table top
	AcDbSweepOptions sweepOptions;
	AcCmColor col;
	col.setRGB(123,72,55);

	// In memory circles for legs.
	AcDbCircle *pCirc1 = new AcDbCircle(AcGePoint3d(1.5,1.5,0.0),AcGeVector3d::kZAxis,0.5);
	AcDbCircle *pCirc2 = new AcDbCircle(AcGePoint3d(1.5,8.5,0.0),AcGeVector3d::kZAxis,0.5);
	AcDbCircle *pCirc3 = new AcDbCircle(AcGePoint3d(18.5,8.5,0.0),AcGeVector3d::kZAxis,0.5);
	AcDbCircle *pCirc4 = new AcDbCircle(AcGePoint3d(18.5,1.5,0.0),AcGeVector3d::kZAxis,0.5);

	pCirc3->setDatabaseDefaults();
	pCirc2->setDatabaseDefaults();
	pCirc1->setDatabaseDefaults();
	pCirc4->setDatabaseDefaults();

	// In memory polyline for table top
	AcDbPolyline * pLine;
	AcGePoint2d pt0(0,-1); 
	AcGePoint2d pt1(0,11); 
	AcGePoint2d pt2(20,11); 
	AcGePoint2d pt3(20,-1); 

	pLine = new AcDbPolyline;
	pLine->setDatabaseDefaults();
	pLine->reset (Adesk::kFalse, 0);

	pLine->addVertexAt (0, pt0);
	pLine->addVertexAt (1, pt1);
	pLine->addVertexAt (2, pt2);
	pLine->addVertexAt (3, pt3);
	pLine->setClosed (Adesk::kTrue);
	pLine->setElevation(10.0);

	AcGeVector3d directionVec = AcGeVector3d::kZAxis;
	directionVec *= 10.0;

	// Create the table legs ,top and set the colors
	CreateExtrudedSurface(pCirc1,directionVec,sweepOptions,col);
	CreateExtrudedSurface(pCirc2,directionVec,sweepOptions,col);
	CreateExtrudedSurface(pCirc3,directionVec,sweepOptions,col);
	CreateExtrudedSurface(pCirc4,directionVec,sweepOptions,col);

	directionVec *= 0.05;
	CreateExtrudedSurface(pLine,directionVec,sweepOptions,col);

	// Clear it all 
	delete pCirc1;
	delete pCirc2;
	delete pCirc3;
	delete pCirc4;
	delete pLine;
}

void CMakeCreation::CreateExtrudedSurface(AcDbEntity* pSweepEnt,
										  const AcGeVector3d& directionVec,
										  AcDbSweepOptions& sweepOptions,
										  AcCmColor col)
{
	AcDbExtrudedSurface *pExtrSurf = new AcDbExtrudedSurface();
	Acad::ErrorStatus es  = pExtrSurf->createExtrudedSurface(pSweepEnt,directionVec,sweepOptions);
	if(Acad::eOk == es)
	{
		CMakeCreation::AddEntityToDatabase(pExtrSurf);
		pExtrSurf->setColor(col);
		pExtrSurf->close();
	}
	else
		delete pExtrSurf;
}

void CMakeCreation::AddRevolvesurface()
{
	// Using AcDbRevolvedSurface to create a revolved surface i.e create a Pen holder on top of the table
	AcCmColor col;
	col.setRGB(230,25,230);
	AcDbRevolvedSurface *pRevSurf = new AcDbRevolvedSurface();
	AcGePoint3d axisPnt(16.7,5.0,10.5);
	AcGeVector3d axisDir = AcGeVector3d::kYAxis;
	double revAngle = 2.0*KPI;
	double startAngle = 0.0;
	AcDbRevolveOptions revolveOptions;

	// In memory polyline to represents the longitudinal cross-section of  the pen holder
	AcDbPolyline * pLine;
	AcGePoint2d pt0(16.0,5.0); 
	AcGePoint2d pt1(16.1,5.0); 
	AcGePoint2d pt2(16.1,8.0); 
	AcGePoint2d pt3(16.0,8.0); 

	pLine = new AcDbPolyline;
	pLine->setDatabaseDefaults();
	pLine->reset (Adesk::kFalse, 0);

	pLine->addVertexAt (0, pt0);
	pLine->addVertexAt (1, pt1);
	pLine->addVertexAt (2, pt2);
	pLine->addVertexAt (3, pt3);
	pLine->setClosed (Adesk::kTrue);
	pLine->setElevation(10.5);

	// Create the surface
	Acad::ErrorStatus es = pRevSurf->createRevolvedSurface(pLine,axisPnt,axisDir,revAngle,startAngle,revolveOptions);
	delete pLine;

	if(Acad::eOk == es)
	{
		AcGeMatrix3d mat;
		mat.setToRotation(KPI/2.0,AcGeVector3d::kXAxis,AcGePoint3d(16.7,5.0,10.5));
		AddEntityToDatabase(pRevSurf);
		pRevSurf->transformBy(mat);
		pRevSurf->setColor(col);
		pRevSurf->close();
	}
	else
		delete pRevSurf;
}

void CMakeCreation::AddSweptSurface()
{
	// Using the AcDbSweptSurface class adds a swept surfaces .
	//Pen is created using the swept surface and its added in the pen holder, 
	// the stand in the light stand is also created using swept surfaces
	Acad::ErrorStatus es;

	// Polyline that represents the axis of the of the pen.
	AcDb3dPolyline * pLine;
	AcGePoint3dArray pts;

	AcCmColor col;
	col.setRGB(253,106,73);

	AcGeVector3d vecdir(-0.4,0.0,3.0);
	vecdir.normalize();
	AcGeVector3d vecperp = vecdir;
	pts.append(AcGePoint3d(16.5,5.0,10.5) );
	pts.append(AcGePoint3d(16.1,5.0,13.5)+1.5*vecdir);
	pLine = new AcDb3dPolyline(k3dSimplePoly,pts);
	pLine->setDatabaseDefaults();

	vecperp.rotateBy(KPI*270.0/180.0,-AcGeVector3d::kYAxis);

	// Circle that represents the cross-section of the pen
	AcDbCircle *pCirc = new AcDbCircle(AcGePoint3d(16.55,5.0,10.5),AcGeVector3d::kZAxis,0.05);
	pCirc->setDatabaseDefaults();

	AcDbSweepOptions sweepOpts;

	// Sweep options to align the cross-section with the axis and also bank it with respect to (W.R.T) the axis
	sweepOpts.setBank(true);
	sweepOpts.setAlign(AcDbSweepOptions::kAlignSweepEntityToPath);

	// Create the pen surface
	AcDbSweptSurface *pSwptSurf = new AcDbSweptSurface();

	es = pSwptSurf->createSweptSurface(pCirc,pLine,sweepOpts);
	delete pCirc;
	delete pLine;

	if(Acad::eOk == es)
	{
		AcGeMatrix3d mat;
		mat.setToTranslation(0.05*vecperp);
		AddEntityToDatabase(pSwptSurf);
		pSwptSurf->transformBy(mat);
		pSwptSurf->setColor(col);
		pSwptSurf->close();
	}
	else
		delete pSwptSurf;

	// Polyline that represents the cross-section of the stand in the light stand
	AcDbPolyline * standline=NULL;
	AcGePoint2d pt0(17.7,7.7); 
	AcGePoint2d pt1(17.7,8.3); 
	AcGePoint2d pt2(18.3,8.3); 
	AcGePoint2d pt3(18.3,7.7); 

	standline = new AcDbPolyline;
	standline->setDatabaseDefaults();
	standline->reset (Adesk::kFalse, 0);

	standline->addVertexAt (0, pt0);
	standline->addVertexAt (1, pt1);
	standline->addVertexAt (2, pt2);
	standline->addVertexAt (3, pt3);
	standline->setClosed (Adesk::kTrue);
	standline->setElevation(10.5);

	// Create a spline that represents the axis of sweep that the polyline above
	// will follow
	pts.removeAll();
	pts.append(AcGePoint3d(19.0,8.0,10.5));
	pts.append(AcGePoint3d(18.7,8.0,13.5));
	pts.append(AcGePoint3d(18.3,8.0,14.5));
	pts.append(AcGePoint3d(18.0,8.0,17.5));

	AcDbSpline *pSpln = new AcDbSpline(pts);

	AcDbSweepOptions standsweepOpts;

	// Create the stand surface
	pSwptSurf = new AcDbSweptSurface();

	// Make sure the profile aligns with the sweep path
    standsweepOpts.setAlign(AcDbSweepOptions::kAlignSweepEntityToPath);
	standsweepOpts.setBank(true);

	es = pSwptSurf->createSweptSurface(standline,pSpln,standsweepOpts);

	delete standline;
	delete pSpln;

	if(Acad::eOk == es)
	{
		AddEntityToDatabase(pSwptSurf);
		col.setRGB(55,230,84);
		pSwptSurf->setColor(col);
		pSwptSurf->close();
	}
	else
		delete pSwptSurf;		

}
void CMakeCreation::AddLoftedSurface()
{
	// Using the AcDbLoftedSurface class creating a lofted Surface. 
	// The lamp shade surface and the bowl surface are created as a lofted surface
	AcCmColor col;
	col.setRGB(252,234,39);

	// In memory circles that represents the lamp shade profile
	AcDbCircle *pCirc1 = new AcDbCircle(AcGePoint3d(18.0,8.0,15.5),AcGeVector3d::kZAxis,2.0);
	AcDbCircle *pCirc2 = new AcDbCircle(AcGePoint3d(18.0,8.0,17.5),AcGeVector3d::kZAxis,1.0);

	AcGePoint3dArray pts;

	pts.append(AcGePoint3d(20.0,8.0,15.5));
	pts.append(AcGePoint3d(19.3,8.0,16.5));
	pts.append(AcGePoint3d(19.0,8.0,17.5));

	// In memory splines that serve as guide curves for the lamp shade
	AcDbSpline *pSpln1 = new AcDbSpline(pts);

	pts.removeAll();
	pts.append(AcGePoint3d(16.0,8.0,15.5));
	pts.append(AcGePoint3d(16.7,8.0,16.5));
	pts.append(AcGePoint3d(17.0,8.0,17.5));

	AcDbSpline *pSpln2 = new AcDbSpline(pts);

	// Create the shade surface
	AcDbLoftedSurface *pLoftSurfTemp = new AcDbLoftedSurface();

	AcDbLoftOptions loftOptsTemp;

	AcArray<AcDbEntity *> pEntsTemp;
	pEntsTemp.append(pCirc1);
	pEntsTemp.append(pCirc2);
	AcArray<AcDbEntity *> pGuidesTemp;

	pGuidesTemp.append(pSpln1);
	pGuidesTemp.append(pSpln2);

	Acad::ErrorStatus esTemp = pLoftSurfTemp->createLoftedSurface(pEntsTemp,pGuidesTemp,NULL,loftOptsTemp);

	if(Acad::eOk == esTemp)
	{
		AddEntityToDatabase(pLoftSurfTemp);
		pLoftSurfTemp->setColor(col);
		pLoftSurfTemp->close();
	}
	else
		delete pLoftSurfTemp;

	delete pCirc1;
	delete pCirc2;
	delete pSpln1;
	delete pSpln2;

	// In memory circles that represents the profile of the bowl that sits on the helix
	pCirc1 = new AcDbCircle(AcGePoint3d(10.0,3.0,12.5),AcGeVector3d::kZAxis,1.0);
	pCirc2 = new AcDbCircle(AcGePoint3d(10.0,3.0,14.5),AcGeVector3d::kZAxis,2.0);

	pts.removeAll();
	pts.append(AcGePoint3d(11.0,3.0,12.5));
	pts.append(AcGePoint3d(11.8,3.0,13.5));
	pts.append(AcGePoint3d(12.0,3.0,14.5));

	// Splines that act as guide curves for the bowl profile.
	pSpln1 = new AcDbSpline(pts);

	pts.removeAll();
	pts.append(AcGePoint3d(9.0,3.0,12.5));
	pts.append(AcGePoint3d(8.2,3.0,13.5));
	pts.append(AcGePoint3d(8.0,3.0,14.5));

	pSpln2 = new AcDbSpline(pts);

	// Create the bowl surface
	pLoftSurfTemp = new AcDbLoftedSurface();

	pEntsTemp.removeAll();
	pEntsTemp.append(pCirc1);
	pEntsTemp.append(pCirc2);

	pGuidesTemp.removeAll();
	pGuidesTemp.append(pSpln1);
	pGuidesTemp.append(pSpln2);

	esTemp = pLoftSurfTemp->createLoftedSurface(pEntsTemp,pGuidesTemp,NULL,loftOptsTemp);

	if(Acad::eOk == esTemp)
	{
		AddEntityToDatabase(pLoftSurfTemp);
		col.setRGB(40,216,251);
		pLoftSurfTemp->setColor(col);
		pLoftSurfTemp->close();
	}
	else
		delete pLoftSurfTemp;

	delete pCirc1;
	delete pCirc2;
	delete pSpln1;
	delete pSpln2;

}

void CMakeCreation::AddHelix()
{
	// Using AcDbHelix helix. 
	// This helix object created using AcDbHelix, acts as a stand for the bowl.
	AcDbHelix *pHelix = new AcDbHelix();
	Acad::ErrorStatus es;
	AcCmColor col;
	col.setRGB(208,83,204);

	pHelix->setDatabaseDefaults();

	// Set the Helix parameters
	es = pHelix->setConstrain(AcDbHelix::kHeight);
	es = pHelix->setHeight(2.0);
	es = pHelix->setTurns(20.0);
	es = pHelix->setAxisVector(AcGeVector3d::kZAxis);	
	es = pHelix->setBaseRadius(0.8);
	es = pHelix->setTopRadius(0.4);
	//pHelix->setAxisPoint(AcGePoint3d(5.0,3.0,10.5));
	pHelix->setAxisPoint(AcGePoint3d(10.0,3.0,10.5));

	// The following call creates the internal spline that defines the helix path
	es = pHelix->createHelix(); // Generate the spline

	if(Acad::eOk == es)
	{
		AddEntityToDatabase(pHelix);
		pHelix->setColor(col);
		pHelix->close();			
	}
	else
		delete pHelix;
}


AcDbObjectId CMakeCreation::AddEntityToDatabase(AcDbEntity *pEnt, ACHAR *spc, AcDbDatabase *pDb)
{
	// Adding entity in to the Database, by default it will add in to the 
	AcDbObjectId outObjId=AcDbObjectId::kNull;
	Acad::ErrorStatus es;
	if(NULL != spc && NULL != pEnt && NULL != pDb)
	{
		AcDbBlockTablePointer pBT(pDb->blockTableId(),AcDb::kForRead);

		if(Acad::eOk == pBT.openStatus())
		{
			AcDbObjectId recordId=AcDbObjectId::kNull;
			pBT->getAt(spc,recordId);
			AcDbBlockTableRecordPointer pBtr(recordId,AcDb::kForWrite);
			if(Acad::eOk == pBtr.openStatus())
			{
				es = pBtr->appendAcDbEntity(outObjId,pEnt);
			}
		}
	}
	return outObjId;
}
