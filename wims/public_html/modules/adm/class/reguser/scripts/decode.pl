#!/usr/bin/perl

use Encode;
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'}) ;
open (IN , $ARGV[0]) ;
 while (<IN>) {
   my $t=decode('utf-8',$_);
   print encode("iso-8859-1",$t)
 }
close(IN);