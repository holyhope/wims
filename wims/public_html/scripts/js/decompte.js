<SCRIPT LANGUAGE="JavaScript">

//Created by Fabrice Guerimand

function decompte(temps) {
i1 = new Image(); i1.src = "gifs/lcdigit/1.gif";
i2 = new Image(); i2.src = "gifs/lcdigit/2.gif";
i3 = new Image(); i3.src = "gifs/lcdigit/3.gif";
i4 = new Image(); i4.src = "gifs/lcdigit/4.gif";
i5 = new Image(); i5.src = "gifs/lcdigit/5.gif";
i6 = new Image(); i6.src = "gifs/lcdigit/6.gif";
i7 = new Image(); i7.src = "gifs/lcdigit/7.gif";
i8 = new Image(); i8.src = "gifs/lcdigit/8.gif";
i9 = new Image(); i9.src = "gifs/lcdigit/9.gif";
i0 = new Image(); i0.src = "gifs/lcdigit/0.gif";
bl = new Image(); bl.src = "gifs/zero.gif";

mille = temps /1000;
mille2 = Math.floor(mille);
cent = (temps - 1000 * mille2) / 100;
cent2 = Math.floor(cent);
dix = (temps -1000 * mille2 - 100 * cent2) / 10;
dix2 = Math.floor(dix);
un = (temps -1000 * mille2 -100 *cent2 -10 *dix2);
un2 = Math.round(un);

document.images.cptu.src = eval("i"+un2+".src");
if(temps>9){document.images.cptd.src = eval("i"+dix2+".src");} else {document.images.cptd.src = eval("bl.src");}
if(temps>99){document.images.cptc.src = eval("i"+cent2+".src");} else {document.images.cptc.src = eval("bl.src");}
if(temps>99){document.images.cptm.src = eval("i"+mille2+".src");} else {document.images.cptm.src = eval("bl.src");}
temps2=temps-1;
if(temps2<0){temps2=0;}

window.setTimeout("decompte(temps2);", 1000 );
}
</script>

!set wims_html_onload=decompte($wims_read_parm);
