/**
 * @author Ryan Johnson <ryan@livepipe.net>
 * @copyright 2007 LivePipe LLC
 * @package Control.TextArea.ToolBar.Markdown
 * @license MIT
 * @url http://livepipe.net/projects/control_textarea/
 * @version 1.0.1
 */

Control.TextArea.ToolBar.Markdown = Class.create();
Object.extend(Control.TextArea.ToolBar.Markdown.prototype,{
	textarea: false,
	toolbar: false,
	options: {},
	initialize: function(textarea,options){
		this.textarea = new Control.TextArea(textarea);
		this.toolbar = new Control.TextArea.ToolBar(this.textarea);
		this.converter = (typeof(Showdown) != 'undefined') ? new Showdown.converter : false;
		this.options = {
			preview: false,
			afterPreview: Prototype.emptyFunction
		};
		Object.extend(this.options,options || {});
		if(this.options.preview){
			this.textarea.observe('change',function(textarea){
				if(this.converter){
					$(this.options.preview).update(this.converter.makeHtml(textarea.getValue()));
					this.options.afterPreview();
				}
			}.bind(this));
		}

		//buttons
		this.toolbar.addButton(names["Italics"],function(){
			this.wrapSelection('<em>','</em>');
		},{
			id: 'markdown_italics_button'
		});
		
		this.toolbar.addButton(names["Bold"],function(){
			this.wrapSelection('<strong>','</strong>');
		},{
			id: 'markdown_bold_button'
		});
		
		this.toolbar.addButton(names["Link"],function(){
			var selection = this.getSelection();
			var response = prompt(names["Enter_Link_URL"],'http://');
			if(response == null)
				return;
			this.replaceSelection('\n<a href="'+response+'">' + (selection == '' ? names["Link_Text"] : selection) + '</a>' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_link_button'
		});
		
		/*this.toolbar.addButton(names["Image"],function(){
			var selection = this.getSelection();
			afficherHud('hud_video_intro');
			var response=null;
			if(response == null)
				return;
			this.replaceSelection('\\img{'+response+'}' + (selection == '' ? '{alt="'+names["image_alt"]+'"}' : selection) + '' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_image_button'
		});*/
		
		this.toolbar.addButton(names["Image"],function(){
			var selection = this.getSelection();
			//afficherHud('hud_video_intro');
			var response = prompt(names["Enter_img_URL"],'test.jpg');

			//if(response == null)
				//return;
			this.replaceSelection('\\img{'+response+'}' + (selection == '' ? '{alt="'+names["image_alt"]+'"}' : selection) + '' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_image_button'
		});
		

		this.toolbar.addButton(names["Heading"],function(){
			this.wrapSelection('\n<h1>','</h1>');
		},{
			id: 'markdown_heading_button'
		});
		
		
		this.toolbar.addButton(names["Unordered_List"],function(){
			this.wrapSelection('\n<ul><li>','</li></ul>');
		},{
			id: 'markdown_unordered_list_button'
		});
		
		this.toolbar.addButton(names["Ordered_List"],function(){
			this.wrapSelection('\n<ol><li>','</li></ol>');
		},{
			id: 'markdown_ordered_list_button'
		});
		
		this.toolbar.addButton('',function(event){
			this.injectEachSelectedLine(function(lines,line){
				lines.push((event.shiftKey ? line.replace(/^\> /,'') : '' + line));
				return lines;
			});
		},{
			id: 'markdown_espace_button'
		});
		this.toolbar.addButton(names["title"],function(){
			this.wrapSelection('\n\\title{}','');
		},{
			id: 'markdown_title_button'
		});
		
		
		this.toolbar.addButton(names["User_guide"],function(){
			function help_url(){
				var url="?session="+document.getElementById("session_wims").innerHTML+"&lang="+version+"&module=adm/createxo&cmd=help&special_parm=JS_editor";

				return url;
				}
			var help_url=help_url();

			window.open(help_url);
		},{
			id: 'markdown_help_button'
		});
		this.toolbar.addButton(names["author"],function(){
			this.wrapSelection('\n\\author{}','');
		},{
			id: 'markdown_auteur_button'
		});
		this.toolbar.addButton(names["range"],function(){
			this.wrapSelection("\n\\range{}",'');
		},{
			id: 'markdown_range_button'
		});
		
		
		
		this.toolbar.addButton('',function(){
			this.wrapSelection('','');
		},{
			id: 'markdown_espace2_button'
		});
		this.toolbar.addButton(names["statement"],function(){
			this.wrapSelection('\n\\statement{}','');
		},{
			id: 'markdown_statem_button'
		});
		this.toolbar.addButton(names["hint"],function(){
			this.wrapSelection('\n\\hint{}','');
		},{
			id: 'markdown_hint_button'
		});
		this.toolbar.addButton(names["help"],function(){
			this.wrapSelection('\n\\help{}','');
		},{
			id: 'help'
		});
		this.toolbar.addButton("espace3",function(){
			this.wrapSelection('','');
		},{
			id: 'markdown_espace3_button'
		});
		this.toolbar.addButton(names["answer"],function(){
			this.wrapSelection('\n\\answer{}{}{type=}','');
		},{
			id: 'markdown_answer_button'
		});
		
		
		this.toolbar.addButton(names["feedback"],function(){
			this.wrapSelection('\n\\feedback{}{}','');
		},{
			id: 'markdown_feed_button'
		});
		this.toolbar.addButton(names["condition"],function(){
			this.wrapSelection('\n\\condition{}{}','');
		},{
			id: 'markdown_condition_button'
		});
		this.toolbar.addButton(names["solution"],function(){
			this.wrapSelection('\n\\solution{}','');
		},{
			id: 'markdown_solution_button'
		});
	}
});