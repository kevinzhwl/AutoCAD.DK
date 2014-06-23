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

#ifndef __ACCOSTG_H__
#define __ACCOSTG_H__

/* NOTES.
HRESULT accoGetCompoundDoc(IAcCoCompoundDoc **ppCompoundDoc [out]);
- This API creates a ACAD CompoundDoc object and hands an
IAcCoCompoundDoc pointer to the client.  The clients can then call
existing named storages or create new named storages in the ACAD database.

Methods of the Interface IAcCoCompoundDoc :

    STDMETHOD(createStorage)(const wchar_t *pStorageName [in], IStorage **ppStorage [out]) PURE;
- creates a new transient storage with the given name.
- fails if one already exists in the database.
- fails if one already exists externally with an internal reference.
- fails if another transient exists with the same name.

    STDMETHOD(getStorage)(const wchar_t *pStorageName [in], IStorage **ppStorage [out]) PURE;
- retrives an existing storage from the database or,
- an external file that has a referece in the database.
- fails if the storage or external reference doesnt exist in the database.

    STDMETHOD(hasStorage)(const wchar_t *pStorageName [in]) PURE;
- to check if the database has a named storage.

    STDMETHOD(purgeStorage)(const wchar_t *pStorageName [in]) PURE;
- purge storage from the database or,
- remove external reference from the database.
- external file is not deleted.
- the user should not hold any IStorage pointers when purging.

    STDMETHOD(setStorageName)(IStorage *pStorage [in], const wchar_t *pStorageName [in]) PURE;
- renames the existing transient storage with the new name.
- fails if a storage/external reference already exists, with the new name.

    STDMETHOD(getStorageName)(IStorage *pStorage [in], wchar_t **pStorageName [out]) PURE;
- gets the storage name for the given storage.
- the memory for the [out] argument is allocated by CoTaskMemAlloc, user
will release this memory using CoTaskMemFree.

    STDMETHOD(saveToDb)(IStorage* [in]) PURE;
- saves the transient storage to the database,
- overwrites if one already exists in the database,
- external reference is lost, if one previously exists.
- external file is not deleted, if one previously exists.

    STDMETHOD(saveToExternalFile)(IStorage *pStorage [in], const wchar_t *pExtFileName [in]) PURE;
- saves the transient storage to the external file.
- overwrites, if one already exists,
- if a previous db storage exists, replaces it with an external reference.

    STDMETHOD(loadFromExternalFile)(const wchar_t *pExtFileName [in], const wchar_t *pStorageName [in]) PURE;
- loads storage from external file,
- fails, if one already exists in the data base with the same name.
- fails, if there is an external reference in the database.
*/

interface IAcCoCompoundDoc : public IUnknown
    {
public:
    STDMETHOD(createStorage)(const wchar_t *pStorageName, IStorage **ppStorage) PURE;
    STDMETHOD(getStorage)(const wchar_t *pStorageName, IStorage **ppStorage) PURE;
    STDMETHOD(hasStorage)(const wchar_t *pStorageName) PURE;
    STDMETHOD(purgeStorage)(const wchar_t *pStorageName) PURE;
    
    STDMETHOD(setStorageName)(IStorage *pStorage, const wchar_t *pStorageName) PURE;
    STDMETHOD(getStorageName)(IStorage *pStorage, wchar_t **pStorageName) PURE;
    
    STDMETHOD(saveToDb)(IStorage*) PURE;
    STDMETHOD(saveToExternalFile)(IStorage *pStorage, const wchar_t *pExtFileName) PURE;
    STDMETHOD(getExternalFileName)(IStorage *pStorage, wchar_t **pExtFileName) PURE;
    STDMETHOD(loadFromExternalFile)(const wchar_t *pExtFileName, const wchar_t *pStorageName) PURE;
    };

EXTERN_C const IID IID_IAcCoCompoundDoc;

HRESULT accoGetCompoundDoc(IAcCoCompoundDoc **ppCompoundDoc);

#endif // __ACCOSTG_H__
