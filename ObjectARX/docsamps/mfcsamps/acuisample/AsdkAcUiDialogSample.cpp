// (C) Copyright 1999 by Autodesk, Inc. 
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

// AsdkAcUiDialogSample.cpp : implementation file
//

#include "stdafx.h"
#include "AsdkAcUiSample.h"
#include "AsdkAcUiDialogSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AsdkAcUiDialogSample dialog


AsdkAcUiDialogSample::AsdkAcUiDialogSample(CWnd* pParent /*=NULL*/)
    : CAcUiDialog(AsdkAcUiDialogSample::IDD, pParent)
{
    //{{AFX_DATA_INIT(AsdkAcUiDialogSample)
    //}}AFX_DATA_INIT

}


void AsdkAcUiDialogSample::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(AsdkAcUiDialogSample)
    DDX_Control(pDX, IDC_COMBO_REGAPPS, m_ctrlRegAppComboBox);
    DDX_Control(pDX, IDC_LIST_BLOCKS, m_ctrlBlockListBox);
    DDX_Control(pDX, IDC_BUTTON_POINT, m_ctrlPickButton);
    DDX_Control(pDX, IDC_BUTTON_ANGLE, m_ctrlAngleButton);
    DDX_Control(pDX, IDC_EDIT_ANGLE, m_ctrlAngleEdit);
    DDX_Control(pDX, IDC_EDIT_XPT, m_ctrlXPtEdit);
    DDX_Control(pDX, IDC_EDIT_YPT, m_ctrlYPtEdit);
    DDX_Control(pDX, IDC_EDIT_ZPT, m_ctrlZPtEdit);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AsdkAcUiDialogSample, CAcUiDialog)
    //{{AFX_MSG_MAP(AsdkAcUiDialogSample)
    ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
    ON_BN_CLICKED(IDC_BUTTON_ANGLE, OnButtonAngle)
    ON_CBN_KILLFOCUS(IDC_COMBO_REGAPPS, OnKillfocusComboRegapps)
    ON_EN_KILLFOCUS(IDC_EDIT_ANGLE, OnKillfocusEditAngle)
    ON_EN_KILLFOCUS(IDC_EDIT_XPT, OnKillfocusEditXpt)
    ON_EN_KILLFOCUS(IDC_EDIT_YPT, OnKillfocusEditYpt)
    ON_EN_KILLFOCUS(IDC_EDIT_ZPT, OnKillfocusEditZpt)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Utility functions
void AsdkAcUiDialogSample::DisplayPoint() 
{
    m_ctrlXPtEdit.SetWindowText(m_strXPt);
    m_ctrlXPtEdit.Convert();

    m_ctrlYPtEdit.SetWindowText(m_strYPt);
    m_ctrlYPtEdit.Convert();

    m_ctrlZPtEdit.SetWindowText(m_strZPt);
    m_ctrlZPtEdit.Convert();
}

bool AsdkAcUiDialogSample::ValidatePoint() 
{
    if (!m_ctrlXPtEdit.Validate())
        return false;

    if (!m_ctrlYPtEdit.Validate())
        return false;

    if (!m_ctrlZPtEdit.Validate())
        return false;

    return true;
}

void AsdkAcUiDialogSample::DisplayAngle() 
{
    m_ctrlAngleEdit.SetWindowText(m_strAngle);
    m_ctrlAngleEdit.Convert();
}

bool AsdkAcUiDialogSample::ValidateAngle() 
{
    if (!m_ctrlAngleEdit.Validate())
        return false;
    
    return true;

}

void AsdkAcUiDialogSample::DisplayBlocks() 
{

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    // Iterate through the block table and disaply the names in the list box.
    const char *pName;
    AcDbBlockTableIterator *pBTItr;
    if (pBlockTable->newIterator(pBTItr) == Acad::eOk) {
        while (!pBTItr->done()) {
            AcDbBlockTableRecord *pRecord;
            if (pBTItr->getRecord(pRecord, AcDb::kForRead) == Acad::eOk) {
                pRecord->getName(pName);
                m_ctrlBlockListBox.InsertString(-1, pName);
                pRecord->close();
            }   
            pBTItr->step();
        }
    }
    pBlockTable->close();

}

void AsdkAcUiDialogSample::DisplayRegApps() 
{

    AcDbRegAppTable *pRegAppTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pRegAppTable, AcDb::kForRead);

    // Iterate through the reg app table and disaply the names in the list box.
    const char *pName;
    AcDbRegAppTableIterator *pItr;
    if (pRegAppTable->newIterator(pItr) == Acad::eOk) {
        while (!pItr->done()) {
            AcDbRegAppTableRecord *pRecord;
            if (pItr->getRecord(pRecord, AcDb::kForRead) == Acad::eOk) {
                pRecord->getName(pName);
                m_ctrlRegAppComboBox.InsertString(-1, pName);
                pRecord->close();
            }   
            pItr->step();
        }
    }
    pRegAppTable->close();

}

/////////////////////////////////////////////////////////////////////////////
// AsdkAcUiDialogSample message handlers

void AsdkAcUiDialogSample::OnButtonPoint() 
{
    // Hide the dialog and give control to the editor
    BeginEditorCommand();

    ads_point pt;

    // Get a point
    if (acedGetPoint(NULL, "\nPick a point: ", pt) == RTNORM) {
        // If the point is good, continue
        CompleteEditorCommand();
        m_strXPt.Format("%g", pt[X]);
        m_strYPt.Format("%g", pt[Y]);
        m_strZPt.Format("%g", pt[Z]);
        DisplayPoint();
    } else {
        // otherwise cancel the command (including the dialog)
        CancelEditorCommand();
    }

}

void AsdkAcUiDialogSample::OnButtonAngle() 
{
    // Hide the dialog and give control to the editor
    BeginEditorCommand();

    // Setup the default point for picking an angle
    // based on the m_strXPt, m_strYPt and m_strZPt values
    ads_point pt; 
    acdbDisToF(m_strXPt, -1, &pt[X]);
    acdbDisToF(m_strYPt, -1, &pt[Y]);
    acdbDisToF(m_strZPt, -1, &pt[Z]);
    
    double angle;

    // Get a point from the user
    if (acedGetAngle(pt, "\nPick an angle: ", &angle) == RTNORM) {
        // If we got an angle, go back to the dialog
        CompleteEditorCommand();
        // Convert the acquired radian value to degrees since the 
        // AcUi control can convert that to the other formats.
        m_strAngle.Format("%g", angle*(180.0/PI));
        DisplayAngle();
    } else {
        // otherwise cancel the command (including the dialog)
        CancelEditorCommand();
    }

}


void AsdkAcUiDialogSample::OnKillfocusEditAngle() 
{

    // Get and update text the user typed in.
    m_ctrlAngleEdit.Convert();
    m_ctrlAngleEdit.GetWindowText(m_strAngle);
    
}

void AsdkAcUiDialogSample::OnKillfocusEditXpt() 
{
    // Get and update text the user typed in.
    m_ctrlXPtEdit.Convert();
    m_ctrlXPtEdit.GetWindowText(m_strXPt);
}

void AsdkAcUiDialogSample::OnKillfocusEditYpt() 
{
    // Get and update text the user typed in.
    m_ctrlYPtEdit.Convert();
    m_ctrlYPtEdit.GetWindowText(m_strYPt);
}

void AsdkAcUiDialogSample::OnKillfocusEditZpt() 
{
    // Get and update text the user typed in.
    m_ctrlZPtEdit.Convert();
    m_ctrlZPtEdit.GetWindowText(m_strZPt);
}


void AsdkAcUiDialogSample::OnKillfocusComboRegapps() 
{
    CString strFromEdit;
    m_ctrlRegAppComboBox.GetWindowText(strFromEdit);
    if (m_ctrlRegAppComboBox.FindString(-1, strFromEdit) == CB_ERR) {
        if (acdbRegApp(strFromEdit) == RTNORM)
            m_ctrlRegAppComboBox.AddString(strFromEdit);
    }
}


void AsdkAcUiDialogSample::OnOK() 
{
    if (!ValidatePoint()) {
        AfxMessageBox("Sorry, Point out of desired range. Try again or Cancel");
        m_ctrlXPtEdit.SetFocus();
        return;
    } 
    
    if (!ValidateAngle()) {
        AfxMessageBox("Sorry, Angle out of desired range. Try again or Cancel");
        m_ctrlAngleEdit.SetFocus();
        return;
    }

    CAcUiDialog::OnOK();

    // Store the data into the registry
    SetDialogData("ANGLE", m_strAngle);
    SetDialogData("POINTX", m_strXPt);
    SetDialogData("POINTY", m_strYPt);
    SetDialogData("POINTZ", m_strZPt);

}


BOOL AsdkAcUiDialogSample::OnInitDialog() 
{
    // Set the dialog name for registry lookup and storage
    SetDialogName("AsdkAcUiSample:AsdkAcUiDialog");

    CAcUiDialog::OnInitDialog();
    
    DLGCTLINFO  dlgSizeInfo[]= {
        { IDC_STATIC_GROUP1, ELASTICX, 20 },
        { IDC_STATIC_GROUP1, ELASTICY, 100 },
        { IDC_EDIT_XPT, ELASTICX, 20 },
        { IDC_EDIT_YPT, ELASTICX, 20 },
        { IDC_EDIT_ZPT, ELASTICX, 20 },
        { IDC_EDIT_ANGLE, ELASTICX, 20 },

        { IDC_STATIC_GROUP2, MOVEX, 20 },
        { IDC_STATIC_GROUP2, ELASTICY, 100 },
        { IDC_STATIC_GROUP2, ELASTICX, 80 },
        { IDC_LIST_BLOCKS, MOVEX, 20 },
        { IDC_LIST_BLOCKS, ELASTICY, 100 },
        { IDC_STATIC_TEXT2, MOVEX, 20 },
        { IDC_STATIC_TEXT2, MOVEY, 100 },
        { IDC_LIST_BLOCKS, ELASTICX, 80 },
        { IDC_STATIC_TEXT2, ELASTICX, 80 },
                
        { IDC_STATIC_GROUP3, MOVEY, 100 },
        { IDC_STATIC_GROUP3, ELASTICX, 20 },
        { IDC_COMBO_REGAPPS, MOVEY, 100 },
        { IDC_COMBO_REGAPPS, ELASTICX, 20 },
        { IDC_STATIC_TEXT3, MOVEY, 100 },
        { IDC_STATIC_TEXT3, ELASTICX, 20 },

        { IDOK, MOVEX, 100 },
        { IDCANCEL, MOVEX, 100 },
    };

    const DWORD numberofentries = sizeof dlgSizeInfo / sizeof DLGCTLINFO;

    SetControlProperty(dlgSizeInfo, numberofentries);

    // Must be within a 100 unit cube centered about 0,0,0
    m_ctrlXPtEdit.SetRange(-50.0, 50.0);
    m_ctrlYPtEdit.SetRange(-50.0, 50.0);
    m_ctrlZPtEdit.SetRange(-50.0, 50.0);

    // Must be between 0 and 90 degrees
    m_ctrlAngleEdit.SetRange(0.0, 90.0 /*(PI/2.0)*/);

    // Assign a title for the dialog
    SetWindowText("AcUiDialog Sample");

    // Load the default bitmaps
    m_ctrlPickButton.AutoLoad();
    m_ctrlAngleButton.AutoLoad();

    // Get and Display the preserved data from the registry
    if (!GetDialogData("ANGLE", m_strAngle))
        m_strAngle = "0.0";
    if (!GetDialogData("POINTX", m_strXPt))
        m_strXPt = "0.0";
    if (!GetDialogData("POINTY", m_strYPt))
        m_strYPt = "0.0";
    if (!GetDialogData("POINTZ", m_strZPt))
        m_strZPt = "0.0";

    DisplayPoint();
    DisplayAngle();
    DisplayBlocks();
    DisplayRegApps();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

