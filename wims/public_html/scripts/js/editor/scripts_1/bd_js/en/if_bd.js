var ifffff= [ '==', '!=</tt> or <tt>&lt;&gt;', '<', '<=', '>', '>=', 'isin', 'notin', 'iswordof', 'notwordof', 'isvarof', 'notvarof', 'isvariableof', 'notvariableof', 'isitemof', 'notitemof', 'islineof', 'notlineof', 'issamecase', 'notsamecase', 'issametext', 'notsametext' ];
function iffffffun(instruction, version){
    switch(instruction)
	{
	case '==' :
chaine_aide='<code>string1  ==  string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt> are identical.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '!=</tt> or <tt>&lt;&gt;' :
chaine_aide='<code>string1  !=  string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt> are not identical.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '<' :
chaine_aide='<code>string1  <  string2</code>'+
'true if numerical evaluation of <tt>string1</tt> is strictly lower than <tt>string2</tt>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '<=' :
chaine_aide='<code>string1  <=  string2</code>'+
'true if numerical evaluation of <tt>string1</tt> is lower than or equals  <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '>' :
chaine_aide='<code>string1  >  string2</code>'+
'true if numerical evaluation of <tt>string1</tt> is strictly greater than  <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case '>=' :
chaine_aide='<code>string1  >=  string2</code>'+
'true if numerical evaluation of <tt>string1</tt> is greater than <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'isin' :
chaine_aide='<code>string1  isin  string2</code>'+
'true if <tt>string1</tt> is a substring of <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notin' :
chaine_aide='<code>string1  notin  string2</code>'+
'true if <tt>string1</tt> is not a substring of <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'iswordof' :
chaine_aide='<code>string1  iswordof  string2</code>'+
'true if <tt>string1</tt> is a word of<tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notwordof' :
chaine_aide='<code>string1  notwordof  string2</code>'+
'true if <tt>string1</tt> is not a word of<tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'isvarof' :
chaine_aide='<code>string1  isvarof  string2</code>'+
'true if <tt>string1</tt> is a mathematical variable of expression <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notvarof' :
chaine_aide='<code>string1  notvarof  string2</code>'+
'si <tt>string1</tt> is not a mathematical variable of expression <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'isvariableof' :
chaine_aide='<code>string1  isvariableof  string2</code>'+
'true if <tt>string1</tt> is a mathematical variable of expression <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notvariableof' :
chaine_aide='<code>string1  notvariableof  string2</code>'+
'true if <tt>string1</tt> is not a mathematical variable of expression <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'isitemof' :
chaine_aide='<code>string1  isitemof  string2</code>'+
'true if <tt>string1</tt> is an item from the list <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notitemof' :
chaine_aide='<code>string1  notitemof  string2</code>'+
'true if <tt>string1</tt> is not an item from the list <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'islineof' :
chaine_aide='<code>string1  islineof  string2</code>'+
'true if <tt>string1</tt> is a line of <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notlineof' :
chaine_aide='<code>string1  notlineof  string2</code>'+
'true if <tt>string1</tt> is not a line of <tt>string2</tt>.'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'issamecase' :
chaine_aide='<code>string1  issamecase  string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt>.....'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notsamecase' :
chaine_aide='<code>string1  notsamecase string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt> .....'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'issametext' :
chaine_aide='<code>string1  issametext string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt> .....'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'notsametext' :
chaine_aide='<code>string1  notsametext  string2</code>'+
'true if <tt>string1</tt> and <tt>string2</tt> ......'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}