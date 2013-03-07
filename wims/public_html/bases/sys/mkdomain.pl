#!/usr/bin/perl

use warnings;
use strict;

$/ = undef;
my $text='';
open IN, "domain/domain";

while (<IN>) { $text = $_ ;
   $text =~ s/[,:]/\n/g;
   $text =~ s/\n +/\n/g;
   $text =~ s/\n\n/\n/g;
   $text =~ s/\\//g;
   $text =~ s/^(\s+)//g;
}
close IN;
$text=join(":\n",sortuniq(split("\n",$text))) . ":\n";

$text=~ s/^://g;
out("domain/domain.template", $text);

sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
