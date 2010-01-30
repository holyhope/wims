
l_en=Engels
l_fr=Frans
l_es=Spaans
l_it=Italiaans
l_cn=Chinees
l_nl=Nederlands
l_si=Sloveens
l_tw=Chinees traditioneel (big5)
l_de=Duits
l_ca=Catalaans
l_pt=Portugees

langname=
!for l in $langlist
 !if $(l_$l)!=$empty
  l=$(l_$l)
 !endif
 langname=!append item $l to $langname
!next l
