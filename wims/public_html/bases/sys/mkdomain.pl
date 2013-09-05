#!/usr/bin/perl

# From the distribution files
# domain : structured list of all (sub)domains (words containing underscores)
# domain.xx : list of correspondance between domain names and their translation (spaces allowed) in language xx.
# this script constructs the following files
# reversedomain  : list of parents of each domain
# domain.json    : list of domains up to third level
# domain.xx.json : sorted list of translations of domain names (without domain_name itself)
# domain.xx.tmp  : should be (not checked) domains of file domain for which a translation exists in domain.xx.
##                 In practice it is (not checked) same as domain.xx,
##                 with empty translation replaced by left member (= domain_name) of record
##                 and completed with domains appearing in domain but not in domain.xx.
##                 This is also sorted.
# domaindic.xx.tmp   : dictionnary for modind
use warnings;
use strict;
use search ('hashdomain', 'listdomain', 'out', 'sortuniq', 'treate_domainfile', 'treate_language','treate_accent');

my $dir='domain';
my @site_lang= treate_language ();
$/ = undef;

## Make sorted list of all domains in domain/domain
my @list=listdomain("$dir/domain");

## For translators : make a domain.template as a base for domain.xx file
## Helpful for creation of new language or to check for completeness of current domain.xx file
#my $text=join(":\n", @list) . ":\n";
#$text=~ s/^://g;
#$text=~ s/ +\n/\n/g;
#out("$dir/domain.template", $text);

## Put in domain/reversedomain the list of parents of each domain.
my %ref= hashdomain("$dir/domain");
my $ref=\%ref;
my $TEXT="##generated\n";
for my $tag (keys %ref) {
  $TEXT .= "$tag:$ref{$tag}\n" ;
}

out("$dir/reversedomain",$TEXT);

## Put in domain/domain.json the sorted list of domains up to third level
out("$dir/domain.json", domainjson(%ref));

## for languages for which domain.xx exists (why not "de" ?), construct files
## domain.xx.tmp : sorted list of domains names and their translation, approximately union of domain and domain.xx
## domain.xx.json : sorted list of translations of domain names (without domain_name itself)
for my $la ( @site_lang) {
 next if !(-e "$dir/domain.$la");
 my %dom = treate_domainfile ("$dir/domain.$la");
 my $dom = \%dom;
  for my $a (@list) {
  if (!$dom{$a}) { $dom{$a} = '' ; }
 };
 my @D=();
 my @D_lang=();
 my @D_reverse=();
 while ( my ($key, $value) = each(%dom) ) {
   push @D, "$key:$value";
   $key=~ s/_/ /g;
   if ($value) {
     ##push @D_reverse, lc(treate_accent($value)) . ":$key|" . lc(treate_accent($value));
     push @D_reverse, lc(treate_accent($value)) . ":$key";
   }
   $value=~ s/'/ /g;
   push @D_lang, lc($value);
 };
 out("$dir/domain.$la.tmp", join("\n",sortuniq(@D)) . "\n");
 out("$dir/domaindic.$la.tmp", join("\n",sortuniq(@D_reverse)) . "\n");
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
