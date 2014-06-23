//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#pragma once

#pragma pack (push, 8)


//Forward declarations.
class AFILE;

class ACCORE_PORT CAcUiPathname : public CAdUiPathname {

public:

// methods
        // constructor (initializes private data)
        CAcUiPathname(void);
        CAcUiPathname(const CAcUiPathname&);

        // destructor (frees allocated storage)
        virtual ~CAcUiPathname(void);

        // parse a string, validate the format and fill in the data
        //  This routine actually calls ParseRelative with the
        //  current document path (if any) or the current application
        //  path as the relative path.
        virtual PathErr Parse( LPCTSTR, const BOOL wildcard_ok = FALSE );

        // check status for the path
        //  the returned values are defined in astat.h
        int Status(void);

        // takes a path and tries to open it.  Return TRUE if
        //  the open succeeded, FALSE otherwise.  Note that
        //  these routines set the current directory to the
        //  appropriate place before opening, and reset it
        //  afterward.
        BOOL Open(AFILE** fdp, const TCHAR *openmode);

        // create an assignment operator that does the right thing.
        const CAcUiPathname& operator=(const CAcUiPathname& pathSrc);
        const CAcUiPathname& operator=(const CAcUiPathname* pathSrc);
        
protected:
        // the guts of the assignment operator
        virtual void AssignCopy( const CAcUiPathname& );
    
};

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc)
{
    AssignCopy( pathSrc);

    return *this;
}

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc)
{
    AssignCopy( *pathSrc);

    return *this;
}

#pragma pack (pop)

