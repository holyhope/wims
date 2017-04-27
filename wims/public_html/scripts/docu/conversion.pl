#!/usr/local/bin/perl

use strict "subs";
use locale;
use warnings;
$/ = undef;
### most of these "mistakes" has been done by the Msg2wims
### should be better to correct it but more difficult !
my $file=$ARGV[0];
open (IN ,$file) ;
my $text = <IN>;
##multiple <p>
$text =~ s:(<p>\s*){2,}:<p>\n:g;
## close br and hr
$text =~ s:<(b|h)r>:<$1r/>:g;
$text =~ s:<p>\s*(<li>|</?ul>|</?ol>):\n$1\n:g;
## delete <p> before <li><ul><ol>
$text =~ s:<br ?/?>\s*(<li>|</?ul>|</?ol>):\n$1\n:g;
## delete <li> empty
$text =~ s:<li>\s*</(u|o)l>:</$1l>:g;
## transform some hr
$text =~ s|<hr\s+width="(\d+)%"\s*/?/>|<hr style="width:$1%"/>|g;
## delete <br/> before table ?
$text =~ s|<br ?/></table>|</table>|g;
## delete multiple <br>
$text =~ s:(<br ?/>\s*)+:<br/>\n:g;
$text =~ s:</div>\s+</div>:</div>\n</div>:g;
$text =~ s:</div>\s*<br/>\s*</div>:</div>\n</div>:g;
close(IN);

open (OUT, ">$file");
print OUT $text ; close OUT;
