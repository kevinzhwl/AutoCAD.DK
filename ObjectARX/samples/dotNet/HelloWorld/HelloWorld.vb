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

' Hello World VB.NET sample
' by Cyrille Fauvel - Autodesk Developer Technical Services
' Copyright Autodesk (c) 2003

Option Explicit On 

Imports System
Imports System.Type
Imports System.CLSCompliantAttribute
Imports System.Reflection
Imports System.Runtime.InteropServices

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.Interop
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.EditorInput

<Assembly: ExtensionApplication(GetType(HelloWorld.HelloWorldApp))> 
<Assembly: CommandClass(GetType(HelloWorldCommands))> 

Namespace HelloWorld

    Public Class HelloWorldApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
            ' Create an AutoCAD toolbar with 4 buttons linked to the 4 commands defined below

            Dim helloModule As System.Reflection.Module = System.Reflection.Assembly.GetExecutingAssembly().GetModules()(0)
            Dim helloModulePath As String = helloModule.FullyQualifiedName
            Try
                helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
                helloModulePath = helloModulePath.Substring(0, helloModulePath.LastIndexOf("\"))
            Catch
                MsgBox("Error with Module Path")
                Exit Sub
            End Try

            Dim acadApp As Autodesk.AutoCAD.Interop.AcadApplication = Autodesk.AutoCAD.ApplicationServices.Application.AcadApplication
            Dim hwTb As Autodesk.AutoCAD.Interop.AcadToolbar = acadApp.MenuGroups.Item(0).Toolbars.Add("Hello World!")
            Dim tbBut0 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(0, "Hello", "Hello World - Hello command", "_HELLO ")
            tbBut0.SetBitmaps(helloModulePath + "\tbBut0.bmp", helloModulePath + "\tbBut0.bmp")
            Dim tbBut1 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(1, "HelloForm", "Hello World - HelloForm command", "_HelloForm ")
            tbBut1.SetBitmaps(helloModulePath + "\tbBut1.bmp", helloModulePath + "\tbBut1.bmp")
            Dim tbBut2 As Autodesk.AutoCAD.Interop.AcadToolbarItem = hwTb.AddToolbarButton(2, "HelloText", "Hello World - Hello command", "_HELLOTEXT ")
            tbBut2.SetBitmaps(helloModulePath + "\tbBut0.bmp", helloModulePath + "\tbBut0.bmp")
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub

    End Class

    Public Class HelloWorldCommands

        ' Defines a command which prompt a message on the AutoCAD command line
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLO")> _
        Public Function HelloCommand()
            Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage(vbNewLine + "Hello World!" + vbNewLine)
        End Function

        ' Defines a command which displays a Windows form
        <Autodesk.AutoCAD.Runtime.CommandMethod("HELLOFORM")> _
        Public Function HelloFormCommand()
            Dim dlg As New HellowWorldForm()
            dlg.ShowDialog()
        End Function

        ' Defines a command which adds a 'Hello World' MText object to Model Space
        <Autodesk.AutoCAD.Runtime.CommandMethod("ASDK", "HELLOTEXT", Autodesk.AutoCAD.Runtime.CommandFlags.Modal)> _
        Public Function HelloTextCommand()
            '   ObjectARX generally reports errors through return values.
            '   .NET uses exceptions (Note - VB.NET has far superior error handling to VB6)
            Dim text As MText
            Dim bt As BlockTable
            Dim btr As BlockTableRecord
            Dim db As Database = HostApplicationServices.WorkingDatabase
            Dim trans As Transaction
            trans = db.TransactionManager.StartTransaction()
            Try
                bt = trans.GetObject(db.BlockTableId, OpenMode.ForRead)
                btr = trans.GetObject(bt(btr.ModelSpace), OpenMode.ForWrite)
                '   Create new mtext and set text
                Try
                    text = New MText()
                    text.Contents = "Hello World!!"
                    '   Append entity to model space
                    btr.AppendEntity(text)
                    trans.AddNewlyCreatedDBObject(text, True)
                Finally
                    'ensure that the mtext is diposed even if we throw
                    'if we don't throw this does nothing
                    text.Dispose()
                End Try
                trans.Commit()
            Finally '   Finally code is invoked whether there's an error or not
                trans.Dispose()
            End Try
        End Function

    End Class

End Namespace