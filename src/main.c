#include "citiesReader.h"
#include "graph.h"
#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char ** argv)
{

	srand(time(NULL));
	if( argc != 2 )
	{
		perror("Veuillez passer une population minimale en paramètre du programme\n");
		return EXIT_FAILURE;
	}
	
	//-----------------------------------------------------------------
	//--- READING cities
	//-----------------------------------------------------------------

	int popMin = atoi(argv[1]);



	ListOfCities* cities;
	cities = citiesReader(popMin);

	//-----------------------------------------------------------------
	//--- COMPUTING complete graph
	//-----------------------------------------------------------------

	int **matrix = adjacency_matrix_creation(cities->number);
	int total_cost = 0;
	adjacency_matrix_filling(matrix, cities);

	// Displaying the matrix
	display_matrix (cities, matrix);
	//Processing an AST for our complete graph.
	matrix = prim(matrix, cities->number, &total_cost);

	printf("The length of the optimal network is of %d\n", total_cost);

	//Saving the graph in a text file

	saveGraph_alt(matrix, cities->number);
	freeListOfCities(cities);

	return 0;
}

