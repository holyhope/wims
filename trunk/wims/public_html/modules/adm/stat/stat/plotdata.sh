#! /bin/sh

if [ -z "$w_stat_module" ]; then w_stat_module=00access.act; fi

actfile=$w_wims_home/log/account/$w_stat_module
site_start=19980101
site_end=`date '+%Y%m%d'`

start=$w_date1
end=$w_date2
step=$w_step
if [ "$start" -lt $site_start ]; then start=$site_start; fi
if [ -z "$end" ]; then end=$site_end; fi
if [ "$end" -gt $site_end ]; then end=$site_end; fi
 f=`awk '$1>='$start' && $1<='$end' {print}' $actfile`
if [ ! -z "$step" ]; then 
 echo "$f" | awk 'BEGIN {a=0;s=0;o=0};
	a<'$step' {a++;s=s+$'$w_plot_type'};
	a>='$step' {print $1" "s/a;o=s/a;a=0;s=0}; 
	END {if(a>0) print $1" "((s+o*('$step'-a))/'$step')}' | uniq
else
 echo "$f" | awk '$1>='$start' && $1 <='$end' {print $1" "$2}'
fi

