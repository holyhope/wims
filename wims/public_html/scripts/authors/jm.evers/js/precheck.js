// 3/05/2008 version 0.02 [added item 10]

//  1 check_s(t)		checks scientiffic notation 4e+4 --> 4*10^4	: returns modified t
//  2 check_o(t)		checks letter o instead of number 0		: returns 0 or 1		
//  3 check_f(t)		checks parenthesis usage in functions sin()	: returns 0 or 1	
//  4 check_x(t)		checks usage of x as multiplication *		: returns 0 or 1
//  5 specialroot(t)		converts sqrt[a](b) to b^(1/a)			: returns modified t
//  6 speciallog(t)		converts log[a](b) to log(b)/(log(a))		: returns modified t
//  7 nthroot(t)		converts root(b,a) to b^(1/a)			: returns modified t
//  8 check_log_NaN(t)		checks negative numbers in log			: returns 0 or 1
//  9 check_sqrt_NaN(t)		checks negative numbers in sqrt			: returns 0 or 1
// 10 normalize(t)		converts accents to letters without...		: reurns modified t


function check_s(t){
    var org=t;
    t=t.replace(/\*\*/g,'^'); 
    t=t.replace(/x10/g,'*10')
    e=t.indexOf('e');
    cc=['0','1','2','3','4','5','6','7','8','9'];
    var c0;var c1;var t0;var t1;var c;var a;var trouble=0;
    while(e!=-1){
	t0=t.charAt(e-1);
	t1=t.charAt(e+1);
	t2=t.charAt(e+2);
	c0=0;c1=0;
	for(p=0;p<10;p++){a=cc[p];if(t0==a){c0=1;}}
	for(p=0;p<10;p++){a=cc[p];if(t1==a){c1=1;}}
	if(c0==0 && c1==1){t=t.replace('e','10^');}
	if(c0==0 && c1==0 && t1=="+"){t=t.replace('e+','10^');}
	if(c0==0 && c1==0 && t1=="-"){t=t.replace('e-','10^-');}
	if(c0==0 && c1==0 && t1==""){t=t.replace('e','E');}
	if(c0==1 && c1==1){t=t.replace('e','*10^');}
	if(c0==1 && c1==0 && t1=="+"){t=t.replace('e+','*10^');}
	if(c0==1 && c1==0 && t1=="-"){t=t.replace('e-','*10^-');}
	if(c0==1 && c1==0 && t1==""){t=t.replace('e','E');}
	t=t.replace('e','E');
	e=t.indexOf('e');
	trouble++;if(trouble>100){alert(r20);return org;}
    }
    t=t.replace(/E/g,"e");
    t=t.replace(/10\^0/g,"10^");
    return t;
}

function check_o(t){
    var dingen=['1','2','3','4','5','6','7','8','9','0','.','+','-','*','/','^','=',' '];
    var ld=dingen.length;var t2;var d;
    var os=['o','O'];var o;var trouble=0;
    for(s=0;s<2;s++){
	o=os[s];t1=t.indexOf(o)
	while(t1!=-1){
	    if(t1<1){t2='a';}else{t2=t.charAt(t1-1);}
	    t3=t.charAt(t1+1);if(t3!=" " && t2!=" "){for(p=0;p<ld;p++){d=dingen[p];if(t3==d || t2==d){alert(r5);return 0;}}}
	    t=t.replace(o,'0');t1=t.indexOf(o);
	    trouble++;if(trouble>200){alert(r20);return 0;}
	}
    }
    return 1;
}

function check_f(t){
    t=t.replace(/log\[/g,'#');
    t=t.replace(/sqrt\[/g,'#');
    var ft;var ismatch;var fun;var F;var t2;var c0;var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh'];
    ft=functies.length;var trouble=0;
    for(s=0;s<ft;s++){
	fun=functies[s];ismatch=t.indexOf(fun);F=fun.toUpperCase();c0=fun.length;
	while(ismatch != -1 ){
	    c=c0+ismatch;t2=t.substring(c,c+1);
	    if(t2=='('){t=t.replace(fun,F);ismatch=t.indexOf(fun);}else{alert(r9);return 0;}
	    trouble++;if(trouble>200){alert(r20);return 0;}
	}
    }
    return 1;
}

function check_x(t){
    var dingen=['1','2','3','4','5','6','7','8','9','0'];
    var t2;var t3;var d;var chk;var trouble=0;
    t1=t.indexOf('x');
    /// tollerate: x1= x2= etc ---> t1>0
    while(t1>0){
	chk=0;
	t2=t.charAt(t1-1);
	t3=t.charAt(t1+1);
	for(s=0;s<10;s++){
	    d=dingen[s];
	    if(t2==d){chk=chk+1;}if(t3==d){chk=chk+1;}
	}
	if(chk==2){alert(r7);return 0;}
	t=t.replace('x','*');t1=t.indexOf('x');
	trouble++;if(trouble>100){alert(r20);return 0;}
    }
    return 1;
}

function specialroot(t){
    var power;var sqrt;var begin;var end;var mod;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;var test;var org;
    t2=t.indexOf("](");if(t2==-1){alert(r11);t="error";return t;}
    org=t;t=t.replace(/sqrt\(/g,"SQRT(");
    t=t.replace(/log\[/g,"LOG~");t=t.replace(/sqrt\[/g,"@[");test=t.replace(/[a-z]\[/g,"#");
    if(test.indexOf("#")!=-1){alert(r11);t="error"; return t;}
    t2=t.indexOf("[");var trouble=0;
    while(t2 != -1){
	begin=t.indexOf("@");t2=t.indexOf("[");t3=t.indexOf("]");
	if(t2==begin+1 && t3>t2){
	    power=t.substring(t2+1,t3);
	    if(power.length==0){alert(r16);t="error";return t;}
	    if(power<2){alert(r16);t="error";return t;}
	    t4="["+power+"]";t=t.replace(t4,'');
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;
	    sqrt=t.substring(begin,end);
	    mod=(power % 2);
	    if(sqrt<0 && mod!=1){alert(r16);t="error";return t;}
	    t=t.replace("@("+sqrt+")","("+sqrt+")^(1/("+power+"))");
	}
	else{t=t.replace("]","?");}
	trouble++;if(trouble>100){alert(r20);t="error";return t;}
    }
    t=t.replace(/SQRT\(/g,"sqrt(");t=t.replace(/LOG~/g,"log[");t=t.replace(/~/g,"[");t=t.replace(/\?/g,"]");t=t.replace(/@/g,"sqrt");
    return t;
}
    
function speciallog(t){
    var noemer;var teller;var begin;var end;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;
    t2=t.indexOf("](");if(t2==-1){alert(r11);t="error";return t;}
    t=t.replace(/log\(/g,'LOG(');
    t=t.replace(/log/g,"@");
    t2=t.indexOf("[");var trouble=0;
    while(t2 != -1){
	begin=t.indexOf("@");t3=t.indexOf("]");
	if(t2==begin+1 && t3>t2){
	    grondtal=t.substring(t2+1,t3);
	    if(grondtal=="10"){alert(r14);t="error";return t;}
	    if(grondtal=="e" || grondtal=='E'){alert(r15);t="error";return t;}
	    t4="["+grondtal+"]";t=t.replace(t4,'');
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;teller=t.substring(begin,end);
	    if(grondtal==teller){alert(r17);}
	    t=t.replace("@("+teller+")","(~("+teller+")/~("+grondtal+"))");
	}else{t=t.replace("[","%");}
	t2=t.indexOf("[");
	trouble++;if(trouble>100){alert(r20);t="error";return t;}
    }
    t=t.replace(/\%/g,"[");t=t.replace(/~/g,"log");t=t.replace(/LOG\(/g,"log(");t=t.replace(/@/g,"log");
    return t;
}

function check_log_NaN(t){
    t=t.replace(/log\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){alert(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;
    while(begin != -1){
	t1=t.indexOf('(');
	t2=t.indexOf(')');
	if(t1=begin+1 && t2>t1){
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;exp=t.substring(begin,end);p=0;variable=0;
	    while(p<27){v=dingen[p];w=exp.indexOf(v);if(w!=-1){p=27;variable=1;}p++;}
	    if(variable==0){test=eval(exp);if(test<=0){alert(r16);return 0;}}
	    t=t.replace('@(','log(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){alert(r20);return 0;}
    }
    return 1;
}

function check_sqrt_NaN(t){
    t=t.replace(/sqrt\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){alert(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;
    while(begin != -1){
	t1=t.indexOf('(');
	t2=t.indexOf(')');
	if(t1=begin+1 && t2>t1){
	    tot=t.length;wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    begin=begin+2;exp=t.substring(begin,end);p=0;variable=0;
	    while(p<27){v=dingen[p];w=exp.indexOf(v);if(w!=-1){p=27;variable=1;}p++;}
	    if(variable==0){test=eval(exp);if(test<0){alert(r16);return 0;}}
	    t=t.replace('@(','sqrt(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){alert(r20);return 0;}
    }
    return 1;
}

function nthroot(t){
    var test=t.replace(/root/g,'@');
    if(test.indexOf('@')==-1){return t;}
    var t1;var t2;var t3;var exp;var variable;
    var under;var wait;var end;var got;var s;var trouble=0;
    t=t.replace(/root/g,'@');var begin=t.indexOf('@');
    var tot=t.length;
    while(begin != -1){
	t1=t.indexOf('(');
	t2=t.indexOf(')');
	if(t1=begin+1 && t2>t1){
	    wait=0;got=0;end=0;
	    for(s=begin;s<tot;s++){
		if(end==0){
		    chr=t.charAt(s);
		    if(chr=="("){wait=wait+1;}
		    if(chr==")"){got=got+1;}
		    if(got!=0){if(wait==got){end=s;}}
		}
	    }
	    under=t.substring(begin+2,end);
	    t3=under.indexOf(',');
	    if(t3==-1){t=t.replace("@("+under+")","sqrt%"+under+"#");}
	    else{
		variable=under.substring(0,t3);
		exp=under.substring(t3+1,end)
		if(exp.indexOf(',')!=-1 || variable.indexOf(',')!=-1 ){alert(r20);t="error";return t;}
		t=t.replace("@("+under+")","%"+variable+"#^%1/%"+exp+"##");
	    }
	}
	else
	{
	    t=t.replace('(','%');
	    t=t.replace(')','#');
	}
	tot=t.length;
	begin=t.indexOf('@');
    	trouble++;if(trouble>100){alert(r20);t="error";return t;}
    }
    t=t.replace(/\%/g,'(');
    t=t.replace(/#/g,')');
    return t;
}

function normalize(t){
    var org=t;
    // we can't use lower.case() because of F(x)= x^123 + C :(
    var accent_H = ['Æ','Ã','À','Ä','Â','É','È','Ë','Ê','Ã','Ì','Ã','Î','Ó','Ò','Ö','Ô','Ú','Ù','Ü','Û','Ç','²','³','¼','½','¾','ß'];
    var normal_H = ['AE','A','A','A','A','E','E','E','E','A','I','I','I','O','O','O','O','U','U','U','U','C','^2','^3','0.25','0.5','0.75','S'];
    var accent_L = ['ò','ó','ô','õ','ö','ø','ù','ú','û','ü','à','á','â','ã','ä','å','ç','è','é','ê','ë','ì','í','î','ï','ñ','æ'];
    var normal_L = ['o','o','o','o','o','o','u','u','u','u','a','a','a','a','a','a','c','e','e','e','e','i','i','i','i','n','ae'];
    var char_t;var p;var str_a;var str_n;var trouble=0;
    for(p=0;p<accent_H.length;p++){
	str_a=accent_H[p];
	str_n=normal_H[p];
	while(t.indexOf(str_a)!=-1){
	    t=t.replace(str_a,str_n);
	    trouble++;if(trouble>200){alert(r20);return org;}
	}
    }
    trouble=0;
    for(p=0;p<accent_L.length;p++){
	str_a=accent_L[p];
	str_n=normal_L[p];
	while(t.indexOf(str_a)!=-1){
	    t=t.replace(str_a,str_n);
	    trouble++;if(trouble>200){alert(r20);return org;}
	}
    }
    return t; 
}
 
//  Ñ N mit Tilde &Ntilde; &#209;
//  Ò O mit accent grave (Gravis) &Ograve; &#210;
//  Ó O mit accent aigu (Akut) &Oacute; &#211; 
//  Ô O mit Zirkumflex &Ocirc; &#212;
//  Õ O mit Tilde &Otilde; &#213;
//  Ö O Umlaut &Ouml; &#214; 
//  × Mal-Zeichen &times; &#215; 
//  Ø O mit Schrägstrich &Oslash; &#216; 
//  Ù U mit accent grave (Gravis) &Ugrave; &#217;
//  Ú U mit accent aigu (Akut) &Uacute; &#218; 
//  Û U mit Zirkumflex &Ucirc; &#219;
//  Ü U Umlaut &Uuml; &#220; 
//  Ý Y mit accent aigu (Akut) &Yacute; &#221; 
//  Þ großes Thorn (isländisch) &THORN; &#222; 
//  ß scharfes S &szlig; &#223;
//  à a mit accent grave (Gravis) &agrave; &#224;
//  á a mit accent aigu (Akut) &aacute; &#225; 
//  â a mit Zirkumflex &acirc; &#226;
//  ã a mit Tilde &atilde; &#227;
//  ä a Umlaut &auml; &#228; 
//  å a mit Ring &aring; &#229;
//  æ a mit legiertem e &aelig; &#230; 
//  ç c mit Häkchen &ccedil; &#231;
//  è e mit accent grave (Gravis) &egrave; &#232;
//  é e mit accent aigu (Akut) &eacute; &#233; 
//  ê e mit Zirkumflex &ecirc; &#234;
//  ë e Umlaut &euml; &#235; 
//  ì i mit accent grave (Gravis) &igrave; &#236;
//  í i mit accent aigu (Akut) &iacute; &#237; 
//  î i mit Zirkumflex &icirc; &#238;
//  ï i Umlaut &iuml; &#239; 
//  ð kleines Eth (isländisch) &eth; &#240;
//  ñ n mit Tilde &ntilde; &#241;

//  ò o mit accent grave (Gravis) &ograve; &#242;
//  ó o mit accent aigu (Akut) &oacute; &#243; 
//  ô o mit Zirkumflex &ocirc; &#244;
//  õ o mit Tilde &otilde; &#245;
//  ö o Umlaut &ouml; &#246; 
//  ÷ Divisions-Zeichen &divide; &#247;
//  ø o mit Schrägstrich &oslash; &#248;
 
//  ù u mit accent grave (Gravis) &ugrave; &#249;
//  ú u mit accent aigu (Akut) &uacute; &#250; 
//  û u mit Zirkumflex &ucirc; &#251;
//  ü u Umlaut &uuml; &#252; 
//  ý y mit accent aigu (Akut) &yacute; &#253; 
//  þ kleines Thorn (isländisch) &thorn; &#254;
//  ÿ 
//  ¡ umgekehrtes Ausrufezeichen &iexcl; &#161;
//  ¢ Cent-Zeichen &cent; &#162; 
//  £ Pfund-Zeichen &pound; &#163; 
//  ¤ Währungszeichen &curren; &#164;
//  ¥ Yen-Zeichen &yen; &#165; 
//  ¦ durchbrochener Strich &brvbar; &#166;
//  § Paragraph-Zeichen &sect; &#167;
//  ¨ Pünktchen oben &uml; &#168;
//  © Copyright-Zeichen &copy; &#169;
//  ª Ordinal-Zeichen weiblich &ordf; &#170; 
//  « angewinkelte Anführungszeichen links &laquo; &#171;
//  ¬ Verneinungs-Zeichen &not; &#172; 
//  ­ bedingter Trennstrich &shy; &#173; 
//  ® Registriermarke-Zeichen &reg; &#174; 
//  ¯ Überstrich &macr; &#175; 
//  ° Grad-Zeichen &deg; &#176;
//  ± Plusminus-Zeichen &plusmn; &#177;
//  ² Hoch-2-Zeichen &sup2; &#178; 
//  ³ Hoch-3-Zeichen &sup3; &#179; 
//  ´ Akut-Zeichen &acute; &#180;
//  µ Mikro-Zeichen &micro; &#181; 
//  ¶ Absatz-Zeichen &para; &#182; 
//  · Mittelpunkt &middot; &#183;
//  ¸ Häkchen unten &cedil; &#184; 
//  ¹ Hoch-1-Zeichen &sup1; &#185; 
//  º Ordinal-Zeichen männlich &ordm; &#186; 
//  » angewinkelte Anführungszeichen rechts &raquo; &#187; 
//  ¼ ein Viertel &frac14; &#188;
//  ½ ein Halb &frac12; &#189; 
//  ¾ drei Viertel &frac34; &#190; 
//  ¿ umgekehrtes Fragezeichen &iquest; &#191; 
//  À A mit accent grave (Gravis) &Agrave; &#192;
//  Á A mit accent aigu (Akut) &Aacute; &#193; 
//  Â A mit Zirkumflex &Acirc; &#194;
//  Ã A mit Tilde &Atilde; &#195;
//  Ä A Umlaut &Auml; &#196; 
//  Å A
 