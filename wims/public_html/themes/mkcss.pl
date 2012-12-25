#!/usr/bin/perl

use strict "vars";
use strict "subs";
use locale;
use warnings;
$/ = undef;

##{
##  last if (/^$/);
##  if  (/^(.*)$/)   { $dir=$1 }
##} ;

my $char="---";

for my $f (glob("*/*.css.template")) {
  my $f1= $f ; $f1 =~ s/.template// ;
  my $TEXT ="/* generated form $f.css.template - do not modify directly */\n" ;
  open(IN,"$f");
  while (<IN> ) {
   my $line=$_ ;
   next if ($line =~ /^#/) ;
   $line =~ s/--- (.*) ---/treate($1)/ge ;
   $TEXT .= $line ;
 }
 close IN ;
 $TEXT .= "\n";
 out("$f1" ,$TEXT) ;
}


sub treate { my ($c)= @_ ;
  open(INN, $c);
  my $text = <INN> ; 
  close(INN) ;
  "\n/* from $c */\n$text" ;
} ;



sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || warn "peut pas créer $bloc"; 
  print OUT $text ; close OUT ; 
} 