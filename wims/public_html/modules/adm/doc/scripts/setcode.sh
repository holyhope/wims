#! /bin/sh

codefile=$w_wims_home/$w_Docdir/$w_doc/.code
echo $w_coder >$codefile
echo $w_coderr >>$codefile
chmod og-rwx $codefile

