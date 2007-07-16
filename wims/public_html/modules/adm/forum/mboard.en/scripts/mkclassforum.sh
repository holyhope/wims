#! /bin/sh

forumdir=$w_Forumdir
mkdir -p $forumdir/.threads

today=`date '+%Y%m%d'`
cat <<@ >$forumdir/.def
!set mb_title=Class message board
!set mb_description=Here you can make discussions within the class.
!set mb_supervisor=$w_wims_supervisor
!set mb_email=$w_wims_supervisormail
!set mb_lang=en
!set mb_readpolicy=alluser
!set mb_sendpolicy=$w_cfm_send
!set mb_password=*
!set mb_creation=$today
!set mb_defined=yes
@

