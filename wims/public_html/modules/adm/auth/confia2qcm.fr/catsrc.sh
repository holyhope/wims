#! /bin/sh

rm -f $w_wims_home/sessions/$w_wims_session/tempsrc
cat <<@ >$w_wims_home/sessions/$w_wims_session/tempsrc
$w_fichsrc
@
