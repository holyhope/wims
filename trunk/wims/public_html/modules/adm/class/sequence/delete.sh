#! /bin/sh

outdir=$w_wims_home/log/classes/$w_wims_class/seq
if [ ! -d $outdir ]; then exit; fi
cd $outdir

n=$(($w_seq+1))
rm -f .sequence$w_seq >/dev/null
while [ $n -le $w_seq_cnt ]; do
 mv .sequence$n .sequence$(($n-1)) >/dev/null
 n=$(($n+1))
done

