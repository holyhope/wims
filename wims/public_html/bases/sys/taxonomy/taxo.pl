#!/usr/bin/perl
use strict "vars";
use strict "subs";
use search ('hashdomain', 'treate_dict', 'sortuniq', 'out', 'canonify', 'reverse_dic');

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

#### wims keywords
if ($option) {
 my ($taxobase,$title,$Tw)=('keywords','','');
 my %refw = hashdomain('domain/domain') ; my $refw=\%refw;
 my %titw = treate_dict ("domain/domain.$LANG"); my $titw=\%titw;
 my (%A);
 for my $a (keys %{$refw->{'next'}}) { $A{$a}=$refw->{'next'}{$a}; }
 for my $taxo (split(',',$A{'domain'})){
   $Tw = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n"
     . '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>'
     . "\n!set title= $titw{$taxo}\n<h2>$titw{$taxo}<\/h2>\n"
     . '<ul id="tree_' .$taxo.'" class="tree">';
  One ($A{$taxo});
  $Tw .= "\n</ul>";

  sub One {
    my ($t) = @_;
   if ($t) {
     for my $tt (split(',', $t)) {
      $Tw .= '<li class="closed">';
      my $tt0=$titw->{$tt};
      if(!$tt0) { $tt0=$tt ; print $tt ."\n" ;};
      $Tw .= "<span id=\"$tt\">$tt0</span><span class=\"small hidden\">($tt)</span>\n"
            . "!set key=$tt0\n"
            . '!href $search_addr' . " >>>>\n"
            . "<ul id=\"list_$tt\">";
      One($A{$tt});
         $Tw .= "\n</ul>";
     }
     $Tw .= "\n</li>";
   }
 }
 out("$outputtaxo/taxo/$taxo.phtml.$LANG", $Tw);
 }
 exit;
}
####
## will not be modified in the subroutines
my %titsheet = treate_dict ("$sheetdir/index/tit.$LANG"); my $titsheet=\%titsheet;
my %addr = reverse_dic ("$moduledir/addr"); my $addr=\%addr;
my %titmodule = treate_dict ("$moduledir/title");my $titmodule=\%titmodule;

taxonomy("unisciel", $LANG, '_','_',);

## impose order in the list
my $ccsstitle='CCSS.Math.Content_'; my @list=();
for my $l ('K','1','2','3','4','5','6','7','HS') { push @list, "$ccsstitle$l" }

taxonomy ("commoncore", $LANG, '_','_',@list);

sub taxonomy { my ($taxo, $lang, $sep1, $sep2,  @list) = @_ ;
   my $vu={}; my $ref;
   my ($title, $desc, $tit) = hashtaxo("$ddir/$taxo.$lang", $sep1, $sep2);
   if ($module) { $ref=hashresultat("$indexdir/$taxo","$indexdir/$taxo" . "_sheet", $tit); }
   my ($T);
   $T = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n";
   $T .= '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>';
   $T .= "\n!set title=$title\n<h2>$title<\/h2>\n";
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
  if (!$tit->{$a}) { print "$a" ; $tit->{$a}=$a};
  if (!$ref->{'total'}{$a}) { $ref->{'total'}{$a}=0 } ;
  if (!$module) {
       $T .= "<input type=\"radio\" name=\"taxon_$taxo\" id=\"$amod\" value=\"$amod\"/>"
          . "<label for=\"$amod\">$tit->{$a}</label><span class=\"small hidden\">($a)</span>";
  } else {
    $T .= "<span id=\"$amod\">$tit->{$a}</span> <span class=\"small hidden\">($a)</span> ";
    if ($ref->{'total'}{$a} >0){
      $T .= "<sup class=\"taxo_nb_elem\">".$ref->{'total'}{$a}."</sup>";
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
    if ($t1) { $t1 =~ s/\n//; $tit{$t0} = $t1; }
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
    for my $a (@aa) {
      chomp $a;
      my $b = $a; $b =~ s!/!~!g;
      if (!$titmodule->{$addr{$a}}) { print "$a\n" ; $titmodule->{$a}=$a};
      my $bb= ($titmodule->{$addr{$a}}) ? $titmodule->{$addr{$a}} . "<span class=\"small hidden\">($b)</span>" : $b;
      if (-e "../../modules/$a/Extitles") {
        my %dic=treate_dict("../../modules/$a/Extitles");
        my @exo= values %dic;
        $ref{'text'}{$ligne[0]} .="<li class=\"taxo_module closed\">\n" .
        "!href target=wims_internal module=$a $bb\n" .
        '<ul class="smaller"><li>' . join('</li><li>', @exo) . '</li></ul>'
        . "</li>\n";
      }
      else {
        $ref{'text'}{$ligne[0]} .="<li class=\"taxo_module\">\n" .
        "!href target=wims_internal module=$a $bb\n </li>\n";
      }
    }
    $ref{'num'}{$ligne[0]}=$cnt0;
    $ref{'total'}{$ligne[0]}=0;
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
   my @modlist=sortuniq(keys $tit);
   for my $id (@modlist) {
     my @ok = grep {/^${id}_/} @modlist;
     push @ok, $id;
     for my $c (@ok) {
      if (!$ref{'num'}{$c}){ $ref{'num'}{$c}=0};
      if (!$ref{'numsheet'}{$c}){ $ref{'numsheet'}{$c}=0};
       $ref{'total'}{$id} += $ref{'num'}{$c} + $ref{'numsheet'}{$c} ;
     }
   }
   \%ref;
}
