SelectionSet - .NET API Sample

 (C) Copyright 2004 by Autodesk, Inc.

This sample demonstrates the basics of using the Selectionset .NET API with AutoCAD.  It has the following commnads:

SSet - this command allows the user to do simple selection of entities and ignores 
       all entities other than circles that are red in color.

Single - This command allows only a single entity to be picked

Implied - This command demonstrates Implied pick

CWindow  - This command demonstrates the Cwindow Selection

CPolygon - This command demonstrates CPolygon selection

OptionSel - This command has a number of keywords attached to the selection.
             Based on the keyword that user enters, it does either 
             fence,window,windowpolygon,lastentitySelection,PreviousSelection.

SSetReactors - This command demonstrates some selection Related input context 
               reactors. It exercises promptingForSelection, PromptedForSelection 
               and SelectionAdded events of the editor.


useSelection - This command helps to use the previous selection options and 
               selection Results that we had during the execution of SSetReactors 
               command. It demonstrates how to use PromptingForSelection and 
               PromptedForSelection events.

To run the sample:  Build the application adding acdbmgd.dll and acmgd.dll as references, and use NETLOAD command to load selectionset.dll from the \bin subfolder.

