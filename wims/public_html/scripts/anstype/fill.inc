!default wims_fill_option=$(replyoption$i)
!set inputsize=!translate x to , in $inputsize
!set inputsize=!items2words $inputsize
!distribute words $inputsize into sizeh,sizev,sizei,sizej
!bound sizev between integer 5 and 500 default 20
!bound sizeh between integer 5 and 1000 default 80
!bound sizei between integer 1 and 100 default $
!default fill_sx=$sizeh
!default fill_sy=$sizev
!set input_rg=!rows2lines $(replygood$i)
!set input_1=!word 1 of $input_rg
!if $input_1=?analyze
 !set input_rg=!line 2 to -1 of $input_rg
!endif
!set input_rg=!translate internal | to $\
$ in $input_rg
!set input_1=!line 1 of $input_rg
!set n=!itemcnt $input_1
!default sizei=$n
!bound sizej between integer 1 and $sizei default 1
!set oef_answer_option$i=$sizeh,$sizev,$sizei,$[ceil($sizei/$sizej)]
!if $fillstarts=$empty
 !set filltotal=$sizei
 !set fillstarts=0
 !reset fillvert fillcutpoints
!else
 !set filltotal=$[$filltotal+$sizei]
!endif
!set fillstarts=$fillstarts,$filltotal
!set fillvert=!append item $sizej to $fillvert
!set fillcutpoints=!append item $[ceil($sizei/$sizej)] to $fillcutpoints
!set input_rg=!nonempty lines $input_rg
!if $(replytype$i)=dragfill
 !set g_=!line 1 of $input_rg
 !set n=!linecnt $input_rg
 !for t_=2 to $n
  !set l_=!line $t_ of $input_rg
  !set l_=!listcomplement $g_ in $l_
  !if $l_!=$empty
   !set g_=$g_,$l_
  !endif
 !next t_
 !!set input_rg=!listuniq $g_
 !set input_rg=$g_
!else
 !if keeporder notwordof $wims_fill_option
   !set input_rg=!lines2items $input_rg
 !else
 !!check the good answer is in the list, else add it
   !set input_rg2=!lines2items $input_rg
   !set input_rg=!line 2 to -1 of $input_rg
   !set l_=!listcomplement $input_rg in $input_rg2
   !if $l_!=$empty
     !set input_rg=$l_,$input_rg
   !endif
 !endif
!endif
!set wims_fill_list=!append item $input_rg to $wims_fill_list
!set dynapi_fill_fields=!append item $i to $dynapi_fill_fields

!if $wims_read_parm=noshow
 !exit
!endif

!default fillcnt=0
!increase fillcnt
!if $wims_read_parm!=noprompt
 <tr><td>$(replyname$i)</td><td>
!endif

!set sup1=&nbsp;<sup>
!if $sizev>=20
 !set sup1=<sup>$sup1
 !if $sizev>=30
  !set sup1=<sup>$sup1
  !if $sizev>=40
   !set sup1=<sup>$sup1
   !if $sizev>=50
    !set sup1=<sup>$sup1
   !endif
  !endif
 !endif
!endif
!set sup2=!replace <sup> by </sup> in $sup1
!set sup2=!replace &nbsp; by $ in $sup2
!set sup1=
!set sup2=
!set vertical=text-top
!set fill_namelist=!append item $fillcnt to $fill_namelist
$sup1<img style="width:1px; height:$[$fill_sy+4]px;vertical-align:$vertical;" src="gifs/transparent.gif" alt="transparent" /><a id="fill$fillcnt">
<img style="width:$[ceil($sizei/$sizej)*$fill_sx]px;height:$[($fill_sy*$sizej)+4]px;vertical-align:$vertical;"
  src="gifs/transparent.gif" alt="transparent" /></a>$sup2
<input type="hidden" name="reply$i" value="" />
!reset inputsize

!if $wims_read_parm!=noprompt
 </td></tr>
!endif
