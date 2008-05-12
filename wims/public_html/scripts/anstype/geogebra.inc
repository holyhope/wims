
pari_precision=$precision

pari_header=\
\
{\
 line(p1,p2)=\
 if(#p2==2,\
  a=p2[2]-p1[2];b=p1[1]-p2[1];c=p2[1]*p1[2]-p1[1]*p2[2];\
  return([0,0,0,a,b,c]));\
 if(#p2==3,\
  return([0,0,0,-p2[2],p2[1],p2[2]*p1[1]-p2[1]*p1[2]]),\
  return([0,0,0,p2[4],p2[5],-(p2[4]*p1[1] + p2[5]*p1[2])]));\
}\
{\
ray(p1,p2)=line(p1,p2)\
}\
{\
 midperpendicular(p1,p2)=\
  x1=p1[1];y1=p1[2];x2=p2[1];y2=p2[2];\
  a=x1-x2;b=y1-y2;c=(x2^2+y2^2-x1^2-y1^2)/2;\
  xm=(x1+x2)/2;ym=(y1+y2)/2;xd=x2-x1;yd=y2-y1;\
  return([0,0,0,a,b,c]);\
}\
\
{\
 perpendicular(p1,p2)=\
  x1=p1[1];y1=p1[2];\
  if(#p2==6,a=-p2[5];b=p2[4],a=p2[1];b=p2[2]);\
  c=-(a*p1[1]+b*p1[2]);\
  return([0,0,0,a,b,c]);\
}\
\
{\
 bissector(p1,p2,p3)=\
  v1=p1-p2; v2=p3-p2;\
  v1=v1/sqrt(norml2(v1)) ; v2=v2/sqrt(norml2(v1)) ;\
  return(midperpendicular(p2+v1,p2+v2));\
}\
{\
 circle(p1,p2)=\
  circ=(x-p1[1])^2 +(y-p1[2])^2 ;\
  if (#p2==2, diff=p2-p1;\
  c=circ-(diff[1]^2+diff[2]^2),\
  c=circ-(p2)^2);\
return([polcoeff(c,2,x),polcoeff(c,2,y),polcoeff(polcoeff(c,1,x),1,y),polcoeff(polcoeff(c,1,x),0,y),polcoeff(polcoeff(c,0,x),1,y),polcoeff(polcoeff(c,0,x),0,y)])\
}\
\
{\
 segment(p1,p2)=\
  if( #p2==2, return(sqrt(norml2(p2-p1))),return(p2));\
}\



{\
 middle(x1,y1,x2,y2)=\
  x=(x1+x2)/2;y=(y1+y2)/2;\
  return([x,y]);\
}\



\\ compute the line through 2 points ax+by+c=0 segment,x1,y1,x2,y2\
{\
 segment(p1,p2)=\
  x1=p1[1];y1=p1[2];x2=p2[1];y2=p2[2];\
  a=y2-y1;b=x1-x2;c=x2*y1-x1*y2;cnorm=max(abs(a),max(abs(b),abs(c)));\
  a=a/cnorm;b=b/cnorm;c=c/cnorm;\
  return([a,b,c,x1,y1,x2,y2]);\
}\
ray(p1,p2)=\
  x1=p1[1];y1=p1[2];x2=p2[1];y2=p2[2];\
  a=y2-y1;b=x1-x2;c=x2*y1-x1*y2;cnorm=max(abs(a),max(abs(b),abs(c)));\
  a=a/cnorm;b=b/cnorm;c=c/cnorm;\
  return([a,b,c,x1,y1]);\
}\
\
\\ compute the mid-perpendicular line of 2 points\
{\
 midper(p1,p2)=\
  x1=p1[1];y1=p1[2];x2=p2[1];y2=p2[2];\
  a=x1-x2;b=y1-y2;c=(x2^2+y2^2-x1^2-y1^2)/2;cnorm=max(abs(a),max(abs(b),abs(c)));\
  a=a/cnorm;b=b/cnorm;c=c/cnorm;\
  xm=(x1+x2)/2;ym=(y1+y2)/2;xd=x2-x1;yd=y2-y1;\
  return([a,b,c,xm+yd,ym-xd,xm-yd,ym+xd]);\
}\
\
\\ compute the middle of 2 points\
{\
 middle(x1,y1,x2,y2)=\
  x=(x1+x2)/2;y=(y1+y2)/2;\
  return([x,y]);\
}\
{\
 barycenter(p1,p2,t)=\
  x1=p1[1];y1=p1[2];x2=p2[1];y2=p2[2] ; t1=t[1]; t2=t[2];\
  if(t1+t2 == 0, return([]), x=(t1*x1+t2*x2)/(t1+t2);y=(t1*y1+t2*y2)/(t1+t2);\
  return([x,y]));\
}\
\
\\ compute the intersection point of two lines\
{\
 line_intersect(l1,l2)=\
  a1=l1[1];b1=l1[2];c1=l1[3];a2=l2[1];b2=l2[2];c2=l2[3];\
  det=a1*b2-a2*b1;\
  if(abs(det)<compare_precision, return("error parallel"));\
  x=-(c1*b2-b1*c2)/det;y=-(a1*c2-a2*c1)/det;\
  return([x,y]);\
}\
\
\\ compute the foot point of perpendicular of a line through a point.\
{\
 foot_perp(l1,p1)=\
  a1=l1[1];b1=l1[2];c1=l1[3];x1=p[1];x2=p[2];c2=-b1*x1+a1*y1;\
  det=(b1)^2+(a1)^2;\
  x=(-c1*a1-c2*b1)/det;y=(a1*c2-b1*c1)/det;\
  return([x,y]);\
}\
\
\\ internal computation, intersection point of a lines and a circle\
{\
 lc_int_(data)=\
  a=data[1];b=data[2];c=data[3];xc=data[4];yc=data[5];r=data[6];\
  if(abs(a)>abs(b),\
   b=-b/a;c=-c/a;\
   A=b^2+1;B=b*(c-xc)-yc;C=(c-xc)^2+yc^2-r^2;discr=B^2-A*C;\
   if(discr<-(compare_precision^2), return("error no_intersection"));\
   if(discr<0, discr=0);\
   discr=sqrt(discr);y1=(-B+discr)/A;y2=(-B-discr)/A;\
   x1=b*y1+c;x2=b*y2+c;\
  ,\
   a=-a/b;c=-c/b;\
   A=a^2+1;B=a*(c-yc)-xc;C=(c-yc)^2+xc^2-r^2;discr=B^2-A*C;\
   if(discr<-(compare_precision^2), return("error no_intersection"));\
   if(discr<0, discr=0);\
   discr=sqrt(discr);x1=(-B+discr)/A;x2=(-B-discr)/A;\
   y1=a*x1+c;y2=a*x2+c;\
  );\
  if(abs(x1)<range_limit && abs(y1)<range_limit && pointcheck([x1,y1])==0,\
   out=[x1,y1], out=[]);\
  if(abs(x2)<range_limit && abs(y2)<range_limit && \
   pointcheck([x2,y2])==0 && max(abs(x1-x2),abs(y1-y2))>closeness,\
   out=concat(out,[x2,y2]));\
  if(out==[], return("error no_available"), return(out));\
}\
\
\\ compute the intersection point of a lines and a circle\
{\
 lc_intersect(l1,c2)=\
  return(lc_int_(l1,c2));\
}\
\
\\ compute the intersection point of two circles\
{\
 circle_intersect(c1,c2)=\
  x1=c1[1];y1=c1[2];r1=c1[3];x2=c2[1];y2=c2[2];r2=c2[3];\
  a=2*(x1-x2);b=2*(y1-y2);c=x2^2+y2^2-x1^2-y1^2+r1^2-r2^2;\
  cnorm=max(abs(a),max(abs(b),abs(c)));\
  return(lc_int_([a/cnorm,b/cnorm,c/cnorm,x1,y1,r1]));\
}\
\
\\ compute a circle of center p1 and through p2.\
{\
 circle(p1,p2)=\
  diff=p2-p1;\
  radius=sqrt(diff[1]^2+diff[2]^2);\
  cir=concat(p1,radius);
  return(cir);\
}\
