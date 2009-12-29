%% This file is language-independent.

\text{header=wims(nonempty lines wims(record 0 of \datafile))}
\integer{n=wims(linecnt \header)}
\text{commonq=}
\for{k=1 to \n}{
 \text{l=\header[\k;]}
 \text{test=wims(char 1 to 3 of \l)}
 \text{l=wims(char 4 to -1 of \l)}
 \text{commonq=\test issametext .IQ?\commonq \l}
}

\integer{qcnt=items(\records)}
\integer{givetrue=1}
\integer{minfalse=0}
\text{option=}
\integer{tot=8}
\text{anstype=checkbox iswordof \option?checkbox:radio}
\text{chars=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z}

\text{ans=}
\text{list=}
\text{pick=}
\text{hint=}
\text{image=}
\text{feedback=}
\text{statement=}
\text{empty=}
\text{Tot=}

\for{rec in \records}{

\text{data=wims(trim wims(record \rec of \datafile))}
\text{data=wims(embraced randitem \data)}
\text{statement1=wims(line 1 of \data)}
\text{statement1=wims(singlespace wims(rows2lines \statement1))}
\integer{n=wims(linecnt \data)}
\text{true1=}
\text{false1=}
\text{contents=statement}
\text{fb1=}
\for{k=2 to \n}{
 \text{l=wims(trim wims(line \k of \data))}
 \text{c=wims(char 1 of \l)}
 \text{l=wims(char 2 to -1 of \l)}
 \text{l=wims(replace internal , by &#44; in \l)}
 \text{l=wims(singlespace wims(rows2lines \l))}
 \text{contents=\contents,\l}
 \if{\c issametext 0}{
   \text{false1=wims(append item \k to \false1)}
 }
 \if{\c issametext 1}{
   \text{true1=wims(append item \k to \true1)}
 }
 \if{\c isin Ff and \k > 2}{
  \text{fb1=\fb1\l}
 }
 \if{\c isin Hh}{
  \text{hint=\l}
 }
 \if{\c isin Ii}{
  \text{image=wims(trim \l)}
 }
 \text{fb1=\fb1,}
}
\integer{truecnt=items(\true1)}
\integer{falsecnt=items(\false1)}
\integer{givetrue1=\givetrue>\truecnt?\truecnt:\givetrue}
\integer{tot1=\tot > \falsecnt+\givetrue?\falsecnt+\givetrue:\tot}
\integer{givetrue1=\givetrue1>\tot1-1?\tot1-1}
\integer{minfalse1=\minfalse>\tot1-\givetrue1?\tot1-\givetrue1:\minfalse}
\text{tsh=shuffle(\truecnt)}
\text{true=item(\tsh,\true1)}
\if{\minfalse1>0}{
 \text{false1=item(1..\minfalse1,\false1);}
 \text{false2=item(\minfalse1+1..\falsecnt,\false1)}
}{
 \integer{minfalse1=0}
 \text{false2=\false1}
 \text{false1=}
}
\text{fsh=shuffle(\falsecnt)}
\text{false2=item(\fsh,\false2)}
\text{pick1=item(1..\givetrue1,\true),\false1 item(1..\tot1-\givetrue1-\minfalse1,\false2)}
\text{ind=wims(makelist 1 for x=1 to \givetrue1),wims(makelist 0 for x=1 to \tot1-\givetrue1)}
\text{sh=shuffle(\tot1)}
\text{ind=item(\sh,\ind)}
\text{pick1=item(\sh,\pick1)}
\text{ans1=positionof(1,\ind)}
\text{list1=item(1..\tot1,\chars)}
\text{Tot=\Tot\tot1,}
\text{list=\list\list1;}
\text{ans=\ans\ans1;}
\text{feedback=\feedback\fb1[\pick1];}
\text{pick1=\contents[\pick1]}
\text{pick=\pick\pick1;}
\text{statement=\statement\statement1;}

}

\text{repind=}
\text{indcolor=}
\text{reps=}
\text{steps=wims(makelist r x for x=1 to \qcnt)}
\text{steps=\steptype notsametext all?wims(items2lines \steps)}
\steps{\steps}

\statement{
\if{\image notsametext }{
  <img align=right hspace=10 src=\imagedir/\image> <p>
}
\commonq
\for{q=1 to \qcnt}{
 \if{\steptype issametext all or (\status issametext end and \q<=\step) or \q=\step}{
  \if{\qcnt>1}{<p> \q. }
  \statement[\q;]
  <p><table border=0 cellspacing=4>
  \for{i=1 to \Tot[\q]}{
   <tr><td nowrap>\embed{reply \q,\i}.</td>
   <td>\pick[\q;\i]</td></tr>
  }
  </table>
  \if{\status issametext end and \repind[\q]>0 and \feedback[\q;\repind[\q]] notsametext }{
   <p><font color=\indcolor[\q]><em>\feedback[\q;\repind[\q]]</em></font>
  }
  \if{\q<\qcnt and (\steptype issametext all or \q<\step)}{<p><hr>}
 }
}
\if{\image notsametext }{<br clear=right>}
}

\answer{\choicename 1}{\ans[1;];\list[1;]}{type=\anstype}{option=\option}
\answer{\choicename 2}{\ans[2;];\list[2;]}{type=\anstype}{option=\option}
\answer{\choicename 3}{\ans[3;];\list[3;]}{type=\anstype}{option=\option}
\answer{\choicename 4}{\ans[4;];\list[4;]}{type=\anstype}{option=\option}
\answer{\choicename 5}{\ans[5;];\list[5;]}{type=\anstype}{option=\option}
\answer{\choicename 6}{\ans[6;];\list[6;]}{type=\anstype}{option=\option}
\answer{\choicename 7}{\ans[7;];\list[7;]}{type=\anstype}{option=\option}
\answer{\choicename 8}{\ans[8;];\list[8;]}{type=\anstype}{option=\option}
\answer{\choicename 9}{\ans[9;];\list[9;]}{type=\anstype}{option=\option}
\answer{\choicename 10}{\ans[10;];\list[10;]}{type=\anstype}{option=\option}
\answer{\choicename 11}{\ans[11;];\list[11;]}{type=\anstype}{option=\option}
\answer{\choicename 12}{\ans[12;];\list[12;]}{type=\anstype}{option=\option}
\answer{\choicename 13}{\ans[13;];\list[13;]}{type=\anstype}{option=\option}
\answer{\choicename 14}{\ans[14;];\list[14;]}{type=\anstype}{option=\option}
\answer{\choicename 15}{\ans[15;];\list[15;]}{type=\anstype}{option=\option}
\answer{\choicename 16}{\ans[16;];\list[16;]}{type=\anstype}{option=\option}
\answer{\choicename 17}{\ans[17;];\list[17;]}{type=\anstype}{option=\option}
\answer{\choicename 18}{\ans[18;];\list[18;]}{type=\anstype}{option=\option}
\answer{\choicename 19}{\ans[19;];\list[19;]}{type=\anstype}{option=\option}
\answer{\choicename 20}{\ans[20;];\list[20;]}{type=\anstype}{option=\option}

\text{reps=\reply1,\reply2,\reply3,\reply4,\reply5,\reply6,\reply7,\preply8,\preply9,\reply10,
  \reply11,\reply12,\reply13,\reply14,\reply15,\reply16,\reply17,\preply8,\preply9,\reply20}
\for{t=1 to \qcnt}{
  \text{ind=positionof(\reps[\t],\chars)}
  \text{repind=\repind\ind,}
  \text{indcolor=\ind isitemof \ans[\t;]?\indcolor[]green,:\indcolor[]red,}
}

\hint{\hint}
