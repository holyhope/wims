var latexname='Latex';
var latex = [
	"\\alpha","\\beta","\\gamma","\\delta", "\\epsilon", "\\varepsilon", "\\zeta", "\\eta", "\\Gamma",
	"\\Delta","\\Theta","\\theta","\\vartheta","\\kappa", "\\lambda", "\\mu", "\\nu", "\\xi", "\\pi",
	"\\varpi","\\rho","\\varrho","\\sigma","\\varsigma", "\\Sigma", "\\Upsilon", "\\Phi", "\\tau", "\\upsilon",
	"\\phi","\\varphi","\\chi","\\psi","\\omega", "\\Psi", "\\Upsilon", "\\Phi", "\\Omega",
	
	"\\pm","\\mp","\\times","\\div","\\ast", "\\star", "\\circ", "\\bullet", "\\cdot",
	"\\cap","\\cup","\\uplus","\\sqcap","\\sqcup", "\\vee", "\\wedge", "\\setminus", "\\wr",
	"\\diamond","\\bigtriangleup","\\bigtriangledown","\\triangleleft","\\triangleright", "\\lhd$^b$", "\\rhd$^b$", "\\unlhd$^b$", "\\unrhd$^b$",
	"\\oplus","\\ominus","\\otimes","\\oslash","\\odot", "\\bigcirc", "\\dagger", "\\ddagger", "\\amalg",
	
	"\\widetilde{abc}","\\overleftarrow{abc}","\\overline{abc}","\\overbrace{abc}","\\sqrt{abc}", "\\widehat{abc}", 
	"\\overrightarrow{abc}", "\\underline{abc}", "\\sqrt[n]{abc}", "\\frac{abc}{xyz}",
	
	"\\hat{a}", "\\check{a}", "\\acute{a}", "\\grave{a}", "\\bar{a}", "\\vec{a}", "\\dot{a}", "\\ddot{a}",
	
	"\\rmoustache", "\\arrowvert", "\\lmoustache", "\\Arrowvert", "\\Arrowvert", "\\bracevert", "\\lgroup"
	];
	

function latexfun(instruction, version){
	// les indices &agrave; partir de 19 correspondent aux instructions latex
	var index2="";
	switch(instruction)
    {
    	case "\\alpha" :
        index2=0;
        break;
    case "\\beta" :
        index2=0;
        break;
    case "\\gamma" :
        index2=0;
        break;
	case "\\delta" :
        index2=0;
        break;
    case "\\epsilon" :
        index2=0;
        break;
    case "\\varepsilon" :
        index2=0;
        break;
	case "\\zeta" :
        index2=0;
        break;
    case "\\eta" :
        index2=0;
        break;
    case "\\Gamma" :
        index2=0;
        break;
	case "\\Delta" :
        index2=0;
        break;
    case "\\Theta" :
        index2=0;
        break;
    case "\\theta" :
        index2=0;
        break;
	case "\\vartheta" :
        index2=0;
        break;
    case "\\kappa" :
        index2=0;
        break;
    case "\\lambda" :
        index2=0;
        break;
	case "\\mu" :
        index2=0;
        break;
    case "\\nu" :
        index2=0;
        break;
	case "\\xi" :
        index2=0;
        break;
    case "\\phi" :
       index2=0;
        break;
	case "\\varphi" :
        index2=0;
        break;
    case "\\rho" :
        index2=0;
        break;
    case "\\varrho" :
        index2=0;
        break;
	case "\\sigma" :
        index2=0;
        break;
    case "\\varsigma" :
        index2=0;
        break;
    case "\\Sigma" :
        index2=0;
        break;
	case "\\upsilon" :
        index2=0;
        break;
    case "\\Phi" :
        index2=0;
        break;
    case "\\chi" :
        index2=0;
        break;
	case "\\psi" :
        index2=0;
        break;
	case "\\pi" :
        index2=0;
        break;
    case "\\omega" :
        index2=0;
        break;
    case "\\Psi" :
        index2=0;
        break;
	case "\\tau" :
        index2=0;
        break;
	case "\\varpi" :
        index2=0;
        break;
	case "\\Upsilon" :
        index2=0;
        break;
    case "\\Phi" :
        index2=0;
        break;
    case "\\Omega" :
        index2=0;
        break;
	case "\\pm" :
        index2=1;
        break;
    case "\\mp" :
        index2=1;
        break;
    case "\\times" :
        index2=1;
        break;
	case "\\div" :
        index2=1;
        break;
    case "\\ast" :
        index2=1;
        break;
    case "\\star" :
        index2=1;
        break;
	case "\\bullet" :
        index2=1;
        break;
    case "\\cdot" :
        index2=1;
        break;
    case "\\cap" :
        index2=1;
        break;
	case "\\cup" :
        index2=1;
        break;
    case "\\uplus" :
        index2=1;
        break;
    case "\\sqcap" :
        index2=1;
        break;
	case "\\sqcup" :
        index2=1;
        break;
    case "\\vee" :
        index2=1;
        break;
    case "\\wedge" :
        index2=1;
        break;
	case "\\setminus" :
        index2=1;
        break;
    case "\\wr" :
        index2=1;
        break;
	case "\\diamond" :
        index2=1;
        break;
    case "\\bigtriangleup" :
       index2=1; 
	   break;
	case "\\bigtriangledown" :
        index2=1;
        break;
    case "\\triangleleft" :
        index2=1;
        break;
	case "\\circ" :
        index2=1;
        break;
	case "\\triangleright" :
        index2=1;
        break;
    case "\\lhd$^b$" :
        index2=1;
        break;
	case "\\rhd$^b$" :
        index2=1;
        break;
    case "\\unlhd$^b$" :
        index2=1;
        break;
    case "\\unrhd$^b$" :
        index2=1;
        break;
	case "\\oplus" :
        index2=1;
        break;
    case "\\ominus" :
        index2=1;
        break;
    case "\\otimes" :
        index2=1;
        break;
	case "\\oslash" :
        index2=1;
        break;
    case "\\odot" :
        index2=1;
        break;
    case "\\bigcirc" :
        index2=1;
        break;
	case "\\dagger" :
        index2=1;
        break;
    case "\\ddagger" :
        index2=1;
        break;
    case "\\amalg" :
        index2=1;
        break;
	case "\\widetilde{abc}" :
        index2=2;
        break;
    case "\\overleftarrow{abc}" :
        index2=2;
        break;
    case "\\overline{abc}" :
        index2=2;
        break;
	case "\\overbrace{abc}" :
        index2=2;
        break;
    case "\\sqrt{abc}" :
        index2=2;
        break;
    case "\\widehat{abc}" :
        index2=2;
        break;
	case "\\overrightarrow{abc}" :
        index2=2;
        break;
    case "\\underline{abc}" :
        index2=2;
        break;
    case "\\sqrt[n]{abc}" :
        index2=2;
        break;
	case "\\frac{abc}{xyz}" :
        index2=2;
        break;
	case "\\hat{a}" :
        index2=3;
        break;
    case "\\check{a}" :
        index2=3;
        break;
    case "\\acute{a}" :
        index2=3;
        break;
	case "\\grave{a}" :
        index2=3;
        break;
    case "\\bar{a}" :
        index2=3;
        break;
    case "\\vec{a}" :
        index2=3;
        break;
	case "\\dot{a}" :
        index2=3;
        break;
    case "\\ddot{a}" :
        index2=3;
        break;
	case "\\rmoustache" :
        index2=4;
        break;
    case "\\arrowvert" :
        index2=4;
        break;
    case "\\lmoustache" :
        index2=4;
        break;
	case "\\Arrowvert" :
        index2=4;
        break;
    case "\\Arrowvert" :
        index2=4;
        break;
    case "\\bracevert" :
        index2=4;
        break;
	case "\\lgroup" :
        index2=4;
        break;
    default :
        index2=0;
    }
	
	
var a = [ 
"<img src='gifs/editor/t1.gif'>",
"<img src='gifs/editor/t2.gif'>",
"<img src='gifs/editor/t3.gif'>",
"<img src='gifs/editor/t4.gif'>",
"<img src='gifs/editor/t5.gif'>"
];

return a[index2];
}