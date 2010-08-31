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
		this.toolbar.addButton('Italique',function(){
			this.wrapSelection('<em>','</em>');
		},{
			id: 'markdown_italics_button'
		});
		
		this.toolbar.addButton('Gras',function(){
			this.wrapSelection('<strong>','</strong>');
		},{
			id: 'markdown_bold_button'
		});
		
		this.toolbar.addButton('Liens Web',function(){
			var selection = this.getSelection();
			var response = prompt('Entrez l&quot;URL du lien','');
			if(response == null)
				return;
			this.replaceSelection('<a href="'+response+'">' + (selection == '' ? 'Link Text' : selection) + '</a>' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_link_button'
		});
		
		this.toolbar.addButton('Image',function(){
			var selection = this.getSelection();
			//afficherHud('hud_video_intro');
			var response="Entrez le nom de l'image !";
			//if(response == null)
				//return;
			this.replaceSelection('\\img{'+response+'}' + (selection == '' ? '{alt="Image manquante"}' : selection) + '' + (response == '' ? '' : '').replace(/^(?!(f|ht)tps?:\/\/)/,'') + '');
		},{
			id: 'markdown_image_button'
		});
		
		//this.toolbar.addButton('Heading',function(){
			//var selection = this.getSelection();
			//if(selection == '')
				//selection = 'Heading';
			//var str = '';
			//(Math.max(5,selection.length)).times(function(){
				//str += '-';
			//});
			//this.replaceSelection("\n" + selection + "\n" + str + "\n");
		//},{
			//id: 'markdown_heading_button'
		//});
		
		this.toolbar.addButton('Ent&ecirc;te niv.1',function(){
			this.wrapSelection('<h1>','</h1>');
		},{
			id: 'markdown_heading_button'
		});
		
		
		this.toolbar.addButton('Liste &agrave; puces',function(){
			this.wrapSelection('<ul>','</ul>');
		},{
			id: 'markdown_unordered_list_button'
		});
		
		this.toolbar.addButton('Liste Num&eacute;rique',function(){
			this.wrapSelection('<li>','</li>');
		},{
			id: 'markdown_ordered_list_button'
		});
		
		this.toolbar.addButton('espace',function(event){
			this.injectEachSelectedLine(function(lines,line){
				lines.push((event.shiftKey ? line.replace(/^\> /,'') : '' + line));
				return lines;
			});
		},{
			id: 'markdown_espace_button'
		});
		this.toolbar.addButton('Titre',function(){
			this.wrapSelection('\n\\title{}','');
		},{
			id: 'markdown_title_button'
		});
		
		
		this.toolbar.addButton('Mode d&apos;emploi',function(){
			function help_url(){
				var url="?session="+document.getElementById("help_url").innerHTML+"&lang=fr&module=adm/createxo.fr&cmd=help&special_parm=enev";

				return url;
				}
			var help_url=help_url();

			window.open(help_url);
		},{
			id: 'markdown_help_button'
		});
		this.toolbar.addButton('Auteur',function(){
			this.wrapSelection('\n\\author{}','');
		},{
			id: 'markdown_auteur_button'
		});
		this.toolbar.addButton('Intervale',function(){
			this.wrapSelection("\n\\range{}",'');
		},{
			id: 'markdown_range_button'
		});
		
		
		
		this.toolbar.addButton('espace2',function(){
			this.wrapSelection('','');
		},{
			id: 'markdown_espace2_button'
		});
		this.toolbar.addButton('&Eacute;nonc&eacute;',function(){
			this.wrapSelection('\n\\statement{}','');
		},{
			id: 'markdown_statem_button'
		});
		this.toolbar.addButton('Indication',function(){
			this.wrapSelection('\n\\hint{}','');
		},{
			id: 'markdown_hint_button'
		});
		this.toolbar.addButton('Aide',function(){
			this.wrapSelection('\n\\help{}','');
		},{
			id: 'help'
		});
		this.toolbar.addButton('espace3',function(){
			this.wrapSelection('','');
		},{
			id: 'markdown_espace3_button'
		});
		this.toolbar.addButton('R&eacute;ponse',function(){
			this.wrapSelection('\n\\answer{}{}{type=}','');
		},{
			id: 'markdown_answer_button'
		});
		
		
		this.toolbar.addButton('Feedback',function(){
			this.wrapSelection('\n\\feedback{}{}','');
		},{
			id: 'markdown_feed_button'
		});
		this.toolbar.addButton('Condition',function(){
			this.wrapSelection('\n\\condition{}{}','');
		},{
			id: 'markdown_condition_button'
		});
		this.toolbar.addButton('Solution',function(){
			this.wrapSelection('\n\\solution{}','');
		},{
			id: 'markdown_solution_button'
		});
	}
});