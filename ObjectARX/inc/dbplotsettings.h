#ifndef AD_DBPLOTSETTINGS_H
#define AD_DBPLOTSETTINGS_H
//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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
// DESCRIPTION: Exported protocol for AcDbPlotSettings

#include "dbmain.h"
#include "dbdict.h"

#pragma pack(push, 8)

// Class definition for paperspace PlotSettings object

class AcDbPlotSettings: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbPlotSettings);

    AcDbPlotSettings(); // This will default to ModelType=True
    AcDbPlotSettings(bool ModelType);
    virtual ~AcDbPlotSettings();

    enum PlotPaperUnits {
        kInches,
        kMillimeters,
        kPixels
    };

    enum PlotRotation {
        k0degrees,
        k90degrees,
        k180degrees,
        k270degrees
    };

    enum PlotType {
        kDisplay,
        kExtents,
        kLimits,
        kView,
        kWindow,
        kLayout
    };

    enum StdScaleType {
        kScaleToFit,                  // Scaled to Fit
        k1_128in_1ft,                 // 1/128"= 1'
        k1_64in_1ft,                  // 1/64"= 1'
        k1_32in_1ft,                  // 1/32"= 1'
        k1_16in_1ft,                  // 1/16"= 1'
        k3_32in_1ft,                  // 3/32"= 1'
        k1_8in_1ft,                   // 1/8" = 1'
        k3_16in_1ft,                  // 3/16"= 1'
        k1_4in_1ft,                   // 1/4" = 1'
        k3_8in_1ft,                   // 3/8" = 1'
        k1_2in_1ft,                   // 1/2" = 1'
        k3_4in_1ft,                   // 3/4" = 1'
        k1in_1ft,                     // 1"= 1'
        k3in_1ft,                     // 3"= 1'
        k6in_1ft,                     // 6"= 1'
        k1ft_1ft,                     // 1'= 1'
        k1_1,                         // 1:1
        k1_2,                         // 1:2
        k1_4,                         // 1:4
        k1_8,                         // 1:8
        k1_10,                        // 1:10
        k1_16,                        // 1:16
        k1_20,                        // 1:20
        k1_30,                        // 1:30
        k1_40,                        // 1:40
        k1_50,                        // 1:50
        k1_100,                       // 1:100
        k2_1,                         // 2:1
        k4_1,                         // 4:1
        k8_1,                         // 8:1
        k10_1,                        // 10:1
        k100_1,                       // 100:1
        k1000_1,                      // 1000:1
        k1and1_2in_1ft                // 1 1/2" = 1'
    };

    enum ShadePlotType {
        kAsDisplayed,
        kWireframe,
        kHidden,
        kRendered
    };

    enum ShadePlotResLevel {
        kDraft,
        kPreview,
        kNormal,
        kPresentation,
        kMaximum,
        kCustom
    };

    Acad::ErrorStatus 
    addToPlotSettingsDict(AcDbDatabase *towhichDb);

    Acad::ErrorStatus 
    copyFrom                   (AcDbPlotSettings *fromPlotSettings);
    
    Acad::ErrorStatus 
    getPlotSettingsName        (const char*& plotSettingsName) const;

    Acad::ErrorStatus 
    getPlotSettingsName        (char*& plotSettingsName) const;

    Acad::ErrorStatus 
    setPlotSettingsName        (const char* plotSettingsName);

    Acad::ErrorStatus 
    getPlotCfgName             (const char*& plotCfgName) const;

    Acad::ErrorStatus    
    getPlotPaperMargins        (double& printableXmin,
                                double& printableYmin,
                                double& printableXmax,
                                double& printableYmax) const;
    Acad::ErrorStatus 
    getPlotPaperSize           (double& paperWidth,
                                double& paperHeight) const;
    Acad::ErrorStatus 
    getCanonicalMediaName      (const char*& mediaName) const;

    Acad::ErrorStatus 
    getPlotOrigin              (double& x,
                                double& y) const;

    AcDbPlotSettings::PlotPaperUnits 
    plotPaperUnits             () const;

    Adesk::Boolean    
    plotViewportBorders        () const;

    void              
    setPlotViewportBorders     (Adesk::Boolean plotViewportBorders);

    Adesk::Boolean    
    plotPlotStyles             () const;

    void              
    setPlotPlotStyles          (Adesk::Boolean plotPlotStyles);

    Adesk::Boolean    
    showPlotStyles             () const;

    void              
    setShowPlotStyles          (Adesk::Boolean showPlotStyles);

    AcDbPlotSettings::PlotRotation   
    plotRotation               () const;

    Adesk::Boolean    
    plotCentered               () const;

    Adesk::Boolean    
    plotHidden                 () const;

    void              
    setPlotHidden              (Adesk::Boolean plotHidden);

    AcDbPlotSettings::ShadePlotType    
    shadePlot                  () const;

    Acad::ErrorStatus              
    setShadePlot               (AcDbPlotSettings::ShadePlotType shadePlot);

    AcDbPlotSettings::ShadePlotResLevel
    shadePlotResLevel          () const;

    Acad::ErrorStatus
    setShadePlotResLevel       (AcDbPlotSettings::ShadePlotResLevel resLevel);

    Adesk::Int16
    shadePlotCustomDPI         () const;

    Acad::ErrorStatus
    setShadePlotCustomDPI      (Adesk::Int16 val);

    AcDbPlotSettings::PlotType 
    plotType                   () const;

    Acad::ErrorStatus 
    getPlotWindowArea          (double& xmin,
                                double& ymin,
                                double& xmax, 
                                double& ymax) const;

    Acad::ErrorStatus 
    getPlotViewName            (const char*& viewName) const;

    Adesk::Boolean    
    useStandardScale           () const;

    Acad::ErrorStatus 
    getCustomPrintScale        (double& numerator,
                                double& denominator) const;

    Acad::ErrorStatus 
    getCurrentStyleSheet       (const char*& styleSheetName) const;

    AcDbPlotSettings::StdScaleType 
    stdScaleType               () const;

    Acad::ErrorStatus 
    getStdScale                (double& scale) const;

    Adesk::Boolean    
    scaleLineweights           () const;

    void              
    setScaleLineweights        (Adesk::Boolean scaleLineweights);

    Adesk::Boolean    
    printLineweights           () const;

    void              
    setPrintLineweights        (Adesk::Boolean printLineweights);

    Adesk::Boolean    
    drawViewportsFirst         () const;

    void              
    setDrawViewportsFirst      (Adesk::Boolean drawViewportsFirst);

    Adesk::Boolean    
    modelType                  () const;

    virtual Acad::ErrorStatus 
    getClassID                 (CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
