
<script language=javascript>
!set srchl=!translate $ $ to + in $srchl
window.open("$wims_ref_name?wims_window=new&module=adm/enc.$lang&session=$(wims_session)_ref&job=search&dom=math&search=$srchl",
	"wims_ref","status=no,toolbar=no,location=no,menubar=no,scrollbars=yes");
</script>

!changeto wimshome/public_html/modules/adm/enc.$lang/welcome.phtml

