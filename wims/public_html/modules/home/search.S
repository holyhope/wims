
!if $srch!=$empty
 suffix_dictionary=
 dictionary=bases/sheet/index/$lang
 translator_unknown=
 sout=!exec translator $srch
 sout=!items2words $sout
 sout=!words2lines $sout
 sout=!translate ? to $ $ in $sout
 sout=!sort lines $sout
 sout=!nonempty lines $sout
 scnt=!linecnt $sout
!else
 scnt=0
!endif

# Limit of shown items
gotlim=50
!distribute item 0,0,, into weight,gotcnt,gotm,gotw,lastmod

!for i=1 to $scnt
 l_=!line $i of $sout
 t_=!wordcnt $l_
 !if $t_=2
  !distribute word $l_ into m_,w_
  !if $m_=$lastmod or $gotcnt>$gotlim
   weight=$[$weight+$w_]
  !else
   !if $lastmod!=$empty
    gotm=$gotm $lastmod
    gotw=$gotw $weight
    !advance gotcnt
   !endif
   lastmod=$m_
   weight=$w_
  !endif
 !endif
!next i
!if $lastmod!=$empty
 gotm=$gotm $lastmod
 gotw=$gotw $weight
 !advance gotcnt
!endif

translator_switch=leaveline
!if $gotcnt=0
 gottype=popular
!else
 gottype=search
 gotw=!words2lines $gotw
 gotm=!words2lines $gotm
 dictionary=bases/sheet/index/weight.$lang
 gotW=!exec translator $gotm
 w_=
 !for i=1 to $gotcnt
  u_=!line $i of $gotw
  v_=!line $i of $gotW
  w_=!append line $[round(100*($u_+1)/($v_+1)^0.7)] to $w_
 !next i
 gotw=!sort reverse numeric lines $w_
 gotm=!line $wims_sort_order of $gotm
!endif

dictionary=bases/sheet/index/title.$lang
gott=!exec translator $gotm
dictionary=bases/sheet/index/description.$lang
gotd=!exec translator $gotm
!if $gotcnt>0 and / notin $gotm
 dictionary=bases/sheet/index/addr.$lang
 gotm=!exec translator $gotm
!endif

