#! /bin/sh
# We use shell script to output oef source file, because
# otherwise the $ sign will be substituted.

sessiond=$w_wims_home/$w_wims_sesdir
oefname=$sessiond/submit.oef

sed 's/\&/\&amp;/g' <$oefname | sed 's/</\&lt;/g;s/>/\&gt;/g'

