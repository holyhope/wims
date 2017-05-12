!set name_subtitle = Ficheros binarios para el ejercicio
!set name_over_quota = No puede añadir más ficheros a su clase porque su contendido\
 ha igualado o superado el espacio de disco autorizado. Lo sentimos.
!set name_add_file = Añadir un nuevo fichero
!set name_add_file_label = Fichero para el ejercicio:
!set name_add_file_help = Puede cargar diferentes tipos de ficheros (imagen, audio, pdf, ...).

!set name_empty_imglist = Este ejercicio no tiene aún ningún fichero binario.
!set name_imglist = Lista de ficheros binarios del ejercicio
!set name_filename = Nombre del fichero
!set name_preview = Vista
!set name_html_code = Código HTML
!set name_oef_code = Código OEF
!set name_Actions = Acciones

!set name_img_default_alt = vista del fichero $$i
!set name_img_accessibility_alt = Describa aquí la imagen

!set name_some_browsers = algunos navegadores web
!set name_ogg_warning = no pueden leer ficheros .ogg.


!set name_access_via_imagedir = Puede acceder a estos ficheros en el enunciado del ejercicio \
 a través del parámetro interno <span class="tt wims_code_variable">\imagedir</span>.

!set name_how_to_hide_help = <h2>Ocultar el nombre de la imagen</h2>\
    If you pick a random picture, the file name can be an help to the student.\
    You can hide this file name with this code:\
    <pre>\img{\imagedir/picture.jpg alt="$name_img_accessibility_alt"}</pre>\
    If the student takes a look at the generated page, he will only see\
    <pre>&lt;img src="a_random_unrelated_file_name" alt="$name_img_accessibility_alt" /&gt;</pre>\
    <p>La ventaja de este segundo método es que los estudiantes no verán el nombre del fichero.</p>\
    <p>A causa de su coste en consumo de recursos, no utilice este método más que cuando sea necesario.\
    The file will be renamed only if the exercise is saved in a module \
     and not in a class.</p>


!set name_save_exo_warning = Los ficheros binarios se guardan permanentemente solo cuando se guarda el ejercicio.
