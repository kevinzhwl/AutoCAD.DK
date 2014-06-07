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
Imports System.IO
Imports System.Reflection
Imports System.Xml
Imports Microsoft.Win32
Imports Autodesk.AutoCAD.Geometry

Namespace Reflection



    Public Class AcReflection
        Dim acDBLineProps() As String = {"StartPoint", "EndPoint", "Normal", _
                                "Thickness", "Color", "ColorIndex", _
                                "Layer", "LayerId", _
                                "Linetype", "LinetypeId", _
                                "LinetypeScale", "LineWeight", _
                                "Hyperlinks", "PlotStyleName", "PlotStyleNameId", _
                                "Degree"}
        Dim acDBArcProps() As String = {"Center", "Normal", "StartAngle", "EndAngle", "Radius", _
                                "Thickness", "Color", "ColorIndex", _
                                "Layer", "LayerId", _
                                "Linetype", "LinetypeId", _
                                "LinetypeScale", "LineWeight", _
                                "Hyperlinks", "PlotStyleName", "PlotStyleNameId"}
        Dim acDBCircleProps() As String = {"Center", "Normal", "Area", "Radius", _
                                        "Thickness", "Color", "ColorIndex", _
                                        "Layer", "LayerId", _
                                        "Linetype", "LinetypeId", _
                                        "LinetypeScale", "LineWeight", _
                                        "Hyperlinks", "PlotStyleName", "PlotStyleNameId"}
        Dim acDBPolyLineProps() As String = {"Vertex", "Length", "Area", "Elevation", _
                                                "Closed", "PLinegen", "NumberOfVertices", _
                                                "HasBulges", "HasWidth", "ConstantWidth", _
                                                "IsOnlyLines", "Normal", _
                                                "Thickness", "Color", "ColorIndex", _
                                                "Layer", "LayerId", _
                                                "Linetype", "LinetypeId", _
                                                "LinetypeScale", "LineWeight", _
                                                "Hyperlinks", "PlotStyleName", "PlotStyleNameId"}
        Dim test As LinearEntity3d

        Dim xmlFilename As String
        Dim xmlWriter As XmlTextWriter

        Sub New(ByVal fileName As String)
            ' Output XML file 
            xmlFilename = fileName
        End Sub


        Sub ProcessEntity(ByVal obj As Object)
            ' Set up the XML output
            xmlWriter = New XmlTextWriter(xmlFilename, System.Text.Encoding.Unicode)

            ' Write header 
            With xmlWriter
                .Formatting = Formatting.Indented
                .WriteStartDocument()
                .WriteComment("Produced by reflection on " + System.DateTime.Now)
                .WriteStartElement("AcReflection")
            End With

            Dim aType As Type = obj.GetType()
            ' Time to see if we can process this entity type
            Select Case aType.FullName
                Case "Autodesk.AutoCAD.DatabaseServices.Line"
                    ProcessClass(obj, acDBLineProps)
                Case "Autodesk.AutoCAD.DatabaseServices.Circle"
                    ProcessClass(obj, acDBCircleProps)
                Case "Autodesk.AutoCAD.DatabaseServices.Arc"
                    ProcessClass(obj, acDBArcProps)
                Case "Autodesk.AutoCAD.DatabaseServices.Polyline"
                    ProcessClass(obj, acDBPolyLineProps)
            End Select

            ' Finally Close the XML File
            xmlWriter.WriteEndElement() ' for Reflection
            xmlWriter.WriteEndDocument()
            xmlWriter.Close()

        End Sub

        Sub ProcessClass(ByVal obj As Object, ByRef interestedProps() As String)
            Dim aType As Type = obj.GetType()
            xmlWriter.WriteStartElement("entity")
            xmlWriter.WriteAttributeString("ID", aType.FullName)

            Dim aBindings As Integer = (BindingFlags.Instance Or BindingFlags.Public Or BindingFlags.Static)
            Dim aProp As PropertyInfo

            ' Process for each property in the class
            For Each aProp In aType.GetProperties(aBindings)
                Dim propertyName As String = aProp.Name.ToString
                If Array.IndexOf(interestedProps, propertyName) > -1 Then
                    'found
                    xmlWriter.WriteStartElement(propertyName)
                    xmlWriter.WriteAttributeString("Type", aProp.PropertyType().ToString())
                    If (InStr(aProp.PropertyType().ToString(), "Autodesk.AutoCAD") > 0) Then
                        ProcessClass(aProp.GetValue(obj, Nothing))
                    Else
                        xmlWriter.WriteAttributeString("Value", CType(aProp.GetValue(obj, Nothing), String))
                    End If
                    xmlWriter.WriteEndElement()
                End If
            Next
            xmlWriter.WriteEndElement()
        End Sub

        Sub ProcessClass(ByVal obj As Object)
            Dim aType As Type = obj.GetType()

            xmlWriter.WriteStartElement("entity")
            xmlWriter.WriteAttributeString("ID", aType.FullName)

            Dim aBindings As Integer = (BindingFlags.DeclaredOnly Or BindingFlags.Instance Or BindingFlags.Public Or BindingFlags.Static)
            Dim aProp As PropertyInfo

            For Each aProp In aType.GetProperties(aBindings)
                Dim propertyName As String = aProp.Name.ToString
                xmlWriter.WriteStartElement(propertyName)
                xmlWriter.WriteAttributeString("Type", aProp.PropertyType().ToString())
                If (InStr(propertyName, "Autodesk.AutoCAD") > 0) Then
                    ' Do nothing .. do not want to go any deeper
                Else
                    ' Index properties are ignored // todo when time avails
                    Try
                        If aProp.GetIndexParameters().Length > 0 Then
                            Dim i As Int16

                            Dim tempObj(aProp.GetIndexParameters().Length) As Object
                            Dim dummyObj As Object = aProp.GetValue(obj, tempObj)
                            xmlWriter.WriteAttributeString("Index", i.ToString())
                            'xmlWriter.WriteAttributeString("Value", CType(aProp.GetValue(obj, tempObj), String))

                        Else
                            xmlWriter.WriteAttributeString("Value", CType(aProp.GetValue(obj, Nothing), String))
                        End If
                    Catch ex As Exception
                        Debug.WriteLine(ex.Message + "::::" + propertyName + " - " + aProp.GetIndexParameters().Length.ToString())
                    End Try
                End If
                xmlWriter.WriteEndElement()
            Next
            xmlWriter.WriteEndElement()
        End Sub
    End Class

End Namespace ' Autodesk.Samples
