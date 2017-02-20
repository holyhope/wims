
!! Selfridge check for primes.
!! Checks primes > 500 000, for otherwise it is in prime table.

!set Selfridge_src=Selfridge_table=vector(1000,x,0);\
\
{ Selfridge_check(x)=if(abs(x)<500000,return(1));\
  Selfridge_f=factor(x-1);Selfridge_n=matsize(Selfridge_f)[1];\
  for(Selfridge_k=1,Selfridge_n,\
    Selfridge_p=Selfridge_f[Selfridge_k,1];\
    if(Selfridge_p>=500000,\
      if(Selfridge_ptr>=999,return(-1));\
      Selfridge_ptr++; Selfridge_table[Selfridge_ptr]=Selfridge_p;\
    );\
    Selfridge_t=0;for(Selfridge_j=2,1000,\
      if(Mod(Selfridge_j,x)^(x-1)!=Mod(1,x), return(0));\
      Selfridge_d=(x-1)/Selfridge_p;\
      if(Mod(Selfridge_j,x)^Selfridge_d!=Mod(1,x),\
        Selfridge_t=Selfridge_j;break();\
      );\
    );\
    if(Selfridge_t==0,return(-1));\
  ); return(1);\
}\
\
{ Selfridge(x)=Selfridge_table[1]=x;\
  if(!isprime(x),return(0));\
  Selfridge_step=1; Selfridge_ptr=1;\
  while(Selfridge_step<=Selfridge_ptr,\
    Selfridge_xx=Selfridge_check(Selfridge_table[Selfridge_step]);\
    if(Selfridge_xx==0 || Selfridge_xx==-1, return(-1));\
    Selfridge_step++;\
  ); return(1);\
}\
\
selfridge(x)=Selfridge(x);
!exit

:
Selfridge_table=vector(1000,x,0);

{ Selfridge_check(x)=if(abs(x)<500000,return(1));
  Selfridge_f=factor(x-1);Selfridge_n=matsize(Selfridge_f)[1];
  for(Selfridge_k=1,Selfridge_n,
    Selfridge_p=Selfridge_f[Selfridge_k,1];
    if(Selfridge_p>=500000,
      if(Selfridge_ptr>=999,return(-1));
      Selfridge_ptr++; Selfridge_table[Selfridge_ptr]=Selfridge_p;
    );
    Selfridge_t=0;for(Selfridge_j=2,1000,
      if(Mod(Selfridge_j,x)^(x-1)!=Mod(1,x), return(0));
      Selfridge_d=(x-1)/Selfridge_p;
      if(Mod(Selfridge_j,x)^Selfridge_d!=Mod(1,x),
        Selfridge_t=Selfridge_j;break();
      );
    );
    if(Selfridge_t==0,return(-1));
  ); return(1);
}

{ Selfridge(x)=Selfridge_table[1]=x;
  if(!isprime(x),return(0));
  Selfridge_step=1; Selfridge_ptr=1;
  while(Selfridge_step<=Selfridge_ptr,
    Selfridge_xx=Selfridge_check(Selfridge_table[Selfridge_step]);
    if(Selfridge_xx==0 || Selfridge_xx==-1, return(-1));
    Selfridge_step++;
  ); return(1);
}

selfridge(x)=Selfridge(x);

