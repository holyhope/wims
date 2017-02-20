#! /bin/sh

wims_home=`pwd`;

test="123,43.5,23.45665 2
0.1,17,123.4,123.99765
2.1,4.123,5  2
2.1,4.123,5  4
2.1,4.123,5
1.23456e+06,1.23456*10^6,0.01234e-23 3"

for a in $test; do
  $wims_home/src/Misc/moneyprint/moneyprint $a;
done
