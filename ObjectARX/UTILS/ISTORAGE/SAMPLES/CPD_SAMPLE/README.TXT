AutoCAD structured storage API sample application.

The Compound document facility in AutoCAD is illustrated in this sample. The 
AutoCAD compound document API allows clients to obtain storage objects that 
support IStorage, store their custom data to these IStorages, and manage multiple 
storages.  The storage objects can also be written to an external files and the 
location of the file is stored in the drawing.  The purpose of this API is to give the 
ability to clients to store and manage their persistent objects that use Istorage, 
inside the AutoCAD database.  

The API is given in the file AcCoStg.h.  The documentation for each of the 
methods is also documented in this header file.  Most of the commands 
implemented in this example call,

HRESULT accoGetCompoundDoc(IAcCoCompoundDoc **ppCompoundDoc);

to get the initial IAcCoCompoundDoc interface pointer, and then use various 
methods of this interface.  AutoCAD does an AddRef() on the storage object, when 
returning this pointer to the user, hence after using the storage object, the client 
will have to Release() the object, in order to commit it to the database and also 
avoid memory leaks.

This sample implements many commands, which illustrate the various aspects of 
the AutoCAD structured storage API.  Now let's see the storage object life cycle.

New storages can be created.
CreateStg
Creates a new named transient storage object.  This command uses the 
createStorage(...) method to create the storage object.

HRESULT createStorage(const wchar_t *pStorageName, IStorage **ppStorage);  

You can also create multiple named storage objects, in one AutoCAD session.

Write some stuff to this storage.
addData 
Adds data to the storage object.  Here we do not use any AutoCAD API.  Just use 
the IStorage pointer you got earlier, and stuff some data into it.  Refer Win32 SDK 
for detailed API's that illustrate IStorage usage.  The sample creates some streams 
and writes data supplied by the user.  Typically in a more general setup, an object 
could store itself to the IStorage pointer.

Commit the storage to the database.
closeStg 
Now it is time to store the object in the database and go home.  The API used is, 
guess what? none.  Just Release() the object.  AutoCAD saves the object to the 
database before killing the object.

Find out if storage is there.
hasStg 
This command tests if a named storage is resident in the database or in an external 
file.  The command uses,

HRESULT hasStorage(const wchar_t *pwStgName);

which returns NOERROR if the storage is present.

openStg 
You should remember the name of the storage object in order to wake it up from 
the database.  Then use the following method to get the IStorage pointer.

HRESULT getStorage(const wchar_t *pStorageName, IStorage **ppStorage)

getStorage(..) does not make distinction between internal storage or stored 
externally.

LoadFromXFile
Suppose you had storage in external file and deleted it.  This operation does not 
delete the external file that has the storage object.  So at a later time, if you want to 
make this storage object live, then use the API

HRESULT  loadFromExternalFile (const wchar_t *pExtFileName, const wchar_t 
*pStorageName);

This command illustrates the use of this API.

What does the object contain?
showData 
What does the storage object contain, that we got just now?  This command uses 
the methods of IStorage to read contents and display them.  Refer Win32 API for 
these methods and their details.

What's in a name?
getStgName
This command is weird, because the user gives the name and he get's back the 
same name.  Well, the purpose of this command is to check if the method works 
correctly.  I am sure there are lot of occasions, when you are curious to know the 
name of the storage object whose IStorage pointer is with you, then use this 
method.  

HRESULT getStorageName (IStorage *pStorage, wchar_t **pStorageName);
Note that, the memory for the [out] argument is allocated by CoTaskMemAlloc, 
and the you will have to release this memory using CoTaskMemFree.

getXFileName
Same as above, except that it gets the external file name for the given IStorage 
pointer.

I don't like that name.
SetStgName
Don't like the name of a storage object ?, change it.  Use setStorageName(..) to do 
this, as illustrated by this command.

HRSULT SetStorageName (IStorage *pStorage, const wchar_t *pStorageName);

Nuke it. 
deleteStg 
Well, you can delete an existing storage object, using what?, of course its name.  
This command uses the purgeStorage(..) to delete the storage.  This API removes 
the storage from the database,

HRESULT purgeStorage (const wchar_t *pStorageName);

If any client is holding an IStorage pointer, then the method returns an error.  
Also, if the storage object is residing in an external file, then only the reference to 
the external file in the database is removed and the external file is untouched.

SAVE ME!!!
saveToDb
This command uses the saveToDb(...) API to save the transient storage to the 
database.  

HRESULT SaveToDb (IStorage*);

If a storage with the same name exists in the database, it is overwritten.  Also, if 
one already exists in the database, as an external reference, the reference would be 
erased and the object is written to the database.  The external file is not deleted and 
this command does not delete the external file.

saveToXFile 
The saveToXFile command illustrates the feature of saving the storage object to an 
external file and have the path to the object recorded in the database.

HRESULT saveToExternalFile (IStorage *pStorage, const wchar_t 
*pExtFileName);

If a storage object is already present, it is overwritten. Also if a previous internal 
storage object exists, then it is replaced with an external reference.

Other Trivia.
listStgOpen 
This command does not use any of AutoCAD API.  The sample application keeps 
track of all active storage objects in an MFC based map object and lists them when 
this command is called.

