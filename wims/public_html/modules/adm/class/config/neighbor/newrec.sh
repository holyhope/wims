#! /bin/sh
#
# Recense new resources on the neighbor class.
#
# Output line: resource_type resource_name type
# type=1: new type=2: exist but different

mdir=`pwd`

classdir=$w_wims_home/log/classes
cd $w_wims_home/log/classes/$w_wims_class
cldir=`pwd`
cd $classdir/$w_nei
ndir=`pwd`
cd $cldir

test=`cat $classdir/$w_nei/.motd 2>/dev/null | grep -c .`
if [ $test -gt 0 ]; then
 if [ ! -e .motd ]; then
  echo "motd -- 1"
 else
  diff -bBq $classdir/$w_nei/.motd .motd >/dev/null || echo "motd -- 2"
 fi 
fi

if [ $w_it_exocnt -gt 0 ]; then
 cd $ndir/src
 test=`ls *.oef`
 cd $cldir
 for i in $test
 do
  if [ ! -e src/$i ]; then
   echo "exo $i 1"
  else
   diff -bBq $classdir/$w_nei/src/$i src/$i >/dev/null || echo "exo $i 2"
  fi
 done
fi

if [ $w_it_sheetcnt -gt 0 ]; then
 cd $ndir/sheets
 test=`ls .sheet[0-9]*`
 cd $cldir
 for i in $test
 do
  t=1
  this=`ls sheets/.sheet[0-9]* 2>/dev/null`
  for k in $this
  do
   if diff -bBq $classdir/$w_nei/sheets/$i $k >/dev/null; then t=0; fi
  done
  if [ $t = 1 ]; then
   j=`echo $i | tr -d '[\.sheet]'`
   echo "sheet $j 1"
  fi
 done
fi

if [ $w_it_examcnt -gt 0 ]; then
 cd $ndir/exams
 test=`ls .exam[0-9]*`
 cd $cldir
 for i in $test
 do
  t=1
  this=`ls -d exams/.exam[0-9]* 2>/dev/null`
  for k in $this
  do
   if diff -bBq $classdir/$w_nei/exams/$i $k >/dev/null; then t=0; fi
  done
  if [ $t = 1 ]; then
   j=`echo $i | tr -d '[\.exam]'`
   echo "exam $j 1"
  fi
 done
fi

if [ $w_it_doccnt -gt 0 ]; then
 cd $classdir/$w_nei/doc
 test=`echo c*`
 cd $cldir
 for i in $test
 do
  t=1
  this=`ls -d doc/c[0-9]* 2>/dev/null`
  for k in $this
  do
   if diff -bBqr $classdir/$w_nei/doc/$i $k >/dev/null; then t=0; fi
  done
  if [ $t = 1 ]; then
   j=`echo $i | tr -d '[c]'`
   echo "doc $j 1"
  fi
 done
fi

