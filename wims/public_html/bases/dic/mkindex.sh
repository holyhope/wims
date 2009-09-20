#! /bin/sh

cd `dirname $0`

for i in ??
do
 cd $i
 rm -f .cnt.$i* 2>/dev/null
 for j in $i.*
 do
  k=`echo $j | sed 's/^'$i'.//'`
  echo "cnt$k="`grep -c . $j` >>.cnt.$i
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

