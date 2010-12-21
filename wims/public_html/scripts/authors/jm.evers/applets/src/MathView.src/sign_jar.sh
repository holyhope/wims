#!/bin/sh

# used for signing home_compiled new java-jars
echo "Your name is..."
read myname
echo "make sure the jar's to sign are in THIS directory"

mykey="~/.keystore"

if [ ! -e $mykey ] ; then
    keytool -genkey -alias $myname
else
    echo ".keystore file exists"
fi

if [ !- e $myname.x509 ] ; then
    keytool -export -alias $myname -rfc -file $myname.x509
else
    echo "$myname.x509 file exists"
fi
    
for i in `ls *.jar` ; do
    jarsigner $i $myname
done
