///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECASSOCIATION_H
#define FORMATCODECASSOCIATION_H

namespace Atil
{

class FormatCodecAssociation : public FormatCodecPropertyInterface
{
public:
    enum AssociationType { kThumbnail, kPage, kTransparencyMask, kOther };

public:
    virtual ~FormatCodecAssociation ();

    virtual FormatCodecPropertyInterface* clone () const;

    virtual AssociationType getType () const;
    virtual void setType ( AssociationType type );

    virtual int associatedTo () const;
    virtual void setAssociatedFrameIndex ( int nFrameIndex );

protected:
	FormatCodecAssociation (AssociationType type, int nFrameIndex);

protected:
    AssociationType mAType;
    int mnFrameIndex;
};


} // end of namespace Atil

#endif




