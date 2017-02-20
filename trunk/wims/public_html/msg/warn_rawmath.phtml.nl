
!set wims_warn_header=<span class="wims_warning">$wims_name_warning.</span>

!if ambiguous iswordof $wims_warn_rawmath
 $wims_warn_header
 <p>
 U hebt een vreemde formule ingetypt, de WIMS interpretatie
 hiervan kan verschillen met uw bedoelingen. Controleer de formule s.v.p.
 </p>
 !set wims_warn_rmremark=yes
!endif

!if unknown iswordof $wims_warn_rawmath
 $wims_warn_header
 <p>
 WIMS heeft een ongedefinieerde variabele of functienaam ontdekt
 <span style="color:red"><b><tt>$wims_warn_rawmath_parm</tt></b></span> in uw formule. Een typfoutje misschien?
 </p>
 !set wims_warn_rmremark=yes
!endif

!if flatpower iswordof $wims_warn_rawmath
 <p><span class="wims_warning">Hint.</span>
 Wil je  <span style="color:green">x<sup>2</sup></span> in typen? Typ dan:
 <tt>x^2</tt> of <tt>x**2</tt>.
 </p>
!endif

!if badprec iswordof $wims_warn_rawmath
 $wims_warn_header
 <p>
 ``<tt>x^1/2</tt>'' betekent <span style="color:green">x/2</span>! typ s.v.p.
 ``<tt>x^(1/2)</tt>'' voor <span style="color:green">x<sup>1/2</sup></span>.
 </p>
!endif

!if unmatched_parentheses iswordof $wims_warn_rawmath
 $wims_warn_header
 <p>
 WIMS heeft een missend haakje ontdekt in een formule.
 Graag even corrigeren 
 </p>
!endif

!if $wims_warn_rmremark=yes
 <p>
 Gebruik altijd ``<tt>*</tt>'' voor vermenigvuldigen 
 en altijd haakjes voor functie argumenten
 <small>Voor experts. Als je niet wilt dat WIMS je uitdrukkingen
 interpreteerd begin dan met ``<tt>1-1+</tt>''.</small>
 </p>
!endif

