
jQuery(function($) {
    var wims_menu = $("#wimsmenumodubox");
    if (wims_menu)
    {
        wims_menu.addClass("{title:'&#8593;&#8595;'}");

        wims_menu.buildMbExtruder({
            position:"left",
            width:250,
            extruderOpacity:0.8,
            textOrientation:"tb",
            onExtOpen:function(){},
            onExtContentLoad:function(){wims_menu.openPanel();},
            onExtClose:function(){}
        });
    }
});
