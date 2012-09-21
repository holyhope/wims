# subject list
Tot_dom=bio,chim,Lang,math,phys

name_math=Mathematics
tot_dom_math=number,algebra,analysis,geom,probstat,misc
dom_algebra=prealg,elemalg,linalg,absalg,code
dom_analysis=precalc,calc
dom_geom=euclgeom,anageom,affgeom
dom_number=prealg,arith
dom_probstat=proba,stat
dom_misc=combi,logic

name_code=teoría de la encriptación
list_code=encriptación, criptología, distancia de Hamming, código corrector de errores,\
	detección de errores, entropía

name_absalg=álgebra abstracta
list_absalg=grupos, anillos, cuerpos

name_linalg=álgebra lineal
list_linalg=matrices, determinante, sistemas lineales, vectores, espacios vectoriales,\
	alicaciones lineales

name_prealg=pre-álgebra
list_prealg=fracciones, decimales, porcentajes, ecuaciones, proporcionalidad

name_elemalg=álgebra elemental
list_elemalg=ecuaciones, polinomios, raíces, números complejos,\
	factorización

name_algebra=álgebra

name_precalc=pre-cálculo
list_precalc=desigualdades, funciones, raíces, ecuaciones, trigonometría,\
	números reales, intervalos, límites

name_calc=cálculo
list_calc=derivadas, integrales, primitivas, integrales definidas,\
	continuidad, derivabilidad, secuencias, series,\
	expansión de Taylor, series de Taylor, series de Fourier,\
	transformaciones de  Laplace, transformaciones de Fourier, límites,\
	EDO, ecuaciones diferenciales

name_analysis=análisis

name_arith=aritmética
list_arith=enteros, aritmética modular, pgcd ppcm, factorización,\
	relación de Bezout, congruencia, números primos, división euclidea,\
	ecuaciones diofantinas, Goldbach

name_number=números
list_number=números complejos, fracción continua, números reales,\
	sistemas de numeración

name_proba=probabilidad
list_proba=distribuciones, entropía

name_stat=estadística
list_stat=datos estadísticos, medias, desviación, regresión

name_probstat=probabilidad-estadística

name_affgeom=geometría afín
list_affgeom=líneas, planos, hiperplanos

name_euclgeom=geometría euclídea
list_euclgeom=líneas, círculos, rectángulos, polígonos,\
	ángulos, triángulos, regla y compás

name_anageom=geometría analítica
list_anageom=superficies, curvas, curvas paramétricas, curvas polares,\
	cónicas, parábola, hipérbole, elipse, círculo, Lissajous

name_geom=geometría
list_geom=grafo, trigonometría

name_combi=combinatoria
list_combi=factorial, combinación, permutación

name_logic=lógica
list_logic=conjuntos, aplicaciones

name_misc=miscelánea

name_bio=Biologie
tot_dom_bio=biology
dom_biology=biology
name_biology=biologie
list_biology=botanics,histology,immunology,medecine,mycology,phylogenetics

list_tmp=!replace internal , by ,name_ in name_ $list_biology
list_tmp=!nospace $list_tmp

!!!### names
!distribute items botanique,histologie,immunologie,médecine,mycologie,phylogénétique\
into $list_tmp

!!!### keywords
list_tmp=!replace internal name_ by keywords_ in $list_tmp

!!!###

name_chim=Chimie
tot_dom_chim=chemistry
dom_chemistry=chemistry
name_chemistry=chimie
list_chemistry=thermodynamics,organics_chemistry

list_tmp=!replace internal , by ,name_ in name_ $list_chemistry
list_tmp=!nospace $list_tmp

!!!### names
!distribute items Thermodynamique,Chimie organique\
into $list_tmp

!!!### keywords
list_tmp=!replace internal name_ by keywords_ in $list_tmp
!distribute items thermo,organics\
into $list_tmp
!!!###


tot_dom_Lang=Lang
name_language=langues
dom_language=language
list_Lang=Lang,listening,grammar,technical,phonetics
list_tmp=!replace internal , by ,name_ in name_ $list_Lang
list_tmp=!nospace $list_tmp
!!!### names
!distribute items langues,Ecoute,Grammaire,Langue technique,Phonétique\
into $list_tmp

!!!### keywords
list_tmp=!replace internal name_ by keywords_ in $list_tmp
!distribute items language,listening,grammaire,technical,phonétique\
into $list_tmp

!!!###

tot_dom_phys=physics
name_physics=physique
name_phys=Physique


!!!### keywords
list_tmp=!replace internal name_ by keywords_ in $list_tmp

!!!###