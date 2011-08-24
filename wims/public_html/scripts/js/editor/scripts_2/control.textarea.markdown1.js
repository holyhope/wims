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
			this.replaceSelection('\n<a target=\"wims_external\" href="'+response+'">' + (selection == '' ? names["Link_Text"] : selection) + '</a>' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
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
			this.replaceSelection('<img src="\\filedir/'+response+'"' + (selection == '' ? ' alt="'+names["image_alt"]+'">' : selection) + '' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_image_button'
		});
		
		this.toolbar.addButton(names["Heading"],function(){
			this.wrapSelection('\n<h2>','</h2>');
		},{
			id: 'markdown_heading_button'
		});
		
		this.toolbar.addButton(names["Unordered_List"],function(){
			this.wrapSelection('\n<ul>\n <li>','\n </li>\n</ul>');
		},{
			id: 'markdown_unordered_list_button'
		});
		
		this.toolbar.addButton(names["Ordered_List"],function(){
			this.wrapSelection('\n<ol>\n <li>','\n </li>\n</ol>');
		},{
			id: 'markdown_ordered_list_button'
		});
		
		this.toolbar.addButton(names["List_item"],function(){
			this.wrapSelection('<li>\n','\n </li>');
		},{
			id: 'markdown_ordered_list_button'
		});
		
		this.toolbar.addButton(names["wims_link"],function(){
		 var selection = this.getSelection();
			var response = prompt(names["Enter_link_name"],'');
			if(response == '' ) return; if(response == null ) return;
			this.replaceSelection(' \\link{'+response+'} ');
		},{
			id: 'markdown_link_button'
		});
		this.toolbar.addButton(names["wims_fold"],function(){
		 var selection = this.getSelection();
			var response = prompt(names["Enter_fold_name"],'');
			if(response == '') return; if(response == null) return;
			this.replaceSelection(' \\fold{'+response+'} ');
		},{
			id: 'markdown_link_button'
		});
		
		this.toolbar.addButton(names["wims_href"],function(){
		 var selection = this.getSelection();
			var response = prompt(names["Enter_href_name"],'');
			var response2 = prompt(names["Enter_href_name2"],'');
			if(response == '' ) return; if(response == null) return;
			this.replaceSelection(' \\href{'+response+'}{'+response2+'} ');
		},{
			id: 'markdown_link_button'
		});
		
		this.toolbar.addButton('',function(event){
			this.injectEachSelectedLine(function(lines,line){
				lines.push((event.shiftKey ? line.replace(/^\> /,'') : '' + line));
				return lines;
			});
		},{
			id: 'markdown_espace_button'
		});
	}
});