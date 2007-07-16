#!/usr/local/bin/perl

$lignes_de_reponse = 5;

while(chomp($essai = <STDIN>)){
    if(length($essai) != 0 && substr($essai,0,1) ne "#"){
	for ($i=0; $i < $lignes_de_reponse; $i++){
	    chomp($tmp=<STDIN>); @reponse[$i]=$tmp;
	}
	$essai_ = $essai;
	$essai_ =~ s/\'/\\\'/g;
	@args = ("echo \"$essai_\" | chemeq > tmp.1");
	system @args;
	open (TMP,'tmp.1');
	$ok=1;
	for ($i=0; $i < $lignes_de_reponse; $i++){
	    chomp($tmp=<TMP>); @result[$i]=$tmp;
	    if (@result[$i] ne @reponse[$i]){$ok=0;}
	}
	if ($ok){print "OK\t\t$essai\n";}
	else{
	    print "***ERREUR***\t$essai\n";
	    for ($i=0; $i < $lignes_de_reponse; $i++){
		if(@result[$i] ne @reponse[$i]){
		    print "ligne $i : on attendait\n";
		    print "\t\"@reponse[$i]\"\n";
		    print "on a trouvé\n";
		    print "\t\"@result[$i]\"\n";
		}
	    }
	}
    }
    
}

