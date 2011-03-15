#! /bin/sh

cd ..
i=`id -un`
find $wims_exec_parm \! -user $i | head -60 | grep -v '^chroot/usr/bin/\[$'

## cherche dans les répertoires $wims_exec_parm les fichiers n'appartenant pas à l'utilisateur
##courant. Se restreindre aux 60 premiers et ne pas tenir compte  du fichier [ de chroot/usr/bin