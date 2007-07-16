#ifndef CHEMEQ_H
#define CHEMEQ_H

//#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#define VERSION "1.12"

typedef struct {
  int Zed;
  char symb[4];
} atome;

extern atome lesatomes[];

typedef std::pair<std::string,int> AtomeCompte;

class Compteur : public std::map<std::string,float>{
public:
  std::ostream & operator << (std::ostream & o)const;
};

std::ostream & operator << (std::ostream & o, const Compteur & c);

class Chemeq;

class fraction{
public:
  int i;
  int d;
  fraction(int numerateur, int denominateur=1):i(numerateur),d(denominateur){};
  void inverse(){int n=i; i=d; d=n;};
  void simplifie();
};

std::ostream & operator << (std::ostream & o, fraction f);

fraction operator * (fraction f, int m);
fraction operator * (int m, fraction f);
fraction operator * (fraction f, fraction m);
fraction operator + (fraction f, fraction g);
fraction operator - (fraction f, fraction g);

bool operator > (fraction f, int i);
bool operator > (fraction f1, fraction f2);
bool operator != (fraction f, int i);

class AtomeListe{
  AtomeListe * suiv, *group;
  char symb[4];
  int Zed, nb, no, sqbr;

 public:
  AtomeListe(const char* nom, int num, AtomeListe * s=0, AtomeListe * g=0){
    strncpy(symb,nom,3); Zed=num; nb=1; sqbr=0;
    /* sqbr == 1 quand il y a un square bracket */
    suiv = s; group=g;
  };
  AtomeListe(const AtomeListe & a):
    suiv(a.suiv), group(a.group), Zed(a.Zed), nb(a.nb), sqbr(a.sqbr){
    strncpy(symb,a.symb,3);
  };
  const char * symbole() const{return symb;};
  int Z()const{return Zed;};
  int sq()const{return sqbr;};
  void sq(int val){sqbr=val;};
  void numerote(int n=0);
  void setmolecularite(int n){nb=n;};
  int getmolecularite()const{return nb;};
  AtomeListe * groupe(){return group;};
  void groupe(AtomeListe * al){group= al;};
  const AtomeListe * suivant()const{return suiv;};
  const AtomeListe * groupe()const{return group;};
  void setsuivant(AtomeListe * s){suiv=s;};
  void compte (Compteur &c, fraction mult=fraction(1,1))const;
  double weight(fraction mult=fraction(1,1))const;
  static AtomeListe * triage(AtomeListe * al);
  void printcount(std::ostream & o, const fraction&, int multiple) const;
  void printnorm(std::ostream & o) const;
  void debug(int decal = 0)const{
    for (int i=0; i< decal; i++) std::cout << " ";
    std::cout << "AtomeListe : ( & = " << this << " symb=\"" << symb << "\" Zed = " << Zed 
	 << " nb = " << nb << " no = " << no 
	 << " suiv = " << suiv << " group = " << group
	 << ")\n";
    if(group) group->debug(2+decal);
    if(suiv) suiv->debug(decal);
  };
};

bool operator == (const AtomeListe & a1, const AtomeListe & a2);

typedef enum { aqueous, gas, sol } moltype;

extern char* moltypeStr[]; /* les chaînes aq, g,s */

class Membre;

class Molec{
  AtomeListe * al;
  int ch;
  fraction nb;
  int no;
  moltype t;
 public:
  Molec(AtomeListe * a, int c = 0, int n=1, int d=1): 
    al(a), ch(c), nb(n,d), t(aqueous){};
  AtomeListe & liste()const{return *al;};
  int charge()const{return ch;};
  void nombre(int n, int d=1){nb=fraction(n,d);};
  fraction nombre()const{return nb;};
  moltype typage()const{return t;};
  void typage(moltype at){t=at;};
  void numero(int n){no=n;};
  int numero()const{return no;};
  void triage(){al = AtomeListe::triage(al);};
  void compte(Compteur & c)const{if (al) al->compte(c,nb);};
  double weight(void)const{if (al) return al->weight(nb); else return 0.0;};
  const std::string signature()const;
  void printNombre(std::ostream & o)const;
  bool printcount(std::ostream & o, bool first) const;
  bool printelec(std::ostream & o, bool first) const;
  bool printspecies(std::ostream & o, bool first) const;
  void printnorm(std::ostream & o)const;
  void printweigh(std::ostream & o)const;
  void coeff( fraction f);
  bool printNernst(std::ostream & o, char * prefix ="");
  bool iswater()const;
  bool iselectron()const;
  fraction  nbelectron()const;
  void debug(int decal = 0)const{
    for (int i=0; i < decal; i++) std::cout << " ";
    std::cout << "Molec : ( " << this << " charge = " << ch 
	 << " nombre = " << nb << " no = " << no;
    al->debug(decal+2);
    std::cout << ")\n";
  };
  // two Molecs are equal if the AtomLists and the charges are equal.
  friend bool operator == (const Molec & m1, const Molec & m2);
  friend Membre operator & (Membre & m1, Membre & m2);
  friend Membre operator - (Membre & m1, Membre & m2);
};

bool operator == (const Molec & m1, const Molec & m2);
std::ostream & operator << (std::ostream & o, const AtomeListe & l);
std::ostream & operator << (std::ostream & o, const Molec & m);

class Membre : public std::vector<Molec *>{
public:
  void compte(Compteur & c)const;
  void numerote();
  void triage();
  void printnorm(std::ostream & o) const;
  void printcount(std::ostream & o) const;
  void printelec(std::ostream & o) const;
  void printspecies(std::ostream & o) const;
  void printweight(std::ostream & o) const;
  void coeff( fraction f);
  void printNernst(std::ostream & o);
  int printableNernst();
  bool redox()const;
  fraction  nbelectron()const;
  void debug(int decal = 0)const{
    for (int i=0; i < decal; i++) std::cout << " ";
    std::cout << "Membre : ( " << this;
    for (int j=0; j < size(); j++){
      std::cout << j << " :\n";
      operator[](j)->debug(decal+2);
    }
    std::cout << "\n";
  }
};

// intersection between two Membres
Membre operator & (Membre & m1, Membre & m2);
// members of first set which are not in the second
Membre operator - (Membre & m1, Membre & m2);

std::ostream & operator << (std::ostream & o, const Membre & m);

class Chemeq{
  Membre * gauche, * droit;
  std::string cste;
  double val;
public:
  Chemeq(Membre * g, Membre * d) : gauche (g), droit(d){};
  const Membre * membredroit()const{return droit;};
  const Membre * membregauche()const{return gauche;};
  void numerote(){gauche->numerote(); droit->numerote();};
  void triage(){gauche->triage(); droit->triage();};
  /* ajuste le coefficient pour qu'il y ait 1 mol du premier réactif */
  void coeff1();
  void normalise(){numerote(); triage(); coeff1();};
  void printnorm(std::ostream & o);
  void printcount(std::ostream & o) const;
  void printelec(std::ostream & o) const;
  void printspecies(std::ostream & o) const;
  void printweight(std::ostream & o) const;
  void printNernst(std::ostream & o);
  std::string equilibre();
  bool redox()const;
  const std::string constante()const{ return cste;};
  void constante (const std::string s) { cste = s;};
  double valeur()const{return val;};
  void valeur(double r){val=r;};
};

std::ostream & operator << (std::ostream & o, const Chemeq & c);
//struct taken from Kyle Burton's gperiodic

/* structure to hold element data, as initialized from the static
 * mendeleiev.c */
enum info_types {
  NAME, SYMBOL, NUMBER, WEIGHT, MELTING, BOILING, PAULING,
  MAX_INFO_NR      /* Has to be the last element */
};

struct table_entry {
  char *info[MAX_INFO_NR];
};

extern struct table_entry table[];

double mendelweight(int i);
int findmendel(const char * symb);
double mendelweight(const char * symb);

#endif 
