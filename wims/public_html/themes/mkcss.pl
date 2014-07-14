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
  my $f1= $f ; $f1 =~ s/.template// ; my $f2 = "$f1.tmp.css" ;
  my $TEXT ="/*! generated form $f - do not modify directly */\n" ;
  open(IN,"$f");
  while (<IN> ) {
   my $line=$_ ;
   next if ($line =~ /^#/) ;
   $line =~ s/--- (.*) ---/treate($1)/ge ;
   $TEXT .= $line ;
 }
 close IN ;
 $TEXT .= "\n";
 out("$f2" ,$TEXT) ;
 system("java -jar yuicompressor $f2 -o $f1 -v; rm $f2");
}


sub treate { my ($c)= @_ ;
  if ($c) {
  open(INN, $c);
  print $c . "\n";
  my $text = <INN> ;
  close(INN) ;
  "\n/*! from $c */\n$text" ;
  }
};



sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || warn "Creation du bloc $bloc impossible";
  print OUT $text ; close OUT ;
}
