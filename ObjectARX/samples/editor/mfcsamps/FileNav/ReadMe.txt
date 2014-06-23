Description:
 (C) Copyright 2002-2006 by Autodesk, Inc.
Example showing how to use the File Navigation Dialog API.

1. Start AutoCAD
2. Load asdkFileNav.arx
3. Command FILENAV
4. Use the dialog to navigate to a desired location or file.
5. When file selection is made with the "Open" button, the selection is echoed 
   to the commandline.


NOTE: On Windows XP based systems, the FILENAV dialog will also display zip files as folders. 
If one does not want the ZIP files to be listed in the FILENAV dialog, you will need to 
unregister "zipfldr.dll" using the command: regsvr32 /u %windir%\system32\zipfldr.dll. After 
doing this you will need to restart AutoCAD for the changes to take affect. If one 
wants the "Zip file as folder" functionality back, just run the 
"regsvr32 %windir%\system32\zipfldr.dll" command.
