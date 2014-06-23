#ifndef ACDB_AUTIL_H
#define ACDB_AUTIL_H
//
// (C) Copyright 1993-1997 by Autodesk, Inc. 
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

#include "adesk.h"
#include "ads.h"

class AcGeMatrix3d;

// ADS input options
//
#define INP_NNULL     0x01
#define INP_NZERO     0x02
#define INP_NNEG      0x04
#define INP_NLIM      0x08
#define INP_DASH      0x20
#define INP_NZCOORD   0x40

// ADS redraw types
//
#define RD_DRAW       1
#define RD_ERASE      2
#define RD_HILITE     3
#define RD_UNHI       4

Adesk::Boolean acdbWcs2Ucs(ads_point p, ads_point q, Adesk::Boolean vec);

Adesk::Boolean acdbWcs2Ecs(ads_point p, ads_point q, ads_point norm, 
			   Adesk::Boolean vec);

Adesk::Boolean acdbUcs2Wcs(ads_point p, ads_point q, Adesk::Boolean vec);

Adesk::Boolean acdbUcs2Ecs(ads_point p, ads_point q, ads_point norm, 
			   Adesk::Boolean vec);

Adesk::Boolean acdbEcs2Wcs(ads_point p, ads_point q, ads_point norm, 
			   Adesk::Boolean vec);

Adesk::Boolean acdbEcs2Ucs(ads_point p, ads_point q, ads_point norm, 
			   Adesk::Boolean vec);

Adesk::Boolean acdbUcsMatrix(AcGeMatrix3d& mat);

#endif
