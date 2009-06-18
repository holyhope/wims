
function zirkel2wims(type,name){
    var data;
    if(type != null && name != null){
	// get only the things we want...
	data = document.getElementById("zirkel").getDrawing(type,name);
    }
    else
    {
	// this function retreives all construction details 
	// excluded objects with name prefix "my_" 
	data = document.getElementById("zirkel").getAllObjects();    
    }
    if(data.indexOf("error") != -1){alert(r19+"\n"+data); return "error";}else{return data;}
}   