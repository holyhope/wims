#! /bin/sh

forumdir=$w_Forumdir
mkdir -p $forumdir/.threads

today=`date '+%Y%m%d'`
cat <<@ >$forumdir/.def
!set mb_title=Forum di discussione del corso
!set mb_description=Qui è possibile discutere con gli altri studenti del corso.
!set mb_supervisor=$w_wims_supervisor
!set mb_email=$w_wims_supervisormail
!set mb_lang=it
!set mb_readpolicy=alluser
!set mb_sendpolicy=$w_cfm_send
!set mb_password=*
!set mb_creation=$today
!set mb_defined=yes
@

