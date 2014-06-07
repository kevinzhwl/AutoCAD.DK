// (C) Copyright 1990-2002 by Autodesk, Inc. 
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

#include "StdAfx.h"
#include "acuiDialog.h"
#include "acuiNavDialog.h"
#include "FileNavDlg.h"
#include "resource.h"

CNavDataArray gDataArray;
CNavFilterArray gFilterArray;

extern HINSTANCE _hdllInstance ;

void FileNavCommand()
{
    LPCTSTR filterALL[] = {
        "*.*", NULL
    };
    LPCTSTR filterCPP[] = {
        "*.zip", "*.c", "*.cpp", "*.h", NULL
    };
    LPCTSTR filterDOC[] = {
        "*.doc", "*.txt", NULL
    };
    LPCTSTR filterDWG[] = {
        "*.dwg", "*.dxb", "*.dxf", NULL
    };
    LPCTSTR filterIMG[] = {
        "*.gif", "*.jpg", "*.tif", "*.tiff", NULL
    };
    LPCTSTR filterDescription[] = {
        "All files", "C++ files", "Documents", "Drawings", "Images", NULL
    };
    LPCTSTR *filterSpec[] = {
        filterALL, filterCPP, filterDOC, filterDWG, filterIMG, NULL
    };

    CNavFilter *f;
    int  i = 0, j;

	gFilterArray.RemoveAllData();

    while (filterSpec[i] != NULL) {
        // Append a new filter.
        f = gFilterArray.AddData();

        if (f != NULL) {
            // Set the filter's description.
            f->SetDescription(filterDescription[i]);

            // Assign the filter strings.
            j = 0;
            while (filterSpec[i][j] != NULL) {
                f->Add(filterSpec[i][j]);
                j++;
            }
        }

        // Prepare to add the next filter.
        i++;
    }
	while (true)
	{
		HWND acadHandle = adsw_acadMainWnd();
		::EnableWindow (acadHandle, true);
		::SetFocus (acadHandle);
		CWnd *pWnd = CWnd::FromHandle(acadHandle);

		CFileNavDlg dlg(gDataArray, gFilterArray, 0, pWnd);
		dlg.SetMultiSelectAllowed(TRUE);
		dlg.SetDialogCaption("Browse down to a file");
		
		
		if (dlg.DoModal() == IDOK) 
		{
			for(int i = 0; i < gDataArray.GetCount(); i++)
			{
				LPITEMIDLIST id = gDataArray[i]->GetID();
				//able to get the text string entered/selected by user in File Name Combo
				//along with its full parth
				CString sText = gDataArray[i]->GetText();
				if (sText.GetLength() != 0)
				{
					acutPrintf ("The file name is:\n%s\n",sText.GetBuffer(sText.GetLength()));
				}
			}
		
		}
		break;
	}
}
