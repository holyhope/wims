
!if $gotcntC > 0
  !set gotcnt=$gotcntC
  !set gotm=$gotmC
  !set gotd=$gotdC
  !set gott=$gottC
!endif

!default gotcntC=0
!if $[$gotcntC + $gotcnt]=0
 !href module=adm/class/classes&type=example $name_allexampleclass
!endif

<ul class="wims_home_result_list wims_class">
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 !set i_=!line $i of $gotiC
 <li class="wims_home_result_list">
 !href module=home&user=anonymous,$m_,anonymous $t_
.
 !if $i_!=$m_
  $i_
 !endif
<span class="small">$d_</span>
</li>
!next i
</ul>
