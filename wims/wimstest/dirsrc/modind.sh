#! /bin/sh

mkdir -p wimstest/tmp/modind/site/lists/
mkdir -p wimstest/tmp/modind/sheet/
#dicsort_separator dicsort_grouping
#export w_translator_unknown w_dictionary w_translator_switch translator_input
export mlist="E1/geometry/oefsquare.fr
E1/number/oefcalcul1.fr
E1/number/oefcalcul2.fr
E1/number/oefnumber.fr
E1/number/oefnumber0.fr"

export slist="fr/U2/1134/sheet1
fr/U2/1134/sheet2
fr/U2/1134/sheet3
fr/U2/1134/sheet4
fr/U2/1134/sheet5"

export modind_sheetdir=public_html/bases/sheet
export modind_outdir=wimstest/tmp/modind/site
export modind_sheetoutdir=wimstest/tmp/modind/sheet

src/Misc/modind
