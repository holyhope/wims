var slib= [ 'chemistry/brut2html', 'chemistry/chemeq_add', 'chemistry/chemeq_compare', 'chemistry/chemeq_components', 'chemistry/chemeq_el', 'chemistry/chemeq_equilibrium', 'chemistry/chemeq_mass', 'chemistry/chemeq_rev', 'chemistry/chemeq_rq', 'chemistry/chemeq_tex', 'chemistry/chemshow', 'chemistry/jmolbutton', 'chemistry/jmolcheckbox', 'chemistry/jmolradiogroup', 'chemistry/jmolshow', 'chemistry/molarmass', 'chemistry/molecule', 'chemistry/moleculeViewer', 'circuits/complist', 'circuits/comppos', 'circuits/draw', 'circuits/drawcomp', 'circuits/drawwire', 'circuits/range', 'data/columnsort', 'data/randline', 'data/random', 'data/randrec', 'draw/brokenlinegraph', 'draw/clock', 'draw/convpixel', 'draw/domino', 'draw/drtgraduee', 'draw/graphviz', 'draw/graphvizpoints', 'draw/range', 'draw/repdroite', 'draw/repere', 'function/bounds', 'function/bounds2', 'function/integrate', 'geo2D/carmetal', 'geo2D/geogebra3', 'geo3D/3Dviewer', 'geo3D/CaR', 'geo3D/Convex3D', 'geo3D/draw', 'geo3D/off2jmol', 'geo3D/off2jmol2', 'geo3D/off2xyz', 'geo3D/polyhedra', 'geo3D/polyhedradual', 'geo3D/threeD', 'graph/connexcomponent', 'graph/connexity', 'graph/distance', 'graph/draw', 'graph/drawcc', 'graph/drawtree', 'graph/gpt', 'graph/graphviz', 'graph/randomconnex', 'graph/randomeuler', 'graph/randtree', 'graph/shortpath', 'graphpaper/correct_milli', 'graphpaper/func', 'graphpaper/func_milli', 'graphpaper/imgpoints', 'graphpaper/millimetre', 'graphpaper/strings', 'graphpaper/tograph', 'graphpaper/whereclick', 'lang/enword2ipa', 'lang/epd2ipa', 'lang/fname', 'lang/fraccord', 'lang/frapostrophe', 'lang/frartdef', 'lang/frcodcoi', 'lang/frverbconj', 'lang/frword2ipa', 'lang/images', 'lang/lex2ipa', 'lang/randomword', 'lang/sampa2ipa', 'lang/swac', 'life/frcommodity', 'list/selshuf', 'matrix/concate', 'matrix/det', 'matrix/givenrank', 'matrix/inverse', 'matrix/invertible', 'matrix/itriangular', 'matrix/non0', 'matrix/orthogonal', 'matrix/random', 'matrix/trace', 'matrix/transpose', 'matrix/triangular', 'matrix/unimodular', 'media/audio', 'media/dewplayer', 'media/player', 'media/player_mp3_multi', 'media/video', 'numeration/ecriturenombre', 'oef/codelim', 'oef/codename', 'oef/env', 'oef/getopt', 'oef/insfilename', 'oef/newfile', 'oef/postsrc', 'oef/presrc', 'polynomial/random', 'stat/1d', 'stat/arithmean', 'stat/beta', 'stat/betacdf', 'stat/betainv', 'stat/betapdf', 'stat/binomial', 'stat/binomialcdf', 'stat/binomialinv', 'stat/binomialpdf', 'stat/cauchy', 'stat/cauchycdf', 'stat/cauchyinv', 'stat/cauchypdf', 'stat/chi2', 'stat/chi2cdf', 'stat/chi2inv', 'stat/chi2pdf', 'stat/correlation', 'stat/covariance', 'stat/deviation', 'stat/discretelaw', 'stat/effectif', 'stat/empiric', 'stat/expo', 'stat/exponential', 'stat/exponentialcdf', 'stat/exponentialinv', 'stat/exponentialpdf', 'stat/fisher', 'stat/fishercdf', 'stat/fisherinv', 'stat/fisherpdf', 'stat/freq', 'stat/gamma', 'stat/gammacdf', 'stat/gammainv', 'stat/gammapdf', 'stat/geomean', 'stat/geometric', 'stat/geometric1', 'stat/geometric1cdf', 'stat/geometric1inv', 'stat/geometric1pdf', 'stat/geometriccdf', 'stat/geometricinv', 'stat/geometricpdf', 'stat/harmonic', 'stat/histo', 'stat/hypergeometric', 'stat/hypergeometriccdf', 'stat/hypergeometricinv', 'stat/hypergeometricpdf', 'stat/hypergeominv', 'stat/laplace', 'stat/laplacecdf', 'stat/laplaceinv', 'stat/laplacepdf', 'stat/linearcong', 'stat/logistic', 'stat/logisticcdf', 'stat/logisticinv', 'stat/logisticpdf', 'stat/lognormal', 'stat/lognormalcdf', 'stat/lognormalinv', 'stat/lognormalpdf', 'stat/median', 'stat/multinomial', 'stat/normal', 'stat/normalcdf', 'stat/normalinv', 'stat/normalpdf', 'stat/pascal', 'stat/pascalcdf', 'stat/pascalinv', 'stat/pascalpdf', 'stat/poisson', 'stat/poissoncdf', 'stat/poissoninv', 'stat/poissonpdf', 'stat/posdiscretelaw', 'stat/prod', 'stat/quadratic', 'stat/random', 'stat/range', 'stat/student', 'stat/studentcdf', 'stat/studentinv', 'stat/studentpdf', 'stat/sum', 'stat/variance', 'stat/weibull', 'stat/weibullcdf', 'stat/weibullinv', 'stat/weibullpdf', 'text/approximation', 'text/cdecomment', 'text/cutchoice2', 'text/cutchoices', 'text/markerror', 'text/markgroup', 'text/marktext', 'text/marktextpartial', 'text/markword', 'text/matrixtex', 'text/maximamatrix', 'text/octavematrix', 'text/sigunits', 'text/spirale', 'text/whitespace', 'triplerelation/tabular', 'utilities/nopaste', 'utilities/notepad', 'utilities/tooltip' ];
function bd(instruction, version){
    switch(instruction)
	{
	case 'chemistry/brut2html' :
chaine_aide='<code>slib(chemistry/brut2html )</code>'+
'<div class="title">HTML form </div>'+
'<div class="out"> Give the html code for a molecule in a brut form </div>'+
'<div class="example"><code>slib(chemistry/brut2html  COCl2)</code></div><div class="example"><code>slib(chemistry/brut2html  NH2^+  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_add' :
chaine_aide='<code>slib(chemistry/chemeq_add )</code>'+
'<div class="title">Computes a combination of chemical equations </div>'+
'<div class="out"> A combination of the given chemical equations. <br> Use  positive coefficients to add an equation, negative coefficients to add a reversed equation.<br> The coefficients can be fractions. </div>'+
'<div class="example"><code>slib(chemistry/chemeq_add  1/2,Cr2O7^2- + 14H^+ + 6e^- -> 2 Cr^3+ + 7H2O,-3,Fe^3+ + e^- -> Fe^2+ )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_compare' :
chaine_aide='<code>slib(chemistry/chemeq_compare )</code>'+
'<div class="title">Comparing chemical equations </div>'+
'<div class="out"> a message (which defaults to "good" or "bad"). </div>'+
'<div class="example"><code>slib(chemistry/chemeq_compare  H2 + O2 -> H2O, 2H2 + O2 -> 2H2O )</code></div><div class="example"><code>slib(chemistry/chemeq_compare  2H2 + O2 -> 2H2O, 2H2_g + O2_g -> 2H2O )</code></div><div class="example"><code>slib(chemistry/chemeq_compare  H2 + 1/2 O2 -> H2O, 2H2 + O2 -> 2H2O )</code></div><div class="example"><code>slib(chemistry/chemeq_compare  Fe + Cu^2+ -> Fe^2+ + Cu, Fe + Cu^2+ -> Fe^2+ + Cu )</code></div><div class="example"><code>slib(chemistry/chemeq_compare  Ag^+ + 1/2 SO4^2- -> 1/2 Ag2(SO4), 2Ag^+ + SO4^2- -> Ag2(SO4) )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_components' :
chaine_aide='<code>slib(chemistry/chemeq_components )</code>'+
'<div class="title">Chemical components </div>'+
'<div class="out"> Outputs a matrix of the reactives in the first line, and the products in  the second line. <br>If the parameter \'htmlbuttons\' is specified, the output  is some code to make clickable buttons; then, the number refers to a reply  field which will receive the results of the buttons\' events. <br>If the  parameter \'shuffle\' is specified, the buttons are shuffled. <br>These buttons  can be made active if the following javascript code is added in the page:  <pre style="color:green;"> &lt;script type="text/javascript"&gt; function getInput(n){   f=window.document.forms[0];   for(i=0; i&lt;f.elements.length; i=i+1){     if (f.elements[i].name=="reply"+n) {        return f.elements[i];     }   }   return null; } function appendToInput(n,msg){   var i=getInput(n);   i.value=i.value+msg+\' \';   i.focus(); } &lt;/script&gt; </pre>  </div>'+
'<div class="example"><code>slib(chemistry/chemeq_components  MnO4^- + 5 e^- + 8H^+ -> Mn^2+ + 4H2O )</code></div><div class="example"><code>slib(chemistry/chemeq_components  MnO4^- + 5 e^- + 8H^+ -> Mn^2+ + 4H2O, htmlbuttons 3 )</code></div><div class="example"><code>slib(chemistry/chemeq_components  MnO4^- + 5 e^- + 8H^+ -> Mn^2+ + 4H2O, htmlbuttons 3,,[extra,redox_extra] )</code></div><div class="example"><code>slib(chemistry/chemeq_components  MnO4^- + 5 e^- + 8H^+ -> Mn^2+ + 4H2O, htmlbuttons 2, shuffle,[extra] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_el' :
chaine_aide='<code>slib(chemistry/chemeq_el )</code>'+
'<div class="title">Returns the number of electrons in a redox reaction </div>'+
'<div class="out"> number of electrons found on either side of the equation </div>'+
'<div class="example"><code>slib(chemistry/chemeq_el  Cr2O7^2- + 14H^+ + 6e^- -> 2 Cr^3+ + 7H2O)</code></div><div class="example"><code>slib(chemistry/chemeq_el  Fe^3+ + e^- -> Fe^2+ )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_equilibrium' :
chaine_aide='<code>slib(chemistry/chemeq_equilibrium )</code>'+
'<div class="title">Analysing the equilibrium in chemical formulas </div>'+
'<div class="out"> a matrix or a table whose lines help to check the equilibrium  of the given equation. </div>'+
'<div class="example"><code>slib(chemistry/chemeq_equilibrium  H2_g + O2_g -> H2O, state, html )</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  H2_g + O2_g -> H2O )</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  H2_g + 1/2O2_g -> H2O, nostate, html )</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  H2_g + 1/2O2_g -> H2O, nostate )</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  BH3_s + 3H2O -> B(OH)3 + 3H2_g, state, html)</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  MnO4^- + 8H^+ + 5e^- -> Mn^2+ + 4H2O, nostate, html )</code></div><div class="example"><code>slib(chemistry/chemeq_equilibrium  MnO4^- + 8H^+ + 5e^- -> Mn^2+ + 4H2O )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_mass' :
chaine_aide='<code>slib(chemistry/chemeq_mass )</code>'+
'<div class="title">Molar Mass </div>'+
'<div class="out"> molar mass </div>'+
'<div class="example"><code>slib(chemistry/chemeq_mass  H2)</code></div><div class="example"><code>slib(chemistry/chemeq_mass  CH4)</code></div><div class="example"><code>slib(chemistry/chemeq_mass  HCO3^-)</code></div><div class="example"><code>slib(chemistry/chemeq_mass  Fe2(SO4)3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_rev' :
chaine_aide='<code>slib(chemistry/chemeq_rev )</code>'+
'<div class="title">Returns a chemical equation reversed </div>'+
'<div class="out"> the chemical equation, reversed </div>'+
'<div class="example"><code>slib(chemistry/chemeq_rev  Cr2O7^2- + 14H^+ + 6e^- -> 2 Cr^3+ + 7H2O)</code></div><div class="example"><code>slib(chemistry/chemeq_rev  Fe^3+ + e^- -> Fe^2+ )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_rq' :
chaine_aide='<code>slib(chemistry/chemeq_rq )</code>'+
'<div class="title">Typeset reaction quotients and Nernst laws for chemical equations </div>'+
'<div class="out"> a TeX source to be fed into !instex to typeset the molecule nicely. </div>'+
'<div class="example"><code>slib(chemistry/chemeq_rq  Cu^2+ + 2e- -> Cu_s (0.34 V) ~ Fe^2+ + 2e- -> Fe_s (-1.44 V))</code></div><div class="example"><code>slib(chemistry/chemeq_rq  Fe^2+ + 2e- -> Fe_s (-0.44 V))</code></div><div class="example"><code>slib(chemistry/chemeq_rq  H2_g + 1/2 O2_g -> H2O)</code></div><div class="example"><code>slib(chemistry/chemeq_rq  N2_g + 3H2_g -> NH3_g (Kp=1e-6) )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemeq_tex' :
chaine_aide='<code>slib(chemistry/chemeq_tex )</code>'+
'<div class="title">Typeset molecules and chemical equations </div>'+
'<div class="out"> a TeX source to be fed into !instex to typeset the molecule nicely. </div>'+
'<div class="example"><code>slib(chemistry/chemeq_tex  H2)</code></div><div class="example"><code>slib(chemistry/chemeq_tex  C2H6)</code></div><div class="example"><code>slib(chemistry/chemeq_tex  HCO3^-)</code></div><div class="example"><code>slib(chemistry/chemeq_tex  Fe^3+ + 6CN^- -> Fe(CN)6^3- )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/chemshow' :
chaine_aide='<code>slib(chemistry/chemshow )</code>'+
'<div class="title">Dessin d\'une molécule en 2D </div>'+
'<div class="out">applet code for inserting WIMSChem </div>'+
'<div class="example"><code>slib(chemistry/chemshow  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/jmolbutton' :
chaine_aide='<code>slib(chemistry/jmolbutton )</code>'+
'<div class="title">Button in Jmol </div>'+
'<div class="out">applet code for inserting jmol button </div>'+
'<div class="example"><code>slib(chemistry/jmolbutton select all;color atoms blue; select none,Bleu )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/jmolcheckbox' :
chaine_aide='<code>slib(chemistry/jmolcheckbox )</code>'+
'<div class="title">Checkbox Button in Jmol </div>'+
'<div class="out">applet code for inserting jmol applet </div>'+
'<div class="example"><code>slib(chemistry/jmolcheckbox select all;color atoms blue; select none)</code></div><div class="example"><code>slib(chemistry/jmolcheckbox  bleu )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/jmolradiogroup' :
chaine_aide='<code>slib(chemistry/jmolradiogroup )</code>'+
'<div class="title">Radio Group in Jmol </div>'+
'<div class="out">applet code for inserting jmol applet </div>'+
'<div class="example"><code>slib(chemistry/jmolradiogroup select all;color atoms blue; select none)</code></div><div class="example"><code>slib(chemistry/jmolradiogroup  bleu )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/jmolshow' :
chaine_aide='<code>slib(chemistry/jmolshow )</code>'+
'<div class="title">Jmol Applet </div>'+
'<div class="out">applet code for inserting jmol applet </div>'+
'<div class="example"><code>slib(chemistry/jmolshow data/molecule_pdb/reseau1.pdb)</code></div><div class="example"><code>slib(chemistry/jmolshow  data/molecule_pdb/xeo2f2.pdb)</code></div><div class="example"><code>slib(chemistry/jmolshow  datamodule/chemistry/mol2D.fr/data/60_18_4.mol )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/molarmass' :
chaine_aide='<code>slib(chemistry/molarmass )</code>'+
'<div class="title">Molar Mass </div>'+
'<div class="out"> molar mass </div>'+
'<div class="example"><code>slib(chemistry/molarmass  H2)</code></div><div class="example"><code>slib(chemistry/molarmass  C H4  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/molecule' :
chaine_aide='<code>slib(chemistry/molecule )</code>'+
'<div class="title">Periodic table </div>'+
'<div class="out"> for each  atom of the molecule M, a line with  number of atoms in M, name,symbol,Z,molar mass and other things ! </div>'+
'<div class="example"><code>slib(chemistry/molecule  H2)</code></div><div class="example"><code>slib(chemistry/molecule  C H4)</code></div><div class="example"><code>slib(chemistry/molecule  N2 0  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'chemistry/moleculeViewer' :
chaine_aide='<code>slib(chemistry/moleculeViewer )</code>'+
'<div class="title">Java Molecule Viewer </div>'+
'<div class="out">applet code for visualizing molecule. The java applet used is  LatticeViewer. Extract from the source : <pre>  LatticeViewer.java  Date :       18th Feb 1998	  Adapted by : Simon P.A.Gill  http://www.le.ac.uk/engineering/spg3/lattice/  The following java code is an adaptation of the Molecule Viewer XYZApp.java  freely distributed by Sun Microsystems. The conditions stated below apply  to this code. S.P.A. Gill takes no responsibility for this code.   Requires class Matrix3D.java (also from Sun at  http://www.javasoft.com:80/applets/js-applets.html)  </pre> </div>'+
'<div class="example"><code>slib(chemistry/moleculeViewer c2h2f2,label=false scale=0.8 height=300 width=300)</code></div><div class="example"><code>slib(chemistry/moleculeViewer  cl2o,label=true scale=1 height=300 width=300 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/complist' :
chaine_aide='<code>slib(circuits/complist )</code>'+
'<div class="title">List available circuit components </div>'+
'<div class="out">comma-separated list of component names. </div>'+
'<div class="example"><code>slib(circuits/complist  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/comppos' :
chaine_aide='<code>slib(circuits/comppos )</code>'+
'<div class="title">Component position information of a circuit type. </div>'+
'<div class="out">A matrix </div>'+
'<div class="example"><code>slib(circuits/comppos 9/br3close )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/draw' :
chaine_aide='<code>slib(circuits/draw )</code>'+
'<div class="title">Draw circuit scheme according a circuit type. </div>'+
'<div class="out">drawing commands for flydraw. </div>'+
'<div class="example"><code>slib(circuits/draw 5/br2out,,,acsrc,diode,cap,res,chas )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/drawcomp' :
chaine_aide='<code>slib(circuits/drawcomp )</code>'+
'<div class="title">Draw circuit components according to a circuit type. </div>'+
'<div class="out">drawing commands for flydraw. </div>'+
'<div class="example"><code>slib(circuits/drawcomp 5/br2out,,,acsrc,diode,cap,res )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/drawwire' :
chaine_aide='<code>slib(circuits/drawwire )</code>'+
'<div class="title">Draw the fixed circuit wiring of a given circuit type. </div>'+
'<div class="out">drawing commands for flydraw. </div>'+
'<div class="example"><code>slib(circuits/drawwire 5/br2out,2,6,blue,medium )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'circuits/range' :
chaine_aide='<code>slib(circuits/range )</code>'+
'<div class="title">Size and range information of a circuit type. </div>'+
'<div class="out">Comma-separated list of items. </div>'+
'<div class="example"><code>slib(circuits/range 9/br3close )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'data/columnsort' :
chaine_aide='<code>slib(data/columnsort )</code>'+
'<div class="title">Sort data according to a column </div>'+
'<div class="out">the sorted data </div>'+
'<div class="example"><code>slib(data/columnsort  3,nocase, 3,5,oui;caen, arles,nice;paris,nice,caen)</code></div><div class="example"><code>slib(data/columnsort  2,numeric, 3,5,oui;caen, 6,non;paris,1,oui )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'data/randline' :
chaine_aide='<code>slib(data/randline )</code>'+
'<div class="title">Take a random line of a data file </div>'+
'<div class="out">the random line (empty if error) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'data/random' :
chaine_aide='<code>slib(data/random )</code>'+
'<div class="title">Randomly selects a number of (different) objects </div>'+
'<div class="out">the randomly select objects </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'data/randrec' :
chaine_aide='<code>slib(data/randrec )</code>'+
'<div class="title">Take a random field of a record file </div>'+
'<div class="out">the random field (empty if error) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/brokenlinegraph' :
chaine_aide='<code>slib(draw/brokenlinegraph )</code>'+
'<div class="title">Trace une fonction affine par morceaux continue en connaissant les points de changement de pente </div>'+
'<div class="out">Les données pour insdraw (draw) </div>'+
'<div class="example"><code>slib(draw/brokenlinegraph 200,200,10,[[0,0],[8,8]],[[0,0],[1,1],[3,0],[0,5],[2,3]],black,grey,red,x,y )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/clock' :
chaine_aide='<code>slib(draw/clock )</code>'+
'<div class="title">Draw a clock according to given time </div>'+
'<div class="out">Source for insdraw </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/convpixel' :
chaine_aide='<code>slib(draw/convpixel )</code>'+
'<div class="title">Conversion pixels </div>'+
'<div class="out"> </div>'+
'<div class="example"><code>slib(draw/convpixel  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/domino' :
chaine_aide='<code>slib(draw/domino )</code>'+
'<div class="title">Domino </div>'+
'<div class="out">code flydraw for a domino </div>'+
'<div class="example"><code>slib(draw/domino 5,3,red,H)</code></div><div class="example"><code>slib(draw/domino  5,0,red,V,Text )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/drtgraduee' :
chaine_aide='<code>slib(draw/drtgraduee )</code>'+
'<div class="title">Droite graduée </div>'+
'<div class="out">Les données pour insdraw. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/graphviz' :
chaine_aide='<code>slib(draw/graphviz )</code>'+
'<div class="title">Graphviz </div>'+
'<div class="out">in the case where the format is dot, output the url address of the image, in the case there is no format, output the code to show the image : &lt;img src=...> ; in the case where the format is jpg, give the coordinates </div>'+
'<div class="example"><code>slib(draw/graphviz digraph bar {1 -> 1 ; 2 -> 1 ; 1 -> 2 ; 3 -> 2  ; 2 -> 3  ;},png dot url)</code></div><div class="example"><code>slib(draw/graphviz  digraph bar {1 -> 1 ; 2 -> 1 ; 1 -> 2 ; 3 -> 2  ; 2 -> 3  ;},url neato)</code></div><div class="example"><code>slib(draw/graphviz  digraph bar {1 -> 1 ; 2 -> 1 ; 1 -> 2 ; 3 -> 2  ; 2 -> 3  ;},png)</code></div><div class="example"><code>slib(draw/graphviz  digraph bar {1 -> 1 ; 2 -> 1 ; 1 -> 2 ; 3 -> 2  ; 2 -> 3  ;},plain)</code></div><div class="example"><code>slib(draw/graphviz  digraph bar {1 -> 1 ; 2 -> 1 ; 1 -> 2 ; 3 -> 2  ; 2 -> 3  ;},png )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/graphvizpoints' :
chaine_aide='<code>slib(draw/graphvizpoints )</code>'+
'<div class="title">Graphviz </div>'+
'<div class="out">the coordinates in pixels of the nodes of a graph  which has been just created by graphviz, one node by line. The first line is  the size in pixels of the image. On each line, the items from 2 to the end should be the text in the nodes (no garanty).  </div>'+
'<div class="example"><code>slib(draw/graphvizpoints    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/range' :
chaine_aide='<code>slib(draw/range )</code>'+
'<div class="title">Range </div>'+
'<div class="out"> reasonable range A,B,C,D such that all points of the list are in the range [A,B] times [C,D] with B - A = D - C </div>'+
'<div class="example"><code>slib(draw/range  1,2,0,2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/repdroite' :
chaine_aide='<code>slib(draw/repdroite )</code>'+
'<div class="title">Calcule les coordonnées des deux points extr&ecirc;mes pour tracer une droite dans un repère </div>'+
'<div class="out">Deux lignes comportant chacune les coordonnées de l\'un des points. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'draw/repere' :
chaine_aide='<code>slib(draw/repere )</code>'+
'<div class="title">Trace un repère </div>'+
'<div class="out">plusieurs lignes <ol><li>Les coordonnées de l\'origine du repère dans le dessin</li><li>L\'échelle en abscisse et en ordonnée</li><li>troisième et les suivantes : les données pour insdraw</li></ol> </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'function/bounds' :
chaine_aide='<code>slib(function/bounds )</code>'+
'<div class="title">The bound of a real function of one variable within an interval [x1,x2] </div>'+
'<div class="out">min,max </div>'+
'<div class="example"><code>slib(function/bounds  sin(x^4)*x^2, x,0,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'function/bounds2' :
chaine_aide='<code>slib(function/bounds2 )</code>'+
'<div class="title">The bound of a real function of two variables within a rectangle [x1,x2],[y1,y2] </div>'+
'<div class="out">min,max </div>'+
'<div class="example"><code>slib(function/bounds2 x^2+sin(x*y)+exp(y^2),[x,y],0,3,-3,2,50   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'function/integrate' :
chaine_aide='<code>slib(function/integrate )</code>'+
'<div class="title">Indefinite or definite integration of a function of one variable </div>'+
'<div class="out">The value (empty if error) </div>'+
'<div class="example"><code>slib(function/integrate sin(x),x,0,5,numeric)</code></div><div class="example"><code>slib(function/integrate  sin(x),x,0,5,fast)</code></div><div class="example"><code>slib(function/integrate  sin(x),x )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo2D/carmetal' :
chaine_aide='<code>slib(geo2D/carmetal )</code>'+
'<div class="title">CaRMetal </div>'+
'<div class="out">applet code for insertig CaRMetal </div>'+
'<div class="example"><code>slib(geo2D/carmetal  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo2D/geogebra3' :
chaine_aide='<code>slib(geo2D/geogebra3 )</code>'+
'<div class="title">Geogebra Applet </div>'+
'<div class="out">  </div>'+
'<div class="example"><code>slib(geo2D/geogebra3 Z=(-3,6.78);W=(0.2,5.8);a=Circle[Z,W];Ellipse[Z,W,5];u=Line[W,Z];showMenuBar=true;showToolBar=true;language=en;customToolBar="0|40@10||1|2";width=600;height=300;setCoordSystem(-9,7,1,11.5))</code></div><div class="example"><code>slib(geo2D/geogebra3  A=(0,3.5);B=(0,5);a=Cercle[A,B];d:y=2x+1;number=2;width=600;language=fr;showToolBar=true;customToolBar="0|40")</code></div><div class="example"><code>slib(geo2D/geogebra3  A=(0,3);B=(0,4);C=(2,3);s=Segment[A,C];Angle[C,A,B];a=Droite[C,B];D=Point[a];b=3;f(x)=b+sin(x);number=3;width=600;language=fr )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/3Dviewer' :
chaine_aide='<code>slib(geo3D/3Dviewer )</code>'+
'<div class="title">3D Viewer </div>'+
'<div class="out">applet code for visualizing simple 3D wireframe polyhedron. The java applet used is  LatticeViewer. Extract from the source : <pre>  LatticeViewer.java  Date :       18th Feb 1998	  Adapted by : Simon P.A.Gill  http://www.le.ac.uk/engineering/spg3/lattice/  The following java code is an adaptation of the Molecule Viewer XYZApp.java  freely distributed by Sun Microsystems. The conditions stated below apply  to this code. S.P.A. Gill takes no responsibility for this code.   Requires class Matrix3D.java (also from Sun at  http://www.javasoft.com:80/applets/js-applets.html)  </pre> </div>'+
'<div class="example"><code>slib(geo3D/3Dviewer cube,label=false scale=0.8 height=300 width=300)</code></div><div class="example"><code>slib(geo3D/3Dviewer  rhombicosidodecahedron,label=true scale=1 height=300 width=300 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/CaR' :
chaine_aide='<code>slib(geo3D/CaR )</code>'+
'<div class="title">3D applet with C.a.R </div>'+
'<div class="out">applet code for drawing a polyhedral object for C.a.R </div>'+
'<div class="example"><code>slib(geo3D/CaR v 0 0 0;v 1 0 0;v 1 1 0;v 0 1 0;v 0 0 1;v 1 0 1;v 1 1 1;v 0 1 1;f 1 2 3 4;f 5 6 7 8;f 1 5 2 6;l 1 5;l 2 6;l 3 7;l 4 8 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/Convex3D' :
chaine_aide='<code>slib(geo3D/Convex3D )</code>'+
'<div class="title">Polyhedron applet with Convex3D </div>'+
'<div class="out">code for draw of drawing a polyhedron with the applet Convex3D </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/draw' :
chaine_aide='<code>slib(geo3D/draw )</code>'+
'<div class="title">Polyedron in flydraw </div>'+
'<div class="out">code for draw of drawing a polyhedron using the projection given par the spherical/ coordonnates phi and theta </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/off2jmol' :
chaine_aide='<code>slib(geo3D/off2jmol )</code>'+
'<div class="title">Format off to xyz </div>'+
'<div class="out">translate format "off" in "xyz" extended (as in LatticeViewer) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/off2jmol2' :
chaine_aide='<code>slib(geo3D/off2jmol2 )</code>'+
'<div class="title">Format off to xyz </div>'+
'<div class="out">translate format "off" in "xyz" extended (as in LatticeViewer) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/off2xyz' :
chaine_aide='<code>slib(geo3D/off2xyz )</code>'+
'<div class="title">Format off to xyz </div>'+
'<div class="out">translate format "off" in "xyz" extended (as in LatticeViewer) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/polyhedra' :
chaine_aide='<code>slib(geo3D/polyhedra )</code>'+
'<div class="title">Polyhedra applet in C.a.R </div>'+
'<div class="out">applet code for drawing a polyhedra by its name with C.a.R </div>'+
'<div class="example"><code>slib(geo3D/polyhedra cube )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/polyhedradual' :
chaine_aide='<code>slib(geo3D/polyhedradual )</code>'+
'<div class="title">Polyhedra applet and its dual in C.a.R </div>'+
'<div class="out">C.a.R code for drawing a polyhedra and its dual ; the polyhedra is given by its name  </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'geo3D/threeD' :
chaine_aide='<code>slib(geo3D/threeD )</code>'+
'<div class="title">ThreeD Applet </div>'+
'<div class="out"> applet code for wireframe models ; based on the applet ThreeD  (http://javaboutique.internet.com/ThreeD/)  </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/connexcomponent' :
chaine_aide='<code>slib(graph/connexcomponent )</code>'+
'<div class="title">Connex component of a vertex in a graph </div>'+
'<div class="out">list of the connex component of the point </div>'+
'<div class="example"><code>slib(graph/connexcomponent [0,0,1;0,0,0;1,1,0],2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/connexity' :
chaine_aide='<code>slib(graph/connexity )</code>'+
'<div class="title">Connex components of a simple graph </div>'+
'<div class="out">number of  connex components of a simple graph,lists of connex components </div>'+
'<div class="example"><code>slib(graph/connexity [0,1,0,0;1,0,0,0;0,0,0,1;0,0,1,0] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/distance' :
chaine_aide='<code>slib(graph/distance )</code>'+
'<div class="title">Matrix of diameter of a graph </div>'+
'<div class="out">matrix of distances </div>'+
'<div class="example"><code>slib(graph/distance 0,1,1;1,0,1;1,1,0)</code></div><div class="example"><code>slib(graph/distance  [0,0,1;0,0,1;1,1,0] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/draw' :
chaine_aide='<code>slib(graph/draw )</code>'+
'<div class="title">Graph draw </div>'+
'<div class="out">code for draw of the graph to be used with draw </div>'+
'<div class="example"><code>slib(graph/draw [0,0,1;0,0,1;1,1,0],red,blue, [A,B,C],[1,3,green;3,2,purple])</code></div><div class="example"><code>slib(graph/draw   [0,0,1,1;0,0,1,1;1,1,0,1;1,1,1,0],red,blue,,[1,3,2,green] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/drawcc' :
chaine_aide='<code>slib(graph/drawcc )</code>'+
'<div class="title">Graph draw with one colored connex component  </div>'+
'<div class="out">code for draw of the graph </div>'+
'<div class="example"><code>slib(graph/drawcc  [0,0,0;0,0,1;0,1,0],[blue,yellow], [A,B,C],2)</code></div><div class="example"><code>slib(graph/drawcc   [0,0,0;0,0,1;0,1,0],[blue,yellow], [A,B,C],1,2   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/drawtree' :
chaine_aide='<code>slib(graph/drawtree )</code>'+
'<div class="title">Tree draw </div>'+
'<div class="out">code for draw of a given tree representation of the tree, text, option : middle, point </div>'+
'<div class="example"><code>slib(graph/drawtree [1,2,3;2,4,5;3,6,7],[[A,B,C],[a,b,c]],middle point   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/gpt' :
chaine_aide='<code>slib(graph/gpt )</code>'+
'<div class="title">Oriented graph without circuit </div>'+
'<div class="out">generation of a graph without circuit to be used with draw: draw source,  matrix, matrix of ranks, matrix of positions of the vertex,  position of points </div>'+
'<div class="example"><code>slib(graph/gpt 5,2,[a,b,c,d],blue,red )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/graphviz' :
chaine_aide='<code>slib(graph/graphviz )</code>'+
'<div class="title">Graphviz </div>'+
'<div class="out">url of the image of the graph generated by graphviz </div>'+
'<div class="example"><code>slib(graph/graphviz [0,1,0;0,1,1;0,0,0])</code></div><div class="example"><code>slib(graph/graphviz  [u,v,0;0,w,x;0,y,0],[a,b,c],edge)</code></div><div class="example"><code>slib(graph/graphviz  [0,T,0;0,1,0;0,1,0],[a,b,c],,rankdir="RL")</code></div><div class="example"><code>slib(graph/graphviz  [0,1,0;0,1,1;0,0,0],no_label_node, )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/randomconnex' :
chaine_aide='<code>slib(graph/randomconnex )</code>'+
'<div class="title">random connex graph </div>'+
'<div class="out">adjacence matrix  </div>'+
'<div class="example"><code>slib(graph/randomconnex 6,3)</code></div><div class="example"><code>slib(graph/randomconnex  6,8)</code></div><div class="example"><code>slib(graph/randomconnex  6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/randomeuler' :
chaine_aide='<code>slib(graph/randomeuler )</code>'+
'<div class="title">random eulerian graph </div>'+
'<div class="out">[adjacence matrix],[eulerian cycle] </div>'+
'<div class="example"><code>slib(graph/randomeuler 6)</code></div><div class="example"><code>slib(graph/randomeuler  6,7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/randtree' :
chaine_aide='<code>slib(graph/randtree )</code>'+
'<div class="title">Random tree </div>'+
'<div class="out">[code for draw of a tree to be used with draw],  [liste of nodes and children],[position of nodes], [position of points on vertices] </div>'+
'<div class="example"><code>slib(graph/randtree  5,3,3,,perfect middle   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graph/shortpath' :
chaine_aide='<code>slib(graph/shortpath )</code>'+
'<div class="title">Shortest path of a graph </div>'+
'<div class="out">list of vertices in a minimal path from s to t   </div>'+
'<div class="example"><code>slib(graph/shortpath  [1,0,1,0;0,1,1,0;0,2,4,1;0,1,1,1],1,3  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/correct_milli' :
chaine_aide='<code>slib(graphpaper/correct_milli )</code>'+
'<div class="title">Graphic paper sheet with red correct plot preloaded </div>'+
'<div class="out">Source for insdraw-ing a graph paper with the dots on it </div>'+
'<div class="example"><code>slib(graphpaper/correct_milli  ,,,,,,,,,[],0,0,1.2,1.5,2.4,3.2)</code></div><div class="example"><code>slib(graphpaper/correct_milli  12,8,0,0,1 max t (ms),1 max U (V),blue,red,[255,128,128],[0,0,1.3,1.4,2.5,3],0,0,1.2,1.5,2.4,3.2     )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/func' :
chaine_aide='<code>slib(graphpaper/func )</code>'+
'<div class="title">One function plot, ready to append to a previously made graph paper </div>'+
'<div class="out">Source for insdraw-ing a graph paper with the dots on it </div>'+
'<div class="example"><code>slib(graphpaper/func  ,,,,,,,,,sin(x))</code></div><div class="example"><code>slib(graphpaper/func  12,8,0,0,,,blue,red,[255,128,128],sin(x)   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/func_milli' :
chaine_aide='<code>slib(graphpaper/func_milli )</code>'+
'<div class="title">Graphic paper sheet with function plot and red correct plot preloaded </div>'+
'<div class="out">Source for insdraw-ing a graph paper with the dots on it </div>'+
'<div class="example"><code>slib(graphpaper/func_milli  ,,,,,,,,,sin(x),[],0,0,1.2,1.5,2.4,3.2)</code></div><div class="example"><code>slib(graphpaper/func_milli  12,8,0,0,1 max t (ms),1 max U (V),blue,red,[255,128,128],sin(x),[0,0,1.3,1.4,2.5,3],0,0,1.2,1.5,2.4,3.2 )</code></div><div class="example"><code>slib(graphpaper/func_milli  ,,,,,,,,,[cos(6.28*t),sin(6.28*t)],[],0,0,1.2,1.5,2.4,3.2    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/imgpoints' :
chaine_aide='<code>slib(graphpaper/imgpoints )</code>'+
'<div class="title">Utility for a clickable graphic paper sheet </div>'+
'<div class="out"> list of coordinates (x, y,) in the pixmap\'s space </div>'+
'<div class="example"><code>slib(graphpaper/imgpoints  12,8,0,0,1,1,2,4)</code></div><div class="example"><code>slib(graphpaper/imgpoints  12,8,0,0,1 max t (ms),1 max U (V),2,4    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/millimetre' :
chaine_aide='<code>slib(graphpaper/millimetre )</code>'+
'<div class="title">Graphic paper sheet </div>'+
'<div class="out">Source for insdraw-ing a graph paper with the dots on it </div>'+
'<div class="example"><code>slib(graphpaper/millimetre  ,,,,,,,,,0,0,1.2,1.5,2.4,3.2)</code></div><div class="example"><code>slib(graphpaper/millimetre  12,8,0,0,1 max t (ms),1 max U (V),blue,red,[255,128,128],0,0,1.2,1.5,2.4,3.2)</code></div><div class="example"><code>slib(graphpaper/millimetre  12,8,0,0,1 max t (ms),1 max U (V),blue,red,[255,128,128],style.grad=x_only, style.dot=o,0,0,1.2,1.5,2.4,3.2    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/strings' :
chaine_aide='<code>slib(graphpaper/strings )</code>'+
'<div class="title">Prepare strings to be written on a graphic paper sheet </div>'+
'<div class="out">Source for insdraw-ing a graph paper with the dots on it </div>'+
'<div class="example"><code>slib(graphpaper/strings  ,,,,,,,,,0,0,1.2,1.5,2.4,3.2)</code></div><div class="example"><code>slib(graphpaper/strings  12,8,0,0,1 max t (ms),1 max U (V),blue,red,[255,128,128],[,1,1,,Hello at 1,1],[red,5,2,large,Large red hello at 5,2]    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/tograph' :
chaine_aide='<code>slib(graphpaper/tograph )</code>'+
'<div class="title">Utility for a clickable graphic paper sheet </div>'+
'<div class="out"> list of coordinates (x1, y1, ...) in graphpaper\'s pixel space </div>'+
'<div class="example"><code>slib(graphpaper/tograph  12,8,0,0,1,1,2,2,3,5   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'graphpaper/whereclick' :
chaine_aide='<code>slib(graphpaper/whereclick )</code>'+
'<div class="title">Utility for a clickable graphic paper sheet </div>'+
'<div class="out"> list of coordinates (x, y,) in the viewport space </div>'+
'<div class="example"><code>slib(graphpaper/whereclick  12,8,0,0,1,1,125,13)</code></div><div class="example"><code>slib(graphpaper/whereclick  12,8,0,0,1 max t (ms),1 max U (V),125,13    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/enword2ipa' :
chaine_aide='<code>slib(lang/enword2ipa )</code>'+
'<div class="title">IPA transcription of english words </div>'+
'<div class="out"> IPA transcription in html symbols by using epd lexique </div>'+
'<div class="example"><code>slib(lang/enword2ipa mother,mothers,father,fathers,toto  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/epd2ipa' :
chaine_aide='<code>slib(lang/epd2ipa )</code>'+
'<div class="title">IPA transcription according to epd ascii codage (for english) </div>'+
'<div class="out"> IPA transcription in html symbols </div>'+
'<div class="example"><code>slib(lang/epd2ipa \'g0dmVD@R,pIktS@-kAdz  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/fname' :
chaine_aide='<code>slib(lang/fname )</code>'+
'<div class="title">A random first name </div>'+
'<div class="out">the random first name </div>'+
'<div class="example"><code>slib(lang/fname fr,boy)</code></div><div class="example"><code>slib(lang/fname  en,girl)</code></div><div class="example"><code>slib(lang/fname  es,boy )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/fraccord' :
chaine_aide='<code>slib(lang/fraccord )</code>'+
'<div class="title">Accord of French adjectives and names </div>'+
'<div class="out">the list of different forms: singular masculine,  singular feminine, plural masculine, plural feminine,  adverbial form (virtual). ATTENTION. This slib does not   know invariable adjectives! </div>'+
'<div class="example"><code>slib(lang/fraccord actif )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/frapostrophe' :
chaine_aide='<code>slib(lang/frapostrophe )</code>'+
'<div class="title">Apostrophe reduction of a French text </div>'+
'<div class="out">the transformed text </div>'+
'<div class="example"><code>slib(lang/frapostrophe  le avion)</code></div><div class="example"><code>slib(lang/frapostrophe   le port)</code></div><div class="example"><code>slib(lang/frapostrophe   de le pain )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/frartdef' :
chaine_aide='<code>slib(lang/frartdef )</code>'+
'<div class="title">Transform a French noun into definite form </div>'+
'<div class="out">the transformed phrase </div>'+
'<div class="example"><code>slib(lang/frartdef  un avion )</code></div><div class="example"><code>slib(lang/frartdef  une)</code></div><div class="example"><code>slib(lang/frartdef  des  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/frcodcoi' :
chaine_aide='<code>slib(lang/frcodcoi )</code>'+
'<div class="title">Find a random complement of a French verb </div>'+
'<div class="out">a random complement </div>'+
'<div class="example"><code>slib(lang/frcodcoi manger )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/frverbconj' :
chaine_aide='<code>slib(lang/frverbconj )</code>'+
'<div class="title">The conjugation of a French verb </div>'+
'<div class="out">the conjugations: multi-line format.   présent, imparfait, futur, conditionnel, impératif,   passé simple, subjonctif, subjonctif imparfait,   participe passé, participe présent. </div>'+
'<div class="example"><code>slib(lang/frverbconj  mordre )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/frword2ipa' :
chaine_aide='<code>slib(lang/frword2ipa )</code>'+
'<div class="title">IPA transcription of french words </div>'+
'<div class="out"> IPA transcription in html symbols by using manual lexique </div>'+
'<div class="example"><code>slib(lang/frword2ipa blessant,mother,bricolage,zozotement  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/images' :
chaine_aide='<code>slib(lang/images )</code>'+
'<div class="title">Images in some datamodule </div>'+
'<div class="out"> Look for the word in the imagedir, then in the images in modules/data/language/images  and give the code for insertion. Return -- if don\'t found. </div>'+
'<div class="example"><code>slib(lang/images [antelope,tree],eng)</code></div><div class="example"><code>slib(lang/images  [fourmi],fra)</code></div><div class="example"><code>slib(lang/images   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/lex2ipa' :
chaine_aide='<code>slib(lang/lex2ipa )</code>'+
'<div class="title">IPA transcription according to ?? ascii codage (for french) </div>'+
'<div class="out"> IPA transcription in html symbols </div>'+
'<div class="example"><code>slib(lang/lex2ipa abazuRdi )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/randomword' :
chaine_aide='<code>slib(lang/randomword )</code>'+
'<div class="title">Output random words in the dictionary </div>'+
'<div class="out">the random words according to specified word lengths, separated by spaces. </div>'+
'<div class="example"><code>slib(lang/randomword  3,4,8,fr)</code></div><div class="example"><code>slib(lang/randomword   3,4,8,en)</code></div><div class="example"><code>slib(lang/randomword    3,4,8,es )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/sampa2ipa' :
chaine_aide='<code>slib(lang/sampa2ipa )</code>'+
'<div class="title">IPA transcription according to Sampa Ascii codage (for english) </div>'+
'<div class="out"> IPA transcription in html symbols </div>'+
'<div class="example"><code>slib(lang/sampa2ipa zi:br@,  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'lang/swac' :
chaine_aide='<code>slib(lang/swac )</code>'+
'<div class="title">Insertion of words (audio) from the swac packs </div>'+
'<div class="out"> Look for the word in the imagedir, then in the swac-shtooka data and give the audio code for insertion. In this case, return also  the swac tags of recording ;    return nothing if don\'t find. </div>'+
'<div class="example"><code>slib(lang/swac aprendizaje,spa,player=dewplayer)</code></div><div class="example"><code>slib(lang/swac  la vieillesse,fra,player=hbs_mp3_player)</code></div><div class="example"><code>slib(lang/swac  aimer,fra,tag=baseform player=player)</code></div><div class="example"><code>slib(lang/swac  carabistouille,fra)</code></div><div class="example"><code>slib(lang/swac  manger,fra,tag=baseform player=player  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'life/frcommodity' :
chaine_aide='<code>slib(life/frcommodity )</code>'+
'<div class="title">Give a random commodity with given price, French </div>'+
'<div class="out">article, object </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'list/selshuf' :
chaine_aide='<code>slib(list/selshuf )</code>'+
'<div class="title">Selective shuffle </div>'+
'<div class="out">the shuffled list (empty if error) </div>'+
'<div class="example"><code>slib(list/selshuf  10,7,2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/concate' :
chaine_aide='<code>slib(matrix/concate )</code>'+
'<div class="title">concatenation </div>'+
'<div class="out">block diagonal matrix with input matrices on the diagonal </div>'+
'<div class="example"><code>slib(matrix/concate [1,2;3,4], [1,2;3,4],[1] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/det' :
chaine_aide='<code>slib(matrix/det )</code>'+
'<div class="title">The determinant of a square matrix </div>'+
'<div class="out">the determinant (empty if error) </div>'+
'<div class="example"><code>slib(matrix/det  1,3;5,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/givenrank' :
chaine_aide='<code>slib(matrix/givenrank )</code>'+
'<div class="title">Generates a random matrix of given rank </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/givenrank 3,5,1,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/inverse' :
chaine_aide='<code>slib(matrix/inverse )</code>'+
'<div class="title">The inverse of a square matrix </div>'+
'<div class="out">the inverse matrix (empty if error) </div>'+
'<div class="example"><code>slib(matrix/inverse 1,0;6,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/invertible' :
chaine_aide='<code>slib(matrix/invertible )</code>'+
'<div class="title">Generates a random invertible matrix </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/invertible  3,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/itriangular' :
chaine_aide='<code>slib(matrix/itriangular )</code>'+
'<div class="title">Generates a random invertible triangular matrix </div>'+
'<div class="out">the generated matrix (no zeros on the diagonal) </div>'+
'<div class="example"><code>slib(matrix/itriangular 4,6,5,random)</code></div><div class="example"><code>slib(matrix/itriangular  4,6,5,u)</code></div><div class="example"><code>slib(matrix/itriangular  4,6,5,d )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/non0' :
chaine_aide='<code>slib(matrix/non0 )</code>'+
'<div class="title">Generates a random matrix with non-zero coefficients </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/non0  3,6,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/orthogonal' :
chaine_aide='<code>slib(matrix/orthogonal )</code>'+
'<div class="title">Generates a random orthogonal matrix </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/orthogonal  4,3,3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/random' :
chaine_aide='<code>slib(matrix/random )</code>'+
'<div class="title">Generates a random matrix </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/random 3,2,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/trace' :
chaine_aide='<code>slib(matrix/trace )</code>'+
'<div class="title">The trace of a square matrix </div>'+
'<div class="out">the trace (empty if error) </div>'+
'<div class="example"><code>slib(matrix/trace 1,2,3;3,2,1;0,0,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/transpose' :
chaine_aide='<code>slib(matrix/transpose )</code>'+
'<div class="title">The transpose of a matrix </div>'+
'<div class="out">the transpose matrix (empty if error) </div>'+
'<div class="example"><code>slib(matrix/transpose 4,2,5;1,0,-3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/triangular' :
chaine_aide='<code>slib(matrix/triangular )</code>'+
'<div class="title">Generates a random triangular matrix </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/triangular 4,2,5,random)</code></div><div class="example"><code>slib(matrix/triangular  4,2,5,u)</code></div><div class="example"><code>slib(matrix/triangular  4,2,5,d )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'matrix/unimodular' :
chaine_aide='<code>slib(matrix/unimodular )</code>'+
'<div class="title">Generates a random unimodular matrix </div>'+
'<div class="out">the generated matrix </div>'+
'<div class="example"><code>slib(matrix/unimodular 3, 5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'media/audio' :
chaine_aide='<code>slib(media/audio )</code>'+
'<div class="title">Audio insertion </div>'+
'<div class="out">Audio insertion in html page </div>'+
'<div class="example"><code>slib(media/audio imagedir/exemple.mp3)</code></div><div class="example"><code>slib(media/audio  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3)</code></div><div class="example"><code>slib(media/audio  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3,width="100" height=20,player=dewplayer)</code></div><div class="example"><code>slib(media/audio  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3,,player=hbs_mp3_player)</code></div><div class="example"><code>slib(media/audio  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3,,player=player_mp3_multi )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'media/dewplayer' :
chaine_aide='<code>slib(media/dewplayer )</code>'+
'<div class="title">Audio insertion with dewplayer </div>'+
'<div class="out">Audio insertion in html page </div>'+
'<div class="example"><code>slib(media/dewplayer imagedir/exemple.mp3)</code></div><div class="example"><code>slib(media/dewplayer  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'media/player' :
chaine_aide='<code>slib(media/player )</code>'+
'<div class="title">Audio insertion with hbs_mp3_player  </div>'+
'<div class="out">  Audio insertion in html page </div>'+
'<div class="example"><code>slib(media/player imagedir/exemple.mp3)</code></div><div class="example"><code>slib(media/player  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'media/player_mp3_multi' :
chaine_aide='<code>slib(media/player_mp3_multi )</code>'+
'<div class="title">Audio insertion with player_mp3_multi  </div>'+
'<div class="out">  Audio insertion in html page </div>'+
'<div class="example"><code>slib(media/player_mp3_multi imagedir/exemple.mp3)</code></div><div class="example"><code>slib(media/player_mp3_multi  http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_bought.mp3|http://packs.shtooka.net/eng-balm-verbs/mp3/eng-I_brought.mp3  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'media/video' :
chaine_aide='<code>slib(media/video )</code>'+
'<div class="title">Video insertion with player_flv_maxi.swf </div>'+
'<div class="out">  Video insertion in html page </div>'+
'<div class="example"><code>slib(media/video imagedir/exemple.flv)</code></div><div class="example"><code>slib(media/video   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'numeration/ecriturenombre' :
chaine_aide='<code>slib(numeration/ecriturenombre )</code>'+
'<div class="title">Ecriture d\'un nombre avec regroupement des chiffres par trois. </div>'+
'<div class="out">Le nombre écrit avec des espaces. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/codelim' :
chaine_aide='<code>slib(oef/codelim )</code>'+
'<div class="title">OEF code length limit register </div>'+
'<div class="out">Returns the input parameter. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/codename' :
chaine_aide='<code>slib(oef/codename )</code>'+
'<div class="title">Register OEF code reply name allow/deny </div>'+
'<div class="out">Returns the names as list. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/env' :
chaine_aide='<code>slib(oef/env )</code>'+
'<div class="title">Get an OEF environment variable </div>'+
'<div class="out">The variable content. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/getopt' :
chaine_aide='<code>slib(oef/getopt )</code>'+
'<div class="title">Output the file name of the last insert </div>'+
'<div class="out">Returns the file name. It is just the content of the variable 	<tt>ins_filename</tt>. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/insfilename' :
chaine_aide='<code>slib(oef/insfilename )</code>'+
'<div class="title">Output the file name of the last insert </div>'+
'<div class="out">Returns the file name. It is just the content of the variable 	<tt>ins_filename</tt>. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/newfile' :
chaine_aide='<code>slib(oef/newfile )</code>'+
'<div class="title">Save a text in a file </div>'+
'<div class="out">URL of the new file </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/postsrc' :
chaine_aide='<code>slib(oef/postsrc )</code>'+
'<div class="title">OEF code input postpender </div>'+
'<div class="out">The unprocessed source input. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'oef/presrc' :
chaine_aide='<code>slib(oef/presrc )</code>'+
'<div class="title">OEF code input prepender </div>'+
'<div class="out">The unprocessed source input. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'polynomial/random' :
chaine_aide='<code>slib(polynomial/random )</code>'+
'<div class="title">Random polynomial </div>'+
'<div class="out">the polynomial </div>'+
'<div class="example"><code>slib(polynomial/random  5,6,t,monic)</code></div><div class="example"><code>slib(polynomial/random  5,6,t,2)</code></div><div class="example"><code>slib(polynomial/random  5,6,t,-3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/1d' :
chaine_aide='<code>slib(stat/1d )</code>'+
'<div class="title">Computes 1-dimensional statistical data </div>'+
'<div class="out">result of computation </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/arithmean' :
chaine_aide='<code>slib(stat/arithmean )</code>'+
'<div class="title">Arithmetic mean of statistical data </div>'+
'<div class="out">arithmetic mean with weights, total weight </div>'+
'<div class="example"><code>slib(stat/arithmean [1,2;3,4;3,5])</code></div><div class="example"><code>slib(stat/arithmean   [1,3,3],[2,4,5] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/beta' :
chaine_aide='<code>slib(stat/beta )</code>'+
'<div class="title">Generation of beta random data </div>'+
'<div class="out">random data of m reals following a beta law of parameters  a and b. If m is a list [r,s], it returns an r by c matrice.  </div>'+
'<div class="example"><code>slib(stat/beta  20,4,6)</code></div><div class="example"><code>slib(stat/beta  [10,5],4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/betacdf' :
chaine_aide='<code>slib(stat/betacdf )</code>'+
'<div class="title">Cumulative density function of Beta law </div>'+
'<div class="out">values on data </div>'+
'<div class="example"><code>slib(stat/betacdf [0.4,0.5,0.9],3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/betainv' :
chaine_aide='<code>slib(stat/betainv )</code>'+
'<div class="title">Quantiles of Beta law </div>'+
'<div class="out">quantile of Beta law on data </div>'+
'<div class="example"><code>slib(stat/betainv [0.3,0.6,0.8],4,7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/betapdf' :
chaine_aide='<code>slib(stat/betapdf )</code>'+
'<div class="title">Probability density function of Beta law </div>'+
'<div class="out">values of probability density function of Beta law on data </div>'+
'<div class="example"><code>slib(stat/betapdf [0.4,0.5,0.9],3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/binomial' :
chaine_aide='<code>slib(stat/binomial )</code>'+
'<div class="title">Generation of binomial random data </div>'+
'<div class="out">random data of m integers following a binomial law of parameters  n and p (n is an integer and p a real between 0 and 1) </div>'+
'<div class="example"><code>slib(stat/binomial 15,10,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/binomialcdf' :
chaine_aide='<code>slib(stat/binomialcdf )</code>'+
'<div class="title">cumulative distribution function of Binomial law </div>'+
'<div class="out">Cumulative distribution binomial law of parameters n and p (0&lt;p&lt;1) </div>'+
'<div class="example"><code>slib(stat/binomialcdf [3,5,6],10,0.6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/binomialinv' :
chaine_aide='<code>slib(stat/binomialinv )</code>'+
'<div class="title">Quantile of Binomial law </div>'+
'<div class="out">quantilei of binomial law of parameters n and p ((0&lt;p&lt;1)) at data </div>'+
'<div class="example"><code>slib(stat/binomialinv [0.2,0.4,0.6],5,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/binomialpdf' :
chaine_aide='<code>slib(stat/binomialpdf )</code>'+
'<div class="title">Binomial law </div>'+
'<div class="out">values of binomial law of parameters n and p ((0&lt;p&lt;1)) on data </div>'+
'<div class="example"><code>slib(stat/binomialpdf [2,4,5],20,0.7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/cauchy' :
chaine_aide='<code>slib(stat/cauchy )</code>'+
'<div class="title">Generation of Cauchy random data </div>'+
'<div class="out">random data of m reals following a Cauchy law of parameters  lambda and sigma. If m is a list [r,s], it returns an r by c matrice.  </div>'+
'<div class="example"><code>slib(stat/cauchy  20,4,6)</code></div><div class="example"><code>slib(stat/cauchy  [10,5],4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/cauchycdf' :
chaine_aide='<code>slib(stat/cauchycdf )</code>'+
'<div class="title">cumulative distribution function of Cauchy law   </div>'+
'<div class="out">Values of cumulative distribution function for Cauchy  of parameters lambda and sigma on data </div>'+
'<div class="example"><code>slib(stat/cauchycdf [2,6.4],5,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/cauchyinv' :
chaine_aide='<code>slib(stat/cauchyinv )</code>'+
'<div class="title">Quantile of Cauchy law of parameters lambda and sigma  </div>'+
'<div class="out">Quantile at data </div>'+
'<div class="example"><code>slib(stat/cauchyinv [0.3,0.5],5,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/cauchypdf' :
chaine_aide='<code>slib(stat/cauchypdf )</code>'+
'<div class="title">Probability density function of Cauchy law  </div>'+
'<div class="out">Values of probability density function of Cauchy law of parameters lambda and sigma  </div>'+
'<div class="example"><code>slib(stat/cauchypdf  [2,3,4],5,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/chi2' :
chaine_aide='<code>slib(stat/chi2 )</code>'+
'<div class="title">Generation of chi2 random data </div>'+
'<div class="out">random data of m reals following a chi2 law of degree n. If m is a list [r,s], it returns an r by c matrice.  </div>'+
'<div class="example"><code>slib(stat/chi2  20,4)</code></div><div class="example"><code>slib(stat/chi2  [2,5],4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/chi2cdf' :
chaine_aide='<code>slib(stat/chi2cdf )</code>'+
'<div class="title">Cumulative distribution function of chi2  </div>'+
'<div class="out">values of cumulative distribution function of chi2  on data </div>'+
'<div class="example"><code>slib(stat/chi2cdf   [2,4,7] ,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/chi2inv' :
chaine_aide='<code>slib(stat/chi2inv )</code>'+
'<div class="title">Quantile of cumulative chi2 distribution </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/chi2inv   [0.2,0.4,0.7] ,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/chi2pdf' :
chaine_aide='<code>slib(stat/chi2pdf )</code>'+
'<div class="title"> Probability density function of chi2  </div>'+
'<div class="out"> values of probability density function of chi2  on data </div>'+
'<div class="example"><code>slib(stat/chi2pdf [2,3,5],5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/correlation' :
chaine_aide='<code>slib(stat/correlation )</code>'+
'<div class="title">Matrix of correlation </div>'+
'<div class="out">matrix of  standard correlation c_i,j/sqrt(c_i,i*c_j,j)  where the c_i,j are the coefficients of  covariance matrix </div>'+
'<div class="example"><code>slib(stat/correlation [1,2,-4],[1,5,6])</code></div><div class="example"><code>slib(stat/correlation  [1,2,-4;1,5,6] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/covariance' :
chaine_aide='<code>slib(stat/covariance )</code>'+
'<div class="title">Matrix of covariance </div>'+
'<div class="out">first line : matrix of  standart covariance sum((x_i-mean_x)*(y_i-mean_y),i=1,n)/n  second line : matrix of covariance  sum((x_i-mean_x)*(y_i-mean_y),i=1,n)/(n-1) </div>'+
'<div class="example"><code>slib(stat/covariance [1,2,3];[3,1,9])</code></div><div class="example"><code>slib(stat/covariance  [1,2,3;3,1,9] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/deviation' :
chaine_aide='<code>slib(stat/deviation )</code>'+
'<div class="title">Deviation of statistical data </div>'+
'<div class="out">standard (empiric) deviation sqrt(sum((x_i-mean)^2,i=1,n)/n),deviation sqrt(sum((x_i-mean)^2,i=1,n))/(n-1)) </div>'+
'<div class="example"><code>slib(stat/deviation [1,2,5])</code></div><div class="example"><code>slib(stat/deviation  [1,2,3;2,4,5])</code></div><div class="example"><code>slib(stat/deviation  [1,3,3],[2,4,5] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/discretelaw' :
chaine_aide='<code>slib(stat/discretelaw )</code>'+
'<div class="title">Generation of a discrete law with nonnegative coefficients </div>'+
'<div class="out">random  data of m>=2 nonnegative real numbers  p_1,p_2,..p_m of sum 1 such that p_i*N are integers, (N>m). Outputs are real (K=R) or rational (K=Q) </div>'+
'<div class="example"><code>slib(stat/discretelaw  5,10)</code></div><div class="example"><code>slib(stat/discretelaw  7,10,Q )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/effectif' :
chaine_aide='<code>slib(stat/effectif )</code>'+
'<div class="title">Effectifs of statistical series in classes </div>'+
'<div class="out"> [effectifs of classes] ,[classes data] </div>'+
'<div class="example"><code>slib(stat/effectif [1,1,1,3,4,5,6,2],[1,4,6])</code></div><div class="example"><code>slib(stat/effectif  [1,1,1,3,4,5,6,2,7 ,4,7],[2,3,6])</code></div><div class="example"><code>slib(stat/effectif  [1,1,1,3,4,5,6,2],[1,4])</code></div><div class="example"><code>slib(stat/effectif  [1,1,1,3,4,5,6,2]  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/empiric' :
chaine_aide='<code>slib(stat/empiric )</code>'+
'<div class="title">Generation of random numbers with a discrete law </div>'+
'<div class="out">random  data of m numbers following the law [p_1,p_2,..p_j] on the values [v_1,v_2,..v_j] (p_i are positive reals of sum 1)   </div>'+
'<div class="example"><code>slib(stat/empiric  5,[0.5,0.5],[3,7])</code></div><div class="example"><code>slib(stat/empiric  5,[1/3,1/3,1/3],[pile,face,tranche]  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/expo' :
chaine_aide='<code>slib(stat/expo )</code>'+
'<div class="title">Generation of exponential random numbers </div>'+
'<div class="out">random data of m numbers following an exponential law of parameter lambda </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/exponential' :
chaine_aide='<code>slib(stat/exponential )</code>'+
'<div class="title">Generation of exponential random numbers </div>'+
'<div class="out">random data of m numbers following an exponential law of parameter lambda </div>'+
'<div class="example"><code>slib(stat/exponential 15,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/exponentialcdf' :
chaine_aide='<code>slib(stat/exponentialcdf )</code>'+
'<div class="title">cumulative distribution function of exponential law  </div>'+
'<div class="out">Values of cumulative distribution function of exponential distribution on data </div>'+
'<div class="example"><code>slib(stat/exponentialcdf [1,2,3],7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/exponentialinv' :
chaine_aide='<code>slib(stat/exponentialinv )</code>'+
'<div class="title">Quantile of exponential law </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/exponentialinv [0.1,0.2,0.3],7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/exponentialpdf' :
chaine_aide='<code>slib(stat/exponentialpdf )</code>'+
'<div class="title">Probability density function of Exponential law </div>'+
'<div class="out">values of probability density function of exponential distribution on data </div>'+
'<div class="example"><code>slib(stat/exponentialpdf [1,2,3],7  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/fisher' :
chaine_aide='<code>slib(stat/fisher )</code>'+
'<div class="title">Generation of Fisher random data </div>'+
'<div class="out">random data of m reals following a Fisher law of parameters a and b . If m is a list [r,s], it returns an r by s matrice.  </div>'+
'<div class="example"><code>slib(stat/fisher  20,4,6)</code></div><div class="example"><code>slib(stat/fisher  [10,5],4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/fishercdf' :
chaine_aide='<code>slib(stat/fishercdf )</code>'+
'<div class="title">Cumulative density function of Fisher law </div>'+
'<div class="out">values on data </div>'+
'<div class="example"><code>slib(stat/fishercdf [0.4,0.5,0.9],3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/fisherinv' :
chaine_aide='<code>slib(stat/fisherinv )</code>'+
'<div class="title">Quantiles of Fisher law </div>'+
'<div class="out">quantile of Fisher law on data </div>'+
'<div class="example"><code>slib(stat/fisherinv [0.3,0.6,0.8],4,7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/fisherpdf' :
chaine_aide='<code>slib(stat/fisherpdf )</code>'+
'<div class="title">Probability density function of Fisher law </div>'+
'<div class="out">values of probability density function of Fisher law on data </div>'+
'<div class="example"><code>slib(stat/fisherpdf [0.4,0.5,0.9],3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/freq' :
chaine_aide='<code>slib(stat/freq )</code>'+
'<div class="title">Frequencies of statistical data </div>'+
'<div class="out">[frequencies of data with respect to classes ],[ classes data](with min and max if necessary) </div>'+
'<div class="example"><code>slib(stat/freq [1,1,1,3,4,5,6,2],[1,4,6])</code></div><div class="example"><code>slib(stat/freq  [1,1,1,3,4,5,6,2,7 ,4,7],[2,3,6])</code></div><div class="example"><code>slib(stat/freq  [1,1,1,3,4,5,6,2],[1,4])</code></div><div class="example"><code>slib(stat/freq  [1,1,1,3,4,5,6,2] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/gamma' :
chaine_aide='<code>slib(stat/gamma )</code>'+
'<div class="title">Generation of Gamma random data </div>'+
'<div class="out">random data of m reals following a Gamma law of parameters a and b . If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/gamma  20,4,6)</code></div><div class="example"><code>slib(stat/gamma  [10,5],4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/gammacdf' :
chaine_aide='<code>slib(stat/gammacdf )</code>'+
'<div class="title">Cumulative distribution function of Gamma law </div>'+
'<div class="out">values of cumulative distribution function of Gamma law on data </div>'+
'<div class="example"><code>slib(stat/gammacdf [0.2,0.4,7],4,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/gammainv' :
chaine_aide='<code>slib(stat/gammainv )</code>'+
'<div class="title">Quantile of cumulative gamma distribution </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/gammainv [0.2,0.4,0.7],4,5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/gammapdf' :
chaine_aide='<code>slib(stat/gammapdf )</code>'+
'<div class="title">Probability density function of gamma law </div>'+
'<div class="out">values of probability density function of gamma law on data </div>'+
'<div class="example"><code>slib(stat/gammapdf [2,4,7],0.5,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geomean' :
chaine_aide='<code>slib(stat/geomean )</code>'+
'<div class="title">Geometric mean of data </div>'+
'<div class="out">geometric mean,total weight </div>'+
'<div class="example"><code>slib(stat/geomean [3,5,6])</code></div><div class="example"><code>slib(stat/geomean  [3,5,6],[4,1,1])</code></div><div class="example"><code>slib(stat/geomean  [3,5,6;4,1,1] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometric' :
chaine_aide='<code>slib(stat/geometric )</code>'+
'<div class="title">Generation of random data with geometric law on N </div>'+
'<div class="out">random data of m reals following a geometric law of parameter p on N. If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/geometric  20,0.3)</code></div><div class="example"><code>slib(stat/geometric  [10,5],0.3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometric1' :
chaine_aide='<code>slib(stat/geometric1 )</code>'+
'<div class="title">Generation of random data with geometric law on N* </div>'+
'<div class="out">random data of m reals following the geometric law of parameter p on N*. If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/geometric1  20,0.3)</code></div><div class="example"><code>slib(stat/geometric1  [10,5],0.3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometric1cdf' :
chaine_aide='<code>slib(stat/geometric1cdf )</code>'+
'<div class="title">cumulative distribution function of geometric law on N* </div>'+
'<div class="out">values of the cumulative distribution function of the geometric distribution on N* of paramter p on data </div>'+
'<div class="example"><code>slib(stat/geometric1cdf [2,4,7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometric1inv' :
chaine_aide='<code>slib(stat/geometric1inv )</code>'+
'<div class="title">Quantiles of a Geometric law on N* </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/geometric1inv [0.2,0.4,0.7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometric1pdf' :
chaine_aide='<code>slib(stat/geometric1pdf )</code>'+
'<div class="title">Probability density function of Geometric law on N* </div>'+
'<div class="out">values of probability density function of the geometric distribution on N* of parameter p. </div>'+
'<div class="example"><code>slib(stat/geometric1pdf [2,4,7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometriccdf' :
chaine_aide='<code>slib(stat/geometriccdf )</code>'+
'<div class="title">cumulative distribution function of geometric law on N </div>'+
'<div class="out">values of the cumulative distribution function of the geometric distribution of parameter p on data </div>'+
'<div class="example"><code>slib(stat/geometriccdf [2,4,7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometricinv' :
chaine_aide='<code>slib(stat/geometricinv )</code>'+
'<div class="title">Quantiles of a Geometric law on N </div>'+
'<div class="out">quantile at data of the Geometric law on N of parameter p </div>'+
'<div class="example"><code>slib(stat/geometricinv [0.2,0.4,0.7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/geometricpdf' :
chaine_aide='<code>slib(stat/geometricpdf )</code>'+
'<div class="title">Probability density function of Geometric law on N </div>'+
'<div class="out">values of probability density function of the geometric distribution on N of parameter p </div>'+
'<div class="example"><code>slib(stat/geometricpdf [2,4,7],0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/harmonic' :
chaine_aide='<code>slib(stat/harmonic )</code>'+
'<div class="title">Harmonic mean of statistical data </div>'+
'<div class="out">Harmonic mean </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/histo' :
chaine_aide='<code>slib(stat/histo )</code>'+
'<div class="title">Histogram </div>'+
'<div class="out">drawing code for plot </div>'+
'<div class="example"><code>slib(stat/histo  [10,5,2,3,10,13],[3,4,6,7,12,14,16],xtics [A1,A3,A6,8,10,12,14],ytics 10, color salmon)</code></div><div class="example"><code>slib(stat/histo  [1,5,2,3,10,13],[3,4,6,7,12,14],xtics [a,b,c,d,e,f],ytics 10, color salmon )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/hypergeometric' :
chaine_aide='<code>slib(stat/hypergeometric )</code>'+
'<div class="title">Generation of Hypergeometric random data </div>'+
'<div class="out">random data of m integers following an hypergeometric law of parameters a and b, c </div>'+
'<div class="example"><code>slib(stat/hypergeometric  20,16,4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/hypergeometriccdf' :
chaine_aide='<code>slib(stat/hypergeometriccdf )</code>'+
'<div class="title">cumulative distribution function of hypergeometric law   </div>'+
'<div class="out">Values on data </div>'+
'<div class="example"><code>slib(stat/hypergeometriccdf [2,4,7],10,5,7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/hypergeometricinv' :
chaine_aide='<code>slib(stat/hypergeometricinv )</code>'+
'<div class="title">Quantile of hypergeometric law inverse </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/hypergeometricinv [0.2,0.4,0.7],10,5,7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/hypergeometricpdf' :
chaine_aide='<code>slib(stat/hypergeometricpdf )</code>'+
'<div class="title">Probability density function of Hypergeometric law  </div>'+
'<div class="out">Values of probability density function of Hypergeometric </div>'+
'<div class="example"><code>slib(stat/hypergeometricpdf [2,4,7],12,4,3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/hypergeominv' :
chaine_aide='<code>slib(stat/hypergeominv )</code>'+
'<div class="title">Hypergeometric law inverse </div>'+
'<div class="out">quantile inverse of cumulative hypergeometric distribution (N,n,k) </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/laplace' :
chaine_aide='<code>slib(stat/laplace )</code>'+
'<div class="title">Generation of Laplace random data </div>'+
'<div class="out">random data of m integers following an Laplace law . If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/laplace  20)</code></div><div class="example"><code>slib(stat/laplace  [10,5] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/laplacecdf' :
chaine_aide='<code>slib(stat/laplacecdf )</code>'+
'<div class="title">Probability  cumulative distribution of laplace law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/laplacecdf [2,4,7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/laplaceinv' :
chaine_aide='<code>slib(stat/laplaceinv )</code>'+
'<div class="title">Quantiles of laplace law </div>'+
'<div class="out">values at data </div>'+
'<div class="example"><code>slib(stat/laplaceinv [0.2,0.4,0.7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/laplacepdf' :
chaine_aide='<code>slib(stat/laplacepdf )</code>'+
'<div class="title">Probability  density function of laplace law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/laplacepdf [2,4,7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/linearcong' :
chaine_aide='<code>slib(stat/linearcong )</code>'+
'<div class="title">Generation of linear congruential random integers </div>'+
'<div class="out">n integers generated by the linear congruences ax+b mod m </div>'+
'<div class="example"><code>slib(stat/linearcong 10, 3,7,11 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/logistic' :
chaine_aide='<code>slib(stat/logistic )</code>'+
'<div class="title">Generation of logistic random data </div>'+
'<div class="out">random data of m integers following an logistic law. If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/logistic  20)</code></div><div class="example"><code>slib(stat/logistic  [10,5] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/logisticcdf' :
chaine_aide='<code>slib(stat/logisticcdf )</code>'+
'<div class="title">Probability cumulative density function of logistic law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/logisticcdf [2,4,7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/logisticinv' :
chaine_aide='<code>slib(stat/logisticinv )</code>'+
'<div class="title">Quantile of  logistic law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/logisticinv [0.2,0.4,0.7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/logisticpdf' :
chaine_aide='<code>slib(stat/logisticpdf )</code>'+
'<div class="title">Probability  density function of logistic law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/logisticpdf [2,4,7] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/lognormal' :
chaine_aide='<code>slib(stat/lognormal )</code>'+
'<div class="title">Generation of lognormal random data </div>'+
'<div class="out">random data of m reals following a lognormal law of parameters a and b . If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/lognormal  20,0,1)</code></div><div class="example"><code>slib(stat/lognormal  [6,5],0,2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/lognormalcdf' :
chaine_aide='<code>slib(stat/lognormalcdf )</code>'+
'<div class="title">Cumulative distribution function of log-normal law  </div>'+
'<div class="out">values of cumulative distribution function of log-normal law   on data </div>'+
'<div class="example"><code>slib(stat/lognormalcdf [2,4,7] ,3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/lognormalinv' :
chaine_aide='<code>slib(stat/lognormalinv )</code>'+
'<div class="title">Quantile of of Log-normal law </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/lognormalinv [0.2,0.4,0.7] ,3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/lognormalpdf' :
chaine_aide='<code>slib(stat/lognormalpdf )</code>'+
'<div class="title">Probability density function of log-normal law  </div>'+
'<div class="out">values of probability density function of log-normal law   on data </div>'+
'<div class="example"><code>slib(stat/lognormalpdf [2,4,7] ,3,4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/median' :
chaine_aide='<code>slib(stat/median )</code>'+
'<div class="title">Data median </div>'+
'<div class="out"> statistic median </div>'+
'<div class="example"><code>slib(stat/median [2,-7,6])</code></div><div class="example"><code>slib(stat/median  [2,-7,6;1,1,4])</code></div><div class="example"><code>slib(stat/median  [2,1;-7,1;6,4])</code></div><div class="example"><code>slib(stat/median  [2,-7,6],[1,1,4]  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/multinomial' :
chaine_aide='<code>slib(stat/multinomial )</code>'+
'<div class="title">Generation of multinomial random data </div>'+
'<div class="out">random data of m integers following a multinomial law of parameters  n and p=[p_1,...,p_j] (n is an integer and p_i are positive reals of sum <= 1; if the sum of the p_i is less than 1, 1-sum(p_i) is add to the list.  </div>'+
'<div class="example"><code>slib(stat/multinomial 3,6,[1/3,1/3] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/normal' :
chaine_aide='<code>slib(stat/normal )</code>'+
'<div class="title">Generation of Gaussian random data </div>'+
'<div class="out">random  data of m reals following a  normal law of parameters mu and  sigma. </div>'+
'<div class="example"><code>slib(stat/normal 10,0,2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/normalcdf' :
chaine_aide='<code>slib(stat/normalcdf )</code>'+
'<div class="title">Cumulative distribution function of the normal distribution </div>'+
'<div class="out">values on data </div>'+
'<div class="example"><code>slib(stat/normalcdf [-2,-4,1],0,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/normalinv' :
chaine_aide='<code>slib(stat/normalinv )</code>'+
'<div class="title">Quantile of Normal law </div>'+
'<div class="out">quantile at data </div>'+
'<div class="example"><code>slib(stat/normalinv [0.2,0.4,0.5],0,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/normalpdf' :
chaine_aide='<code>slib(stat/normalpdf )</code>'+
'<div class="title">Probability density function of Normal law </div>'+
'<div class="out">values of Probability density function of normal distribution </div>'+
'<div class="example"><code>slib(stat/normalpdf [-2,-4,1],0,1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/pascal' :
chaine_aide='<code>slib(stat/pascal )</code>'+
'<div class="title">Generation of Pascal random data </div>'+
'<div class="out">random data of m reals following a Pascal law of parameters n and p. If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/pascal  20,4,0.3)</code></div><div class="example"><code>slib(stat/pascal  [10,5],4,0.3 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/pascalcdf' :
chaine_aide='<code>slib(stat/pascalcdf )</code>'+
'<div class="title">cumulative distribution function of Binomial law </div>'+
'<div class="out">Cumulative distribution binomial law of parameters n and p (0&lt;p&lt;1) </div>'+
'<div class="example"><code>slib(stat/pascalcdf [3,5,6],10,0.6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/pascalinv' :
chaine_aide='<code>slib(stat/pascalinv )</code>'+
'<div class="title">Quantile of Negative Binomial law </div>'+
'<div class="out">quantile of binomial law of parameters n and p ((0&lt;p&lt;1)) at data </div>'+
'<div class="example"><code>slib(stat/pascalinv [0.2,0.4,0.6],5,0.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/pascalpdf' :
chaine_aide='<code>slib(stat/pascalpdf )</code>'+
'<div class="title">Negative Binomial law (Pascal law) </div>'+
'<div class="out">values of binomial law of parameters n and p ((0&lt;p&lt;1)) on data </div>'+
'<div class="example"><code>slib(stat/pascalpdf [2,4,5],20,0.7 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/poisson' :
chaine_aide='<code>slib(stat/poisson )</code>'+
'<div class="title">Generation of random numbers with Poisson law  </div>'+
'<div class="out">random  data of m numbers following the Poisson law  of parameter lambda (positive number)   </div>'+
'<div class="example"><code>slib(stat/poisson  5,2.5 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/poissoncdf' :
chaine_aide='<code>slib(stat/poissoncdf )</code>'+
'<div class="title">cumulative distribution function of Poisson law </div>'+
'<div class="out">values on data of the cumulative distribution function of the Poisson law of parameter p </div>'+
'<div class="example"><code>slib(stat/poissoncdf [2,4,7],6.1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/poissoninv' :
chaine_aide='<code>slib(stat/poissoninv )</code>'+
'<div class="title">Quantile of Poisson law </div>'+
'<div class="out">quantile at data of the Poisson law of parameter p </div>'+
'<div class="example"><code>slib(stat/poissoninv [0.2,0.4,0.7],6.1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/poissonpdf' :
chaine_aide='<code>slib(stat/poissonpdf )</code>'+
'<div class="title">Probability density function of Poisson law </div>'+
'<div class="out">values of the probability density function of the Poisson law of parameter p on data </div>'+
'<div class="example"><code>slib(stat/poissonpdf [2,4,7],6.1 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/posdiscretelaw' :
chaine_aide='<code>slib(stat/posdiscretelaw )</code>'+
'<div class="title">Generation of a discrete law with positive coefficients </div>'+
'<div class="out">random  data of m>=2 positive  real numbers  p_1,p_2,..p_m of sum 1 such that p_i*N are integers, (N>m). Outputs are real (K=R) or rational (K=Q) </div>'+
'<div class="example"><code>slib(stat/posdiscretelaw  5, 100)</code></div><div class="example"><code>slib(stat/posdiscretelaw  7,10,Q )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/prod' :
chaine_aide='<code>slib(stat/prod )</code>'+
'<div class="title">Product of data </div>'+
'<div class="out">data product  </div>'+
'<div class="example"><code>slib(stat/prod [2,-7,6])</code></div><div class="example"><code>slib(stat/prod  [2,7,6;1,1,4])</code></div><div class="example"><code>slib(stat/prod  [2,1;7,1;6,4])</code></div><div class="example"><code>slib(stat/prod  [2,7,6],[1,1,4] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/quadratic' :
chaine_aide='<code>slib(stat/quadratic )</code>'+
'<div class="title">Quadratic mean </div>'+
'<div class="out">standard quadratic mean of data x_1,..,x_n = sum(x_i^2)/n </div>'+
'<div class="example"><code>slib(stat/quadratic [2,-7,6])</code></div><div class="example"><code>slib(stat/quadratic  [2,1;-7,1;6,4])</code></div><div class="example"><code>slib(stat/quadratic  [2,-7,6],[1,1,4])</code></div><div class="example"><code>slib(stat/quadratic  [2,-7,6;1,1,4] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/random' :
chaine_aide='<code>slib(stat/random )</code>'+
'<div class="title">Generation of random numbers </div>'+
'<div class="out">sequence of  m random  numbers between N and M in the coefficient ring </div>'+
'<div class="example"><code>slib(stat/random  10,-3,10,Z)</code></div><div class="example"><code>slib(stat/random  10,-3,10,R  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/range' :
chaine_aide='<code>slib(stat/range )</code>'+
'<div class="title">Data range </div>'+
'<div class="out">data range </div>'+
'<div class="example"><code>slib(stat/range 1,3,5,0,10,-4)</code></div><div class="example"><code>slib(stat/range  1 3 5 0 10 -4)</code></div><div class="example"><code>slib(stat/range  1;3;5;0;10;-4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/student' :
chaine_aide='<code>slib(stat/student )</code>'+
'<div class="title">Generation of Student random data </div>'+
'<div class="out">random data of m reals following a Student law of degree n. If m is a list [r,s], it returns an r by c matrice.  </div>'+
'<div class="example"><code>slib(stat/student  20,4)</code></div><div class="example"><code>slib(stat/student  [2,5],4 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/studentcdf' :
chaine_aide='<code>slib(stat/studentcdf )</code>'+
'<div class="title">Probability cumulative density function of Student law </div>'+
'<div class="out">values  at data </div>'+
'<div class="example"><code>slib(stat/studentcdf [2,4,7],5  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/studentinv' :
chaine_aide='<code>slib(stat/studentinv )</code>'+
'<div class="title">Quantile of Student law </div>'+
'<div class="out">values at data </div>'+
'<div class="example"><code>slib(stat/studentinv [0.2,0.4,0.7],5  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/studentpdf' :
chaine_aide='<code>slib(stat/studentpdf )</code>'+
'<div class="title">Probability density function of Student law </div>'+
'<div class="out">values of probability density function of Student law on data </div>'+
'<div class="example"><code>slib(stat/studentpdf [2,4,7],5  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/sum' :
chaine_aide='<code>slib(stat/sum )</code>'+
'<div class="title">Data sum </div>'+
'<div class="out">data sum </div>'+
'<div class="example"><code>slib(stat/sum [2,-7,6])</code></div><div class="example"><code>slib(stat/sum  [2,1;-7,6;1,1])</code></div><div class="example"><code>slib(stat/sum  [2,-7,1],[1,6,1])</code></div><div class="example"><code>slib(stat/sum  [2,-7,1;1,6,1] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/variance' :
chaine_aide='<code>slib(stat/variance )</code>'+
'<div class="title">Variance </div>'+
'<div class="out">standard variance of data x_1,..,x_n = sum(x_i^2-mean)/n, sum(x_i^2-mean)/(n-1) </div>'+
'<div class="example"><code>slib(stat/variance [2,-7,6])</code></div><div class="example"><code>slib(stat/variance  [2,-7,6;1,1,4])</code></div><div class="example"><code>slib(stat/variance  [2,-7,6],[1,1,4] )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/weibull' :
chaine_aide='<code>slib(stat/weibull )</code>'+
'<div class="title">Generation of Weibull random data </div>'+
'<div class="out">random data of m reals following a Weilbull law of parameters a and b . If m is a list [r,s], it returns an r by  s matrice.  </div>'+
'<div class="example"><code>slib(stat/weibull  20,4,6)</code></div><div class="example"><code>slib(stat/weibull  [10,5],4,6 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/weibullcdf' :
chaine_aide='<code>slib(stat/weibullcdf )</code>'+
'<div class="title">cumulative distribution function of Weibull law </div>'+
'<div class="out">values at data </div>'+
'<div class="example"><code>slib(stat/weibullcdf [0.2,0.4,0.7],0.6,0.8 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/weibullinv' :
chaine_aide='<code>slib(stat/weibullinv )</code>'+
'<div class="title">Quantile of Weibull law </div>'+
'<div class="out">quantiles at data </div>'+
'<div class="example"><code>slib(stat/weibullinv [0.2,0.4,0.7],6,8 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'stat/weibullpdf' :
chaine_aide='<code>slib(stat/weibullpdf )</code>'+
'<div class="title">Probability density function of Weibull law </div>'+
'<div class="out">values of probability density function of Weibull law on data </div>'+
'<div class="example"><code>slib(stat/weibullpdf [0.2,0.4,0.7],6,8 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/approximation' :
chaine_aide='<code>slib(text/approximation )</code>'+
'<div class="title">Calculate an interval for the answer type range </div>'+
'<div class="out">three numbers for the answer type range : minimum, maximum, real with the number of significative digits, an error of +/- "tolerance" on the last number is allowed (calculated with the given real). </div>'+
'<div class="example"><code>slib(text/approximation 234765)</code></div><div class="example"><code>slib(text/approximation  0.006543)</code></div><div class="example"><code>slib(text/approximation  45.987543,5,10 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/cdecomment' :
chaine_aide='<code>slib(text/cdecomment )</code>'+
'<div class="title">Extract comment from a c source code. </div>'+
'<div class="out">The resulting source </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/cutchoice2' :
chaine_aide='<code>slib(text/cutchoice2 )</code>'+
'<div class="title">Cut out embedded choices for OEF </div>'+
'<div class="out">Text output with each choice in isolated rows </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/cutchoices' :
chaine_aide='<code>slib(text/cutchoices )</code>'+
'<div class="title">Cut out embedded choices for OEF </div>'+
'<div class="out">Text output with each choice in isolated lines </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/markerror' :
chaine_aide='<code>slib(text/markerror )</code>'+
'<div class="title">For marking words with mistake </div>'+
'<div class="out"> a matrix :    position of the false_word in the sentence ; Text output with comas beetween words; list of good answers;number of words in the sentence  </div>'+
'<div class="example"><code>slib(text/markerror  The ball is ??rond|round?? and ??gren|green??.)</code></div><div class="example"><code>slib(text/markerror  ??They bal|The ball?? is ??raid|red?? and green.)</code></div><div class="example"><code>slib(text/markerror  ??The ball?? is ??raid|red?? and green. )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/markgroup' :
chaine_aide='<code>slib(text/markgroup )</code>'+
'<div class="title">For marking  group of words with given explanation </div>'+
'<div class="out"> position of words embedded in text by  ?? (one line by embedding);  Text output with comas ; liste of explanations (one for groups of words); number of words </div>'+
'<div class="example"><code>slib(text/markgroup  The ball is ??red magenta|rouge||rose?? and ??light green|vert??.)</code></div><div class="example"><code>slib(text/markgroup  ??red magenta|rouge?? is the ??balle|ball.)</code></div><div class="example"><code>slib(text/markgroup  The ball is ??red magenta?? and ??light green|vert??. )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/marktext' :
chaine_aide='<code>slib(text/marktext )</code>'+
'<div class="title">Texte for use with type mark for OEF (word) </div>'+
'<div class="out"> position of words which was inside ?? ; Text output with comas ; number of words </div>'+
'<div class="example"><code>slib(text/marktext  The ball is ??red?? and ??green??.)</code></div><div class="example"><code>slib(text/marktext  ??The ball?? is red and green. )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/marktextpartial' :
chaine_aide='<code>slib(text/marktextpartial )</code>'+
'<div class="title">For marking  some words with given explanation </div>'+
'<div class="out"> position of words embedded in text by  ?? ?? (without the joker) amongst all the groups of the form ?? ?? (one line by embedding); [position in the text of the ?? ??]; Text output with comas ; list of explanations (one by groups of words); number of words </div>'+
'<div class="example"><code>slib(text/marktextpartial  Je??@_??mange??_|article+nom??une??@_??pomme que j)</code></div><div class="example"><code>slib(text/marktextpartial \'ai??@_??cueillie sur un??_|article + nom??arbre )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/markword' :
chaine_aide='<code>slib(text/markword )</code>'+
'<div class="title">For use with type mark in OEF </div>'+
'<div class="out"> position of characters which was inside ?? in the word output; Text output with comas ; number of characters </div>'+
'<div class="example"><code>slib(text/markword  ??bi??cycle)</code></div><div class="example"><code>slib(text/markword  bi??cycle?? )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/matrixtex' :
chaine_aide='<code>slib(text/matrixtex )</code>'+
'<div class="title"> Matrix in Tex </div>'+
'<div class="out">tex matrix with  options (lbrace,lbrack,..., or nothing) </div>'+
'<div class="example"><code>slib(text/matrixtex  [1,2;x^2,y;e_1,e_2],lbrace,rbrack )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/maximamatrix' :
chaine_aide='<code>slib(text/maximamatrix )</code>'+
'<div class="title">Transform a matrix to maxima format </div>'+
'<div class="out">the matrix in format for input to Maxima. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/octavematrix' :
chaine_aide='<code>slib(text/octavematrix )</code>'+
'<div class="title">Transform an octave output matrix into standard format </div>'+
'<div class="out">the output matrix in format wims from output of Octave. </div>'+
''+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/sigunits' :
chaine_aide='<code>slib(text/sigunits )</code>'+
'<div class="title">make a representation of a physical quantity with a given number of significative digits </div>'+
'<div class="out">the physical quantity with the right number of digits, or a numeric value which would be equal to the result with the right number of digits. </div>'+
'<div class="example"><code>slib(text/sigunits 1.2345A,2)</code></div><div class="example"><code>slib(text/sigunits  1.2V,5)</code></div><div class="example"><code>slib(text/sigunits  12,3)</code></div><div class="example"><code>slib(text/sigunits  12,3,4)</code></div><div class="example"><code>slib(text/sigunits  0.50A.h)</code></div><div class="example"><code>slib(text/sigunits  1800C,3,,A.h)</code></div><div class="example"><code>slib(text/sigunits  1.8°,5,,rad )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/spirale' :
chaine_aide='<code>slib(text/spirale )</code>'+
'<div class="title">Write on a spirale </div>'+
'<div class="out">code for flydraw: text written on a spirale </div>'+
'<div class="example"><code>slib(text/spirale voici un essai )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'text/whitespace' :
chaine_aide='<code>slib(text/whitespace )</code>'+
'<div class="title">Replace white spaces </div>'+
'<div class="out"> text where white spaces are replaced by subst  </div>'+
'<div class="example"><code>slib(text/whitespace  ??@__??,??_??,Je mange ??_?? une pomme  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'triplerelation/tabular' :
chaine_aide='<code>slib(triplerelation/tabular )</code>'+
'<div class="title">Double entry table for training to relations between three quantities </div>'+
'<div class="out">One table with input fields, <br>the number NR of replies, <br>the list of the NR replies, <br>the list of the (NR+1) chunks of table to be interleaved with \\\\\embed{} in the statement of an OEF exercise. </div>'+
'<div class="example"><code>slib(triplerelation/tabular  ,,,2,2,,1 )</code></div><div class="example"><code>slib(triplerelation/tabular  (distance,m,1000,2000,y*z),(duration,s,10,20,x/z),(velocity,m/s,50,200,x/y),4,2 )</code></div><div class="example"><code>slib(triplerelation/tabular  (distance,m,1000,2000,y*z),(duration,s,10,20,x/z),(impossible_velocity,m/s,-50,-10,x/y),4,2 )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'utilities/nopaste' :
chaine_aide='<code>slib(utilities/nopaste )</code>'+
'<div class="title">No copy-paste </div>'+
'<div class="out">put this javascript in the page and it is not possible to copy-paste.  </div>'+
'<div class="example"><code>slib(utilities/nopaste    )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'utilities/notepad' :
chaine_aide='<code>slib(utilities/notepad )</code>'+
'<div class="title">Notepad </div>'+
'<div class="out">javascript for create a note pad </div>'+
'<div class="example"><code>slib(utilities/notepad  Ouvrir une fenêtre de brouillon,size=small  )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	case 'utilities/tooltip' :
chaine_aide='<code>slib(utilities/tooltip )</code>'+
'<div class="title">Tooltip containing an html text which appears when the mouse points on a word. </div>'+
'<div class="out"> code for tooltip </div>'+
'<div class="example"><code>slib(utilities/tooltip  rouge,, une couleur)</code></div><div class="example"><code>slib(utilities/tooltip  mouse here,nojs [DURATION, 1000,TITLE,)</code></div><div class="example"><code>slib(utilities/tooltip \'First clue)</code></div><div class="example"><code>slib(utilities/tooltip \'], the word has 5 letters)</code></div><div class="example"><code>slib(utilities/tooltip  mouse here, [FONTSIZE, )</code></div><div class="example"><code>slib(utilities/tooltip \'25pt)</code></div><div class="example"><code>slib(utilities/tooltip \'], .....)</code></div><div class="example"><code>slib(utilities/tooltip  mouse here, [TITLE, )</code></div><div class="example"><code>slib(utilities/tooltip \'Some Title)</code></div><div class="example"><code>slib(utilities/tooltip \', PADDING, 9],another example)</code></div><div class="example"><code>slib(utilities/tooltip   )</code></div>'+
'' ; return chaine_aide;
	   break;
	////******************** 

	
	}
}