#!/usr/bin/perl -w


use strict "vars";
use strict "subs";
use locale;
use warnings;
#$/ = undef;

my $warning1='is the first character of a delimiter but occurred as data';
my $warning2="info: line \$";
my $warning21=": character \"&\" is the first character of a delimiter but occurred as data";
my $DIR=".";
while ($_ = shift(@ARGV))
{
  last if (/^$/);
  if  (/^(.*)$/)   {$DIR=$1 }
}

my @Files = GetFilesList ($DIR);
foreach my $File  (@Files) {
	treate($File);
}

sub treate { my ($file)=@_;
  my $text='';
  open(IN,$file);
  while (<IN>) {
   next if (/$warning1/);
   next if (/$warning2\d+$warning21/);
   next if (/data-dropdown-menu/); #is not a member of a group specified for any attribute (html5)
   next if (/no attribute \"data/); #html5
   next if (/aria-label/);  #html5
   next if (/nav/);  #html5
   $text .= $_;
  }
  close IN;
  out($file, $text);
}


sub out { my ($bloc, $text) = @_;
  open  (OUT, ">$bloc") || warn "peut pas créer $bloc";
  print OUT $text; close OUT;
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
