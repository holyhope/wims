editAreaLoader.load_syntax["diff"] = {
    'QUOTEMARKS' : {1: ' " '}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : { 'diff' : ['-r' ]}
	,'OPERATORS' :[
		'*', '+', '-', '/', '^', '=', '>', '<', '//','--'
	]
	,'DELIMITERS' :[
		'(', ')', '[', ']','{','}'
	]
	,'REGEXPS' :
	{
	   'diff2' : { 'search': '(\n<)(.*)()',
			'class' : 'diff2',
			'modifiers' : 'g', 'execute' : 'before' }
	 ,'diff1' : { 'search': '(\n>)(.*)()',
			'class' : 'diff1',
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
			 'diff1' : 'color: #FF3A6E;'
			,'diff2' : 'color: #48BDDF;'
		}
	}
};

