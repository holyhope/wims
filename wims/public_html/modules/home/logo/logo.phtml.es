
<center><h1>
El logo de WIMS
</h1>
<p>
<img src="gifs/logo-160.gif" align=middle alt="logo">
</center>
<p>La curva representa el trazo de un punto sobre un disco de radio 1 rodando
dentro de un círculo fijo de radio 3. Y la deformación de la curva representa
lo que ocurre cuando la distancia del punto al centro del disco movible varía 
entre 0 y infinito.
<p>
Este logo animado se creó con la aplicación
!href module=tool/geometry/animtrace.es Representaciones animadas
 bajo WIMS.
<p>
<ul>
<li>Tipo de dibujo: curva paramétrica en 2D.
<li>Ecuaciones:
<pre>
     x=(1-s)*cos(t+pi*s)+s*cos(2*t)
     y=(1-s)*sin(t+pi*s)-s*sin(2*t)
</pre>
  (donde s es el ``parámetro secuencial'' como se define en 
  <font color=red>Representaciones animadas</font>.)
<li>Rango de las variables:
<pre>
     -1&lt;x&lt;1, -1&lt;y&lt;1, 0&lt;t&lt;2*pi.
</pre>
</ul>
Puede
!href module=tool/geometry/animtrace.es&cmd=new&type=parametric2D&x1=(1-s)*cos(t+pi*s)+s*cos(2*t)&y1=(1-s)*sin(t+pi*s)-s*sin(2*t)&tleft=0&tright=2*pi&xleft=-1&xright=1&yleft=-1&yright=1&special_parm=noshow cargar directamente estos parámetros
 en el menú de <font color=red>Representaciones animadas</font>
para representarlo usted mismo.
<p>
Fecha de creación 03-27-1998, &copy; XIAO, Gang.
<p><hr> <p>
<center>
!href module=home Volver a wims
.</center>

