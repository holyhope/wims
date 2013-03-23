!if $gotcntS > 0
  !set gotcnt=$gotcntS
  !set gotm=$gotmS
  !set gotd=$gotdS
  !set gott=$gottS
!endif

!if $gotcnt=0
 !changeto lang/welcome-S.phtml.$lang
!endif

$wims_name_sheet

<ul class="wims_home_result_list wims_sheet">
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 <li class="wims_home_result_list">
 !href module=adm/sheet&job=read&sh=$search_lang/$m_ $t_
, $d_
</li>
!next i
</ul>
