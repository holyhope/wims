
!set wims_module_log=error: $error $wims_class

<b>Error</b>.

!if not_supervisor iswordof $error
 Lo sentimos, sólo el profesor de una clase virtual puede acceder a este módulo.
 !exit
!endif

!if not_secure iswordof $error
 !if $code!=$empty
  Código secreto incorrecto.
 !else
  A este módulo sólo se puede acceder desde una estación de trabajo segura.
 !endif
 Acceso rechazado.
 !exit
!endif

!if checkhost iswordof $error
 Su conexión actual no forma parte de las definidas como estaciones de
 trabajo seguras. Se trata probablemente de un error que puede hacerle perder 
 el control de la clase. En consecuencia no se ha modificado la relación de
 estaciones de trabajo seguras.
 !exit
!endif

!if bad_file iswordof $error
 Lo sentimos pero no reconocemos <em>$wims_deposit</em> 
 como copia de seguridad de una clase. Es posible que haya enviado un fichero
 incorrecto o que haya sido dañado.
 !exit
!endif

!if empty_file iswordof $error
 No encontramos recursos de clase en su copia de seguridad.
 <tt>$wims_deposit</tt>.
 !exit
!endif

!if no_upload iswordof $error
 Los datos enviados han expirado. Acción fallida, por favor reinténtela.
 !exit
!endif

!if remote_sharing iswordof $error
 La clase vecina comparte sus recursos. Antes de que deje de compartirlos,
 usted ni puede negarse a que siga compartiéndolos ni puede eliminarla de
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
 Ha intentado realizar una operación con una clase que no es su vecina
 efectiva.
 <p>
 Recuerde que una clase es su vecina efectiva únicamente si se han declarado
 las vecindades mutuas A LA VEZ por usted y por la otra clase.
 !exit
!endif

!if localmirror iswordof $error
 No tiene sentido hacer una réplica de una clase en el mismo servidor.
 !exit
!endif

!if toobigfile iswordof $error
 La taille de votre fichier est trop importante : la limite est de 12K.
 !exit
!endif

!msg $error

