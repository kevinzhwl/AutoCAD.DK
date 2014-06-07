//
// (C) Copyright 1999 by Autodesk, Inc. 
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
#ifndef _LAB6EMPLOYEEENTRY_H
#define _LAB6EMPLOYEEENTRY_H

#include "dbmain.h"
#define EMPLOYEE_ENTRY_SERVICE "OARXLABS_EMP_ENTRY_SVC"

//we don't want this warning
//AcDbObject *IS* exported
#pragma warning( disable : 4275 )
//we don't want this warning
//AcDbObjectId *IS* exported
#pragma warning( disable : 4251 )
//_LAB6OBJECT is defined in the Lab6Object project
//export the class depending on the
//_LAB6OBJECT symbol
class 
#ifdef _LAB6OBJECT
_declspec(dllexport)
#endif
EmployeeEntry : public AcDbObject{
protected:
    AcDbObjectId m_idEmp;
    static long version;
public:
    ACRX_DECLARE_MEMBERS(EmployeeEntry);
    const AcDbObjectId employee()const;
    Acad::ErrorStatus setEmployee(const AcDbObjectId& idEmp);

    //AcDbObject overrides
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 and vc6 do not properly support array new and delete.
    // The "vector deleting dtor" gets optimized into a scalar deleting
    // dtor by the linker if the server dll does not call vector delete.
    // The linker shouldn't do that, because it doesn't know that the
    // object won't be passed to some other dll which *does* do vector
    // delete.
    //
#ifdef MEM_DEBUG
#undef new
#undef delete
#endif
    void *operator new[](unsigned nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](unsigned nSize, const char *file, int line) { return 0;}
#ifdef MEM_DEBUG
#define new DEBUG_NEW
#define delete DEBUG_DELETE
#endif


};

#endif //_LAB6EMPLOYEEENTRY_H