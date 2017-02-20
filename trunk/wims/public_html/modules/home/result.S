!if $gotcntS > 0
  !set gotcnt=$gotcntS
  !set gotm=$gotmS
  !set gotd=$gotdS
  !set gott=$gottS
!endif

!default gotcntS=0
!if $[$gotcntS + $gotcnt]=0
 !changeto lang/welcome-S.phtml.$lang
!endif

<ul class="wims_home_result_list wims_sheet">
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 !set i_=!line $i of $gotiS
 !set n_=!line $i of $gotm_
 !if $i_=$n_ or $i_ issametext
   !set i_=$d_
 !endif
 !if $i_=$empty
  !set i_=!lookup $n_ in wimshome/public_html/$basedir/information.$search_lang
 !endif
 <li class="wims_home_result_list">
 $ii_
 !href module=adm/sheet&job=read&sh=$search_lang/$m_ $t_
 !if $i_ != $empty
, $i_
 !else
.
!endif
</li>
!next i
</ul>
