
Refer to ARX Developer's Guide

To use chglyr.arx:

Make sure chglyr.arx is in your main AutoCAD directory.

1. Start AutoCAD and open a new drawing.

2. Make a few entities such as lines, circles, arcs etc. These will be placed 
on layer 0 by default.

3. Make a new layer using the DDLMODES command. Remember the new layer's name.

4. Type (arxload "chglyr") to load chglyr.arx.

5. Type the ASDK_ADS_CHLAYER command, defined by chglyr.arx.

6. When asked to choose an entity, do so. 

7. When asked for a layer name, enter the name of the layer you created in step 
three above.

8. You can verify the entity was moved to the layer you specified using the LIST 
command with the ALL option. 

Problems:

If you neglect to create a layer before running the ASDK_ADS_CHLAYER command, 
AutoCAD will not warn you that the entity wasn't moved to the new layer.
