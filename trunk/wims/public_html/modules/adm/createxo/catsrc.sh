#! /bin/sh
# We use shell script to output oef source file, because
# otherwise the $ sign will be substituted.

sessiond=$w_wims_home/$w_wims_sesdir
oefname=$sessiond/submit.oef

LC_ALL=C sed 's/\&/\&amp;/g' <$oefname | LC_ALL=C sed 's/</\&lt;/g;s/>/\&gt;/g'
