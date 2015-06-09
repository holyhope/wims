#!/usr/bin/perl
use strict "vars";
use strict "subs";
use warnings;
use Text::Balanced qw (extract_bracketed extract_tagged);
my $tag='test';
my $file='test';
my $out='.';
while ($_ = shift (@ARGV))
{
  last if (!/^--/);
  if (/^--file=(.*)$/) { $file = $1; }
  elsif (/^--tag=(.*)$/) { $tag = $1; }
  elsif (/^--out=(.*)$/) { $out = $1; }
  else {
    print STDERR "unknown option: $_\n" if (!/^--help$/);
    #usage(); # includes --help !
  }
} ;

my $text; my $test=0;
open(IN, "$file.html") ;
while (<IN>){
  next if !(/\<test\>/) && $test==0 ;
  $test=1; $text .= $_;

}
close IN;
my @u=extract_tagged ($text ,"<$tag>","</$tag>");
out("$out/$file",$u[0] ."\n");

sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || warn "peut pas créer $bloc";
  print OUT $text ; close OUT ;
}

