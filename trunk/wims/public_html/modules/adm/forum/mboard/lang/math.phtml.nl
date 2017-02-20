
<h3>Hoe kan ik Wiskundige formules in een forum bericht verwerken?</h3>
 
Afgezien van de normale manieren om berichten op te stellen, 
is het bij WIMS mogelijk om ook heel gemakkelijk <b>Wiskundige formules</b> op te nemen in een forum bericht.  
Wanneer een lezer uw bericht leest, worden de wiskundige formules
automatisch geformateerd zoals het hoort.
<p>
Het message board gebruikt het backslash karakter <span class="wims_emph">\</span>
om te zien wannneer er een wiskundig symbool of formule wordt bedoeld.
De regels zijn als volgt:
<p>
Als U een normale backslash <span class="wims_emph">\</span>  wilt, kunt U typen: <span class="tt">\\</span>.
<p>
Wilt U wiskundig materiaal of griekse letters gebruiken in het bericht,
typ dan gewoon <span class="tt">\</span> in, gevolgd door de naam van het symbool of de griekse letter
Bij voorbeeld, <span class="tt">\pi</span> geef dan $m_pi,
<span class="tt">\le</span> geeft $m_le, <span class="tt">\pm</span> wordt $m_pm, <span class="tt">\rightarrow</span> wordt
$m_rightarrow, enz.
De namen van de wiskundige symbolen volgen de TeX/LaTeX standaard.<br />
Hier is een lijst van
!href target=wims_help module=help/wimsdoc.en&subject=mathfonts#mathfonts wiskundige symbolen 
 en hun namen (vervang <span class="tt">$$m_</span> door <span class="tt">\</span> in de naam).
<p>
Maar algemeen, om een gehele formule in een bericht te laden, geef dan
de formule vlgs TeX in.<br />
Om de formule te formateren, plaats een backslash \ gevolgd door
een paar ronde haken.<br /> 
Bijvoorbeeld:
 <span class="tt">\(x^3-3x+cos(2pi*x)^5)</span> wordt
!insmath x^3-3*x+cos(2pi*x)^5
, or <span class="tt">\(sqrt(x^2+y^2))</span> wordt
!insmath sqrt(x^2+y^2)
. U kunt invoeren <span class="tt">\(integrate(x^2+1)dx)</span> voor
!insmath integrate(x^2+1)*dx
, of<span class="tt">\(integrate(exp(x^2+1),x=1..infinity))</span> voor
!insmath integrate(exp(x^2+1),x=1..infinity)
. U kunt ook een som 
!insmath sum(1/n^2,n=1..infinity)
 aangeven door <span class="tt">\(sum(1/n^2),n=1..infinity)</span>, of het produkt
!insmath product(n/(n+1),n=1..infinity)
 door<span class="tt"> \(product(n/(n+1),n=1..infinity)</span>.
<p>
Meer help is over het invoeren van Wiskunde is beschikbaar op 
!href target=wims_help module=help/main&chapter=1&open=1_math#math deze pagina
.
<p>
Om de matrix
!insmath [1,2,3;4,5,6;7,8,9]
, te laten zien moet U intypen <span class="tt">\([1,2,3;4,5,6;7,8,9])</span>. 
Geneste matrices worden ook geaccepteerd.
 <div class="wimscenter">
Terug naar het
!href cmd=resume forum
</div>

