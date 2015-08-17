#!/usr/bin/perl
use Time::Local;
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'});
my ($day,$month,$year)=@ARGV;
my $date=timelocal(0,0,0,$day,$month-1,$year);
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime($date);
print $wday;
