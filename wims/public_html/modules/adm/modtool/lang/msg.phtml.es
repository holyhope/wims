!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if empty_data iswordof $error
 !distribute items $wims_name_title,$wims_name_Description,$wims_name_Type into tmp_title, tmp_description, tmp_category

 Quiere cumplir la definici�n de
 <span class="tt wims_warning">$(tmp_$(empty_data)</span>
 de su m�dulo.
 !exit
!endif

!if bad_fname iswordof $error
 Nombre de fichero ilegal. Quiere elegir otro nombre para su fichero.
 !exit
!endif

!if binary_file iswordof $error
 Fichero binario prohibido.
 !exit
!endif

!if illegal_filedesc iswordof $error
 No pueden poner sino definiciones directas en filedesc.
 !exit
!endif

!if badoriginal iswordof $error
 Este m�dulo no puede copiarse.
 !exit
!endif

!if clash iswordof $error
 El m�dulo de destino ya existe.
 !exit
!endif

!if badtarget iswordof $error
 La direcci�n de destino no es buena: demasiado larga, demasiado corta,
 incompleta o caracteres no admitidos.
 <ul>
  !if incorrect_t1 iswordof $error
   <li>incorrect zone</li>
  !endif
  !if incorrect_t2 iswordof $error
   <li>incorrect category</li>
  !endif
  !if incorrect_t3 iswordof $error
   <li>incorrect name</li>
  !endif
  !if incorrect_t4 iswordof $error
   <li>incorrect language</li>
  !endif
  !if incorrect_tlen iswordof $error
   <li>too long or too short address</li>
  !endif
 </ul>
 !exit
!endif

!if symlink iswordof $error
 Imposible de copiar el m�dulo fuente, ya que contiene v�nculos simb�licos.
 !exit
!endif

!if file_too_large iswordof $error
  The module cannot be archived, it is too large.
  !exit
!endif
!msg $error
