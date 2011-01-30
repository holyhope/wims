!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!distribute lines Beginners mode \
Expert mode\
File mode\
Andere methoden\
Voorbeelden\
Stuur het bestand\
Broncode van de oefening\
Terug naar het menu\
Doorgaan met het maken van de oefening\
Verander een bestaande oefening uit uw klas\
Terug naar het vorige menu.\
Stuur de broncode\
Wissen\
Demonstatie\
Aanpassen\
Test de oefening\
Corrigeer de fout\
Terug naar \
Uw oefening is nu als volgt: \
Hier staan de beschikbare voorbeelden. Kies er &eacute;&eacute;n.\
De module waarin uw oefening tijdelijk is opgenomen.\
into wims_name_normalmode, wims_name_rawmode,wims_name_filemode,wims_name_othermethods,\
  name_model,name_sendfile,name_source,name_menuback,name_continue,name_modify,\
  name_prevstep,name_sendsource,name_clean,name_demo,name_adapt,name_testexo,\
  name_correction,name_backmodule,name_realisation,name_availablemodels,name_temp_module

!set name_normal=!lowercase $wims_name_normalmode
!set name_raw=!lowercase $wims_name_rawmode
!set name_file=!lowercase $wims_name_filemode

!set name_modefile1=U werkt nu in de filemode van Createxo.In deze mode kunt u lokaal geschreven OEF oefeningen opsturen naar de server.\
Beginners kunnen beter
!set name_modefile2=Om online te bewerken kan ook gebruik worden gemaakt van

!set name_chemistry=Exercises for chemistry
!distribute lines Basis oefeningen\
Oefeningen die werken met een data lijst\
Exercises for chemistry\
Games\
into name_first,name_datalist,name_chemistry,name_game

!set name_save=!nosubst hier is de broncode van <font color="red"><b>$oef_title</b></font>,\
in OEF formaat (Open Exercice Format).\
 Het kan via kopieren tussen de twee regels en plakken op uw eigen pc worden bewaard.

!distribute lines Aantal parameters\
  Aantal antwoorden\
  Stuur een plaatje op.\
  Of verandere de broncode \
  Voeg deze oefening toe aan uw klas\
  Als vervanging van een bestaande oefening\
  als een nieuwe oefening\
  stuur opnieuw\
  Verwerk de oefening in een ontwikkelings module\
  Bewaar de broncode\
  van de oefening op uw eigen computer!\
 into name_parameter_cnt,name_answer_cnt,name_deposit,name_modify,name_putinclass,\
name_replace,name_new,name_sendagain,name_developer,name_savesource,name_download

!set name_success=De softawre heeft de oefening met succes verwerkt.

!if $level=1
!distribute lines Geef de oefening een titel\
Formaat van het statement van de oefening:\
Deze oefening vraag naar\
open antwoorden en\
meerkeuze vragen\
Niet berekende uitdrukkingen als <tt>3*5-sin(pi/3)</tt>) worden\
toegestaan,niet toegestaan\
conditites worden gebruikt op de open antwoorden te controleren.\
into name_givetitle,name_giveformat,name_exo,name_answer1,name_answer2,\
name_nonnumeric,name_prompt,name_condition
!endif

!if $level=2
 !set types=!sort nocase lines \
auto,			default\
literal expression,	litexp\
algebraic expression,	algexp\
formal expression,	formal\
approximative text,	atext\
case-nonsensitive text,	nocase\
case-sensitive text,	case\
raw text,		raw\
character set, 		chset\
equation,		equation\
finite set,		set\
matrix,			matrix\
number,			numeric\
number with range,	range\
number with units,	units\
numerical function,	function\
vector,			vector\
words in a list,	wlist

!distribute lines Geef de inhoud van de oefening \
Hier kunnen de random parameters worden gedeclareerd \
Het statement van de oefening\
Open antwoordmodel\
Correcte antwoord\
Vereiste precisie bij getalsmatige antwoorden\
Getalsmatige antwoorden worden vergeleken in het interval\
Aanvullende condities bij de analyse van getalsmatige antwoorden\
Naam van de conditie\
Declaratie van de conditie\
Meerkeuze vragen\
Correcte keuzes\
Foutieve keuzes\
Er kan ook optioneel een indicatieve hint en/of een oplossing worden gegeven\
Indicatie<br>(html formaat)\
Oplossing<br>(html formaat)\
into name_content,name_alea,name_statement,name_free,name_goodsol,name_precision,name_function,\
 name_condition_numeric,name_name_condition,name_definition,name_multiple,name_goodchoice,name_badchoice,\
 name_option,name_indication,name_solution

!endif

!if $level=4
  !set name_update1=!nosubst De oefening <tt>$existing.oef</tt> is met succes toegevoegd aan module
  !set name_update2=Het is niet gelukt oefening <tt>$existing</tt> toe te voegen aan module
  !set name_update3=Uw oefening is met succes geinstalleerd.
  !set name_update4= Er is een identieke oefening in uw klas aangetroffen. De laatste toevoeging worde genegeerd.<p>
  !set name_update5=Deze oefening is alleen bereikaar voor studenten \
  in uw eigen klas en alleen dan als de oefening is opgenomen in een werkblad.
  !distribute lines U kunt nu \
  de oefeningen uit uw eigen klas bekijken \
  en deze opnemen in werkbladen.\
  into name_youcan, name_consult,name_sheet
!endif
!if $level=7
 name_warning_empty=Please choose the source file name.
 name_choice_module=Select a module
 name_choice_filename=Nameof the exercise source file (only alphanumeric symbols are allowed).
!endif

!distribute lines  U werkt nu in de expert mode van Createxo.\
Deze oefening is gebaseerd op een standaard model, probeer de\
Voeg de complete broncode toe\
om een bestaand broncode bestand te registreren, kopieer daartoe het bestand in het tekstvenster.\
Hier is de code van een bestaande oefening uit uw klas.\
Deze kan worden veranderd in het onderstaande venster.\
Hier is de code van uw geimporteerde publieke oefening. U kunt deze desgewenst nog aanpassen in het onderstaande venster.\
Omdat deze oefening is gebaseerd op een standaard model, probeer de\
script tester\
 into name_brut,name_try,name_allsource,name_copy,name_source2,name_modify_window,name_public,name_test_extern,name_testerscript

!exit
:delete
De oefening <em>$deltitle</em> is uit de lijst met oefeningen uit uw klas verwijderd.
<p>
Hier staat de broncode van de oefening, voor het geval u deze nog wilt bewaren voor later.
Gebruik daarvoor de expert mode van Createxo:
!href module=adm/createxo&mode=raw $wims_name_createxo
<p>

!exit
:model
<b>Opmerking</b>. Deze voorbeeld modellen kunnen worden gebruikt om snel
een oefening te bouwen. 
Uiteraard zijn dit veelal simpelere toepassingen en wordt niet al het potentieel van Createxo benut. 
!exit

:register
Uw oefening is met succes opgenomen in deze server.
Bedankt namens allen die profiteren van uw inzet en moeite ! 
<p>
De administrator van deze server zal de oefening nog controleren en de definitieve plaats bepalen.
Dit kan enkele dagen in beslag nemen.

!exit
