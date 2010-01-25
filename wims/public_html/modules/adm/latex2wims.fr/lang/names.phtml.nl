!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!distribute line Transférer un fichier\
  een nieuw bestand opsturen\
  Kopieer de bestanden naar de server\
  WIMS-doc\
  PDF documentatie\
  Login voor Modtool\
  het latex bestand\
  het css bestand\
  het latex2wims sty bestand\
  Een voorbeeld document maken ?\
  Stap\
  Opgestuurde bestanden\
  Naar de volgende stap\
  U kunt\
  een LaTeX bestand opsturen.\
  U moet\
  Kies het LaTeX bestand\
  opgestuurd op\
  Als er oefeningen zijn, kies dan het werkblad nummer\
  Geef de naam van het document uit uw Modtool account\
  of maak een nieuwe document in uw Modtool account maken\
  U moet eerst een document maken in uw modtool account\
  U moet een echt document selecteren.\
  Uitvoeren\
  Terug naar de vorige stadia.\
  kunt u ook bereiken via\
  Controleer het resultaat\
into name_transfer,name_newtransfer,name_transfer_wims,name_documentation,name_pdf,name_modtool,\
  name_latex,name_css, name_latex2wims,name_example,name_step,name_filet,name_newstep,\
  name_youmust,name_atleast,name_youcan,name_selectmain,name_transferdate,\
  name_sheet,name_namedocument,name_newmodule,name_createfirst,name_select_warning,\
  name_exec,name_comeback,name_gotomodtool,name_test
  
  
!set name_warning=!nosubst de bestanden van het document  <tt $stylett>$document</tt>\
    worden gewist en vervangen door de nieuwe.

!set name_select_example=Om verder te gaan, kunt U de drie bestanden ophalen\
(latex code [*.tex], latex style [*.sty] en een html [*.css]) 

!set choix=Kies
!exit


:1
 maakt van een LaTeX bestand een WIMS document binnen Modtool.
En is alleen te gebruiken door docenten met een modtool account.
<p>
Voor een goed resultaat moet ook een css bestand worden gebruikt.
Lees hiervoor eerst deze 

!exit
:2
Om een
!mailurl $wims_site_manager modtool account aan te vragen \
WIMS new developer
 als WIMS module ontwikkelaar.

!exit
:3
maakt van een LaTeX bestand een WIMS document binnen Modtool.
<br>En is alleen te gebruiken door docenten met een modtool account.
<p>
Voor een goed resultaat moet ook een css bestand worden gebruikt.
Leest hiervoor eerst deze 

!exit
:4 
de bestanden van het document <tt $stylett>$document</tt>
    worden gewist en vervangen door de nieuwe.
   <p>Uitvoeren ? 
!exit
