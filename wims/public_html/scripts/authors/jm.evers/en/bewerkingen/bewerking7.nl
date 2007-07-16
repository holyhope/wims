#################################################################
#			SNIJPUNTEN				#
#		GOED$n X1,Y1,X2,Y2 (1,2,3,4,5 snijpunten)	#
#		ANT$n (X1:Y1) of ook (X2:Y2)			#			#
#################################################################
ANT$n=!lower $(ANT$n)
wims_exec_error=
!if $woordmax=
    woordmax=10
!endif
noodsprong=$afrondingsfactor
#ivm grafische "rekenmachine mode"
!if $afrondingsfactor=1000000
    afrondingsfactor=100
!endif

# eerste antwoord de coordinaten
leeg=!wordcnt $(ANT$n) 
    !if $leeg=0
	OPMERKING=!record 21 of woorden.$taal
	!increase poging
	TERUG=1
	!goto NIKS 
    !endif
    !if $leeg>$woordmax
	OPMERKING=!record 33 of woorden.$taal
	!increase poging
	TERUG=1
	!goto NIKS 
    !endif
    #dus (1:0) (7;0)
    test=!replace internal ( by # in $(ANT$n)
    !if # notin $test
	OPMERKING=!record 90 of woorden.$taal
	TERUG=1
	!increase poging
	!goto NIKS
    !endif
    test=!replace : by # in $(ANT$n)
    test=!replace ; by # in $test
    !if # notin $test
	OPMERKING=!record 90 of woorden.$taal
	TERUG=1
	!increase poging
	!goto NIKS
    !endif
    !if , isin $(ANT$n)
	OPMERKING=!record 109 of woorden.$taal
	TERUG=1
	!goto NIKS 
    !endif
    !if \ isin $(ANT$n) and \ notin $(GOED$n)
	OPMERKING=!record 29 of woorden.$taal
	!increase poging
	TERUG=1
	!goto NIKS
    !endif

	ant=!nospace $(ANT$n)
	!if sqrt isin $ant
	    ant=!replace internal sqrt by SQRT in $ant
	!endif
	ant=!replace [a-z\~\`\!\@\&\#\%\_\"\'\?\|\=\<\>] by  in $ant
	ant=!replace internal ):( by , in $ant
	ant=!replace internal );( by , in $ant
	ant=!replace internal )( by , in $ant
	ant=!replace internal ; by , in $ant
	ant=!replace internal : by , in $ant
	ant=!replace internal ( by  in $ant
	ant=!replace internal ) by  in $ant
	ant=!nospace $ant 	 
	laatstetest=!itemcnt $ant
	    #bijvoorbeeld 2 snijpunten :max 4 items: X1,Y1,X2,Y2
	itemsgoed=!itemcnt $(GOED$n)    
	!if $laatstetest > $itemsgoed
	    OPMERKING=!record 141 of woorden.$taal
	    TERUG=1
	    !increase poging
	    !goto NIKS
	!else
	    !if $laatstetest < $itemsgoed
		OPMERKING=!record 35 of woorden.$taal
		TERUG=1
		!increase poging
		!goto NIKS
	    !endif
	!endif
    !if SQRT isin $ant
	!for r=1 to $itemsgoed
	    a=!item $r of $ant    
	    !if SQRT isin $a
		a=!replace internal SQRT by sqrt, in $a
		deel1=!item 1 of $a
		deel2=!item 2 of $a
		antw=!append item $deel1($deel2) to $antw
		antw=!rawmath $antw
	    !else
		antw=!append item $a to $antw	
	    !endif
	!next r
	ant=$antw
    !endif	
	!for r=1 to $itemsgoed
	    G$r=!item $r of $(GOED$n)
    	    A$r=!item $r of $ant
	!next r
	    #afronden van het antwoord
	    #afrondingsfactor=0 : exact
	!if $afrondingsfactor > 0
	    !for r=1 to $itemsgoed
		g$r=$[(round($afrondingsfactor*($(G$r))))/$afrondingsfactor]
    		a$r=$[(round($afrondingsfactor*($(A$r))))/$afrondingsfactor]
	    !next r
	!else
	    # pari if(1/5==0,2,ja,nee) ==> nee 
	    # pari if(1.0*(1/5)==0,2,ja,nee) ==> ja 
	    !for r=1 to $itemsgoed
		a$r=1.0*$(A$r)
		g$r=1.0*$(G$r)
	    !next    
	!endif
	##dit moet beter/sneller kunnen (matrix)
	tussenscore=0
	!if $itemsgoed=2
	#1 snijpunt
	    test1=!exec pari if( ($g1==$a1 && $g2==$a2),1,0)
	    tussenscore=$test1
	    ANT$n=($A1:$A2)  
	    !goto KLAAR
	!endif	
	!if $itemsgoed=4
	#2 snijpunten
		test=!exec pari if( ($g1==$a1 && $g2==$a2) || ($g1==$a3 && $g2==$a4),1,0)\
		if( ($g3==$a1 && $g4==$a2) || ($g3==$a3 && $g4==$a4),1,0)
		test1=!line 1 of $test
		test2=!line 2 of $test
		tussenscore=$[$test1 + $test2]
		ANT$n=($A1:$A2) &and; ($A3:$A4)
	    !goto KLAAR
	!endif
	!if $itemsgoed=6
	#3 snijpunten
		test=!exec pari if( ($g1==$a1 && $g2==$a2) || ($g1==$a3 && $g2==$a4) || ($g1==$a5 && $g2==$a6),1,0)\
		if( ($g3==$a1 && $g4==$a2) || ($g3==$a3 && $g4==$a4) || ($g3==$a5 && $g4==$a6),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6),1,0)
		!for t=1 to 3
		    test1=!item $t of $test
		    tussenscore=$[$tussenscore+$test1]
		!next
		ANT$n=($A1:$A2) &and; ($A3:$A4) &and;  ($A5:$A6)
	    !goto KLAAR
	!endif
	!if $itemsgoed=8
	#4 snijpunten
		test=!exec pari if( ($g1==$a1 && $g2==$a2) || ($g1==$a3 && $g2==$a4) || ($g1==$a5 && $g2==$a6) || ($g1==$a7 && $g2==$a8),1,0)\
		if( ($g3==$a1 && $g4==$a2) || ($g3==$a3 && $g4==$a4) || ($g3==$a5 && $g4==$a6) || ($g3==$a7 && $g4==$a8),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6) || ($g5==$a7 && $g6==$a8),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6) || ($g7==$a7 && $g8==$a7),1,0)
		!for t=1 to 4
		    test1=!item $t of $test
		    tussenscore=$[$tussenscore+$test1]
		!next
		ANT$n=($A1:$A2) &and; ($A3:$A4) &and; ($A5:$A6) &and; ($A7:$A8)
	    !goto KLAAR
	!endif
	!if $itemsgoed=10
	#snijpunten
		test=!exec pari if( ($g1==$a1 && $g2==$a2) || ($g1==$a3 && $g2==$a4) || ($g1==$a5 && $g2==$a6) || ($g1==$a7 && $g2==$a8) || ($g1==$a9 && $g2==$a10),1,0)\
		if( ($g3==$a1 && $g4==$a2) || ($g3==$a3 && $g4==$a4) || ($g3==$a5 && $g4==$a6) || ($g3==$a7 && $g4==$a8) || ($g3==$a9 && $g4==$a10),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6) || ($g5==$a7 && $g6==$a8) || ($g5==$a9 && $g6==$a10),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6) || ($g7==$a7 && $g8==$a7) || ($g7==$a9 && $g8==$a10),1,0)\
		if( ($g5==$a1 && $g6==$a2) || ($g5==$a3 && $g6==$a4) || ($g5==$a5 && $g6==$a6) || ($g7==$a7 && $g8==$a7) || ($g9==$a9 && $g10==$a10),1,0)
		!for t=1 to 5
		    test1=!item $t of $test
		    tussenscore=$[$tussenscore+$test1]
		!next
		ANT$n=($A1:$A2) &and; ($A3:$A4) &and; ($A5:$A6) &and; ($A7:$A8) &and; ($A9:$A10)
	    !goto KLAAR
	!endif
:KLAAR
    !if $tussenscore = $[$itemsgoed/2]
	ANT$n=$(ANT$n) $OK
    !else
	!if $tussenscore > $[$itemsgoed/4]
	    ANT$n=$(ANT$n) $BOK
	!else
	    ANT$n=$(ANT$n) $NOK
	!endif		
    !endif
    ANTWOORD=$[(round(20*$tussenscore/$itemsgoed))/10]
    TERUG=0
:NIKS
!exit