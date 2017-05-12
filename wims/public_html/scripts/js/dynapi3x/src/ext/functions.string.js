/*
	DynAPI Distribution
	dynapi.functions.String extension
*/

var dynafunc = dynapi.functions;
dynafunc.String = {}; // used by dynapi.library


// String Functions --------------------------------

dynafunc.trim = function(s,dir){
	if(!s) return;
	else s+=''; // make sure s is a string
	dir=(dir)? dir:'<>';
	if(dir=='<'||dir=='<>') s=s.replace(/^(\s+)/g,'');
	if(dir=='>'||dir=='<>') s=s.replace(/(\s+)$/g,'');
	return s;

};
dynafunc.strRepeat = function(s,n) {
	if(!s) return '';
	var i,a=[];
	for(i=1;i<=n;i++){
		a[a.length]=s;
	}
	return a.join('');
};
dynafunc.strReverse = function(s) {
	if(!s) return '';
	var a=(s+'').split('');
	a.reverse();
	return a.join('');
};
dynafunc.strStuff = function(s,v,index) {
	if(!s) return '';
	if (index==null) s=s+v+'';
	else {
		var t1=t2=s+'';
		s=t1.substr(0,index)+v+t2.substr(index,t2.length-index);
	}
	return s;
};
