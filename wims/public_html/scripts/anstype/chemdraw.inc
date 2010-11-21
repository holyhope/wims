!set help_option=$wims_read_parm
!default help_option=single,atom,double,erasor,template
!set lang_=$lang
!if $lang_ notwordof fr
  lang_=fr
!endif
!set ch_=<ul>
!for t_ in $help_option
   !set c_=!lookup $t_ in lang/chemdraw.$lang_
   !set ch_=$ch_\<li>$c_</li>
!next
!set ch_=$ch_</ul>

!read oef/special/tooltip.phtml $wims_name_help,[ABOVE,false,WIDTH,300],$ch_