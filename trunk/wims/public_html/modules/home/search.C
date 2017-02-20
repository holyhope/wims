!!##class
basedir=bases/class
!if $srch!=$empty
 suffix_dictionary=
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
 !advance gotcnt
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
  !else
   gotm=$gotm $l_
 !endif
!next i
!if $lastmod!=$empty
 gotm=$gotm $lastmod
 gotw=$gotw $weight
 !advance gotcnt
!endif

gotm=!words2lines $gotm
gotm=!line 1 to $gotlim2 of $gotm
gotcnt=!linecnt $gotm

translator_switch=leaveline
dictionary=$basedir/title
gott=!exec translator $gotm
dictionary=$basedir/description
gotd=!exec translator $gotm
dictionary=$basedir/information
gotiC=!exec translator $gotm

!if $gotcnt>0 and / notin $gotm
 dictionary=$basedir/addr
 gotm=!exec translator $gotm
!endif
