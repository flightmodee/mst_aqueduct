#include "citiesReader.h"
#include "graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	if( argc != 2 )
	{
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
	for(int i=0; i<cities->number; i++)
		printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
	


	//-----------------------------------------------------------------
	//--- COMPUTING complete graph
	//-----------------------------------------------------------------

	int **matrix = adjacency_matrix_creation(cities);

	// Displaying the matrix
	display_matrix (cities, matrix);

	printf("\n%d", cities->number);
	
	/* 
	Écriture du graphe (chaque ligne correspond à une arête)
	!!! Ci-dessous, on écrit le graphe complet pour l'exemple.
	Dans votre rendu, cette fonction prendra un graphe en argument,
	pas une liste de villes.
	*/
	saveGraph_alt(matrix, cities->number);
	freeListOfCities(cities);

	return 0;
}

