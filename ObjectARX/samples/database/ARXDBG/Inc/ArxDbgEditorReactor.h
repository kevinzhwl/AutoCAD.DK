//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
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

#ifndef ARXDBGEDITORREACTOR_H
#define ARXDBGEDITORREACTOR_H

/****************************************************************************
**
**  CLASS ArxDbgEditorReactor:
**
**  **jma
**
*************************************/

class ArxDbgEditorReactor : public AcEditorReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgEditorReactor);

        // constructor/destructors
                    ArxDbgEditorReactor();
    virtual         ~ArxDbgEditorReactor();

        // messages that are sent by notification
    virtual void    unknownCommand(const char* cmdStr, AcDbVoidPtrArray *al);
    virtual void    commandWillStart(const char* cmdStr);
    virtual void    commandEnded(const char* cmdStr);
    virtual void    commandCancelled(const char* cmdStr);
    virtual void    commandFailed(const char* cmdStr);
 
    virtual void    lispWillStart(const char* firstLine);
    virtual void    lispEnded();
    virtual void    lispCancelled();

    virtual void    beginClose(AcDbDatabase* pDwg);

    virtual void    beginDxfIn(AcDbDatabase* db);
    virtual void    abortDxfIn(AcDbDatabase* db);
    virtual void    dxfInComplete(AcDbDatabase* db);

    virtual void    beginDxfOut(AcDbDatabase* pDwg);
    virtual void    abortDxfOut(AcDbDatabase* pDwg);
    virtual void    dxfOutComplete(AcDbDatabase* pDwg);

    virtual void    beginDwgOpen(char* filename);
    virtual void    endDwgOpen(const char* filename);
    virtual void    dwgFileOpened(AcDbDatabase* pDwg, char* fileName);
    virtual void	initialDwgFileOpenComplete(AcDbDatabase* pDwg);

    virtual void    databaseConstructed(AcDbDatabase*);
    virtual void    databaseToBeDestroyed(AcDbDatabase* pDwg);

    virtual void    beginSave(AcDbDatabase* pDwg, const char* pIntendedName);
    virtual void    saveComplete(AcDbDatabase* pDwg, const char* pActualName);
    virtual void	abortSave(AcDbDatabase* pDwg);

    virtual void    beginInsert(AcDbDatabase* pTo, const char* pBlockName, AcDbDatabase* pFrom);
    virtual void    beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom);
    virtual void    otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom);
    virtual void    abortInsert(AcDbDatabase* pTo);
    virtual void    endInsert(AcDbDatabase* pTo);

    virtual void    wblockNotice(AcDbDatabase* pDb);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId);
    virtual void    beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom); 
    virtual void    otherWblock(AcDbDatabase* pTo, AcDbIdMapping& pIdMap, AcDbDatabase* pFrom);
    virtual void    abortWblock(AcDbDatabase* pTo);
    virtual void    endWblock(AcDbDatabase* pTo);

    virtual void    beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& pIdMap);
    virtual void    beginDeepCloneXlation(AcDbIdMapping& pIdMap, Acad::ErrorStatus* pRetStatus);
    virtual void    abortDeepClone(AcDbIdMapping& pIdMap);
    virtual void    endDeepClone(AcDbIdMapping& pIdMap);

    virtual void    sysVarChanged(const char * varName, Adesk::Boolean success);
    virtual void    sysVarWillChange(const char * varName);

    virtual void    beginAttach(AcDbDatabase* pTo, const char* pName, AcDbDatabase* pFrom);
    virtual void    otherAttach(AcDbDatabase* pTo, AcDbDatabase* pFrom);
    virtual void    abortAttach(AcDbDatabase* pTo);
    virtual void    endAttach(AcDbDatabase* pTo);
    virtual void    redirected(AcDbObjectId newId, AcDbObjectId oldId);
    virtual void    comandeered(AcDbDatabase* pTo, AcDbObjectId id, AcDbDatabase* pFrom);
    virtual void    beginRestore(AcDbDatabase* pTo, const char*, AcDbDatabase* pFrom);
    virtual void    abortRestore(AcDbDatabase* pTo);
    virtual void    endRestore(AcDbDatabase* pTo);

    virtual void    xrefSubcommandBindItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void    xrefSubcommandAttachItem(AcDbDatabase* pHost, int activity, const char* pPath);
    virtual void    xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const char* pPath);
    virtual void    xrefSubcommandDetachItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void    xrefSubcommandPathItem(int activity, AcDbObjectId blockId, const char* pNewPath);
    virtual void    xrefSubcommandReloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void    xrefSubcommandUnloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId);

    virtual void    undoSubcommandAuto(int activity, Adesk::Boolean state);
    virtual void    undoSubcommandControl(int activity, int option);
    virtual void    undoSubcommandBegin(int activity);
    virtual void    undoSubcommandEnd(int activity);
    virtual void    undoSubcommandMark(int activity);
    virtual void    undoSubcommandBack(int activity);
    virtual void    undoSubcommandNumber(int activity, int num);

    virtual void    pickfirstModified();
    virtual void    layoutSwitched(const char* newLayoutName);

    virtual void    docFrameMovedOrResized(long hwndDocFrame, bool bMoved);
    virtual void    mainFrameMovedOrResized(long hwndMainFrame, bool bMoved);

    virtual void    beginDoubleClick(const AcGePoint3d& clickPoint);
    virtual void    beginRightClick(const AcGePoint3d& clickPoint);

    virtual void    toolbarBitmapSizeWillChange(Adesk::Boolean bLarge);
    virtual void    toolbarBitmapSizeChanged(Adesk::Boolean bLarge);

    virtual void    beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping& idMap);

    virtual void    partialOpenNotice(AcDbDatabase* pDb);
    virtual void	objectsLazyLoaded(const AcDbObjectIdArray& idArray);

    virtual void	beginQuit();
    virtual void	quitAborted();
    virtual void	quitWillStart();

    virtual void	modelessOperationWillStart(const char* contextStr);
    virtual void	modelessOperationEnded(const char* contextStr);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

		// helper functions
    void    printReactorMessage(LPCTSTR event) const;
    void    printReactorMessage(LPCTSTR event, LPCTSTR msg) const;
    void    printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const;
    void    printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const;
    void    printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const;

    LPCTSTR    xrefActivityToStr(int activity, CString& str);
    LPCTSTR    undoActivityToStr(int activity, CString& str);

        // outlawed functions
							ArxDbgEditorReactor(const& ArxDbgEditorReactor);
    ArxDbgEditorReactor&	operator=(const& ArxDbgEditorReactor);        
};

#endif    // ARXDBGEDITORREACTOR_H
