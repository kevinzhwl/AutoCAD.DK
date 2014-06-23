//
// Copyright (C) 2008-2010 by Autodesk, Inc.
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

#pragma once

#include "acstring.h"

class AcRxVariableReactor;

///<summary>Represents a variable in the system. Variables are a convenient way to advertise arbitrary state to other parts of the system.</summary>
///<remarks>
///Variables are created by declaring them in the registry. The following format should be used (elements between {} should be replaced 
///with a legal value for the property or type indicated inside the {}).
//
///[HKEY_LOCAL_MACHINE\{ProductRegistryRoot}\Variables\{AcRxVariable::name()}]
///@="{some value}"  : Required, will be converted to PrimaryDataType
///"PrimaryType"=dword:{AcRxVariable::primaryType()}  :  Required
///"SecondaryType"=dword:{AcRxVariable::seondaryType()}  : Optional
///"TypeFlags"=dword:{AcRxVariable::typeFlags()}  : Optional
///"StorageType"=dword:{AcRxVariable::StorageType}  : Required
///"Owner"="{LogicalAppName|exe}" : Optional
///"Range"="{lowerbound},{upperbound}" : Optional, applies to RTREAL, RTANG, RTSHORT and RTLONG primary types
///
///Note these variables can be get/set using acedGetVar/acedSetVar functions in AutoCAD. They are also visible to the SETVAR command.
///</remarks>
class AcRxVariable
{
public:
    ///<summary>Possible storage type values.</summary>
    enum StorageType
    {
        ///<summary>Application wide, does not persist.</summary>
        kStoragePerSession = 0,
        ///<summary>Application wide, persists per user.</summary>
        kStoragePerUser = 1,
        ///<summary>Application wide, persists per AutoCAD profile.</summary>
        kStoragePerProfile = 2,
        ///<summary>document wide, persists in drawing.</summary>
        kStoragePerDatabase = 3
    };
    ///<summary>Possible secondary type values.</summary>
    enum SecondaryType
    {
        ///<summary>No secondary data type is specified.</summary>
        kSecondaryTypeNone = 0,
        ///<summary>The variable is a boolean. Only valid when primaryDataType==RTSHORT</summary>
        kSecondaryTypeBoolean = 1,
        ///<summary>The variable is a RealDWG symbol name. Only valid when primaryDataType==RTSTR</summary>
        kSecondaryTypeSymbolName = 2,
        ///<summary>The variable represents area value. Only valid when primaryDataType==RTREAL</summary>
        kSecondaryTypeArea = 3,
        ///<summary>The variable represents distance value. Only valid when primaryDataType==RTREAL</summary>
        kSecondaryTypeDistance = 4,
        ///<summary>Marks the last item in the enumeration</summary>
        kSecondaryTypeLast = 4,
    };
    ///<summary>Possible type flag values. These can be 'OR'-ed together.</summary>
    enum TypeFlags
    {
        ///<summary>No type flags are specified.</summary>
        kTypeFlagsNone = 0,
        ///<summary>Spaces are allowed in the variable values. Only valid when primaryDataType==RTSTR</summary>
        kTypeFlagSpacesAllowed = 1,
        ///<summary>. character should be interpreted as empty string. Only valid when primaryDataType==RTSTR</summary>
        kTypeFlagDotMeansEmpty = 2, //primaryType == RTSTR
        ///<summary>Variable does not record for undo.</summary>
        kTypeFlagNoUndo = 4,
        ///<summary>Variable sends notifications when it is set to the same value as the previous value.
        ///Variables normally ignore attempts to set the same value twice in a row.</summary>
        kTypeFlagsChatty = 8
    };
    ///<summary>Represents a bounded range.</summary>
    struct Range
    {
        Range():lowerBound(0), upperBound(0) {}
        ///<summary>Initializes a range to the specified lower and upper bounds.</summary>
        Range(int lb, int ub):lowerBound(lb), upperBound(ub) {}
        ///<summary>Lower bound of the range</summary>
        int lowerBound;
        ///<summary>Upeer bound of the range</summary>
        int upperBound;
    };
    ///<summary>Returns the name of the variable.</summary>
    ///<returns>A non-null, null terminated const ACHAR pointer that represents name.</returns>
    ACDB_PORT const ACHAR* name() const;
    ///<summary>Returns the primary data type of the variable.</summary>
    ///<returns>A short integer (16 bit) that reprents the primary data type.</returns>
    ///<remarks>The allowed values are RTREAL, RTSHORT, RTSTR, RTLONG from adscodes.h</remarks>
    ACDB_PORT short primaryType() const;
    ///<summary>Returns the secondary data type of the variable.</summary>
    ///<returns>A SecondaryType enum value that reprents the secondary data type.</returns>
    ///<remarks>The allowed values are from the SeondaryType enumeration.</remarks>
    ACDB_PORT AcRxVariable::SecondaryType secondaryType() const;
    ///<summary>Returns the storage type of the variable.</summary>
    ///<returns>An StorageType enum value that reprents the storage type.</returns>
    ///<remarks>The allowed values are from the StorageType enumeration.</remarks>
    ACDB_PORT AcRxVariable::StorageType storageType() const;
    ///<summary>Returns the type flags of the variable.</summary>
    ///<returns>A short integer (16 bit) that reprents the type flags.</returns>
    ///<remarks>The allowed values are from the TypeFlags enumeration.</remarks>
    ACDB_PORT short typeFlags() const;
    ///<summary>Returns the range of the variable.</summary>
    ///<returns>Range object that provides the valid range of the variable or NULL if no range restriction was specified</returns>
    ACDB_PORT const Range* range() const;
    ///<summary>Sets the value of the variable.</summary>
    ///<param name='value'>The new value of the variable. Type of <paramref name='value'/> (as given by <paramref name='value'/>.restype) must match
    ///the primaryDataType of the variable.</param>
    ///<param name='ownerId'>Optional. If the variable is read-only then this parameter must be used. The calling application must pass
    ///void* value that RealDWG passed to the application via the acrxEntryPoint function when the application was first loaded.</param>
    ///<param name='failReason'>Optional. If more information is available about the failure then it will be passed to the caller via this
    ///parameter </param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable if the variable is read-only. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT Acad::ErrorStatus setValue(const resbuf& value, void* ownerId = NULL, AcString* failReason=NULL);
    ///<summary>Gets the value of the variable.</summary>
    ///<param name='value'>The current value of the variable. If the <paramref name='value'/>.restype==RTSTR upon successful return 
    ///then <paramref name='value'/>.resval.rstring must be freed using acutDelString </param>
    ///<returns>Returns Acad::eOk if sucessful.</returns>
    ACDB_PORT Acad::ErrorStatus getValue(resbuf& value) const;
    ///<summary>Gets a value indicating whether the variable is read-only.</summary>
    ///<param name='reason'>Optional. If more information is available why the variable is read-only then it will be passed to 
    ///the caller via this parameter </param>
    ///<returns>Returns Acad::eOk if sucessful.</returns>
    ///<remarks>The value of a read-only variable can only be set by its owner.</remarks>
    ACDB_PORT bool isReadOnly(AcString* reason=NULL) const;
    ///<summary>Sets a value indicating whether the variable is read-only</summary>
    ///<param name='value'>Pass true to set the variable read-only.</param>
    ///<param name='ownerId'>The calling application must pass void* value that RealDWG passed to the application via the acrxEntryPoint function 
    ///when the application was first loaded. If the variable already has a different owner then the function will fail. Otherwise the caller will
    ///become the owner of the variable.
    ///Note: This must not be NULL.</param>
    ///<param name='reason'>Optional. If more information is available why the variable is now read-only then the caller should provide it via
    ///this parameter. The parameter is ignored when <paramref name='value'/> is false.</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT Acad::ErrorStatus setIsReadOnly(bool value, void* ownerId, const AcString* reason=NULL);
    ///<summary>Add an observer for this variable.</summary>
    ///<param name='reactor'>Pointer to an object that will receive notifications.</param>
    ACDB_PORT void addReactor(AcRxVariableReactor* reactor);
    ///<summary>Remove an observer for this variable.</summary>
    ///<param name='reactor'>Pointer to an observer that has been receiving notifications.</param>
    ACDB_PORT void removeReactor(AcRxVariableReactor* reactor);
    ///<summary>Reset this variable to its default value. Observers are notified.</summary>
    ///<returns>Returns Acad::eOk if sucessful.</returns>
    ACDB_PORT Acad::ErrorStatus reset();

    ///<summary>Destructor</summary>
    ~AcRxVariable();
 private:
    friend class AcRxImpVariable;
    AcRxVariable(AcRxImpVariable*);
    AcRxImpVariable* m_pImp;
};

///<summary>A singleton instance of this type represents all variables in the system.</summary>
class AcRxVariablesDictionary
{
public:
    ~AcRxVariablesDictionary();
    ///<summary>Add an observer for any variable.</summary>
    ///<param name='reactor'>Pointer to an object that will receive notifications.</param>
    ACDB_PORT void addReactor(AcRxVariableReactor* reactor);
    ///<summary>Remove an observer for any variable.</summary>
    ///<param name='reactor'>Pointer to an observer that has been receiving notifications.</param>
    ACDB_PORT void removeReactor(AcRxVariableReactor* reactor);
    ///<summary>Retrieves the names of all variables currently registered in the system.</summary>
    ///<returns>Returns a constant reference to an array of strings that hold the names of the variables.</returns>
    ACDB_PORT const AcArray<AcString>& getAllNames() const;
    ///<summary>Retrieves a variable.</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<returns>Returns NULL if no variable with the specified name can be found. Other it returns a valid pointer to an AcRxVariable object.</returns>
    ACDB_PORT AcRxVariable* getVariable(const ACHAR* name) const;
    ///<summary>Gets the AcRxVariablesDictionary. This a singleton instance</summary>
    ///<returns>Returns a pointer to the singleton AcrxVariablesDictionary object in the system.</returns>
    ACDB_PORT static AcRxVariablesDictionary* get();
    ///<summary>Resets variables in the AcRxVariablesDictionary, filtered by "filter", to their default values.</summary>
    ///<param name='filter'>Strorage type of variable to reset.</param>
    ///<returns>Returns Acad::eOk if sucessful. Errors out if fails to reset any variable.</returns>
    ACDB_PORT Acad::ErrorStatus reset(AcRxVariable::StorageType filter);

    //Helper functions, we can add more here as we need them

    ///<summary>Gets the named boolean value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='def'>default value that the function will return if the variable does not exist</param>
    ///<returns>Returns the boolean value stored in the named variable of <paramref name='def'/> 
    ///if the variable does not exist</returns>
    ACDB_PORT static bool getBool(const ACHAR* name, bool def);
    ///<summary>Sets the named boolean value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='val'>new value to set</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT static Acad::ErrorStatus setBool(const ACHAR* name, bool val);
    ///<summary>Gets the named Int16 value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='def'>default value that the function will return if the variable does not exist</param>
    ///<returns>Returns the Int16 value stored in the named variable of <paramref name='def'/> 
    ///if the variable does not exist</returns>
    ACDB_PORT static short getInt16(const ACHAR* name, short def);
    ///<summary>Sets the named Int16 value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='val'>new value to set</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT static Acad::ErrorStatus setInt16(const ACHAR* name, short val);
    ///<summary>Gets the named double value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='def'>default value that the function will return if the variable does not exist</param>
    ///<returns>Returns the double value stored in the named variable of <paramref name='def'/> 
    ///if the variable does not exist</returns>
    ACDB_PORT static double getDouble(const ACHAR* name, double def);
    ///<summary>Sets the named double value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='val'>new value to set</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT static Acad::ErrorStatus setDouble(const ACHAR* name, double val);
    ///<summary>Gets the named string value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<returns>Returns the AcString value stored in the named variable of 
    ///if the variable does not exist. The function will return NULL if there's no sysvar with this name</returns>
    ACDB_PORT static AcString getString(const ACHAR* name);
    ///<summary>Sets the named string value</summary>
    ///<param name='name'>Name of the variable to retrieve</param>
    ///<param name='val'>new value to set</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ACDB_PORT static Acad::ErrorStatus setString(const ACHAR* name, const ACHAR* val);

private:
    friend class AcRxImpVariablesDictionary;
    AcRxVariablesDictionary(AcRxImpVariablesDictionary*);
    AcRxImpVariablesDictionary* m_pImp;
};
///<summary>Provides more information in conjunction with AcRxVariableReactor::changed event.</summary>
class AcRxVariableChangedEventArgs
{
public:
    ///<summary>Gets the old value of the variable.</summary>
    ///<returns>Constant reference to the old value of the variable. This value should not be modified. resval.rstring should NOT be freed.</returns>
    ACDB_PORT const resbuf& oldValue() const;
    ///<summary>Gets the new value of the variable.</summary>
    ///<returns>Constant reference to the new value of the variable. This value should not be modified. resval.rstring should NOT be freed.</returns>
    ACDB_PORT const resbuf& newValue() const;

    friend class AcRxImpVariableChangingEventArgs;
    AcRxVariableChangedEventArgs(AcRxImpVariableChangingEventArgs*);
protected:
    AcRxImpVariableChangingEventArgs* m_pImp;
};

///<summary>Provides more information in conjunction with AcRxVariableReactor::changing event.</summary>
class AcRxVariableChangingEventArgs : public AcRxVariableChangedEventArgs
{
public:
    ///<summary>Modify the new value for the variable.</summary>
    ///<param name='value'>The new value of the variable. Type of <paramref name='value'/> (as given by <paramref name='value'/>.restype) must match
    ///the primaryDataType of the variable.</param>
    ///<param name='ownerId'>Optional. If the variable is read-only then this parameter must be used. The calling application must pass
    ///void* value that RealDWG passed to the application via the acrxEntryPoint function when the application was first loaded.</param>
    ///<returns>Returns Acad::eOk if sucessful. Acad::eNotApplicable when the variable has a different owner. Other Acad::ErrorStatus values for 
    ///other failures.</returns>
    ///<remarks>Note that if any observers call this method it will cause the notification cycle to be repeated. All observers who have
    ///already seen the 'changing' notification will see it again with the updated 'newValue'. The cycle is repeated until either some 
    ///observers call veto or no observers call setNewValue or if the cycle makes not progress</remarks>
    ACDB_PORT Acad::ErrorStatus setNewValue(const resbuf& value, void* ownerId = NULL);
    ///<summary>Vetos the variable change.</summary>
    ///<param name='failReason'>Optional. If more information is available about the failure then it should be be passed via this
    ///parameter </param>
    ACDB_PORT void veto(const ACHAR* failReason);
    ///<summary>Returns true if the value due to reset</summary>
    ///<returns>true, if resetting otherwise false</returns>
    ACDB_PORT bool isResetting() const;
    AcRxVariableChangingEventArgs(AcRxImpVariableChangingEventArgs*);
};
///<summary>Callback interface implemented by observers that are interested in events related to variables.</summary>
class ADESK_NO_VTABLE AcRxVariableReactor : public AcRxObject
{
public:
    ///<summary>Called when a variable is about to change but the value has not been modified yet. Callees can veto the change.</summary>
    ///<param name='sender'>Pointer to the variable that is about to change.</param>
    ///<param name='args'>More information about the change.</param>
    ///<remarks>Note that this notification is sent when the variable is about to be set to a new value. This notification is not raised when
    ///when the underlying storage changes thus implicitcly causing the variable to change. For example, if you have a kStoragePerProfile variable
    ///this notification is NOT raised when the profile changes. Similarly, kStoragePerDatabase variables do NOT raise this event when active/working
    ///database changes.</remarks>
    virtual void changing(const AcRxVariable* sender, AcRxVariableChangingEventArgs& args) {}
    ///<summary>Called when a variable has changed.</summary>
    ///<param name='sender'>Pointer to the variable that has changed.</param>
    ///<param name='args'>More information about the change.</param>
    ///<remarks>Note that this notification is sent when the variable has been set to a new value. This notification is not raised when
    ///when the underlying storage changes thus implicitcly causing the variable to change. For example, if you have a kStoragePerProfile variable
    ///this notification is NOT raised when the profile changes. Similarly, kStoragePerDatabase variables do NOT raise this event when active/working
    ///database changes.</remarks>
    virtual void changed(const AcRxVariable* sender, const AcRxVariableChangedEventArgs& args) {}
};

