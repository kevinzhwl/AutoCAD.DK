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

#ifndef  ATILVERSIONS_H
#define  ATILVERSIONS_H

/// <summary>
/// The public classes, those in the export /inc folder that are exposed by 
/// ATIL.lib library constitute an API for applications. That API is versioned
/// by the defines below. This version number doubles as a version number for
/// the ATIL.lib library itself. 
/// </summary>
///
/// <remarks>
/// The Minor version below is incremented for:
/// 1) The addition of new classes being defined
/// 2) Special cases of binary compatible API additions to existing classes (methods)
/// 3) Major changes of internal logic while maintaining the API. These changes
///    may change implementation behavior while not changing the published usage.
///    This could be interpreted as a warning not to depend on implementation 
///    side effects of ATIL objects. 
///
/// The Major version is incremented when a change is made that renders previous
/// versions of the client api incompatible with the new release of the ATIL. It
/// means that applications will/may need to "port" their application including
/// binary or API incompatibility.
/// </remarks>
///
#define ATILIMAGEAPIMAJORVERSION "3"
#define ATILIMAGEAPIMIMORVERSION "0"

/// <summary>
/// API versions are dictated by these defines located in the ATIL library.
/// When ATIL is built and released, the internal interfaces to the subsystems
/// define these as part of their build string sentinels. This allows checking
/// of AtilImp(ST/MT/98) libraries for API compatability with the ATIL.lib core.
/// </summary>
///
/// <remarks>
/// The Minor version below is incremented for:
/// 1) The addition of new classes such that older subsystems remain compatible. (rare)
///    **This would mean that a "refusal" method would be needed to deny
///    the new class support.
///
/// The Major version is incremented when a change is made that renders previous
/// versions of the implementation subsystems incompatible with the new release 
/// of ATIL.
///
/// NOTE:: Although this versioning provides a degree of safety when mixing
/// implementation libraries with different versions of the ATIL core library,
/// such is NOT recommended. The AtilImp library released with the Atil library
/// are meant to be a matched pair.
/// </remarks>
///
#define ATILSUBSYSTEMAPIMAJORVERSION "3"
#define ATILSUBSYSTEMAPIMINORVERSION "0"

/// <summary>
/// API versions are dictated by these defines located in the ATIL library.
/// When ATIL is built and released, all included format codecs use these 
/// defines as part of their build string sentinels. Then each codec returns
/// an instance of a custom derived class(FormatCodecApiVersion) that returned
/// to and used by ATIL to test compatibility with a codec before registering it
/// for use with ATIL.
///
/// By using a derived class, some custom implementation is possible that may
/// allow a codec to be compatible with more than one version of the API.
/// </summary>
///
/// <remarks>
/// The Minor version below is incremented for:
/// 1) The addition of new property types being defined
/// 2) Special cases of binary compatible API additions (methods)
/// 3) Major changes of internal logic while maintaining the API. These changes
///    may change implementation behavior while not changing the published usage.
///    This could be interpreted as a warning not to depend on implementation 
///    side effects of ATIL objects. 
///
/// The Major version is incremented when a change is made that renders previous
/// versions of the format codecs incompatible with the new release of the ATIL
/// communication system of API classes.
/// </remarks>
///
#define ATILFORMATCODECAPIMAJORVERSION "7"
#define ATILFORMATCODECAPIMINORVERSION "0"

#endif
