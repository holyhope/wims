#!/usr/bin/perl
##script to generate some index files from tags of index.tags.xml for
## shtooka packages
use locale;
use warnings;
my @dirs=() ;
my $lang='' ;
my @SPECIAL=('');
my $INDEX_XML_FILE='index.xml' ;
my $PREFIX;
my @EXTRA=(
'swac_tech_qlt',
'swac_tech_date',
'swac_tech_soft',
'description',
'swac_coll_authors',
'swac_coll_copyright',
'swac_coll_desc',
'swac_coll_license',
'swac_coll_name',
'swac_coll_org',
'swac_coll_section',
'swac_lang',
'swac_pron_speed',
'swac_speak_birth_year',
'swac_speak_gender',
'swac_speak_lang_country',
'swac_speak_lang',
'swac_speak_lang_region',
'swac_speak_liv_country',
'swac_speak_liv_town',
'swac_speak_name',
'copyright',
'swac_coll_url',
'genre',
'license',
'title',
) ;

my $Extra=join('|', @EXTRA) ; 
my @CHAMP=(
'swac_alphaidx',
'swac_baseform',
'swac_form_name', 
'swac_coll',
);

#my $MODE='utf8' ; 
my ($MODE,$MODEOUT) = ('', ''); 
while ($_ = shift(@ARGV)) {
  last if (/^$/);
  if    (/^--dir=(.*)$/)     { push @dirs, $1 ; }
  elsif (/^--special=(.*)$/) { push @SPECIAL, $1; }
  elsif (/^--file=(.*)$/)    { $INDEX_XML_FILE = $1; }
  elsif (/^--lang=(.*)$/)    { $lang = $1; }
  elsif (/^--mode=(.*)$/)    { $MODE = $1; }
  elsif (/^--modeout=(.*)$/) { $MODEOUT = $1; }
  elsif (/^--prefix=(.*)$/)  { $PREFIX = $1; }
  else { 
    print STDERR "unknown option: $_\n" if (!/^--help$/);
    usage(); # includes --help !
  }
}
my %hash=('swac_alphaidx' => 'swac_baseform',
'swac_text' => 'swac_baseform',) ; 

my %ALLTAGS = ('swac_text' => {}) ; 
push @dirs, glob("$lang-*") if ($lang) ;

for (@dirs) { ConsListe("$_/$INDEX_XML_FILE", \%ALLTAGS, $_); }
if ($PREFIX) { ConsListe("$INDEX_XML_FILE", \%ALLTAGS, $PREFIX); }

my @KEYS=(keys %{$ALLTAGS{swac_text}}) ; 

##On complète
for $field (keys %hash) { $field2=$hash{$field} ; 
   for my $k (sort @KEYS) {
    if( !($ALLTAGS{$field2}{$k}) ) {
      if( ($ALLTAGS{$field}{$k})) { 
        $ALLTAGS{$field2}{$k}= traite_francais( $ALLTAGS{$field}{$k}) ;
      }
    }
  }
}
sub traite_francais { my ($a) = @_ ;
   if ($a =~ /(\w+)\s+(s')/) { $a = "s'". $1 ; } ;
   if ($a =~ /(\w+)\s+(se)/) { $a = "se ". $1 } ;
   $a =~ s/\best-à-dire/c'est-à-dire/ ; 
   $a =~ s /plaire\|\(conversation\)/s'il vous plaît/;
   $a =~ s/\((\w+)\)// ;
   $a =~ s /^|//;
   $a}
#### problème avec s'il te pl
out(":" . join( "\n:",  @KEYS), canon2("")) ; 

@SPECIAL= (keys %ALLTAGS)  if ($#SPECIAL==0) ; 
for my $special (@SPECIAL) {
   out(indexkey($special), canon2($special)) if (indexkey($special)) && !($special =~ /($Extra)/);  
} 

## permet de passer du fichier index.tags.txt à un fichier en tableau 

#out(tableau(@CHAMP), 'ALL') ; 
out(tags(@CHAMP), canon('swac_tags')) ; 
sub tableau {  my @list = @_ ;
my $TEXT = "[TAG]" ; $cc=1;
for my $b (@list) {
   $TEXT .= "$b=\\\&$cc\n" ; 
   $cc ++
}

$TEXT .= "\n\n[LIST]\n" ; 
  for my $k (sort @KEYS) {
    $TEXT .= $ALLTAGS{swac_text}{$k} ;
    for my $b (@list) {
           $TEXT .= ';' . $ALLTAGS{$b}{$k} ;
      }   
      $TEXT .=  ";$k\n"
  }
  $TEXT
 }
  sub tags {  my @list = @_ ;
  my $TEXT = "" ;
  for my $k (sort @KEYS) {
    $TEXT .= $k . ":" 
          . 'swac_text' . '="' . $ALLTAGS{'swac_text'}{$k}. '"' . "\\\n"; 
    for my $b (@list) {
           $TEXT .= $b . '="' .  $ALLTAGS{$b}{$k} . '"' . "\\\n" if ($ALLTAGS{$b}{$k}) ;
      }
     $TEXT .= "\n" ;
  }
  $TEXT =~ s/\\\n\n/\n/g ;
  $TEXT ; 
 }
 

sub indexkey { my ($swac)=@_ ; 
 my %HA = %{$ALLTAGS{$swac}} ; 
 %h = ();
 while (my ($key, $val) = each %HA)
   { $v = $val ; $v=~ s/\|/,/g ; 
    for my $val2 ( split(',',$v) ) {
     $h{$val2} .= (($h{$val2}) ? "," : "") . $key if  $HA{$key} =~ /$val/  ;
   } 
   }
 my $text = "";
 for my $a (keys %h){ 
     $text .= $a . ":" . $h{$a} . "\n" ;
 }
 $text ;
}
 
my (%errmsg); # empèche le ré-affichage d'un même warning.
$SIG{__WARN__} = sub { my ($x) = @_;
  return if $errmsg{$x};
  $errmsg{$x} = 1;
  print STDERR "### $x";
};

#### à modifier ou partir d'un fichier sans global !

sub ConsListe { my ($file, $ref, $dir) = @_;
  my ($id) = '';
  open (IN, $file) || die "$file n'existe pas";
#  print STDERR "... lecture de $file\n";
  ### le lit en utf8
  if ($MODE eq 'utf8') {binmode IN ,":utf8";}
  while(<IN>) {
    next if (/^#/ || /^\s*$/); # vire commmentaires + lignes vides
    next if (/<\/file\>/) ;
    s/<tag\s*//g;
    s/\s*\/\>//g;
    if (/<file path=\"(.*)\"/) { $id = $dir . '/' . $1 ; }
    if (/(\w+)\s*=\s*\"?(.*?)\"?\s*$/) {
      next if (!$id);
      my ($r, $field) = ($2,$1);
      $field = canonify($field) ;
      next if ($field =~ /(?:$Extra|path)/) ; 
      $r = Traite($r) ;
      $ref->{$field}->{$id} = $r;
    }
  }
  close(IN);
}

sub Traite { my ($record) = @_;
  $record =~ s/œ/oe/g;
  $record =~ s/\x{153}/oe/g; 
  $record =~ tr/‘’ –/`' :/;
  $record =~ s/\s+$//;
  $record =~ s/ {2,}/ /;
  $record ;
}

sub canon { my ($special)=@_ ; 
  $special = 'swac' . $special if !($special=~ /swac/) ;
  $special =~  s/^(swac)/$lang/ if ($lang) ;
  $special =~  s/swac/sw/ ;
  $special =~ s/ //g; 
  $special ;
}

sub canon2 { my ($special)=@_ ; 
  $special=canon($special) ;
  $special . '_keys' ; 
}

sub canonify { my ($special)=@_ ; 
  $special =~ tr /A-Z/a-z/ ; 
  $special ; 
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}

sub out { my ($text, $file) = @_ ; 
  open( OUT, ">$file") ; 
  ## fichier ouvert en utf8 mais il y a toujours les problèmes d'encodage
  if ($MODEOUT eq 'utf8') {binmode OUT ,":utf8";} else {binmode OUT ,":encoding(iso-8859-1)"};
  print OUT $text ;
  close OUT ; 
}

sub usage {
  print STDERR << "EOT"
swac.pl crée les fichiers dont j'ai besoin pour mon utilisation dans wims : 
  - un fichier SWAC_keys contenant les adresses des fichiers audio :base_swac/nom
  - des fichiers utilisables par "lookup" ; on peut en créer un par tags : 
   ils sont de la forme 
    " texte_du_tag_demande:adresse_audio1,adresse_audio2, ..."
    le texte_du_tag a été un peu normalisé en enlevant les espaces en trop.
    
swac.pl [ --dir=]  [ --special=] [ --file= ] [ --mode=]
  --dir= : les dossiers dans lesquels on va chercher le fichier
  --file= le nom du fichier  (le même pour tous), par défaut index.tags.txt
  --special= les index que l'on désire sortir : par défaut 
    tous ceux qui ne sont pas communs, sauf
    SWAC_TECH_QLT|SWAC_TECH_DATE|SWAC_TECH_SOFT|DESCRIPTION
    --mode= utf8 ou rien pour l'instant
EOT
;
  exit 1;
}

