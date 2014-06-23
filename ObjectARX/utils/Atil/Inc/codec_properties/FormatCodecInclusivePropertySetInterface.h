//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2014 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////



#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif

#ifndef FORMATCODECINCLUSIVEPROPERTYSETINTERFACE_H
#define FORMATCODECINCLUSIVEPROPERTYSETINTERFACE_H

namespace Atil
{

/// <summary>
/// This class groups properties into a set of properties much
/// like a "structure" in "c". 
/// </summary>
///
class FormatCodecInclusivePropertySetInterface : public FormatCodecPropertyInterface
{

public:
    /// <summary>
    /// The virtual destructor.
    /// </summary>
    ///
    virtual ~FormatCodecInclusivePropertySetInterface ();

    /// <summary>
    /// This returns the number of properties in the set.
    /// </summary>
    /// 
    /// <returns>
    /// The number of properties in the set.
    /// </returns>
    ///
    virtual int getNumProperties () const;

    /// <summary>
    /// This returns a selected property from the properties in the set.
    /// </summary>
    /// 
    /// <param name="nIndex">
    /// The index of the property to that is returned.
    /// </param>
    ///
    /// <returns>
    /// A pointer to the property at the index. This pointer should not be freed by the caller.
    /// </returns>
    ///
    virtual FormatCodecPropertyInterface* getProperty (int nIndex) const;

protected:
    /// <summary>
    /// (Protected) Copy constructor.
    /// </summary>
    ///
    /// <param name="iter">
    /// The instance to be copied.
    /// </param>
    ///
    FormatCodecInclusivePropertySetInterface (const FormatCodecInclusivePropertySetInterface& iter);

    /// <summary>
    /// (Protected) The simple constructor.
    /// </summary>
    ///
    FormatCodecInclusivePropertySetInterface ();

    /// <summary>
    /// (Protected) The pre-allocating constructor.
    /// </summary>
    /// 
    /// <param name="nNumToAlloc">
    /// The number of properties that will be in the set.
    /// </param>
    ///
    FormatCodecInclusivePropertySetInterface (int nNumToAlloc);


    /// <summary>
    /// (Protected) This sets the property at index in the set.
    /// </summary>
    /// 
    /// <param name="nIndex">
    /// The index of the property that is to be set.
    /// </param>
    ///
    /// <param name="pProperty">
    /// A pointer to the property that should be placed at the index. The 
    /// property will be <c>clone()</c> copied. The pointer is not held by the set.
    /// </param>
    ///
    void setProperty (int nIndex, FormatCodecPropertyInterface* pProperty);

    /// <summary>
    /// (Protected) This adds the property to the set.
    /// </summary>
    /// 
    /// <param name="pProperty">
    /// A pointer to the property that should be placed at the index. The 
    /// property will be <c>clone()</c> copied. The pointer is not held by the set.
    /// </param>
    ///
    void appendProperty (FormatCodecPropertyInterface* pProperty);

    /// <summary>
    /// (Protected) The array of property pointers held by the set.
    /// </summary>
    ///
    FormatCodecPropertyInterface** mppProperties;

    /// <summary>
    /// (Protected) The number of properties that have been set into the set.
    /// </summary>
    int mnNumProperties;

    /// <summary>
    /// (Protected) The length of the property array.
    /// </summary>
    int mnArraySize;

private:
    FormatCodecInclusivePropertySetInterface& operator= (const FormatCodecInclusivePropertySetInterface& from);    
};

} // end of namespace Atil

#endif
