!set lang_exists=yes

!set name_intro=!nosubst Quieren que sea accesible en su clase \
el recurso público <tt class="wims_fname">$dir</tt> o modificar su título, su texto descriptivo\
o su estatuto

!if $doc>0
 !set name_intro=$name_intro o suprimir el vínculo sobre este recurso en su clase
!endif
