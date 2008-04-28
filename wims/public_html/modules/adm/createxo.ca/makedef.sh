#! /bin/sh

sessiond=$w_wims_home/$w_wims_sesdir
oefname=$sessiond/submit.oef
deposit=$sessiond/user-deposit

if [ ! -z "$w_mode" ]; then
 cat $deposit >$oefname 2>/dev/null
else
 cat <<@ | sed 's/&#36;/$/g' >$oefname
\title{$w_oef_title}
$w_header

$w_oef_parms
\statement{$w_oef_statement}

$w_hints
$w_answers
$w_choices
$w_conditions
$w_solutions
@
 cat $oefname >$deposit 2>/dev/null
fi

rm -f $sessiond/submit.def 2>/dev/null
oef2wims_mdef="oefenv"
export oef2wims_mdef
../bin/oef2wims $oefname >$sessiond/oef2wims.out

cd $sessiond
mkdir -p getfile
if [ ! -e getfile/submit.oef ]; then ln -s ../submit.oef getfile; fi

