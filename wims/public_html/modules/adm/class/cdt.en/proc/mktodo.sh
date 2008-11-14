#! /bin/sh
if [ "$w_cdt_supervise" = "yes" ]; then
 cat $w_wims_home/log/classes/$w_wims_class/cdt/index | awk -F"," -v dir=$w_wims_class -v jourb=$w_jour_begin -v joure=$w_jour_end '$1>=jourb && $1<=joure {print $0","dir;}' | sort | head -c 15000;
else 
 rm -f $w_wims_home/sessions/$w_wims_session/tmp;
 for i in $w_courses; do
  name=`awk -F'=' '$1=="!set class_description" {print $2; exit}' $w_wims_home/log/classes/$w_class_parent/$i/.def`;
  cat $w_wims_home/log/classes/$w_wims_class/$i/cdt/index | awk -F"," -v dir=$w_wims_class/$i -v name="$name" -v jourb=$w_jour_begin -v joure=$w_jour_end '$1>=jourb && $1<=joure {print $0","dir","name;}'>>$w_wims_home/s2/$w_wims_session/tmp;
 done;
 cat $w_wims_home/s2/$w_wims_session/tmp | sort | head -c 15000;
 rm -f $w_wims_home/s2/$w_wims_session/tmp;
fi;