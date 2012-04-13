!distribute items $wims_read_parm into r_,date_ 
!goto $r_
:1
!formselect dyear$i from $creyear to $expyear
!formselect dmonth$i from 1 to 12 prompt $months
!formselect dday$i from 1 to 31
!exit

:2
!formselect dyear$i from $creyear to $expyear
!formselect dmonth$i from 1 to 12 prompt $months
!formselect dday$i from 1 to 31
!exit

:3
!formselect jyear from $creyear to $expyear
!formselect jmonth from 1 to 12 prompt $months
!formselect jday list 0,$v prompt ---,$v

:4
!formselect jyear2 list 0,$v1 prompt ---,$v1
!formselect jmonth2 from 0 to 12 prompt ---,$months
!formselect jday2 list 0,$v prompt ---,$v
!exit

:5
!let day=!char 7 to 8 of $date_
!let month=!char 5 to 6 of $date_
!let year=!char 1 to 4 of $date_
!if $cdt_nbmonth>12  
 $year/$month/$day
!else 
 $month/$day
!endif
!exit