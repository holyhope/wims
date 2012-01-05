
editAreaLoader.load_syntax['octave'] = {
    'QUOTEMARKS' : {1: ' " '}
    ,'COMMENT_SINGLE' : {1 : '\\'}
	,'COMMENT_MULTI' : {'/\*' : '\*/'}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : {
	 'octstatement' : ['function', 'break', 'case', 'catch', 'classdef', 'continue', 'else', 'elseif', 'end', 'for', 'function', 'global', 'if', 'otherwise', 'parfor', 'persistent', 'return', 'spmd', 'switch', 'try', 'while','error' , 'length' , 'size' , 'ones' , 'zeros' , 'rand' ,
     'log'  , 'log2'  , 'log10' , 'exp'  , 'sqrt'  , 'sin'  , 'cos' , 'tan'  ,
     'asin'  , 'acos'  , 'atan' , 'abs'  , 'ceil'  , 'floor'  , 'round'  ,
     'fix'  , 'power' , 'atan2' , 'mod' , 'true'  , 'false'  , 'pi'  , 
     'Inf'  , 'NaN' , 'eye' , 'diag' , 'repmat' , 'reshape' , 'strvcat' ,
     'all' , 'any' , 'find' , 'linspace' , 'logspace' , 'mean' , 'sum' , 'max' ,
     'min' , 'ind2sub' , 'sub2ind' , 'fopen' , 'fclose' , 'fscanf' , 'fprintf' ,
     'fread' , 'fwrite' , 'disp' , 'input' ]
	 ,'octfunction' : ['betacdf', 'empirical_rnd', 'laplace_inv', 'stdnormal_cdf', 'betainv', 'expcdf', 'laplace_pdf', 'stdnormal_inv', 'betapdf', 'expinv', 'laplace_rnd', 'stdnormal_pdf', 'betarnd', 'exppdf', 'logistic_cdf', 'stdnormal_rnd', 'binocdf', 'exprnd', 'logistic_inv', 'tcdf', 'binoinv', 'binopdf', 'finv', 'logistic_rnd', 'tpdf', 'binornd', 'fpdf', 'logncdf', 'trnd', 'cauchy_cdf', 'frnd', 'logninv', 'unidcdf', 'cauchy_inv', 'gamcdf', 'lognpdf', 'unidinv', 'cauchy_pdf', 'gaminv', 'lognrnd', 'unidpdf', 'cauchy_rnd', 'gampdf', 'nbincdf', 'unidrnd', 'chi2cdf', 'gamrnd', 'nbininv', 'unifcdf', 'chi2inv', 'geocdf', 'nbinpdf', 'unifinv', 'chi2pdf', 'geoinv', 'nbinrnd', 'unifpdf', 'chi2rnd', 'geopdf', 'normcdf', 'unifrnd', 'discrete_cdf', 'geornd', 'norminv', 'wblcdf', 'discrete_inv', 'hygecdf', 'normpdf', 'wblinv', 'discrete_pdf', 'hygeinv', 'normrnd', 'wblpdf', 'discrete_rnd', 'hygepdf', 'poisscdf', 'wblrnd', 'empirical_cdf', 'hygernd', 'poissinv', 'wienrnd', 'empirical_inv', 'kolmogorov_smirnov_cdf', 'poisspdf', 'empirical_pdf', 'laplace_cdf', 'poissrnd'] 
	 }
	 ,'OPERATORS' :[
		'*', '+', '-', '/', '^', ':=', '<', '=', '>'
	]
	,'DELIMITERS' :[
		'(', ')', '[', ']','{','}','\(', '\)'
	]
	 ,'STYLES' : {
		'COMMENTS': 'color: #0000CD;'
		,'QUOTESMARKS': 'color: #6381F8;'
		,'KEYWORDS' : {
			'octstatement' : 'color: #3399FF;'
			,'octfunction' : 'color: #FF3A6E;'
			}
		,'OPERATORS' : 'color: #CD00CD;'
		,'DELIMITERS' : 'color: #60CA00;'
		}
};