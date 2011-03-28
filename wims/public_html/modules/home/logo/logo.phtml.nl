
<center><h1>
Het WIMS logo 
</h1>
<p>
<img src="gifs/logo-160.gif" align="middle" alt="logo">
</center>
<p>
Deze curve volgt een punt op een schijf met straal 1, rond draaiend
binnen een vaste cirkel met straal 3. 
De vorming van deze curve volgt als de afstand
van het punt naar het centrum van de bewegende schijf varieert van
0 tot oneindig. 
<p>
Dit bewegende plaatje is gemaakt met de module
!href module=tool/geometry/animtrace Tracés animés
 met WIMS.
<p>
<ul>
<li>Type plot: een parametrische curve in 2D.</li>
<li>Vergelijkingen:
<pre>
     x=(1-s)*cos(t+pi*s)+s*cos(2*t)
     y=(1-s)*sin(t+pi*s)-s*sin(2*t)
</pre>
  (waarbij s de ``sequentiele parameter'' is, zoals gedefineerd in 
  <font color="red">Tracés animés</font>.)
</li>
<li>Variabelen range:
<pre>
     -1&lt;x&lt;1, -1&lt;y&lt;1, 0&lt;t&lt;2*pi.
</pre>
</li>
</ul>
Je kunt ook
!href module=tool/geometry/animtrace.en&cmd=new&type=parametric2D&x1=(1-s)*cos(t+pi*s)+s*cos(2*t)&y1=(1-s)*sin(t+pi*s)-s*sin(2*t)&tleft=0&tright=2*pi&xleft=-1&xright=1&yleft=-1&yright=1&special_parm=noshow  direct deze instellingen

in het menu van <font color="red">Tracés animés</font>
om het zelf te plotten.
<p>
Gemaakt op 03-27-1998, &copy; XIAO, Gang.
<p><hr> <p>
<center>
!href module=home Terug naar WIMS
</center>
</div>
