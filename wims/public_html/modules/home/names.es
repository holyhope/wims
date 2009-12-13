
N_manage	=Administración de WIMS en línea
N_best		=los mejores
N_new		=lo nuevo
N_New		=Lo nuevo
N_mirror	=réplicas
N_Mirror	=Réplicas
N_forum		=foros
N_Forum		=Foros
N_pref		=preferencias
N_Pref		=Preferencias
N_help		=ayuda
N_Help		=Ayuda
N_within	=en
N_clear		=Empezar de nuevo
N_go		=mostrar
N_at		=en
N_or		=o
N_import	=importar
N_Mboard	=Foro de discusión
N_hide		=ocultar

S_tip		=<b>Consejo</b>. Dejar la búsqueda vacía en algunas categorías\
devuelve la lista de los recursos más populares.

V_title		=Servidor Interactivo Multipropósito WIMS
V_cls		=Clases virtuales
V_stu		=área de los estudiantes
V_sup		=área de los profesores
V_ex		=clases de ejemplo
V_Quit		=Cerrar la clase
V_Wsup		=Escribir al supervisor
V_Chpref	=Cambiar las preferencias
V_Chpass	=Cambiar la contraseña
V_sh		=hoja de trabajo
V_shs		=hoja de trabajo
V_exam		=examen

CR_1		=Crear mis propios
CR_OEF		=ejercicios interactivos sencillos
CR_mod		=módulos a toda potencia

E_doc		=documentación técnica
E_src		=Bajar los fuentes
E_ref		=lista de enlaces inversos
E_stat		=estadísticas del sitio
E_comp		=compilada el
E_manager	=Administrador del sitio:

RE_found	=!nosubst Encontrados $gotcnt $tt para su búsqueda
RE_nomatch	=!nosubst Su búsqueda no dio ningún resultado
RE_pop		=!nosubst Aquí están los $gotcnt $tt más populares
RE_pop2		=!nosubst $gotcnt $tt por orden de popularidad\
(número $[$list_start+1] - $[$list_start+$gotcnt])
RE_try		=Pruebe

U_greet		=!nosubst ¡Hola, $wims_firstname $wims_lastname! Bienvenido/a\
a $wims_classname, moderada por $supmail.



U_newmsg	=Hay $$newmsgcnt nuevo(s) mensajes(s) en el foro de la clase.
U_nosheet	=Esta clase no tiene aún hojas de trabajo. Por favor, vuelva a entrar\
más tarde, cuando su profesor haya preparado una.
U_assign	=El profesor ha preparado las siguientes hojas de trabajo.
U_expired	=expirado
U_done		=hecho
U_average	=calidad
U_Doc		=Documento
U_Sheet		=Hoja
U_Exam		=Examen
U_cdt           =Cuaderno de texto
U_Vote		=Encuesta
U_myscore	=Mis puntuaciones
U_examworking	=<b><font color=red>Atención.</font></b> Usted estaba trabajando en un examen.
U_examdouble	=En este caso no puede conectarse desde otro puesto.
U_examcont	=Continuar el examen.
U_oclass	=Zonas de trabajo
U_back=		=Atrás
U_account	=Mi cuenta
U_teacher	=profesor
U_Docstatus=ni leer ni escribir en,leer pero no escribir en,leer y escribir en
U_weight    = coeficiente

U_gotoclass1	=Entrar como participante:
U_gotoclass3	=Entrar como profesor:
U_gotoclass	=Sus zonas de trabajo:



U_inscription1	=Para inscribirse en una zona de trabajo, pulse una de las clases:
U_inscription2	=Inscribirse en una zona de trabajo como participante.
U_clickhere	=Pulse aquí
U_supervise	=para entrar a una zona como profesor.
U_creatclass	=Crear una clase nueva.


SU_greet	=!nosubst ¡Hola, $wims_firstname $wims_lastname! Bienvenido/a a la página\
de mantenimiento de su clase
SU_Bhome	=Volver a la página principal del profesor
SU_log		=acceso del profesor
SU_exp1		=la cual expira el
SU_exp2		=	
SU_Uprep	=En preparación
SU_Ac		=Activo
SU_Ex		=Expirado
SU_Hi		=Expirado+Oculto
SU_nosheet	=Su clase todavía no tiene recursos.
SU_Crone	=Crear un recurso.
SU_shlist	=Lista de recursos.
SU_shno		=Número
SU_shti		=Título
SU_shst		=Estado
SU_Howsh	=Cómo añadir una tarea a una hoja de ejercicios
SU_classexo	=Ejercicios de la clase (es decir, sus creaciones)
SU_Gateway	=Administración de la estructura
SU_Bprogram=Vuelta al programa

SE_list		=Participantes y puntuaciones
SE_part		=Página inicial para el participante
SE_mod		=Mensaje del día
SE_prop		=Config./Mantenim.
SE_secu		=Administración de seguridad

ADD_1		=Añadir un
ADD_doc		=documento
ADD_sheet	=hoja de ejercicios
ADD_exam	=examen
ADD_exo		=ejercicio
ADD_vote	=encuesta
ADD_class	=clase
ADD_2		=	
ADD_3           =Añadir una
ADD_cdt         =cuaderno de texto



CL_Names	=Niveles,Clases,Programas,Cursos,Cursos interclase
CL_Name	=nivel, clase,programa,Curso,Curso interclase
CL_Test		=Zona de pruebas
CL_otherNames=Other $(CL_Names[2]),$(CL_Names[3]),$(CL_Names[4]) of the class

ER_expression	=<b>Atención.</b> ¿Busca usted una expresión matemática? \
 Aquí no tiene sentido.

!if $wims_supertype=4
 U_oclass	=Cambiar de zona
!else
 U_oclass	=Otras clases
!endif
