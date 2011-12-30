
editAreaLoader.load_syntax['gp'] = {
    'QUOTEMARKS' : {1: ' " '}
    ,'COMMENT_SINGLE' : {1 : '\/\/'}
	,'COMMENT_MULTI' : {'/\*' : '\*/'}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : {
      'gpstatement' : ['break', 'return', 'next']
     ,'gpconditional' :	['if']
     ,'gprepeat' : [ 'until', 'while', 'for', 'fordiv', 'forprime', 'forstep', 'forvec', 'forell','forsubgroup']
     ,'gpscope' : [ 'my', 'local', 'global']
     ,'gpdefaults' : [ 'colors', 'compatible', 'datadir', 'debug', 'debugfiles', 'debugmem', 'echo', 
'factor_add_primes', 'format', 'help', 'histsize', 'lines', 'log', 'logfile', 
'new_galois_format', 'output', 'parisize', 'path', 'prettyprinter', 
'primelimit', 'prompt', 'prompt', 'prompt_cont', 'psfile', 'realprecision', 
'secure', 'seriesprecision', 'simplify', 'strictmatch', 'TeXstyle', 'timer' ]
    ,'gpinterface' : ['default']
    ,'gpinput' : ['read', 'input']
    ,'gpfunction' : ['Col', 'List', 'Mat', 'Mod', 'Pol', 'Polrev', 'Qfb', 'Ser', 'Set', 'Str', 
    'Strchr', 'Strexpand', 'Strprintf', 'Strtex', 'Vec', 'Vecrev', 'Vecsmall', 'binary', 'bitand', 
    'bitneg', 'bitnegimply', 'bitor', 'bittest', 'bitxor', 'ceil', 'centerlift', 'component',
    'conj', 'conjvec', 'denominator', 'floor', 'frac', 'imag', 'length', 'lift', 'norm', 'norml2', 
    'numerator', 'numtoperm', 'padicprec', 'permtonum', 'precision', 'random', 'real', 'round',
    'sizebyte', 'sizedigit', 'truncate', 'valuation', 'variable', 'breakloop', 'factor_proven', 
    'graphcolormap', 'graphcolors',  'histfile', 'readline',  'recover', 'ellL1', 'elladd', 
    'ellak', 'ellan', 'ellanalyticrank', 'ellap', 
    'ellbil', 'ellchangecurve', 'ellchangepoint', 'ellconvertname', 'elldivpol', 'elleisnum', 'elleta', 
    'ellgenerators', 'ellglobalred', 'ellgroup', 'ellheight', 'ellheightmatrix', 'ellidentify', 'ellinit', 
    'ellisoncurve', 'ellj', 'elllocalred', 'elllog', 'elllseries', 'ellminimalmodel', 'ellmodulareqn', 
    'ellorder', 'ellordinate', 'ellpointtoz', 'ellpow', 'ellrootno', 'ellsearch', 'ellsigma', 'ellsub', 
    'elltaniyama', 'elltatepairing', 'elltors', 'ellweilpairing', 'ellwp', 'ellzeta', 'ellztopoint', 'clone',
    'copy', 'unclone', '_avma', '_badtype', '_cast', '_cgetg', '_const', '_formatcode', '_gerepileall', 
    '_gerepileupto', '_maxprime', '_stack_lim', '_strtoclosure', '_toGENstr', '_tovec', '_typedef', '_wrap', 
    'plot', 'plotbox', 'plotclip', 'plotcolor', 'plotcopy', 'plotcursor', 'plotdraw', 'ploth', 'plothraw', 
    'plothsizes', 'plotinit', 'plotkill', 'plotlines', 'plotlinetype', 'plotmove', 'plotpoints', 'plotpointsize', 
    'plotpointtype', 'plotrbox', 'plotrecth', 'plotrecthraw', 'plotrline', 'plotrmove', 'plotrpoint',
    'plotscale', 'plotstring', 'psdraw', 'psploth', 'psplothraw', 'algdep', 'charpoly', 'concat', 
    'lindep', 'listcreate', 'listinsert', 'listkill', 'listpop', 'listput', 'listsort', 'matadjoint',
    'matcompanion', 'matdet', 'matdetint', 'matdiagonal', 'mateigen', 'matfrobenius', 'mathess', 
    'mathilbert', 'mathnf', 'mathnfmod', 'mathnfmodid', 'matid', 'matimage', 'matimagecompl', 
    'matindexrank', 'matintersect', 'matinverseimage', 'matisdiagonal', 'matker', 'matkerint', 
    'matmuldiagonal', 'matmultodiagonal', 'matpascal', 'matrank', 'matrix', 'matrixqz', 'matsize', 
    'matsnf', 'matsolve', 'matsolvemod', 'matsupplement', 'mattranspose', 'minpoly', 'qfgaussred',
    'qfjacobi', 'qflll', 'qflllgram', 'qfminim', 'qfperfection', 'qfrep', 'qfsign', 'setintersect',
    'setisset', 'setminus', 'setsearch', 'setunion', 'trace', 'vecextract', 'vecsort', 'vector',
    'vectorsmall', 'vectorv', 'a1', 'a2', 'a3', 'a4', 'a6', 'area', 'b2', 'b4', 'b6', 'b8', 'bid',
    'bnf', 'c4', 'c6', 'clgp', 'codiff', 'cyc', 'diff', 'disc', 'e', 'eta', 'f', 'fu', 'futu',
    'gen', 'group', 'index', 'j', 'mod', 'nf', 'no', 'omega', 'orders', 'p', 'pol', 'r1', 'r2',
    'reg', 'roots', 'sign', 't2', 'tate', 'tu', 'tufu', 'w', 'zk', 'zkst', 'bnfcertify', 
    'bnfcompress', 'bnfdecodemodule', 'bnfinit', 'bnfisintnorm', 'bnfisnorm', 'bnfisprincipal', 
    'bnfissunit', 'bnfisunit', 'bnfnarrow', 'bnfsignunit', 'bnfsunit', 'bnrL1', 'bnrclassno', 
    'bnrclassnolist', 'bnrconductor', 'bnrconductorofchar', 'bnrdisc', 'bnrdisclist', 'bnrinit', 
    'bnrisconductor', 'bnrisprincipal', 'bnrrootnumber', 'bnrstark', 'dirzetak', 'factornf',
    'galoisexport', 'galoisfixedfield', 'galoisgetpol', 'galoisidentify', 'galoisinit', 
    'galoisisabelian', 'galoisisnormal', 'galoispermtopol', 'galoissubcyclo', 'galoissubfields', 
    'galoissubgroups', 'idealadd', 'idealaddtoone', 'idealappr', 'idealchinese', 'idealcoprime', 
    'idealdiv', 'idealfactor', 'idealfactorback', 'idealfrobenius', 'idealhnf', 'idealintersect',
    'idealinv', 'ideallist', 'ideallistarch', 'ideallog', 'idealmin', 'idealmul', 'idealnorm', 
    'idealpow', 'idealprimedec', 'idealramgroups', 'idealred', 'idealstar', 'idealtwoelt', 
    'idealval', 'matalgtobasis', 'matbasistoalg', 'modreverse', 'newtonpoly', 'nfalgtobasis', 
    'nfbasis', 'nfbasistoalg', 'nfdetint', 'nfdisc', 'nfeltadd', 'nfeltdiv', 'nfeltdiveuc',
    'nfeltdivmodpr', 'nfeltdivrem', 'nfeltmod', 'nfeltmul', 'nfeltmulmodpr', 'nfeltnorm', 
    'nfeltpow', 'nfeltpowmodpr', 'nfeltreduce', 'nfeltreducemodpr', 'nfelttrace', 'nfeltval', 
    'nffactor', 'nffactorback', 'nffactormod', 'nfgaloisapply', 'nfgaloisconj', 'nfhilbert', 
    'nfhnf', 'nfhnfmod', 'nfinit', 'nfisideal', 'nfisincl', 'nfisisom', 'nfkermodpr', 
    'nfmodprinit', 'nfnewprec', 'nfroots', 'nfrootsof1', 'nfsnf', 'nfsolvemodpr', 
    'nfsubfields', 'polcompositum', 'polgalois', 'polred', 'polredabs', 'polredord', 
    'poltschirnhaus', 'rnfalgtobasis', 'rnfbasis', 'rnfbasistoalg', 'rnfcharpoly', 
    'rnfconductor', 'rnfdedekind', 'rnfdet', 'rnfdisc', 'rnfeltabstorel', 'rnfeltdown', 
    'rnfeltreltoabs', 'rnfeltup', 'rnfequation', 'rnfhnfbasis', 'rnfidealabstorel', 
    'rnfidealdown', 'rnfidealhnf', 'rnfidealmul', 'rnfidealnormabs', 'rnfidealnormrel', 
    'rnfidealreltoabs', 'rnfidealtwoelt', 'rnfidealup', 'rnfinit', 'rnfisabelian', 'rnfisfree', 
    'rnfisnorm', 'rnfisnorminit', 'rnfkummer', 'rnflllgram', 'rnfnormgroup', 'rnfpolred', 
    'rnfpolredabs', 'rnfpseudobasis', 'rnfsteinitz', 'subgrouplist', 'zetak', 'zetakinit', 
    'addprimes', 'bestappr', 'bezout', 'bezoutres', 'bigomega', 'binomial', 'chinese', 
    'content', 'contfrac', 'contfracpnqn', 'core', 'coredisc', 'dirdiv', 'direuler', 'dirmul', 
    'divisors', 'eulerphi', 'factor', 'factorback', 'factorcantor', 'factorff', 'factorial', 
    'factorint', 'factormod', 'ffgen', 'ffinit', 'fflog', 'fforder', 'ffprimroot', 'fibonacci', 
    'gcd', 'hilbert', 'isfundamental', 'ispower', 'isprime', 'ispseudoprime', 'issquare', 
    'issquarefree', 'kronecker', 'lcm', 'moebius', 'nextprime', 'numbpart', 'numdiv', 'omega',
    'partitions', 'polrootsff', 'precprime', 'prime', 'primepi', 'primes', 'qfbclassno', 
    'qfbcompraw', 'qfbhclassno', 'qfbnucomp', 'qfbnupow', 'qfbpowraw', 'qfbprimeform', 
    'qfbred', 'qfbsolve', 'quadclassunit', 'quaddisc', 'quadgen', 'quadhilbert', 'quadpoly',
    'quadray', 'quadregulator', 'quadunit', 'removeprimes', 'sigma', 'sqrtint', 'stirling', 
    'sumdedekind', 'zncoppersmith', 'znlog', 'znorder', 'znprimroot', 'znstar', 'divrem', 'lex', 
    'max', 'min', 'shift', 'shiftmul', 'sign', 'vecmax', 'vecmin', 'O', 'deriv', 'diffop', 'eval', 
    'factorpadic', 'intformal', 'padicappr', 'padicfields', 'polchebyshev', 'polcoeff', 'polcyclo', 
    'poldegree', 'poldisc', 'poldiscreduced', 'polhensellift', 'polhermite', 'polinterpolate', 
    'polisirreducible', 'pollead', 'pollegendre', 'polrecip', 'polresultant', 'polroots', 'polrootsmod', 
    'polrootspadic', 'polsturm', 'polsubcyclo', 'polsylvestermatrix', 'polsym', 'poltchebi', 'polzagier',
    'serconvol', 'serlaplace', 'serreverse', 'subst', 'substpol', 'substvec', 'taylor', 'thue', 'thueinit',
    '_eval_mnemonic', 'addhelp', 'alarm', 'alias', 'allocatemem', 'apply', 'error','extern', 'externstr', 
    'getheap', 'getrand', 'getstack', 'gettime',    'install', 'kill',  
     'next', 'print', 'print1', 'printf', 'printtex', 'quit',  'readvec',  'select', 
    'setrand', 'system', 'trap', 'type',  'version', 'warning', 'whatnow',  'write', 
    'write1', 'writebin', 'writetex', 'derivnum', 'intcirc', 'intfouriercos', 'intfourierexp', 
    'intfouriersin', 'intfuncinit', 'intlaplaceinv', 'intmellininv', 'intmellininvshort', 'intnum',
    'intnuminit', 'intnuminitgen', 'intnumromb', 'intnumstep', 'prod', 'prodeuler', 'prodinf', 
    'solve', 'sum', 'sumalt', 'sumdiv', 'suminf', 'sumnum', 'sumnumalt', 'sumnuminit', 'sumpos', 
    'add', 'adde', 'and', 'call', 'coeff', 'concat', 'deriv', 'div', 'dive', 'divent', 'divente', 
    'divround', 'divrounde', 'eq', 'fact', 'ge', 'gt', 'hist', 'id', 'le', 'lt', 'mm', 'mod', 
    'mode', 'mul', 'mule', 'ne', 'neg', 'not', 'or', 'pl', 'pound', 'pow', 'pp', 'shiftl', 
    'shiftle', 'shiftr', 'shiftre', 'store', 'sub', 'sube', 'trans', 'Euler', 'I', 'Pi', 
    'abs', 'acos', 'acosh', 'agm', 'arg', 'asin', 'asinh', 'atan', 'atanh', 'bernfrac', 
    'bernreal', 'bernvec', 'besselh1', 'besselh2', 'besseli', 'besselj', 'besseljh', 'besselk', 
    'besseln', 'cos', 'cosh', 'cotan', 'dilog', 'eint1', 'erfc', 'eta', 'exp', 'gamma', 'gammah',
    'hyperu', 'incgam', 'incgamc', 'lngamma', 'polylog', 'psi', 'sin', 'sinh', 'sqr', 'sqrt', 
    'sqrtn', 'tan', 'tanh', 'teichmuller', 'theta', 'thetanullk', 'weber', 'zeta']
}
   ,'OPERATORS' :[
		'*', '+', '-', '/', '^', ':=', '<', '=', '>'
	]
	,'DELIMITERS' :[
		'(', ')', '[', ']','{','}','\(', '\)'
	]
	,
	'STYLES' : {
		'COMMENTS': 'color: #0000CD;'
		,'QUOTESMARKS': 'color: #6381F8;'
		,'KEYWORDS' : {
			'gpstatement' : 'color: #e52d2d;'
			,'gpconditional' : 'color: #FF00FF;'
			,'gprepeat' : 'color: #CD00CD;'
			,'gpscope' : 'color: #00CD00;'
			,'gpdefaults' : 'color: #00CD00;'
			,'gpinterface' : 'color: #00CD00;'
			,'gpinput' : 'color: #00CD00;'
			,'gpfunction' : 'color: #FF3A6E;'
			}
		,'OPERATORS' : 'color: #CD00CD;'
		,'DELIMITERS' : 'color: #60CA00;'
		}
};