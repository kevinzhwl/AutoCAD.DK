//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// DESCRIPTION: True Color Definitions


// headers
#ifndef AD_DBCOLOR_H
#define AD_DBCOLOR_H 1

#include "adesk.h"
#include "acadstrc.h"
#include <assert.h>
#pragma pack (push, 8)


class AcCmEntityColor;


// It takes care of the color method, which is one of the following: 
// byBlock, byLayer, or byColor.
// Depending on this color method it stores RGB, ACI, or Layerindex.
//
// Note: To save memory I did the following:
//          It is not deriving from AcDbXObject. 
//          No virtual methods.
//          Color Method stored in last byte mRGBM.
class AcCmEntityColor
{
public:
    enum Color { kRed,
                 kGreen,
                 kBlue
    };

    // Color Method.
    enum ColorMethod {   kByLayer =0xC0, 
                         kByBlock,
                         kByColor,
                         kByACI,
                         kByPen,
                         kForeground,
                         kLayerOff,
                         // Run-time states
                         kLayerFrozen,
                         kNone
    };

    enum ACIcolorMethod {kACIbyBlock    = 0,
                         kACIforeground = 7,
                         kACIbyLayer    = 256,
                         // Run-time states
                         kACIclear      = 0,    
                         kACIstandard   = 7,
                         kACImaximum    = 255,
                         kACInone       = 257,
                         kACIfrozenLayer= -32700
    };

    // Blue, green, red, and Color Method (byBlock, byLayer, byColor).
    // Is stored that way for better performance. 
    union RGBM {
        Adesk::UInt32    whole;
        Adesk::Int16     indirect;
        struct {
            Adesk::UInt8 blue, 
                         green, 
                         red, 
                         colorMethod;
        };
    };

    AcCmEntityColor     ();
    AcCmEntityColor     (const AcCmEntityColor & color);
    AcCmEntityColor     (const ColorMethod eColorMethod);
    AcCmEntityColor     (const Adesk::UInt8 red, 
                         const Adesk::UInt8 green, 
                         const Adesk::UInt8 blue);

    AcCmEntityColor&    operator =  (const AcCmEntityColor& color);
    bool                operator == (const AcCmEntityColor& color) const;
    bool                operator != (const AcCmEntityColor& color) const;


    // Set/get components
    Acad::ErrorStatus   setColorMethod  (const ColorMethod eColorMethod);
    ColorMethod         colorMethod     () const;

    Acad::ErrorStatus   setColor        (const Adesk::UInt32 color);
    Adesk::UInt32       color           () const;   

    Acad::ErrorStatus   setColorIndex   (const Adesk::Int16 colorIndex);
    Adesk::Int16        colorIndex      () const;

    Acad::ErrorStatus   setLayerIndex   (const Adesk::Int16 layerIndex);
    Adesk::Int16        layerIndex      () const;   

    Acad::ErrorStatus   setPenIndex     (const Adesk::UInt16 penIndex);
    Adesk::UInt16       penIndex        () const;   

    // Set/get RGB components
    Acad::ErrorStatus   setRGB  (const Adesk::UInt8 red, 
                                 const Adesk::UInt8 green, 
                                 const Adesk::UInt8 blue);
    Acad::ErrorStatus   setRed  (const Adesk::UInt8 red);
    Acad::ErrorStatus   setGreen(const Adesk::UInt8 green);
    Acad::ErrorStatus   setBlue (const Adesk::UInt8 blue);
    Adesk::UInt8        red     () const;
    Adesk::UInt8        green   () const;
    Adesk::UInt8        blue    () const;

    // Method check
    bool                isByColor   () const;
    bool                isByLayer   () const;
    bool                isByBlock   () const;
    bool                isByACI     ()   const;
    bool                isByPen     ()  const;
    bool                isForeground() const;
    bool                isLayerOff  () const;
    // Run time states.
    bool                isLayerFrozen() const;
    bool                isNone      ()   const;

    // conversion
    Adesk::UInt32       trueColor () const;
    Adesk::UInt8        trueColorMethod () const;
    Acad::ErrorStatus   setTrueColor ();
    Acad::ErrorStatus   setTrueColorMethod ();



    // static methods for reuse in other classes.
    static  Acad::ErrorStatus   setColorMethod(RGBM* rgbm, const ColorMethod eColorMethod);
    static  ColorMethod         colorMethod   (const RGBM* rgbm);

    static  Acad::ErrorStatus   setColor      (RGBM* rgbm, const Adesk::UInt32 color);
    static  Adesk::UInt32       color         (const RGBM* rgbm);   

    static  Acad::ErrorStatus   setColorIndex (RGBM* rgbm, const Adesk::Int16 colorIndex);
    static  Adesk::Int16        colorIndex    (const RGBM* rgbm);

    static  Acad::ErrorStatus   setLayerIndex (RGBM* rgbm, const Adesk::Int16 layerIndex);
    static  Adesk::Int16        layerIndex    (const RGBM* rgbm);   

    static  Acad::ErrorStatus   setPenIndex   (RGBM* rgbm, const Adesk::UInt16 penIndex);
    static  Adesk::UInt16       penIndex      (const RGBM* rgbm);   

    // Set/get RGB components
    static Acad::ErrorStatus    setRGB  (RGBM* rgbm,
                                         const Adesk::UInt8 red, 
                                         const Adesk::UInt8 green, 
                                         const Adesk::UInt8 blue);
    static Acad::ErrorStatus    setRed  (RGBM* rgbm, const Adesk::UInt8 red);
    static Acad::ErrorStatus    setGreen(RGBM* rgbm, const Adesk::UInt8 green);
    static Acad::ErrorStatus    setBlue (RGBM* rgbm, const Adesk::UInt8 blue);
    static Adesk::UInt8         red     (const RGBM* rgbm);
    static Adesk::UInt8         green   (const RGBM* rgbm);
    static Adesk::UInt8         blue    (const RGBM* rgbm);

    // Method check
    static  bool                isByColor   (const RGBM* rgbm);
    static  bool                isByLayer   (const RGBM* rgbm);
    static  bool                isByBlock   (const RGBM* rgbm);
    static  bool                isByACI     (const RGBM* rgbm);
    static  bool                isByPen     (const RGBM* rgbm);
    static  bool                isForeground(const RGBM* rgbm);
    static  bool                isLayerOff  (const RGBM* rgbm);
    // Run time states.
    static  bool                isLayerFrozen(const RGBM* rgbm);
    static  bool                isNone      (const RGBM* rgbm);



    // Look up mapping between ACI and RGB.
    static Adesk::UInt32        trueColor       (const RGBM* rgbm);
    static Adesk::UInt8         trueColorMethod (const Adesk::Int16);
    static Acad::ErrorStatus    setTrueColor    (RGBM* rgbm);
    static Acad::ErrorStatus    setTrueColorMethod (RGBM* rgbm);

    static Adesk::UInt32        lookUpRGB       (const Adesk::UInt8 colorIndex);
    static Adesk::UInt8         lookUpACI       (const Adesk::UInt8 red,
                                                 const Adesk::UInt8 green,
                                                 const Adesk::UInt8 blue); 

protected:
    Acad::ErrorStatus           setIndirect (const Adesk::Int16 Indirect);
    Adesk::Int16                indirect() const;   
    RGBM mRGBM;

public:
    // The Look Up Table (LUT) provides a mapping between ACI and RGB 
    // and contains each ACI's representation in RGB.
    static const Adesk::UInt8 mLUT[256][3]; 
};

// AcCmEntityColor inline
//

// Default color method is kByColor.
inline 
AcCmEntityColor::AcCmEntityColor()
{
    mRGBM.whole = 0;
    mRGBM.colorMethod = kByColor;
}

inline
AcCmEntityColor::AcCmEntityColor (const AcCmEntityColor & color)
{
    mRGBM.whole = color.mRGBM.whole;
}


// parameter:   eColorMethod    Color method information (byBlock, byLayer, byColor).
inline 
AcCmEntityColor::AcCmEntityColor(const ColorMethod eColorMethod)
{
    mRGBM.whole = 0;
    mRGBM.colorMethod = eColorMethod;
}

// Default color method is kByColor.
// parameter:   red, green, blue
inline  
AcCmEntityColor::AcCmEntityColor(const Adesk::UInt8 red, 
                                 const Adesk::UInt8 green, 
                                 const Adesk::UInt8 blue)
{
    mRGBM.red   = red;
    mRGBM.green = green;
    mRGBM.blue  = blue;
    mRGBM.colorMethod = kByColor;
}

inline AcCmEntityColor& 
AcCmEntityColor::operator= (const AcCmEntityColor & color)
{
    mRGBM.whole = color.mRGBM.whole;
    return *this;
}

inline bool
AcCmEntityColor::operator==(const AcCmEntityColor& color) const
{
    return mRGBM.whole == color.mRGBM.whole;
}

inline bool
AcCmEntityColor::operator!=(const AcCmEntityColor& color) const
{
    return mRGBM.whole != color.mRGBM.whole;
}

// get Color Method
inline AcCmEntityColor::ColorMethod     
AcCmEntityColor::colorMethod() const
{
    return (ColorMethod) mRGBM.colorMethod;
}

// get RGB
//
// return value:    Depending on color method (fourth byte):
//                  kByLayer:   Layer index in first and second byte.
//                  kByColor:   RGB and color method.
//                              First byte blue, second byte green and third byte red.
//                              Fourth byte is color method.
//
//                  kByACI:     ACI index in first and second byte.
//
//                  kByBlock,   
//                  kForeground: Only color method (fourth byte) is valid.    
inline Adesk::UInt32    
AcCmEntityColor::color () const
{
    return mRGBM.whole;
}

// return value:    Layer index.
inline Adesk::Int16
AcCmEntityColor::layerIndex () const
{
    assert (mRGBM.colorMethod == kByLayer ||
            mRGBM.colorMethod == kLayerOff); 

    return mRGBM.indirect;
}

// return value:    Layer index.
inline Adesk::UInt16
AcCmEntityColor::penIndex () const
{
    return (Adesk::UInt16) mRGBM.indirect;
}

// get red
inline Adesk::UInt8    
AcCmEntityColor::red  () const
{
    return mRGBM.red;
}

// get green
inline Adesk::UInt8
AcCmEntityColor::green() const
{
    return mRGBM.green;
}

// get blue
inline Adesk::UInt8    
AcCmEntityColor::blue () const
{
    return mRGBM.blue;
}

inline bool
AcCmEntityColor::isByColor() const
{
    return mRGBM.colorMethod == kByColor; 
}

inline bool
AcCmEntityColor::isByLayer() const
{
    return (mRGBM.colorMethod  == kByLayer ||
            (mRGBM.colorMethod == kByACI   && 
             mRGBM.indirect    == kACIbyLayer)) ? true : false;    
}

inline bool
AcCmEntityColor::isByBlock() const
{
    return (mRGBM.colorMethod  == kByBlock ||
            (mRGBM.colorMethod == kByACI   && 
             mRGBM.indirect    == kACIbyBlock)) ? true : false;    
}

inline bool
AcCmEntityColor::isByACI()   const
{
    return mRGBM.colorMethod == kByACI;
}

inline bool
AcCmEntityColor::isByPen()   const
{
    return mRGBM.colorMethod == kByPen;
}

inline bool
AcCmEntityColor::isForeground()   const
{
    return (mRGBM.colorMethod  == kForeground ||
            (mRGBM.colorMethod == kByACI      && 
             mRGBM.indirect    == kACIforeground)) ? true : false;    
}

inline bool
AcCmEntityColor::isLayerOff() const
{   
    return (mRGBM.colorMethod  == kLayerOff ||
            (mRGBM.colorMethod == kByACI && 
             mRGBM.indirect    <  0      && // layer off for ACI is negative
             mRGBM.indirect    != kACIfrozenLayer)) ? true : false;    
}

inline bool
AcCmEntityColor::isLayerFrozen() const
{   
    return (mRGBM.colorMethod  == kLayerFrozen ||
            (mRGBM.colorMethod == kByACI       && 
             mRGBM.indirect    == kACIfrozenLayer)) ? true : false;    
}

inline bool
AcCmEntityColor::isNone()   const
{
    return (mRGBM.colorMethod  == kNone ||
            (mRGBM.colorMethod == kByACI       && 
             mRGBM.indirect    == kACInone)) ? true : false;    
}

// get indirect
//
// return value:    Indirect can be used for layer index and others.
inline Adesk::Int16    
AcCmEntityColor::indirect () const
{
    assert (mRGBM.colorMethod != kByColor); 
    return mRGBM.indirect;
}

// set indirect
// 
// parameter:   Indirect can be used for layer index and others.
inline Acad::ErrorStatus             
AcCmEntityColor::setIndirect  (const Adesk::Int16 Indirect)
{
    assert (mRGBM.colorMethod != kByColor); 
    mRGBM.indirect = Indirect;
    return Acad::eOk;
}

#pragma pack (pop)
#endif // AD_DBCOLOR_H 
