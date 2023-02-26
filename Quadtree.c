#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE} bool;

typedef struct bloc_image
{ int toutnoir ;
struct bloc_image * fils[4] ;
} bloc_image ;

typedef bloc_image *image ;

image  Construit_blanc(){
	image m = malloc(sizeof(bloc_image));
	m=NULL;
	return m;
}

image  Construit_noir(){
	image m = malloc(sizeof(bloc_image));
	m->toutnoir=TRUE;
	m->fils[0]=NULL;
	m->fils[1]=NULL;
	m->fils[2]=NULL;
	m->fils[3]=NULL;
	return m;
}

image  Construit_compose(image ihg, image ihd, image ibg, image ibd){
	image m = malloc(sizeof(bloc_image));
	m->toutnoir=FALSE;
	m->fils[0]=ihg;
	m->fils[1]=ihd;
	m->fils[2]=ibg;
	m->fils[3]=ibd;
	return m;
}

void aff_nrml (image m){
	if (m==NULL)
	{
		printf("B");
	} else if ((m->toutnoir==TRUE) &&(m->fils[0]==NULL) && (m->fils[1]==NULL) && (m->fils[2]==NULL) && (m->fils[3]==NULL))
	{
		printf("N");
	} else {
		printf("+");
		aff_nrml(m->fils[0]);
		aff_nrml(m->fils[1]);
		aff_nrml(m->fils[2]);
		aff_nrml(m->fils[3]);
	}
}

void aff_prfdr_bis (image m, int p){
	if (m==NULL)
	{
		printf("B%d ", p);
	} else if ((m->toutnoir==TRUE) &&(m->fils[0]==NULL) && (m->fils[1]==NULL) && (m->fils[2]==NULL) && (m->fils[3]==NULL))
	{
		printf("N%d ", p);
	} else {
		printf("+%d", p);
		aff_prfdr_bis(m->fils[0], p+1);
		aff_prfdr_bis(m->fils[1], p+1);
		aff_prfdr_bis(m->fils[2], p+1);
		aff_prfdr_bis(m->fils[3], p+1);
	}
}
bool EstBlanche(image m){
	if (m==NULL)
	{
		return TRUE;
	} else if ((m->toutnoir==TRUE) &&(m->fils[0]==NULL) && (m->fils[1]==NULL) && (m->fils[2]==NULL) && (m->fils[3]==NULL))
	{
		return FALSE;
	}else return (EstBlanche(m->fils[0]) && EstBlanche(m->fils[1]) && EstBlanche(m->fils[2]) && EstBlanche(m->fils[3]));
}
bool EstNoire(image m){
	if (m==NULL)
	{
		return FALSE;
	} else if ((m->toutnoir==TRUE) &&(m->fils[0]==NULL) && (m->fils[1]==NULL) && (m->fils[2]==NULL) && (m->fils[3]==NULL))
	{
		return TRUE;
	}else return (EstNoire(m->fils[0]) && EstNoire(m->fils[1]) && EstNoire(m->fils[2]) && EstNoire(m->fils[3]));
}

image Copie(image m){
	if (m==NULL)
	{
		return (Construit_blanc());
	} else if ((m->toutnoir==TRUE) &&(m->fils[0]==NULL) && (m->fils[1]==NULL) && (m->fils[2]==NULL) && (m->fils[3]==NULL))
	{
		return (Construit_noir());
	} else return (Construit_compose( Copie(m->fils[0]), Copie(m->fils[1]), Copie(m->fils[2]), Copie(m->fils[3])  )  );
}
void Rendmemoire (image* m){
	if ((*m)!=NULL)
	{
		Rendmemoire(&(*m)->fils[0]);
		Rendmemoire(&(*m)->fils[1]);
		Rendmemoire(&(*m)->fils[2]);
		Rendmemoire(&(*m)->fils[3]); 
		free (*m);
        *m=NULL;
	}
    
}

double Air(image m){
	if (EstBlanche(m))
	{
		return 0.0;
	}
	else if (EstNoire(m)){
		return 1.0;
	} else return ((1.0/4)*(Air(m->fils[0])+Air(m->fils[1])+Air(m->fils[2])+Air(m->fils[3]) ));

}

image Bis_lecture(int* i, char* s){
	if (s[*(i)]=='N')
	{
		return Construit_noir();
	} else if (s[*i]=='B')
	{
		return Construit_blanc();
	}else{ 
		*i=*i+1;
		image ihg= Bis_lecture(i, s);
		*i=*i+1;
		image ihd= Bis_lecture(i, s);
		*i=*i+1;
		image ibg= Bis_lecture(i, s);
		*i=*i+1;
		image ibd= Bis_lecture(i, s);
		return Construit_compose(ihg, ihd, ibg, ibd);
	}

}

image Lecture(){
    char s[1000];
	scanf("%s",s);
	int i=0;
	return Bis_lecture(&i, s);
}
int CompteSousImagesGrises(image m){
    if (EstBlanche(m)) {
        return 0;
    } else if (EstNoire(m)){
        return 0;
    }
    else {
        double A=Air(m);
        return ( ((A>=(1.0/3.0)) && (A<=(2.0/3.0))) + CompteSousImagesGrises(m->fils[0])+ CompteSousImagesGrises(m->fils[1])+ CompteSousImagesGrises(m->fils[2])+ CompteSousImagesGrises(m->fils[3]) );

    }
}

void Negatif(image* m){
    if(EstBlanche((*m))){
        (*m)=Construit_noir();
    } else if (EstNoire((*m))) {
        Rendmemoire(&(*m));
        (*m)==NULL;
    }else {
        Negatif(&((*m)->fils[0]));
        Negatif(&((*m)->fils[1]));
        Negatif(&((*m)->fils[2]));
        Negatif(&((*m)->fils[3]));
    }
}

int UnionNoir(image m1, image m2){
    if ( (EstNoire(m1)) || (EstNoire(m2)) ){
        return 1;
    } else if (EstBlanche(m1)){
        return EstNoire(m2);
    }else if (EstBlanche(m2)){
        return EstNoire(m2);
    }else {
        return (  UnionNoir(m1->fils[0], m2->fils[0])&&UnionNoir(m1->fils[1], m2->fils[1])&&UnionNoir(m1->fils[2], m2->fils[2])&&UnionNoir(m1->fils[3], m2->fils[3])  );
        
        
    }


}

void Intersection(image *m1, image m2){
    if (!(EstBlanche((*m1)))){
        if(EstNoire((*m1))){
            Rendmemoire(&(*m1));
            *m1=Copie(m2);
        
    
    } else if (!(EstNoire(m2))){
        if (EstBlanche(m2)){
            Rendmemoire(&(*m1));
            *m1=Construit_blanc();
        } else{
            Intersection(&((*m1)->fils[0]),m2->fils[0]);
            Intersection(&((*m1)->fils[1]),m2->fils[1]);
            Intersection(&((*m1)->fils[2]),m2->fils[2]);
            Intersection(&((*m1)->fils[3]),m2->fils[3]);
        }
    
    }
    }
}
int puissance(int x, int n) {
  int res = 1;
  for (int i = 0; i < n; i++)
  {
   res=res*x;
  }
  return res;
}

void bis_k( image m,char* t[], int DL, int FL,int DC, int FC){
    if(EstBlanche(m)){
        for (int i=DL; i<FL; i++){
            for (int j=DC; j<FC; j++){
                t[i][j]='.';
            }
        }
    }else if(EstNoire(m)){
        for (int i=DL; i<FL; i++){
            for (int j=DC; j<FC; j++){
                t[i][j]='8';
            }
        }
    } else if (((FL-DL)<=1)||((FC-DC)<=1)){
        t[DL][DC]='-';
    } else {
        bis_k(m->fils[0], t, DL,(FL+DL)/2, DC, (FC+DC)/2);
        bis_k(m->fils[1], t, DL,(FL+DL)/2,  (FC+DC)/2,FC);
        bis_k(m->fils[2], t, (FL+DL)/2,FL, DC, (FC+DC)/2);
        bis_k(m->fils[3], t, (FL+DL)/2,FL, (FC+DC)/2,FC);
    }


}

void print_tab(char* t[], int k){
    for (int i=0; i<k; i++){
            for (int j=0; j<k; j++){
                printf("%c",t[i][j]);
            }
            printf("\n");
        }
}

void aff_2_k_pixel( image m, int k){
    int puiss_2k= puissance(2, k);
    
    char **t=malloc(puiss_2k * sizeof(char*));
    for(int i=0; i< puiss_2k; i++){
        t[i]=malloc(puiss_2k * sizeof(char));
    }
    bis_k(m,t,0,puiss_2k,0,puiss_2k);
    print_tab(t,puiss_2k);
    
}


int main(int argc, char const *argv[])
{
	image m=Construit_compose( Construit_noir() , Construit_compose(Construit_noir(), Construit_blanc(), Construit_blanc(), Construit_blanc()), Construit_blanc(),Construit_compose (Construit_noir(), Construit_noir(), Construit_blanc(), Construit_noir()) );
	//aff_nrml(m);
	printf ("\n");
	/*aff_prfdr_bis(m, 0);
	printf ("\n");
	image m2 = Construit_compose( Construit_noir() , Construit_compose(Construit_compose(Construit_noir(),Construit_noir(),Construit_noir(),Construit_noir()),Construit_noir(),Construit_noir(),Construit_noir()),Construit_noir(),Construit_noir());
	aff_nrml(m2);
	printf ("\n");
	image m3 = Construit_compose(Construit_blanc(), Construit_compose(Construit_compose(Construit_blanc(),Construit_blanc(),Construit_blanc(),Construit_blanc()),Construit_blanc(),Construit_blanc(),Construit_blanc()),Construit_blanc(),Construit_blanc());
	aff_nrml(m3);
	printf ("\n");
	image mm=Lecture();
    aff_nrml(mm);
    printf("\n");
    aff_nrml(mm->fils[0]);
    printf("%f\n %d\n",Air(mm),CompteSousImagesGrises(mm));
    Negatif(&mm);
    aff_nrml(mm);
    image mm2=Lecture();
    aff_nrml(mm2);
    printf("\n");
    aff_2_k_pixel(mm2, 3);
	printf("e-n :%d    e-b :%d\n",EstNoire(m2),EstBlanche(m3) );*/
	return 0;
}
