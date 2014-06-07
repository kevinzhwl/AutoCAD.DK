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

#ifndef ARXDBGPERSISTENTENTREACTOR_H
#define ARXDBGPERSISTENTENTREACTOR_H

#include "ArxDbgPersistentObjReactor.h"

/****************************************************************************
**
**	CLASS ArxDbgPersistEntReactor:
**
**	**jma
**
*************************************/

class ArxDbgPersistentEntReactor : public ArxDbgPersistentObjReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgPersistentEntReactor);

        // constructors/destructors
					ArxDbgPersistentEntReactor()	{}
    virtual			~ArxDbgPersistentEntReactor()	{}

    virtual void    modifiedGraphics(const AcDbObject* obj);

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual	Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual	Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

protected:
		// helper functions
    virtual void	printReactorMessage(LPCTSTR event, const AcDbObject* obj) const;

private:
		// data members
    static Adesk::Int16 m_version;

        // outlawed functions
                                ArxDbgPersistentEntReactor(const& ArxDbgPersistentEntReactor);
    ArxDbgPersistentEntReactor&	operator=(const& ArxDbgPersistentEntReactor);        

};

#endif    // ARXDBGPERSISTENTENTREACTOR_H
