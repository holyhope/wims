!set lang_exists=yes

!set name_intro=!nosubst U wilt <span class="tt wims_fname">$dir</span> zichtbaar maken \
in uw klas of de titel, \
omschrijving of toegangsrechten en status veranderen

!set name_wksheet=Link the document with the sheet (optional)

!if $doc>0
 !set name_intro=$name_intro of de link naar dit materiaal verwijderen
!endif
