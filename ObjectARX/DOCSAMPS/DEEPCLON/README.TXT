ARX Developer's Guide

Chapter 13 -- Deep Cloning 

 <> Deep Clone Basics 
  <> Typical Deep Clone Operation

Filename:
  deepclon\deepclon.cpp

Description:
  cloneSameOwnerObjects()
  cloneDiffOwnerObjects()

Procedure:
 1. Load deepclon.arx
 2. Draw one circle and one line
 2. Command: ASDK_DIFFOWNER
 3. Select the circle for Model Space then press enter
 4. Select the line for Paper Space then press enter

    Two object ID should be printed. The object ID's are retreived
    from an object ID map that was created/filled during deep clone
    process.

    The Developer's Guide and the source code explains what took
    place in more detail.
    
    ASDK_SAMEOWNER command is similar
   
