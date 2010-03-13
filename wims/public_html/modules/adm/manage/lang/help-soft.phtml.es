<h3>Software empleado internamente: $help_conf</h3>

!goto $help_conf

:pari
PARI/GP es un programa de cálculo teórico de precisión arbitraria. Debido a
su gran velocidad, es la herramienta de cálculo  ideal para muchas de las necesidades
de cálculo  de WIMS. Muchos módulos lo utilizan, incluidos numerosos ejercicios de
álgebra lineal. Si este programa no está disponible gran parte del servidor
funcionará de forma deficiente.
<p>
Versión recomendada: 2.1.* (otras versiones pueden presentar problemas de
compatibilidad).
!goto end

:mupad
MuPAD es una gran aplicación de álgebra simbólica. Es un tanto lento en su carga
y no es de fuente abierta, y por tanto se usa de forma limitada por los
módulos WIMS. Los módulos que hacen uso de MuPAD incluyen especialmente las
herramientas en línea relacionadas con el cálculo.
<p>
Debido a sus problemas de licencia, MuPAD debe descargarse directamente del sitio
de su distribuidor (http://www.mupad.de/). Por favor siga las instrucciones del
paquete sobre cómo instalarlo, y ponga la ruta exacta de instalación en la
configuración de la orden MuPAD.
<p>
Versión recomendada: 1.4.* (otras versiones pueden presentar problemas de
compatibilidad).
!goto end

:maxima
Maxima es un paquete de fuente abierta de álgebra simbólica. Se usa
principalmente cuando deben calcularse derivadas y/o integrales.
<p>
Debemos señalar que la versión 5.6 (con GCL 2.4) de Maxima tiene un fallo
que impide que se compile bajo RedHat 7.*. Si se encuentra con problemas
de este tipo, descargue una copia de una versión anterior (la 5.4) desde
<a target=wims_external
href="http://wims.unice.fr/download/other-packages/">http://wims.unice.fr/download/other-packages/</a>.
<p>
Versión recomendada: 5.4. (otras versiones pueden presentar problemas de
compatibilidad).
!goto end

:yacas
Yacas (Yet Another Computer Algebra System)
es un nuevo paquete de fuente abierta de álgebra simbólica. Debido a su
rápido desarrollo es un paquete muy prometedor. En consecuencia es probable
que se use cada vez más en WIMS.
<p>
!goto end

:octave
Octave es un paquete de fuente abierta de análisis numérico. Todavía no se
usa en WIMS. En consecuencia puede saltarse su instalación por ahora.
!goto end

:m2
Macaulay 2 es una potente aplicación especializada en álgebra conmutativa.
Por ahora únicamente se utiliza en una pocas herramientas de cálculo que
utilizan ventanas emergentes. Si no lo instala, estas pocas calculadoras
emergentes no funcionarán, pero el resto del servidor no se verá afectado.
!goto end

:gap
GAP es un potente programa de cálculo para la teoría de los grupos, en la
actualidad usado por dos herramientas de WIMS que computan grupos finitos.
Necesitará GAP si quiere que funcionen estas dos herramientas.
!goto end

:povray
Povray es una aplicación gráfica de traza de rayos. La utilizan las herramientas
gráficas para renderizar superficies de alta calidad. En la actualidad la
incluyen la mayor parte de las distribuciones de Linux. Si le da problemas,
antes de nada compruebe que está instalado en su sistema Linux e instálelo si es
necesario.
<p>
Versión recomendada: 3.0*-3.1* (otras versiones pueden presentar problemas de
compatibilidad).
!goto end

:end

<p>
Puede hacer una búsqueda del término <tt>$help_conf</tt> en la página
principal de WIMS para obtener la lista de módulos que hacen uso de este software.

