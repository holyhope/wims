#!/usr/bin/perl


## validator file validator_uri
my $file = shift(@ARGV);
my $uri = shift(@ARGV);
if ($uri =~ /http/) {
  use WebService::Validator::HTML::W3C;
   my $v = WebService::Validator::HTML::W3C->new(detailed => 1);
    $v->validator_uri($uri);
}
{
  use WebService::Validator::HTML::W3C::Fast;
  my $v = WebService::Validator::HTML::W3C::Fast->new("detailed" => 1, validator_path  => '$uri');
}
 if ( $v->validate_file("$file") ) {
   if ( !$v->is_valid )
   {
     foreach my $E (@{$v->errors}) {
       ##next if ($E->msg =~ /not allowed in prolog/);
       next if ($E->msg =~ /Conflict between Mime Type/); #error coming from last.html
       next if ($E->msg =~ /xmlParseEntityRef/); #error I do not understand, link with &
       printf("\$wims_name_Error: line %d, %s\n", $E->line, $E->msg);
     }
     foreach my $E (@{$v->warnings}) {
       next if ($E->msg =~ /character "(&amp;|&)" is the first character of a delimiter but occurred as data/);  ##due to wims
       next if ($E->msg =~ /Conflict between Mime Type/);  #error coming from last.html
       next if ($E->msg =~ /xmlParseEntityRef/); #error I do not understand, link with &
       printf("\$wims_name_warning: line %d, %s\n", $E->line, $E->msg);}
   }
 } else {
     printf ("Failed to validate the validator $v->uri : %s\n", $v->validator_error);
 }
