#! /bin/sh

wimstest/test.sh
lcov --capture --directory src --output-file coverage.info
genhtml coverage.info --output-directory gcovout

test=`xdg-open 2>/dev/null`
if [ "$test" ]; then
  xdg-open gcovout/index.html ;
  exit
fi

test=`open 2>/dev/null`
if [ !"$test" ]; then
  open gcovout/index.html;
  exit
fi

