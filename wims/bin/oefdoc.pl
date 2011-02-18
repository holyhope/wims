#!/usr/bin/perl

use locale;
#use warnings;
#use strict;
##$/ = undef; # slurp
##lancer du répertoire scipts/help

my %name = (
  ) ; 
my $name = \%name;
$name->{'explanation'}{'fr'}="Explication" ; 
$name->{'example'}{'fr'}="Exemple" ;
$name->{'special'}{'fr'}="Méthodes spéciales<br>(énoncé)";
$name->{'syntax'}{'fr'}="Syntaxe";
$name->{'slib'}{'fr'}='SLIB';
$name->{'anstype'}{'fr'}='Types de réponses' ; 

$name->{'explanation'}{'en'}="Explanation" ; 
$name->{'example'}{'en'}="Example" ;
$name->{'special'}{'en'}="Special method<br>(statement)";
$name->{'syntax'}{'en'}="Syntax";
$name->{'slib'}{'en'}='SLIB';
$name->{'anstype'}{'en'}='Answer types' ;

$name->{'explanation'}{'cn'}="Explanation" ; 
$name->{'example'}{'cn'}="Example" ;
$name->{'special'}{'cn'}="Special method<br>(statement)";
$name->{'syntax'}{'cn'}="Syntax";
$name->{'slib'}{'cn'}='SLIB';
$name->{'anstype'}{'cn'}='Answer types' ;

$name->{'explanation'}{'nl'}="Explanation" ; 
$name->{'example'}{'nl'}="Example" ;
$name->{'special'}{'nl'}="Special method<br>(statement)";
$name->{'syntax'}{'nl'}="Syntax";
$name->{'slib'}{'nl'}='SLIB';
$name->{'anstype'}{'nl'}='Answer types' ; 

$name->{'explanation'}{'it'}="Spiegazione" ; 
$name->{'example'}{'it'}="Esempio" ;
$name->{'special'}{'it'}="Metodi speciali<br>(enunciato)";
$name->{'syntax'}{'it'}="Sintassi";
$name->{'slib'}{'it'}='SLIB';
$name->{'anstype'}{'it'}='Tipi di risposte' ; 

my $DOSSIER="public_html/scripts/js/editor/scripts_1/bd_js";
my $slibdir="public_html/scripts/slib/";
my $helpdir="public_html/scripts/help";

my @Lang=('en','fr','cn', 'nl','it') ;
#@Lang=('en') ; 
system(`mkdir -p $DOSSIER`) ;
my @table=('if', 'oefparm0', 'oefparm1', 'oefparm2', 'oefparm3', 'oefparm4', 'oefparm5','oefcommand') ; 

my %Command = (
  ) ; 
my $Command = \%Command ;
$Command->{'begin'}{'if'}= "  " ; 
$Command->{'end'}{'if'}= "  " ; 
$Command->{'begin'}{'oefparm0'}= '\\\\' ; 
$Command->{'end'}{'oefparm0'}= "\{  =  \}" ;
$Command->{'begin'}{'oefcommand'}= '\\\\' ; 
$Command->{'end'}{'oefcommand'}= "\{  \}" ;
##$Command->{'begin'}{'anstype'}='\\\\answer\{  \}\{  \}\{type=' ;
$Command->{'begin'}{'anstype'}='' ;
##$Command->{'end'}{'anstype'}='\}\{option=  \}\{ weight= \}\n' ;
$Command->{'end'}{'anstype'}='' ;
for my $tag ("oefparm4") {
   $Command->{'begin'}{$tag}= "" ; 
   $Command->{'end'}{$tag}= "\(  \)" ;
}
for my $tag ("oefparm2", "oefparm3") {
   $Command->{'begin'}{$tag}= " " ; 
   $Command->{'end'}{$tag}= " " ;
}
for my $tag ( "oefparm1") {
   $Command->{'begin'}{$tag}= "" ; 
   $Command->{'end'}{$tag}= "" ;
}

for my $tag ("oefparm5") {
   $Command->{'begin'}{$tag}= '\\\\' ;
   $Command->{'end'}{$tag}= "" ;
}

for my $tag ("slib") {
   $Command->{'begin'}{$tag}= "slib(" ; 
   $Command->{'end'}{$tag}= " )" ;
}

my @phtml=("expandlines", "imagefill", "help", "tabs2lines", "rename", "tooltip") ; 
for my $tag (@phtml) {
   $Command->{'begin'}{$tag}= "\\special\{" ; 
   $Command->{'end'}{$tag}= " \}" ;
}

##### generation
#for my $lang (@Lang) {print "oefdoc.pl $lang\n" ;  system(`mkdir -p $DOSSIER/$lang`) ;
 #for my $file (@table) { tableau ($file,$lang,3) ;} ;
 #phtml("$helpdir/$lang/special",$lang,"special",@phtml) ; 
 #slib($lang) ;
#}
### ne pas faire de double boucle ... ????
for my $lang (@Lang) { 
   print "oefdoc.pl $lang\n" ;  system(`mkdir -p $DOSSIER/$lang`) ;
   tableau('if',$lang) ; 
   tableau('oefparm0',$lang) ;
   tableau('oefparm1',$lang) ;
   tableau('oefparm2',$lang) ;
   tableau('oefparm3',$lang) ;
   tableau('oefparm4',$lang) ;
   tableau('oefparm5',$lang) ;
   tableau('oefcommand',$lang) ;
   phtml("$helpdir/$lang/special",$lang,"special",@phtml) ;
   anstype($lang) ; 
   slib($lang) ;
};

sub anstype { my ($lang)=@_ ;
 my %HASH = (
  ) ; 
 my %HELP = (
  ) ; 
 my $HELP = \%HELP ; 
 open (IN, "$helpdir/$lang/reply.phtml") ;
   while (<IN>) {my $line = $_; my @t=();
    next if ($line =~ /^\!set/) ;
    next if !($line) ;
    if ($line =~ /\\\n/) {
      my @L= split( ',', $line) ;
      my $t1 = $L[0] ; $t1=~ s/\|/,/ ;
      my @ta=split(',',$t1) ;
      if ($ta[1]) {@t=split(' ',$ta[1]) ; } else {@t=($L[0])};
      for my $tag (@t) { $HASH{$tag} = cleanup3($L[1] . ' ' . (($L[2]) ? $L[2]: '')); $HELP{$tag}=$ta[0] ;} 
     }
   }
 close IN ;
 my $text ='';
 my $Text = "var anstypename='$name->{'anstype'}{$lang}';\n" ;
   my $var=join ("$Command->{'end'}{'anstype'}\',\'$Command->{'begin'}{'anstype'}", sort keys(%HASH)) ;
   $Text .="var anstype = [ '$Command->{'begin'}{'anstype'}$var$Command->{'end'}{'anstype'}' ];\n" ;
   for my $tag (keys(%HASH)){
     $text .=begin_js("$Command->{'begin'}{'anstype'}$tag$Command->{'end'}{'anstype'}") 
           . title_js($tag,'title')
           . middle_js($HASH{$tag},'out',$lang)
           . end_js("<a target=\"wims_help\" href=\"wims.cgi?lang=$lang&module=adm%2Fcreatexo&modtoolhelp=yes&+special_parm=reply,$HELP{$tag}\">++>></a>") ;
   }
   $Text .= function_js($text,'anstype') ;
  out ("$DOSSIER/$lang/anstype" . "_bd\.js",$Text) ;
}
sub slib {my ($lang)= @_ ;
 my $Text = "var slibname='$name->{'slib'}{$lang}';\n" ;
 my @list_keyword=();
 my %HASH = (
  ) ; 
 my $HASH = \%HASH ;
for my $file (glob("$slibdir/*/*")) {
#for my $file (glob("$slibdir/function/integrate")) {
 $file =~s/$slibdir\///;
 my $text=''; my $tag='';
 open (IN, "$slibdir/$file"); 
 while (<IN>) {my $line=$_; 
    if  ($line=~/^ *!exit/) { last ;}
    if ($line=~ s/^ *slib_(\w+) *=//){
     $tag=$1;
     $line=cleanup($line) ;
     if ($tag=~/parms/) {
       $line=~s/\\//;
       $HASH->{nbparm}{$file}=$line;
     } else
     {
       $HASH->{$tag}{$file}=$line ;
     }
     } else {
       next if !($tag) ; 
       if ($tag=~/parms/) {
        chomp $line ;
        next if ($line) ; 
        my @parm=split(",", $line) ;
        if (($parm[1]) && ($parm[1] =~ s/\\//)) {
          $HASH->{$tag}{$file}.= cleanup3($parm[1]) . ",";
         }
         else
         {  $HASH->{$tag}{$file}= (($HASH->{$tag}{$file})? $HASH->{$tag}{$file}:' ') . (($parm[1]) ? cleanup3($parm[1]):'') ;
         }
       # $HASH->{$tag}{$file} .= "\[$parm[0]\]" if ($parm[0]);
       }
       else {
         $HASH->{$tag}{$file} .= cleanup($line);
         $tag='' if !($line=~/\\$/) ; 
       }
     }
   }
 close IN;
  push @list_keyword, $file if ($HASH->{'title'}{$file});
 $tag='';
 }
 my $var=join ("$Command->{'end'}{'slib'}\',\'$Command->{'begin'}{'slib'}", @list_keyword) ;
 $Text .="var slib = [ '$Command->{'begin'}{'slib'}$var$Command->{'end'}{'slib'}' ];\n" ; 
 my $text='' ;
 for my $file (@list_keyword) {
  next if !($HASH->{'title'}{$file}) ;
  my @examples=split("\\\\\\\\",$HASH->{'example'}{$file}) if ($HASH->{'example'}{$file});
  my $example='';
  for my $ex (@examples) {
    next if !($ex) ;
    $example .="<div class=\"title\">$name->{'example'}{$lang}</div><code><font color=\"red\">slib($file</font> $ex <font color=\"red\">)</font></code>" ;
  }
  $text.=begin_js("$Command->{'begin'}{'slib'}$file$Command->{'end'}{'slib'}") 
           . title_js($HASH->{'title'}{$file},'title')
           . syntax_js("<font color=\"red\">slib($file</font> " . ($HASH->{'parms'}{$file}  ? $HASH->{'parms'}{$file} : '') . " <font color=\"red\">)</font>",$lang)
           . middle_js($HASH->{'out'}{$file},'out',$lang)
           . middle1_js (cleanup($example),'',$lang)
           . end_js("<a target=\"wims_help\" href=\"wims.cgi?lang=$lang&module=adm%2Fcreatexo&modtoolhelp=yes&special_parm=slib&+slibdet=$file#slib\">++>></a>") ;
 $text =cleanup2($text) ; 
 }
 $Text .= function_js($text,'slib') ;
  out ("$DOSSIER/$lang/slib" . "_bd\.js",$Text) ;
}
##special methode
sub phtml {my ($dir,$lang,$f,@file)=@_ ;
 my $cities=$f;
 my %HASH = (
  example       => {},
  signification => {},
  syntaxe => {},
  ) ; 
 my $HASH = \%HASH ; 
 my $text='';
 my $tag='';
 my $Text="var specialname= '$name->{'special'}{$lang}';\n";
 for my $meth (@file) {
    open (IN, "$dir/$meth.phtml"); 
    while (<IN>) {my $line=$_;
    next if !($line) ;
    if ($line =~ /^:/) {
    chomp $line;
       $tag=$line; $tag=~ s/://;
    } 
    else
    {
     $HASH->{$tag}{$meth} .= cleanup($line) . "\\n" ;
    }
  }
}
 my $var=join (" }\', \'\\\\special{", @phtml) ;
 ### cas particulier
 my $meth='embed';
 my $embd='\\\\embed{r  }' ;
   open (IN, "$helpdir/$lang/embedans.phtml"); 
    while (<IN>) {my $line=$_;
    next if !($line) ;
    if ($line =~ /^:/) {
    chomp $line;
       $tag=$line; $tag=~ s/://;
    } 
    else
    {
     $HASH->{$tag}{$meth} .= cleanup($line) . "\\n" ;
    }
  }
  close IN ;
  $Text .= "var special= [ '$embd', '\\\\special{$var }'];\n" ;
  $text = begin_js("$embd") 
        . syntax_js("\\\\embed{r i, option }",$lang)
        . (($HASH->{'signification'}{$meth}) ? middle_js($HASH->{'signification'}{$meth},'title',$lang) : '')
        . (($HASH->{'example'}{$meth}) ? middle1_js ($HASH->{'example'}{$meth},'title',$lang) : '')
        . end_js("") ;
  ## fin cas particulier embed
  for my $meth (@phtml) {
   $text .= begin_js("\\\\special{$meth }")
           . syntax_js("\\\\special{$meth }",$lang) 
           . (($HASH->{'signification'}{$meth}) ? middle_js($HASH->{'signification'}{$meth},'title',$lang ) : '')
           . (($HASH->{'example'}{$meth}) ? middle1_js ($HASH->{'example'}{$meth},'title',$lang) : '')
           . end_js("") ;
    
  }
  $Text .= function_js($text,'special') ;

  out ("$DOSSIER/$lang/$f" . "_bd\.js",$Text) ;

}
##file : nom du fichier, n nombre de lignes dans chaque record
sub tableau { my ($file, $lang) = @_ ;
### mettre $file à la place ensuite
  my $file1="$helpdir/$lang/$file";
  my $cities=$file ;
  if ($file =~ /if/){ $cities .= 'f' } ; 
  my @list_keyword;
  my $text='';
##bug s'il n'y a pas de documentation
  open (IN, $file1);
  my $cnt=0 ;my $nl;
  my $Text = '' ; 
  while (<IN>) { my $line=$_;
   chomp $line ;
   next if !($line) ; 
   if ($line =~ s /^://) {
     $cnt ++ ;
     if ($cnt == 1 ) { $Text = "var $cities" . "name= '$line';\n ";  }
     next if $cnt < 3 ;
     $line =~ s/:// ;
     if($text) { $text .= end_js("") ;}
       if ($text) {$text .= begin_js($Command->{'begin'}{$file} . $line . $Command->{'end'}{$file}) ;}
        else
       { $text = begin_js($Command->{'begin'}{$file} . $line . $Command->{'end'}{$file}) ; };
     push @list_keyword, $line;
     $nl=0;
     }
     else  {
       next if $cnt<3 ; if ($line =~ /^(\d)/) { my $arg=$1 ; next }  
       $nl ++ ;
       $line = cleanup($line); if ($line =~ /help=/) { $line = '' ;}
       if ($nl==1 && !($file=~/oefcommand/)){ 
         if ($line) { $text .= syntax_js($line,$lang) ; }
        }
        else {
         if ($line) { $text .= middle_js($line,1,$lang) ; }
	   }
	 }
   }
  close IN ;
  	 $text .= end_js("") ;
  my $var=join ("$Command->{'end'}{$file}\', \'$Command->{'begin'}{$file}", @list_keyword) ;
  $Text .="var $cities= [ \'$Command->{'begin'}{$file}$var$Command->{'end'}{$file}\' ];\n" 
  . function_js($text,$cities) ;
  out ("$DOSSIER/$lang/$cities" . "_bd\.js",$Text) ;
}

sub begin_js {my ($t)= @_ ;
"case \'$t\' \:\nchaine_aide="
}
sub syntax_js {my ($line,$lang)=@_ ;
 "\'<div class=\"syntax\"><div class=\"title\">$name->{'syntax'}{$lang}</div><code>$line</code></div>\'+\n"
}
sub middle_js {my ($line,$tag,$lang)=@_ ;
 if ($tag) { $line="<div class=\"title\">$name->{'explanation'}{$lang}</div>$line" }
 "\'<div class=\"explication\">$line</div>\'+\n";
}

sub middle1_js {my ($line,$tag,$lang)=@_ ;
 if ($tag) { $line="<div class=\"title\">$name->{'example'}{$lang}</div>$line" }
 "\'<div class=\"exemple\">$line</div>\'+\n";
}

sub title_js {my ($line,$tag)=@_ ;
 "\'<div class=\"title\">$line</div>\'+\n";
}

sub end_js {my ($text)=@_ ;
  "\'$text\' ; return chaine_aide;
	   break;
	////******************** \n
	"
}
sub function_js {my ($text,$tag)=@_ ;
 "function $tag" . "fun(instruction){
    switch(instruction)
	{
	$text
	}
}"
}

sub cleanup { my ($txt)=@_ ;
  return $txt if !($txt) ;
  $txt=~ s/\\\b/&#92;/g ;
  $txt=~ s/\\\(/&#92;(/g ;
  $txt=~ s/\\\)/&#92;)/g ;
  $txt=~ s,\\,\\\\,g ; 
  $txt=~ s/'/\\'/g ;
  $txt=~ s/\n/ /g ;
  return $txt ; 
}
sub cleanup2 {my ($txt)=@_ ;
  $txt=~ s/\\\\ / /g if ($txt) ;
  return $txt;
}
sub cleanup3 {my ($txt)=@_ ;
  $txt=~ s/'/\\'/g if ($txt);
  return $txt;
}


sub htmltex { my ($TEXT) = @_ ;
$TEXT =~ s/<tt>\\/\\ttb{/g;
$TEXT =~ s/_/\\_/g;
$TEXT =~ s/\^/\\^{}/g;
$TEXT =~ s/\&/\\\&/g;
$TEXT =~ s/<(tt)>/\\text$1\{/g;
$TEXT =~ s/<(em|i)>/\\textit\{/g;
$TEXT =~ s/<b>/\\textbf\{/g;
$TEXT =~ s'</(b|tt|em|i)>'}'g;
$TEXT =~ s/<br>/\\par /g;
$TEXT =~ s/<p>/\\par /g;
$TEXT =~ s/<\/p>/\\par /g;
$TEXT =~ s/<ul>/\\begin{itemize}\n /g;
$TEXT =~ s/<\/ul>/\\end{itemize}\n /g;
$TEXT =~ s/<ol>/\\begin{enumerate}\n /g;
$TEXT =~ s/<\/ol>/\\end{enumerate}\n /g;
$TEXT =~ s/<li>/\\item /g;
$TEXT =~ s/<\/li>/\n /g;
$TEXT =~ s/<\/center>/\\end{center}\n /g;
$TEXT =~ s/<center>/\\begin{center}\n /g;
$TEXT =~ s/<\/center>/\n /g;
$TEXT =~ s/<center>/\n /g;
$TEXT =~ s/<table[^>]*>/\\begin{table}\\begin{tabular}{*{1}{p{30mm}}|*{1}{p{50mm}|}|*{1}{p{50mm}|}}\\hline /g;
$TEXT =~ s/<\/table>/\\\\ \\hline \\end{tabular} \\end{table}/g;
$TEXT =~ s/\$table_tr/\\\\\\hline /g;
$TEXT =~ s/\$table_hdtr/\\\\ \\hline/g;
$TEXT =~ s/\$table_header/\\begin{table}\\begin{tabular}{*{1}{p{30mm}}|*{1}{p{50mm}|}|*{1}{p{50mm}|}}\\hline/g ; 
$TEXT =~ s/\$table_end/\\end{tabular}\\end{table}/g;
#$TEXT =~ s/<caption>/\\caption\{ /g;
#$TEXT =~ s/<\/caption>/\}\n /g;
$TEXT =~ s/<tr[^>]*>/\\\\/g;
$TEXT =~ s/<\/tr>/\\\\/g;
$TEXT =~ s/<(td|th) colspan=(\d)( nowrap)?>/\\multicolumn{$2}{|c|}{/g;
$TEXT =~ s/<\/(td|th)>/&/g;
$TEXT =~ s/<(td|th)[^>]*>/&/g;
$TEXT =~ s/&&/&/g;
$TEXT =~ s/\_/_/g;
$TEXT =~ s/&amp;/\\&/g;
$TEXT =~ s'\\\\&'\\\\'g;
$TEXT =~ s/&nbsp;/ /g;
$TEXT =~ s/&eacute;/é/g;
$TEXT =~ s/&egrave;/è/g;
$TEXT =~ s/&agrave;/à/g;
$TEXT =~ s/&ecirc;/ê/g;
$TEXT =~ s/&lt;/</g;
$TEXT =~ s/<(H|h)3>/\\subsection{/g;
$TEXT =~ s/<\/(H|h)3>/}/g;
$TEXT =~ s/<(H|h)4>/\\subsubsection{/g;
$TEXT =~ s/<\/(H|h)4>/}/g;
$TEXT =~ s/<(H|h)2>/\\section{/g;
$TEXT =~ s/<\/(H|h)2>/}/g;
$TEXT =~ s/&gt;/>/g;
$TEXT =~ s/\#//g;
$TEXT =~ s/<hr>/\\hrule/g;
$TEXT =~ s/<pre>/\\begin{verbatim}/g;
$TEXT =~ s/<\/pre>/\\end{verbatim}/g;
$TEXT =~ s/\n{3,}/\n\n/g;
$TEXT =~ s/<a[^>]+>([^<]+)<\/a>/\\url{$1}/g;

$TEXT ; 
}

sub out { my ($bloc, $text) = @_ ;
  open  (OUT, ">$bloc") || die "peut pas créer $bloc"; 
  print OUT "<!-- Automatically generated by bin/oefdoc.pl -->\n" . $text ; close OUT ; 
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
