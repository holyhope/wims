#!/usr/bin/perl
##example classes

use warnings;
use strict;
use search ('out', 'sortuniq', 'hashdomain', 'treate_accent', 'treate_dict');

my $dir='../../../log/classes/';
my $dirdomain='domain';
## list of all domains in domain/domain
my %ref= ();
my $ref=\%ref;
my @list=listclass();
my $dirout="../class";
$ref=refclass(@list);
my @Key = ('supervisor','domain','level','lang','institution','description','addr','keywords','title', 'information');
my @Lang= ('fr','en','it','nl');
my %T = ('version' => 'version',
'lang' => 'language',
'description' => 'title',
'supervisor' => 'author',
'institution' => 'description',
'level' => 'level',
'information' => 'information',
);
my %keywords=();

for my $key (@Key) {
  my $text='';
  for my $cl (@list) {
    $text .=  "$cl:";
    $text .= $ref{$cl}{$key} if ($ref{$cl}{$key});
    $text .= "\n";
  };
  out("$dirout/$T{$key}",join("\n",sort( split("\n", $text)))) if ($T{$key});
}
for my $l (@Lang) { my $text='';
  my %dom = treate_dict ("$dirdomain/domain.$l");
  my $dom = \%dom;
  for my $cl (@list) {
    next if (!($ref{$cl}{'lang'} =~ /$l/));
    next if (!$ref{$cl}{'keywords'});
    $ref{$cl}{'keywords'}=lc(treate_accent($ref{$cl}{'keywords'}));
    for my $k (sortuniq(split(', *',$ref{$cl}{'keywords'}))) {
      $k =treate_accent($k);
      if ($keywords{$k}) { $keywords{$k} .= " " . $cl  } else { $keywords{$k} = $cl};
      next if !($dom{$k});
      my $d=lc(treate_accent($dom{$k}));
      if ($keywords{$d}) { $keywords{$d} .= " " . $cl  } else { $keywords{$d} = $cl};
    }
    for my $k (split(',',$ref{$cl}{'domain'})) {
      if ($keywords{$k}) { $keywords{$k} .= " " . $cl  } else { $keywords{$k} = $cl};
       next if !($dom{$k});
       my $d=lc(treate_accent($dom{$k}));
      if ($keywords{$d}) { $keywords{$d} .= " " . $cl  } else { $keywords{$d} = $cl};
  }
 }
   while ( my ($key, $value) = each (%keywords) ) {
     my $v = join(" ", sortuniq(split(" ",$value)));
     $text .= "$key:$v\n";
   }
   $text =~ s / +(\w+:)/ $1/g;
   out("$dirout/$l", join("\n", sortuniq(split("\n",$text))));
}

###############################
sub refclass { my @L=@_;
  for my $cl (@L) {
    open IN, "$dir/$cl/.def";
    while(<IN>) {
    if ($_ =~ /!set class_(\w+)=\s*(.*)/) {
    my $f = $1; my $r= $2;
     if ($f =~ /\blevel/) {
        $r=~ s/ //g;
        if( $r) { $ref{$cl}{$f}= "level" . join(', level', split(',',$r));}
       }
       else { $ref{$cl}{$1}=$2;}}
       }
    close IN;
  }
}

sub listclass {
 my @L= ();
 for my $cl (glob("$dir/*")) {
   $cl=~s /$dir\///;
   push @L, $cl if (!($cl =~ /[A-Z]+/) && $cl < 10000);
  }
  @L
}
