#!/usr/bin/perl

use warnings;
use strict;
use Encode qw(encode decode);


#use Text::Balanced qw (extract_bracketed extract_tagged);
my $dir='../../modules';
my $site='../site/lists';
my $dom_templ='domain/domain.template';
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

for my $lang ('fr','en','fr','si','cn','nl','ca') {
  my %Domain = ( ) ;
  my $Domain=\%Domain;
  my @KEYWORDS=();
  if (-e "$site/A.$lang") {
    open LI, "$site/A.$lang";
    while(<LI>){ my $F=$_ ; chomp $F; 
      my $file= "$dir/$F/INDEX";
      next if ($file=~/(adm|devel)\//) ;
      my @keywords = treate_file ($file, $lang, \%Domain) ;
      push @KEYWORDS, @keywords;
   };
     close LI;
  } else {
    for my $file (glob("$dir/*/*/*")) { 
    next if ($file=~/(adm|devel)\//) ;
    my @keywords = treate_file ($file, $lang, \%Domain) ;
    push @KEYWORDS, @keywords;
   }
 }
 if (-e $dom_templ) {
   open LI, $dom_templ;
   while (<LI>) { my @m=split(":\n",$_);
     for my $a (@m) { $a =~ s/_/ /g;
     push @KEYWORDS, treate_group($a) };
   }
   close LI;
   };

 my $file="domain/domain.$lang";
  if (-e $file) {
      open LI, $file;
       while (<LI>) { s /,/\n/g; s /:/\n/g; s /\n+/\n/g; 
       my @m=split("\n",$_);
     for my $a (@m) { $a =~ s/_/ /g;
     push @KEYWORDS, treate_group($a) };
   }
   close LI;
   };
 out("wgrp/wgrp.$lang", join("\n", sortuniq( @KEYWORDS )))  if (@KEYWORDS);
 ##for my $d (sortuniq(keys %Domain)) {
 ##  out("test/$d.$lang", join("\n",sortuniq(split("\n",$Domain{$d})) ))  if ($Domain{$d}); }
}

sub treate_file { my ($file, $lang, $ref) = @_;
 my @res = (); my @lu = (); my @l = (); my @dom = ();
 my $keyl ='' ; my $keyw=''; my $keyu;
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
    if ($line =~ /keywords_$lang\s*=/) {
     $keyl=treate_keyword($line);
     next if (!($line =~ /,/));
     @l = treate_group($line);
    };
    if ($line =~ /keywords\s*=/) {
     $keyu=treate_keyword($line);
     next if (!($line =~ /,/));
     @lu = treate_group($line);
    }
  }
  close IN;
  if (@l) { push @res, @l } else { push @res, @lu if (@lu) };
  if ($keyl) { $keyw = $keyl } else { $keyw = $keyu if ($keyu); }
  if( @dom ) {
     for my $a (@dom) {
      if ($a) {$ref->{$a} .= $keyw . "\n" if ($keyw)  ;
      }
   }
  }
  @res;
}

sub treate_group { my ($line) = @_ ;
  $line=~ s/keywords_(\w+)\s*=\s*//g;
  $line=~ s/keywords\s*=\s*//g;
    $line=treate_accent($line);
  my @k = split(',', $line);
  my @tmp;
  for my $la (@k) { $la =~ s/^\s+//g; $la =~ s/\s+$//g; $la=lc($la);
    next if !($la);
    next if !($la =~ / /);
    push @tmp, "$la:$la," if ($la);
  }
  @tmp;
}

sub treate_keyword { my ($line) = @_ ;
  $line=~ s/keywords_(\w+)\s*=\s*//g;
  $line=~ s/keywords\s*=\s*//g;
  $line=treate_accent($line);
  if (!($line =~ /,/)) {$line =~ tr / /,/ ;};
  my @k = split(',', $line);
  my $tmp;
  for my $la (@k) { $la =~ s/^\s+//g; $la =~ s/\s+$//g; $la=lc($la);
  $tmp= join("\n",split(',', $la)) if ($la);
  }
  $tmp;
}

sub treate_accent {my ($txt) = @_; 
  $txt=decode('iso-8859-1',$txt);
  $txt =~ tr/éèêëàáâãäåùìíîïóôòç/eeeeaaaaaauiiiioooc/;
  $txt =~ s/[ÀÁÂÃÄÅ]/A/g;
  $txt =~ s/Ç/C/g;
  $txt =~ s/[ÈÉÊË]/E/g;
  $txt =~ s/[ÌÏÎÍ]/I/g;
  $txt= encode("iso-8859-1",$txt);
  $txt
}

sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
