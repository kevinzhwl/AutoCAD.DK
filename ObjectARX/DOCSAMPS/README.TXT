       ARX Programmer's Guide Sample Code Table of Contents

This directory (and some of the samples in the "samples" directory)
contain code to build ARX applications which use sample code from the ARX
Programmer's Guide.  Users can run these ARX applications to verify the
behavior of sample code found in the Programmer's Guide.

This file provides a quick correlation between the pieces of sample code
shown in the ARX Programmer's Guide and the actual source files they come
from.  Each sample in the manual has a source file that is part of a
sample program that can be built and run.

In the listing below,  the samples are listed in the order they are found
in the Programmer's Guide.  Also,  any directory path that does not start
with "sample" or "inc" is a path relative to the directory containing this
readme file.  All paths that start with "sample" are referring to the
"sample" directory that is alongside the directory containing this readme
file.


description                                       file name
-------------------------------------------------------------
ch. 1
changeLayer()                                     chglyr\arx\chglyr.cpp
changeLayerADS()                                  chglyr\ads\chglyr.c
changeLayerLISP                                   chglyr\lisp\chglyr.lsp

ch. 2
createLine()                                      ents\ents.cpp
createCircle()                                    ents\ents.cpp
createNewLayer()                                  ents\ents.cpp
changeColor()                                     ents\ents.cpp
createGroup()                                     ents\ents.cpp

ch. 3
AsdkCommandReactor::commandEnded()                sample\notfsamp\notfsamp.cpp
initApp()/unloadApp()                             custobj\custobj.cpp
createCircle() with error checking                entswerr\entswerr.cpp
createNewLayer() with error checking              entswerr\entswerr.cpp

ch. 4
createDwg() & readDwg()                           testdb\testdb.cpp

ch. 5
selectEntity()                                    specials\getobjid.cpp
printXdata()/addXdata()                           xdata\xdata.cpp
createXrecord()/listXrecord()                     xtsndict\arx\xtsndict.cpp
createXrecord()/listXrecord()                     xtsndict\ads\xtsndict.c

ch. 6
subentity highlighting sample program             hilight\hilight.cpp
createInsert()/hilitInsert()                      sample\polysamp\hilit.cpp
createLine()                                      ents\ents.cpp
makeABlock()                                      complex\complex.cpp
defineBlockWithAttributes()                       complex\complex.cpp
addBlockWithAtributes()                           complex\complex.cpp
printAll()                                        complex\complex.cpp
createPolyline()                                  complex\complex.cpp
iterate()                                         pliniter\pliniter.cpp
projectEllipse()/offsetEllipse()                  curve\curve.cpp

ch. 7
addLayer()                                        tablerec\tablerec.cpp
iterateLinetypes()                                tbliter\tbliter.cpp
groups()/makegroup()/removeAllButLines()          groups\groups.cpp
createDictionary()                                custobj\custobj.cpp
iterateDictionary()                               custobj\custobj.cpp
createXrecord()/listXrecord()                     xrecord\arx\xrecord.cpp
createXrecord()/listXrecord()                     xrecord\ads\xrecord.c

ch. 8
ACRX macro expanded                               specials\acrxmac.txt

ch. 9
dwgOutFields()                                    sample\polysamp\poly.cpp
dwgInFields()                                     sample\polysamp\poly.cpp
dxfOutFields()                                    sample\polysamp\poly.cpp
dxfInFields() order independent                   sample\polysamp\poly.cpp
dxfInFields() order dependent                     sample\polysamp\poly.cpp
  (the order dependent version of dxfInFields() is
  #ifdef'd on ORDER_DEPENDENT)

makeOwner()                                       specials\makeownr.cpp
custom ownership hierarchy sample program         ownrshp\ownrshp.cpp
createObjs()                                      ownrshp\ownrshp.c
AsdkPoly::setNumSides()                           sample\polysamp\poly.cpp
AsdkPoly::applyPartialUndo()                      sample\polysamp\poly.cpp
interobject references sample program             referenc\referenc.cpp
custom database object sample program             custobj\custobj.cpp

ch. 10
worldDraw() (subentity traits)                    acgismps\traits\traits.cpp
worldDraw() (mesh generation)                     acgismps\mesh\mesh.cpp
worldDraw() (shell generation)                    acgismps\shell\shell.cpp
worldDraw() (textstyle use)                       acgismps\textstyl\textstyl.cpp
getTextStyle() (AcDb->AcGi style)                 acgismps\stylcvrt\stylcvrt.cpp
viewportDraw() (transforms)                       acgismps\coordsys\coordsys.cpp
worldDraw/viewportDraw() (showing use of                        
  getNumPixelsInUnitSquare)                       acgismps\viewgeom\viewgeom.cpp
viewportDraw() (window coords)                    acgismps\icon\icon.cpp
worlDraw()/viewportDraw() (arc tesselation)       acgismps\teselate\teselate.cpp
getOsnapPoints()                                  sample\polysamp\poly.cpp
getGripPoints()                                   sample\polysamp\poly.cpp
moveGripPointsAt()                                sample\polysamp\poly.cpp
getStretchPoints()                                sample\polysamp\poly.cpp
moveStretchPointsAt()                             sample\polysamp\poly.cpp
transformBy()                                     sample\polysamp\poly.cpp
getTransformedCopy()                              sample\polysamp\poly.cpp
intersectWith() (both versions)                   sample\polysamp\poly.cpp
AcEdJig sample program                            elipsjig\elipsjig.cpp

ch. 11
No code samples in this chapter

ch. 12
database reactor sample program                   dbreact\dbreact.cpp
getting/using reactor objectId                    sample\notfsamp\notfsamp.cpp
persistent reactor sample program                 persreac\persreac.cpp

ch. 13
transactCommand() and other functions             sample\polysamp\transact.cpp

ch. 14
cloneSameOwnerObjects()                           deepclon\deepclon.cpp
cloneDiffOwnerObjects()                           deepclon\deepclon.cpp
cloning objects in NOD                            clonod\clonenod.cpp
standard deepclone() implementation               sample\polysamp\poly.cpp
standard wblockclone() implementation             sample\polysamp\poly.cpp
otherWblock() reactor notification                othrwblk\othrwblk.cpp
beginDeepCloneXlation() notification              clonreac\clonereac.cpp

ch. 15
initialization and addX calls                     tempapp\tempapp.cpp
calling protocol extension functions              specials\xcall.cpp
ACRX_X_CALL useage                                tempapp\tempapp.cpp
protocol extension sample program                 tempapp\tempapp.cpp

ch. 16
Dynamic library MFC with ARX sample               utils\mfcextras\resourcehelper.h
                                                  utils\mfcextras\arxmfcdll.cpp

Static library MFC with ARX sample                mfcsamps\static\mfctempl.h
                                                  mfcsamps\static\mfctempl.cpp
                                                  mfcsamps\static\rxtemplt.cpp

ch. 17
ActiveX Automation sample
step 2                                            sample\polysamp\polyolea\polyolea.odl
step 3                                            sample\polysamp\polyolea\polyolea.h
step 4                                            sample\polysamp\polyolea\polyolea.reg
step 6                                            sample\polysamp\polyolea\cpoly.h
step 6                                            sample\polysamp\polyolea\cpoly.cpp
step 7                                            inc\interfac.h
step 7                                            sample\polysamp\polyolea\cpoly.cpp
step 8                                            sample\polysamp\polyolea\cpoly.h
step 8                                            sample\polysamp\polyolea\server.cpp
step 9                                            sample\polysamp\polyolea\cpoly.cpp
step 11                                           sample\polysamp\main.cpp

Appendix A
ADS to ADS-Rx sample program                      fact\fact.cpp
