#! /bin/sh

content=`sed 's/\&/\&amp;/g;s/</\&lt;/g' 2>/dev/null <$w_wims_home/$w_wims_sesdir/user-deposit`
cat <<@
<textarea cols=70 rows=24 nowrap style="{white-space: pre}" 
name=wims_deposit>$content</textarea>
@

rm -f $w_wims_home/$w_wims_sesdir/user-deposit >/dev/null

