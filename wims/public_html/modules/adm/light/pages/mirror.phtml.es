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
!let module_title	=Réplicas públicas
!let module_description	=lista de sitios WIMS accesibles al público.
!let module_version	=2.08
!let module_wims_version=2.08

!! This is the Spanish template file
!let module_language	=es

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

!let module_translator	=Juan Rafael Fernández García
!let module_translator_address=juanrafael.fernandez@hispalinux.es

!!INDEXEND

!!<html><head>
!!$wims_html_header
!!</head>
!!<body $wims_htmlbody>
!header1
<h1 class="wims_title">
<font size=+2>W</font>WW
<font size=+2>I</font>nteractive
<font size=+2>M</font>ultipurpose<br>
<font size=+2>S</font>erver
<font size="-1">en <a href="/">$httpd_HTTP_HOST</a></font> <br>
$module_title</h1> <p>

!set mir=wimshome/public_html/html/mirrors.es
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
 Este sitio WIMS no parece mantener una lista de réplicas. Lo sentimos.
 <p>
!else
 Aquí están los otros sitios WIMS que se sabe que están abiertos al
 público general. Si usa normalmente WIMS en su trabajo, le sugerimos
 que añada a sus Favoritos al menos una de estas direcciones.
 <p>$table_header
 $table_hdtr<th>Sitio</th><th>Localización</th><th>País</th><th>Idiomas<br>en que funciona</th><th>Comentarios</th></tr>
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
   <img src="gifs/$L_.gif" alt="$L_.gif" height="16">
  !next L_
!!  <td align="center">!mailurl n$e_ $m_\nWIMS site
  </td><td>$r_&nbsp;</td></tr>
 !next i_
 $table_end <p>
!endif

:end
Si tiene una instalación WIMS y quiere que aparezca en este listado,
por favor
!mailurl wimsdev@cru.fr escríbame\
wims mirror
.
<p>
WIMS se puede 
!href module=adm/light&phtml=download.phtml.$lang descargar
 gratuitamente,
y puede instalarse sobre sistemas operativos Linux.
Por favor, lea el archivo <a href="README">README</a>  para obtener más información sobre cómo instalar WIMS.

!tail

