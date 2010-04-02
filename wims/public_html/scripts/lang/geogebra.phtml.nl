!set lang_exists=yes
!!INPUT
!set inp0=Veel te veel objecten getekend. Het aantal toegestaan 
!set inp1=objecten. Probeer opnieuw...
!set inp2=Versturen
!set inp3=Ik weet het niet

!!GEOGEBRA
!set pointnocoord=!nosubst een punt $(M_objet[1])
!set vectornocoord=!nosubst een vector $(M_objet[1])
!set circlenocoord=!nosubst een cirkel $(M_objet[1])
!set linenocoord=!nosubst een lijn $(M_objet[1])
!set curvenocoord=!nosubst een polynome curve $(M_objet[1])
!set conicnocoord=!nosubst een kegelsnede $(M_objet[1])
!set parabolanocoord=!nosubst een parabool $(M_objet[1])
!set ellipsenocoord=!nosubst een ellips $(M_objet[1])
!set hyperbolanocoord=!nosubst een hyperbool $(M_objet[1])
!set anglenocoord=!nosubst een hoek $(M_objet[1])
!set textnocoord=!nosubst een tekst $(M_objet[1])
!set numericnocoord=!nosubst een numerieke variabele $(M_objet[1])
!set segmentnocoord=!nosubst een lijnstuk $(M_objet[1])
!set polygonnocoord=!nosubst een polygoon $(M_objet[1])
!set functionnocoord=!nosubst een curve $(M_objet[1])
!set raynocoord=!nosubst een halve lijn $(M_objet[1])

!set pointcoord=!nosubst het punt $(M_objet[1]) met co&ouml;rdinaten ($(M_objet[3..4]))
!set vectorcoord=!nosubst de vector $(M_objet[1]) met co&ouml;rdinaat ($(M_objet[3..4]))
!set circlecoord=!nosubst een cirkel $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set linecoord=!nosubst de lijn $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set curvecoord=!nosubst de polynome curve $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set coniccoord=!nosubst de kegelsnede $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set parabolacoord=!nosubst de parabool $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set ellipsecoord=!nosubst de ellipse $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set hyperbolacoord=!nosubst de hyperbool $(M_objet[1]) met vergelijking \($(M_objet[3..-1]))
!set anglecoord=!nosubst de hoek van $(M_objet[1])  (in degrees) $(M_objet[3..-1])
!set textcoord=!nosubst de tekst: $(M_objet[1])
!set numericcoord=!nosubst de variabele $(M_objet[1]) met waarde $(M_objet[3..-1])
!set segmentcoord=!nosubst een lijnstuk $(M_objet[1]) met lengte $(M_objet[3..-1])
!set polygoncoord=!nosubst een polygoon $(M_objet[1]) met oppervlak $(M_objet[3..-1])
!set functioncoord=!nosubst de curve met vergelijking y=$(M_objet[1]) waarin \($(M_objet[1]) = $(M_objet[3..-1]))
!set raycoord=!nosubst de halve lijn $(M_objet[1]) op de lijn met vergelijking \($(M_objet[3..-1]))


!!!! commande anglicisée + type des paramètres + formal
!!!! si un paramètre risque de manquer on le remplace par _

!set anglepointpointpointformal=!nosubst de hoek $(M_objet[3])$(M_objet[4])$(M_objet[5])
!set angle_point_formal=!nosubst de hoek in $(M_objet[4])

!set bisectorlinelineformal=!nosubst de bisector $(M_objet[1]) of the lines $(M_objet[3]) and $(M_objet[4])
!set bisectorpointpointpointformal=!nosubst de bisectrice $(M_objet[1]) van de hoek $(M_objet[3])$(M_objet[4])$(M_objet[5])

!set centercircleformal=!nosubst het middelpunt $(M_objet[1]) van de cirkel $(M_objet[3])
!set centersegmentformal=!nosubst het midden $(M_objet[1]) van lijnstuk $(M_objet[3])
!set centerpointpointformal=!nosubst het midden $(M_objet[1]) van de punten $(M_objet[3]) en $(M_objet[4])

!set circle__formal=!nosubst een cirkel $(M_objet[1])
!set circlepoint_formal=!nosubst een cirkel $(M_objet[1]) met middelpunt $(M_objet[3])
!set circlepointnumericformal=!nosubst de cirkel $(M_objet[1]) met middelpunt $(M_objet[3]) en radius $(M_objet[4])
!set circle_pointformal=!nosubst een cirkel $(M_objet[1]) door $(M_objet[4])
!set circle_numericformal=!nosubst een cirkel $(M_objet[1]) met radius $(M_objet[4])
!set circlepointpointformal=!nosubst de cirkel $(M_objet[1]) met middelpunt $(M_objet[3]) door $(M_objet[4])
!set circlepointpointpointformal=!nosubst de cirkel $(M_objet[1]) door $(M_objet[3]), $(M_objet[4]) en $(M_objet[5])

!set conicpointpointpointpointpointformal=!nosubst de kegelsnede $(M_objet[1]) door de punten $(M_objet[3]), $(M_objet[4]), $(M_objet[5]), $(M_objet[6]) en $(M_objet[7])
!set conicpointpointpointpoint_formal=!nosubst de kegelsnede $(M_objet[1]) door de punten $(M_objet[3]), $(M_objet[4]), $(M_objet[5]) en $(M_objet[6])
!set conicpointpointpoint__formal=!nosubst de kegelsnede  $(M_objet[1]) door de $(M_objet[3]), $(M_objet[4]) en $(M_objet[5])
!set conicpointpoint___formal=!nosubst de kegelsnede  $(M_objet[1]) door de $(M_objet[3]) en $(M_objet[4])

!set curveformal=!nosubst de polynome curve
!set ellipseformal=!nosubst de ellips
!set functionformal=!nosubst de curve met vergelijking y = $(M_objet[1])
!set hyperbolaformal=!nosubst de hyperbool

!set intersectionlinelineformal=!nosubst het snijpunt van $(M_objet[1]) met $(M_objet[3]) en $(M_objet[4])
!set intersectioncirclecircleformal=!nosubst een snijpunt $(M_objet[1]) van $(M_objet[3]) en van $(M_objet[4])
!set intersectioncirclecirclenumericformal=!nosubst een snijpunt $(M_objet[1]) van $(M_objet[3]) en van $(M_objet[4])

!set line__formal=!nosubst een lijn $(M_objet[1])
!set linepoint_formal=!nosubst een lijn $(M_objet[1]) door $(M_objet[3])
!set line_pointformal=!nosubst een lijn $(M_objet[1]) door $(M_objet[4])
!set linepointlineformal=!nosubst de lijn $(M_objet[1]) door $(M_objet[3]) parallel aan $(M_objet[4])
!set line_lineformal=!nosubst een lijn $(M_objet[1]) parallel aan $(M_objet[4])
!set linepointpointformal=!nosubst de lijn $(M_objet[1]) door $(M_objet[3]) en $(M_objet[4])
!set linepointvectorformal=!nosubst de lijn $(M_objet[1]) door $(M_objet[3]) en richtingsvector $(M_objet[4])

!set midperpendicularsegmentformal=!nosubst de middenloodlijn $(M_objet[1]) van lijnstuk $(M_objet[3])
!set midperpendicularpointpointformal=!nosubst de middenloodlijn $(M_objet[1]) van lijnstuk [$(M_objet[3]), $(M_objet[4])]

!set numericformal=!nosubst de variabele $(M_objet[1]) met waarde $(M_objet[3])
!set parabolaformal=!nosubst de parabool

!set perpendicularpointlineformal=!nosubst de lijn $(M_objet[1]) loodrecht op $(M_objet[4]) en door $(M_objet[3])

!!defaut
!set pointnumericformal=!nosubst een punt $(M_objet[1]) op $(M_objet[3])
!set point_formal=!nosubst een punt $(M_objet[1])
!set pointformal=!nosubst een punt $(M_objet[1])
!set pointlineformal=!nosubst een punt $(M_objet[1]) op de lijn $(M_objet[3])
!set pointcircleformal=!nosubst een punt $(M_objet[1]) op de cirkel $(M_objet[3])
!set pointsegmentformal=!nosubst een punt $(M_objet[1]) op de lijnstuk $(M_objet[3])
!set pointpointnumericformal=!nosubst een punt $(M_objet[1]) op afstand $(M_objet[4]) van $(M_objet[3])
!set pointpolygonformal=!nosubst een punt $(M_objet[1]) op de polygoon $(M_objet[3])

!set polygonpointpointnumericformal=!nosubst de regelmatige polygoon met $(M_objet[5]) zijden with $(M_objet[3])$(M_objet[4]) als zijde
!set polygon4formal=!nosubst de vierkant met $(M_objet[3])$(M_objet[4]) als een zijde 
!set polygon3formal=!nosubst de gelijkzijdige driehoek met $(M_objet[3])$(M_objet[4]) als een zijde
!set polygon5formal=!nosubst de regelmatige vijfhoek met $(M_objet[3])$(M_objet[4]) als een zijde
!set polygont6formal=!nosubst de regelmatige zeshoek met $(M_objet[3])$(M_objet[4]) als een zijde
!set polygon7formal=!nosubst de regelmatige zevenhoek met $(M_objet[3])$(M_objet[4]) als een zijde
!set polygon8formal=!nosubst de regelmatige achthoek met $(M_objet[3])$(M_objet[4]) als een zijde


!set polygonpointpointpointformal=!nosubst $(M_objet[1]) de driehoek $(M_objet[3])$(M_objet[4])$(M_objet[5]) 
!set polygonpointpointpointformal=!nosubst $(M_objet[1]) de driehoek $(M_objet[3])$(M_objet[4])$(M_objet[5])
!set polygonpoint4formal=!nosubst $(M_objet[1]) de vierhoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])
!set polygonpoint5formal=!nosubst $(M_objet[1]) de vijfhoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])$(M_objet[7])
!set polygonpoint6formal=!nosubst $(M_objet[1]) de zeshoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])$(M_objet[7])$(M_objet[8])
!set polygonpoint7formal=!nosubst $(M_objet[1]) de zevenhoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])$(M_objet[7])$(M_objet[8])$(M_objet[9])
!set polygonpoint8formal=!nosubst $(M_objet[1]) de achthoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])$(M_objet[7])$(M_objet[8])$(M_objet[9])$(M_objet[10])
!set polygonpointformal=!nosubst $(M_objet[1]) de veelhoek $(M_objet[3])$(M_objet[4])$(M_objet[5])$(M_objet[6])$(M_objet[7])$(M_objet[8])$(M_objet[9])$(M_objet[10])$(M_objet[11])$(M_objet[12])$(M_objet[13])$(M_objet[14]) ...


!set raypointpointformal=!nosubst de halve lijn $(M_objet[1]) van $(M_objet[3]) door $(M_objet[4])
!set raypoint_formal=!nosubst een halve lijn $(M_objet[1]) van $(M_objet[3])
!set ray_pointformal=!nosubst de halve lijn $(M_objet[1]) door $(M_objet[4])
!set raypointvectorformal=!nosubst de halve lijn $(M_objet[1]) van $(M_objet[3]) met richtingsvector vector $(M_objet[4])
!set ray_vectorformal=!nosubst de halve lijn $(M_objet[1]) van $(M_objet[3]) met richtingsvector vector $(M_objet[4])

!set rotationlinenumericpointformal=!nosubst de afbeelding $(M_objet[1]) van de lijn $(M_objet[3]) by de rotatie om $(M_objet[5]) over een hoek $(M_objet[4])
!set rotationpointnumericpointformal=!nosubst de afbeelding $(M_objet[1]) van de punt $(M_objet[3]) by de rotatie om $(M_objet[5]) over een hoek $(M_objet[4])
!set rotationvectornumericpointformal=!nosubst de afbeelding $(M_objet[1]) van de vector $(M_objet[3]) by de rotatie om $(M_objet[5]) over een hoek $(M_objet[4])

!set segmentpoint_formal=!nosubst een lijnstuk $(M_objet[1]) met eindpunt $(M_objet[3])
!set segment_pointformal=!nosubst een lijnstuk $(M_objet[1]) met eindpunt $(M_objet[3])
!set segmentpointnumericformal=!nosubst het lijnstuk $(M_objet[1]) met eindpunt $(M_objet[3]) en met lengte $(M_objet[4])
!set segmentpointpointformal=!nosubst het lijnstuk $(M_objet[1]) met eindpunten $(M_objet[3]) en $(M_objet[4])
!set segmentpointpointpolygonformal=!nosubst het lijnstuk $(M_objet[1]) met eindpunten $(M_objet[3]) en $(M_objet[4]) op de polygoon $(M_objet[5])

!set symetrylinelineformal=!nosubst de symmetrische afbeelding$(M_objet[1]) van de lijn $(M_objet[3]) op lijn $(M_objet[4])
!set symetrylinepointformal=!nosubst de symmetrische afbeelding$(M_objet[1]) van de lijn $(M_objet[3]) om $(M_objet[4])
!set symetrypointlineformal=!nosubst de gespiegelde afbeelding $(M_objet[1]) van de punt $(M_objet[3]) ap lijn $(M_objet[4])
!set symetrypointpointformal=!nosubst de symmetrische afbeelding$(M_objet[1]) van de punt $(M_objet[3]) om het punt $(M_objet[4])

!set tangentpointcircleformal=!nosubst de raaklijn $(M_objet[1]) aan de cirkel $(M_objet[4]) door $(M_objet[3])

!set textformal=!nosubst de tekst $(M_objet[1])

!set translationlinevectorformal=!nosubst de translatie $(M_objet[1]) van de lijn $(M_objet[3]) met vector $(M_objet[4])
!set translationpointvectorformal=!nosubst de translatie $(M_objet[1]) van de punt $(M_objet[3]) met vector $(M_objet[4])
!set translationvectorpointformal=!nosubst de vector $(M_objet[1]) van $(M_objet[4]) met richtings vector $(M_objet[3])

!set vectorpointpointformal=!nosubst de vector $(M_objet[1]) van $(M_objet[3]) naar $(M_objet[4])
!set vector_pointformal=!nosubst een vector $(M_objet[1]) met eindpunt  $(M_objet[4])
!set vectorpoint_formal=!nosubst een vector $(M_objet[1]) van $(M_objet[3])
!set vectorpointnumericformal=!nosubst de vector $(M_objet[1]) van $(M_objet[3]), met lengte $(M_objet[4])
!set vectorpointformal=!nosubst de vector $(M_objet[1]) van O naar $(M_objet[3])

!!first should be the language term in small letters ans met no accent
!set typelangue= punt=point \
snijpunt=intersection \
puntcirkel=pointcircle \
lijn=line \
lijnstuk=segment \
cirkel=circle \
functie=function \
polynoom=polynomial \
kegelsnede=conic \
ellips=ellipse \
hyperbool=hyperbola \
parabool=parabola \
vector=vector \
hoek=angle\
loodrecht=perpendicular \
symmetrie=symetry\
middenloodlijn=midperpendicular\
raaklijn=tangent\
middelpunt=center\
halvelijn=ray\
midden=middle\
centrum=center\
rotatie=rotation\
translatie=translation\
homothety=homothety\
polygoon=polygon\
bisectrice=bisector\
anglegeom=anglegeom


!set w_penalty=Er zijn strafpunten gegeven omdat er teveel objecten zijn getekend.
!set w_analyze=Je hebt getekend:
!set w_NO= Nee. Je moest getekend hebben 
!set w_OK= Ja. Je hebt getekend
!set w_yes= Ja.
!set w_no= Nee.
!set w_and=en
!set w_uname= Object met foutief label
!set w_ARC= Cercle DemiCercle ArcCercle ArcCercleCirconscrit
!! I don't know what to do with this.
