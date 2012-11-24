
!read themes/$wims_theme/table.proc
!if $special_parm=flydraw
 <p><center><h3>Flydraw commando's</h3></center><p>
 !read help/flydraw.phtml
 !exit
!endif

<p>
!if $special_parm=jsxgraph
   $name_remark_jsxgraph
  <textarea id="jsxbox" cols="100" rows="15" name="wims_jsxgraph" readonly>
   !read example.jsxscript
  </textarea>
 !goto common
!endif

!if $special_parm=pari
 <a href="http://pari.math.u-bordeaux.fr/dochtml/html.stable/" target="wims_external">
 Pari/GP commando's
 </a>
!goto common
!endif
</p>
:common

<form action="http://www.google.com/search"/>
<div>
<input type="submit" value="Search Google"/> voor documentatie van
<select name="q">
!for sw in $swname
 <option value="$sw documentation">$sw</option>
!next sw
</select>
</div>
</form>


!if $special_parm!=flydraw
<p>
!href cmd=help&special_parm=flydraw Flydraw documentatie
.
</p>
!endif
!if $special_parm!=pari
<p>
 <a href="http://pari.math.u-bordeaux.fr/dochtml/html.stable/" target="wims_external">
 Pari/GP commando's
 </a>
</p>
!endif
<p>
Invoer en uitvoer  van de aangesproken programma's is beperkt tot 16K.
Uiteraard is ook netwerktoegang onderbopnden en is het schijven van tempfiles -mits toegestaan- beperkt tot de huidige directory.
De procestijd wordt beperkt tot een paar seconden. Het geheugengebruikt wordt bewaakt.
</p><p>
!if $securetest=$empty
    Niet geinstalleerde software kan mogelijke worden uitgevoerd op andere WIMS servers : <span class="tt">$swname_comp</span>.<p>
!else
    Speciale aanwijzing voor C interface: de programmastart is <span class="tt">int test(void)</span>,
 en niet <span class="tt">main()</span>!
!endif
</p>
