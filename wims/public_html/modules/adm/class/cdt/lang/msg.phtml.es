!set wims_module_log=error: $error
<b>Erreur : </b>
!goto $error
!exit

:not_supervisor
 Afligido, pero la operación de preparación/modificación del cuaderno de textos se reserva al profesor de la clase.
!exit

:bad_class
 ¡Extraño, pero encuentro que su clase no es válida!
!exit

:bad_day
 La fecha introducida no es válida.
!exit

:bad_jday
 La fecha para los deberes no es válida.
!exit

:bad_date
 La fecha que quieren modificar no existe.
!exit

:day_exists
 La fecha introducida ya existe en el cuaderno de textos.
!exit

:same_devoir
 No pueden introducir dos fechas de deberes idénticas.
!exit

:same_devoir2
 No pueden, a partir del mismo día, introducir dos veces la misma fecha de deberes.<br>
 Utilizar más bien el vínculo
 !href cmd=new&job=adddate&filename=$jyear$jmonth$jday modificar una fecha
 .
!exit

:toomany_todo
 Ya alcanzaron el número máximo de deberes que se pueden dar en dicha fecha.
!exit

:day_dontexist
 La fecha introducida no es válida.
!exit
