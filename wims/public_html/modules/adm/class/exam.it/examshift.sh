#! /bin/sh

outdir=$w_wims_home/log/classes/$w_wims_class
if [ ! -d $outdir/exams ]; then exit; fi
cd $outdir/exams

n=$(($w_exam+1))
rm -f .exam$w_exam >/dev/null
while [ $n -le $w_scnt ]; do
 mv .exam$n .exam$(($n-1)) >/dev/null
 n=$(($n+1))
done

