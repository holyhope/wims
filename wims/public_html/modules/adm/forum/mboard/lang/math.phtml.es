
<h3>Cómo incluir fórmulas matemáticas en los mensajes.</h3>

Además de las características convecionales que le permiten navegar
a través de los mensajes del foro, el foro de discusión
de WIMS hace posible incluir formulas matemáticas de una manera muy
cómoda. Cuando el lector vea su mensaje, verá las fórmulas formateadas
automáticamente.
<p>
El gestor de foros de discusión usa la barra invertida <span class="wims_emph">\</span>
para detectar cuándo quiere usted que interprete lo que escribe como un símbolo
matemático o una fórmula. La regla es como sigue:
<p>
Si quiere escribir una `\' en su mensaje y quiere que aparezca como una
barra invertida, la escribe dos veces: `<span class="tt">\\</span>'.
<p>
Si sólo quiere insertar algunos símbolos matemáticos o letras
griegas en su mensaje, no tiene más que escribir una <span class="tt">\</span>  seguida por el
nombre del símbolo o de la letra griega. Por ejemplo, <span class="tt">\pi</span> le devuelve
$m_pi, <span class="tt">\le</span> da $m_le, <span class="tt">\pm</span> da $m_pm, <span class="tt">\rightarrow</span> 
da $m_rightarrow, etc. Los nombres de los símbolos siguen la convención 
estándar de TeX. Aquí tiene una
!href target=wims_help module=help/wimsdoc.en&subject=mathfonts#mathfonts lista de símbolos matemáticos y sus nombres
 (sustituya <span class="tt">$$m_</span> por <span class="tt">\</span> en los nombres).
<p>
De forma más generalizada, para insertar una fórmula matemática completa en el mensaje,
puede escribir la fórmula de la forma normal en que la introduciría en cualquier
software matemático o cualquier herramienta de cálculo de WIMS. Para 
formatear la fórmula y mostrarla bonita en el foro de discusión, sólo tiene
que encerrarla entre una par de paréntesis precedidos por una barra invertida `\'.
Por ejemplo,, <span class="tt">\(x^3-3x+cos(2pi*x)^5)</span> le devuelve
!insmath x^3-3*x+cos(2pi*x)^5
, o <span class="tt">\(sqrt(x^2+y^2))</span> le da
!insmath sqrt(x^2+y^2)
. Puede escribir <span class="tt">\(integrate(x^2+1)dx)</span> para
!insmath integrate(x^2+1)*dx
, o <span class="tt">\(integrate(exp(x^2+1),x=1..infinity))</span> para
!insmath integrate(exp(x^2+1),x=1..infinity)
. También puede escribir la suma
!insmath sum(1/n^2,n=1..infinity)
 usando <span class="tt">\(sum(1/n^2,n=1..infinity)</span>, o el producto
!insmath product(n/(n+1),n=1..infinity)
 usando <span class="tt">\(product(n/(n+1),n=1..infinity)</span>.
<p>
Puede obtener más ayuda acerca de cómo introducir expresiones 
matemáticas en
!href target=wims_help module=help/main&chapter=1&open=1_math#math esta página
.
<p>
Para mostrar una matriz
!insmath [1,2,3;4,5,6;7,8,9]
, escribiría <span class="tt">\([1,2,3;4,5,6;7,8,9])</span>. Se aceptan matrices anidadas
(y se representarán correctamente).
<p>
Para expertos en TeX o LaTeX, tenga en cuenta que si el foro de discusión ve
una fórmula encerrada entre un par de paréntesis precedidos por <span class="tt">\</span> 
que contiene barras invertidas, lo interpretará como fuente de TeX, y 
lo enviará directamente a TeX para que lo formatee. Esto le permitirá escribir
fórmulas muy complejas si sabe cómo se escriben en TeX.
<p>
Finalmente, el botón `Vista previa' de la página de composición de los mensajes
le permite comprobar si la fórmula que ha introducido se mostrará
correctamente.

 <div class="wimscenter">
!href cmd=resume Volver a los mensajes.
</div>

