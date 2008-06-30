#BERWERKIGEN:
#antwoord niet leeg
#antwoord niet te groot $(woord_max$teller)
#nakijken op aanwezigheid van de variabelen a,b,c enz: $(varlist$n)!=
#stript alle letters uit het antwoord: $(alleen_cijfers)$n=ja
#als antwoord gelijk is aan vraag, teruggeven maar als de vraag 
#verkeerde breukstreep
#geen komma of punt

leeg=!wordcnt $(ANT$n) 
	!if $leeg=0
	    OPMERKING=!record 21 of woorden.$taal
	    poging=$[$poging+1]
	    TERUG=1
	    !goto NIKS 
	!endif

	!if $leeg>$(woordmax$n)
	    OPMERKING=!record 33 of woorden.$taal
	    poging=$[$poging+1]
	    TERUG=1
	    !goto NIKS 
	!endif
!if : notin $(ANT$n) and : isin $(GOED$n)
    OPMERKING=!record 34 of woorden.$taal
    TERUG=1
    !goto NIKS
!endif




!if , isin $(ANT$n) or . isin $(ANT$n) and , notin $(GOED$n) and . notin $(GOED$n)
    OPMERKING=!record 103 of woorden.$taal
    TERUG=1
    poging=$[$poging+1]
    !goto NIKS
!endif

!if $(ANT$n) issametext $(som$n)
    OPMERKING=!record 39 of woorden.$taal
    TERUG=1
    poging=$[$poging+1]
    !goto NIKS
!endif

#strippen alle eventuele karakter...dus antwoord is alleen een getal en  dus varlist=0
ANT$n=!lower $(ANT$n)
!if $(varcnt$n)=0
	alfabet=!record 5 of woorden.$taal
	    !for q=1 to 26
		letter=!item $q of $alfabet
		!if $letter isin $(ANT$n)
		
		OPMERKING=!record  101 of  woorden.$taal
		TERUG=1
		!goto NIKS
		!endif		
	    !next

!else
	TEST$n=$(ANT$n)
        !for q=1 to $(varcnt$n)
	var=!item $q of $(varlist$n)
	TEST$n=!replace internal $var by   in $(TEST$n)
	    !if $var notin $(ANT$n)
		poging=$[$poging+1]
		OPMERKING=!record 100 of woorden.$taal
		TERUG=1
		!goto NIKS
	    
	    !endif
	!next
#als TEST nog letters bevat:
	alfabet=!record 5 of woorden.$taal
	    !for q=1 to 26
		letter=!item $q of $alfabet
		!if $letter isin $(TEST$n)
		    OPMERKING=!record 40 of woorden.$taal
		    TERUG=1
		    !goto NIKS
		!endif		
	    !next

!endif

!if \ isin $(ANT$n) and \ notin $(GOED$n)
    OPMERKING=!record 29 of woorden.$taal
    poging=$[$poging+1]
    TERUG=1
    !goto NIKS
!endif
	
##laatste test als het aantal woorden in het antwoord niet gelijk is aan woordmax is 
#er wat misgegaan
woorden=!wordcnt $(ANT$n)
!if $woorden>$(woordmax$n)
    OPMERKING=!record 34 of woorden.$taal
    TERUG=1
    !goto NIKS
!endif

:NIKS


