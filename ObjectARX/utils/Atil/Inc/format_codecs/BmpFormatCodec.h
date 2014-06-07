///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////

#ifndef  IMAGEFORMATCODEC_H
#include <ImageFormatCodec.h>
#endif

#ifndef FORMATCODECAPIVERSIONINTERFACE_H
namespace Atil { class FormatCodecApiVersionInterface; }
#endif

#ifndef BMPFORMATCODEC_H
#define BMPFORMATCODEC_H

extern "C"
{
    const Atil::FormatCodecApiVersionInterface* ATIL_EXPORT bmpApiVersion ();
}

class BmpFormatCodec : public Atil::ImageFormatCodec
{
//    enum FormatDecodabilityType { kStronglyTyped,
//                                  kMultiFileStronglyTyped,
//                                  kLooselyTyped
//                                };

public:
    BmpFormatCodec ();
    virtual ~BmpFormatCodec ();

    virtual void getLibVersionInfo (unsigned int& nLibMajor,
        unsigned int& nLibMinor, unsigned int& nBuild) const;
    virtual void getApiVersionInfo (unsigned int& nMajor, unsigned int& nMinor) const;

    virtual Atil::ImageFormatCodec::CodecCapability codecCapability () const;

    virtual bool isValidFileName (const Atil::FileSpecifier& fs) const;
    virtual Atil::ImageFormatCodec::FormatType getFormatDecodabilityType () const;

    virtual FormatOrganization getFormatOrganization () const;
    virtual FormatFrameType getFormatFrameType () const;

    virtual bool isFormatFeature ( FormatFeature feature ) const;
    virtual bool isSupportedProperty (
        Atil::FormatCodecPropertyInterface::PropertyIdentifier propId,
        Atil::StringBuffer* pCustomPropertyName = NULL) const;

    virtual int getNumExtensions () const;
    virtual void getExtensionText (int nExtensionIndex,
        Atil::StringBuffer& sbExtension) const;

    virtual void getFormatName (Atil::StringBuffer& sbFormatName) const;
    virtual void getDescriptionText (Atil::StringBuffer& sbDescription) const;
    virtual void getCopyrightText (Atil::StringBuffer& sbCopyright) const;

    virtual Atil::ImageFormatCodec::FormatDecodability isDecodableFile (
        const Atil::FileSpecifier& fileSpecifier, Atil::FindFileInterface * ff = NULL) const;

    virtual bool isEncodableImage (const Atil::DataModelAttributes& allAboutImageData,
        Atil::Size size ) const;

    virtual Atil::ReadImageFileInterface* openImage (
        const Atil::FileSpecifier* fsThisImage) const;

    virtual Atil::ReadImageFileInterface * openImage (
        const Atil::FileSpecifier* fsThisImage, Atil::FindFileInterface& ff) const;

    virtual Atil::WriteImageFileInterface* writeImage ( ) const;

    // Clone the open image file. It is used by FileReadDescriptor when cloning.
    // Not recommended for developers. FileReadDescriptor should be used instead.
    virtual Atil::ReadImageFileInterface* cloneOpenImage (
        const Atil::ReadImageFileInterface* pOpenImage ) const;
};

#endif

