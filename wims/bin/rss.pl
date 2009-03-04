#!/usr/bin/perl
use HTTP::Date;

$wims_ref='http://127.0.0.1/wims';
$file='' ; 
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'}) ; 

while ($_ = shift (@ARGV))
{
  last if (!/^--/);
     if (/^--wims=(.*)$/) { $wims_ref  = $1; }
     elsif (/^--file=(.*)$/) { $file   = $1 ; }
     elsif (/^--out=(.*)$/) { $out     = $1 . "/" ; }
     elsif (/^--type=(.*)$/) { $modif     = $1 ; }
} ;
$wims_ref =~ s,/wims.cgi,, ; 
$head= "<\?xml version=\"1.0\" encoding=\"ISO-8859-1\"\?>
<rss version=\"2.0\">
    <channel>
        <title>WIMS</title>
        <link>$wims_ref</link>
        <description>NEWS</description>
        \n"
;

$tail="</channel></rss>"; 

open(IN, "$file.$modif") or die $file ;
my @lignes = <IN>;
my ($cnt, $used)= (1) ; 
foreach( reverse( @lignes ) ) {
  my @l=split(":", $_)  ;
  my $date= convdate($l[0]) ;
  my @ta=split(" ", $l[1]) ;
  next if !($l[1]) || ($used =~ /$l[1]/) || ($cnt > 100) ; 
  $cnt ++ ;
  $used .= " " . $l[1] ; 
  $text .=
"<item>
   <title>$l[1]</title>
   <link>$wims_ref/wims.cgi?module=$ta[0]</link>
   <guid isPermaLink=\"true\">$wims_ref/wims.cgi?module=$ta[0]</guid>
   <description>$ta[0] version $ta[1]</description>
  <pubDate>$date</pubDate>
</item>\n"
}
out("$out$modif.xml" , $head . $text . $tail) ;

sub convdate { my ($d)= @_ ;
     $d =~ s/(\d{4,4})(\d{2,2})(\d{2,2})/$1-$2-$3 03:00:00/ ;
     time2str(str2time($d)); 
}

sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || die $bloc ; 
  print OUT $text ; close OUT ; 
}
