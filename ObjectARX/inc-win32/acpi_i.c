/*
   (C) Copyright 1999-2011 by Autodesk, Inc. 
  
   Permission to use, copy, modify, and distribute this software in
   object code form for any purpose and without fee is hereby granted, 
   provided that the above copyright notice appears in all copies and 
   that both that copyright notice and the limited warranty and
   restricted rights notice below appear in all supporting 
   documentation.
  
   AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
   AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
   DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
   UNINTERRUPTED OR ERROR FREE.
  
   Use, duplication, or disclosure by the U.S. Government is subject to 
   restrictions set forth in FAR 52.227-19 (Commercial Computer
   Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
   (Rights in Technical Data and Computer Software), as applicable.
  
  
*/


/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Feb 03 17:09:05 2011
 */
/* Compiler settings for U:\develop\global\src\coreapps\opm\Acpi\\acpi.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyIdentifier,0xB2BB79F7,0x06BD,0x42FB,0x81,0x4F,0xEF,0xD6,0x56,0xC1,0x69,0x8C);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspector,0x22A2DE3F,0x1F1E,0x4F04,0xBD,0x55,0xD0,0xF1,0x70,0x32,0x81,0xF9);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspector2,0x75C47098,0xAEEA,0x4355,0xA3,0xB2,0x5E,0x08,0x78,0x96,0x14,0xEA);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditControl,0x6371C569,0x72C0,0x43a0,0xA4,0x57,0x1E,0x9D,0x2E,0xB9,0x20,0x1E);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditControl2,0xFB6BE6DF,0x75C6,0x4F7C,0x94,0x34,0x9B,0x49,0xAF,0x5D,0x98,0x68);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditEventsSink,0xB7332190,0x3EA0,0x4fff,0x97,0x85,0x8E,0x8E,0x0D,0x3F,0x6B,0x21);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyEditEventsSink2,0xDA1087DA,0xCA82,0x4BC1,0xB7,0x70,0x20,0x68,0x78,0x2B,0xEF,0x71);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyUnspecified,0x63ECCF04,0x51B1,0x4fe1,0x97,0x2C,0x9E,0xFD,0x42,0x0A,0xDE,0xF4);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyExpression,0x214D0B04,0xB4BF,0x4D7C,0xA2,0xB8,0x36,0x4E,0x94,0x5E,0xF3,0x11);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyDisplay,0x6a0d7861,0x8773,0x4d56,0xac,0x16,0x95,0xaf,0xf3,0x05,0x1e,0xbd);


MIDL_DEFINE_GUID(IID, IID_IAcPiCategorizeProperties,0x8590b992,0xd9a1,0x48d1,0x89,0x9a,0x35,0x8d,0x77,0xe1,0x51,0x2a);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropCommandButtons,0xA6CD83FA,0x32A5,0x4c1e,0x9F,0x2E,0x48,0x7A,0x61,0x2F,0x4A,0x77);


MIDL_DEFINE_GUID(IID, IID_IAcPiCommandButton,0xA5EAB6FD,0xEB1A,0x43d5,0xBC,0xE0,0x2D,0xA8,0xC4,0x0F,0x21,0xBA);


MIDL_DEFINE_GUID(IID, IID_IAcPiCommandButton2,0xAF4178BF,0x3E04,0x477e,0x80,0xB3,0x33,0xFC,0x2D,0xAE,0x49,0x4E);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorEventsSink,0x3EAF5E3F,0x5D7B,0x4873,0xB8,0xF4,0xA6,0xD9,0xB2,0xD1,0xEB,0x33);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorRefreshEventSink,0x61D3D5C0,0x29D0,0x47a1,0x83,0x89,0xD8,0x04,0xF0,0x95,0x22,0x4A);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorInputEventSink,0xB6E9DB08,0x8B45,0x4ad2,0xB3,0x3C,0x98,0x5B,0xBE,0x4F,0x37,0x56);


MIDL_DEFINE_GUID(IID, IID_IAcPiPropertyInspectorTheme,0x0DB7BC6A,0x444E,0x4477,0xA8,0xE3,0xCC,0x1F,0xF5,0x05,0x3A,0xCD);


MIDL_DEFINE_GUID(IID, IID_IAcPropertyFilter,0x96D606CB,0x1705,0x476d,0x83,0xB4,0x56,0x96,0x1F,0x95,0x1A,0x26);


MIDL_DEFINE_GUID(IID, IID_IAcPiFiltering,0xA3421DB2,0x9202,0x4325,0x99,0x96,0x30,0x8B,0x2C,0xA3,0x2E,0x07);


MIDL_DEFINE_GUID(IID, LIBID_ACPILib,0xC8CAF5A0,0xB473,0x453B,0xB5,0xF0,0xF0,0xBC,0x7A,0x96,0x1C,0x8B);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPiPropertyInspector,0x31DBB451,0x9109,0x41EA,0x85,0x4C,0xB2,0x59,0x05,0x22,0x5A,0xEA);


MIDL_DEFINE_GUID(CLSID, CLSID_AcPiPropertyIdentifier,0x8B049801,0x6BC7,0x46E5,0xAA,0x22,0x95,0xAE,0xA2,0x39,0xBE,0x54);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



