/*
	DynAPI Distribution
	HTMLCalendar Class - based on calendar script from The JavaScript Source!! http://javascript.internet.com

	The DynAPI Distribution is distributed under the terms of the GNU LGPL license.
	
	Requires: HTMLContainer
*/

// to-do: add floating drop down menu to the month and year fields
function HTMLCalendar(css,date){
	this.HTMLContainer = HTMLContainer;
	this.HTMLContainer(css,null);	

	this._date = date;
};
var p = dynapi.setPrototype('HTMLCalendar','HTMLContainer');
p._olHConGetInnerHTML = HTMLContainer.prototype.getInnerHTML;
p.getInnerHTML = function(){
	this._build();
	return this._olHConGetInnerHTML();
}
// color props
p.borSize = 1;
p.borCol = '#BBBBBB';
p.titleBgCol ='#CCCCCC';
p.titleFgCol ='#000000';
p.wkDayBgCol ='#FFFFFF';
p.wkDayFgCol = '#000000';
p.selBorCol = '#CCCCCC';
p.selBgCol = '#DEDEFF';
p.selFgCol = '#000000';
p.selTDayBgCol = '#EEEEEE';
p.selTDayFgCol = '#000000'
p._build = function(dt){
	var tmp;
	var idate=((dt)? dt:this._date)||new Date();
	this._date = new Date(idate.toString());
	var Calendar = new Date(idate.toString());
	var day_of_week = new Array('Sun','Mon','Tue','Wed','Thu','Fri','Sat');
	var month_of_year = new Array('January','February','March','April','May','June','July','August','September','October','November','December');
	var year = Calendar.getFullYear(),month = Calendar.getMonth();
	var today = (new Date()).getDate();
	var selectedDay = Calendar.getDate(),weekday = Calendar.getDay();
	var DAYS_OF_WEEK = 7,DAYS_OF_MONTH = 31,cal;
	var TR_start = '<tr>',TR_end = '</tr>';
	
	tmp = '<td><table cellspacing="0" bgcolor="@1" @2><tr><td width="20"><b><center><font face="arial" size="2" color="@3">';
	var highlight_today = tmp.replace(/@0/,0).replace(/@1/,this.selTDayBgCol).replace(/@2/,'').replace(/@3/,this.selTDayFgCol);
	var highlight_start = tmp.replace(/@0/,1).replace(/@1/,this.selBgCol).replace(/@2/,((dynapi.ua.ns4)? 'border="1"':'style="border:2px solid '+this.selBorCol+'"')).replace(/@3/,this.selFgCol);
	var highlight_end   = '</font></center></td></tr></table></b>';
	
	tmp = '<td @0 width="30" height="27"><center><font face=arial size="2" color="@1">';	
	var TD_wkDayStart = tmp.replace(/@0/,'bgcolor="'+this.wkDayBgCol+'"').replace(/@1/,this.wkDayFgCol);
	var TD_start = tmp.replace(/@0/,'').replace(/@1/,this.foreCol)
	var TD_end = '</font></center></td>';

	tmp = (dynapi.ua.ns4)? 'border="'+this.borSize+'"':'style="border:'+this.borSize+'px solid '+this.borCol+'"';
	cal='<table '+tmp+' width="'+(239+this.borSize)+'" bgcolor="'+this.backCol+'" cellspacing="0" cellpadding="0"><tr><td>';
	cal+='<table border="0" cellspacing="0" cellpadding="2">' + TR_start;
	cal+='<td colspan="' + DAYS_OF_WEEK + '" bgcolor="'+this.titleBgCol+'"><center><b><font face="arial" size="2" color="'+this.titleFgCol+'">';
	cal+=month_of_year[month]  + ' &nbsp;&nbsp;' + year + '</b>' + TD_end + TR_end;
	cal+=TR_start;

	Calendar.setDate(1);
	Calendar.setMonth(month);

	// build days-of-week
	for(index=0; index < DAYS_OF_WEEK; index++){
		tmp = day_of_week[index];
		if(weekday == index) tmp = '<b>' + day_of_week[index] + '</b>';
		cal += TD_wkDayStart + tmp + TD_end;
	}

	cal += TD_end + TR_end;
	cal += TR_start;
	for(index=0; index < Calendar.getDay(); index++){
		cal += TD_start + '&nbsp;' + TD_end;
	}

	// build days-of-month
	for(index=0; index < DAYS_OF_MONTH; index++){
		if( Calendar.getDate() > index ){
			week_day =Calendar.getDay();
			if(week_day == 0) cal += TR_start;
			if(week_day != DAYS_OF_WEEK){
				var day  = Calendar.getDate();
				if(selectedDay==Calendar.getDate()){
					cal += highlight_start + day + highlight_end + TD_end;
				}else{
					idate=year+"/"+(month+1)+"/"+day
					click='onclick="'+this+'._build(\''+idate+'\');return false;"';
					click = '<a '+click+' style="text-decoration:none;color:@0" href="javascript:;">'+ day + '</a>'
					if(today==Calendar.getDate()){
						click=click.replace(/@0/,this.selTDayFgCol);
						cal += highlight_today + click + highlight_end + TD_end;
					}
					else {
						click=click.replace(/@0/,this.foreCol);
						cal += TD_start +click+TD_end;
					}
					
				}
			}

			if(week_day == DAYS_OF_WEEK)
			al += TR_end;
		}
		Calendar.setDate(Calendar.getDate()+1);
	}
	cal += '</td></tr></table></table>';

	this.setHTML(cal);
	this.invokeEvent('change');
};
p.getDate  = function(dt){return this._date};
p.setDate  = function(dt){
	this._build(dt);
};
