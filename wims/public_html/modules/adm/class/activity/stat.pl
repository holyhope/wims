#!/usr/bin/perl

use Time::Local;

push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'}) ; 
while ($_ = shift (@ARGV))
{
  last if (!/^--/);
     if (/^--file=(.*)$/) { $OUT   = $1; } # fichier de sortie
     if (/^--sheet=(.*)$/) {$SHEET = $1; } # nombre de feuilles
} ;
#fichier à lire
$FILE = "/" . $_;
for my $sh (1..$SHEET) {
  $lastdate{$sh}='' ; 
  $score{$sh} = 0 ; 
}

$session=' ';
$nbsessions = 0 ; 
  #le fichier est récupéré ordonné par dates croissantes
open(IN, $FILE) ;
while(<IN>){ 
 #extraction de l'info de la ligne
 #20070914.23:52:03 6BA720BDC3  1  1 score 10  	82.238.218.220
 #next si ligne d'examen
 next if (/^E/);
 @_ = split(/ +/) ;
 $dattime=$_[0] ; 
 if ($_[4] eq 'score' || (!$lastdate{$_[2]}) ) {
  if (!($session eq $_[1])){ $nbsessions ++ ; $session = $_[1] ; } ;
  $dattime=~/([0-9]+)\.([0-9:]+)/ ; 
  ($date,$time) = ($1,$2);
  $date =~/([0-9][0-9][0-9][0-9])([0-9][0-9])([0-9][0-9])/;
  my ($annee,$mois,$jour)=($1,$2,$3) ;
  $date=converttime($time,$date);
  if(!$lastdate{$_[2]} && $_[4] eq 'new'){#on initialise s'il n'avait jamais fait cette feuille :
	   $lastdate{$_[2]}=$date;
	   $duree{$_[2]}= 0;
	   next ; 
   } else {
#on juge que s'il y a moins de 15mn entre deux dates consecutives, le bonhomme a travaille pendant ce temps
	    if ($date-$lastdate{$_[2]}<900){
	       $duree{$_[2]} +=  ($date-$lastdate{$_[2]}); 
	    } else { }
	      $lastdate{$_[2]}=$date;
  }
  if ($_[4] eq 'score') {; 
    $score{$_[2]} ++ ;
    $feuille{$_[2]} = 1 ; $exo{$_[2] . '.' . $_[3]} ++ ;#ne me sert à rien
  } ;  ##nombre de fois pour l'exo feuille.numero 
 } ;
}

my ($text,$score_global,$duree_globale,$nombresessions_globale)= (' ',0,0,0) ; 
for  my $sh (1..$SHEET) {
 $text .= $score{$sh} . ',' . converttime2($duree{$sh}) . ',' ;
 $score_global += $score{$sh} ; $duree_globale += $duree{$sh} ; 
}
#dernière connexion,nb_sessions,nb exos abordés total, nb exos par feuille, temps par feuille
print $dattime . ',' . $nbsessions 
      . ',' . $score_global . ',' . converttime2($duree_globale) 
      . "," . $text ;

sub converttime {
    my $heure=shift;
    my $date=shift;
    $heure =~/([0-9]+):([0-9]+):([0-9]+)/;
    $heure= 3600*$1+60*$2+$3;
    $date =~/([0-9][0-9][0-9][0-9])([0-9][0-9])([0-9][0-9])/;
    my $annee=$1;
    my $mois=$2;
    my $jour=$3;
    return timelocal(0,0,0,$jour,$mois - 1,$annee) + $heure;
    
}

sub converttime2 {
    $duree=shift;
    $secondes = $duree% 60;
    $duree = ($duree-$secondes)/ 60;
    $minutes = $duree% 60;
    $duree = ($duree-$minutes)/ 60;
    $heures = $duree;
    "$heures:$minutes:$secondes";
}