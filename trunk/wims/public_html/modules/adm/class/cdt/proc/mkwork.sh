#! /bin/sh
if [ "$w_cdt_supervise" = "yes" ]; then
 ls $w_wims_home/log/classes/$w_wims_class/cdt/def | awk -v dir=$w_wims_class -v end=$w_jour_end -v begin=$w_jour_begin '$0<=end && $0>=begin{print $0","dir;}' | sort | head -c 15000;
else
 rm -f $w_wims_home/sessions/$w_wims_session/tmp;
 for i in $w_courses; do
  name=`awk -F'=' '$1=="!set class_description" {print $2; exit}' $w_wims_home/log/classes/$w_class_parent/$i/.def`;
  ls $w_wims_home/log/classes/$w_wims_class/$i/cdt/def | awk -v dir=$w_wims_class/$i -v end=$w_jour_end -v begin=$w_jour_begin -v name="$name" '$0<=end && $0>=begin{print $0","dir","name;}' >>$w_wims_home/s2/$w_wims_session/tmp;
 done;
 cat $w_wims_home/s2/$w_wims_session/tmp | sort | head -c 15000;
 rm -f $w_wims_home/s2/$w_wims_session/tmp;
fi;