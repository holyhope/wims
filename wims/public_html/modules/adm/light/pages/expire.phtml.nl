!!INDEX
!let module_author	=XIAO Gang
!let module_address	=xiao@unice.fr
!let module_title	=KLASSE EINDDATUM
!let module_description	=Verander de uiterste-gebruiksdatum van Uw klas
!let module_version	=1.10
!let module_wims_version=1.50
!let module_language	=nl
!let module_copyright	=&copy; 1999 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=E1 E2 E3 E4 E5 E6 H1 H2 H3 H4 H5 H6 U1 U2 U3 U4 G R

!! e.g. algebra, analysis, geometry, etc.
!let module_domain	=

!! For search engines; anything you like.
!let module_keywords	=


!!INDEXEND

!!<html><head>
!!$wims_html_header
!!</head>
!!<body $wims_htmlbody>
!header1

!if $wims_user!=supervisor
 <p>Nee, deze pagina is alleen beschikbaar voor de supervisor.
 !tail
 !exit
!endif

<hr width=1>
<center><h3>$wims_classname, $wims_institutionname</h3>
<p><h1>Expiration date of the class</h1></center> <p>
!set months=Januari,Februari,Maart,April,Mei,Juni,Juli,Augustus,September,October,November,December
!set today=!char 1 to 8 of $wims_now
!set thisyear=!char 1 to 4 of $today
!set thismonth=!char 5,6 of $today
!set thisday=!char 7,8 of $today
!if $parm1=$empty
 :old
 !defread wimshome/log/classes/$wims_class/.def
 !set d_=!char 7,8 of $class_expiration
 !set m_=!char 5,6 of $class_expiration
 !set y_=!char 1 to 4 of $class_expiration
!else
 !set y_=!char -4 to -1 of 0000$[$parm1]
 !set m_=!char -2,-1 of 00$[$parm2]
 !set d_=!char -2,-1 of 00$[$parm3]
 !ifval NaN isin $y_$m_$d_ or \
	$y_$m_$d_>$thisyear$thismonth$thisday+10000 or\
	$y_$m_$d_<$thisyear$thismonth$thisday or\
	$m_<1 or $m_>12 or $d_<1 or $d_>31
  !goto old
 !endif
 !defread wimshome/log/classes/$wims_class/.def
 !writefile wimshome/log/classes/$wims_class/.def !set class_password=$class_password\
!set class_supervisor=$class_supervisor\
!set class_description=$class_description\
!set class_institution=$class_institution\
!set class_email=$class_email\
!set class_lang=$class_lang\
!set class_creation=$class_creation\
!set class_expiration=$y_$m_$d_\
!set class_limit=$class_limit\
!set class_level=$class_level\
!set class_defined=yes
 !defread wimshome/log/classes/$wims_class/.def
 !goto old
!endif

Huidige einddatum van de klas:
!item $m_ of $months
 $d_, $y_.

!form reply
Nieuwe einddatum van de klas:
!set parm2=$[$m_]
!formselect parm2 from 1 to 12 prompt $months
 <input size=2 maxlength=2 name=parm3 value="$d_">,
!set parm1=$y_
!formselect parm1 list $thisyear,$[$thisyear+1]
. <p><center>
<input type=submit value="$wims_name_tosave">
</center></form>
<p>Een einddatum gesteld op vandaag sluit deze klas. (effectief van af morgen).
<p><b>Attentie.</b>
 De geldigheids/houdbaarheids duur van een klas kan niet langer zijn dan 1 jaar
(van af morgen).
!tail

