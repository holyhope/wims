editAreaLoader.load_syntax["wimsdata"] = {
    'QUOTEMARKS' : {1: ' " '}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : {
      'c' : ['|']
      }
	,'OPERATORS' :[
		'@', '*', '+', '-', '/', '^', ':=', '<', '=', '>','//','$'
	]
	,'DELIMITERS' :[
		'(', ')', '[', ']','{','}','\(', '\)','??','??'
	]
	,'REGEXPS' :
	{
		'wimsvariables' : { 'search': '(\\$)([a-zA-Z0-9_]*)()',
			'class' : 'wimsvariables',
			'modifiers' : 'g', 'execute' : 'before' },
		'record' : { 'search': '(\n)(:)()',
			'class' : 'record',
			'modifiers' : 'g', 'execute' : 'before' },
		'question' : { 'search': '(\\?\\?)([^\\?]+)(\\?\\?)',
			'class' : 'question',
			'modifiers' : 'g', 'execute' : 'after' }
	}
	,'STYLES' : {
		'COMMENTS': 'color: #0000CD;'
		,'QUOTESMARKS': 'color: #6381F8;'
		,'KEYWORDS' : {
			'c' : 'color: #48BDDF;'
			}
		,'OPERATORS' : 'color: #60CA00;'
		,'DELIMITERS' : 'color: #60CA00;',
		'REGEXPS': {
			'wimsvariables' : 'color: #FF3A6E;'
			,'question' : 'color:#985717;'
			,'record' : 'color:blue;'
		}
	}
};
