This is a sample application using the AutoCAD SQL Interface Link API.  

  Commands             What it demonstrates
  --------             --------------------
  ASESMP_DIAG          - Gets access to the ASE global diagnostics area,
                       demonstrates how to map ASE global error,
                       how get access to diagnostics parameters and
                       how to clear global diagnostics area by means of
                       CAseAppl::clearAseErr()
  
  ASESMP_CONNECTASE    - Connects ASE to the DB3 environment by means of
                       CAseLinkPath::connectAse()
  
  ASESMP_DISCONNECTASE - Disconnects ASE from the DB3 environment by means of
                       CAseLinkPath::disconnectAse()
  
  ASESMP_CREATETABLE   - Creates a database table by means of 
                       CAseLinkPath::createTable().
                       The created table path is DB3.ASE.DB3SAMPLE.NEWTBL.
                       The created table structure is the following:
                       
                       EMP_ID      INTEGER  (maps to DECIMAL(11) under DB3)
                       LAST_NAME   CHAR(25)
                       FIRST_NAME  CHAR(15)
                       
                       EMP_ID is considered to be a key column to 
                       address the table rows.
  
  ASESMP_DROPTABLE     - Drops the database table DB3.ASE.DB3SAMPLE.NEWTBL by
                       means of CAseLinkPath::dropTable().
  
  ASESMP_CREATELPN     - Creates the LPN NEWLPN to the database table
                       DB3.ASE.DB3SAMPLE.NEWTBL with EMP_ID as the key column.
                       Gets the table structure by means of
                       CAseLinkPath::getTableDsc().
  
  ASESMP_ADDROW        - Adds row to the database table DB3.ASE.DB3SAMPLE.NEWTBL 
                       by means of CAseLinkPath::addRow().
  
  ASESMP_UPDROW        - Updates the row(s) with the specified key
                       in the database table
                       DB3.ASE.DB3SAMPLE.NEWTBL by means of
                       CAseLinkPath::updRow().
  
  ASESMP_DELROW        - Deletes the row(s) with the specified key from 
                       the database table DB3.ASE.DB3SAMPLE.NEWTBL by 
                       means of CAseLinkPath::delRow().
  
  ASESMP_MAKELINK      - Links the selected entity and row from the
                       database table with the specified key by means 
                       of LPN NEWLPN.
  
  ASESMP_GETROWS       - Prints rows from the database table 
                       linked with the selected entity by 
                       means of NEWLPN.
                       Demonstrates the correspondence
                       [graphics -> extern database]
  
  ASESMP_GETENTS       - Highlights the entities linked by means of LPN
                       NEWLPN with the database table with the rows
                       defined by the specified SQL WHERE condition.
                       Demonstrates the correspondence
                       [extern database -> graphics]
