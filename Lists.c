
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE} bool;

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


/* implementation des listes chainees et certaines fonctions utiles */

void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}


/*** Fonctions et procédures de listes chainées ***/

bool ZeroEnDeuxiemePosition(Liste l) {
  return( (l != NULL) && (l->suivant != NULL) && ( l->suivant->nombre == 0 ));
}

bool QueDesZeros(Liste l) {
  if ( l == NULL ) {
    return TRUE;
  }
  else return ( (l->nombre == 0) && QueDesZeros(l->suivant) );
}

/* Version récursive sans sous-fonctionnalité */
int Compte0Initiaux1(Liste l) {
  if (estVide(l) || premier(l) != 0) {
    return 0;
  }
  else return 1 + Compte0Initiaux1(suite(l));
}

/* Version itérative */
int Compte0Initiaux2(Liste l) {

  Liste p = l;
  int cpt = 0;
  while ( (p!= NULL) && (p->nombre) == 0) {
    cpt++;
    p = p->suivant;
  }
  return cpt;
}

/* Version avec sous-fonction récursive terminale */
int Compte0Initiaux3Bis(Liste l, int acc) {
  if (estVide(l) || premier(l) != 0) {
    return acc;
  }
  else return Compte0Initiaux3Bis(suite(l), acc + 1);
}

int Compte0Initiaux3(Liste l) {
  return Compte0Initiaux3Bis(l, 0);
}

/* Version avec sous-procédure récursive terminale */
void Compte0Initiaux4Bis(Liste l, int *acc) {
  if (!estVide(l) && premier(l) == 0) {
    (*acc)++;
    Compte0Initiaux4Bis(suite(l), acc);
  }
}

int Compte0Initiaux4(Liste l) {
  int i = 0;
  Compte0Initiaux4Bis(l, &i);
  return i;
}

Liste IntersectionTriee( Liste l1, Liste l2){

    if ((l1==NULL) || (l2==NULL)) 
    {
        return NULL;
    } else if (l1->nombre == l2->nombre)
    {
        return ajoute(l1->nombre,IntersectionTriee(l1->suivant, l2->suivant) );
    }else if (l1->nombre < l2->nombre)
    {
      return  IntersectionTriee(l1->suivant, l2) ;
    } else return IntersectionTriee(l1, l2->suivant) ;
}

void ElimineKpremiersX (Liste* l, int k , int x){
    if ((k!=0)&&((*l)!= NULL))
    {
        if (x==(*l)->nombre)
        {
            depile(l);
            ElimineKpremiersX (l,(k-1),x);
        } else ElimineKpremiersX (&((*l)->suivant),k,x); 
    }

}

void bis4(Liste* l, int* k, int x){
    if ((*l)!=NULL)
    {
        bis4(&((*l)->suivant), k, x);
        if ((x==(*l)->nombre)&&(*k>0))
        {
            depile(l);
            (*k)=(*k)-1;
        }
    }
}

void ElimineKderniersX(Liste* l, int k, int x){
    
    int m =k;
    bis4(l,&m,x);
}

/*** Implémentations des files ***/

typedef Liste* File;


void ajoute_f (int x, File* f){

    Liste t= (Liste)malloc(sizeof(Bloc));
    t->nombre=x;

    if (*f==NULL)
    {
        *f=(File)malloc(sizeof(Liste));
        **f=NULL;
    }

     if (**f==NULL)
    {
        **f=t;
        t->suivant=t;
    } else {
        t->suivant=(**f)->suivant;
        (**f)->suivant=t;
        **f=t;

    }
}


void sortir_f (int *x,File* f){
    if ((*f==NULL)||(**f==NULL))
    {
        printf("erreur !\n");
    }else if ( **f==(**f)->suivant){
            free(**f);
            **f=NULL;
        }
    else {
        Liste tmp=(**f)->suivant;
        (**f)->suivant=(**f)->suivant->suivant;
        *x=tmp->nombre;
        free(tmp);
        tmp=NULL;


    }
}
/* Fonction Permutation */
typedef struct SuperBloc{
    Liste liste;
    struct SuperBloc* suivant;
}SuperBloc;

typedef SuperBloc* SuperListe;

SuperListe SuperListeInit(void) {
  return NULL;
}

bool SuperListeEstVide(SuperListe L) {
  return L == NULL;
}

SuperListe SuperListeAjoute(Liste l, SuperListe p) {
  SuperListe tmp = (SuperListe) malloc(sizeof(SuperBloc));
  tmp->liste = l;
  tmp->suivant = p;
  return tmp;
}

SuperListe SuperListeAjouteX(int x, SuperListe p) {
  SuperListe tmp = (SuperListe) malloc(sizeof(SuperBloc));
  initVide(&tmp->liste);
  empile(x, &tmp->liste);
  tmp->suivant = p;
  return tmp;
}

SuperListe SuperListeSuite(SuperListe p) {
  return p->suivant;
}

Liste SuperListePremier(SuperListe p) {
  return p->liste;
}
void detruire_liste (Liste* l){
    if (*l!=NULL)
    {
        depile(l);
        detruire_liste(l);
    }
}

void SuperListeDepile(SuperListe *L) {
    SuperListe tmp = *L ;
    *L = SuperListeSuite(*L) ;
    detruire_liste(&(tmp->liste));
    free(tmp);
}

void SuperListeFree(SuperListe *p) {
  if (!SuperListeEstVide(*p)) {
    SuperListeDepile(p);
    SuperListeFree(p);
  }
}

SuperListe Concat(SuperListe L1, SuperListe L2) {
  if (SuperListeEstVide(L1)) {
    return L2;
  }
  else {
    return SuperListeAjoute(SuperListePremier(L1), Concat(SuperListeSuite(L1), L2));
  }
}

SuperListe AETTL(int x, SuperListe L) {
  if (SuperListeEstVide(L)) {
    return SuperListeInit();
  }
  else {
    return SuperListeAjoute(ajoute(x, SuperListePremier(L)), AETTL(x, SuperListeSuite(L)));
  }
}

SuperListe ATP(int x, Liste L) {
  if (estVide(L)) {
    return SuperListeAjouteX(x, SuperListeInit());
  }
  else {
    return SuperListeAjoute(ajoute(x, L), AETTL(premier(L), ATP(x, suite(L))));
  }
}

SuperListe ATLTP(int x, SuperListe L) {
  if (SuperListeEstVide(L)) {
    return SuperListeInit();
  }
  else {
    return Concat(ATP(x, SuperListePremier(L)), ATLTP(x, SuperListeSuite(L)));
  }
}

SuperListe Permutations(int n) {
  if (n == 0) {
    return SuperListeAjoute(NULL, NULL);
  }
  else {
    return ATLTP(n, Permutations(n - 1));
  }
}

/* fonction utiles pour imprimer les resultats */

void print(Liste l){
    if (l!=NULL){
        printf("%d  ", l->nombre);
        print(l->suivant);
    }else printf ("\n");
}

void print_file(File f){
    if ( (f!=NULL) && (*f!=NULL))
    {
        Liste p=*f,x=p->suivant;
        while ( x!=p){
            printf("%d  ",x->nombre );
            x=x->suivant;
        }
        printf("%d\n",x->nombre );
    } else printf("vide\n");
}

void print_s (SuperListe l){
if (l!=NULL){
        print (l->liste);
        print_s(l->suivant);
}

}

int main (){
  
             
return 0;
}
