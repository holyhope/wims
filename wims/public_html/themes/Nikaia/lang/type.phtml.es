!read adm/title.phtml 3\
Explorar por tipo de recursos

Los tipos de recursos siguientes están disponibles en este servidor.

<ol class="wims_browse_type_list">
<li class="wims_browse_type_list">
Calculadoras y generadoras de gráficas en línea: entre otras, puede echar un vistazo a
 <ul class="wims_browse_type_list">
 <li class="wims_browse_type_list">
  !set cat=T
  !reset key
  !href $search_addr Todas la herramientas en línea disponibles
  ordenadas por popularidad.
 </li><li class="wims_browse_type_list">
  Calculadoras numéricas:
  !set cat=P
  !set key=número, complejo, raíces
  !href $search_addr calculadoras sencillas emergentes
  (simplificar, fracciones, conversiones, factorización, números complejos, etc.) y
  varias
  !set cat=T
  !set key=número, raíces
  !href $search_addr calculadoras especializadas
  (enteros, fracciones continuas, características positivas, etc.)
 </li><li class="wims_browse_type_list">
  Análisis
  !set key=análisis, cálculo, funciones
  !set cat=P
  !href $search_addr herramientas emergentes
  y
  !set cat=T
  !href $search_addr calculadoras
, para casi todo lo que desee averiguar en el cálculo o las funciones:
  derivada, integral, límite, mínimo/máximo, raíces, secuencias y series,
  transformaciones de Fourier y Laplace, etc.
 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=álgebra lineal
  !href $search_addr Calculadoras de álgebra lineal
  $ : sistemas lineales, matrices, determinante, espacios vectoriales, etc.
 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=plotter
  Varias trazadoras:
  !href $search_addr herramientas complejas
  a menudo con animaciones y ejemplos, o
  !set cat=P
  !href $search_addr trazadoras emergentes rápidas
. Trazan curvas, superficies, secuencias/series...
 </li><li class="wims_browse_type_list">
  !set cat=T
  !set key=estadísticas, datos
  !href $search_addr Calculadoras estadísticas
$ : medias y desviaciones, histograma, regresión...
 </li></ul>
 
</li><li class="wims_browse_type_list">Ejercicios interactivos: los ejercicios de WIMS son de varios estilos diferentes.
En particular, hay:
 <ul class="wims_browse_type_list">
  <li class="wims_browse_type_list">
  !set cat=X
  !reset key
  !href $search_addr Todos los ejercicios disponibles
  clasificados por orden de popularidad.
  </li><li class="wims_browse_type_list">
  !set key=opciones gráficas
  !href $search_addr Opciones gráficas
  presentan problemas por medio de imágenes al azar, y le piden que elija la
  imagen correcta.
  </li><li class="wims_browse_type_list">
  !set key=tiro
  !href $search_addr Ejercicios de tiro
  le piden que pulse en la posición de un punto oculto, y le dan una 
  puntuación a sus respuestas según la precisión de sus clicks.
  </li><li class="wims_browse_type_list">
  !set key=dibujo
  !href $search_addr Ejercicios de dibujo
  le piden que dibuje una curva con el ratón, y puntúan sus respuestas 
  según la precisión de sus curvas.
  </li><li class="wims_browse_type_list">
  !set key=coincidencia
  !href $search_addr Ejercicios de coincidencia
  le presentan una imagen (una curva), y le piden que halle una expresión
  que genere esa imagen, normalmente permitiéndole varios intentos.
  </li><li class="wims_browse_type_list">
  !set key=deductio
  !href $search_addr Ejercicios Deductio
  que permiten deducciones y razonamientos interactivos.
  </li><li class="wims_browse_type_list">
  !set key=diálogo
  !href $search_addr Ejercicios de diálogo
  en los cuales usted puede hacerle preguntas al servidor para resolver un problema.
  ¡Pero recibirá una penalización si hace preguntas inútiles!
  </li><li class="wims_browse_type_list">
  !set key=escenario
  !href $search_addr Ejercicios de escenario
  presentan un razonamiento aleatorio y posiblemente falso, y usted debe descubrir
  el paso incorrecto.
  </li><li class="wims_browse_type_list">
  !set cat=O
  !reset key
  !href $search_addr Ejercicios OEF
  (Open Exercise Format, Formato Abierto de Ejercicios)
  son colecciones de ejercicios creados en línea. La preguntas pueden ser altamente
  aleatorias, y las respuestas pueden ser múltiples opciones, números, funciones, etc.
  </li><li class="wims_browse_type_list">
  !set cat=X
  !set key=contrib
  !href $search_addr Ejercicios
  procedentes de contribuciones de varios profesores e instituciones de enseñanza.

 </li></ul>
 Puede también examinar los ejercicios
 !href module=$module&cmd=new&job=subject por temas
.
</li><li class="wims_browse_type_list">Matemáticas recreativas: 
 !set cat=R
 !reset key
 !href $search_addr clasificadas por orden de popularidad
.
</li>

</ol>
