// 3/5/2008 version 0.02 [added item 10]
// 18/5/2008 version 0.03 [added item 11]
// 19/5/2008 version 0.04 [added item 12,13,14,15]
// this is all very premature !!! The naming needs to be adapted to f1,f2...f20

//  1 science(t)	checks scientific notation 4e+4 --> 4*10^4		: returns modified t or "error"
//  2 check_o(t)	checks letter o instead of number 0			: returns 0 or 1 (0=error,1=success)		
//  3 check_f(t)	checks parenthesis usage in functions sin()		: returns 0 or 1	
//  4 check_x(t)	checks usage of x as multiplication *			: returns 0 or 1
//  5 specialroot(t)	converts sqrt[a](b) to b^(1/a)				: returns modified t or "error"
//  6 speciallog(t)	converts log[a](b) to log(b)/(log(a))			: returns modified t or "error"
//  7 nthroot(t)	converts root(b,a) to b^(1/a)				: returns modified t or "error"
//  8 check_log_NaN(t)	checks negative numbers in log				: returns 0 or 1
//  9 check_sqrt_NaN(t)	checks negative numbers in sqrt				: returns 0 or 1
// 10 normalize(t)	converts accents to letters without...			: returns modified t or "error"
// 11 prefix(t)		converts SI prefixes to powers of 10			: returns modified t or "error"
// 12 check_s2(t)	checks and corrects powers 10^01,10^0.1			: returns modified t or "error"
// 13 arrows(t,arg1,arg2,arg3) 
//	t is answer ; if needed "t" will be corrected for special sqrt[] and log[] syntax
// 	arg1=switch:
// 		arg1=0	: converts ascii arrows to unified "->"
// 		arg1=1	: converts ascii arrows to unified "\u2192"
// 		arg1=2	: returns no arrows ,just the text after the last arrow
// 		arg1=3	: returns no arrows...the answer is an array 
// 		arg1=4	: returns the answer ,checks on all steps if arg2 and "=" are present
// 	arg2=x	: variable name in needed ($varlist?)
// 	arg3=3	: amount -if any- of arrows...
//
// 14 keywords(t)	convert all keywords to  ' and '			: returns modified t or "error"
// 15 upper_f(t)	converts all 'known' functions and 'and' to uppercase	: returns modified t or "error"
// 16 is_number(t)	checks if no text is present				: returns 0 or 1  (0=error,1=success)
// 17 is_real_number(t)	checks if real number: no sqrt or e+ allowed			: returns 0 or 1  (0=error,1=success)
    
function SetTexAppSize(){
    if( document.getElementById('TexApp1') ){ // starts with 1 !!!!
	var p = 1;var size = new Array(2);
	while ( document.getElementById('TexApp'+p) ){
    	    size = document.getElementById('TexApp'+p).getPrefferedSize();                                                                   
    	    try{
		document.getElementById('TexApp'+p).width = size[0];                                                                             
    		document.getElementById('TexApp'+p).height = size[1];
	    }catch(e){}// problems on opera/safari
	    p++;
	} 
    }                                                 
}

function setAlarm(txt){
    var h=document.documentElement.clientHeight;
    var w=document.documentElement.clientWidth;
    document.getElementById('alarmtext').style.display = "block"
    document.getElementById('alarmtext').style.top = h/3.5;
    document.getElementById('alarmtext').style.left =w/4;
    document.getElementById('alarmtext').innerHTML='<table cellpadding=\"10\"><tr><th>'+txt+'</th></tr></table>';
    setTimeout('resetAlarm()',4000);
}
	
function resetAlarm(){
    document.getElementById('alarmtext').style.display = "none"
}

function science(t){// corrected: startvalue+3 != startvalu*10^3 :)
    t=t.replace(/\*\*/g,'^'); 
    t=t.replace(/x10/g,'*10')
    e=t.indexOf('e');
    cc=['0','1','2','3','4','5','6','7','8','9'];
    var c0;var c1;var t0;var t1;var c;var a;var trouble=0;var s;
    while(e!=-1){
	t0=t.charAt(e-1);
	t1=t.charAt(e+1);
	t2=t.charAt(e+2);
	c0=0;c1=0;
	for(s=0;s<10;s++){a=cc[s];if(t0==a){c0=1;}}
	for(s=0;s<10;s++){a=cc[s];if(t1==a){c1=1;}}
	if(c0==1 && c1==1){t=t.replace('e','*10^');}
	if(c0==1 && c1==0 && t1=="+"){t=t.replace('e+','*10^');}
	if(c0==1 && c1==0 && t1=="-"){t=t.replace('e-','*10^-');}
	if(c0==1 && c1==0 && t1==""){t=t.replace('e','E');}
	t=t.replace('e','E');
	e=t.indexOf('e');
	trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
    }
    t=t.replace(/E/g,"e");
    t=t.replace(/10\^0/g,"10^");
    return t;
}

function check_o(t){
    var alfabet="abcdefghijklmonpqrstuvwxyz";
    var Alfabet="ABCDEFGHIJKLMONPQRSTUVWXYZ";
    
    var dingen=['1','2','3','4','5','6','7','8','9','0','.','+','-','*','/','^','=',' '];
    var ld=dingen.length;var t2;var d;var sa;
    var os=['o','O'];var o;var trouble=0;
    for(s=0;s<2;s++){
	o=os[s];t1=t.indexOf(o)
	while(t1!=-1){
	    if(t1<1){t2='a';}else{t2=t.charAt(t1-1);}
	    t3=t.charAt(t1+1);
	    if(t3!=" " && t2!=" "){
		if(alfabet.indexOf(t2)==-1 && Alfabet.indexOf(t2)==-1 && alfabet.indexOf(t3)==-1 && Alfabet.indexOf(t3)==-1){
		    for(sa=0;sa<ld;sa++){
			d=dingen[sa];
		        if(t3==d || t2==d){
			    setAlarm(r5);return 0;
			}
		    }
		}
	    }    
	    t=t.replace(o,'0');t1=t.indexOf(o);
	    trouble++;if(trouble>200){setAlarm(r20);return 0;}
	}
    }
    return 1;
}

function check_f(t){
    var alfabet="abcdefghijklmonpqrstuvwxyz";
    var Alfabet="ABCDEFGHIJKLMONPQRSTUVWXYZ";
    t=t.replace(/log\[/g,'#');
    t=t.replace(/sqrt\[/g,'#');
    var ft;var ismatch;var fun;var F;var t2;var c0;var t1;
    var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh'];
    ft=functies.length;var trouble=0;
    for(s=0;s<ft;s++){
	fun=functies[s];ismatch=t.indexOf(fun);F=fun.toUpperCase();c0=fun.length;
	while(ismatch != -1 ){
	    c=c0+ismatch;t1=t.substring(ismatch-1,ismatch);t2=t.substring(c,c+1);
	    if(t2=='(' || alfabet.indexOf(t1)!=-1 || Alfabet.indexOf(t1)!=-1 || alfabet.indexOf(t2)!=-1 || Alfabet.indexOf(t2)!=-1){t=t.replace(fun,F);ismatch=t.indexOf(fun);}else{setAlarm(r9);return 0;}
	    trouble++;if(trouble>200){setAlarm(r20);return 0;}
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
	if(chk==2){setAlarm(r7);return 0;}
	t=t.replace('x','*');t1=t.indexOf('x');
	trouble++;if(trouble>100){setAlarm(r20);return 0;}
    }
    return 1;
}

function specialroot(t){
    var power;var sqrt;var begin;var end;var mod;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;var test;var org;
    t2=t.indexOf("](");if(t2==-1){setAlarm(r11);t="error";return t;}
    org=t;t=t.replace(/sqrt\(/g,"SQRT(");
    t=t.replace(/log\[/g,"LOG~");t=t.replace(/sqrt\[/g,"@[");test=t.replace(/[a-z]\[/g,"#");
    if(test.indexOf("#")!=-1){setAlarm(r11);t="error"; return t;}
    t2=t.indexOf("[");var trouble=0;
    while(t2 != -1){
	begin=t.indexOf("@");t2=t.indexOf("[");t3=t.indexOf("]");
	if(t2==begin+1 && t3>t2){
	    power=t.substring(t2+1,t3);
	    if(power.length==0){setAlarm(r16);t="error";return t;}
	    if(power<2){setAlarm(r16);t="error";return t;}
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
	    if(sqrt<0 && mod!=1){setAlarm(r16);t="error";return t;}
	    t=t.replace("@("+sqrt+")","("+sqrt+")^(1/("+power+"))");
	}
	else{t=t.replace("]","?");}
	trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
    }
    t=t.replace(/SQRT\(/g,"sqrt(");t=t.replace(/LOG~/g,"log[");t=t.replace(/~/g,"[");t=t.replace(/\?/g,"]");t=t.replace(/@/g,"sqrt");
    return t;
}
    
function speciallog(t){
    var noemer;var teller;var begin;var end;var tot;var wait;var got;var chr;var t1;var t2;var t3;var t4;
    t2=t.indexOf("](");if(t2==-1){setAlarm(r11);t="error";return t;}
    t=t.replace(/log\(/g,'LOG(');
    t=t.replace(/log/g,"@");
    t2=t.indexOf("[");var trouble=0;
    while(t2 != -1){
	begin=t.indexOf("@");t3=t.indexOf("]");
	if(t2==begin+1 && t3>t2){
	    grondtal=t.substring(t2+1,t3);
	    if(grondtal=="10"){setAlarm(r14);t="error";return t;}
	    if(grondtal=="e" || grondtal=='E'){setAlarm(r15);t="error";return t;}
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
	    if(grondtal==teller){setAlarm(r17);}
	    t=t.replace("@("+teller+")","(~("+teller+")/~("+grondtal+"))");
	}else{t=t.replace("[","%");}
	t2=t.indexOf("[");
	trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
    }
    t=t.replace(/\%/g,"[");t=t.replace(/~/g,"log");t=t.replace(/LOG\(/g,"log(");t=t.replace(/@/g,"log");
    return t;
}

function check_log_NaN(t){
    t=t.replace(/log\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){setAlarm(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;var sa;
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
	    begin=begin+2;exp=t.substring(begin,end);sa=0;variable=0;
	    while(sa<27){v=dingen[sa];w=exp.indexOf(v);if(w!=-1){sa=27;variable=1;}sa++;}
	    if(variable==0){test=eval(exp);if(test<=0){setAlarm(r16);return 0;}}
	    t=t.replace('@(','log(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){setAlarm(r20);return 0;}
    }
    return 1;
}

function check_sqrt_NaN(t){
    t=t.replace(/sqrt\(/g,'@(');if(t.indexOf('@')==-1){return 1;}
    if(t.indexOf('--')!=-1 || t.indexOf('++')!=-1 ){setAlarm(r18);return 0;}
    dingen=['@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'];
    begin=t.indexOf('@');var exp;var variable;var trouble=0;var s;var sa;
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
	    begin=begin+2;exp=t.substring(begin,end);exp=exp.replace(/\ /g,'');sa=0;variable=0;
	    while(sa<27){v=dingen[sa];w=exp.indexOf(v);if(w!=-1){sa=27;variable=1;}sa++;}
	    if(variable==0){test=eval(exp);if(test<0){setAlarm(r16);return 0;}}
	    t=t.replace('@(','sqrt(');begin=t.indexOf('@');
	}else{return 1;}
	trouble++;
	if(trouble>100){setAlarm(r20);return 0;}
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
		if(exp.indexOf(',')!=-1 || variable.indexOf(',')!=-1 ){setAlarm(r20);t="error";return t;}
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
    	trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
    }
    t=t.replace(/\%/g,'(');
    t=t.replace(/#/g,')');
    return t;
}

function normalize(t){
    // we can't use lower.case() because of F(x)= x^123 + C :(
    var accent_H = ['Æ','Ã','À','Ä','Â','É','È','Ë','Ê','Ã','Ì','Ã','Î','Ó','Ò','Ö','Ô','Ú','Ù','Ü','Û','Ç','²','³','¼','½','¾','ß'];
    var normal_H = ['AE','A','A','A','A','E','E','E','E','A','I','I','I','O','O','O','O','U','U','U','U','C','^2','^3','0.25','0.5','0.75','S'];
    var accent_L = ['ò','ó','ô','õ','ö','ø','ù','ú','û','ü','à','á','â','ã','ä','å','ç','è','é','ê','ë','ì','í','î','ï','ñ','æ'];
    var normal_L = ['o','o','o','o','o','o','u','u','u','u','a','a','a','a','a','a','c','e','e','e','e','i','i','i','i','n','ae'];
    var char_t;var s;var str_a;var str_n;var trouble=0;
    for(s=0;s<accent_H.length;s++){
	str_a=accent_H[s];
	str_n=normal_H[s];
	while(t.indexOf(str_a)!=-1){
	    t=t.replace(str_a,str_n);
	    trouble++;if(trouble>200){setAlarm(r20);t="error";return t;}
	}
    }
    trouble=0;
    for(s=0;s<accent_L.length;s++){
	str_a=accent_L[s];
	str_n=normal_L[s];
	while(t.indexOf(str_a)!=-1){
	    t=t.replace(str_a,str_n);
	    trouble++;if(trouble>200){setAlarm(r20);t="error";return t;}
	}
    }
    return t; 
}
 
function prefix(t){
    // replace SI prefixes 
    // still no good: case sensitive !!! can not / will not do a lowercase on the student reply ...
    var SI=['*10^-1','*10^1','*10^6','*10^12','*10^15','*10^18','*10^15','*10^12','*10^9','*10^6','*10^3','*10^2','*10^1','*10^-1','*10^-2','*10^-3','*10^-6','*10^-9','*10^-12','*10^-15','*10^-18'];
    var VA1=['déci','déca','méga','téra','péta','exa','peta','tera','giga','mega','kilo','hecto','deca','deci','centi','milli','micro','nano','pico','femto','atto'];
    var VA2=['Déci','Déca','Méga','Téra','Péta','Exa','Peta','Tera','Giga','Mega','Kilo','Hecto','Deca','Deci','Centi','Milli','Micro','Nano','Pico','Femto','Atto'];
    var trouble=0;var l=VA1.length;var prefix1;var prefix2;var prefix3;var x1;var x2;var x3;var s;var number;var s1;var s2;var s3;var rep=0;var t;var x4;
    for (s=0;s<l;s++){
	number=SI[s];prefix1=VA1[s];prefix2=VA2[s];prefix3=prefix1.toUpperCase();x1=t.indexOf(prefix1);x2=t.indexOf(prefix2);x3=t.indexOf(prefix3)
	while(x1 != -1 || x2 !=-1 || x3 !=-1){
	    rep=0;s1=t.indexOf('*'+prefix1);s2=t.indexOf('*'+prefix2);s3=t.indexOf('*'+prefix3);
	    if(s1 != -1){t=t.replace('*'+prefix1,number);rep=1;}if(s2 != -1){t=t.replace('*'+prefix2,number);rep=1;}if(s3 != -1){t=t.replace('*'+prefix3,number);rep=1;}
	    if(rep==0){t=t.replace(prefix1,number);t=t.replace(prefix2,number);t=t.replace(prefix3,number);}
	    x1=t.indexOf(prefix1);x2=t.indexOf(prefix2);x3=t.indexOf(prefix3);
	    trouble++;if(trouble>200){setAlarm(r20);t="error";return t;}
	}
    }
    if(t.charAt(0)=='*'){x4=t.length;t=t.substring(1,x4);} 
    return t;  
} 


function check_s2(t){
    // scientific notation...broken exponents or 10^03 or 10^+3 10^0.4 10^.5 10^12.3 ...
    var x=t.indexOf('^');
    if(x != -1){
	var x1=t.charAt(x+1);var x2=t.charAt(x+2);var x3=t.charAt(x+3);
	if(x1 == '.' || x2 == '.' || x3 == '.'){setAlarm(r10);t="error";return t;}
	if(x1 == '0' && x2 == ''  && x3 == '' ){t=t.replace(/\*10\^0/,'*1');}
	if(x1 == '0' && x2 != '' ){x=x.replace(/10\^0/,'10^');}
	if(x1 == '+' && x2 == ''  && x3 == '' ){setAlarm(r16);t="error";return t;}
	if(x1 == '+' && x2 != '' ){t=t.replace(/\^\+/g,'^');}
    }
    return t;
}

    

function keywords(t){
    var kwords=[' en ',' et ',' of ',' or ',' ou ',' plus ',' and ','and/or',' & '];
    var a1;t=t.replace(/\~/g,' ');var trouble=0;t=t.toLowerCase();
    for (var s=0 ; s<kwords.length ; s++){
	a1=kwords[s];
	while(t.indexOf(a1) != -1){
	    t=t.replace(a1,'~');
	    trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
	}
    }
    t=t.replace(/\~/g,' and ');
    return t;
}

function upper_f(t){
    var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh','pi',' and ',' or '];
    var trouble=0;var fun;var FUN;
    for(s=0;s<functies.length;s++){
	fun=functies[s];FUN=fun.toUpperCase();
	while( t.indexOf(fun) != -1 ){
	    t=t.replace(fun,FUN);
	    trouble++;if(trouble>100){setAlarm(r20);t="error";return t;}
	}
    }
    return t;
}

function upper_varlist(varlist,t){
    return t;
}

function rawmath(t){
    // poor mans rawmath?
    var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh','pi'];
    return t;
}

function represent(t){
    // unicode math display ?
    return t;
}
function arrows(t,arg1,arg2,arg3){
    // modify t in order to have a uniform arrow.
    var ascii_arrows=['volgt','alors','thus','dus','therefor','ergo','<===>','===>','<==>','==>','<=>','=>','<--->','--->','<-->','-->','<->','->'];
    var a1;t=t.replace(/@/g,' ');var trouble=0;var s;total_arrows=0;
    for( s=0 ; s<ascii_arrows.length ; s++){
	a1=ascii_arrows[s];
	while(t.indexOf(a1) != -1){
	    t=t.replace(a1,'@');total_arrows++;
	    trouble++;if(trouble>100){setAlarm(t+"<br>"+r20);t="error";return t;}
	}
    }
    
    // arg3>0 there should be arrows
    if(arg3){
	if(arg3==1){if(total_arrows == 0){setAlarm(r30+"  "+arg3);t="error";return t;}}
	if(arg3>1){if(total_arrows < arg3){setAlarm(r31+"  "+arg3);t="error";return t;}}
    }

    // arg2 is the variable: we replace x1=,y_1=,z_9= by x=,y=,z= : just 1 variable at a time
    if(arg2){
	// preserve keywords...convert to ' and '
	t=keywords(t);if(t=="error"){return t;}
	t=t.replace(/[\s\r\n\ ]/g,'');
	for(var m=1;m<10;m++){
	    a1=arg2+"_"+m+"=";t=t.replace(a1,arg2+"=");
	    a1=arg2+m+"=";t=t.replace(a1,arg2+"=");
	}
	t=t.replace(/and/g,' and '); 
    }
    
    var arrow_array=t.split('@');

    // there could ? be an sqrt[3](5) or log[7](12) in the sub_answers...
    if(t.indexOf('[')!= -1){
	var new_arrow_array=new Array();
	t="";
	for(s=0;s<total_arrows+1;s++){
	    a1=arrow_array[s];
	    if(a1.indexOf('sqrt[') != -1){a1=specialroot(a1);if(a1=="error"){t="error";return;}}
	    if(a1.indexOf('log[') != -1){a1=speciallog(a1);if(a1=="error"){t="error";return;}}
	    // rebuild the answer...
	    t=t+"@"+a1;
	    new_arrow_array[s]=a1;
	}
	arrow_array=new_arrow_array;
    }

    if(arg1==0){
	// returns standardized arrow " -> "
	t=t.replace(/@/g,' -> ');return t;
    }
    if(arg1==1){
	// returns unicode arrow symbol
	t=t.replace(/@/g,' \u2192 ');return t;
    }

    if(arg1==2){
	// returns only the text after the last arrow
	t=arrow_array[total_arrows];
	// but should the answer be in the form arg2=1234 ?
	if(arg2){
	    a1=t.replace(/[\s\r\n\ ]/g,'');
	    var x1=a1.indexOf(arg2);var is=a1.indexOf('=');
	    if(x1==-1 || is==-1){setAlarm(r22+"  "+a1);t="error";return t;}
	    if(x1>is){setAlarm(r29+"  "+a1);t="error";return t;}
	}
	// if there are more arrows, skip these and alert the student about this
	if(total_arrows>0){
	    var rem="";
	    for(m=0;m<total_arrows;m++){
		a1=arrow_array[m];
		rem=rem+" \u2192 "+a1;
	    }
	    setAlarm("\""+rem+"\""+r32);
	}
	return t;
    }
    
    if(arg1==3){
	// returns the answer as an array split by the arrow symbol: no arrows present in this answer
	// will not be used...
	t=arrow_array;return t;
    }
    
    if(arg1==4){
	// returns the complete "stream of deduction"...and checks...
	// every step [between arrows] if there is an arg2 (variable) and an "="
	for(s=0;s<total_arrows-1;s++){
	    a1=arrow_array[s];a1=a1.replace(/[\s\r\n\ ]/g,'');
	    a2=arrow_array[s+1];a2=a2.replace(/[\s\r\n\ ]/g,'');
	    if(a1 == a2){setAlarm(r33+"<br>"+a1+" \u2192 "+a2);t="error";return t;}
	    if(a1.indexOf(arg2) == -1 && a1.indexOf('=') == -1){setAlarm(r30+" : "+a1);t="error";return t;}
	}
	if(arg2){
	    // and sees if the last argument is a conclusion  : arg2=12345 and arg2=54321
	    a1=arrow_array[total_arrows];
	    var x1=a1.indexOf(arg2);
	    var is=a1.indexOf('=');
	    if(x1==-1 || is==-1){setAlarm(r22+"  "+a1);t="error";return t;}
	    if(x1 > is ){setAlarm(r29+" : "+a1);t="error";return t;}
	}
	t=t.replace(/@/g,' -> ');return t;
    }
    setAlarm("syntax error in function <br> arrows(t,arg1,arg2,arg3)<br> t is answer <br> arg1=switch, arg1=0: converts ascii arrows to unified \"->\" <br> arg1=1 : converts ascii arrows to unified \"\u2192\" <br> arg1=2 : returns no arrows ,just the text after the last arrow<br> arg1=3 : returns no arrows...the answer is an array <br> arg1=4 : returns the answer ,checks on all steps<br> arg2=variable name<br>arg3=amount if any of arrows...");
}

function is_number(t){
    t=science(t);
    var s=t.toLowerCase();
    var functies=['log','ln','abs','sqrt','sin','cos','tan','atan','acos','sinh','cosh','tanh','pi'];
    var f;var F;
    for(var p=0;p<functies.length;p++){
	f=functies[p];
	F=f.toUpperCase();
	s=s.replace(f,F);
    }
    s=s.replace(/[a-z\~\!\@\#\$\&\_\=\:\;]/g,'');
    if(s.length != t.length){setAlarm(r37+" "+t); return 0;}else{return 1;}
}

function is_real_number(t){
    t=science(t);
    var s=t.toLowerCase();
    s=s.replace(/[a-z\~\!\@\#\$\&\_\=\:\;]/g,'');
    if(s.length != t.length){setAlarm(r37+" "+t) ; return 0;}else{return 1;}
}
