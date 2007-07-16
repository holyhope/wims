#! /bin/sh

forumdir=$w_Forumdir
mkdir -p $forumdir/.threads

today=`date '+%Y%m%d'`
cat <<@ >$forumdir/.def
!set mb_title=班级信息板
!set mb_description=你可在班级范围里在这儿讨论问题
!set mb_supervisor=$w_wims_supervisor
!set mb_email=$w_wims_supervisormail
!set mb_lang=cn
!set mb_readpolicy=alluser
!set mb_sendpolicy=$w_cfm_send
!set mb_password=*
!set mb_creation=$today
!set mb_defined=yes
@

