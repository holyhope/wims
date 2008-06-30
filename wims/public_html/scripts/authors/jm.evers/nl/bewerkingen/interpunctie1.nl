#check op
#	leeg
#	maximale aantal woorden
#	: ; % / \ < > . ,
leeg=!wordcnt $(ANT$n) 
	!if $leeg=0
	    OPMERKING=!record 21 of woorden.$taal
	    TERUG=1
	    !exit 
	!endif

	!if $(woordmax$n)!=  and $leeg>$(woordmax$n)
	    OPMERKING=!record 33 of woorden.$taal
	    TERUG=1
	    !exit 
	!endif

	!if : notin $(ANT$n) and : isin $(GOED$n)
	    OPMERKING=!record 34 of woorden.$taal
	    TERUG=1
	    !exit
	!endif

	!if % notin $(ANT$n) and % isin $(GOED$n)
	    OPMERKING=!record 99 of woorden.$taal
	    TERUG=1
	    !exit
	!endif
	
	!if % isin $(ANT$n) and % notin $(GOED$n)
	    OPMERKING=!record 104 of woorden.$taal
	    TERUG=1
	    !exit
	!endif
	
	

	!if  / isin $(GOED$n) and  / notin $(ANT$n) 
	    !if : isin $(ANT$n) or \ isin $(ANT$n) 
		OPMERKING=!record 29 of woorden.$taal
    		TERUG=1
    		!exit	
	    !endif
	!endif

	!if , isin $(ANT$n)  and , notin $(GOED$n)
		OPMERKING=!record 109 of woorden.$taal
		TERUG=1
		!exit
	!endif
	
	!if . isin $(ANT$n)  and . notin $(GOED$n)
		OPMERKING=!record 103 of woorden.$taal
		TERUG=1
		!exit
	!endif
	    
	tussentest1=!replace \<\> by # in $(GOED$n)
	tussentest2=!replace internal # by   in $(ANT$n)
	tussentest2=!replace [\<\>] by # in $tussentest2

	!if ( # notin $tussentest2 and # isin $tussentest1 )
		OPMERKING=!record 123 of woorden.$taal
		TERUG=1
		!exit
	!endif

	!if ( # isin $tussentest2 and # notin $tussentest1 )
		OPMERKING=!record 124 of woorden.$taal
		TERUG=1
		!exit
	!endif


