//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
//

#ifndef ARXDBGDLINKERREACTOR_H
#define ARXDBGDLINKERREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgDLinkerReactor:
**
**  **jma
**
*************************************/

class ArxDbgDLinkerReactor : public AcRxDLinkerReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxDbgDLinkerReactor);

        // constructors/destructor
					ArxDbgDLinkerReactor();
    virtual			~ArxDbgDLinkerReactor();

    virtual void	rxAppWillBeLoaded(const char* moduleName);
    virtual void	rxAppLoaded(const char* moduleName);
    virtual void	rxAppLoadAborted(const char* moduleName);

    virtual void	rxAppWillBeUnloaded(const char* moduleName);
    virtual void	rxAppUnloaded(const char* moduleName);
    virtual void	rxAppUnloadAborted(const char* moduleName);

private:
    void    printReactorMessage(LPCTSTR event, const char* moduleName) const;

        // outlawed functions
							ArxDbgDLinkerReactor(const& ArxDbgDLinkerReactor);
    ArxDbgDLinkerReactor&	operator=(const& ArxDbgDLinkerReactor);        
};


#endif    // ARXDBGDLINKERREACTOR_H
