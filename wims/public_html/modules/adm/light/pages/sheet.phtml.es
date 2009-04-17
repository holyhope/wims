!!INDEX
!let module_author	=XIAO Gang
!let module_address	=xiao@unice.fr
!let module_title	=HOJAS DE TRABAJO
!let module_description	=Presentación de las hojas de trabajo para los estudiantes
!let module_version	=2.22
!let module_wims_version=2.22
!let module_language	=es
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=E1 E2 E3 E4 E5 E6 H1 H2 H3 H4 H5 H6 U1 U2 U3 U4 G R

!! e.g. algebra, analysis, geometry, etc.
!let module_domain	=

!! For search engines; anything you like.
!let module_keywords	=

!let module_translator	=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es

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
<hr> <p><h1>Hoja de trabajo número $parm1<br>$sheet_title</h1></center> <p>
$sheet_desc<p>

!if $sheet_expiration!=$empty and $sheet_active=1
 !set expday=!char 7,8 of $sheet_expiration
 !set expmon=!char 5,6 of $sheet_expiration
 !set expyear=!char 1 to 4 of $sheet_expiration
 !set months=enero,febrero,marzo,abril,mayo,junio,julio,agosto,septiembre,octubre,noviembre,diciembre
 !set expmon=!item $expmon of $months
 Puede trabajar en esta hoja de trabajo hasta el $expday $expmon $expyear.
 <p>
!endif

!if $sheet_active=2
 <blink><b><font color=red>Atención</font></b></blink>
 Esta hoja de trabajo ha expirado. Todavía puede trabajar con ella,
 pero no se tomarán en cuenta las puntuaciones.
 <p>
!endif

!if $sheet_active=$empty
 !set n=0
!else
 !set n=!recordcnt wimshome/log/classes/$wims_class/sheets/.sheet$parm1
!endif

!if $n=0
 !if $sheet_active=$empty
  No está  autorizado a consultar el contenido de esta hoja por el momento.
  Por favor contacte con su profesor.
 !else
  ¡La hoja de trabajo está vacía! No tiene asignado nada en ella. Posiblemente
  se trate de un error del profesor.
 !endif
!else
 Trabajo asignado en esta hoja de trabajo: (el registro de puntuaciones está
 !set dd=!getscorestatus sheet=$parm1
 !if $dd=yes
  !if $wims_scorereg!=suspend
   abierto, pero puede
   !href cmd=resume&parm5=suspend anularlo
.)
  !else
   suspendido por usted mismo.
   !href cmd=resume&parm5=reopen Reactivarlo
.)
  !endif
 !else
  cerrado para su conexión.)
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
   <small>$[$got] de $[$require] puntos obtenidos, calidad
   $[$mean]/10.</small>
  !endif
 !next i
 </ul>
!endif

!if $wims_user=supervisor
<p>
!href module=adm/class/sheet&sheet=$parm1 Página de administración de la hoja de trabajo
 (para el profesor).
!endif
<p>
!tail

