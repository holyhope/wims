#BEWERKIGEN:
#antwoord niet leeg
#antwoord niet te groot $(woord_max$teller)
#speciaal voor coordinaten (a:b), en (x,f) wordt a:b,x,f
#vervang heekjes () door ,
#geeft de som terug bij [] {} <>
#vervangt : ;  door ,
#alle text weg
##verwacht GOED$n=X1:Y1,X2:Y2,X3:Y3

leeg=!wordcnt $(ANT$n) 

	!if $leeg=0
	    OPMERKING=!record 21 of woorden.$taal
	    
	    poging=$[$poging+1]
	    TERUG=1
	    !exit 
	!endif

	!if $leeg>$(woordmax$n)
	    OPMERKING=!record 33 of woorden.$taal
	    poging=$[$poging+1]
	    TERUG=1
	    !exit 
	!endif

!if [ isin $(ANT$n) or { isin $(ANT$n)
#}
    OPMERKING=!record 89 of woorden.$taal
    TERUG=1
    poging=$[$poging+1]
    !exit
!endif

test=!replace internal # by   in $(ANT$n)
test=!replace internal ( by # in $test
test=!replace internal ) by # in $test
	!if # notin $test
	    OPMERKING=!record 90 of woorden.$taal
	    TERUG=1
	    poging=$[$poging+1]
	    !exit
	    
	!endif



!if \ isin $(ANT$n)
    OPMERKING=!record 29 of woorden.$taal
    poging=$[$poging+1]
    TERUG=1
    !exit
!endif




	
    #(X:Y) en blah  (X2:Y2) blahblah (X3,Y3)  wordt 3 woorden  X,Y X2,Y2 X3,Y3
    ANT$n=!lower $(ANT$n)

	AAA=!replace [a-zA-z] by  in $(ANT$n)	
	AAA=!nospace $AAA
	AAA=!replace internal ),( by # in $AAA
	AAA=!replace internal ).( by # in $AAA
	#nu testen op gebroken getallen met punt of komma:alleen gehele getallen graag 
	    !if . isin $AAA
		OPMERKING=!record 27 of woorden.$taal
		TERUG=1
		!exit
	    !endif 
	    !if , isin $AAA
		OPMERKING=!record 91 of woorden.$taal
		TERUG=1
		!exit
	    !endif 
	#nu dus(X:Y)#(X;Y)(X:Y)
	AAA=!replace internal # by ,  in $AAA    
	AAA=!replace internal )/( by , in $AAA 
	AAA=!replace internal )+( by , in $AAA
	AAA=!replace internal )-( by ,  in $AAA 
	AAA=!replace internal );( by ,  in $AAA
	AAA=!replace internal ):( by ,  in $AAA 
	AAA=!replace internal )&( by ,  in $AAA 
	AAA=!replace internal )?( by ,  in $AAA
	AAA=!replace internal )|( by ,  in $AAA
	AAA=!replace internal )( by ,  in $AAA
	AAA=!replace internal ( by   in $AAA
	AAA=!replace internal ) by   in $AAA
    
#nu X:Y,X2:Y2,X3:Y3    



:NIKS

!exit

