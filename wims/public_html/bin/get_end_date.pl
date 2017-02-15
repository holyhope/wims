#!/bin/sh

# INPUT : $duration,$date_format
# returns the date it will be in $duration seconds, formated as $date_format
exec perl <<'EOF'
use strict;
use warnings;
use Time::Piece;

my ($duration,$date_format)=(0,"%Y-%m-%d - %T");

if($ENV{'wims_exec_parm'}){
  my @params = split(',', $ENV{'wims_exec_parm'});
  $duration=$params[0];
  if($#params>0){$date_format=$params[1];}
}

my $Start = localtime;
my $End = $Start + $duration;
print $End->strftime($date_format)."\n";

EOF
