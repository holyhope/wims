#!/usr/bin/perl

use warnings;
use strict;
use Encode qw(encode decode);
use search ('out', 'sortuniq', 'treate_accent', 'treate_language', 'treate_dict');

#use Text::Balanced qw (extract_bracketed extract_tagged);
my @site_lang=treate_language ();
my $dir='../../modules';
my $site='../site/lists';
my $ddir='domain';
my $outputkeywords='tmp';
my $dom_templ='domain/domain.template';
my $dom_reverse='domain/reversedomain';
my $dom_json='domain/domain.json';
#$/ = undef;
###'arts','earth_sciences','history'
my @DOMAIN=('biology','chemistry','history','informatics',
  'language','mathematics','physics');

if (-e $dom_json) {
   open LI, $dom_json;  my $text;
   while(<LI>) {
   next if (/^#|<--/) ; $text .= $_;
   };
   $text=~ s/(\[|\])//g;
   $text=~ s/\'//g;
   push @DOMAIN, split(",\n", $text);
}

my %trad = ();
## should put all perl programm together
## read reversedomain
if (-e $dom_reverse) {
   open LI, $dom_reverse;
   while(<LI>) {
     my @s= split(':', $_);
     my $k= $s[0]; $k =~ s/\s//g if ($k);
     my $v= $s[1]; $v =~ s/\s//g if ($v);
     $trad{$k}=$v if (($k) && ($v));
   }
  close LI
}

for my $lang (@site_lang) {
  my %Domain = ( ) ;
  my $Domain=\%Domain;
  my @KEYWORDS=();
  if (-e "$site/A.$lang") {
    open LI, "$site/A.$lang";
    while(<LI>){ my $F=$_ ; chomp $F;
      my $file= "$dir/$F/INDEX";
      next if ($file=~/(adm|devel)\//) ;
      my @keywords = treate_index ($file, $lang, \%Domain) ;
      push @KEYWORDS, @keywords;
   };
     close LI;
  } else {
    for my $file (glob("$dir/*/*/*")) {
    next if ($file=~/(adm|devel)\//) ;
    my @keywords = treate_index ($file, $lang, \%Domain) ;
    push @KEYWORDS, @keywords;
   }
 }

### traite les groupes de mots cles
 if (-e $dom_templ) {
   open LI, $dom_templ;
   while (<LI>) { my @m=split(":\n",$_);
     for my $a (@m) { $a =~ s/_/ /g;
     push @KEYWORDS, split(",", treate_group($a)) };
   }
   close LI;
   };
### traite les groupes de mots domaine
 my $file="domain/domain.$lang";
  if (-e $file) {
      open LI, $file;
       while (<LI>) { s /,/\n/g; s /:/\n/g; s /\n+/\n/g;
       my @m=split("\n",$_);
     for my $a (@m) { $a =~ s/_/ /g;
        push @KEYWORDS, split(",", treate_group($a)) };
   }
   close LI;
   };

 out("wgrp/wgrp.$lang", join("\n", sortuniq( @KEYWORDS )))  if (@KEYWORDS);


 my @list=();
 my @ALL=();
 my @ALL_WIMS=();
 for my $d (@DOMAIN) {
   if ($Domain{$d}) {
    push @ALL, split("\n",$Domain{$d});
    out("keywords/$d.$lang.tmp",
     "\"" .
     join("\",\n\"",sortuniq(split("\n",$Domain{$d})) )
     . "'"
     );
    push @list, $d ;
    };
 }
 next if !(-e "$ddir/domain.$lang");
 my %dom = treate_dict ("$ddir/domain.$lang");
 while ( my ($key, $value) = each(%dom) ) {
   push @ALL, split(",", lc(treate_accent($value)));
   push @ALL_WIMS, split(",", lc(treate_accent($value)));
 }
 out("keywords/list.$lang", join(",",sortuniq(@list)));
##only official keywords
 out("$outputkeywords/keywords.$lang.json",
     "[\"" . join("\",\n\"",sortuniq(@ALL_WIMS) ) . "\"]"
);
##all keywords
out("$outputkeywords/all.$lang.json",
     "[\"" . join("\",\n\"",sortuniq(@ALL) ) . "\"]"
);

}

######################################################

sub treate_index { my ($file, $lang, $ref) = @_;
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
      for my $a (split(",", $line)) {
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
      if ($a) {$ref->{$a} .= $keyw . "\n" if ($keyw) ;
      }
   }
  }
  @res;
}

sub treate_group { my ($line) = @_ ;
  $line=~ s/keywords_(\w+)\s*=\s*//g;
  $line=~ s/keywords\s*=\s*//g;
  $line=treate_accent($line);
  $line =~ s/\./,/g;
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
  for my $la (@k) {
  $la =~ s/^\s+//g; $la =~ s/\s+$//g; $la=lc($la);
  ##$la=~ s/($nokeyword)//g;
  if ($la && length($la) > 2 ) {
    if ($tmp) { $tmp .= "\n" . join("\n",split(',', $la))}
      else
      {$tmp = join("\n",split(',', $la))}
  }
  }
  #$tmp=~ s/'/\\'/g if ($tmp);
  $tmp;
}

