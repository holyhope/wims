#antwoord niet leeg
#antwoord niet te groot $woordmax
#nakijken op aanwezigheid van de variabelen a,b,c enz: $(varlist$n)!=0
#stript alle letters uit het antwoord:
#als antwoord gelijk is aan vraag, teruggeven maar als de vraag 
#verkeerde breukstreep
#geen komma of 
#let op f(x) y= enz
#het antwoord:: ANTWOORD=1 anders ANTWOORD=0
!if $(latex$n)=ja
    latex=ja
!endif    
!if $woordmax!=
    woordmax=10
!endif    

    leeg=!wordcnt $(ANT$n) 
	!if $leeg=0
	    OPMERKING=!record 21 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !goto NIKS 
	!endif

	!if $leeg > $woordmax
	    OPMERKING=!record 33 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !goto NIKS 
	!endif

	!if : notin $(ANT$n) and : isin $(GOED$n)
	    !increase poging
	    OPMERKING=!record 34 of woorden.$taal
	    TERUG=1
	    !goto NIKS
	!endif

	!if  / isin $(GOED$n) and  / notin $(ANT$n) 
	    !if : isin $(ANT$n) or \ isin $(ANT$n) 
    		!increase poging
		OPMERKING=!record 29 of woorden.$taal
    		TERUG=1
    		!goto NIKS	
	    !endif
	!endif

	!if , isin $(ANT$n)  and , notin $(GOED$n)
		!increase poging    
		OPMERKING=!record 109 of woorden.$taal
		TERUG=1
		!goto NIKS
	!endif
	
	!if ( $varlist notin $(ANT$n) ) and ( $varlist isin $(GOED$n) )
	    testvar=$varlist
	    OPMERKING=!record 126 of woorden.$taal
	    TERUG=1
	    !increase poging
	    !goto NIKS
	!endif
    
	!if $letterlijk=ja or $letterlijk!=nee

	    operators=+,-,/,*,(,),=
	    ANTW=!rawmath $(ANT$n)
	    TESTGOED=!rawmath $(som$n)
	
	    !for qq=1 to 7
		OPERATOR=!item $qq of $operators
		ANTW=!replace internal $OPERATOR by , in $ANTW	
		TESTGOED=!replace internal $OPERATOR by , in $TESTGOED 
	    !next

	    aantal_dingen=!itemcnt $TESTGOED
	    aantal_matches=0
	    
	    !for qq=1 to $aantal_dingen
		TEST_ANTW=!item $qq of $ANTW
		!if $TEST_ANTW isitemof $TESTGOED
		    !increase aantal_matches 
		!endif    
	    !next
	    !if $aantal_matches=$aantal_dingen
		TERUG=1
		OPMERKING=!record 39 of woorden.$taal
		!increase poging
		!goto NIKS
	    !endif
	!endif


	#strippen alle eventuele karakter...dus antwoord is alleen een getal en  dus varlist=0
	AAA=!nospace $(ANT$n)
	GGG=!nospace $(GOED$n)
	!if $varcnt=0
		AAA=!replace [a-z\~`!@#$%&_|=+-"':;?] by   in $AAA
		GGG=!replace [a-z\~`!@#$%&_|=+-"':;?] by   in $GGG
	!else
		!if $vergelijking=ja
		    !if $argument notin $AAA
			!increase poging
		        OPMERKING=!record 113 of woorden.$taal
			TERUG=1
			!goto NIKS
		    !else
			ALFABET=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
			!for L=1 to 26
			    LETTER=!item $L of $ALFABET
				!if $LETTER notin $argument
			     	    alfabet=!append item $LETTER to $alfabet
				!endif
			!next
			
			AAA=!replace internal $argument by   in $AAA
			GGG=!replace internal $argument by   in $(GOED$n)
			ALFA=!itemcnt $alfabet
		    !endif			
		!else
			alfabet=x,y,z,f,g,u,v,a,b,c,d,e,h,i,j,k,l,m,n,o,p,q,r,s,t,w
			ALFA=26
		!endif        
		
		    onzin=
		    AAA=!replace [\~\!\@\#\$\%\&\=\:\;\"\'\?\|] by   in $AAA
		    GGG=!replace [\~\!\@\#\$\%\&\=\:\;\"\'\?\|] by   in $GGG
		    !for q=1 to $ALFA
			VV=!item $q of $alfabet
			    !if $VV isin $GGG and $VV notin $AAA		    
				!increase poging
				testvar=$VV
				OPMERKING=!record 126 of woorden.$taal
				TERUG=1
				!goto NIKS
			    !else
				!if ($VV isin $(som$n)) and ($VV isin $AAA) and ($VV notin $GGG)
				    TERUG=0
				    ANTWOORD=0
				    !goto NIKS    
				!endif
				!if $VV notin $GGG and $VV isin $AAA
				    AAA=!replace internal $VV by   in $AAA
				    onzin=!append word $VV to $onzin
				!endif 
			    !endif
		    !next
		!if $onzin!=
		    onzin=!nospace $onzin
		    OPMERKING=!record 40 of woorden.$taal
		    OPMERKING=$OPMERKING <br>"$onzin" ??
		!endif
	 
	!endif


	AAA=!rawmath $AAA
	GGG=!rawmath $GGG
##laatste test als het aantal woorden in het antwoord niet gelijk is aan woordmax is 
#er wat misgegaan

    leeg=!wordcnt $AAA
	!if $leeg>$woordmax
	    OPMERKING=!record 34 of woorden.$taal
	    TERUG=1
	    !increase poging
	    !goto NIKS
	!endif

    $wims_exec_error=
    
#problemen met 0.2=1/5

!if . isin $AAA or . isin $GGG
    AAA=$[1.0*($AAA)]
    GGG=$[1.0*($GGG)]
!endif    

    test=!exec pari if((($AAA)==($GGG)),1,0)
    
    
    !ifval $AAA=$GGG or $test=1
	    ANTWOORD=1
	    TERUG=0	
	    !if $latex=ja
		ANT$n=!rawmath $(ANT$n)
		ANT$n=!texmath $(ANT$n)
	    !endif
    !else
	!if $test=0
	    ANTWOORD=0
	    TERUG=0
	!else
	    !if $wims_exec_error!=
		OPMERKING=!record 106 of woorden.$taal
		TERUG=1
		ANTWOORD=0
		!goto NIKS
	    !endif
	!endif    
    !endif    


:NIKS

