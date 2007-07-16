#! /bin/sh

cd $w_wims_home/log/classes/$w_class
list=`ls -I supervisor .users`

for u in $list
do
 lastname=`awk -F '=' '/user_lastname/ {print $2}' .users/$u`
 firstname=`awk -F '=' '/user_firstname/ {print $2}' .users/$u`
 echo ":$lastname,$firstname,$u" >>.userlist.raw
done
sort -f .userlist.raw >.userlist
rm -f .userlist.raw >/dev/null

