!set lang_exists=yes

!read adm/lang/sheetexam.phtml.$lang

!set name_student1=!nosubst Er mag aan dit werkblad gewerkt worden tot $expday $expmon $expyear
!set name_student2=Dit werkblad is verlopen. Er kan nog wel aan\
 worden gewerkt, maar de behaalde cijfers worden niet meer geregistreerd.
!set name_student3= Dit werkblad mag op dit moment nog niet worden ingezien.\
Neem desgewenst contact op met je docent.

!set name_score=!nosubst $[$got] uit $[$require] punten behaald, kwaliteit
!set name_score2=!nosubst $[$require] punten vereist.

!set name_scoreopen=De cijfer registratie is open.
!set name_scoreclosesup=L'arrêt de la notation n'est pas autorisé par votre enseignant.

!set name_textsource=Hier staat de broncode van het werkblad. U kunt deze via \
knippen en plakken in uw eigen klas importeren.
!set name_answer=Antwoord op oefening

!set name_title=!nosubst  Werkblad #$sh
!set name_exo=!defof name_exo in wimshome/public_html/scripts/oef/$modu_lang/names
!set name_noprint=!defof name_noprint in oef/$modu_lang/names
!set name_answers=!defof name_answers in oef/$modu_lang/names

!distribute items leerniveau,tijdsduur \
into name_level,name_duration
