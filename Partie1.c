#include <stdio.h>
#include <stdlib.h>

double e (int n){ // on supposera que n>2 pour avoir plus de précision
    double k=1, res=2;
    for (int i = 2; i <= n; i++)
    {
        k=k*i;
        res=res+1/((double)k);
    }
    return res;
}


double puissance_itr(double x, int n) {
  float res = 1;
  if (n < 0) {
    x = 1/x;
    n = -n;
  }
  for (int i = 0; i < n; i++)
  {
   res=res*x;
  }
  return res;
}

double bis5(double x, int n){
    if (n==0)
    {
        return 1;
    } else return x*bis5(x,n-1);
}
double puissance_rec(double x, int n) {
 if (n>=0)
    {
        return  bis5 (x,n);
    } else return 1/((double)bis5(x,-n));
}

double puissance_recterm_bis(double x, int n, double acc) {
  if (n == 0) {
    return acc;
  }
 else return puissance_recterm_bis(x, n - 1, acc * x);
}

double puissance_recterm(double x, int n) {
  if (n < 0) {
    x = 1/x;
    n = -n;
  }
  return puissance_recterm_bis(x, n, 1);
}

float puissance_itr2(float x, int n) {
  float cpt = 1;
  if (n < 0) {
    x = 1/x;
    n = -n;
  }
  for (; n > 1; n -= 2) {
    cpt = cpt * x * x;
  }
  if (n == 1) {
    cpt = cpt * x;
  }
  return cpt;
}


float bis_float ( float x, int n){
   if (n == 0 ) {
    return 1;
  }
  float acc = bis_float(x, n/2);
  if (n % 2 == 0) {
    return acc * acc;
  }
  else return acc * acc * x;
}

float puissance_rec2_float(float x, int n) {
 
  if (n < 0) {
      x = 1/x;
      n=-n;
  }
  bis_float (x,n);
  
}

float bis_double ( double x, int n){
   if (n == 0 ) {
    return 1;
  }
  double acc = bis_double(x, n/2);
  if (n % 2 == 0) {
    return acc * acc;
  }
  else return acc * acc * x;
}

float puissance_rec2_double(double x, int n) {
 
  if (n < 0) {
      x = 1/x;
      n=-n;
  }
  bis_double (x,n);
  
}

int ackermannI(int m, int n) {
  if (m == 0) {
    return n + 1;
  }
  else {
    int r = 1;
    for (int i = 1; i <= n + 1; i++) {
      r = ackermannI(m - 1, r);
    }
    return r;
  }
}

int ackermannR(int m, int n) {
  if (m == 0) {
    return n + 1;
  }
  if (n == 0) {
    return ackermannR(m - 1, 1);
  }
  else {
    return ackermannR(m - 1, ackermannR(m, n - 1));
  }
}

double X_rec(int n) {
  if (n == 0) {
    return 1;
  } else {
        float y = X_rec(n - 1);
        return y + 1/y;
      }
}

double X_itr(int n) {
  double x = 1;
  for ( int i=1 ; i<=n ; i++ ) {
    x = x + 1/x;
  }
  return x;
}

int main(void) {
  double exp = e(10);
  double p1 = puissance_rec2_double(1.1,10);
  double p2 = puissance_rec2_double(1.01,100);
  double p3 = puissance_rec2_double(1.001,1000);
   double p4 = puissance_rec2_float(1.1,10);
  double p5 = puissance_rec2_float(1.01,100);
  double p6 = puissance_rec2_float(1.001,1000);
  /* on remarque que double a plus de précision qu'un float quand la puissance est 
  trop grande ( car double est codé sur 64bits et le float sur 32bits)*/
  double p7 = puissance_rec(1.1,10);
  double p8 = puissance_rec(1.01,100);
  double p9 = puissance_rec(1.001,1000);
  double p10 = puissance_recterm(1.1,10);
  double p11 = puissance_recterm(1.01,100);
  double p12 = puissance_recterm(1.001,1000);
  /* on remarque que les algorithme de theta(n) sont plus précis que ceux de theta (log2(n))
  effectivement car si on a une erreur sur l appel recursif n/2 celui ci sera multiplié par une autre erreur
  ce qui fait que le taux d erreur augmente */
  // on remarque aussi pour des grand nombre le temps de calcul prend plus de temps en recursif qu'en recursif terminal
  int ack0 = ackermannR(0,0);
  int ack1 = ackermannR(1,0);
  int ack2 = ackermannR(2,0);
  int ack3 = ackermannR(3,0);
  int ack4 = ackermannR(4,0);
  /* int ack6 = ackermannR(6,0); en utilisant la valeur 6 la fonction tourne dans le vide et ne s'arrete pas */
  float X100_itr = X_itr(100);
  float X100_rec = X_rec(100);
  printf("1) e = %lf\n", exp);
  printf("2-a diviser pour regner avec double) 1.1^10 = %lf\n   1.01^100 = %lf\n   1.001^1000 = %lf\n", p1,p2,p3);
  printf("2-b diviser pour regner avec float) 1.1^10 = %f\n   1.01^100 = %f\n   1.001^1000 = %f\n", p4,p5,p6);
  printf("2-c recursive non terminal theta(n)) 1.1^10 = %lf\n   1.01^100 = %lf\n   1.001^1000 = %lf\n", p7,p8,p9);
  printf("2-d recursive terminale theta(n)) 1.1^10 = %lf\n   1.01^100 = %lf\n   1.001^1000 = %lf\n", p10,p11,p12);

  printf("3) Ack(0,0) = %i\n   Ack(1,0) = %i\n   Ack(2,0) = %i\n   Ack(3,0) = %i\n   Ack(4,0) = %i\n", ack0,ack1,ack2,ack3,ack4);
  printf("4) X_100 = %lf (itérative)\n   X_100 = %lf (récursive)\n", X100_itr, X100_rec);
    return 0;
}
