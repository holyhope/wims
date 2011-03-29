
!set wims_warn_header=<p><font color="red"><blink><b>Waarschuwing.</b></blink></font>

!if ambiguous iswordof $wims_warn_rawmath
 $wims_warn_header
 U hebt een vreemde formule ingetypt, de WIMS interpretatie
 hiervan kan verschillen met uw bedoelingen. Controleer de formule s.v.p.

 <p>
 !set wims_warn_rmremark=yes
!endif

!if unknown iswordof $wims_warn_rawmath
 $wims_warn_header
 WIMS heeft een ongedefinieerde variabele of functienaam ontdekt
 <font color="red"><b><tt>$wims_warn_rawmath_parm</tt></b></font> in uw formule. Een typfoutje misschien?
 <p>
 !set wims_warn_rmremark=yes
!endif

!if flatpower iswordof $wims_warn_rawmath
 <p><font color="red"><b>Hint.</font></b>
 Wil je  <font color="green">x<sup>2</sup></font> in typen? Typ dan:
 <tt>x^2</tt> of <tt>x**2</tt>.
 <p>
!endif

!if badprec iswordof $wims_warn_rawmath
 $wims_warn_header
 ``<tt>x^1/2</tt>'' betekent <font color="green">x/2</font>! typ s.v.p.
 ``<tt>x^(1/2)</tt>'' voor <font color="green">x<sup>1/2</sup></font>.
 <p>
!endif

!if unmatched_parentheses iswordof $wims_warn_rawmath
 $wims_warn_header
 WIMS heeft een missend haakje ontdekt in een formule.
 Graag even corrigeren 
 <p>
!endif

!if $wims_warn_rmremark=yes
 Gebruik altijd ``<tt>*</tt>'' voor vermenigvuldigen 
 en altijd haakjes voor functie argumenten
 <small>Voor experts. Als je niet wilt dat WIMS je uitdrukkingen
 interpreteerd begin dan met ``<tt>1-1+</tt>''.</small>
 <p>
!endif

