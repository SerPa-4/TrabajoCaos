

//Necesita array de personas y matriz adyacencia
#define N1 10
#define N2 10
#define personas N1+N2


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






int matriz_adyacencia[N1+N2][N1+N2];
struct persona{
    int cooperate;  //1 (si) o 0 (no)
    double payoff;  //recompensa total al jugar al juego
}; typedef struct persona Persona;
Persona population_tot[N1+N2];

//realiza una ronda de interacciones
void round_of_game(int matriz_adyacencia[N1+N2][N1+N2], Persona population_tot[N1+N2]);
    int same_family(int person, int neighbour);
    void PD(Persona population_tot[N1+N2], int person, int neighbour);
    void SD(Persona population_tot[N1+N2], int person, int neighbour);  

int main(){
    printf("OWO");
}




void round_of_game(int matriz_adyacencia[N1+N2][N1+N2], Persona population_tot[N1+N2]){
    //bruteforces
    for(int person = 0; person < N1+N2; person++){//every person in population

        for(int neighbour = 0; neighbour < N1+N2; neighbour++){//Every possible neighbour the person plays with

            if (matriz_adyacencia[person][neighbour] == 1){ // if they are linked, then play
                if (same_family(person, neighbour))
                    PD(population_tot,person,neighbour);
                else
                {
                    SD(population_tot, person, neighbour);
                }
                
            }
            //otherwise, they are not neighbours

        }
    }
    /*
    Por como esta programado, cada pareja de vecinos juega 2 veces, no influye si todos van multiplicados por un factor, pero para corregir
    */
   for (int persona = 0; persona < N1+N2; persona++){
       population_tot[persona].payoff /= 2;
   }
}

int same_family(int person, int neighbour){
    if (person < N1 && neighbour < N1) 
        return 1;//ambos pertenecen a la familia 1
    if (person > N1 && neighbour > N1)
        return 1;//ambos pertenencen a la familia 2

    //en cualquier otro caso
    return 0;//familias diferentes
    
}



void PD(Persona population_tot[N1+N2], int person, int neighbour){     //Dilema del Prisionero
    if(population_tot[person].cooperate==1 && population_tot[neighbour].cooperate==1){
        population_tot[person].payoff+=PD_R;
        population_tot[neighbour].payoff+=PD_R;
    }
    if(population_tot[person].cooperate==1 && population_tot[neighbour].cooperate==0){
        population_tot[person].payoff+=PD_S;
        population_tot[neighbour].payoff+=PD_T;
    }
    if(population_tot[person].cooperate==0 && population_tot[neighbour].cooperate==1){
        population_tot[person].payoff+=PD_T;
        population_tot[neighbour].payoff+=PD_S;
    }
    if(population_tot[person].cooperate==0 && population_tot[neighbour].cooperate==0){
        population_tot[person].payoff+=PD_P;
        population_tot[neighbour].payoff+=PD_P;
    }
}

void SD(Persona population_tot[N1+N2], int person, int neighbour){     //Halcón-Paloma
    if(population_tot[person].cooperate==1 && population_tot[neighbour].cooperate==1){
        population_tot[person].payoff+=SD_T;
        population_tot[neighbour].payoff+=SD_T;
    }
    if(population_tot[person].cooperate==1 && population_tot[neighbour].cooperate==0){
        population_tot[person].payoff+=SD_L;
        population_tot[neighbour].payoff+=SD_W;
    }
    if(population_tot[person].cooperate==0 && population_tot[neighbour].cooperate==1){
        population_tot[person].payoff+=SD_W;
        population_tot[neighbour].payoff+=SD_L;
    }
    if(population_tot[person].cooperate==0 && population_tot[neighbour].cooperate==0){
        population_tot[person].payoff+=SD_X;
        population_tot[neighbour].payoff+=SD_X;
    }

}
