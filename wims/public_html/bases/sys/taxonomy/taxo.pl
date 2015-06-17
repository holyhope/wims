#!/usr/bin/perl
use strict "vars";
use strict "subs";
use search ('hashdomain', 'treate_dict', 'sortuniq', 'out', 'canonify', 'reverse_dic', 'treate_language');

use locale;
use warnings;
my $LANG='fr';
## leave simple quotes
my $joker='$wims_name_erase';
my $outputtaxo='../../modules/';
my $ddir='taxonomy';
my $indexdir="../classification";
my $sheetdir="../sheet";
my $moduledir="../site";
my ($module,$option)=('','');
while ($_ = shift (@ARGV))
{
  last if (!/^--/);
  if (/^--lang=(.*)$/) { $LANG = $1; }
  elsif (/^--joker=(.*)$/) { $joker = $1; }
  elsif (/^--module=(.*)$/) { $module = $1; }
  elsif (/^--option=(.*)$/) { $option = $1; }
  elsif (/^--output=(.*)$/) { $outputtaxo = "$outputtaxo/$1"; }
}

exit if (!(grep {$_ eq $LANG} treate_language()));

#### wims keywords
sub underscore { my ($a)=@_ ; $a=~ s/\_/ /g ; $a; }
## hack for suffix
sub suffix { my ($a)=@_ ; $a=~ s/(e|s|l|r)\b//; $a; }

sub count { my ($file)=@_ ;
 my $refcount={};
  open INC, "$file";
  while (<INC>){
   if (/^(.*):(.*)/) { my @L=split(' ', $2) ; $refcount->{$1}=$#L+1 }
  };
  close INC;
  $refcount
}

if ($option) {
 my $refcount= count("$moduledir/A.$LANG");
 ## initialisation, will not change
 my %refw = hashdomain('domain/domain') ; my $refw=\%refw;
 my %titw = treate_dict ("domain/domain.$LANG"); my $titw=\%titw;
 my (%Next); for my $a (keys %{$refw->{'next'}}) { $Next{$a}=$refw->{'next'}{$a}; }

 my $Tw;
 for my $taxo (split(',',$Next{'domain'})){
   if ( !(defined $titw{$taxo})) { $titw{$taxo}=$taxo} ;
   $Tw = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n"
     . '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>'
     . "\n!set title= $titw{$taxo}\n<h2>$titw{$taxo}<\/h2>\n"
     . '<ul id="tree_' .$taxo.'" class="tree">';
  One ($Next{$taxo}, $refcount, $taxo, $taxo);
  $Tw .= "\n</ul>";

  sub One { my ($t, $refcount, $taxo, $chemin) = @_;
    return if (!$t);
    for my $tt (split(',', $t)) {
      $Tw .= "<li  \n".
      "!if $tt notitemof \$parm\n".
      " class=\"closed\"\n".
      "!endif\n".
      ">\n";
      my $tt0=$titw->{$tt};
      if(!$tt0) { $tt0=$tt ; # print $tt ."\n" ;
      };
      my $chemin1 .= "$chemin,$tt" ;
      my $cc='';
      my $tt1=underscore($tt);
      my $T;
      if(defined($refcount->{$tt1})) {  $T=$refcount->{$tt1}}
        else { if (defined($refcount->{suffix($tt1)})) { $T= $refcount->{suffix($tt1)}}};
      if ($T) { $cc="<sup class=\"pastille taxo_nb_elem\">". $T."</sup>" };
      $Tw .= "<span class=\"tree_icon\" id=\"$tt\">$tt0</span><span class=\"small hidden\">($tt)</span>$cc\n"
          . "!set key=$tt0\n";
     # if ($T) {$Tw .= '!href $search_addr&parm=' . "$tt&browse_parm=$chemin1 &#128270; \$wims_name_search\n";}
      $Tw .= '!href $search_addr&parm=' . "$tt&browse_parm=$chemin1 &#128270; \$wims_name_search\n";
      $Tw .=  "<ul id=\"list_$tt\">";
      One($Next{$tt}, $refcount,$taxo, $chemin1);
      $Tw .= "\n</ul>";
    }
    $Tw .= "\n</li>";
 }
 out("$outputtaxo/taxo/$taxo.phtml.$LANG", $Tw);
 }
 exit;
}
####
## will not be modified in the subroutines
## LANG here must be a language for the moment
my %titsheet = treate_dict ("$sheetdir/index/tit.$LANG"); my $titsheet=\%titsheet;
my %addr = reverse_dic ("$moduledir/addr"); my $addr=\%addr;
my %titmodule = treate_dict ("$moduledir/title");my $titmodule=\%titmodule;

for my $t (glob("$ddir/*.$LANG")) {
  $t =~ s,$ddir\/,,g;
  my @t_=split('\.',$t); next if !($t_[1] eq $LANG);
  next if $t_[0] eq 'commoncore' ;
  taxonomy($t_[0], $LANG, '_','_',);
}

## impose order in the list
my $ccsstitle='CCSS.Math.Content_'; my @list=();
for my $l ('K','1','2','3','4','5','6','7','HS') { push @list, "$ccsstitle$l" }

taxonomy ("commoncore", $LANG, '_','_',@list);

sub taxonomy { my ($taxo, $lang, $sep1, $sep2,  @list) = @_ ;
   my $vu={}; my $ref; my $desctaxo;
   my ($title, $desc, $tit) = hashtaxo("$ddir/$taxo.$lang", $sep1, $sep2);
   my @title_ = split(',', $title);
   ($title,$desctaxo)=@title_;
   if (!(defined $desctaxo)) { $desctaxo='' };
   if ($module) { $ref=hashresultat("$indexdir/$taxo","$indexdir/$taxo" . "_sheet", $tit); }
   my ($T);
   $T = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n";
   $T .= '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>';
   $T .= "\n!set title=$title\n!set desctaxo=$desctaxo\n<h2>$title<\/h2>\n";
   $T .= '<ul id="tree_'.$taxo.'" class="tree">';
    if (!@list) { @list=sort keys %{$desc} };
   for my $a (@list) { $T .= one($a, $taxo, $desc, $tit, $ref, $vu); };
   $T .= "\n</ul>";
   if (!$module) {
     $T .= "<input type=\"radio\" name=\"taxon_$taxo\" id=\"empty\" value=\"\"/> $joker";
   }
   out("$outputtaxo/$taxo.phtml.$lang", $T);
}


sub one {my ($a, $taxo, $desc, $tit, $ref, $vu)=@_;
  return "" if (defined($vu->{$a}));
  $vu->{$a} = 1;
  my @prec=split('_',$a); my $prec0=join('_',@prec[0..$#prec-1]);
  my $amod = $a;
  my $T = '<li class="closed">';
  if (!$tit->{$a}) { print "warning $a has no title" ; $tit->{$a}=$a};
  if (!$ref->{'total'}{$a}) { $ref->{'total'}{$a}=0 } ;
  if (!$ref->{'totalexo'}{$a}) { $ref->{'totalexo'}{$a}=0 } ;
  if (!$module) {
       $T .= "<input type=\"radio\" name=\"taxon_$taxo\" id=\"$amod\" value=\"$amod\"/>"
          . "<label for=\"$amod\">$tit->{$a}</label> <span class=\"small hidden\">($a)</span>";
  } else {
    $T .= "<span class=\"tree_icon\" id=\"$amod\">$tit->{$a}</span> <span class=\"small hidden\">($a)</span> ";
    if ($ref->{'total'}{$a} >0){
      $T .= "<sup class=\"pastille taxo_nb_modules\">".$ref->{'total'}{$a}." \$name_M</sup>";
    }
    if ($ref->{'totalexo'}{$a} >0){
      $T .= "<sup class=\"pastille taxo_nb_exo\">".$ref->{'totalexo'}{$a}." \$name_X</sup>";
    }
  }
  if ($ref->{'text'}{$a} || $desc->{$a}){
    $T .="<ul id=\"list_$amod\">";
    if ($ref->{'text'}{$a}){ $T .=  $ref->{'text'}{$a}; }
    if ($ref->{'sheet'}{$a}){ $T .=  $ref->{'sheet'}{$a}; }
    if ($desc->{$a}) {
      for my $b (sortuniq (split ',', $desc->{$a})) { $T .= one($b, $taxo, $desc, $tit, $ref, $vu) };
    }
    $T .= "\n</ul>";
  }
  $T . "</li>";
}

sub hashtaxo { my ($file, $sep1, $sep2)=@_;
  my (%desc, %tit, $title);
  open IN, "$file";
  while (<IN>) {
##la premiere ligne est le titre !
    if (!$title) { $title=$_; next}
    my ($t0,$t1) = split(":", $_);
    my @index = split("$sep1", $t0);
    my $cnt = $#index;
    foreach my $a (2..$cnt) {
      $desc{join($sep2, @index[0..$a-1])} .= join($sep2, @index[0..$a]) . ",";
    }
    if ($t1) { $t1 =~ s/\n//; $tit{$t0} = $t1;}
  }
  close IN;
  ($title, \%desc, \%tit)
}

sub hashresultat { my ($file, $filesheet, $tit)=@_;
  my %ref;
  open IN, "$file";
  while (<IN>){
    my @ligne=split(':', $_);
    next if (!$ligne[0]);
    my @aa=sortuniq(split(',', $ligne[1]));
    my $cnt0=$#aa+1;
    my $cntexo=0;
    for my $a (@aa) {
      chomp $a;
      my $b = $a; $b =~ s!/!~!g;
      if (!defined($addr{$a})) {print "warning: module $a does not exist on the server\n"; next};
      if (!$titmodule->{$addr{$a}}) { print "$a\n" ; $titmodule->{$a}=$a};
      my $bb= ($titmodule->{$addr{$a}}) ? $titmodule->{$addr{$a}} . "<span class=\"small hidden\">($b)</span>": $b;
      my @exo; my $nb=1;
      if (-e "../../modules/$a/Extitles") {
        my %dic=treate_dict("../../modules/$a/Extitles");
        @exo= values %dic;
        $nb=$#exo;
      };
      ##jmevers test
      open INN, "../../modules/$a/INDEX";
      my $testjm=0;
      while (<INN>) { $testjm=1 if ($_=~ /authors\/jm.evers\/proc\/var.def/);} close INN;
      if ($testjm){
         my @nbexo=`ls ../../modules/$a/exos/exo*`;
         $nb=$#nbexo+1;
        ###TODO; creer @exo comme dans le cas OEF (liste des titres des exos)
      }
      if (@exo) {
        $nb=$#exo+1;
        $ref{'text'}{$ligne[0]} .="<li class=\"taxo_module closed\">\n" .
        "<span class=\"tree_icon\">$bb</span>"
        . ($nb>1?"<sup class=\"pastille taxo_nb_exo\">$nb \$name_X</sup>":"" )
        . "\n!set wims_ref_class=wims_button\n".
        "!href target=wims_internal module=$a &rArr;\n" .
        '<ul class="smaller"><li>' . join('</li><li>', @exo) . '</li></ul>'
        . "</li>\n";
        $cntexo += $nb ;
      }
      else {
        $ref{'text'}{$ligne[0]} .="<li class=\"taxo_module\">\n" .
        "!href target=wims_internal module=$a $bb\n"
        . ($nb>1?"<sup class=\"taxo_nb_exo\">$nb</sup>":"" )
        . "</li>\n";
        $cntexo += $nb ;
      }
    }
    $ref{'num'}{$ligne[0]}=$cnt0;
    $ref{'numexo'}{$ligne[0]}=$cntexo;
    $ref{'total'}{$ligne[0]}=0;
    $ref{'totalexo'}{$ligne[0]}=0;
  }
  close IN;
  if (-e "$filesheet") {
   open IN, "$filesheet";
   while (<IN>){
    my @ligne=split(':', $_);
    next if (!$ligne[0]);
    my @aa=sortuniq(split(',', $ligne[1]));
    my $cnt0=$#aa+1;
    for my $a (@aa) {
      chomp $a;
      my $b = canonify($a);
      if($titsheet->{$b}) { $b = $titsheet->{$b} . " <span class=\"small hidden\">($b)</span>" } else { $b =~ s!/!~!g;}
      $ref{'sheet'}{$ligne[0]} .="<li class=\"taxo_module\">\n"
   . "!href target=wims_internal module=adm/sheet\&+job=read\&+sh=$a $b\n </li>\n";
      }
   $ref{'numsheet'}{$ligne[0]}=$cnt0;
   }
  }
   my @modlist=sortuniq(keys %{$tit});
   for my $id (@modlist) {
     my @ok = grep {/^${id}_/} @modlist;
     push @ok, $id;
     for my $c (@ok) {
      if (!$ref{'num'}{$c}){ $ref{'num'}{$c}=0};
      if (!$ref{'numexo'}{$c}){ $ref{'numexo'}{$c}=0};
      if (!$ref{'numsheet'}{$c}){ $ref{'numsheet'}{$c}=0};
       $ref{'total'}{$id} += $ref{'num'}{$c} + $ref{'numsheet'}{$c} ;
       $ref{'totalexo'}{$id} += $ref{'numexo'}{$c} ;
     }
   }
   \%ref;
}

