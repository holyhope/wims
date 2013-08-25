package search;

use strict;
use warnings;
use Encode;  

use Exporter;
our @ISA = 'Exporter';
our @EXPORT = ('hashdomain', 'listdomain', 'out','sortuniq', 'treate_accent','treate_domainfile', 'treate_language');

sub treate_domainfile { my ($file) = @_;
   my %ref = ( ) ; my $ref=\%ref; my $text;
   open IN, "$file";
   while (<IN>) { 
   $text = $_ ;
   $text =~ s/\n +/\n/g;
   $text =~ s/\\//g;
   $text =~ s/^(\s+)//g;
   $text=~ s/\n+/\n/g;
   my @L = sortuniq(split("\n",$text));
   for my $l (@L) {
     my @la=split(":", $l) ;
     $ref{$la[0]}=$la[1] if ($la[1]);
    }
   }
  close IN;
 %ref;
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
  return if !(@_) ; 
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}

sub listdomain { my ($file)=@_ ; 
  my $text='';
  open IN, "$file";
  while (<IN>) { $text = $_ ;
   $text =~ s/[,:]/\n/g;
   $text =~ s/\n +/\n/g;
   $text =~ s/\\//g;
   $text =~ s/^(\s+)//g;
   $text=~ s/\n+/\n/g;
 }
 close IN;
 sortuniq(split("\n",$text))
}

## reversing the domain tree

sub hashdomain { my ($file)=@_;
 open IN, "$file";
 my %ref = ( ) ; my $ref=\%ref;
 while (<IN>) { my $text=$_ ; $text=~ s/\\\n\s*//g;
   $text=~ s/\n\s+/\n/g;
   my @text= split("\n", $text);
   for my $line (@text) { 
     next if !($line) ;
     $line =~ s/\s+//g;
     my @cut=split(":", $line) ;
     if ($cut[1]) {
       my @son=split(',',$cut[1]);
      for my $s (@son) { 
        if ($ref{$s}) { $ref{$s} .= "," . $cut[0]} else {$ref{$s} = $cut[0]}
      }
     }
   }
}
close IN;
  %ref
}

sub treate_language {
  my $site_language='en fr nl it cn';
  my $conf='../../../log/wims.conf';
  if (-e "$conf") {
   open IN, "$conf";
   while (<IN>) {
     if ($_ =~ s/site_languages=//) { $site_language= $_ ; }
   }
  close IN;
 }
split(' ', $site_language) ;
}
