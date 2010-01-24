
<h3>Hoe kan ik Wiskundige formules in een forum bericht verwerken?</h3>
 
Afgezien van de normale manieren om berichten op te stellen, 
is het bij WIMS mogelijk om ook heel gemakkelijk <b>Wiskundige formules</b> op te nemen in een forum bericht.  
Wanneer een lezer uw bericht leest, worden de wiskundige formules
automatisch geformateerd zoals het hoort.
<p>
Het message board gebruikt het backslash karakter `<font color=blue>\</font>'
om te zien wannneer er een wiskundig symbool of formule wordt bedoeld.
De regels zijn als volgt:
<p>
Als U een normale backslash `<font color=blue>\</font>'  wilt, kunt U typen: <tt>\\</tt>.
<p>
Wilt U wiskundig materiaal of griekse letters gebruiken in het bericht,
typ dan gewoon <tt>\</tt> in, gevolgd door de naam van het symbool of de griekse letter
Bij voorbeeld, <tt>\pi</tt> geef dan $m_pi,
<tt>\le</tt> geeft $m_le, <tt>\pm</tt> wordt $m_pm, <tt>\rightarrow</tt> wordt
$m_rightarrow, enz.
De namen van de wiskundige symbolen volgen de TeX/LaTeX standaard.<br>
Hier is een lijst van
!href target=wims_help module=help/wimsdoc.en&subject=mathfonts#mathfonts wiskundige symbolen 
 en hun namen (vervang <tt>$$m_</tt> door <tt>\</tt> in de naam).
<p>
Maar algemeen, om een gehele formule in een bericht te laden, geef dan
de formule vlgs TeX in.<br>
Om de formule te formateren, plaats een backslash \ gevolgd door
een paar ronde haken.<br> 
Bijvoorbeeld:
 <tt>\(x^3-3x+cos(2pi*x)^5)</tt> wordt
!insmath x^3-3*x+cos(2pi*x)^5
, or <tt>\(sqrt(x^2+y^2))</tt> wordt
!insmath sqrt(x^2+y^2)
. U kunt invoeren <tt>\(integrate(x^2+1)dx)</tt> voor
!insmath integrate(x^2+1)*dx
, of<tt>\(integrate(exp(x^2+1),x=1..infinity))</tt> voor
!insmath integrate(exp(x^2+1),x=1..infinity)
. U kunt ook een som 
!insmath sum(1/n^2,n=1..infinity)
 aangeven door <tt>\(sum(1/n^2),n=1..infinity)</tt>, of het produkt
!insmath product(n/(n+1),n=1..infinity)
 door<tt> \(product(n/(n+1),n=1..infinity)</tt>.
<p>
Meer help is over het invoeren van Wiskunde is beschikbaar op 
!href target=wims_help module=help/main&chapter=1&open=1_math#math deze pagina
.
<p>
Om de matrix
!insmath [1,2,3;4,5,6;7,8,9]
, te laten zien moet U intypen <tt>\([1,2,3;4,5,6;7,8,9])</tt>. 
Genested matrices worden ook geaccepteerd.
<p><center>
Terug naar het
!href cmd=resume forum
</center> <p>

