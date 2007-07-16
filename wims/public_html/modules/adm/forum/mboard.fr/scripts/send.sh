#! /bin/sh

forumdir=$w_Forumdir

if [ ! -d $forumdir/$w_month ]; then
 mkdir $forumdir/$w_month
fi

msgfile=$forumdir/$w_month/$w_ident
cat >$msgfile <<@
!set p_=!word 1 of \$wims_read_parm
!bound p_ within none,header,source,html default none
!goto \$p_
:none
!exit
:header
!set m_subject=$w_c_subject
!set m_date=$w_month$w_day
!set m_time=$w_time
!set m_from=$w_c_sender
!set m_sender_ip=$REMOTE_ADDR
!set m_sender_id=$w_wims_user
!set m_sender_class=$w_wims_class
!set m_email=$w_c_smail
!set m_to=
!set m_prec=$w_c_prec
!set m_exists=yes
!exit
:source
<pre>
@
sed 's/</\&lt;/g;s/!/\&#33;/g;s/:/\&#58;/g;s/\$/\&#36;/g' $session_dir/user-deposit >>$msgfile
cat >>$msgfile <<@
</pre>
!exit
:html
@
cat $session_dir/message.wims >>$msgfile
echo >>$msgfile <<@

!exit
@

