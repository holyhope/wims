  editAreaLoader.load_syntax["flydraw"] = {
    'QUOTEMARKS' : {1: ' " '}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : {
	'flydraw' : [
'affine', 'animate', 'animstep', 'arc', 'arrow', 'arrow2', 'circle', 'comment', 'copy', 'insert', 'copyresized', 'darrow', 'dasharrow', 'dashedarrow', 'darrow2', 'dasharrow2', 'dashedarrow2', 'dhlinedashedhorizontalline', 'dashhorizontalline', 'hdline', 'horizontaldashedline', 'diamondfill', 'diafill', 'dline', 'dashedline', 'dashline', 'dlines', 'dashedlines', 'dashlines', 'dotfill', 'pointfill', 'diskfill', 'dvline', 'dashedverticaline', 'dashverticalline', 'vdline', 'verticaldashedline', 'ellipse', 'fcircle', 'ball', 'disk', 'filledcircle', 'fellipse', 'filledellipse', 'fill', 'flood', 'floodfill', 'filltoborder', 'fpoly', 'filledpoly', 'filledpolygon', 'fpolygon', 'frect', 'filledrect', 'fillecrectangle', 'frectangle', 'fsquare', 'filledsquare', 'ftriangle', 'filledtriangle', 'gridfill', 'hatchfill', 'hline', 'horizontalline', 'interlace', 'killaffine', 'killbrush', 'killlinear', 'killrotation,killrotate', 'killtile', 'killtranslation', 'killtranslate', 'lattice', 'levelcurve', 'levelstep', 'line', 'seg', 'segment', 'linear', 'lines', 'linewidth', 'multicopy', 'new', 'output', 'parallel', 'pixels', 'plot', 'curve', 'plotjump', 'plotstep', 'plotsteps', 'tstep', 'tsteps', 'point', 'points', 'poly', 'polygon', 'range', 'rays', 'rect', 'rectangle', 'resetmatrix', 'resetparallelogram', 'resetvector', 'resettransform', 'rotation', 'rotate', 'setbrush', 'setmatrix', 'setparallelogram', 'setpixel', 'setstyle', 'settile', 'settransform', 'setvector', 'size', 'square', 'text', 'print', 'string', 'write', 'textup', 'stringup', 'writeup', 'trange', 'ranget', 'translation', 'translate', 'transparent', 'triangle', 'vimg', 'vimgfile', 'vline', 'verticalline', 'xrange', 'rangex', 'yrange', 'rangey' ]
}
	,'OPERATORS' :[
		'*', '+', '-', '/', '^', '<', '=', '>','//'
	]
	,'DELIMITERS' :[
		'(', ')', '[', ']','{','}'
	]
	,'REGEXPS' :
	{
		'oefvariables' : { 'search': '()(\\\\\\w+)()',
			'class' : 'oefvariables',
			'modifiers' : 'g', 'execute' : 'before' }
	}
	,'STYLES' : {
		'COMMENTS': 'color: #0000CD;'
		,'QUOTESMARKS': 'color: #6381F8;'
		,'KEYWORDS' : {
			'flydraw' : 'color: #48BDDF;'
			}
		,'OPERATORS' : 'color: #FF00FF;'
		,'DELIMITERS' : 'color: #60CA00;'
		,'REGEXPS': {
			'oefvariables' : 'color: #FF3A6E;'
		}
	}
};

