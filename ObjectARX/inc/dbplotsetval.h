#ifndef AD_DBPLOTSETVAL_H
#define AD_DBPLOTSETVAL_H
//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1988-1999 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
// Name:    dbplotsetval.h
//
// Remarks: This class exports access methods which validate data on an 
//          AcDbPlotSettings object before actually setting the data on
//          the object.
//
//////////////////////////////////////////////////////////////////////////////
//
#pragma pack (push, 8)
class AcArray;
class AcDbPlotSettings;

typedef AcDbPlotSettings::PlotPaperUnits PlotPaperUnits;
typedef AcDbPlotSettings::PlotRotation   PlotRotation;
typedef AcDbPlotSettings::PlotType       PlotType;
typedef AcDbPlotSettings::StdScaleType   StdScaleType;

class AcDbPlotSettingsValidator {
public:    
    virtual Acad::ErrorStatus 
    setPlotCfgName            (AcDbPlotSettings* pPlotSet,
                               const char* plotDeviceName,
                               const char* mediaName = NULL     ) = 0;
    virtual Acad::ErrorStatus 
    setCanonicalMediaName     (AcDbPlotSettings* pPlotSet,
                               const char* mediaName            ) = 0;
    virtual Acad::ErrorStatus
    setPlotOrigin             (AcDbPlotSettings *pPlotSet, 
                               const double xCoordinate,
                               const double yCoordinate         ) = 0;
    virtual Acad::ErrorStatus 
    setPlotPaperUnits         (AcDbPlotSettings* pPlotSet,
                               const PlotPaperUnits units       ) = 0;
    virtual Acad::ErrorStatus 
    setPlotRotation           (AcDbPlotSettings* pPlotSet,
                               const PlotRotation rotationType  ) = 0;
    virtual Acad::ErrorStatus 
    setPlotCentered           (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean isCentered        ) = 0;
    virtual Acad::ErrorStatus 
    setPlotType               (AcDbPlotSettings* pPlotSet,
                               const PlotType plotAreaType      ) = 0;
    virtual Acad::ErrorStatus 
    setPlotWindowArea         (AcDbPlotSettings* pPlotSet,
                               const double xmin,
                               const double ymin,
                               const double xmax,
                               const double ymax                ) = 0;
    virtual Acad::ErrorStatus 
    setPlotViewName           (AcDbPlotSettings* pPlotSet,
                               const char* viewName             ) = 0;
    virtual Acad::ErrorStatus 
    setUseStandardScale       (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean useStandard       ) = 0;
    virtual Acad::ErrorStatus 
    setCustomPrintScale       (AcDbPlotSettings* pPlotSet,
                               const double numerator,
                               const double denominator         ) = 0;
    virtual Acad::ErrorStatus 
    setCurrentStyleSheet      (AcDbPlotSettings* pPlotSet,
                               const char* styleSheetName       ) = 0;
    virtual Acad::ErrorStatus 
    setStdScaleType           (AcDbPlotSettings* pPlotSet,
                               const StdScaleType scaleType     ) = 0;
    virtual Acad::ErrorStatus 
    setStdScale               (AcDbPlotSettings* pPlotSet,
                               const double standardScale       ) = 0;
    virtual Acad::ErrorStatus               
    plotDeviceList            (AcArray<const char*> & deviceList) = 0;

    virtual Acad::ErrorStatus               
    canonicalMediaNameList    (AcDbPlotSettings* pPlotSet,
                               AcArray<const char*> & mediaList ) = 0;
    virtual Acad::ErrorStatus
    getLocaleMediaName        (AcDbPlotSettings *pPlotSet,
                               const char*  canonicalName,
                               const char*& localeName          ) = 0;
    virtual Acad::ErrorStatus
    getLocaleMediaName        (AcDbPlotSettings *pPlotSet,
                               int index,
                               const char*& localeName          ) = 0;
    virtual Acad::ErrorStatus
    setClosestMediaName       (AcDbPlotSettings* pPlotSet,
                               const double paperWidth,
                               const double paperHeight,
                               const PlotPaperUnits units,       
                               Adesk::Boolean matchPrintableArea) = 0;
    virtual Acad::ErrorStatus               
    plotStyleSheetList        (AcArray<const char*> & styleList ) = 0;  

    virtual void              
    refreshLists              (AcDbPlotSettings* pPlotSet       ) = 0;

    virtual void
    setZoomToPaperOnUpdate    (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean doZoom            ) = 0;

    virtual Acad::ErrorStatus
    setDefaultPlotConfig       (AcDbPlotSettings* pPlotSet      ) = 0;
};
#pragma pack (pop)
#endif // AD_DBPLOTSETVAL_H
