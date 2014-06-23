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
//
#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <adslib.h>
#include <acestext.h>

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Acad::ErrorStatus
createCircle(AcDbObjectId& circleId)
{
    circleId = AcDbObjectId::kNull;

    AcGePoint3d center(9.0, 3.0, 0.0);
    AcGeVector3d normal(0.0, 0.0, 1.0);
    AcDbCircle *pCirc = new AcDbCircle(center, normal, 2.0);

    if (pCirc == NULL)
        return Acad::eOutOfMemory;

    AcDbBlockTable *pBlockTable;
    Acad::ErrorStatus es = acdbCurDwg()->getBlockTable(
        pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk) {
        delete pCirc;
        return es;
    }

    AcDbBlockTableRecord *pBlockTableRecord;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE,
        pBlockTableRecord, AcDb::kForWrite);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pBlockTable->close();
        if (es2 != Acad::eOk) {
            acrx_abort("\nApp X failed to close Block"
                " Table. Error: %d",
                acadErrorStatusText(es2));
        }
        delete pCirc;
        return es;
    }

    es = pBlockTable->close();
    if (es != Acad::eOk) {
        acrx_abort("\nApp X failed to close Block Table."
            " Error: %d", acadErrorStatusText(es));
    }

    es = pBlockTableRecord->appendAcDbEntity(circleId,
        pCirc);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pBlockTableRecord->close();
        if (es2 != Acad::eOk) {
            acrx_abort("\nApp X failed to close"
                " Model Space Block Record. Error: %s",
                acadErrorStatusText(es2));
        }
        delete pCirc;
        return es;
    }

    es = pBlockTableRecord->close();
    if (es != Acad::eOk) {
        acrx_abort("\nApp X failed to close"
            " Model Space Block Record. Error: %d",
            acadErrorStatusText(es));
    }

    es = pCirc->close();
    if (es != Acad::eOk) {
        acrx_abort("\nApp X failed to"
            " close circle entity. Error: %d",
            acadErrorStatusText(es));
    }
    return es;
}

Acad::ErrorStatus
createNewLayer()
{
    AcDbLayerTableRecord *pLayerTableRecord
        = new AcDbLayerTableRecord;

    if (pLayerTableRecord == NULL)
        return Acad::eOutOfMemory;

    Acad::ErrorStatus es
        = pLayerTableRecord->setName("ASDK_MYLAYER");
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        return es;
    }

    AcDbLayerTable *pLayerTable;
    es= acdbCurDwg()->getLayerTable(pLayerTable,
        AcDb::kForWrite);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        return es;
    }

    // The linetype objectId default is 0 which is
    // not a valid Id.  So, it must be set to a
    // valid Id...for example the CONTINUOUS linetype.
    // Other data members have valid defaults so
    // they can be left alone.
    //
    AcDbLinetypeTable *pLinetypeTbl;
    es = acdbCurDwg()->getLinetypeTable(pLinetypeTbl,
        AcDb::kForRead);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        es = pLayerTable->close();
        if (es != Acad::eOk) {
            acrx_abort("\nApp X failed to close Layer"
                " Table. Error: %d",
                acadErrorStatusText(es));
        }
        return es;
    }

    AcDbObjectId ltypeObjId;
    es = pLinetypeTbl->getAt("CONTINUOUS", ltypeObjId);
    if (es != Acad::eOk) {
        delete pLayerTableRecord;
        es = pLayerTable->close();
        if (es != Acad::eOk) {
            acrx_abort("\nApp X failed to close Layer"
                " Table. Error: %d",
                acadErrorStatusText(es));
        }
        return es;
    }

    pLayerTableRecord->setLinetypeObjectId(ltypeObjId);

    es = pLayerTable->add(pLayerTableRecord);
    if (es != Acad::eOk) {
        Acad::ErrorStatus es2 = pLayerTable->close();
        if (es2 != Acad::eOk) {
            acrx_abort("\nApp X failed to close Layer"
                " Table. Error: %d",
                acadErrorStatusText(es2));
        }
        delete pLayerTableRecord;
        return es;
    }

    es = pLayerTable->close();
    if (es != Acad::eOk) {
        acrx_abort("\nApp X failed to close Layer"
            " Table. Error: %d",
            acadErrorStatusText(es));
    }

    es = pLayerTableRecord->close();
    if (es != Acad::eOk) {
        acrx_abort("\nApp X failed to close Layer"
            " Table Record. Error: %d",
            acadErrorStatusText(es));
    }
    return es;
}

// END CODE APPEARING IN SDK DOCUMENT.


void doit()
{
    AcDbObjectId circleId;
    Acad::ErrorStatus es = createCircle(circleId);
    if (es != Acad::eOk) {
        ads_printf("\nError creating circle: %s",
            acadErrorStatusText(es));
    }

    es = createNewLayer();
    if (es != Acad::eOk) {
        ads_printf("\nError creating layer: %s",
            acadErrorStatusText(es));
    }
}


void initApp()
{
    acedRegCmds->addCommand("ASDK_ERROR_TEST",
                            "ASDK_ERRTST",
                            "ERRTST",
                            ACRX_CMD_MODAL,
                            doit);
}

void unloadApp()
{
    acedRegCmds->removeGroup("ASDK_ERROR_TEST");
}

extern "C"
AcRx::AppRetCode acrxEntryPoint(
    AcRx::AppMsgCode msg,
    void* pkt)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
