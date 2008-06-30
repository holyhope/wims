!if $plaatje=
    !set plaatje=insert1-gif
!endif

!if $LINKTEXT=
    !set LINKTEXT=replay
!endif

<script type="text/javascript">

<!-- function NieuwPlaatje() { MijnVenster = window.open("wims.cgi?&session=$session&module=$module&cmd=getins&special_parm=$plaatje", "$voornaam $achternaam", "width=$XSIZE,height=$YSIZE,left=0,top=0"); MijnVenster.focus();  }
     function Wegwezen() { onclick=window.close("cerrar esta ventana") }

//-->

</script>

<a href="javascript:NieuwPlaatje()">

<B>$LINKTEXT</B>

</a>


