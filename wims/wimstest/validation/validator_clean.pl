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
my $option='';
while ($_ = shift(@ARGV))
{
  last if (/^$/);
  if (/^--option=(.*)$/)  { $option = $1}
  elsif  (/^--dir=(.*)$/)   {$DIR = $1 }
}
my @Files = GetFilesList ($DIR);
foreach my $File  (@Files) {
	treate($File);
	if($option==1){ treate2($File)};
}

sub treate { my ($file)=@_;
  my $text='';
  open(IN,$file);
  while (<IN>) {
   next if (/$warning1/);
   next if (/$warning2\d+$warning21/);
   next if (/data-dropdown/); #is not a member of a group specified for any attribute (html5)
   next if (/no attribute \"data/); #html5
   next if (/aria-label/);  #html5
   next if (/nav/);  #html5
   next if (/no attribute "autocompletion"/);
   next if (/no attribute "autocomplete"/);
   next if (/validating: test.html/);
   $text .= $_;
  }
  close IN;
  out($file, $text);
}

sub treate2 { my ($file)=@_;
  my $text='';
  open(IN,$file);
  while (<IN>) {
   next if (/start tag was here/);
   next if (/value of attribute "type" cannot be "search"/);
   next if (/there is no attribute "results"/);
   next if (/there is no attribute "placeholder"/);
   next if (/there is no attribute "name"/);
   next if (/there is no attribute "type"/);
   next if (/document type does not allow element "style" here/);
   next if (/document type does not allow element "div" here\s*END/); ## last in the result come from the debug
   next if (/document type does not allow element "link" here/);
   $text .= $_;
  }
  close IN;
  $text =~ s/line \d+://g;
  $text =~ s/END//g;
  $text =~ s/\n{2,}/\n/g;
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
