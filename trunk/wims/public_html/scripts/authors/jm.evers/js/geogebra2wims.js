/* 
14/6/2013
Changed to geogebra3 : OpenJDK was not able to export the java array getAllObjectNames()
(as was already a problem for internet explorer version 6,7,8?) 
Resulting in lockups of the browser and OpenJDK java virtual machine.
getAllObjectNames() function is depreciated since geogebra > 2.7 (btw: Oracle / Sun virtualmachine  & plugin were/are ok ! )

getAllObjectNames() is replaced by a combination of
int getObjectNumber() -> Returns the total number of objects in the construction.
String getObjectName(int i) --> returns the construction name of the i-th object

Added 'triangle','quadrilateral' 'etc' als alternatives for 'polygon' (pffff)
Now this script recognizes : 
list_of_things=['text','point','line','segment','circle','function','polygon','conic','ellipse','polynomial','vector','number','angle'];
And will alert , if it encounters a unknown object.

Examples:
circle @ name @ x_center @ y_center @ radius
line @ name @ slope @ constant   (e.g. : y = slope*x + constant)
line @ name @ perp @ x = number (e.g. : vertical line x=some_number)
polygon @ name @ surface_area @ A @ B @ C .... @ Z (e.g. : names of corners points)

remarks: 
geogebra3 has some issues with frame closing, it will not respond to normal appletmethods stop(),destroy()
I will try to get hold of the source code  geogebra-2.7 ; and manually add the required new functions.
geogebra4 is much too heavy for normal usage (use a CAS in java applet ? )
*/
function geogebra2wims(list_of_things){
    var debug=0;var polygon_alternatives = ['triangle','quadrilateral','pentagon','hexagon','heptagon','octagon'];var applet = document.getElementById("ggbApplet");var max = applet.getObjectNumber();var total_object_count=0;var point_count=0;var line_count=0;var circle_count=0;var segment_count=0;var polygon_count=0;var function_count=0;var polynomial_count=0;var conic_count=0;var ellipse_count=0;var hyperbola_count=0;var vector_count=0;var angle_count=0;var text_count=0;var reply='';var data = '';if(debug == 1 ){alert(' \"list_of_things\" to check \n'+list_of_things);}var listcnt = list_of_things.length;
    for( var i = 0 ; i < max ; i++ ){
	var thing = applet.getObjectName(i);var whatisit = applet.getObjectType(thing);if( polygon_alternatives.indexOf(whatisit) != -1 ){whatisit = "polygon";}if(debug == 1){alert("whatisit = "+whatisit);}
	for ( var p=0 ; p < listcnt ; p++){
	    var it = list_of_things[p];
	    if( it == whatisit ){
		data = applet.getValueString(thing);data = encodeURIComponent(data);if(debug == 1){alert("found : "+it+"="+whatisit+"\ndata = "+data);}if( it=="circle" ){ data = data.replace(/%C2%B2/g,'@');} else {data = data.replace(/%C2%B/g,'^');}data = decodeURIComponent(data);
		if (data.indexOf("_") != 2 ){/* protected names my_somename*/
		  total_object_count++;
		  if (it == "point"){var x = applet.getXcoord(thing);var y = applet.getYcoord(thing);data='point@'+thing+'@'+x+'@'+y ;point_count++;} 
		  else if (it == "circle"){ data = data.replace(/\=/g,'');var t = data.length;var c = data.indexOf(':');data = data.substring(c+1,t);var broken_up_string = data.replace(/[x-y]/g,'');broken_up_string = broken_up_string.split("@");var x = broken_up_string[0];var y = broken_up_string[1];var d = broken_up_string[2];if (x == ' ' || x==' + ' || x == ' - '){x = 0;}if (y == ' ' || y == ' + ' || y == ' + '){y = 0;}if (d == ' '){d = 0;}x='-1*('+x+')';y = '-1*('+y+')';data='circle@'+thing+'@'+parseFloat(eval(x))+'@'+parseFloat(eval(y))+'@'+d;circle_count++;}
		  else if (it == "line"){ var t = data.length;var n = data.indexOf(':');var f = data.indexOf('=');var d = data.indexOf('x');var e = data.indexOf('y');var a,b,c,r,q; if( d > 0 && e > 0 ){ a = data.substring(n+1,d); a = a.replace(/\ /g,""); if(a == 'x'){a = '1';} if(a == ''){a = '1';} if(a == '-'){a = '-1';} b = data.substring(d+1,e); b = b.replace(/\ /g,""); if(b == '+'){b = '1';}if(b == '-'){b='-1';} c = data.substring(f+1,t);r = '(-1*('+a+')/('+b+'))';q = '('+c+')/('+b+')';data='line@'+thing+'@'+parseFloat(eval(r))+'@'+parseFloat(eval(q));} else {if (d > 0 ){ c = data.substring(f+1,t);r = 'perp'; q = 'x='+c;data='line@'+thing+'@'+r+'@'+q;} else { c = data.substring(f+1,t);r = '0';q = c;data='line@'+thing+'@'+parseFloat(eval(r))+'@'+parseFloat(eval(q));	}}  line_count++;}
  		  else if (it == "polygon" ){var def=applet.getCommandString(thing);var i1=def.indexOf("[");var i2=def.indexOf("]");var points_of_polygon = def.substring(i1+1,i2);while ( points_of_polygon.indexOf(',') != -1){points_of_polygon = points_of_polygon.replace(',','@');}data = data.replace(/\=/g,'@');data = 'polygone@'+data+'@'+points_of_polygon;polygon_count++;}
  		  else if (it == "segment"){data = 'segment@'+data;segment_count++;}	
  		  else if (it == "function"){data = 'function@'+data;function_count++;}
  		  else if (it == "polynomial"){data = 'polynomial@'+data;polynomial_count++;}
  		  else if (it == "conic"){data = 'conic@'+data;conic_count++;}
  		  else if (it == "ellipse"){data = 'ellipse@'+data;ellipse_count++;}
  		  else if (it == "hyperbola"){data = 'hyperbola@'+data;hyperbola_count++;}
  		  else if (it == "text"){data = 'text@'+data;text_count++;}
  		  else if (it == "angle"){data = data.split("=");name = data[0];data = data[1];data=name+'@'+data;angle_count++;}
  		  else if (it == "vector"){var x = applet.getXcoord(thing);var y = applet.getYcoord(thing);data = 'vector@'+thing+'@'+x+'@'+y ;vector_count++;}
		  else {alert ('object type with name: '+thing+'... is not in my list, please add: ' + it);}
		  if( i < max - 1 ){ reply = reply + data +',';} else {reply = reply + data ;}if(debug == '1'){alert ('we add the variable \"data\" to the URL string :\n' +data);}
		}
	    }
        }
    }
    // lost track about this ...
    reply = reply.replace(/undefined/g,'');reply = reply.replace(/%C2%B/g,'^');reply = reply.replace(/%CE%B/g,'angle@');reply = reply.replace(/\^0/g,' degree');
    reply = total_object_count+','+point_count+','+circle_count+','+line_count+','+segment_count+','+polygon_count+','+conic_count+','+ellipse_count+','+hyperbola_count+','+angle_count+','+vector_count+','+function_count+','+polynomial_count+','+text_count+','+reply;
    // if some inputareas are present called myinpu0....myinput100 ; read these as well         
    // and append it to the "geogebra string" as "text="+txt  
    // we use @ as fieldseparator.   
    if(document.getElementById('myinput0') ){var p = 0;var t="";var txt="";while( document.getElementById('myinput'+p) ){ t = document.getElementById('myinput'+p).value; if( p == 0 ){ txt = t; } else { txt = txt +"@"+t;} p++;  } reply=reply+",text="+txt;}if(debug == 1){alert(reply);}
    return reply;
}

