// (C) Copyright 1997 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Header for Rx application definitions and C++
//                access to AutoCAD Graphics System.
//

#ifndef _ACGS_H
#define _ACGS_H

Adesk::Boolean acgsGetDisplayInfo (int &        drawingWidth,	
                                   int &        drawingHeight,	 
                                   int &        aspectWidth,
                                   int &        aspectHeight);

Adesk::Boolean acgsGetViewportInfo (int         viewportNumber,
                                    int &       left,	
                                    int &       bottom,
                                    int &       right,	
                                    int &       top);	

// This class is returned to the user by acgsGetScreenShot, below.
class ScreenShot {      // pure virtual, abstract
    public:
	virtual Adesk::Boolean getSize (int & width,			 
                                    int & height,
                                    int & depth) const = 0; 

    virtual Adesk::Boolean getColorMap (int             index,
                                        unsigned char & red,
                                        unsigned char & green,
                                        unsigned char & blue) const = 0;

	virtual void const * getScanline (int offsetFromLeft,
                                      int offsetFromTop) const = 0;

	void * operator new (size_t size); // static

	// Be sure to delete your screen shot when you are through with it.
	void operator delete (void * p);   // static

	ScreenShot();
	virtual ~ScreenShot () = 0;
};

ScreenShot * acgsGetScreenShot    (int			viewportNumber);

Adesk::Boolean acgsDisplayImage   (int          viewportNumber,
                                   long         originLeft,	
                                   long         originTop,	
                                   int          imageWidth,	
                                   int          imageHeight,	
                                   void const * imageData,		
                                   int          hasTransparency);

Adesk::Boolean acgsRemoveAnonymousGraphics (int viewportNumber);

#endif // _ACGS_H
