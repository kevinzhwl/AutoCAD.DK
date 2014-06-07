// (C) Copyright 1990-2003 by Autodesk, Inc. 
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

#ifndef _DATAMGR_H_
#define _DATAMGR_H_ 1

#include "acdocman.h"
#include <map>

template <class T> class AsdkDataManager : public AcApDocManagerReactor
{
public:
    AsdkDataManager()
    {
        acDocManager->addReactor(this);
    }
    ~AsdkDataManager()
    {
        acDocManager->removeReactor(this);
    }
    virtual void documentToBeDestroyed( AcApDocument *pDoc )
    {
        m_dataMap.erase(pDoc);
    };

    T& docData(AcApDocument* pDoc)
    {
        std::map<AcApDocument*, T>::iterator i;
        i = m_dataMap.find(pDoc);
        if (i==m_dataMap.end())
            return  m_dataMap[ pDoc ];
        else
            return (*i).second;
    }
    
    T& docData()
    {
        return docData(acDocManager->curDocument());
    }
    
private:
    std::map<AcApDocument*, T> m_dataMap;
};

#endif  /* _DATAMGR_H_ */
