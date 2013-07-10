#!/usr/bin/perl

use warnings;
use strict;
use search ('hashdomain', 'listdomain', 'out', 'sortuniq', 'treate_domainfile');

$/ = undef;
my $dir='domain';
## list of all domains in domain/domain

my @list=listdomain("$dir/domain");
#my $text=join(":\n", @list) . ":\n"; 
#$text=~ s/^://g;
#$text=~ s/ +\n/\n/g;
#out("$dir/domain.template", $text);

my %ref= hashdomain("$dir/domain");
my $ref=\%ref;
my $TEXT="##generated\n";
for my $tag (keys %ref) {
  $TEXT .= "$tag:$ref{$tag}\n" ;
}

out("$dir/reversedomain",$TEXT);

##domain list in the three  first levels
out("$dir/domain.json", domainjson(%ref));

for my $la ('fr','en','it','si','cn','nl','ca','es') {
 next if !(-e "$dir/domain.$la");
 my %dom = treate_domainfile ("$dir/domain.$la");
 my $dom = \%dom; 
  for my $a (@list) {
  if (!$dom{$a}) { $dom{$a} = '' ; }
 };
 my @D=();
 my @D_lang=();
 while ( my ($key, $value) = each(%dom) ) {
   push @D, "$key:$value";
   $value=~ s/'/ /g;
   push @D_lang, lc($value);
 };
 out("$dir/domain.$la.tmp", join("\n",sortuniq(@D)) . "\n");
 out("$dir/domain.$la.json", "\"" . join("\",\n\"",sortuniq(@D_lang)) . "\"");
}

#####################################################
sub domainjson { my ($ref) = @_ ; 
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
"<!-- generated -->\n['" . join("',\n'", sortuniq(@D)) . "']";
}
