
!set inputoption=!replace internal $	$ by $\
$ in $inputsize
!set inputsize=!line 1 of $inputoption
!set inputoption=!line 2 to -1 of $inputoption
!set option=!line 1 of $inputoption
!if $option issametext default
  !set option=class="wims_oef_input"
  !set inputoption=!line 2 to -1 of $inputoption
  !set inputoption=$option $inputoption
!endif
