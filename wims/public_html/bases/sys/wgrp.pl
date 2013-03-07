#!/usr/bin/perl

use warnings;
use strict;
use locale;


#use Text::Balanced qw (extract_bracketed extract_tagged);
my $dir="../../modules";
#$/ = undef;

my %trad = ( 
"algebras" => 'algebra',
'algo' => 'algorithmic',
'algorithmics' => 'algorithmic',
'analisi' => 'analysis',
'analiza' => 'analysis',
'arithmetic_number'  => 'arithmetic',
'arithmetics'  => 'arithmetic',
"calculous"  => 'calculus',
'evklidska_geometrija' => 'euclidian_geometry',
'geometrija' => 'geometry',
'geometrye' => 'geometry',
'logica' => 'logic',
'logika' => 'logic',
'math' => 'mathematics',
'physique' => 'physics',
'proba' => 'probability',
'botany' => 'botanics',
'=linear_algebra' => 'linear_algebra',
'linearna_algebra' => 'linear_algebra',
'linear' => 'linear_algebra',
);

for my $lang ('it','en','fr','si','cn','nl','ca') {
  my %Domain = ( ) ;
  my $Domain=\%Domain;
  my @KEYWORDS=();
  for my $file (glob("$dir/*/*/*/INDEX")) { 
    next if ($file=~/(adm|devel)\//) ;
    my @keywords = treate_file ($file, $lang, \%Domain) ;
    push @KEYWORDS, @keywords;
 };

 out("wgrp/wgrp.$lang", join("\n", sortuniq( @KEYWORDS )))  if (@KEYWORDS);
 for my $d (sortuniq(keys %Domain)) {
   out("test/$d.$lang", join("\n",sortuniq(split("\n",$Domain{$d})) ))  if ($Domain{$d});
 }
}

sub treate_file { my ($file, $lang, $ref) = @_;
 my @res = (); my @lu = (); my @l = (); my @dom = ();
 my $keyl ='' ; my $keywords=''; my $keyu;
 open(IN, $file) ;
  while (<IN>) { my $line = $_; 
    next if !($line =~ /keywords|domain/) ;
    $line =~ s/,\s+/,/g; $line =~ s/\s+,/,/g;
    if ($line =~ /domain=/){ $line =~ s/domain=// ;
      $line =~ s/( +\n|\n)//g;
      $line =~ s/ +/_/g;
      next if( $line =~ /[^[:ascii:]]/);
      $line = lc($line);
      for my $a (split(",",$line)) {
       $a = $trad{$a} if ($trad{$a});
       next if ($a =~ /tevila/) ;
       push @dom, $a ;
      };
    }
    $line =~ tr/ιθ/ee/;
    if ($line =~ /keywords_$lang=/) {
     $line =~ s/keywords\_$lang=\s*//;
     $keyl=treate_keyword($line);
     next if (!($line =~ /,/));
     @l = treate_line($line);
    };
    if ($line =~ /keywords=/) {
     $line =~ s/keywords=\s*//;
     $keyu=treate_keyword($line);
     next if (!($line =~ /,/));
     @lu = treate_line($line);
    }
  }
  close IN;
  if (@l) { push @res, @l } else { push @res, @lu if (@lu) };
  if ($keyl) { $keywords = $keyl } else { $keywords = $keyu if ($keyu); }
  if( @dom ) {
     for my $a (@dom) {
      if ($a) {$ref->{$a} .= $keywords . "\n" if ($keywords)  ;
      }
   }
  }
  @res;
}

sub treate_line { my $line = $_ ;
  $line=~ s/keywords_(\w+)=//g;
  $line=~ s/keywords=//g;
  my @k = split(',', $line);
  my @tmp;
  for my $la (@k) { $la =~ s/^\s+//g; $la =~ s/\s+$//g; $la=lc($la);
    next if !($la =~ / /);
    push @tmp, "$la:$la," if ($la);
  }
  @tmp;
}

sub treate_keyword { my $line = $_ ;
  $line=~ s/keywords_(\w+)=//g;
  $line=~ s/keywords=//g;
  if (!($line =~ /,/)) {$line =~ tr / /,/ ;};
  my @k = split(',', $line);
  my $tmp;
  for my $la (@k) { $la =~ s/^\s+//g; $la =~ s/\s+$//g; $la=lc($la);
  $tmp= join("\n",split(',', $la)) if ($la);
  }
  $tmp;
}

sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
