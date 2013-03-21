#!/usr/bin/perl

use warnings;
use strict;

$/ = undef;
my $dir='domain';
my $text=''; my $text2='';
## list of all domains in domain/domain
open IN, "$dir/domain";

while (<IN>) { $text = $_ ;
   $text =~ s/[,:]/\n/g;
   $text =~ s/\n +/\n/g;
   $text =~ s/\n\n/\n/g;
   $text =~ s/\\//g;
   $text =~ s/^(\s+)//g;
}
close IN;
$text=~ s/\n\n/\n/g;
$text2="[\"" . join("\",\n\"",sortuniq(split("\n",$text))) . "\"]";
$text=join(":\n",sortuniq(split("\n",$text))) . ":\n";
$text=~ s/^://g;
$text=~ s/ +\n/\n/g;
$text2=~ s/^://g; 
$text2=~ s/ +\n/\n/g;
out("$dir/domain.template", $text);
out("$dir/domain.json", $text2);

## reversing the domain tree
my %ref = ( ) ;
my $ref=\%ref;
$/ = undef;

###fixme : it is not really a tree : so there may be several fathers
open IN, "$dir/domain";
while (<IN>) { my $text=$_ ; $text=~ s/\\\n\s*//g;
   $text=~ s/\n\s+/\n/g;
   my @text= split("\n", $text);
   for my $line (@text) { 
     next if !($line) ;
     $line =~ s/\s+//g;
     my @cut=split(":", $line) ;
     if ($cut[1]) {
       my @son=split(',',$cut[1]);
      for my $s (@son) { $ref{$s} = $cut[0]; }
     } 
   }
}
close IN;

my $TEXT="##generated\n";
for my $tag (keys %ref) {
  $TEXT .= "$tag:$ref{$tag}\n" ;
}
out("$dir/reversedomain",$TEXT);


sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
