#! /bin/sh

wims_home=`pwd`;

test="123,43.5,23.45665 2"

$wims_home/src/Misc/moneyprint/moneyprint $test
echo "\n"
