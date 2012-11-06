
$(function(){

    $("#wimsmenumodubox").addClass("{title:'MENU'}");
    
    $("#wimsmenumodubox").buildMbExtruder({
        position:"right",
        width:300,
        extruderOpacity:.8,
        textOrientation:"tb",
        onExtOpen:function(){},
        onExtContentLoad:function(){$("#wimsmenumodubox").openPanel();},
        onExtClose:function(){}
    });

});