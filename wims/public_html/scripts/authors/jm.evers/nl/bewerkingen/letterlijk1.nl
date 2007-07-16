#################################################################
#	CHECKT OF DE SOM -SOMS- LETTERLIJK IS OVERGENOMEN	#
#	EN OP AANWEZIGHEID VAN DE JUISTE VARIABELEN		#
#	IVM PARI if(ANT==GOED,ja,nee)				#
#	stript alle niet-relevante letters & dingen		#	
#	geeft variable $AAA terug als gestript $(ANT$n)		#	
#			verondersteld				#
#								#
#	antwoord leerling 		$(ANT$n)		#
#	goede antwoord 			$(GOED$n)		#
#	de letterlijke vraag		$(som$n)		#
#	we rekenen met geschoond	$AAA			#
#								#
#################################################################
alfabet=abcdefghijklmnopqrstuvwxyz

JOUW_ANTWOORD=!lower $(ANT$n)

JOUW_ANTWOORD=!rawmath $JOUW_ANTWOORD
TESTGOED=!rawmath $(som$n)
CONTROLE=!rawmath $(GOED$n)

VAR=!varlist $(GOED$n)
VARCNT=!itemcnt $VAR	
	
!if $VARCNT=0
    TERUG=1
    OPMERKING=!record 106 of woorden.$taal
    !exit
!endif

aantal_letters=$[26-$VARCNT]		

!for p=1 to $VARCNT

    testvar=!item $p of $VAR
    
    !if $testvar notin $JOUW_ANTWOORD
	!increase poging
	TERUG=1
	OPMERKING=!record 126 of woorden.$taal
	!exit
    !endif     
    
    alfabet=!replace $testvar by   in $alfabet
!next


!for p=1 to $aantal_letters

    lettertje=!char $p of $alfabet
    JOUW_ANTWOORD=!replace internal $lettertje by   in $JOUW_ANTWOORD
    TESTGOED=!replace internal $lettertje by   in $TESTGOED
    CONTROLE=!replace internal $lettertje by   in $CONTROLE

!next
    JOUW_ANTWOORD=!rawmath $JOUW_ANTWOORD
    TESTGOED=!rawmath $TESTGOED
    CONTROLE=!rawmath $CONTROLE




    AAA=$JOUW_ANTWOORD 
    AAA=!replace [\~\`\%\!\#\&\_\=\|\"\'\:\;\?\] by   in $AAA
    

    JOUW_ANTWOORD=!replace [\(\)\~\`\!\@\#\$\%\&\_\|\=\+\-\"\'\:\;\?] by   in $JOUW_ANTWOORD	 
    TESTGOED=!replace [\(\)\~\`\!\@\#\$\%\&\_\|\=\+\-\"\'\:\;\?] by  in $TESTGOED
    CONTROLE=!replace [\(\)\~\`\!\@\#\$\%\&\_\|\=\+\-\"\'\:\;\?] by  in $CONTROLE


    JOUW_ANTWOORD=!nospace $JOUW_ANTWOORD
    TESTGOED=!nospace $TESTGOED
    CONTROLE=!nospace $CONTROLE
    
!if $wims_site_manager=jm.evers@schaersvoorde.nl
    JOUW_ANTWOORD=!exec toascii $JOUW_ANTWOORD 
    TESTGOED=!exec toascii $TESTGOED 
    CONTROLE=!exec toascii $CONTROLE
    #LET OP we gebruiken nu onze eigen toascii ; het is onzinnig om die grote octave wakker te
    #maken voor zo'n simpele bewerking...
    # onze toascii staat in public_html/bin/toascii.
    #de broncode toascii.c staat in src/Misc/jm.evers/toascii
    #en toascii is niet geinstalleerd....    
!else
    JOUW_ANTWOORD=!exec octave sum(toascii("$JOUW_ANTWOORD")) 
    TESTGOED=!exec octave sum(toascii("$TESTGOED")) 
    CONTROLE=!exec octave sum(toascii("$CONTROLE"))
!endif    
    !if ($TESTGOED = $JOUW_ANTWOORD) and  ($TESTGOED != $CONTROLE) 
	TERUG=1
	OPMERKING=!record 39 of woorden.$taal
    !else
	!if $JOUW_ANTWOORD=0 or $TESTGOED=0 or $CONTROLE=0
	    TERUG=1
	    OPMERKING=!record 106 of woorden.$taal
	!endif
    !endif
	    	    
