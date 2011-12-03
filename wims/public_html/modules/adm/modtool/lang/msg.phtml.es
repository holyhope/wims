!set wims_module_log=error: $error

<span class="wims_warning">$wims_name_Error</span>.

!if empty_data iswordof $error
 !distribute items $wims_name_title,$wims_name_Description,$wims_name_Type into tmp_title, tmp_description, tmp_category

 Quiere cumplir la definición de
 <tt class="wims_warning">$(tmp_$(empty_data)</tt>
 de su módulo.
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
 Este módulo no puede copiarse.
 !exit
!endif

!if clash iswordof $error
 El módulo de destino ya existe.
 !exit
!endif

!if badtarget iswordof $error
 La dirección de destino no es buena: demasiado larga, demasiado corta,
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
 Imposible de copiar el módulo fuente, ya que contiene vínculos simbólicos.
 !exit
!endif

!msg $error
