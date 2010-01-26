 !goto $wims_read_parm
 
:1
<ul><li>Une <b>classe individuelle</b> est prévue
 pour la gestion d'un groupe d'élèves par un enseignant.
 </li>
 <li>Un <b>groupement de classes</b> permet aux
 enseignants d'échanger ou de partager des matériels pédagogiques, et aux
 élèves de passer d'une classe à l'autre sans retaper le mot de passe.
 </li><li>
 Une structure d'<b>établissement</b> est un rassemblement 
 multi-niveaux de classes
 virtuelles, capable de
 gérer le besoin d'un établissement d'enseignement tout entier :
 bases de données d'élèves et d'enseignants,
 différents niveaux d'enseignement, programmes, sujets et classes d'élèves,
 responsabilités d'enseignants, etc.
 </li></ul>
 Pour les groupements et les établissements, le lien ci-dessus permet 
 de créer leur <b>portail</b>. Vous aurez ensuite à créer les classes 
 qu'ils contiennent.
 !exit
:2
 
  La création 
 !if $Cltype<2
   d'une <font color="blue">classe</font>
   est une opération réservée à un <font color="blue">enseignant</font>. 
 !else
    de <font color="blue">$name_classe</font>
 est une opération réservée à un <font color="blue">administrateur</font>
(qui peut être un enseignant).
 !endif
 Vous avez besoin d'une adresse électronique opérationnelle pour l'opération.
 Après la création de votre $name_classe, vous devez assumer la responsabilité de
 sa maintenance. <p>
 Pour créer votre $name_classe, veuillez remplir les renseignements suivants :
!exit
 
:step1
Bonjour, $supervisor! <p>
 Vous êtes en train de créer 
 !if $Cltype<2
 la
!else
 le
 !endif
 $name_classe $classname sur le site WIMS à l'adresse
 $httpd_HTTP_HOST,
 !if $Cltype iswordof 0 1
  !let tmp=!positionof item $ilevel in $levelid
  de niveau ``<b><font color=green>$(leveldesc[$tmp])</font></b>'',
 !endif
 qui prendra fin le $exp_day/$exp_month/$exp_year. 
 Le nombre maximum de participants est de $ilimit ; 
 l'inscription est
 !if $pword!=$empty
  protégée par le mot de passe $name_classesss.
 !else
  ouvert à tout le monde sur l'internet (en êtes-vous sûr? Sachez que le
  gestionnaire du site peut les refuser et les détruire).
 !endif
 <p>
 Si vous décelez une erreur dans les renseignements ci-dessus, veuillez
 !href module=$module&cmd=reply&step=0 la corriger.
 <p>Sinon, afin de vérifier l'exactitude de vos mots de passe,
 veuillez les retaper encore une fois. 
 !exit
:step2
 
  Bonjour, $supervisor! <p>
 Maintenant vous avez besoin d'un code pour terminer l'opération de création
 de votre $name_classe sous WIMS sur le site $httpd_HTTP_HOST. <p>
 Ce code vient d'être envoyé à votre adresse électronique
 ``<tt>$email</tt>''. Veuillez consulter votre boîte à lettre
 électronique (attendez quelques instants si nécessaire) et lire le message
 qui vous a été envoyé. Relevez le code écrit dans le message et copiez-le ci-dessous.

!exit 
:step3
 
 Bonjour, $supervisor!<p>
 Votre $name_classe $classname est maintenant en place. Félicitations
 et amusez-vous bien&nbsp;!<p>
 Le nombre de participants est limité à $ilimit participants (y compris vous)
 
!exit