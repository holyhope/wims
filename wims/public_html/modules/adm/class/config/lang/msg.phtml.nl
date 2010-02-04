
!set wims_module_log=error: $error $wims_class

<b>Fout</b>.

!if not_supervisor iswordof $error
Helaas, maar deze module is alleen voor de supervisor van een 
virtuele klas bedoeld.
 !exit
!endif

!if not_secure iswordof $error
 !if $code!=$empty
  Incorrecte beveilingings code.
 !else
 Deze module is alleen bereikbaar door een "secure host".
 !endif
Toegang Geweigerd !
 !exit
!endif

!if checkhost iswordof $error
Uw huidige ipadres staat niet in de nieuwe lijst van "secure hosts".
Waarschijnlijk is dit een klein foutje.
En ik zal dus de "secure host" datalijst 
niet bijwerken.
 !exit
!endif

!if bad_file iswordof $error
Helaas, maar ik kan de <em>$wims_deposit</em> file niet als een klas backup-file identificeren.
Of U hebt een verkeerde file gestuurd of de archief-file zelf is corrupt.
 
 !exit
!endif

!if empty_file iswordof $error
Er zijn geen klas backup bestanden aangetroffen in uw backup-file 
<tt>$wims_deposit</tt>.
 !exit
!endif

!if no_upload iswordof $error
De gestuurde data zijn ongeldig ! Probeer het nog eens.
 !exit
!endif

!if remote_sharing iswordof $error
Een "buurt-klas" deelt enkele bronnen uit uw klas.<br>
U kunt alleen wijzigingen aanbrengen in materiaal dat niet gedeelt is met anderen.<br>
Voor beide klassen moet U de deling van materiaal beeindigen.
 !exit
!endif

!if share_dep iswordof $error
 Le partage de ressources doit respecter les dépendances&nbsp;: vous devez d'abord partager                                                
 !if sheet iswordof $error                                                                                                                 
  les exercices avant de partager les feuilles de travail.                                                                                 
 !else                                                                                                                                     
  !if exam iswordof $error                                                                                                                 
   les exercices et les feuilles de travail avant de partager les examens.                                                                 
  !else                                                                                                                                    
   !if livret iswordof $error                                                                                                              
    les exercices et les feuilles de travail avant de partager le livret de compétences.                                                   
   !endif                                                                                                                                  
  !endif                                                                                                                                   
 !endif                                                                                                                                    
 !exit                                                                                                                                     
!endif

!if stopshare_dep iswordof $error                                                                                                          
 Le partage de ressources doit respecter les dépendances&nbsp;: vous devez d'abord arr&ecirc;ter le partage                                
 !if sheet iswordof $error                                                                                                                 
  des examens et du livret de compétences avant celui des feuilles de travail .                                                            
 !else                                                                                                                                     
  !if exo iswordof $error                                                                                                                  
   des feuilles de travail avant celui des exercices.                                                                                      
  !endif                                                                                                                                   
 !endif                                                                                                                                    
 !exit                                                                                                                                     
!endif

!if not_neighbor iswordof $error
U hebt geef erkende "buurt-klas". 
 <br>
 Onthoud goed dat een klas pas echt een "buurt-klas" als dit door <b>beide</b> klassen wordt erkend !


 !exit
!endif

!if localmirror iswordof $error
Het spiegelen/kopieren van een klas op de zelfde server heeft geen nut! 
 !exit
!endif

!if toobigfile iswordof $error
 La taille de votre fichier est trop importante : la limite est de 12K.
 !exit
!endif

!msg $error

