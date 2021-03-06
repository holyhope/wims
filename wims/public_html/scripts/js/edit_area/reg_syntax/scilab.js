
editAreaLoader.load_syntax['scilab'] = {
    'QUOTEMARKS' : {1: ' " '}
   ,'COMMENT_SINGLE' : {1 : '\\'}
	,'COMMENT_MULTI' : {'/\*' : '\*/'}
	,'KEYWORD_CASE_SENSITIVE' : true
	,'KEYWORDS' : {
	 'scilab' : ['abcd','abinv','abort','abs','acoshm','acosh','acosm','acos','addcolor',
'addf','addinter','addmenu','add_edge','add_node','adj2sp','adj_lists','aff2ab',
'amell','analpf','analyze','ans','apropos','arc_graph','arc_number','argn','arhnk',
'arl2','arma2p','armac','armax1','armax','arma','arsimul','artest','articul','ascii',
'asinhm','asinh','asinm','asin','atanhm','atanh','atanm','atan','augment','auread',
'auwrite','balanc','balreal','bandwr','basename','bdiag','besseli','besselj',
'besselk','bessely','best_match','bezout','bifish','bilin','binomial','black',
'bloc2exp','bloc2ss','bode','bool2s','boolean','boucle','break','bstap','buttmag',
'bvode','cainv','calerf','calfrq','call','canon','casc','case','ccontrg','cdfbet',
'cdfbin','cdfchi','cdfchn','cdffnc','cdff','cdfgam','cdfnbn','cdfnor','cdfpoi',
'cdft','ceil','center','cepstrum','chaintest','chain_struct','champ1','champ',
'chart','chdir','cheb1mag','cheb2mag','check_graph','check_io','chepol','chfact',
'chol','chsolve','circuit','classmarkov','clean','clearfun','clearglobal',
'clear','close','cls2dls','cmb_lin','cmndred','cmoment','code2str','coeff','coffg',
'coff','colcompr','colcomp','colinout','colormap','colregul','companion','comp',
'cond','conj','connex','contour2di','contour2d','contourf','contour',
'contract_edge','contrss','contr','cont_frm','cont_mat','convex_hull','convol',
'convstr','con_nodes','copfac','copy','correl','corr','coshm','cosh','cosm','cos',
'cotg','cothm','coth','covar','csim','cspect','ctr_gram','cumprod','cumsum',
'curblock','cycle_basis','czt','c_link','dasrt','dassl','datafit','date','dbphi',
'dcf','ddp','debug','dec2hex','deff','definedfields','degree','delbpt',
'delete_arcs','delete_nodes','delete','delip','delmenu','demos','denom',
'derivative','derivat','des2ss','des2tf','determ','detr','det','dft','dhinf',
'dhnorm','diag','diary','diff','diophant','dirname','dispbpt','dispfiles','disp',
'dlgamma','double','dragrect','drawaxis','drawlater','drawnow','draw','driver',
'dscr','dsearch','dsimul','dtsi','dt_ility','duplicate','edge_number',
'edit_curv','edit_graph_menus','edit_graph','edit','eigenmarkov','ell1mag',
'elseif','else','emptystr','endfunction','end','eqfir','eqiir','equil1','equil',
'ereduc','erfcx','erfc','erf','errbar','errcatch','errclear','error','eval3dp',
'eval3d','eval','evans','evstr','excel2sci','execstr','exec','exists','exit','expm',
'exp','external','eye','fac3d','factors','faurre','fchamp','fcontour2d','fcontour',
'fec','feedback','feval','ffilt','fftshift','fft','fgrayplot','figure','fileinfo',
'file','filter','findm','findobj','findx0BD','find_freq','find_path','find',
'findABCD','findAC','findBD','findBDK','findR','fit_dat','fix','floor','flts','foo',
'formatman','format','fort','for','fourplan','fplot2d','fplot3d1','fplot3d',
'fprintf','fprintfMat','frep2tf','freq','freson','frexp','frfit','frmag','fscanf',
'fscanfMat','fsfirlin','fsolve','fspecg','fstabst','fstair','ftest','ftuneq',
'fullrfk','fullrf','full','fun2string','funcprot','functions','function',
'funptr','fusee','gainplot','gamitg','gammaln','gamma','gcare','gcd','gcf',
'genfac3d','genlib','genmarkov','gen_net','geom3d','geomean','getblocklabel',
'getcolor','getcurblock','getcwd','getdate','getd','getenv','getfield','getfont',
'getf','getio','getlinestyle','getmark','getpid','getscicosvars','getsymbol',
'getvalue','getversion','get_function_path','get','gfare','gfrancis','girth',
'givens','glever','glist','global','glue','gpeche','graduate','grand',
'graphics_entities','graph_2_mat','graph_center','graph_complement',
'graph_diameter','graph_power','graph_simp','graph_sum','graph_union',
'graph-list','graycolormap','grayplot','graypolarplot','grep','group',
'gr_menu','gschur','gsort','gspec','gstacksize','gtild','g_margin','h2norm','halt',
'hamilton','hankelsv','hank','harmean','havewindow','help','hermit','hess',
'hex2dec','hilb','hinf','hist3d','histplot','horner','host','hotcolormap',
'householder','hrmt','htrianr','hypermat','h_cl','h_inf_st','h_inf','h_norm',
'iconvert','icon_edit','ieee','if','iirgroup','iirlp','iir','ilib_build',
'ilib_compile','ilib_for_link','ilib_gen_gateway','ilib_gen_loader',
'ilib_gen_Make','imag','impl','imrep2ss','imult','im_inv','inistate','input',
'int16','int2d','int32','int3d','int8','intc','intdec','integrate','interpln',
'interp','intersci','intersect','intg','intl','intppty','intsplin','inttrap',
'inttype','int','invr','invsyslin','inv_coeff','inv','iqr','isdef','isdir','isequal',
'iserror','isglobal','isinf','isnan','isoview','isreal','is_connex','jmat',
'justify','kalm','karmarkar','kernel','keyboard','knapsack','kpure','krac2',
'kroneck','kron','lasterror','lattn','lattp','lcf','lcmdiag','lcm','ldivf','ldiv',
'leastsq','legends','length','leqr','levin','lev','lex_sort','lft','lgfft','library',
'lib','lin2mu','lincos','lindquist','lines','line_graph','linfn','linf','link',
'linmeq','linpro','linsolve','linspace','lin','listfiles','list','lmisolver',
'lmitool','loadmatfile','loadplots','loadwave','load_graph','load','locate',
'log10','log1p','log2','logm','logspace','log','lotest','lqe','lqg2stan','lqg_ltr',
'lqg','lqr','lsq','lsslist','lstcat','lstsize','ltitr','ludel','lufact','luget',
'lusolve','lu','lyap','macglov','macr2lst','macrovar','macro','mad','make_graph',
'make_index','manedit','man','mapsound','markp2ss','matfile2sci','matrix',
'mat_2_graph','maxi','max_cap_path','max_clique','max_flow','max','mclearerr',
'mclose','meanf','mean','median','meof','mese','mesh2d','mfft','mfile2sci','mgeti',
'mgetl','mgetstr','mget','milk_drop','mine','mini','minreal','minss',
'min_lcost_cflow','min_lcost_flow1','min_lcost_flow2','min_qcost_flow',
'min_weight_tree','min','mlist','mode','modulo','moment','mopen','move',
'mps2linpro','mputl','mputstr','mput','mrfit','msd','mseek','mtell','mtlb_load',
'mtlb_mode','mtlb_save','mtlb_sparse','mu2lin','mulf','mvvacov','m_circle',
'names','nand2mean','nanmax','nanmeanf','nanmean','nanmedian','nanmin',
'nanstdev','nansum','narsimul','ndims','nearfloat','nehari','neighbors',
'netclose','netwindows','netwindow','newest','newfun','nextpow2','nf3d','nfreq',
'nlev','nnz','nodes_2_path','nodes_degrees','node_number','noisegen','norm',
'null','numdiff','numer','nyquist','obscont1','obscont','observer','obsvss',
'obsv_mat','obs_gram','odedc','odedi','odeoptions','ode_discrete','ode_root',
'ode','oldload','oldsave','ones','optim','orth','param3d1','param3d',
'paramfplot2d','parrot','part','pathconvert','path_2_nodes','pause','pbig',
'pdiv','pen2ea','pencan','penlaur','perctl','perfect_match','pertrans','pfss',
'phasemag','phc','pinv','pipe_network','playsnd','plot2d1','plot2d2','plot2d3',
'plot2d4','plot2d','plot3d1','plot3d2','plot3d3','plot3d','plotframe',
'plotprofile','plot_graph','plot','plzr','pmodulo','pol2des','pol2str','pol2tex',
'polarplot','polar','polfact','poly','portr3d','portrait','power','ppol','prbs_a',
'predecessors','predef','printf','printing','print','prod','profile','projsl',
'projspec','proj','psmall','pspect','pvm_addhosts','pvm_barrier','pvm_bcast',
'pvm_bufinfo','pvm_config','pvm_delhosts','pvm_error','pvm_exit',
'pvm_f772sci','pvm_getinst','pvm_gettid','pvm_get_timer','pvm_gsize',
'pvm_halt','pvm_joingroup','pvm_kill','pvm_lvgroup','pvm_mytid','pvm_parent',
'pvm_probe','pvm_recv','pvm_reduce','pvm_sci2f77','pvm_send','pvm_set_timer',
'pvm_spawn_independent','pvm_spawn','pvm_start','pvm_tasks',
'pvm_tidtohost','pvm','pwd','p_margin','qassign','qr','quapro','quart','quaskro',
'quit','randpencil','rand','range','rankqr','rank','rat','rcond','rdivf','read4b',
'readb','readc_','readmps','read','real','recur','reglin','regress','remezb','remez',
'repfreq','replot','residu','resume','return','riccati','riccsl','ricc','ric_desc',
'rlist','roots','rotate','round','routh_t','rowcompr','rowcomp','rowinout',
'rowregul','rowshuff','rpem','rref','rtitr','rubberbox','salesman','savewave',
'save_graph','save','scaling','scanf','schur','sci2exp','sci2for','sci2map',
'sciargs','scicosim','scicos','scifunc_block','sd2sci','secto3d','select',
'semidef','sensi','setbpt','seteventhandler','setfield','setmenu',
'setscicosvars','set','sfact','sgrid','shortest_path','showprofile',
'show_arcs','show_graph','show_nodes','sident','signm','sign','simp_mode','simp',
'sincd','sinc','sinc','sinhm','sinh','sinm','sin','size','sm2des','sm2ss','smooth',
'solve','sorder','sort','sound','sp2adj','spaninter','spanplus','spantwo','sparse',
'spchol','spcompack','specfact','spec','speye','spget','splin','split_edge',
'spones','sprand','sprintf','spzeros','sqroot','sqrtm','sqrt','squarewave',
'square','srfaur','srkf','ss2des','ss2ss','ss2tf','sscanf','sskf','ssprint','ssrand',
'stabil','stacksize','standard_define','standard_draw','standard_input',
'standard_origin','standard_output','startup','stdevf','stdev','steadycos',
'str2code','strange','strcat','strindex','strings','string','stripblanks',
'strong_connex','strong_con_nodes','strsubst','st_deviation','st_ility',
'subf','subgraph','subplot','successors','sum','supernode','sva','svd','svplot',
'sylm','sylv','sysconv','sysdiag','sysfact','syslin','syssize','systems','system',
'systmat','tabul','tangent','tanhm','tanh','tanm','tan','tdinit','testmatrix',
'texprint','tf2des','tf2ss','then','thrownan','timer','time_id','titlepage',
'tk_getdir','tk_getfile','tlist','toeplitz','tokenpos','tokens','trace',
'translatepaths','trans_closure','trans','trfmod','trianfml','tril','trimmean',
'trisolve','triu','trzeros','typename','typeof','type','uicontrol','uimenu',
'uint16','uint32','uint8','ui_observer','ulink','unglue','union','unique','unix_g',
'unix_s','unix_w','unix_x','unix','unobs','unsetmenu','user','varargin',
'varargout','variancef','variance','varn','warning','wavread','wavwrite',
'wcenter','wfir','what','whereami','whereis','where','while','whos','who_user','who',
'wiener','wigner','window','winsid','with_gtk','with_pvm','with_texmacs',
'with_tk','writb','write4b','write','xarcs','xarc','xarrows','xaxis','xbasc',
'xbasimp','xbasr','xchange','xclear','xclea','xclick','xclip','xdel','xend','xfarcs',
'xfarc','xfpolys','xfpoly','xfrect','xgetech','xgetfile','xgetmouse','xget',
'xgraduate','xgrid','xinfo','xinit','xlfont','xload','xname','xnumb','xpause',
'xpolys','xpoly','xrects','xrect','xrpoly','xs2fig','xs2gif','xs2ppm','xs2ps',
'xsave','xsegs','select','xsetech','xsetm','xset','xstringb','xstringl','xstring',
'xtape','xtitle','x_choices','x_choose','x_dialog','x_matrix','x_mdialog',
'x_message_modeless','x_message','yulewalk','zeropen','zeros','zgrid','zpbutt',
'zpch1','zpch2','zpell','mfprintf','mfscanf','mprintf','mscanf','msprintf',
'msscanf','mucomp',
'ABSBLK_f','AFFICH_f','ANDLOG_f','ANIMXY_f','BIGSOM_f','CLINDUMMY_f','CLKIN_f',
'CLKINV_f','CLKOUT_f','CLKOUTV_f','CLKSOM_f','CLKSOMV_f','CLKSPLIT_f',
'CLOCK_f','CLR_f','CLSS_f','CONST_f','COSBLK_f','CURV_f','DELAY_f','DELAYV_f',
'DEMUX_f','DLR_f','DLRADAPT_f','DLSS_f','EVENTSCOPE_f','EVTDLY_f','EVTGEN_f',
'EXPBLK_f','G_make','GAIN_f','GAINBLK_f','GENERAL_f','GENERIC_f','GENSIN_f',
'GENSQR_f','HALT_f','IFTHEL_f','IN_f','INTEGRAL_f','INTRP2BLK_f','INTRPLBLK_f',
'INVBLK_f','LOGBLK_f','LOOKUP_f','Matplot1','Matplot','MAX_f','MCLOCK_f',
'MFCLCK_f','MIN_f','MUX_f','NDcost','NEGTOPOS_f','OUT_f','POSTONEG_f','POWBLK_f',
'PROD_f','QUANT_f','RAND_f','READC_f','REGISTER_f','RELAY_f','RFILE_f',
'ScilabEval','Sfgrayplot','Sgrayplot','SAMPLEHOLD_f','SAT_f','SAWTOOTH_f',
'SCOPE_f','SCOPXY_f','SELECT_f','SINBLK_f','SOM_f','SPLIT_f','STOP_f','SUPER_f',
'TANBLK_f','TCLSS_f','TEXT_f','TIME_f','TK_EvalFile','TK_EvalStr','TK_GetVar',
'TK_SetVar','TRASH_f','WFILE_f','WRITEC_f','ZCROSS_f']
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
			'scilab' : 'color: #3399FF;'
			}
		,'OPERATORS' : 'color: #CD00CD;'
		,'DELIMITERS' : 'color: #60CA00;'
		}
};
