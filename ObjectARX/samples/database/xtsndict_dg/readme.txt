(C) Copyright 1998 by Autodesk, Inc.

Description:

This program demonstrates using extension dictionaries. Two commands are defined in this program:  CREATE and LISTXREC.
 
The CREATE command calls the function createXrecord(), which instantiates an xrecord object and adds it to the extension dictionary of a user-selected object.

The LISTXREC command calls the listXrecord() function, which opens the extension dictionary of a user-selected object, looks for the xrecord created by the CREATE command, and then calls the printList() function to print the data stored in the xrecord.

To use xtsndict.arx:
1. Load the arx application.
2. Draw an entity.
3. Command: CREATE (select the entity)
This will create an extension dictionary for the selected entity and place an xrecord object within it.
4. Command: LISTXREC (select the entity)
This will list the contents of the xrecord in the extension dictionary of the entity selected. Do not select an entity that has not had an extension dictionary and xrecord created by the CREATE command (or equivalent).