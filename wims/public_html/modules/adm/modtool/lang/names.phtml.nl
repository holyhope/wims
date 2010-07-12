!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set name_auth=Ontwikkelaars authentificatie
!set name_prop=Account gegevens
!set name_modname=!nosubst Lijst modules van <em>$auth_name</em>
!set name_create=Maak een nieuwe module
!set name_diff=Controleer verschil (diff)
!set name_flist=Lijst van files
!set name_binfile=Binaire bestanden
!set name_del=Verwijder een module
!set name_size=Grootte
!set name_publish=!nosubst Publiceer <em>$i_title</em><br>\
	<tt><font size="+0">$mod</font></tt>

!set name_file=Aanwezige binaire bestanden
!set name_nofile=Geen binaire bestanden aanwezig in deze module.
!set name_depos=Stuur een binair bestand op
!set name_in_module=in de module
!set name_replace=een vervangend bestand&nbsp;
!set name_addfile=Voeg een nieuw bestand toe&nbsp;
!set name_gestion=Voor documenten klik op de link <tt>$wims_name_docgestion</tt>
!set name_your_module=Uw module
!set name_file2=bevat de volgende bestanden
!set name_updateadress=Vernieuw het adres
!set name_simpl_address=Deze module heeft slechts een enkelvoudig adres
!set gnu=&copy; $year (<a href=COPYING>GNU GPL</a>)

!set name_type=oefening, hulpmiddel, document, recreatie, OEF, Deductio
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
!set name_levellist=E: lagere school; H: middelbare school; U: universiteit; <br>G:promotie ; R: onderzoek

!set name_accountchange=Verander uw ontwikkelaars account
!set name_empty=laat het wachtwoord veld leeg ,als u het niet wilt veranderen
!set name_change=Uw wachtwoord is veranderd.

!if $job=modname
  !set name_moddevcnt=!nosubst U heeft $totalcnt modules in bewerking.
  !set name_limited=!nosubst lijst beperkt tot $maxlist items
  
  !distribute lines Laat alleen modules zien waarvan het adres bevat\
  Klik op de titel van een module, om deze te gaan bewerken.\
   U hebt geen modules in ontwikkeling. S.v.p. klik hier \
   zet een backup-file terug\
  into name_browselist,name_clicktitle,name_nomodule,name_restore
!endif

!if $job iswordof copy move
  !distribute lines Kopie,Hernoemen,Dupliceren,Hernoemen\
  maak een kopie\
  Het veranderen van de modulenaam zal leiden tot problemen met werkbladen, repetities en documenten die deze module gebruiken.\
 into name_choice,name_copy,name_warning1
!set name_public_module=!nosubst de reeds gebubliceerde module <em>$otit</em> (<tt>$original2</tt>) naar de\
  development afdeling, met als adres
!set name_warning2= Hernoemen of dupliceren van een reeds gepubliceerde c.q. openbare module\
  kan leiden tot een dubbele aanwezigheid bij latere publikatie. Wees dus voorzichtig met het manipuleren van reeds bestaande en gepubliceerde WIMS modules !\
  <p>Wil U deze module uitproberen, plaats deze dan in de <tt>test zone</tt>.
!set name_warning3=Wanneer U reeds deze module heeft gepubliceerd, zorg dan het adres van deze module\
  exact overeenkomt met het adres van de reeds gepubliceerde versie.<small>Anders worden er dus twee "dezelfde" modules  gepubliceerd.</small> 
!endif

!if $job=auth
  !set name_intro=Dit hulpprogramma is bedoeld voor het online ontwikkelen van speciale WIMS modules,\
 en is alleen toegankelijk voor gebruikers met een ontwikkelaar-account op deze server.\
 <p> Geef hier s.v.p. uw modtool loginnaam.
 
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
 !set name_internal_error=  Er is een interne fout opgetreden : het is onmogelijk een backup archief te maken.<br> Neem s.v.p. kontakt op met de 
!endif

!if $job=publish
  !distribute lines Modtool submissie id\
  Type publicatie\
  experimentele versie,stabiele versie - verander een bestaande module,stabiele versie - voeg een nieuwe module toe\
  Is deze module een vertaald<br>en gemaakt door een ander ? \
  Toegelaten mede auteurs\
  Lees mij eerst !\
  De veranderde versie van uw module zal vanaf morgen te vinden zijn in de database van de WIMS zoekmachine\
  Als dit niet de bedoeling is, graag de systeembeheerder van deze server vragen de module handmatig te verwijderen\
  U wordt een email ter bevestiging toegestuurd.\
  OK, ga door\
 into name_publishaccount,name_publishtype,name_prompt,name_translation,name_authorized,name_readhelp,\
   name_local,name_error,name_emailsend,name_goahead

 !set name_warning0=!nosubst Dit is een openbare / publiek-adres module en die wordt geinstalleerd op\
  de "hoofd distributie server" $publishname (<tt>$centralhost</tt>). Geef hier uw "publicatie id".
 !set name_warning1= Wanneer dit een verbeterde/vernieuwde versie is van een bestaande module,\
 niet vergeten het <em>versienummer</em> van de module te verhogen.Als U dit niet doet, zal niemand uw nieuwe versie gaan gebruiken.
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

!endif

!if $job=diff
  !distribute lines Er is geen verschil gevonden tussen deze ontwikkelings versie en de reeds gepubliceerde versie van deze module op de server.\
  Er zijn veel te veel verschillen tussen de ontwikkelings versie en de reeds gepubliceerde versie van de module op deze server.\
    De verschillen tussen de ontwikkelings versie en de reeds gepubliceerde versie op deze server zijn&nbsp;:\
  into name_diff1,name_diff2,name_diff3
!endif

!if $job=restore

 !set name_warning1=Uw bestand ziet er niet uit als een module backup file ! <p>U kunt voor deze \
 herstelprocedure alleen archieven gebruiken die eerder door Modtool zelf zijn aangemaakt ! Probeer het opnieuw.
 
 !distribute lines Ik kan in dit archief <b>geen valide</b> backup van een WIMS module ontdekken. Een fout in het bestand !\
 Er is geen verschil gevonden tussen de bestaande module en de backup.\
   Zeer veel verschillen tussen de bestaande module en de backup versie.\
   Er zijn verschillen tussen de bestaande module en de backup versie\
   Geef de backup file\
   controleer verschillend met de bestaande module.\
   Ga aan het werk met deze module.\
   Module hersteld\
  into name_norecognize,name_diff1,name_diff2,name_diff3,name_restore,name_show_diff,name_gotowork,\
    name_restored
  
!set name_illegal=De getuurde archieven bevatten niet-toegestane bestands types! Ik kan geen hersteloperatie uitvoeren.\
 <p>Is dit soms een oude backupfile. Probeer bestand voor bestand te kopieren.
!set name_warning2=Alleen backups van Modtool of gedownload van het "publicatie centrum"\
   <a href="$downloadsite">$downloadsite</a> worden geaccepteerd.\
   De backup files mogen nooit handmatig worden gewijzigd.
!set name_warning_diff=!nosubst Deze backup module overschrijft nu -zonder pardon- de bestaande module met het zelfde module-adres !\
   U kunt nog wel de verschillen checken met de bestaande module 
 
!endif

!exit
:del
Verwijderde modules zijn definitief weg !
Maak dus eerst een
!href cmd=reply&jobreq=backup  backup

<p>
<b>Attentie</b>: wanneer deze module nog in gebruik is in werkbladen, repetities of documenten
 wordt dit lesmateriaal dus onbruikbaar !


<p>
Weet U zeker dat deze module verwijderd moet worden?

!exit
:delconfirm
  Het bestand 
 <font color=blue><em>$fname</em></font>
 uit deze module
 <font color=blue><em>$title</em></font> is verwijderd.
!exit

:delfile

Weet U zeker dat deze file 
<font color=blue><em>$fname</em></font>
verwijderd moet worden uit module
<font color=blue><em>$title</em></font>&nbsp;?
!exit
