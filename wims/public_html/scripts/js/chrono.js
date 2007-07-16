
<script language=javascript>
var rtick;
rtick=$wims_read_parm;
function clock() {
 document.chrono.clock.value=rtick; rtick--;
 if(rtick<0) rtick=0;
 Timer= setTimeout("clock()",1000);                    
}                   
</script>
!set wims_html_onload=clock();

