
!set wims_warn_header=<p><span class="wims_warning">$wims_name_warning.</span>

!if inconsistent_columns iswordof $wims_warn_rawmatrix
 $wims_warn_header
 Ik kan de opgegeven matrix niet interpreteren, omdat ogenschijnlijk
 verschillende rijen/kolommen verschillende aantallen elementen bevatten.
 Controleer de matrix en gebruik <b>komma's</b> in plaats van spaties om de elementen te scheiden. 
 
 <p>
!endif

