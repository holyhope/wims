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
!let module_title	=Mirror Sites
!let module_description	=lijst van alle bereikbare WIMS servers. 
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

<html><head>
$wims_html_header
</head>
<body $wims_htmlbody>
!headmenu
<center><h1>
<font color=red>W</font>WW
<font color=red>I</font>nteractieve
<font color=red>M</font>ultipurpose
<font color=red>S</font>erver<br>
<font size="-1">op <a href=/>$httpd_HTTP_HOST</a></font> <p>
$module_title</h1></center> <p>

!set mir=wimshome/public_html/html/mirrors.en
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
 This WIMS site does not keep a list of mirror sites. Sorry.
 <p>
!else
 Here are the other WIMS sites known to be open to the general public.
 If you use WIMS regularly in your work, we suggest
 that you bookmark at least some of these addresses, so that if your favorite
 site becomes temporarily unavailable, you won't see your work disrupted.
 <p>$table_header
 $table_hdtr<th>Site</th>
 <th>Location</th>
 <th>Country</th>
 <th>Supported<br>languages</th>
 <th>Comments</th>
 </tr>
 !for i_=1 to $n
  !set j_=!item $i_ of $c
  !set l_=!record $j_ of $mir
  !distribute lines $l_ into u_,t_,C_,l_,m_,e_,r_
  !readproc mirror.proc
  $table_tr<td align=center>
  <a href="$u_">$U_</a></td>
  <td align=center>$t_</td>
  <td align=center>$C_</td>
  <td align=center>
  !for L_ in $l_
   <img src=gifs/$L_.gif height=16>
  !next L_
!!  <td align=center>!mailurl n$e_ $m_\nWIMS site
  </td><td>$r_&nbsp;</td></tr>
 !next i_
 $table_end <p>
!endif

:end
Heeft U een WIMS server geinstalleerd op internet, en wilt Uw adres opgenomen in
deze lijst, 
!mailurl xiao@unice.fr schrijf me\
wims mirror
.
<p>
WIMS is software die vrij beschikbaar is, en kan worden 
<a href="http://wims.unice.fr/download/wims/">gedownload</a>,
en geinstalleerd op GNU/LinuX systemen.
<p>
Lees het README bestand in de download directory voor meer details m.b.t de installatie.


!tail

