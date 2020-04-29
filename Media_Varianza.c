#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100000

void med_var(float *serie,int Numero,float *Media,float *Varianza)
{
    *Media=0;
    for(int i=0;i<Numero;i++)
        *Media+=serie[i]/((float)Numero);

    *Varianza=0;
    for(int j=0;j<Numero;j++)
        *Varianza+=(serie[j]*serie[j]-(*Media)*(*Media))/((float)(Numero-1));

}

































/*
int main()
{
    FILE *f;
    f=fopen("estadistica.txt","w");

    float a,b;
    a=-2;   b=5;

    float n[N],media,varianza;
    for(int i=0;i<N;i++)
        n[i]=a+(b-a)*(rand()/((float)RAND_MAX+1));

    for(int j=0;j<N;j++)
        fprintf(f,"%d\t%f\n",j,n[j]);

    med_var(n,N,&media,&varianza);
    fprintf(f,"\t%f\t%f\n",media,varianza);



    fclose(f);

}
*/
