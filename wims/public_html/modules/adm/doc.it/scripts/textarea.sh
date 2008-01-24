#! /bin/sh

content=`sed 's/\&/\&amp;/g;s/</\&lt;/g' <$w_wims_home/$w_wims_sesdir/doc.src`
cat <<@
<textarea cols=70 rows=20 wrap
name=wims_deposit>$content</textarea>
@

rm -f $w_wims_home/$w_wims_sesdir/user-deposit >/dev/null

