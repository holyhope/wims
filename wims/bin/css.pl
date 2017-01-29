#!/usr/bin/perl
## create the file public_html/bases/sys/css_classes from the css of public_html/themes/standard
## use in documentation
use warnings;
use strict;
#use Text::Balanced qw (extract_bracketed extract_tagged);

$/ = undef;

 my $dir="public_html/themes/_css";
 my $outfile="public_html/bases/sys/css_classes";
 my $TEXT=" ";###generated by bin/css.pl - do not change by hand \n;
 my $file='utilities.css' ;
 ##$TEXT  .= "\n!!generated from file : $file\n";
 my $text=treate_file("$dir/$file");
 $TEXT .= "\n$text";
 out($outfile, $TEXT) ;


sub treate_file { my ($file)=@_;
 my $test=0;
 open(IN, $file) ;
  my $text = <IN>; close(IN);
  $text =~ s/\n\t+//g ;
  $text =~ s/\n\}/\}/g ;
  $text =~ s/\{[^\{]+\}/\{ \}/g ;
  $text =~ s/\{ \}(.)/\{ \}\n$1/g ;
  $text =~ s,\/\*,<h3>,g ;
  $text =~ s,\*\/,<\/h3>,g ;
  $text ;
}
sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}
