#! /bin/sh

cd $w_wims_home/$w_wims_sesdir
sdir=`pwd`
cldir=$w_wims_home/log/classes/$w_wims_class

rm -Rf getfile/class 2>/dev/null
mkdir -p getfile/class
cd $cldir
dirs=`ls -d version $w_dirs 2>/dev/null`
if [ ! -z "$dirs" ]; then
 cp -pRL $dirs $sdir/getfile/class
fi

# cp of user file when in superclass
if [ -n "$w_class_superclass" ]; then
 cd $w_wims_home/log/classes/$w_class_superclass/.users
 l=`grep user_participate=.*$w_tmpnum_class * | cut -d":" -f1 `;
 for f in $l; do cp $f $sdir/getfile/class/.users/; done;
fi
# end cp user

cd $sdir/getfile
echo $w_wims_class >class/serial

if [ $w_format = zip ]; then
 rm -f class.zip 2>/dev/null
 zip -r class.zip class >/dev/null
fi

if [ $w_format = tgz ] || [ $w_format = tar.gz ]; then
 tar -czf class.$w_format class >/dev/null
fi

ls -l class.$w_format | awk '{print $5}'
mv class.$w_format $w_fname.$w_format
rm -R class

