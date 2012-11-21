jQuery.noConflict();

jQuery(function($) {
    
    var wims_menu = $("#wimsmenumodubox");
    
    if (wims_menu)
    {    
        wims_menu.addClass("{title:'MENU'}");
        
        wims_menu.buildMbExtruder({
            position:"left",
            width:300,
            extruderOpacity:.8,
            textOrientation:"tb",
            onExtOpen:function(){},
            onExtContentLoad:function(){wims_menu.openPanel();},
            onExtClose:function(){}
        });
    }

});