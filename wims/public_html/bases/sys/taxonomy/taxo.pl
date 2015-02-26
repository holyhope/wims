#!/usr/bin/perl
use strict "vars";
use strict "subs";
use search ('hashdomain', 'treate_dict');

use locale;
use warnings;
my $LANG='fr';
## leave simple quotes
my $joker='$wims_name_erase';
my $outputtaxo='../../modules/';
my $ddir='taxonomy';
my $indexdir="../classification";
my $module='';
my $option='';
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
 my ($taxo,$title,$Tw)=('keywords','WIMS','');
 my %refw = hashdomain('domain/domain') ; my $refw=\%refw;
 my %titw = treate_dict ("domain/domain.$LANG"); my $titw=\%titw;
 my (%A);
 for my $a (keys %{$refw->{'next'}}) { $A{$a}=$refw->{'next'}{$a}; }

 $Tw = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n"
     . '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>'
     . "\n!set title=$title\n<h2>$title<\/h2>\n"
     . '<ul id="tree_' .$taxo.'" class="tree">';

 One ($A{'domain'});
 $Tw .= "\n</ul>";

 sub One {
   my ($t) = @_;
   if ($t) {
     for my $tt (split(',', $t)) {
      $Tw .= '<li class="closed">';
      my $tt0=$titw->{$tt};
      $Tw .= "<span id=\"$tt\">$tt0</span>\n"
            . "!set key=$tt0\n"
            . '!href $search_addr' . " >>>>\n"
            . "<ul id=\"list_$tt\">";
      One($A{$tt});
         $Tw .= "\n</ul>";
     }
     $Tw .= "\n</li>";
   }
 }

 out("$outputtaxo/$taxo.phtml.$LANG", $Tw);
 exit;
}
####

taxonomy("unisciel", $LANG, '_','_',);

my $ccsstitle='CCSS.Math.Content_';
taxonomy ("commoncore", $LANG, '_','_',
 ($ccsstitle . 'K',$ccsstitle . '1',$ccsstitle . '2',
 $ccsstitle . '3',$ccsstitle . '4',$ccsstitle . '5',
 $ccsstitle . '6',$ccsstitle . '7',$ccsstitle . 'HS'));

my (%vu,%tit,%desc,$ref,@list);
sub taxonomy { my ($taxo, $lang, $sep1, $sep2) = @_ ;
   my ($title, %desc) = hashtaxo("$ddir/$taxo.$lang", $sep1, $sep2);
   if ($module) { my %ref=hashresultat("$indexdir/$taxo"); $ref=\%ref; }
   my ($T);
   $T = "!! This file is generated by taxo.pl. Do not modify directly \n!set lang_exists=yes\n";
   $T .= '<a class="wims_button float_right" onclick="treeToggleAll(\'#tree_'.$taxo.'\');">$name_fold</a>';
   $T .= "\n!set title=$title\n<h2>$title<\/h2>\n";
   $T .= '<ul id="tree_'.$taxo.'" class="tree">';
   @list=sort keys %desc;
   for my $a (@list) { $T .= one($a, $taxo) ; };
   $T .= "\n</ul>";
   if (!$module) {
     $T .= "<input type=\"radio\" name=\"taxon_$taxo\" id=\"empty\" value=\"\"/> $joker";
   }
   out("$outputtaxo/$taxo.phtml.$lang", $T);
}


sub one {my ($a, $taxo)=@_;
  return "" if (defined($vu{$a}));
  $vu{$a} = 1;
  my @prec=split('_',$a); my $prec0=join('_',@prec[0..$#prec-1]);
  my ($amod) = $a;
  my ($T) = '<li class="closed">';
  if (!$tit{$a}) { print "$a\n" ; $tit{$a}=$a};
  if (!$ref->{'total'}{$a}) { $ref->{'total'}{$a}=0 } ;
  if (!$module) {
       $T .= "<input type=\"radio\" name=\"taxon_$taxo\" id=\"$amod\" value=\"$amod\"/>"
          . "<label for=\"$amod\">$tit{$a}</label><span class=\"small hidden\">($a)</span>";
  } else {
    $T .= "<span id=\"$amod\">$tit{$a}</span> <span class=\"small hidden\">($a)</span> ";
    if ($ref->{'total'}{$a} >0){
      $T .= "<sup class=\"taxo_nb_elem\">".$ref->{'total'}{$a}."</sup>";
    }
  }
  if ($ref->{'text'}{$a} || $desc{$a}){
    $T .="<ul id=\"list_$amod\">";
    if ($ref->{'text'}{$a}){ $T .=  $ref->{'text'}{$a}; }
    if ($desc{$a}) {
      for my $b (sortuniq (split ',', $desc{$a})) { $T .= one($b, $taxo) };
    }
    $T .= "\n</ul>";
  }

  # if ($ref->{'text'}{$a}){ $T .= "\n\n\n</div>";}
  $T . "</li>";
}

sub hashtaxo { my ($file, $sep1, $sep2)=@_;
  open IN, "$file";
  my $title;
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
  ($title, %desc, %tit)
}

sub hashresultat { my ($file,@list)=@_;
  my %ref; my $ref=\%ref;
  open IN, "$file";
  while (<IN>){
    my @ligne=split(':', $_);
    next if (!$ligne[0]);
    my @aa=split(',', $ligne[1]);
    my $cnt0=$#aa+1;
    #$ref->{'text'}{$ligne[0]} = "<ul class=\"module_list\" >";
    for my $a (@aa) {
      chomp $a;
      my $b = $a; $b =~ s!/!~!g;
      $ref->{'text'}{$ligne[0]} .="<li class=\"taxo_module\">\n!href target=wims_internal module=$a $b\n</li>\n"
    }
    #$ref->{'text'}{$ligne[0]} .= "</ul>";
    $ref->{'num'}{$ligne[0]}=$cnt0 ;
    $ref->{'total'}{$ligne[0]}=0;
  }
  my @modlist=sort keys %tit;
   for my $id (@modlist) {
     my @ok = grep {/^${id}_/} @modlist;
     push @ok, $id;
     for my $c (@ok) {
      if (!$ref->{'num'}{$c}){ $ref->{'num'}{$c}=0};
       $ref->{'total'}{$id} += $ref->{'num'}{$c};
     }
   }
   %ref;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}


sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") || die "cannot create $bloc";
  print OUT $text ; close OUT;
}
