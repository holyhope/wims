
!set n=!recordcnt mirrors.es
!if $n<1
 !exit
!endif

!set n=$[min($n,10)]
 <p><center>
 <table border=2 bgcolor=$wims_ref_bgcolor>
 <caption>Réplicas de WIMS
 <tr><th>Sitio<th>Localización<th>País<th>Idiomas<br>que admite<th>Comentarios
 !for i_=1 to $n
  !set l_=!record $i_ of mirrors.es
  !distribute lines $l_ into u_,t_,C_,l_,m_,e_,r_
  !set l_=!items2words $l_
  !set l_=!words2items $l_
  <tr><td align=center>
  <a href="http://$u_">$u_</a>
  <td align=center>$t_
  <td align=center>$C_
  <td align=center>
  !for L_ in $l_
   <img src=gifs/$L_.gif>
  !next L_
  <td>$r_&nbsp;
 !next i_
 </table></center><p>

