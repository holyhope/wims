#!/bin/sh
exec /usr/bin/perl  <<'EOF'
use Time::Local;
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'});
my ($option)=shift @ARGV;
if ($option==1) {
 my ($day,$month,$year)=@ARGV;
 print timelocal(0,0,0,$day,$month-1,$year);
} else
{
  my ($date)=@ARGV;
  ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime($date);
  if ($mday <10) { $mday="0" . $mday };
  $mon=$mon+1;
  if($mon<10) {$mon="0" . $mon};
  print $mday . " " . $mon . " " . eval($year+1900) . " " . $wday . " " . $yday . " " . $isdst
}

EOF
