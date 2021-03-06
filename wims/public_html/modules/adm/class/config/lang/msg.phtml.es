
!set wims_module_log=error: $error $wims_class

<b>$wims_name_Error</b>.

!if not_secure iswordof $error
 !if $code!=$empty
  C�digo secreto incorrecto.
 !else
  A este m�dulo s�lo se puede acceder desde una estaci�n de trabajo segura.
 !endif
 Acceso rechazado.
 !exit
!endif

!if checkhost iswordof $error
 Su conexi�n actual no forma parte de las definidas como estaciones de
 trabajo seguras. Se trata probablemente de un error que puede hacerle perder
 el control de la clase. En consecuencia no se ha modificado la relaci�n de
 estaciones de trabajo seguras.
 !exit
!endif

!if bad_file iswordof $error
 Lo sentimos pero no reconocemos <em>$wims_deposit</em>
 como copia de seguridad de una clase. Es posible que haya enviado un fichero
 incorrecto o que haya sido da�ado.
 !exit
!endif

!if empty_file iswordof $error
 No encontramos recursos de clase en su copia de seguridad.
 <span class="tt wims_fname">$wims_deposit</span>.
 !exit
!endif

!if no_upload iswordof $error
 Los datos enviados han expirado. Acci�n fallida, por favor reint�ntela.
 !exit
!endif

!if remote_sharing iswordof $error
 Una clase vecina comparte sus recursos. Antes de que deje de compartirlos,
 usted ni puede negarse a que siga comparti�ndolos ni puede eliminarla de
 su lista de vecinas.
 !exit
!endif

!if share_dep iswordof $error
 Al compartir recursos es necesario respetar las dependencias: debe compartir
 los ejercicios antes de compartir sus hojas de trabajo y debe compartir
 las hojas de trabajo antes de compartir las hojas de examen.
 !exit
!endif

!if not_neighbor iswordof $error
 Ha intentado realizar una operaci�n con una clase que no es su vecina
 efectiva.
 <br />
 Recuerde que una clase es su vecina efectiva �nicamente si se han declarado
 las vecindades mutuas A LA VEZ por usted y por la otra clase.
 !exit
!endif

!if localmirror iswordof $error
 No tiene sentido hacer una r�plica de una clase en el mismo servidor.
 !exit
!endif

!if toobigfile iswordof $error
 El tama�o de su fichero es demasiado importante: el l�mite es de 12K.
 !exit
!endif

!msg $error

