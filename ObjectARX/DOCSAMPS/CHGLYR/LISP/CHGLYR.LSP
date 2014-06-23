;;;    Copyright (C) 1996 by Autodesk, Inc.
;;;
;;;    Permission to use, copy, modify, and distribute this software
;;;    for any purpose and without fee is hereby granted, provided
;;;    that the above copyright notice appears in all copies and
;;;    that both that copyright notice and the limited warranty and
;;;    restricted rights notice below appear in all supporting
;;;    documentation.
;;;
;;;    AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
;;;    AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
;;;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
;;;    DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
;;;    UNINTERRUPTED OR ERROR FREE.
;;;
;;;    Use, duplication, or disclosure by the U.S. Government is subject to
;;;    restrictions set forth in FAR 52.227-19 (Commercial Computer
;;;    Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) 
;;;    (Rights in Technical Data and Computer Software), as applicable.
;;;

;;; THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
(defun asdk_changeLayerLISP(ename newLayer / eList)

    (setq eList (entget ename))

    ; substitute the new layer name for the old
    ;
    (setq eList
        (subst (cons 8 newLayer) (assoc 8 eList) eList))

    ; Modify the entity's data in drawing to reflect
    ; the changed layer
    ;
    (entmod eList)
    (princ)
)
;;; END CODE APPEARING IN SDK DOCUMENT.

(defun c:asdk_lisp_chlayer ()
    (setq ent (car (entsel 
        "\nselect an entity to change the layer of: ")))
    (setq layername (getstring "\nNew layer name (32 char max): "))
    (asdk_changeLayerLISP ent layername)
)
