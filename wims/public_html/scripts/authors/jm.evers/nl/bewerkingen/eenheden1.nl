#antwoord 50 centimeter = 0.5 meter
#
!if $eenheid!=
    eenheid=!replace [0-9] by  in $(GOED$n)
    eenheid=!lower $eenheid
!endif

eenheden=kiloton,ton,kilo,pond,gram,milligram,\
kilometer,meter,centimeter,millimeter,\


ANT$n=!lower $(ANT$n)

testeenheid=!replace [0-9] by  in $(ANT$n)
testeenheid=!words2lines $testeenheid

!if $eenheid notin $(ANT$n)




!endif


:NIKS