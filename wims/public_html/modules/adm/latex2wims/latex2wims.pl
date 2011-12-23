#!/usr/bin/perl

use strict "vars";
use strict "subs";
use locale;
use warnings;
use Text::Balanced qw (extract_bracketed extract_tagged);

$/ = undef; # slurp
#
###############################################################################
#
#    This file is part of latex2wims
#
#    latex2wims is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    latex2wims is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with latex2wims; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
###############################################################################
#
my ($FILE, $MACRO, $EMBED, $NUMERO, $doc_DIR, $DIR, $author, $email, $worksheet, $SHEET,$ABOUT) ;
my $verbose = 0;
my $depth = 2 ;
my $INDEX = 0 ;
my $TOOLTIP = 0 ;
my $STYLE = '' ;
my $OPTION = '' ;
my $tooltip_prompt = '<img src="gifs/picto.gif" alt="picto">' ;
my $linkout='' ; 
$worksheet= '';
$SHEET = '' ;
$DIR = '';
$doc_DIR = '';
my @SECTIONS = qw(document part chapter section subsection subsubsection);
#my @SECTIONS = ( document part entete frame subsection subsubsection );
#TODO biblio dans un fichier séparé si on a rencontré \begin{thebibliography} Non,
# on n'a qu'a mettre cet environnement de type link
#$doc_DIR=$ENV{'w_docdir'}; 
#$DIR=$ENV{'w_dir'};
#$DIR =~ s/ +//; 
push (@ARGV,split(' ', $ENV{'wims_exec_parm'})) if ($ENV{'wims_exec_parm'}) ; 

while ($_ = shift (@ARGV))
{
  last if (!/^--/);
     if (/^--style=(.*)$/) { $STYLE   = $1; }  
  elsif (/^--macro=(.*)$/) { $MACRO   = $1; }
  elsif (/^--docdir=(.*)$/){ $doc_DIR = $1; }
  elsif (/^--dir=(.*)$/)   { $DIR     = $1; }
  elsif (/^--embed=(.*)$/) { $EMBED   = $1; } 
  elsif (/^--verbose$/)    { $verbose = 1; }
  elsif (/^--author=(.*)$/){ $author  = $1; }
  elsif (/^--email=(.*)$/) { $email   = $1; }
  elsif (/^--worksheet=(.*)$/) { $worksheet   = $1; } 
  elsif (/^--tooltip_prompt=(.*)$/) { $tooltip_prompt = $1; }
  elsif (/^--linkout=(.*)$/) { $linkout = $1; }
  elsif (/^--cut=(.*)$/) { @SECTIONS = split(',',$1) ;} 
  elsif (/^--help$/) {
   usage(); # includes --help !
    exit 1;
  }
} ;

$FILE = $_;

$DIR = $DIR . '/' if ($DIR) ;
$doc_DIR = $doc_DIR . '/' if ($doc_DIR) ; 
my $LOAD = '\reload{<img src="gifs/doc/etoile.gif" alt="rechargez" width="20" height="20" border=0>}';
my $FLECHE = '<img src="gifs/arrows/right3.32.gif" alt=" ---> " width="25" height="15" border=0>';
$linkout = "\\doc{module=$linkout}" . $FLECHE if ($linkout) ; 

##################################
##Initialisation
#si je rajoute les listes : type=fold : signifierait que les item sont en fold [demande
#d'avoir des titres, ca serait du type description en latex
#pas de titre ? deb fin <ul ... >  </ul>
#type = 
#hash contenant les caractéristiques des environnements latex, voir \environmentwims
my %hash_environ = (
  titre  => {},
  style  => {},
  type   => {},
  deb    => {},
  fin    => {},
  parm   => {},
  origin => {},
  list   => {},
  tabular => {},
);


#hash contenant les commandes venant de \defwims, \def & co ou par defaut
my %hash_command = (
  cnt_arg    => {},
  definition => {},
  origin     => {},
);
my @liste_env_list = ('itemize', 'description', 'enumerate', 'trivlist') ; 
  $hash_environ{type}{'description_item'} = 'fold' ;
  $hash_environ{titre}{'description_item'} = ' ' ;

my @liste_env_tabular = ('tabular') ; 

my @liste_env_spec = ('equation', 'multline', 'latexonly',
  'pmatrix','smallmatrix', 'eqnarray', 'array', 'algorithmic', 'algorithm', 'align',
  'thebibliography', 'pspicture', 'picture', 'cases', 'gather',
  'displaymath', 'math', 'center', 'minipage', 'lstlisting');
  
my @liste_com_spec = ('paragraph', 'href', 'url', 'exercise', 'doc') ; #je ne m'en sers pas encore 

#commandes par défaut : sont écrasés par un \def ou un \defwims 

#$hash_command{cnt_arg}{text} = 1 ;
#$hash_command{definition}{text} = '\) #1 \(' ;
#$hash_command{origin}{text} = 'defaut' ;

$hash_command{cnt_arg}{paragraph} = 1 ;
$hash_command{definition}{paragraph} = '<p class="paragraph"> #1 </p>' ;
$hash_command{origin}{paragraph} = 'defaut' ;

$hash_command{cnt_arg}{href} = 2 ;
$hash_command{definition}{href} = '<a http:"#1" target="wims_external">#2</a>';
$hash_command{origin}{href} = 'defaut' ;

$hash_command{cnt_arg}{url} = 1 ;
$hash_command{definition}{url} = '<a http:"#1" target="wims_external">#1</a>';
$hash_command{origin}{url} = 'defaut' ;

$hash_command{cnt_arg}{exercise} = 2 ;
$hash_command{definition}{exercise} = "\\exercise\{\#1\}\{\#2\}";
$hash_command{origin}{exercise} = 'defwims' ;

$hash_command{cnt_arg}{doc} = 2 ;
$hash_command{definition}{doc} = '\doc{#1&cmd=new}{#2}';
$hash_command{origin}{doc} = 'defwims' ;

#a un label est associé son bloc [nom de fichier]
my %hash_bloc = (
  fichier  => {},
  titre    => {},
);

my %hash_index = (
  page    => {},
);

#type sert à repérer les fichiers embed ou fold. 
my %hash = (
  text   => {},
  prev   => {},
  next   => {},
  upbl   => {},
  titb   => {},
  tittoc => {},
  keyw   => {},
  datm   => {},
  label  => {},
  toc    => {},
  chemin => {},
  niveau => {},
  type   => {}, 
  author => {},
  title => {},
  email => {},
  toctip => {},
);

my %hash_toc = ();

my %prefixe = ( fold => 'F_' , link => 'L_' );

my %hash_secinv;
for (my $i = 0; $i <= $#SECTIONS; $i++) { $hash_secinv{$SECTIONS[$i]} = $i; }

my (%errmsg); # empèche le ré-affichage d'un même warning.
$SIG{__WARN__} = sub { my ($x) = @_;
  return if $errmsg{$x};
  $errmsg{$x} = 1;
  print STDERR "### $x";
};

#imposé par wims
my $BASE = $doc_DIR . 'doc/1/src';
my $BASE0= $doc_DIR . 'doc/1';

system("mkdir -p $BASE0") if (!$ENV{'wims_exec_parm'});
system("mkdir -p $BASE") if (!$ENV{'wims_exec_parm'});

$hash{niveau}{'main'} = 0;
#pour algorithmic
#TODO récupérer les informations dans le fichier de l'utilisateur

my %hash_algo = (
  titre => {},
  apres => {},
  avant => {},
  suite => {}
) ;
my $algo_noend = 0 ;
my $voca = %{$hash_algo{titre}} ;
my @liste_voca = ('FOR', 'IF','WHILE','REPEAT','ELSE','ELSIF','ENDIF','DO',
 'ENDWHILE', 'REQUIRE','ENSURE','ENDFOR','STATE','UNTIL','THEN', 'RETURN') ; 

$hash_command{definition}{algorithmicrequire}='<b>Require</b>';
$hash_command{origin}{algorithmicrequire}='defaut';
$hash_command{cnt_arg}{algorithmicrequire}= 0 ;
$hash_command{definition}{algorithmicensure}='<b>Ensure</b>';
$hash_command{definition}{algorithmicend}='<b>end</b>';
$hash_command{definition}{algorithmicif}='<b>if</b>';
$hash_command{definition}{algorithmicthen}='<b>then</b>';
$hash_command{definition}{algorithmicelse}='<b>else</b>';
$hash_command{definition}{algorithmicelsif}="<b>$hash_command{definition}{algorithmicelse} $hash_command{definition}{algorithmicif}</b>";
$hash_command{definition}{algorithmicendif}="<b>$hash_command{definition}{algorithmicend} $hash_command{definition}{algorithmicif}</b>";
$hash_command{definition}{algorithmicfor}='<b>for</b>';
$hash_command{definition}{algorithmicforall}='<b>for all</b>';
$hash_command{definition}{algorithmicdo}='<b>do</b>';
$hash_command{definition}{algorithmicendfor}="<b>$hash_command{definition}{algorithmicend} $hash_command{definition}{algorithmicfor}</b>";
$hash_command{definition}{algorithmicwhile}='<b>while</b>';
$hash_command{definition}{algorithmicendwhile}="<b>$hash_command{definition}{algorithmicend} $hash_command{definition}{algorithmicwhile}</b>";
$hash_command{definition}{algorithmicloop}='<b>loop</b>';
$hash_command{definition}{algorithmicendloop}="<b>$hash_command{definition}{algorithmicend} $hash_command{definition}{algorithmicloop}</b";
$hash_command{definition}{algorithmicrepeat}='<b>repeat</b>';
$hash_command{definition}{algorithmicuntil}='<b>until</b>';
$hash_command{definition}{algorithmicprint}='<b>print</b>';
$hash_command{definition}{algorithmicreturn}='<b>return</b>';


for my $cmd (@liste_voca) { $hash_command{origin}{"algorithmic\L$cmd\E"} = 'defaut' }

for my $cmd ('FOR','IF','WHILE','REPEAT','ELSE','ELSIF') {
          $hash_algo{apres}{$cmd} = 1 ;
} ;
for my $cmd ('IF') { $hash_algo{suite}{$cmd} = 'THEN' ;} ;
for my $cmd ('FOR','WHILE') { $hash_algo{suite}{$cmd} = 'DO' ;} ;
for my $cmd ('ENDFOR','ENDIF', 'ENDWHILE','UNTIL','ELSE','ELSIF') {
          $hash_algo{avant}{$cmd} = -1 ;
} ;
for my $cmd ('FOR','IF','WHILE','REQUIRE','ENSURE', 'STATE','UNTIL') {
          $hash_algo{avant}{$cmd} = 0 ;
} ;
for my $cmd ('ENDFOR','ENDIF','ENDWHILE','REQUIRE','ENSURE', 'STATE','UNTIL') {
          $hash_algo{apres}{$cmd} = 0 ;
}


# lit les fichiers wims.sty  puis les fichers .tex. pour éviter : un seul fichier tex, le premier ? 

my $TEXT = Init($FILE, \%hash_environ, \%hash_command, \%hash, \%hash_algo);
out1 ('sheet', $SHEET) ;
$ABOUT = $hash{about}{main} ; 
out1 ('about.phtml', (($ABOUT)? $ABOUT :'') . '
<p>
Ce document a été créé par Latex2wims.<p>

!changeto docu/about.phtml') ;
if (!($hash{author}{main})) {
  warn " ATTENTION : Vous devez mettre un nom d'auteur \\author{xxx}" ;
  $hash{author}{main}=$author } ;
if (!($hash{title}{main})) {
  warn " ATTENTION : Vous devez mettre un titre : \\title{xx} " ;
  $hash{title}{main} = '??' } ;
if (!($hash{email}{main})) {
  warn " ATTENTION : Vous devez mettre un email \\email{xxx}" ;
  $hash{email}{main}=$email } ;
  

# PASSE 2: ferme les \section & co
my $SEC_MIN_GLOBAL = 10; # = \infty
#$SEC_MIN_GLOBAL = 3 ; 
my @cnt = (0) x ($#SECTIONS + 1);
my ($secpattern) = join('|', @SECTIONS);
$TEXT =~ s/\\begin\s*{($secpattern)\s*}/cnt_section($1,\@cnt)/eg;
$TEXT =~ s/\[fragile\]//g;
$TEXT =~ s/\s*\\frametitle//g;
$TEXT =~ s/\\end\s*{\s*($secpattern)\s*}/<\/$1>/g;
$TEXT =~ s/\\wimsentre{($secpattern)}/\\wimsentre$1/g;
$TEXT =~ s/\\(wimsentre)?($secpattern)\b\*?/open_close($2,\@cnt,$1)/eg;
$TEXT =~ s|</document>.*||s;
$TEXT =~ s|.*<document>||s;
if($SEC_MIN_GLOBAL == 10) {$SEC_MIN_GLOBAL = 0} ; 
my ($NIVEAU, $NIVEAU_max) = ($SEC_MIN_GLOBAL, $SEC_MIN_GLOBAL + $depth - 1);
 


# PASSE 3: crée les blocs venant des sections et co
#  et renvoie une partie de la table des matières
my $toc = analyse_texte ($TEXT, \%hash, 'main', $NIVEAU, $NIVEAU_max, '');
# PASSE 4: création de tous les blocs ( environnements de type fold ou link)
{
  my ($ref, $ref_env)  = (\%hash, \%hash_environ);
  while (my ($Id, $TEXT) = each (%{$hash{text}})) {
    $TEXT = TraiteText ($TEXT, $ref, $ref_env, $Id);
#TODO non testé l'utilisation de prev etc
    $ref->{text}{$Id} = $TEXT;
  }
}
#récupération de tous les labels et rajout du titre en haut de la table dans la toc du tag
#On les traite pour que le label soit associé au nom du fichier créé automatiquement.
#$hash{toc}{$tag} contient les fichiers des sections en dessous de $tag

# PASSE 5
for my $tag (keys %{$hash{text}}) {
  my $T = $hash{text}{$tag};
  $T =~ s/\\label\s*\{([^}]+)\}/store_label($1, $tag, \%hash_bloc)/eg;
  $T =~ s/\\index\s*\{([^}]+)\}/store_index($1, $tag, \%hash_index)/eg;
  $hash{text}{$tag} = $T;
  my $tagupbl = $hash{upbl}{$tag};
  #plus utilisé, mais j'hésite !
#  $hash_toc{$tag} = "\\link{$tagupbl}\n\n" . $hash{toc}{$tagupbl};
}
 
   
# PASSE 6: sort l'index mis à jour des ref à l'aide des labels créés auparavant  et rajoute 
#TODO rajouter eqref mais ca dépend vraiment de la phrase !
for my $tag (keys %{$hash{text}}) {
  my $macro = '\\\\ref|\\\\cite|\\\\eqref';
  my $T = $hash{text}{$tag};
  my $cle = 'prev|next|upbl|titb|keyw|datm'; 
  $T =~ s/($macro)\{([^}]+)\}\{([^}]+)\}/store_ref($2, $3, $2, \%hash_bloc)/eg;
# repere toto~\cite{}
  $T =~ s/([^\s]+)\~($macro)\s*([.*])?\s*\{([^}]+)\}/store_ref($4, $1 .
    ($3||''), $4, \%hash_bloc)/eg;
  $T =~ s/($macro)\s*([.*])?\{([^}]+)\}/store_ref($3, ($2 ? "$3: $2" : $3), $3, \%hash_bloc)/eg;  
  $T =~ s/\\($cle)\s*\{(\w*)\}/store_tag($1, $2, $tag, \%hash, \%hash_bloc)/eg;
  $hash{text}{$tag} = $T;
}
my @L = sort {$a cmp $b} (keys %{$hash_index{page}}) ;
out('index', selection('<div class="index">' . makeindex (\%hash_index, 0, @L) . '</div>'
                         ,'left-selection','index')) if ($INDEX == 1 && makeindex (\%hash_index));

#crée les blocs [entourés de la table des matières]

#crée les deux sortes de fichiers demandés par wims .def (fichier de définition général) +
# nom.hd  qui gère les règles de navigation  pour chaque bloc
#attention : dans le cas où il y a un \\embed{toto}, il faut créer le fichier toto.hd ...
#TODO : \embed{toto} : je suppose ici que le contenu de toto est du wims à ne pas 
#interpréter
#pour l'instant je m'en suis servi pour stocker des programmes qui interviennent plusieurs fois. 

#Crée le vrai fichier qui est mis dans le dossier src
#On ne met pas de table de matières si le bloc est de type fold
#TODO option = chemin tout seul, toc à gauche + chemin, toc à gauche et à droite + chemin,  
#style selection droite, selection gauche

for my $tag (keys %{$hash{text}}) {
  complete ($tag, \%hash);
  out ("$tag.hd", hd($tag,\%hash)); 
  my $txt = traitement_final($hash{text}{$tag});
  my $tagupbl = $hash{upbl}{$tag};
  my $type = $hash{type}{$tag} ;
 #si type est non vide il est égal à embed ou fold
  my $dotoc_left = ($OPTION =~ /toc_left/ && !$type);
  my $dotoc_right = ($OPTION =~ /toc_right/ && !$type);
  my $dotoc_up = ($OPTION =~ /toc_up/ && !$type);
  my $dotoc_down = ($OPTION =~ /toc_down/ && !$type);
  my $CHEMIN = chemin($tag, \%hash);
  #J'ai enlevé $LOAD
  $CHEMIN = ($dotoc_up || $dotoc_down)  && ($CHEMIN =~ $FLECHE) ? $CHEMIN : '';
  my $CHEMIN_up=($dotoc_up) ? "<div id=\"up_toc\">$CHEMIN</div>": '' ;
  my $CHEMIN_down=($dotoc_down) ? "<div id=\"down_toc\">$CHEMIN</div>" : '' ; 
  my @Chemin = split(',', $hash{chemin}{$tag});
  my $TOCg = $dotoc_left ? selection($hash{toc}{main}, 'left_selection', @Chemin) : '';
  my $TOCd = ($dotoc_right && $tagupbl ne 'main') ? selection($hash{toc}{$tagupbl}, 'right_selection', @Chemin) : '';
  my $tit_index = ($hash{titb}{index})? $hash{titb}{index} : 'Index' ;
  my $index = ($INDEX == 1) ? "\n\n\\link{index}{$tit_index}" : '';
  my $tooltip = ($TOOLTIP == 1) ? "<script type=\"text/javascript\" src=\"scripts/js/wz_tooltip.js\"></script>" : '' ;
  out ($tag, $tooltip . toc_HTML ($txt, clean($TOCg,\%hash), clean($TOCd,\%hash), $CHEMIN_up, $CHEMIN_down, $index) );
}
if ($INDEX == 1) { out ('index.hd', hd('index',\%hash) )};
my @style = sortuniq(split(',',$STYLE)) if ($STYLE) ;
out_def ('.def', def (\%hash, @style ));

##############

sub analyse_texte { my ($TEXT, $ref, $Id, $niveau, $niveau_max, $Toc) = @_;
  my $link = ($niveau <= $niveau_max);
  return $Toc if $niveau > $#SECTIONS ;
  my $section = $SECTIONS[$niveau];
  my $sectiontag = "<$section>";
  my @decoup = split (/$sectiontag/, $TEXT);
  my $text = $decoup[0];
  my $toc_titre ;
  my ($cnt, $id) = (1, "");
  #On parcourt un texte $Id : $text  et on enlève tous les niveaux inférieurs
 # (boucle while)
  while ( $decoup[$cnt]) {
  #tient compte des titres courts pour la toc
    my @u = extract_tagged ($decoup[$cnt],'\[','\]');
    $toc_titre = ($u[4]) ? $u[4] : '' ;
    @u = extract_tagged ($u[1],'{','}');
    if (!$u[4]) { $NUMERO = 1 ; warn " ATTENTION : section dans $Id sans titre ; l'option numerotation a été rajoutée"};
    my @extract = extract_tagged ($sectiontag . $u[1], $sectiontag);

    my $idold =  $id;
    $id = $Id . ($link? 'S': "$prefixe{fold}S") . $cnt;
    $cnt++;
    my $titre = $u[4];
    $toc_titre = $titre if (!$toc_titre) ;
    $titre =~ s/\n/ /g;
    $titre = Numero($id) . "  $titre" if ($NUMERO);
    $toc_titre = Numero($id) . "  $toc_titre" if ($NUMERO);
    $text .=  $link ?"\n\n\\link{$id}\n\n"
                    :"\n\n\\fold{$id}{<span class=\"$section\">$titre</span>}\n\n";
    if ($link) {
      $Toc .=  "\n\n<XXXX=$id>\\link{$id}{$toc_titre}</font><YYYY=$id>\n\n";
    }
    $text .= $extract[1];
    $ref->{titb}{$id} = $titre;
    $ref->{tittoc}{$id} = $toc_titre;
    $ref->{text}{$id} = $extract[4];
    $ref->{type}{$id} = 'fold' if !$link ;
    $Toc = analyse_texte ($ref->{text}{$id}, $ref, $id, $niveau + 1, $niveau_max, $Toc) ;
    $ref->{upbl}{$id} = $Id;
    $ref->{prev}{$id} = $idold;
    $ref->{next}{$idold} = $id;
   #modifier avec selection
    my $tp = '' ; 
    if ($TOOLTIP==1) {
    if (!$ref->{toctip}{$Id}) {$ref->{toctip}{$Id}=' ' ; } else {
      $ref->{toctip}{$Id} .= ($ref->{tittoc}{$id}) ?  '<br>': '' ;}
    $ref->{toctip}{$Id} .= $ref->{tittoc}{$id} ;
    $tp = "ZZZZZ$id" ; }
    $ref->{toc}{$Id} .= "\n<XXXX=$id>\\link{$id}{$ref->{tittoc}{$id}
    }$tp <YYYY=$id>\n";
  }
 #maintenant, ce qui reste dans $text est exactement ce qu'on doit mettre dans le hash->{text}{$Id}
  $ref->{text}{$Id} = $text;
  $ref->{titb}{main} = $ref->{title}{main};
  $ref->{tittoc}{main} = $ref->{title}{main} if (!$ref->{tittoc}{main});
  $Toc;
}

sub store_tag { my ($cle, $label, $tag, $ref, $ref_bloc) = @_;
  $ref->{$cle}{$tag} = $ref_bloc->{fichier}{$label} ;
  '';
}

sub store_label { my ($label, $Id, $ref) = @_;
   $ref->{fichier}{$label} = $Id; 
   "<a name=\"$label\"></a>";
}

sub dbg { print STDERR "$_[0]\n" if ($verbose); }

sub store_index { my ($label, $Id, $ref_index) = @_;
   dbg("... index: \"$label\"");
   my $L = $ref_index->{page}{$label};
   $ref_index->{page}{$label} =  !$L ? $Id : "$L,$Id";
   "<a name=\"$label\"></a>";
}

sub class_index { my ($index,$level) = @_ ; 
     my @a = split('!', $index) ; 
     ($a[$level])? $a[$level] : $index ; 
 }
 #!(keys %{$ref_index->{page}}
 #sort keys %{$ref_index->{page}} ; 

sub makeindex { my ($ref_index, $level, @L ) = @_; 
   return '' if (!$#L) ;
   my $dejavu = '' ;
   my $TEXT = "\n<ul class=\"index\">";
   for my $index (@L) {
      next if ($dejavu =~ /\b$index\b/) ; 
      my @list = sort {$a cmp $b} grep {class_index($_, $level) eq class_index($index, $level)} @L ;
      my @l = split('!', $index) ; 
      if ($l[$level]) {
          $TEXT .= "<li> " ;  
          for my $ind (split(',',$ref_index->{page}{$index})) {
             if ($ind && !($dejavu =~ /\b$ind\b/)) { 
                 $TEXT .= "\\link{$ind}{".  $l[$level] . " }{$ind}" ;
             }
          }
          $dejavu .= ' ' . join (' , ', @list) ;
          $TEXT .= makeindex ($ref_index, $level + 1, @list) . "</li>" ;
      };
   }
   "$TEXT </ul>";
}

sub TraiteText {my ($TEXT, $ref, $ref_env, $Id) = @_;
  $TEXT =~ s/\s*$//; # strip trailing whitespace
 #0 ul et li sans rien
 #1 avec style
 $TEXT =~ s/\\(begin|end)\s*{wimsonly}/\n/g;
 for my $rubrique (keys %{$ref_env->{list}}) {
     $TEXT = traite_list ($TEXT, $ref, $ref_env, $Id, $rubrique,1);
 }

 for my $rubrique (@liste_env_list) {
     $TEXT = traite_list ($TEXT, $ref, $ref_env, $Id, $rubrique,0);
 }

for my $rubrique (keys %{$ref_env->{tabular}}) {
     if ($TEXT =~ /\\begin{$rubrique}/) {
       $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique,0);
     }
 }
 
for my $rubrique (@liste_env_tabular) {
   if ($TEXT =~ /\\begin{$rubrique}/) {
     $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique,0);
   }
}
 
 for my $rubrique (@liste_env_spec) {
    if ($TEXT =~ /\\begin{$rubrique(\*)?}/) {
      $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique, 1);
    }
  }
#le 1 et 0 servent à initialiser le compteur dans le cas ou on doit créer de nouveaux blocs dans la même page
  
  for my  $rubrique (keys %{$ref_env->{titre}}) {
    if ($TEXT =~ /\\begin{$rubrique}/) {
      $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique,1);
    }
  }
  for my $rubrique (keys %{$ref_env->{list}}) {
     $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique,0);
     $TEXT = traite_environ ($TEXT, $ref, $ref_env, $Id, $rubrique . '_item',0);
  }
 
  if ($TEXT =~ /\\begin\{\s*(\w*)\s*\}/g) {
     warn " ATTENTION : environnement non répertorié : $1" if $1 ne 'matrix';
  }
  $TEXT =~ s,<li>\n+</li>,<li></li>,g;
  $TEXT;
}

#on pourrait faire une boucle  while ; on pourrait avoir deux fois le meme environnement imbrique ?
#begin{proof} \begin{proof} \end{proof}\end{proof} Je crois que c'est pour cela que je fais ce truc
#tordu. En fait  split me sert uniquement à trouver le premier <$environ>
#$cnt sert à numéroter semi-globalement (création de blocs correspondant à un même environnement dans une meme page
#exemple mainS4S3F_proof1,mainS4S3F_proof2,mainS4S3F_proof3,mainS4S3F_proof4,mainS4S3F_proof5

sub traite_list {my ($TEXT, $ref, $ref_env, $Id, $environ, $option) = @_;
 my ($e_item, $b_item , $b_class, $e_class) = (' ',' ', ' ', ' ');
  if ( $option == 1 ) {
         $e_item = "\\end{$environ\_item}" ;
         $b_item = "\\begin{$environ\_item}" ;
      my $style = $ref_env->{style}{$environ} ;
      $style = ($style) ? $style : $environ;
      $b_class= "ul class=\"$style\"" ;
      $e_class= "\/ul" ; 
      }
      {
        if    ($environ eq 'enumerate'){ $b_class = "ol class=\"enumerate\"" ; $e_class= "\/ol" ; }
        elsif ($environ eq 'itemize'){ $b_class = "ul class=\"itemize\"" ;  $e_class= "\/ul" ;}
        elsif ($environ eq 'description'){
              $b_class = "ul style=\"list-style:none;\"" ;  
              $e_class= "\/ul" ;
              $e_item = "\\end{$environ\_item}" ;
              $b_item = "\\begin{$environ\_item}"
              }
        elsif ($environ eq 'trivlist') { $b_class = "ul style=\"list-style:none;\"" ;  
               $e_class= "\/ul" ;
        }
      }; 
  $TEXT =~ s/\\begin{$environ(\*)?}/<$environ>/g;
  $TEXT =~ s|\\end{$environ(\*)?}|<\/$environ>|g;
  
  my @decoup = split ("<$environ>", $TEXT);

  my $a = join ("<$environ>", @decoup[1..$#decoup]);
  return $TEXT if (!$a) ;
  my @u = extract_tagged ("<$environ>$a", "<$environ>");
  my $milieu = "<$environ>" . $u[4] . "<\/$environ>"   ; 
#FIXME pas de listes emboitées de type différent !
  $milieu =~ s|<$environ>\s*\\item|<$environ><li>$b_item|g ;
  $milieu =~ s|</$environ>|</li><$e_class>|g;
  $milieu =~ s|\\item|$e_item</li><li>$b_item|g;
  $milieu =~ s|</li><$e_class>|$e_item</li><$e_class>|g;
  $milieu =~ s|<$environ>|<$b_class>|g; 
  $decoup[0] . $milieu . traite_list ($u[1], $ref, $ref_env, $Id, $environ,$option);
}
  
sub traite_environ {my ($TEXT, $ref, $ref_env, $Id, $environ, $cnt) = @_;
  $TEXT =~ s/\\begin{$environ\*?}/<$environ>/g;
  $TEXT =~ s|\\end{$environ\*?}|</$environ>|g;
  
  my @decoup = split ("<$environ>", $TEXT);

  my $a = join ("<$environ>", @decoup[1..$#decoup]);
  return $TEXT if (!$a);
  
  my @u = extract_tagged ("<$environ>$a", "<$environ>");
  my $milieu = $u[4];
  return $TEXT if (!$milieu);

  my $pat_env = join('|', @liste_env_spec);
  my $patt_env = join('|', @liste_env_tabular); 
  if ($environ =~ /\b($pat_env)\b/) { $milieu = $1->($milieu) ; }
  elsif ($environ =~ /\b($patt_env)\b/) { $milieu = tabular->($milieu,$environ) ; }
  else { my @milieu1 = extract_bracketed ($milieu, '{}');
    if ($milieu1[0]) { $milieu = $milieu1[4] ; };
    my $type = $ref_env->{type}{$environ};

    if ($type && ($type eq 'fold' || $type eq 'link')) {
      my $titre = $ref_env->{titre}{$environ};
      my $newtag = $Id . $prefixe{$type} . $environ . $cnt;
      $ref->{type}{$newtag} = 'fold' if $type eq 'fold' ;
      $cnt++;
      # LaTeX interdit des [ ] imbriqués.
      if ($milieu =~ s/^\s*\[([^\]]+)\]//) {
        $titre =  ($titre) ? "$titre [ $1 ]" :  $1 ;
      }
      $ref->{titb}{$newtag} = $titre;
      $ref->{text}{$newtag} = encadrement("<$environ>$milieu<\/$environ>", $environ, $ref_env);
      $ref->{upbl}{$newtag} = $Id;
      $milieu = "\n\\$type\{$newtag\}\{"
        . encadr_defaut("<$environ>$titre<\/$environ>", $environ, $ref_env,'titre')
        . "\}\n\n" ;
    } else {  my $milieu1 = $milieu ; 
      $milieu = encadrement("<$environ>$milieu<\/$environ>", $environ, $ref_env, 'full');
    }
  }
  $decoup[0] . $milieu . traite_environ ($u[1], $ref, $ref_env, $Id, $environ, $cnt);
}

sub hd {my ($tag, $ref) = @_;
  my $txt = '';
  for  my $cle ('prev','next','upbl','titb','keyw','datm') {
    my $KEY = $ref->{$cle}{$tag};
    $txt .= "!set $cle=$KEY\n" if ($KEY);
  }
  $txt;
}
#rajoute un next aux section/subsection/ si cela n'existe pas [dernier] dernier sur index si il y a
#rajoute main pour ceux qui n'ont pas de parents. 
sub complete {my ($tag, $ref) = @_;
  $ref->{datm}{$tag} = isotime() if  !($ref->{datm}{$tag}) ; 
  $ref->{upbl}{$tag} = 'main' if  !($ref->{upbl}{$tag}) ;
  my $upbl = $ref->{upbl}{$tag};
  if (!$ref->{next}{$tag}) {
    my $a = $ref->{next}{$upbl};
    $ref->{next}{$tag} = $a || 'main';
  };
  if (!$ref->{prev}{$tag}) {
    my $b = $ref->{prev}{$upbl};
    $ref->{prev}{$tag} = $b || 'main';
  };
  if ($INDEX == 1 && !($ref->{titb}{index})) { $ref->{titb}{index} = 'Index' ;}
}

#option full  <h2 class="defn">Définition [titre perso]</h2> <div class= "definition">  </div> si cela existe
#option bloc  <div class= "definition"> </div>  si cela existe (intérieur d'un fold ou d'un link)
#option titre  <h2 class="defn">Définition </h2>  si cela existe (titre d'un fold)
sub encadr_defaut { my ($TEXT, $rubrique, $ref_env, $option) = @_;
  my $a = $ref_env->{titre}{$rubrique};
  my $b = $ref_env->{style}{$rubrique};
  if (!$b) {
    $b = $rubrique;
    $ref_env->{style}{$rubrique} = $b;
    dbg("... environnement $rubrique sans style css, par defaut $rubrique")
  };
  my $div_d = "<div class=\"$b\">";
  my $div_f = '</div>';
  if ( $option eq 'titre') { 
    $TEXT =~ s/<$rubrique>/<span class=\"$b\">/g;
    $TEXT =~ s/<\/$rubrique>/<\/span>\n\n/g;
  } elsif (!$a || $option eq 'bloc') {
    $TEXT =~ s/<$rubrique>\s*(\[[^\]]+\])?/$div_d/g;
    $TEXT =~ s/<\/$rubrique>/$div_f\n\n/g;
  } elsif ($option eq 'full') {
    $TEXT =~ s/<$rubrique>\s*(\[[^\]]+\])/<h2 class=\"$b\">$a $1<\/h2>$div_d/g;
    $TEXT =~ s/<$rubrique>/<h2 class=\"$b\">$a<\/h2>$div_d/g;
    $TEXT =~ s/<\/$rubrique>/$div_f\n\n/g;
  } else  { 
    $TEXT =~ s/<$rubrique>/<span class=\"$b\">/g;
    $TEXT =~ s/<\/$rubrique>/<\/span>\n\n/g;
  }
  $TEXT;
}
sub encadrement {  my ($TEXT, $rubrique, $ref_env) = @_;
  my $debut = $ref_env->{deb}{$rubrique};
  my $fin   = $ref_env->{fin}{$rubrique};
  my $opt= ($ref_env->{type}{$rubrique} && $ref_env->{type}{$rubrique}=~ /fold/) ? 'bloc' : 'full' ; 
  return encadr_defaut ($TEXT, $rubrique, $ref_env, $opt) if (!$debut && !$fin);

  $TEXT =~ s/<$rubrique>//;
  my $cnt_arg = $ref_env->{cnt_arg}{$rubrique};
  my $d = join('   ', subst($TEXT, $cnt_arg, $debut, $rubrique, $ref_env));
  my ($com,$txt) = subst($TEXT, $cnt_arg, $fin);
  $d =~ s/<\/$rubrique>/$com/;
  $d;
}


sub tabular { my ( $b, $style ) = @_; 
  my @v = extract_bracketed ($b, '{}') ; 
  my $stylerow = $style . "_row";
  my $stylecell = $style . "_cell";
  $b =  "<table class=\"$style\"><tr class=\"$stylerow\"><td class=\"$stylecell\">" . $v[1] . '</table>';
  $b =~ s|\&|&nbsp;</td><td class=\"$stylecell\">&nbsp;|g;
  $b =~ s/\\hline//g;
  $b =~ s|\\\\\s*</table>|</td></tr></table>|g;
  my $par="\\\\\\(|\\\\\\)" ;
  my @dectab = split(/$par/, $b) ; 
  $b = $dectab[0] ; 
  $b =~ s|\\\\|</td></tr><tr class=\"$stylerow\"><td class=\"$stylecell\">|g;
  my $cnt = 0; $b = '' ; 
  while ($cnt <= $#dectab/2) { 
     my $c = $dectab[2*$cnt] ; 
     $c =~ s|\\\\|</td></tr><tr class=\"stylerow\"><td class=\"$stylecell\">|g;
     $b .=  $c . (($dectab[2*$cnt+1]) ? "\\(" . $dectab[2*$cnt+1] .  "\\)" : '' )  ; 
     $cnt ++ ; 
 };
 $b ; 
}

sub minipage { my ( $b ) = @_; 
 my @v = extract_bracketed ($b, '{}') ;
 my $width = $v[0] ;
 $width =~ s/\{(.*)\}/$1/;
 $width = linewidth($width) ;
  "<div style=\"width:$width; display:inline-block;\">
   $v[1] 
   </div>";
}
sub lstlisting { my ($b,$id ) = @_ ;
  $b =~ s ,\\,\\\\,g ;
  "<pre class=\"lstlisting\" id=\"lstlisting$id\">$b</pre>";
}

sub multline { my ( $b) = @_;
  $b =~ s/\\\\\s*=/\\)<br>\\(== /g;
  $b =~ s|\\\\|\\)<br>\\(|g;
  "<div class=\"math\">\\(" . $b . "\\)</div>\n";
}

sub equation { my ( $b) = @_;
  $b = "\\(  $b \\)";
  if ($b =~ s/\\label{([^\}]+)}//) { $b = "\\label{$1}" . $b };
  '<div class="math">' . $b . '</div>' ;
}

sub align1 { my ( $b) = @_;
  $b = "\\(\\begin{matrix}  $b  \\end{matrix} \\)";
  if ($b =~ s/\\label{([^\}])}//) { $b = "\\label{$1}" . $b };
  '<div class="math">' . $b . '</div>' ;
}
sub align { my ( $b) = @_;
  $b =  '<table border=0 align="center" class="tableau"><tr><td>\\(' . $b . '\\\\</table>';
  if ($b =~ s/\\label{([^\}])}//) { $b = "\\label{$1}" . $b };
  $b =~ s|\&|\\)&nbsp;</td><td>&nbsp;\\(|g;
  $b =~ s|\\\\\s*</table>|\\)</td></tr></table>|g;
  $b =~ s|\\\\|\\)</td></tr><tr><td>\\(|g;
  '<div class="math">' . $b . '</div>' ;
}

sub pmatrix {"\\left ( \\begin{matrix} " . $_[0] . "\\end{matrix} \\right )" ;}
sub smallmatrix {"\\left ( \\begin{matrix} " . $_[0] . "\\end{matrix} \\right )" ;}
sub eqnarray {" <div class=\"math\">\\(\\begin{matrix} " . $_[0] . "\\end{matrix})</div> " ;}
sub center {" <div class=\"center\">" . $_[0] . "</div>"}

sub array {my ( $b ) = @_ ;
  my @v = extract_bracketed ($b, '{}');
  "\\begin{matrix} " . $v[1] . "\\end{matrix} ";
}
#TODO pour l'instant
sub cases {"\\Biggl \\{\\begin{matrix} " . $_[0] . "\\end{matrix}" ; }

sub gather { my ($b) = @_;
  my @decoup = split ('\\\\intertext', $b);
  my $cnt = 1;
  $b = equation($decoup[0]);
  while ($cnt <= $#decoup) {
    my @a = extract_bracketed ( $decoup[$cnt], '{}' );
    my $c = $a[0];
    $c =~ s/\{(.*)\}/$1/;
    $b .= $c . equation($a[1]);
    $cnt ++;
  }
  $b;
}

sub displaymath {"<div class=\"math\">\\( " . $_[0]. "\\)</div>"; }
sub math {" \\( " . $_[0]. "\\) "; }


sub thebibliography { my ( $b ) = @_;
  $b =~ s/\\bibitem{([^}]+)}/<\/li>\n<li>\[$1\]\\label{$1} /g;
  $b =~ s/\{\d+\}\s*<\/li>//;
  '<h2 class="thebibliography">' . $hash{titb}{ref} 
  . "</h2>\n<ul class=\"thebibliography\">$b </li></ul>\n";
}
sub pspicture { '<p>dessin à faire dans wims</p>' ; }
sub picture { '<p>dessin à faire dans wims</p>' ; }

#decoupe ce qui se trouve à l'intérieur de \begin{wims} \end{wims} pour ne pas y toucher.
# même pour verbatim, lstlisting
sub traite_special { my ( $TEXT, $ref_spec, $ref, $environ ) = @_;
  $TEXT = recup_embed($TEXT, $ref) ;
  $TEXT =~ s/\\begin{$environ}/<$environ>/g;
  $TEXT =~ s/\\end{$environ}/<\/$environ>/g;
  $TEXT =~ s/\r\n/\n/gs ;
  my @decoup = split ("<$environ>", $TEXT);
  my $cnt = 1;
  if ($#decoup) {
    $TEXT = $decoup[0];
    while ($cnt <= $#decoup) {
      my @a = extract_tagged("<$environ>" . $decoup[$cnt], "<$environ>");
      die "Bug dans $environ insertion: $decoup[$cnt]" if (!defined($a[4]));
      $TEXT .= $environ . 'insertion' . $cnt . $a[1];
      $ref_spec->{$cnt} = $a[4];
      $cnt++;
    }
  }
  $TEXT;
}

sub latexonly { '' }

sub store_cmd { my ($def, $id, $narg, $val, $ref_command) = @_;
  if ($hash_secinv{$id}) {
    warn " ATTENTION : commande perso \"$id: argument invalide\n";
    return '';
  }
  my $origin = $ref_command->{origin}{$id};
  return '' if ($origin && $origin eq 'defwims' && $def ne 'defwims');
  $ref_command->{origin}{$id} = $def;
  $ref_command->{cnt_arg}{$id} = $narg;
  $ref_command->{definition}{$id} = $val;
  dbg("... commande perso \"$id\": argument: \"$narg\" definition: \"$val\"");
 '' ;
}
  
sub store_environ { my ($def, $cmd, $narg, $titre, $deb, $fin, $ref_env) = @_;
  my $origin = $ref_env->{origin}{$cmd};
  return '' if ($origin && $origin eq 'environmentwims' && $def ne 'environmentwims');
  $ref_env->{deb}{$cmd} = $deb;
  $ref_env->{fin}{$cmd} = $fin;
  $ref_env->{cnt_arg}{$cmd} = $narg;
  $ref_env->{titre}{$cmd} = $titre;
  $ref_env->{origin}{$cmd} = $def;
  my $style = $ref_env->{style}{$cmd} ;
  $style = ($style)? $style : $cmd ; 
  #if (!$ref_env->{deb}{$cmd}) { $ref_env->{deb}{$cmd} = "<div class=\"$style\"> "; }
  #if (!$ref_env->{fin}{$cmd}) { $ref_env->{fin}{$cmd} = "</div> "; }
  dbg("... environnement perso \"$cmd\" argument: \"$narg\" titre: \"$titre\" style: \"$style\" debut: \"$deb\"  fin: \"$fin\"");
  '';
}


sub recup_command {my ($TEXT, $ref_command) = @_;
  my $DEF = '(defwims|def|newcommand|renewcommand)';
  #FIXME ? mauvais pour def \def\toto#1#2 ... demander de le refaire avec defwims s'il y a plus de 3 arguments ? 
  $TEXT =~ s/\\$DEF\s*\\(\w*)#(\d)\{(.*)\}/store_cmd($1,$2,$3,$4,$ref_command)/eg;
  #2 arguments
  $TEXT =~ s/\\$DEF\s*\\(\w*)#(\d)#(\d)\{(.*)\}/store_cmd($1,$2,$4,$5,$ref_command)/eg;
  $TEXT =~ s/\\$DEF\s*\\(\w*)\s*\{(.*)\}/store_cmd($1,$2,0,$3,$ref_command)/eg;
  #3 arguments
  $TEXT =~ s/\\$DEF\s*\\(\w*)#(\d)#(\d)#(\d)\{(.*)\}/store_cmd($1,$2,$5,$6,$ref_command)/eg;
  # newcommand avec paramètres
  $TEXT =~ s/\\$DEF\s*\{\\(\w*)\}\s*\[(\d)\]\s*\{(.*)\}/store_cmd($1,$2,$3,$4,$ref_command)/eg;
  # newcommand sans paramètres
  $TEXT =~ s/\\$DEF\s*\{\\(\w*)\}\s*\{(.*)\}/store_cmd($1,$2,0,$3,$ref_command)/eg;
  $TEXT;
}

sub recup_config { my ($cmd, $arg, $ref_env) = @_;
  my @L = (split (',', $arg));
  my $style = $L[0];
  my $type = 'style';
  if ($cmd eq 'typefold') { $style = 'fold';  $type = 'type' };
  if ($cmd eq 'typelink') { $style = 'link' ; $type = 'type' };
  if ($cmd eq 'tablewims') { $type = 'tabular' ; };
  if ($cmd eq 'listwims') {                   $type = 'list' };
  for my $rubrique (@L) {
    $ref_env->{$type}{$rubrique} = $style;
    dbg("... commande $rubrique de $type $style");
    if ($cmd eq 'listwims') { $ref_env->{'style'}{$rubrique . '_item'} = $style . '_item' ; 
                              $ref_env->{'titre'}{$rubrique . '_item'} = '' }
  }
  push @liste_env_tabular, (keys %{$ref_env->{tabular}}) ; 
 '';
}
sub recup_environ {my ($TEXT, $ref_env) = @_;
  my $pat = '\s*\{(.*)\}';
  $TEXT =~ s/\\(typefold|typelink|samestyle|listwims|tablewims)\{([^\}]+)\}/recup_config($1,$2, $ref_env)/eg;
  # {nom}[#param]{titre}{debut}{fin}
  $TEXT =~ s/\\(environmentwims|[re]?newenvironment)\s*\{(\w*)\}\[(\d)\]$pat$pat$pat/store_environ($1,$2,$3,$4,$5,$6,$ref_env)/eg;
  # {nom}{titre}{debut}{fin}
  $TEXT =~ s/\\(environmentwims|[re]?newenvironment)\s*\{(\w*)\}$pat$pat/store_environ($1,$2,0,'', $3,$4,$ref_env)/eg;
 #\newtheorem{nom}[]?{titre}[]?
  $TEXT =~ s /(\\newtheorem\*?)\s*\{(\w*)\}\s*(\[[^\]]*\])?\s*\{([^\}]*)\}\s*(\[[^\]]*\])?\s*/store_environ($1,$2,0,$4,'','',$ref_env)/ge;
  $TEXT;
}

#on suppose que le texte commence par \command{}{}{}{} avec le bon nombre d'arguments

sub traite_command {my ($TEXT, $command, $ref_command) = @_;
  my $cnt_arg = $ref_command->{cnt_arg}{$command};
  my $com = $ref_command->{definition}{$command};
  if ($cnt_arg) {
    $TEXT =~ s/\\$command\s*\{/\{/;
    $TEXT = join ( "  ", subst($TEXT, $cnt_arg, $com));
  } else {
    $TEXT =~ s/\\$command\_/$com . '_'/ge;
    $TEXT =~ s/\\$command\b/$com/ge;
  }
  $TEXT;
}
#Texte = {}{}{} ou []{}{} qui sont les arguments
sub subst { my ($TEXT, $cnt_arg, $com, $environ, $ref_env ) = @_;
  my (@a,$u,$v);
  my $cnt = 0;
  while ($cnt < $cnt_arg) {
    @a = extract_tagged($TEXT, '{','}');
    ($u,$v) = ($a[1],$a[4]);
    if (!$a[0]) {
      @a = extract_tagged($TEXT, '\[','\]');
      ($u,$v) = ($a[1],$a[4]);
    }
    $TEXT = $u;
    $cnt ++;
     my $sub="" ; 
    if ($v) {
       $sub = $environ && $ref_env->{titre}{$environ} ? join (' ' , ( $ref_env->{titre}{$environ}, $v)) : $v;}
    else {$sub=''} ; 
     if (($com) && ("#$cnt")) { $com =~ s/#$cnt/$sub/ge ;  }  ; 
  }
  ($com, $TEXT);
}

sub Traite_command { my ($TEXT, $command, $ref_command) = @_;
  my $cnt_arg = $ref_command->{cnt_arg}{$command};
  if ($cnt_arg) {
    my @decoup = split ("\\\\$command\{", $TEXT );
    my $cnt = 1;
    $TEXT = $decoup[0];
    while ($cnt <= $#decoup) {
      $TEXT .= traite_command ('{' . $decoup[$cnt], $command, $ref_command);
      $cnt++;
    }
  } else {
    while( $TEXT =~ /\\$command\b/) {
      $TEXT = traite_command ($TEXT, $command, $ref_command);
    }
  }
  $TEXT;
}

my %outagain;
sub out { my ($bloc, $text) = @_;
  warn "Écrase $bloc" if ($outagain{$bloc});
  $outagain{$bloc} = 1;
  open  (OUT, ">$BASE/$bloc") || die "ne peut pas créer $BASE/$bloc";
  print OUT $text ; close OUT;
}

sub out1 { my ($bloc, $text) = @_;
  warn "Écrase $bloc" if ($outagain{$bloc});
  $outagain{$bloc} = 1;
  open  (OUT, ">$doc_DIR$bloc") || die "ne peut pas créer $doc_DIR/$bloc";
  print OUT $text ; close OUT;
}

sub out_def { my ($bloc, $text) = @_;
  open  (OUT, ">$BASE0/$bloc") || die "peut pas créer $BASE0/$bloc";
  print OUT $text ; close OUT;
}

# PASSE 1: développe 'input/include'
sub find_expand { my ($file) = @_; 
  if (!open(IN, $DIR . $file)) { warn "$DIR$file n'existe pas"; return; }
  dbg("... lecture de $file");
  my $text = <IN>; close(IN);
  $text =~ s/([^%]\s*\\end{document})[[:print:][:space:]]+/$1/;
  $text =~ s/([^%])\s*\\endinput[[:print:][:space:]]+/$1/;
  $text =~ s/\%\\(input|include|wimsinclude)([^\n]+)?//g;
  $text =~ s/\\(input|include|wimsinclude)\s*{?([a-zA-Z0-9\-_\/]+)\.(sty|tex)\s*}?/find_expand("$2.$3")/eg;
  $text =~ s/\\lstinputlisting\s*\{([a-zA-Z0-9\-_\/\.]+)\s*\}/"\\begin\{lstlisting\}\n" . find_expand($1) . "\n\\end\{lstlisting\}"/eg;
 
  $text;
}

sub open_close { my ($sec, $cnt, $entre) = @_;
  my ($txt) = '';
  my ($ind) = $hash_secinv{$sec};
  #ferme
  for (my $i = $#SECTIONS; $i >= $ind; $i--)
  {
    if ($cnt->[$i]) { $txt .= "</$SECTIONS[$i]>\n"; $cnt->[$i] = 0; }
  }
  #ouvre
  if (!$entre) {
    $txt .= "<$sec>"; $cnt->[$ind] = 1;
    $SEC_MIN_GLOBAL = $ind if ($ind < $SEC_MIN_GLOBAL && $ind);
  }
  $txt;
}

sub cnt_section { my ($sec, $cnt) = @_ ; 
  my ($txt) = '';
  my ($ind) = $hash_secinv{$sec};
  $SEC_MIN_GLOBAL = $ind if ($ind < $SEC_MIN_GLOBAL && $ind);
  "<$sec>"
 }
    

sub store { my ($ref, $cle, $id, $text, $court) = @_ ;
   $ref->{$cle}{$id}=$text ;
   if (defined($court)) { $court =~ s/\[|\]//g ; $ref->{tittoc}{$id} = $court ; } ;
   '';
 }
sub store_option { my ($A) = @_ ; $A = join(' ' , split(',', $A)) ;
    if ($A =~ s/numero//)  { $NUMERO = 1 ;} ;
    if ($A =~ s/index//)   { $INDEX = 1 ;}
    if ($A =~ s/tooltip//) { $TOOLTIP = 1 ;}
    if ($A =~ s/depth\s*=\s*([0-8])//) { $depth = $1 ; }
    $OPTION .= $A ;
   '' ;
 }

sub store_include { my ($A) = @_ ; $A = join(' ' , split(',', $A)) ;
    if ($A =~ s/(\w*)\.(tex|sty)//) { 
         if ($MACRO) {$MACRO .= ",$1.$2" } else {$MACRO = "$1.$2" } 
    };
    if ($A =~ s/(\w*\.css)\b//) { if ($STYLE) {$STYLE .= ",$1" } else {$STYLE = $1 } };
    if ($A =~ s/embed\s*=\s*([^}]+)//) { $EMBED = $1 ; }
   '' ;
 }

sub add { my ($a,$b)=@_ ;
    if ($a) {$a .= ",$b" } else {$a = $b } 
 }

sub Init { my ($file, $ref_env, $ref_command, $ref, $ref_algo) = @_;
  my ($total, $TEXT) = (0, find_expand($file));
  my %hash_spec = (wims =>{}, verbatim =>{}, lstlisting => {});
  my $ref_spec = \%hash_spec;
  $TEXT = traite_special ($TEXT, $ref_spec->{wims}, $ref,'wims');
  $TEXT = traite_special ($TEXT, $ref_spec->{verbatim}, $ref,'verbatim');
  $TEXT = traite_special ($TEXT, $ref_spec->{lstlisting}, $ref,'lstlisting');
  $TEXT = traitement_initial ($TEXT);
  $TEXT =~ s/\\wimsoption\s*\{([^\}]+)\}/store_option($1)/eg ;
  $TEXT =~ s/\\makeindex/store_option('index')/eg ;
  $TEXT =~ s/\\wimsinclude\s*\{([^\}]+)\}/store_include($1)/eg ;
  $TEXT =~ s/\\(title|email|author|about)\s*(\[[^\]]+\])?\s*\{([^\}]+)\}/store($ref,$1,'main',$3,$2)/eg ;
  
  $TEXT = traite_preambule ($TEXT, $ref_env, $ref_command, $ref);
  for my $command (keys %{$ref_command->{definition}}) {
    $TEXT = Traite_command ($TEXT, $command, $ref_command);
  }
  for my $A (@liste_voca) {
   $ref_algo->{titre}{$A} =  $ref_command->{definition}{"algorithmic\L$A\E"}  if ($ref_command->{definition}{"algorithmic\L$A\E"}) ;
} ;
  $TEXT =~ s/wimsinsertion(\d*)/$ref_spec->{'wims'}{$1}/g;
  $TEXT =~ s/verbatiminsertion(\d*)/<pre class="verbatim" id="verbatim$1">$ref_spec->{'verbatim'}{$1}<\/pre>/g;
  $TEXT =~ s/lstlistinginsertion(\d*)/lstlisting($ref_spec->{'lstlisting'}{$1},$1)/eg;
  $TEXT;
}

#sub store_makeindex { my ($txt) = @_ ;
#    $txt =~ s/\\printindex/\link{index}{Index}/ ;
#   }
sub traitement_final { my ($TEXT) = @_;
 #FIXME : je ne peux pas faire ca à cause des exercices de développement dont l'adresse
 #contienne un ~. De toute facon
 #ca ne devrait pas exister, mais quand même. ou les wims only
#   $TEXT =~ s/~/&nbsp;/g;
   $TEXT;
}

sub traitemath {my ($txt) = @_;
  my $test = 0;
  while ($txt =~ /\$\$/) {
    $txt = $` . ($test == 0 ? '<div class="math">\\(' : '\\)</div>') . $';
    $test = 1-$test;
  }
  $txt;
}

sub traitement_initial { my ($TEXT) = @_;
  $TEXT =~ s/\s*$//; # strip trailing whitespace
  $TEXT =~ s/\r\n/\n/gs ; 
  $TEXT = traitemath($TEXT);
  $TEXT =~ s/{\s*\\(bf|tt|it)\b/\\text$1\{/g;
  $TEXT =~ s/\\begin\b\s*/\\begin/g;
  $TEXT =~ s/\\end\b\s*/\\end/g;
  #$TEXT =~ s/\\text\b/\\hbox/g;
  $TEXT =~ s,\\\[,<p class="math">\\(,g;
  $TEXT =~ s,\\\],\\)</p>,g;
  $TEXT =~ s/\$([^\$]+)\$/\\( $1 \\)/g;

  $TEXT =~ s/\\`\s*{a}/à/g;
  $TEXT =~ s/\\\^\s*{a}/â/g;
  $TEXT =~ s/\\'\s*{a}/á/g;
  $TEXT =~ s/\\'\s*{e}/é/g;
  $TEXT =~ s/\\`\s*{e}/è/g;
  $TEXT =~ s/\\\^\s*{e}/ê/g;
  $TEXT =~ s/\\\^\s*{i}/î/g;
  $TEXT =~ s/\\\`\s*{i}/ì/g;
  $TEXT =~ s/\\\"\s*{i}/ï/g;
  $TEXT =~ s/\\\"\s*{\\i}/ï/g;
  $TEXT =~ s/\\\^\s*{o}/ô/g;
  $TEXT =~ s/\\\"\s*{o}/ö/g;
  $TEXT =~ s/\\\`\s*{o}/ò/g;
  $TEXT =~ s/\\\^\s*{u}/û/g;
  $TEXT =~ s/\\`\s*{u}/ù/g;
  $TEXT =~ s/\\c\s*\{c\}/ç/g;

  $TEXT =~ s/\\`\s*a/à/g;
  $TEXT =~ s/\\\^\s*a/â/g;
  $TEXT =~ s/\\'\s*a/á/g;
  $TEXT =~ s/\\'\s*e/é/g;
  $TEXT =~ s/\\`\s*e/è/g;
  $TEXT =~ s/\\\^\s*e/ê/g;
  $TEXT =~ s/\\`\s*E/È/g;
  $TEXT =~ s/\\\'\s*E/É/g;
  $TEXT =~ s/\\\^\s*E/Ê/g;
  $TEXT =~ s/\\\^\s*i/î/g;
  $TEXT =~ s/\\\`\s*i/ì/g;
  $TEXT =~ s/\\\"\s*i/ï/g;
  $TEXT =~ s/\\\^\s*o/ô/g;
  $TEXT =~ s/\\\"\s*o/ö/g;
  $TEXT =~ s/\\\`\s*o/ò/g;
  $TEXT =~ s/\\\^\s*u/û/g;
  $TEXT =~ s/\\`\s*u/ù/g;
  $TEXT =~ s/\\c \s*c/ç/g;
  
  $TEXT =~ s/{\s*\\`\s*a\s*}/à/g;
  $TEXT =~ s/{\s*\\\^\s*a\s*}/â/g;
  $TEXT =~ s/{\s*\\'\s*a\s*}/á/g;
  $TEXT =~ s/{\s*\\'\s*e\s*}/é/g;
  $TEXT =~ s/{\s*\\`\s*e\s*}/è/g;
  $TEXT =~ s/{\s*\\\^\s*e\s*}/ê/g;
  $TEXT =~ s/{\s*\\\^\s*i\s*}/î/g;
  $TEXT =~ s/{\s*\\\`\s*i\s*}/ì/g;
  $TEXT =~ s/{\s*\\\"\s*i\s*}/ï/g;
  $TEXT =~ s/{\s*\\\^\s*o\s*}/ô/g;
  $TEXT =~ s/{\s*\\\"\s*o\s*}/ö/g;
  $TEXT =~ s/{\s*\\\`\s*o\s*}/ò/g;
  $TEXT =~ s/{\s*\\\^\s*u\s*}/û/g;
  $TEXT =~ s/{\s*\\`\s*u\s*}/ù/g;
  $TEXT =~ s/{\s*\\c \s*c\s*}/ç/g;
  $TEXT =~ s/{\\textquotesingle}/'/g;
  $TEXT =~ s/\\textquotesingle/'/g;
  $TEXT =~ s/\\guillemotleft/<</g;
  $TEXT =~ s/\\guillemotright/>>/g;
# MODIF YVES NOEL 19/09/2011 (debut)
  $TEXT =~ s/>>/&gt;&gt;/g;
  $TEXT =~ s/~~/&nbsp;&nbsp;/g;
  $TEXT =~ s/\\onslide\+<[0-9]*>//g;
  $TEXT =~ s/\\onslide<[0-9]*->//g;
  $TEXT =~ s/\\onslide<[0-9]*>//g;
  $TEXT =~ s/\\onslide\+<[0-9]*\-[0-9]*>//g;
  $TEXT =~ s/\\onslide<[0-9]*\-[0-9]*->//g;
  $TEXT =~ s/\\onslide<[0-9]*\-[0-9]*>//g;
# MODIF YVES NOEL 19/09/2011 (fin)
  $TEXT =~ s/{}//g;
  $TEXT =~ s/\\selectlanguage{french}\\sffamily//g;
  
 #$TEXT =~ s/([^\\])\%+/$1/g;
  $TEXT =~ s/([^\\])\%.*/$1/g;
  $TEXT =~ s/\n\%.*/\n/g;
  $TEXT =~ s/\\\\\[\S*\]/\n\n/g;
  $TEXT =~ s/\\(vspace|hspace|vskip|hskip)\**{\S*}//g;
  $TEXT =~ s/\\parskip=*[a-z0-9 \.]+//g;
  $TEXT =~ s/\\(vskip|hskip)\s*[a-z0-9 \.]+//g;
  $TEXT =~ s/\\smallskip/\n/g;
  $TEXT =~ s/\\(med|big)skip/\n\n/g;
#  $TEXT =~ s/\\makebox\[(\w)cm\]{ }/\&nbsp\&nbsp\&nbsp/g;
  $TEXT =~ s/~(:|;|\?|\!)/&nbsp;$1/g;
 #utiliser verb uniquement dans le cas d'un mot
#FIXME:  $TEXT =~ s/\verb"([^"]+)"/<tt class=verb>$1<\/tt>/g;
  $TEXT =~ s/\\includegraphics\s*\[(.*)\]\s*{(.*)}/<img src=\"\\filedir\/$2\" $1 alt=\"\">/g;
  $TEXT =~ s/\\includegraphics\s*{(.*)}/<img src=\"$1\" alt=\"\">/g;
  $TEXT =~ s/\\(begin|end){document}/\\document /g;
  $TEXT =~ s/\\exercise{module=([^\&]+)\&([^}]+)}{([^}]+)}/store_sheet($1,$2,$3,$worksheet)/eg ; 
  $TEXT =~ s/\\xspace//g;
  $TEXT;
}

sub linewidth { my ($line)= @_ ;
  $line =~ s/1\.[0]\s*\\linewidth/100\%/g;
  $line =~ s/0?\.([0-9])\s*\\linewidth/$1 0\%/g;
  $line =~ s/0?\.([0-9]{2})[0-9]?\s*\\linewidth/$1\%/g;
  $line =~ s/ //g;
  $line ;
}
sub store_sheet { my ($ad1,$ad2,$titre,$worksheet) = @_ ;
   $ad2 =~ s/worksheet=(\d)+//g ; 
   $SHEET .= ":$ad1\n$ad2\n$titre\n\n" ;
   "\\exercise\{module=$ad1\&$ad2\&worksheet=$worksheet\}\{$titre\}" ; 
 }
 
sub traite_preambule { my ($TEXT, $ref_env, $ref_command, $ref) = @_;
  if ($TEXT=~ s/\\usepackage\[([^]]+)\]\{algorithmic\}//) {
       $algo_noend = 1  if ($1 =~ /noend/);
       
  } ;
  $TEXT = recup_environ($TEXT, $ref_env);
  $TEXT = recup_command($TEXT, $ref_command);
  $TEXT = recup_embed($TEXT, $ref) ;
  for my $cmd ('ref','index') {
     $ref->{titb}{$cmd} = $ref_command->{definition}{$cmd . "name"} 
  }
  $TEXT;
}

sub store_embed { my ($id, $titre, $ref) = @_ ;
     $ref->{titb}{$id} = $titre ; $ref->{text}{$id} = `cat $EMBED/$id` ;
     $ref->{upbl}{$id}='main'; $ref->{type}{$id}='embed';
     "\\embed{$id}{$titre}" ;
}

sub recup_embed { my ($TEXT, $ref) = @_ ;
     $TEXT =~ s /\\embed\s*{([^}]+)}\s*{(.*)}/store_embed ($1, $2, $ref)/eg ;
     $TEXT ;
 }

#FIXME on ne peut prendre qu'un seul fichier de style
#crée le fichier 1/.def
sub def { my ($ref, @style) = @_;
  my $tit = $ref->{title}{main};
  my $aut = $ref->{author}{main};
  my $mail= $ref->{email}{main};
  my $datm= $ref->{datm}{main};
  my $header = '' ;
  my $header_tmp ;
  for my $file (@style){
    if (!open(IN, $DIR . $file)) { die "le fichier $DIR$file n'existe pas";}
    open (IN, $DIR . $file);
    ($header_tmp = <IN>) =~ s/\n/\t/g;
    $header .= "\t $header_tmp" ;
  }
  close IN;
"copyright=gnu
docopen=yes
dlang=fr
tit=$tit
author=$aut
email=$mail
header=$header
datm=$datm";
}
#TODO en fait il faudrait renvoyer dans le cas ou le fichier est de type fold à la page en dessus
# dépliée. Je ne suis pas sure de savoir faire ! sinon, on perd la table des matières.

sub store_ref { my ($link, $titre, $anchor, $ref_bloc) = @_;
  my $txt = '' ;
  my @list = (split(',', $link)) ; 
  for my $l (@list) {
  dbg("... référence fichier: \"$l\" titre \"$l\"");
  my $page = $ref_bloc->{fichier}{$l} ;
  warn  "label $link n'existe pas" if !($page) ;
  $txt .= ($#list) ? " \\link{$page}{$l}{$anchor}":
             " \\link{$page}{$titre}{$anchor}";
 }
 $txt ;
};


#crée la page

sub toc_HTML {my ($text, $toc_g, $toc_d, $CHEMIN_up, $CHEMIN_down, $index) = @_ ;
  if (($toc_g) || ($toc_d)) {
    $CHEMIN_up . '<table class="doc_table"><tr>'
   . (($toc_g) ? '<td class="left_toc" id="left_toc">'. $toc_g 
   . $index . '</td>' : '')
   . '<td valign="top" align="left" width="100%"><div class="wimsdoc">'
   . $text
   . '</div>' .  $CHEMIN_down . ' </td>'
   . (($toc_d) ? '<td class="right_toc" id="right_toc">'
   . $toc_d
   . '<center>'
   . $LOAD
   . '</center></td>' : '') 
   . '</tr></table>'  }
   else {$CHEMIN_up . $text . $CHEMIN_down };
 }

 #################################

sub store_algo { my ($txt, $acc, $cmd, $comment, $indent) = @_ ;
  $txt .= " " . $acc ;
  $txt .= $hash_algo{titre}{$hash_algo{suite}{$cmd}} if  ($hash_algo{suite}{$cmd}) ;
  $indent = $indent + $hash_algo{avant}{$cmd} ;
  $txt = "\n" . indent($indent) .  $hash_algo{titre}{$cmd} . $txt  if ( !($cmd =~ /END/) || $algo_noend == 0);
  $txt .=  indent(3) . "{<i>$comment</i>}" if ($comment) ;
  $txt .= "\n" ;
  $txt =~ s/\n+/\n/ ;
  $indent += $hash_algo{apres}{$cmd} ;
  ($txt, $indent) ;
}

sub algorithm { '<div class="algorithm">' . algorithmic (@_) . '</div>' } ;

sub algorithmic { my ($Text) = @_;
  my $text ='' ; my $indent = 0 ;
  my @T = split('\n', $Text);
  for my $i (1..$#T) {
    my $ligne = $T[$i];
 #   $ligne =~ s/\$([^\$]+)\$/$1/g;
  #  $ligne =~ s/\\\(//g;
 #   $ligne =~ s/\\\)//g;
    $ligne =~ s/\$([^\$]+)\$/\\( $1 \\)/g;
    $ligne =~ s/^\[H\]//;
    next if ($ligne =~ /\\begin\{algorithmic\}\[1\]/);
    $ligne = "\n\n" if ($ligne =~ /\\end\{algorithmic\}/);
    $ligne =~ s/\\caption\s*\{\s*([^\}]*)\}/<h4 class=\"algo_titre\"> $1 <\/h4>/;
    $ligne =~ s/\\cdots/.../g;
    $ligne =~ s/\\geq/>=/g;
    $ligne =~ s/\\leq/<=/g;
    $ligne =~ s/\\bmod/mod/g;
#    $ligne =~ s/\[/<i>/g;
#    $ligne =~ s/\]/<\/i>/g;
    my $cle = 'FOR|WHILE|IF|UNTIL|ELSE|ELSIF|REQUIRE|ENSURE|STATE|ENDFOR|ENDWHILE|ENDIF' ;
    if ($ligne =~ /\s*\\($cle)\s*(\[[^\]]+\]*)?\{([^\n]+)\}\s*([^\n]*)/) {
         ($ligne,$indent) = store_algo($3, $4, $1, $2, $indent) ;
    }    
    if ($ligne =~ /\s*\\($cle)\s*(\[[^\]]+\]*)?\s*([^\n]*)/) {($ligne,$indent) = store_algo('',$3, $1, $2, $indent);}
  #TODO accepter des commentaires de plusieurs lignes ; présentation
    #des commentaires ?
    if ($ligne =~ /^\s*\\COMMENT/) { $ligne = "<i>$ligne</i>\n" };
    $text .= "\n" . $ligne;
    $text =~ s/\n{2,}/\n/g ;
    $text =~ s/\n+/<br>/g ;
    $text =~ s/(<br>)+/<br>/g ;
  }
  $text ;
}

sub indent { my $espace = "&nbsp;" x  6 ; $espace x $_[0]; }

sub Numero { my ($id) = @_;
  return '' if ($id =~ /F_[^S]\d/)  || ($id =~ /L_/); #cela ne provient pas d'une section et co
  $id =~ s /(F|L)_//g;
  $id =~ s/mainS(\d+)/&Roman($1)/e;
  $id =~ s/S(\d+)S(\d+)S(\d+)/-$1-$2-$3/;
  $id =~ s/S(\d+)S(\d+)/-$1-$2/;
  $id =~ s/S(\d+)/-$1/;
  $id;
}

# permet de faire modifier quelque chose dans la table pour un tag
#TODO j'ai rajouté l'option couleur, du coup je ne sais plus faire fonctionner le shif
sub selection { my ($text, $couleur, @tag) = @_ ;
  return '' if !defined($text);
  for my $ta (@tag) {
    $text =~ s/XXXX=$ta>/div class="$couleur">/g;
    $text =~ s/YYYY=$ta>/\/div>/g;
  };
  $text;
}

sub clean { my ($text, $ref) = @_;
  return '' if !defined($text);
   $text =~ s/<XXXX=\w*>//g;
   $text =~ s/<YYYY=\w*>//g;
   $text =~ s/ZZZZZ(\w+)/store_tip($1,$ref)/ge;
   $text;
}

sub store_tip { my ($tag,$ref)=@_ ; 
  my $tip = $ref->{toctip}{$tag} ;
  my $title=$ref->{tittoc}{$tag} ;
  $tip =~ s/'/\\\\'/g if ($tip) ; 
   $title =~ s/'/\\\\'/g if ($title) ; 
  $ref->{toctip}{$tag} ?  "<a onmouseover=\"Tip('$tip',TITLE,'$title',TITLEBGCOLOR,'',WIDTH,'200px')\" onmouseout=\"UnTip()\">$tooltip_prompt<\/a>" : '' ; 
}

sub chemin { my ($tag, $ref) = @_;
  my $tagsup = $tag;
  my $ch = $tag;
  my $txt = ($ref->{tittoc}{$tagsup}) ? $ref->{tittoc}{$tagsup} : $ref->{titb}{$tagsup} ;
  my $niv = 0;
  while ($tagsup !~ /^main\b/) {
    $niv++;
    $tagsup = $ref->{upbl}{$tagsup};
    $ch  = "$tagsup,$ch";
    $txt = "\\link{$tagsup}{$ref->{tittoc}{$tagsup}} $FLECHE $txt" ; #if ($tagsup !~ /^main\b/);
  }
  $ref->{chemin}{$tag} = $ch;
  $ref->{niveau}{$tag} = $niv;
  return $LOAD if (!$txt);
  '<div class="wims_chemin">' . $LOAD . "$linkout  $txt" . '</div>';}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}


sub isotime {
    my ($sec,$min,$hour,$mday,$mon,$year) = localtime(time);
    $year += 1900;
    $mon += 1 ; $mday += 1 ;
    $mday = sprintf("%02d", $mday);
    $mon  = sprintf("%02d", $mon);
    "$year-$mon-$mday $hour:$min:$sec";
}
 
 sub usage {
  print STDERR << "EOT"
latex2wims [--style=style.css] [--macro=wims.sty] [--dir=dossier1] [--docdir=dossier2] [--embed=dossier3] [--verbose] file

  --style=style.css : style.css fichier de style css à utiliser 
     (peut aussi être mis dans le fichier file : \\wimsinclude{style.css})
  --macro=wims.sty : wims.sty fichier de style à utiliser 
     (peut aussi être mis dans le fichier file : \\wimsinclude{wims.sty})
  --dir=dossier1 : dossier1 est le répertoire où se trouvent tous les fichiers dont le fichier file
  --docdir=dossier2 : dossier2 est le répertoire dans lequel sera créé le document 
     (un dossier dans le compte Modtool par exemple)
  --embed=dossier3 : les fichiers de dossier3 sont appelés dans file 
     par la commande \embed{} (pour expert) 
  --verbose : détails 
EOT
;
  exit 1;
}
 
##======================================================================##
## Adapted from work by OZAWA Sakuro <ozawa@prince.pe.u-tokyo.ac.jp>
## Copyright (c) 1995 OZAWA Sakuro.  All rights reserved.  This
## program is free software; you can redistribute it and/or modify
## it under the same terms as Perl itself.
##======================================================================##

sub Roman { my($arg) = shift;
  my %roman_digit = qw(1 IV 10 XL 100 CD 1000 MMMMMM);
  my @figure = reverse sort keys %roman_digit;
  grep($roman_digit{$_} = [split(//, $roman_digit{$_}, 2)], @figure);
  0 < $arg and $arg < 4000 or return undef;
  my($x, $roman);
  foreach (@figure) {
    my($digit, $i, $v) = (int($arg / $_), @{$roman_digit{$_}});
    if (1 <= $digit and $digit <= 3) {
      $roman .= $i x $digit;
    } elsif ($digit == 4) {
      $roman .= "$i$v";
    } elsif ($digit == 5) {
      $roman .= $v;
    } elsif (6 <= $digit and $digit <= 8) {
      $roman .= $v . $i x ($digit - 5);
    } elsif ($digit == 9) {
      $roman .= "$i$x";
    }
    $arg -= $digit * $_;
    $x = $i;
  }
  $roman
 }
