#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Parisi_Rapuano.c"

#define N1 10
#define N2 10

//de mayor a menor
#define PD_T 1.5
#define PD_R 1.0
#define PD_P 0.0
#define PD_S 0.0

//de mayor a menor
#define SD_W 1.5
#define SD_T 1.0
#define SD_L 0.0
#define SD_X -1.0

void iniMatrix(int A[][N1],int col,int fil,int type);
double MaximoArray(int A[][N1],int lenght,int indice);

struct persona{
    int group; //1 o 2
    int cooperate;  //1 (si) o 0 (no)
    double payoff;  //recompensa total al jugar al juego
}; typedef struct persona Persona;


void copy_chain(Persona *x, Persona *y, int length){    //x se copia en y
    for(int i=0;i<length;i++){
        y[i].group=x[i].group;
        y[i].cooperate=x[i].cooperate;
        y[i].payoff=x[i].payoff;
    }
}

void print_chain(Persona *x, int length){
    printf("\n");
    for(int i=0;i<length;i++)
        printf("Group=%d\tCooperate=%d\tPayoff=%lf\n",x[i].group,x[i].cooperate,x[i].payoff);
}

void PD(Persona *x,int pos_x,Persona *y,int pos_y){     //Dilema del Prisionero
    if(x[pos_x].cooperate==1 && y[pos_y].cooperate==1){
        x[pos_x].payoff+=PD_R;
        //y[pos_y].payoff+=PD_R;
    }
    if(x[pos_x].cooperate==1 && y[pos_y].cooperate==0){
        x[pos_x].payoff+=PD_S;
        //y[pos_y].payoff+=PD_T;
    }
    if(x[pos_x].cooperate==0 && y[pos_y].cooperate==1){
        x[pos_x].payoff+=PD_T;
        //y[pos_y].payoff+=PD_S;
    }
    if(x[pos_x].cooperate==0 && y[pos_y].cooperate==0){
        x[pos_x].payoff+=PD_P;
        //y[pos_y].payoff+=PD_P;
    }
}

void SD(Persona *x,int pos_x,Persona *y,int pos_y){     //Halcón-Paloma
    if(x[pos_x].cooperate==1 && y[pos_y].cooperate==1){
        x[pos_x].payoff+=SD_T;
        //y[pos_y].payoff+=SD_T;
    }
    if(x[pos_x].cooperate==1 && y[pos_y].cooperate==0){
        x[pos_x].payoff+=SD_L;
        //y[pos_y].payoff+=SD_W;
    }
    if(x[pos_x].cooperate==0 && y[pos_y].cooperate==1){
        x[pos_x].payoff+=SD_W;
        //y[pos_y].payoff+=SD_L;
    }
    if(x[pos_x].cooperate==0 && y[pos_y].cooperate==0){
        x[pos_x].payoff+=SD_X;
        //y[pos_y].payoff+=SD_X;
    }

}

void Game(Persona *x, int length){    //cada nodo juega con todos sus vecinos
    Persona aux[length];
    copy_chain(x,aux,length);       //guardamos una copia

    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++)
            if(x[i].group==x[j].group)
                PD(x,i,aux,j);
            else
                SD(x,i,aux,j);
    }
}
// FUncion donde calculamos si el nodo i cambia su estrategioa o no
void  PayoffChange( Persona *x,int length, int Matriz_de_adyacencia[][N1])
    {
        int *aux; // Array auxiliar para guardar los cambios o no de la estrategia
        for(int i=0;i<length;i++){
            int dado = (int)(random()*length+1); // Tiramos un numero aleatorio para ver con que vecino comparamos
                if (x[i].payoff< x[dado].payoff){ // la primera condicion para ver si cambiamos la estrategia si nuestro payoof es mayor que el del nodo mirado no cambiamos si es menor entrmaos
                double maximo=MaximoArray(Matriz_de_adyacencia,N1,i); // calculo del maximo para los nodos que vemos
                double probabilidad =  (x[dado].payoff-x[i].payoff)/maximo; // calculo de la probabulidad de cambiar nuestra estrategia
                double omega = random();    // Tiramos un numero aleatorio entre 0 y 1
                if(omega > probabilidad) aux[i]=x[dado].cooperate; // Hacemos metropolis
                else aux[i]=x[i].cooperate;
                }else{
                aux[i]=x[i].cooperate;
                }
        }
        for(int i=0;i<length;i++)
                x[i].cooperate=aux[i];
    }


// Para el maximo me da igual un int o double deperndera del problema
double MaximoArray(int A[][N1],int lenght,int indice)
{
    double Max=(double)(A[indice][0]-A[indice][indice]);
    for (int i=1;i<N1;i++){
        double aux=(A[indice][i]-A[indice][indice]);
        if (aux>=Max) Max=aux;
    }
    return Max;
}
int main(){

    ini_rand(time(NULL));   //Inicia la semilla de nuemro srandom para Parisi-Rapuano
    int Adj_matrix[N1][N1]; // de primeras pruebo una matrriz

    iniMatrix(Adj_matrix,N1,N1,1);
    Persona Population[N1+N2];
    Persona Population_aux[N1+N2];  //Para almanecenar los cambios como dijo el hombre

//#######################################################
//Toma las comndiciones iniciales

    for(int i=0;i<N1;i++)
        Population[i].group=1;

    for(int i=0;i<N2;i++)
        Population[N1+i].group=2;

    for(int i=0;i<(N1+N2);i++)  //Inicialmente igual de probable que cooperen o no
        Population[i].cooperate=(int)(2*random());

    for(int i=0;i<(N1+N2);i++)
        Population[i].payoff=0;
    /*

    print_chain(Population, N1+N2);

    Game(Population,N1+N2);

    print_chain(Population, N1+N2);
    */
}
void iniMatrix(int A[][N1],int col,int fila,int type)//
{
    switch(type){
        case 0:
            for (int i=0;i<fila;i++)
                for(int j=0; j<col;j++)
                {
                    A[i][j]= (int)((random())*(fila+1));
                }
        case 1:
            for (int i=0;i<fila;i++){
                for(int j=0; j<col;j++)
                {
                    A[i][j]= (int)((random())*(fila+1));
                }
                A[i][i]=0;
            }
    }
}
/*
Para pintar matrices
for (int i=0;i<N1;i++)
    {
        for(int j=0; j<N1;j++)
                {
                    printf("%d \t",Adj_matrix[i][j]);
                }
             printf("\n");
    }
*/
