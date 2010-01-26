!goto $wims_read_parm
!exit

:allowtype

<center><b>Indication sur l'enregistrement des notes.</b> </center>

 Dans le mode sélectif, vous pouvez imposer une
 restriction dans le temps pour l'enregistrement des notes en ajoutant des
 mots
 <font color=blue><b>
 <tt>&gt;aaaammjj.hh:mm</tt></b></font>
 (début) et/ou
 <font color=blue><b>
 <tt>&lt;aaaammjj.hh:mm</tt></b></font>
 (fin). Les dates et heures doivent être en temps local du SERVEUR
 et ces mots doivent être séparés des autres par des espaces.
 <br>
 Les heures de coupure sont là pour permettre aux gens de passer l'examen dans
 des séances différées. Un participant ayant travaillé sur l'examen avant une
 heure de coupure ne peut plus retravailler dessus après la coupure.
 <br>
 Format des heures de coupure: <tt>aaaammjj.hh:mm</tt> (séparez plusieurs
 heures de coupure par des espaces).
 </small>
!exit

:dependency
 <center><b>Dépendances des scores</b></center>
 Les dépendances des scores veulent dire qu'un participant doit
  d'abord acquérir des points dans d'autres exercices de la feuille, avant
  de pouvoir travailler sur celui-ci. Par exemple,
  <font color=blue><tt>1:50,2:30,3+4+5:60</tt></font>
  signifie que le participant doit avoir un succès de 50% sur l'exercice 1,
  30% sur l'exercice 2, et une moyenne de succès de 60% sur les exercices
  3,4,5.
!exit

:options
 <center><b>Options.</b></center>
 Une seule option est pour l'instant disponible
  <ul>
   <li><em>autogen</em> veut dire que l'exercice est généré automatiquement même si l'utilisateur ne clique pas dessus. Pour qu'il puisse consulter l'exercice enregistré quand la session est fermée. Formellement déconseillé
  sauf pour exercices à correction manuelle.</li>
  </ul>
!exit

:contenu
 <center><b>Contenu d'un exercice</b></center>
Cet exercice peut être pris (aléatoirement) dans une liste d'exercices
existants dans des feuilles de travail. Veuillez marquer parmi les exercices des
feuilles de la liste suivante ceux que vous voulez prendre pour cet exercice d'examen.
!exit