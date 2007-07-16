#! /bin/sh

PWD=`pwd`
HOME=`echo $PWD | sed 's!/public_html$!!'`

cat <<1
Status: 503 Server uncompiled
Content-type: text/html


WIMS (WWW Interactive Multipurpose Server) needs to be recompiled!
<p>

Webmaster: please recompile the WIMS server.
(Go to $HOME, and type \`./compile'.)

1

