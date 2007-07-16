#! /bin/sh

g=`sed 's/\&/\&amp;/g;s/</\&lt;/g' <$w_wims_home/log/classes/$w_wims_class/.grades`

echo "<textarea cols=70 rows=15 name=wims_deposit>$g</textarea>"

