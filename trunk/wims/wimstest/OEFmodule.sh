#! /bin/sh

FILE="wimstest/ALLOEFHTML/index.html"

if [ $1 ]; then
 for a in $(seq $#); do file=$1;
  echo "$file"
  bin/oefcompile test $file
  shift
 done
else
  bin/oefcompile test $fi
fi

wimstest/diff2html.sh

test=`xdg-open 2>/dev/null`
if [ "$test" ]; then
  xdg-open $FILE ;
  exit
fi

test=`open 2>/dev/null`
if [ !"$test" ]; then
  open $FILE;
  exit
fi

