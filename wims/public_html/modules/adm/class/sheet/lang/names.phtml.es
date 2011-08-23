!let lang_exists=yes

!read adm/lang/date.phtml.$moduclass_lang
!read adm/lang/sheetexam.phtml.$lang
 
!set statutname=$(wims_name_shstatus[1]),$wims_name_shstatus
!set seriesaction=!nosubst $wims_name_change,$wims_name_erase,$wims_name_up

!let name_shtab=!nosubst $wims_name_number,$wims_name_title,$wims_name_Description,Puntos,Points,$name_weight,$name_dependency,$wims_name_comment,$wims_name_action,Paramètres de la série,$wims_name_feedbackexo

!if $activetest<=0
 !let wims_name_sheetadmin=Página de preparación
 !set name_title=!nosubst Preparación de la hoja de trabajo $sheet
!else
 !let wims_name_sheetadmin=Página de gestión
 !set name_title=!nosubst Gestión de la hoja $sheet
!endif
!let name_mksheet=Pulse para crearla

!distribute lines Informaciones generales \
Contenido de la hoja de trabajo\
Esta hoja de trabajo no tiene aún contenido.\
El título original es\
Modificación del ejercicio\
Número de puntos pedidos\
Corregir el código fuente\
La fecha de expiración de la hoja debe ser previa a la fecha de expiración de la clase\
Se ignora pues su petición.\
into name_info,name_content,name_warning,name_oldtitle,name_titlemodif,\
name_pointsasked,name_correctsource,name_expiration1,name_expiration2

!set name_text1=Para añadir un trabajo (ejercicio, herramienta, etc.) a la hoja, deben en primer lugar elegirlo\
(véase abajo); regule los distintos parámetros propuestos y lanza el ejercicio.\
A continuación, utilizan el vínculo sobre el borde del ejercicio para añadirlo a la hoja.\
Para elegir su trabajo, tienen una de las posibilidades siguientes

!set name_text2= Pasar por el motor de investigación
!set name_text3=Buscar un ejercicio entre
!set name_text4=Buscar un ejercicio de su cuenta

!set name_getsource=Voici le source de cette feuille. Vous pouvez copier ce source (entre les deux lignes composées de `*'; \
utilisez le presse-papier) dans un fichier, ce qui vous permettra de réutiliser le contenu dans une autre feuille ultérieurement. 

!set name_regmodif=Modificación registrada
!! be careful define variable below only if module help/teacher/program work in your lang. Keep , at the same place.
!!set name_helpprog=Ayudarse de esta correspondencia orientativa, entre los programas de la enseñanza francesa y los ejercicios Wims
!set name_helpprog=$empty
