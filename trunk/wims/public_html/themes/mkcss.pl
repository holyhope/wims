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
  my @f3=split("/",$f1);
  my $f3=$f3[0];
  my $TEXT ="/*! generated from $f - do not modify directly */\n" ;
  my %colors;
  open(IN,"$f");
  while (<IN> ) {
   my $line=$_ ;
   $line =~ s/#[^\n]+//g ;
   $line =~ s/--- (.*) ---/treate($1)/ge ;
   $TEXT .= $line ;
 }
 close IN ;
 $TEXT .= "\n";
 # lecture de oefcolors
 my $fc="$f3/oefcolors";
 if (!(-e $fc)) { $fc="oefcolors" };
 open(INN, "$fc");
 $/ = "\n";
 while(<INN>) {
  if( /!set (\w+)=(\w+)/) { $colors{$1}=$2;}
 }
 close INN;
 ## remplacement des couleurs oef
 my $colors=\%colors;
 for my $k (keys %{$colors}) {
   $TEXT =~ s/color: *$k/color:$colors{$k}/g;
 }

 out("$f2" ,$TEXT) ;
 $/ = undef;
 system("java -jar yuicompressor $f2 -o $f1 -v; rm $f2");
}

sub t { my ($c1,$c2,$L)=@_; $L->{$c1}=$c2};

sub treate { my ($c)= @_ ;
  return if ((!$c) || ($c =~ /#/));
  open(INN, $c);
  my $text = <INN> ;
  close(INN) ;
  "\n/*! from $c */\n$text" ;
};

sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || warn "Creation du bloc $bloc impossible";
  print OUT $text ; close OUT ;
}
