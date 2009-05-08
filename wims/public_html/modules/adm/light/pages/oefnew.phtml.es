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
!let module_title	=Latest additions or modifications of OEF exercises
!let module_description	=list of new OEF recently added to this site.
!let module_version	=1.20
!let module_wims_version=1.50
!let module_language	=en
!let module_copyright	=&copy; 1998 (<a href=COPYING>GNU GPL</a>)
!let module_category	=adm
!let module_level	=H1 H2 H3 H4 H5 H6 U1 U2 U3 U4 G R
!let module_domain	=
!let module_keywords	=
!readproc colors-adm

!!INDEXEND

!!<HTML><HEAD>
!!$wims_html_header
!!</HEAD>
!!<BODY $wims_htmlbody>
!!!headmenu
!header1
<h1 class="wims_title">
<font color=red>W</font>WW
<font color=red>I</font>nteractive
<font color=red>M</font>athematics
<font color=red>S</font>erver<br>
<font size="-1">at <a href="/">$httpd_HTTP_HOST</a></font> </h1>

!set llimit=100
!set list=!mexec getnewoef.sh
!set n=!linecnt $list
!if $n<=0
 !goto end
!endif
!set tot=!line 1 of $list
The $[$n-1] most recent modifications / additions within $tot OEF exercice
of the site<br>
(except those in newly added modules.)
</center>

<p><center><table border=0 cellspacing=1 bgcolor="$table_bgcolor">
<tr><th>Module<th>Exercice

!for i=2 to $n
 !set li=!line $i of $list
 !distribute items $li into m,o
 !set mname=!module title $m
 !exchange table_color1,table_color2
 <tr bgcolor="$table_color2">
 <td>
 !href module=$m $mname
 <td>
 !href module=$m&cmd=new&exo=$o $o
!next i
</table></center> <p>
:end
!tail

