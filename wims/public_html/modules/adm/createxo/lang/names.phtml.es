!set lang_exists=yes

!if $wims_read_parm!=
  !goto $wims_read_parm
!endif

!distribute lines Modo guiado\
  Modo experto\
  Modo fichero\
  modelos preparados\
  Enviar el fichero\
  Código de su ejercicio\
  Volver al menú inicial\
  Continuar al contenido del ejercicio\
  Modificar un ejercicio existente de la clase\
  Volver a la etapa precedente\
  Enviar el código fuente\
  Vaciar\
  Demostración\
  Adaptar\
  Probar el ejercicio\
  Corregir el error\
  Volver a\
  La realización de su ejercicio será como sigue.\
  Aquí tiene los modelos de ejercicios disponibles. Elija uno.\
  Módulo que contiene temporalmente su ejercicio\
into wims_name_normalmode, wims_name_rawmode,wims_name_filemode,\
  name_model,name_sendfile,name_source,name_menuback,name_continue,name_modify,\
  name_prevstep,name_sendsource,name_clean,name_demo,wims_name_adapt,name_testexo,\
  name_correction,name_backmodule,name_realisation,name_availablemodels,name_temp_module

!set name_normal=!lowercase $wims_name_normalmode
!set name_raw=!lowercase $wims_name_rawmode
!set name_file=!lowercase $wims_name_filemode

!set name_modefile1=Está en modo fichero para la creación de ejercicios. Bajo este modo\
   puede enviar un fichero fuente OEF local al servidor. Para crear un ejercicio desde cero preferirá el
 !set name_modefile2=Para corregir en línea, pueden también utilizar el

!distribute line Ejercicios básicos\
Ejercicios con una lista de datos\
Ejercicios de química\
Juegos\
Ejercicios con imagenes o audio\
Escoger ítems\
Diferentes tipos de cuestiones\
Llenar agujeros\
Ordenar\
Clasificar\
into name_first,name_datalist,name_chemistry,name_game,name_imaudio,\
name_select,name_question,name_gapfill,name_order,name_classify

!set name_save=!nosubst  Aquí está el código fuente de su ejercicio <span class="wims_warning">$oef_title</span>,\
 en formato OEF (Open Exercice Format). Para guardarlo, corte el texto situado entre las dos líneas \
 horizontales, y péguelo en un archivo.

!distribute lines Número de parámetros\
  Número de respuestas\
  También puede enviar un fichero de imagen\
  O modificar el fichero fuente y después\
  añadir este ejercicio a su clase, bien\
  para sustituir al antiguo\
  para hacer de él uno nuevo\
  reenviarlo\
  Ponerlo en el módulo de desarrollo\
  hacer una copia \
  de seguridad del código fuente !\
into name_parameter_cnt,name_answer_cnt,name_deposit,name_modify,name_putinclass,\
name_replace,name_new,name_sendagain,name_developer,name_savesource,name_download

!set name_success=El software ha reconocido su ejercicio como válido

!if $level=1
!distribute lines Dele un título al ejercicio que quiere crear\
  Formato del enunciado del problema\
  Este ejercicio pedirá\
  respuestas libres y \
  respuestas de opciones múltiples\
  Las respuestas numéricas no calculadas (como <span class="tt">3*5-sin(pi/3)</span>) serán\
  aceptadas,rechazadas\
  condiciones especiales para corregir las respuestas libres\
into name_givetitle,name_giveformat,name_exo,name_answer1,name_answer2,\
name_nonnumeric,name_prompt,name_condition
!endif

!if $level=2
 !set types=!sort nocase lines \
auto,default\
expresión literal,litexp\
expresión algebraica,algexp\
expresión formal,formal\
texto aproximado,atext\
texto convertido en minúsculas,nocase\
texto exacto,case\
texto bruto,raw\
ecuación,equation\
conjunto finito,set\
matriz,matrix\
número,numeric\
número con zona,range\
número con unidad,units\
función numérica,function\
vector,vector\
palabras en una lista,wlist
chset,chset\
clickfill,clickfill\
dragfill,dragfill\
compose,compose\
coord,coord\
correspond,correspond\
keyboard,keyboard\
matrix,matrix\
numexp,numexp\
reorder,reorder\
fset,fset\
aset,aset\
sigunits,sigunits\
time,time

!distribute lines Ahora, por favor, introduce el contenido de tu ejercicio \
 Puedes definir los parámetros aleatorios aquí\
 La explicación del ejercicio \
 Respuestas libres\
 Solución correcta\
 Precisión requerida para respuestas numéricas\
 Las funciones (numéricas) serán comparadas en el intervalo\
 Condiciones para el análisis de respuestas (numéricas)\
 Nombre de la condición\
 Definición de la condición\
 Elecciones \
 Elecciones correctas\
 Elecciones incorrectas\
 Puedes dar opcionalemente una nota y/o solución\
 Indicación\
 Solución\
into name_content,name_alea,name_statement,name_free,name_goodsol,name_precision,name_function,\
 name_condition_numeric,name_name_condition,name_definition,name_multiple,name_goodchoice,name_badchoice,\
 name_option,name_indication,name_solution

!endif

!if $level=4
  !set name_update1=!nosubst El ejercicio <span class="tt">$existing.oef</span> se ha actualizado con éxito
  !set name_update2=Ha fallado la actualización del ejercicio <span class="tt">$existing</span> en el módulo
  !set name_update3=Su ejercicio se ha instalado con éxito.
   !set name_update4= Hemos encontrado un ejercicio idéntico en su clase. Se ignoran los registros dobles.\
  !set name_update5=Este ejercicio será accesible únicamente a los participantes de su clase, \
    y solamente si lo pone en una hoja de trabajo.
  !distribute lines Ahora puede\
    Consultar los ejercicios de la clase\
    y eventualmente añadirlos a las hojas de trabajo\
 into name_youcan, name_consult,name_sheet
!endif

!if $level=7
 name_warning_empty=Por favor, escoja el nombre del fichero de código.
 name_choice_module=Seleccionar un módulo
 name_choice_filename=Nombre del fichero de código del ejercicio (utilizar solo caracteres alfanuméricos)
 name_register_dev=Guardar el fichero de código del ejercicio en la cuenta de Modtool
!endif

!distribute lines Está en modo experto de creación de ejercicios. \
  Puesto que este ejercicio se basa en un modelo estándar, inténtelo \
  Entre el código entero \
  para registrar un fichero de código existente, copie el fichero en la ventana.\
 Ahí tiene el código de un ejercicio existente de su clase. \
  Pueden modificarlo en la ventana siguiente. \
  Ahí tiene el código de un ejercicio público que quiere importar. Pueden modificarlo en la ventana siguiente antes de ponerlo en la clase. \
Pueden probar algunos programas externos con el \
probador de script \
 into name_brut,name_try,name_allsource,name_copy,name_source2,name_modify_window,name_public,name_test_extern,name_testerscript

!exit
:delete
El ejercicio <em>$deltitle</em> se ha eliminado de la lista de ejercicios de la
clase.

En el caso en que haya sido un error y desee repararlo, aquí tiene
el código fuente del ejercicio, que puede guardar como medida de seguridad,
y copiarlo posteriormente en

!exit
:model
<b>Note</b>. Estos modelos tienen por objeto permitir a los más apremiados construir
rápidamente sus ejercicios. Tienen pues a menudo una estructura simplificada
y estandarizada, y no ofrecen la plena potencia de la sintaxis OEF.
Pero pueden siempre poner los ejercicios en modo experto para añadir más
funcionalidades o modificarlos según su gusto.
!exit

:register
Su ejercicio se ha registrado con éxito en este servidor. Le agradecemos
sinceramente su contribución, en nombre de todos aquellos que se
beneficiarán de él.
<p>
El administrador de este sitio verificará su ejercicio, y decidirá si ponerlo
o no en una categoría apropiada. 
Esto podría tardar algún tiempo.
/p>
!exit
