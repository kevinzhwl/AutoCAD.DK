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

#ifndef ARXDBGRBLIST_H
#define ARXDBGRBLIST_H


/******************************************************************
**
**	CLASS ArxDbgRbList
**		Thin wrapper for resbuf chains.  This should be used
**	by other classes and wrapped "thicker" whenever possible.
**	Pay attentiob to orphan/adopt semantics since there is some
**	direct access to the underlying representation.
**
**	**jma
**
****************************/

class ArxDbgRbList {

public:
                ArxDbgRbList();                     // constructs empty list
                ArxDbgRbList(resbuf* adoptedList);  // adopts resbuf chain
                ArxDbgRbList(const ArxDbgRbList&);	// copy constructor (does deep clone)
    virtual		~ArxDbgRbList();

        // assignment
    ArxDbgRbList&        operator=(const ArxDbgRbList& list);    // assign a copy

        // operations on an ArxDbgRbList
    int			length();
    bool        isEmpty()    { return m_head == NULL; }

    void        addHead(resbuf* newNode);
    void        addTail(resbuf* newNode);
    void        append(ArxDbgRbList& appendList);    // destructive to appended list

    resbuf*		detach(resbuf* nodeToDel);    // detach but don't delete
    resbuf*     detach(resbuf* startNode, resbuf* endNode);
    resbuf*     detachHead()    { return detach(m_head); }
    resbuf*     detachTail()    { return detach(m_tail); }

    void        remove(resbuf* nodeToDel);    // detach and delete
    void        removeHead()    { remove(m_head); }
    void        removeTail()    { remove(m_tail); }
    void        removeAll();

        // direct operations on resbuf chain, use only if absolutely necessary
        // these are considered "semi-private"
    void        adoptData(resbuf* adoptedList);	// object takes resposiblity for resbuf*
    resbuf*     orphanData();                   // object gives up responsibility for resbuf*
    resbuf*     data() { return m_head; }       // return pointer to data to pass to ADS

private:
    resbuf*		m_head;        // head of resbuf chain
    resbuf*     m_tail;        // tail of resbuf chain

    bool        addToEmptyList(resbuf* newElement);    // helper function
};


//////////////////////////////////////////////////////////////////////////

    // global functions applicable to raw resbuf usage but also used as helper
    // functions for ArxDbgRbList class
int			dxfCodeToDataType(int resType);
void        dxfToStr(const resbuf* rb, CString& dxfCodeStr, CString& valueStr);
LPCTSTR     bytesToHexStr(char* buffer, int len, CString& hexStr);
resbuf*     duplicateResbufNode(resbuf* rb);
resbuf*     duplicateResbufChain(resbuf* rb);
resbuf*     duplicateResbufChain(resbuf* startPtr, resbuf* endPtr);
resbuf*     ptArrayToResbuf(const AcGePoint3dArray& ptArray);
resbuf*     tailOfResbufChain(resbuf* const rb);
void        printResbufChain(resbuf* const rb);


#endif    // ARXDBGRBLIST_H
