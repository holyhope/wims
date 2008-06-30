#################################################################
#	ALLEEN ONGELIJKHEDEN					#
#		GOED$n x<4&&x>5 of 4<x&&x>5 of x<4&&4<x&&x<5	#
#		ANT$n x<4 en x>5	5<=x<6 			#
#################################################################
ANT$n=!lower $(ANT$n)
wims_exec_error=
!if $woordmax=
    woordmax=10
!endif
tussenscore=0
testscore=0
noodsprong=$afrondingsfactor
#ivm grafische "rekenmachine mode"
!if $afrondingsfactor=1000000
    afrondingsfactor=100
!endif

    leeg=!wordcnt $(ANT$n) 
	!if $leeg=0
	    OPMERKING=!record 21 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !exit 
	!endif
	!if $leeg>$woordmax
	    OPMERKING=!record 33 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !exit 
	!endif
	!if , isin $(ANT$n)
	    OPMERKING=!record 109 of woorden.$taal
	    TERUG=1
	    !exit 
	!endif
	!if x notin $(ANT$n)
	    OPMERKING=!record 23 of woorden.$taal
	    TERUG=1
	    !exit 
	!endif
	test=!replace internal < by # in $(ANT$n)
	test=!replace internal > by # in $test
	!if # notin $test
	    OPMERKING=!record 115 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !exit 
	!endif

#HET TWEEDE GEDEELTE : $(ANT$n) de ongelijkheid
## eerst de getallen....wat een werk 
##(daar moeten we een C-programma voor schijven !!)
# testen op >= =< in GOED$n en ANT$n

	
	aa=!replace internal sqrt by SQRT in $(ANT$n)
##checken op >= 
	test1=!replace internal <= by @ in $(GOED$n)
	test1=!replace internal =< by @ in $test1
	test1=!replace internal => by @ in $test1
	test1=!replace internal >= by @ in $test1
	aaa=!replace internal @ by  in $aa
	aaa=!nospace $aaa
	aaa=!replace internal <= by @ in $aaa
	aaa=!replace internal =< by @ in $aaa
	aaa=!replace internal => by @ in $aaa
	aaa=!replace internal >= by @ in $aaa
	!if @ isin $test1
	    !if @ notin $aaa
	    	ANTWOORD=0
		ANT$n=!htmlmath $(ANT$n)
		ANT$n=$(ANT$n) $NOK 
		TERUG=0
		!exit	    
	    !endif
	!else
	    !if @ isin $aaa
	    	ANTWOORD=0
		ANT$n=!htmlmath $(ANT$n)
		ANT$n=$(ANT$n) $NOK 
		TERUG=0
		!exit	    
	    !endif
	!endif
##
	aa=!words2items $aa
	aa=!nospace $aa
	aa=!rawmath $aa
	aa=!replace [a-z\~\`\!\@\&\&\#\%\_\"\:\;|'\?\|\=\>\<] by ,  in $aa 
	aa=!replace internal SQRT by sqrt in $aa
	!for p=1 to $woordmax
	    aa=!replace internal ,, by , in $aa
	!next
	aa=!replace internal sqrt, by sqrt in $aa
	aa=!replace internal (, by ( in $aa
	aa=!replace internal ,) by ) in $aa
	aa=!replace internal ,. by . in $aa
	aa=!replace internal ., by . in $aa
	aa=!replace internal ,/ by / in $aa
	aa=!replace internal /, by / in $aa
	aa=!replace internal ,* by * in $aa
	aa=!replace internal *, by * in $aa
	aa=!replace internal ^, by ^ in $aa
	aa=!replace internal ,^ by ^ in $aa
	aa=!replace internal ^, by ^ in $aa
#problemen bij 3 getallen -4,-4,-4	
	#aa=!replace internal ,- by - in $aa
	#aa=!replace internal -, by - in $aa
	aa=!replace internal ,+ by + in $aa
	aa=!replace internal +, by + in $aa
	aa=!nospace $aa
#LET OP: CRUCIAAL noteer GOED$n alijd als x<4&&x>5
    
	gg=!replace internal && by , in $(GOED$n)	
	gg=!replace [x\<\>\&\&&\=] by  in $gg	
	gg=!nospace $gg
	T1=!char 1 of $aa	
	T2=!char -1 of $aa
	!if $T1=,
	    aa=!char 2 to -1 of $aa
	!endif    
	!if $T2=,
	    aa=!char 1 to -2 of $aa
	!endif    

	R=!itemcnt $aa
	S=!itemcnt $gg

#debug	
	!if $R > $S or $R=0
	    OPMERKING=!record 145 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !exit
	!endif

	!for r=1 to $R
	    A$r=!item $r of $aa
	    G$r=!item $r of $gg
	!next
	
	!if $afrondingsfactor > 0
	    !for r=1 to $R
		a$r=$[(round(($(A$r))*$afrondingsfactor))/$afrondingsfactor]
		g$r=$[(round(($(G$r))*$afrondingsfactor))/$afrondingsfactor]
	    !next
	!else
	    # pari if(1/5==0,2,ja,nee) ==> nee 
	    # pari if(1.0*(1/5)==0,2,ja,nee) ==> ja 
	    !for r=1 to $R
		a$r=1.0*$(A$r)
		g$r=1.0*$(G$r)
	    !next	
	!endif
	!if $R=3
	    test1=!exec pari if( ($a1==$g1 || $a1==$g2 || $a1==$g3) && ($a2==$g1 || $a2==$g2 || $a2==$g3) && ($a3==$g1 || $a3==$g2 || $a3==$g3),ja,nee)
	!endif
	!if $R=2
	    test1=!exec pari if( ($a1==$g1 || $a1==$g2) && ($a2==$g2 || $a2==$g1),ja,nee)
	!endif	
	!if $R=1
	    test1=!exec pari if($a1==$g1,ja,nee)
	!endif
#OPMERKING=$R =R $S=S $a1=a1 $g1=g1 test1=$test1
#	TERUG=1
#	!exit

	!if $wims_exec_error!=
	    OPMERKING=!record 145 of woorden.$taal
	    !increase poging
	    TERUG=1
	    !exit
	!endif
	##getallen niet goed: klaar...antwoord fout
	!if $test1=nee
	    ANTWOORD=0
	    ANT$n=!htmlmath $(ANT$n)
	    ANT$n= $(ANT$n) $NOK 
	    TERUG=0
	    !exit
	!endif	
#DE ONGELIJKHEID (wat een ellende)
	test=!replace internal sqrt by SQRT in $(ANT$n)    
	test=!words2items $test
	test=!replace [a-wyz\~\`\!\@\&\+\#\%\_\"\'\?\|] by , in $test
	test=!replace internal SQRT by sqrt in $test
	test=!rawmath $test
    !for q=1 to $woordmax
	test=!replace internal ,, by , in $test
    !next
	test=!replace internal =, by = in $test
	test=!replace internal ,= by = in $test
	test=!replace internal *, by * in $test
	test=!replace internal ,* by * in $test
	test=!replace internal (, by ( in $test
	test=!replace internal ,) by ) in $test
	test=!replace internal +, by + in $test
	test=!replace internal ,+ by + in $test
	test=!replace internal ^, by ^ in $test
	test=!replace internal ,^ by ^ in $test
	test=!replace internal -, by - in $test
	test=!replace internal ,- by - in $test
	test=!replace internal /, by / in $test
	test=!replace internal ,/ by / in $test
	test=!replace internal >, by > in $test
	test=!replace internal ,> by > in $test
	test=!replace internal <, by < in $test
	test=!replace internal ,< by < in $test
	test=!replace internal >,x by >x in $test
	test=!replace internal x,> by x> in $test
	test=!replace internal <,x by <x in $test
	test=!replace internal x,< by x< in $test
	test=!replace internal xx by x&&x in $test
	test=!replace internal x,x by x&&x in $test
# oh man
        test=!replace internal =x< by =x&&x< in $test
        test=!replace internal =x> by =x&&x> in $test
## 5< =x=> =6 6< =x&&x>  =6
        test=!replace internal >x= by >x&&x= in $test
        test=!replace internal <x= by <x&&x= in $test
        
	
	test=!replace internal <x< by <x&&x< in $test
	test=!replace internal >x> by >x&&x> in $test
	test=!replace internal >x< by >x&&x< in $test
	test=!replace internal <x> by <x&&x> in $test
	T1=!char 1 of $test
	T2=!char -1 of $test
	!if $T1=,
	    test=!char 2 to -1 of $test
	!endif    
	!if $T2=,
	    test=!char 1 to -2 of $test
	!endif    

	test=!replace internal , by && in $test
	##vreselijke truuk: we vervangen de x door een getal; testen of de bewering waar is	
	test=!replace internal x by 0 in $test
	ggg=!replace internal x by 0 in $(GOED$n)
	##x>4 of 4<x => 0>4&&4<0
	controle=!exec pari if(($test)==($ggg),ja,nee)	
	
	!if $controle=ja
	    TERUG=0
	    ANTWOORD=1
	    result=$OK
	!else    
	    TERUG=0
	    ANTWOORD=0
	    result=$NOK 
	!endif
	
	ANT$n=!htmlmath $(ANT$n)
	ANT$n=<b>$(ANT$n)</b> $result 	    
	    
	

afrondingsfactor=$noodsprong

