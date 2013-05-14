#!/usr/bin/perl

use warnings;
use strict;

my $dirform="form";
my $dirdic="dic";
my %list=();
my $list=\%list;
my @Keywords=();
my @Files = GetFilesList ($dirform);
foreach my $File  (@Files) {
	next if !($File =~ /.def\b/) ;
	my @l=treate_keywords($File);
	push @Keywords, @l;
}
@Keywords=sortuniq(@Keywords);
out("$dirdic/form.json", "\"" .join("\",\n\"", @Keywords) . "\",");

my @text=();
while ( my ($key, $value) = each (%list) ) {
     push @text, "$key:$value" ; }
###il faut sorter  
out("$dirdic/form", join("\n",sortuniq(@text)));

sub treate_keywords { my ($file) = @_ ;
   my $t=0; my $t1=0; my @keywords=();
   my $file1 = $file ; $file1=~ s,$dirform/(.*)\.def,$1,;
    open IN, $file;
    while(<IN>) {
     my $k = $_ ;
     if( ($k =~ /^:/) && $t==0 && $t1==0) {
      $t = 1; $k =~ s/://; 
      push @keywords,split(", *",lc($k)) ;
     }
     if( !($k =~ /^:/) && $t==1 && $t1==0) {
      push @keywords,split(", *",lc($k)) ;
     }
     if( ($k =~ /^:/) && $t==1 ) {$t1=1}
    }
    for my $k (@keywords) { chomp $k;
     next if !($k); 
    if (!$list{$k}) { $list{$k} .= $file1 ." "; } else {$list{$k} .= $file1 . " " };
    }
    close IN;
   @keywords;
   
   
}

sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") ;
  print OUT $text ; close OUT;
}


sub sortuniq {
  my $prev = "not $_[0]";
  grep { $_ ne $prev && ($prev = $_, 1) } sort @_;
}

sub GetFilesList
{
        my $Path = $_[0];
        my $FileFound;
        my @FilesList=();

        # Lecture de la liste des fichiers
        opendir (my $FhRep, $Path)
                or die "Impossible d'ouvrir le repertoire $Path\n";
        my @Contenu = grep { !/^\.\.?$/ } readdir($FhRep);
        closedir ($FhRep);

        foreach my $FileFound (@Contenu) {
                # Traitement des fichiers
                if ( -f "$Path/$FileFound") {
                        push ( @FilesList, "$Path/$FileFound" );
                }
                # Traitement des repertoires
                elsif ( -d "$Path/$FileFound") {
                        # Boucle pour lancer la recherche en mode recursif
                        push (@FilesList, GetFilesList("$Path/$FileFound") );
                }

        }
        return @FilesList;
}



