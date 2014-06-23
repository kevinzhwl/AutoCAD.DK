ObjectARX Utils - DatFiles

1) ObjectARX Syntax Highlighting in Microsoft Developer Studio.

If you wish to have syntax highlighting support for the ARX defines and symbols: 

a) Copy the usertype.dat file to your msdev\bin directory. If you already have 
a usertype.dat file you may append the contents of both files. 

b) The next time you start msdev the terms listed in the file will be shown in
the user defined keyword color.

c) The files mfc42.dat  and adsfunc.dat provides most of the identifiers for 
MFC Version 4.2 and ADS respectively. They can both be used in a similar way.

2) ObjectARX Debugging help in Microsoft Developer Studio.

While debugging you can see automatic expansions of some classes in the variables
window. To add your own classes you should edit the autoexp.dat file in the
msedv\bin directory. Some of the definitions for the ObjectARX classes have
been included in the file ARXDebug.dat

a) Open the file ARXdebug.dat and copy the contents to the clipboard.

b) Open the file autoexp.dat in the msdev\bin directory of your Microsoft
Developer Studio installation.

c) Paste the clipboard contents just above the '[Unicode]' line near the end
of the file


