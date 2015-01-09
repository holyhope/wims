!set lang_exists=yes

!set name_noexercise= No tiene ningún ejercicio que se pueda grabar.
!set name_listexercise=!nosubst Pueden grabarse los ejercicios de la hoja de trabajo $logsheet
!set name_noexercise2=No se ha grabado ningún ejercicio de
!set name_click= !nosubst Estos son los ejercicios grabados de $(names[1]) $(names[2]).
Pulse en la fecha para reproducir uno..\


!distribute items Pasos,Número,Puntuación\
into name_Step,name_number,wims_name_Score

!set name_source=source
!set name_sendmail=Bug?
!set name_bug=If you think the exercise is bugged, thanks to send a mail by clicking\
on the button <span class="wims_button disabled">$name_sendmail</span> and joining the file\
<span class="wims_button disabled">$name_source</span>.
