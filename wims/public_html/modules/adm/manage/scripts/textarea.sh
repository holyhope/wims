#! /bin/sh

content=`cat $w_wims_home/$w_file | sed 's/\&/\&amp;/g;s/</\&lt;/g'`
cat <<@
<textarea rows=25 cols=70 wrap="off" style="width: 100%;"
$w_textarea_ro name="wims_deposit">$content</textarea>
@

