!set lang_exists=yes

!read adm/lang/sheetexam.phtml.$lang

!set name_student1=!nosubst Puede trabajar en esta hoja hasta el $expday $expmon $expyear
!set name_student2=Esta hoja ha expirado. Puede seguir \
 trabajando en ella, pero sus puntuaciones ya no serán tenidas en cuenta.
!set name_student3= Por el momento no está autorizado a consultar el contenido de esta hoja.\
  Por favor contacte con su profesor.

!set name_score=!nosubst $[$got] de $[$require] puntos obtenidos, calidad
!set name_score2=!nosubst $[$require] puntos exigidos.

!set name_scoresuspend=El registro de las puntuaciones suspendido por usted mismo.
!set name_scoreopen=El registro de las puntuaciones está abierto
!set name_scoreclosesup=L'arrêt de la notation n'est pas autorisé par votre enseignant.

!set name_textsource= Este es el fichero fuente de la hoja. Puede importarlo a su clase \
  simplemente mediante el sistema de cortar y pegar.
!set name_answer=Respuestas del ejercicio

!set name_title=!nosubst Hoja de trabajo número $sh
!set name_empty=¡Esta hoja está en blanco! Se trata probablemente de un error.

!set name_scoreopen=L'enregistrement des notes est ouvert.

!set name_textsource=Voici le fichier source de cette feuille. Vous pouvez l'importer \
  dans votre classe en utilisant un copier-coller.
!set name_answer=Réponse à l'exercice


!set name_title=!nosubst $wims_name_sheet $wims_name_number$sh
!set name_exo=!defof name_exo in wimshome/public_html/scripts/oef/$modu_lang/names
!set name_noprint=!defof name_noprint in oef/$modu_lang/names
!set name_answers=!defof name_answers in oef/$modu_lang/names

!distribute items nivel aproximado, duración \
into name_level,name_duration
