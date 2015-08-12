#!/usr/bin/perl
#use strict;

use Time::Local;
my ($OUT, $SHEET, $OPTION, $SH);
my $limit='10';
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'});
while ($_ = shift (@ARGV))
{
  last if (!/^--/);
     if (/^--file=(.*)$/) { $OUT   = $1; } # fichier de sortie
     if (/^--sheet=(.*)$/) {$SHEET = $1; } # nombre de feuilles
     if (/^--option=(.*):(.*)$/) {$OPTION = $1; $SH=$2} # option exobyday
};
#fichier à lire
my $FILE = "/" . $_;
my $FILE = $_;
$SH =~ s/,/|/g;
my (%lastdate, %score, %duree, $dattime);
my %exobyday=();
my %scorebyday=();
my %goodbyday=();
my %exobyday0=();
my %scorebyday0=();
my %goodbyday0=();

for my $sh (1..$SHEET) {
   $lastdate{$sh}='';
   $score{$sh} = 0;
}
my $session=' ';
my $nbsessions = 0;
  #le fichier est récupéré ordonné par dates croissantes
open(IN, $FILE);
while(<IN>){
 #extraction de l'info de la ligne
 #20070914.23:52:03 6BA720BDC3  1  1 score 10  	82.238.218.220
 #next si ligne d'examen
 next if (/^E/);
 @_ = split(/ +/);
 $dattime=$_[0];
 if ($_[4] eq 'score' || (!$lastdate{$_[2]}) ) {
  if (!($session eq $_[1])){ $nbsessions ++; $session = $_[1]; };
  $dattime=~/([0-9]+)\.([0-9:]+)/;
  my ($date, $time) = ($1,$2);
  ##$exobyday{$date}=0 if !($exobyday{$date});
  $date =~/([0-9][0-9][0-9][0-9])([0-9][0-9])([0-9][0-9])/;
  if (($_[2]=~ /$SH/ || !($SH)) && ($_[4] eq 'score')) {
    $exobyday{$date} ++ ;
    $scorebyday{$date} ++ if $_[5] >= $limit;
    $goodbyday{$date} .= $exobyday{$date} . ',' if $_[5] >= $limit;
## n'a de sens que s'il y a une seule sheet
    if ($_[2]=~ /$SH/){
      $exobyday0{$_[3]}->{$date} ++;
      $scorebyday0{$_[3]}->{$date} ++ if $_[5] >= $limit;
      $goodbyday0{$_[3]}->{$date} .= $exobyday0{$_[3]}->{$date} . ',' if $_[5] >= $limit;
    }
  }
  my ($annee, $mois, $jour)=($1,$2,$3);
  $date=converttime($time,$date);

  if(!$lastdate{$_[2]} && $_[4] eq 'new'){#on initialise s'il n'avait jamais fait cette feuille :
      $lastdate{$_[2]}=$date;
      $duree{$_[2]}= 0;
      next;
   } else {
#on juge que s'il y a moins de 15mn entre deux dates consecutives, le bonhomme a travaille pendant ce temps
        if ($date-$lastdate{$_[2]}<900){
           $duree{$_[2]} += ($date-$lastdate{$_[2]});
        } else { }
          $lastdate{$_[2]}=$date;
  }
  if ($_[4] eq 'score') {;
    $score{$_[2]} ++;
   ## $feuille{$_[2]} = 1; $exo{$_[2] . '.' . $_[3]} ++;#ne me sert à rien
  };  ##nombre de fois pour l'exo feuille.numero
 };
}

my ($text,$score_global,$duree_globale,$nombresessions_globale)= (' ',0,0,0);
for my $sh (1..$SHEET) {
 $text .= $score{$sh} . ',' . converttime2($duree{$sh}) . ',';
 $score_global += $score{$sh}; $duree_globale += $duree{$sh};
}
#dernière connexion,nb_sessions,nb exos abordés total, nb exos par feuille, temps par feuille
print $dattime . ',' . $nbsessions
      . ',' . $score_global . ',' . converttime2($duree_globale)
      . "," . $text;

if ($OPTION eq 'exobyday'){
my ($xcoord, $ycoord, $zcoord, $tmp) ;
for my $date ( sort keys %exobyday ) {
  my $tmp=',' if ($xcoord);
  $xcoord .= "$tmp$date";
  $ycoord .= "$tmp" . $exobyday{$date};
  $zcoord .= "$tmp" . $scorebyday{$date};
  $good .= "$tmp" . "[" . $goodbyday{$date} ."]" ;
  }
  print "\n[$xcoord],[$ycoord],[$zcoord],[$good]";
  $tmp='';
}

if ($SH=~/\d+\b/) {
 for my $ex (sort keys %exobyday0){
  my ($ycoord,$zcoord,$good,$xcoord)='';
   for my $date ( sort keys %exobyday ) {
      $xcoord .= "$tmp$date" .',';
      $ycoord .= $exobyday0{$ex}{$date} . ',';
      $zcoord .= $scorebyday0{$ex}{$date} . ',';
      $good .= "[" . $goodbyday0{$ex}{$date} ."]," ;
   }
   print  "\n$ex,[$xcoord],[$ycoord],[$zcoord],[$good]";
  }
}
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
    my $duree=shift;
    my $secondes = $duree% 60;
    $duree = ($duree-$secondes)/ 60;
    my $minutes = $duree% 60;
    $duree = ($duree-$minutes)/ 60;
    my $heures = $duree;
    "$heures:$minutes:$secondes";
}
