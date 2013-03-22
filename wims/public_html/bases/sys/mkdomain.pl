#!/usr/bin/perl

use warnings;
use strict;

$/ = undef;
my $dir='domain';
## list of all domains in domain/domain

my @list=listdomain();
my $text=join(":\n", @list) . ":\n"; 
$text=~ s/^://g;
$text=~ s/ +\n/\n/g;
out("$dir/domain.template", $text);

my %ref= hashdomain() ;
my $ref=\%ref;
my $TEXT="##generated\n";
for my $tag (keys %ref) {
  $TEXT .= "$tag:$ref{$tag}\n" ;
}
out("$dir/reversedomain",$TEXT);

##domain list in the three  first levels
out("$dir/domain.json", domainjson(%ref));


sub domainjson  { my ($ref) = @_ ; 
  my @D=();
  while ( my ($key, $value) = each(%ref) ) {
    if ( $value =~ /domain\b/ ) { push @D, $key }
    else { 
      if ($ref{$value}) {
       if ($ref{$value} =~ /domain\b/) { push @D, $key } 
         else {
             if ($ref{$ref{$value}}) {
               if($ref{$ref{$value}} =~ /domain\b/) { push @D, $key; } 
               }
           }
       }; 
     };
   }
"##generated\n['" . join("',\n'", sortuniq(@D)) . "']";
}

sub listdomain {
  open IN, "$dir/domain";
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

sub hashdomain {
 open IN, "$dir/domain";
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

sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
