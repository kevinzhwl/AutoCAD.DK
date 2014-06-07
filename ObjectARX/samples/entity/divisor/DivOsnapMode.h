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
#include <string.h>

#include "DivGlyph.h"

// Note: All template class functions have been inlined in the .h, due to the bug
// described in the MS Knowledge Base Article Q128789:
// BUG: LNK2001 on Member Function When Use Nested Class Template
 
template <int i> class AsdkDivOsnapMode : public AcDbCustomOsnapMode
{
public:
    AsdkDivOsnapMode( const char *szLoc, const char *szGlob, const char *szTooltip, const char *szGlyph ){
        m_szLocal = strdup( szLoc );
        m_szGlobal = strdup( szGlob );
        m_szTooltip = strdup( szTooltip );
        m_pGlyph = new AsdkDivGlyph<i>( szGlyph );
    }
    virtual ~AsdkDivOsnapMode(){
        delete m_szLocal; m_szLocal = NULL;
        delete m_szGlobal; m_szGlobal = NULL;
        delete m_szTooltip; m_szTooltip = NULL;
        delete m_pGlyph; m_pGlyph = NULL;
    }
    virtual const char* localModeString() const { return m_szLocal; }
    virtual const char* globalModeString() const { return m_szGlobal; }
    virtual const AcRxClass* entityOsnapClass() const { return AsdkDivOsnapInfo<i>::desc(); }
    virtual AcGiGlyph* glyph() const { return m_pGlyph; }
    virtual const char* tooltipString() const { return m_szTooltip; }

private:
    AsdkDivGlyph<i> *m_pGlyph;
    char *m_szLocal;
    char *m_szGlobal;
    char *m_szTooltip;
};
