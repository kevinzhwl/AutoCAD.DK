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
// custobj.cpp
// This program demonstrates what it takes to create a custom object class.
// Essentially,  this means deriving a class from AcDbObject and providing
// your own implementations of dwgInFields, dwgOutFields, dxfInFields, and
// dxfOutFields.

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <adslib.h>


// function prototypes

void createDictionary();
void iterateDictionary();
void initApp();
void unloadApp();
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

                       
// class declarations

class MyClass : public AcDbObject
//
// This is a custom object class to demonstrate what's necessary to
// make it work.
//
// To keep it simple,  this class has a single integer data member.
// Get and set functions are provided for this data member.
//
{
public:
    ACRX_DECLARE_MEMBERS(MyClass);
    MyClass() : mIntval(0){};
    MyClass(const Adesk::Int16& val): mIntval(val) {};
    Acad::ErrorStatus           getData(Adesk::Int16&);
    Acad::ErrorStatus           setData(const Adesk::Int16&);
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;
private:
    Adesk::Int16 mIntval;
};

ACRX_DXF_DEFINE_MEMBERS(MyClass, AcDbObject, 0, MYCLASS, CUSTOBJ);
MAKE_ACDBOPENOBJECT_FUNCTION(MyClass);


// gets value of integer data member
//
Acad::ErrorStatus
MyClass::getData(Adesk::Int16& val)
{
    // This is the "get" function.  "val" needs to return with the value
    // of the mIntval data member.  Don't forget to use assertReadEnabled().
    //...

    return Acad::eOk;
}


// Sets value of integer data member
//
Acad::ErrorStatus
MyClass::setData(const Adesk::Int16& val)
{
    // The mIntval data member needs to be set to the value in "val"
    // Don't forget to use assertWriteEnabled() to trigger openedForModify
    // notification.
    //...

    return Acad::eOk;
}


// Files data in from a DWG file
//
Acad::ErrorStatus
MyClass::dwgInFields(AcDbDwgFiler* filer)
{
    // first you need to call assertWriteEnabled() to let AutoCAD know the
    // object is about to be written to and to trigger openedForModify()
    // notification.  Then you need to call the parent class's dwgInFields
    // member function then you need to read in the value for mIntval.
    //...

    // For wblock filing we wrote out our owner as a hard
    // pointer Id so now we need to read it in to keep things
    // in sync.
    //
    if (filer->filerType() == AcDb::kWblockCloneFiler) {
        AcDbHardPointerId id;
        filer->readItem(&id);
    }
    return filer->filerStatus();
}


// Files data out to a DWG file
//
Acad::ErrorStatus
MyClass::dwgOutFields(AcDbDwgFiler* filer) const
{
    // first you need to call assertReadEnabled() to let AutoCAD know the
    // object is about to be read.  Then you need to call the parent class's
    // dwgOutFields member function then you need to write out the mIntval
    // value.
    //...

    // Since objects of this class will be in the Named
    // Objects Dictionary tree and may be hard referenced
    // by some other object, to support wblock we need to
    // file out our owner as a hard pointer Id so that it
    // will be added to the list of objects to be wblocked
    //
    if (filer->filerType() == AcDb::kWblockCloneFiler)
        filer->writeHardPointerId((AcDbHardPointerId)ownerId());

    return filer->filerStatus();
}


// Files data in from a DXF file
//
Acad::ErrorStatus
MyClass::dxfInFields(AcDbDxfFiler* filer)
{
    // call assertWriteEnabled() to let AutoCAD know the object is about to
    // be written to and to trigger openedForModify notification.
    //...

    Acad::ErrorStatus es;
    // call the parent class's dxfInFields member function
    //...

    // Check to see if we're at the right subclass data marker
    // If not,  then return Acad::eBadDxfSequence
    //...

    struct resbuf inbuf;
    // implement a loop to read in the data members
    //...

    return filer->filerStatus();
}


// Files data out to a DXF file
//
Acad::ErrorStatus
MyClass::dxfOutFields(AcDbDxfFiler* filer) const
{
    // first call assertReadEnabled() to let AutoCAD know a read on the object
    // is about to take place.  Then call the parent class's dxfOutFields member
    // function then write out the subclass data marker for "myclass"
    // then write out the mIntval value.
    //...

    return filer->filerStatus();
}


// Creates two objects of class "MyClass" fills them in with the integers
// 1 & 2 and then adds them to the dictionary associated with the key
// "TEST_DICT".  If this dictionary doesn't exist,  then it's created and
// added to the named objects dictionary.
//
void
createDictionary()
{
    AcDbDictionary *pNamedobj;
    // Open the namedobjects dictionary for write setting pNamedobj to
    // point to it.
    //...

    AcDbDictionary *pDict;
    // Search for and open for write (using the pointer pDict to point to
    // it) the dictionary associated with the key "TEST_DICT".  If it's
    // not found,  then create it (setting pDict to point to it) and add
    // it to the namedobjects dictionary.
    //
    // Don't forget to close the namedobjects dictionary when done with
    // it. 
    // ...

    // if the new dictionary is successfully added to the namedobjects
    // dictionary,  create a couple of objects of the "myclass" class.
    // then add them to the newly created dictionary.  Don't forget to
    // close the new objects and the new dictionary when you're done
    // with them.  You'll need to close the myclass objects before closing
    // the new dictionary.
    //.
    if (pDict) {
        // create new objects to add to the new dictionary
        //
        MyClass *pObj1 = new MyClass(1),
                *pObj2 = new MyClass(2);

        AcDbObjectId rId1, rId2;

        // add the new objects to the dictionary
        //
        pDict->setAt("OBJ1", pObj1, rId1);
        pDict->setAt("OBJ2", pObj2, rId2);

        // close the new objects
        //
        pObj1->close();
        pObj2->close();

        // close the new dictionary
        //
        pDict->close();
    }
}


// Opens the dictionary associated with the key "TEST_DICT" and iterates
// through all it's entries printing out the integer data value in each
// entry.
//
void
iterateDictionary()
{
    AcDbDictionary *pNamedobj;
    // Open the namedobjects dictionary for read setting pNamedobj to point
    // to it.
    //...

    AcDbDictionary *pDict;
    // try to access and open the dictionary created in the createDictionary
    // function above.  Use pDict as the pointer.  If it cannot be found or
    // opened,  print an error message, close the namedobject dictionary,
    // and return.  If it does open then just close the namedobject dictionary.
    //...
    
    AcDbDictionaryIterator *pDictIter;
    // Ask the TEST_DICT dictionary for an iterator,  setting pDictIter
    // to point to it.
    //...

    // Set up a loop that uses the iterator to walk down the entries in
    // the dictionary,  reading each "myclass" object's "mIntval" value
    // and printing it out.
    //
    // For this sample we can just assme that there are only MyClass
    // objects stored in the dictionary being iterated over.

    MyClass *pMyCl;
    Adesk::Int16 val;
    for (; !pDictIter->done(); pDictIter->next()) {
          
        // get the current record opened for read setting pMyCl to point
        // to it.  To get pMyCl to work,  you will need to explicitly cast
        // it to an AcDbObject*&  i.e.   (AcDbObject*&)pMyCl
        // ...

        // get the mIntval value of the object pointed to by pMyCl and
        // store it in the variable "val"
        // ...

        // close the MyClass object
        // ...
      
        // print the integer value stored in "val"
        // ...
    }
 
    // delete the iterator
    // ...

    // close the dictionary pointed to by pDict
    // ...
}


// Initialization function called from acrxEntryPoint during kInitAppMsg
// case.  This function is used to add commands to the command stack and
// to add classes to the ACRX class hierarchy
//
void
initApp()
{
    acedRegCmds->addCommand("DICTIONARY_COMMANDS", "CREATE", "CREATE",
        ACRX_CMD_MODAL, createDictionary);

    acedRegCmds->addCommand("DICTIONARY_COMMANDS", "ITERATE", "ITERATE",
        ACRX_CMD_MODAL, iterateDictionary);

    MyClass::rxInit();
    acrxBuildClassHierarchy();
}


// Clean up function called from acrxEntryPoint during the kUnloadAppMsg
// case.  This function removes this apps command set from the command
// stack.
//
void
unloadApp()
{
    acedRegCmds->removeGroup("DICTIONARY_COMMANDS");
    
    // Remove the MyClass class from the ACRX runtime class hierarchy.
    // If this is done while database is still active, it should cause
    // all objects of class MyClass to be turned into proxies. 
    //
    deleteAcRxClass(MyClass::desc());
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
