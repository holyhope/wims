#!/usr/bin/perl
use strict; use warnings;

use Time::Local;
my ($OUT, $SHEET);
my $SH='';my $OPTION='';
my $LIMIT='9';
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'});
while ($_ = shift (@ARGV))
{
  last if (!/^--/);
     if (/^--file=(.*)$/) { $OUT   = $1; } # fichier de sortie
     if (/^--sheet=(.*)$/) {$SHEET = $1; } # nombre de feuilles
     if (/^--option=(.*):(.*)$/) {$OPTION = $1; $SH=$2} # option exobyday
     if (/^--limit=(\d+)$/) {$LIMIT=$1} # limite de notes
};
#fichier à lire
#my $FILE = "/" . $_;
my $FILE = $_;

my $SH0=$SH;
$SH =~ s/,/|/g;
my (%lastdate, %score, %duree, $dattime);
my (%exobyday,%scorebyday, %goodbyday)=((),(),());
my (%exobyday1, %scorebyday1, %goodbyday1)=((),(),());
my (%exobydaysh, %scorebydaysh, %goodbydaysh)=((),(),());
my %seconds=();
for my $sh (1..$SHEET) {
   $lastdate{$sh}='';
   $score{$sh} = 0;
}
my ($session,$nbsessions)=(' ',0);
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
  if (!($session eq $_[1])){ $nbsessions ++; $session=$_[1]; };
  $dattime=~/([0-9]+)\.([0-9:]+)/;
  my ($date, $time) = ($1,$2);
  $date =~/([0-9][0-9][0-9][0-9])([0-9][0-9])([0-9][0-9])/;
  $seconds{$date}=timelocal(0,0,0,$3,$2-1,$1);
  if (($_[2]=~ /$SH/ || !($SH)) && ($_[4] eq 'score')) {
    $exobyday{$date} ++ ;
    $exobydaysh{$_[2]}->{$date} ++ ;
    if ($_[5] >= $LIMIT){
      $scorebyday{$date} ++ ;
      $goodbyday{$date} .= (($goodbyday{$date})? ',':'') . $exobyday{$date};
      $scorebydaysh{$_[2]}->{$date} ++;
      $goodbydaysh{$_[2]}->{$date} .= (($goodbydaysh{$_[2]}{$date})? ',':'') . $exobydaysh{$_[2]}->{$date};
    }
## n'a de sens que s'il y a une seule sheet
    if ($_[2]=~ /$SH0/){
      $exobyday1{$_[3]}->{$date} ++;
      if ($_[5] >= $LIMIT){
        $scorebyday1{$_[3]}->{$date} ++;
        $goodbyday1{$_[3]}->{$date} .= (($goodbyday1{$_[3]}{$date})? ',':'') . $exobyday1{$_[3]}->{$date};
      }
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
        if ($lastdate{$_[2]} && $date-$lastdate{$_[2]}<900){
           $duree{$_[2]} += ($date-$lastdate{$_[2]});
        } else { }
          $lastdate{$_[2]}=$date;
  }
  if ($_[4] eq 'score') {;
    $score{$_[2]} ++;
  };
 };
}

my ($text,$score_global,$duree_globale,$nombresessions_globale)= (' ',0,0,0);
for my $sh (1..$SHEET) {
 $text .= $score{$sh} . ',' . converttime2($duree{$sh}) . ',';
 $score_global += $score{$sh}; if ($duree{$sh}) { $duree_globale += $duree{$sh}};
}
#dernière connexion,nb_sessions,nb exos abordés total, nb exos par feuille, temps par feuille
exit if !($dattime);

print $dattime . ',' . $nbsessions  . ',' . $score_global . ','
   . converttime2($duree_globale) . ',' . $text;

if ($OPTION eq 'exobyday'){
for my $date (sort keys %exobyday ) {
   if (!$exobyday{$date}) {$exobyday{$date}=0;}
   if (!$scorebyday{$date}) {$scorebyday{$date}=0;}
   if (!$goodbyday{$date}) {$goodbyday{$date}='';}
}

my ($xcoord, $ycoord, $zcoord, $good, $tmp, $day, $init, $t, $wday)=('','','','','','','','') ;
for my $date ( sort keys %exobyday ) {
  if ($xcoord) {$tmp=',' ;} else {
   $init=$seconds{$date} ;
   my @wday = localtime($date); $wday=$wday[6]}
  $xcoord .= "$tmp$date";
  $t = ($seconds{$date}-$init) % 86400; $t=$wday+($seconds{$date}-$init-$t)/ 86400;
  $day .= $tmp . $t;
  $ycoord .= $tmp . $exobyday{$date};
  $zcoord .= $tmp . $scorebyday{$date};
  $good .= "$tmp" . '[' . $goodbyday{$date} .']';
}
###liste de dates, liste du nombre d'exos faits à cette date, liste des nombres de reussite,
###liste des listes de positions des reussites

print "\n[$xcoord],[$day],[$ycoord],[$zcoord],[$good]";

if (!($SH0=~ /,/)) {
 for my $ex (sort {$a <=> $b} keys %exobyday1){
   my ($xcoord,$ycoord,$zcoord,$good,$tmp)=('','','','','');
   for my $date ( sort keys %exobyday ) {
      if (!$exobyday1{$ex}->{$date}) { $exobyday1{$ex}->{$date}=0;}
      if (!$scorebyday1{$ex}->{$date}) {$scorebyday1{$ex}->{$date} = 0;}
      if (!$goodbyday1{$ex}->{$date}) { $goodbyday1{$ex}->{$date}='';}
      if ($xcoord) {$tmp=',' };
      $xcoord .= "$tmp$date";
      $ycoord .= $tmp . $exobyday1{$ex}->{$date};
      $zcoord .= $tmp . $scorebyday1{$ex}->{$date};
      $good .= $tmp . '[' . $goodbyday1{$ex}->{$date} . ']';
 }
###pour les exercices d'une feuille
###numero exo, liste de dates, liste du nombre d'exos faits à cette date, liste des nombres de reussite,
###liste des listes de positions des reussites
   print "\n$ex,[$xcoord],[$ycoord],[$zcoord],[$good]";
  }
 }
 else {
  for my $sh (sort {$a <=> $b} keys %exobydaysh){
    my ($xcoord,$ycoord,$zcoord,$good,$tmp)=('','','','','');
    for my $date ( sort ( keys %exobyday) ) {
      if ($xcoord) {$tmp=',' };
      $xcoord .= "$tmp$date";
      if (!$exobydaysh{$sh}->{$date}) { $exobydaysh{$sh}->{$date}=0;}
      if (!$scorebydaysh{$sh}->{$date}) {$scorebydaysh{$sh}->{$date} = 0;}
      if (!$goodbydaysh{$sh}->{$date}) { $goodbydaysh{$sh}->{$date}='';}
      $ycoord .= $tmp . $exobydaysh{$sh}->{$date};
      $zcoord .= $tmp . $scorebydaysh{$sh}->{$date};
      $good .= $tmp . '[' . $goodbydaysh{$sh}->{$date} . ']';
   }
###pour les feuilles d'une liste de feuilles
###numero feuille, liste de dates, liste du nombre d'exos faits à cette date, liste des nombres de reussite,
###liste des listes de positions des reussites
   print "\n$sh,[$xcoord],[$ycoord],[$zcoord],[$good]";
  }
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
    return "0:0:0" if !($duree);
    my $secondes = $duree% 60;
    $duree = ($duree-$secondes)/ 60;
    my $minutes = $duree% 60;
    $duree = ($duree-$minutes)/ 60;
    my $heures = $duree;
    "$heures:$minutes:$secondes";
}
