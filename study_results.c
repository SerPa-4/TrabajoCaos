

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

//estudio payoffs y nueva poblacion
void study_results(int matriz_adyacencia[N1+N2][N1+N2], Persona population_tot[N1+N2]);//estudia resultados de la array y realiza los cambios a nuevo array
    double maximo_payoff(Persona population_tot[N1+N2]);//halla maximo payoff de entre todas las parejas
    int compare_with_neighbour(Persona population_tot[N1+N2], Persona new_population[N1+N2],int matriz_adyacencia[N1+N2][N1+N2], int person, double max_diff_payoff)//compara payoff 2 vecinos
    void copy_chain(Persona *x, Persona *y, int length);//copia un array de structs en otro


struct persona{
    int cooperate;  //1 (si) o 0 (no)
    double payoff;  //recompensa total al jugar al juego
}; typedef struct persona Persona;

int main(){
}

void study_results(int matriz_adyacencia[N1+N2][N1+N2], Persona population_tot[N1+N2]){
    Persona new_population[N1+N2];
    copy_chain(population_tot,new_population,N1+N2);//copiamos la buena en la temporar

    max_diff_payoff = maximo_payoff(population_tot);//halla la maxima diferencia de payoff

    for (int person = 0; person < N1 + N2 ; person++){
        compare_with_neighbour(population_tot, new_population, matriz_adyacencia, person, max_diff_payoff);
    }
    //ahora tendremos ya la nueva poblacion (cambios de cooperacion)
    copy_chain(population_new, population_tot, N1+N2);//copiamos la temporal en la buena para tener la nueva

    //al acabar reset all payoff 0
    for(int i = 0; i < N1+N2; i++){
        population_tot[i].payoff = 0;
    }
}

double maximo_payoff(Persona population_tot[N1+N2]){
    double max = 0;
    double min = 0;
    for(int person = 0; person < N1+N2; person++){
        if (population_tot[persona].payoff > max)
            max = population_tot[person].payoff;
        if (population_tot[persona].payoff < min)
            min = population_tot[person].payoff;
        
    }

    return  max-min;
}


//compara con el vecino y devuelve si cambia o no
int compare_with_neighbour(Persona population_tot[N1+N2], Persona new_population[N1+N2],int matriz_adyacencia[N1+N2][N1+N2], int person, double max_diff_payoff){
    int neighbours[N1+N2];
    int index_neigh = 0;

    //obtener listado vecinos
    for (int i = 0; i < N1+N2; i++){
        if (matriz_adyacencia[person][i]){
            neighbours[index_neigh] = i;
            index_neigh += 1;
        }

    }

    //seleccionamos al azar el vecino con el que comparar
    index_neigh += 1;
    index_neigh = rand() % index_neigh //genera un integre aleatorio entre 0 e index_neig-1

    //Nuestro vecino sera: neighbours[index_neigh]
    int vecino = neighbours[index_neigh];
    double payoff_rival = population_tot[vecino].payoff;
    double diff_payoff = payoff_rival-population_tot[person]  ;
    //si rival tiene mas dineros
    if (diff_payoff > 0);
        //proporcional a la diferneicai de dinero, metodo altura
        double aleatoria = rand()/(double)(RAND_MAX+1);
        double comparar = diff_payoff/max_diff_payoff;
        if (aleatoria < comparar){
            new_population[person].cooperate = population_tot.tot[vecino].cooperate;
        }
    


}








void copy_chain(Persona *x, Persona *y, int length){    //copia contenidos una struct en otra
    for(int i=0;i<length;i++){
        y[i].cooperate=x[i].cooperate;
        y[i].payoff=x[i].payoff;
    }
}

