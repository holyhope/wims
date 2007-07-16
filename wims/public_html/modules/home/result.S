
!if $gotcnt=0
 <p>
 !changeto wimshome/public_html/bases/sheet/$lang/welcome.phtml
!endif

<ul>
!for i=1 to $gotcnt
 !set m_=!line $i of $gotm
 !set t_=!line $i of $gott
 !set d_=!line $i of $gotd
 <li>
 !href module=adm/sheet&job=read&sh=$lang/$m_ $t_
, $d_
!next i
</ul> <p>

