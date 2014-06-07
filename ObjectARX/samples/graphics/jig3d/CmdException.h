//
// (C) Copyright 1998-2003 by Autodesk, Inc. 
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
#if !defined(_CMDEXCEPTION_H)
#define _CMDEXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CmdException
{
    const char* m_strDesc;
    const Acad::ErrorStatus m_Es;
public:
    CmdException(const Acad::ErrorStatus es,const char* strDesc=NULL)
        :m_strDesc(strDesc),m_Es(es) 
	{}
    CmdException(const char* strDesc)
        :m_strDesc(strDesc),m_Es(Acad::eInvalidInput) 
	{}
    const char* description() const 
	{
		return m_strDesc;
	}
    const Acad::ErrorStatus errorStatus() const 
	{
		return m_Es;
	}
};

#endif