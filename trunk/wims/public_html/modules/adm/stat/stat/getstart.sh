#! /bin/sh

if [ -z "$w_stat_module" ]; then w_stat_module=00access.act; fi
awk '{print $1; exit}' $w_wims_home/log/account/$w_stat_module

