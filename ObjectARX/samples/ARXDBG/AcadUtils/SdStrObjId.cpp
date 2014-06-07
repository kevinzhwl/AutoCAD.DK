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

#include "stdafx.h"
#include "SdStrObjId.h"


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// SdStrObjIdNode //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    SdStrObjIdNode::SdStrObjIdNode (constructor)
**
**    **jma
**
*************************************/

SdStrObjIdNode::SdStrObjIdNode(LPCTSTR name, const AcDbObjectId& objId)
:    m_name(name),
    m_objid(objId)
{
}


/////////////////////////////////////////////////////////////////////////////
///////////////////////////// SdStrObjIdList ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**    SdStrObjIdList::SdStrObjIdList(constructor)
**
**    **jma
**
*************************************/

SdStrObjIdList::SdStrObjIdList(BOOL caseSensitive)
:    m_caseSensitive(caseSensitive)
{
}

/****************************************************************************
**
**    SdStrObjIdList::~SdStrObjIdList (destructor)
**
**    **jma
**
*************************************/

SdStrObjIdList::~SdStrObjIdList()
{
    RemoveAll();
}

/****************************************************************************
**
**    SdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

void
SdStrObjIdList::RemoveAll()
{
    SdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while(pos != NULL){
        nodePtr = static_cast<SdStrObjIdNode*>(m_list.GetNext(pos));
        delete nodePtr;
    }
    m_list.RemoveAll();
}

/****************************************************************************
**
**    SdStrObjIdList::AddAlpha
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddAlpha(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    SdStrObjIdNode* tmpNode;

    POSITION pos = m_list.GetHeadPosition();

    if (!m_caseSensitive) {
        while (pos != NULL) {
            tmpNode = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.CompareNoCase(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    else {
        while (pos != NULL) {
            tmpNode = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
            if (tmpNode && (tmpNode->m_name.Compare(name) > 0))
                return(m_list.InsertBefore(pos, static_cast<void*>(newNode)));
            m_list.GetNext(pos);
        }
    }
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::AddHead
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddHead(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    return(m_list.AddHead(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::AddTail
**
**    **jma
**
*************************************/

POSITION
SdStrObjIdList::AddTail(LPCTSTR name, const AcDbObjectId& objId)
{
    SdStrObjIdNode* newNode = new SdStrObjIdNode(name, objId);
    return(m_list.AddTail(static_cast<void*>(newNode)));
}

/****************************************************************************
**
**    SdStrObjIdList::GetAtIndex
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetAtIndex(int index, CString& str, AcDbObjectId& objId) const
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        SdStrObjIdNode* node;
        node = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
        str = node->m_name;
        objId = node->m_objid;
        return(TRUE);
    }
    else
        return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetIndexFor(const CString& str, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetIndexFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetIndexFor(const AcDbObjectId& objId, int& index) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            index = i;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetMatchFor(const CString& str, AcDbObjectId& objId) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (str.CompareNoCase(tmpStr) == 0) {
            objId = tmpId;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::GetMatchFor
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::GetMatchFor(const AcDbObjectId& objId, CString& str) const
{
    CString tmpStr;
    AcDbObjectId tmpId;

    SdStrObjIdListIterator iter(*this);
    for (int i=0; !iter.done(); iter.next(), i++) {
        iter.item(tmpStr, tmpId);
        if (tmpId == objId) {
            str = tmpStr;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**    SdStrObjIdList::Rename
**
**    **jma
**
*************************************/

BOOL
SdStrObjIdList::Rename(const CString& oldName, const CString& newName)
{
    SdStrObjIdNode* nodePtr;

    POSITION pos = m_list.GetHeadPosition();
    while (pos != NULL) {
        nodePtr = static_cast<SdStrObjIdNode*>(m_list.GetNext(pos));
        if (nodePtr->m_name == oldName) {
            nodePtr->m_name = newName;
            return(TRUE);
        }
    }
    return(FALSE);
}

/****************************************************************************
**
**	SdStrObjIdList::RemoveAt
**
**	**jma
**
*************************************/

void
SdStrObjIdList::RemoveAt(int index)
{
    POSITION pos = m_list.FindIndex(index);
    if (pos) {
        SdStrObjIdNode* node;
        node = static_cast<SdStrObjIdNode*>(m_list.GetAt(pos));
        delete node;
        m_list.RemoveAt(pos);
    }
}

/****************************************************************************
**
**    SdStrObjIdListIterator::SdStrObjIdListIterator
**
**    **jma
**
*************************************/

SdStrObjIdListIterator::SdStrObjIdListIterator(const SdStrObjIdList& list)
:    m_list(list.m_list)
{
    m_pos = m_list.GetHeadPosition();
}

/****************************************************************************
**
**    SdStrObjIdListIterator::item
**
**    **jma
**
*************************************/

void
SdStrObjIdListIterator::item(CString& name, AcDbObjectId& objId) const
{
    SdStrObjIdNode* node;

    node = static_cast<SdStrObjIdNode*>(m_list.GetAt(m_pos));
    name = node->m_name;
    objId = node->m_objid;
}






