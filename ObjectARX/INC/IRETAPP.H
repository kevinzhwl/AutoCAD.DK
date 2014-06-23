#ifndef __IRETAPP_H__
#define __IRETAPP_H__
//
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
// This interface is to be implemented by all the automation objects.
// The purpose is to let AutoCAD pass its application object (LPDISPATCH)
// to automation objects so that VB users can get the application
// object from any automation object.
//

// {765B4640-664A-11cf-93F3-0800099EB3B7}
DEFINE_GUID(IID_IRetrieveApplication, 
0x765b4640, 0x664a, 0x11cf, 0x93, 0xf3, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IRetrieveApplication */
DECLARE_INTERFACE_(IRetrieveApplication, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IRetrieveApplication methods */
    STDMETHOD(SetApplicationObject)(THIS_ LPDISPATCH pAppDisp) PURE;
};

typedef IRetrieveApplication FAR* LPRETRIEVEAPPLICATION;

#endif // __IRETAPP_H__
