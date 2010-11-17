#! /bin/sh

content=`sed 's/\&/\&amp;/g;s/</\&lt;/g' <$w_wims_home/$w_wims_sesdir/doc.src`
cat <<@
<textarea cols="70" rows="20" wrap="off"
name="wims_deposit" id="wims_deposit_id">$content</textarea>
@

rm -f $w_wims_home/$w_wims_sesdir/user-deposit >/dev/null

