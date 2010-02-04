!set wims_module_log=error: $error
!set level=$[$level-1]

<center><h3>Fout</h3></center> <p>

!if no_title iswordof $error
Geef de oefening eerst een titel.
 !exit
!endif

!if empty_title iswordof $error
 De software kan geen titel vinden voor uw oefening.<br>Ga na of de oefening wel een geldige titel heeft.

 !exit
!endif

!if no_answer iswordof $error
 Deze oefening moet op zijn minst 1 antwoord vragen.(open antwoord of meerkeuze).

 !exit
!endif

!if no_statement iswordof $error
 De oefening is incompleet en mist het <em>statement</em>.

 !exit
!endif

!if no_reply2 iswordof $error
 De oefening is incompleet en mist een geldige antwoord definitie.
 (vul alle velden in)

 !exit
!endif

!if def_fail iswordof $error
    De software kon uw oefening niet compileren tot een geldige OEF.
    Er zijn fouten gevonden in uw definities:
 <p><pre>$oef2wims_out</pre> <p>
 !if $mode!=$empty
  !set level=1
 !else
  !set level=2
 !endif
 !exit
!endif

!if name_exhaust iswordof $error
 Er zijn meerdere oefeningen in uw klas met een zelfde titel/naam.
 Als de oefeningen echt anders zijn, geef ze dan verschillende namen 


 !exit
!endif

!if name_exhaustpub iswordof $error
    Er zijn reeds meerdere oefeningen opgenomen met een zelfde naam/titel als
    de oefening waar u nu aan werkt.<br>Kies een andere naam voor deze oefening.


 !exit
!endif

!if unknown iswordof $error
 Het opsturen van uw oefening is helaas mislukt door onbekende redenen.
 !exit
!endif

!if already iswordof $error
 De oefening is reeds geinstalleerd.
 !exit
!endif

!if not_class iswordof $error
 Dit verzoek is niet toegestaan.
 !exit
!endif

!if not_supervisor iswordof $error
 Hmm...alleen supervisors kunnen oefeningen verijderen !
 <p>Dit verzoek is niet toegestaan.

 !exit
!endif

!if not_exist iswordof $error
 !if $catmodule!=$empty
  De oefening <tt>$del</tt> uit <tt>$catmodule</tt>
  bestaat niet <b>of</b> mag niet door u worden geimporteerd.

 !else
  Deze oefening <tt>$del</tt> bestaat niet in uw klas. 
 !endif
 !exit
!endif





