#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

#define p_link 0.1
#define conectividad_promedio 6


struct persona{
    int group; //1 o 2
    int cooperate;  //1 (si) o 0 (no)
    double payoff;  //recompensa total al jugar al juego
}; typedef struct persona Persona;


//La poblacion de cada familia sera un array
//Habra dos arrays, uno para cada familia
void matrix_to_0(int matriz_adyacencia[N1+N2][N1+N2]); //funcion que enlaza la red compleja, realiza la tarea en tres regiones

void link_nodes(int matriz_adyacencia[N1+N2][N1+N2]);
    void links_pop_1(int matriz_adyacencia[N1+N2][N1+N2]);
    void links_pop_2(int matriz_adyacencia[N1+N2][N1+N2]);
    void links_interpop(int matriz_adyacencia[N1+N2][N1+N2]);
    void diag_0(int matriz_adyacencia[N1+N2][N1+N2]);
    int has_link_interpop();
    int has_link_intrapop(int members);

void print_matrix(int matriz_adyacencia[N1+N2][N1+N2]);


int matriz_adyacencia[N1+N2][N1+N2]; //inicializar matriz adyacencia
/*No me acordaba de como hay que llamar a las matrices
void word(int sum[2][2]){
    printf("SMART\n");
    printf("%d", sum[1][1]);
    printf("HEEYEYEYEYE");
}
*/
int main(){
    int sum[2][2] = {{0,1},{2,10}};
    
    srand(time(NULL));
    matrix_to_0(matriz_adyacencia);
    link_nodes(matriz_adyacencia);

    
    print_matrix(matriz_adyacencia);//chupa mucho tiempo para matrices grandes, solo dibuja
    
    ////word(sum);
    printf("HAHS");
   
}
 
//Evalua si hay que tirar un link entre dos individuos de poblaciones diferentes o no
int has_link_interpop(){

    //generate random numberm
    double random_number = random()/((double)RAND_MAX+1);

    //metodo altura, para condicionar a la variable aleatoria
    //comparamos metodo altura con la probabilidad definida para intrafamilias
    //if random < prob --> return
    if(random_number < p_link) 
        return 1;
    //else
    return 0;

}

int has_link_intrapop(int members){//members es N1 o N2

    //generate random number
    double random_number = random()/((double)RAND_MAX+1);

    //metodo altura, para condicionar a la variable aleatoria
    //probabilidad a  conenctividad promedio (6) red ER:   p = <k>/(N-1)
    double probabiliy_k = conectividad_promedio/(double)(members-1);
    //printf("%lf\n", probabiliy_k); //debugging reasons
    //if random < prob --> return yes
    if(random_number < probabiliy_k) 
        return 1;
    //else
    return 0;

}

void matrix_to_0(int matriz_adyacencia[N1+N2][N1+N2]){  //Inicializa la matriz a 0 en todos casillas
    
    for(int i = 0; i < N1+N2; i++){
        for(int j = 0; j < N1 + N2 ; j++){
            matriz_adyacencia[i][j] = 0;
        }
    }
}

void copy_chain(Persona *x, Persona *y, int length){    //copia contenidos una struct en otra
    for(int i=0;i<length;i++){
        y[i].group=x[i].group;
        y[i].cooperate=x[i].cooperate;
        y[i].payoff=x[i].payoff;
    }
}


/*Añadir un readme con la matriz para que se vea de forma visual*/
void links_pop_1(int matriz_adyacencia[N1+N2][N1+N2]){
    int people_pop_1 = N1;

    //Generar links entre individuos misma poblacion
    for (int i = 0; i < people_pop_1;i++){//individuo que lanza el link

        for(int j = 1; j < people_pop_1; j++){//individuo que recibe el link

            if (has_link_intrapop(N1)){
                matriz_adyacencia[i][j] = 1;//escribir link en matriz en region poblacion 1 con poblaicon 1
                matriz_adyacencia[j][i] = 1;//Asegurar sea simetrica (bidireccional)
            }
        }
    }

}

void links_pop_2(int matriz_adyacencia[N1+N2][N1+N2]){
    int people_pop_2 = N2;

    //Generar links entre individuos misma poblacion
    for (int i = 0; i < people_pop_2;i++){//individuo que lanza el link

        for(int j = 1; j < people_pop_2; j++){//individuo que recibe el link

            if (has_link_intrapop(N2)){
                matriz_adyacencia[i+N1][j+N1] = 1;//escribir link matriz, region poblacion 2 con poblacion 2
                matriz_adyacencia[j+N1][i+N1] = 1;//Asegurar sea simetrica (bidireccional)
            }
        }
    }

}


void links_interpop(int matriz_adyacencia[N1+N2][N1+N2]){
    int people_pop_1 = N1;
    int people_pop_2 = N2;

    //Generar links entre individuos misma poblacion
    for (int i = 0; i < people_pop_1;i++){//individuo que lanza el link

        for(int j = 0; j < people_pop_2; j++){//individuo que recibe el link

            if (has_link_interpop()){
                matriz_adyacencia[i+N1][j] = 1;//escribir link matriz, region poblacion 1 con poblacion 2
                matriz_adyacencia[j][i+N1] = 1;//escribir link matriz, region poblacion 2 con poblacion 1
            }
        }
    }
}

void diag_0(int matriz_adyacencia[N1+N2][N1+N2]){
    for(int i = 0; i < N1+N2;i++){
        matriz_adyacencia[i][i] = 0;
    }
}

void link_nodes(int matriz_adyacencia[N1+N2][N1+N2]){
    links_pop_1(matriz_adyacencia);
    links_pop_2(matriz_adyacencia);
    links_interpop(matriz_adyacencia);
    diag_0(matriz_adyacencia);
}

void print_matrix(int matriz_adyacencia[N1+N2][N1+N2]){
    for(int i = 0; i < N1+N2;i++){
        for (int j = 0; j < N1+N2; j++){
            printf("%d " , matriz_adyacencia[i][j]);
        }
        printf("\n");
    }
}