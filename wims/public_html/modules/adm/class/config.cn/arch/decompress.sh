#! /bin/sh

cd $w_wims_home/$w_wims_sesdir
cldir=$w_wims_home/log/classes/$w_wims_class

rm -Rf upload 2>/dev/null
mkdir -p upload
cd upload
mv ../user-deposit $w_wims_deposit

if [ $w_format = zip ]; then
 unzip $w_wims_deposit
fi

if [ $w_format = tgz ] || [ $w_format = tar.gz ]; then
 tar -xzf $w_wims_deposit
fi

rm -f $w_wims_deposit
find . ! \( -type f -o -type d \) -exec rm -f '{}' \;
find . -type f -exec chmod a-x,og-w '{}' \;

