
!!INDEX
!! Erase the above line to hide your page from wims search engine.
!! Line starting with double exclamations are comment lines.
!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!
!! Indexing definitions. You should modify them according to your case.
!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

!! Put every definition in ONE LINE!!
!let module_author	=XIAO, Gang
!let module_address	=xiao@unice.fr
!let module_title	=Mirrors
!let module_description	=lijst van WIMS mirrors. 
!let module_version	=2.08
!let module_wims_version=2.08

!! This is English template file
!let module_language	=nl

!!Your copyright policy.
!!Your page will be included in wims distribution if the word `GNU'
!! appears in the following definition.
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)

!! Possible categories: exercise, tool, dictionary, course, recreation.
!let module_category	=adm

!! En: elementary school. Hn: high school. Un: undergrad. 
!! G: graduate. R: research.
!! E1,...,E6; H1...,H6; U1,...,U4; G; R
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

<h1 class="wims_title">
<font size=+2>W</font>WW
<font size=+2>I</font>nteractieve
<font size=+2>M</font>ultipurpose
<font size=+2>S</font>erver<br>
<font size="-1">op <a href="/">$httpd_HTTP_HOST</a></font> <br>
$module_title</h1> <p>

!set mir=wimshome/public_html/html/mirrors.nl
!set thissite=!tolower $httpd_SERVER_NAME
!set n=!recordcnt $mir
!set c=
!for i_=1 to $n
 !set m_=!record $i_ of $mir
 !set l_=!line 1 of $m_
 !set l_=!trim $l_
 !set l_=!translate / to $\
$ in $l_
 !set l_=!line 1 of $l_
 !set l_=!lower $l_
 !if $l_!=$thissite
  !set c=!append item $i_ to $c
 !endif
!next i_
!set n=!itemcnt $c
!if $n<1
    Deze WIMS server heeft helaas geen lijst met actieve mirrors geinstalleerd.
 <p>
!else
    Hier is een lijst met WIMS servers die open staan voor publiek.
    Bij regelmatig WIMS gebruik en geen eigen server, is het verstandig een bookmark 
    van deze adressen lijst te maken.
 <p>$table_header
 $table_hdtr<th>Website</th>
 <th>Locatie</th>
 <th>Land</th>
 <th>Ondersteund <br>de talen</th>
 <th>Opmerkingen</th>
 </tr>
 !for i_=1 to $n
  !set j_=!item $i_ of $c
  !set l_=!record $j_ of $mir
  !distribute lines $l_ into u_,t_,C_,l_,m_,e_,r_
  !readproc mirror.proc
  $table_tr<td align="center">
  <a href="$u_">$U_</a></td>
  <td align="center">$t_</td>
  <td align="center">$C_</td>
  <td align="center">
  !for L_ in $l_
   <img src="gifs/$L_.gif" alt="$L_.gif" height=16>
  !next L_
!!  <td align="center">!mailurl n$e_ $m_\nWIMS site
  </td><td>$r_&nbsp;</td></tr>
 !next i_
 $table_end <p>
!endif

:end

Heeft u een WIMS server geinstalleerd op internet en wilt dit adres opgenomen zien in
deze lijst, schrijf een email naar de
!mailurl wimsdev@cru.fr ontwikkelings afdeling\
wims mirror
.
<p>
WIMS is vrije software en kan gratis worden 
!href module=adm/light&phtml=download.phtml.$lang verkregen
en geinstalleerd alle op GNU/Linux systemen.
<p>
Lees het <a href="README">README</a> bestand in de download directory voor 
meer details mbt de installatie.

!tail

