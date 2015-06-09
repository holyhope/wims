package search;

use strict;
use warnings;
use Encode;

use Exporter;
our @ISA = 'Exporter';
our @EXPORT = ('hashdomain', 'listdomain', 'out', 'sortuniq', 'treate_accent',
  'treate_dict', 'treate_language', 'dictionnary', 'reverse_dic', 'canonify');

sub canonify { my ($w)=@_; treate_accent(lc($w)) }

sub treate_dict { my ($file) = @_;
   my %ref = ( ) ; my $ref=\%ref;
   my $text;
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
     $ref{canonify($la[0])}=join(':',@la[1..@la-1]) if ($la[1]);
    }
   }
  close IN;
 %ref;
}

sub dictionnary { my ($file, @words)=@_;
  my %dic=treate_dict($file) ;
  my $dic=\%dic;
  my @W=();
  if (@words) {
   for my $w (@words) {
    next if !($w);
    for my $ww (split(',', $w)) {
     if ( $dic{canonify($ww)} ) { push @W, $dic{canonify($ww)} ; };
     }
   }
   sortuniq ( @W )
   }
   @W;
}

sub treate_accent {my ($txt) = @_;
  $txt=decode('iso-8859-1',$txt);
  $txt =~ tr/éèêëàáâãäåùìíîïóôòç/eeeeaaaaaauiiiioooc/;
  $txt =~ s/[ÀÁÂÃÄÅ]/A/g;
  $txt =~ s/Ç/C/g;
  $txt =~ s/[ÈÉÊË]/E/g;
  $txt =~ s/[ÌÏÎÍ]/I/g;
  $txt =~ s/'/ /g;
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
 $/ = undef;
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
       $ref->{'next'}{$cut[0]}=$cut[1];
      for my $s (@son) {
        if ($ref->{'prev'}{$s}) { $ref->{'prev'}{$s} .= "," . $cut[0]} else {$ref->{'prev'}{$s} = $cut[0]}
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
  $site_language=~  s/,/ /g; $site_language=~  s/ +/ /g;
  split(' ', $site_language) ;
}

sub reverse_dic { my @liste=@_;
  my %ref = ( ) ; my $ref=\%ref;
  for my $file (@liste) {
   open IN, "$file";
   while (<IN>) {
    next if ($_ =~ /^#/);
    my $text= $_ ; $text=~ s/\n//;
    my @text=split(":", $text);
    my $t=$text[0]; $t=~ s/\n//;
    my @L= split(",",$text[1]);
    for my $a (@L) {
     if ($ref{$a}) {  $ref{$a}.= "," . $t ; }
     else { $ref{$a} = $t ; }
    }
   }
   close IN;
  }
  %ref
}
