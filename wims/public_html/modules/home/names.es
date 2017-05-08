N_manage = Administración de WIMS en línea
wims_name_mirror = Réplicas
wims_name_Mirror = Réplicas
wims_name_pref = Preferencias

N_within = entre
## define also in scripts/adm/search_engine
N_clear = Empezar de nuevo

N_go = ir
name_importfromtest=teaching materials from Test Zone.
N_at = en
N_hide = Ocultar
name_allexampleclass=Todas las clases abiertas

V_title = WWW Interactive Multipurpose Server
V_cls = Clases virtuales
wims_name_n_participant = Área de estudiantes
wims_name_n_supervisor = Área de profesores
wims_name_mail = Escribir al supervisor
wims_name_pref = Cambiar las preferencias
wims_name_ref = Lista de enlaces inversos
wims_name_stat = Estadísticas del sitio

CR_1 = Creación
CR_Docs=Tutoriales
## old version
CR_OEF = Ejercicios interactivos
CR_mod = Módulos de alto nivel
##
CR_sequence=Usted ha optado por presentar los siguientes recursos en secuencia \
  para los participantes. Recuerde actualizarla cuando agregue \
  un nuevo recurso.


E_comp = compilado el
E_manager = Administrador del sitio: $wims_name_manager

RE_prev = !nosubst Resultados anteriores
RE_next = !nosubst Resultados siguientes
RE_found = !nosubst Encontrados $Gotcnt $tt para su búsqueda
RE_found2= Están clasificados de acuerdo al tipo de actividad.\
  Haga clic en el botón correspondiente para verlas.
RE_warning_more= !nosubst Hay demasiados resultados, así que no se muestran todos \
  (limitado a $gotlim2 de cada tipo). Puede refinar la búsqueda \
  añadiendo palabras y seleccionando el tipo de búsqueda a todas las palabras \
  (totes les paraules).
RE_nomatch = !nosubst Su búsqueda no dio ningún resultado
RE_pop = !nosubst Aquí están los $gotcnt $tt más populares
RE_pop2 = !nosubst $gotcnt $tt por orden de popularidad\
(número $[$list_start+1] - $[$list_start+$gotcnt])
RE_try = Pruebe
RE_noKeyword    = Tiene que escribir una palabra clave

U_greet = !nosubst ¡Hola, $wims_firstname $wims_lastname! Bienvenido/a\
a $wims_classname, moderada por $supmail.

U_newmsg = Hay $$newmsgcnt nuevo(s) mensajes(s) en el foro de la clase.
U_nosheet = Esta clase no tiene aún hojas de trabajo. Por favor, vuelva a entrar\
más tarde, cuando su profesor haya preparado una.

U_assign = El profesor ha preparado las siguientes hojas de trabajo.
U_expired = expirado
U_done = hecho
U_average = calidad
U_examworking = Usted está trabajando en un examen.
U_examdouble = En este caso no puede conectarse desde otro puesto.
U_examcont = Continuar el examen.
wims_name_U_oclass = Zonas de trabajo
wims_name_U_account = Mi cuenta
wims_name_coeff = coeficiente

U_gotoclass1 = Entrar como participante:
U_gotoclass3 = Entrar como profesor:
U_gotoclass0 = Sus zonas de trabajo:
U_gotoclass11 = $U_gotoclass1
U_gotoclass31 = $U_gotoclass3
U_gotoclass01 = $U_gotoclass0

U_inscription1 = Para inscribirse en una zona de trabajo, pulse en una de las clases:
U_inscription2 = Inscribirse en una zona de trabajo como participante.
U_clickhere = Pulse aquí
U_supervise = Inscribirse en una zona de trabajo como profesor.
name_gotosupervise=Para entrar en otra clase como profesor, contacte con el administrador\
 del grupo de clases.

SU_greet = !nosubst ¡Hola, $wims_firstname $wims_lastname! Bienvenido/a a la página de mantenimiento de su clase
SU_Bhome = Volver a la página principal del profesor
SU_log = acceso del profesor
SU_exp1 = la cual expira el
SU_exp2 =
SU_nosheet = Su clase todavía no tiene recursos.
SU_shlist = Lista de recursos.
wims_name_SU_Gateway = Administración de la estructura
SU_Bprogram = Vuelta al programa
SU_nopartconnected=Ningun alumno está actualmenta conectado
SU_numpartconnected=!nosubst Hay actualmente $wims_numpartconnected alumno(s) conectado(s)
U_supconnected       = El profesor está conectado.

wims_name_SE_list = Alumnos y notas (old)
wims_name_n_participant = Página inicial para el participante

wims_name_SE_mod = Mensaje del día
wims_name_SE_secu = Administración de la seguridad

ADD_1 = Añadir un
ADD_doc = documento
ADD_sheet = hoja de ejercicios
ADD_exam = examen
ADD_exo = ejercicio
ADD_vote = cuestionario
ADD_class = clase
ADD_2 = 
ADD_3 = Añadir una
ADD_cdt = Agenda

CL_Names = Niveles,Clases,Programas,Cursos,Cursos interclase
CL_Name = nivel, clase,programa,curso,curso interclase
CL_Test = Zona de pruebas
CL_otherNames = Otras $(CL_Names[2]),$(CL_Names[3]),$(CL_Names[4]) de la clase

!if $wims_supertype = 4
 wims_name_U_oclass = Cambiar de zona
!else
 wims_name_U_oclass = Otras clases
!endif
!set name_deps = Tiene que mejorar sus notas en los ejercicios
!set name_dep = Tiene que mejorar su nota en el ejercicio
!set name_dep2 = antes de trabajar en este.
!set name_dep3 = Volver a la hoja de trabajo.
