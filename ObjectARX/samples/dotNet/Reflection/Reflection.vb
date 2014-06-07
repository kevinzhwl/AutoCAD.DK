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


Option Explicit On 

Imports System
Imports System.Type
Imports System.CLSCompliantAttribute
Imports System.Reflection
Imports System.Runtime.InteropServices
Imports System.Xml

Imports Autodesk.AutoCAD.Runtime
Imports Autodesk.AutoCAD.DatabaseServices
Imports Autodesk.AutoCAD.ApplicationServices
Imports Autodesk.AutoCAD.EditorInput


<Assembly: ExtensionApplication(GetType(Reflection.ReflectionApp))> 
<Assembly: CommandClass(GetType(ReflectionCommand))> 
'<Assembly: AssemblyKeyFile("..\..\mykey.snk")> 

Namespace Reflection
    '<summary>
    'Summary description for "Reflection" sample.
    'To run this sample project create the references to acdbmgd, acmgd, System, System.Data, System.Drawing and System.XML
    'The steps to run this application :
    '1. Draw an entity (circle, ploygon etc.) 
    '2. Call "NetLoad" from the command prompt
    '3. Load Filer "Reflection.dll"
    '4. Call "reflection" from the command prompt
    '5. Select the entity
    '6. Enter a filename
    'Result : the application will dump the information at the filename entered in .XML.
    ' The .XML will be save under /bin folder
    '</summary>
    Public Class ReflectionApp
        Implements Autodesk.AutoCAD.Runtime.IExtensionApplication

        Public Sub Initialize() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Initialize
        End Sub

        Public Sub Terminate() Implements Autodesk.AutoCAD.Runtime.IExtensionApplication.Terminate
        End Sub
    End Class

    Public Class ReflectionCommand
        Dim ed As Editor = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor

        <Autodesk.AutoCAD.Runtime.CommandMethod("Reflection")> _
        Public Function exportObjectInfo()

            Dim objID As ObjectId = SelectMyEntity()
            Dim exportFilename As String

            If (objID.IsNull) Then
                ed.WriteMessage("*cancelled*" + Chr(10))
                Exit Function
            End If

            exportFilename = SelectMyExportFilename()
            If exportFilename = Nothing Then
                ed.WriteMessage("*cancelled*" + Chr(10))
                Exit Function
            End If

            Dim myTrans As Transaction = HostApplicationServices.WorkingDatabase.TransactionManager.StartTransaction()
            'Dim ent As Entity = CType(myTrans.GetObject(entRes.ObjectId, OpenMode.ForRead), Entity)
            Dim obj As Object = CType(myTrans.GetObject(objID, OpenMode.ForRead), Object)

            Dim outXml As AcReflection = New AcReflection(exportFilename)
            outXml.ProcessEntity(obj)
            myTrans.Commit()
        End Function

        Function SelectMyEntity()
            Dim opt As New PromptEntityOptions("Please select an Entity to export")
            Dim entRes As PromptEntityResult

            Do
                entRes = ed.GetEntity(opt)
                opt.Message = Chr(10) & "an Entity please"
            Loop Until ((entRes.Status = PromptStatus.Error) Or _
                        (entRes.Status = PromptStatus.None) Or _
                        (entRes.Status = PromptStatus.Cancel) Or _
                         (entRes.Status = PromptStatus.OK))
            If (entRes.Status <> PromptStatus.OK) Then
                ' Cancelled
                Return Nothing
            End If
            Return entRes.ObjectId
        End Function

        Function SelectMyExportFilename()
            Dim filename As String
            Dim stringOpt As New PromptStringOptions(Chr(10) + "Please specify the filename you wish to export to")
            Dim promptRes As PromptResult
            Do
                promptRes = ed.GetString(stringOpt)
                stringOpt.Message = Chr(10) + "filename please"
            Loop Until ((promptRes.Status = PromptStatus.Error) Or _
                        (promptRes.Status = PromptStatus.None) Or _
                        (promptRes.Status = PromptStatus.Cancel) Or _
                         (promptRes.Status = PromptStatus.OK))


            If (promptRes.Status <> PromptStatus.OK) Or (promptRes.StringResult.Length() = 0) Then
                ' Cancelled
                Return Nothing
            End If

            filename = promptRes.StringResult.Trim()
            If Right(filename, 4).ToUpper() <> ".XML" Then
                filename = filename + ".xml"
            End If
            Return filename

        End Function
    End Class

End Namespace
