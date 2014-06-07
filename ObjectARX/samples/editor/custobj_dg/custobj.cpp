// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
// Description:
//
// This program demonstrates what it takes to create a
// custom object class.  Essentially, this means deriving a
// class from AcDbObject and providing your own
// implementations of dwgInFields, dwgOutFields,
// dxfInFields, and dxfOutFields.

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>

void createDictionary();
void iterateDictionary();
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkMyClass : public AcDbObject
//
// This class demonstrates custom objects.
//
// To keep it simple, this class has a single integer data
// member.  Get and set functions are provided for this
// data member.
//
{
public:
    ACRX_DECLARE_MEMBERS(AsdkMyClass);
    AsdkMyClass(): mIntval(0) {};
    AsdkMyClass(const Adesk::Int16& val): mIntval(val) {};

    Acad::ErrorStatus         getData     (Adesk::Int16&);
    Acad::ErrorStatus         setData     (Adesk::Int16);

    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*)
        const;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*)
        const;
private:
    Adesk::Int16 mIntval;
};

ACRX_DXF_DEFINE_MEMBERS(AsdkMyClass, AcDbObject, 
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
0,
    ASDKMYCLASS, SAMP2);

// Gets the value of the integer data member.
//
Acad::ErrorStatus
AsdkMyClass::getData(Adesk::Int16& val)
{
    // Tells AutoCAD a read operation is taking place.
    //
    assertReadEnabled();
    val = mIntval;
    return Acad::eOk;
}

// Sets the value of the integer data member.
//
Acad::ErrorStatus
AsdkMyClass::setData(Adesk::Int16 val)
{
    // Triggers openedForModify notification.
    //
    assertWriteEnabled();
    mIntval = val;
    return Acad::eOk;
}

// Files data in from a DWG file.
//
Acad::ErrorStatus
AsdkMyClass::dwgInFields(AcDbDwgFiler* pFiler)
{
    assertWriteEnabled();

    AcDbObject::dwgInFields(pFiler);
    // For wblock filing we wrote out our owner as a hard
    // pointer ID so now we need to read it in to keep things
    // in sync.
    //
    if (pFiler->filerType() == AcDb::kWblockCloneFiler) {
        AcDbHardPointerId id;
        pFiler->readItem(&id);
    }
    pFiler->readItem(&mIntval);
    return pFiler->filerStatus();
}

// Files data out to a DWG file.
//
Acad::ErrorStatus
AsdkMyClass::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    assertReadEnabled();

    AcDbObject::dwgOutFields(pFiler);
    // Since objects of this class will be in the Named
    // Objects Dictionary tree and may be hard referenced
    // by some other object, to support wblock we need to
    // file out our owner as a hard pointer ID so that it
    // will be added to the list of objects to be wblocked.
    //
    if (pFiler->filerType() == AcDb::kWblockCloneFiler)
        pFiler->writeHardPointerId((AcDbHardPointerId)ownerId());
    pFiler->writeItem(mIntval);
    return pFiler->filerStatus();
}

// Files data in from a DXF file.
//
Acad::ErrorStatus
AsdkMyClass::dxfInFields(AcDbDxfFiler* pFiler)
{
    assertWriteEnabled();

    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfInFields(pFiler))
        != Acad::eOk)
    {
        return es;
    }

    // Check if we're at the right subclass getData marker.
    //
    if (!pFiler->atSubclassData("AsdkMyClass")) {
        return Acad::eBadDxfSequence;
    }

    struct resbuf inbuf;
    while (es == Acad::eOk) {
        if ((es = pFiler->readItem(&inbuf)) == Acad::eOk) {
            if (inbuf.restype == AcDb::kDxfInt16) {
                mIntval = inbuf.resval.rint;
            }
        }
    }
    return pFiler->filerStatus();
}

// Files data out to a DXF file.
//
Acad::ErrorStatus
AsdkMyClass::dxfOutFields(AcDbDxfFiler* pFiler) const
{
    assertReadEnabled();

    AcDbObject::dxfOutFields(pFiler);
    pFiler->writeItem(AcDb::kDxfSubclass, "AsdkMyClass");
    pFiler->writeItem(AcDb::kDxfInt16, mIntval);
    return pFiler->filerStatus();
}

// This function creates two objects of class AsdkMyClass. It fills them in
// with the integers 1 and 2, and then adds them to the
// dictionary associated with the key ASDK_DICT.  If this
// dictionary doesn't exist, it is created and added
// to the named object dictionary.
//
void
createDictionary()
{
    AcDbDictionary *pNamedobj;
    acdbHostApplicationServices()->workingDatabase()->
        getNamedObjectsDictionary(pNamedobj, AcDb::kForWrite);

    // Check to see if the dictionary we want to create is
    // already present. If not, create it and add
    // it to the named object dictionary.
    //
    AcDbDictionary *pDict;
    if (pNamedobj->getAt("ASDK_DICT", (AcDbObject*&) pDict,
        AcDb::kForWrite) == Acad::eKeyNotFound)
    {
        pDict = new AcDbDictionary;
        AcDbObjectId DictId;
        pNamedobj->setAt("ASDK_DICT", pDict, DictId);
    }
    pNamedobj->close();

    if (pDict) {
        // Create new objects to add to the new dictionary,
        // add them, then close them.
        //
        AsdkMyClass *pObj1 = new AsdkMyClass(1);
        AsdkMyClass *pObj2 = new AsdkMyClass(2);

        AcDbObjectId rId1, rId2;
        pDict->setAt("OBJ1", pObj1, rId1);
        pDict->setAt("OBJ2", pObj2, rId2);

        pObj1->close();
        pObj2->close();
        pDict->close();
    }
}


// Opens the dictionary associated with the key ASDK_DICT
// and iterates through all its entries, printing out the
// integer data value in each entry.
//
void
iterateDictionary()
{
    AcDbDictionary *pNamedobj;
    acdbHostApplicationServices()->workingDatabase()
        ->getNamedObjectsDictionary(pNamedobj, AcDb::kForRead);

    // Get a pointer to the ASDK_DICT dictionary.
    //
    AcDbDictionary *pDict;
    pNamedobj->getAt("ASDK_DICT", (AcDbObject*&)pDict,
        AcDb::kForRead);

    pNamedobj->close();

    // Get an iterator for the ASDK_DICT dictionary.
    //
    AcDbDictionaryIterator* pDictIter= pDict->newIterator();

    AsdkMyClass *pMyCl;
    Adesk::Int16 val;
    for (; !pDictIter->done(); pDictIter->next()) {

        // Get the current record, open it for read, and
        // print its data.
        //
        pDictIter->getObject((AcDbObject*&)pMyCl,
            AcDb::kForRead);
        pMyCl->getData(val);
        pMyCl->close();
        acutPrintf("\nintval is:  %d", val);
    }
    delete pDictIter;
    pDict->close();
}

// The initialization function called from the acrxEntryPoint() function during the
// kInitAppMsg case is used to add commands
// to the command stack and to add classes to the ACRX class
// hierarchy.
//
void
initApp()
{
    acedRegCmds->addCommand("ASDK_DICTIONARY_COMMANDS",
        "ASDK_CREATE", "CREATE", ACRX_CMD_MODAL,
        createDictionary);

    acedRegCmds->addCommand("ASDK_DICTIONARY_COMMANDS",
        "ASDK_ITERATE", "ITERATE", ACRX_CMD_MODAL,
        iterateDictionary);

    AsdkMyClass::rxInit();
    acrxBuildClassHierarchy();
}


// The clean up function called from the acrxEntryPoint() function during the
// kUnloadAppMsg case removes this application's
// command set from the command stack and removes this application's
// custom classes from the ACRX runtime class hierarchy.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("ASDK_DICTIONARY_COMMANDS");

    // Remove the AsdkMyClass class from the ACRX runtime
    // class hierarchy.  If this is done while the database is
    // still active, it should cause all objects of class
    // AsdkMyClass to be turned into proxies.
    //
    deleteAcRxClass(AsdkMyClass::desc());
}

// END CODE APPEARING IN SDK DOCUMENT.


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
