
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Pongo todos los parametros como variables y no constantes, ya se cambiaran a #define segun se vea necesario
*/
#define N1 100
#define N2 100

double defect_reward=1.12;
double coop_reward=0;
double defect_punish=-0.4;
double prob=0.3;
double time_step = 0.001;


double fx1(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob);
double fx2(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob);
double runge_kutta_x1(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob, double time_step);
double runge_kutta_x2(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob, double time_step);
void hundred_arrows();

double modulo(double x, double y){
    double m;
    m=x*x+y*y;
    return pow(m,0.5);
}

int main(){
    hundred_arrows();


    FILE *fp;
    fp = fopen("XD.txt", "w");
    double j = 0;
    for(int i = 0; i < 1000; i++){

        fprintf(fp,"%lf \t %lf \n", j,j*2-1000/j);
        j+=1;
    }
    fclose(fp);
}









//N1 y N2 se pueden definir mediante defines
double fx1(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob){

    double b = defect_reward;
    double r = coop_reward;
    double e = defect_punish;
    double p = prob;

    double logist_eq = x1*(1-x1);
    double par_first_half = (N1 - 1)*(x1 * (1 - b + r) -r);
    double par_second_half= N2*p*(x2 * (1 - b + e) - e);

    return logist_eq * (par_first_half + par_second_half);
}

double fx2(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob){
    double b = defect_reward;
    double r = coop_reward;
    double e = defect_punish;
    double p = prob;


    double logist_eq = x2*(1-x2);
    double par_first_half = (N2 - 1)*(x2 * (1 - b + r) -r);
    double par_second_half= N1*p*(x1 * (1 - b + e) - e);

    return logist_eq * (par_first_half + par_second_half);
}

double runge_kutta_x1(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob, double time_step){
    double t = time_step;

    double K1 = fx1(x1, x2, defect_reward, coop_reward, defect_punish, prob) * t;
    double K2 = fx1(x1 + 0.5*K1, x2, defect_reward, coop_reward, defect_punish, prob) * t;
    double K3 = fx1(x1 + 0.5*K2, x2, defect_reward, coop_reward, defect_punish, prob) * t;
    double K4 = fx1(x1 + K3, x2, defect_reward, coop_reward, defect_punish, prob) * t;

    return x1 + 1.0/6 * (K1 + 2*K2 + 2*K3 + K4);

}

double runge_kutta_x2(double x1, double x2, double defect_reward, double coop_reward, double defect_punish, double prob, double time_step){
    double t = time_step;

    double K1 = fx2(x1, x2, defect_reward, coop_reward, defect_punish, prob) * t;
    double K2 = fx2(x1, x2 + 0.5*K1, defect_reward, coop_reward, defect_punish, prob) * t;
    double K3 = fx2(x1, x2 + 0.5*K2, defect_reward, coop_reward, defect_punish, prob) * t;
    double K4 = fx2(x1, x2 + K3, defect_reward, coop_reward, defect_punish, prob) * t;

    return x2 + 1.0/6 * (K1 + 2*K2 + 2*K3 + K4);

}




void hundred_arrows(){
    FILE *fp;
    fp = fopen("phase_portrait.txt", "w");

    double x1 = 0;
    double x2 = 0;

    double derivada_x1;
    double derivada_x2;
    double derivada_modulo;
    double componente_x, componente_y;

    double min, max;

    derivada_x1=fx1(x1,x2,defect_reward,coop_reward,defect_punish,prob);
    derivada_x2=fx2(x1,x2,defect_reward,coop_reward,defect_punish,prob);
    derivada_modulo=modulo(derivada_x1,derivada_x2);

    //min=max=derivada_modulo;      Creia que podria usarlo

    for (int i = 0; i < 11; i++){
        for (int j = 0; j <11 ; j++){
            derivada_x1=fx1(x1,x2,defect_reward,coop_reward,defect_punish,prob);
            derivada_x2=fx2(x1,x2,defect_reward,coop_reward,defect_punish,prob);
            derivada_modulo=modulo(derivada_x1,derivada_x2);

            /*
            if(derivada_modulo>max)
                max=derivada_modulo;
            if(derivada_modulo<min)
                min=derivada_modulo;
            */

            componente_x=derivada_x1/(25*derivada_modulo);
            componente_y=derivada_x2/(25*derivada_modulo);

            if(derivada_modulo==0)
                componente_x=componente_y=0;


            fprintf(fp,"%lf \t %lf \t %lf \t %lf \t %lf \n", x1,x2,componente_x,componente_y,derivada_modulo);

            x2 +=1.0/10;
        }
        x2 = 0;
        x1 += 1.0/10;
    }
    //fprintf(fp,"\n # %lf\t %lf",min,max);
    fclose(fp);
}
