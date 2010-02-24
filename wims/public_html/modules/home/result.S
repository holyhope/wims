
!if $gotcnt=0
 <p>
 !changeto wimshome/public_html/bases/sheet/$lang/welcome.phtml
!endif

<ul  class="wims_home_result_list">
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 <li class="wims_home_result_list">
 !href module=adm/sheet&job=read&sh=$search_lang/$m_ $t_
, $d_
</li>
!next i
</ul> <p>

