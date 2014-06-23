
This sample shows the usage of creating a custom filer derived from
AcDbDwgFiler, trapping the contents	of an entity's filing data, 
writing the data in a custom format and re-creating the entities 
using custom format. 

How to use it: 

 a) Build the application.
 b) Start autocad and load the ARX application.
 c) Create some entities in autocad.
 d) Command: writefile, enter file name and select the entities.
 e) Command: readentity and enter the file name. Since this sample program
    supports few entities such as line, arc, circle, ray, xline, spline,
    solid3d, region, text etc. only these entities will be re-created. 
    All the other entity type will be rejected. 
