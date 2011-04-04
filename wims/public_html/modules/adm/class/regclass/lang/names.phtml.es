!set lang_exists=yes

!set lev_E=educación primaria
!set lev_H=educación secundaria
!set lev_U=universidad
!set lv1=!char 1 of $ilevel
!set lv2=!char 2 of $ilevel
!set name_level=$(lev_$lv1), año $lv2
!set levelid=E1,E2,E3,E4,E5,E6,H1,H2,H3,H4,H5,H6,H7,U1,U2,U3,U4,U5,G,R
!set leveldesc=$levelid
!set nblevel=!itemcnt $levelid

!read adm/lang/class_title.phtml.$modu_lang

!if $Cltype iswordof 2 4
   !if $Cltype=2
    !set name_classe=agrupación de clases
    !set name_sup=del profesor-administrador
   !else
    !set name_classe=portal de centro educativo
    !set name_sup=del administrador
   !endif
     !set name_classes= el $name_classe
     !set name_classess= un $name_classe
     !set name_classesss= del $name_classe
     !set name_classessss= El $name_classe
 !else
   !set name_classe=clase
   !set name_classes=la $name_classe
   !set name_classess=una $name_classe
   !set name_classesss= de la $name_classe
   !set name_classessss= La $name_classe
   !set name_sup=del profesor
 !endif

!distribute lines Seguir\
  Reiniciar la operación\
  Creación de $name_classess\
  Nombre del centro educativo\
a lo sumo\
a lo menos\
  Reservado a los expertos\
  caracteres\
  Volver de nuevo al principio de la operación.\
  Seleccione el tipo de clase virtual que desea crear.\
  entre 4 y 16 caracteres, dígitos o letras sin acentuar\
 into name_continue,name_again,title,name_Name_portal,name_atmost,name_atleast,name_expert,\
   name_characters,name_comeback,name_choose,name_warningpass

!if $regpolicy=file
  !set noright=(no está autorizado para hacer eso).
 !else
  !set noright=(únicamente el administrador del sitio puede hacerlo).
 !endif

!set name_regpolicy=la creación de una clase no tendrá éxito a menos que dé una dirección\
   de correo correcta a la que tenga acceso en este momento

!set name_help1=Esta contraseña le permitirá acceder a la $name_classe como su supervisor.\
  Debe ser la única persona que la conozca.

!set name_help2=La contraseña $name_classesss se requerirá para la inscripción\
   de los participantes en la clase; así que deberá comunicársela a sus estudiantes.

!set name_help3=La contraseña $name_classesss se requerirá para la inscripción\
   de los profesores $name_classesss; sus estudiantes y alumnos no deben conocerla.

!distribute lines Es la fecha a la cual se archivará automáticamente su clase.\
  Límite de participantes de la $name_classe\
  Acceso seguro\
  Opcional\
  Nombres de las estaciones de trabajo desde las que efectuará las operaciones sensibles sobre su $name_classe.\
  Esta clave es de un solo uso. ¡No puede usarse para conectar a la $name_classe!\
 Clave de la $name_classe\
  into name_help_date,name_help_limit,name_secure,name_optional,name_host,name_warning_code,name_code

 !exit
