!!@# translate between !!@# et !!#@
!if nom_fichier iswordof $error
  <span class="wims_warning">
!!@#
de naam van het bestand is ongeschikt.
Een bestandsnaam mag geen
  <span class="tt">..</span> en ook geen <span class="tt"> / </span> bevatten .
!!#@
</span>
  !exit
!endif
!if bad_data iswordof $error
!!@#
<b>Fout.</b> Ik begrijp niet wat de bedoeling is. Tik foutje ?
!!#@
 !exit
!endif

!if $error!=$empty
  !if target iswordof error
    <span class="wims_warning">
!!@#
 Kies een module.
!!#@
</span>
    !exit
  !endif
<span class="wims_warning">
!!@#
Niet vergeten de verplichte velden, gemarkeerd met een * in te vullen.
!!#@
</span>
!endif
!if type_exo iswordof $error or file iswordof $error
!!@#
In bijzonder :
!!#@
<dl>
!if type_exo iswordof $error
 <dt>
!!@#
Kies het type meerkeuze vraag
!!#@
 </dt>
!endif

!if file iswordof $error
  <dt>
!!@#
Deze oefening zal straks alleen correct kunnen werken als de data voldoen aan de vereiste syntax,
zoals omschreven in de help pagina's.
In dit stadium wordt er een bestands naam verwacht.
!!#@
</dt>
!endif
</dl>
!if oefempty iswordof $error and $transfert=yes
!!@#
Eert moet er een OEF module in uw Modtool account worden aangemaakt.
!!#@
!endif
!exit


!msg $error
