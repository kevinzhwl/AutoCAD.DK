
' Copyright 2004 by Autodesk, Inc.

'Permission to use, copy, modify, and distribute this software in
'object code form for any purpose and without fee is hereby granted, 
'provided that the above copyright notice appears in all copies and 
'that both that copyright notice and the limited warranty and
'restricted rights notice below appear in all supporting 
'documentation.

'AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
'AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
'MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
'DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
'UNINTERRUPTED OR ERROR FREE.

'Use, duplication, or disclosure by the U.S. Government is subject to 
'restrictions set forth in FAR 52.227-19 (Commercial Computer
'Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
'(Rights in Technical Data and Computer Software), as applicable.

Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Geometry
Imports Autodesk.AutoCAD.ApplicationServices
Imports DBTransMan = Autodesk.AutoCAD.DatabaseServices.TransactionManager

'This application implements a command called MKENTS. It will create a line and 
'a circle, append them to an object ID array, change the circle's color to red,
'and then make a group of the line and circle using "ASDK_TEST_GROUP" as the 
'group's name. The MKENTS command also creates a new layer named "ASDK_MYLAYER".
'
'To use Ents.dll:
'
'1. Start AutoCAD and open a new drawing.
'2. Type netload and select Ents.dll.
'3. Execute the MKENTS command.
'
'Autodesk references added to this project are the acdbmgd.dll and acmgd.dll .NET components,
'and the AutoCAD Type Library COM component.

Namespace CreateEntities

    Public Class MakeEntities
        <CommandMethod("MKENTS")> _
        Public Sub runit()
            Call createNewLayer()
            Dim coll As New ObjectIdCollection()

            coll.Add(CreateCircle())
            coll.Add(CreateLine())
            Dim last As Integer
            last = coll.Count
            changeColor(coll.Item(last - 1), 1)
            createGroup(coll, "ASDK_TEST_GROUP")
        End Sub

        Public Sub createNewLayer()
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim LT As LayerTable = tm.GetObject(db.LayerTableId, OpenMode.ForWrite, False)
                Dim LTRec As New LayerTableRecord()
                LTRec.Name = "ASDK_MYLAYER"
                LT.Add(LTRec)
                tm.AddNewlyCreatedDBObject(LTRec, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
        End Sub

        Public Function CreateLine() As ObjectId
            Dim startpt As New Point3d(4.0, 2.0, 0.0)
            Dim endpt As New Point3d(10.0, 7.0, 0.0)
            Dim pLine As New Line(startpt, endpt)

            Dim lineid As ObjectId
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim bt As BlockTable = tm.GetObject(db.BlockTableId, OpenMode.ForRead, False)
                Dim btr As BlockTableRecord = tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False)
                lineid = btr.AppendEntity(pLine)
                tm.AddNewlyCreatedDBObject(pLine, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
            Return lineid
        End Function

        Public Function CreateCircle() As ObjectId
            Dim center As New Point3d(9.0, 3.0, 0.0)
            Dim normal As New Vector3d(0.0, 0.0, 1.0)
            Dim pcirc As New Circle(center, normal, 2.0)
            Dim Circid As ObjectId

            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction
            Try
                Dim bt As BlockTable = tm.GetObject(db.BlockTableId, OpenMode.ForRead, False)
                Dim btr As BlockTableRecord = tm.GetObject(bt(BlockTableRecord.ModelSpace), OpenMode.ForWrite, False)
                Circid = btr.AppendEntity(pcirc)
                tm.AddNewlyCreatedDBObject(pcirc, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
            Return Circid
        End Function

        Private Sub changeColor(ByVal entId As ObjectId, ByVal newColor As Long)
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim ent As Entity = tm.GetObject(entId, OpenMode.ForWrite, True)
                ent.ColorIndex = newColor
                ta.Commit()
            Catch
                Console.WriteLine("Error in setting the color for the entity")
            Finally
                ta.Dispose()
            End Try
        End Sub

        Private Sub createGroup(ByVal objIds As ObjectIdCollection, ByVal pGroupName As System.String)
            Dim db As Database = Application.DocumentManager.MdiActiveDocument.Database
            Dim tm As DBTransMan = db.TransactionManager
            'start a transaction
            Dim ta As Transaction = tm.StartTransaction()
            Try
                Dim gp As New Group(pGroupName, True)
                Dim dict As DBDictionary = tm.GetObject(db.GroupDictionaryId, OpenMode.ForWrite, True)
                dict.SetAt("ASDK_NEWNAME", gp)
                Dim thisId As ObjectId
                For Each thisId In objIds
                    gp.Append(thisId)
                Next
                tm.AddNewlyCreatedDBObject(gp, True)
                ta.Commit()
            Finally
                ta.Dispose()
            End Try
        End Sub
    End Class

End Namespace
