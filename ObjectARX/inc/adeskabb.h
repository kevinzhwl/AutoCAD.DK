//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef   _ADESKABB_H
#define   _ADESKABB_H

// DESCRIPTION:
//
// Using the fully qualified names from the `Adesk' struct can be
// cumbersome.	If there are no global name conflicts use the
// following synonyms for convenience.
//
// Note:  All interface descriptions must use fully qualified names.
//	  That is, header files MUST NOT include this file and MUST
//	  NOT use these abbreviations.
//
// Note:  If any of the following abbreviations cause conflicts and
//	  this file cannot be included, then the acceptable abbreviations
//	  (those that do not cause conflicts) will have to be manually
//	  introduced, or another abbreviation header file will have to
//	  be created containing only the acceptable abbreviations.
//
// Note:  When this file is included in a source file, it MUST BE
//	  included AFTER all other include files (except possibly
//	  other abbreviation include files).
//	  For example:
//            #include "foo.h"
//            #include "bar.h"
//            #include "adeskabb.h" // <- Must be last!

#include "adesk.h"

typedef Adesk::Int8	    Int8;
typedef Adesk::Int16	    Int16;
typedef Adesk::Int32	    Int32;
typedef Adesk::UInt8	    UInt8;
typedef Adesk::UInt16	    UInt16;
typedef Adesk::UInt32	    UInt32;
typedef Adesk::uchar	    uchar;
typedef Adesk::ushort	    ushort;
typedef Adesk::uint	    uint;
typedef Adesk::ulong	    ulong;
#ifndef __APPLE__
// Conflicts with a OS X CoreFoundation type.
typedef Adesk::Boolean	    Boolean;
#endif
typedef Adesk::Boolean     AdBoolean;


typedef enum
{
    kTrue                   = Adesk::kTrue,
    kFalse                  = Adesk::kFalse
}
AdBooleanVal;

#endif /* _ADESKABB_H */
