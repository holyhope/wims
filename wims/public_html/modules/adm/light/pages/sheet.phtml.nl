!!INDEX
!let module_author	=XIAO Gang
!let module_address	=xiao@unice.fr
!let module_title	=WERKBLADEN
!let module_description	=Werkblad presentatie voor leerlingen
!let module_version	=2.00
!let module_wims_version=2.00
!let module_language	=nl
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=E1 E2 E3 E4 E5 E6 H1 H2 H3 H4 H5 H6 U1 U2 U3 U4 G R

!! e.g. algebra, analysis, geometry, etc.
!let module_domain	=

!! For search engines; anything you like.
!let module_keywords	=

!!INDEXEND

!if $parm5=suspend
 !set wims_scorereg=suspend
!endif
!if $parm5=reopen
 !set wims_scorereg=
!endif

<html><head>
$wims_html_header
</head>
<body $wims_htmlbody>
!headmenu

!set sheet=!record $parm1 of wimshome/log/classes/$wims_class/sheets/.sheets
!distribute lines $sheet into sheet_active,sheet_expiration,sheet_title,sheet_desc
!if $wims_user != supervisor and $sheet_active<1
 !distribute items $ into sheet_active,sheet_expiration,sheet_title,sheet_desc
!endif
!set requires=!getscorerequire sheet=$parm1
!set scores=!getscore sheet=$parm1
!set means=!getscoremean sheet=$parm1

<hr width=1>
<center><h3>$wims_classname, $wims_institutionname</h3>
<hr> <p><h1>Work sheet #$parm1<br>$sheet_title</h1></center> <p>
$sheet_desc<p>

!if $sheet_expiration!=$empty and $sheet_active=1
 !set expday=!char 7,8 of $sheet_expiration
 !set expmon=!char 5,6 of $sheet_expiration
 !set expyear=!char 1 to 4 of $sheet_expiration
 !set months=Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec
 !set expmon=!item $expmon of $months
 U kunt aan dit werkblad werken tot $expday $expmon $expyear.
 <p>
!endif

!if $sheet_active=2
 <blink><b><font color=red>Waarschuwing</font></b></blink>
 Dit werkblad is verlopen. U kunt er nog wel aan werken, maar de cijfers worden niet
 meer verwerkt.
 <p>
!endif

!if $sheet_active=$empty
 !set n=0
!else
 !set n=!recordcnt wimshome/log/classes/$wims_class/sheets/.sheet$parm1
!endif

!if $n=0
 !if $sheet_active=$empty
  You have no right to consult the content of this sheet for the time being.
  Please contact your supervisor.
 !else
  The sheet is empty! Nothing is assigned for you in it. Possibly an 
  error in the manipulation by your supervisor.
 !endif
!else
 Assigned works in this sheet: (Score registration is
 !set dd=!getscorestatus sheet=$parm1
 !if $dd=yes
  !if $wims_scorereg!=suspend
   open, but you can
   !href cmd=resume&parm5=suspend suspend it
.)
  !else
   suspended by yourself.
   !href cmd=resume&parm5=reopen Reactivate it
.)
  !endif
 !else
  closed for your connection.)
 !endif
 <p><ul>
 !for i=1 to $n
  !set ex=!record $i of wimshome/log/classes/$wims_class/sheets/.sheet$parm1
  !distribute lines $ex into di,pa,require,we,ti,de
  !set got=!word $i of $scores
  !set mean=!word $i of $means
  <li><p>$i. 
  !href module=$di&cmd=new&worksheet=$parm1&$pa $ti
, $de
  !if $require>0
   <small>$[$got] out of $[$require] points obtained, quality
   $[$mean]/10.</small>
  !endif
 !next i
 </ul>
!endif

!if $wims_user=supervisor
<p>
!href module=adm/class/sheet&sheet=$parm1 Sheet management page
 (for supervisor).
!endif
<p>
!tail

