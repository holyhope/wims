#! /bin/sh

wims_home=`pwd`;
export w_dictionary=$wims_home/wimstest/dic.sorted
export w_suffix_dictionary=

export wims_exec_parm="titi tutu xxxx"

$wims_home/src/Misc/translator
echo "\n"

export w_translator_unknown=leave
$wims_home/src/Misc/translator
echo "\n"
