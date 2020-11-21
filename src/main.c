#include "citiesReader.h"
#include "adjacency_matrix.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
gcc -o graphe main.c citiesReader.c adjacency_matrix.c -lm
./graphe 250000
*/
void saveGraph(ListOfCities * cities){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<cities->number; i++){
    for(int j=0; j<i; j++){
      fprintf(fileOut, "%i %i\n", i, j);
    }
  }
  fclose(fileOut);
}

/*
void saveGraph_alt(int **matrix){

	FILE *fileout = NULL;
	fileout = fopen("resuGraph.dat", "w");

	for (int i = 0; i < 

}
*/

int main(int argc, char ** argv) {

  if( argc != 2 ){
    perror("Veuillez passer une population minimale en paramètre du programme");
    return EXIT_FAILURE;
  }
//-----------------------------------------------------------------
//--- READING cities
//-----------------------------------------------------------------

	int popMin = atoi(argv[1]);

	ListOfCities* cities;
	cities = citiesReader(popMin);

	// ... just to check! This line can be removed.
	for(int i=0; i<cities->number; i++){
		printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
	}

	int **matrix = adjacency_matrix_creation(cities);

	// Displaying the matrix
	display_matrix (cities, matrix) ;

//-----------------------------------------------------------------
//--- COMPUTING complete graph
//-----------------------------------------------------------------


  /* 
   Écriture du graphe (chaque ligne correspond à une arête)
   !!! Ci-dessous, on écrit le graphe complet pour l'exemple.
   Dans votre rendu, cette fonction prendra un graphe en argument,
   pas une liste de villes.
  */
  saveGraph(cities);


  freeListOfCities(cities);

  return 0;
}

