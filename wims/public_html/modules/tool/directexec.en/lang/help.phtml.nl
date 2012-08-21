
!read themes/$wims_theme/table.proc
!if $special_parm=flydraw
 <p><center><h3>Flydraw commands</h3></center><p>
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
 Pari/GP commands
 </a>
!goto common
!endif
</p>
:common

<form action="http://www.google.com/search">
<input type="submit" value="Search Google"> for documentation of
<select name="q">
!for sw in $swname
 <option value="$sw documentation">$sw
!next sw
</select></form>


!if $special_parm!=flydraw
<p>
!href cmd=help&special_parm=flydraw Flydraw documentation
.
</p>
!endif
!if $special_parm!=pari
<p>
 <a href="http://pari.math.u-bordeaux.fr/dochtml/html.stable/" target="wims_external">
 Pari/GP commands
 </a>

!endif
<p>
Input and output of any execution is limited to 16K. For obvious security
reasons, there is no network access, file writing is limited to the current
directory if not downright denied, and execution time is limited to a few seconds.
</p>
<p>
!if $securetest=$empty
 Other software can be executed on some other wims servers as <tt>$swname_comp</tt>.<p>
!else
 Special note for C interface: the entry point is <tt>int test(void)</tt>,
 but not <tt>main()</tt>!
!endif
</p>