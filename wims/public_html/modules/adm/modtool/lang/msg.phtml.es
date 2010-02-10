!set wims_module_log=error: $error

<b>Error</b>.

!if bad_auth iswordof $error
 Fracaso de autenticación. Vuelve a intentar.
 !exit
!endif

!if bad_pass iswordof $error
 Mala contraseña: debe tener entre 4 y 16 caracteres,
 cartas y cifras solamente. ¡Y la contraseña repetida debe ser idéntica
 primero! Intente aún.
 !exit
!endif

!if empty_data iswordof $error
 Quiere cumplir la definición de
 <b><em><font color=red>$(name_$empty_data)</font></em></b>
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
 !exit
!endif

!if symlink iswordof $error
 Imposible de copiar el módulo fuente, ya que contiene vínculos simbólicos.
 !exit
!endif

!msg $error

