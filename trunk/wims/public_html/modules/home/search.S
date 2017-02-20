!!##sheet
basedir=bases/sheet/index
!if $srch!=$empty
 suffix_dictionary=bases/sys/suffix.$search_lang
 dictionary=$basedir/$search_lang
 translator_unknown=
 !read search.common
!else
 scnt=0
!endif

# Limit of shown items
gotlim=1000
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
 dictionary=$basedir/weight.$search_lang
 gotW=!exec translator $gotm
 w_=
 !for i=1 to $gotcnt
  u_=!line $i of $gotw
  v_=!line $i of $gotW
  w_=!append line $[round(100*($u_+1)/($v_+1)^0.7)] to $w_
 !next i
 gotw=!sort reverse numeric lines $w_
 gotm=!line $wims_sort_order of $gotm
 gotm=!line 1 to $gotlim2 of $gotm
 gotcnt=!linecnt $gotm
!endif

dictionary=$basedir/title.$search_lang
gott=!exec translator $gotm
translator_unknown1=$translator_unknown
translator_unknown=leave

dictionary=$basedir/description.$search_lang
gotd=!exec translator $gotm
dictionary=$basedir/information.$search_lang
gotiS=!exec translator $gotm

!! by precaution
translator_unknown=$translator_unknown1

gotm_=!replace internal $ $ by $\
$ in $gotm

!if $gotcnt>0 and / notin $gotm
 dictionary=$basedir/addr.$search_lang
 gotm=!exec translator $gotm
!endif
