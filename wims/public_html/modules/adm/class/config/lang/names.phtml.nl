!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!set classname=<b><font color=green>$wims_classname</font></b>\
 of <b><font color=green>$wims_institutionname</font></b>

!set months=Januari,Februari,Maart,April,Mei,Juni,Juli,Augustus,September,Oktober,November,December
!set title=Configuratie en Onderhoud

!distribute items oefeningen,werkbladen,proefwerken,documenten,vragenlijsten,huiswerk agenda,\
	studenten accounts,docenten accounts,discussie forum,bericht van de dag,raport boekje,\
	pedagogische werkvolgorde,forum berichten\
	into name_exo,name_sheet,name_exam,name_doc,name_vote,name_cdt,\
	name_user,name_sup,name_forum,name_motd,name_livret,name_seq,name_forum_mesg

!distribute items subklassen,studentens,oefeningen,documenten,docenten\
into wims_name_zones,wims_name_participants,wims_name_exercises,wims_name_docs,wims_name_teachers


!distribute item bericht van de dag,\
	oefening,werkblad,proefwerk,document,student\
	into name_motd,name_exo,name_sheet,name_exam,name_doc,name_user	

!distribute item berichten van de dag,\
	oefeningen,werkbladen,proefwerken,documenten,studenten\
	into name_motds,name_exos,name_sheets,name_exams,name_docs,name_users

!if $job=arch
 !set title=Backup en Herstel
 !set name_intro=Er kan een backup archief van uw klas worden aangemaakt, in het volgende formaat
 !set name_tosend=Om de klas te herstellen via een backup archief; geef de backup archief naam
 !set name_namefile=Geef de naam van het backup archief
 !set name_help=Er wordt gevraagd naar de specifiek te herstellen onderdelen van uw klas.
 
 !set name_deposit=!nosubst Het backup archief <tt>$wims_deposit</tt> bevar de volgend onderdelen.\
 Geef aan welke items moeten worden gebruikt voor het herstel van uw klas.
 
 !set name_no_restore=De herstelprocedure wordt afgebroken: er is gedeeld materiaal van een andere klas aanwezig.\
 Herstel kan alleen worden uitgevoerd op het originele materiaal van af de uitlenende klas.

 !distribute lines Er is niets geselecteerd voor het herstel.\
 Herstel alles behalve de klas configuratie en het supervisor account.\
 <font color=red>Opgelet !</font> <small>Zie opmerkingen hieronder.</small>\
   Klas configuratie.\
   Supervisor account (inclusief uw wachtwoord)\
   Studenten accounts\
   Aanwezige accounts\
   documenten\
   Aanwezige documenten\
   oefeningen\
   Aanwezige oefeningen\
   werkbladen\
   Impliceerd herstel van alle oefeningen uit de klas\
   Aanwezige werkbladen\
   proefwerken\
   Impliceerd herstel van alle werkbladen en oefeningen\
   Aanwezige proefwerken\
   forum berichten\
   Aanwezige berichten\
   Studenten activiteit registratie en server cijfers. Impliceerd herstel van studenten accounts.\
   Handmatig ingevoerde cijfers\
   Aanwezige cijfers\
   de klasse agenda\
   De aanwezige klasse agenda\
   Raport boekje\
   Bestaande raport boekje\
   Pedagogische werkvolgorde\
   Impliceerd het herstel van werkbladen, oefeningen, proefwerken en documenten\
   Aanwezige werkvolgorde\
   Herstel methode\
   Vervangine\
   vervang aanwezig materiaal door de backup.\
   Samenvoegen\
   vervang al het aanwezige materiaal, behalve de studenten accounts en de klasse oefeningen; bij deze klasse oefeningen worden alles met een gelijke naam overschreven.\
   Vervang en herstel het aangegeven materiaal\
   into name_noselect,name_all,name_danger,name_config,name_teacher,name_part,name_part1,name_doc,\
   name_doc1,name_exo,name_exo1,name_sheet,name_sheet0,name_sheet1,name_exam,name_exam0,name_exam1,name_forum,\
   name_forum1,name_activity,name_manual,name_manual1,name_cdt,name_cdt1,name_livret,name_livret1,name_seq,\
   name_seq0,name_seq1,name_method,name_replace,name_replace1,name_merge,name_merge1,\
   name_selectrestore
   
!distribute lines Backup archief hersteld klas\
Herstel van studenten accounts (en alle gerigistreerde studenten activiteit) is geannuleerd : er is niet genoeg ruimte meer over.\
De klas einddatum is veranderd na de herstelprocedure, omdat de upload datum \
into name_restore1,name_restore2,name_restore3

 !distribute items onherkenbaar is, te vroeg is, te laat is into ebad,eearly,elate
 
 !distribute lines Helaas, het maken van een backup archief is mislukt. Een interne fout.\
 Hier is het backup archief van uw klas\
 Klik hier voor het downloaden\
 Er kan ook een selectieve backup worden aangemaakt. Klik op\
 Selectieve backup\
 \
 Verander en bewaar het backup archief.\
 into name_download1,name_download2,name_download3,name_download4,name_download5,\
 name_selective1,name_selective2,name_selective3

 !set name_download5=Het backup archief is misschien te groot om naar deze sever te sturen.\
 Om (meerdere) kleinere archieven aan te leggen kunt u gebruik maken van een selectieve backup.
  
 !goto commun
!endif

!if $job=clean
 !set title=Opschonen van een klas
 !set name_lines=Studenten activeiten
 !set name_empty=Deze klas is leeg!<p> Er staat dus ook niets in  dat opgeschoond kan worden.
 !set name_no_erase=Kan niet worden opgeschoond omdat er materiaal wordt gedeeld met een andere klas.

 !distribute lines Opschonen\
   Dit verwijdert ook de activiteiten registratie\
   Dit verwijdert ook de proefwerken\
   Maak een backup van de klas\
   Aanwezig materiaal in de klas\
 into name_cleanall,name_erase1,name_warning_exam,name_saveclass,name_ressource
  !set name_warning_clean=Let op: er is geen undelete op dit systeem !

 !goto commun
!endif

!if $job=neighbor
 !set title=Buurklassen
 !set name_noclass=Er kunnen geen buurklassen worden gedefinieerd omdater er geen andere klasses zijn.
 !set name_toomany=Er zijn te veel klassen op deze server geinstalleerd. Geef een zoekterm om naar een klas te zoeken.
 !set name_toomany2=Er zijn te veel klassen gevonden .Geef een betere zoekterm in.

 !distribute lines Zoek naar een klas\
 Er zijn geen klassen gevonden. Probeer opnieuw.\
 Het aanmaken van buurklassen geeft de mogelijkheid om gemeenschappelijk materiaal te gebruiken.\
 Klik op een klas om de procedure te starten.\
 Klassen met een zelfde taal\
 Klassen met een andere taal\
 Voorbeelden\
into name_research,name_noclass,name_exampleclass,name_help,name_changeneigh,\
  name_samelanguage,name_otherlanguage,name_example

 !distribute lines Buurklassen<br>definieren\
   Delen van materiaal\
   door u\
   door een ander\
   Wederzijds gedeeld.\
   U deelt.\
   U leent.\
   Wederzijds goedkeuring.\
   Geeft U permissie om te lenen.\
   U heeft permissie om te lenen.\
   Stop de deling\
   Delen\
   Importeer alle deelnemers\
   Lesmateriaal\
   Importeer ander materiaal\
   Klassen die uw materiaal mogen lenen\
   Materiaal met toestemming\
   actief\
   Lijst van andere klassen\
   Gedeeld materiaal info\
   Demonstratie klassen op deze server\
 into name_declaration,name_sharing,name_byyou,name_other,name_actif,name_share1,name_share2,\
 name_permit1,name_permit2,name_permit3,name_stopsharing,name_share,name_everybodyimport,name_teaching,\
 name_otherone,name_classsharing,name_ressourceallowed,name_active,name_listclass,name_info,name_exampleclass
 
 !distribute lines Buurklassen\
    heeft uw klas nog nioet geaccepteerd als buur\
    accepteerd u als buur voor
    met \
    U deelt het onderstaande materiaal afkomstig uit klas\
    heeft geen uitleenbaar metariaal\
    heeft het onderstaande materiaal om uit te lenen\
    De zelfde naam in uw klas\
    Leeg\
    niet klaar voor gebruik\
    Vervang\
    Deze loginnaam bestaat al in uw klas\
    Verwijderde student bestaat in uw klas\
    Importeren uit klas\
    Met succes overgezet\
    Studenten accounts uit de buurklas\
    Kontroleer het resultaat\
    into name_neighbor_relation,name_text1,name_text2,name_with,name_sharealready,\
    name_no_ressource,name_importable,name_same_title,name_empty,name_inpreparation,\
    name_replace,name_existinglogin,name_part_erased,name_import,name_transfered,\
    name_neigh_account,name_verify

 !set name_inactif=!subst Het ge&iuml;mporteerde materiaal $(name_$itype) is op inactief gezet, \
 zodat u het naar uw eigen wensen kunt aanpassen.
 
 !set name_accept=!nosubst Accepteerd u de klas <em><font color=blue>$nei_description</font></em> als buurklas ?
   
 !if $job2=stopshare
  !set title=Stop de deling
  !set name_warning=Uw klas heeft een aciteve cijfer registratie en de gedeelde bronnen zijn niet leeg.\
  Als u nu stop met lenen kan hier later niet meer op worden terug gekomen.<p>\
  U wilt definitef stoppen met delen ?
 !set name_stop=Stoppen
 !endif
 !if $job2=sharelist
  !set title= informatie over gedeeld materiaal.
  !set name_sharelist=!nosubst Uw klas deelt $(name_$rec) afkomstig uit 
  !distribute lines U deelt geen materiaal uit andere klassen.\
  U deelt materiaal uit andere klassen\
  into name_noresource,name_resource
  !endif
  
  !if $job2=addshare
    !set title=Delen van lesmateriaal met andere klassen
    !set name_class_share=De klas <em><font color=blue>$nei_description</font></em>\
    heeft het onderstaande materiaal voor uitlening beschikbaar.
  !distribute lines beschikbaar\
    Uw klas deelt dit materiaal daadwerkelijk.\
    Dit materiaal kan niet worden gedeeld omdat dit materiaal uit een andere klas afkomstig is.\
    Opschonen van uw materiaal\
    mits mogelijk\
    Het supervisor account delen is niet verstandig ! \
  into name_available,name_actually_sharing,name_nosharing,name_cleanup,name_ifpossible,\
    name_dangerous
  
  !set name_warning1=Dit materiaal kan niet worden uitgeleend: omdat uw klas het materiaal leent uit een andere klas.\
  !set name_warning2=!nosubst U kunt dit materiaal niet delen om dat uw eigen $(name_$r) niet leeg zijn.\
  Voor dat met een deling kan worden begonnen moet u eerst
  !set name_warning_erase=!nosubst Dit verwijdert dus al uw bestaande $(name_$r)! En zonder backup is dit definitef weg.
   
  !endif
  
  !distribute items ---,<small>supervisor</small>,\
	<small>student</small>,\
	<small>iedereen</small> into n_n0, n_n1, n_n2, n_n3
	
 !goto commun
!endif

!if $job=connect
 !set title=Verbinding met andere servers / platformen
 !set name_listserver=Lijst met bestaande server verbindingen

 !distribute Test de server verbinding\
   Test een verbinding met een klas\
   Voeg een verbinding met een klas toe\
   Onderhoud van de verbonden klas\
   lokale klas, klas op een andere server\
   class definition, user list, score averages, score details,all but class definition\
   Remote class\
   Remote server\
   Synchronize\
   (with the other one) for\
   Manage\
   Destroy remote class\
   This connection to the remote server is working.\
   The connection has been added to your class, but the remote server returns an error message\
   The remote server does not reply. Please report to the\
  The connection is rejected by the remote server. Error message\
  Checked remote class\
  This connection is working. Data returned from the remote class\
  To connect to a class on the above server, please specify\
  Identifier of the remote class\
  If the remote class is empty, the server will create a new class on the remote server, duplicating the properties of this one.\
  Automatically update the remote class for changes made on this one\
  Allow the remote class to modify this one\
  This class has no connections to other servers.\
  You have declared the following connections to other servers.\
  Server\
  Actually, this WIMS server has the following connectable servers.\
 into wims_name_connecttest,wims_name_classtest,wims_name_addconnection,wims_name_connectmanage,name_prompt1,\
   name_prompt2,name_synchronize,name_withotherone,name_remoteclass,name_remoteserver,wims_name_Manage,\
   wims_name_destroy,name_working,name_error1,name_errornoreply,name_errorreject,name_check,name_data,\
   name_toconnect,name_identifier,name_help,name_automatically,name_allow,name_noconnection,name_declaration,\
   wims_name_server,name_listserver

 !goto commun
!endif

!if $job=access
 !set title=Configuratie toegangsbeleid
 !goto commun
!endif

!if $job=grestrict
 !set title=Score restricties
 !goto commun
!endif

!if $job=present
 !set title=Configuratie van het uiterlijk van de virtuele klas
 !goto commun
!endif

!if $job=oefdefault
 !set title=Configuratie voor OEF modules<br>[Online Exercise Format] 
  !distribute One series will have\
   Level of severity\
   Time limit\
   seconds\
   Number of items shown in multiple choices\
   Give solution (if available) ?\
   never,if the score is not maximal,always\
   Always contain good reply\
   Penalty for bad replies in multiple choices.\
   Show good reply.\
   Allow hint (if available).\
  into name_series,name_severity,name_chrono,name_secondes,name_qcm,\
    name_solution,name_prompt,name_prompt1,name_prompt2,name_prompt3,name_prompt4

   !set name_warning=ou can put two numbers into the time limit,a smaller limit followed by a bigger one.\
In this case, the first limit starts score reduction, which will got to 0 if the second limit is reached.
  
 !goto commun
!endif

!if $job=security
 !set title=Beschikbare beveiligings instellingen voor virtuele Klassen
 !set name_see_activity2=You should be the origin of all these activities; if this is not \
   the case, you should verify where there is a leak of your supervisor's password.
 !set name_see_activity1=See the log file of management activities of your class. 
 !distribute lines Set up the class-wide restriction\
 of sites allowed to get scores.\
 Other security setups in the\
 class configuration\
 into name_restriction1,name_restriction2,name_otherrestriction1,name_otherrestriction2
 !goto commun
!endif

!if $job=authtype
 !set title=Ldap authentification
 !set name_intro_authtype=Kies <tt>ldap</tt> en vul dit formulier in \
  als u een ldap server gebruikt voor authentificatie.
 !goto commun
!endif

!if $job=import
 !set code1=None
 !set code2=$wims_name_yes but different
 !set code3=$wims_name_yes, active and different
!endif

!if $job=propagate
  !if $wims_supertype=2
   !set name_thisclass=du portail
   !set name_subclasses=sous-classes
  !else
   !set name_thisclass=de la zone actuelle
   !set name_subclasses=zones dépendantes
  !endif
   
 !distribute lines Setups successfully sent to $name_subclasses\
  You can choose to send the following setups of the $name_thisclass to all its $name_subclasses\
 into name_propagate_succes,name_propagate_choose

 !set name_warning=Please note that $name_subclasses will not automatically share later \
   changes of the setups of $name_thisclass. You must send the changes each time you \
   want them to be effective in $name_subclasses.

!endif

!if $job=log
  !set name_warning_log=Here is the log of certain managing activities of your class. This log\
allows you to verify whether there are suspicious activities.
!endif

!if $job=index
  !set title=!nosusbt Actualisation de l'index $tit
  !set name_done=Done
  !set name_result=Script output

  !if $job2=structure
   !set tit=Subclass index update
  !endif
  !if $job2=userlist
   !set tit=Participant index update
  !endif
  !if $job2=teacherlist
   !set tit=Teacher index update
  !endif
  !if $job2=oef
   !set tit=Exercise index update
  !endif
  !if $job2=doc
    !set tit=Document index update
   !endif
!endif

!if $job=list
  !distribute line Institution name\
    Class name\
    Option words\
    Modtool Account\
    Connection lock level\
    Number of the best scores\
    Participant number limit\
    Expiration date\
    Registration of exercises\
    Registration of exams\
    visible by students\
    Other configurations\
    Préférences personnelles\
    Répercuter les configurations aux zones dépendantes\
    Définir des classes voisines\
    des liens vers d'autres serveurs\
    Utiliser une authentification\
    des participants par annuaire ldap\
    Actualiser les index\
   dont le changement de\
    Faire une sauvegarde ou restauration de la classe\
    restreindre les ressources accessibles\
    restreindre les sites \
    pour lequels les scores sont enregistrés\
    faire un nettoyage sélectif\
   Configurer les\
    Utilisation actuelle d'espace disque\
    La limite est\
  into name_name_institution,name_name_class,name_optionword,name_devaccount,name_lock_level,\
    name_bestscore,name_limit,name_expirationdate,name_register_exo,name_register_exam,\
    name_visible,name_apparence,name_pref,name_dependant_zone,name_neigh,name_link,name_useauth,name_ldap,name_index,\
    name_change,name_load,name_restriction1,name_restriction2,name_score,name_clean,\
    name_config,name_disk,name_limit

!endif

:commun
!distribute lines Authentificatie\
Persoonlijke instellingen\
Toegangsbeleid\
OEF configuratie\
Buur klassen\
Security management\
Selectieve opschoning\
Actualiseer de index\
Andere servers\
Wachtwoorden\
Andere zones\
Uiterlijk\
Score instellingen\
Platform adressen\
of\
into wims_name_config_auth,wims_name_config_pref,wims_name_config_restr,wims_name_config_oef,\
wims_name_config_neigh,wims_name_config_secure,wims_name_config_clean,wims_config_refresh,\
wims_name_config_otherserver,wims_name_config_passwd,wims_name_config_propagate,wims_name_config_present,\
wims_name_config_score,wims_name_config_ent,name_of

!distribute lines Toegestane adressen\
   Style sheet\
   Logo van de klas\
   Positie van het logo\
   links boven, rechts boven\
   Style theme van de klas\
   Iconen\
   Leerniveau\
   Toegangsbeleid voor registeren van cijfers\
   Inschrijvings wachtwoord (klasse wachtwoord)\
   Wachtwoord docent\
   Configureer de opslag van toetsresultaten\
   Links naar andere leerplatformen of webpagina's\
   Pagina achtergrond kleur\
   Menu achtergrond kleur\
   Menu link kleur\
   Achtergrond plaatje\
   download een css-style bestand\
   Score kleuren (de 0  10) \
   into name_secure,name_css,name_logo,name_position_logo,name_logo_side,name_theme,\
   name_theme_icon,name_level,name_security,name_password,name_supass,name_exolog,name_ent,\
   name_background_color,name_menu_color,name_refmenu_color,name_image,name_css_transfer,name_colorscore

!set name_content_style = U kunt een algemeen stylesheet definieren\
<br>(als <tt>$name_css</tt> op <tt>klas</tt> is gezet)&nbsp;:

!set name_content_style2=of kopieer hier een css-stylesheet

!exit
:arch

 You have uploaded resources backed up from another class. If you
 restore incompatible resources to your class, it will simply be destroyed.
 !href cmd=help&special_parm=dependencies Why?
 <p>
 !href cmd=reply&job=list Stop
 if you are not completely sure of what you are doing. (In any case, keep a
 backup of the current status before continuing.)
 
 :arch_end
 <p><b>IMPORTANT</b>. <ul><li> There is no check of integrity in your uploaded data,
and manual modification of the backup archives is not supported by the
system. Errors introduced by manual modification of archives will result
in unpredictable behavior of your class.

<li> Whenever possible, avoid restoring 
<font color=red>class configuration</font> and
<font color=red>supervisor account</font>.
Errors in the uploaded data for these two fields may make you
completely lose control of your class.

<li> You can use the backup of a class to install a new one. In this case,
avoid restoring scores and grades (server-computed and manual). These two
resources cannot be erased once they are installed (security measure).
And many class maintenance operations will be unavailable if there are
non-empty score data.
</ul>
!exit

:clean
You cannot erase resources of the class
 when participant activities have already started.
 <p>
 This is an important security measure. If you feel that it is an
 inconvenience, think of the following two aspects.
 <p>
 On the one hand, suppose that a student steals your password. If (s)he
 comes to this page and erases everything, honest students will
 suffer a lot, and your teaching activities will be greatly disturbed.
 <p>
 On the other hand, different resources of the class are inter-dependent.
 If you
 erase some resources without erasing those depending on them, your class
 will no longer work.
 !href cmd=help&special_parm=dependencies Examples.
 <p>
 Anyway, if you really want to clean this class, you can always expire it
 (by setting its expiration date to today; the class will disappear the next
 morning), or
 <a href="mailto:$wims_site_manager?subject=Please erase my class">ask
 the site manager</a> to erase it for you.
 
 !exit
 
 :clean2
<b>Remark</b>. 1. This page is only available when the class is being set
up. Once student activity has started, cleaning will no longer be possible.
<p>
2. Shared resources can only be cleaned from the class
originating the sharing. The other class should first
!href cmd=reply&job=neighbor&job2=sharelist stop the sharing
 of the resources before erasing them.

:connect_first_info
Server / platform connection allows your class to directly communicate with
one on another WIMS server or another web e-learning platform. Participants
can transparently navigate between the connected classes.
<p>
In particular, you can mirror this class to a remote WIMS server,
so that if this server becomes momentarily unavailable, work
may continue on the mirror class. Scores on the mirror can be merged later.
!exit
:connect_first

This WIMS server has not declared any connectable remote server. In order
 to use this connection feature, the
 <a href="mailto:$wims_site_manager?subject=server connection">site
 manager</a> must declare such remote server, and the remote server must also
 declare this WIMS server as connectable. 
 (The site manager can refer to the file
 <tt>$basedir/log/classes/.connections/myself</tt> for details of how to
 declare site connections.)
 
 !exit
 
:import2
 The work sheet you want to import may use exercises defined in the
   neighboring class.
   <p>
   If the same exercises do not exist in your class, the imported worksheet
   won't work correctly. Please verify carefully whether all the class
   exercises in the neighbor are duplicated in your class.
:import3
   Exam sheets are based on work sheets to make up their
   contents. <p>
   Importing an exam sheet makes sense only if you have exactly the same 
   active work sheets as your neighbor, and only if these sheets are in the
   same order within the two classes.
   <p>
   If this is not the case, the imported exam sheet will almost certainly
   behave erratically.
!exit 
:import4

You are about to replace an existing $(name_$itype)
  in your class by
  the imported resource. No recovery will be possible after this
  operation, and your existing $(name_$itype), which is different from the
  imported one, will be definitely lost.
!exit

:import5
 Aucun compte de participant n'est ajouté à votre classe. Vérifiez si votre
 classe est pleine (et s'il y a encore de la place dans le site pour ajouter
 de nouveaux participants).
!exit

:auth1
This configuration tool is only accessible to secure hosts.
<p>
As you haven't defined any secure hosts, we are checking your authentification
by sending a secret code to your email address. Please check your mail, pick
the code, and type it below.

!exit
:auth2

<b>Note</b>. This authentification is to ensure that even if your password
is stolen or leaked, damages to your class will be limited.
Defining correct secure hosts will simplify the class
configuration procedure, while keeping a high security level.
!exit

:download
<b>Remark</b>. Depending on the class activities, usually it is participant
activities, forum messages and class documents that are of large size. You
may also consider the possibility of making several selective backups for
different resources.

!exit