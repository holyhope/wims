
!set wims_warn_header=<p><span class="wims_warning">$wims_name_warning.</span>

!if inconsistent_columns iswordof $wims_warn_rawmatrix
 $wims_warn_header
 Soy incapaz de interpretar la matriz que ha introducido, porque
 parece que las filas tienen distinto número de elementos. Por favor,
 verifique la matriz, y use COMAS para separar los elementos, en lugar
 de espacios.
 <p>
!endif

