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
// enttemp.h
//
#ifndef ENTTEMP_H
#define ENTTEMP_H 1

#define TEMPERATURE_SERVICE  "AsdkTemperature"

// The following struct and typedef are used by clients using the
// enttemp api
//
struct TempApp
{
    enum dependency {kNone = -1,
                     kRemove = 0,
                     kAdd = 1};
};

typedef double (*EnergyFuncPtr)(AcDbEntity*);

// ----- EntTemperature -----

class EntTemperature : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(EntTemperature);
	virtual double reflectedEnergy(AcDbEntity* pEnt) const = 0;
};

#endif /* ENTTEMP_H */
