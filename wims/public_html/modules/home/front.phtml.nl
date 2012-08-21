Op deze website, vind je
<ul class="wims_home_list">
<li>
!href module=$module&cmd=new&search_category=D Lesmateriaal 
&nbsp;en verwijzingen naar diverse onderwerpen.
</li><li>
!href module=$module&cmd=new&search_category=T Online rekenmachines en functie plotters
&nbsp;: getallen, functies, matrices, krommen, oppervlakken, etc.
</li><li>
!href module=$module&cmd=new&search_category=X Interactieve oefeningen
&nbsp;van verschillende stijl en moeilijkheidsgraad.
</li><li>
!href module=$module&cmd=new&search_category=R Wiskundige ontspanning
&nbsp;: puzzels en spelletjes.
</li>
</ul>
Bezoek:
<ul class="wims_home_list">
<li>
!href module=adm/class/classes Openbare virtuele klaslokalen.
</li>
!if $wims_theme_version=0
<li>
!href module=adm/doc Interactieve Documenten.
 en                                                                                                                                        
!href module=help/teacher/faq FAQ [Frans]
.</li>
!endif
</ul>

!!exit
!if $wims_theme_version=0
Je kunt ook deze website
!href module=adm/browse&$browse_parm browsen
.
!endif

For mathematical formulas, the server is currently set to <a href="http://www.w3.org/Math/" target="wims_external">MathML</a> 
if you have a suitable browser. If not, you can use another browser or 
use the server with "math with images" in 
!href module=adm/light&+phtml=useropts.phtml.$lang $wims_name_pref

!! adapted to french version...