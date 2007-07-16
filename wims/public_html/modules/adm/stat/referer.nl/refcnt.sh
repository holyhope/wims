#! /bin/sh

if [ -z "$w_type" ]; then exit; fi
cd ../log/referer

site_start=19980101
site_end=`date '+%Y%m%d'`

start=$w_date1
end=$w_date2
if [ "$start" -lt $site_start ]; then start=$site_start; fi
if [ -z "$end" ]; then end=$site_end; fi
if [ "$end" -gt $site_end ]; then end=$site_end; fi

awk 'BEGIN {a=0}; $1<='$end' && $1>='$start' {a=a+$2}; END {print a}' refauto.cnt

if [ -z "$w_key" ]; then
awk '$1<='$end' && $1>='$start' {print $2"	- "$3}' ref$w_type.cnt \
	| sort -k 2 \
	| awk 'BEGIN {a=0;b=""}; $3 == b {a=a+$1};
	$3 != b {if(a>0) print a" "b; b=$3;a=$1};
	END {print a" "b}' | sort -nr | head -$w_reflim
else
awk 'BEGIN {IGNORECASE=1};
	$1<='$end' && $1>='$start' {if(match($3,"'$w_key'")>0) print $2"	- "$3}' ref$w_type.cnt \
	| sort -k 2 \
	| awk 'BEGIN {a=0;b=""}; $3 == b {a=a+$1}; \
	$3 != b {if(a>0) print a" "b; b=$3;a=$1};
	END {print a" "b}' | sort -nr | head -$w_reflim
fi


