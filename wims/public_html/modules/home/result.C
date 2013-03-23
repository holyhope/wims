
!if $gotcntC > 0
  !set gotcnt=$gotcntC
  !set gotm=$gotmC
  !set gotd=$gotdC
  !set gott=$gottC
!endif
$wims_name_n_example
<ul class="wims_home_result_list wims_class">
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 <li class="wims_home_result_list">
 !href module=home&user=anonymous,$m_,anonymous $t_
</li>
!next i
</ul>
