!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!distribute line Lijst van forums\
	Beheerders authentificatie\
	Gebruikers authentificatie\
	Gebruikers aanmelding\
	into n_list,n_authowner,n_authuser,n_register

!distribute line bezoeker\
  gebruiker\
  beheerder\
  inschrijven\
  Er zijn geen forums geinstalleerd op deze site.\
  Wachtwoord van de beheerder\
into name_visitor,name_user,name_owner,name_register,name_noforum,\
 name_pass_owner

!set name_number_message=!nosubst We hebben $ccnt forums op deze site.\
Zoek in de volgende tabel:
!exit

:create
klik op <span class="wims_button disabled">$name_register</span> om je aan te melden. 
Je kunt ook
!href module=adm/forum/regforum je eigen forum
&nbsp;maken.

!exit

:enter
Om naar binnen te gaan als <b><font color=green>$mb_title</font></b>
een <em>geregistreerde gebruiker</em>, 
geef s.v.p. je loginnaam en wachtwoord:

!exit

:owner

Om naar binnen te gaan als <b><font color=green>$mb_title</font></b> 
<em>beheerder</em> vul hier het wachtwoord in:

!exit
