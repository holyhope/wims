!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_auth=Ontwikkelaars authentificatie
!set name_prop=Account gegevens
!set name_modname=!nosubst Lijst modules van <em>$(auth_name[1]) $(auth_name[2])</em>
!set name_create=Maak een nieuwe module
!set name_diff=Controleer verschil (diff)
!! must be the same as wims_name_modcontent in html/names.phtml.$lang
!! dont succeed not to duplicate
!set name_flist=Lijst van files
!set name_files_binfile=Binaire bestanden
!set name_del=Verwijder een module
!set name_size=Grootte (bytes)
!set name_publish=!nosubst Publiceer $i_title<br/><span class="tt">$mod</span>
!set name_publication=Publication
!set name_validation_message=Vraag de sitemanager de installatie hiervan te controleren.
!set name_compile=Compileren latex2wims
!set name_backup=Backup
!set name_edfile=Bestands modificatie
!set name_showfile=Bestands inhoud

!distribute line Files OEF/src\
Files OEF/src/cpp\
Editable data files\
Translation files\
Configuration files\
Help Files\
into name_files_src,name_files_cpp, name_files_other,name_files_lang,name_files_phtml,name_files_help

!! wims_name_properties
!set name_index=Eigenschappen

!set name_file=Aanwezige binaire bestanden
!set name_file1=Aanwezige
!set name_nofile=Geen binaire bestanden aanwezig in deze module.
!set name_depos=Stuur een binair, bestand op
!set name_in_module=in de module
!set name_replace=een vervangend bestand&nbsp;
!set name_addfile=Voeg een nieuw bestand toe&nbsp;
!set name_successfile=Het bestand is opgemonen in de module.
!set name_nosuccessfile=Het bestand is niet geupload naar de module.\
  Kontroleer of de bestandsnaam geen vreemde lettertekens bevat of \
  een van de volgende karakters
!set name_successdeletefile=is verwijderd uit de module
!set name_failuredeletefile=is NIKET verwijderd uit de module
!set name_changefile=Hernoemen
!set name_changenamefile=Nieuwe  naam van het bestand
!set name_warning_changenamefile=Let op, veranderen van een bestandsnaam kan\
problemen veroorzaken in werkbladen in een klas.

!set name_help_addfile=De naam <span class="tt wims_fname">name_file</span> mag geen accenten en spaties bevatten en ook geen min-tekens..
!set name_help_addfile_src=De naam van de OEF broncode moet zijn in de vorm <span class="tt"> src/name_file.oef</span>
!set name_help_addfile_cpp=De naam van een cpp bestand uit een OEF moet zijn in de vorm <span class="tt wims_fname">src/cpp/name_file.cpp</span>.
!set name_help_addfile_other=De naam van het bestand moet zijn in de vorm <span class="tt wims_fname">name_file</span>.
!set name_help_addfile_lang=De naam van het bestand moet zijn in de vorm <span class="tt wims_fname">lang/name_file.xx</span> waarin <span class="tt wims_fname">xx</span> de twee letter landcode voorstelt.
!set name_help_addfile_phtml=U kunt een aantal van deze bestanden te wijzigen bij het configureren van uw module.
!set name_gestion=Voor documenten klik op de link <span class="wims_button disabled">$wims_name_docgestion</span>
!set name_your_module=Uw module
!set name_your_module_OEF=is een module met oefeningen in het OEF formaat en
!set name_file2=bevat de volgende bestanden
!set name_updateadress=Vernieuw het adres
!set name_simpl_address=Deze module heeft slechts een enkelvoudig adres
!set gnu=!nosubst &copy; $year (<a href=\"COPYING\">GNU GPL</a>)

!set name_type=OEF, document, oefening, hulpmiddel, recreatie, Deductio
!set name_zone=Zone
!set name_Category=Categorie
!set name_category=!nosubst $wims_name_Type
!set name_createnew=Maak een nieuwe module
!set name_noquicktool=Quicktool is niet geinstalleerd op deze server.
!set name_rename=hernoemen
!set name_duplicate=dupliceren
!set name_increment=Niet vergeten het versie nummer te verhogen bij publicatie !
!set name_backto=!nosubst Terug naar $otit
!set name_this1=uw nieuwe module
!set name_this2=de module in bewerking
!set name_levellist=E: lagere school; H: middelbare school; U: universiteit; <br />G:promotie ; R: onderzoek

!set name_accountchange=Verander uw ontwikkelaars account
!set name_empty=laat het wachtwoord veld leeg ,als u het niet wilt veranderen
!set name_change=Uw wachtwoord is veranderd.
!set name_translation_language=Andere talen
!set name_images=Common images
!set name_help_images=if you need images in an OEF exercise.

!distribute lines Test options\
  Formule\
  plaatje laag,plaatje hoog, MathML\
  inzoomen\
  Letter afstand\
  normaal,groot\
  grootte van wiskunde lettertype\
into name_optiontest,name_formule,name_useropts1, name_useropts2,name_fonte,name_useropts3,\
  name_useropts4

!if $job iswordof modname restore
  !set name_moddevcnt=!nosubst U heeft $totalcnt modules in bewerking.
  !set name_limited=!nosubst lijst beperkt tot $maxlist items

  !distribute lines Laat alleen modules zien waarvan het adres bevat\
  Klik op de titel van een module, om deze te gaan bewerken.\
   U hebt geen modules in ontwikkeling. S.v.p. klik hier \
   zet een backup-file terug\
  into name_browselist,name_clicktitle,name_nomodule,name_restore
!endif

!distribute lines Kopie,Hernoemen,Dupliceren,Hernoemen\
 into name_choice
!set name_move=$(name_choice[2])
!set name_copy=$(name_choice[3])
!if $job iswordof copy move
  !distribute lines maak een kopie\
  Het veranderen van de modulenaam zal leiden tot problemen met werkbladen, repetities en documenten die deze module gebruiken.\
 into name_copy,name_warning1
!set name_public_module=!nosubst de reeds gebubliceerde module <span class="wims_mod_title">$otit</span> \
  (<span class="tt wims_fname">$original2</span>) naar de development afdeling, met als adres
!set name_warning2= Hernoemen of dupliceren van een reeds gepubliceerde c.q. openbare module\
  kan leiden tot een dubbele aanwezigheid bij latere publikatie. Wees dus voorzichtig met het manipuleren van reeds bestaande en gepubliceerde WIMS modules !\
  <p>Wil U deze module uitproberen, plaats deze dan in de <span class="tt wims_fname">test</span> zone.
!set name_warning3=Wanneer U reeds deze module heeft gepubliceerd, zorg dan het adres van deze module\
  exact overeenkomt met het adres van de reeds gepubliceerde versie.<span class="small">Anders worden er dus twee "dezelfde" modules gepubliceerd.</span></p>
!endif

!if $job=auth
  !set name_intro=Dit hulpprogramma is bedoeld voor het online ontwikkelen van speciale WIMS modules,\
 en is alleen toegankelijk voor gebruikers met een ontwikkelaar-account op deze server.\
 <p> Geef hier s.v.p. uw modtool loginnaam.</p>

  !distribute lines stuur een email naar de systeembeheerder\
    als u het wachtwoord vergeten bent.\
    Bent U geinteresseerd in het maken van WIMS modules,\
    WIMS new developer voor een account (loginnaam en wachtwoord).\
    U kunt altjd vrijblijvend en zonder speciaal account\
    interactieve WIMS oefeningen te maken.\
 into name_manager,name_forget,name_developer,name_identification,name_createxo1,\
    name_createxo2

!endif

!if $job=backup
 !set name_save= Hier is de backup file van de module
 !set name_internal_error=  Er is een interne fout opgetreden : het is onmogelijk een backup archief te maken.<br /> Neem s.v.p. kontakt op met de
!endif

!if $job=publish
  !distribute lines Modtool submissie id\
  Type publicatie\
  experimentele versie,stabiele versie - verander een bestaande module,stabiele versie - voeg een nieuwe module toe\
  Is deze module een vertaald<br />en gemaakt door een ander ? \
  Toegelaten mede auteurs\
  Lees mij eerst !\
  De veranderde versie van uw module zal vanaf morgen te vinden zijn in de database van de WIMS zoekmachine\
  Als dit niet de bedoeling is, graag de systeembeheerder van deze server vragen de module handmatig te verwijderen\
  U wordt een email ter bevestiging toegestuurd.\
  OK, ga door\
  De volgende domeinnamen zijn niet bekend \
 into name_publishaccount,name_publishtype,name_prompt,name_translation,name_authorized,name_readhelp,\
   name_local,name_error,name_emailsend,name_goahead,name_warning_nodomain

 !set name_warning0=!nosubst Dit is een openbare / publiek-adres module en die wordt geinstalleerd op\
  de "hoofd distributie server" $publishname.
 !set name_warning01=Geef hier uw "publicatie id".
 !set name_warning1= Wanneer dit een verbeterde/vernieuwde versie is van een bestaande module,\
 niet vergeten het <em>versienummer</em> van de module te verhogen. Als U dit niet doet, zal niemand uw nieuwe versie gaan gebruiken.
 !set name_warning2=Uw module heeft een lokaal adres.\
 Het kan dus alleen worden gepubliceerd op deze lokale WIMS server. Wilt U toch doorgaan?
 !set name_warning3=Het grote voordeel van publicatie op een lokale WIMS server is,\
 dat de module gewoon door de zoekmachine van deze lokale server kan worden aangeroepen.
 !set name_cheat1=!nosubst Deze module heeft versie WIMS-$Wver2 nodig,\
 terwijl deze server versie $wims_version is. \
 U moet de INDEX file van de module even veranderen\
  om dit recht te trekken.
 !set name_cheat2=Als U zeker bent van uw zaak, kunt U de andere servers om de tuin leiden \
 door ze te laten denken dat U met oudere versie werkt. (een rikante operatie...)
 !set name_warning_domain=!nosubst Het domein en de zoektermen van de module moeten nog worden gecontrolleerd.\
     Dus <span class="wims_label">$wims_name_Domain</span> en \
     <span class="wims_label">$wims_name_Keywords</span>. \
     Als niets van toepassing is op uw module, stuur ons dan een voorstel voor een nieuw domein etc.
  !set name_warning_domain2=!nosubst Klik op de help voor \
     <span class="wims_label">$wims_name_Domain</span> of\
     <span class="wims_label">$wims_name_Keywords</span> voor de beschikbare lijst.
  !set name_warning_keywords=!nosubst Voor verbetering van de zoektermen, zie ook \
   <span class="wims_label">$wims_name_Domain</span> en \
   <span class="wims_label">$wims_name_Keywords</span>),\
   gebruik hiervoor de technische engelse versie.\
   Stuur uw bijdrage voor domeinen en / of zoektermen naar

 !set name_warning_keywords_unknown=De volgende zoektermen zijn niet opgenomen in de officiele zoektermlijst van WIMS
 !set name_warning_keywords2=Alleen de officiele zoektermen komen in aanmerking voor 'autocompletering' in de zoekmachine. Controleer of er geen bruikbare alternatieven in de zoektermlijst van WIMS aanwezig zijn.
 !set name_warning_suggestion=Nieuwe voorstellen voor domeinen en / of zoektermen zijn uiteraard welkom.
!endif

!if $job=diff
  !distribute lines Er is geen verschil gevonden tussen deze ontwikkelings versie en de reeds gepubliceerde versie van deze module op de server.\
  Er zijn veel te veel verschillen tussen de ontwikkelings versie en de reeds gepubliceerde versie van de module op deze server.\
    De verschillen tussen de ontwikkelings versie en de reeds gepubliceerde versie op deze server zijn&nbsp;:\
  into name_diff1,name_diff2,name_diff3
!endif

!if $job=restore
 !set name_warning1=Uw bestand ziet er niet uit als een module backup file ! <p>U kunt voor deze \
 herstelprocedure alleen archieven gebruiken die eerder door Modtool zelf zijn aangemaakt ! \
 </p>Probeer het opnieuw.

 !distribute lines Ik kan in dit archief <b>geen valide</b> backup van een WIMS module ontdekken. Een fout in het bestand !\
 Er is geen verschil gevonden tussen de bestaande module en de backup.\
   Zeer veel verschillen tussen de bestaande module en de backup versie.\
   Er zijn verschillen tussen de bestaande module en de backup versie\
   Geef de backup file\
   controleer verschillend met de bestaande module.\
   Ga aan het werk met deze module.\
   Module is hersteld\
  into name_norecognize,name_diff1,name_diff2,name_diff3,name_restoref,name_show_diff,name_gotowork,\
    name_restored

!set name_illegal=De getuurde archieven bevatten niet-toegestane bestands types! Ik kan geen hersteloperatie uitvoeren.\
 <p>Is dit soms een oude backupfile. Probeer bestand voor bestand te kopieren.
!set name_warning2=Alleen backups van Modtool worden geaccepteerd.\
   De backup files mogen nooit handmatig worden gewijzigd.
!set name_warning_diff=!nosubst Deze backup module overschrijft nu -zonder pardon- de bestaande module met het zelfde module-adres !\
   U kunt nog wel de verschillen checken met de bestaande module

!endif

!exit
:del
Verwijderde modules zijn definitief weg !
Maak dus eerst een
!href cmd=reply&jobreq=backup backup

<p>
<b>Attentie</b>: wanneer deze module nog in gebruik is in werkbladen, repetities of documenten
 wordt dit lesmateriaal dus onbruikbaar !


<p>
Weet U zeker dat deze module verwijderd moet worden?
!!</p> close after the name of the module
!exit
:delconfirm
  Het bestand
 <span class="wims_fname">$fname</span>
 uit deze module
 <span class="wims_mod_title">$title</span> is verwijderd.
!exit

:delfile

Weet U zeker dat deze file
<span class="wims_fname">$fname</span>
verwijderd moet worden uit module
<span class="wims_mod_title">$title</span>&nbsp;?
!exit
