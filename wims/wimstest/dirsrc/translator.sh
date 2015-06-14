#! /bin/sh

wims_home=`pwd`;
wims_dirtest="$wims_home/wimstest/dirtest";

export w_dictionary=$wims_dirtest/dic.sorted
export w_suffix_dictionary=
export wims_exec_parm="titi tutu xxxx"
$wims_home/src/Misc/translator
export w_translator_unknown=leave

$wims_home/src/Misc/translator
echo ""

