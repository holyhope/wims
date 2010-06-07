!if $wims_read_parm!=$empty
  !goto $wims_read_parm
!endif

!distribute lines Método de prueba. Escribirá solamente en el directorio prueba. \
La actualización del sistema Wims está en curso. Ahí tienes el resumen de la escritura de salida actual. \
Es la versión pública más reciente del programa informático. No necesitan actualización. ¡\
La versión pública más reciente es \
Ustedes son más reciente que la versión pública!  Ninguna actualización pendiente. \
Salida de la última actualización \
resumen \
Pulsan aquí \

into name_test,name_warning, name_mostrecent,name_mostrecent2,name_morerecent,\
  name_output,name_summary,name_click

!set name_sorry=!nosubst Afligido, la carga a distancia de la nueva versión de Wims a partir <de tt> $download< /tt> ha fallado. Intente más tarde, por favor.
!set name_summary=!nosubst Resumen de la última actualización: (Enviar lo a $wims_maintainer en caso de error.)
!set name_detailed=!nosubst Salida detallada de la última actualización: (Enviar lo a $wims_maintainer en caso de error.)
!set name_sorry2=!nosubst Afligido, el lugar de carga a distancia <tt> $download< /tt> es  inaccesible.
!set name_version=!nosubst Este sitio WIms está actualmente en versión $wims_version.

!exit
:update
para cargar a distencia WIMS $pubversion de <tt>$download</tt> y poner al dia
el servidor. <b><font color=red>$wims_name_warning</font></b> Eso creará
indisponibilidades momentáneas del servidor.
<em>No ponen al día si el servidor está ocupado.</em>
<p>
<b>Note</b>. La actualización del servidor no modificará sus recursos locales
(clases, ejercicios, documentos, módulos en desarrollo).
<p>
<b><font color=red>IMPORTANTE</font></b> ¡Deben comprobar
los derechos sobre los ficheros después de las actualizaciones!
