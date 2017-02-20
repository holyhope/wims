#! /bin/sh

tmpfile=$PWD/$session_dir/stat
modstatfile=$PWD/../bin/modstat
cd ../log/account

site_start=19980101
site_end=`date '+%Y%m%d'`

if [ -z "$w_stat_module" ]; then w_stat_module=00access.act; fi

start=$w_date1
end=$w_date2
if [ "$start" -lt $site_start ]; then start=$site_start; fi
if [ -z "$end" ]; then end=$site_end; fi
if [ "$end" -gt $site_end ]; then end=$site_end; fi

access=`awk 'BEGIN {a=0;b=0;c=0}; $1>='$start' && $1 <='$end'{a=a+$2;b=b+$3;c=c+$4}; END {print a" "b" "c}' $w_stat_module`

echo $access

if [ "$w_modules" != "yes" ]; then exit; fi

rm -f $tmpfile.mod >/dev/null
ll=`ls [EHLUct]* | grep -v 'classes@' | sed 's/\...$//g' | sort | uniq`

export ll start end
$modstatfile >$tmpfile.mod

cat $tmpfile.mod | sort -nr 2>/dev/null | head -n $(($w_max_modules+5))

#rm $tmpfile.mod

