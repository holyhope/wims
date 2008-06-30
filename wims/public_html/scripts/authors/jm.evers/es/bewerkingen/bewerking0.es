#BEWERKIGEN:
#antwoord niet leeg
#antwoord niet te groot $(woordmax$n)
#nakijken op aanwezigheid van de variabelen a,b,c enz: $(varlist$n)!=
#stript alle letters uit het antwoord: $(alleen_cijfers)$n=ja
#als antwoord gelijk is aan vraag, teruggeven maar als de vraag 
#verkeerde breukstreep
#geen komma of punt

AAA=!wordcnt $(ANT$n) 
	!if $AAA=0
	    OPMERKING=!record 21 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !goto NIKS 
	!endif

#speciaal geval : 
    !if : isin $(ANT$n) and : isin $(GOED$n)
	TUSSEN=!replace internal : by , in $(ANT$n)
	T1=!item 1 of $TUSSEN
        T2=!item 2 of $TUSSEN
	    !if $T1=  and $T2=
		OPMERKING=!record 21 of woorden.$taal
		!increase poging
		TERUG=1
		!goto NIKS 
	    !else
		!if $T1= or $T2=
		    OPMERKING=!record 35 of woorden.$taal
		    !increase poging
		    TERUG=1
		    !goto NIKS 
	        !endif
	    !endif
    !endif
    
!if , isin $(ANT$n) 
    OPMERKING=!record 22 of woorden.$taal
    TERUG=1
    !increase poging
    !goto NIKS
!endif

!if . isin $(ANT$n) and . notin $(GOED$n)
    OPMERKING=!record 27 of woorden.$taal
    TERUG=1
    !increase poging
    !goto NIKS
!endif


ANT$n=!lower $(ANT$n)
	!if sqrt notin $(ANT$n) and sqrt isin $(GOED$n)  
	    !if sq isin $(ANT$n) or sqr isin $(ANT$n) or qr isin $(ANT$n) or qrt isin $(ANT$n)
		OPMERKING=!record 32 of woorden.$taal
		!increase poging
		TERUG=1
		!goto NIKS
	    !endif
		
		OPMERKING=!record 97 of woorden.$taal
		TERUG=1
		!increase poging
		!goto NIKS
	
	!endif
	!if sqrt isin $(ANT$n)  and sqrt isin $(GOED$n)
		ANT$n=!nospace $(ANT$n)
		dingen=!record 85 of woorden.$taal
		    !for q=1 to 8
			dingetje=!item $q of $dingen
			    !if $dingetje notin $(GOED$n)
			        ANT$n=!replace internal $dingetje by   in $(ANT$n)
			    !endif
		    !next
		ANT$n=!replace internal sqrt by SQRT in $(ANT$n)
		ANT$n=!replace [a-z\~\!\@\#\$\%\&\_\=\"\?\|] by  in $(ANT$n)    
		ANT$n=!replace internal SQRT by sqrt in $(ANT$n)		
		ANT$n=!nospace $(ANT$n)	

	!endif
!if \ isin $(ANT$n) and \ notin $(GOED$n)
    OPMERKING=!record 29 of woorden.$taal
    !increase poging
    TERUG=1
    !goto NIKS
!endif

:NIKS


