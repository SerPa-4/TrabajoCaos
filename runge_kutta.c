#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double fx1(double x1){
    return sin(x1);
}

double runge_kutta_x1(double x1, double time_step){
    double t = time_step;

    double K1 = fx1(x1) * t;
    double K2 = fx1(x1 + 0.5*K1) * t;
    double K3 = fx1(x1 + 0.5*K2) * t;
    double K4 = fx1(x1 + K3) * t;

    return x1 + 1.0/6 * (K1 + 2*K2 + 2*K3 + K4);

}



int main(){

    FILE *fp;
    fp = fopen("file.txt", "w+");

    double values[100];

    srand(time(NULL));

    double time_step = 0.01;
    for(int j = 0; j < 100; j++){
        double x1 = 6.2*rand()/(double)(RAND_MAX);
        printf("%lf \n", x1);
        for(int i = 0; i < 10000; i++){
            x1 = runge_kutta_x1(x1, time_step);
            //printf("%lf \t %lf \n" , x1, time_step*i);
            //fprintf(fp,"%lf \t %lf \n", x1, time_step*i);
        }
        values[j] = x1;
    }
    printf("RESULTS:\n");
    for (int i= 0; i<100; i++){
        printf("%lf\n", values[i]);
    }
}