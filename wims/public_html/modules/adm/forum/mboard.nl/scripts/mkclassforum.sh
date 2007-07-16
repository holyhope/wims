#! /bin/sh

forumdir=$w_Forumdir
mkdir -p $forumdir/.threads

today=`date '+%Y%m%d'`
cat <<@ >$forumdir/.def
!set mb_title=Het bulletin board
!set mb_description=Op deze plek kun je discussi&euml;ren met medeleerlingen of docenten.
!set mb_supervisor=$w_wims_supervisor
!set mb_email=$w_wims_supervisormail
!set mb_lang=nl
!set mb_readpolicy=alluser
!set mb_sendpolicy=$w_cfm_send
!set mb_password=*
!set mb_creation=$today
!set mb_defined=yes
@

