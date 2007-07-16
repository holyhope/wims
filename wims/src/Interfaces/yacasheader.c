char *firstupper[]={
"abs",
"and",
"arg",
"complex",
"conjugate",
"cos",
"cosh",
"cot",
"coth",
"csc",
"csch",
"denom",
"exp",
"factor",
"factorize",
"i",
"im",
"infinity",
"integrate",
"limit",
"ln",
"max",
"min",
"not",
"or",
"pi",
"print",
"random",
"re",
"round",
"sec",
"sech",
"sign",
"simplify",
"sin",
"sinh",
"solve",
"sqrt",
"tan",
"tanh",
"undefined",
};
#define firstupperno (sizeof(firstupper)/sizeof(firstupper[0]))

char header[]="\
tg(x) := Tan(x)\n\
log(x) := Ln(x)\n\
e := Exp(1)\n\
E := Exp(1)\n\
sgn(x) := Sign(x)\n\
ch(x) := Cosh(x)\n\
sh(x) := Sinh(x)\n\
th(x) := Tanh(x)\n\
acos(x) := ArcCos(x)\n\
arccos(x) := ArcCos(x)\n\
asin(x) := ArcSin(x)\n\
arcsin(x) := ArcSin(x)\n\
atan(x) := ArcTan(x)\n\
arctan(x) := ArcTan(x)\n\
arctg(x) := ArcTan(x)\n\
Argch(x) := ArcCosh(x)\n\
argch(x) := ArcCosh(x)\n\
acosh(x) := ArcCosh(x)\n\
Argsh(x) := ArcSinh(x)\n\
argsh(x) := ArcSinh(x)\n\
asinh(x) := ArcSinh(x)\n\
Argth(x) := ArcTanh(x)\n\
argth(x) := ArcTanh(x)\n\
atanh(x) := ArcTanh(x)\n\
ctg(x) := Cot(x)\n\
rint(x) := Round(x)\n\
RANDOM() := Random()\n\
SOLVE(x,y) := Solve(x,y)\n\
";

