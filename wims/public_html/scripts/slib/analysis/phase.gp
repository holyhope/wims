\\ Les variables commentées sont mis par defaut dans wims

\\color=red
\\LIM = 15;
\\NTEST  =  50;
\\MINDIV  =  2; \\
\\MAXCOUNT  =  50; \\ ??
\\XDIV  =  25; \\ on découpe le carré en petits carrés
\\YDIV  =  25;
\\ zoom =  4.0;
\\XMIN  =  (-zoom);
\\YMIN  =  (-zoom);
\\XMAX  =  (zoom);
\\YMAX  =  (zoom);
\\dx(x,y) = funct[1];
\\dy(x,y) = funct[2];

program_gp=ARROW_LEN  =  5; \\ taille de la flèche\
ARROW_WIDTH = 8;\
XSTEP  =  1.0*(XMAX-XMIN)/XDIV;\
YSTEP  =  1.0*((YMAX-YMIN)/YDIV);\
XDEN  =  (1.0/XSTEP);\
YDEN  =  (1.0/YSTEP);\
RAND_MAX  =  2^31;\
MIN_STEP  =  2; /* minimum steps to draw arrows */\
width = 200; /*en fait le résultat n'en dépend. Définit plutot la precision\
en pixels*/\
height = 200; \\à mettre à l'extérieur ?\
\
pr  =  matrix(XDIV,YDIV); /* footprint */\
xr  =  matrix(XDIV,YDIV);\
nr  =  matrix(XDIV,YDIV); /* used by get_point() */\
\
gxden = 1.*width/(XMAX - XMIN);\
gxden1  =  gxden^(-1);\
gyden = 1.*height/(YMAX - YMIN);\
gyden1  =  gyden^(-1);\
\
img  =  [];\
ARROW = matrix(7,1);\
transx( x)  =  round((x - XMIN)*XDEN);\
transy( y)  =  round((y - YMIN)*YDEN);\
\
/* returns 0 for success,  - 1 for out - of - bound or already - gone - to (x,y)\
et met 1 dans la matrice pr */\
\
footprint( px, py)  =\
{\
  if (px >= 1 && px <=  XDIV && py >= 1 && py<= YDIV && !pr[px,py],\
    pr[px,py]  =  1; 0, - 1\
  );\
}\
\
/* returns 0 for success, -1 for fail */\
get_point()  =\
{\
  local(div, i, j,\
  mdiv, mi = 0, mj = 0,found);\
  mdiv = 0;\
  div = 1;\
  xr  =   pr;\
  while (1,\
      if (div > XDIV, break);\
      found = 0;\
      for (i = 1, XDIV-div+1,\
       for (j = 1,YDIV-div+1,\
        if (xr[i,j] == 0,\
         found = 1; mdiv = div;\
         mi = i; mj = j; break;\
        )\
       )\
      );\
      if (!found, break);\
       xr  =  matrix(XDIV-div,YDIV-div,i,j,\
       if( (xr[i,j]+xr[i,j+1]+xr[i+1,j]+xr[i+1,j+1]), 1, 0)\
        );\
      div ++;\
    );\
  if (mdiv >=  MINDIV,\
      x0  =  XMIN + (mi + (mdiv - 1)*0.5)*XSTEP;\
      y0  =  YMIN + (mj + (mdiv - 1)*0.5)*YSTEP;\
      return(0)\
     ,\
      return(-1)\
  );\
}\
\
draw_init()  =  pr  =   matrix(XDIV,YDIV);\
\
frand( mmin,  mmax) = mmin + (mmax - mmin)*random(RAND_MAX)/RAND_MAX*1.;\
\
\
get_dt()  =\
{\
  local(dt,\
   x1, y1, xp, yp, i);\
\
  dt = 1.0;\
\\ initialiser au hasard le random ??\
\
  for (i = 1, NTEST,\
      x1 = frand(XMIN, XMAX);\
      y1 = frand(YMIN, YMAX);\
\\    xp = abs(subst(subst( dx, x,x1), y,y1));\
\\    yp = abs(subst(subst( dy, x,x1), y,y1));\
      xp = abs(dx(x1,y1));\
      yp = abs(dy(x1,y1));\
      if (xp*dt > XSTEP, dt = XSTEP/xp);\
      if (yp*dt > YSTEP, dt = YSTEP/yp);\
    );\
  dt*0.5; /* for precision */\
}\
\
do_loop( x0,  y0,  dt)  =\
{\
  local(i, count = 0, steps = 0,\
   px, py, x1,y1, lx, ly,\
   xa  = vector(5), ya  = vector(5),img1);\
   x1  =  x0; y1  =  y0;\
   img1 = [round((x1 - XMIN)*gxden)*gxden1 + XMIN, round((y1 - YMIN)*gyden)*gyden1 + YMIN];\
   while (1,\
      steps ++;\
      px = transx(x1); py = transy(y1);\
      if (footprint(px, py)<0 && steps > 1, break);\
      lx = x1; ly = y1;\
      count = 0;\
      while (count < MAXCOUNT,\
        count ++;\
        xa[1] = x1; ya[1] = y1;\
        for (i = 2, 5,\
        xa[i] = xa[1] + dx(xa[i-1],ya[i-1])*dt;\
        ya[i] = ya[1] + dy(xa[i-1],ya[i-1])*dt\
         );\
        x1 = (xa[2]+2.0*xa[3]+xa[4]-xa[5])*(1/3.0);\
        y1 = (ya[2]+2.0*ya[3]+ya[4]-ya[5])*(1/3.0);\
        if (transx(x1) !=  px, break);\
        if (transy(y1) !=  py, break);\
      );\
      if (dt>0 && steps == 1,\
        dir_angle =  if( x1 !=  x0, atan((y1-y0)/(x1-x0))+if(x1-x0 <0,Pi,0), sign(y1-y0)*Pi/2));\
      img2  =  [round((x1-XMIN)*gxden)*gxden1 + XMIN, round((y1-YMIN)*gyden)*gyden1 + YMIN];\
      img1  =  concat( img1, img2);\
    );\
  img  =  concat(img, [mattranspose(img1)]);\
 steps;\
}\
\
draw_main( dt)  =\
{ local(x0, y0, px0, py0, px1, py1, px2, py2, px3, py3,\
   step1, step2);\
  x0 = 0; y0 = 0;\
  draw_init();\
  test  =  0; test1  =  0;\
  while(test  >=  0 && test1 < LIM,\
   test1 ++;\
   step1 = do_loop(x0, y0, dt);\
   step2 = do_loop(x0, y0, -dt);\
   if (step1 >= MIN_STEP+1 && step2 >= MIN_STEP, /* draw an arrow */\
    px0 = round((x0-XMIN)*gxden)*gxden1 + XMIN;\
    py0 = round((y0-YMIN)*gyden)*gyden1 + YMIN;\
    px1 = px0+round(ARROW_LEN*cos(dir_angle))*gxden1;\
    py1 = py0+round(ARROW_LEN*sin(dir_angle))*gyden1;\
	  ARROW  =  concat(ARROW, [arrow; px0;py0;px1;py1;ARROW_WIDTH;color])\
   );\
  test  =  get_point();\
  );\
 ARROW;\
}\
\
draw_main(get_dt());
