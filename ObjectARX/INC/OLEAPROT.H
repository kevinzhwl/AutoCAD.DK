//
// (C) Copyright 1996-1997 by Autodesk, Inc. 
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
// oleaprot.h
//
#ifndef OLEAPROT_H
#define OLEAPROT_H 1

#define AUTOMATION_SERVICE  "AdeskAutomation"

// ----- AutomationWrap -----

class AcAutomationWrap: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcAutomationWrap);
	virtual CLSID *GetCLSID()  =0;
	virtual void SetCLSID(CLSID *clsid) =0;
	virtual IUnknown *GetIUnknown(AcDbObject *pObj) =0;
	virtual void SetIUnknown(AcDbObject *pObj, IUnknown *pUnkOuter) =0;
};
/* This is the protocol extension creation protocol. It is added to the 
 * AcDbDatabase object.
 * By using this protocol to get subsequent protocols, no library other 
 * than the standard acad libraries need be supplied to the user
 */
class AcAutoWrapCreate: public AcRxObject
{
public:
   ACRX_DECLARE_MEMBERS(AcAutoWrapCreate);

   virtual AcAutomationWrap *CreateAutomationProtocol(AcDbObject *pObj, LPCLSID
pclsid) = 0;
}; 

/* Helper function */
#define GET_AUTOMATION_PROTOCOL(pObj) AcAutomationWrap::cast(pObj->queryX(AcAutomationWrap::desc()))  
#define GET_OLEAUTO_CREATE_PROTO(pDb) AcAutoWrapCreate::cast(pDb->queryX(AcAutoWrapCreate::desc())) 
#endif /* OLEAPROT_H */
