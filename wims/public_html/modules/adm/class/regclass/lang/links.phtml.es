 Diversos enlaces a su $name_classe:<ul>
 <li>El enlace
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/classes&type=authsupervisor&class=$code">http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/classes&type=authsupervisor&class=$code</a>
  le lleva a la página de mantenimiento $name_classesss (preparación de hojas
  de trabajo, lista de los participantes y de sus progresos, etc.). <p>
 <li>El enlace
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/reguser&class=$code&subclass=yes">http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/reguser&class=$code&subclass=yes</a>
  permite a sus alumnos autoinscribirse en una clase (o le permite inscribirles)
   !if $Cltype>=2
    cuando haya creado las clases del $name_classe. 
   !endif
   !if $password!=$empty
    (necesitarán la contraseña de la clase para inscribirse por sí mismos).
   !endif
  !if $Cltype>=2
    <p>
  <li>El enlace
   <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/reguser&class=$code">http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/reguser&class=$code</a>
  permite a los profesores inscribirse en su $name_classe (o le permite a usted inscribirles).
  !if $password!=$empty
    (necesitarán la contraseña de la clase para inscribirse por sí mismos).
   !endif
  !endif
  <p>
 <li>Finalmente, el enlace
  <a href="http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/classes&type=authparticipant&class=$code">http://$httpd_HTTP_HOST$httpd_SCRIPT_NAME?lang=es&module=adm/class/classes&type=authparticipant&class=$code</a>
  lleva a los estudiantes inscritos a la página inicial $name_classesss. Las hojas 
  de trabajo que prepare les serán accesibles desde esta página de inicio.
  <p>
 </ul>
 <p><b><font color="red">Importante.</font></b> 
 ¡Guarde estos enlaces antes de salir de esta página!
 También le aconsejamos que anote el número de la clase.

