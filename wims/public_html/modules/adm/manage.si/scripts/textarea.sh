#! /bin/sh

content=`cat $w_wims_home/$w_file | sed 's/\&/\&amp;/g;s/</\&lt;/g'`
cat <<@
<textarea rows=25 cols=70 nowrap style="width: 100%; white-space: pre"
$w_textarea_ro name=wims_deposit>$content</textarea>
@

