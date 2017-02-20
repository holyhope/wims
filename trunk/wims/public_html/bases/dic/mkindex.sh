#! /bin/sh

cd `dirname $0`

for i in ??
do
 cd $i
 rm -f .cnt.$i* 2>/dev/null
 for j in $i.*
 do
  k=`echo $j | sed 's/^'$i'.//'`
  if [ -e $i.$k ] ; then ## $k != *
   echo "cnt$k="`grep -c . $j` >>.cnt.$i
  fi
 done
 if [ $i = fr ]; then
  for f in conj accord; do
   grep -v '#' $f.src > $f
   ../../../../bin/dicsort $f
   mv $f.sorted $f
  done
 fi
 cd ..
done

