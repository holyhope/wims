#!/usr/bin/perl
##example classes

use warnings;
use strict;

my $dir='../../../log/classes/';
## list of all domains in domain/domain
my %ref= ();
my $ref=\%ref;
my @list=listclass();
my $dirout="../class";
$ref=refclass(@list);
my @Key = ('supervisor','domain','level','lang','institution','description',"addr",'keywords','title');
my @Lang= ('fr','en','it','nl') ; 
my %T = ('version' => 'version',
'lang' => 'language',
'institution' => 'title',
'supervisor' => 'author',
'description' => 'description',
'level' => 'level',
);
my %keywords=();

for my $key (@Key) {
  my $text='';
  for my $cl (@list) {
    $text .=  "$cl:"; 
    $text .= $ref{$cl}{$key} if ($ref{$cl}{$key});
    $text .= "\n";
  };
  out("$dirout/$T{$key}",join("\n",sort( split("\n", $text)))) if ($T{$key}) ; 
}
for my $l (@Lang) { my $text='';
  for my $cl (@list) { 
    next if (!($ref{$cl}{'lang'} =~ /$l/)) ;
    for my $k (split(',',$ref{$cl}{'keywords'})) {
      if ($keywords{$k}) { $keywords{$k} .= " " . $cl  } else { $keywords{$k} = $cl};
    }
    for my $k (split(',',$ref{$cl}{'domain'})) {
      if ($keywords{$k}) { $keywords{$k} .= " " . $cl  } else { $keywords{$k} = $cl};
    }
 }
   while ( my ($key, $value) = each (%keywords) ) {
     $text .= lc("$key:$value\n") ; 
   }
   $text =~ s / +(\w+:)/$1/g;
   out("$dirout/$l", join("\n", sortuniq(split("\n",$text)))); 
}

sub refclass { my @L=@_ ; 
  for my $cl (@L) {
    open IN, "$dir/$cl/.def";
    while(<IN>) {
    if ($_ =~ /!set class_(\w+)=\s*(.*)/) { $ref{$cl}{$1}=$2 ;}}
    close IN;
  }
}

sub listclass { 
 my @L= () ;
 for my $cl (glob("$dir/*")) {
   $cl=~s /$dir\/// ; 
   push @L, $cl if (!($cl =~ /[A-Z]+/) && $cl < 10000) ;
  }
  @L
}
sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}

sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}
