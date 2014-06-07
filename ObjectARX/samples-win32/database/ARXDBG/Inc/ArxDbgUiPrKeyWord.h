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
//

#ifndef ARXDBGUIPRKEYWORD_H
#define ARXDBGUIPRKEYWORD_H

#include "ArxDbgUiPrBase.h"

/****************************************************************************
**
**  CLASS ArxDbgUiPrKeyWord:
**      A prompt with keywords only. Doesn't do much over what Prompt
**  does except provide a "go" function to issue the prompt.
**
**  **jma
**
*************************************/

class ArxDbgUiPrKeyWord : public ArxDbgUiPrBase {

public:
                    ArxDbgUiPrKeyWord(LPCTSTR msg, LPCTSTR keyWordList);
    virtual         ~ArxDbgUiPrKeyWord();

    virtual Status  go();                           // issue the prompt
    LPCTSTR         value();                        // for consistency

    void            setAllowNone(bool allowIt);

protected:
    bool			m_allowNone;

private:
        // outlawed functions
                        ArxDbgUiPrKeyWord(const ArxDbgUiPrKeyWord&);
    ArxDbgUiPrKeyWord&	operator=(const ArxDbgUiPrKeyWord&);
};


#endif  // ARXDBGUIPRKEYWORD_H
